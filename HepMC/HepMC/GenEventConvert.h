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
  GenEvent * read_next_event() { return getGenEventfromHEPEVT(); }
  bool       fill_next_event( GenEvent * evt ) { return toGenEvent(evt); }

  // decide how to deal with HEPEVT
  bool  printInconsistencyErrors() const { return itsInconsitencyErrors; }
  void  setInconsitencyErrors( bool b ) { itsInconsitencyErrors = b; }
  
  // print 
  void  print_hepevt( std::ostream & os = std::cout );

private:

  bool itsInconsitencyErrors; 

};

} // HepMC

#include "CLHEP/HepMC/GenEventConvert.icc"

#endif // GENEVENTCONVERT_H
