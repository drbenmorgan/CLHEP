// $Id: isNucleus.cc,v 1.1.1.1 2003/07/15 20:15:05 garren Exp $
// ----------------------------------------------------------------------
//
// isNucleus.cc
//
//  extended PID type
//
// This implements an ad-hoc numbering scheme for ions.
// Ion numbers are FAAAZZZ00L. F = 1 and flags this as an ion.
// AAA, and ZZZ are A (number of nucleons) and Z (number of protons) respectively.
// The first digit, L, contains the J-spin as L = 2J + 1.
//
// ----------------------------------------------------------------------

#include "CLHEP/HepPDT/ParticleID.hh"

namespace HepPDT {

bool ParticleID::isNucleus( ) const
{
     if( ( digit(n10) == 1 ) && ( digit(nq2) == 0 ) && ( digit(nq3) == 0 ) )
         { return true; }
     return false;
}

} // HepPDT
