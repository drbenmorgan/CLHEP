// $Id: NullDecayModel.hh,v 1.1.1.1 2003/07/15 20:15:05 garren Exp $
// ----------------------------------------------------------------------
//
// NullDecayModel.hh
// Author:  Lynn Garren, Walter Brown, Marc Paterno
//
// ----------------------------------------------------------------------
#ifndef NULLDECAYMODEL_HH
#define NULLDECAYMODEL_HH

#include "CLHEP/HepPDT/DefaultConfig.hh"
#include "CLHEP/HepPDT/NullDecayModelT.hh"

namespace HepPDT {

typedef  NullDecayModelT<DefaultConfig>  NullDecayModel;

// register this object
REGISTER_DECAY_MODE(NullDecayModel,NullDecayModel::Config)

}	// HepPDT

#endif // NULLDECAYMODEL_HH

