// ----------------------------------------------------------------------
// CBstdhep.hh
// ----------------------------------------------------------------------
// Author:  Lynn Garren, Marc Paterno
// 
// This is part of the Fortran interface to the stdhep common blocks
// Do not attempt to use hepevt_ directly.
//
// ----------------------------------------------------------------------
#ifndef CBSTDHEP_HH
#define CBSTDHEP_HH

#include "CLHEP/StdHep/StdEvent.hh"

#include "CLHEP/HepMC/include/stdhep.h"
#include "CLHEP/HepMC/include/hepev4.h"
#include "CLHEP/StdHep/include/stdtmp.h"

namespace StdHep {

/**
 * @author
 * @ingroup StdHep
 */
class CBstdhep {

public:

  CBstdhep() 
  : hptr( & hepevt_ ),
    hptr2( & hepev2_ ),
    hptr3( & hepev3_ ),
    hptr4( & hepev4_ ),
    hptr5( & hepev5_ ), 
    tptr( & stdtmp_ ), 
    tptr4( & tmpev4_ ),
    itsTrustMothers( true )
  { ; }

  hepevt_t * hepevt() { return hptr; }
  hepev2_t * hepev2() { return hptr2; }
  hepev3_t * hepev3() { return hptr3; }
  hepev4_t * hepev4() { return hptr4; }
  hepev5_t * hepev5() { return hptr5; }
  static int max_number_entries() { return NMXHEP; }
  static int max_multiple_interactions() { return NMXMLT; }
  int        number_children( int index );
  int        number_parents( int index ); 

  void       clean( );
  void       cleanStdtmp( );
  bool       toGenEvent( HepMC::GenEvent *, bool printErrors );
  bool       fromStdEvent( const StdEvent * );
  
  // decide how to deal with HEPEVT
  bool  trustMothers() const { return itsTrustMothers; }
  void  setTrustMothers( bool b ) { itsTrustMothers = b; }

private:

  hepevt_t * hptr;
  hepev2_t * hptr2;
  hepev3_t * hptr3;
  hepev4_t * hptr4;
  hepev5_t * hptr5;
  stdtmp_t * tptr;
  tmpev4_t * tptr4;
  bool       itsTrustMothers;

  // internal methods
  bool CollisionToStdTmp( const HepMC::GenEvent * col );
  bool MultipleInteractionInfo( int & i );
  int  findInTemporaryMap( const std::map<HepMC::GenParticle*,int>& m, 
                           HepMC::GenParticle* p);
  HepMC::GenParticle* createParticle( int index );
  void buildProductionVertex( int i, 
                              std::vector<HepMC::GenParticle*>& hepevt_particle, 
  		              HepMC::GenEvent* evt,
			      bool printInconsistencyErrors );
  void buildEndVertex( int i, std::vector<HepMC::GenParticle*>& hepevt_particle, 
                       HepMC::GenEvent* evt,
		       bool printInconsistencyErrors );

};	// CBstdhep

}	// StdHep

#include "CLHEP/StdHep/CBstdhep.icc"
#include "CLHEP/StdHep/StdHepfromStdEvent.icc"
#include "CLHEP/StdHep/StdHeptoGenEvent.icc"

#endif // CBSTDHEP_HH
