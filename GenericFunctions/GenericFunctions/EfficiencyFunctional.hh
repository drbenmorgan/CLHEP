// -*- C++ -*-
// $Id:
//-------------------------------------------------------------//
//                                                             //
// This functional returns the Likelihood of a functoin        //
// given some data                                             //
//                                                             //
//-------------------------------------------------------------//
#ifndef _EfficiencyFunctional_h_
#define _EfficiencyFunctional_h_
#include "CLHEP/GenericFunctions/AbsFunctional.hh"
#include "CLHEP/GenericFunctions/ArgumentList.hh"

namespace Genfun {

  /**
   * @author
   * @ingroup genfun
   */
  class EfficiencyFunctional:public AbsFunctional {

  public:
  
    // Constructor:
    EfficiencyFunctional(const ArgumentList & aList);

    // Destructor:
    ~EfficiencyFunctional();

    // Evaluate ChiSquared of a function w.r.t the data.
    virtual double operator [] (const AbsFunction & function) const;

  private:

    const ArgumentList _aList;

  };
} // namespace Genfun
#endif
