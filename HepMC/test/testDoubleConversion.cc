#include "CLHEP/HepMC/DoubleConversion.hh"

#include <sstream>
#include <iomanip>

// #define VERBOSE

#include <iostream>

int main() {
  using namespace HepMC;
  double t1 = 1.0;
#ifdef VERBOSE
  std::cout << "Hex representation of 1 is " 
  	<< DoubleConversion::d2x (t1) << "\n"; 
#endif
  if ( DoubleConversion::d2x (t1) != "3ff0000000000000" ) {
    std::cout << "d2x(double): Hex representation of 1.0 is " 
  	<< DoubleConversion::d2x (t1) << " which is incorrect\n"; 
    return 1;
  }
  unsigned long a1 = 0x40100000;
  unsigned long a2 = 0;
  std::vector<unsigned long> v;
  v.push_back(a1);
  v.push_back(a2);
  double d4 = DoubleConversion::longs2double(v);
#ifdef VERBOSE
  std::cout << "d4 (should be 4.0) is " << d4 << "\n";
#endif
  if (d4 != 4.0) {
    std::cout << "longs2double(v): double represented by 0x4010000000000000 is "
  	<< d4 << "\n                 which should be 4.0\n"; 
    return 2;  
  }    
  double x = 1.0;
  int t30 = 1 << 30;
  int t22 = 1 << 22;
  x *= t30;
  x *= t22;
  double y = 1;
  double z = .0625;
  x *= z;
  for (int k=0; k<6; k++) {
    x += y*z;
    y += 1;
    z *= 256;
  }
#ifdef VERBOSE
  std::cout << "Hex representation of x (should be 42f0060504030201) is " 
  	<< DoubleConversion::d2x (x) << "\n"; 
#endif
  if (DoubleConversion::d2x (x) != "42f0060504030201") {
    std::cout << "d2x(double): Hex representation of x2 is " 
  	<< DoubleConversion::d2x (x) 
	<< "\n                 which should be 42f0060504030201\n"; 
    return 3;
  }
  v = DoubleConversion::dto2longs(x);
#ifdef VERBOSE
  std::cout << "Longs representing x are " 
  	<< std::hex << v[0] << ", " << std::hex << v[1] << "\n";
#endif
  if (v.size() != 2) {
    std::cout << "dto2longs(double): Longs representing x are vector of size " 
  	<< v.size() <<  "\n";
    return 4;
  }
  if ( (v[0] != 0x42f00605ul) || (v[1] != 0x04030201ul) ) {
    std::cout << "dto2longs(double): Longs representing x are\n" 
  	      << "                   " 
	      << std::hex << v[0] << ", " << std::hex << v[1] << "\n"
	      << "        (should be 42f00605, 4030201\n";
    return 5;
  } 

  return 0;
}
