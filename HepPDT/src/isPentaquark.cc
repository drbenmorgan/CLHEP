// ----------------------------------------------------------------------
//
// isPentaquark.cc
//
//  check to see if this is a valid pentaquark
//
// ----------------------------------------------------------------------

#include "CLHEP/HepPDT/ParticleID.hh"

namespace HepPDT {

bool ParticleID::isPentaquark( ) const
{
    // a pentaquark is of the form 9abcdej,
    // where j is the spin and a, b, c, d, and e are quarks
    if( extraBits() > 0 ) { return false; }
    if( digit(n) != 9 )  { return false; }
    if( digit(nr) == 9 || digit(nr) == 0 )  { return false; }
    if( digit(nj) == 9 || digit(nl) == 0 )  { return false; }
    if( digit(nq1) == 0 )  { return false; }
    if( digit(nq2) == 0 )  { return false; }
    if( digit(nq3) == 0 )  { return false; }
    if( digit(nj) == 0 )  { return false; }
    // check ordering
    if( digit(nq2) > digit(nq1) )  { return false; }
    if( digit(nq1) > digit(nl) )  { return false; }
    if( digit(nl) > digit(nr) )  { return false; }
    return true;
}

} // HepPDT
