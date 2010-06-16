// ======================================================================
//
// Test basic functionality of primary type traits
//
// Author:  W. E. Brown, 2010-03-27, adapted in part from the boost
// library's type_traits and related functionality whose internal
// attributions bear the following various notices:
//
//   (C) Copyright John Maddock 2000.
//   Distributed under the Boost Software License, Version 1.0.
//   See http://www.boost.org/LICENSE_1_0.txt
//
// ======================================================================


#include "CLHEP/Utility/noncopyable.h"
#include "CLHEP/Utility/type_traits.h"

#include <cassert>
#include <iostream>


using namespace CLHEP;


// primary type category codes:
unsigned  _unknown                 = 0uL    ;
unsigned  _void                    = 1uL <<  0;
unsigned  _integral                = 1uL <<  1;
unsigned  _floating_point          = 1uL <<  2;
unsigned  _array                   = 1uL <<  3;
unsigned  _pointer                 = 1uL <<  4;
unsigned  _lvalue_reference        = 1uL <<  5;
unsigned  _rvalue_reference        = 1uL <<  6;
unsigned  _member_object_pointer   = 1uL <<  7;
unsigned  _member_function_pointer = 1uL <<  8;
unsigned  _enum                    = 1uL <<  9;
unsigned  _union                   = 1uL << 10;  // Help, compiler!
unsigned  _class                   = 1uL << 11;
unsigned  _function                = 1uL << 12;

// composite type category codes:
unsigned  _reference               = 1uL << 13;
unsigned  _arithmetic              = 1uL << 14;
unsigned  _fundamental             = 1uL << 15;
unsigned  _object                  = 1uL << 16;
unsigned  _scalar                  = 1uL << 17;
unsigned  _compound                = 1uL << 18;
unsigned  _member_pointer          = 1uL << 19;


// evaluate categories:
template< typename T >
  unsigned
  evaluate()
{
  unsigned  ans = _unknown;

  if( is_void                   <T>::value )  ans += _void;
  if( is_integral               <T>::value )  ans += _integral;
  if( is_floating_point         <T>::value )  ans += _floating_point;
  if( is_array                  <T>::value )  ans += _array;
  if( is_pointer                <T>::value )  ans += _pointer;
  if( is_lvalue_reference       <T>::value )  ans += _lvalue_reference;
  if( is_rvalue_reference       <T>::value )  ans += _rvalue_reference;
  if( is_member_object_pointer  <T>::value )  ans += _member_object_pointer;
  if( is_member_function_pointer<T>::value )  ans += _member_function_pointer;
  if( is_enum                   <T>::value )  ans += _enum;
  if( is_union                  <T>::value )  ans += _union;
  if( is_class                  <T>::value )  ans += _class;
  if( is_function               <T>::value )  ans += _function;;

  if( is_reference              <T>::value )  ans += _reference;
  if( is_arithmetic             <T>::value )  ans += _arithmetic;
  if( is_fundamental            <T>::value )  ans += _fundamental;
  if( is_object                 <T>::value )  ans += _object;
  if( is_scalar                 <T>::value )  ans += _scalar;
  if( is_compound               <T>::value )  ans += _compound;
  if( is_member_pointer         <T>::value )  ans += _member_pointer;

  return ans;
}


unsigned  cat_void
  = _void | _fundamental;
unsigned  cat_int
  = _integral | _arithmetic | _object | _fundamental | _scalar;
unsigned  cat_flt
  = _floating_point | _arithmetic | _object | _fundamental | _scalar;
unsigned  cat_arr
  = _array | _object | _compound;
unsigned  cat_ptr
  = _pointer | _object | _compound | _scalar;
unsigned  cat_lref
  = _lvalue_reference | _reference | _compound;
unsigned  cat_rref
  = _rvalue_reference | _reference | _compound;
unsigned  cat_mem_obj_ptr
  = _member_object_pointer | _member_pointer | _object | _compound | _scalar;
