// ----------------------------------------------------------------------
// CBhepevt.h
// ----------------------------------------------------------------------
// Author:  Lynn Garren, Marc Paterno
// 
// This is part of the Fortran interface to the stdhep common blocks
// Do not attempt to use hepevt_ directly.
//
// user code:
//   CBhepevt * hep = CBhepevt::instance();
//   hep->hepevt()->nhep;
//   hep->hepev2()->jmulti[i];
// ----------------------------------------------------------------------
#ifndef CBHEPEVT_H
#define CBHEPEVT_H

#include "CLHEP/HepMC/GenEvent.h"
#include "CLHEP/HepMC/HepMCConfig.h"

#include "CLHEP/HepMC/include/stdhep.h"
#include "CLHEP/HepMC/include/hepev4.h"

namespace HepMC {

/**
 * @author
 * @ingroup hepmc
 */
class CBhepevt {

public:

  CBhepevt() 
  : hptr( & hepevt_ ),
    hptr2( & hepev2_ ),
    hptr3( & hepev3_ ),
    hptr4( & hepev4_ ),
    hptr5( & hepev5_ ), 
    itsTrustMothers( true ),
    itsTrustMothersAndDaughters( false )
  { ; }

  hepevt_t * hepevt() { return hptr; }
  hepev2_t * hepev2() { return hptr2; }
  hepev3_t * hepev3() { return hptr3; }
  hepev4_t * hepev4() { return hptr4; }
  hepev5_t * hepev5() { return hptr5; }
  static int max_number_entries() { return NMXHEP; }
  static int max_multiple_interactions() { return NMXMLT; }
  int        event_number() { return hptr->nevhep; }
  int        number_entries() { return hptr->nhep; }
  int        first_parent( int index );  // index of 1st mother
  int        last_parent( int index );   // index of last mother
  int        first_child( int index );   // index of 1st daughter
  int        last_child( int index );    // index of last daughter
  int        number_children( int index );
  int        number_parents( int index ); 

  void       clean( );
  void       zero_everything() { clean(); }
  bool       check_hepevt_consistency( std::ostream & os = std::cout );
  bool       toGenEvent( GenEvent *, bool printErrors );
  bool       fromGenEvent( const GenEvent * );
  bool       addtoHEPEVT( const GenEvent * );     // not yet implemented
  
  void       print( std::ostream & os = std::cout ) const;
  void       printHEPEVT( std::ostream & os = std::cout );
  void       print_legend( std::ostream & os = std::cout );
  void       printHEPEVTparticle( int index, std::ostream & os = std::cout );
  
  // decide how to deal with HEPEVT
  bool  trustMothers() const { return itsTrustMothers; }
  bool  trustMothersAndDaughters() const { return itsTrustMothersAndDaughters; }
  void  setTrustMothers( bool b ) { itsTrustMothers = b; }
  void  setTrustMothersAndDaughters( bool b ) { itsTrustMothersAndDaughters = b; }

private:

  hepevt_t * hptr;
  hepev2_t * hptr2;
  hepev3_t * hptr3;
  hepev4_t * hptr4;
  hepev5_t * hptr5;
  bool       itsTrustMothers;
  bool       itsTrustMothersAndDaughters;

  // internal functions
  GenParticle* createParticle( int index );
  void buildProductionVertex( int i, 
                              std::vector<GenParticle*>& hepevt_particle, 
  		              GenEvent* evt,
			      bool printInconsistencyErrors );
  void buildEndVertex( int i, std::vector<GenParticle*>& hepevt_particle, 
                       GenEvent* evt,
		       bool printInconsistencyErrors );
  int  find( const std::map<GenParticle*,int>& m, GenParticle* p);

};	// CBhepevt

}	// HepMC

#include "CLHEP/HepMC/CBhepevt.icc"
#include "CLHEP/HepMC/GenEventtoHEPEVT.icc"
#include "CLHEP/HepMC/HEPEVTtoGenEvent.icc"

#endif // CBHEPEVT_H
