// -*- C++ -*-
// $Id: ConstOverParameter.hh,v 1.2 2003/09/06 14:04:13 boudreau Exp $
//--------------------------ConstOverParameter------------------------------//
//                                                                          //
// ConstOverParameter, result of multiplying a parameter with a constant.   //
// Joe Boudreau, Petar Maksimovic, November 1999                            //
//                                                                          //
//--------------------------------------------------------------------------//

#ifndef ConstOverParameter_h
#define ConstOverParameter_h 1
#include "CLHEP/GenericFunctions/AbsParameter.hh"

namespace Genfun {

  /**
   * @author
   * @ingroup genfun
   */
  class ConstOverParameter : public AbsParameter  {

    PARAMETER_OBJECT_DEF(ConstOverParameter)
  
      public:
  
    // Constructor
    ConstOverParameter(double, const AbsParameter *);
  
    // Copy constructor
    ConstOverParameter(const ConstOverParameter &right);

    // Destructor
    virtual ~ConstOverParameter();
  
    // Retreive function value
    virtual double getValue() const;

  private:

    // It is illegal to assign a ConstOverParameter
    const ConstOverParameter & operator=(const ConstOverParameter &right);

    double        _constant;
    AbsParameter *_parameter;
  };
} // namespace Genfun
#endif
