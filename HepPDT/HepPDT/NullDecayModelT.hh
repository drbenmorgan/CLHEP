// $Id: NullDecayModelT.hh,v 1.1.1.1 2003/07/15 20:15:05 garren Exp $
// ----------------------------------------------------------------------
//
// NullDecayModelT.hh
// Author:  Lynn Garren, Walter Brown, Marc Paterno
//
// Note: users' decay models inheriting from this class must have
//  an explicit constructor that takes a const reference to a vector of doubles
//  as well as implentations of all methods declared pure virtual.
// User code will need :
//     #include "CLHEP/HepPDT/NullDecayModelT.hh"
//     REGISTER_DECAY_MODE(ModeA,ModeA::Config)
//
// ----------------------------------------------------------------------
#ifndef NULLDECAYMODELT_HH
#define NULLDECAYMODELT_HH

#include "CLHEP/HepPDT/DecayModelBase.hh"

namespace HepPDT {

/**
 * @author
 * @ingroup heppdt
 */
template< class Config >
class NullDecayModelT  : public DecayModelBase<Config> {

public:
  typedef typename Config::ParticleData PD;	// ParticleDataType
  typedef typename Config::PT           PT;	// ParticleType

  // ---  birth/death:
  NullDecayModelT( std::vector<double> const & /*decayModelParameters*/ ) {;}
  virtual ~NullDecayModelT() {;}

  // ---  copying:
  //
  inline NullDecayModelT( const NullDecayModelT<Config> & /*orig*/ ) {;}
  inline NullDecayModelT &  operator = ( const NullDecayModelT<Config> & /*rhs*/ ) { return *this; }
  inline void swap( NullDecayModelT<Config> & /*other*/ ) {;}

  // --- decay method placeholder
  //
  virtual void decay( const std::vector< PD > & /*products*/,
                      const PT                & /*parent*/,
                      std::vector<PT>         & /*daughters*/ ) {;}
   
  // accessor placeholders
  virtual int         parameters( std::vector<double> & /*fillme*/) const { return 0; }
  virtual std::string name() const { return "NullDecayModelT<>"; }

};  // NullDecayModelT

template< class Config >
inline 
void  swap( NullDecayModelT<Config> & first, NullDecayModelT<Config> & second ) {
  first.swap( second );
}

}	// HepPDT

#endif // NULLDECAYMODELT_HH

