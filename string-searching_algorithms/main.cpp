
#include <iostream>

#include "utility.h"
#include "simple_algorithm.h"
#include "Harspul.h"


int main()
{
    db database = db("database.txt");
    database.numberNeedlesForOneHaystack = 100;

    algorithmsContainer algs;

    algs.addAlgorithm("simple search", simple_Algorithm);
    algs.addAlgorithm("Boyer-Moore-Horspoo", Algroithm_Harspul);

    database.loop(algs);

}


