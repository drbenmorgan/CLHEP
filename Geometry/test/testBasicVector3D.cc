// -*- C++ -*-
// $Id: testBasicVector3D.cc,v 1.5 2010/06/16 16:21:27 garren Exp $
// ---------------------------------------------------------------------------

#include <iostream>
#include <assert.h>
#include "CLHEP/Geometry/Point3D.h"
#include "CLHEP/Geometry/Vector3D.h"
#include "CLHEP/Geometry/Normal3D.h"
#include "CLHEP/Geometry/Transform3D.h"
#include "CLHEP/Units/PhysicalConstants.h"

bool EQUAL(double a, double b) {
  double del = a - b;
  if (del < 0) del = -del;
  return del < 0.000001;
}

using namespace HepGeom;

#define CHECK(point,type)                                         \
  /* Check default constructor */                                 \
  point p00;                                                      \
  assert(p00.x() == 0 && p00.y() == 0 && p00.z() == 0);           \
                                                                  \
  /* Check constructor from three numbers */                      \
  point p01(1,2,3);                                               \
  point p02(4.,5.,6.);                                            \
  assert(p01.x() == 1 && p01.y() == 2 && p01.z() == 3);           \
  assert(p02.x() == 4 && p02.y() == 5 && p02.z() == 6);           \
                                                                  \
  /* Check constructor from array */                              \
  float farray[] = {1,2,3};                                       \
  type  darray[] = {4,5,6};                                       \
  point p03(farray);                 assert(p03 == point(1,2,3)); \
  point p04(darray);                 assert(p04 == point(4,5,6)); \
                                                                  \
  /* Check conversion to array */                                 \
  const point p05(1,2,3);                                         \
  const type * a = p05;                                           \
  assert(a[0] == 1 && a[1] == 2 && a[2] == 3);                    \
  point p06(4,5,6);                                               \
  a = p06;                                                        \
  assert(a[0] == 4 && a[1] == 5 && a[2] == 6);                    \
  type * b = p06;                                                 \
  b[0] = 7;                                                       \
  b[1] = 8;                                                       \
  b[2] = 9;                          assert(p06 == point(7,8,9)); \
                                                                  \
  /* Check copy constructor */                                    \
  point p10(p01);                    assert(p10 == point(1,2,3)); \
  point p11(Point3D <float>(1,2,3)); assert(p11 == point(1,2,3)); \
  point p12(Vector3D<float>(4,5,6)); assert(p12 == point(4,5,6)); \
  point p13(Normal3D<float>(7,8,9)); assert(p13 == point(7,8,9)); \
  point p14(Point3D <type> (1,2,3)); assert(p14 == point(1,2,3)); \
  point p15(Vector3D<type> (4,5,6)); assert(p15 == point(4,5,6)); \
  point p16(Normal3D<type> (7,8,9)); assert(p16 == point(7,8,9)); \
                                                                  \
  /* Check assignment */                                          \
  point p20;                                                      \
  p20 = Point3D <float>(1,2,3);      assert(p20 == point(1,2,3)); \
  p20 = Vector3D<float>(4,5,6);      assert(p20 == point(4,5,6)); \
  p20 = Normal3D<float>(7,8,9);      assert(p20 == point(7,8,9)); \
  p20 = Point3D <type> (1,2,3);      assert(p20 == point(1,2,3)); \
  p20 = Vector3D<type> (4,5,6);      assert(p20 == point(4,5,6)); \
  p20 = Normal3D<type> (7,8,9);      assert(p20 == point(7,8,9)); \
                                                                  \
  /* Check arithmetic operations */                               \
  point p21(1,2,3);                                               \
  p21 += point(1,2,3);               assert(p21 == point(2,4,6)); \
  p21 += Point3D <float>(1,1,1);     assert(p21 == point(3,5,7)); \
  p21 += Vector3D<float>(1,1,1);     assert(p21 == point(4,6,8)); \
  p21 += Normal3D<float>(1,1,1);     assert(p21 == point(5,7,9)); \
  p21 -= point(1,2,3);               assert(p21 == point(4,5,6)); \
  p21 -= Point3D <type>(1,1,1);      assert(p21 == point(3,4,5)); \
  p21 -= Vector3D<type>(1,1,1);      assert(p21 == point(2,3,4)); \
  p21 -= Normal3D<type>(1,1,1);      assert(p21 == point(1,2,3)); \
  p21 *= 2;                          assert(p21 == point(2,4,6)); \
  p21 /= 2;                          assert(p21 == point(1,2,3)); \
  p21 *= 2.0f;                       assert(p21 == point(2,4,6)); \
  p21 /= 2.0f;                       assert(p21 == point(1,2,3)); \
  p21 *= 2.0;                        assert(p21 == point(2,4,6)); \
  p21 /= 2.0;                        assert(p21 == point(1,2,3)); \
                                                                  \
  /* Check subscripting */                                        \
  point p22(1,2,3);                                               \
  assert(p22(0) == 1 && p22(1) == 2 && p22(2) == 3);              \
  assert(p22[0] == 1 && p22[1] == 2 && p22[2] == 3);              \
  p22(0) = 4;                                                     \
  p22(1) = 5;                                                     \
  p22(2) = 6;                        assert(p22 == point(4,5,6)); \
  p22[0] = 7;                                                     \
  p22[1] = 8;                                                     \
  p22[2] = 9;                        assert(p22 == point(7,8,9)); \
                                                                  \
  /* Check carthesian coordinate system */                        \
  point p30;                                                      \
  p30.setX(1);                                                    \
  p30.setY(2);                                                    \
  p30.setZ(3);                       assert(p30 == point(1,2,3)); \
  p30.set(4,5,6);                                                 \
  assert(p30.x() == 4 && p30.y() == 5 && p30.z() == 6);           \
                                                                  \
  /* Check cylindrical coordinate system */                       \
  point p40(12,16,1);                assert(p40.perp2() == 400);  \
                                     assert(p40.perp()  ==  20);  \
                                     assert(p40.rho()   ==  20);  \
  p40.setPerp(5);                    assert(p40 == point(3,4,1)); \
  p40.set(0,0,1);                                                 \
  p40.setPerp(5);                    assert(p40 == point(0,0,1)); \
                                                                  \
  /* Check spherical coordinate system */                         \
  point p50(2,3,6);     assert(p50.mag2()     == 49);             \
                        assert(p50.mag()      ==  7);             \
                        assert(p50.r()        ==  7);             \
                        assert(p50.getR()     ==  7);             \
  point p51(0,0,1);     assert(p51.phi()      ==  0);             \
  point p52(2,4,5);     assert(EQUAL(p52.phi()     ,atan2(2.,1.))); \
                        assert(EQUAL(p52.getPhi()  ,atan2(2.,1.))); \
  point p53(0,0,0);     assert(p53.theta()    ==  0);             \
                        assert(p53.cosTheta() ==  1);             \
  point p54(3,4,10);    assert(EQUAL(p54.theta()   ,atan2(1.,2.))); \
                        assert(EQUAL(p54.getTheta(),atan2(1.,2.))); \
                        assert(EQUAL(p54.cosTheta(),sqrt(0.8)));  \
  point p55(2,3,6);                                               \
  p55.setMag(14);       assert(p55 == point(4,6,12));             \
  p55.setR(7);          assert(p55 == point(2,3,6));              \
  point p56 = p55;                                                \
  p56.setPhi(CLHEP::pi/6);   assert(EQUAL(p56.getPhi(),CLHEP::pi/6));       \
                        assert(EQUAL(p56.mag()   ,p55.mag()));    \
                        assert(EQUAL(p56.theta() ,p55.theta()));  \
  point p57 = p55;                                                \
  p57.setTheta(CLHEP::pi/3); assert(EQUAL(p57.cosTheta(),0.5));        \
                        assert(EQUAL(p57.mag()     ,p55.mag()));  \
                        assert(EQUAL(p57.phi()     ,p55.phi()));  \
                                                                  \
  /* Check pseudo-rapidity */                                     \
  point p60(2,3,6);                                               \
  point p61 = p60;                                                \
  p61.setEta(2);        assert(EQUAL(p61.pseudoRapidity(),2));    \
                        assert(EQUAL(p61.getEta()        ,2));    \
                        assert(EQUAL(p61.eta()           ,2));    \
                        assert(EQUAL(p61.mag()           ,7));    \
                        assert(EQUAL(p61.phi(),p60.phi()));       \
                                                                  \
  /* Check combination of two vectors */                          \
  point p70(1,2,3);     assert(p70.dot(p70)   == p70.mag2());     \
  point p71( 1,2, 3);                                             \
  point p72(-3,2,-1);   assert(p71.cross(p72) == point(-8,-8,8)); \
  point p73(3,4,0);     assert(p73.perp2(point(0,1,0)) == 9);     \
                        assert(p73.perp (point(1,0,0)) == 4);     \
  point p74(1,0,0);                                               \
  point p75(1,1,0);     assert(EQUAL(p74.angle(p75),CLHEP::pi/4));     \
                        assert(EQUAL(p75.angle(p00),CLHEP::pi/2));     \
                                                                  \
  /* Check related vectors */                                     \
  point p80(1,2,3);                                               \
  point p81 = p80.unit();       assert(EQUAL(p81.mag()   ,1));    \
  point p82 = p80.orthogonal(); assert(EQUAL(p82.dot(p81),0));    \
                                                                  \
  /* Check rotations */                                           \
  point p90(2,0.5,sqrt(3.)/2);                                     \
  p90.rotateX(CLHEP::pi/6);          assert(p90.x()    == 2);          \
                                assert(EQUAL(p90.y(),0));         \
                                assert(EQUAL(p90.z(),1));         \
  point p91(sqrt(3.)/2,2,0.5);                                     \
  p91.rotateY(CLHEP::pi/6);          assert(EQUAL(p91.x(),1));         \
                                assert(p91.y()    == 2);          \
                                assert(EQUAL(p91.z(),0));         \
  point p92(0.5,sqrt(3.)/2,2);                                     \
  p92.rotateZ(CLHEP::pi/6);          assert(EQUAL(p92.x(),0));         \
                                assert(EQUAL(p92.y(),1));         \
                                assert(p92.z()    == 2);          \
  point p93(1,1,sqrt(2.));                                         \
  p93.rotate(CLHEP::pi,Vector3D<float>(-1,-1,sqrt(2.)));                \
                                assert(EQUAL(p93.x(),-1));        \
                                assert(EQUAL(p93.y(),-1));        \
                                assert(EQUAL(p93.z(),-sqrt(2.)));  \
                                                                  \
  /* Check transformations */                                     \
  point p100(1,1,sqrt(2.));                                        \
  Transform3D m;                                                  \
  m = Rotate3D(CLHEP::pi,Vector3D<float>(-1,-1,sqrt(2.)));              \
  p100.transform(m);            assert(EQUAL(p100.x(),-1));       \
                                assert(EQUAL(p100.y(),-1));       \
                                assert(EQUAL(p100.z(),-sqrt(2.))); \
                                                                  \
  /* Check input/output */                                        \
  point p110;                                                     \
  std::cin  >> p110;                                              \
  std::cout << p110 << std::endl;                                 \
                                                                  \
  /* Check non-member arithmetics */                              \
  point p120(-1,-2,-3);                                           \
  p120 = +p120;                 assert(p120 == point(-1,-2,-3));  \
  p120 = -p120;                 assert(p120 == point(1,2,3));     \
  point p121(1,2,3);                                              \
  p121 = p121 + Point3D <float>(1,1,1); assert(p121 == point(2,3,4));\
  p121 = p121 + Vector3D<float>(1,1,1); assert(p121 == point(3,4,5));\
  p121 = p121 + Normal3D<float>(1,1,1); assert(p121 == point(4,5,6));\
  p121 = p121 - Point3D <type> (1,1,1); assert(p121 == point(3,4,5));\
  p121 = p121 - Vector3D<type> (1,1,1); assert(p121 == point(2,3,4));\
  p121 = p121 - Normal3D<type> (1,1,1); assert(p121 == point(1,2,3));\
  p121 = p121 * 2;              assert(p121 == point(2,4,6));     \
  p121 = p121 / 2;              assert(p121 == point(1,2,3));     \
  p121 = p121 * 2.0f;           assert(p121 == point(2,4,6));     \
  p121 = p121 / 2.0f;           assert(p121 == point(1,2,3));     \
  p121 = p121 * 2.0;            assert(p121 == point(2,4,6));     \
  p121 = p121 / 2.0;            assert(p121 == point(1,2,3));     \
  p121 = 2    * p121;           assert(p121 == point(2,4,6));     \
  p121 = 0.5f * p121;           assert(p121 == point(1,2,3));     \
  p121 = 2.0  * p121;           assert(p121 == point(2,4,6));     \
  assert(p121 *  p121 == p121.mag2());                            \
  assert(p121 *  Point3D <float>(1,1,1) == 12);                   \
  assert(p121 *  Vector3D<float>(1,1,1) == 12);                   \
  assert(p121 *  Normal3D<float>(1,1,1) == 12);                   \
  assert(p121 == Point3D <float>(2,4,6));                         \
  assert(p121 == Vector3D<float>(2,4,6));                         \
  assert(p121 == Normal3D<float>(2,4,6));                         \
  assert(p121 != Point3D <type> (3,4,6));                         \
  assert(p121 != Vector3D<type> (2,5,6));                         \
  assert(p121 != Normal3D<type> (2,4,7));                         \

void CheckPointFloat()   { CHECK(Point3D<float>  , float)  }
void CheckVectorFloat()  { CHECK(Vector3D<float> , float)  }
void CheckNormalFloat()  { CHECK(Normal3D<float> , float)  }
void CheckPointDouble()  { CHECK(Point3D<double> , double) }
void CheckVectorDouble() { CHECK(Vector3D<double>, double) }
void CheckNormalDouble() { CHECK(Normal3D<double>, double) }

int main()
{
  CheckPointFloat();
  CheckVectorFloat();
  CheckNormalFloat();
  CheckPointDouble();
  CheckVectorDouble();
  CheckNormalDouble();
  return 0;
}
