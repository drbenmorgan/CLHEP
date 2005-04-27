// ----------------------------------------------------------------------
//
// QQDecayTable.hh
// Author: Lynn Garren
//
// This class holds all the information in the QQ decay.dec table
// 
// ----------------------------------------------------------------------
#ifndef QQDECAYTABLE_HH
#define QQDECAYTABLE_HH

#include <string>
#include <map>

#include "CLHEP/HepPDT/defs.h"
#if HAVE_SSTREAM
#include <sstream>
#else
#include "CLHEP/HepPDT/StringStream.h"
#endif
#include "CLHEP/HepPDT/QQStructs.hh"
#include "CLHEP/HepPDT/QQDecay.hh"
#include "CLHEP/HepPDT/Version.hh"

namespace HepPDT {

/**
 * @author
 * @ingroup heppdt
 */
class QQDecayTable  {

public:

  typedef std::map<std::string,PARTICLE> ParticleMap;
  typedef std::map<std::string,QQBAR> QuarkMap;
  typedef std::map<std::string,QQDecay> DecayMap;

  // -- constructors
  QQDecayTable();
  QQDecayTable( std::istream & pdfile );
  ~QQDecayTable();

  // ---  copying:
  //
  void  swap ( QQDecayTable & rhs );
  QQDecayTable( const QQDecayTable & orig );
  QQDecayTable & operator = ( const QQDecayTable & rhs );

  // --- mutators
  //
  void addParticle ( std::string & nm, PARTICLE p ) { itsParticleMap[nm] = p; }
  void addQQbar    ( std::string & nm, QQBAR q )    { itsQuarkMap[nm] = q; }
  void addDecay    ( std::string & nm, QQDecay d )  { itsDecayMap[nm] = d; }
  void readQQstream( std::istream & pdfile );

  // --- accessors
  //
  PARTICLE particle( const std::string & name );
  QQBAR    qqbar( const std::string & name );
  QQDecay  decay( const std::string & name );
  const ParticleMap particleMap( ) const { return itsParticleMap; }
  const QuarkMap    quarkMap( )    const { return itsQuarkMap; }
  const DecayMap    decayMap( )    const { return itsDecayMap; }
  void writeTable( std::ostream & os ) const;	// intended for diagnostic use

private:

  int         itsVersion;		// decay.dec version
  ParticleMap itsParticleMap;
  QuarkMap    itsQuarkMap;
  DecayMap    itsDecayMap;

  // helper methods
  bool getQQLineType( std::string & ltype, std::string & name, const std::string & pdline );
  int  getQQversion( const std::string & pdline );
  int  getQQbar( const std::string & pdline );
  void addPDG( const std::string & pdline );
  void addParity( const std::string & pdline );
  void addCParity( const std::string & pdline );
  void addMixing( const std::string & pdline );
  bool parseQQDecayLine( QQDecay & dcy, QQChannel & ch, const std::string & pdline );
  PARTICLE parseParticle( const std::string & pdline );

};  // QQDecayTable

inline void swap( QQDecayTable & first, QQDecayTable & second ) {
  first.swap( second );
}

}  // namespace HepPDT

#endif // QQDECAYTABLE_HH
