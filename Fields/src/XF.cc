#include "CLHEP/Fields/XF.h"
#include <assert.h>
#include <iostream>
namespace XF
{



  //------------------------------------------------------------------//
  //                                                                  //
  //  Implementation of Function                                      //
  //                                                                  //
  //------------------------------------------------------------------//

  Function::Function ()
  {
  }

  Function::~Function ()
  {
  }

  Product operator * (const Function & a, const Function & b)
  {
    return Product (&a, &b);
  }

  PreMult operator * (const HepGeom::Transform3D & xf, const Function & b)
  {
    return PreMult (xf, &b);
  }

  PostMult operator * (const Function & a, const HepGeom::Transform3D & xf)
  {
    return PostMult (&a, xf);
  }

  unsigned int Function::dimensionality () const
  {
    return 1;
  }

  //------------------------------------------------------------------//
  //                                                                  //
  //  Implementation of Product                                       //
  //                                                                  //
  //------------------------------------------------------------------//

  Product::Product (const Function * arg1,
		    const Function * arg2):_arg1 (arg1->clone ()),
    _arg2 (arg2->clone ())
  {
    if (arg1->dimensionality () != arg2->dimensionality ())
      {
	std::cout <<"Warning:  dimension mismatch in XF::Product" << std::endl;
	assert(0);
      }
  }


  // Every function must override this:
  Product *Product::clone () const
  {
    return new Product (*this);
  }

  // Copy constructor:
  Product::Product (const Product & right):Function (),
    _arg1 (right._arg1->clone ()), _arg2 (right._arg2->clone ())
  {
  }


  Product::~Product ()
  {
    delete _arg1;
    delete _arg2;
  }

  unsigned int Product::dimensionality () const
  {
    return _arg1->dimensionality ();
  }

  HepGeom::Transform3D Product::operator        () (double x) const
  {
    return (*_arg1) (x) * (*_arg2) (x);
  }

  HepGeom::Transform3D Product::operator        () (const Genfun::Argument & x) const
  {
    return (*_arg1) (x) * (*_arg2) (x);
  }



  //------------------------------------------------------------------//
  //                                                                  //
  //  Implementation of PreMult                                       //
  //                                                                  //
  //------------------------------------------------------------------//

  PreMult::PreMult (const HepGeom::Transform3D & arg1,
		    const Function * arg2):_arg1 (arg1),
    _arg2 (arg2->clone ())
  {
  }


  // Every function must override this:
  PreMult *PreMult::clone () const
  {
    return new PreMult (*this);
  }

  // Copy constructor:
  PreMult::PreMult (const PreMult & right):Function (), _arg1 (right._arg1),
    _arg2 (right._arg2->clone ())
  {
  }


  PreMult::~PreMult ()
  {
    delete _arg2;
  }

  unsigned int PreMult::dimensionality () const
  {
    return _arg2->dimensionality ();
  }

  HepGeom::Transform3D PreMult::operator        () (double x) const
  {
    return _arg1 * (*_arg2) (x);
  }

  HepGeom::Transform3D PreMult::operator        () (const Genfun::Argument & x) const
  {
    return _arg1 * (*_arg2) (x);
  }


  //------------------------------------------------------------------//
  //                                                                  //
  //  Implementation of PostMult                                      //
  //                                                                  //
  //------------------------------------------------------------------//

  PostMult::PostMult (const Function * arg1,
		      const HepGeom::Transform3D & arg2):_arg1 (arg1->clone ()),
    _arg2 (arg2)
  {
  }


  // Every function must override this:
  PostMult *PostMult::clone () const
  {
    return new PostMult (*this);
  }

  // Copy constructor:
  PostMult::PostMult (const PostMult & right):Function (),
    _arg1 (right._arg1->clone ()), _arg2 (right._arg2)
  {
  }


  PostMult::~PostMult ()
  {
    delete _arg1;
  }

  unsigned int PostMult::dimensionality () const
  {
    return _arg1->dimensionality ();
  }

  HepGeom::Transform3D PostMult::operator        () (double x) const
  {
    return (*_arg1) (x) * _arg2;
  }

  HepGeom::Transform3D PostMult::operator        () (const Genfun::Argument & x) const
  {
    return (*_arg1) (x) * _arg2;
  }


  Pow::Pow (const HepGeom::Transform3D & xform, Genfun::GENFUNCTION f):xf (xform),
    function (f.clone ())
  {
  }

  Pow::~Pow ()
  {
    delete function;
  }

  HepGeom::Transform3D Pow::operator        () (double x) const
  {
    //
    // Get the translation part and the rotation part:
    //
    CLHEP::HepRotation rotate = xf.getRotation ();
    CLHEP::Hep3Vector translate = xf.getTranslation ();
    CLHEP::HepAxisAngle aa = rotate.axisAngle ();
    //
    // Evaluate the function
    //
    double nTimes = (*function) (x);
    //
    // Modify:
    //
      translate *= nTimes;
      aa.setDelta (aa.delta () * nTimes);
    //
    // Now compose these and return a result:
    //
      return HepGeom::Translate3D (translate) * HepGeom::Rotate3D (aa.delta (),
						       aa.axis ());
  }

  HepGeom::Transform3D Pow::operator        () (const Genfun::Argument & argument) const
  {
    return operator        () (argument[0]);
  }

  Pow *Pow::clone () const
  {
    return new Pow (*this);
  }

  Pow::Pow (const Pow & right):Function (), xf (right.xf),
    function (right.function->clone ())
  {
  }

}
