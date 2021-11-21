#pragma warning( push )
#pragma warning( disable : 4789 )
#include "Harspul.h"
int SearchSymbols(char haystack,int length,char elements[20])
{
	int k = -1;
	for (int i = 0; i < length; ++i)
	{
		if (haystack == elements[i])
		{
			k = i;
			break;
		}
	}
	if (k == -1)
	{
		return length;
	}
	else
	{
		return k;
	}
}
bool Proverka(std::string& needle, std::string haystack, int i,int length)
{
	int k = 0;
	for (int j = 0; j <length;++j)
	{
		if (i + j < haystack.length()-1) 
		{
			if (haystack[i + j] != needle[j])
			{
				k += 1;
			}
		}
		else
		{
			break;
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
int Slojenie(std::string& needle, std::string haystack, int shiftTable[20], int i,int length,char elements[20],int lengthShiftAndElements)
{
	int sovpadenia = 0;
	int k = -1;;
	for (int j = length-1;j > 0; --j)
	{
		if (i + j < haystack.length())
		{
			if (haystack[i + j] != needle[j])
			{
				k = j + i;
				break;
			}
			else
			{
				sovpadenia += 1;
			}
		}
	}
	if (sovpadenia== 0)
	{
		return shiftTable[SearchSymbols(haystack[k], lengthShiftAndElements, elements)];
	}
	else
	{
		return shiftTable[SearchSymbols(needle[length-1], lengthShiftAndElements, elements)];
	}
}
bool ProverkaElements(char needle, char Elements[20], int length)
{
	int k = 0;
	for (int i = 0; i < length; ++i)
	{
		if (needle == Elements[i])
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
outputData Algroithm_Harspul(std::string& needle, std::string haystack)
{
	outputData out;
	int length = needle.length();
	char elements[100];
	int shift[100];
	int lengthShiftAndElements = 0;
	for (int i = length - 2; i > -1; --i)
	{
		if (ProverkaElements(needle[i], elements, length))
		{
			elements[lengthShiftAndElements] = needle[i];
			shift[lengthShiftAndElements] = length - 1 - i;
			lengthShiftAndElements += 1;
		}
	}
	shift[lengthShiftAndElements] = length;
	if (ProverkaElements(needle[length - 1], elements, length))
	{
		elements[lengthShiftAndElements] = needle[length-1];
	}
	int i = 0;
	int sovpadenia = 0;
	while (i<haystack.length())
	{
		if (Proverka(needle, haystack, i,length))
		{
			out.id.push_back(i);
			break;
		}
		else
		{
			i = i + Slojenie(needle, haystack, shift, i,length,elements,lengthShiftAndElements);
		}
	}
	if (out.id.empty())
		out.errors.push_back(-1);
	return out;
}
