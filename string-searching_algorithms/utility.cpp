#include "utility.h"
#include <chrono>
#include <random>

void algorithmsContainer::addAlgorithm(std::string name, std::function<outputData(std::string&, std::string)> alg)
{
    algorithm a = { name, alg };
    this->algsList.push_back(a);
}


db::db(std::string indexFilename)
{
    this->indexFile = indexFilename;
    this->parseIndexFile();
}


int db::parseIndexFile()
{
    int error = 0;
    
    std::ifstream st(this->indexFile);
    if (!st.is_open())
        return -1;

    while (st.peek() != EOF)
    {
        dbFsFrame fsFrame;
        st >> fsFrame.haystackFilename;
        
        if (st.fail())
        {
            std::cout << "parse element corrupt!\n";
            error = -2;
            continue;
        }

        std::cout << "parse element complete\n";

        this->index.push_back(fsFrame);
    }

    st.close();
    std::cout << '\n';
    
    return error;
}


int db::loadHaystack(std::string& haystackFilename)
{
    currentFrame.haystack = {};
    
    std::ifstream st(haystackFilename);
    if (!st.is_open())
        return -1;

    while (st.peek() != EOF)
    {
        std::string str;
        std::getline(st, str);
        this->currentFrame.haystack += str;
    }

    st.close();
    return 0;
}


void profit(int sol, long int duration)
{
    std::cout << "Successful search! " << "Solution: " << sol << '\n';
    std::cout << "duration " << duration << " microseconds\n";
}


void no(int rightSol, int wrongSol)
{
    std::cout << "Wrong search! " << "Right solution: " << rightSol << " Get solution: " << wrongSol << '\n';
}


void db::algsLoop(algorithmsContainer& algs, needleWithSol& curNeedleWithSol)
{
    for (auto a : algs.algsList)
    {
        std::cout << "Algorithm name: " << a.name << '\n';

        auto start = std::chrono::system_clock::now();
        outputData out = a.alg(curNeedleWithSol.needle, currentFrame.haystack);
        auto finish = std::chrono::system_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(finish - start).count();

        if (out.errors.size() == 1)
        {
            if (curNeedleWithSol.sol == -1)
            {
                profit(curNeedleWithSol.sol, duration);
            }
            else
            {
                no(curNeedleWithSol.sol, out.errors.front());
            }
        }
        else if (out.id.size() == 1)
        {
            if (curNeedleWithSol.sol == out.id.front())
            {
                profit(curNeedleWithSol.sol, duration);
            }
            else
            {
                no(curNeedleWithSol.sol, out.id.front());
            }
        }
        else
        {
            std::cout << "Something wrong.\n";
        }
        std::cout << '\n';
    }
}


void db::loop(algorithmsContainer& algs)
{    
    for (auto ind : index)
    {
        if (loadHaystack(ind.haystackFilename) > 0)
        {
            std::cout << "broken Fs frame " << ind.haystackFilename << '\n';
            continue;
        }
        else
        {
            needlesGenerator(numberNeedlesForOneHaystack);
            
            for (auto i : currentFrame.needlesWithSolutions)
            {
                algsLoop(algs, i);
            }
        } 
    }
}


int getRandomBetween(int leftBound, int rightBound)
{
    std::default_random_engine generator;
    std::uniform_int_distribution<int> distribution(leftBound, rightBound);
    return distribution(generator);
}


void db::needlesGenerator(int countNeedles)
{
    int len = (int)currentFrame.haystack.length();
    int pieceRange = len / countNeedles;

    std::default_random_engine generator;
    

    for (int i = 1; i <= countNeedles; i++)
    {
        int leftBound = (i - 1) * pieceRange;
        int rightBound = (i) * pieceRange;

        int leftNeeldeBound = getRandomBetween(leftBound, rightBound);
        
        int rightNeeldeBound = getRandomBetween(leftNeeldeBound, rightBound);

        int sol = leftNeeldeBound;
        std::string needle = currentFrame.haystack.substr(leftNeeldeBound, rightNeeldeBound - leftNeeldeBound);

        currentFrame.needlesWithSolutions.push_back(needleWithSol(needle, sol));
    }
}
