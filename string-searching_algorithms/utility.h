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
    std::string needlesWithSolitionFilename;
};

struct dbDataFrame
{
    std::string haystack;
    std::string needle;
    int solution;
};

struct algorithm
{
    std::string name;
    std::function<outputData(std::string&, std::string)> alg;
};


struct algorithms
{
    std::vector<algorithm> allAlgs;
};


class db
{
    std::string indexFile;
    std::vector<dbFsFrame> index;

    dbDataFrame currentFrame;

    int parseIndexFile();
    int loadFrame(dbFsFrame& currentFsFrame);
    void parseError(int error);

public:
    db(std::string indexFilename);
    void loop(algorithms& algs);

};


