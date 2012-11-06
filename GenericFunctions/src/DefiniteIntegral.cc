// -*- C++ -*-
// $Id: DefiniteIntegral.cc,v 1.6 2010/06/16 18:22:01 garren Exp $

#include <cmath>
#include <vector>
#include <stdexcept>
#include "CLHEP/GenericFunctions/DefiniteIntegral.hh"
#include "CLHEP/GenericFunctions/AbsFunction.hh"


namespace Genfun {


  class DefiniteIntegral::Clockwork {
    
    //
    // This class has limited visibility its functions, data,
    // and nested classes are all public:
    // 
    
  public:
    
    class QuadratureRule {
      
    public:
      
      // Constructorctor:
      QuadratureRule() {};
      
      // Destructor:
      virtual ~QuadratureRule() {};
      
      // Integrate at the j^th level of refinement:
      virtual double integrate(const AbsFunction & function, 
			       double a,
			       double b,
			       unsigned int j) const=0;
      
      // Return the step multiplier:
      virtual unsigned int stepMultiplier () const=0;

      // Return the number of function calls:
      virtual unsigned int numFunctionCalls() const =0;

    };
    
    class TrapezoidQuadratureRule:public QuadratureRule {
      
    public:
      
      // Constructor:
      TrapezoidQuadratureRule():retVal(0),nFunctionCalls(0) {};
      
      // Destructor:
      ~TrapezoidQuadratureRule() {};
      
      // Integrate at the j^th level of refinement:
      virtual double integrate(const AbsFunction & function, 
			       double a,
			       double b,
			       unsigned int j) const;
      
      // The step is doubled at each level of refinement:
      virtual unsigned int stepMultiplier () const {return 2;}

      // Returns number of function calls:
      virtual unsigned int numFunctionCalls() const {return nFunctionCalls;};
      
    private:

      mutable double retVal;
      mutable unsigned int nFunctionCalls;

    };
    
    class XtMidpointQuadratureRule:public QuadratureRule {
      
    public:
      
      // Constructor:
      XtMidpointQuadratureRule():retVal(0),nFunctionCalls(0) {};
      
      // Destructorctor:
      ~XtMidpointQuadratureRule() {};
      
      // Integrate at the j^th level of refinement:
      virtual double integrate(const AbsFunction & function, 
			       double a,
			       double b,
			       unsigned int j) const;
      
      // The step is tripled at each level of refinement:
      virtual unsigned int stepMultiplier () const {return 3;}

      // Returns number of function calls:
      virtual unsigned int numFunctionCalls() const {return nFunctionCalls;};
      
    private:

      mutable double retVal;
      mutable unsigned int nFunctionCalls;
    };
    
    double                              a;              // lower limit of integration
    double                              b;              // upper limit of integration
    DefiniteIntegral::Type              type;           // open or closed
    mutable unsigned int                nFunctionCalls; // bookkeeping
    unsigned int                        MAXITER;        // Max no of step doubling, tripling, etc.
    double                              EPS;            // Target precision
    unsigned int                        K;              // Minimum order =2*5=10

    // Polynomial interpolation with Neville's method:
    void polint(std::vector<double>::iterator xArray, std::vector<double>::iterator yArray, double x, double & y, double & deltay) const;
    
  };

  
  DefiniteIntegral::DefiniteIntegral(double a, double b, Type type):
    c(new Clockwork()) {
    c->a              = a;
    c->b              = b;
    c->type           = type;
    c->nFunctionCalls = 0;
    c->MAXITER        = type==OPEN ? 20 : 14; 
    c->EPS            = 1.0E-6;
    c->K              = 5;
  }
  
  DefiniteIntegral::~DefiniteIntegral() {
    delete c;
  }

  DefiniteIntegral::DefiniteIntegral(const DefiniteIntegral & right) 
  :AbsFunctional(right), c(new Clockwork(*right.c)) {
  }

  DefiniteIntegral & DefiniteIntegral::operator = (const DefiniteIntegral & right) {
    if (this!=&right) {
      delete c;
      c = new Clockwork(*right.c);
    }
    return *this;
  }
  
  void DefiniteIntegral::setEpsilon(double eps) {
    c->EPS=eps;
  }

