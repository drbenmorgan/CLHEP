// ----------------------------------------------------------------------
//
// ZMexHandler.cc -- implementations for the standard handlers.
//
//
// The following methods are defined here:
//    standardHandling( ZMexception & x, bool willThrow )
//    ZMexThrowErrors::takeCareOf()
//
// Revision History:
//	970923	PhilC	Initial version
//	971113  WEB	Updated to conform to standard coding techniques
//	980615	WEB	Added namespace support
//
// ----------------------------------------------------------------------


#include "CLHEP/Exceptions/ZMexHandler.h"

#include "CLHEP/Exceptions/ZMexception.h"


namespace zmex  {


//******************************************
//
// standardHandling( ZMexception & x, bool willThrow )
// provides functionality common to many (most?) handlers:
//   record the handler's name
//   record (via x.wasThrown() ) the determined action
//   obtain permission, from the exception, to log;
//     if granted, invoke the exception's logger
//   return the determined action
//
//******************************************

ZMexAction
ZMexHandlerBehavior::
standardHandling( const ZMexception & x, bool willThrow )  {

  x.handlerUsed( name() );		// record handler's name
  x.wasThrown( willThrow );		// record go/nogo decision

  int & val = ZMexSeverityLimit[ x.severity() ];

  if ( x.OKtoLog()  &&  val != 0 )	// handle logging, if desired
    if ( x.logMe() == ZMexLOGGED  &&  val > 0 )
      --val;

  return  willThrow ? ZMexThrowIt
		    : ZMexIgnoreIt;
}


//*******************************
//
// ZMexThrowErrors::takeCareOf()
//
//*******************************

ZMexAction
ZMexThrowErrors::
takeCareOf( const ZMexception & x ) {
  //DEBUG  cerr << "ThrowErrors::takeCareOf" << endl;
  return standardHandling( x, ( x.severity() >= ZMexERROR ) ? true
                                                            : false
                         );
}


}  // namespace zmex
