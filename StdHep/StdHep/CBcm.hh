// $Id: CBcm.hh,v 1.1.1.1 2003/07/15 20:15:05 garren Exp $
// ----------------------------------------------------------------------
// CBcm.hh
// ----------------------------------------------------------------------
// Author:  Lynn Garren, Marc Paterno,
// 
// This is the Fortran interface to the stdcm1 common block
// Do not attempt to use stdcm1_ directly.
//
// ----------------------------------------------------------------------
#ifndef CBCM_HH
#define CBCM_HH

#include "CLHEP/StdHep/include/stdcm1.h"

namespace StdHep  {

/**
 * @author
 * @ingroup StdHep
 */
class CBcm {

public:

  CBcm() : cptr1( & stdcm1_ ), cptr2( & stdcm2_ ) { ; }

  stdcm1_t * stdcm1() { return cptr1; }
  stdcm2_t * stdcm2() { return cptr2; }

private:

  stdcm1_t * cptr1;
  stdcm2_t * cptr2;

};	// CBcm

}	// StdHep

#endif // CBCM_HH