  void DefiniteIntegral::setMaxIter(unsigned int maxIter) {
    c->MAXITER=maxIter;
  }

  void DefiniteIntegral::setMinOrder(unsigned int minOrder) {
    c->K=(minOrder+1)/2;
  }

  double DefiniteIntegral::operator [] (const AbsFunction & function) const {

    const Clockwork::QuadratureRule * rule = c->type==OPEN ? 
      (Clockwork::QuadratureRule *) new Clockwork::XtMidpointQuadratureRule() : 
      (Clockwork::QuadratureRule *) new Clockwork::TrapezoidQuadratureRule();
    double xMult=rule->stepMultiplier();

    c->nFunctionCalls=0;
    std::vector<double> s(c->MAXITER+2),h(c->MAXITER+2);
    h[1]=1.0;
    for (unsigned int j=1;j<=c->MAXITER;j++) {
      s[j]=rule->integrate(function, c->a, c->b, j);
      c->nFunctionCalls=rule->numFunctionCalls();
      if (j>=c->K) {
	double ss, dss;
	c->polint(h.begin()+j-c->K,s.begin()+j-c->K,0.0,ss, dss);
	if (fabs(dss) <= c->EPS*fabs(ss)) {
	  delete rule;
	  return ss;
	}
      }
      s[j+1]=s[j];
      h[j+1]=h[j]/xMult/xMult;
    }
    delete rule;
    throw std::runtime_error("DefiniteIntegral:  too many steps.  No convergence");
    return 0.0;                   // Never get here.
  }
  
  void DefiniteIntegral::Clockwork::polint(std::vector<double>::iterator xArray, std::vector<double>::iterator yArray, double x, double & y, double & deltay) const {
    double dif = fabs(x-xArray[1]),dift;
    std::vector<double> c(K+1),d(K+1);
    unsigned int ns=1;
    for (unsigned int i=1;i<=K;i++) {
      dift=fabs(x-xArray[i]);
      if (dift<dif) {
	ns=i;
	dif=dift;
      }
      c[i]=d[i]=yArray[i];
    }
    y = yArray[ns--];
    for (unsigned int m=1;m<K;m++) {
      for (unsigned int i=1;i<=K-m;i++) {
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
      deltay = 2*ns < (K-m) ? c[ns+1]: d[ns--];
      y += deltay;
    }
  }
  
  unsigned int DefiniteIntegral::numFunctionCalls() const {
    return c->nFunctionCalls;
  }

  // Quadrature rules:
  double DefiniteIntegral::Clockwork::TrapezoidQuadratureRule::integrate(const AbsFunction & function, double a, double b, unsigned int n) const {
    unsigned int it, j;
    if (n==1) {
      retVal = 0.5*(b-a)*(function(a)+function(b));
      nFunctionCalls+=2;
    }
    else { 
      for (it=1,j=1;j<n-1;j++)  it <<=1;
      double tnm=it;
      double del = (b-a)/tnm;
      double x=a+0.5*del;
      double sum;
      for (sum=0.0,j=1;j<=it;j++,x+=del) {
	sum +=function(x);
	nFunctionCalls++;
      }
      retVal = 0.5*(retVal+(b-a)*sum/tnm);
    }
    return retVal;
  }

  // Quadrature rules:
  double DefiniteIntegral::Clockwork::XtMidpointQuadratureRule::integrate(const AbsFunction & function, double a, double b, unsigned int n) const {
    unsigned int it, j;
    if (n==1) {
      retVal = (b-a)*(function((a+b)/2.0));
      nFunctionCalls+=1;
    }
    else { 
      for (it=1,j=1;j<n-1;j++)  it *=3;
      double tnm=it;
      double del  = (b-a)/(3.0*tnm);
      double ddel = del+del;
      double x=a+0.5*del;
      double sum=0;
      for (j=1;j<=it;j++) {
	sum +=function(x);
	x+=ddel;
	sum +=function(x);
	x+=del;
	nFunctionCalls+=2;
      }
      retVal = (retVal+(b-a)*sum/tnm)/3.0;
    }
    return retVal;
  }
  
  

} // namespace Genfun
