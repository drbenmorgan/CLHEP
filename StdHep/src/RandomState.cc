// ----------------------------------------------------------------------
// RandomState.cc
// Author: Lynn Garren
// ----------------------------------------------------------------------

#include <vector>
#include <string>
#include <sstream>

#include "CLHEP/StdHep/RandomState.hh"
#include "CLHEP/HepMC/DoubleConversion.hh"

namespace StdHep  {
RandomState::RandomState(  )
: myRandomState( "" )
{ ; }


RandomState::RandomState( const RandomState & orig )
: myRandomState( orig.myRandomState )
{ ; }


RandomState& RandomState::operator=( const RandomState & rhs )
{ if( this != & rhs )
  {
    myRandomState = rhs.myRandomState;
  }
  return *this;
}

RandomState:: ~RandomState()
{ ; }

std::ostream& RandomState::getStateAsStream( std::ostream & os )  const
{
    os << myRandomState << std::endl;
    return os;
}


std::vector<unsigned long> RandomState::getStateAsLongs(  )  const
{
    // we assume here that this makes sense
    // this method assumes that the state consists solely of a list of longs
    std::vector<unsigned long> result;
    std::istringstream st(myRandomState);
    int i;
    while(st) {
       st >> i;
       result.push_back(i);
    }
    return result;
}


void RandomState::print( std::ostream & os ) const
{
    os << "begin RandomState state"  << std::endl;
    os << myRandomState << std::endl;
    os << "end RandomState state" << std::endl;
}

void  RandomState::putState( std::istream& ist )
{
   std::ostringstream st;
   std::string str;
   while(ist) {
       ist >> str;
       st << str;
   }
   myRandomState = st.str();
}

void  RandomState::putState( std::string const & st )
{
   myRandomState = st;
}

void  RandomState::putState( std::vector<unsigned long> const & rs )
{
   std::ostringstream st;
   for( unsigned int i=0; i<rs.size(); ++i ) {
       st << " " << rs[i];
   }
   myRandomState = st.str();
}

void  RandomState::appendSeed( unsigned long sd )
{
   std::ostringstream st(myRandomState);
   st << " " << sd;
   myRandomState = st.str();
}

void  RandomState::appendSeed( double sd )
{
   std::ostringstream st(myRandomState);
   unsigned long i1, i2;
   HepMC::DoubleConversion::dto2longs(sd,i1,i2);
   st << " " << i1 << " " << i2;
   myRandomState = st.str();
}

void  RandomState::clear(  )
{
    myRandomState = "";
}

}	// StdHep
