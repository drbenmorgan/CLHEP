// $Id: TableBuilderT.hh,v 1.1.1.1 2003/07/15 20:15:05 garren Exp $
// ----------------------------------------------------------------------
//
// TableBuilderT.hh
// Author: Marc Paterno, Walter Brown, Lynn Garren
//
// ----------------------------------------------------------------------
// User code:
//    ParticleDataTable pdt;
//    {
//       TableBuilderT      tb(pdt);
//       addPythiaParticles( istream1, tb );
//       addPythiaParticles( istream2, tb );
//       tb.addParticle( myTempParticleData );
//       // ...
//    }  // triggers tb's destruction, filling pdt!
// ----------------------------------------------------------------------
#ifndef TABLEBUILDERT_HH
#define TABLEBUILDERT_HH


#include <iostream>
#include <string>
#include <map>

#include "CLHEP/HepPDT/ParticleDataTableT.hh"
#include "CLHEP/HepPDT/TempParticleData.hh"
#include "CLHEP/HepPDT/DefTable.hh"
#include "CLHEP/HepPDT/QQDecayTable.hh"
#include "CLHEP/HepPDT/stringtodouble.hh"

namespace HepPDT {


/**
 * @author
 * @ingroup heppdt
 */
template< class Config >
class TableBuilderT  {
  typedef  std::map<ParticleID,TempParticleData>   TempMap;
  typedef  std::map<std::string,ParticleID>        TempIDMap;
  typedef  std::map<std::string,TempAliasData>     TempAliasMap;

public:
  explicit TableBuilderT( ParticleDataTableT<Config> & table,
                          std::ostream & str = std::cerr )
  : pdt(table), os(str)   { reverseEngineer(); }
  ~TableBuilderT()  { pdt.convertTemporaryMap( tempPDT, os ); }

  inline TempParticleData &  getParticleData( ParticleID pid );
  inline TempParticleData &  getParticleData( std::string const & name );
  inline TempParticleData &  getAntiParticle( ParticleID pid, 
                                              const std::string & aname );

  // --- mutators
  //
  inline void addParticle( TempParticleData const & pd );
         void removeParticle(ParticleID pid )  { tempPDT.erase(pid); }
  
  inline void addAlias( TempAliasData const & ad );

  // --- booleans
  //
  inline bool hasParticleData( std::string const & name );
  inline bool hasAlias( std::string const & alias );
         bool hasDefinition( std::string const & def ) { return tempDefMap.hasDefinition( def ); }

  // --- accessors
  //
         int             size()       const { return tempPDT.size(); }
         int             aliasSize()  const { return tempAliases.size(); }
         DefTable      & definitions()      { return tempDefMap; }
	 double          definition( std::string const & def ) { return tempDefMap.definition( def ); }
  inline TempAliasData & aliasData( std::string const & alias );

private:
  ParticleDataTableT<Config> &  pdt;
  TempMap                       tempPDT;
  TempIDMap                     tempIDT;
  TempAliasMap                  tempAliases;	// hold EvtGen alias information
  DefTable                      tempDefMap;	// hold EvtGen "Define" info
  std::ostream &                os;   		// for diagnostics

  inline void fillPDT();		// ????
  // unpack existing PDT so its contents can be modified and added to
  inline void reverseEngineer();

  // forbidden copy:
  TableBuilderT &  operator = ( TableBuilderT const & );
  TableBuilderT( TableBuilderT const & );

};  // TableBuilderT<>


// --- free functions
//

template< class Config >
inline
bool  addPDGParticles( std::istream & pdfile, TableBuilderT<Config> & tb );

template< class Config >
inline
bool  addPythiaParticles( std::istream & pdfile, TableBuilderT<Config> & tb );

template< class Config >
inline
bool  addHerwigParticles( std::istream & pdfile, TableBuilderT<Config> & tb );

template< class Config >
inline
bool  addIsajetParticles( std::istream & pdfile, TableBuilderT<Config> & tb );

template< class Config >
inline
bool  addQQParticles( QQDecayTable & qd, TableBuilderT<Config> & tb );

template< class Config >
inline
bool  addEvtGenParticles( std::istream & pdfile, TableBuilderT<Config> & tb );

}  // namespace HepPDT

#include "CLHEP/HepPDT/TableBuilderT.icc"
#include "CLHEP/HepPDT/TableBuilderPythiaT.icc"
#include "CLHEP/HepPDT/TableBuilderHerwigT.icc"
#include "CLHEP/HepPDT/TableBuilderIsajetT.icc"
#include "CLHEP/HepPDT/TableBuilderTEvtGen.icc"
#include "CLHEP/HepPDT/TableBuilderTQQ.icc"

#endif // TABLEBUILDERT_HH
