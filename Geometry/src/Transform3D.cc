// -*- C++ -*-
// $Id: Transform3D.cc,v 1.1.1.1 2003/07/15 20:15:05 garren Exp $
// ---------------------------------------------------------------------------
//
// This file is a part of the CLHEP - a Class Library for High Energy Physics.
//
// Hep geometrical 3D Transformation library
//
// Author: Evgeni Chernyaev <Evgueni.Tcherniaev@cern.ch>
//
// History:
// 24.09.96 E.Chernyaev - initial version

#include <iostream>
#include "CLHEP/Geometry/Transform3D.h"

const HepTransform3D HepTransform3D::Identity = HepTransform3D ();

//   T R A N S F O R M A T I O N 

double HepTransform3D::operator () (int i, int j) const {
  if (i == 0) {
    if (j == 0) { return xx; }
    if (j == 1) { return xy; }
    if (j == 2) { return xz; } 
    if (j == 3) { return dx; } 
  } else if (i == 1) {
    if (j == 0) { return yx; }
    if (j == 1) { return yy; }
    if (j == 2) { return yz; } 
    if (j == 3) { return dy; } 
  } else if (i == 2) {
    if (j == 0) { return zx; }
    if (j == 1) { return zy; }
    if (j == 2) { return zz; } 
    if (j == 3) { return dz; } 
  } else if (i == 3) {
    if (j == 0) { return 0.0; }
    if (j == 1) { return 0.0; }
    if (j == 2) { return 0.0; } 
    if (j == 3) { return 1.0; } 
  } 
  std::cerr << "HepTransform3D subscripting: bad indeces "
	       << "(" << i << "," << j << ")" << std::endl;
  return 0.0;
}

HepTransform3D::HepTransform3D(
const HepPoint3D &fr0, const HepPoint3D &fr1, const HepPoint3D &fr2,
const HepPoint3D &to0, const HepPoint3D &to1, const HepPoint3D &to2)
/***********************************************************************
 *                                                                     *
 * Name: HepTransform3D::HepTransform3D              Date:    24.09.96 *
 * Author: E.Chernyaev (IHEP/Protvino)               Revised:          *
 *                                                                     *
 * Function: Create 3D Transformation from one coordinate system       *
 *           defined by its origin "fr0" and two axes "fr0->fr1",      *
 *           "fr0->fr2" to another coordinate system "to0", "to0->to1" *
 *           and "to0->to2"                                            *
 *                                                                     *
 ***********************************************************************/
{
  HepVector3D    x1,y1,z1, x2,y2,z2;
  double      cos1, cos2;

  x1 = (fr1 - fr0).unit();
  y1 = (fr2 - fr0).unit();
  x2 = (to1 - to0).unit();
  y2 = (to2 - to0).unit();

  //   C H E C K   A N G L E S

  cos1 = x1*y1;
  cos2 = x2*y2;

  if (abs(1.0-cos1) <= 0.000001 || abs(1.0-cos2) <= 0.000001) {
    std::cerr << "HepTransform3D: zero angle between axes" << std::endl;
    setIdentity();
  }else{
    if (abs(cos1-cos2) > 0.000001) {
      std::cerr << "HepTransform3D: angles between axes are not equal"
		<< std::endl;
    }

    //   F I N D   R O T A T I O N   M A T R I X
    
    z1 = (x1.cross(y1)).unit();
    y1  = z1.cross(x1);
    
    z2 = (x2.cross(y2)).unit();
    y2  = z2.cross(x2);

    double detxx =  (y1.y()*z1.z() - z1.y()*y1.z());
    double detxy = -(y1.x()*z1.z() - z1.x()*y1.z());
    double detxz =  (y1.x()*z1.y() - z1.x()*y1.y());
    double detyx = -(x1.y()*z1.z() - z1.y()*x1.z());
    double detyy =  (x1.x()*z1.z() - z1.x()*x1.z());
    double detyz = -(x1.x()*z1.y() - z1.x()*x1.y());
    double detzx =  (x1.y()*y1.z() - y1.y()*x1.z());
    double detzy = -(x1.x()*y1.z() - y1.x()*x1.z());
    double detzz =  (x1.x()*y1.y() - y1.x()*x1.y());
 
    double txx = x2.x()*detxx + y2.x()*detyx + z2.x()*detzx; 
    double txy = x2.x()*detxy + y2.x()*detyy + z2.x()*detzy; 
    double txz = x2.x()*detxz + y2.x()*detyz + z2.x()*detzz; 
    double tyx = x2.y()*detxx + y2.y()*detyx + z2.y()*detzx; 
    double tyy = x2.y()*detxy + y2.y()*detyy + z2.y()*detzy; 
    double tyz = x2.y()*detxz + y2.y()*detyz + z2.y()*detzz; 
    double tzx = x2.z()*detxx + y2.z()*detyx + z2.z()*detzx; 
    double tzy = x2.z()*detxy + y2.z()*detyy + z2.z()*detzy; 
    double tzz = x2.z()*detxz + y2.z()*detyz + z2.z()*detzz; 

    //   S E T    T R A N S F O R M A T I O N 

    double dx1 = fr0.x(), dy1 = fr0.y(), dz1 = fr0.z();
    double dx2 = to0.x(), dy2 = to0.y(), dz2 = to0.z();

    setTransform(txx, txy, txz, dx2-txx*dx1-txy*dy1-txz*dz1,
		 tyx, tyy, tyz, dy2-tyx*dx1-tyy*dy1-tyz*dz1,
		 tzx, tzy, tzz, dz2-tzx*dx1-tzy*dy1-tzz*dz1);
  }
}

