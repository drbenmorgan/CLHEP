// ----------------------------------------------------------------------
// StdRandom.cc
// ----------------------------------------------------------------------

#include <vector>
#include <string>
#include <sstream>

#include "CLHEP/StdHep/StdRandom.hh"
#include "CLHEP/HepMC/DoubleConversion.hh"

namespace StdHep  {
StdRandom::StdRandom(  )
: myRandomState( "" )
{ ; }


StdRandom::StdRandom( const StdRandom & orig )
: myRandomState( orig.myRandomState )
{ ; }


StdRandom& StdRandom::operator=( const StdRandom & rhs )
{ if( this != & rhs )
  {
    myRandomState = rhs.myRandomState;
  }
  return *this;
}

StdRandom:: ~StdRandom()
{ ; }

std::ostream& StdRandom::getStateAsStream( std::ostream & os )  const
{
    os << myRandomState << std::endl;
    return os;
}


std::vector<unsigned long> StdRandom::getStateAsLongs(  )  const
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


void StdRandom::print( std::ostream & os ) const
{
    os << "begin StdRandom state"  << std::endl;
    os << myRandomState << std::endl;
    os << "end StdRandom state" << std::endl;
}

void  StdRandom::putState( std::istream& ist )
{
   std::ostringstream st;
   std::string str;
   while(ist) {
       ist >> str;
       st << str;
   }
   myRandomState = st.str();
}

void  StdRandom::putState( std::string const & st )
{
   myRandomState = st;
}

void  StdRandom::putState( std::vector<unsigned long> const & rs )
{
   std::ostringstream st;
   for( unsigned int i=0; i<rs.size(); ++i ) {
       st << " " << rs[i];
   }
   myRandomState = st.str();
}

void  StdRandom::appendSeed( unsigned long sd )
{
   std::ostringstream st(myRandomState);
   st << " " << sd;
   myRandomState = st.str();
}

void  StdRandom::appendSeed( double sd )
{
   std::ostringstream st(myRandomState);
   std::vector<unsigned long> two;
   two = HepMC::DoubleConversion::dto2longs(sd);
   if (two.size() > 1 ) {
       st << " " << two[0] << " " << two[1];
   }
   myRandomState = st.str();
}

void  StdRandom::clear(  )
{
    myRandomState = "";
}

}	// StdHep
