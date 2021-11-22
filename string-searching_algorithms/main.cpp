
#include <iostream>

#include "utility.h"
#include "simple_algorithm.h"


int main()
{
    db database = db("database.txt");
    database.numberNeedlesForOneHaystack = 100;

    algorithmsContainer algs;

    algs.addAlgorithm("simple search", simple_Algorithm);

    database.loop(algs);

}


