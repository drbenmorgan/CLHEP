// -*- C++ -*-
// $Id: ConstPlusParameter.hh,v 1.1.1.1 2003/07/15 20:15:05 garren Exp $
//--------------------------ConstPlusParameter------------------------------//
//                                                                          //
// ConstPlusParameter, result of adding a constant to a parameters.         //
// Joe Boudreau, Petar Maksimovic, November 1999                            //
//                                                                          //
//--------------------------------------------------------------------------//

#ifndef ConstPlusParameter_h
#define ConstPlusParameter_h 1
#include "CLHEP/GenericFunctions/AbsParameter.hh"

namespace Genfun {

  /**
   * @author
   * @ingroup genfun
   */
  class ConstPlusParameter : public AbsParameter  {

    PARAMETER_OBJECT_DEF(ConstPlusParameter)
  
      public:
  
    // Constructor
    ConstPlusParameter(double, const AbsParameter *);
  
    // Copy constructor
    ConstPlusParameter(const ConstPlusParameter &right);

    // Destructor
    virtual ~ConstPlusParameter();
  
    // Retreive function value
    virtual double getValue() const;

  private:

    // It is illegal to assign a ConstPlusParameter
    const ConstPlusParameter & operator=(const ConstPlusParameter &right);

    double        _constant;
    AbsParameter *_parameter;
  };
} // namespace Genfun
#endif
