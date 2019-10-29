#ifndef ZMEXCLASSINFO_H
#define ZMEXCLASSINFO_H


// ----------------------------------------------------------------------
//
// ZMexClassInfo.h - class declaration for the member of ZOOM Exception
//		     classes that contains all the static information
//		     that does NOT depend on the parent class.
//
//	Every ZOOM exception must have a static member classInfo, of type
//	ZMexClassInfo.  This is done in the macro ZMexStandardContents.
//	See ZMexception.h.
//
// 	Methods (in .icc):
// 	 	ZMexClassInfo() constructor
//  		const string name() const;
//  		const string facility() const;
//  		int nextCount();
//  		ZMexHandler getHandler() const;
//  		ZMexHandler setHandler(const ZMexHandler & newHandler);
// 	 	ZMexLogger getLogger() const;
//  		ZMexLogger setLogger(const ZMexLogger & newLogger);
//		void logNMore();
//              bool OKtoLog() const;
//		int count() const;
//		int filterMax() const;
//
//	A related header is ZMexHeritage.h which contains class static info
//	which DOES depend on the parent class.
//
// Revision History
//	970911	MF	Initial version
//	970914	MF	Added nextCount to be able to keep count_ private
//	970916	WEB	Updated per code review
//	970917	WEB	Updated per code review 2
//      971112  WEB	Updated for conformance to standard and the zoom
//			compatability headers
//	971211	WEB	Updated per code walkthrough
//	971217	WEB	Added count() and filterMax() member functions
//	980219	WEB	Fixed get/set Logger/Handler return type
//	980615	WEB	Added namespace support
//      990721  JVR     Added setName, setFacility, and setSeverity functions
//      000217  WEB     Improve C++ standard compliance
//      000503  WEB     Avoid global using
//      010411  MF	setName, setFacility and setSeverity return old value
//			and take const argument reference
//	011212	WEB	Pass all std::strings by const &; add new 3- and
//			4-arg constructors in lieu of a single 5-arg
//			constructor taking default arguments
//	031105	LG	Get rid of all ZMutility references

//
// ----------------------------------------------------------------------

#ifndef STRING_INCLUDED
  #define STRING_INCLUDED
  #include <string>
#endif

#ifndef ZMEXHANDLER_H
  #include "CLHEP/Exceptions/ZMexHandler.h"
#endif

#ifndef ZMEXLOGGER_H
  #include "CLHEP/Exceptions/ZMexLogger.h"
#endif

#ifndef ZMEXSEVERITY_H
  #include "CLHEP/Exceptions/ZMexSeverity.h"
#endif


namespace zmex  {


// ******************************************************
//
// ZMexClassInfo
//
// Template for ZMexClassInfo (used to define classInfo)
//
// ******************************************************

// Contains all the methods which are logically "virtual class statics",
// and which do not depend on a Parent's method (see note (1)).
// Each derived exception contains a ZMexClassInfo member named classInfo.

// The members and functions of ZMexClassInfo are public so that when the
// exception class uses classInfo it can get at the info.  But classInfo itself
// is declared protected, to isolate this from the actual interface.


class ZMexClassInfo {

  // - Methods - //

public:

  ZMexClassInfo(
    const std::string & name
  , const std::string & facility
  , const ZMexSeverity  s = ZMexERROR
  );

  ZMexClassInfo(
    const std::string & name
  , const std::string & facility
  , const ZMexSeverity  s
  , const ZMexHandler & h
  );

  ZMexClassInfo(
    const std::string & name
  , const std::string & facility
  , const ZMexSeverity  s
  , const ZMexHandler & h
  , const ZMexLogger &  l
  );

  const std::string name() const;
    // return the name_ of this exception type, which ought to match the
    // class name ZMexWhatever.
  const std::string setName(const std::string& newName);

  const std::string facility() const;
    // return the name of facility_ this exception type is under.
  const std::string setFacility(const std::string& newFacility);

  ZMexSeverity severity() const;
    // return the severity_ of the exception class.
  ZMexSeverity setSeverity(const ZMexSeverity& newSeverity);

  int nextCount();
    // increment the count_ and return that value
  int count() const;
    // return the current count_ value

  ZMexHandler getHandler () const ;
  ZMexHandler setHandler( const ZMexHandler & newHandler );
    // Replace previous handler with this new one.

  ZMexLogger getLogger() const;
  ZMexLogger setLogger( const ZMexLogger & newLogger );
    // Replace previous logger with this new one.

  void logNMore( const int N );
    // Allow logging the next N exceptions of this class.

  bool OKtoLog() const;
    // May the currently-thrown exception be logged
    // (based on count_ <= filterMax_)?

  int filterMax() const;
    // return the current filterMax_ value

  // - Data Members - //

private:
  int           count_;
  int           filterMax_;
  std::string   name_;                                             // was const
  std::string   facility_;                                         // was const
  ZMexSeverity  severity_;                                         // was const

  ZMexHandler   handler_;
  ZMexLogger    logger_;

};  // ZMexClassInfo


}  // namespace zmex


#define ZMEXCLASSINFO_ICC
#include "CLHEP/Exceptions/ZMexClassInfo.icc"
#undef ZMEXCLASSINFO_ICC


#endif  // ZMEXCLASSINFO_H
