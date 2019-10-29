// This program tests the DEFECT_NO_EXCEPTIONS version of the Exceptions package:
//   12-Dec-2001  WEB  Avoid signed/unsigned comparison warnings

#ifndef DEFECT_NO_EXCEPTIONS
  #define DEFECT_NO_EXCEPTIONS 1
#endif


#include "CLHEP/Exceptions/ZMthrow.h"
#include "CLHEP/Exceptions/ZMexception.h"
#include "CLHEP/Exceptions/ZMerrno.h"
using namespace zmex;

#include <fstream>
using namespace std;


// We try to have this test program test several cases, including
// several actual throws, so we assume that the DEFECT_NO_EXCEPTIONS version of
// the ZMthrow macro will use exit() or abort() and so override
// those behaviors in order to keep going for multiple testing herein:
#include <stdio.h>
#define exit( x ) printf( "this is an actual exit\n", x );
#define abort(  ) printf( "this is an actual abort\n"  );


ZMexStandardDefinition( ZMexception, ZMxTop );
ZMexClassInfo ZMxTop::_classInfo( "ZMxTop", "HepTuple" );

ZMexStandardDefinition( ZMxTop, ZMxHepTuple );
ZMexClassInfo ZMxHepTuple::_classInfo( "ZMxHeptuple", "HepTuple" );

ZMexStandardDefinition( ZMexception, ZMxTop2 );
ZMexClassInfo ZMxTop2::_classInfo( "ZMxTop2", "Other Top Exception" );

ZMexStandardDefinition( ZMxTop2, ZMxHepTuple2 );
ZMexClassInfo ZMxHepTuple2::_classInfo( "ZMxHepTuple2", "Other HepTuple" );

ZMexStandardDefinition( ZMxHepTuple2, ZMxColumn );
ZMexClassInfo ZMxColumn::_classInfo( "ZMxColumn", "Column excep" );


int main (  ) {

  ZMxTop::setHandler( ZMexIgnoreAlways(  ) );
  ZMxHepTuple::setHandler( ZMexThrowAlways(  ) );

  printf( "Try to ignore a ZMxTop with msg -top-\n" );
  ZMthrow( ZMxTop( "top" ) );
  printf( "Try to throw a ZMxHepTuple with msg -bottom-\n" );
  ZMthrow( ZMxHepTuple( "bottom" ) );

  printf( "Try to throw a top exception with a ZMhParentHandler\n" );
  ZMthrow( ZMxTop2( "top2" ) );

  printf( "Try to throw a ZMxColumn\n" );
  ZMthrow( ZMxColumn( "a column error" ) );

  ZMxHepTuple2::setHandler( ZMexIgnoreNextN( 3 ) );

  std::ofstream logfile( "exception.report" );
  ZMxHepTuple2::setLogger( ZMexLogAlways( logfile ) );

  printf( "Try to throw a ZMxTop2\n" );
  ZMthrow( ZMxTop2( "top2" ) );

  printf( "Try to ignore a ZMxHepTuple2\n" );
  ZMthrow( ZMxHepTuple2( "a heptuple error" ) );

  //ZMxColumn::logNMore(  4  );
  printf( "Try to ignore a ZMxColumn\n" );
  ZMthrow( ZMxColumn( "2 column error" ) );
  printf( "Try to ignore a ZMxColumn\n" );
  ZMthrow( ZMxColumn( "3 column error" ) );
  printf( "Try to throw a ZMxColumn\n" );
  ZMthrow( ZMxColumn( "4 column error" ) );
  printf( "Try to throw a ZMxColumn\n" );
  ZMthrow( ZMxColumn( "5 column error" ) );

  std::cout << "logged the following exceptions\n";
  unsigned int s;
  for ( s = 0; s <  ZMerrno.size(  ); s++  ) {
    std::cout << ZMerrno.get( s )->name(  ) << " : " <<
		ZMerrno.get( s )->message(  ) << std::endl;
  }
  std::cout << "Reset the length of ZMerrno to 4\n";
  ZMerrno.setMax( 4 );
  for ( s = 0; s <  ZMerrno.size(  ); s++  ) {
    std::cout << ZMerrno.get( s )->name(  ) << " : " <<
		ZMerrno.get( s )->message(  ) << std::endl;
  }

  return 0;
}
