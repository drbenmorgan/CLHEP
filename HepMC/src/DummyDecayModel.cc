// ----------------------------------------------------------------------
//
// DummyDecayModel.cc
// Author:  Lynn Garren, Walter Brown
//
//  the default decay model which has no functional decay() method
//
// ----------------------------------------------------------------------

#include <algorithm>	// swap()

#include "CLHEP/HepMC/DummyDecayModel.h"

namespace HepMC {

int  DummyDecayModel::parameters( std::vector<double> & fillme) const
{
     for( unsigned int i=0; i < itsParameters.size(); ++i ) {
         fillme.push_back( itsParameters[i] );
     }
     return itsParameters.size();
}

DummyDecayModel::DummyDecayModel( std::vector<double> const & decayModelParameters )
: itsParameters( decayModelParameters )
{ ; }

DummyDecayModel::DummyDecayModel( const DummyDecayModel & orig )
: itsParameters( orig.itsParameters )
{ ; }


DummyDecayModel &  DummyDecayModel::operator = ( const DummyDecayModel & rhs )
{
    DummyDecayModel temp( rhs );
    temp.swap(*this);
    return *this;
}

void DummyDecayModel::swap( DummyDecayModel & other )
{
    std::swap( itsParameters, other.itsParameters );
}

}	// HepPDT
