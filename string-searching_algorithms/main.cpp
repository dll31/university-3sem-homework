
#include <iostream>

#include "utility.h"
#include "simple_algorithm.h"


int main()
{
    //right solution: 57, 80, 185.
    std::string haystack = "One of the use cases of pointers to const elements is as function parameters: a function that takes a pointer to non-const as parameter can modify the value passed as argument, while a function that takes a pointer to const as parameter cannot.";
    std::string needle = "func";

    db database = db("database.txt");

    algorithm alg;
    alg.name = "simple search";
    alg.alg = simple_Algorithm;

    algorithms algs;
    algs.allAlgs.push_back(alg);

    database.loop(algs);


    int x = 0;
    //outputData data = simple_Algorithm(needle, haystack);
    
    /*if (data.errors.empty())
    {
        for (auto i : data.id)
        {
            std::cout << i << '\n';
        }
    }
    else
    {
        std::cout << data.errors[0];
    }*/
    
}


