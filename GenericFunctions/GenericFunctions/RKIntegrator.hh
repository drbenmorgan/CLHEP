// -*- C++ -*-
// $Id:
//---------------------Runge-Kutte Integrator-------------------------------//
//                                                                          //
// Class RKIntegrator                                                       //
// Joe Boudreau, November 2002                                              //
//                                                                          //
// This is a Runge-Kutta Numerical integrator for a set of N autonomous     //
// first order differential equations in N variables. The point is to       //
// create one or more functions which are defined by A) the differential    //
// equations governing their time evolution, and B) their values at time    //
// t=0.                                                                     //
//                                                                          //
// You add differential eqns one at a time to this integrator.  Each one    //
// is a GENFUNCTION governing the time evolution of the i^th variable, and  //
// should depend on all of the N variables, but not on the time             //
// explicitly.  You should add N differential equations in all.   Each      //
// time you add a differential equation the integrator creates a parameter  //
// for you representing the starting value of the variable, and returns a   //
// pointer.  You may either set the values of that parameter to desired     //
// values or else connect it to an external parameter if you wish to vary   //
// the shape of the function by adjusting starting values.                  //
//                                                                          //
// In addition, you may request the integrator to create a control          //
// parameter.  The control parameter may also be set, or connected.         //
// It can be used in the equations that define the time evolution of the    //
// variables.                                                               //
//--------------------------------------------------------------------------//
#ifndef RKIntegrator_h
#define RKIntegrator_h 1
#include "CLHEP/GenericFunctions/AbsFunction.hh"
#include "CLHEP/GenericFunctions/Parameter.hh"
#include "CLHEP/GenericFunctions/RCBase.hh"
#include <vector>
#include <set>
namespace Genfun {

  /**
   * @author
   * @ingroup genfun
   */

  class RKIntegrator {

  public:

    // Some helper classes:
    class RKFunction;
    class RKData;

    // Constructor
    RKIntegrator();

    // Destructor
    virtual ~RKIntegrator();
  
    // Add a differential equation governing the time evolution of the next variable.
    // Get back a parameter representing the starting value of that variable.  You 
    // can either arrange for that parameter to have the right starting value, or you
    // can connect it to another parameter so that you may change it. 
    Parameter * addDiffEquation (const AbsFunction  * diffEquation,
				 const std::string & variableName="anon",
				 double defStartingValue=0.0,
				 double startingValueMin=0.0,
				 double startingValueMax=0.0);


    // Create a control parameter.  You can then connnect this to some other
    // parameter.
    Parameter *createControlParameter (const std::string & variableName="anon",
				       double defStartingValue=0.0,
				       double startingValueMin=0.0,
				       double startingValueMax=0.0);

    // Get back a function. This function will now actually change as parameters
    // are changed; this includes both control parameters and starting value 
    // parameters.
    const RKFunction *getFunction(unsigned int i) const;


  private:

    // It is illegal to assign an adjustable constant
    const RKIntegrator & operator=(const RKIntegrator &right);

    // It is illegal to copy an RKIntegrator
    RKIntegrator(const RKIntegrator &right);
  
    // Here is the data, it belongs to the integrator and to the
    // functions, and is reference counted:
    RKData                          *_data;


    // Here are the functions:
    std::vector<const RKFunction *> _fcn;


  };


  class RKIntegrator::RKData : public Genfun::RCBase {
    

  public:
    
    struct Data{

      std::vector<double>         variable;
      mutable std::vector<double> firstDerivative;
      double time; 
      mutable bool   dcalc;
 
      Data(int size): variable(size), firstDerivative(size), time(0), dcalc(false) {} 
      bool operator <  (const Data & right) const { return time < right.time; }
      bool operator == (const Data & right) const { return time==right.time; } 
    };

    RKData();
    void lock();
    void recache();

    std::vector<Parameter *>           _startingValParameter;
    std::vector<double>                _startingValParameterCache;

    std::vector <Parameter *>          _controlParameter;
    std::vector <double>               _controlParameterCache;

    std::vector<const AbsFunction *>   _diffEqn;
    std::set<Data >                    _fx;
    bool                               _locked;

  private:

    ~RKData();
    friend class ImaginaryFriend;  // Silence compiler warnings.

  };

  class RKIntegrator::RKFunction : public AbsFunction {

    FUNCTION_OBJECT_DEF(RKFunction)

      public:

    // Constructor
    RKFunction(RKData *data, unsigned int index);

    // Destructor
    virtual ~RKFunction();
  
    // Copy constructor
    RKFunction(const RKFunction &right);
  
    // Retreive function value
    virtual double operator ()(double argument) const;
    virtual double operator ()(const Argument & a) const {return operator() (a[0]);}

  private:

    // It is illegal to assign a RKFunction
    const RKFunction & operator=(const RKFunction &right);

    // The shared data:
    RKData              *_data;
    const  unsigned int  _index;

    void rk4 (const RKData::Data & sdata, RKData::Data & ddata) const;
  
    void rkstep (const RKData::Data & sdata, RKData::Data & ddata) const;
    void rkck   (const RKData::Data & sdata, RKData::Data & ddata, std::vector<double> & errors) const;
};


} // namespace Genfun

#endif
