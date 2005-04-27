// ----------------------------------------------------------------------
#include "CLHEP/Random/Randomize.h"
#include "CLHEP/Random/NonRandomEngine.h"
#include "CLHEP/Random/defs.h"
#include <iostream>
#include <iomanip>
#include <vector>

#define CLEAN_OUTPUT
#ifdef CLEAN_OUTPUT
  std::ofstream output("testSaveEngineStatus.cout");  
#else
  std::ostream & output = std::cout;
#endif

// Normally on  for routine validation:

#define TEST_ORIGINAL_SAVE

// Normally off for routine validation:

#ifdef TURNOFF
#define TEST_MISSING_FILES
#define CREATE_OLD_SAVES
#define VERIFY_OLD_SAVES
#endif

#define VERBOSER
#define VERBOSER2

using namespace CLHEP;

double remembered_r2;
double remembered_r1005;
double remembered_r1006;
double remembered_r1007;

// Absolutely Safe Equals Without Registers Screwing Us Up
bool equals01(const std::vector<double> &ab) {
  return ab[1]==ab[0];
}  
bool equals(double a, double b) {
  std::vector<double> ab(2);
  ab[0]=a;  ab[1]=b;
  return (equals01(ab));
}

// ------------------- The following should all FAIL ------------

int saveStepX() {
  double r = RandGauss::shoot();
  output << "r(1) = " << r << std::endl;
  HepRandom::saveEngineStatus();
  r = RandGauss::shoot();
  output << "r(2) = " << r << std::endl;
  remembered_r2 = r;
  r = RandGauss::shoot();
  output << "r(3) = " << r << std::endl;
  for (int i=0; i < 1001; i++) {
    r = RandGauss::shoot();
  }    
  r = RandGauss::shoot();
  remembered_r1005 = r;
  output << "r1005= " << r << std::endl;
  r = RandGauss::shoot();
  return 0;
}

int restoreStepX() {
  HepRandom::restoreEngineStatus();
  double r = RandGauss::shoot();
  output << "restored r(2) = " << r << std::endl;
  if ( ! equals(r,remembered_r2) ) {
    output << "THIS DOES NOT MATCH REMEMBERED VALUE BUT THAT IS EXPECTED\n";
  }
  r = RandGauss::shoot();
  output << "restored r(3) = " << r << std::endl;
  for (int i=0; i < 1001; i++) {
    r = RandGauss::shoot();
  }    
  r = RandGauss::shoot();
  output << "restored r1005= " << r << std::endl;
  if ( !equals(r,remembered_r1005) ) {
    output << "THIS DOES NOT MATCH REMEMBERED VALUE BUT THAT IS EXPECTED\n";
  }
  return 0;
}

int BsaveStepX() {
  int r = RandFlat::shootBit();
  output << "r(1) = " << r << std::endl;
  HepRandom::saveEngineStatus();
  r = RandFlat::shootBit();
  output << "r(2) = " << r << std::endl;
  remembered_r2 = r;
  r = RandFlat::shootBit();
  output << "r(3) = " << r << std::endl;
  double d;
  for (int i=0; i < 1001; i++) {
    d = RandFlat::shoot();
    if (d > 1) output << 
    "This line inserted so clever compilers don't warn about not using d\n";
  }    
  r = RandFlat::shootBit();
  remembered_r1005 = r;
  output << "r1005= " << r << std::endl;
  r = RandFlat::shootBit();
  return 0;
}

int BrestoreStepX() {
  HepRandom::restoreEngineStatus();
  int r = RandFlat::shootBit();
  output << "restored r(2) = " << r << std::endl;
  if ( r != remembered_r2 ) {
    output << "THIS DOES NOT MATCH REMEMBERED VALUE BUT THAT IS EXPECTED\n";
  }
  r = RandFlat::shootBit();
  output << "restored r(3) = " << r << std::endl;
  for (int i=0; i < 1001; i++) {
    r = RandFlat::shootBit();
  }    
  r = RandFlat::shootBit();
  output << "restored r1005= " << r << std::endl;
  if ( r != remembered_r1005 ) {
    output << "THIS DOES NOT MATCH REMEMBERED VALUE BUT THAT IS EXPECTED\n";
  }
  return 0;
}

// ------------------- The following should all WORK ------------

