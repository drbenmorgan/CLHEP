// ----------------------------------------------------------------------
//
// SpinState.hh
// Author:  Lynn Garren
//
// ----------------------------------------------------------------------
#ifndef SPINSTATE_HH
#define SPINSTATE_HH

namespace HepPDT {

/**
 * @author
 * @ingroup heppdt
 */
class SpinState  {

public:

  // ---  birth/death:
  //
  inline SpinState( double ts = 0., double spin = 0., double oam =0. );

  // ---  copying:
  //
  inline SpinState( const SpinState & orig );
  inline SpinState& operator = ( const SpinState & rhs );
  inline void swap( SpinState & other );

  // ---  booleans:
  //
  inline bool  operator == ( const SpinState & rhs ) const;

  // ---  accessors:
  //
  double totalSpin()     const {  return itsTotalSpin; }
  double spin()          const {  return itsSpin; }
  double orbAngMom()     const {  return itsOrbAngMom; }

  // ---  mutators:
  //
  void  setTotalSpin( double spin )  {  itsTotalSpin = spin; }
  void  setSpin( double spin )       {  itsSpin = spin; }
  void  setOrbAngMom( double ang )   {  itsOrbAngMom = ang; }
  
private:

  // ---  class-specific data:
  //
  double  itsTotalSpin;
  double  itsSpin;
  double  itsOrbAngMom;

};  // SpinState

inline
void swap( SpinState & first,SpinState & second )  { first.swap( second ); }

}	// HepPDT

#include "CLHEP/HepPDT/SpinState.icc"

#endif // SPINSTATE_HH
