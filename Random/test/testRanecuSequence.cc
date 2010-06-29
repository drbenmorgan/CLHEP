// ----------------------------------------------------------------------
//
// testRanecuSequence 
// look at report that certain seeds produce identical sequences
// 
// ----------------------------------------------------------------------
#include <iostream> 
#include <string>
#include <vector>
#include "CLHEP/Random/RanecuEngine.h"
#include "CLHEP/Random/Random.h"

struct Sample {
    int seed;
    std::vector<double> case1;
    std::vector<double> case2;
    std::vector<double> case3;
    std::vector<double> case4;
    std::vector<double> case5;
};

void useSeed( int, std::vector<Sample>& );

bool compareSamples( Sample&, Sample&, std::ofstream& );

int main() { 

    std::ofstream output("testRanecuSequence.output");  

    output << " Setting CLHEP Random Engine..." << std::endl;
    CLHEP::HepRandom::setTheEngine(new CLHEP::RanecuEngine);
    
    std::vector<Sample> ranList;

    // the first 4 seeds once resulted in identical sequences
    useSeed(1275177715, ranList);
    useSeed(1275171265, ranList);
    useSeed(1275168040, ranList);
    useSeed(1275168040-2048*215, ranList);
    useSeed(4132429, ranList);
    useSeed(-1357924, ranList);
    
    int sd = 53208134;
    for ( int i = 0; i < 1000; ++i ) {
        ++sd;
	useSeed(sd, ranList);
    }
    
    int numbad = 0;
    output << std::endl;
    for ( unsigned int it=0; it < ranList.size(); ++it ) {
        for ( unsigned int jt=it+1; jt < ranList.size(); ++jt ) {
	    if( ! compareSamples(ranList[it], ranList[jt], output ) ) {
	        ++numbad;
	        output << "ERROR: Seed " << ranList[it].seed 
		       << " and Seed " << ranList[jt].seed 
		       << " are " << (ranList[jt].seed - ranList[it].seed )
		       << " apart and result in identical sequences" << std::endl;
	        std::cerr << "Seed " << ranList[it].seed 
		          << " and Seed " << ranList[jt].seed 
			  << " are " << (ranList[jt].seed - ranList[it].seed )
			  << " apart and result in identical sequences" << std::endl;
	    }
	}
    }

    output << " numbad is " << numbad << std::endl;
    return numbad;
} 

void useSeed( int seed, std::vector<Sample>& ranList )
{
    Sample v;
    v.seed = seed;
// case 1  -- default constructor
    CLHEP::RanecuEngine c1;
    for( int i = 0; i < 15; ++i ) {
        v.case1.push_back( c1.flat() );
    }
// case 2
    CLHEP::RanecuEngine c2(seed);
    for( int i = 0; i < 15; ++i ) {
        v.case2.push_back( c2.flat() );
    }
// case 3 - use HepRandom
    CLHEP::HepRandom::setTheSeed(seed);
    for( int i = 0; i < 15; ++i ) {
        v.case3.push_back(  CLHEP::HepRandom::getTheEngine()->flat() );
    }
// case 4
    CLHEP::RanecuEngine c4(1);
    c4.setSeed(seed);
    for( int i = 0; i < 15; ++i ) {
        v.case4.push_back( c4.flat() );
    }
// case 5
    CLHEP::RanecuEngine c5(1);
    long seedarray[2];
    seedarray[0] = seed;
    seedarray[1] = 1;
    c5.setSeeds(seedarray,2);
    for( int i = 0; i < 15; ++i ) {
        v.case5.push_back( c5.flat() );
    }
//
    ranList.push_back(v);

}

bool compareSamples( Sample& s1, Sample& s2, std::ofstream& output )
{
    if ( s1.case1 == s2.case1 ) {
        output << " case1:  default constructor \n" ;
        output << " comparing Seed " << s1.seed << " and Seed " << s2.seed << std::endl;
        output << " case1 sequence:" ;
	for( unsigned int i=0; i < s1.case1.size(); ++i ) output << " " << s1.case1[i];
	output << std::endl;
        return false;
    }
    if ( s1.case2 == s2.case2 ) {
        output << " case2:  construct with single seed \n" ;
        output << " comparing Seed " << s1.seed << " and Seed " << s2.seed << std::endl;
        output << " case2 sequence:" ;
	for( unsigned int i=0; i < s1.case2.size(); ++i ) output << " " << s1.case2[i];
	output << std::endl;
        return false;
    }
    if ( s1.case3 == s2.case3 ) {
        output << " case3:  construct with single seed \n" ;
        output << " comparing Seed " << s1.seed << " and Seed " << s2.seed << std::endl;
        output << " case3 sequence:" ;
	for( unsigned int i=0; i < s1.case3.size(); ++i ) output << " " << s1.case3[i];
	output << std::endl;
        return false;
    }
    if ( s1.case4 == s2.case4 ) {
        output << " case4:  use setSeed \n" ;
        output << " comparing Seed " << s1.seed << " and Seed " << s2.seed << std::endl;
        output << " case4 sequence:" ;
	for( unsigned int i=0; i < s1.case4.size(); ++i ) output << " " << s1.case4[i];
	output << std::endl;
        return false;
    }
    if ( s1.case5 == s2.case5 ) {
        output << " case5:  use setSeeds \n" ;
        output << " comparing Seed " << s1.seed << " and Seed " << s2.seed << std::endl;
        output << " case5 sequence:" ;
	for( unsigned int i=0; i < s1.case5.size(); ++i ) output << " " << s1.case5[i];
	output << std::endl;
        return false;
    }

    return true;
}
