// $Id: CBInterface.h,v 1.1.1.1 2003/07/15 20:15:05 garren Exp $
// ----------------------------------------------------------------------
// CBInterface.h
// ----------------------------------------------------------------------
// Author:  Lynn Garren, Marc Paterno
// 
// This is the Fortran interface to a generic collection of common blocks
// The singleton implementation allows you to both read and write
//
// ----------------------------------------------------------------------
#ifndef CBINTERFACE_H
#define CBINTERFACE_H

namespace HepMC {

template<class S>
class CBInterface {

public:

  static CBInterface< S > * instance()
  { 
      static CBInterface< S > me;
      return &me;
  }
  
  S* operator->() { return & myS; }
  S& operator*()  { return myS; }
  
private:
  S myS;

};	// CBInterface

}	// HepMC

#endif	// CBINTERFACE_H
