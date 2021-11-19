#pragma warning( push )
#pragma warning( disable : 4789 )
#include "Harspul.h"
int SearchSymbols(char haystack, std::string& needle)
{
	int k = -1;
	for (int i = 0; i < 8; ++i)
	{
		if (haystack == needle[i])
		{
			k = i;
			break;
		}
	}
	if (k == -1)
	{
		return 7;
	}
	else
	{
		return k;
	}
}
bool Proverka(std::string& needle, std::string haystack, int i)
{
	int k = 0;
	for (int j = 7; j > 0; --j)
	{
		if (haystack[j + i] != needle[j])
		{
			k += 1;
		}
	}
	if (k == 0)
	{
		return true;
	}
	else
	{
		return false;
	}
}
int Slojenie(std::string& needle, std::string haystack, int shiftTable[8], int i)
{
	for (int j = 7; j > 0; --j)
	{
		if (haystack[j + i] != needle[j])
		{
			return shiftTable[SearchSymbols(haystack[j + i], needle)];
		}
	}
}
outputData Algroithm_Harspul(std::string& needle, std::string haystack)
{
	outputData out;
	int length = 8;
	int shiftTable[8];
	for (int i = 0; i < length; ++i)
	{
		if (length-1!=i)
		{
			shiftTable[i] = length - i - 1;
		}
		else
		{
			shiftTable[i] = length;
		}
	}
	int i = 0;
	int slojenie = 8;
	while (i<haystack.length())
	{
		if (Proverka(needle, haystack, i))
		{
			out.id.push_back(i);
			i = i + 8;
		}
		else
		{
			i = i + Slojenie(needle, haystack, shiftTable, i);
		}
	}
	if (out.id.empty())
		out.errors.push_back(-1);
	return out;
}
