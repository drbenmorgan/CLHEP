//--------------------------------------------------------------------------
#ifndef HEPMC_IO_ASCII_H
#define HEPMC_IO_ASCII_H

//////////////////////////////////////////////////////////////////////////
// Matt.Dobbs@Cern.CH, January 2000, refer to:
// M. Dobbs and J.B. Hansen, "The HepMC C++ Monte Carlo Event Record for
// High Energy Physics", Computer Physics Communications (to be published).
//
// event input/output in ascii format for machine reading
//////////////////////////////////////////////////////////////////////////
//
// Strategy for reading or writing events/particleData as machine readable
//  ascii to a file. When instantiating, the mode of file to be created 
//  must be specified. Options are:
//      HepIOS::in     open file for input 
//      HepIOS::out    open file for output
//      HepIOS::trunc  erase old file when opening (i.e. ios::out|ios::trunc
//                    removes oldfile, and creates a new one for output )
//      HepIOS::app    append output to end of file
//  for the purposes of this class, simultaneous input and output mode 
//  ( HepIOS::in | HepIOS::out ) is not allowed.
// 
// Event listings are preceded by the key:
//  "HepMC::IO_Ascii-START_EVENT_LISTING\n"
//  and terminated by the key:
//  "HepMC::IO_Ascii-END_EVENT_LISTING\n"
// Comments are allowed. They need not be preceded by anything, though if
//  a comment is written using write_comment( const string ) then it will be
//  preceded by "HepMC::IO_Ascii-COMMENT\n"
// Each event, vertex, particle, particle data is preceded by 
//  "E ","V ","P ","D "    respectively.
// Comments may appear anywhere in the file -- so long as they do not contain
//  any of the 4 start/stop keys.
//

// this is done in CLHEP/HepMC/defs.h
// --> HANDLE COMPILER INCONSISTENCIES
//#if __GNUC__ && (__GNUC__ > 2) // Linux gcc 3.x
//#define USE_OPENMODE_INSTEAD_OF_OPEN_MODE
//#endif // Platform
//
//#ifdef USE_OPENMODE_INSTEAD_OF_OPEN_MODE
//#define open_mode openmode
//#endif // USE_OPENMODE_INSTEAD_OF_OPEN_MODE


#include <fstream>
#include <string>
#include <map>
#include <vector>
#include <iostream>
#include "CLHEP/HepMC/defs.h"
#include "CLHEP/HepMC/GenEvent.h"

namespace HepMC {

    class IO_Ascii {
    public:
	IO_Ascii( const char* filename="IO_Ascii.dat", 
		  HepIOSOpenMode mode=HepIOS::out );
	~IO_Ascii();

	void          write_event( const GenEvent* evt );
	bool          fill_next_event( GenEvent* evt );
	// insert a comment directly into the output file --- normally you
	//  only want to do this at the beginning or end of the file. All
	//  comments are preceded with "HepMC::IO_Ascii-COMMENT\n"
  	void          write_comment( const std::string comment );

	int           rdstate() const;
	void          clear();

	void          print( std::ostream& ostr = std::cout ) const;
	//
	// read_next_event() differs from
	// the fill_***() method in that it creates a new event or pdt
	// before calling the  correspondingfill_*** method
	// (they are not intended to be over-ridden)
	GenEvent*    read_next_event();
	//
	// The overloaded stream operators >>,<< are identical to
	//   read_next_event and write_event methods respectively.
	// the event argument for the overloaded stream operators is a pointer,
	// which is passed by reference.
	//  i.e.  GenEvent* evt; 
	//        io >> evt; 
	// will give the expected result.
	// (note: I don't see any reason to have separate const and non-const
	//  versions of operator<<, but the pedantic ansi standard insists 
	//  on it) 
	      GenEvent*& operator>>( GenEvent*& );
	const GenEvent*& operator<<( const GenEvent*& );
	      GenEvent*& operator<<( GenEvent*& );

    protected: // for internal use only
	void          write_vertex( GenVertex* );
	void          write_particle( GenParticle* p );
	GenVertex*    read_vertex( std::map<GenParticle*,int>& 
				   particle_to_end_vertex );
	GenParticle*  read_particle( std::map<GenParticle*,int>& 
				     particle_to_end_vertex );
	bool          write_end_listing();
	bool          search_for_key_end( std::istream& in, 
					  const char* key);
	bool          search_for_key_beginning( std::istream& in, 
						const char* key );
	bool          eat_key( std::iostream& in, const char* key );
	int           find_in_map( const std::map<GenVertex*,int>& m, 
				   GenVertex* v) const;
	void          output( const double& );
	void          output( const int& );
	void          output( const long int& );
	void          output( const unsigned long int& );
	void          output( const char& );
    private: // use of copy constructor is not allowed
	IO_Ascii( const IO_Ascii& ) {}
    private: // data members
	HepIOSOpenMode m_mode;
	std::fstream        m_file;
	bool                m_finished_first_event_io;
    };

    //////////////
    // Inlines  //
    //////////////

    inline void IO_Ascii::output( const double& d ) {
	if ( d == 0. ) {
	    m_file << ' ' << (int)0;
	} else {
	    m_file << ' ' << d;
	}
    }
    inline void IO_Ascii::output( const int& i ) { m_file << ' ' << i; }
    inline void IO_Ascii::output( const long int& i ) { m_file << ' ' << i; }
    inline void IO_Ascii::output( const unsigned long int& i ) { m_file << ' ' << i; }
    inline void IO_Ascii::output( const char& c ) { m_file << c; }
    inline int  IO_Ascii::rdstate() const { return (int)m_file.rdstate(); }
    inline void IO_Ascii::clear() { m_file.clear(); }

    inline GenEvent* IO_Ascii::read_next_event() {
	// creates a new event and fills it by calling 
	// the sister method read_next_event( GenEvent* )
	// 
        // 1. create an empty event container
        GenEvent* evt = new GenEvent();
	// 2. fill the evt container - if the read is successful, return the
	//    pointer, otherwise return null and delete the evt
	if ( fill_next_event( evt ) ) return evt;
	// note: the below delete is only reached if read fails
	//       ... thus there is not much overhead in new then delete 
	//       since this statement is rarely reached
	delete evt;
	return 0;
    }

    inline GenEvent*& IO_Ascii::operator>>( GenEvent*& evt ){
	evt = read_next_event();
	return evt;
    }

    inline const GenEvent*& IO_Ascii::operator<<(
					      const GenEvent*& evt ) {
	write_event( evt );
	return evt;
    }

    inline GenEvent*& IO_Ascii::operator<<( GenEvent*& evt ) {
	write_event( evt );
	return evt;
    }

} // HepMC

#endif  // HEPMC_IO_ASCII_H
//--------------------------------------------------------------------------
