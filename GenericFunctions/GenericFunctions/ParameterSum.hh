// -*- C++ -*-
// $Id: ParameterSum.hh,v 1.1.1.1 2003/07/15 20:15:05 garren Exp $
//--------------------------ParameterSum------------------------------------//
//                                                                          //
// ParameterSum, result of addition of two parameters.                      //
// Joe Boudreau, Petar Maksimovic, November 1999                            //
//                                                                          //
//--------------------------------------------------------------------------//

#ifndef ParameterSum_h
#define ParameterSum_h 1
#include "CLHEP/GenericFunctions/AbsParameter.hh"

namespace Genfun {

  /**
   * @author
   * @ingroup genfun
   */
  class ParameterSum : public AbsParameter  {

    PARAMETER_OBJECT_DEF(ParameterSum)
  
      public:
  
    // Constructor
    ParameterSum(const AbsParameter *arg1, const AbsParameter *arg2);
  
    // Copy constructor
    ParameterSum(const ParameterSum &right);

    // Destructor
    virtual ~ParameterSum();
  
    // Retreive function value
    virtual double getValue() const;

  private:

    // It is illegal to assign a ParameterSum
    const ParameterSum & operator=(const ParameterSum &right);

    AbsParameter *_arg1;
    AbsParameter *_arg2;
  };
} // namespace Genfun
#endif
