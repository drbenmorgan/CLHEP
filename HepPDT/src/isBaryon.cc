// $Id: isBaryon.cc,v 1.1.1.1.2.1 2005/03/17 22:42:53 garren Exp $
// ----------------------------------------------------------------------
//
// isBaryon.cc
//
//  check to see if this is a valid baryon
//
// ----------------------------------------------------------------------

#include "CLHEP/HepPDT/ParticleID.hh"

namespace HepPDT {

bool ParticleID::isBaryon( ) const
{
    if( extraBits() > 0 ) { return false; }
    if( abspid() <= 100 ) { return false; }
    if( fundamentalID() <= 100 && fundamentalID() > 0 ) { return false; }
    if( abspid() == 2110 || abspid() == 2210 ) { return true; }
    if( digit(nj) > 0 && digit(nq3) > 0 && digit(nq2) > 0 && digit(nq1) > 0 ) { return true; }
    return false;
}

} // HepPDT
