#ifndef ZMEXLOGGER_H
#define ZMEXLOGGER_H


// ----------------------------------------------------------------------
//
// ZMexLogger.h - class declaration for the ZOOM Exception Logger base class
//               and the basic logger ZMexLogger, the base class 
//		 ZMexLogBehavior, and behaviors supplied with the package:
//			ZMexLogNever
//			ZMexLogAlways
//			ZMexLogTwice
//			ZMexLogViaParent
//			ZMexValidationStyle
//
// Revision History:
//	970917	WEB	Updated per code review 2
//	970919	WEB	Updated per code review 4
//	971007	WEB	Removed limiting logger; all loggers now
//			optionally limit by exception severity
//	971008	WEB	ZMutility is the new name for the Utility package
//      971112  WEB	Updated for conformance to standard and the zoom
//			compatability headers
//	971211	WEB	Updated per code walkthrough
//      971215  WEB     Removed unused 2nd parm to ZMexLogger constructor
//	980615	WEB	Added namespace support
//	010410	MF 	Added ZMexValidationStyle
//
// ----------------------------------------------------------------------

#ifndef STRING_INCLUDED
  #define STRING_INCLUDED
  #include <string>
#endif

#include <iostream>

#ifndef ZMEXLOGRESULT_H
  #include "CLHEP/Exceptions/ZMexLogResult.h"
#endif

#ifndef ZMHANDLETO_H
  #include "CLHEP/RefCount/ZMhandleTo.h"
#endif


// ----------------------------------------------------------------------


namespace zmex  {


// ----------------------------------------------------------------------


class ZMexLogger;
class ZMexception;


// ----------------------------------------------------------------------


// ---------------
// ZMexLogBehavior
// ---------------

class ZMexLogBehavior  {
  // Logger behavior interface class

public:

  ZMexLogBehavior();
    // Construct this behavior

  virtual ~ZMexLogBehavior();
    // Destroy this behavior

  virtual ZMexLogBehavior *  clone() const;
    // Duplicate this logger object

  virtual ZMexLogResult  emit( const ZMexception & x );
    // Extract the formatted message, then
    // carry out this logger's basic logging behavior

  virtual ZMexLogResult  emit( const std::string & s );
    // Carry out this logger's basic logging behavior
    // Do nothing with s; this base class function ought never be called

  virtual bool isTimeDesired()     const;
  virtual bool isFilePathDesired() const;

};  // ZMexLogBehavior



// ------------
// ZMexLogNever
// ------------

class ZMexLogNever  :  public ZMexLogBehavior  {

public:

  ZMexLogNever();
    // Construct this behavior

  virtual ~ZMexLogNever();
    // Destroy this behavior

  virtual ZMexLogResult  emit( const ZMexception & x );
    // Extract the formatted message, then
    // carry out this logger's basic logging behavior

  virtual ZMexLogNever *  clone() const;
    // Duplicate this logger object

  virtual ZMexLogResult  emit( const std::string & s );
    // Carry out this logger's basic logging behavior: do nothing with s

};  // ZMexLogNever


// -------------
// ZMexLogAlways
// -------------

class ZMexLogAlways  :  public ZMexLogBehavior  {

public:

  ZMexLogAlways();
  ZMexLogAlways( std::ostream & os );
    // Construct this behavior with given destination

  virtual ~ZMexLogAlways();
    // Destroy this behavior

  virtual ZMexLogAlways *  clone() const;
    // Duplicate this logger object

  virtual ZMexLogResult  emit( const ZMexception & x );
    // Extract the formatted message, then
    // carry out this logger's basic logging behavior

  virtual ZMexLogResult  emit( const std::string & s );
    // Carry out this logger's basic logging behavior: myOs << s

private:

  std::ostream &  myOs;
    // This logger's destination for messages to be logged

};  // ZMexLogAlways


// -------------
// ZMexLogTwice
// -------------

class ZMexLogTwice  :  public ZMexLogBehavior  {

public:

  ZMexLogTwice( std::ostream & os1 );
  ZMexLogTwice( std::ostream & os1, std::ostream & os2 );
    // Construct this behavior with given destinations

  virtual ~ZMexLogTwice();
    // Destroy this behavior

  virtual ZMexLogTwice *  clone() const;
    // Duplicate this logger object

  virtual ZMexLogResult  emit( const ZMexception & x );
    // Extract the formatted message, then
    // carry out this logger's basic logging behavior

  virtual ZMexLogResult  emit( const std::string & s );
    // Carry out this logger's basic logging behavior: os_ << s, os2_ << s

private:

  std::ostream &  myOs1;
  std::ostream &  myOs2;

};  // ZMexLogTwice


// ----------------
// ZMexLogViaParent
// ----------------

class ZMexLogViaParent  :  public ZMexLogBehavior  {

public:

  ZMexLogViaParent();
    // Construct this behavior

  virtual ~ZMexLogViaParent();
    // Destroy this behavior

  virtual ZMexLogViaParent *  clone() const;
    // Duplicate this logger object

  virtual ZMexLogResult  emit( const ZMexception & x );
    // Extract the formatted message, then
    // carry out this logger's basic logging behavior

  virtual ZMexLogResult  emit( const std::string & s );
    // Carry out this logger's basic logging behavior: defer elsewhere

};  // ZMexLogViaParent


// -----------------
// ZMexValidationStyle
// -----------------

class ZMexValidationStyle  :  public ZMexLogBehavior  {

public:

  ZMexValidationStyle();
  ZMexValidationStyle( std::ostream & os );
    // Construct this behavior with given destination

  virtual ~ZMexValidationStyle();
    // Destroy this behavior

  virtual ZMexValidationStyle * clone() const;
    // Duplicate this logger object

  virtual ZMexLogResult  emit( const ZMexception & x );
    // Extract the formatted message, then
    // carry out this logger's basic logging behavior

  virtual ZMexLogResult  emit( const std::string & s );
    // Carry out this logger's basic logging behavior: myOs << s

  virtual bool isTimeDesired()     const;
  virtual bool isFilePathDesired() const;

private:

  std::ostream &  myOs;
    // This logger's destination for messages to be logged

};  // ZMexValidationStyle

//************
// ZMexLogger
//************


class ZMexLogger  :  public ZMhandleTo< ZMexLogBehavior >  {
  // Class defining logger interface

public:

  ZMexLogger( const ZMexLogBehavior & desiredBehavior );
    // Construct logger with specified behavior

  ~ZMexLogger();
    // Destroy logger with its behavior

  ZMexLogResult  emit( const ZMexception & exc );
    // Hand over the exception for formatting and log entry

  ZMexLogResult  emit( const std::string & message );
    // Hand over the given string (or char*) for log entry

  ZMexLogBehavior *  control();
    // Grant access to the representation
    // to permit calling specialized behavior functions

};  // ZMexLogger


// ----------------------------------------------------------------------


}  // namespace zmex


// ----------------------------------------------------------------------


#endif  // ZMEXLOGGER_H
