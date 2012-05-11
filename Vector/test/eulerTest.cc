// eulerTest.cc

// Test extreme cases for Euler angles --
// We perturb the matrix slightly before taking Euler angles.
// A test will have failed if the Rotation resulting from taking euler angles 
// and forming a rotation from them, is ever significantly different than the
// origninal rotation.


#include "CLHEP/Vector/Rotation.h"
#include "CLHEP/Vector/EulerAngles.h"
#include "CLHEP/Units/PhysicalConstants.h"

#include <iostream>
#include <math.h>

using std::cout;
using namespace CLHEP;

const int Nperturbs = 24;

void perturb ( int i, const HepRotation & r, HepRotation & rp, double & del );
bool compareR ( const HepRotation & r1, const HepRotation & r2, double tol );

bool test (double phi, double theta, double psi) {
  HepRotation r (phi, theta, psi);
  HepRotation rp;
  HepRotation rpe;
  HepEulerAngles e;
  bool retval = true;
  double del;
  cout << "\n\n -------------------------------- \n\n";
  for ( int i = 0; i < Nperturbs; ++i ) {
    perturb ( i, r, rp, del );
    e = rp.eulerAngles();
    cout << "(" << phi <<", " << theta << ", " << psi << ") --> "<< e << "\n";
    cout << "       e.phi() = "  << e.phi() 
         << "    rp.phi() = " << rp.phi()  
	 << " difference is " << (e.phi() - rp.phi())/del << " * del\n";    
    if ( std::fabs (e.phi() - rp.phi()) > 200*del ) {
      cout << "phi discrepancy in "  << rp << "\n";
      cout << "       e.phi() = "  << e.phi() 
           << "    rp.phi() = " << rp.phi()  
	   << " difference is " << e.phi() - rp.phi() << "\n";
      if (del < 1.0e-4) cout << "??????????\n";
      retval = false;
    }
    if ( std::fabs (e.theta() - rp.theta()) > 200*del ) {
      cout << "theta discrepancy in "  << rp << "\n";
      cout << "       e.theta() = "  << e.theta() 
           << "    rp.theta() = " << rp.theta()
	   << " difference is " << e.theta() - rp.theta() << "\n";
      if (del < 1.0e-4) cout << "??????????\n";
      retval = false;
    }
    cout << "       e.psi() = "  << e.psi() 
         << "    rp.psi() = " << rp.psi() 
	 << " difference is " << (e.psi() - rp.psi())/del << " * del\n";
     if ( std::fabs (e.psi() - rp.psi()) > 200*del ) {
      cout << "psi discrepancy in "  << rp << "\n";
      cout << "       e.psi() = "  << e.psi() 
           << "    rp.psi() = " << rp.psi() 
	   << " difference is " << e.psi() - rp.psi() << "\n";
      if (del < 1.0e-4) cout << "??????????\n";
      retval = false;
    }
    rpe.set(e);
    retval &= compareR (rpe, rp, del);
  }
  return retval;
}

