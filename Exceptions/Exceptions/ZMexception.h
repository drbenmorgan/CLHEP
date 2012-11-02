#ifndef ZMEXCEPTION_H
#define ZMEXCEPTION_H


// ----------------------------------------------------------------------
//
// ZMexception.h - class declaration for the ZOOM Exception base classes,
//		   and macros to help set up specific exceptions definitions.
//
//   class ZMexception:  This is the public base type of all exceptions.
//                       In particular this is the interface seen by
//                       handler and logger.  Methods are defined in
//  			 a macro ZMexClassStaticMethods, in ZMexception.icc,
//			 or in .../Exceptions/src/ZMexception.cc:
//
//   in the macro	ZMexception.icc		src/ZMexception.cc
//   ------------	---------------		------------------
//   setHandler()	ZMexception
//   getHandler()	message()
//   setLogger()
//   getLogger()	count()
//   isTypeOf()		wasThrown()		logMessage(optText)
//   isBaseOf()		severity()
//   isDerivedFrom	location(line, file)
//   logNMore()		fileName()
//   handleMe()		line()
//   logMe()					name()
//						facility()
//			OKtoLog()
//
// ZMexClassStaticMethods is defined here.  It is used not only by the base
// class definition (ZMexception) but also by a couple of macros established
// for the convenience of creators of ZMex exceptions:
//
//   ZMexStandardContents contains definitions of all the functions in the
//			  interface for exception creators which are implemented
//			  via methods in classInfo.  See technical notes 2 - 5.
//
//   ZMexStandardDefinition defines an exception in the inheritance hierarchy,
//			   with no specific data or member functions beyond
//			   the standard contents.  If more members are needed,
//			   use this macro as an example and add them after the
//			   ZMexStandardContents.
//
// See technical note 1 for instructions on how to use these macros to define
// ZOOM exceptions.  (Technical notes are in file technical-notes in the
// doc area of the Exceptions product).
//
// One further key macro should be known:
//
//   ZMthrow(x) in ZMthrow.h calls ZMthrow_ but adds on the line and file
//   arguments.  ZMthrow_(x,line,file) does the dispatching of the exception
//   handling.
//
// Related structures include:
//
//   ZMexClassInfo  contains the definitions of the classInfo structure.
//			ZMexClassInfo.h
//
// Revision History:
//	970912	MF	Initial version after separating out classInfo etc.
//	970914	MF	Corrected isBaseOf method, which needs isDerivedFrom.
//	970916	WEB	Updated per code review
//	970917	WEB	Updated per code review 2
//	970918	WEB	Updated per code review 3
//	970918	PGC	Updated per code review 4
//      971112  WEB	Updated for conformance to standard and the zoom
//			compatability headers
//	971211	WEB	Updated per code walkthrough
//      971215  WEB     Gave names to the default handler & logger
//      980219  WEB     Corrected return types of get/set Handler/Logger
//			to match those of those classes' methods
//      980304  WEB     Cleaned up logMessage() & related stuff
//      980421  WEB     Moved name() and facility() from .icc to .cc
//	980615	WEB	Added namespace support
//	990318  MF	Added virtual destructor
//      990801  JVR     Added logObject() for augmented exception purposes
//	000217	WEB	Improve C++ standards compliance
//	000503	WEB	Avoid global using
//	010413	MF	Vetted for proper namespace behavior:
//			all macros need to use the equivalent of ZM_QUAL_NAME 
//			to append zmex if (and only if) namespaces are enabled.
//	010626	MF	ctor from ostringstream for syntactic convenience
//	010626	MF	Have ctor use string& rather than string 
//	011012	MF	Include ZMutility/sstream so ostringstream& is OK
//			(KCC somehow survived the omission; gcc does not)
//	011217  MF	logMe() for base class does 
//			ZMexception::classInfo().getLogger().emit(*this);
//			instead of emit(msg).  This significantly improves
//			the look of the output when this path is taken, and
//			when logging to an ErrorLog allows statistics to work.
//	031105	LG	Get rid of all ZMutility references
//      051117  LG      Always use <sstream>
//
// ----------------------------------------------------------------------

#include "CLHEP/Exceptions/defs.h"

#include <iosfwd>

#ifndef STRING_INCLUDED
  #define STRING_INCLUDED
  #include <string>
#endif

