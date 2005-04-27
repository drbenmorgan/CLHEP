//////////////////////////////////////////////////////////////////////////
// Lynn Garren
//
// This program tests the random state information in GenEvent
// The remainder of GenEvent is irrelevant for this test
// 
// This test uses the rand() generator, which does not return state information
// Therefore, we save the state by knowing the initial seed and 
// how many times we called rand()
// 
//////////////////////////////////////////////////////////////////////////

#include <vector>
#include <iostream>
#include <stdlib.h>

#include "CLHEP/HepMC/defs.h"
#include "CLHEP/HepMC/GenEvent.h"

std::vector<unsigned long> myState( const unsigned int seed, 
                                    const unsigned int nseq )
{
   std::vector<unsigned long> rndm;
   rndm.push_back((unsigned long)seed);
   rndm.push_back((unsigned long)nseq);
   return rndm;
}

long myRestore( const std::vector<unsigned long>& rv )
{
    unsigned int is, ns, iseq;
    long rnd=0;
    is = rv[0];
    ns = rv[1];
    srand(is);
    for( iseq=0; iseq<ns; ++iseq ) { rnd = rand(); }
    return rnd;
}

int main() { 

    int status=0;
    HepMC::GenEvent evt;
    std::vector<unsigned long> rs;
    long rnd, savernd;
    unsigned int iseq;
    // set some seed
    unsigned int iseed = 3214;
    // fill and save an arbitrary vector just for grins
    for( int i=0; i<5; ++i) { rs.push_back(i*312); }
    evt.set_random_states( rs );
    // print empty event
    // this will show the random state we saved
    evt.print();
    // clear our copy
    rs.clear(); 
    // set the seed for random
    srand(iseed);
    for( iseq=0; iseq<12; ++iseq ) { rnd = rand(); }
    savernd = rnd;
    std::cout << " saving state that produced " << rnd << std::endl;
    rs = myState( iseed, iseq);
    evt.set_random_states( rs );
    for( iseq=0; iseq<14; ++iseq ) { rnd = rand(); }
    std::cout << " throw more numbers, arriving at " << rnd << std::endl;
    rs = evt.random_states( );
    rnd = myRestore( rs );
    std::cout << " state is now back to " << rnd << std::endl;
    if( rnd != savernd ) {
       std::cout << "Random numbers " << rnd << " and " 
                 <<  savernd << " do not match" << std::endl;
       status=1;
    }
    return status;
}
