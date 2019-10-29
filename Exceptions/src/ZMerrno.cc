// ----------------------------------------------------------------------
//
// ZMerrno.cc -- implementation of the error list mechanism.
//
// The following are instantiated here:
//	ZMerrnoList ZMerrno;
//
// The following methods of ZMerrnoList are defined here:
//	void write(ZMexception& x);
//	const ZMexception* get(unsigned int k=0);
//	string name(unsigned int k=0);
//	void erase();
//	unsigned int setMax(unsigned int maxNumber);
//
// Revision History:
//   970916	WEB	Updated per code review
//   970917	WEB	Updated per code review 2
//   971113	WEB	Updated to conform to standard coding techniques
//   980615	WEB	Added namespace support
//   980728	WEB	Added destructor; fixed other memory leaks
//
// ----------------------------------------------------------------------


#include "CLHEP/Exceptions/ZMerrno.h"

#include "CLHEP/Exceptions/ZMexception.h"


namespace zmex  {


//********
//
// ZMerrno
//
//********

ZMerrnoList ZMerrno;
  // Define the actual ZMerrno instance !!


//***************
//
// ~ZMerrnoList()
//
//***************

ZMerrnoList::~ZMerrnoList() {

  while ( size() > 0 )  {
    const ZMexception * e = errors_.front();
    errors_.pop_front();
    delete const_cast<ZMexception *>( e );
  }

}  // ZMerrnoList::~ZMerrnoList()


//*************************
//
// write( ZMexception & x )
//
//*************************

void ZMerrnoList::write( const ZMexception & x ) {
  // copy an exception onto ZMerrno

  ++count_;
  ++countSinceCleared_;

  if ( max_ <= 0 ) {
    return;
  }

  if ( max_ <= size() ) {
    // Get rid of the oldest.
    const ZMexception * e = errors_.front();
    errors_.pop_front();
    delete const_cast<ZMexception *>( e );
  }

  errors_.push_back( x.clone() );

}  // ZMerrnoList::write()


//*******
//
// get(k)
//
//*******

const ZMexception * ZMerrnoList::get( unsigned int k ) const {
  // Obtain a const pointer to the exception for the latest-but-k entry
  // on ZMerrno.
  // Will be NULL if ZMerrno has been cleared since the last ZMthrow,
  // and also if k is not less than ZMerrno.size().

  return  k < size() ? errors_[size()-1-k]
		     : 0;

}  // ZMerrnoList::get()


//********
//
// name(k)
//
//********

std::string ZMerrnoList::name( unsigned int k ) const {
  // Obtain the mnemonic name of the latest-but-k exception on ZMerrno

  return  k < size() ? get(k)->name()
		     : std::string();

}  // ZMerrnoList::name()


//********
//
// erase()
//
//********

// Remove the latest entry.

void ZMerrnoList::erase() {

  if ( size() > 0 )  {
    const ZMexception * e = errors_.back();
    errors_.pop_back();
    delete const_cast<ZMexception *>( e );
  }

}  // ZMerrnoList::erase()


//**********************************
//
//  setMax (unsigned int maxNumber)
//
//**********************************

unsigned int ZMerrnoList::setMax( unsigned int newMax ) {
  // Set the maximum number of exceptions to be kept in the list.
  // Zero completely disables the ZMerrno mechanism.

  unsigned int oldMax = max_;
  // If a reduction, you may have to pop some old entries off:
  while ( newMax < size() ) {
    const ZMexception * e = errors_.front();
    errors_.pop_front();
    delete const_cast<ZMexception *>( e );
  }
  max_ = newMax;
  return oldMax;

}  // ZMerrnoList::setMax()


}  // namespace zmex