HepTransform3D HepTransform3D::inverse() const
/***********************************************************************
 *                                                                     *
 * Name: HepTransform3D::inverse                     Date:    24.09.96 *
 * Author: E.Chernyaev (IHEP/Protvino)               Revised:          *
 *                                                                     *
 * Function: Find inverse affine transformation                        *
 *                                                                     *
 ***********************************************************************/
{
  double detxx = yy*zz-yz*zy, detxy = yx*zz-yz*zx, detxz = yx*zy-yy*zx;
  double det   = xx*detxx - xy*detxy + xz*detxz;
  if (det == 0) {
    std::cerr << "HepTransform3D::inverse error: zero determinant"
	      << std::endl;
    return HepTransform3D();
  }
  det = 1./det; detxx *= det; detxy *= det; detxz *= det;
  double detyx = (xy*zz-xz*zy)*det;
  double detyy = (xx*zz-xz*zx)*det;
  double detyz = (xx*zy-xy*zx)*det;
  double detzx = (xy*yz-xz*yy)*det;
  double detzy = (xx*yz-xz*yx)*det;
  double detzz = (xx*yy-xy*yx)*det;
  return HepTransform3D
    (detxx, -detyx,  detzx, -detxx*dx+detyx*dy-detzx*dz,
    -detxy,  detyy, -detzy,  detxy*dx-detyy*dy+detzy*dz,
     detxz, -detyz,  detzz, -detxz*dx+detyz*dy-detzz*dz);
}

void
HepTransform3D::getDecomposition(HepScale3D & scale,
				 HepRotate3D & rotation,
				 HepTranslate3D & translation) const
/***********************************************************************
 *                                                            CLHEP-1.7*
 * Name: HepTransform3D::getDecomposition            Date:    09.06.01 *
 * Author: E.Chernyaev (IHEP/Protvino)               Revised:          *
 *                                                                     *
 * Function: Gets decomposition of general transformation on           *
 *           three consequentive specific transformations:             *
 *           Scale, then Rotation, then Translation.                   *
 *           If there was a reflection, then ScaleZ will be negative.  *
 *                                                                     *
 ***********************************************************************/
{
  double sx = sqrt(xx*xx + yx*yx + zx*zx);
  double sy = sqrt(xy*xy + yy*yy + zy*zy);
  double sz = sqrt(xz*xz + yz*yz + zz*zz);

  if (xx*(yy*zz-yz*zy) - xy*(yx*zz-yz*zx) + xz*(yx*zy-yy*zx) < 0) sz = -sz;
  scale.setTransform(sx,0,0,0,  0,sy,0,0, 0,0,sz,0);
  rotation.setTransform(xx/sx,xy/sy,xz/sz,0,
			yx/sx,yy/sy,yz/sz,0,
			zx/sx,zy/sy,zz/sz,0); 
  translation.setTransform(1,0,0,dx, 0,1,0,dy, 0,0,1,dz);
}

