// $Id: extraBits.cc,v 1.1.1.1 2003/07/15 20:15:05 garren Exp $
// ----------------------------------------------------------------------
//
// extraBits.cc
//
// returns everything beyond the 7th digit (e.g. outside the numbering scheme)
//
// ----------------------------------------------------------------------

#include "CLHEP/HepPDT/ParticleID.hh"

namespace HepPDT {

int ParticleID::extraBits( ) const
{
    return abspid()/10000000;
}

} // HepPDT
