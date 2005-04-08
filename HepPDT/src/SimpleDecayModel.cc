// ----------------------------------------------------------------------
//
// SimpleDecayModel.cc
// Author:  Lynn Garren, Walter Brown
//
//  the default decay model which has no functional decay() method
//
// ----------------------------------------------------------------------

#include <algorithm>	// swap()

#include "CLHEP/HepPDT/SimpleDecayModel.hh"

namespace HepPDT {

SimpleDecayModel::~SimpleDecayModel() 
{
}

int  SimpleDecayModel::parameters( std::vector<double> & fillme) const
{
     for( unsigned int i=0; i < itsParameters.size(); ++i ) {
         fillme.push_back( itsParameters[i] );
     }
     return itsParameters.size();
}

SimpleDecayModel::SimpleDecayModel( std::vector<double> const & decayModelParameters )
: itsParameters( decayModelParameters )
{ ; }

SimpleDecayModel::SimpleDecayModel( const SimpleDecayModel & orig )
: itsParameters( orig.itsParameters )
{ ; }


SimpleDecayModel &  SimpleDecayModel::operator = ( const SimpleDecayModel & rhs )
{
    SimpleDecayModel temp( rhs );
    temp.swap(*this);
    return *this;
}

void SimpleDecayModel::swap( SimpleDecayModel & other )
{
    std::swap( itsParameters, other.itsParameters );
}

}	// HepPDT
