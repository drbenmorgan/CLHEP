#ifndef STDHEP_RANDOMSTATE_HH
#define STDHEP_RANDOMSTATE_HH
// ----------------------------------------------------------------------
// RandomState.hh
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
class RandomState {

public:

  // ---  birth/death:
  //
  RandomState(  );
  RandomState( const RandomState & orig );
  RandomState& operator=( const RandomState & );
  ~RandomState();

  // ---  accessors:
  //
  std::ostream&               getStateAsStream( std::ostream& )  const;
  std::vector<unsigned long>  getStateAsLongs(  )  const;
  std::string                 getStateAsString()  const { return myRandomState; }

  void print( std::ostream & os = std::cout ) const;

  // ---  mutators:
  //
  void  putState( std::istream& );
  void  putState( std::string const & );
  void  putState( std::vector<unsigned long> const & );
  void  appendSeed( unsigned long sd );
  void  appendSeed( double sd );
  void  clear(  );

private:

  std::string myRandomState;
  
};	// RandomState

}

#endif // STDHEP_RANDOMSTATE_HH
