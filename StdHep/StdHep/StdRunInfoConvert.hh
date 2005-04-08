// ----------------------------------------------------------------------
//
// StdRunInfoConvert.hh
// L. Garren
//
//  defines various free functions:
//           build StdEvent from HEPEVT, and vice-versa
//
// ----------------------------------------------------------------------
#ifndef STDRUNINFOCONVERT_HH
#define STDRUNINFOCONVERT_HH

#include "CLHEP/StdHep/StdRunInfo.hh"

namespace StdHep {

/**
 * @author
 * @ingroup StdHep
 */

StdRunInfo * getRunInfoFromSTDCM( int i );
bool         RunInfoToSTDCM( StdRunInfo * run );

} // StdHep

#include "CLHEP/StdHep/StdRunInfoConvert.icc"

#endif // STDRUNINFOCONVERT_HH
