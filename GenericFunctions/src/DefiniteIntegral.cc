// -*- C++ -*-
// $Id: DefiniteIntegral.cc,v 1.4.4.1 2003/11/21 16:48:14 garren Exp $

#include <cmath>

#include "CLHEP/GenericFunctions/DefiniteIntegral.hh"
#include "CLHEP/GenericFunctions/AbsFunction.hh"
namespace Genfun {

const int DefiniteIntegral::_K =5;
const int DefiniteIntegral::_KP=_K+1;
DefiniteIntegral::DefiniteIntegral(double a, double b):
_a(a), _b(b)
{}

DefiniteIntegral::~DefiniteIntegral() {
}



#define FANCY
double DefiniteIntegral::operator [] (const AbsFunction & function) const {

  const int MAXITERATIONS=40;    // Maximum number of iterations
  const double EPS=1.0E-6;       // Precision
#ifdef FANCY

  double s[MAXITERATIONS+2],h[MAXITERATIONS+2];
  h[1]=1.0;
  for (int j=1;j<=MAXITERATIONS;j++) {
    s[j]=_trapzd(function, _a, _b, j);
    if (j>=_K) {
      double ss, dss;
      _polint(h+j-_K,s+j-_K,0.0,ss, dss);
      if (fabs(dss) <= EPS*fabs(ss)) return ss;
    }
    s[j+1]=s[j];
    h[j+1]=0.25*h[j];
  }
#else
  double olds = -1E-30;
  for (int j=1;j<MAXITERATIONS;j++) {
    double s = _trapzd(function, _a,_b,j);
    if (fabs(s-olds)<=EPS*fabs(olds)) return s;
    olds=s;
  }
#endif
  std::cerr
    << "DefiniteIntegral:  too many steps.  No convergence"
    << std::endl;
  return 0.0;                   // Never get here.
}

double DefiniteIntegral::_trapzd(const AbsFunction & function, double a, double b, int n) const {
  int it, j;
  if (n==1) {
    _sTrap = 0.5*(b-a)*(function(a)+function(b));
  }
  else { 
    for (it=1,j=1;j<n-1;j++)  it <<=1;
    double tnm=it;
    double del = (b-a)/tnm;
    double x=a+0.5*del;
    double sum;
    for (sum=0.0,j=1;j<=it;j++,x+=del) sum +=function(x);
    _sTrap = 0.5*(_sTrap+(b-a)*sum/tnm);
  }
  return _sTrap;
}


void DefiniteIntegral::_polint(double *xArray, double *yArray, double x, double & y, double & deltay) const {

  double dif = fabs(x-xArray[1]),dift;
  double c[_KP],d[_KP];
  int ns=1;
  for (int i=1;i<=_K;i++) {
    dift=fabs(x-xArray[i]);
    if (dift<dif) {
      ns=i;
      dif=dift;
    }
    c[i]=d[i]=yArray[i];
  }
  y = yArray[ns--];
  for (int m=1;m<_K;m++) {
    for (int i=1;i<=_K-m;i++) {
      double ho = xArray[i]-x;
      double hp=  xArray[i+m]-x;
      double w=c[i+1]-d[i];
      double den=ho-hp;
      if (den==0)
	std::cerr
	  << "Error in polynomial extrapolation"
	  << std::endl;
      den=w/den;
      d[i]=hp*den;
      c[i]=ho*den;
    }
    deltay = 2*ns < (_K-m) ? c[ns+1]: d[ns--];
    y += deltay;
  }
}
} // namespace Genfun
