// ----------------------------------------------------------------------
//
// testThrowFrom.cc - test the ZMthrow_from() method,
//                    and the ZMexValidationStyle behavior,
//                    and setName, setSeverity, setFacility.
//
// History:
//   10-Apr-2001  mf   Initial draft testing just ZMthrow_from()
//   11-Apr-2001  mf   Test the other enhancements.
//   12-Jun-2002  web  Insert conditional try-catch to allow testing in
//     presence of true exceptions
//
// ----------------------------------------------------------------------

#include "CLHEP/Exceptions/ZMthrow.h"
#include "CLHEP/Exceptions/ZMexception.h"

using namespace zmex;

ZMexStandardDefinition( ZMexception, ZMxTest );
ZMexClassInfo ZMxTest::_classInfo(
  "ZMxTest", "Test", ZMexSEVERE );

int main()  {

//  std::cout << "starting...\n";


// Not:      ZMexception::setHandler( ZMexIgnoreAlways() ) ;
// Instead:
  ZMxTest::setSeverity( ZMexWARNING ); // Which should not abort

  ZMexception::setLogger( ZMexValidationStyle(std::cout) ) ;

//  std::cout << "throwing...\n";

  ZMthrow_from( ZMxTest("Artificial Exception"), 1000,
                "directory/subdirectory/fictitious.file" );

  ZMthrow_from( ZMxTest("Artificial backslash Exception"), 4000,
                "directory/subdirectory\\fictitious.file" );

  ZMthrow_from( ZMxTest("Artificial no slash Exception"), 4000,
                "fictitious.file" );

  ZMthrow( ZMxTest("Normal exception") );

  ZMxTest::setName("MyExName");
  ZMthrow( ZMxTest("Exception with new name") );

  ZMxTest::setFacility("newFacility");
  ZMthrow( ZMxTest("Exception from new facility") );

  // -------------
  // Done, go home
  // -------------

  ZMexception::setLogger( ZMexLogAlways(std::cout) ) ;

  ZMxTest::setSeverity( ZMexERROR ); // Which should not abort
#ifndef DEFECT_NO_EXCEPTIONS
  try {
#endif
    ZMthrow( ZMxTest("Ordinary Error") );
#ifndef DEFECT_NO_EXCEPTIONS
  }
  catch( ZMexception & e )  {
    std::cerr << "Caught: " << e.name() << "\n";
  }
#endif

  return 0;

}  // main()
