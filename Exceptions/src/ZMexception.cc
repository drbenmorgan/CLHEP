// ----------------------------------------------------------------------
//
// ZMexception.cc -- implementation of the ZMexception class
//
// Methods found here:
// 	handleThis(x)
// 	logMessage()
//
// Revision History:
//      970912  MF	Initial version after separating .icc from .cc
//      970916  WEB	Updated per code review
//      970917  WEB	Updated per code review 2
//      970918  WEB	Updated per code review 3
//	971113  WEB	Updated to conform to standard coding techniques
//	971211	WEB	Updated per code walkthrough
//	971215	WEB	Gave names to the default handler & logger
//	971217	WEB	Append filter failure messages in logMessage()
//	971219	WEB	Append newline to formatted messages
//	980213	WEB	Include ZMutility/ZMtime.h instead of <ctime>
//	980223	WEB	Include ZMutility/ctime instead of ZMtime
//	980304	WEB	Reformat logged messages to avoid excessively
//			long lines; otherwise cleaned up logMessage() &
//                      related stuff
//      980421  WEB     Moved name() and facility() from .icc to .cc
//	980615	WEB	Added namespace support
//	000217	WEB	Improve C++ standards compliance
//	010410	MF	Added code to supress time and file path
//	010626	MF	Added code for ctor from ostringstream
//	031105	LG	Get rid of all ZMutility references
//
// ----------------------------------------------------------------------


#include "CLHEP/Exceptions/defs.h"
#include "CLHEP/Exceptions/ZMexception.h"
#include "CLHEP/Exceptions/ZMexAction.h"
#include "CLHEP/Exceptions/ZMexHandler.h"
#include "CLHEP/Exceptions/ZMexLogger.h"
#include "CLHEP/Exceptions/ZMexLogResult.h"

#include <sstream>
#include <ctime>


namespace zmex  {

// **************************************
//
// ZMexUserActivity, ZMexUserNumericalTag
//
// **************************************

std::string ZMexUserActivity = "";
int ZMexUserNumericalTag = 0;


// *******************
//
// ZMhandler, ZMlogger
//
// *******************

ZMexHandler &  ZMhandler()  {
  static ZMexHandler ZMhandler = ZMexHandler( ZMexThrowErrors() );
  return ZMhandler;
}  // ZMhandler()

ZMexLogger &  ZMlogger()  {
  static ZMexLogger ZMlogger = ZMexLogger(  ZMexLogAlways() );
  return  ZMlogger;
}


// ***********************
//
// ZMexception::_classInfo
//
// ***********************

ZMexClassInfo  ZMexception::_classInfo(
  "ZMexception"
, "Exceptions"
, ZMexFATAL
, ZMhandler()
, ZMlogger()
);


// ***********************
// ZMexception::facility()
// ***********************

std::string ZMexception::facility() const {

  return  classInfo().facility();

}  // ZMexception::facility()


// *******************
// ZMexception::name()
// *******************

std::string ZMexception::name() const {

  return  classInfo().name();

}  // ZMexception::name()


//*************
// logMessage()
//*************

// This will be overridden in cases where, for a particular exception,
// one wishes to include auxiliary information with the logged message.
// The overriding function should compose its string, then call this
// (its ancestor) function with that string as argument.

std::string ZMexception::logMessage( const std::string optText ) const {

  std::ostringstream mesg;

  // define how each follow-on line should begin:
  #define NEXT "\n  "

  // Supply the exception's identification as the first line:
  mesg << facility()
       << "-" << ZMexSeverityLetter[ severity() ]
       << "-" << name() << " [#" << count() << "]";

  // Second line gives the exception instance's message
  mesg << NEXT << message();

  // Warn if this exception hits the max for its severity:
  if ( 1 == ZMexSeverityLimit[ severity() ] )
    mesg << NEXT "-- Note:  severity threshhold has been reached; "
	    "logging will be suppressed "
	    "for any future exceptions of this severity";

  // Warn if this exception hits the max for its class:
  if ( classInfo().count() == classInfo().filterMax() )
    mesg << NEXT "-- Note:  class threshhold has been reached; "
	    "logging will be suppressed "
	    "for any future exceptions of this class";

  // Insert optional text (probably from override calling this as its ancestor):
  if ( optText.length() )
    mesg << NEXT << optText;

  // Insert time stamp:
  ZMexLogger lgr = getLogger();
  if ( lgr.control()->isTimeDesired() ) {
    time_t now( time(0) );
    char * timeText = ctime( & now );
    timeText[24] = '\0';  // overwrite terminal '\n'
    mesg << NEXT << timeText;
  }

  // Identify whence we got here:
  mesg << NEXT "-- ZMthrow was issued at line " << line();
  std::string fullName = fileName();
  std::string fname;
  if ( lgr.control()->isFilePathDesired() ) {
    fname = fullName;
  } else {
    unsigned int lastSlash = fullName.find_last_of("/\\");
    if ( lastSlash == fullName.length() ) {
      fname = fullName;
    } else {
      fname = fullName.substr(lastSlash+1);
    }
  }
  mesg << NEXT "of file \"" << fname << '\"';

  // Identify disposition:
  mesg << NEXT "... Exception " << ( wasThrown() ? "thrown!"
			                         : "ignored"
				   );

  // Include optional user information, part 1:
  if ( ZMexUserActivity.length() )
    mesg << NEXT "-- ZMexUserActivity was: " << ZMexUserActivity;

  // Include optional user information, part 2:
  if ( ZMexUserNumericalTag )
    mesg << NEXT "-- User Numerical Tag was: " << ZMexUserNumericalTag;

  return  mesg.str() + '\n';

}  // ZMexception::logMessage()

//***********************************************
// Constructor of ZMexception from ostringstream&
//***********************************************

ZMexception::ZMexception(
  const std::ostringstream &  msg
, const ZMexSeverity howBad
, int                icount
)  :
  message_(msg.str())
, line_( 0 )
, sourceFileName_( "not ZMthrow'n as of yet" )
, mySeverity_( howBad == ZMexSEVERITYenumLAST ? _classInfo.severity() : howBad )
, myCount_( icount )
, wasThrown_( false )
{ }

}  // namespace zmex
