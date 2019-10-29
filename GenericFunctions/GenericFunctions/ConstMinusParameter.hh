// -*- C++ -*-
// $Id: ConstMinusParameter.hh,v 1.2 2003/09/06 14:04:13 boudreau Exp $
//--------------------------ConstMinusParameter-----------------------------//
//                                                                          //
// ConstMinusParameter, result of subtracting a parameter from a constant.  //
// Joe Boudreau, Petar Maksimovic, November 1999                            //
//                                                                          //
//--------------------------------------------------------------------------//

#ifndef ConstMinusParameter_h
#define ConstMinusParameter_h 1
#include "CLHEP/GenericFunctions/AbsParameter.hh"

namespace Genfun {

  /**
   * @author
   * @ingroup genfun
   */
  class ConstMinusParameter : public AbsParameter  {

    PARAMETER_OBJECT_DEF(ConstMinusParameter)
  
      public:
  
    // Constructor
    ConstMinusParameter(double, const AbsParameter *);
  
    // Copy constructor
    ConstMinusParameter(const ConstMinusParameter &right);

    // Destructor
    virtual ~ConstMinusParameter();
  
    // Retreive function value
    virtual double getValue() const;

  private:

    // It is illegal to assign a ConstMinusParameter
    const ConstMinusParameter & operator=(const ConstMinusParameter &right);

    double        _constant;
    AbsParameter *_parameter;
  };
} // namespace Genfun
#endif
