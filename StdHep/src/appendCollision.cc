// $Id: appendCollision.cc,v 1.1.1.1 2003/07/15 20:15:05 garren Exp $
// -*- C++ -*-
//
// ----------------------------------------------------------------------
// appendCollision.cc
// add a Collision
// ----------------------------------------------------------------------

#include "CLHEP/StdHep/StdEvent.hh"

namespace StdHep  {

void  StdEvent::appendCollision( HepMC::GenEvent* c ) 
{ 
  itsCollisionList.push_back( c ); 
}

}  // StdHep
