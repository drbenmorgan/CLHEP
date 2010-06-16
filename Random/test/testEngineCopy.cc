// -*- C++ -*-
// $Id: testEngineCopy.cc,v 1.2 2010/06/16 17:24:53 garren Exp $
// ----------------------------------------------------------------------
#include "CLHEP/Random/Randomize.h"
#include "CLHEP/Random/NonRandomEngine.h"
#include "CLHEP/Random/defs.h"
#include <iostream>
#include <iomanip>
#include <vector>

#define CLEAN_OUTPUT
#ifdef CLEAN_OUTPUT
  std::ofstream output("testEngineCopy.cout");  
#else
  std::ostream & output = std::cout;
#endif

// Normally on  for routine validation:

#ifdef TURNOFF
#endif

#define TEST_ENGINE_COPY

#define VERBOSER
#define VERBOSER2

using namespace CLHEP;

// Absolutely Safe Equals Without Registers Screwing Us Up
bool equals01(const std::vector<double> &ab) {
  return ab[1]==ab[0];
}  
bool equals(double a, double b) {
  std::vector<double> ab(2);
  ab[0]=a;  ab[1]=b;
  return (equals01(ab));
}

std::vector<double> aSequence(int n) {
  std::vector<double> v;
  DualRand e(13542);
  RandFlat f(e);
  for (int i=0; i<n; i++) {
    v.push_back(f()); 
  }
  return v;
}


// ----------- Copy of engines -----------

template <class E>
int vectorTest64(int n) {
  output << "Copy 64bit test for " << E::engineName() << "\n";

  E e;				    
  double x = 0;	
  for (int i=0; i<n; i++) x += e.flat();	    
  E f( e );
  x = e.flat();
  output << "x = " << x << std::endl;

  double y = f.flat();
  output << "y = " << y << std::endl;
  if( x != y ) return n;
  
  for( int i=0; i<1000; ++i ) {
      x = e.flat();
      y = f.flat();
      if( !equals(x,y) ) {
          output << "i = " << i << " x, y " << x << " " << y
	         << " vectorTest64 problem: e != f \n";
	  return n+i;
      }
  }

  return 0;
}
// special case for NonRandomEngine
template <>
int vectorTest64<NonRandomEngine>(int n) {
  output << "Copy 64bit test for " << NonRandomEngine::engineName() << "\n";

  std::vector<double> nonRand = aSequence(500);
  NonRandomEngine e; 
  e.setRandomSequence(&nonRand[0], nonRand.size());

  double x = 0;	
  for (int i=0; i<n; i++) x += e.flat();	    
  std::vector<unsigned long> v = e.put();
  NonRandomEngine f(e);
  x = e.flat();
  output << "x = " << x << std::endl;

  double y = f.flat();
  output << "y = " << y << std::endl;
  if( x != y ) return n;
  
  for( int i=0; i<300; ++i ) {
      if( e.flat() != f.flat() ) {
          output << "i = " << i << " vectorTest64 for NonRandomEngine problem: e != f \n";
	  return n+i;
      }
  }

  return 0;
}

template <class E>
E vectorRestore1(int n, std::vector<double> & v) {
  output << "Copy for " << E::engineName() << "\n";
  E e(97538466);				    
  double r=0;					    
  for (int i=0; i<n; i++) r += e.flat();	    
  E f(e);    
  for (int j=0; j<25; j++) v.push_back(e.flat());   
#ifdef VERBOSER2
  output << "First four of v are: " 
    	<< v[0] << ",  " << v[1] << ",  " << v[2] << ",  " << v[3] << "\n";
#endif
  return f;
}

template <>
NonRandomEngine
vectorRestore1<NonRandomEngine> (int n, std::vector<double> & v) {
#ifdef VERBOSER2
  output << "Copy for " << NonRandomEngine::engineName() << "\n";
#endif
  std::vector<double> nonRand = aSequence(500);
  NonRandomEngine e; 
  e.setRandomSequence(&nonRand[0], nonRand.size());
  double r=0;
  for (int i=0; i<n; i++) r += e.flat();
  NonRandomEngine f(e);
  for (int j=0; j<25; j++) v.push_back(e.flat()); 
#ifdef VERBOSER2
  output << "First four of v are: " 
    	<< v[0] << ",  " << v[1] << ",  " << v[2] << ",  " << v[3] << "\n";
#endif
  return f;
}

template <class E>
int vectorRestore2(E & f, const std::vector<double> & v) {
  int stat = 0;
  std::vector<double> k;
  for (int j=0; j<25; j++) k.push_back(f.flat());
#ifdef VERBOSER2
  output << "First four of k are: " 
    	<< k[0] << ",  " << k[1] << ",  " << k[2] << ",  " << k[3] << "\n";
#endif
  for (int m=0; m<25; m++) {
    if ( v[m] != k[m] ) {
      std::cout << "???? Incorrect copy restored value for engine: " 
    		<< E::engineName() << "\n"; 
      #ifdef CLEAN_OUTPUT
      output << "???? Incorrect copy restored value for engine: " 
    		<< E::engineName() << "\n"; 
      #endif
      stat |= 1048576;
      return stat;
    }
  }
  return stat;       
}


template <class E>
int vectorRestore(int n) {
  std::vector<double> v;
  int status1 = vectorTest64<E>(n);
  E f = vectorRestore1<E>(n,v);
  int status2 = vectorRestore2<E>(f, v);  
  return (status1 | status2);  
}



// ---------------------------------------------
// ---------------------------------------------
// ---------------------------------------------


int main() {
  int stat = 0;

#ifdef TEST_ENGINE_COPY
  output << "\n=================================\n";
  output << "         Part IX \n";
  output << "    Copy test of engines\n";
  output << "=================================\n\n";

  stat |= vectorRestore<DualRand>(113);
  // copies of DRand48Engine are not allowed
  //stat |= vectorRestore<DRand48Engine>(114);
  stat |= vectorRestore<Hurd160Engine>(115);
  stat |= vectorRestore<Hurd288Engine>(116);
  stat |= vectorRestore<HepJamesRandom>(117);
  stat |= vectorRestore<MTwistEngine>(118);
  stat |= vectorRestore<RanecuEngine>(139);
  stat |= vectorRestore<Ranlux64Engine>(119);
  stat |= vectorRestore<RanluxEngine>(120);
  stat |= vectorRestore<RanshiEngine>(121);
  stat |= vectorRestore<TripleRand>(122);
  stat |= vectorRestore<NonRandomEngine>(123);
  // anonymous engines are not copyable
  //stat |= vectorRestore<RandEngine>(129);
#endif

  output << "\n=============================================\n\n";

  if (stat != 0) {
     std::cout << "One or more problems detected: stat = " << stat << "\n";
     output << "One or more problems detected: stat = " << stat << "\n";
  }  else {
     output << "ranRestoreTest passed with no problems detected.\n";    
  }

  if (stat == 0) return 0;
  if (stat > 0) return -(stat|1);
  return stat|1;
}	

