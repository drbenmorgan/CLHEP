// ----------------------------------------------------------------------
//
// testzmex.cc - test whether namespaces work out.
//
// History:
//	04/13/01 mf	wrote
//
//
// usage:  Place into src and test makefile
// override CPPFLAGS += -DZM_USE_NAMESPACES
// and build.
// ----------------------------------------------------------------------



#include <string>
  using std::string;

#include "CLHEP/Cast/itos.h"

#include "CLHEP/Exceptions/ZMthrow.h"
#include "CLHEP/Exceptions/ZMexception.h"
#include "CLHEP/Exceptions/ZMerrno.h"


// remove the above line to test with namespace on.

// ----------
// Define exception classes and default behaviors:
// ----------

ZMexStandardDefinition( zmex::ZMexception, ZMxTest );
zmex::ZMexClassInfo ZMxTest::_classInfo(
  "ZMxTest", "Test", zmex::ZMexSEVERE );


// ----------
// Define output formats, etc
// ----------

const string QUOTE    = "\"";
const string NEWLINE1 = "\n";
const string NEWLINE2 = "\n\n";

void display( const zmex::ZMexception * ex )  {

  zmex::ZMlogger().emit( NEWLINE1
               + ex->name() + ": " + QUOTE + ex->message() + QUOTE + NEWLINE1
               + "  " + (ex->wasThrown() ? "thrown" : "ignored")
               + " by " + ex->handlerUsed() + "()" + NEWLINE1
               );

}


int main()  {

  // ----------
  // Begin testing, check out basic logger:
  // ----------
  zmex::ZMlogger().emit( NEWLINE1 );
  zmex::ZMlogger().emit( "----------  Begin testing:  ----------\n" );
  zmex::ZMlogger().emit( NEWLINE1 );
  zmex::ZMlogger().emit( "This message checks out basic logger behavior\n" );

  ZMthrow( ZMxTest( "Testing exception behavior" ) );

  // ----------
  // Done, go home
  // ----------
  return 0;

}  // main()
