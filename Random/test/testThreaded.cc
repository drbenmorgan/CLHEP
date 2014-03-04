#include "CLHEP/Random/DualRand.h"
#include "CLHEP/Random/Hurd160Engine.h"
#include "CLHEP/Random/Hurd288Engine.h"
#include "CLHEP/Random/JamesRandom.h"
#include "CLHEP/Random/MTwistEngine.h"
#include "CLHEP/Random/RandEngine.h"
#include "CLHEP/Random/RanecuEngine.h"
#include "CLHEP/Random/Ranlux64Engine.h"
#include "CLHEP/Random/RanluxEngine.h"
#include "CLHEP/Random/RanshiEngine.h"
#include "CLHEP/Random/TripleRand.h"

#include "CLHEP/Random/RandBinomial.h"
#include "CLHEP/Random/RandChiSquare.h"
#include "CLHEP/Random/RandGauss.h"
#include "CLHEP/Random/RandGamma.h"
#include "CLHEP/Random/RandGaussZiggurat.h"
#include "CLHEP/Random/RandExpZiggurat.h"
#include "CLHEP/Utility/atomic_int.h"
#include <cmath>
#include <iostream>
#include <vector>

// Some logic to only run the test if the compiler supports
// threading
#if __cplusplus >= 201103L

  #if __GNUC__ > 4 || (__GNUC__ == 4 && __GNUC_MINOR__ > 7)
    #define CLHEP_RUN_THREADED_TESTS 1
    #include <thread>
  #elif __clang__
    #if __has_feature(cxx_thread_local) && __has_feature(c_atomic)
      #define CLHEP_RUN_THREADED_TESTS 1
      #include <thread>
    #else
      #define CLHEP_RUN_THREADED_TESTS 0
    #endif
  #else
    #define CLHEP_RUN_THREADED_TESTS 0
  #endif

#else
  #define CLHEP_RUN_THREADED_TESTS 0
#endif

void testRandGauss(std::vector<double> const& reference, bool& result) {

  // Check that the fire and two shoot methods all give the same
  // random number sequence. The output of the fire method is passed
  // in. fire does not use thread local variables, but instead
  // nonstatic class data members for the caching. shoot should
  // be using thread local variables for the caching. Random
  // numbers are generated in pairs and on a subsequent call
  // the second number is used. Note it is important that an
  // odd number of random numbers are generated for this test,
  // because that causes there to be a number in the cache from
  // the first thread when the second thread executes. It proves
  // that the second thread is using a different cache when it
  // does not use that cached value.

  long seedL = 100;
  CLHEP::HepJamesRandom engine(seedL);
  CLHEP::RandGauss dist(engine);

  result = true;

  // Just a sanity check first. The fire method reproduces
  // itself.
  if (reference[0] != dist.fire() ||
      reference[1] != dist.fire() ||
      reference[2] != dist.fire() ||
      reference[3] != dist.fire() ||
      reference[4] != dist.fire()) {
    result = false;
  }

  // check the shoot method where we pass in an engine
  CLHEP::HepJamesRandom engine1(seedL);
  if (reference[0] != CLHEP::RandGauss::shoot(&engine1) ||
      reference[1] != CLHEP::RandGauss::shoot(&engine1) ||
      reference[2] != CLHEP::RandGauss::shoot(&engine1) ||
      reference[3] != CLHEP::RandGauss::shoot(&engine1) ||
      reference[4] != CLHEP::RandGauss::shoot(&engine1)) {
    result = false;
  }

  // check the shoot method using the CLHEP thread local
  // engine
  CLHEP::HepJamesRandom engine2(seedL);
  CLHEP::HepRandom::setTheEngine(&engine2);
  // setFlag causes it to not use the cached value
  // and generate a new pair of random numbers
  CLHEP::RandGauss::setFlag(false);
  if (reference[0] != CLHEP::RandGauss::shoot() ||
      reference[1] != CLHEP::RandGauss::shoot() ||
      reference[2] != CLHEP::RandGauss::shoot() ||
      reference[3] != CLHEP::RandGauss::shoot() ||
      reference[4] != CLHEP::RandGauss::shoot()) {
    result = false;
  }
}

