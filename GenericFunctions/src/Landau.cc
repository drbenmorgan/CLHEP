// -*- C++ -*-
// $Id: Landau.cc,v 1.4 2003/10/10 17:40:39 garren Exp $
// ---------------------------------------------------------------------------
 
#include "CLHEP/GenericFunctions/Landau.hh"
#include "CLHEP/GenericFunctions/Variable.hh"
#include <cmath>
#include <assert.h>

using namespace std;

namespace Genfun {
FUNCTION_OBJECT_IMP(Landau)

Landau::Landau():
  _peak("Peak", 5.0 ,0, 10),
  _width("Width",1.0,0, 10)
{}

Landau::~Landau() {
}

Landau::Landau(const Landau & right):
_peak(right._peak),
_width(right._width)
{
}

double Landau::operator() (double x) const {
  double s   = _width.getValue();
  double x0  = _peak.getValue();
  double xs  = x0 + 0.222782*s;
  return _denlan((x-xs)/s)/s;
}

Parameter & Landau::peak() {
  return _peak;
}

Parameter & Landau::width() {
  return _width;
}

const Parameter & Landau::peak() const {
  return _peak;
}

const Parameter & Landau::width() const {
  return _width;
}

double Landau::_denlan(double x) const {
    /* Initialized data */

    static float p1[5] = { (float).4259894875,(float)-.124976255,(float)
            .039842437,(float)-.006298287635,(float).001511162253 };
    static float q5[5] = { (float)1.,(float)156.9424537,(float)3745.310488,(
            float)9834.698876,(float)66924.28357 };
    static float p6[5] = { (float)1.000827619,(float)664.9143136,(float)
            62972.92665,(float)475554.6998,(float)-5743609.109 };
    static float q6[5] = { (float)1.,(float)651.4101098,(float)56974.73333,(
            float)165917.4725,(float)-2815759.939 };
    static float a1[3] = { (float).04166666667,(float)-.01996527778,(float)
            .02709538966 };
    static float a2[2] = { (float)-1.84556867,(float)-4.284640743 };
    static float q1[5] = { (float)1.,(float)-.3388260629,(float).09594393323,(
            float)-.01608042283,(float).003778942063 };
    static float p2[5] = { (float).1788541609,(float).1173957403,(float)
            .01488850518,(float)-.001394989411,(float)1.283617211e-4 };
    static float q2[5] = { (float)1.,(float).7428795082,(float).3153932961,(
            float).06694219548,(float).008790609714 };
    static float p3[5] = { (float).1788544503,(float).09359161662,(float)
            .006325387654,(float)6.611667319e-5,(float)-2.031049101e-6 };
    static float q3[5] = { (float)1.,(float).6097809921,(float).2560616665,(
            float).04746722384,(float).006957301675 };
    static float p4[5] = { (float).9874054407,(float)118.6723273,(float)
            849.279436,(float)-743.7792444,(float)427.0262186 };
    static float q4[5] = { (float)1.,(float)106.8615961,(float)337.6496214,(
            float)2016.712389,(float)1597.063511 };
    static float p5[5] = { (float)1.003675074,(float)167.5702434,(float)
            4789.711289,(float)21217.86767,(float)-22324.9491 };

    /* System generated locals */
    float ret_val, r__1;

    /* Local variables */
    static float u, v;
    v = x;
    if (v < (float)-5.5) {
        u = exp(v + (float)1.);
        ret_val = exp(-1 / u) / sqrt(u) * (float).3989422803 * ((a1[0] + (a1[
                1] + a1[2] * u) * u) * u + 1);
    } else if (v < (float)-1.) {
        u = exp(-v - 1);
        ret_val = exp(-u) * sqrt(u) * (p1[0] + (p1[1] + (p1[2] + (p1[3] + p1[
                4] * v) * v) * v) * v) / (q1[0] + (q1[1] + (q1[2] + (q1[3] + 
                q1[4] * v) * v) * v) * v);
    } else if (v < (float)1.) {
        ret_val = (p2[0] + (p2[1] + (p2[2] + (p2[3] + p2[4] * v) * v) * v) * 
                v) / (q2[0] + (q2[1] + (q2[2] + (q2[3] + q2[4] * v) * v) * v) 
                * v);
    } else if (v < (float)5.) {
        ret_val = (p3[0] + (p3[1] + (p3[2] + (p3[3] + p3[4] * v) * v) * v) * 
                v) / (q3[0] + (q3[1] + (q3[2] + (q3[3] + q3[4] * v) * v) * v) 
                * v);
    } else if (v < (float)12.) {
        u = 1 / v;
/* Computing 2nd power */
        r__1 = u;
        ret_val = r__1 * r__1 * (p4[0] + (p4[1] + (p4[2] + (p4[3] + p4[4] * u)
                 * u) * u) * u) / (q4[0] + (q4[1] + (q4[2] + (q4[3] + q4[4] * 
                u) * u) * u) * u);
    } else if (v < (float)50.) {
        u = 1 / v;
/* Computing 2nd power */
        r__1 = u;
        ret_val = r__1 * r__1 * (p5[0] + (p5[1] + (p5[2] + (p5[3] + p5[4] * u)
                 * u) * u) * u) / (q5[0] + (q5[1] + (q5[2] + (q5[3] + q5[4] * 
                u) * u) * u) * u);
    } else if (v < (float)300.) {
        u = 1 / v;
/* Computing 2nd power */
        r__1 = u;
        ret_val = r__1 * r__1 * (p6[0] + (p6[1] + (p6[2] + (p6[3] + p6[4] * u)
                 * u) * u) * u) / (q6[0] + (q6[1] + (q6[2] + (q6[3] + q6[4] * 
                u) * u) * u) * u);
    } else {
        u = 1 / (v - v * log(v) / (v + 1));
/* Computing 2nd power */
        r__1 = u;
        ret_val = r__1 * r__1 * ((a2[0] + a2[1] * u) * u + 1);
    }
    return ret_val;

}

} // namespace Genfun
