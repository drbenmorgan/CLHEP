// $Id: 
// -*- C++ -*-
//
// -----------------------------------------------------------------------
//                             HEP Random
//                      --- StaticRandomStates ---
//                      class implementation file
// -----------------------------------------------------------------------
//
// =======================================================================
// Mark Fischler  - Created: Dec. 21, 2004
// =======================================================================

#include "CLHEP/Random/StaticRandomStates.h"
#include "CLHEP/Random/RandGauss.h"
#include "CLHEP/Random/RandFlat.h"

//======================//
//                      //
// Maintenance warning: //
//			//
//======================//
//
// Currently, only two distributions (RandFlat and RandGauss) have cached
// distribution state.  All such distributions must be saved below, so if
// another such distribution is added, this implementation file must be 
// modified to reflect that.

namespace CLHEP {


std::ostream & StaticRandomStates::save(std::ostream & os){
  RandGauss::saveFullState(os);
  RandFlat::saveDistState(os);
  return os;
}

std::istream & StaticRandomStates::restore(std::istream & is) {
  RandGauss::restoreFullState(is);
  RandFlat::restoreDistState(is);
  return is;
}


}  // namespace CLHEP