int saveStep() {
  int stat=0;
  double r = RandGauss::shoot();
  output << "r(1) = " << r << std::endl;
  RandGauss::saveEngineStatus();
  r = RandGauss::shoot();
  output << "r(2) = " << r << std::endl;
  remembered_r2 = r;
  r = RandGauss::shoot();
  output << "r(3) = " << r << std::endl;
  for (int i=0; i < 1001; i++) {
    r = RandGauss::shoot();
  }    
  r = RandGauss::shoot();
  remembered_r1005 = r;
  output << "r1005= " << r << std::endl;
  r = RandGauss::shoot();
  return stat;
}

int restoreStep() {
  int stat=0;
  RandGauss::restoreEngineStatus();
  double r = RandGauss::shoot();
  output << "restored r(2) = " << r << std::endl;
  if ( !equals(r,remembered_r2) ) {
    std::cout << "restored r(2) = " << r << std::endl;
    std::cout << "????? THIS DOES NOT MATCH REMEMBERED VALUE!\n";
    #ifdef CLEAN_OUTPUT
    output << "restored r(2) = " << r << std::endl;
    output << "????? THIS DOES NOT MATCH REMEMBERED VALUE!\n";
    #endif
    stat += 1;
  }
  r = RandGauss::shoot();
  output << "restored r(3) = " << r << std::endl;
  for (int i=0; i < 1001; i++) {
    r = RandGauss::shoot();
  }    
  r = RandGauss::shoot();
  output << "restored r1005= " << r << std::endl;
  if ( !equals(r,remembered_r1005) ) {
    std::cout << "restored r1005= " << r << std::endl;
    std::cout << "????? THIS DOES NOT MATCH REMEMBERED VALUE!\n";
    #ifdef CLEAN_OUTPUT
    output << "restored r1005= " << r << std::endl;
    output << "????? THIS DOES NOT MATCH REMEMBERED VALUE!\n";
    #endif
    stat += 2;
  }
  return stat;
}

int BsaveStep() {
  int stat=0;
  int r = RandFlat::shootBit();
  output << "r(1) = " << r << std::endl;
  RandFlat::saveEngineStatus();
  r = RandFlat::shootBit();
  output << "r(2) = " << r << std::endl;
  remembered_r2 = r;
  r = RandFlat::shootBit();
  output << "r(3) = " << r << std::endl;
  for (int i=0; i < 1001; i++) {
    r = RandFlat::shootBit();
  }    
  r = RandFlat::shootBit();
  remembered_r1005 = r;
  output << "r1005 = " << r << std::endl;
  r = RandFlat::shootBit();
  remembered_r1006 = r;
  output << "r1006 = " << r << std::endl;
  r = RandFlat::shootBit();
  remembered_r1007 = r;
  output << "r1007 = " << r << std::endl;
  r = RandFlat::shootBit();
  return stat;
}

int BrestoreStep() {
  int stat=0;
  RandFlat::restoreEngineStatus();
  int r = RandFlat::shootBit();
  output << "restored r(2) = " << r << std::endl;
  if ( r != remembered_r2 ) {
    stat += 4;
    std::cout << "restored r(2) = " << r << std::endl;
    std::cout << "????? THIS DOES NOT MATCH REMEMBERED VALUE!\n";
    #ifdef CLEAN_OUTPUT
    output << "restored r(2) = " << r << std::endl;
    output << "????? THIS DOES NOT MATCH REMEMBERED VALUE!\n";
    #endif
  }
  r = RandFlat::shootBit();
  output << "restored r(3) = " << r << std::endl;
  for (int i=0; i < 1001; i++) {
    r = RandFlat::shootBit();
  }    
  r = RandFlat::shootBit();
  output << "restored r1005= " << r << std::endl;
  if ( r != remembered_r1005 ) {
    stat += 8;
    std::cout << "restored r1005= " << r << std::endl;
    std::cout << "????? THIS DOES NOT MATCH REMEMBERED VALUE!\n";
    #ifdef CLEAN_OUTPUT
    output << "restored r1005= " << r << std::endl;
    output << "????? THIS DOES NOT MATCH REMEMBERED VALUE!\n";
    #endif
  }
  r = RandFlat::shootBit();
  output << "restored r1006= " << r << std::endl;
  if ( r != remembered_r1006 ) {
    stat += 16;
    std::cout << "restored r1006= " << r << std::endl;
    std::cout << "????? THIS DOES NOT MATCH REMEMBERED VALUE!\n";
    #ifdef CLEAN_OUTPUT
    output << "restored r1006= " << r << std::endl;
    output << "????? THIS DOES NOT MATCH REMEMBERED VALUE!\n";
    #endif
  }
  r = RandFlat::shootBit();
  output << "restored r1007= " << r << std::endl;
  if ( r != remembered_r1007 ) {
    stat += 32;
    std::cout << "restored r1007= " << r << std::endl;
    std::cout << "????? THIS DOES NOT MATCH REMEMBERED VALUE!\n";
    #ifdef CLEAN_OUTPUT
    output << "restored r1007= " << r << std::endl;
    output << "????? THIS DOES NOT MATCH REMEMBERED VALUE!\n";
    #endif
  }
  return stat;
}

