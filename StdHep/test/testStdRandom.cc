//////////////////////////////////////////////////////////////////////////
// Lynn Garren
//
// This program tests StdHep::StdRandom
// 
//////////////////////////////////////////////////////////////////////////

#include <vector>
#include <iostream>

#include "CLHEP/StdHep/StdRandom.hh"

int main() { 

    int status=0;
    StdHep::StdRandom rstate;

    // fill and save an arbitrary vector just for grins
    std::vector<unsigned long> rs;
    for( int i=0; i<6; ++i) { rs.push_back(i*312); }
    rstate.putState( rs );
    rstate.print();
    
    return status;
}
