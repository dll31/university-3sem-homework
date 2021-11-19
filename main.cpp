#include <string.h>
#include <iostream>
#include <vector>

#define d 10

struct outputData
{
    std::vector<int> id;
    std::vector<int> errors;
};

outputData rabinKarp(std::string& pattern, std::string text, int q) 
{
  outputData out;
  int m = pattern.length();
  int n = text.length();
  int i, j;
  int p = 0;
  int t = 0;
  int h = 1;

  for (i = 0; i < m - 1; i++)
    h = (h * d) % q;

  for (i = 0; i < m; i++) {
    p = (d * p + pattern[i]) % q;
    t = (d * t + text[i]) % q;
  }

  for (i = 0; i <= n - m; i++) {
    if (p == t) {
      for (j = 0; j < m; j++) {
        if (text[i + j] != pattern[j])
          break;
      }

      if (j == m)
      {
        out.id.push_back(i);
        break;
      }
    }

    if (i < n - m) {
      t = (d * (t - text[i] * h) + text[i + m]) % q;

      if (t < 0)
        t = (t + q);
    }
  }
  if (out.id.empty())
    {
      out.errors.push_back(-1);
    }
  return out;
}

int main() 
{
  outputData data;
  std::string text = "ABCCDDAEFG";
  std::string pattern = "AEFG";
  int q = 13;
  data = rabinKarp(pattern, text, q);
  for (auto i : data.id)
    {   
        std::cout << i << '\n';
    }
}

