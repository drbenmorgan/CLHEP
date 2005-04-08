// -*- C++ -*-
//
// ----------------------------------------------------------------------
// appendCollision.cc
// Author: Lynn Garren
//
// add a Collision
// ----------------------------------------------------------------------

#include "CLHEP/StdHep/StdEvent.hh"

namespace StdHep  {

void  StdEvent::appendCollision( HepMC::GenEvent* c ) 
{ 
  itsCollisionList.push_back( c ); 
}

}  // StdHep
