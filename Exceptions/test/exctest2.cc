// Test program to check out environment's exception-handling

#include <iostream>
using std::cerr;
using std::endl;


class Exception  {
public:
  Exception( const char [] )  {}
};


class Oops : public Exception  {
public:
  Oops( const char s[] ) : Exception( s )  {}
};


int main()  {

  try  {
    cerr << "Starting main() ..." << endl;

    cerr << "About to:  throw( Oops(\"Ouch\") )" << endl;
    const Exception & o = Oops("Ouch");
    throw o;
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
