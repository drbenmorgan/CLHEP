// $Id: RandomEngine.cc,v 1.1.1.1 2003/07/15 20:15:05 garren Exp $
// -*- C++ -*-
//
// ------------------------------------------------------------------------
//                             HEP Random
//                       --- HepRandomEngine ---
//                      class implementation file
// ------------------------------------------------------------------------
// This file is part of Geant4 (simulation toolkit for HEP).

// ========================================================================
// Gabriele Cosmo - Created: 5th September 1995
//                - Minor corrections: 31st October 1996
//                - Moved table of seeds to HepRandom: 19th March 1998
// Ken Smith      - Added conversion operators:  6th Aug 1998
// =======================================================================

#include "CLHEP/Random/RandomEngine.h"
#include <cmath>	// for pow()

//------------------------- HepRandomEngine ------------------------------

HepRandomEngine::HepRandomEngine() 
: theSeeds(&theSeed),
  exponent_bit_32( pow(2.,32.) )
{
  theSeed = 19780503L;
}

HepRandomEngine::~HepRandomEngine() {}

HepRandomEngine::operator double() {
  return flat();
}

HepRandomEngine::operator float() {
  return float( flat() );
}

HepRandomEngine::operator unsigned int() {
  return (unsigned int)( flat() * exponent_bit_32 );
}
