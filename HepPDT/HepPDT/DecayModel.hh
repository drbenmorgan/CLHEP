// $Id: DecayModel.hh,v 1.1.1.1 2003/07/15 20:15:05 garren Exp $
// ----------------------------------------------------------------------
//
// DecayModel.hh
// Author:  Lynn Garren, Walter Brown
//
// Note: users' decay models inheriting from this class must have
//  an explicit constructor that takes a const reference to a vector of doubles
//  as well as implentations of all methods declared pure virtual.
// User code will need :
//     #include "CLHEP/HepPDT/DecayModelBase.hh"
//     REGISTER_DECAY_MODE(ModeA,ModeA::Config)
//
// ----------------------------------------------------------------------
#ifndef DECAYMODEL_HH
#define DECAYMODEL_HH

#include "CLHEP/HepPDT/DefaultConfig.hh"
#include "CLHEP/HepPDT/DecayModelBase.hh"

namespace HepPDT {

typedef  DecayModelBase<DefaultConfig>  DecayModel;

}	// HepPDT

#endif // DECAYMODEL_HH

