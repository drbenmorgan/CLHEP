// $Id: ResonanceStructure.cc,v 1.1.1.1 2003/07/15 20:15:05 garren Exp $
// ----------------------------------------------------------------------
//
// ResonanceStructure.cc
//
// ----------------------------------------------------------------------

#include "CLHEP/HepPDT/ResonanceStructure.hh"

namespace HepPDT {

ResonanceStructure::ResonanceStructure( Measurement mass, Measurement width,
                                        double min, double max )
: itsMass        ( mass ),
  itsTotalWidth       ( width ),
  itsLowerCutoff ( min ),
  itsUpperCutoff ( max )
{ ; }

ResonanceStructure::ResonanceStructure( const ResonanceStructure & orig )
: itsMass        ( orig.itsMass ),
  itsTotalWidth       ( orig.itsTotalWidth ),
  itsLowerCutoff ( orig.itsLowerCutoff ),
  itsUpperCutoff ( orig.itsUpperCutoff )
{ ; }

ResonanceStructure& ResonanceStructure::operator=( const ResonanceStructure & rhs )
{
  ResonanceStructure temp( rhs );
  swap( temp );
  return *this;
}

void ResonanceStructure::swap ( ResonanceStructure & other )  
{
  itsMass .swap(other.itsMass);
  itsTotalWidth.swap(other.itsTotalWidth);
  std::swap(itsLowerCutoff, other.itsLowerCutoff);
  std::swap(itsUpperCutoff, other.itsUpperCutoff);
}


ResonanceStructure::~ResonanceStructure()
{ ; }

void ResonanceStructure::setTotalWidthFromLifetime( Measurement const & lt ) 
{
    // totalwidth = hbar / lifetime
    static double epsilon = 1.0e-20;
    static double hbar = 6.58211889e-25; // in GeV s
    double wid, sig;
    // make no changes if lifetime is not greater than zero
    if( lt.value() < epsilon ) { return; }
    wid = hbar/lt.value();
    if( lt.sigma() < epsilon ) {
         sig = 0.;
    } else {
        sig = (lt.sigma()/lt.value())*wid;
    }
    itsTotalWidth = Measurement(wid,sig);
}

}	// HepPDT
