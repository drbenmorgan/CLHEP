// -*- C++ -*-
// $Id: AssociatedLegendre.hh,v 1.2 2003/09/06 14:04:13 boudreau Exp $
//---------------------AssociatedLegendre-----------------------------------//
//                                                                          //
// Class AssociatedLegendre.  An associated legendre polynomial             //
// Joe Boudreau, Petar Maksimovic, November 1999                            //
//                                                                          //
//--------------------------------------------------------------------------//
#ifndef AssociatedLegendre_h
#define AssociatedLegendre_h 1
#include "CLHEP/GenericFunctions/AbsFunction.hh"
#include "CLHEP/GenericFunctions/Parameter.hh"

namespace Genfun {

  /**
   * @author
   * @ingroup genfun
   */
  class AssociatedLegendre : public AbsFunction  {
  
    FUNCTION_OBJECT_DEF(AssociatedLegendre)

      public:

    // Constructor
    AssociatedLegendre(unsigned int l, unsigned int m);

    // Copy constructor
    AssociatedLegendre(const AssociatedLegendre &right);
  
    // Destructor
    virtual ~AssociatedLegendre();
  
    // Retreive function value
    virtual double operator ()(double argument) const;
    virtual double operator ()(const Argument & a) const {return operator() (a[0]);}
  
    // Get the integer variable l
    unsigned int l() const;

    // Get the integer variable mj
    unsigned int m() const;

  private:

    // It is illegal to assign an adjustable constant
    const AssociatedLegendre & operator=(const AssociatedLegendre &right);

    // Here is the decay constant
    unsigned int _l;

    // Here is the sigma
    unsigned int _m;

    // Here is the "work function"
    const AbsFunction *_function;

    // This function is needed in all constructors:
    void create(); 
  };

} // namespace Genfun



#endif