bool
HepTransform3D::isNear(const HepTransform3D & t, double tolerance) const
{
  return ( (abs(xx - t.xx) <= tolerance) && 
           (abs(xy - t.xy) <= tolerance) &&
           (abs(xz - t.xz) <= tolerance) &&
           (abs(dx - t.dx) <= tolerance) &&
           (abs(yx - t.yx) <= tolerance) &&
           (abs(yy - t.yy) <= tolerance) &&
           (abs(yz - t.yz) <= tolerance) &&
           (abs(dy - t.dy) <= tolerance) &&
           (abs(zx - t.zx) <= tolerance) &&
           (abs(zy - t.zy) <= tolerance) &&
           (abs(zz - t.zz) <= tolerance) &&
           (abs(dz - t.dz) <= tolerance) );
}

bool
HepTransform3D::operator==(const HepTransform3D & t) const
{
  return (this == &t) ? true :
    (xx==t.xx && xy==t.xy && xz==t.xz && dx==t.dx && 
     yx==t.yx && yy==t.yy && yz==t.yz && dy==t.dy &&
     zx==t.zx && zy==t.zy && zz==t.zz && dz==t.dz );
}

//   3 D   R O T A T I O N

HepRotate3D::HepRotate3D(double a, const HepPoint3D &p1, const HepPoint3D &p2)
/***********************************************************************
 *                                                                     *
 * Name: HepRotate3D::Rotate3D                       Date:    24.09.96 *
 * Author: E.Chernyaev (IHEP/Protvino)               Revised:          *
 *                                                                     *
 * Function: Create 3D Rotation through angle "a" (counterclockwise)   *
 *           around the axis p1->p2                                    *
 *                                                                     *
 ***********************************************************************/
  : HepTransform3D()
{
  if (a == 0) return;

  double cx = p2.x()-p1.x(), cy = p2.y()-p1.y(), cz = p2.z()-p1.z();
  double ll = sqrt(cx*cx + cy*cy + cz*cz); 
  if (ll == 0) {
    std::cerr << "HepRotate3D: zero axis" << std::endl;
  }else{
    double cosa = cos(a), sina = sin(a);
    cx /= ll; cy /= ll; cz /= ll;   
    
    double txx = cosa + (1-cosa)*cx*cx;
    double txy =        (1-cosa)*cx*cy - sina*cz;
    double txz =        (1-cosa)*cx*cz + sina*cy;
    
    double tyx =        (1-cosa)*cy*cx + sina*cz;
    double tyy = cosa + (1-cosa)*cy*cy; 
    double tyz =        (1-cosa)*cy*cz - sina*cx;
    
    double tzx =        (1-cosa)*cz*cx - sina*cy;
    double tzy =        (1-cosa)*cz*cy + sina*cx;
    double tzz = cosa + (1-cosa)*cz*cz;
    
    double tdx = p1.x(), tdy = p1.y(), tdz = p1.z(); 
    
    setTransform(txx, txy, txz, tdx-txx*tdx-txy*tdy-txz*tdz,
		 tyx, tyy, tyz, tdy-tyx*tdx-tyy*tdy-tyz*tdz,
		 tzx, tzy, tzz, tdz-tzx*tdx-tzy*tdy-tzz*tdz);
  }
}

//   3 D   R E F L E C T I O N 

HepReflect3D::HepReflect3D(double a, double b, double c, double d)
/***********************************************************************
 *                                                                     *
 * Name: HepReflect3D::HepReflect3D                  Date:    24.09.96 *
 * Author: E.Chernyaev (IHEP/Protvino)               Revised:          *
 *                                                                     *
 * Function: Create 3D Reflection in a plane a*x + b*y + c*z + d = 0   *
 *                                                                     *
 ***********************************************************************/
{
  double ll = a*a+b*b+c*c;
  if (ll == 0) {
    std::cerr << "HepReflect3D: zero normal" << std::endl;
    setIdentity();
  }else{
    ll = 1/ll;
    double aa = a*a*ll, ab = a*b*ll, ac = a*c*ll, ad = a*d*ll,
              bb = b*b*ll, bc = b*c*ll, bd = b*d*ll,
              cc = c*c*ll, cd = c*d*ll;
    setTransform(-aa+bb+cc, -ab-ab,    -ac-ac,    -ad-ad,
		 -ab-ab,     aa-bb+cc, -bc-bc,    -bd-bd,
		 -ac-ac,    -bc-bc,     aa+bb-cc, -cd-cd);
  }
}
