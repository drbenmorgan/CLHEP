// $Id: ParticleID.hh,v 1.1.1.1.4.1 2004/04/21 16:14:51 garren Exp $
// ----------------------------------------------------------------------
//
// ParticleID.hh
//
//  various utilities to extract information from the particle ID
//
//  In the standard numbering scheme, the PID digits (base 10) are:
//            +/- n nr nl nq1 nq2 nq3 nj
//  It is expected that any 7 digit number used as a PID will adhere to 
//  the Monte Carlo numbering scheme documented by the PDG.
//  Note that many "new" particles not explicitly defined already 
//  can be expressed within this numbering scheme. 
//
// ----------------------------------------------------------------------
#ifndef PARTICLEID_HH
#define PARTICLEID_HH

#include <string>
#include <algorithm>	// swap()

// Particle names
#include "CLHEP/HepPDT/ParticleName.hh"

namespace HepPDT {

// convert from 2J+1 to the actual spin value 
double spinitod( int js );
int spindtoi( double spin );

// translate between generator ID's and standard numbering scheme
int translatePythiatoPDT( const int pythiaID );
int translateIsajettoPDT( const int isajetID );
int translateHerwigtoPDT( const int herwigID);
int translateQQtoPDT( const int qqID);
int translateGeanttoPDT( const int geantID);
int translatePDGtabletoPDT( const int pdgID);
int translateEvtGentoPDT( const int evtGenID );

int translatePDTtoPythia( const int pid );
int translatePDTtoIsajet( const int pid );
int translatePDTtoHerwig( const int pid );
int translatePDTtoQQ( const int pid );
int translatePDTtoGeant( const int pid );
int translatePDTtoPDGtable( const int pid );
int translatePDTtoEvtGen( const int pid );

//  PID digits (base 10) are: n nr nl nq1 nq2 nq3 nj
//  the location enum provides a convenient index into the PID
enum location { nj=1, nq3, nq2, nq1, nl, nr, n, n8, n9, n10 };

// constituent quarks
/**
 * @author
 * @ingroup heppdt
 */
struct Quarks {
    // -- constructors
    //
    Quarks( ) : nq1(0), nq2(0), nq3(0)  {}
    Quarks( short q1, short q2, short q3) : nq1(q1), nq2(q2), nq3(q3)  {}
    // -- data members
    //
    short nq1;
    short nq2;
    short nq3;
};

/**
 * @author
 * @ingroup heppdt
 */
class ParticleID {

public:

  // ---  birth/death:
  //
  inline ParticleID( int pid = 0 );

  // ---  copying:
  //
  inline ParticleID( const ParticleID & orig );
  inline ParticleID& operator=( const ParticleID & );
  inline void swap( ParticleID & other ); 

  inline bool  operator <  ( ParticleID const & other ) const;
  inline bool  operator == ( ParticleID const & other ) const;

  // ---  accessors:
  //
  int    pid( )        const { return itsPID; }
  inline int abspid( )        const;

  // ---  boolean methods:
  //
  bool isValid( )   const;
  bool isMeson( )   const;
  bool isBaryon( )  const;
  bool isDiQuark( ) const;
  bool isHadron( )  const;
  bool isLepton( )  const;
  bool isNucleus( ) const;
  //
  inline bool hasUp( )      const;
  inline bool hasDown( )    const;
  inline bool hasStrange( ) const;
  inline bool hasCharm( )   const;
  inline bool hasBottom( )  const;
  inline bool hasTop( )     const;

  // jSpin returns 2J+1, where J is the total spin
  int  jSpin( )        const;
  // sSpin returns 2S+1, where S is the spin
  int  sSpin( )        const;
  // lSpin returns 2L+1, where L is the orbital angular momentum
  int  lSpin( )        const;
  // return the first two digits if this is a "fundamental" particle
  int fundamentalID( ) const;
  // returns everything beyond the 7th digit (e.g. outside the numbering scheme)
  int extraBits( ) const;
  // returns a list of 3 constituent quarks
  Quarks quarks( ) const;
  // this is mostly for use by functions like addPDGParticles that have to 
  // figure out the charge from the PID
  int threeCharge( ) const;
  // if this is a nucleus, get A and Z
  int A( ) const;
  int Z( ) const;
  // digit returns the digit at a named location in the PID
  unsigned short digit(location) const;
  // particle name
  const std::string PDTname() const { return particleName( itsPID ); }

private:

  int itsPID;

};  // ParticleID

inline
void swap( ParticleID & first, ParticleID & second ) { first.swap( second ); }

} // HepPDT

#include "CLHEP/HepPDT/ParticleID.icc"

#endif // PARTICLEID_HH
