// -*- C++ -*-
// $Id: ConstTimesParameter.hh,v 1.2 2003/09/06 14:04:13 boudreau Exp $
//--------------------------ConstTimesParameter-----------------------------//
//                                                                          //
// ConstTimesParameter, result of subtracting a parameter from a constant.  //
// Joe Boudreau, Petar Maksimovic, November 1999                            //
//                                                                          //
//--------------------------------------------------------------------------//

#ifndef ConstTimesParameter_h
#define ConstTimesParameter_h 1
#include "CLHEP/GenericFunctions/AbsParameter.hh"

namespace Genfun {

  /**
   * @author
   * @ingroup genfun
   */
  class ConstTimesParameter : public AbsParameter  {

    PARAMETER_OBJECT_DEF(ConstTimesParameter)
  
      public:
  
    // Constructor
    ConstTimesParameter(double, const AbsParameter *);
  
    // Copy constructor
    ConstTimesParameter(const ConstTimesParameter &right);

    // Destructor
    virtual ~ConstTimesParameter();
  
    // Retreive function value
    virtual double getValue() const;

  private:

    // It is illegal to assign a ConstTimesParameter
    const ConstTimesParameter & operator=(const ConstTimesParameter &right);

    double        _constant;
    AbsParameter *_parameter;
  };
} // namespace Genfun
#endif
