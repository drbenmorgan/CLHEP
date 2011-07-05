// -*- C++ -*-
// ---------------------------------------------------------------------------
//
// This file is a part of the CLHEP - a Class Library for High Energy Physics.
//

#ifdef GNUPRAGMA
#pragma implementation
#endif

#include "CLHEP/Matrix/defs.h"
#include "CLHEP/Matrix/Matrix.h"
#include "CLHEP/Vector/Rotation.h"

namespace CLHEP {

HepMatrix & HepMatrix::operator=(const HepRotation &m2) {
  if(9!=size_) {
    //delete &m;
    size_ = 9;
    m.resize(size_);
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
