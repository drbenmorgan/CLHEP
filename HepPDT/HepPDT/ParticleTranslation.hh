// $Id: ParticleTranslation.hh,v 1.1 2004/04/14 23:56:27 garren Exp $
// ----------------------------------------------------------------------
//
// ParticleTranslation.hh
// Author: Lynn Garren
//
// Use this class to maintain translation info
// This class is used when testing translations
// ----------------------------------------------------------------------
#ifndef PARTICLETRANSLATION_HH
#define PARTICLETRANSLATION_HH

#include <string>
#include <iostream>

#include "CLHEP/HepPDT/ParticleID.hh"

namespace HepPDT {

/**
 * @author
 * @ingroup heppdt
 */
class ParticleTranslation  {

public:

  // ---  birth/death:
  //
  inline ParticleTranslation( ParticleID, int, std::string &, std::string & mc );
  inline ParticleTranslation( );
  inline ~ParticleTranslation();

  // ---  copying:
  //
  inline void  swap ( ParticleTranslation & rhs );
  inline ParticleTranslation( const ParticleTranslation & orig );
  inline ParticleTranslation & operator = ( const ParticleTranslation & rhs );

  // ---  accessors:
  //
  const std::string             name()    const { return itsPID.PDTname(); }
  const std::string &   originalName()    const { return itsOriginalName; }
  const std::string & monteCarloName()    const { return itsMonteCarloName; }
  ParticleID                      ID()    const { return itsPID; }
  int                            pid()    const { return itsPID.pid(); }
  int                            oid()    const { return itsOriginalID; }
  
  inline void write( std::ostream & os ) const;

private:
  // ---  class-specific data:
  //
  ParticleID      itsPID;
  int             itsOriginalID;
  std::string     itsOriginalName;
  std::string     itsMonteCarloName;

};  // ParticleTranslation

inline void swap( ParticleTranslation & first, ParticleTranslation & second ) {
  first.swap( second );
}

}	// HepPDT

#include "CLHEP/HepPDT/ParticleTranslation.icc"

#endif // PARTICLETRANSLATION_HH
