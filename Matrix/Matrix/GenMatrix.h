// -*- C++ -*-
// CLASSDOC OFF
// ---------------------------------------------------------------------------
// CLASSDOC ON
//
// This file is a part of the CLHEP - a Class Library for High Energy Physics.
//
// 
// Copyright Cornell University 1993, 1996, All Rights Reserved.
// 
// This software written by Nobu Katayama and Mike Smyth, Cornell University.
// 
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions
// are met:
// 1. Redistributions of source code must retain the above copyright
//    notice and author attribution, this list of conditions and the
//    following disclaimer. 
// 2. Redistributions in binary form must reproduce the above copyright
//    notice and author attribution, this list of conditions and the
//    following disclaimer in the documentation and/or other materials
//    provided with the distribution.
// 3. Neither the name of the University nor the names of its contributors
//    may be used to endorse or promote products derived from this software
//    without specific prior written permission.
// 
// Creation of derivative forms of this software for commercial
// utilization may be subject to restriction; written permission may be
// obtained from Cornell University.
// 
// CORNELL MAKES NO REPRESENTATIONS OR WARRANTIES, EXPRESS OR IMPLIED.  By way
// of example, but not limitation, CORNELL MAKES NO REPRESENTATIONS OR
// WARRANTIES OF MERCANTABILITY OR FITNESS FOR ANY PARTICULAR PURPOSE OR THAT
// THE USE OF THIS SOFTWARE OR DOCUMENTATION WILL NOT INFRINGE ANY PATENTS,
// COPYRIGHTS, TRADEMARKS, OR OTHER RIGHTS.  Cornell University shall not be
// held liable for any liability with respect to any claim by the user or any
// other party arising from use of the program.
//
// 
// This is the definition of the HepGenMatrix, base class for HepMatrix,
// HepSymMatrix and HepDiagMatrix. This is an abstract cless.
// See definitions in Matrix.h, SymMatrix.h, DiagMatrix.h and Vector.h

#ifndef _GENMatrix_H_
#define _GENMatrix_H_

#ifdef GNUPRAGMA
#pragma interface
#endif

#include <vector>

#include <iostream>
#include "CLHEP/Matrix/defs.h"

namespace CLHEP {

class HepGenMatrix_row;
class HepGenMatrix_row_const;
class HepGenMatrix;

/**
 * @author
 * @ingroup matrix
 */
class HepGenMatrix {
 
public:
   virtual ~HepGenMatrix() {}


#ifdef DISABLE_ALLOC   // disable this non-compliant allocator
#else
   template <class T, size_t size> class Alloc 
   {
 
   public:  
     typedef T value_type;  
     typedef size_t size_type;  
     typedef ptrdiff_t difference_type;  
     typedef T* pointer;  
     typedef const T* const_pointer;  
     typedef T& reference;  
     typedef const T& const_reference;
 
     pointer address(reference r) const { return &r; }  
     const_pointer address(const_reference r) const { return &r; }  
     Alloc() throw() {}  
     Alloc(const Alloc<T,size>&) throw() {}   
     ~Alloc() throw() {}  
     pointer allocate(size_type n, const void* hint=0 ) { if( n <= size ) return pool; else return new T[n]; }  
     void deallocate(pointer p, size_type n) { if (p == pool ) return; delete [] p; }  
     void construct(pointer p, const T& val ) { new(p) T(val); }  
     void destroy(pointer p) { p->~T(); }  
     size_type max_size() const throw() { size_type c = (size_type)(-1) /sizeof(T); return (0 < c ? c : 1); }  
     template<class O> struct rebind { typedef Alloc<O,size> other; };
 
   private:  
     T pool[size];
   };
#endif

#ifdef DISABLE_ALLOC
   typedef std::vector<double >::iterator mIter;
   typedef std::vector<double >::const_iterator mcIter;
#else
   typedef std::vector<double,Alloc<double,25> >::iterator mIter;
   typedef std::vector<double,Alloc<double,25> >::const_iterator mcIter;
#endif

   virtual int num_row() const = 0;
   virtual int num_col() const = 0;

   virtual const double & operator()(int row, int col) const =0;
   virtual double & operator()(int row, int col) =0;
   // Read or write a matrix element. 
   // ** Note that the indexing starts from (1,1). **

   virtual void invert(int&) = 0;

   class HepGenMatrix_row {
   public:
      inline HepGenMatrix_row(HepGenMatrix&,int);
      double & operator[](int);
   private:
      HepGenMatrix& _a;
      int _r;
   };
   class HepGenMatrix_row_const {
   public:
      inline HepGenMatrix_row_const (const HepGenMatrix&,int);
      const double & operator[](int) const;
   private:
      const HepGenMatrix& _a;
      int _r;
   };
   // helper classes to implement m[i][j]

   inline HepGenMatrix_row operator[] (int);
   inline const HepGenMatrix_row_const operator[] (int) const;
   // Read or write a matrix element.
   // While it may not look like it, you simply do m[i][j] to get an
   // element. 
   // ** Note that the indexing starts from [0][0]. **

   inline static void swap(int&,int&);
#ifdef DISABLE_ALLOC
   inline static void swap(std::vector<double >&, std::vector<double >&);
#else
   inline static void swap(std::vector<double,Alloc<double,25> >&, std::vector<double,Alloc<double,25> >&);
#endif

   virtual bool operator== ( const HepGenMatrix& ) const;
   // equality operator for matrices (BaBar)

   static void error(const char *s);

protected:
   virtual int num_size() const = 0;
   void delete_m(int size, double*);
   double* new_m(int size);

public:
   enum{size_max = 25};
   // This is not the maximum size of the Matrix. It is the maximum length of
   // the array (1D) which can be put on the pile.
   //
   // This enum used to be private, but it then is not accessible
   // in the definition of array_pile in the .cc file for Sun CC 4.0.1.
   // efrank@upenn5.hep.upenn.edu
 
private:
   void operator=(const HepGenMatrix &) {}
   // Remove default operator for HepGenMatrix.

   friend class HepGenMatrix_row;
   friend class HepGenMatrix_row_const;

   //-ap: removed this as it is taken over by the std::vector<double>
   //-ap  double data_array[size_max];  
};

double norm(const HepGenMatrix &m);
double norm1(const HepGenMatrix &m);
double norm_infinity(const HepGenMatrix &m);
// 2, 1 or infinity-norm of a matrix.

}  // namespace CLHEP

#ifdef ENABLE_BACKWARDS_COMPATIBILITY
//  backwards compatibility will be enabled ONLY in CLHEP 1.9
using namespace CLHEP;
#endif

#ifndef HEP_DEBUG_INLINE
#include "CLHEP/Matrix/GenMatrix.icc"
#endif


#endif
