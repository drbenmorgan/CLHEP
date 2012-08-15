#ifndef _ClebschGordanCoefficientSet_h_
#define _ClebschGordanCoefficientSet_h_
#include <map>
#include <algorithm>
#include <cmath>
namespace Genfun {

  class ClebschGordanCoefficientSet {

  public:

    double operator () (unsigned int l1, unsigned int l2, int m1, int m2, int L, int M) const; 
    
  private:

    // Key used to optimize access (look up previously calcuated results).
    class Key {

    public:
      
      inline Key(unsigned int xl1, unsigned int xl2, int xm1, int xm2, unsigned int xL):
	l1(xl1),l2(xl2),m1(xm1),m2(xm2),L(xL) {}
      
      inline bool operator < (const Key & o) const {
	if ( l1!=o.l1) return l1<o.l1;
	if ( l2!=o.l2) return l2<o.l2;
	if ( m1!=o.m1) return m1<o.m1;
	if ( m2!=o.m2) return m2<o.m2;
	if ( L!=o.L  ) return L<o.L;
	return false;
      }
      
      
      inline bool operator== (const Key & o) const {
	return l1==o.l1 && l2 == o.l2 && m1==o.m1 && m2==o.m2 && L == o.L;
      }

    private:
      
      unsigned int l1;
      unsigned     l2;
      int          m1;
      int          m2;
      unsigned int L;
      // M=m1+m2;
      
    };
    

    mutable std::map<Key, double> coeff;

    static double calcCoefficient(int l1, int l2, int L, int m1, int m2, int M);

  };




  inline double ClebschGordanCoefficientSet::operator () (unsigned int l1, unsigned int l2, int m1, int m2, int L, int M) const {
    if ((m1+m2)!=M) return 0;
    
    Key key(l1,l2,m1,m2,L);
    std::map<Key,double>::iterator i=coeff.find(key),end=coeff.end();
    if (i==end) {
      double c = calcCoefficient(l1, l2, L, m1, m2,M);
      coeff[key]=c;
      return c;
    }

    return (*i).second;
   
  }
}

#endif
