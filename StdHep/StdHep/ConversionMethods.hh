// $Id: ConversionMethods.hh,v 1.1.1.1 2003/07/15 20:15:05 garren Exp $
// ----------------------------------------------------------------------
//
// ConversionMethods.hh
// L. Garren
//
//  defines various free functions:
//           build StdEvent from HEPEVT, and vice-versa
//  printVersion defined here
//
// user code:
//   CBcm * tmp = CBcm::instance();
//   tmp->stdcm1()->nhep;
// ----------------------------------------------------------------------
#ifndef CONVERSIONMETHODS_HH
#define CONVERSIONMETHODS_HH

#include <iostream>

#include "CLHEP/StdHep/StdRunInfoConvert.hh"
#include "CLHEP/StdHep/StdEventConvert.hh"
#include "CLHEP/StdHep/CBcm.hh"
#include "CLHEP/StdHep/CBstdhep.hh"
#include "CLHEP/HepMC/CBInterface.h"

namespace StdHep {

/**
 * @author
 * @ingroup StdHep
 */

typedef  StdEventConvert<CBstdhep>    ConvertStdHep;
typedef  HepMC::CBInterface<CBstdhep> FIstdhep;
typedef  HepMC::CBInterface<CBcm>     FIcm;

} // StdHep

#endif // CONVERSIONMETHODS_HH
