//---------------XF::Function (transformation field)--------------------//
//                                                                      //
//  XF::Function, class of function objects which evaluate to a         //
//  evaluate to a HepTransform, and a class XF::Pow which can be        //
//  used to exponentiate any transform.  The transformations fields     //
//  can be multiplied together or multiplied with a fixed global        //
//  transformation.  These can be used to build arbitrary               //
//  HepTransform3D-valued-fields which are very compact.  Chief         //
//  application so far is in geometry modelling where it is a           //
//  powerful technique for parameterization.                            //
//                                                                      //
//  Example:                                                            //
//                                                                      //
//  // Define some constants:                                           //
//  int          N;                                                     //
//  double       c1, c2, r, z;                                          //
//                                                                      //
// // Construct a simple linear function of a variable i:               //
//                                                                      //
//  Variable      i;                                                    //
//                                                                      //
//  GENFUNCTION   g =  c1+c2*i;                                         //
//                                                                      //
//  // Create a transfunction                                           //
//                                                                      //
//  TRANSFUNCTION xf =  Pow(HepRotateZ3D(1),g)*                         //
//                      HepTranslateX3D(r)*                             //
//                      HepTranslateZ3D(z);                             //
//                                                                      //
//  // Evaluation of TRANSFUNCTION                                      //
//                                                                      //
//  HepTransform3D x = xf(33.2);                                        //
//                                                                      //
//                                                                      //
// ...                                                                  //
// Similar techniques may be used to create a transformation field of   //
// more than one variable.                                              //
//                                                                      //
//                                                                      //
//----------------------------------------------------------------------//
#ifndef TransformFunction_h
#define TransformFunction_h 1
#include "CLHEP/GenericFunctions/AbsFunction.hh"
#include "CLHEP/GenericFunctions/Argument.hh"
#include "CLHEP/Geometry/Transform3D.h"

//-----------------------------------------------------------------------//
// Exact return type of arithmentic operations.  To the user, the return //
// type is TRANSFUNCTION, or const XF::Function &.                       //
//-----------------------------------------------------------------------//

namespace XF
{

  class Product;
  class PreMult;
  class PostMult;
  class Pow;


  class Function
  {

  public:

    // Default Constructor
    Function ();

    // Destructor
    virtual ~ Function ();

    // Function value:  N-dimensional functions must override these:
    virtual unsigned int dimensionality () const;	//returns 1;

    // Function value
    virtual HepGeom::Transform3D operator         () (double argument) const = 0;
    virtual HepGeom::Transform3D operator         () (const Genfun::
						Argument & argument) const =
      0;

    // Every function must override this:
    virtual Function *clone () const = 0;

    // Copy constructor
      Function (const Function & right);

  private:

    // Assignment operator
    const Function & operator = (const Function & right);

  };






  class Pow:public Function
  {

  public:

    Pow (const HepGeom::Transform3D &, Genfun::GENFUNCTION f);

      virtual ~ Pow ();

    virtual HepGeom::Transform3D operator         () (double argument) const;
    virtual HepGeom::Transform3D operator         () (const Genfun::
						Argument & argument) const;

    // Every function must override this:
    Pow *clone () const;

    // Copy constructor:
      Pow (const Pow & right);

  private:

    // Assignment operator
    const Pow & operator = (const Pow & right);

    const HepGeom::Transform3D xf;
    const Genfun::AbsFunction * function;

  };





  Product operator * (const Function & op1, const Function & op2);
  PreMult operator * (const HepGeom::Transform3D & xf, const Function & op2);
  PostMult operator * (const Function & op2, const HepGeom::Transform3D & xf);


  // Internally used class:: Product:

  class Product:public Function
  {

  public:


    Product (const Function * arg1, const Function * arg2);

      virtual ~ Product ();

    virtual unsigned int dimensionality () const;

    virtual HepGeom::Transform3D operator         () (double argument) const;
    virtual HepGeom::Transform3D operator         () (const Genfun::
						Argument & argument) const;

    // Every function must override this:
    virtual Product *clone () const;

    // Copy constructor:
      Product (const Product & right);

  private:

    const Function *_arg1;
    const Function *_arg2;

  };

  // Internally used class:: PreMult :

  class PreMult:public Function
  {

  public:


    PreMult (const HepGeom::Transform3D & arg1, const Function * arg2);

      virtual ~ PreMult ();

    virtual unsigned int dimensionality () const;

    virtual HepGeom::Transform3D operator         () (double argument) const;
    virtual HepGeom::Transform3D operator         () (const Genfun::
						Argument & argument) const;

    // Every function must override this:
    virtual PreMult *clone () const;

    // Copy constructor:
      PreMult (const PreMult & right);

  private:

    const HepGeom::Transform3D _arg1;
    const Function *_arg2;

  };

  // Internally used class:: PostMult :

  class PostMult:public Function
  {

  public:


    PostMult (const Function * arg1, const HepGeom::Transform3D & arg2);

      virtual ~ PostMult ();

    virtual unsigned int dimensionality () const;

    virtual HepGeom::Transform3D operator         () (double argument) const;
    virtual HepGeom::Transform3D operator         () (const Genfun::
						Argument & argument) const;

    // Every function must override this:
    virtual PostMult *clone () const;

    // Copy constructor:
      PostMult (const PostMult & right);

  private:

    const Function *_arg1;
    const HepGeom::Transform3D _arg2;

  };

  typedef const Function & TRANSFUNCTION;



}

#endif
