// ----------------------------------------------------------------------
//
// digit.cc
// Author: Lynn Garren
//
//  split the PID into constituent integers
//
// ----------------------------------------------------------------------

#include "CLHEP/HepPDT/ParticleID.hh"
#include <cmath>	// for pow()

namespace HepPDT {

unsigned short ParticleID::digit( location loc ) const
{
    //  PID digits (base 10) are: n nr nl nq1 nq2 nq3 nj
    //  the location enum provides a convenient index into the PID
    int numerator = (int) std::pow(10.0,(loc-1));
    return (abspid()/numerator)%10;
}

} // HepPDT
