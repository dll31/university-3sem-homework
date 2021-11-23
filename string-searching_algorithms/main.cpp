
#include <iostream>

#include "utility.h"
#include "simple_algorithm.h"
#include "RabinKarp.h"
#include "KMP.h"


int main()
{
    db database = db("database.txt", "outdata.csv");
    database.numberNeedlesForOneHaystack = 100;
    database.numberRepeatValue = 10;

    algorithmsContainer algs;

    algs.addAlgorithm("simple search", simple_Algorithm);
    algs.addAlgorithm("Rabin-Karp", rabinKarp);
    algs.addAlgorithm("Knuth-Morris-Pratt", Algroithm_KMP);

    database.loop(algs);

}


