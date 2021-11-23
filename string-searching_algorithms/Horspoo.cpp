#define val -1

outputData Algroithm_Harspul_no(std::string& needle, std::string haystack)
{
    int shiftTable[UCHAR_MAX] = {};

    outputData out;

    std::string shiftTableNeedle = needle.substr(0, needle.length() - 1);
    int needle_abs = needle.length();

    for (int i = 0; i <= needle_abs-1; i++)
    {
        if (shiftTable[shiftTableNeedle[i]] == 0)
        {
            shiftTable[shiftTableNeedle[i]] = needle_abs - shiftTableNeedle.find_last_of(shiftTableNeedle[i]) - 1;
        }
    }

    for (size_t i = 0; i < UCHAR_MAX; i++)
        if (shiftTable[i] == 0)
            shiftTable[i] = needle_abs;

    int i = 0;
    while (true)
    {
        if ((i + needle_abs) > haystack.length())
        {
            out.errors.push_back(-1);
            break;
        }

        if (std::equal(&haystack[i], &haystack[i + needle_abs], &needle[0]))
        {
            out.id.push_back(i);
            break;
        }
        else
        {
            int delta = shiftTable[haystack[i + needle_abs - 1]];
            if (delta > needle_abs || delta <= 0)
                delta = needle_abs;
            i += delta;
        }
    }
    return out;
}
