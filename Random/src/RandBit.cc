// $Id: RandBit.cc,v 1.3 2003/07/25 20:59:21 garren Exp $
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

#include "Random/defs.h"
#include "CLHEP/Random/RandBit.h"

namespace CLHEP {

RandBit::~RandBit() {
}

RandBit::RandBit(const RandBit& right) : RandFlat(right) {
}

}  // namespace CLHEP

