#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

struct data
{
    std::string& needle;
    std::istream haystack;
};


struct outputData
{
    std::vector<int> sId;
    std::vector<int> errors;
};