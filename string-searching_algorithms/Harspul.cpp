#pragma warning( push )
#pragma warning( disable : 4789 )
#include "Harspul.h"

#define len 400
int vernut(char haystack, int shift[len],int length)
{
	if (shift[haystack] == 0)
	{
		return length;
	}
	else
	{
		return shift[haystack];
	}
}
bool Proverka(std::string& needle, std::string& haystack, int i,int length)
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
int Slojenie(std::string& needle, std::string& haystack, int shift[len], int i,int length)
{
	int sovpadenia = 0;
	char k = ' ';
	for (int j = length-1;j > 0; --j)
	{
		if (i + j < haystack.length())
		{
			if (haystack[i + j] != needle[j])
			{
				k = haystack[i + j];
				break;
			}
			else
			{
				sovpadenia += 1;
			}
		}
	}
	if (sovpadenia == 0)
	{
		return vernut(k, shift, length);
	}
	else
	{
		return vernut(needle[length-1],shift,length);
	}
}
bool ProverkaElements(char needle, int shift[len])
{
	if (shift[needle] == 0)
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
	int shift[len] = { 0 };
	for (int i = length - 2; i > -1; --i)
	{
		if (ProverkaElements(needle[i], shift))
		{
			shift[needle[i]] = length - 1 - i;
		}
	}
	if (ProverkaElements(needle[length - 1], shift))
	{
		shift[needle[length-1]] = length;
	}
	int i = 0;
	while (i<haystack.length())
	{
		if (Proverka(needle, haystack, i,length))
		{
			out.id.push_back(i);
			break;
		}
		else
		{
			i = i + Slojenie(needle, haystack, shift, i,length);
		}
	}
	if (out.id.empty())
		out.errors.push_back(-1);
	return out;
}
