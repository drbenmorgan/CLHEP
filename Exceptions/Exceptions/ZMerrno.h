#ifndef ZMERRNO_H
#define ZMERRNO_H


// ----------------------------------------------------------------------
//
// ZMerrno.h - declaration of ZMerrno and its ZMerrnoList class
//
// Declares the following, which are defined in ZMerrno.cc:
//   ZMerrnoList();
//   unsigned int setMax(unsigned int max_number);
//   void write(ZMexception& x);
//   string name(unsigned int k = 0) const;
//   const ZMexception* get(unsigned int k=0) const;
//   void clear();
//   void erase();
//   discard();
//
// Defined in ZMerrno.icc:
//   int size() const;
//   int count() const;
//   int countSinceCleared() const;
//
// Revision History:
//	970916	WEB	Updated per code review
//	970917	WEB	Updated per code review 2
//      970918  PGC     Change deque from Exception object to Exception
//                      pointer to keep polymorphism.
//      971112  WEB	Updated for conformance to standard and the zoom
//			compatability headers
//	980615	WEB	Added namespace support
//	980728	WEB	Added ZMerrnoList destructor
//	000217	WEB	Improve C++ standard compliance
//	000503	WEB	Avoid global using
//	011030	MF	Changed return type of size() to unsigned int 
//			to avoid conversion warnings
//	031105	LG	Get rid of all ZMutility references
//
// ----------------------------------------------------------------------

#ifndef STRING_INCLUDED
  #define STRING_INCLUDED
  #include <string>
#endif

#ifndef DEQUE_INCLUDED
  #define DEQUE_INCLUDED
  #include <deque>
#endif


namespace zmex  {


class ZMexception;

class ZMerrnoList {

public:

  ZMerrnoList();
    // Constructor of list.

  ~ZMerrnoList();
    // Destructor of list.

  unsigned int setMax( unsigned int limit );
    // Set the maximum number of exceptions to be kept in the ZMerrnoList.
    // We prohibit unlimited size because each exception kept
    // may represent a memory leak of at least sizeof(ZMexception).  You
    // really do want a circular buffer; in Unix the size of that buffer is 1.
    // Zero completely disables the ZMerrno mechanism and clears out and
    // deletes the exceptions on the list.

  void write( const ZMexception & x );
    // Copy an exception onto ZMerrno at the "back" of the deque

  int countSinceCleared() const;
    // Returns the number of exceptions since last cleared

  std::string name( unsigned int k = 0 ) const;
    // Obtain the mnemonic name of the latest-but-k exception on ZMerrno.
    // Thus name()gets the name of the latest exception.

  const ZMexception* get( unsigned int k = 0 ) const;
    // Obtain a pointer to the exception for the latest-but-k exception
    // on ZMerrno.  Thus get() obtains a const pointer to the latest exception.
    // Allows perusal of things like the message and the logger
    // and handler used when the exception was encountered.  Should be
    // checked for 0 since ZMerrno may not go back as far as requested.

  void clear();
    // Zero out the countSinceCleared.

  void erase();
    // Remove the top entry, restoring the top (latest entry) to the
    // previous entry (if any).  For instance, if you have a loop in which
    // some known ignorable happening places a value on the ZMerrnoList, you
    // can erase each one so as not to wipe out the history for others.

  int count() const;
    // Return the number of exceptions ever placed on the ZMerrnoList
    // via ZMerrnoList::write().

  unsigned int size() const;
    // Return the number of entries currently on the stack.

private:

  std::deque< const ZMexception * > errors_;

  unsigned int max_;
  enum { ZMERRNO_LENGTH = 100 };
    // Default maximum number of entries on the stack

  int count_;
  int countSinceCleared_;

};  // ZMerrnoList


extern ZMerrnoList ZMerrno;


}  // namespace zmex


#define ZMERRNO_ICC
#include "CLHEP/Exceptions/ZMerrno.icc"
#undef ZMERRNO_ICC


#endif  // ZMERRNO_H
