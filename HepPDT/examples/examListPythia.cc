// ----------------------------------------------------------------------
// examListPythia.cc
//
// list Pythia particle ID translations
//
// ----------------------------------------------------------------------

#include "CLHEP/HepPDT/defs.h"
#include <fstream>

#include "CLHEP/HepPDT/TranslationList.hh"

extern "C" {
    void list_pythia_ ( );
}

int main()
{
    const char infile[] = "data/pythia.tbl";
    const char outfile[] = "examListPythia.out";
    // open input file
    std::ifstream pdfile( infile );
    if( !pdfile ) { 
      std::cerr << "cannot open " << infile << std::endl;
      exit(-1);
    }
    // open the output file
    std::ofstream os( outfile );
    if( !os ) { 
      std::cerr << "cannot open " << outfile << std::endl;
      exit(-1);
    }
    // get Pythia listing using the fortran pylist function
    // write the output of pylist to examListPythia.lpt
    list_pythia_();
    // just call the list function, which returns a bool
    return HepPDT::listPythiaTranslation( pdfile, os);
}
