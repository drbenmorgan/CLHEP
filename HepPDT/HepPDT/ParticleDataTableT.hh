// $Id: ParticleDataTableT.hh,v 1.1.1.1 2003/07/15 20:15:05 garren Exp $
// ----------------------------------------------------------------------
//
// ParticleDataTableT.hh
// Author: Lynn Garren, Walter Brown
//
// ----------------------------------------------------------------------
#ifndef PARTICLEDATATABLET_HH
#define PARTICLEDATATABLET_HH

#include <iostream>
#include <map>

#include "CLHEP/HepPDT/ParticleID.hh"
#include "CLHEP/HepPDT/DecayDataT.hh"
#include "CLHEP/HepPDT/DecayChannelT.hh"
#include "CLHEP/HepPDT/ParticleDataT.hh"
#include "CLHEP/HepPDT/Version.hh"

namespace HepPDT {
  
/**
 * @author
 * @ingroup heppdt
 */
template< class Config >
class ParticleDataTableT  {
  
public:
  typedef typename Config::CPDlist                CPDlist;
  typedef typename Config::DDlist                 DDlist;
  typedef typename Config::DecayData              DecayData;
  typedef typename Config::ParticleData           ParticleData;
  typedef typename Config::ParticleDataTable      ParticleDataTable;
  typedef typename Config::CPDID                  CPDID;
  typedef typename Config::DDID                   DDID;
  typedef typename Config::CPD                    CPD;

  typedef  std::map<ParticleID,TempParticleData>  TempMap;
  typedef  std::map<ParticleID,ParticleData>      PDTMap;

  typedef typename  PDTMap::const_iterator  const_iterator;

  // ---  birth/death:
  //
  inline ParticleDataTableT( std::string name = " " );
  inline ~ParticleDataTableT();

  // ---  accessors:
  //
  int             size()  const { return itsMap.size(); }
  const_iterator  begin() const { return itsMap.begin(); }
  const_iterator  end()   const { return itsMap.end(); }
  std::string     tableName() const { return itsTableName; }

  inline ParticleData const * particle( ParticleID ) const;
  inline ParticleData       * particle( ParticleID );

  inline ParticleData       * operator [] ( ParticleID );
  inline ParticleData const * operator [] ( ParticleID ) const;

  void writeParticleData( std::ostream & outstr );
  
  void convertTemporaryMap( TempMap & tempPDT, std::ostream & err );

  DDID addDecayData( DecayData const & d );

private:
  // --- local data:
  CPDlist     itsCPDlist;
  DDlist      itsDDlist;
  PDTMap      itsMap;
  std::string itsTableName;

  // ---  copying; forbidden:
  ParticleDataTableT( const ParticleDataTableT & orig );
  ParticleDataTableT& operator=( const ParticleDataTableT & );
  
  // --- add method is private
  void addParticle( ParticleData const & p );
  CPDID addParticleData( CPD const & cpd );
  typedef typename  PDTMap::iterator        iterator;
  //?iterator        begin()       { return itsMap.begin(); }
  //?iterator        end()       { return itsMap.end(); }

};  // ParticleDataTableT

// --- free functions
//

template< class Config >
bool writePDGStream (std::ostream & os, const ParticleDataTableT<Config> & table);

template< class Config >
bool writePythiaStream (std::ostream & os, const ParticleDataTableT<Config> & table);

template< class Config >
bool writeHerwigStream (std::ostream & os, const ParticleDataTableT<Config> & table);

template< class Config >
bool writeIsajetStream (std::ostream & os, const ParticleDataTableT<Config> & table);

template< class Config >
bool writeQQStream (std::ostream & os, const ParticleDataTableT<Config> & table);

template< class Config >
bool writeEvtGenStream (std::ostream & os, const ParticleDataTableT<Config> & table);


}	// HepPDT

#include "CLHEP/HepPDT/ParticleDataTableT.icc"
#include "CLHEP/HepPDT/convertTemporaryMap.icc"

#endif // PARTICLEDATATABLET_HH