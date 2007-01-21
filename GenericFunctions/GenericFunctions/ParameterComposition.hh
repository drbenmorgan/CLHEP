// -*- C++ -*-
// $Id: 
//--------------------------ParameterComposition----------------------------//
//                                                                          //
// ParameterComposition, result of composition of two functions.            //
// Joe Boudreau, Petar Maksimovic, November 1999                            //
//                                                                          //
//--------------------------------------------------------------------------//

#ifndef ParameterComposition_h
#define ParameterComposition_h 1
#include "CLHEP/GenericFunctions/AbsFunction.hh"
#include "CLHEP/GenericFunctions/AbsParameter.hh"

namespace Genfun {

  /**
   * @author
   * @ingroup genfun
   */
  class ParameterComposition : public AbsParameter {

    PARAMETER_OBJECT_DEF(ParameterComposition)

      public:

    // Constructor
    ParameterComposition(const AbsFunction *arg1, const AbsParameter *arg2);

    // Copy constructor
    ParameterComposition(const ParameterComposition &right);
  
    // Destructor
    virtual ~ParameterComposition();

    // Retreive parameter value
    virtual double getValue() const;


  private:

    // It is illegal to assign a ParameterComposition
    const ParameterComposition & operator=(const ParameterComposition &right);

    const AbsFunction  *_arg1;
    AbsParameter *_arg2;  
  };
} // namespace Genfun
#endif
