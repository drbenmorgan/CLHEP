// $Id: hasMethods.cc,v 1.1.1.1 2003/07/15 20:15:05 garren Exp $
// ----------------------------------------------------------------------
//
// hasMethods.cc
//
//  check to see if this CommonParticleData has a particular constituent
//  look at Constituents, not PID
//
// ----------------------------------------------------------------------

#include "CLHEP/HepPDT/CommonParticleData.hh"

namespace HepPDT {

bool CommonParticleData::hasUp( ) const
{
    unsigned int i;
    if( itsQuarks.size() == 0 ) { return false; }
    for( i=0; i<itsQuarks.size(); ++i ) {
       if( itsQuarks[i].isUp() ) { return true; }
    }
    return false;
}

bool CommonParticleData::hasDown( ) const
{
    unsigned int i;
    if( itsQuarks.size() == 0 ) { return false; }
    for( i=0; i<itsQuarks.size(); ++i ) {
       if( itsQuarks[i].isDown() ) { return true; }
    }
    return false;
}

bool CommonParticleData::hasStrange( ) const
{
    unsigned int i;
    if( itsQuarks.size() == 0 ) { return false; }
    for( i=0; i<itsQuarks.size(); ++i ) {
       if( itsQuarks[i].isStrange() ) { return true; }
    }
    return false;
}

bool CommonParticleData::hasCharm( ) const
{
    unsigned int i;
    if( itsQuarks.size() == 0 ) { return false; }
    for( i=0; i<itsQuarks.size(); ++i ) {
       if( itsQuarks[i].isCharm() ) { return true; }
    }
    return false;
}

bool CommonParticleData::hasBottom( ) const
{
    unsigned int i;
    if( itsQuarks.size() == 0 ) { return false; }
    for( i=0; i<itsQuarks.size(); ++i ) {
       if( itsQuarks[i].isBottom() ) { return true; }
    }
    return false;
}

bool CommonParticleData::hasTop( ) const
{
    unsigned int i;
    if( itsQuarks.size() == 0 ) { return false; }
    for( i=0; i<itsQuarks.size(); ++i ) {
       if( itsQuarks[i].isTop() ) { return true; }
    }
    return false;
}

} // HepPDT
