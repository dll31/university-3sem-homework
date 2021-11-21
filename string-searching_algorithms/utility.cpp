#include "utility.h"
#include <chrono>

void algorithmsContainer::addAlgorithm(std::string name, std::function<outputData(std::string&, std::string)> alg)
{
    algorithm a = { name, alg };
    this->algsList.push_back(a);
}


db::db(std::string indexFilename)
{
    this->indexFile = indexFilename;
    this->parseError(this->parseIndexFile());
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
        st >> fsFrame.haystackFilename >> fsFrame.needlesWithSolitionFilename;
        
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


int db::loadFrame(dbFsFrame& currentFsFrame)
{
    std::ifstream st(currentFsFrame.haystackFilename);
    if (!st.is_open())
        return -1;

    while (st.peek() != EOF)
    {
        std::string str;
        std::getline(st, str);
        this->currentFrame.haystack += str;
    }

    st.close();

    std::ifstream _st(currentFsFrame.needlesWithSolitionFilename);
    if (!_st.is_open())
        return -1;

    std::string str;
    int sol; 
    _st >> str >> sol;
    if (_st.fail())
        return -3;

    _st.close();
    currentFrame.needle = str;
    currentFrame.solution = sol;

    return 0;
}


void db::loop(algorithmsContainer& algs)
{
    for (auto ind : index)
    {
        if (loadFrame(ind))
        {
            std::cout << "broken Fs frame " << ind.haystackFilename << " " << ind.needlesWithSolitionFilename << '\n';
            continue;
        }

        for (auto a : algs.algsList)
        {
            std::cout << "Algorithm name: " << a.name << '\n';
            
            auto start = std::chrono::system_clock::now();
            outputData out = a.alg(currentFrame.needle, currentFrame.haystack);
            auto finish = std::chrono::system_clock::now();
            auto duration = std::chrono::duration_cast<std::chrono::microseconds>(finish - start).count();

            if (currentFrame.solution == -1 && out.id.empty() && out.errors.size() == 1)
            {
                std::cout << "Successful search! " << "Solution: " << -1 << '\n';
                std::cout << "duration " << duration << " ms\n";
            }
            else
            {
                if (currentFrame.solution == out.id[0])
                {
                    std::cout << "Successful search! " << "Solution: " << out.id[0] << '\n';
                    std::cout << "duration " << duration << " ms\n";
                }
                else
                    std::cout << "Wrong search! " << "Right solution: " << currentFrame.solution << " Get solution: " << out.id[0] << '\n';
            }
            std::cout << '\n';
        }
    }
    
    
}


void db::parseError(int error)
{

}