#ifndef ZMEXSEVERITY_H
  #include "CLHEP/Exceptions/ZMexSeverity.h"
#endif

#ifndef ZMEXLOGRESULT_H
  #include "CLHEP/Exceptions/ZMexLogResult.h"
#endif

#ifndef ZMEXACTION_H
  #include "CLHEP/Exceptions/ZMexAction.h"
#endif

#ifndef ZMEXCLASSINFO_H
  #include "CLHEP/Exceptions/ZMexClassInfo.h"
#endif

#include <sstream>


#ifdef ZM_USE_NAMESPACES
#define ZMEX zmex
#else
#define ZMEX
#endif

namespace zmex  {


class ZMexHandler;
class ZMexLogger;
class ZMexNoParent;

// **************************************
//
// ZMexUserActivity, ZMexUserNumericalTag
//
// **************************************

extern std::string ZMexUserActivity;
extern int ZMexUserNumericalTag;


// *******************
//
// ZMhandler, ZMlogger
//
// *******************

ZMexHandler &  ZMhandler();
ZMexLogger  &  ZMlogger();

// ***********
//
// ZMexception
//
// ***********

class ZMexception {

protected:
  static ZMexClassInfo _classInfo;
    // The base class has these static members for its class information.

  const std::string message_;
    // Indicates reason for the exception.  Should be unique to the line of
    // code doing ZMthrow.  Multiple lines can throw the same ZMexception,
    // but normally supply different messages.

  #ifndef DEFECT_NO_MUTABLE
  mutable
  #endif
  int    line_;
  #ifndef DEFECT_NO_MUTABLE
  mutable
  #endif
  std::string sourceFileName_;
    // Indicate location of the source of the exception

    // Copy for each instance of the class-wide data to snapshot them.
  const ZMexSeverity mySeverity_;
  const int          myCount_;
  #ifndef DEFECT_NO_MUTABLE
  mutable
  #endif
  std::string     handlerUsed_;
  #ifndef DEFECT_NO_MUTABLE
  mutable
  #endif
  bool       wasThrown_;



public:
  // ********************** //
  // Constructor/Destructor //
  // ********************** //

  ZMexception(
    const std::string &      mesg
  , const ZMexSeverity howBad = ZMexSEVERITYenumLAST
  , int                icount  = ZMexception::_classInfo.nextCount()
  );

  explicit
  ZMexception(
    const std::ostringstream & msg
  , const ZMexSeverity howBad = ZMexSEVERITYenumLAST
  , int                icount  = ZMexception::_classInfo.nextCount()
  );

  virtual ~ZMexception() {}

  // ********************** //
  // Instance Methods       //
  // ********************** //

  void location( int line, const std::string file ) const;
    // Set the location of the creator of the exception

  ZMexSeverity severity() const;
    // Determine the severity of this exception.

  int line() const;
  std::string fileName() const;
    // Determine the file/line number of the ZMthrow of this exception.

  std::string message() const;
  int count() const;

  std::string handlerUsed() const;
  bool   wasThrown() const;

  // The following are for internal use of the exception mechanism routines:
  void handlerUsed( const std::string handlerName ) const;
  void wasThrown( bool b ) const;

  virtual std::string logMessage( const std::string optText = "" ) const;

  virtual std::string facility() const;
    // Return the class facility preamble string.

  virtual std::string name() const;
    // Return the exception name string, e.g., "ZMexWhatever".

  bool OKtoLog() const;


  // ****************************
  //
  // Methods dealt with in the
  // ZMexClassStaticMethods macro
  //
  // ****************************

public:
  // ********************** //
  // Class static Methods   //
  // ********************** //

  // This declares the standard static methods and the virtual
  // functions that depend on the static member of exception class --
  // classInfo.  Technical note 5 explains why we will
  // need to use a macro defining these methods, rather than using simple
  // virtual methods or using templates.

  // Note - These declarations become moot for every class derived from
  // ZMexception, because the methods of the same names are explicitly
  // declared and defined in the ZMexClassStaticMethods macro.  However,
  // it is useful to have these declarations here in the base class, to
  // set forth a clean and commented specification of the interface to
  // these routines.  The interface applies to ALL ZOOM exceptions.