unsigned  cat_mbr_fctn_ptr
  = _member_function_pointer | _member_pointer | _object | _compound | _scalar;
unsigned  cat_enum
  = _enum | _object | _compound | _scalar;
unsigned  cat_union
  = _union | _object | _compound;
unsigned  cat_class
  = _class | _object | _compound;
unsigned  cat_fctn
  = _function | _compound;


// define some test types:

// class type:
struct mytype
{
  int a;
  int * p;
  int f();
};  // mytype


// enum type:
enum myenum { a=12, b=16 };


// union type:
union myblend
{
  int a;
  int * p;
  int f();
};

enum enum_UDT{ one, two, three };
struct UDT
{
  UDT() { };
  ~UDT() { };
  UDT(const UDT&);
  UDT& operator=(const UDT&);
  int i;

  void f1();
  int f2();
  int f3(int);
  int f4(int, float);
};

typedef void(*f1)();
typedef int(*f2)(int);
typedef int(*f3)(int, bool);
typedef void (UDT::*mf1)();
typedef int (UDT::*mf2)();
typedef int (UDT::*mf3)(int);
typedef int (UDT::*mf4)(int, float);
typedef int (UDT::*mp);
typedef int (UDT::*cmf)(int) const;

// cv-qualifiers applied to reference types should have no effect

// This is intentional:
// r_type and cr_type should be the same type
// but some compilers wrongly apply cv-qualifiers
// to reference types (this may generate a warning
// on some compilers):

typedef int& r_type;
#if ! defined(_MSC_VER)
typedef const r_type cr_type;
#endif  // _MSC_VER

struct POD_UDT { int x; };
struct empty_UDT
{
  empty_UDT() { };
  empty_UDT(const empty_UDT&) { };
  ~empty_UDT() { };
  empty_UDT& operator=(const empty_UDT&){ return *this; }
  bool operator==(const empty_UDT&)const
  { return true; }
};
struct empty_POD_UDT
{
  bool operator==(const empty_POD_UDT&)const
  { return true; }
};
union union_UDT
{
  int x;
  double y;
  ~union_UDT() { }
};
union POD_union_UDT
{
  int x;
  double y;
};
union empty_union_UDT
{
  ~empty_union_UDT() { }
};
union empty_POD_union_UDT { };

struct nothrow_copy_UDT
{
  nothrow_copy_UDT();
  nothrow_copy_UDT(const nothrow_copy_UDT&)throw();
  ~nothrow_copy_UDT() { };
  nothrow_copy_UDT& operator=(const nothrow_copy_UDT&){ return *this; }
  bool operator==(const nothrow_copy_UDT&)const
  { return true; }
};

struct nothrow_assign_UDT
{
  nothrow_assign_UDT();
  nothrow_assign_UDT(const nothrow_assign_UDT&);
  ~nothrow_assign_UDT() { };
  nothrow_assign_UDT& operator=(const nothrow_assign_UDT&)throw(){ return *this; }
  bool operator==(const nothrow_assign_UDT&)const
  { return true; }
};

struct nothrow_construct_UDT
{
  nothrow_construct_UDT()throw();
  nothrow_construct_UDT(const nothrow_construct_UDT&);
  ~nothrow_construct_UDT() { };
  nothrow_construct_UDT& operator=(const nothrow_construct_UDT&){ return *this; }
  bool operator==(const nothrow_construct_UDT&)const
  { return true; }
};

class Base { };

class Derived : public Base { };
class Derived2 : public Base { };
class MultiBase : public Derived, public Derived2  { };
class PrivateBase : private Base { };

class NonDerived { };

enum enum1
{ one_,two_ };

enum enum2
{ three_,four_ };

struct VB
{ virtual ~VB() { }; };

struct VD : VB
{ ~VD() { }; };

// struct non_pointer:
// used to verify that is_pointer does not return
// true for class types that implement operator void*()