int main () {

  bool res = true;
  double PI = CLHEP::pi;

  // Some cases not in the potentially unstable region:
  res &= test (  .05,	       PI/5,   .1	);    
  res &= test (  .4,	       PI/7,   -.35	);    
  res &= test (  PI/3,         PI/6,   -PI/3	);    
  res &= test (  PI/5,         PI/2,   -PI/2.5  );    
  res &= test ( -PI/5,         PI/2,   PI/3	);    
  res &= test ( -4*PI/5,       PI/2,   PI/2.5	);    
  res &= test (  4*PI/5,       PI/2,   2*PI/3	);    
  res &= test ( -3*PI/4,       PI/2,   -PI/3	);    
  res &= test (  5*PI/6,       PI/2,   -4*PI/5	);    
  res &= test (  5*PI/6,       PI/2,   -PI/3	);    

  // Specialized cases
  res &= test (  .05,	       0,      .1       );    
  res &= test (  .2,	       0,      1.1      );    
  res &= test (  -.4,	       0,      .4       );    
  res &= test (  -2.4,	       0,     2.0       );    
  res &= test (  -2.4,	       0,     -2.0      );    
  res &= test (  -2.2,	       0,     1.8       );    
  res &= test (  -2.2,	       0,     -1.8      );    
  res &= test (  .05,	       PI,     .1       );    
  res &= test (  .2,	       PI,     1.1      );    
  res &= test (  -.4,	       PI,     .4       );    
  res &= test (  -2.4,	       PI,     2.0      );    
  res &= test (  -2.4,	       PI,     -2.0     );    
  res &= test (  -2.2,	       PI,     1.8      );    
  res &= test (  -2.2,	       PI,     -1.8     );    
  
  // Cases near zero
  res &= test (  .1,	.0000000004,	.5	 );    
  res &= test (  -1.2,  .0000000004,	.5	 );    
  res &= test (  .7,	.0000000004,	-.6	 );    
  res &= test (  1.5,	.0000000004,	-1.1	 );    
  res &= test (  1.4,	.0000000004,	-1.5	 );    
  res &= test (  -.1,	.0000000000028, .5	 );    
  res &= test (  -1.2,  .0000000000028, -.5	 );    
  res &= test (  .7,	.0000000000028, -.6	 );    
  res &= test (  -1.5,  .0000000000028, -1.1	 );    
  res &= test (  1.4,	.0000000000028, 1.5	 );    

  // Cases near PI
  double nearPI = PI - .00000002; 
  res &= test (  .1,	nearPI, 	 .5    );    
  res &= test (  -1.2,  nearPI, 	 .5    );    
  res &= test (  .7,	nearPI, 	-.6    );    
  res &= test (  1.5,	nearPI, 	-1.1   );    
  res &= test (  1.4,	nearPI, 	-1.5   );    
  res &= test (  2.4,	nearPI, 	-1.6   );    
  res &= test (  2.3,	nearPI, 	 1.9   );    
  res &= test ( -2.8,	nearPI, 	  .6   );    
  res &= test (  -.4,	nearPI, 	-3.1   );    
  nearPI = PI - .000000000009;   
  res &= test (   .1,	 nearPI,	 -.5	);    
  res &= test (   1.2,   nearPI,	 .5	);    
  res &= test (   .7,	 nearPI,	 -.6	);    
  res &= test (   1.5,   nearPI,	 1.1	);    
  res &= test (   -1.4,  nearPI,	 -1.5	);    
  res &= test (  2.1,	nearPI, 	-1.2    );    
  res &= test (  2.9,	nearPI, 	  .9    );    
  res &= test ( -2.8,	nearPI, 	 1.6    );    
  res &= test (  -.4,	nearPI, 	-3.0    );    
  
  if (!res) return -1;
  return 0;
}

bool compareR ( const HepRotation & r1, const HepRotation & r2, double tol ) {
  HepRep3x3 m1 = r1.rep3x3();
  HepRep3x3 m2 = r2.rep3x3();
  double flaw = 0;
  flaw = max (flaw, (m1.xx_ - m2.xx_));
  flaw = max (flaw, (m1.xy_ - m2.xy_));
  flaw = max (flaw, (m1.xz_ - m2.xz_));
  flaw = max (flaw, (m1.yx_ - m2.yx_));
  flaw = max (flaw, (m1.yy_ - m2.yy_));
  flaw = max (flaw, (m1.yz_ - m2.yz_));
  flaw = max (flaw, (m1.zx_ - m2.zx_));
  flaw = max (flaw, (m1.zy_ - m2.zy_));
  flaw = max (flaw, (m1.zz_ - m2.zz_));
  if (flaw > 20*std::sqrt(tol)) {
    cout << "???????? comparison flaw at level of " <<  flaw  << "\n"
         << r1 << r2;
  }
  cout << "flaw size is " << flaw << " (" << flaw/std::sqrt(tol) << ")\n\n";
  return (flaw <= tol);
}

void perturb ( int i, const HepRotation & r, HepRotation & rp, double & del ) {
  
  HepRep3x3 p0 (  1,  3, -2,
        	 -1, -2,  4, 
	          2, -1, -1  );

  HepRep3x3 p1 (  1, -1, -2,
                  1,  3, -1, 
	          2, -1, -3  );

  HepRep3x3 p2 (  5,  1, -5,
        	 -3, -2,  3, 
		 -1,  4, -1  );

  HepRep3x3 p3 ( -2, -2, 1,
        	 -1, -2, -4, 
	          4,  2, -2  );

  HepRep3x3 p[4];
  p[0] = p0;
  p[1] = p1;
  p[2] = p2;
  p[3] = p3;

  int cycle = i/4;
  double q;
  switch (cycle){
    case 0: q = 1.0e-14; break;
    case 1: q = 1.0e-12; break;
    case 2: q = 1.0e-10; break;
    case 3: q = 1.0e-8;  break;
    case 4: q = 1.0e-6;  break;
    case 5: q = 1.0e-4;  break;    
  }
  HepRep3x3 d = p[i%4];
  HepRep3x3 m = r.rep3x3();
  if ((m.zz_ + q*d.zz_) < -1) {
    d.zz_ = -d.zz_;
  }
  cout << "i = " << i << " q is " << q << "\n";
  rp.set (HepRep3x3 ( m.xx_ + q*d.xx_ , m.xy_ + q*d.xy_ , m.xz_ + q*d.xz_ ,
                      m.yx_ + q*d.yx_ , m.yy_ + q*d.yy_ , m.yz_ + q*d.yz_ ,
		      m.zx_ + q*d.zx_ , m.zy_ + q*d.zy_ , m.zz_ + q*d.zz_ ) );
  del = q;
}