  /*
  static ZMexHandler setHandler( const ZMexHandler & newHandler );
    // Replace previous handler; return old handler.

  static const ZMexHandler getHandler();
    // Return the current handler.

  static ZMexLogger setLogger( const ZMexLogger & newLogger );
    // Replace previous logger; return old logger.

  static const ZMexLogger getLogger();
    // Return the current logger.

  static ZMexSeverity setSeverity ( const ZMexSeverity & newSeverity );
    // Replace previous severity; return old severity.

  static const std::string setName ( const std::string & newName );
    // Replace previous name; return old name.

  static const std::string setFacility ( const std::string & newFacility );
    // Replace previous Facility; return old Facility.

  static bool isTypeOf( const ZMexception & x );
    // Test if x is this type of exception

  static bool isBaseOf( const ZMexception & x );
    // Test if x is exactly or derived from this type of exception
  */

  // ************************************************************** //
  // Virtual instance methods that utilize class static information //
  // ************************************************************** //

  // Note - These are just like the class static methods in that they
  // have to be declared explicitly for each exception class, lest they
  // incorrectly use the method of that name in the base class ZMexception.
  // See technical note 6.
  // The difference is that (letting x be an instance of an exception type X)
  // these "instance methods" are invoked as x.f(), while the "class static
  // methods" are invoked by X::f().

  // These instance methods have to be virtual because the exception x is passed
  // to a method expecting a ZMexception, which then invokes x.method().  If
  // method() is not virtual you get ZMexception.method() - which we don't
  // want - even though X has a method of that same name defined.

  /*
  virtual ZMexClassInfo & classInfo();
    // return  the appropriate classInfo

  virtual ZMexAction handleMe() const;
    // handle the current instance

  virtual ZMexLogResult logMe() const;
    // log the current instance

  virtual bool isDerivedFrom( const std::string name,
			      const std::string facility );
    // check if this intance is of class derived form the one qualified
    // by name and facility.
    // Test if this exception is derived from an exception with given name
  */

  // ****************************
  // ZMexClassStaticMethods macro
  // ****************************

  // This macro contains definitions implementing the standard static methods
  // (class-wide logically virtual functions) that depend on the static member
  // of the exception class -- classInfo.  Technical note 5
  // addresses the need to use a macro defining these methods,

  // CODING NOTE -- THE ROUTINES DEFINED HERE SHOULD MATCH EXACTLY THE
  //		    INTERFACE DECLARED ABOVE (except that static methods
  //                may not be declared const).

#define ZMexClassStaticMethods						\
									\
  static zmex::ZMexHandler setHandler( 			\
		const zmex::ZMexHandler & newHandler ) {	\
    return  _classInfo.setHandler( newHandler); }			\
  static zmex::ZMexHandler getHandler() {			\
    return  _classInfo.getHandler(); }					\
									\
  static zmex::ZMexLogger setLogger( 			\
		const zmex::ZMexLogger & newLogger ) {	\
    return _classInfo.setLogger( newLogger ); }				\
  static zmex::ZMexLogger getLogger() {			\
    return  _classInfo.getLogger(); }					\
									\
  static zmex::ZMexSeverity setSeverity (			\
	const zmex::ZMexSeverity & newSeverity ) {		\
    return _classInfo.setSeverity (newSeverity); }			\
  static const std::string setName ( const std::string & newName ) {    \
    return _classInfo.setName (newName); }				\
  static const std::string setFacility(const std::string& newFacility){	\
    return _classInfo.setFacility (newFacility); }			\
  static bool isTypeOf( const zmex::ZMexception & x ) {	\
    return  ( (_classInfo.name() == x.name()) && 			\
	      (_classInfo.facility() == x.facility() ) ); }		\
									\
  static bool isBaseOf( const zmex::ZMexception & x ) {	\
    return  ( x.isDerivedFrom (_classInfo.name(),			\
			       _classInfo.facility()) ); }		\
									\
  static void logNMore( const int N )  {				\
    _classInfo.logNMore( N ); }						\

//
// end of ZMexClassStaticMethods macro

  // ****************************
  // ZMexVirtualMethods macro
  // ****************************

  // This macro contains definitions implementing the standard virtual methods
  // that depend on the static members of the exception class -- classInfo.
  // Technical note 5 addresses the need to use a macro defining
  // these methods,

