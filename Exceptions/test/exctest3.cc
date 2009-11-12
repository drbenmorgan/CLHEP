// Test program to check out the environment exception-handling

#include <iostream>
using std::cerr;
using std::endl;


class Exception  {
public:
  Exception( const char [] )  {}
  virtual ~Exception() {}
  virtual void f() const { cerr << "Exception::f()" << endl; }
};


class Oops : public Exception  {
public:
  Oops( const char s[] ) : Exception( s )  {}
  virtual ~Oops() {}
  virtual void f() const { cerr << "Oops::f()" << endl; }
};


int main()  {

  try  {
    cerr << "Starting main() ..." << endl;
    cerr << "About to:  throw( Oops(\"Ouch\") )" << endl;

    try { throw Oops("Ouch"); }
    catch ( const Exception & x )  {
      x.f();
      throw;
    }
    catch ( ... )  {
      cerr << "Caught unknown!" << endl;
      throw;
    }

    // Unreachable statement (we certainly hope!):
    cerr << "The following ought to produce a compilation warning \n"
         << "Got past:  throw( Oops(\"Ouch\") ) -- not good!" << endl;
  }
  catch ( const Oops & egad )  {
    cerr << "Caught:  Oops" << endl;
  }
  catch ( const Exception & egad )  {
    cerr << "Caught:  Exception" << endl;
  }
  catch ( ... )  {
    cerr << "Caught:  don't know what" << endl;
  }

  cerr << "Done." << endl;
  return 0;

}  // main()
