////////////////////////////////////////////////////////////////////////
//
// File: pretend.hh
// $Id: pretend.hh,v 1.1.1.1 2003/07/15 20:15:05 garren Exp $
// Purpose: This is to fake out the gcc -pedantic switch when dealing
//          with singleton instances.
//
// Author:  Walter Brown
//
////////////////////////////////////////////////////////////////////////

#ifndef PRETEND_HH
#define PRETEND_HH

template< class T >
inline
void  pretend_to_use( T const & )
{}

#endif // #ifndef PRETEND_HH