  // CODING NOTE -- THE ROUTINES DEFINED HERE SHOULD MATCH EXACTLY THE
  //		    INTERFACE DECLARED ABOVE (except that static methods
  //                may not be declared const).

#define ZMexVirtualMethods(Parent,Class)				\
									\
  virtual Class * 	                          clone() const {	\
    return  new Class( *this ); }					\
									\
  virtual zmex::ZMexClassInfo & classInfo() const {	\
    return  Class::_classInfo; }					\
									\
  virtual zmex::ZMexAction handleMe() const {		\
	  /* DEBUG  std::cerr << #Class "::handleMe()" << std::endl; */	\
    zmex::ZMexAction result = 				\
		Class::classInfo().getHandler().takeCareOf( *this );	\
    return  (result == zmex::ZMexHANDLEVIAPARENT) ? 	\
			Parent::handleMe() : result; }			\
									\
  virtual zmex::ZMexLogResult logMe() const {		\
	/* DEBUG  std::cerr << #Class "::logMe()" << std::endl; */	\
    zmex::ZMexLogResult result = 				\
		Class::classInfo().getLogger().emit( *this );		\
    return  (result == zmex::ZMexLOGVIAPARENT) ? 		\
				Parent::logMe()	: result; }		\
									\
  virtual bool isDerivedFrom( const std::string aName,			\
			      const std::string aFacility ) const {	\
    return  aName == name()  &&  aFacility == facility()		\
      ? true								\
      : Parent::isDerivedFrom( aName, aFacility );			\
  }									\

//
// end of ZMexVirtualMethods macro

public:
  ZMexClassStaticMethods;
    // Define all the static methods for the ZMexception base class.

  // Special cases for the virtual functions for the top exception class.
  virtual ZMexception * clone() const {
    return  new ZMexception ( *this );
  }

  virtual zmex::ZMexClassInfo & classInfo() const {
    return  ZMexception::_classInfo;
  }

  virtual ZMexAction handleMe() const {
    // DEBUG  std::cerr << "ZMexception::handleMe()" << std::endl;
    return  ZMexception::classInfo().getHandler().takeCareOf( *this );
  }

  virtual ZMexLogResult logMe() const {
    // DEBUG  std::cerr << "ZMexception::logMe()" << std::endl;
    return ZMexception::classInfo().getLogger().emit(*this);
  }

  virtual bool isDerivedFrom(
    const std::string 
  , const std::string 
  ) const {
    return  false;
  }

  virtual void logObject() const {}                                //added

};  // ZMexception


// *************************************
//
// Macros for deriving ZOOM exceptions
//
// *************************************


// *******************************
// ZMexStandardContents macro
// *******************************

#define ZMexStandardContents(Parent,Class)				\
public:									\
  static zmex::ZMexClassInfo _classInfo;			\
public:									\
  Class(								\
    const std::string  & mesg						\
  , const zmex::ZMexSeverity howBad = 			\
			zmex::ZMexSEVERITYenumLAST		\
  , int                      icount = _classInfo.nextCount()		\
  )  :									\
    Parent(								\
      mesg								\
    , (howBad == zmex::ZMexSEVERITYenumLAST ? 		\
			_classInfo.severity() : howBad)			\
    , icount								\
    )									\
  { }									\
									\
  Class(								\
    const std::ostringstream&  msg					\
  , const zmex::ZMexSeverity howBad = 			\
			zmex::ZMexSEVERITYenumLAST		\
  , int                      icount = _classInfo.nextCount()		\
  )  :									\
    Parent(								\
      msg								\
    , (howBad == zmex::ZMexSEVERITYenumLAST ? 		\
			_classInfo.severity() : howBad)			\
    , icount								\
    )									\
  { }									\
									\
  ZMexClassStaticMethods;						\
  ZMexVirtualMethods(Parent,Class);					\

//
// end of ZMexStandardContents macro


// *******************************
// ZMexStandardDefinition macro
// *******************************

#define ZMexStandardDefinition(Parent,Class) 				\
  class Class : public Parent { 					\
    ZMexStandardContents(Parent,Class)	 				\
  }									\

//
// end of ZMexStandardDefinition macro


}  // namespace zmex


#define ZMEXCEPTION_ICC
#include "CLHEP/Exceptions/ZMexception.icc"
#undef ZMEXCEPTION_ICC


#endif  // ZMEXCEPTION_H
