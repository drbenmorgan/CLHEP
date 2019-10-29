// ----------------------------------------------------------------------
//
// testExceptions.cc - test the DEFECT_NO_EXCEPTIONS version of the Exceptions package
//
// History:
//   19-Dec-1997  WEB  Initial draft; redefining exit() based on an idea
//     by Philippe Canal
//   04-Mar-1998  WEB  Minor grammar update
//   15-Jun-1998  WEB  Added namespace support
//   26-Jun-2001  MF   Tested ctor of ZMexception from ostringstream
//   12-Dec-2001  WEB  Avoid signed/unsigned comparison warnings
//   12-Jun-2002  WEB  Rearrange to ensure correct ZMthrow definition
//
// ----------------------------------------------------------------------

#include <sstream>
#include <string>
  using std::string;

#include "CLHEP/Exceptions/defs.h"
#include "CLHEP/Cast/itos.h"
#include "CLHEP/Exceptions/ZMthrow.h"
#include "CLHEP/Exceptions/ZMexception.h"
#include "CLHEP/Exceptions/ZMerrno.h"


using namespace zmex;

// ----------
// In case our compilation environment does not support exceptions:
//
//   Since this program tests several cases, including several actual throws,
//   we assume that the DEFECT_NO_EXCEPTIONS version of the ZMthrow macro
//   will use abort() and so override abort()'s behavior in order to keep
//   going for multiple testing herein:  (earlier we used exit(), which we
//   also overide)
// ----------

#ifdef DEFECT_NO_EXCEPTIONS

#define exit( x )  \
  ZMlogger().emit( "Note:  exception would have been correctly thrown here\n" );

#define abort()  \
  ZMlogger().emit( "Note:  exception would have been correctly thrown here\n" );

#endif  // DEFECT_NO_EXCEPTIONS


// ----------
// Define exception classes and default behaviors:
// ----------

ZMexStandardDefinition( ZMexception, ZMxTest );
ZMexClassInfo ZMxTest::_classInfo(
  "ZMxTest", "Test", ZMexSEVERE );

ZMexStandardDefinition( ZMxTest, ZMxInfo );
ZMexClassInfo ZMxInfo::_classInfo(
  "ZMxInfo", "Test", ZMexINFO );

ZMexStandardDefinition( ZMxTest, ZMxGoof );
ZMexClassInfo ZMxGoof::_classInfo(
  "ZMxGoof", "Test", ZMexERROR );

ZMexStandardDefinition( ZMxGoof, ZMxOops );
ZMexClassInfo ZMxOops::_classInfo(
  "ZMxOops", "Test", ZMexWARNING );

ZMexStandardDefinition( ZMxGoof, ZMxBooBoo );
ZMexClassInfo ZMxBooBoo::_classInfo(
  "ZMxBooBoo", "Test", ZMexFATAL, ZMexIgnoreAlways() );


// ----------
// Define output formats, etc
// ----------

const string QUOTE    = "\"";
const string NEWLINE1 = "\n";
const string NEWLINE2 = "\n\n";

void display( const ZMexception * ex )  {

  ZMlogger().emit( NEWLINE1
		 + ex->name() + ": " + QUOTE + ex->message() + QUOTE + NEWLINE1
		 + "  " + (ex->wasThrown() ? "thrown" : "ignored")
		 + " by " + ex->handlerUsed() + "()" + NEWLINE1
		 );

}


