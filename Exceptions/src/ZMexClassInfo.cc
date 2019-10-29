// ----------------------------------------------------------------------
//
// ZMexClassInfo.cc
//
// Contains the following methods:
//
// ZMexClassInfo()
//
// Revision History
//	011212	WEB	Initial version w/ constructor no longer inline;
//      		add new 3- and 4-arg constructors in lieu of a
//			single 5-arg constructor taking default arguments
//
// ----------------------------------------------------------------------


#include "CLHEP/Exceptions/ZMexClassInfo.h"


namespace zmex  {


// ZMexClassInfo()
//------------------

ZMexClassInfo::ZMexClassInfo(
  const std::string &  nname
, const std::string &  ffacility
, const ZMexSeverity   s
) :
  count_    ( 0 )
, filterMax_( -1 )
, name_     ( nname )
, facility_ ( ffacility )
, severity_ ( s )
, handler_  ( ZMexHandleViaParent() )
, logger_   ( ZMexLogViaParent() )
{
}

ZMexClassInfo::ZMexClassInfo(
  const std::string &  nname
, const std::string &  ffacility
, const ZMexSeverity   s
, const ZMexHandler &  h
) :
  count_    ( 0 )
, filterMax_( -1 )
, name_     ( nname )
, facility_ ( ffacility )
, severity_ ( s )
, handler_  ( h )
, logger_   ( ZMexLogViaParent() )
{
}

ZMexClassInfo::ZMexClassInfo(
  const std::string &  nname
, const std::string &  ffacility
, const ZMexSeverity   s
, const ZMexHandler &  h
, const ZMexLogger &   l
) :
  count_    ( 0 )
, filterMax_( -1 )
, name_     ( nname )
, facility_ ( ffacility )
, severity_ ( s )
, handler_  ( h )
, logger_   ( l )
{
}


}  // namespace zmex
