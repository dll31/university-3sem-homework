#include "utility.h"
#include <chrono>
#include <random>


outFile::outFile()
{
    bool isOpen = false;
}

void outFile::init(std::string outDataFilename)
{
    this->outDataFilename = outDataFilename;

    this->out.open(this->outDataFilename);
    if (!this->out.is_open())
        isOpen = false;
    else
        isOpen = true;
}

int outFile::openFile()
{
    std::ofstream out(this->outDataFilename);
    if (!out.is_open())
        isOpen = false;
    else
        isOpen = true;
    return isOpen;
}

bool outFile::isOpenF()
{
    return isOpen;
}


//outFile::~outFile()
//{
//    if (this->isOpenF())
//        this->out.close();
//}


void algorithmsContainer::addAlgorithm(std::string name, std::function<outputData(std::string&, std::string)> alg)
{
    algorithm a = { name, alg };
    this->algsList.push_back(a);
}


db::db(std::string indexFilename, std::string outFilename)
{
    this->indexFile = indexFilename;
    this->parseIndexFile();
    this->outputFile.init(outFilename);

    if (!this->outputFile.isOpenF())
        std::cout << "Broken out filename " << outFilename << '\n';
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


void db::algsLoop(algorithmsContainer& algs)
{
    for (auto a : algs.algsList)
    {
        std::cout << "Algorithm name: " << a.name << '\n';

        if (outputFile.isOpenF())
            outputFile.out << a.name << '\n';
        
        for (auto j : currentFrame.needlesWithSolutions)
        {
            for (int i = 0; i < numberRepeatValue; i++)
            {
                auto start = std::chrono::system_clock::now();
                outputData out = a.alg(j.needle, currentFrame.haystack);
                auto finish = std::chrono::system_clock::now();
                auto duration = std::chrono::duration_cast<std::chrono::microseconds>(finish - start).count();

                if (out.errors.size() == 1)
                {
                    if (j.sol == -1)
                    {
                        profit(j.sol, duration);
                        outputFile.out << j.sol << ',' << duration << ',';
                    }
                    else
                    {
                        no(j.sol, out.errors.front());
                        outputFile.out << 0 << ',' << -1 << ',';
                    }
                }
                else if (out.id.size() == 1)
                {
                    if (j.sol == out.id.front())
                    {
                        outputFile.out << j.sol << ',' << duration << ',';
                        profit(j.sol, duration);
                    }
                    else
                    {
                        no(j.sol, out.id.front());
                        outputFile.out << 0 << ',' << -1 << ',';
                    }
                }
                else
                {
                    std::cout << "Something wrong.\n";
                }
                std::cout << '\n';
            }
            outputFile.out << '\n';
        }
    }

    outputFile.out.close();
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
            algsLoop(algs);
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
