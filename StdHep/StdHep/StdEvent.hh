// $Id: StdEvent.hh,v 1.1.1.1 2003/07/15 20:15:05 garren Exp $
// -*- C++ -*-
//
// ----------------------------------------------------------------------
// StdEvent.hh
//
//  StdCollision has been replaced by GenEvent
// ----------------------------------------------------------------------
#ifndef STDEVENT_HH
#define STDEVENT_HH

#include <vector>
#include <iostream>

#include "CLHEP/HepMC/GenEvent.h"
#include "CLHEP/HepMC/GenParticle.h"
#include "CLHEP/HepMC/GenVertex.h"

namespace StdHep  {

/**
 * @author
 * @ingroup stdhep
 */
class StdEvent {

public:

  typedef std::vector<HepMC::GenEvent*> CollisionList;
  typedef HepMC::GenParticle            Particle;
  typedef HepMC::GenEvent               Collision;

  // ---  birth/death:
  //
  StdEvent( int EventNumber, std::vector<HepMC::GenEvent*> & cvect );
  StdEvent( const StdEvent & orig );
  StdEvent& operator=( const StdEvent & );
  ~StdEvent();

  // ---  accessors:
  //
  int          eventNumber()      const  { return itsEventNumber; }
  int          numCollisions()    const  { return itsCollisionList.size(); }
  int          numParticles()     const;
  int          numVertices()      const;
  int          size()             const  { return itsCollisionList.size(); }
  CollisionList::const_iterator  begin() const  { return itsCollisionList.begin(); }
  CollisionList::const_iterator  end()   const  { return itsCollisionList.end(); }

  HepMC::GenParticle* particle( int i )           const;
  HepMC::GenParticle* particle( int i, int icol ) const;
  HepMC::GenVertex*   vertex( int i )             const;
  HepMC::GenVertex*   vertex( int i, int icol )   const;
  HepMC::GenEvent*    collision( int i )          const;

  std::vector<HepMC::GenParticle*> children(HepMC::GenParticle*)    const;
  std::vector<HepMC::GenParticle*> descendants(HepMC::GenParticle*) const;
  std::vector<HepMC::GenParticle*> parents(HepMC::GenParticle*)     const;
  std::vector<HepMC::GenParticle*> ancestors(HepMC::GenParticle*)   const;

  std::vector<HepMC::GenParticle*> children(HepMC::GenVertex*)    const;
  std::vector<HepMC::GenParticle*> descendants(HepMC::GenVertex*) const;
  std::vector<HepMC::GenParticle*> parents(HepMC::GenVertex*)     const;
  std::vector<HepMC::GenParticle*> ancestors(HepMC::GenVertex*)   const;

  void print( std::ostream & os = std::cout ) const;
  void tree ( std::ostream & os = std::cout ) const;

  // ---  mutators:
  //
  void  setEventNumber      ( int nmbr )     { itsEventNumber = nmbr; }
  void  appendCollision     ( HepMC::GenEvent* c );

  // -- old method names
  //
  int       EventNumber()         const  { return eventNumber(); }
  int       NumberParticles()     const  { return numParticles(); }
  int       NumberCollisions()    const  { return numCollisions(); }
  Particle  HEParticle( int i )   const  { return *(particle(i)); }
  Collision HEPCollision( int i ) const  { return *(itsCollisionList[i]); }

  // -- iterators
  //

private:

  int           itsEventNumber;
  CollisionList itsCollisionList;
  
};	// StdEvent

}

#endif // STDEVENT_HH
