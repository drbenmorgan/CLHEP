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

HepMatrix & HepMatrix::operator=(const HepRotation &m1) {
  if(9!=size_) {
    //delete &m;
    size_ = 9;
    m.resize(size_);
  }
  nrow = ncol = 3;
  mIter mm1;
  mm1 = m.begin();
  *mm1++ = m1.xx();
  *mm1++ = m1.xy();
  *mm1++ = m1.xz();
  *mm1++ = m1.yx();
  *mm1++ = m1.yy();
  *mm1++ = m1.yz();
  *mm1++ = m1.zx();
  *mm1++ = m1.zy();
  *mm1   = m1.zz();
  return (*this);
}

}  // namespace CLHEP
