// ----------------------------------------------------------------------
//
// testBug73093 -- Test of CLHEP::Ranlux64Engine with 64 bit seeds
//
// Frank Winklmeier  2010-09-24 
// L. Garren	     2010-10-21	rewritten for test suite
// 
// ----------------------------------------------------------------------

#include <iostream>
#include <cmath>
#include <stdlib.h>

#include "CLHEP/Random/Ranlux64Engine.h"

using namespace std;

int valid_range( )
{
    std::ofstream output("testBug73093.cout");  

    int bad = 0;
    long seed;
    long mult=-235421;
    // use several seeds
    for( int il=0; il<100; ++il ) {
	if(  sizeof(long) > 4 ) {
            // using atol so 32bit compilers won't complain
            seed =       atol("9899876543210000");
	    mult = mult + atol("120034020050070");
	} else {
            seed =       987654321;
	    mult = mult + 12003400;
	}
	seed += il*mult;

	CLHEP::Ranlux64Engine rng;
	const long N = 20;

	rng.setSeed(seed, /*lux*/ 1);
	output <<  endl;
	output << "sizeof(long) = " << sizeof(long) << endl;
	output << "Generating " << N << " random numbers with seed " << seed << endl;
	output << "Using seed " << seed <<  endl;

	double sum(0);
	for (long i=0; i<N; ++i) {
	  double r = rng.flat();
	  if( abs(r) > 1.0 ) ++bad;
	  output << r << endl;
	  sum += r;
	}  

	output << "Sum: " << sum << endl;
	output << "Average: " << sum / N << endl;
    }
    
    return bad;
}

int check_sequence()
{
    // if the seed is less than 32bits long on a 64bit machine,  the random
    // number sequence should be the same as the sequence on a 32bit machine
    std::ofstream output("testBug73093.seq");  
    int bad = 0;
    long seed;
    long mult=-235421;
    // use several seeds
    for( int il=0; il<50; ++il ) {
        seed = 97654321;
	seed += il*mult;

	CLHEP::Ranlux64Engine rng;
	const long N = 20;

	rng.setSeed(seed, /*lux*/ 1);

	double sum(0);
	for (long i=0; i<N; ++i) {
	  double r = rng.flat();
	  if( abs(r) > 1.0 ) ++bad;
	  output << "[" << il << "][" << i << "] = " << r << ";" << endl;
	  sum += r;
	}  
    }
    return bad;
}

int main()
{

    int bad = 0;
    bad += valid_range( );
    bad += check_sequence( );
    
    return bad;
}
