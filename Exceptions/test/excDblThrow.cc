// Explore single- and double-throwing techniques


#include <iostream>
  using std::cerr;


struct B  {

  B()                         { cerr << "make B\n"; }
  B( B const & b )            { cerr << "copy B\n"; }
  virtual char  type() const  { return 'B'; };

};  // struct B


struct D : public B  {

  D()                         { cerr << "make D\n"; }
  D( const D & d ) : B( d )   { cerr << "copy D\n"; }
  virtual char  type() const  { return 'D'; };

};  // struct D


#define single( obj )               \
  cerr << "\nsingle( " #obj " )\n"; \
  const B &  ref = obj;             \
  throw ref;


#define double( obj )               \
  cerr << "\ndouble( " #obj " )\n"; \
  try  { throw obj; }               \
  catch ( const B & x )  { throw; }


void  f( void g() )  {

  try  { g(); }
//catch( D const & x )  { cerr << "Caught D is " << x.type() << '\n'; }
  catch( B const & x )  { cerr << "Caught B is " << x.type() << '\n'; }

}


void  test1()  { double( B() ); }
void  test2()  { double( D() ); }
void  test3()  { single( B() ); }
void  test4()  { single( D() ); }


int  main()  {

  cerr << "\nTesting double throws:\n";
  f( test1 );
  f( test2 );

  cerr << "\nTesting single throws:\n";
  f( test3 );
  f( test4 );

}
