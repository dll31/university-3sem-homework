#include <iostream>
#include <string>
#include <vector> 


using namespace std;

string::size_type KMP(const string& S, const string& pattern)
{
	vector<int> pf(pattern.length());

	pf[0] = 0;
	for (int k = 0, i = 1; i < pattern.length(); ++i)
	{
		if (pattern[i] == pattern[k])
		{
			k++;
			pf[i] = k;
		}
		else if (k == 0)
		{
			pf[i] = 0;
		}
		else
		{
			k = pf[k - 1];
		}
	}
}

int main()
{
	string pattern = "st";
	string ss = "testovastroka";
	KMP(ss, pattern);

	return 0;
}