#include "CLHEP/GenericFunctions/VoigtProfile.hh"
#include "CLHEP/GenericFunctions/Variable.hh"
#include <cmath>
#include <complex>

#if (defined __STRICT_ANSI__) || (defined _WIN32)
#ifndef M_PI
#define M_PI            3.14159265358979323846
#endif // M_PI
#endif // __STRICT_ANSI__

using namespace std;

inline double Pow(double x,int n) {
  double val=1;
  for(int i=0;i<n;i++){
    val=val*x;
  }
  return val;
}

inline std::complex<double> nwwerf(std::complex<double> z) {
  std::complex<double>  zh,r[38],s,t,v;

  const double z1 = 1;
  const double hf = z1/2;
  const double z10 = 10;
  const double c1 = 74/z10;
  const double c2 = 83/z10;
  const double c3 = z10/32;
  const double c4 = 16/z10;
  const double c = 1.12837916709551257;
  const double p = Pow(2.0*c4,33);

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



namespace Genfun {
FUNCTION_OBJECT_IMP(VoigtProfile)


VoigtProfile::VoigtProfile():
  _mass("mass",    50, 10, 90),
  _width ("width", 5, 0,   100),
  _sigma("sigma",  5, 0,   100)
{}

  VoigtProfile::VoigtProfile(const VoigtProfile & right):
    AbsFunction(),
    _mass(right._mass),
    _width (right._width),
    _sigma(right._sigma)
{
}

VoigtProfile::~VoigtProfile() {
}

double VoigtProfile::operator() (double x) const {
  double M=_mass.getValue();
  double G=_width.getValue()/2.0;
  double s=_sigma.getValue();
  static const double sqrt2=sqrt(2.0);
  static const double sqrt2PI=sqrt(2.0*M_PI);
  static const std::complex<double> I(0,1);
  std::complex<double> z = ((x-M) + I*G)/sqrt2/s;
  
  double f=nwwerf(z).real()/s/sqrt2PI;

  return f;

}

Parameter & VoigtProfile::mass() {
  return _mass;
}


Parameter & VoigtProfile::width() {
  return _width;
}

Parameter & VoigtProfile::sigma() {
  return _sigma;
}


} // namespace Genfun