// --- The following should work, by failing in an expected way -------

template <class E, class D>
int fileNotThere() {
  int stat = 0;
  HepRandomEngine * old = D::getTheEngine();
  E e(123);
  output << "File-not-found test restoring "<<D::distributionName()<<":\n";
  D::setTheEngine(&e);
  D::restoreEngineStatus("noSuchFile");
  D::setTheEngine(old);  // If we don't do this, then the static engine shared
  			 // by every shoot() method reamins e -- which is about
			 // to go out of scope and be destructed!
  return stat;
}

template <class E>
int fileNotThereEngine() {
  int stat = 0;
  stat |= fileNotThere <E, RandBinomial>();
  stat |= fileNotThere <E, RandBit>();
  stat |= fileNotThere <E, RandBreitWigner>();
  stat |= fileNotThere <E, RandChiSquare>();
  stat |= fileNotThere <E, RandExponential>();
  stat |= fileNotThere <E, RandFlat>();
  stat |= fileNotThere <E, RandGamma>();
  stat |= fileNotThere <E, RandGauss>();
  stat |= fileNotThere <E, RandGaussQ>();
  stat |= fileNotThere <E, RandGaussT>();
  stat |= fileNotThere <E, RandLandau>();
  stat |= fileNotThere <E, RandPoisson>();
  stat |= fileNotThere <E, RandPoissonQ>();
  stat |= fileNotThere <E, RandPoissonT>();
  stat |= fileNotThere <E, RandStudentT>();
  return stat;
}

int missingFile() {
  int stat = 0;
  stat |= fileNotThereEngine<DRand48Engine>();
  stat |= fileNotThereEngine<DualRand>();
  stat |= fileNotThereEngine<Hurd160Engine>();
  stat |= fileNotThereEngine<Hurd288Engine>();
  stat |= fileNotThereEngine<HepJamesRandom>();
  stat |= fileNotThereEngine<MTwistEngine>();
  stat |= fileNotThereEngine<RandEngine>();
  stat |= fileNotThereEngine<RanecuEngine>();
  stat |= fileNotThereEngine<Ranlux64Engine>();
  stat |= fileNotThereEngine<RanluxEngine>();
  stat |= fileNotThereEngine<RanshiEngine>();
  stat |= fileNotThereEngine<TripleRand>();
  return stat;
}
  
// -- The following was used to capture old-form engine states (sans name) --

template <class E, class D>
int saveEngine(const char* filename) {
  int stat = 0;
  HepRandomEngine * old = D::getTheEngine();
  E e(123);
  D::setTheEngine(&e);
  double r=0; 
  for (int i=0; i<3; i++) r += D::shoot();
  D::saveEngineStatus(filename);
  if (r == -99999999.1) stat = 999; // This prevents clever compilers from
  				    // deducing that r is never needed
  D::setTheEngine(old);  // If we don't do this, then the static engine shared
  			 // by every shoot() method reamins e -- which is about
			 // to go out of scope and be destructed!
  return stat;
}

// -- The following checks on static engine restores, from old and new forms --

template <class E, class D>
int checkSaveEngine(const char* filename) {
  int stat = 0;
  HepRandomEngine * old = D::getTheEngine();

  // Generate save with current format (default file name is fine)
  E e(123);
  D::setTheEngine(&e);
  double r=0; 
  for (int i=0; i<3; i++) r += D::shoot();
  D::saveEngineStatus();

  // Figure out what the key variate value should be
  double keyValue = D::shoot();

  // Restore state based on old file, and check for proper value
  D::restoreEngineStatus(filename);
  if (!equals(D::shoot(), keyValue)) {
    std::cout << "???? Value mismatch from file " << filename << "\n";
    #ifdef CLEAN_OUTPUT
    output << "???? Value mismatch from file " << filename << "\n";
    #endif
    stat |= 64;
  }

  // Restore state based on that save, and check for proper value
  D::restoreEngineStatus();
  if (!equals(D::shoot(),keyValue)) {
    std::cout << "???? Value mismatch from new-format file \n";
    #ifdef CLEAN_OUTPUT
    output << "???? Value mismatch from new-format file \n";
    #endif
    stat |= 128;
  }

  D::setTheEngine(old);  
  return stat;
}

