#include "CLHEP/GenericFunctions/ClebschGordanCoefficientSet.hh"
#include <iostream>
#include <cmath>
#include <stdexcept>
inline double factorial (int N) {
  double retVal(1.0);
  for (int i=2;i<=N;i++) retVal*=i;
  return retVal;
}


namespace Genfun {                                 
  double ClebschGordanCoefficientSet::calcCoefficient(int l1, int l2, int L, int xm1, int xm2, int M)  {

    if (xm1+xm2!=M) return 0;
    double F1=sqrt((2*L+1)*factorial(L+l1-l2)*factorial(L-l1+l2)*factorial(l1+l2-L)/factorial(l1+l2+L+1));
    double F2=sqrt(factorial(L+M)*factorial(L-M)*factorial(l1-xm1)*factorial(l1+xm1)*factorial(l2-xm2)
		   *factorial(l2+xm2));
    double F3=0.0;
    int max=0;
    max = std::max(max,l2+xm2);
    max = std::max(max,l1-xm1);
    max = std::max(max,l1+l2-L);
    //    max = std::max(max,l2-L-xm1);
    //  max = std::max(max,l1+xm2-L);
    for (int k=0;k<=max;k++) {
      double term = factorial(k);
      bool skipTerm=false;
      {
	int T=l1 + l2 -L -k;
	if (T>=0) term *= factorial(T); else skipTerm=true;
      }
      if (!skipTerm)
	{
	  int T=l1-xm1-k;
	  if (T>=0) term *= factorial(T); else skipTerm=true;
	}
      if (!skipTerm)
	{
	  int T=l2+xm2-k;
	  if (T>=0) term *= factorial(T); else skipTerm=true;
	}
      if (!skipTerm)
	{
	  int T=L-l2+xm1+k;
	  if (T>=0) term *= factorial(T); else skipTerm=true;
	}
      if (!skipTerm)
	{
	  int T=L-l1-xm2+k;
	  if (T>=0) term *= factorial(T); else skipTerm=true;
	}
      if (!skipTerm) F3+= ((k%2) ? -1:1)/term;
    }


    return F1*F2*F3;
  }
}
