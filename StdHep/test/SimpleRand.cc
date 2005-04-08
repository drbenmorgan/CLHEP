//////////////////////////////////////////////////////////////////////////
// SimpleRand.cc
// Author: Lynn Garren
//
// Since it is unfair to introduce a dependency on CLHEP Random for the sake
// of the test, we use a simple, non-robust, interface to random() 
//////////////////////////////////////////////////////////////////////////

#include "SimpleRand.hh"

static const int MarkerLen = 64; // Enough room to hold a begin or end marker. 

SimpleRand::SimpleRand(long seed) 
: theSeed(seed), seq(0)
{
   setSeed(theSeed);
   seq = 0;
}

SimpleRand::SimpleRand()
: theSeed(197805031), seq(0)
{
   setSeed(theSeed);
   seq = 0;
}

SimpleRand::~SimpleRand() {}

void SimpleRand::setSeed(long seed)
{
   theSeed = seed;
   srand( int(seed) );
   seq = 0;
}

void SimpleRand::saveStatus( std::ostream& os ) const
{
   put(os);
}

std::ostream & SimpleRand::put ( std::ostream& os ) const
{
     char beginMarker[] = "SimpleRand-begin";
     char endMarker[]   = "SimpleRand-end";

     os << " " << beginMarker << "\n";
     os << theSeed << " " << seq << " ";
     os << endMarker << "\n";
     return os;
}

void SimpleRand::restoreStatus( std::istream& is )
{
   get( is );
}

std::istream & SimpleRand::get ( std::istream& is )
{
   // The only way to restore the status of SimpleRand is to
   // keep track of the number of shooted random sequences, reset
   // the engine and re-shoot them again. The Rand algorithm does
   // not provide any way of getting its internal status.
  char beginMarker [MarkerLen];
  is >> std::ws;
  is.width(MarkerLen);  // causes the next read to the char* to be <=
			// that many bytes, INCLUDING A TERMINATION \0 
			// (Stroustrup, section 21.3.2)
  is >> beginMarker;
  if (strcmp(beginMarker,"SimpleRand-begin")) {
     is.clear(std::ios::badbit | is.rdstate());
     std::cout << "\nInput stream mispositioned or"
	       << "\nSimpleRand state description missing or"
	       << "\nwrong engine type found." << std::endl;
     return is;
  }

  char endMarker   [MarkerLen];
  long count;
  is >> theSeed;
  is >> count;
  is >> std::ws;
  is.width(MarkerLen);  
  is >> endMarker;
  if (strcmp(endMarker,"SimpleRand-end")) {
     is.clear(std::ios::badbit | is.rdstate());
     std::cerr << "\nSimpleRand state description incomplete."
	       << "\nInput stream is probably mispositioned now." << std::endl;
     return is;
   }
   setSeed(theSeed);
   while (seq < count) flat();
   return is;
}
  

void SimpleRand::showStatus() const
{
   std::cout << std::endl;
   std::cout << "---------- Rand engine status ----------" << std::endl;
   std::cout << " Initial seed  = " << theSeed << std::endl;
   std::cout << " Shooted sequences = " << seq << std::endl;
   std::cout << "----------------------------------------" << std::endl;
}

                                                                          
unsigned int SimpleRand::SimpleRandBuilder() 
{ // RAND_MAX = 2**31 - 1
    unsigned int x = rand() << 1; ++seq; // bits 31-1                      
    x ^= ( (x>>23) ^ (x>>7) ) ^1;        // bit 0 (weakly pseudo-random)   
    return x & 0xFFFFFFFF;               // mask in case int is 64 bits    
}                                                                       
                                                                           
double SimpleRand::flat()                                      
{                                                              
  double r;                                                    
  do { r = SimpleRandBuilder();
     } while ( r == 0 ); 
  return r/4294967296.0; 
}  

SimpleRand::operator unsigned int() {
  return SimpleRandBuilder();
}
