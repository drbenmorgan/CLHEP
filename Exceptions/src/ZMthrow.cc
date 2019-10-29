// ----------------------------------------------------------------------
//
// ZMthrow.cc -- implementation of ZMthrow
//
// ZMthrow_() is invoked by the ZMthrow(x) macro, which supplies the lineNum
// and file arguments as well as the constructed ZOOM exception object.
//
// Revision History:
//	970910	MF	Initial version
//	970916	WEB	Updated per code review
//	970917	WEB	Updated per code review 2
//	980615	WEB	Added namespace support
//
// ----------------------------------------------------------------------


#include "CLHEP/Exceptions/ZMthrow.h"
#include "CLHEP/Exceptions/ZMexSeverity.h"
#include "CLHEP/Exceptions/ZMexception.h"
#include "CLHEP/Exceptions/ZMerrno.h"


namespace zmex  {



//**********************
//
// ZMthrow_ ()
//
//**********************

ZMexAction ZMthrow_(
  const ZMexception & userException
, int                 lineNum
, const char          fileName[]
)  {

  // a) Place the lineNum and fileName information into the exception object.

  // b) Cause the handler to be invoked via x.X::handleMe().
  //    That finds the handler, puts the handler name into the exception,
  //    and invokes the handler's takeCareOf() method, passing it the
  //    exception object so that, if any parent handlers are involved,
  //    you later have x.Y::handleMe() invoked, where Y is an ancestor of X.

  // c) If the exception is of severity ZMexERROR or higher, copy the
  //    exception object onto ZMerrno.

  // d) Return the result of the handler's decision.

  // The following are done elsewhere, so ZMthrow_ does not have to:
  //   The constructor for ZMexception takes care of incrementing
  //     the static count, and saving its value.
  //   The handler notifies the exception object of the handler's
  //     decision whether to have the object be thrown or ignored.
  //   Identifying the logger to call, and saving that information,
  //     in this exception instance, is done by x.logMe()
  //     called by handler, assuming the handler decides to log.

  userException.location( lineNum, fileName );		// (a)

  ZMexAction whatToDo = userException.handleMe();	// (b)

  if ( userException.severity() >= ZMexERROR )		// (c)
    ZMerrno.write( userException );

  return whatToDo;					// (d)

}  // ZMthrow_()

}  // namespace zmex