struct non_pointer
{ operator void*(){return this;} };
struct non_int_pointer
{
  int i;
  operator int*(){return &i;}
};
struct int_constructible
{ int_constructible(int); };
struct int_convertible
{ operator int(); };

// struct non_empty:
// used to verify that is_empty does not emit
// spurious warnings or errors.

struct non_empty : private noncopyable
{ int i; };

// abstract base classes:
struct test_abc1
{
  test_abc1();
  virtual ~test_abc1();
  test_abc1(const test_abc1&);
  test_abc1& operator=(const test_abc1&);
  virtual void foo() = 0;
  virtual void foo2() = 0;
};

struct test_abc2
{
  virtual ~test_abc2();
  virtual void foo() = 0;
  virtual void foo2() = 0;
};

struct test_abc3 : public test_abc1
{ virtual void foo3() = 0; };

struct incomplete_type;

struct polymorphic_base
{
  virtual ~polymorphic_base();
  virtual void method();
};

struct polymorphic_derived1 : polymorphic_base
{ };

struct polymorphic_derived2 : polymorphic_base
{ virtual void method(); };

struct virtual_inherit1 : virtual Base { };
struct virtual_inherit2 : virtual_inherit1 { };
struct virtual_inherit3 : private virtual Base { };
struct virtual_inherit4 : virtual noncopyable { };
struct virtual_inherit5 : virtual int_convertible { };
struct virtual_inherit6 : virtual Base { virtual ~virtual_inherit6()throw(); };

typedef void foo0_t();
typedef void foo1_t(int);
typedef void foo2_t(int&, double);
typedef void foo3_t(int&, bool, int, int);
typedef void foo4_t(int, bool, int*, int[], int, int, int, int, int);

struct trivial_except_construct
{
  trivial_except_construct();
  int i;
};

struct trivial_except_destroy
{
  ~trivial_except_destroy();
  int i;
};

struct trivial_except_copy
{
  trivial_except_copy(trivial_except_copy const&);
  int i;
};

struct trivial_except_assign
{
  trivial_except_assign& operator=(trivial_except_assign const&);
  int i;
};

template <class T>
struct wrap
{
  T t;
  int j;
protected:
  wrap();
  wrap(const wrap&);
  wrap& operator=(const wrap&);
};


struct convertible_to_pointer
{ operator char*() const; };


typedef const double (UDT::*mp2) ;


