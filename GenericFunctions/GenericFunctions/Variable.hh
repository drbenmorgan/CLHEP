// -*- C++ -*-
// $Id: Variable.hh,v 1.2 2003/09/06 14:04:13 boudreau Exp $
//----------------------X------------ --------------------------------------//
//                                                                          //
//  Class Variable                                                          //
//  Joe Boudreau, Petar Maksimovic, Nov. 1999                               //
//                                                                          //
//  Variable is a function that returns the variable itself.                //
//--------------------------------------------------------------------------//
#ifndef Variable_h
#define Variable_h 1
#include "CLHEP/GenericFunctions/AbsFunction.hh"
namespace Genfun {

  /**
   * @author
   * @ingroup genfun
   */
  class Variable : public AbsFunction  {
  
    FUNCTION_OBJECT_DEF(Variable)

      public:

    // Constructor
    Variable(unsigned int selectionIndex=0,
             unsigned int dimensionality=1);
  
    // Copy constructor
    Variable(const Variable &right);
  
    // Destructor
    virtual ~Variable();
  
    // Retrieve function value
    virtual double operator ()(double argument) const; 
    virtual double operator ()(const Argument & a) const;

    // Get the dimensionality, as specified in the constructor:
    virtual unsigned int dimensionality() const ;  
  
    // Get the selectionIndex:
    unsigned int index() const;

    // Derivative.  
    Derivative partial (unsigned int) const;

    // Does this function have an analytic derivative?
    virtual bool hasAnalyticDerivative() const {return true;}

  private:

    // It is illegal to assign a fixed constant
    const Variable & operator=(const Variable &right);

    // The selection index is used to select a particular element from
    // the argument.  By default it is zero.....
    unsigned int _selectionIndex;

    // The dimensionality, length of the argument list:
    unsigned int _dimensionality;

  };

} // namespace Genfun
#endif
