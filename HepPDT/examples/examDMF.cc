////////////////////////////////////////////////////////////////////////
//
// File: TestDMF.cc
// $Id: examDMF.cc,v 1.1.1.1 2003/07/15 20:15:05 garren Exp $
// Purpose: Test of the DMFactory class template
//
// Author:  Marc Paterno
// Created:
// Modified:
//
////////////////////////////////////////////////////////////////////////

#if defined (NT_MSVCPP)
#pragma warning (disable: 4786)
#endif

#include "CLHEP/config/CLHEP.h"
#include "CLHEP/config/iostream.h"

#include <string>
#include <cassert>
#include <typeinfo>

#include "CLHEP/HepPDT/DMFactory.hh"
#include "CLHEP/HepPDT/SimpleParticle.hh"
#include "CLHEP/HepPDT/DefaultConfig.hh"

#ifdef __osf__
template class HepPDT::DMFactory<DefaultConfig>;
#endif

//  The decay mode headers are included to force linking of the needed 
//  object files from a static library.  If you have a lot of decay modes,
//  use one "all decay modes header" that includes the appropriate headers.
#include "ModeA.hh"
#include "ModeB.hh"

using namespace std;

int main()
{
        typedef HepPDT::DMFactory<DefaultConfig>       Factory;
        typedef HepPDT::DecayModelBase<DefaultConfig>  Product; 

	Factory* fac = Factory::instance();
	assert ( fac != 0 );
	assert ( fac->numKeys() >= 2 );

        // dummy arguments for decay	
	SimpleParticle const simp = SimpleParticle();
	std::vector< HepPDT::ParticleDataT<DefaultConfig> > const dp;
	std::vector< SimpleParticle > dtr;

	vector<double> v1, v2;
	v1.push_back(10.0);
	v1.push_back(-10.0);
	v2.push_back(-100.0);

	auto_ptr<Product> p1 = fac->makeProduct("ModeA", v1);
	p1->decay( dp, simp, dtr );
	cout << endl;

	auto_ptr<Product> p2 = fac->makeProduct("ModeB", v2);
	p2->decay( dp, simp, dtr );
	cout << endl;

	vector<double> v3;
	auto_ptr<Product> p3 = fac->makeProduct("nonesuch", v3);
	assert ( p3.get() == 0 );

	return 0;
}

/*
** Local Variables: --
** mode: c++ --
** c-file-style: "gnu" --
** tab-width: 2 --
** End: --
*/