int main() {

  std::ofstream output("testThreaded.cout");

#if CLHEP_RUN_THREADED_TESTS == 0
  output << "Not running testThreaded.cc tests because compiler does not support needed features.\n";
  return 0;
#else
  output << "Running testThreaded.cc tests.\n";

  long seedL = 100;
  CLHEP::HepJamesRandom engine(seedL);
  CLHEP::RandGauss dist(engine);
  std::vector<double> generatedNumbers;

  generatedNumbers.push_back(dist.fire());
  generatedNumbers.push_back(dist.fire());
  generatedNumbers.push_back(dist.fire());
  generatedNumbers.push_back(dist.fire());
  generatedNumbers.push_back(dist.fire());

  bool result1 = true;
  // First test that the fire and shoot methods give consistent results
  std::thread t1(testRandGauss, std::cref(generatedNumbers), std::ref(result1));
  t1.join();
  if(!result1) {
    output << "testRandGauss failed on thread 1. fire and 2 shoot functions do not give the same results.\n";
    return 1;
  }

  bool result2 = true;
  // RandGauss generates numbers in pairs and caches the second, using the
  // second on a subsequent call instead of generating another.  The following
  // will fail if the cache is not thread local because the first random
  // number generated will be the cached one from the previous thread instead
  // of a new one.
  std::thread t2(testRandGauss, std::cref(generatedNumbers), std::ref(result2));
  t2.join();
  if(!result2) {
    output << "testRandGauss failed on thread 2. This might mean the cache in RandGauss is not really thread local.\n";
    output << "Maybe a problem in the macro logic in CLHEP/Utility/thread_local.h.\n";
    return 1;
  }

  output << "Verified that CLHEP_THREAD_LOCAL types are really thread local\n";

  CLHEP_ATOMIC_INT_TYPE numberOfEngines(0);
  if(numberOfEngines.load() == 0) {
    output << "If this is printing, it means CLHEP_ATOMIC_INT_TYPE really has type atomic<int>\n";
  }

  // The default seed values for the engines are not supposed
  // to change nor are the initial random numbers from a sequence.
  // I empirically determined the values before the threading code
  // changes and test that they are still the same.
  double epsilon = 0.0001;
  {
    CLHEP::DualRand engine1;
    CLHEP::DualRand engine2;
    CLHEP::DualRand engine3;
    if(std::fabs(engine1.flat() - 0.412678) > epsilon ||
       std::fabs(engine2.flat() - 0.112937) > epsilon ||
       std::fabs(engine3.flat() - 0.998563) > epsilon) {
      output << "Error, default seeds changed for DualRand random engine.\n";
      return 1;
    }
  }
  {
    CLHEP::Hurd160Engine engine1;
    CLHEP::Hurd160Engine engine2;
    CLHEP::Hurd160Engine engine3;
    if(std::fabs(engine1.flat() - 0.104097) > epsilon ||
       std::fabs(engine2.flat() - 0.392414) > epsilon ||
       std::fabs(engine3.flat() - 0.7008) > epsilon) {
      output << "Error, default seeds changed for Hurd160Engine random engine.\n";
      return 1;
    }
  }
  {
    CLHEP::Hurd288Engine engine1;
    CLHEP::Hurd288Engine engine2;
    CLHEP::Hurd288Engine engine3;
    if(std::fabs(engine1.flat() - 0.942396) > epsilon ||
       std::fabs(engine2.flat() - 0.422952) > epsilon ||
       std::fabs(engine3.flat() - 0.528602) > epsilon) {
      output << "Error, default seeds changed for Hurd288Engine random engine.\n";
      return 1;
    }
  }
  {
    // Actually engines 3, 4, and 5 because each thread above created
    // a default HepJamesRandom engine. The default one whose creation
    // was triggered in the CLHEP::HepRandom::setTheEngine call.
    CLHEP::HepJamesRandom engine3;
    CLHEP::HepJamesRandom engine4;
    CLHEP::HepJamesRandom engine5;
    if(std::fabs(engine3.flat() - 0.837788) > epsilon ||
       std::fabs(engine4.flat() - 0.846736) > epsilon ||
       std::fabs(engine5.flat() - 0.608056) > epsilon) {
      output << "Error, default seeds changed for HepJamesRandom random engine.\n";
      return 1;
    }
  }
  {
    CLHEP::MTwistEngine engine1;
    CLHEP::MTwistEngine engine2;
    CLHEP::MTwistEngine engine3;
    if(std::fabs(engine1.flat() - 0.350114) > epsilon ||
       std::fabs(engine2.flat() - 0.575236) > epsilon ||
       std::fabs(engine3.flat() - 0.143409) > epsilon) {
      output << "Error, default seeds changed for MTwistEngine random engine.\n";
      return 1;
    }
  }
  {
    CLHEP::RanecuEngine engine1;
    CLHEP::RanecuEngine engine2;
    CLHEP::RanecuEngine engine3;
    if(std::fabs(engine1.flat() - 0.154707) > epsilon ||
       std::fabs(engine2.flat() - 0.417668) > epsilon ||
       std::fabs(engine3.flat() - 0.350542) > epsilon) {
      output << "Error, default seeds changed for RanecuEngine random engine.\n";
      return 1;
    }
  }
  {
    CLHEP::Ranlux64Engine engine1;
    CLHEP::Ranlux64Engine engine2;
    CLHEP::Ranlux64Engine engine3;
    if(std::fabs(engine1.flat() - 0.214757) > epsilon ||
       std::fabs(engine2.flat() - 0.517081) > epsilon ||
       std::fabs(engine3.flat() - 0.464734) > epsilon) {
      output << "Error, default seeds changed for Ranlux64Engine random engine.\n";
      return 1;
    }
  }
  {
    CLHEP::RanluxEngine engine1;
    CLHEP::RanluxEngine engine2;
    CLHEP::RanluxEngine engine3;
    if(std::fabs(engine1.flat() - 0.117402) > epsilon ||
       std::fabs(engine2.flat() - 0.856504) > epsilon ||
       std::fabs(engine3.flat() - 0.68177) > epsilon) {
      output << "Error, default seeds changed for RanluxEngine random engine.\n";
      return 1;
    }
  }
  {
    CLHEP::RanshiEngine engine1;
    CLHEP::RanshiEngine engine2;
    CLHEP::RanshiEngine engine3;
    if(std::fabs(engine1.flat() - 0.989873) > epsilon ||
       std::fabs(engine2.flat() - 0.548671) > epsilon ||
       std::fabs(engine3.flat() - 0.917996) > epsilon) {
      output << "Error, default seeds changed for RanshiEngine random engine.\n";
      return 1;
    }
  }
  {
    CLHEP::TripleRand engine1;
    CLHEP::TripleRand engine2;
    CLHEP::TripleRand engine3;
    if(std::fabs(engine1.flat() - 0.838579) > epsilon ||
       std::fabs(engine2.flat() - 0.212374) > epsilon ||
       std::fabs(engine3.flat() - 0.84029) > epsilon) {
      output << "Error, default seeds changed for TripleRand random engine.\n";
      return 1;
    }
  }

  // Test to reference values determined by running this code once
  // Results should be reproducible so they should not change.
  {
    long seedL = 100;
    CLHEP::HepJamesRandom engine(seedL);
    if(CLHEP::RandBinomial::shoot(&engine, 50, 0.2) != 12) {
      output << "Error, results changed for RandBinomial.\n";
      return 1;
    }
  }
  {
    long seedL = 100;
    CLHEP::HepJamesRandom engine(seedL);
    if(std::fabs(CLHEP::RandChiSquare::shoot(&engine) - 0.031799) > epsilon) {
      output << "Error, results changed for RandChiSquared.\n";
      return 1;
    }
  }
  {
    long seedL = 100;
    CLHEP::HepJamesRandom engine(seedL);
    if(std::fabs(CLHEP::RandExpZiggurat::shoot(&engine) - 1.59601) > epsilon) {
      output << "Error, results changed for RandExpZiggurat.\n";
      return 1;
    }
  }
  {
    long seedL = 100;
    CLHEP::HepJamesRandom engine(seedL);
    if(std::fabs(CLHEP::RandGamma::shoot(&engine) - 1.25744) > epsilon) {
      output << "Error, results changed for RandGamma.\n";
      return 1;
    }
  }
  {
    long seedL = 100;
    CLHEP::HepJamesRandom engine(seedL);
    if(std::fabs(CLHEP::RandGaussZiggurat::shoot(&engine) - (-0.138855)) > epsilon) {
      output << "Error, results changed for RandGaussZiggurat.\n";
      return 1;
    }
  }
  return 0;
#endif
}