// ---------------------------------------------
// ---------------------------------------------
// ---------------------------------------------


int main() {
  int stat = 0;

#ifdef TEST_ORIGINAL_SAVE
  output << "=====================================\n";
  output << "             Part I \n";
  output << "Original tests of static save/restore\n";
  output << "=====================================\n\n";
  
  output << "Using old method or HepRandom::saveEngineStatus:\n";
  output << "All these tests should have a chance of failure.\n";

  output << RandGauss:: getTheEngine()->name();  
  output << RandGaussQ::getTheEngine()->name();  

  stat |= saveStepX();
  stat |= restoreStepX();
  stat |= BsaveStepX();
  stat |= BrestoreStepX();
  
  output << "Using the class-specific RandGauss::saveEngineStatus:\n";
  output << "All these tests should work properly.\n";

  stat |= saveStep();
  stat |= restoreStep();
  stat |= BsaveStep();
  stat |= BrestoreStep();
#endif
  
#ifdef TEST_MISSING_FILES
  output << "\n=======================================\n";
  output << "             Part Ia \n";
  output << "Test of behavior when a file is missing \n";
  output << "=======================================\n\n";

  output << "Testing restoreEngineStatus with missing file:\n";
  output << "Expect a number of <Failure to find or open> messages!\n";
  stat |= missingFile();
#endif

#ifdef CREATE_OLD_SAVES
  stat |= saveEngine<DRand48Engine, RandPoisson>("DRand48Engine.oldsav");
  stat |= saveEngine<DualRand,      RandPoisson>("DualRand.oldsav");
  stat |= saveEngine<Hurd160Engine, RandPoisson>("Hurd160Engine.oldsav");
  stat |= saveEngine<Hurd288Engine, RandPoisson>("Hurd288Engine.oldsav");
  stat |= saveEngine<HepJamesRandom,RandPoisson>("HepJamesRandom.oldsav");
  stat |= saveEngine<MTwistEngine,  RandPoisson>("MTwistEngine.oldsav");
  stat |= saveEngine<RanecuEngine,  RandPoisson>("RanecuEngine.oldsav");
  stat |= saveEngine<Ranlux64Engine,RandPoisson>("Ranlux64Engine.oldsav");
  stat |= saveEngine<RanluxEngine,  RandPoisson>("RanluxEngine.oldsav");
  stat |= saveEngine<RanshiEngine,  RandPoisson>("RanshiEngine.oldsav");
  stat |= saveEngine<TripleRand,    RandPoisson>("TripleRand.oldsav");
#endif

#ifdef VERIFY_OLD_SAVES
  output << "\n==============================================\n";
  output << "               Part Ib \n";
  output << "  Verification that changes wont invalidate \n";
  output << "invalidate engine saves from previous versions \n";
  output << "==============================================\n\n";

  stat |= checkSaveEngine<DRand48Engine, RandPoisson>("DRand48Engine.oldsav");
  stat |= checkSaveEngine<DualRand,      RandPoisson>("DualRand.oldsav");
  stat |= checkSaveEngine<Hurd160Engine, RandPoisson>("Hurd160Engine.oldsav");
  stat |= checkSaveEngine<Hurd288Engine, RandPoisson>("Hurd288Engine.oldsav");
  stat |= checkSaveEngine<HepJamesRandom,RandPoisson>("HepJamesRandom.oldsav");
  stat |= checkSaveEngine<MTwistEngine,  RandPoisson>("MTwistEngine.oldsav");
  stat |= checkSaveEngine<Ranlux64Engine,RandPoisson>("Ranlux64Engine.oldsav");
  stat |= checkSaveEngine<RanluxEngine,  RandPoisson>("RanluxEngine.oldsav");
  stat |= checkSaveEngine<RanshiEngine,  RandPoisson>("RanshiEngine.oldsav");
  stat |= checkSaveEngine<TripleRand,    RandPoisson>("TripleRand.oldsav");
  stat |= checkSaveEngine<RanecuEngine,  RandPoisson>("RanecuEngine.oldsav");
#endif

  output << "\n=============================================\n\n";

  if (stat != 0) {
     std::cout << "One or more problems detected: stat = " << stat << "\n";
     output << "One or more problems detected: stat = " << stat << "\n";
  }  else {
     output << "testSaveEngineStatus passed with no problems detected.\n";    
  }

  if (stat == 0) return 0;
  if (stat > 0) return -(stat|1);
  return stat|1;
}	

