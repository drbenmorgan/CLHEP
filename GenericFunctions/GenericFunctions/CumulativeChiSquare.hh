// -*- C++ -*-
// $Id: CumulativeChiSquare.hh,v 1.2 2003/09/06 14:04:13 boudreau Exp $
//---------------------CumulativeChiSquare----------------------------------//
//                                                                          //
// Class CumulativeChiSquare, also known as the probability chi squared     //
// Joe Boudreau, October 2000                                               //
//                                                                          //
//--------------------------------------------------------------------------//
#ifndef CumulativeChiSquare_h
#define CumulativeChiSquare_h 1
#include "CLHEP/GenericFunctions/AbsFunction.hh"
#include "CLHEP/GenericFunctions/Parameter.hh"
namespace Genfun {

  /**
   * @author
   * @ingroup genfun
   */
  class CumulativeChiSquare : public AbsFunction  {

    FUNCTION_OBJECT_DEF(CumulativeChiSquare)

      public:

    // Constructor
    CumulativeChiSquare(unsigned int nDof);

    // Copy constructor
    CumulativeChiSquare(const CumulativeChiSquare &right);
  
    // Destructor
    virtual ~CumulativeChiSquare();
  
    // Retreive function value
    virtual double operator ()(double argument) const;
    virtual double operator ()(const Argument & a) const {return operator() (a[0]);}
  
    // Get the integer variable l
    unsigned int nDof() const;

  private:

    // It is illegal to assign an adjustable constant
    const CumulativeChiSquare & operator=(const CumulativeChiSquare &right);

    // Here is the decay constant
    unsigned int _nDof;
  
    // Here is the "work function"
    const AbsFunction *_function;

    // This function is needed in all constructors:
    void create(); 

  };
} // namespace Genfun

#endif
