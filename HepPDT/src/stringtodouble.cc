// ----------------------------------------------------------------------
//
// stringtodouble.cc
// Author: Lynn Garren
//
// ----------------------------------------------------------------------

#include <sstream>

#include "CLHEP/HepPDT/defs.h"
#include "CLHEP/HepPDT/stringtodouble.hh"

namespace HepPDT {

double stringtodouble( std::string & numb )
{
    double dn;
    int sl = numb.length();
    std::istringstream snum( numb.substr(0,sl).c_str() );
    snum >> dn;
    return dn;
}

}  // namespace HepPDT
