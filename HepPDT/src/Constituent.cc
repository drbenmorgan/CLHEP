// ----------------------------------------------------------------------
//
// Constituent.cc
//
// ----------------------------------------------------------------------

#include "CLHEP/HepPDT/Constituent.hh"

namespace HepPDT {

bool Constituent::isUp( ) const
{
    if( itsPid.fundamentalID() == 2 ) { return true; }
    return false;
}

bool Constituent::isDown( ) const
{
    if( itsPid.fundamentalID() == 1 ) { return true; }
    return false;
}

bool Constituent::isStrange( ) const
{
    if( itsPid.fundamentalID() == 3 ) { return true; }
    return false;
}

bool Constituent::isCharm( ) const
{
    if( itsPid.fundamentalID() == 4 ) { return true; }
    return false;
}

bool Constituent::isBottom( ) const
{
    if( itsPid.fundamentalID() == 5 ) { return true; }
    return false;
}

bool Constituent::isTop( ) const
{
    if( itsPid.fundamentalID() == 6 ) { return true; }
    return false;
}

} // HepPDT
