#ifndef STDRANDOM_HH
#define STDRANDOM_HH
// ----------------------------------------------------------------------
// StdRandom.hh
//
// Container for the random state
// ----------------------------------------------------------------------

#include <vector>
#include <string>
#include <iostream>

namespace StdHep  {

/**
 * @author
 * @ingroup stdhep
 */
class StdRandom {

public:

  // ---  birth/death:
  //
  StdRandom(  );
  StdRandom( const StdRandom & orig );
  StdRandom& operator=( const StdRandom & );
  ~StdRandom();

  // ---  accessors:
  //
  std::ostream&               getStateAsStream( std::ostream& )  const;
  std::vector<unsigned long>  getStateAsLongs(  )  const;
  std::string                 getStateAsString()  const { return myRandomState; }

  void print( std::ostream & os = std::cout ) const;

  // ---  mutators:
  //
  void  putState( std::istream& );
  void  putState( std::string& );
  void  putState( std::vector<unsigned long> );
  void  appendSeed( unsigned long sd );
  void  appendSeed( double sd );
  void  clear(  );

private:

  std::string myRandomState;
  
};	// StdRandom

}

#endif // STDRANDOM_HH