int
  main()
{
  // void types
  assert(evaluate<void                   >() == cat_void);
  assert(evaluate<void    const          >() == cat_void);
  assert(evaluate<void          volatile >() == cat_void);
  assert(evaluate<void    const volatile >() == cat_void);

  // integral types
  assert(evaluate<bool                   >() == cat_int);
  assert(evaluate<bool    const          >() == cat_int);
  assert(evaluate<bool          volatile >() == cat_int);
  assert(evaluate<bool    const volatile >() == cat_int);
  assert(evaluate<char                   >() == cat_int);
  assert(evaluate<char    const          >() == cat_int);
  assert(evaluate<char          volatile >() == cat_int);
  assert(evaluate<char    const volatile >() == cat_int);
  typedef  signed char  schar;
  assert(evaluate<schar                  >() == cat_int);
  assert(evaluate<schar   const          >() == cat_int);
  assert(evaluate<schar         volatile >() == cat_int);
  assert(evaluate<schar   const volatile >() == cat_int);
  typedef  unsigned char  uchar;
  assert(evaluate<uchar                  >() == cat_int);
  assert(evaluate<uchar   const          >() == cat_int);
  assert(evaluate<uchar         volatile >() == cat_int);
  assert(evaluate<uchar   const volatile >() == cat_int);
  assert(evaluate<short                  >() == cat_int);
  assert(evaluate<short   const          >() == cat_int);
  assert(evaluate<short         volatile >() == cat_int);
  assert(evaluate<short   const volatile >() == cat_int);
  typedef  unsigned short  ushort;
  assert(evaluate<ushort                 >() == cat_int);
  assert(evaluate<ushort  const          >() == cat_int);
  assert(evaluate<ushort        volatile >() == cat_int);
  assert(evaluate<ushort  const volatile >() == cat_int);
  assert(evaluate<int                    >() == cat_int);
  assert(evaluate<int     const          >() == cat_int);
  assert(evaluate<int           volatile >() == cat_int);
  assert(evaluate<int     const volatile >() == cat_int);
  typedef  unsigned int  uint;
  assert(evaluate<uint                   >() == cat_int);
  assert(evaluate<uint    const          >() == cat_int);
  assert(evaluate<uint          volatile >() == cat_int);
  assert(evaluate<uint    const volatile >() == cat_int);
  assert(evaluate<long                   >() == cat_int);
  assert(evaluate<long    const          >() == cat_int);
  assert(evaluate<long          volatile >() == cat_int);
  assert(evaluate<long    const volatile >() == cat_int);
  typedef  unsigned long  ulong;
  assert(evaluate<ulong                  >() == cat_int);
  assert(evaluate<ulong   const          >() == cat_int);
  assert(evaluate<ulong         volatile >() == cat_int);
  assert(evaluate<ulong   const volatile >() == cat_int);

  // floating-point types
  assert(evaluate<float                  >() == cat_flt);
  assert(evaluate<float   const          >() == cat_flt);
  assert(evaluate<float         volatile >() == cat_flt);
  assert(evaluate<float   const volatile >() == cat_flt);
  assert(evaluate<double                 >() == cat_flt);
  assert(evaluate<double  const          >() == cat_flt);
  assert(evaluate<double        volatile >() == cat_flt);
  assert(evaluate<double  const volatile >() == cat_flt);
  typedef  long double  ldouble;
  assert(evaluate<ldouble                >() == cat_flt);
  assert(evaluate<ldouble const          >() == cat_flt);
  assert(evaluate<ldouble       volatile >() == cat_flt);
  assert(evaluate<ldouble const volatile >() == cat_flt);

  // array types
  assert(evaluate<double              [1]>() == cat_arr);
  assert(evaluate<char const          [2]>() == cat_arr);
  assert(evaluate<float volatile      [3]>() == cat_arr);
  assert(evaluate<long const volatile [4]>() == cat_arr);
  assert(evaluate<mytype *            [6]>() == cat_arr);
  assert(evaluate<unsigned *          [6]>() == cat_arr);
  assert(evaluate<long double      [7][7]>() == cat_arr);
  assert(evaluate<UDT                 [2]>() == cat_arr);

  // pointer types
  assert(evaluate<char *                 >() == cat_ptr);
  assert(evaluate<int *                  >() == cat_ptr);
  assert(evaluate<int const *            >() == cat_ptr);
  assert(evaluate<int volatile *         >() == cat_ptr);
  assert(evaluate<int * *                >() == cat_ptr);
  assert(evaluate<int * * volatile       >() == cat_ptr);
  assert(evaluate<uint volatile *        >() == cat_ptr);
  assert(evaluate<long volatile * const  >() == cat_ptr);
  assert(evaluate<double * const *       >() == cat_ptr);
  assert(evaluate<float * const * const  >() == cat_ptr);
  assert(evaluate<int (*)(int)           >() == cat_ptr);
  assert(evaluate<non_pointer*           >() == cat_ptr);
  assert(evaluate<f1                     >() == cat_ptr);
  assert(evaluate<f2                     >() == cat_ptr);
  assert(evaluate<f3                     >() == cat_ptr);

  // lvalue reference types
  assert(evaluate<int &                  >() == cat_lref);
  assert(evaluate<int const &            >() == cat_lref);
  assert(evaluate<int volatile &         >() == cat_lref);
  assert(evaluate<int const volatile &   >() == cat_lref);
  assert(evaluate<int * &                >() == cat_lref);
  assert(evaluate<int (&)(int)           >() == cat_lref);
  assert(evaluate<int (&)[2]             >() == cat_lref);
  assert(evaluate<r_type                 >() == cat_lref);
  #if ! defined(_MSC_VER)
  assert(evaluate<cr_type                >() == cat_lref);
  #endif  // _MSC_VER
  assert(evaluate<UDT &                  >() == cat_lref);
  assert(evaluate<const UDT &            >() == cat_lref);
  assert(evaluate<volatile UDT &         >() == cat_lref);
  assert(evaluate<const volatile UDT &   >() == cat_lref);

  // member object pointer types
  assert(evaluate<int mytype::*          >() == cat_mem_obj_ptr);
  assert(evaluate<int mytype::* const    >() == cat_mem_obj_ptr);
  assert(evaluate<int mytype::* volatile >() == cat_mem_obj_ptr);
  assert(evaluate<mp                     >() == cat_mem_obj_ptr);
  assert(evaluate<mp2                    >() == cat_mem_obj_ptr);

  // member function pointer types
  assert(evaluate<int (mytype::*)()      >() == cat_mbr_fctn_ptr);
  assert(evaluate<int (mytype::*)()const >() == cat_mbr_fctn_ptr);
  assert(evaluate<int (mytype::*)(int)   >() == cat_mbr_fctn_ptr);
  assert(evaluate<mf1                    >() == cat_mbr_fctn_ptr);
  assert(evaluate<mf2                    >() == cat_mbr_fctn_ptr);
  assert(evaluate<mf3                    >() == cat_mbr_fctn_ptr);
  assert(evaluate<mf4                    >() == cat_mbr_fctn_ptr);
  assert(evaluate<cmf                    >() == cat_mbr_fctn_ptr);

  // enum types
  assert(evaluate<myenum                 >() == cat_enum);
  assert(evaluate<myenum const           >() == cat_enum);
  assert(evaluate<myenum volatile        >() == cat_enum);
  assert(evaluate<myenum const volatile  >() == cat_enum);
  assert(evaluate<enum_UDT               >() == cat_enum);

  // union types
  #if 0
  assert(evaluate<myblend                >() == cat_union);
  assert(evaluate<myblend const          >() == cat_union);
  assert(evaluate<myblend volatile       >() == cat_union);
  assert(evaluate<myblend const volatile >() == cat_union);
  assert(evaluate<union_UDT              >() == cat_union);
  assert(evaluate<POD_union_UDT          >() == cat_union);
  assert(evaluate<empty_union_UDT        >() == cat_union);
  assert(evaluate<empty_POD_union_UDT    >() == cat_union);
  assert(evaluate<union_UDT const        >() == cat_union);
  assert(evaluate<POD_union_UDT volatile >() == cat_union);
  assert(evaluate<empty_union_UDT const volatile>() == cat_union);
  assert(evaluate<empty_POD_union_UDT const>() == cat_union);
  #endif  // 0

  // class types
  assert(evaluate<UDT                    >() == cat_class);
  assert(evaluate<UDT const              >() == cat_class);
  assert(evaluate<UDT volatile           >() == cat_class);
  assert(evaluate<UDT const volatile     >() == cat_class);
  assert(evaluate<empty_UDT              >() == cat_class);
  assert(evaluate<test_abc1              >() == cat_class);
  assert(evaluate<test_abc1 const        >() == cat_class);
  assert(evaluate<std::iostream          >() == cat_class);

  // function types
  assert(evaluate<int (int)              >() == cat_fctn);
  assert(evaluate<void (int,float, long) >() == cat_fctn);
  assert(evaluate<foo0_t                 >() == cat_fctn);
  assert(evaluate<foo1_t                 >() == cat_fctn);
  assert(evaluate<foo2_t                 >() == cat_fctn);
  assert(evaluate<foo3_t                 >() == cat_fctn);
  assert(evaluate<foo4_t                 >() == cat_fctn);

  return 0;
}
