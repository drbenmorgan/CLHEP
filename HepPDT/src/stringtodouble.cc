// ----------------------------------------------------------------------
//
// stringtodouble.cc
// Author: Lynn Garren
//
// ----------------------------------------------------------------------

#include "CLHEP/HepPDT/defs.h"
#if HAVE_SSTREAM
#include <sstream>
#else
#include "CLHEP/HepPDT/StringStream.h"
#endif
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
