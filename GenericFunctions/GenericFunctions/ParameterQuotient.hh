// -*- C++ -*-
// $Id: ParameterQuotient.hh,v 1.1.1.1 2003/07/15 20:15:05 garren Exp $
//--------------------------ParameterQuotient-------------------------------//
//                                                                          //
// ParameterQuotient, result of division of two parameters.                 //
// Joe Boudreau, Petar Maksimovic, November 1999                            //
//                                                                          //
//--------------------------------------------------------------------------//

#ifndef ParameterQuotient_h
#define ParameterQuotient_h 1
#include "CLHEP/GenericFunctions/AbsParameter.hh"
namespace Genfun {

  /**
   * @author
   * @ingroup genfun
   */
  class ParameterQuotient : public AbsParameter  {

    PARAMETER_OBJECT_DEF(ParameterQuotient)
  
      public:
  
    // Constructor
    ParameterQuotient(const AbsParameter *arg1, const AbsParameter *arg2);
  
    // Copy constructor
    ParameterQuotient(const ParameterQuotient &right);

    // Destructor
    virtual ~ParameterQuotient();
  
    // Retreive function value
    virtual double getValue() const;

  private:

    // It is illegal to assign a ParameterQuotient
    const ParameterQuotient & operator=(const ParameterQuotient &right);

    AbsParameter *_arg1;
    AbsParameter *_arg2;
  };
} // namespace Genfun
#endif
