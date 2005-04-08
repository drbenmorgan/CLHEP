// -*- C++ -*-
//
// ----------------------------------------------------------------------
// StdEvent.cc
// Author: Lynn Garren
// ----------------------------------------------------------------------

//#include <iostream.h>		// uncomment if cout is used

#include "CLHEP/StdHep/StdEvent.hh"

namespace StdHep  {

StdEvent::StdEvent( int EventNumber, std::vector<HepMC::GenEvent*> & cvect  )
: itsEventNumber      ( EventNumber ), 
  itsCollisionList    ( cvect )
{ ; }

StdEvent::StdEvent( const StdEvent & orig )
: itsEventNumber      ( orig.itsEventNumber ), 
  itsCollisionList    ( orig.itsCollisionList )
{ ; }

StdEvent& StdEvent::operator=( const StdEvent & rhs )
{ if( this != & rhs )
  {
    itsEventNumber      = rhs.itsEventNumber;
    itsCollisionList    = rhs.itsCollisionList;
  }
  return *this;
}

StdEvent::~StdEvent()  
{
  typedef std::vector<HepMC::GenEvent*>::reverse_iterator cit;
  for( cit i = itsCollisionList.rbegin(); i != itsCollisionList.rend(); ++i )
  {
      delete *i;
  }
}

}  // StdHep
