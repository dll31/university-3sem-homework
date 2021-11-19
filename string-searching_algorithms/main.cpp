
#include <iostream>
#include "utility.h"
#include "simple_algorithm.h"
#include "Harspul.h"


int main()
{
    //right solution: 57, 80, 185.
    std::string haystack = "One of the use cases of pointers to const elements is as function parameters: a function that takes a pointer to non-const as parameter can modify the value passed as argument, while a function that takes a pointer to const as parameter cannot.";
    std::string needle = "elements";

    //outputData data = simple_Algorithm(needle, haystack);
    outputData data = Algroithm_Harspul(needle, haystack);
    
    for (auto i : data.id)
    {   
        std::cout << i << '\n';
    }
    
}


