// $Id: ModeAT.hh,v 1.1.1.1 2003/07/15 20:15:05 garren Exp $
// ----------------------------------------------------------------------
//
// ModeAT.hh
// Author:  Lynn Garren
//
// ----------------------------------------------------------------------
#ifndef MODEAT_HH
#define MODEAT_HH

#if defined(NT_MSVCPP)
#pragma warning (disable: 4786)
#endif

using namespace std;

#include "CLHEP/HepPDT/DecayModelBase.hh"

namespace HepPDT {

template< class C >
class ModeAT : public DecayModelBase< C > {

public:
  typedef          C                    Config; // Template Parameter
  typedef typename Config::ParticleData PD;	// ParticleDataType
  typedef typename Config::PT           PT;	// ParticleType

  // ---  birth/death:
  ModeAT( std::vector<double> const & /*decayModelParameters*/ ) {;}
  virtual ~ModeAT() {;}

  // ---  copying:
  //
  inline ModeAT( const ModeAT<Config> & /*orig*/ ) {;}
  inline ModeAT &  operator = ( const ModeAT<Config> & /*rhs*/ ) { return *this; }
  inline void swap( ModeAT<Config> & /*other*/ ) {;}

  // --- decay method placeholder
  //
  virtual void decay( const std::vector< PD > & /*products*/,
                      const PT                & /*parent*/,
                      std::vector<PT>         & /*daughters*/ ) 
		      { std::cout << "ModeA decay" << std::endl; }
   
  // accessor placeholders
  virtual int         parameters( std::vector<double> & /*fillme*/) const { return 0; }
  virtual std::string name() const { return "ModeAT<>"; }

};  // ModeAT

template< class Config >
inline 
void  swap( ModeAT<Config> & first, ModeAT<Config> & second ) {
  first.swap( second );
}

}	// HepPDT

#endif // MODEAT_HH

