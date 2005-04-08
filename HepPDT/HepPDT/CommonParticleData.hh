// ----------------------------------------------------------------------
//
// CommonParticleData.hh
// Author: Lynn Garren
//
// This is a base class for particle data information
// ----------------------------------------------------------------------
#ifndef COMMONPARTICLEDATA_HH
#define COMMONPARTICLEDATA_HH

#include <string>
#include <vector>

#include "CLHEP/HepPDT/ParticleID.hh"
#include "CLHEP/HepPDT/SpinState.hh"
#include "CLHEP/HepPDT/Constituent.hh"
#include "CLHEP/HepPDT/ResonanceStructure.hh"
#include "CLHEP/HepPDT/TempParticleData.hh"

namespace HepPDT {

/**
 * @author
 * @ingroup heppdt
 */
class CommonParticleData  {

public:

  // ---  birth/death:
  //
  inline CommonParticleData( const TempParticleData & tpd );
  inline ~CommonParticleData();

  // ---  copying:
  //
  inline void  swap ( CommonParticleData & rhs );
  inline CommonParticleData( const CommonParticleData & orig );
  inline CommonParticleData & operator = ( const CommonParticleData & rhs );

  // ---  accessors:
  //
  const std::string &         name()        const { return itsParticleName; }
  ParticleID                  ID()          const { return itsID; }
  int                         pid( )        const { return itsID.pid(); }
  double                      charge()      const { return itsCharge; }
  double                      color()       const { return itsColorCharge; }
  SpinState                   spin()        const { return itsSpin; }
  Measurement                 mass()        const { return itsResonance->mass(); }
  Measurement                 totalWidth()  const { return itsResonance->totalWidth(); }
  inline Measurement          lifetime()    const;
  int                         numConstituents() const { return itsQuarks.size(); }
  inline Constituent          constituent( unsigned int i ) const;
  inline ParticleID           constituentParticle( unsigned int i ) const;
  ResonanceStructure const *  resonance()   const { return itsResonance; }
  
  void write( std::ostream & os ) const;
 
  // --- booleans:
  //
  bool isMeson( )   const { return itsID.isMeson(); }
  bool isBaryon( )  const { return itsID.isBaryon(); }
  bool isDiQuark( ) const { return itsID.isDiQuark(); }
  bool isHadron( )  const { return itsID.isHadron(); }
  bool isLepton( )  const { return itsID.isLepton(); }
  bool isNucleus( ) const { return itsID.isNucleus(); }
  // has methods look at Constituents, not PID
  bool hasUp()      const;
  bool hasDown()    const;
  bool hasStrange() const;
  bool hasCharm()   const;
  bool hasBottom()  const;
  bool hasTop()     const;
  // compare masses
  inline bool operator <  ( const CommonParticleData & other ) const;
  // use PID and ignore everything else
  inline bool operator == ( const CommonParticleData & other ) const;

  // ---  mutators:
  //
  void  setCharge( double chg )            { itsCharge = chg; }
  void  setColor( double col )             { itsColorCharge = col; }
  void  setSpin( const SpinState & spin )  { itsSpin = spin; }
  void  addConstituent( Constituent c )    { itsQuarks.push_back( c ); }

private:

  // default constructor not allowed
  CommonParticleData();
 
  // ---  class-specific data:
  //
  ParticleID                itsID;
  std::string               itsParticleName;
  double                    itsCharge;
  double                    itsColorCharge;
  SpinState                 itsSpin;
  std::vector<Constituent>  itsQuarks;
  ResonanceStructure *      itsResonance;

  // helper method
  inline void getConstituentsFromPID( );

};  // CommonParticleData

inline void swap( CommonParticleData & first, CommonParticleData & second ) {
  first.swap( second );
}

}	// HepPDT

#include "CLHEP/HepPDT/CommonParticleData.icc"

#endif // COMMONPARTICLEDATA_HH
