// ----------------------------------------------------------------------
//
// DecayModelBase.hh
// Author:  Lynn Garren, Walter Brown, Marc Paterno
//
// Note: users' decay models inheriting from this class must have
//  an explicit constructor that takes a const reference to a vector of doubles
//  as well as implentations of all methods declared pure virtual.
// User code will need :
//     #include "CLHEP/HepPDT/DecayModelBase.hh"
//     REGISTER_DECAY_MODE(ModeA,ModeA::Config)
//
// ----------------------------------------------------------------------
#ifndef DECAYMODELBASE_HH
#define DECAYMODELBASE_HH

#include <string>
#include <vector>

#define REGISTER_DECAY_MODE(type,config) \
    namespace { HepPDT::RegisterMe<type,config> registered##type(#type); }


namespace HepPDT {

/**
 * @author
 * @ingroup heppdt
 */
template< class CONFIG >
class DecayModelBase  {

public:
  typedef          CONFIG               Config; // Template Parameter
  typedef typename CONFIG::ParticleData PD;	// ParticleDataType
  typedef typename CONFIG::PT           PT;	// ParticleType

  // ---  death:
  virtual ~DecayModelBase() {;}

  // ---  copying:
  //
  inline DecayModelBase( const DecayModelBase<CONFIG> & orig ) {;}
  inline DecayModelBase &  operator = ( const DecayModelBase<CONFIG> & rhs ) { return *this; }
  inline void swap( DecayModelBase<CONFIG> & other ) {;}

  // --- decay method placeholder
  //
  virtual void decay( const std::vector< PD > & products,
                      const PT                & parent,
                      std::vector<PT>         & daughters ) = 0;
   
  // accessor placeholders
  virtual int         parameters( std::vector<double> & fillme) const = 0;
  virtual std::string name() const = 0;
  
protected:

  // --- birth
  DecayModelBase(  ) {;}

  // ---  DecayModelBase<>-specific data, e.g., Helicity and/or PartialWaveAmplitudes
  //

};  // DecayModelBase

template< class CONFIG >
inline 
void  swap( DecayModelBase<CONFIG> & first, DecayModelBase<CONFIG> & second ) {
  first.swap( second );
}

}	// HepPDT

#endif // DECAYMODELBASE_HH