int main()  {
  unsigned int k;

  // ----------
  // Begin testing, check out basic logger:
  // ----------
  ZMlogger().emit( NEWLINE1 );
  ZMlogger().emit( "----------  Begin testing:  ----------\n" );
  ZMlogger().emit( NEWLINE1 );
  ZMlogger().emit( "This message checks out basic logger behavior\n" );


  // ----------
  // Test default informational behavior:
  // ----------
  ZMlogger().emit( NEWLINE2 );
  ZMlogger().emit(
    "----------  Testing default informational behavior:  ----------\n" );
  ZMlogger().emit( NEWLINE1 );
  ZMthrow( ZMxInfo( "Testing default informational exception behavior" ) );

  // ----------
  // Test default informational behavior using an ostringstream
  // ----------

  ZMlogger().emit( NEWLINE2 );
  ZMlogger().emit(
  "----------  Testing default ostringstream behavior 3 times:  ----------\n" );
  std::ostringstream oss;
  oss << "Accumulated numbers are ";
  for ( k = 0;  k < 3;  ++k )  {
    ZMlogger().emit( NEWLINE1 );
    if ( k > 0 )
      oss << ", ";
    oss << k;
    ZMthrow( ZMxOops( oss ) );
  }

  // ----------
  // Test default ignoring behavior 3 times:
  // ----------
  ZMlogger().emit( NEWLINE2 );
  ZMlogger().emit(
    "----------  Testing default ignoring behavior 3 times:  ----------\n" );
  for ( k = 0;  k < 3;  ++k )  {
    ZMlogger().emit( NEWLINE1 );
    string testMesg = "Testing default exception ignoring behavior #";
    ZMthrow( ZMxOops( testMesg + itos(k+1) ) );
  }


  // ----------
  // Test defined ignoring behavior 3 times:
  // ----------
  ZMlogger().emit( NEWLINE2 );
  ZMlogger().emit(
    "----------  Testing defined ignoring behavior 3 times:  ----------\n" );
  for ( k = 0;  k < 3;  ++k )  {
    ZMlogger().emit( NEWLINE1 );
    string testMesg = "Testing defined exception ignoring behavior #";
    ZMthrow( ZMxBooBoo( testMesg + itos(k+1) ) );
  }

  // ----------
  // Test default throwing behavior 3 times:
  // ----------
  ZMlogger().emit( NEWLINE2 );
  ZMlogger().emit(
    "----------  Testing default throwing behavior 3 times:  ----------\n" );
  for ( k = 0;  k < 3;  ++k )  {
    ZMlogger().emit( NEWLINE1 );
    string testMesg = "Testing default exception throwing behavior #";
#ifndef DEFECT_NO_EXCEPTIONS
    try  {
#endif
      ZMthrow( ZMxGoof( testMesg + itos(k+1) ) );
#ifndef DEFECT_NO_EXCEPTIONS
    }
    catch ( ZMexception & e )  {
      std::cerr << "Caught: " << e.name() << "\n";
    }
#endif
  }


  // ----------
  // Test forced throwing behavior 3 times:
  // ----------
  ZMlogger().emit( NEWLINE2 );
  ZMlogger().emit(
    "----------  Testing forced throwing behavior 3 times:  ----------\n" );
  ZMxBooBoo::setHandler( ZMexThrowAlways() );
  for ( k = 0;  k < 3;  ++k )  {
    ZMlogger().emit( NEWLINE1 );
    string testMesg = "Testing forced exception throwing behavior #";
#ifndef DEFECT_NO_EXCEPTIONS
    try  {
#endif
      ZMthrow( ZMxBooBoo( testMesg + itos(k+1) ) );
#ifndef DEFECT_NO_EXCEPTIONS
    }
    catch ( ZMexception & e )  {
      std::cerr << "Caught: " << e.name() << "\n";
    }
#endif
  }

  // ----------
  // Test scheduled throwing behavior 3 times:
  // ----------
  ZMlogger().emit( NEWLINE2 );
  ZMlogger().emit(
    "----------  Testing scheduled throwing behavior 3 times:  ----------\n" );
  ZMxBooBoo::setHandler( ZMexIgnoreNextN( 2 ) );
  for ( k = 0;  k < 3;  ++k )  {
    ZMlogger().emit( NEWLINE1 );
    string testMesg = "Testing scheduled exception throwing behavior #";
#ifndef DEFECT_NO_EXCEPTIONS
    try  {
#endif
      ZMthrow( ZMxBooBoo( testMesg + itos(k+1) ) );
#ifndef DEFECT_NO_EXCEPTIONS
    }
    catch ( ZMexception & e )  {
      std::cerr << "Caught: " << e.name() << "\n";
    }
#endif
  }


  //ZMxColumn::logNMore(  4  );


  // ----------
  // Test exception history:
  // ----------
  ZMlogger().emit( NEWLINE2 );
  ZMlogger().emit( "---------- Test exception history:  ----------\n" );

  ZMlogger().emit( NEWLINE1 );
  ZMlogger().emit( string( "The following " )
                 + itos( ZMerrno.size() )
                 + " exceptions were recorded (most recent first):\n"
                 );
  for ( k = 0;  k <  ZMerrno.size();  ++k  )
    display( ZMerrno.get( k ) );

  const int NEWMAX = 4;
  ZMerrno.setMax( NEWMAX );
  ZMlogger().emit( NEWLINE1 );
  ZMlogger().emit( string("ZMerrno.setMax( ")
                 + itos( NEWMAX )
                 + " );"
                 );

  ZMlogger().emit( string( " we now have record of these " )
                 + itos(ZMerrno.size())
                 + " exceptions:\n"
                 );
  for ( k = 0;  k <  ZMerrno.size();  ++k  )
    display( ZMerrno.get( k ) );

  // ----------
  // Done, go home
  // ----------
  return 0;

}  // main()
