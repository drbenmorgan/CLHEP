// ======================================================================
//
// Test basic functionality of primary type traits
//
// Author:  W. E. Brown, 2010-03-24, adapted from the boost library's
// type_traits and related functionality whose internal attributions bear
// the following various notices:
//
//   (C) Copyright John Maddock 2000.
//   Distributed under the Boost Software License, Version 1.0.
//   See http://www.boost.org/LICENSE_1_0.txt
//
// ======================================================================


#include "CLHEP/Utility/noncopyable.h"
#include "CLHEP/Utility/type_traits.h"

#include <cassert>


using namespace CLHEP;


// define some test types:

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


int main()
{
  #define claim_void(Type)       (is_void<Type>::value)
  #define has_void_type(Type)    assert(claim_void(Type))
  #define has_nonvoid_type(Type) assert(!claim_void(Type))

  has_void_type(void);
  has_void_type(void const);
  has_void_type(void volatile);
  has_void_type(void const volatile);

  has_nonvoid_type(void*);
  has_nonvoid_type(int);
  has_nonvoid_type(test_abc1);
  has_nonvoid_type(foo0_t);
  has_nonvoid_type(foo1_t);
  has_nonvoid_type(foo2_t);
  has_nonvoid_type(foo3_t);
  has_nonvoid_type(foo4_t);
  has_nonvoid_type(incomplete_type);

  #define claim_integral(Type)       (is_integral<Type>::value)
  #define has_integral_type(Type)    assert(claim_integral(Type))
  #define has_nonintegral_type(Type) assert(!claim_integral(Type))

  has_integral_type(bool);
  has_integral_type(bool const);
  has_integral_type(bool volatile);
  has_integral_type(bool const volatile);

  has_integral_type(signed char);
  has_integral_type(signed char const);
  has_integral_type(signed char volatile);
  has_integral_type(signed char const volatile);
  has_integral_type(unsigned char);
  has_integral_type(char);
  has_integral_type(unsigned char const);
  has_integral_type(char const);
  has_integral_type(unsigned char volatile);
  has_integral_type(char volatile);
  has_integral_type(unsigned char const volatile);
  has_integral_type(char const volatile);

  has_integral_type(unsigned short);
  has_integral_type(short);
  has_integral_type(unsigned short const);
  has_integral_type(short const);
  has_integral_type(unsigned short volatile);
  has_integral_type(short volatile);
  has_integral_type(unsigned short const volatile);
  has_integral_type(short const volatile);

  has_integral_type(unsigned int);
  has_integral_type(int);
  has_integral_type(unsigned int const);
  has_integral_type(int const);
  has_integral_type(unsigned int volatile);
  has_integral_type(int volatile);
  has_integral_type(unsigned int const volatile);
  has_integral_type(int const volatile);

  has_integral_type(unsigned long);
  has_integral_type(long);
  has_integral_type(unsigned long const);
  has_integral_type(long const);
  has_integral_type(unsigned long volatile);
  has_integral_type(long volatile);
  has_integral_type(unsigned long const volatile);
  has_integral_type(long const volatile);

  has_nonintegral_type(void);
  has_nonintegral_type(float);
  has_nonintegral_type(UDT);
  has_nonintegral_type(test_abc1);
  has_nonintegral_type(empty_UDT);
  has_nonintegral_type(int*);
  has_nonintegral_type(int&);
  has_nonintegral_type(const int&);
  has_nonintegral_type(int[2]);
  has_nonintegral_type(test_abc1);
  has_nonintegral_type(foo0_t);
  has_nonintegral_type(foo1_t);
  has_nonintegral_type(foo2_t);
  has_nonintegral_type(foo3_t);
  has_nonintegral_type(foo4_t);
  has_nonintegral_type(incomplete_type);

  #define claim_floating(Type)       (is_floating_point<Type>::value)
  #define has_floating_type(Type)    assert(claim_floating(Type))
  #define has_nonfloating_type(Type) assert(!claim_floating(Type))

  has_floating_type(float);
  has_floating_type(float const);
  has_floating_type(float volatile);
  has_floating_type(float const volatile);

  has_floating_type(double);
  has_floating_type(double const);
  has_floating_type(double volatile);
  has_floating_type(double const volatile);

  has_floating_type(long double);
  has_floating_type(long double const);
  has_floating_type(long double volatile);
  has_floating_type(long double const volatile);

  has_nonfloating_type(void);
  has_nonfloating_type(int);
  has_nonfloating_type(UDT);
  has_nonfloating_type(test_abc1);
  has_nonfloating_type(empty_UDT);
  has_nonfloating_type(float*);
  has_nonfloating_type(float&);
  has_nonfloating_type(const float&);
  has_nonfloating_type(float[2]);

  has_nonfloating_type(test_abc1);
  has_nonfloating_type(foo0_t);
  has_nonfloating_type(foo1_t);
  has_nonfloating_type(foo2_t);
  has_nonfloating_type(foo3_t);
  has_nonfloating_type(foo4_t);
  has_nonfloating_type(incomplete_type);

  #define claim_array(Type)       (is_array<Type>::value)
  #define has_array_type(Type)    assert(claim_array(Type))
  #define has_nonarray_type(Type) assert(!claim_array(Type))

  has_nonarray_type(int);
  has_nonarray_type(int*);
  has_nonarray_type(const int*);
  has_nonarray_type(const volatile int*);
  has_nonarray_type(int*const);
  has_nonarray_type(const int*volatile);
  has_nonarray_type(const volatile int*const);
  has_array_type(int[2]);
  has_array_type(const int[2]);
  has_array_type(const volatile int[2]);
  has_array_type(int[2][3]);
  has_array_type(UDT[2]);
  has_nonarray_type(int(&)[2]);
  has_nonarray_type(f1);
  has_nonarray_type(void);
  has_nonarray_type(test_abc1);
  has_nonarray_type(convertible_to_pointer);
  has_nonarray_type(test_abc1);
  has_nonarray_type(foo0_t);
  has_nonarray_type(incomplete_type);

  #define claim_ptr(Type)       (is_pointer<Type>::value)
  #define has_ptr_type(Type)    assert(claim_ptr(Type))
  #define has_nonptr_type(Type) assert(!claim_ptr(Type))

  has_nonptr_type(int);
  has_nonptr_type(int&);
  has_ptr_type(int*);
  has_ptr_type(const int*);
  has_ptr_type(volatile int*);
  has_ptr_type(non_pointer*);
  has_ptr_type(int*const);
  has_ptr_type(int*volatile);
  has_ptr_type(int*const volatile);
  has_nonptr_type(non_pointer);
  has_nonptr_type(int*&);
  has_nonptr_type(int(&)[2]);
  has_nonptr_type(int[2]);
  has_nonptr_type(char[sizeof(void*)]);
  has_nonptr_type(void);

  has_ptr_type(f1);
  has_ptr_type(f2);
  has_ptr_type(f3);
  has_nonptr_type(mf1);
  has_nonptr_type(mf2);
  has_nonptr_type(mf3);
  has_nonptr_type(mf4);
  has_nonptr_type(test_abc1);

  has_nonptr_type(foo0_t);
  has_nonptr_type(foo1_t);
  has_nonptr_type(foo2_t);
  has_nonptr_type(foo3_t);
  has_nonptr_type(foo4_t);

  has_nonptr_type(test_abc1);

  #define claim_lref(Type)       (is_lvalue_reference<Type>::value)
  #define has_lref_type(Type)    assert(claim_lref(Type))
  #define has_nonlref_type(Type) assert(!claim_lref(Type))

  #define claim_ref(Type)       (is_reference<Type>::value)
  #define has_ref_type(Type)    assert(claim_ref(Type))
  #define has_nonref_type(Type) assert(!claim_ref(Type))

  #define lref(Type)   has_lref_type(Type);    has_ref_type(Type);
  #define nonref(Type) has_nonlref_type(Type); has_nonref_type(Type);

  lref(int&);
  lref(const int&);
  lref(volatile int &);
  lref(const volatile int &);
  lref(r_type);
  #if ! defined(_MSC_VER)
  lref(cr_type);
  #endif  // _MSC_VER
  lref(UDT&);
  lref(const UDT&);
  lref(volatile UDT&);
  lref(const volatile UDT&);
  lref(int (&)(int));
  lref(int (&)[2]);

  nonref(int [2]);
  nonref(const int [2]);
  nonref(volatile int [2]);
  nonref(const volatile int [2]);
  nonref(bool);
  nonref(void);
  nonref(test_abc1);
  nonref(foo0_t);
  nonref(incomplete_type);

  #define claim_mbrobjptr(Type)       (is_member_object_pointer<Type>::value)
  #define has_mbrobjptr_type(Type)    assert(claim_mbrobjptr(Type))
  #define has_nonmbrobjptr_type(Type) assert(!claim_mbrobjptr(Type))

  has_nonmbrobjptr_type(f1);
  has_nonmbrobjptr_type(f2);
  has_nonmbrobjptr_type(f3);
  has_nonmbrobjptr_type(void*);
  has_nonmbrobjptr_type(mf1);
  has_nonmbrobjptr_type(mf2);
  has_nonmbrobjptr_type(mf3);
  has_nonmbrobjptr_type(mf4);
  has_nonmbrobjptr_type(cmf);
  has_mbrobjptr_type(mp);
  has_mbrobjptr_type(mp2);
  has_nonmbrobjptr_type(void);
  has_nonmbrobjptr_type(test_abc1);
  has_nonmbrobjptr_type(foo0_t);

  #define claim_mbrfctnptr(Type)       (is_member_function_pointer<Type>::value)
  #define has_mbrfctnptr_type(Type)    assert(claim_mbrfctnptr(Type))
  #define has_nonmbrfctnptr_type(Type) assert(!claim_mbrfctnptr(Type))

  has_nonmbrfctnptr_type(f1);
  has_nonmbrfctnptr_type(f2);
  has_nonmbrfctnptr_type(f3);
  has_nonmbrfctnptr_type(void*);
  has_mbrfctnptr_type(mf1);
  has_mbrfctnptr_type(mf2);
  has_mbrfctnptr_type(mf3);
  has_mbrfctnptr_type(mf4);
  has_mbrfctnptr_type(cmf);
  has_nonmbrfctnptr_type(mp);
  has_nonmbrfctnptr_type(void);
  has_nonmbrfctnptr_type(test_abc1);
  has_nonmbrfctnptr_type(foo0_t);
  has_nonmbrfctnptr_type(int&);
  has_nonmbrfctnptr_type(const int&);
  has_nonmbrfctnptr_type(const int[2]);
  has_nonmbrfctnptr_type(const int[]);
  has_nonmbrfctnptr_type(void);

  #define claim_enum(Type)       (is_enum<Type>::value)
  #define has_enum_type(Type)    assert(claim_enum(Type))
  #define has_nonenum_type(Type) assert(!claim_enum(Type))

  has_nonenum_type(int);
  has_nonenum_type(long double);
  has_enum_type(enum_UDT);
  has_nonenum_type(int_convertible);
  has_nonenum_type(int&);
  has_nonenum_type(noncopyable);
  has_nonenum_type(void);
  has_nonenum_type(test_abc1);
  has_nonenum_type(foo0_t);
  has_nonenum_type(int&);
  has_nonenum_type(const int&);
  has_nonmbrfctnptr_type(const int[2]);
  has_nonmbrfctnptr_type(const int[]);
  has_nonmbrfctnptr_type(void);

  return 0;
}
