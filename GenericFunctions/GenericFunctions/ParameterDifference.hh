// -*- C++ -*-
// $Id: ParameterDifference.hh,v 1.2 2003/09/06 14:04:13 boudreau Exp $
//--------------------------ParameterDifference-----------------------------//
//                                                                          //
// ParameterDifference, result of subtraction of two parameters.            //
// Joe Boudreau, Petar Maksimovic, November 1999                            //
//                                                                          //
//--------------------------------------------------------------------------//

#ifndef ParameterDifference_h
#define ParameterDifference_h 1
#include "CLHEP/GenericFunctions/AbsParameter.hh"

namespace Genfun {

  /**
   * @author
   * @ingroup genfun
   */
  class ParameterDifference : public AbsParameter  {

    PARAMETER_OBJECT_DEF(ParameterDifference)
  
      public:
  
    // Constructor
    ParameterDifference(const AbsParameter *arg1, const AbsParameter *arg2);
  
    // Copy constructor
    ParameterDifference(const ParameterDifference &right);

    // Destructor
    virtual ~ParameterDifference();
  
    // Retreive parameter value
    virtual double getValue() const;

  private:

    // It is illegal to assign a ParameterDifference
    const ParameterDifference & operator=(const ParameterDifference &right);

    AbsParameter *_arg1;
    AbsParameter *_arg2;
  };
} // namespace Genfun
#endif
