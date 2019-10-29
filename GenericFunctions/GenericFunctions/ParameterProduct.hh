// -*- C++ -*-
// $Id: ParameterProduct.hh,v 1.2 2003/09/06 14:04:13 boudreau Exp $
//--------------------------ParameterProduct--------------------------------//
//                                                                          //
// ParameterProduct, result of multiplication of two parameters.            //
// Joe Boudreau, Petar Maksimovic, November 1999                            //
//                                                                          //
//--------------------------------------------------------------------------//

#ifndef ParameterProduct_h
#define ParameterProduct_h 1
#include "CLHEP/GenericFunctions/AbsParameter.hh"

namespace Genfun {

  /**
   * @author
   * @ingroup genfun
   */
  class ParameterProduct : public AbsParameter  {
  
    PARAMETER_OBJECT_DEF(ParameterProduct)

      public:
  
    // Constructor
    ParameterProduct(const AbsParameter *arg1, const AbsParameter *arg2);
  
    // Copy constructor
    ParameterProduct(const ParameterProduct &right);

    // Destructor
    virtual ~ParameterProduct();
  
    // Retreive function value
    virtual double getValue() const;

  private:

    // It is illegal to assign a ParameterProduct
    const ParameterProduct & operator=(const ParameterProduct &right);

    AbsParameter *_arg1;
    AbsParameter *_arg2;
  };
} // namespace Genfun
#endif
