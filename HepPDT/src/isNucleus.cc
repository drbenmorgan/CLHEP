// $Id: isNucleus.cc,v 1.1.1.1.2.1 2005/03/16 01:36:02 garren Exp $
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
     // a proton can also be a Hydrogen nucleus
     if( abspid() == 2212 ) { return true; }
     // ad-hoc nuclear fragment numbering
     if( ( digit(n10) == 1 ) && ( digit(nq2) == 0 ) && ( digit(nq3) == 0 ) )
         { return true; }
     return false;
}

} // HepPDT
