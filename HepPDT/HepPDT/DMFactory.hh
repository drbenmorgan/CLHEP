////////////////////////////////////////////////////////////////////////
//
// File: DMFactory.hh
// $Id: DMFactory.hh,v 1.1.1.1 2003/07/15 20:15:05 garren Exp $
// Purpose: interface for the DMFactory class
//
// Author:  Marc Paterno
// Created:
// Modified:
//
////////////////////////////////////////////////////////////////////////

#ifndef PATTERNS_DMFACTORY_HPP
#define PATTERNS_DMFACTORY_HPP

#if defined(NT_MSVCPP)
#pragma warning (disable: 4786)
#endif

#include <iostream>
#include <assert.h>
#include <memory>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include <iterator>

#include "CLHEP/HepPDT/DecayModelBase.hh"
#include "CLHEP/HepPDT/pretend.hh"
//
// This template deals with creation of objects of type T.
// T must inherit from DecayModelBase.
//

namespace HepPDT {

/**
 * @author
 * @ingroup heppdt
 */
template< class Config >
struct MakerBase
{
  typedef typename Config::ParticleData PD;	// ParticleDataType
  typedef typename Config::PT           PT;	// ParticleType
  typedef DecayModelBase<Config>        Product; 
	virtual Product* make(const std::vector<double>& arg) = 0;
	virtual ~MakerBase() {};
};

/**
 * @author
 * @ingroup heppdt
 */
template <class T, class Config>
struct Maker : public MakerBase<Config>
{
  typedef DecayModelBase<Config>        Product; 
	virtual ~Maker() {}
	virtual Product* make(const std::vector<double>& arg) { return new T(arg); }
};

/**
 * @author
 * @ingroup heppdt
 */
template< class Config >
class DMFactory
{
public:
  typedef typename Config::ParticleData PD;	// ParticleDataType
  typedef typename Config::PT           PT;	// ParticleType
  typedef DecayModelBase<Config>            Product; 
	
	typedef std::map<std::string, MakerBase<Config>*>  funcmap;
	typedef typename funcmap::const_iterator      const_iterator;
	typedef typename funcmap::iterator            iterator;
	
	// The singleton instance
	static DMFactory* instance();
	

	void addProduct(const std::string& k, MakerBase<Config>* m);

	std::auto_ptr<Product> makeProduct(const std::string& k, 
					   const std::vector<double>& a) const;
	
	// Don't use the following, unless you like memory leaks.
	Product*         unsafeMakeProduct(const std::string& k, 
			                   const std::vector<double>& a) const;
		
	// Return the number of keys we know about (same as the number of
	// products, unless one product comes under more than one key).
	unsigned long numKeys() const;

	
private:
	
	funcmap _makerfuncs;
	
	// Singleton stuff
	DMFactory();
	~DMFactory();

	DMFactory(const DMFactory&);            // not implemented
	DMFactory& operator=(const DMFactory&); // not implemented

	static DMFactory* _inst;
	static void destroy_and_clear();
		
	struct Cleaner;
	friend struct Cleaner;
	struct Cleaner { ~Cleaner() { DMFactory::destroy_and_clear(); } };
		
}; // class DMFactory

//
// This template deals with registration of products. Creation of an
// instance of RegisterMe<T> registers something than can create a T
// in the DMFactory.
//

/**
 * @author
 * @ingroup heppdt
 */
template <class T, class Config>
struct RegisterMe
{
	RegisterMe(const std::string& key)
	{
		typedef T product_t;
		MakerBase<Config>* p = new Maker<product_t,Config>;
		DMFactory<Config>::instance()->addProduct(key, p);
	}
};

}	// HepPDT

#include "CLHEP/HepPDT/DMFactory.icc"

#endif // #ifndef PATTERNS_DMFACTORY_HPP

/*
** Local Variables: --
** mode: c++ --
** c-file-style: "gnu" --
** tab-width: 2 --
** End: --
*/
