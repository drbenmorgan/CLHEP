// ----------------------------------------------------------------------
//
// SimpleDecayModel.hh
// Author:  Lynn Garren, Walter Brown
//
//  the default decay model which has no functional decay() method
//
// ----------------------------------------------------------------------
#ifndef SIMPLEDECAYMODEL_HH
#define SIMPLEDECAYMODEL_HH

#include <vector>

#include "CLHEP/HepPDT/DefaultConfig.hh"
#include "CLHEP/HepPDT/DecayModel.hh"

namespace HepPDT {

/**
 * @author
 * @ingroup heppdt
 */
class SimpleDecayModel : public DecayModel {

public:
  typedef  DecayModel::PD   PD;	// ParticleDataType
  typedef  DecayModel::PT   PT;	// ParticleType

  // ---  birth/death:
  //
  SimpleDecayModel( std::vector<double> const & decayModelParameters );
  virtual ~SimpleDecayModel();

  // ---  copying:
  //
  SimpleDecayModel( const SimpleDecayModel & orig );
  SimpleDecayModel &  operator = ( const SimpleDecayModel & rhs );
  void swap( SimpleDecayModel & other );

  // --- decay method placeholder
  //
  virtual void decay( const std::vector< PD > & /*products*/,
                      const PT                & /*parent*/,
                      std::vector<PT>         & /*daughters*/ )  { ; }

  // accessors
  int         parameters( std::vector<double> & fillme) const;
  std::string name() const      { return "SimpleDecayModel"; }

  // mutators?
  
    
private:

  // ---  SimpleDecayModel<>-specific data, e.g., Helicity and/or PartialWaveAmplitudes
  //
  std::vector<double>      itsParameters;

};  // SimpleDecayModel

inline 
void  swap( SimpleDecayModel & first, SimpleDecayModel & second ) {
  first.swap( second );
}

// register this object
REGISTER_DECAY_MODE(SimpleDecayModel,SimpleDecayModel::Config)

}	// HepPDT

#endif // SIMPLEDECAYMODEL_HH

