#include <iostream> 
#include <stdexcept>
#include <stdint.h>
#include "CLHEP/Random/RanecuEngine.h"
#include "CLHEP/Random/Random.h"

int main() { 
	std::cout << std::endl << "short " << sizeof(short) << std::endl; 
	std::cout << "int " << sizeof(int) << std::endl; 
	std::cout << "unsigned int " << sizeof(unsigned int) << std::endl; 
	std::cout << "long " << sizeof(long) << std::endl; 
//	std::cout << "long long " << sizeof(long long) << std::endl; 
	std::cout << "float " << sizeof(float) << std::endl; 
	std::cout << "double " << sizeof(double) << std::endl; 
	std::cout << "long double " << sizeof(long double) << std::endl << std::endl; 

//long x=2315432636836836423; 
//CLHEP::RanecuEngine eng(x);

	CLHEP::RanecuEngine *eng = new CLHEP::RanecuEngine;
	CLHEP::HepRandom::setTheEngine(eng);
	CLHEP::HepRandom *g;
	g=CLHEP::HepRandom::getTheGenerator();
	
	int badcount = 0;

	long rvals[2];
	try {
		std::ifstream in("/dev/urandom", std::ios::in | std::ios::binary);
		if(in.is_open()) {
			in.read((char *)(&rvals), 2*sizeof(long));
			in.close();
			if(in.fail()) {
				throw std::runtime_error("File read error");
			}
		} else throw std::runtime_error("File open error");
	} catch(std::runtime_error e) {
		std::ostringstream dStr;
		dStr << "Error: " << e.what() 
		<< " processing seed from file \"" << "/dev/urandom" << "\"."; 
		++badcount;
		throw std::runtime_error(dStr.str().c_str());
	}

	int nNumbers = 20; 

	long seeds[3];
	//***********************************************************************
	// If either of these is negative then the generator generates the same
	// sequence of numbers no matter what the seeds are. There is no warning that
	// the sequence is not really responding to the attempt to create a random
	// initial condition. If on the other hand, both of the initial values
	// happen to be positive, as will happen about 1/4 of the time, then the
	// genertor fails. My conjecture is that eventually both seeds may randomly
	// fall in the range of 32 bit integers, at which point a stable valid  
	// sequence begins.
	seeds[0]=rvals[0];
	seeds[1]=rvals[1];
	seeds[2]=0;

	std::cout << std::endl << "********************" << std::endl;
	std::cout << "This is the case that may or may not fail." << std::endl;
	std::cout << "However, if it has values in (0,1), they are a " << std::endl
				<< "deterministic sequence beginning with 0.154707." << std::endl;
	std::cout << "seeds[0] = " << seeds[0] << "\n" 
				<< "seeds[1] = " << seeds[1] << std::endl << std::endl;

	g->setTheSeeds(seeds);
	for (int i=0; i < nNumbers; ++i) { 
		double r = g->flat(); 
		std::cout << i << " " << r << std::endl; 
		if (r < 0 || r > 1.0 ) {
                    std::cout << "Error: bad random number " << r << std::endl; 
		    ++badcount;
                }
	}
	const long *pseeds=g->getTheSeeds();
	std::cout << "Final seeds[0] = " << pseeds[0] << "\n" 
				<< "Final seeds[1] = " << pseeds[1] << std::endl << std::endl;

	//***********************************************************************
	// Forcing these seeds to positive values reliably crashes the generator.
	seeds[0]=std::abs(rvals[0]);
	seeds[1]=std::abs(rvals[1]);
	seeds[2]=0;

	std::cout << std::endl << "********************" << std::endl;
	std::cout << "This is the case that always fails." << std::endl;
	std::cout << "seeds[0] = " << seeds[0] << "\n" 
				<< "seeds[1] = " << seeds[1] << std::endl << std::endl;

	g->setTheSeeds(seeds);
	for (int i=0; i < nNumbers; ++i) { 
		double r = g->flat(); 
		std::cout << i << " " << r << std::endl; 
		if (r < 0 || r > 1.0 ) {
                    std::cout << "Error: bad random number " << r << std::endl; 
		    ++badcount;
                }
	}
	pseeds=g->getTheSeeds();
	std::cout << "Final seeds[0] = " << pseeds[0] << "\n" 
				<< "Final seeds[1] = " << pseeds[1] << std::endl << std::endl;

	//***********************************************************************
	// 4-byte positive integers generate valid sequences, which appear to remain
	// within bounds.
	seeds[0]= std::abs(static_cast<int32_t>(rvals[0]));
	seeds[1]= std::abs(static_cast<int32_t>(rvals[1]));
	seeds[2]=0;

	std::cout << std::endl << "********************" << std::endl;
	std::cout << "This is the case that works." << std::endl;
	std::cout << std::endl << "seeds[0] = " << seeds[0] << "\n" 
				<< "seeds[1] = " << seeds[1] << "\n"
				<< "seeds[2] = " << seeds[2] << std::endl << std::endl;

	g->setTheSeeds(seeds);
	for (int i=0; i < nNumbers; ++i) { 
		double r = g->flat(); 
		std::cout << i << " " << r << std::endl; 
		if (r < 0 || r > 1.0 ) {
                    std::cout << "Error: bad random number " << r << std::endl; 
		    ++badcount;
                }
	} 
	pseeds=g->getTheSeeds();
	std::cout << "Final seeds[0] = " << pseeds[0] << "\n" 
				<< "Final seeds[1] = " << pseeds[1] << std::endl << std::endl;

	//***********************************************************************
	// This tests the conjecture that eventually a bad sequence will rectify
	// itself. This starts with the seeds that always fail and loops until both
	// seeds are in the range of positive 32-bit integers. It appears from
	// my early tests that my conjecture of a stable correct region that
	// the generator falls into may be correct.
	seeds[0]=std::abs(rvals[0]);
	seeds[1]=std::abs(rvals[1]);
	seeds[2]=0;

	std::cout << std::endl << "********************" << std::endl;
	std::cout << "This case loops until it valid short seeds occur." << std::endl;
	std::cout << "seeds[0] = " << seeds[0] << "\n" 
				<< "seeds[1] = " << seeds[1] << std::endl << std::endl;

	g->setTheSeeds(seeds);
	// Loop as long as the values are bad.
	double r;
	unsigned int low = ~0;
//	unsigned long mask = ~static_cast<unsigned long>(low);
	unsigned long mask = (~0) << 31;
	unsigned long skipcount = 0;
	std::cout << "low = " << low << "  mask = " << mask << std::endl;
	do {r = g->flat(); pseeds = g->getTheSeeds(); ++skipcount;} 
		while((pseeds[0]&mask) || (pseeds[1]&mask));

	std::cout << std::endl << "Loop terminates on two short seeds." << std::endl;
	std::cout << "Skipcount = " << skipcount << std::endl;
	std::cout << "pseeds[0]&mask = " << (pseeds[0]&mask) << std::endl;
	std::cout << "pseeds[1]&mask = " << (pseeds[1]&mask) << std::endl;
	std::cout << "Final seeds[0] = " << pseeds[0] << "\n" 
				<< "Final seeds[1] = " << pseeds[1] << std::endl << std::endl;

	std::cout << "This should be a valid sequence." << std::endl;	
	for (int i=0; i < nNumbers; ++i) { 
		double r = g->flat(); 
		std::cout << i << " " << r << std::endl; 
		if (r < 0 || r > 1.0 ) {
                    std::cout << "Error: bad random number " << r << std::endl; 
		    ++badcount;
                }
	}
	pseeds=g->getTheSeeds();
	std::cout << "seeds[0] = " << pseeds[0] << "\n" 
				<< "seeds[1] = " << pseeds[1] << std::endl << std::endl;

        if( badcount > 0 ) std::cout << "Found " << badcount << " bad seeds" << std::endl;
	return badcount; 
} 
