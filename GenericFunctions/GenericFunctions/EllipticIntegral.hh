// -*- C++ -*-
// $Id: 
//---------------------EllipticIntegral---------------------------------------//
//                                                                            //
//                                                                            //
// Joe Boudreau, September 2001                                               //
//                                                                            //
//--------------------------------------------------------------------------  //
#ifndef EllipticIntegral_h
#define EllipticIntegral_h 1
#include "CLHEP/GenericFunctions/AbsFunction.hh"
#include "CLHEP/GenericFunctions/Parameter.hh"

namespace Genfun {
namespace EllipticIntegral {

  class FirstKind : public AbsFunction  {

    FUNCTION_OBJECT_DEF(FirstKind)

      public:

    // Constructor:  
    FirstKind ();

    // Copy constructor
    FirstKind(const FirstKind &right);
  
    // Destructor
    virtual ~FirstKind();
  
    // Retreive function value
    virtual double operator ()(double argument) const;
    virtual double operator ()(const Argument & a) const {return operator() (a[0]);}
  
    // Get the k-parameter.  Default value = 1.0.
    Parameter & k(); 
    const Parameter & k() const; 

  private:

    // It is illegal to assign an adjustable constant
    const FirstKind & operator=(const FirstKind &right);

    Parameter _k;    // the k parameter
  
  };

  class SecondKind : public AbsFunction  {

    FUNCTION_OBJECT_DEF(SecondKind)

      public:

    // Constructor:  
    SecondKind ();

    // Copy constructor
    SecondKind(const SecondKind &right);
  
    // Destructor
    virtual ~SecondKind();
  
    // Retreive function value
    virtual double operator ()(double argument) const;
    virtual double operator ()(const Argument & a) const {return operator() (a[0]);}
  
    // Get the k-parameter.  Default value = 1.0.
    Parameter & k(); 
    const Parameter & k() const; 

  private:

    // It is illegal to assign an adjustable constant
    const SecondKind & operator=(const SecondKind &right);

    Parameter _k;    // the k parameter
  
  };

  class ThirdKind : public AbsFunction  {

    FUNCTION_OBJECT_DEF(ThirdKind)

      public:

    // Constructor:  
    ThirdKind ();

    // Copy constructor
    ThirdKind(const ThirdKind &right);
  
    // Destructor
    virtual ~ThirdKind();
  
    // Retreive function value
    virtual double operator ()(double argument) const;
    virtual double operator ()(const Argument & a) const {return operator() (a[0]);}
  
    // Get the k-parameter.  Default value = 1.0.
    Parameter & k(); 
    const Parameter & k() const; 

    // Get the n-parameter.  Default value = 1.0.
    Parameter & n(); 
    const Parameter & n() const; 

  private:

    // It is illegal to assign an adjustable constant
    const ThirdKind & operator=(const ThirdKind &right);

    Parameter _k;    // the k parameter
    Parameter _n;    // the n parameter
  
  };

} // end namespace EllipticIntegral 
} // end namespace Genfun

#include "CLHEP/GenericFunctions/EllipticIntegral.icc"
#endif
