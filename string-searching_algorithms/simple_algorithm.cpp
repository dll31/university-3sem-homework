
#include "simple_algorithm.h"


outputData simple_Algorithm(std::string& needle, std::string haystack)
{
    outputData out;

    int haystackLen = (int)haystack.length();
    int needleLen = (int)needle.length();


    for (int i = 0; i < (haystack.length() - needle.length()); i++)
    {
        for (int j = 0; j < needle.length(); j++)
        {
            if (!std::equal(&haystack[i + j], &haystack[i + j + 1], &needle[j]))
                break;

            if (j == needle.length() - 1)
                out.sId.push_back(i);
        }
    }

    if (out.sId.empty())
        out.errors.push_back(-1);

    return out;
}