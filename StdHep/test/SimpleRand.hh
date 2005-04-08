#ifndef SIMPLE_RAND_HH
#define SIMPLE_RAND_HH
//////////////////////////////////////////////////////////////////////////
// SimpleRand.hh
// Author: Lynn Garren
//
// Since it is unfair to introduce a dependency on CLHEP Random for the sake
// of the test, we use a simple, non-robust, interface to random() 
//////////////////////////////////////////////////////////////////////////

#include <iostream>

class SimpleRand {

public:

  SimpleRand();
  SimpleRand(long seed);
  ~SimpleRand();
  // Constructors and destructor

  double flat();
  // It returns a pseudo random number between 0 and 1,
  // according to the standard stdlib random function rand()
  // but excluding the end points.
  //
  // WARNING:  rand() is quite a weak generator on most systems,                    <
  // will not pass several randomness tests, and does not give a           <
  // reproducible sequence of numbers.                                                                        <

  void setSeed(long seed);
  // Sets the state of the algorithm according to seed.

  std::ostream & put (std::ostream & os) const;
  void saveStatus( std::ostream & os ) const;

  std::istream & get (std::istream & is);
  void restoreStatus( std::istream & is );

  void showStatus() const;
  // Dumps the engine status on the screen.
 
  operator unsigned int(); // 32-bit flat value, quickest of all.

private:

  unsigned int SimpleRandBuilder();

private:

  long theSeed;
  long seq;

};

#endif	// SIMPLE_RAND_HH
