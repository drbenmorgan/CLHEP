// -*- C++ -*-
// $Id: ranRestoreTest.cc,v 1.1.1.1 2003/07/15 20:15:05 garren Exp $
// ----------------------------------------------------------------------
#include "CLHEP/Random/Randomize.h"
#include "Random/defs.h"
#include <iostream>

double remembered_r2;
double remembered_r1005;
double remembered_r1006;
double remembered_r1007;

// ------------------- The following should all FAIL ------------

void saveStepX() {
  double r = RandGauss::shoot();
  std::cout << "r(1) = " << r << std::endl;
  HepRandom::saveEngineStatus();
  r = RandGauss::shoot();
  std::cout << "r(2) = " << r << std::endl;
  remembered_r2 = r;
  r = RandGauss::shoot();
  std::cout << "r(3) = " << r << std::endl;
  for (int i=0; i < 1001; i++) {
    r = RandGauss::shoot();
  }    
  r = RandGauss::shoot();
  remembered_r1005 = r;
  std::cout << "r1005= " << r << std::endl;
  r = RandGauss::shoot();
  return;
}

void restoreStepX() {
  HepRandom::restoreEngineStatus();
  double r = RandGauss::shoot();
  std::cout << "restored r(2) = " << r << std::endl;
  if ( r != remembered_r2 ) {
    std::cout << "????? THIS DOES NOT MATCH REMEMBERED VALUE!\n";
  }
  r = RandGauss::shoot();
  std::cout << "restored r(3) = " << r << std::endl;
  for (int i=0; i < 1001; i++) {
    r = RandGauss::shoot();
  }    
  r = RandGauss::shoot();
  std::cout << "restored r1005= " << r << std::endl;
  if ( r != remembered_r1005 ) {
    std::cout << "????? THIS DOES NOT MATCH REMEMBERED VALUE!\n";
  }
  return;
}

void BsaveStepX() {
  int r = RandFlat::shootBit();
  std::cout << "r(1) = " << r << std::endl;
  HepRandom::saveEngineStatus();
  r = RandFlat::shootBit();
  std::cout << "r(2) = " << r << std::endl;
  remembered_r2 = r;
  r = RandFlat::shootBit();
  std::cout << "r(3) = " << r << std::endl;
  double d;
  for (int i=0; i < 1001; i++) {
    d = RandFlat::shoot();
    if (d > 1) std::cout << 
    "This line inserted so clever compilers don't warn about not using d\n";
  }    
  r = RandFlat::shootBit();
  remembered_r1005 = r;
  std::cout << "r1005= " << r << std::endl;
  r = RandFlat::shootBit();
  return;
}

void BrestoreStepX() {
  HepRandom::restoreEngineStatus();
  int r = RandFlat::shootBit();
  std::cout << "restored r(2) = " << r << std::endl;
  if ( r != remembered_r2 ) {
    std::cout << "????? THIS DOES NOT MATCH REMEMBERED VALUE!\n";
  }
  r = RandFlat::shootBit();
  std::cout << "restored r(3) = " << r << std::endl;
  for (int i=0; i < 1001; i++) {
    r = RandFlat::shootBit();
  }    
  r = RandFlat::shootBit();
  std::cout << "restored r1005= " << r << std::endl;
  if ( r != remembered_r1005 ) {
    std::cout << "????? THIS DOES NOT MATCH REMEMBERED VALUE!\n";
  }
  return;
}

// ------------------- The following should all WORK ------------

void saveStep() {
  double r = RandGauss::shoot();
  std::cout << "r(1) = " << r << std::endl;
  RandGauss::saveEngineStatus();
  r = RandGauss::shoot();
  std::cout << "r(2) = " << r << std::endl;
  remembered_r2 = r;
  r = RandGauss::shoot();
  std::cout << "r(3) = " << r << std::endl;
  for (int i=0; i < 1001; i++) {
    r = RandGauss::shoot();
  }    
  r = RandGauss::shoot();
  remembered_r1005 = r;
  std::cout << "r1005= " << r << std::endl;
  r = RandGauss::shoot();
  return;
}

void restoreStep() {
  RandGauss::restoreEngineStatus();
  double r = RandGauss::shoot();
  std::cout << "restored r(2) = " << r << std::endl;
  if ( r != remembered_r2 ) {
    std::cout << "????? THIS DOES NOT MATCH REMEMBERED VALUE!\n";
  }
  r = RandGauss::shoot();
  std::cout << "restored r(3) = " << r << std::endl;
  for (int i=0; i < 1001; i++) {
    r = RandGauss::shoot();
  }    
  r = RandGauss::shoot();
  std::cout << "restored r1005= " << r << std::endl;
  if ( r != remembered_r1005 ) {
    std::cout << "????? THIS DOES NOT MATCH REMEMBERED VALUE!\n";
  }
  return;
}

void BsaveStep() {
  int r = RandFlat::shootBit();
  std::cout << "r(1) = " << r << std::endl;
  RandFlat::saveEngineStatus();
  r = RandFlat::shootBit();
  std::cout << "r(2) = " << r << std::endl;
  remembered_r2 = r;
  r = RandFlat::shootBit();
  std::cout << "r(3) = " << r << std::endl;
  for (int i=0; i < 1001; i++) {
    r = RandFlat::shootBit();
  }    
  r = RandFlat::shootBit();
  remembered_r1005 = r;
  std::cout << "r1005 = " << r << std::endl;
  r = RandFlat::shootBit();
  remembered_r1006 = r;
  std::cout << "r1006 = " << r << std::endl;
  r = RandFlat::shootBit();
  remembered_r1007 = r;
  std::cout << "r1007 = " << r << std::endl;
  r = RandFlat::shootBit();
  return;
}

void BrestoreStep() {
  RandFlat::restoreEngineStatus();
  int r = RandFlat::shootBit();
  std::cout << "restored r(2) = " << r << std::endl;
  if ( r != remembered_r2 ) {
    std::cout << "????? THIS DOES NOT MATCH REMEMBERED VALUE!\n";
  }
  r = RandFlat::shootBit();
  std::cout << "restored r(3) = " << r << std::endl;
  for (int i=0; i < 1001; i++) {
    r = RandFlat::shootBit();
  }    
  r = RandFlat::shootBit();
  std::cout << "restored r1005= " << r << std::endl;
  if ( r != remembered_r1005 ) {
    std::cout << "????? THIS DOES NOT MATCH REMEMBERED VALUE!\n";
  }
  r = RandFlat::shootBit();
  std::cout << "restored r1006= " << r << std::endl;
  if ( r != remembered_r1006 ) {
    std::cout << "????? THIS DOES NOT MATCH REMEMBERED VALUE!\n";
  }
  r = RandFlat::shootBit();
  std::cout << "restored r1007= " << r << std::endl;
  if ( r != remembered_r1007 ) {
    std::cout << "????? THIS DOES NOT MATCH REMEMBERED VALUE!\n";
  }
  return;
}

// --------------------------------------------------


int main() {
  std::cout << "Using old method or HepRandom::saveEngineStatus:\n";
  std::cout << "All these tests should have a chance of failure.\n";

  saveStepX();
  restoreStepX();
  BsaveStepX();
  BrestoreStepX();
  
  std::cout << "Using the class-specifice RandGauss::saveEngineStatus:\n";
  std::cout << "All these tests should work properly.\n";

  saveStep();
  restoreStep();
  BsaveStep();
  BrestoreStep();
  
  return 0;
}	

