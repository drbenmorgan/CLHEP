// $Id: RandBit.cc,v 1.2 2003/07/17 19:20:02 garren Exp $
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

#include "CLHEP/Random/RandBit.h"

namespace CLHEP {

RandBit::~RandBit() {
}

RandBit::RandBit(const RandBit& right) : RandFlat(right) {
}

}  // namespace CLHEP

