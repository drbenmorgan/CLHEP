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


#include "CLHEP/Cast/defs.h"
#if HAVE_SSTREAM
#include <sstream>
#else
#include "CLHEP/Cast/StringStream.h"
#endif
#include "CLHEP/Cast/itos.h"


std::string  itos( long i )  {

  std::ostringstream s;
  s << i;

  return s.str();

} // itos()
