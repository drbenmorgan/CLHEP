// $Id: StdEventConvert.hh,v 1.1.1.1 2003/07/15 20:15:05 garren Exp $
// ----------------------------------------------------------------------
//
// StdEventConvert.hh
// L. Garren
//
//           build StdEvent from HEPEVT, and vice-versa
//
// ----------------------------------------------------------------------
#ifndef STDEVENTCONVERT_HH
#define STDEVENTCONVERT_HH

#include <map>
#include <vector>

#include "CLHEP/HepMC/CBInterface.h"
#include "CLHEP/StdHep/StdEvent.hh"
#include "CLHEP/HepMC/GenEvent.h"

namespace StdHep {

/**
 * @author
 * @ingroup StdHep
 */
template<class S>
class StdEventConvert {

public:

  StdEventConvert( bool p=true )
  : itsInconsitencyErrors( p )
  { ; }
  ~StdEventConvert() {;}

  // conversion methods
  StdEvent * getStdEvent( int & evnum );
  HepMC::GenEvent * toCollision();
  bool       fromStdEvent( const StdEvent * );

  // decide how to deal with HEPEVT
  bool  printInconsistencyErrors() const { return itsInconsitencyErrors; }
  void  setInconsitencyErrors( bool b ) { itsInconsitencyErrors = b; }


private:

  bool itsInconsitencyErrors; 

};	// StdEventConvert

} // StdHep

#include "CLHEP/StdHep/StdEventConvert.icc"

#endif // STDEVENTCONVERT_HH
