
#include <iostream>

#include "utility.h"
#include "simple_algorithm.h"
#include "Harspul.h"


int main()
{
    db database = db("database.txt");
    database.numberNeedlesForOneHaystack = 100;

    algorithmsContainer algs;
    //algs.addAlgorithm("simple search", simple_Algorithm);
    algs.addAlgorithm("Boyer-Moore-Horspoo", Algroithm_Harspul);
    /*std::string haystack = "One of the use cases of pointers to const elements is as function parameters: a function that takes a pointer to non-const as parameter can modify the value passed as argument, while a function that takes a pointer to const as parameter cannot.";
    std::string needle = "e of the use cases of pointers to const elements is as function parameters: a function that takes a pointer to non-const as parameter can modify the value passed as argument, while a function that takes a pointer to const as parameter cannot.";
    outputData data=Algroithm_Harspul(needle, haystack);
    for (auto i : data.id)
    {
      std::cout << i << '\n';
    }*/
    database.loop(algs);

}


