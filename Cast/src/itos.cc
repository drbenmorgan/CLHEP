// ----------------------------------------------------------------------
//
// itos - convert (long) integer to string
//
// History:
//   19-Dec-1997  WEB  Initial draft
//   05-Dec-1998  WEB  Added "using" statement
//   14-Feb-2000  WEB  Improve C++ Standard compliance
//
// ----------------------------------------------------------------------

#include <sstream>

#include "CLHEP/Cast/defs.h"
#include "CLHEP/Cast/itos.h"


std::string  itos( long i )  {

  std::ostringstream s;
  s << i;

  return s.str();

} // itos()
