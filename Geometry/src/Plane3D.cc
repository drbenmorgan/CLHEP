// -*- C++ -*-
// $Id: Plane3D.cc,v 1.1.1.1 2003/07/15 20:15:05 garren Exp $
// ---------------------------------------------------------------------------
//
// This file is a part of the CLHEP - a Class Library for High Energy Physics.
//
// Hep geometrical 3D Plane class
//
// Author: Evgeni Chernyaev <Evgueni.Tcherniaev@cern.ch>
//
// History:
// 22.09.96 E.Chernyaev - initial version
// 19.10.96 J.Allison - added == and <<.

#include "CLHEP/Geometry/Plane3D.h"

std::ostream& operator << (std::ostream& os, const HepPlane3D& p) {
  return os
    << '(' << p.a() << ',' << p.b() << ',' << p.c() << ',' << p.d() << ')';
}
