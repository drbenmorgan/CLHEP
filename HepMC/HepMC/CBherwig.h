// $Id: CBherwig.h,v 1.1.2.2 2005/03/03 20:19:40 garren Exp $
// ----------------------------------------------------------------------
// CBherwig.h
// ----------------------------------------------------------------------
// Author:  Lynn Garren, Marc Paterno
// 
// This is part of the Fortran interface to the herwig common blocks
// Do not attempt to use the common blocks directly.
//
// user code:
//   CBherwig * hep = CBherwig::instance();
//   hep->hepevt()->nhep;
// ----------------------------------------------------------------------
#ifndef CBHERWIG_H
#define CBHERWIG_H
//////////////////////////////////////////////////////////////////////////
// Matt.Dobbs@Cern.CH, October 2002, refer to:
// M. Dobbs and J.B. Hansen, "The HepMC C++ Monte Carlo Event Record for
// High Energy Physics", Computer Physics Communications (to be published).
//
// IO class for reading the (non-standard) HEPEVT common block from 
//  the Herwig monte carlo program.
// Notes:
//   - The HERWIG HEPEVT common block is non-standard, primarily because it 
//     contains some color flow information. When you call CBherwig, a copy
//     is made of the HEPEVT common block and all work is done on the copy.
//   - The HERWIG HEPEVT common block has some EXTRA non-physical ENTRIES 
//     (such as CMS frame, HARD subprocess, and CONE).
//     These are removed by CBherwig. Thus the HepMC event will APPEAR
//     to have fewer particles in it that herwig did.
//     There is a switch itsNoBarcodeGaps. For
//       true  - then the extra particles are removed from HEPEVT, with 
//               the result that the HepMC barcodes will be sequential, with 
//               no gaps.
//       false - the barcodes will correspond directly to the HEPEVT index, but
//               there will be gaps ... ie some barcodes will be unassigned.
//       this switch requested by I Hinchliffe, October 31, 2002
//   - some of the Herwig GLUON SPLITTING products are not properly documented
//     in hepevt. I was unable to repair this in a simple and robust way. 
//     Therefore some of the gluon splitting products will be orphans 
//     in the HepMC output. 
//////////////////////////////////////////////////////////////////////////

#include "CLHEP/HepMC/GenEvent.h"
#include "CLHEP/HepMC/HepMCConfig.h"

#include "CLHEP/HepMC/include/stdhep.h"

namespace HepMC {

/**
 * @author
 * @ingroup hepmc
 */
class CBherwig {

public:

  CBherwig();
  ~CBherwig();

  hepevt_t * hepevt() { return hptr; }
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
  bool       addtoHEPEVT( const GenEvent * );     // not yet implemented

  bool       no_gaps_in_barcodes() const  { return itsNoBarcodeGaps; }
  void       set_no_gaps_in_barcodes( bool a ) { itsNoBarcodeGaps=a; }
  
  void       print( std::ostream & os = std::cout ) const;
  void       printHEPEVT( std::ostream & os = std::cout );
  void       print_legend( std::ostream & os = std::cout );
  void       printHEPEVTparticle( int index, std::ostream & os = std::cout );

protected: // for internal use only
  
  // decide how to deal with HEPEVT
  bool  trustMothers() const { return itsTrustMothers; }
  bool  trustMothersAndDaughters() const { return itsTrustMothersAndDaughters; }
  void  setTrustMothers( bool b ) { itsTrustMothers = b; }
  void  setTrustMothersAndDaughters( bool b ) { itsTrustMothersAndDaughters = b; }
  int   translate_herwig_to_pdg_id( int i, bool printInconsistencyErrors ) const;

private:

  hepevt_t * hptr;
  bool       itsTrustMothers;
  bool       itsTrustMothersAndDaughters;
  bool       itsNoBarcodeGaps;
  // we need to use HepPDT translation instead
  std::vector<int>  m_herwig_to_pdg_id;
  std::set<int>     m_no_antiparticles;

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

  void  repair_hepevt( bool printInconsistencyErrors );
  void  remove_gaps_in_hepevt();
  void  zero_hepevt_entry( int i );

};	// CBherwig

}	// HepMC

#include "CLHEP/HepMC/CBherwig.icc"

#endif // CBHERWIG_H
