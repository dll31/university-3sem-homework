#include "Header.h"

using namespace std;

outputData Algroithm_KMP(const string& pattern, const string& S )
{
	outputData out;
	vector<int> pf(pattern.length());
	cout << "Index, gde peresikaetsy podstroka i stroka" << endl;

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

	for (int k = 0, i = 0; i < S.length(); ++i)
	{
		if (pattern[k] == S[i])
		{
			k++;

			if (k == pattern.length())
			{
				out.id.push_back(i - pattern.length() + 1);
			}

		}
		else
		{
			if (k != 0)
			{
				k = pf[k - 1];
			}
		}
	}
	if (out.id.empty())
		out.errors.push_back(-1);
	return out;
};