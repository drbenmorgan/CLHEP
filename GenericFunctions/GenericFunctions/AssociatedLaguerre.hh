// -*- C++ -*-
// $Id: AssociatedLaguerre.hh,v 1.2 2003/09/06 14:04:13 boudreau Exp $
//---------------------AssociatedLaguerre-----------------------------------//
//                                                                          //
// Class AssociatedLaguerre.  An associated laguerre polynomial L_n^k(x)    //
// Joe Boudreau, Petar Maksimovic, November 1999                            //
//                                                                          //
//                                                                          //
// Different definitions exist.  These are taken from Arfken, Mathematical  //
// Methods for physicists                                                   //
//                                                                          //
//--------------------------------------------------------------------------//
#ifndef AssociatedLaguerre_h
#define AssociatedLaguerre_h 1
#include "CLHEP/GenericFunctions/AbsFunction.hh"

namespace Genfun {

  /**
   * @author
   * @ingroup genfun
   */
  class AssociatedLaguerre : public AbsFunction  {
  
    FUNCTION_OBJECT_DEF(AssociatedLaguerre)

      public:

    // Constructor
    AssociatedLaguerre(unsigned int n, unsigned int k);

    // Copy constructor
    AssociatedLaguerre(const AssociatedLaguerre &right);
  
    // Destructor
    virtual ~AssociatedLaguerre();
  
    // Retreive function value

    virtual double operator ()(double argument) const;
    virtual double operator ()(const Argument & a) const {return operator() (a[0]);}
  
    // Get the integer variable n
    unsigned int n() const;

    // Get the integer variable k
    unsigned int k() const;

  private:

    // It is illegal to assign an adjustable constant
    const AssociatedLaguerre & operator=(const AssociatedLaguerre &right);

    // Here is the decay constant
    unsigned int _n;

    // Here is the sigma
    unsigned int _k;

    // Here is the "work function"
    const AbsFunction *_function;

    // This function is needed in all constructors:
    void create(); 
  };

} // namespace Genfun



#endif


