// -*- C++ -*-
// $Id: AnalyticConvolution.cc,v 1.3 2003/09/06 14:04:14 boudreau Exp $
#include "CLHEP/GenericFunctions/AnalyticConvolution.hh"
#include "CLHEP/GenericFunctions/Gaussian.hh"
#include "CLHEP/GenericFunctions/Exponential.hh"
namespace Genfun {
FUNCTION_OBJECT_IMP(AnalyticConvolution)

AnalyticConvolution::AnalyticConvolution(AnalyticConvolution::Type          type) :
  _lifetime ("Lifetime",  1.0, 0.0),  // Bounded from below by zero, by default
  _frequency("Frequency", 0.0, 0.0),  // Bounded from below by zero, by default
  _sigma    ("Sigma",     1.0, 0.0),  // Bounded from below by zero, by default
  _offset   ("Offset",    0.0),       // Offset is unbounded
  _type(type)
{
}

AnalyticConvolution::AnalyticConvolution(const AnalyticConvolution & right):
  _lifetime  (right._lifetime),
  _frequency (right._frequency),
  _sigma     (right._sigma),
  _offset    (right._offset),
  _type(right._type)
{
}

AnalyticConvolution::~AnalyticConvolution() {
}

Parameter & AnalyticConvolution::frequency() {
  return _frequency;
}

const Parameter & AnalyticConvolution::frequency() const {
  return _frequency;
}

Parameter & AnalyticConvolution::lifetime() {
  return _lifetime;
}

const Parameter & AnalyticConvolution::lifetime() const {
  return _lifetime;
}

Parameter & AnalyticConvolution::sigma() {
  return _sigma;
}

const Parameter & AnalyticConvolution::sigma() const {
  return _sigma;
}

Parameter & AnalyticConvolution::offset() {
  return _offset;
}

const Parameter & AnalyticConvolution::offset() const {
  return _offset;
}
double AnalyticConvolution::operator() (double argument) const {
  // Fetch the paramters.  This operator does not convolve numerically.
  static const double sqrtTwo = sqrt(2.0);
  double sigma  = _sigma.getValue();
  double tau    = _lifetime.getValue();
  double offset = _offset.getValue();
  double x      =  argument-offset;
  double freq   = _frequency.getValue();
 
  // smeared exponential an its asymmetry.
  double expG=0, asymm=0;  
  
  if (_type==SMEARED_NEG_EXP) {
    expG = exp((sigma*sigma +2*tau*(/*offset*/x))/(2.0*tau*tau)) * 
      erfc((sigma*sigma+tau*(/*offset*/x))/(sqrtTwo*sigma*tau))/(2.0*tau);
    return expG;
  }
  else {
    expG = exp((sigma*sigma +2*tau*(/*offset*/-x))/(2.0*tau*tau)) * 
      erfc((sigma*sigma+tau*(/*offset*/-x))/(sqrtTwo*sigma*tau))/(2.0*tau);
  }
  
  // Both sign distribution=> return smeared exponential:
  if (_type==SMEARED_EXP) {
    return expG;
  }
  
  
  // Calcualtion of asymmetry:

  // First, if the mixing frequency is too high compared with the lifetime, we
  // cannot see this oscillation.  We abandon the complicated approach and just do
  // this instead: 
  if (sigma>6.0*tau) {
    asymm = expG*(1/(1+tau*tau*freq*freq));
  }
  else {
    std::complex<double> z(freq*sigma/sqrtTwo, (sigma/tau-x/sigma)/sqrtTwo);
    if (x<0) {
      if (_type==SMEARED_COS_EXP|| _type==MIXED || _type==UNMIXED ) {
	asymm= 2.0*nwwerf(z).real()/tau/4.0*exp(-x*x/2.0/sigma/sigma);
      }
      else if (_type==SMEARED_SIN_EXP) {
	asymm= 2.0*nwwerf(z).imag()/tau/4.0*exp(-x*x/2.0/sigma/sigma);
      }
    }
    else {
      if (_type==SMEARED_COS_EXP||_type==MIXED || _type==UNMIXED) {
	asymm= -2.0*nwwerf(std::conj(z)).real()/tau/4*exp(-x*x/2.0/sigma/sigma) +
	  exp(sigma*sigma/2 *(1/tau/tau - freq*freq) - x/tau)*(1./tau)*cos(freq*x - freq/tau*sigma*sigma);
      }
      else if (_type==SMEARED_SIN_EXP) {
	asymm= +2.0*nwwerf(std::conj(z)).imag()/tau/4*exp(-x*x/2.0/sigma/sigma) +
	  exp(sigma*sigma/2 *(1/tau/tau - freq*freq) - x/tau)*(1./tau)*sin(freq*x - freq/tau*sigma*sigma);
      }
    } 
  }
  
  // Return either MIXED, UNMIXED, or ASYMMETRY function.
  if (_type==UNMIXED) {
    double retVal = (expG+asymm)/2.0;
    if (retVal<0)
      std::cerr
	<< "Warning in AnalyticConvolution:  negative probablity"
	<< std::endl;
    if (retVal<0)
      std::cerr
	<< sigma << ' ' << tau << ' ' << offset << ' '
	<< freq << ' '<< argument
	<< std::endl;
    if (retVal<0)
      std::cerr << retVal << std::endl;
    return retVal;
  }
  else if (_type==MIXED) {
    double retVal = (expG-asymm)/2.0;
    if (retVal<0)
      std::cerr
	<< "Warning in AnalyticConvolution:  negative probablity"
	<< std::endl;
    if (retVal<0)
      std::cerr
	<< sigma << ' ' << tau << ' ' << offset << ' '
	<< freq << ' ' << argument
	<< std::endl;
    if (retVal<0)
      std::cerr << retVal << std::endl;
    return retVal;
  }
  else if (_type==SMEARED_COS_EXP || _type==SMEARED_SIN_EXP) {
    return asymm;
  }
  else {
    std::cerr
      << "Unknown sign parity.  State is not allowed"
      << std::endl;
    exit(0);
    return 0.0;
  }

}

double AnalyticConvolution::erfc(double x) const {
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

double AnalyticConvolution::pow(double x,int n) const {
  double val=1;
  for(int i=0;i<n;i++){
    val=val*x;
  }
  return val;
}

std::complex<double> AnalyticConvolution::nwwerf(std::complex<double> z) const {
  std::complex<double>  zh,r[38],s,t,v;

  const double z1 = 1;
  const double hf = z1/2;
  const double z10 = 10;
  const double c1 = 74/z10;
  const double c2 = 83/z10;
  const double c3 = z10/32;
  const double c4 = 16/z10;
  const double c = 1.12837916709551257;
  const double p = pow(2.0*c4,33);

  double x=z.real();
  double y=z.imag();
  double xa=(x >= 0) ? x : -x;
  double ya=(y >= 0) ? y : -y;
  if(ya < c1 && xa < c2){
    zh = std::complex<double>(ya+c4,xa);
    r[37]= std::complex<double>(0,0);
    //       do 1 n = 36,1,-1
    for(int n = 36; n>0; n--){   
      t=zh+double(n)*std::conj(r[n+1]);
      r[n]=hf*t/std::norm(t);
    }
    double xl=p;
    s=std::complex<double>(0,0);
    //    do 2 n = 33,1,-1
    for(int k=33; k>0; k--){
      xl=c3*xl;
      s=r[k]*(s+xl);
    }
    v=c*s;
  }
  else{
      zh=std::complex<double>(ya,xa);
      r[1]=std::complex<double>(0,0);
       //       do 3 n = 9,1,-1
       for(int n=9;n>0;n--){
	 t=zh+double(n)*std::conj(r[1]);
	 r[1]=hf*t/std::norm(t);
       }
       v=c*r[1];
  }
  if(ya == 0) v= std::complex<double>(exp(-xa*xa),v.imag());
  if(y < 0) {
    v=2.0*std::exp(std::complex<double>(-xa,-ya)*std::complex<double>(xa,ya))-v;
    if(x > 0) v=std::conj(v);
  }
  else{
    if(x < 0) v=std::conj(v);
  }
  return v;
}
} // namespace Genfun
