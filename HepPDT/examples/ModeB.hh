
#ifndef MODEB_HPP
#define MODEB_HPP

#if defined(NT_MSVCPP)
#pragma warning (disable: 4786)
#endif

#include "CLHEP/HepPDT/DefaultConfig.hh"
#include "CLHEP/HepPDT/DecayModel.hh"

class ModeB : public HepPDT::DecayModel
{
public:
  typedef  HepPDT::DecayModel::Config   Config;
  typedef  HepPDT::DecayModel::PD   PD;	// ParticleDataType
  typedef  HepPDT::DecayModel::PT   PT;	// ParticleType

  // ---  birth/death:
  //
  ModeB( std::vector<double> const & ) {;}
  virtual ~ModeB() {;}

  // ---  copying:
  //
  ModeB( const ModeB & /*orig*/ ) {;}
  ModeB &  operator = ( const ModeB & rhs );
  void swap( ModeB & /*other*/ ) {;}

  // --- decay method
  virtual void decay( const std::vector< PD > & /*products*/,
                      const PT                & /*parent*/,
                      std::vector<PT>         & /*daughters*/ );
  // accessors
  int         parameters( std::vector<double> & p ) const { return p.size();}
  std::string name() const      { return "ModeB"; }
	
}; // class ModeB

inline 
void  swap( ModeB & first, ModeB & second ) {
  first.swap( second );
}

REGISTER_DECAY_MODE(ModeB,ModeB::Config)

#endif // MODEB_HPP

/*
** Local Variables: --
** mode: c++ --
** c-file-style: "gnu" --
** tab-width: 2 --
** End: --
*/
