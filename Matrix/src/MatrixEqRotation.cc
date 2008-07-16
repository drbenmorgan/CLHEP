// -*- C++ -*-
// ---------------------------------------------------------------------------
//
// This file is a part of the CLHEP - a Class Library for High Energy Physics.
// 
// 
// Copyright Cornell University 1993, 1996, All Rights Reserved.
// 
// This software written by Nobu Katayama and Mike Smyth, Cornell University.
// 
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions
// are met:
// 1. Redistributions of source code must retain the above copyright
//    notice and author attribution, this list of conditions and the
//    following disclaimer. 
// 2. Redistributions in binary form must reproduce the above copyright
//    notice and author attribution, this list of conditions and the
//    following disclaimer in the documentation and/or other materials
//    provided with the distribution.
// 3. Neither the name of the University nor the names of its contributors
//    may be used to endorse or promote products derived from this software
//    without specific prior written permission.
// 
// Creation of derivative forms of this software for commercial
// utilization may be subject to restriction; written permission may be
// obtained from Cornell University.
// 
// CORNELL MAKES NO REPRESENTATIONS OR WARRANTIES, EXPRESS OR IMPLIED.  By way
// of example, but not limitation, CORNELL MAKES NO REPRESENTATIONS OR
// WARRANTIES OF MERCANTABILITY OR FITNESS FOR ANY PARTICULAR PURPOSE OR THAT
// THE USE OF THIS SOFTWARE OR DOCUMENTATION WILL NOT INFRINGE ANY PATENTS,
// COPYRIGHTS, TRADEMARKS, OR OTHER RIGHTS.  Cornell University shall not be
// held liable for any liability with respect to any claim by the user or any
// other party arising from use of the program.
//

#ifdef GNUPRAGMA
#pragma implementation
#endif

#include "CLHEP/Matrix/defs.h"
#include "CLHEP/Matrix/Matrix.h"
#include "CLHEP/Vector/Rotation.h"

namespace CLHEP {

HepMatrix & HepMatrix::operator=(const HepRotation &m2) {
  if(9!=size) {
    //delete &m;
    size = 9;
    m.resize(size);
  }
  nrow = ncol = 3;
  mIter mm;
  mm = m.begin();
  *mm++ = m2.xx();
  *mm++ = m2.xy();
  *mm++ = m2.xz();
  *mm++ = m2.yx();
  *mm++ = m2.yy();
  *mm++ = m2.yz();
  *mm++ = m2.zx();
  *mm++ = m2.zy();
  *mm   = m2.zz();
  return (*this);
}

}  // namespace CLHEP
