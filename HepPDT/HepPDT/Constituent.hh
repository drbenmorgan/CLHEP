// $Id: Constituent.hh,v 1.1.1.1 2003/07/15 20:15:05 garren Exp $
// ----------------------------------------------------------------------
//
// Constituent.hh
//
// Holds a particle constituent (e.g. ParticleID of the quark type)
// ----------------------------------------------------------------------
#ifndef CONSTITUENT_HH
#define CONSTITUENT_HH

#include <algorithm>	// swap()

#include "CLHEP/HepPDT/ParticleID.hh"

namespace HepPDT {

/**
 * @author
 * @ingroup heppdt
 */
class Constituent  {

public:
  // ---  birth/death:
  //
  Constituent( ParticleID p = ParticleID(0), int m = -1 )
    : itsPid(p), itsMultiplicity(m)  {}
    
  // ---  copying:
  //
  Constituent( Constituent const & orig )
    :  itsPid(orig.itsPid), itsMultiplicity(orig.itsMultiplicity)  {}
  Constituent &  operator = ( Constituent const & rhs ) {
    Constituent temp( rhs );
    swap( temp );
    return *this;
  }
  void swap( Constituent & other ) {
    std::swap(itsPid, other.itsPid );
    std::swap( itsMultiplicity, other.itsMultiplicity );
  }

  // ---  accessors:
  int         multiplicity() const  { return itsMultiplicity; }
  ParticleID  pid()          const  { return itsPid; }

  // ---  booleans:
  bool  isUp() const;
  bool  isDown() const;
  bool  isStrange() const;
  bool  isCharm() const;
  bool  isBottom() const;
  bool  isTop() const;

private:
  // -- data members
  ParticleID  itsPid;
  int         itsMultiplicity;

};  // Constituent


inline
void swap( Constituent & first, Constituent & second ) { first.swap( second ); }

}	// HepPDT

#endif // CONSTITUENT_HH
