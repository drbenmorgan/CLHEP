// $Id: GenEventConvert.h,v 1.1.1.1 2003/07/15 20:15:05 garren Exp $
// ----------------------------------------------------------------------
//
// GenEventConvert.h
//
//  defines methods to build GenEvent from some set of common blocks
//  also fill the common blocks from GenEvent
//  Specific implementation is found in the common block class.
//
//  We plan to use this template with other common block sets (e.g. pythia)
//
// ----------------------------------------------------------------------
#ifndef GENEVENTCONVERT_H
#define GENEVENTCONVERT_H

#include <map>
#include <vector>

#include "CLHEP/HepMC/CBInterface.h"
#include "CLHEP/HepMC/GenEvent.h"
#include "CLHEP/HepMC/HepMCConfig.h"

namespace HepMC {

/**
 * @author
 * @ingroup hepmc
 */
template<class S>
class GenEventConvert {

public:

  GenEventConvert( bool p=true )
  : itsInconsitencyErrors( p )
  { ; }
  ~GenEventConvert() {;}

  // conversion methods
  GenEvent * getGenEventfromHEPEVT();
  bool       toGenEvent( GenEvent * );
  bool       fromGenEvent( const GenEvent * );
  bool       addtoHEPEVT( const GenEvent * );

  // decide how to deal with HEPEVT
  bool  printInconsistencyErrors() const { return itsInconsitencyErrors; }
  void  setInconsitencyErrors( bool b ) { itsInconsitencyErrors = b; }

private:

  bool itsInconsitencyErrors; 

};

} // HepMC

#include "CLHEP/HepMC/GenEventConvert.icc"

#endif // GENEVENTCONVERT_H
