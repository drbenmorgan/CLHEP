// $Id: ConvertHEPEVT.h,v 1.1.1.1 2003/07/15 20:15:05 garren Exp $
// ----------------------------------------------------------------------
//
// ConvertHEPEVT.h
//
//  defines methods to build GenEvent from HEPEVT, and vice-versa
//
// User Code:
//#include "CLHEP/HepMC/ConvertHEPEVT.h"
//#include "CLHEP/HepMC/GenEvent.h"
//  ...
//    HepMC::ConvertHEPEVT conv;
//    HepMC::GenEvent* evt = conv.getGenEventfromHEPEVT();
//    bool tf = conv.fromGenEvent( evt );
//
// ----------------------------------------------------------------------
#ifndef CONVERTHEPEVT_H
#define CONVERTHEPEVT_H

#include "CLHEP/HepMC/GenEventConvert.h"
#include "CLHEP/HepMC/CBhepevt.h"

namespace HepMC {

typedef  GenEventConvert<CBhepevt>  ConvertHEPEVT;
typedef  CBInterface<CBhepevt>      FIhepevt;

}

#endif // CONVERTHEPEVT_H
