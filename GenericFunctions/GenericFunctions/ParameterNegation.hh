// -*- C++ -*-
// $Id: ParameterNegation.hh,v 1.2 2003/09/06 14:04:13 boudreau Exp $
//--------------------------ParameterNegation-------------------------------//
//                                                                          //
// ParameterNegation, result of negating a parameters.                      //
// Joe Boudreau, Petar Maksimovic, November 1999                            //
//                                                                          //
//--------------------------------------------------------------------------//

#ifndef ParameterNegation_h
#define ParameterNegation_h 1
#include "CLHEP/GenericFunctions/AbsParameter.hh"

namespace Genfun {

  /**
   * @author
   * @ingroup genfun
   */
  class ParameterNegation : public AbsParameter  {
  
    PARAMETER_OBJECT_DEF(ParameterNegation)

      public:
  
    // Constructor
    ParameterNegation(const AbsParameter *arg1);
  
    // Copy constructor
    ParameterNegation(const ParameterNegation &right);

    // Destructor
    virtual ~ParameterNegation();
  
    // Retreive parameter value
    virtual double getValue() const;

  private:

    // It is illegal to assign a ParameterNegation
    const ParameterNegation & operator=(const ParameterNegation &right);

    // The parameter to be negated:
    AbsParameter *_arg1;

  };
} // namespace Genfun
#endif
