// -*- C++ -*-
// $Id: AbsFunctional.hh,v 1.2 2003/09/06 14:04:13 boudreau Exp $
// A functional is a mapping from functions to real numbers.
// Here is their base class:
#ifndef _AbsFunctional_h_
#define _AbsFunctional_h_

namespace Genfun {

  class AbsFunction;
  
  /**
   * @author
   * @ingroup genfun
   */
  class AbsFunctional {

  public:

    // Constructor
    AbsFunctional(); 

    // Destructor:
    virtual ~AbsFunctional();

    // A functional is a mapping from functions to 
    // real numbers.  This defines that mapping:
    virtual double operator[] (const AbsFunction & function) const = 0;

  };
} // namespace Genfun
#endif
