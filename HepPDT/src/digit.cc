// $Id: digit.cc,v 1.1.1.1 2003/07/15 20:15:05 garren Exp $
// ----------------------------------------------------------------------
//
// digit.cc
//
//  split the PID into constituent integers
//
// ----------------------------------------------------------------------

#include "CLHEP/HepPDT/ParticleID.hh"

namespace HepPDT {

unsigned short ParticleID::digit( location loc ) const
{
    //  PID digits (base 10) are: n nr nl nq1 nq2 nq3 nj
    //  the location enum provides a convenient index into the PID
    int numerator = (int) pow(10.0,(loc-1));
    return (abspid()/numerator)%10;
}

} // HepPDT
