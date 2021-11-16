
#include <iostream>

#include "utility.h"
#include "simple_algorithm.h"


int main()
{
    //right solution: 57, 80, 185.
    std::string str = "One of the use cases of pointers to const elements is as function parameters: a function that takes a pointer to non-const as parameter can modify the value passed as argument, while a function that takes a pointer to const as parameter cannot.";
    std::string needle = "function";

    outputData data = simple_Algorithm(needle, str);
    
    for (auto i : data.sId)
    {   
        std::cout << i << '\n';
    }
    
}


