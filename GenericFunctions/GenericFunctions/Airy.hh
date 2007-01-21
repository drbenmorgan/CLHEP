// -*- C++ -*-
// $Id: 
// Airy Functions Ai and Bi
#ifndef Airy_h
#define Airy_h 1
#include "CLHEP/GenericFunctions/AbsFunction.hh"
namespace Genfun {

  /**
   * @author
   * @ingroup genfun
   */
  class Airy : public AbsFunction  {

    FUNCTION_OBJECT_DEF(Airy)

      public:

    enum Type {Ai, Bi};

    // Constructor:  Use this one and you will get a Airy function Ai or Bi
    Airy (Type type);

    // Copy constructor
    Airy(const Airy &right);
  
    // Destructor
    virtual ~Airy();
  
    // Retreive function value
    virtual double operator ()(double argument) const;
    virtual double operator ()(const Argument & a) const {return operator() (a[0]);}
  
  private:

    // It is illegal to assign an adjustable constant
    const Airy & operator=(const Airy &right);

    // The type and order of the Airy function
    Type      _type;
  
  };

} // namespace Genfun


#include "CLHEP/GenericFunctions/Airy.icc"
#endif
