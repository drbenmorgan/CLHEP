// $Id: ion.cc,v 1.1.1.1 2003/07/15 20:15:05 garren Exp $
// ----------------------------------------------------------------------
//
// ion.cc
//
// return A and Z if this is a nucleus
//
// ----------------------------------------------------------------------

#include "CLHEP/HepPDT/ParticleID.hh"

namespace HepPDT {

int ParticleID::A( ) const
{
    if( ! isNucleus() ) { return 0; }
    return ( abspid()/1000000 )%1000;
}

int ParticleID::Z( ) const
{
    if( ! isNucleus() ) { return 0; }
    return ( abspid()/1000 )%1000;
}

} // HepPDT
