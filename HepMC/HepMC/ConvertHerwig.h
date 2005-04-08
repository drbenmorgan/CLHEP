// ----------------------------------------------------------------------
//
// ConvertHerwig.h
//
//  defines methods to build GenEvent from Herwig
//
// User Code:
//#include "CLHEP/HepMC/ConvertHerwig.h"
//#include "CLHEP/HepMC/GenEvent.h"
//  ...
//    HepMC::ConvertHerwig conv;
//    HepMC::GenEvent* evt = conv.getGenEventfromHEPEVT();
//    bool tf = conv.fromGenEvent( evt );
//
// ----------------------------------------------------------------------
#ifndef CONVERT_HERWIG_H
#define CONVERT_HERWIG_H

#include "CLHEP/HepMC/GenEventConvert.h"
#include "CLHEP/HepMC/CBherwig.h"

namespace HepMC {

typedef  GenEventConvert<CBherwig>  ConvertHerwig;
typedef  CBInterface<CBherwig>      FIherwig;

}

#endif // CONVERT_HERWIG_H
