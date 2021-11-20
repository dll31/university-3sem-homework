
#include <iostream>

#include "utility.h"
#include "simple_algorithm.h"


int main()
{
    db database = db("database.txt");
    algorithmsContainer algs;

    algs.addAlgorithm("simple search", simple_Algorithm);

    database.loop(algs);

}


