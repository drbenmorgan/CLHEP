// $Id: RandBit.cc,v 1.4 2003/08/13 20:00:12 garren Exp $
// -*- C++ -*-
//
// -----------------------------------------------------------------------
//                             HEP Random
//                          --- RandBit ---
//                      class implementation file
// -----------------------------------------------------------------------
// This file is part of Geant4 (simulation toolkit for HEP).

// =======================================================================
// M Fischler     - Created from RandFlat.cc, deleting almost all the content
//		    since inheritance takes care of it.  2/15/00
// =======================================================================

#include "CLHEP/Random/defs.h"
#include "CLHEP/Random/RandBit.h"

namespace CLHEP {

RandBit::~RandBit() {
}

RandBit::RandBit(const RandBit& right) : RandFlat(right) {
}

}  // namespace CLHEP

