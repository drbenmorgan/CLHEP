// ----------------------------------------------------------------------
//
// ZMexLogger.cc - define basic logging behaviors
//
// History:
//	970919	WEB	Created based on code review 4 comments on
//			ZMexLogger behavior desired
//	971007	WEB	Removed limiting logger; all loggers now
//			optionally limit by exception severity
//	971211	WEB	Updated per code walkthrough
//	971211	WEB	Created from ZMexLogger.icc per code walkthrough
//	971215  WEB	Removed unused 2nd parm to ZMexLogger constructor
//	971219	WEB	Use std::flush instead of endl in ...::emit()
//	980617	WEB	Added namespace support
//	990104  WEB	Merged with .icc; restructured os data member
//                      ownership
//      990802  JVR     Added support for augmented exception logging
//      010410  MF      Added ZMexValidationStyle
//
// ----------------------------------------------------------------------


#include "CLHEP/Exceptions/ZMexLogger.h"
#include "CLHEP/Exceptions/ZMexception.h"


// ----------------------------------------------------------------------


namespace zmex  {


// ----------------------------------------------------------------------


// -----------------
// ZMexLogBehavior::
// -----------------

ZMexLogBehavior::ZMexLogBehavior()  { ; }

ZMexLogBehavior::~ZMexLogBehavior()  { ; }

ZMexLogBehavior *
ZMexLogBehavior::clone() const  { return  new ZMexLogBehavior( *this ); }

ZMexLogResult  ZMexLogBehavior::emit( const ZMexception & )  {
  return ZMexNOTLOGGED;
}

ZMexLogResult  ZMexLogBehavior::emit(
  const std::string &
)  {
  //DEBUG  cerr << "ZMexLogBehavior::emit()" << endl;

  // Do nothing with string& (but do it well!):
  return ZMexNOTLOGGED;
}

bool ZMexLogBehavior::isTimeDesired()     const { return true; }
bool ZMexLogBehavior::isFilePathDesired() const { return true; }

// --------------
// ZMexLogNever::
// --------------

ZMexLogNever::ZMexLogNever()
: ZMexLogBehavior()
{ ; }

ZMexLogNever::~ZMexLogNever()  { ; }

ZMexLogNever *
ZMexLogNever::clone() const  { return  new ZMexLogNever( *this ); }

ZMexLogResult  ZMexLogNever::emit( const ZMexception & )  {
  return  ZMexNOTLOGGED;                                                  //
}

ZMexLogResult  ZMexLogNever::emit(
  const std::string &
)  {
  //DEBUG  cerr << "ZMexLogNever::emit()" << endl;

  // Do nothing with string& (but do it well!):
  return ZMexNOTLOGGED;
}


// ---------------
// ZMexLogAlways::
// ---------------

ZMexLogAlways::ZMexLogAlways( )
: ZMexLogBehavior()
, myOs( std::cerr )
{ ; }

ZMexLogAlways::ZMexLogAlways( std::ostream & os )
: ZMexLogBehavior()
, myOs( os )
{ ; }

ZMexLogAlways::~ZMexLogAlways()  { ; }

ZMexLogAlways *
ZMexLogAlways::clone() const  { return  new ZMexLogAlways( *this ); }

ZMexLogResult  ZMexLogAlways::emit( const ZMexception & x )  {
  std::string s = x.logMessage();                                       //
  if ( s != "" )
    return  emit( s );

  x.logObject();
  return ZMexLOGGED;
}

ZMexLogResult  ZMexLogAlways::emit(
  const std::string & s
)  {
  //DEBUG  cerr << "ZMexLogAlways::emit( \"" << s << "\" )" << endl;

  // Emit the message, flushing the output right away:
  myOs << s << std::flush;
  return  ZMexLOGGED;
}

// ---------------
// ZMexLogTwice::
// ---------------

ZMexLogTwice::ZMexLogTwice( std::ostream & os1 )
: ZMexLogBehavior()
, myOs1( os1 )
, myOs2( std::cerr )
{ ; }

ZMexLogTwice::ZMexLogTwice( std::ostream & os1, std::ostream & os2 )
: ZMexLogBehavior()
, myOs1( os1 )
, myOs2( os2 )
{ ; }

ZMexLogTwice::~ZMexLogTwice()  { ; }

ZMexLogTwice *
ZMexLogTwice::clone() const  { return  new ZMexLogTwice( *this ); }

ZMexLogResult  ZMexLogTwice::emit( const ZMexception & x )  {
  std::string s = x.logMessage();
  if (s != "")
    return  emit( s );

  std::cerr << "WARNING: ZMexLogTwice() does not log in the usual manner for";
  std::cerr << " SuperEx's.\n\t Its ostreams may not have received logs.\n";
  x.logObject();
  return ZMexLOGGED;
}

ZMexLogResult  ZMexLogTwice::emit(
  const std::string & s
)  {
  //DEBUG  cerr << "ZMexLogTwice::emit( \"" << s << "\" )" << endl;

  // Emit the message, flushing the output right away:
  myOs1 << s << std::flush;
  myOs2 << s << std::flush;
  return  ZMexLOGGED;
}


// ------------------
// ZMexLogViaParent::
// ------------------

ZMexLogViaParent::ZMexLogViaParent()
: ZMexLogBehavior()
{ ; }

ZMexLogViaParent::~ZMexLogViaParent()  { ; }

ZMexLogViaParent *
ZMexLogViaParent::clone() const  { return  new ZMexLogViaParent( *this ); }

ZMexLogResult  ZMexLogViaParent::emit( const ZMexception & )  {
  return  ZMexLOGVIAPARENT;                                                 //
}

ZMexLogResult  ZMexLogViaParent::emit( const std::string & )  {
  //DEBUG  cerr << "ZMexLogViaParent::emit( \"" << s << "\" )" << endl;

  // Bump logging decisions to someone else's logger:
  return ZMexLOGVIAPARENT;
}


// ------------------
// ZMexValidationStyle::
// ------------------

ZMexValidationStyle::ZMexValidationStyle( )
: ZMexLogBehavior()
, myOs( std::cerr )
{ ; }

ZMexValidationStyle::ZMexValidationStyle( std::ostream & os )
: ZMexLogBehavior()
, myOs( os )
{ ; }

ZMexValidationStyle::~ZMexValidationStyle()  { ; }

ZMexValidationStyle *
ZMexValidationStyle::clone() const { return  new ZMexValidationStyle( *this ); }

ZMexLogResult  ZMexValidationStyle::emit( const ZMexception & x )  {
  std::string s = x.logMessage();  
  if ( s != "" )
    return  emit( s );

  x.logObject();
  return ZMexLOGGED;
}

ZMexLogResult  ZMexValidationStyle::emit(
  const std::string & s
)  {
  //DEBUG  cerr << "ZMexValidationStyle::emit( \"" << s << "\" )" << endl;

  // Emit the message, flushing the output right away:
  myOs << s << std::flush;
  return  ZMexLOGGED;
}

bool ZMexValidationStyle::isTimeDesired()     const { return false; }
bool ZMexValidationStyle::isFilePathDesired() const { return false; }

// ------------
// ZMexLogger::
// ------------

ZMexLogger::ZMexLogger(
  const ZMexLogBehavior & desiredBehavior
)
:  ZMhandleTo<ZMexLogBehavior>( desiredBehavior )
{ ; }
  // Construct logger with specified behavior.

ZMexLogger::~ZMexLogger()  { ; }
  // Destroy logger with its behavior.

ZMexLogResult  ZMexLogger::emit( const ZMexception & exc )  {
  return  rep_->emit( exc );
}
  // Force the given exception's message into the log.

ZMexLogResult  ZMexLogger::emit( const std::string & message )  {
  return  rep_->emit( message );
}
  // Force the given message into the log.

ZMexLogBehavior *  ZMexLogger::control()  { return rep_; }
    // Grant access to the representation
    // to permit calling specialized behavior functions.


// ----------------------------------------------------------------------


}  // namespace zmex
