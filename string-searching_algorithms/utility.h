#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <unordered_map>
#include <functional>
#include <fstream>


struct outputData
{
    std::vector<int> id;
    std::vector<int> errors;
};


struct dbFsFrame
{
    std::string haystackFilename;
};


struct needleWithSol
{
    std::string needle;
    int sol;

    needleWithSol(std::string& needle, int sol)
    {
        this->needle = needle;
        this->sol = sol;
    }
};


struct dbDataFrame
{
    std::string haystack;
    std::vector<needleWithSol> needlesWithSolutions;
};


struct algorithm
{
    std::string name;
    std::function<outputData(std::string&, std::string)> alg;
};


class algorithmsContainer
{
public:
    std::vector<algorithm> algsList;

    void addAlgorithm(std::string name, std::function<outputData(std::string&, std::string)> alg);

};


class db
{
    std::string indexFile;
    std::vector<dbFsFrame> index;

    dbDataFrame currentFrame;

    int parseIndexFile();
    int loadHaystack(std::string& haystackFilename);
    void needlesGenerator(int countNeedles);

public:
    int numberNeedlesForOneHaystack = 100;
    db(std::string indexFilename);
    void algsLoop(algorithmsContainer& algs, needleWithSol& curNeedleWithSol);
    void loop(algorithmsContainer& algs);

    

};


