#include "CLHEP/config/defs.h"
#ifdef ENABLE_BACKWARDS_COMPATIBILITY
// -*- C++ -*-
// CLASSDOC OFF
// $Id: sstream.h,v 1.1.2.1 2004/06/30 15:22:26 garren Exp $
// ---------------------------------------------------------------------------
// CLASSDOC ON
//
// This file is a part of the CLHEP - a Class Library for High Energy Physics.
//
// Note that gcc 2.95.2 will not be supported after CLHEP 1.9,
// making this header moot
//

#ifndef HEP_SSTREAM_H
#define HEP_SSTREAM_H

#include "CLHEP/config/defs.h"
#if HAVE_SSTREAM
#include <sstream>
#else
#include "CLHEP/HepPDT/StringStream.h"
#endif

#endif /* HEP_SSTREAM_H */

#endif	// ENABLE_BACKWARDS_COMPATIBILITY
