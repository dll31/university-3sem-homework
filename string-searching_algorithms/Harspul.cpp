#define val -1
#include "climits"
#include "Harspul.h"

outputData Algroithm_Harspul(std::string& needle, std::string haystack)
{
    int shiftTable[UCHAR_MAX] = {};

    outputData out;

    std::string shiftTableNeedle = needle.substr(0, needle.length() - 1);
    int lengthNeedle = needle.length();

    for (int i = 0; i <= lengthNeedle - 1; i++)
    {
        if (shiftTable[shiftTableNeedle[i]] == 0)
        {
            shiftTable[shiftTableNeedle[i]] = lengthNeedle - shiftTableNeedle.find_last_of(shiftTableNeedle[i]) - 1;
        }
    }

    for (size_t i = 0; i < UCHAR_MAX; i++)
        if (shiftTable[i] == 0)
            shiftTable[i] = lengthNeedle;

    int i = 0;
    while (true)
    {
        if ((i + lengthNeedle) > haystack.length())
        {
            out.errors.push_back(-1);
            break;
        }

        if (std::equal(&haystack[i], &haystack[i + lengthNeedle], &needle[0]))
        {
            out.id.push_back(i);
            break;
        }
        else
        {
            int shift= shiftTable[haystack[i + lengthNeedle - 1]];
            if (shift > lengthNeedle || shift <= 0)
                shift = lengthNeedle;
            i += shift;
        }
    }
    return out;
}

