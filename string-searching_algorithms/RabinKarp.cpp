#include "RabinKarp.h"

#define d 256

outputData rabinKarp(std::string& pattern, std::string text) 
{
  outputData out;
  int prime_number = 58789;
  int len_of_pattern = pattern.length();
  int len_of_text = text.length();
  int i, j;
  int hash_for_pattern = 0;
  int hash_for_txt = 0;
  int h = 1;

  for (i = 0; i < len_of_pattern - 1; i++)
    h = (h * d) % prime_number;

  for (i = 0; i < len_of_pattern; i++) {
    hash_for_pattern = (d * hash_for_pattern + pattern[i]) % prime_number;
    hash_for_txt = (d * hash_for_txt + text[i]) % prime_number;
  }

  for (i = 0; i <= len_of_text - len_of_pattern; i++) {
    if (hash_for_pattern == hash_for_txt) {
      for (j = 0; j < len_of_pattern; j++) {
        if (text[i + j] != pattern[j])
          break;
      }

      if (j == len_of_pattern)
      {
        out.id.push_back(i);
        return out;
      }
    }

    if (i < len_of_text - len_of_pattern) {
      hash_for_txt = (d * (hash_for_txt - text[i] * h) + text[i + len_of_pattern]) % prime_number;

      if (hash_for_txt < 0)
        hash_for_txt = (hash_for_txt + prime_number);
    }
  }
  out.errors.push_back(-1);
  return out;
}

