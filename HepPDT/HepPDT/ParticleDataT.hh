// ----------------------------------------------------------------------
//
// ParticleDataT.hh
// Author: Lynn Garren
//
// This is a base class for particle data information
// ----------------------------------------------------------------------
#ifndef PARTICLEDATAT_HH
#define PARTICLEDATAT_HH

#include <algorithm>	// swap()

#include "CLHEP/HepPDT/ParticleID.hh"
#include "CLHEP/HepPDT/Measurement.hh"
#include "CLHEP/HepPDT/SpinState.hh"
#include "CLHEP/HepPDT/ResonanceStructure.hh"
#include "CLHEP/HepPDT/Constituent.hh"
#include "CLHEP/HepPDT/TempParticleData.hh"
#include "CLHEP/HepPDT/DecayChannelT.hh"

namespace HepPDT {

/**
 * @author
 * @ingroup heppdt
 */
template< class Config >
class ParticleDataT {

public:
  // --- useful typedef's
  //
  typedef  typename Config::CPD          CPD;
  typedef  typename Config::PT           PT;

  typedef  typename Config::ParticleData ParticleData;
  typedef  typename Config::DecayData    DecayData;
  typedef  typename Config::DecayChannel DecayChannel;

  typedef  typename Config::CPDID        CPDID;
  typedef  typename Config::DDID         DDID;

  // ---  birth/death:
  //
  inline ParticleDataT( const CPDID & cpdid, const DDID & ddid );
  inline ~ParticleDataT();

  // ---  copying:
  //
  inline void  swap( ParticleDataT<Config> & other );
  inline ParticleDataT( const ParticleDataT<Config> & orig );
  inline ParticleDataT& operator = ( const ParticleDataT<Config> & rhs );

  // ---  ParticleData accessors:
  //
  const std::string &         name()        const { return itsCPDID->name();      }
  ParticleID                  ID()          const { return itsCPDID->ID();        }
  int                         pid( )        const { return itsCPDID->ID().pid(); }
  double                      charge()      const { return itsCPDID->charge();    }
  double                      color()       const { return itsCPDID->color();     }
  SpinState                   spin()        const { return itsCPDID->spin();      }
  Measurement                 mass()        const { return itsCPDID->mass(); }
  Measurement                 totalWidth()  const { return itsCPDID->totalWidth();  }
  Measurement                 lifetime()    const { return itsCPDID->lifetime();  }
  int                         numConstituents() const { return itsCPDID->numConstituents(); }
  inline Constituent          constituent( unsigned int i ) const 
                                           { return itsCPDID->constituent(i); }
  inline ParticleID           constituentParticle( unsigned int i ) const
                                            { return itsCPDID->constituentParticle(i); }
  ResonanceStructure const *  resonance()   const { return itsCPDID->resonance(); }

  // --- ParticleData booleans:
  //
  bool isMeson( )   const  { return itsCPDID->isMeson(); }
  bool isBaryon( )  const  { return itsCPDID->isBaryon(); }
  bool isDiQuark( ) const  { return itsCPDID->isDiQuark(); }
  bool isHadron( )  const  { return itsCPDID->isHadron(); }
  bool isLepton( )  const  { return itsCPDID->isLepton(); }
  bool isNucleus( ) const  { return itsCPDID->isNucleus(); }
  bool hasUp()      const  { return itsCPDID->hasUp();      }
  bool hasDown()    const  { return itsCPDID->hasDown();    }
  bool hasStrange() const  { return itsCPDID->hasStrange(); }
  bool hasCharm()   const  { return itsCPDID->hasCharm();   }
  bool hasBottom()  const  { return itsCPDID->hasBottom();  }
  bool hasTop()     const  { return itsCPDID->hasTop();     }

  // ---  ParticleData mutators:
  //
  void  setCharge( double chg )            { itsCPDID->setCharge(chg); }
  void  setColor( double col )             { itsCPDID->setColor(col); }
  void  setSpin( SpinState const & spin )  { itsCPDID->setSpin(spin); }
  void  addConstituent( Constituent c )    { itsCPDID->addConstituent(c); }

  // ---  DecayData accessors:
  //
  int                  numDecayChannels() const { return itsDDID->size(); }
  bool                 isStable()         const { return itsDDID->isStable(); }
  DecayChannelT<Config>  channel( int i )    const { return itsDDID->channel(i); }

  // ---  decay methods:
  //
  bool  decay( int i, const PT & parent, std::vector<PT> & daughters );
  bool  decay( double rdm, const PT & parent, std::vector<PT> & daughters );

  // ---  DecayData mutators:
  //
  void  appendMode( DecayChannel const & dcp)  { itsDDID->appendMode(dcp); }
  void  setDecayData( DDID dd )                { itsDDID = dd; }

  // ---  accessors:
  //
  DDID   getDecayData()            const { return itsDDID; }
  CPDID  getCommonParticleData()   const { return itsCPDID; }
  
  // write prints all information about a particle INCLUDING its decays
  // writeParticleInfo prints all information about a particle EXCEPT its decays
  inline void write( std::ostream & os ) const;
  inline void writeParticleInfo( std::ostream & os ) const;

  // ---  booleans:
  //
  //bool  operator <  ( ParticleDataT<Config> const & other ) const;
  //bool  operator == ( ParticleDataT<Config> const & other ) const;

private:

  // ---  class-specific data:
  //
  CPDID  itsCPDID;	// pointer/iterator to ParticleData
  DDID   itsDDID;	// pointer/iterator to DecayData

  // default constructor not allowed
  ParticleDataT( );

};  // ParticleDataT

template< class Config >
inline
void  swap( ParticleDataT<Config> & first, ParticleDataT<Config> & second ) {
  first.swap( second );
}

}	// HepPDT

#include "CLHEP/HepPDT/ParticleDataT.icc"

#endif // PARTICLEDATAT_HH
