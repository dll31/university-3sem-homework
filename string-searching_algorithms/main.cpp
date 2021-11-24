
#include <iostream>

#include "utility.h"
#include "simple_algorithm.h"
#include "RabinKarp.h"
#include "KMP.h"
#include "Harspul.h"


int main()
{
    db database = db("database.txt", "outdata.csv");
    database.numberNeedlesForOneHaystack = 100;
    database.numberRepeatValue = 10;

    algorithmsContainer algs;

    algs.addAlgorithm("brute force algorithm", simple_Algorithm);
    algs.addAlgorithm("Rabin-Karp algorithm", rabinKarp);
    algs.addAlgorithm("Knuth-Morris-Pratt algorithm", Algroithm_KMP);
    algs.addAlgorithm("Boyer-Moore-Horspool algorithm", Algroithm_Harspul);

    database.loop(algs);

}


