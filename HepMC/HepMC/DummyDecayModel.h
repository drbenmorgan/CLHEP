// $Id: DummyDecayModel.h,v 1.1.1.1 2003/07/15 20:15:05 garren Exp $
// ----------------------------------------------------------------------
//
// DummyDecayModel.h
// Author:  Lynn Garren, Walter Brown
//
//  the default decay model which has no functional decay() method
//
// ----------------------------------------------------------------------
#ifndef DUMMYDECAYMODEL_H
#define DUMMYDECAYMODEL_H

#include <vector>

#include "CLHEP/HepPDT/DecayModel.hh"

namespace HepMC {

/**
 * @author
 * @ingroup hepmc
 */
class DummyDecayModel : public HepPDT::DecayModel {

public:
  typedef  HepPDT::DecayModel::PD   PD;	// ParticleDataType
  typedef  HepPDT::DecayModel::PT   PT;	// ParticleType

  // ---  birth/death:
  //
  DummyDecayModel( std::vector<double> const & decayModelParameters );
  virtual ~DummyDecayModel() { ; }

  // ---  copying:
  //
  DummyDecayModel( const DummyDecayModel & orig );
  DummyDecayModel &  operator = ( const DummyDecayModel & rhs );
  void swap( DummyDecayModel & other );

  // --- decay method placeholder
  //
  virtual void decay( const std::vector< PD > & /*products*/,
                      const PT                & /*parent*/,
                      std::vector<PT>         & /*daughters*/ )  { ; }

  // accessors
  int         parameters( std::vector<double> & fillme) const;
  std::string name() const      { return "DummyDecayModel"; }

  // mutators?
  
    
private:

  // ---  DummyDecayModel<>-specific data, e.g., Helicity and/or PartialWaveAmplitudes
  //
  std::vector<double>      itsParameters;

};  // DummyDecayModel

inline 
void  swap( DummyDecayModel & first, DummyDecayModel & second ) {
  first.swap( second );
}

// register this object
REGISTER_DECAY_MODE(DummyDecayModel,DummyDecayModel::Config)

}	// HepMC

#endif // DUMMYDECAYMODEL_H

