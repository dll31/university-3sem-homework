
#include <iostream>

#include "utility.h"
#include "simple_algorithm.h"
#include "RabinKarp.h"
#include "KMP.h"
#include "Sunday.h"


int main()
{
    db database = db("database.txt", "outdata.csv");
    database.numberNeedlesForOneHaystack = 10;
    database.numberRepeatValue = 1;

    algorithmsContainer algs;

    algs.addAlgorithm("simple search", simple_Algorithm);
    algs.addAlgorithm("Rabin-Karp", rabinKarp);
    algs.addAlgorithm("Knuth-Morris-Pratt", Algroithm_KMP);
	algs.addAlgorithm("Sunday", Sunday);
    database.loop(algs);

}


