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


class outFile 
{
private:
    std::string outDataFilename;
    bool isOpen;
public:
    std::ofstream out;

    outFile();
    void init(std::string outDataFilename);
    int openFile();
    bool isOpenF();
    //~outFile();
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
    outFile outputFile;
    
    int numberNeedlesForOneHaystack = 100;
    int numberRepeatValue = 10;

    db(std::string indexFilename, std::string outFilename);
    void algsLoop(algorithmsContainer& algs);
    void loop(algorithmsContainer& algs);
};


