#include "CLHEP/GenericFunctions/GenericFunctions.hh"
#include "CLHEP/GenericFunctions/Sin.hh"
#include "CLHEP/GenericFunctions/Cos.hh"
#include "CLHEP/GenericFunctions/defs.h"
#include <float.h>
#include <cassert>
#include <cmath>


int  main(int, char **) {
  
  using namespace Genfun;

  GENFUNCTION  f = Sin(), g = Cos();
  GENPARAMETER p = Parameter("Parameter", 4.0);

  for (double x = 0; x < 100; x++) {
    // Test Simple Arithmetic Operations Between Functions
    
    assert (fabs((f*g) (x) - (sin(x)*cos(x))) <= FLT_EPSILON);
    assert (fabs((f+g) (x) - (sin(x)+cos(x))) <= FLT_EPSILON);
    assert (fabs((f-g) (x) - (sin(x)-cos(x))) <= FLT_EPSILON);
    assert (fabs((f/g) (x) - (sin(x)/cos(x))) <= FLT_EPSILON);
    
    // Test Simple Arithmetic Operations Between Functions and Parameters
    
    assert (fabs((p*f)(x)- 4.0*sin(x)) <= FLT_EPSILON);
    assert (fabs((f*p)(x)- 4.0*sin(x)) <= FLT_EPSILON);
    
    // Test Simple Arithmetic Operations Between Functions and Constants
    
    assert (fabs((f*4.0)(x)- 4.0*sin(x)) <= FLT_EPSILON);
    assert (fabs((4.0*f)(x)- 4.0*sin(x)) <= FLT_EPSILON);
    
    // Test Function composition
    assert (fabs(((f(g))(x)) - sin(cos(x))) <= FLT_EPSILON);
    
  }
  

  // Test Simple Arithmetic Operations Between Parameters 
  assert (fabs((p*p).getValue()- 4.0*4.0) <= FLT_EPSILON);

  // Test Simple Arithmetic Operations Between Parameters and Constants
  assert (fabs((4*p).getValue()- 4.0*4.0) <= FLT_EPSILON);
  assert (fabs((p*4).getValue()- 4.0*4.0) <= FLT_EPSILON);

  // Congratulate the lucky user:
  std::cout << "GenericFunctions autotest has passed" << std::endl;
  return 0;
}
