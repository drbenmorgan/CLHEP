// $Id: DecayChannel.hh,v 1.1.1.1 2003/07/15 20:15:05 garren Exp $
// ----------------------------------------------------------------------
//
// DecayChannel.hh
//
// ----------------------------------------------------------------------
#ifndef DECAYCHANNEL_HH
#define DECAYCHANNEL_HH

#include "CLHEP/HepPDT/DefaultConfig.hh"
#include "CLHEP/HepPDT/DecayChannelT.hh"

namespace HepPDT {

typedef  DecayChannelT<DefaultConfig>  DecayChannel;

}	// HepPDT

#endif // DECAYCHANNEL_HH

