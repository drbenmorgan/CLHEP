#include <iostream>
using std::cerr;
using std::endl;


#include "CLHEP/Exceptions/ZMexception.h"
#include "CLHEP/Exceptions/ZMthrow.h"
using namespace zmex;


ZMexStandardDefinition(ZMexception,Oops);
ZMexClassInfo Oops::_classInfo( "Oops", "exctest1", ZMexERROR );


int main()  {

  cerr << "Starting main() ..." << endl;

#ifndef DEFECT_NO_EXCEPTIONS
  try  {
#endif
    //cerr << "About to:  Oops::setHandler( ZMexHandler( ZMexIgnoreAlways() ) );
    //Oops::setHandler( ZMexHandler( ZMexIgnoreAlways() ) );

    cerr << "About to:  ZMthrow( Oops(\"Ouch\") )" << endl;
    ZMthrow( Oops("Ouch") );
    // unreachable statement:
    cerr << "Got past:  ZMthrow( Oops(\"Ouch\") ) -- not good!" << endl;
#ifndef DEFECT_NO_EXCEPTIONS
  }
  catch ( const Oops egad )  {
    cerr << "Caught:  Oops" << endl;
  }
  catch ( const ZMexception egad )  {
    cerr << "Caught:  ZMexception" << endl;
  }
  catch ( ... )  {
    cerr << "Caught:  don't know what" << endl;
  }
#endif

  cerr << "Done." << endl;
  return 0;

}  // main()
