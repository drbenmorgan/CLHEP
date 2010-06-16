// ======================================================================
// -*- C++ -*-
// $Id: testIsConvertible.cc,v 1.2 2010/06/16 14:15:01 garren Exp $
// ---------------------------------------------------------------------------
// Test is_convertible type trait
//
// W. E. Brown, 2010-03-19
// based on work by John Maddock
// ======================================================================


#include <CLHEP/Utility/noncopyable.h>
#include <CLHEP/Utility/type_traits.h>
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
class MultiBase : public Derived, public Derived2 { };
class PrivateBase : private Base { };

class NonDerived { };

enum enum1
{
  one_,two_
};

enum enum2
{
  three_,four_
};

struct VB
{
  virtual ~VB() { };
};

struct VD : VB
{
  ~VD() { };
};

// struct non_pointer:
// used to verify that is_pointer does not return
// true for class types that implement operator void*()
//
struct non_pointer
{
  operator void*(){return this;}
};
struct non_int_pointer
{
  int i;
  operator int*(){return &i;}
};
struct int_constructible
{
  int_constructible(int);
};
struct int_convertible
{
  operator int();
};
//
// struct non_empty:
// used to verify that is_empty does not emit
// spurious warnings or errors.
//
struct non_empty : private noncopyable
{
  int i;
};
//
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
{
  virtual void foo3() = 0;
};

struct incomplete_type;

struct polymorphic_base
{
  virtual ~polymorphic_base();
  virtual void method();
};

struct polymorphic_derived1 : polymorphic_base
{
};

struct polymorphic_derived2 : polymorphic_base
{
  virtual void method();
};

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

template< typename T >
struct wrap
{
  T t;
  int j;
protected:
  wrap();
  wrap(const wrap&);
  wrap& operator=(const wrap&);
};


template< typename T >
struct convertible_from
{ convertible_from(T); };

struct base2 { };
struct middle2 : virtual base2 { };
struct derived2 : middle2 { };


int main()
{
  #define conversion_claim(From,To) (is_convertible<From,To>::value)
  #define does_convert(From,To)     assert(conversion_claim(From,To))
  #define does_not_convert(From,To) assert(!conversion_claim(From,To))

  does_not_convert(NonDerived,Base);

  does_convert(Base,Base);
  does_convert(Derived,Base);
  does_convert(Derived,Derived);
  does_not_convert(Base,Derived);

  does_convert(Derived&, Base&);
  does_convert(const Derived&, const Base&);
  does_not_convert(Base&, Derived&);
  does_not_convert(const Base&, const Derived&);

  does_convert(Derived*, Base*);
  does_convert(const Derived*, const Base*);
  does_not_convert(Base*, Derived*);
  does_not_convert(const Base*, const Derived*);

  does_convert(polymorphic_derived1,polymorphic_base);
  does_convert(polymorphic_derived2,polymorphic_base);
  does_not_convert(polymorphic_base,polymorphic_derived1);
  does_not_convert(polymorphic_base,polymorphic_derived2);

  does_convert(virtual_inherit2,virtual_inherit1);
  does_convert(VD,VB);

  does_convert(void,void);
  does_not_convert(void,float);
  does_convert(float,void);
  //does_convert(float,int);

  does_convert(enum1, int);

  does_not_convert(const int *, int*);
  does_not_convert(const int&, int&);
  does_not_convert(const int*, int[3]);
  does_convert(const int&, int);
  does_convert(int(&)[4], const int*);
  does_convert(int(&)(int), int(*)(int));
  does_convert(int *, const int*);
  does_convert(int&, const int&);
  does_convert(int[2], int*);
  does_convert(int[2], const int*);
  does_not_convert(const int[2], int*);
  does_not_convert(int*, int[3]);
  //does_convert(test_abc3, const test_abc1&);

  does_convert(non_pointer, void*);
  does_not_convert(non_pointer, int*);
  does_convert(non_int_pointer, int*);
  does_convert(non_int_pointer, void*);

  does_not_convert(test_abc1&, test_abc2&);
  does_not_convert(test_abc1&, int_constructible);
  does_not_convert(int_constructible, test_abc1&);

  does_not_convert(test_abc1&, test_abc2);

  #if defined(__GNUC__) && ((__GNUC__ < 4) || (__GNUC_MINOR__ < 2))
    // known to be defective
  #elif defined(_MSC_VER)  && (_MSC_VER <= 1400)
    // known to be defective
  #else
    // let's give it a try
  does_convert(int, int_constructible);
  does_convert(float,convertible_from<float> );
  does_convert(float,convertible_from<float const&> );
  does_convert(float,convertible_from<float&> );

  does_convert(float,convertible_from<char> );
  does_convert(float,convertible_from<char const&> );
  does_not_convert(float,convertible_from<char&> );

  does_convert(char,convertible_from<char> );
  does_convert(char,convertible_from<char const&> );
  does_convert(char,convertible_from<char&> );

  does_convert(float&,convertible_from<float> );
  does_convert(float const&,convertible_from<float> );
  does_convert(float&,convertible_from<float&> );
  does_convert(float const&,convertible_from<float const&> );
  does_convert(float&,convertible_from<float const&> );
  #endif  // compiler

  return 0;
}
