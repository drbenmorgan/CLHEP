#ifndef ZMEXHANDLER_H
#define ZMEXHANDLER_H


// ----------------------------------------------------------------------
//
// ZMexHandler.h - interface class declarations for the ZOOM Exception
//                 Handler base class and the basic handlers:
//   ZMexThrowAlways
//   ZMexIgnoreAlways
//   ZMexThrowErrors
//   ZMexIgnoreNextN
//   ZMexHandleViaParent
// These can be used as examples if custom handlers are desired.
//
// Revision History:
// 	970909	MF	Initial version
// 	970916	WEB	Updated per code review
// 	970917	WEB	Updated per code review 2
// 	970923	WEB	Updated per code review 4
// 	971008	WEB	ZMutility is the new name for the Utility package
//      971112  WEB	Updated for conformance to standard and the zoom
//			compatability headers
//	980615	WEB	Added namespace support
//      990318  MF      Modified intializer list orders to avoid warnings
//	000217	WEB	Improve C++ standards compliance
//	000503	WEB	Avoid global using
//	031105	LG	Get rid of all ZMutility references
//
// ----------------------------------------------------------------------

#ifndef STRING_INCLUDED
  #define STRING_INCLUDED
  #include <string>
#endif

#ifndef ZMHANDLETO_H
  #include "CLHEP/RefCount/ZMhandleTo.h"
#endif

#ifndef ZMEXSEVERITY_H
  #include "CLHEP/Exceptions/ZMexSeverity.h"
#endif

#ifndef ZMEXACTION_H
  #include "CLHEP/Exceptions/ZMexAction.h"
#endif


namespace zmex  {


class ZMexception;


//********************
//
// ZMexHandlerBehavior
//
//********************

class ZMexHandlerBehavior {
  // Handler behavior interface definition

public:
  ZMexHandlerBehavior(
    const std::string name = "ZMexHandlerBehavior"
  ) : name_( name ) { }

  virtual ~ZMexHandlerBehavior() { }

  virtual ZMexHandlerBehavior * clone() const  {
    return  new ZMexHandlerBehavior( *this );
  }

  virtual std::string name() const { return name_; }
  virtual ZMexAction takeCareOf( const ZMexception & x ) { return ZMexThrowIt; }

protected:
  /*virtual void handleLog( ZMexception & x, const int limit );*/
  ZMexAction standardHandling( const ZMexception & x, bool willThrow );

private:
  const std::string name_;

};  // ZMexHandlerBehavior



//************
//
// ZMexHandler
//
//************

class ZMexHandler  :  public ZMhandleTo< ZMexHandlerBehavior >  {
  // Handler interface

public:
  ZMexHandler(
    const ZMexHandlerBehavior & behaviorWanted
  )  :
    ZMhandleTo<ZMexHandlerBehavior>( behaviorWanted )
  { }

  virtual ~ZMexHandler() { }

  std::string name() const {
    return  rep_->name();
  }

  virtual ZMexAction takeCareOf( const ZMexception & x )  {
    return  rep_->takeCareOf(x);
  }

  int setLogLimit( ZMexSeverity s, int limit ) {
    int lim = ZMexSeverityLimit[ s ];
    ZMexSeverityLimit[ s ] = limit;
    return  lim;
  }

};  // ZMexHandler



//****************
//
// ZMexThrowAlways
//
//****************

class ZMexThrowAlways :  public ZMexHandlerBehavior {

public:
  ZMexThrowAlways() : ZMexHandlerBehavior( "ZMexThrowAlways" ) { }
  virtual ZMexThrowAlways * clone() const;
  virtual ZMexAction takeCareOf( const ZMexception & x );
};


//****************
//
// ZMexThrowErrors
//
//****************

class ZMexThrowErrors :  public ZMexHandlerBehavior {

public:
  ZMexThrowErrors() : ZMexHandlerBehavior( "ZMexThrowErrors" ) { }
  virtual ZMexThrowErrors * clone() const;
  virtual ZMexAction takeCareOf( const ZMexception & x );
};


//*****************
//
// ZMexIgnoreAlways
//
//*****************

class ZMexIgnoreAlways :  public ZMexHandlerBehavior {

public:
  ZMexIgnoreAlways() : ZMexHandlerBehavior( "ZMexIgnoreAlways" ) { }
  virtual ZMexIgnoreAlways * clone() const;
  virtual ZMexAction takeCareOf( const ZMexception & x );
};


//*****************
//
// ZMexIgnoreNextN
//
//*****************

class ZMexIgnoreNextN :  public ZMexHandlerBehavior {

public:
  ZMexIgnoreNextN( int n ) :
    ZMexHandlerBehavior( "ZMexIgnoreNextN" ),
    countDown_( n )
  { }
  virtual ZMexIgnoreNextN * clone() const;
  virtual ZMexAction takeCareOf( const ZMexception & x );

private:
  int countDown_;
};


//******************
//
// ZMexHandleViaParent
//
//******************

class ZMexHandleViaParent :  public ZMexHandlerBehavior {
public:
  ZMexHandleViaParent() : ZMexHandlerBehavior( "" ) { }
  virtual ZMexHandleViaParent * clone() const;
  virtual ZMexAction takeCareOf( const ZMexception & x );
};


}  // namespace zmex


#define ZMEXHANDLER_ICC
#include "CLHEP/Exceptions/ZMexHandler.icc"
#undef ZMEXHANDLER_ICC


#endif  // ZMEXHANDLER_H
