// $Id: ConvertHEPEVT.h,v 1.2 2003/10/10 15:56:34 garren Exp $
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
#ifndef CONVERT_HEPEVT_H
#define CONVERT_HEPEVT_H

#include "CLHEP/HepMC/GenEventConvert.h"
#include "CLHEP/HepMC/CBhepevt.h"

namespace HepMC {

typedef  GenEventConvert<CBhepevt>  ConvertHEPEVT;
typedef  CBInterface<CBhepevt>      FIhepevt;

}

#endif // CONVERT_HEPEVT_H
