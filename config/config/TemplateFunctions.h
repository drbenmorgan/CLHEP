#include "CLHEP/config/defs.h"
#ifdef ENABLE_BACKWARDS_COMPATIBILITY
// -*- C++ -*-
// CLASSDOC OFF
// $Id: TemplateFunctions.h,v 1.1.2.3 2004/07/01 17:38:51 garren Exp $
// ---------------------------------------------------------------------------
// CLASSDOC ON
//
// This file is a part of the CLHEP - a Class Library for High Energy Physics.
//
// This file contains template definitions of some usefull functions.
//
// sqr was already replaced by sqrt in CLHEP 1.8 so we do not include it here
//
#ifndef HEP_TEMPLATEFUNCTIONS_H
#define HEP_TEMPLATEFUNCTIONS_H

#include <algorithm>  // for min() and max()
#include <cmath>      // double abs()
#include <stdlib.h>   // int abs()

#include "CLHEP/config/CLHEP.h"

using namespace std;

// Geant 4.6.2 still has at least one reference to sqr
#ifndef CLHEP_SQR_DEFINED
#define CLHEP_SQR_DEFINED
#ifdef sqr
#undef sqr
#endif
template <class T>
inline T sqr(const T& x) {
  return x*x;
}
#endif

// Geant4 calls abs(CLHEP::HepLorentzVector)
#ifndef CLHEP_ABS_DEFINED
#define CLHEP_ABS_DEFINED
#ifdef abs
#undef abs
#endif
template <class T>
inline T abs(const T& a) {
  return a < 0 ? -a : a;
}
#endif

#endif /* HEP_TEMPLATEFUNCTIONS_H */

#endif	// ENABLE_BACKWARDS_COMPATIBILITY
