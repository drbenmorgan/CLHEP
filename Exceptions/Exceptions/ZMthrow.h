#ifndef ZMTHROW_H
#define ZMTHROW_H

// ----------------------------------------------------------------------
//
// ZMthrow.h - macro definition for the ZMthrow macro, tand function
//	       declarations for ZMthrow_from() and ZMthrow_().
//
//   ZMthrow(x) calls ZMthrow_ but adds on the line and file arguments.
//   It either throws or not, depending on the return value of ZMthrow_.
//
//   ZMthrow_from(x,line,file) calls ZMthrow_ using the supplied line and file
//   file arguments.  Again, it either throws or not, depending on the return 
//   value of ZMthrow_.
//
//   ZMthrow_(), should not be used directly by user code, but is defined in 
//   ZMthrow.cc for use by the ZMthrow macro and by ZMthrow_from.
//
//	NOTE -- ZMthrow() and ZMthrow_from() are NOT in namespace zmex::
//		ZMthrow() is NOT namespace qualified; it is a macro.
//		ZMthrow_from() is NOT namespace qualified; it is a macro.
//
// Revision History
//	970910	MF	Initial version
//	970916	WEB	Update per code review
//	970917	WEB	Update per code review 2
//      970918  PGC     Replace monolitic if by do while loop
//      971113  WEB     Correct minor typo
//	980615	WEB	Add namespace support
//	000218	WEB	Replace NOTHROW by DEFECT_NO_EXCEPTIONS for
//        		ISOcxx compatibility
//	000512	WEB	DEBUG corrections; remove useless reference in
//	  		NO_EXCEPTIONS definition
//	010409	MF	ZMthrow_from()
//	010413	MF	Include ZMenvironment and make other changes to 
//			make sure namespaces are treated properly.  
//	031105	LG	Get rid of all ZMutility references
//
// ----------------------------------------------------------------------

#ifndef ZMEXACTION_H
  #include "CLHEP/Exceptions/ZMexAction.h"
#endif

#include <stdlib.h> // for abort()
#include <string>

/* DEBUG #include <iostream> // for cerr */


namespace zmex  {


class ZMexception;


//*******************
//
// ZMthrow_from macro
//
//*******************


#ifdef DEFECT_NO_EXCEPTIONS

#define ZMthrow_from(userExcept, line, file )				\
do { 									\
  if ( zmex::ZMthrow_( userExcept, line, file ) == 	\
			zmex::ZMexThrowIt )  {		\
    abort(); }								\
} while (false)								\

#else

#define ZMthrow_from(userExcept, line, file )				\
do { 									\
  try { throw userExcept; }						\
  catch ( const zmex::ZMexception & x )  {		        \
    if ( zmex::ZMthrow_( x, line, file ) == 		\
			zmex::ZMexThrowIt ) {		\
      throw;								\
    }									\
  }									\
} while (false)								\

#endif  // NOTHROW

//
// End of the ZMthrow_from macro, which should NOT end with a semicolon.

//**************
//
// ZMthrow macro
//
//**************

#define ZMthrow(userExcept) ZMthrow_from(userExcept, __LINE__, __FILE__)

//
// End of the ZMthrow macro, which should NOT end with a semicolon.

// NOTE - This is a macro.  It has to be a monolithic statement so that a
//	  construct like
//		if (xxx) ZMthrow(ZMxAbc); else dowhatever;
//	  works.  Since the content CANNOT therefore be in a block, we use
//        a do-while loop that will be executed exactly once.

//***********
//
// ZMthrow_()
//
//***********

ZMexAction ZMthrow_(
  const ZMexception & userException
, int                 lineNum
, const char          fileName[]
);

}  // namespace zmex



#endif  // ZMTHROW_H
