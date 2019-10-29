// -*- C++ -*-
// $Id: AbsParameter.hh,v 1.2 2003/09/06 14:04:13 boudreau Exp $
#ifndef _AbsParameter_h_
#define _AbsParameter_h_

namespace Genfun {
  class Parameter;
  class ParameterSum;
  class ParameterDifference;
  class ParameterProduct;
  class ParameterQuotient;
  class ParameterNegation;
  class ConstPlusParameter;
  class ConstMinusParameter;
  class ConstTimesParameter;
  class ConstOverParameter;

  /**
   * @author
   * @ingroup genfun
   */
  class AbsParameter {
    
  public:
    
    // Default Constructor
    AbsParameter();
    
    // Copy constructor:
    AbsParameter(const AbsParameter &);

    // Destructor
    virtual ~AbsParameter();
  
    // Parameter value
    virtual double getValue()  const=0;   

    // Every parameter must override this:
    AbsParameter * clone() const;

    // Extra lingual type information:
    virtual Parameter *parameter() {return 0;}
    virtual const Parameter *parameter() const {return 0;}

  private:

    // Cannot assign an AbsParameter:
    AbsParameter & operator= (const AbsParameter &);

    virtual AbsParameter *_clone() const=0;

  };

// Now for some additional operations:


ConstTimesParameter               operator * (double c, const AbsParameter &op2);
ConstPlusParameter                operator + (double c, const AbsParameter &op2);
ConstMinusParameter               operator - (double c, const AbsParameter &op2);
ConstOverParameter                operator / (double c, const AbsParameter &op2);

ConstTimesParameter               operator * (const AbsParameter &op2, double c);
ConstPlusParameter                operator + (const AbsParameter &op2, double c);
ConstPlusParameter                operator - (const AbsParameter &op2, double c);
ConstTimesParameter               operator / (const AbsParameter &op2, double c);


ParameterProduct                  operator * (const AbsParameter &op1, const AbsParameter &op2);
ParameterSum                      operator + (const AbsParameter &op1, const AbsParameter &op2);
ParameterDifference               operator - (const AbsParameter &op1, const AbsParameter &op2);
ParameterQuotient                 operator / (const AbsParameter &op1, const AbsParameter &op2);
ParameterNegation                 operator - (const AbsParameter &op1);

typedef const AbsParameter & GENPARAMETER;

} // namespace Genfun   

// Poor man's covariant return type:
#define PARAMETER_OBJECT_DEF(classname)              \
public:                                              \
  classname *clone() const;                          \
private:                                             \
  virtual AbsParameter* _clone() const;

// Poor man's covariant return type:  
#define PARAMETER_OBJECT_IMP(classname)              \
classname *classname::clone () const {               \
  return (classname *) _clone();                     \
}                                                    \
AbsParameter *classname::_clone () const {           \
  return new classname(*this);                       \
}


#include "CLHEP/GenericFunctions/ParameterProduct.hh"
#include "CLHEP/GenericFunctions/ParameterSum.hh"
#include "CLHEP/GenericFunctions/ParameterDifference.hh"
#include "CLHEP/GenericFunctions/ParameterQuotient.hh"
#include "CLHEP/GenericFunctions/ParameterNegation.hh"
#include "CLHEP/GenericFunctions/ConstPlusParameter.hh"
#include "CLHEP/GenericFunctions/ConstMinusParameter.hh"
#include "CLHEP/GenericFunctions/ConstTimesParameter.hh"
#include "CLHEP/GenericFunctions/ConstOverParameter.hh"

#endif
