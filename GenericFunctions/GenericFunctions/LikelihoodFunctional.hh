// -*- C++ -*-
// $Id: LikelihoodFunctional.hh,v 1.2 2003/09/06 14:04:13 boudreau Exp $
//-------------------------------------------------------------//
//                                                             //
// This functional returns the Likelihood of a functoin        //
// given some data                                             //
//                                                             //
//-------------------------------------------------------------//
#ifndef _LikelihoodFunctional_h_
#define _LikelihoodFunctional_h_
#include "CLHEP/GenericFunctions/AbsFunctional.hh"
#include "CLHEP/GenericFunctions/ArgumentList.hh"

namespace Genfun {

  /**
   * @author
   * @ingroup genfun
   */
  class LikelihoodFunctional:public AbsFunctional {

  public:
  
    // Constructor:
    LikelihoodFunctional(const ArgumentList & aList);

    // Destructor:
    ~LikelihoodFunctional();

    // Evaluate ChiSquared of a function w.r.t the data.
    virtual double operator [] (const AbsFunction & function) const;

  private:

    const ArgumentList _aList;

  };
} // namespace Genfun
#endif
