// $Id: TempParticleData.hh,v 1.1.1.1 2003/07/15 20:15:05 garren Exp $
// ----------------------------------------------------------------------
//
// TempParticleData.hh
//
// temporary structure to hold particles while getting all the info
// ----------------------------------------------------------------------
#ifndef TEMPPARTICLEDATA_HH
#define TEMPPARTICLEDATA_HH

#include <string>
#include <vector>

#include "CLHEP/HepPDT/SpinState.hh"
#include "CLHEP/HepPDT/ParticleID.hh"
#include "CLHEP/HepPDT/Measurement.hh"

namespace HepPDT {

// free function
double calculateWidthFromLifetime( double );

// constituent information
/**
 * @author
 * @ingroup heppdt
 */
struct TempConstituent {
    TempConstituent( ParticleID p = ParticleID(0), int m = -1 )
      : tempConstituentPID(p), tempMultiplicity(m)  {}
    ParticleID tempConstituentPID;
    int        tempMultiplicity;
};

/**
 * @author
 * @ingroup heppdt
 */
struct TempDecayData  {
  std::string         tempDecayName;	// use string to hold int if necessary
  double              tempBranchingFraction;
  std::vector<std::string> tempDaughterList;
  std::vector<double>      tempDecayParameters;
};

// useful typedef
  typedef std::vector<TempDecayData>  TDDlist;

// Hold Alias information from EvtGen
/**
 * @author
 * @ingroup heppdt
 */
struct TempAliasData {

  // ---  birth/death:
  //
  TempAliasData();	// used in a map<>

  std::string    tempAlias;		// the alias
  std::string    tempAliasedParticle;	// the "real" particle
  std::string    tempChargeConj;	// set if there is a charge conjugate alias
  TDDlist        tempAliasDecayList;	// decay list for the alias
};

/**
 * @author
 * @ingroup heppdt
 */
struct TempParticleData  {

  // ---  birth/death:
  //
  TempParticleData();	// used in a map<>
  explicit TempParticleData( int id );
  explicit TempParticleData( ParticleID pid );
  TempParticleData( int id, std::string const & name, double charge,
                    SpinState const & Spin, 
		    Measurement const & mass, Measurement const & wid );

  // ---  copying:
  //
  TempParticleData( TempParticleData const & orig );
  TempParticleData & operator = ( TempParticleData const & rhs );
  void swap( TempParticleData & other );
  TempParticleData  antiparticle( std::string const & name );
 
  // -- mutator - get spin state and quark list from PID
  bool processPID();

  // -- data members (public by design)
  //
  ParticleID                   tempID;
  std::string                  tempParticleName;
  double                       tempCharge;
  double                       tempColorCharge;
  SpinState                    tempSpin;
  Measurement                  tempMass;
  Measurement                  tempWidth;
  double                       tempLowCutoff;
  double                       tempHighCutoff;
  std::vector<TempConstituent> tempQuarks;
  TDDlist                      tempDecayList; 

};  // TempParticleData

inline
void swap( TempParticleData & first, TempParticleData & second ) { first.swap( second ); }

}	// HepPDT

#endif // TEMPPARTICLEDATA_HH
