// $Id: DecayDataT.hh,v 1.1.1.1 2003/07/15 20:15:05 garren Exp $
// ----------------------------------------------------------------------
//
// DecayDataT.hh
//
// ----------------------------------------------------------------------
#ifndef DECAYDATAT_HH
#define DECAYDATAT_HH

#include <vector>

#include "CLHEP/HepPDT/DecayChannelT.hh"

namespace HepPDT {

/**
 * @author
 * @ingroup heppdt
 */
template< class Config >
class DecayDataT {

public:
  // --- useful typedef's
  //
  typedef typename Config::PT           PT;	// ParticleType

  // ---  birth/death:
  //
  inline DecayDataT( );
  inline DecayDataT( std::vector<DecayChannelT<Config> > const & dv );
  inline ~DecayDataT();

  // ---  copying:
  //
  inline DecayDataT( DecayDataT<Config> const & orig );
  inline DecayDataT & operator = ( DecayDataT<Config> const & rhs );
  inline void swap( DecayDataT<Config> & other );

  // ---  accessors:
  //
  bool                   isStable()     const;
  int                    size()         const { return itsDecayList.size(); }
  DecayChannelT<Config>  channel( int i ) const { return itsDecayList[i]; }

  // ---  decay methods:
  //
  // ask for a specific decay
  bool  decay( int i, const PT & parent, std::vector<PT> & daughters );
  // do a random decay based on a number from 0 to 1
  bool  decay( double rdm, const PT & parent, std::vector<PT> & daughters );
  
  inline void write( std::ostream & os ) const;

  // ---  mutators:
  //
  void  appendMode( DecayChannelT<Config> );

private:

  std::vector<DecayChannelT<Config> > itsDecayList; 

};  // DecayDataT

template< class Config >
inline
void swap( DecayDataT<Config> & first, DecayDataT<Config> & second )  {
  first.swap( second );
}

}	// HepPDT

#include "CLHEP/HepPDT/DecayDataT.icc"

#endif // DECAYDATAT_HH
