// -*- C++ -*-
// $Id: PuncturedSmearedExp.cc,v 1.4 2010/06/16 18:22:01 garren Exp $
#include "CLHEP/GenericFunctions/PuncturedSmearedExp.hh"
#include <sstream>
#include <cmath>
namespace Genfun {
FUNCTION_OBJECT_IMP(PuncturedSmearedExp)

PuncturedSmearedExp::PuncturedSmearedExp() :
  _lifetime ("Lifetime",  1.0, 0.0),  // Bounded from below by zero, by default
  _sigma    ("Sigma",     1.0, 0.0)   // Bounded from below by zero, by default
{
}

PuncturedSmearedExp::PuncturedSmearedExp(const PuncturedSmearedExp & right):
  AbsFunction(right),
  _lifetime  (right._lifetime),
  _sigma     (right._sigma),
  _punctures (right._punctures)
{
}

void PuncturedSmearedExp::puncture(double xmin, double xmax) {
  std::ostringstream mn, mx;
  mn << "Min_" << _punctures.size()/2;
  mx << "Max_" << _punctures.size()/2;
  _punctures.push_back(Parameter(mn.str(), xmin, 0.0, 10.0));
  _punctures.push_back(Parameter(mx.str(), xmax, 0.0, 10.0));
}


Parameter & PuncturedSmearedExp::min(unsigned int i) {
  return _punctures[2*i];
}

const Parameter & PuncturedSmearedExp::min(unsigned int i) const {
  return _punctures[2*i];
}


Parameter & PuncturedSmearedExp::max(unsigned int i) {
  return _punctures[2*i+1];

}

const Parameter & PuncturedSmearedExp::max(unsigned int i) const {
  return _punctures[2*i+1];
}
 

PuncturedSmearedExp::~PuncturedSmearedExp() {
}

Parameter & PuncturedSmearedExp::lifetime() {
  return _lifetime;
}

const Parameter & PuncturedSmearedExp::lifetime() const {
  return _lifetime;
}

Parameter & PuncturedSmearedExp::sigma() {
  return _sigma;
}

const Parameter & PuncturedSmearedExp::sigma() const {
  return _sigma;
}


double PuncturedSmearedExp::operator() (double argument) const {
  // Fetch the paramters.  This operator does not convolve numerically.
  static const double sqrtTwo = sqrt(2.0);

  double xsigma  = _sigma.getValue();
  double tau    = _lifetime.getValue();
  double x      =  argument;

  // Copy:
  std::vector<double> punctures(_punctures.size());
  for (size_t i=0;i<_punctures.size();i++) punctures[i]=_punctures[i].getValue();
  
  // Overlap elimination:
  bool overlap=true;

  while (overlap) {

    overlap=false;

    for (size_t i=0;i<punctures.size()/2;i++) {
      std::sort(punctures.begin()+2*i, punctures.begin()+2*i+2);
      double min1=punctures[2*i];
      double max1=punctures[2*i+1];
      for (size_t j=i+1;j<punctures.size()/2;j++) {
	std::sort(punctures.begin()+2*j, punctures.begin()+2*j+2);
	double min2=punctures[2*j];
	double max2=punctures[2*j+1];
	if ((min2>min1 && max1>min2) || (min1>min2 && max2<min1)) {
	  punctures[2*i]  =std::min(min1,min2);
	  punctures[2*i+1]=std::max(max1,max2);
	  std::vector<double>::iterator t0=punctures.begin()+2*j, t1=t0+2;
	  punctures.erase(t0,t1);
	  overlap=true;
	  break;
	}
      }
      if (overlap) break;
    }
  } 

  double expG=0,norm=0;
  for (size_t i=0;i<punctures.size()/2;i++) {
    
    double a = punctures[2*i];
    double b = punctures[2*i+1];

    double alpha = (a/xsigma + xsigma/tau)/sqrtTwo;
    double beta  = (b/xsigma + xsigma/tau)/sqrtTwo;
    double delta = 1/sqrtTwo/xsigma;

       
    norm += 2*tau*exp(1/(4*delta*delta*tau*tau))*(exp(-alpha/(delta*tau)) - exp(-beta/(delta*tau)));

    expG += ((erfc(alpha-delta*x) - erfc(beta-delta*x))*exp(-x/tau) );

    
  }

  // protection:
  if (norm==0) return norm;

  return expG/norm;
}

double PuncturedSmearedExp::erfc(double x) const {
  // This is accurate to 7 places.
  // See Numerical Recipes P 221
  double t, z, ans;
  z = (x < 0) ? -x : x;
  t = 1.0/(1.0+.5*z);
  ans = t*exp(-z*z-1.26551223+t*(1.00002368+t*(0.37409196+t*(0.09678418+
	t*(-0.18628806+t*(0.27886807+t*(-1.13520398+t*(1.48851587+
	t*(-0.82215223+t*0.17087277 ))) ))) )));
  if ( x < 0 ) ans = 2.0 - ans;
  return ans;
}

double PuncturedSmearedExp::pow(double x,int n) const {
  double val=1;
  for(int i=0;i<n;i++){
    val=val*x;
  }
  return val;
}

} // namespace Genfun


