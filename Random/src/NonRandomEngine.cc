// $Id: NonRandomEngine.cc,v 1.4.2.4 2005/03/15 21:20:42 fischler Exp $
// -*- C++ -*-
//
// -----------------------------------------------------------------------
//                           Hep Random
//                        --- NonRandomEngine ---
//                   class implementation file
// -----------------------------------------------------------------------
// M. Fischler    - Created 9/30/99
//
// M. Fischler    - Modifications to capture sequence as a vector, which
//		    are needed to retain sanity when put and get are involved.
// Mark Fischler  - Methods for distrib. instance save/restore 12/8/04    
// M. Fischler	  - Initialization of all state data (even those parts unused)
//                - at ctor time, to thwart a VC++ i/o bug.
// M. Fischler    - put/get for vectors of ulongs		3/15/05
//
//=========================================================================

#include "CLHEP/Random/defs.h"
#include "CLHEP/Random/NonRandomEngine.h"
#include "CLHEP/Random/engineIDulong.h"
#include "CLHEP/Random/DoubConv.hh"
#include <stdlib.h>
#include <iostream>
#include <string>
#include <cassert>

namespace CLHEP {

std::string NonRandomEngine::name() const {return "NonRandomEngine";}

NonRandomEngine::NonRandomEngine() : nextHasBeenSet(false), 
				     sequenceHasBeenSet(false),
				     intervalHasBeenSet(false) ,
                                     nextRandom(0.05),
				     nInSeq(0),
				     randomInterval(0.1) { }

NonRandomEngine::~NonRandomEngine() { }


void NonRandomEngine::setNextRandom(double r) {
  nextRandom = r;
  nextHasBeenSet=true;
  return;
}

void NonRandomEngine::setRandomSequence(double* s, int n) {
  sequence.clear();
  for (int i=0; i<n; i++) sequence.push_back(*s++);
  assert (sequence.size() == (unsigned int)n);
  nInSeq = 0;
  sequenceHasBeenSet=true;
  nextHasBeenSet=false;
  return;
}

void NonRandomEngine::setRandomInterval(double x) {
  randomInterval = x;
  intervalHasBeenSet=true;
  return;
}

double NonRandomEngine::flat() {

  if (sequenceHasBeenSet) {
    double v = sequence[nInSeq++];
    if (nInSeq >= sequence.size() ) sequenceHasBeenSet = false;
    return v;
  }

  if ( !nextHasBeenSet ) {
    std::cout 
	<< "Attempt to use NonRandomEngine without setting next random!\n";
    exit(1);
  }

  double a = nextRandom;
  nextHasBeenSet = false;

  if (intervalHasBeenSet) {
    nextRandom += randomInterval;
    if ( nextRandom >= 1 ) nextRandom -= 1.0;
    nextHasBeenSet = true;
  }

  return a;
}


void NonRandomEngine::flatArray(const int size, double* vect) {
  for (int i = 0; i < size; ++i) {
    vect[i] = flat();
  }
}

std::ostream & NonRandomEngine::put (std::ostream & os) const {
  std::string beginMarker = "NonRandomEngine-begin";
  std::string  endMarker  = "NonRandomEngine-end";

  int pr = os.precision(20);
  os << " " << beginMarker << "\n";
  os << nextHasBeenSet  << " ";
  os << sequenceHasBeenSet << " ";
  os << intervalHasBeenSet << "\n";
  os << nextRandom << " " << nInSeq << " " << randomInterval << "\n";
  os <<  sequence.size() << "\n";
  for (unsigned int i = 0; i < sequence.size(); ++i) {
    os << sequence[i]  << "\n";
  }
  os << endMarker   << "\n ";
  os.precision(pr);
  return os;
}

std::vector<unsigned long> NonRandomEngine::put () const {
  std::vector<unsigned long> v;
  v.push_back (engineIDulong<NonRandomEngine>());
  std::vector<unsigned long> t;
  v.push_back(static_cast<unsigned long>(nextHasBeenSet));
  v.push_back(static_cast<unsigned long>(sequenceHasBeenSet));
  v.push_back(static_cast<unsigned long>(intervalHasBeenSet));
  t = DoubConv::dto2longs(nextRandom);
  v.push_back(t[0]); v.push_back(t[1]);
  v.push_back(static_cast<unsigned long>(nInSeq));
  t = DoubConv::dto2longs(randomInterval);
  v.push_back(t[0]); v.push_back(t[1]);
  v.push_back(static_cast<unsigned long>(sequence.size()));
  for (int i=0; i<sequence.size(); ++i) {
    t = DoubConv::dto2longs(sequence[i]);
    v.push_back(t[0]); v.push_back(t[1]);
  }
  return v;
}

std::istream & NonRandomEngine::get (std::istream & is) {
  std::string beginMarker = "NonRandomEngine-begin";
  is >> beginMarker;
  if (beginMarker != "NonRandomEngine-begin") {
    is.clear(std::ios::badbit | is.rdstate());
    std::cerr << "\nInput mispositioned or"
	      << "\nNonRandomEngine state description missing or"
	      << "\nwrong engine type found.\n";
    return is;
  }
  return getState(is);
}

std::string NonRandomEngine::beginTag ( )  { 
  return "NonRandomEngine-begin"; 
}  

std::istream & NonRandomEngine::getState (std::istream & is) {
  std::string  endMarker  = "NonRandomEngine-end";
  is >> nextHasBeenSet >> sequenceHasBeenSet >> intervalHasBeenSet;
  is >> nextRandom >> nInSeq >> randomInterval;
  unsigned int seqSize;
  is >> seqSize;
  sequence.clear();
  double x;
  for (unsigned int i = 0; i < seqSize; ++i) {
    is >> x;
    sequence.push_back(x);
  }
  is >> endMarker;
  if (endMarker != "NonRandomEngine-end") {
    is.clear(std::ios::badbit | is.rdstate());
    std::cerr << "\n NonRandomEngine state description incomplete."
	      << "\nInput stream is probably mispositioned now." << std::endl;
    return is;
  }
  return is;
}

bool NonRandomEngine::get (const std::vector<unsigned long> & v) {
  if (v[0] != engineIDulong<NonRandomEngine>()) {
    std::cerr << 
    	"\nNonRandomEngine get:state vector has wrong ID word - state unchanged\n";
    return false;
  }
  return getState(v);
}

bool NonRandomEngine::getState (const std::vector<unsigned long> & v) {
  unsigned int seqSize = v[9];
  if (v.size() != 2*seqSize + 10 ) {
    std::cerr << 
   "\nNonRandomEngine get:state vector has wrong length - state unchanged\n";
    return false;
  }
  std::vector<unsigned long> t(2);
  nextHasBeenSet     = (v[1]!=0);
  sequenceHasBeenSet = (v[2]!=0);
  intervalHasBeenSet = (v[3]!=0);
  t[0] = v[4]; t[1] = v[5]; nextRandom = DoubConv::longs2double(t);
  nInSeq = v[6];
  t[0] = v[7]; t[1] = v[8]; randomInterval = DoubConv::longs2double(t);
  sequence.clear();
  for (int i=0; i<seqSize; ++i) {
    t[0] = v[2*i+10]; t[1] = v[2*i+11];
    sequence.push_back(DoubConv::longs2double(t));
  }
  return true;
}


}  // namespace CLHEP

