// $Id: Measurement.hh,v 1.1.1.1 2003/07/15 20:15:05 garren Exp $
// ----------------------------------------------------------------------
//
// Measurement.hh
// author:  Mark Fischler
// ----------------------------------------------------------------------
#ifndef MEASUREMENT_HH
#define MEASUREMENT_HH

namespace HepPDT {

/**
 * @author
 * @ingroup heppdt
 */
class Measurement {
public:
  inline Measurement ();  
  inline Measurement ( double value, double sigma );

  inline Measurement ( const Measurement &m );
  inline void swap( Measurement & other );
  inline Measurement& operator = ( Measurement const & rhs );

  inline bool  operator <  ( Measurement const & other ) const;
  inline bool  operator == ( Measurement const & other ) const;

  inline double   value()  const;
  inline double   sigma()  const;
  inline operator double() const;

private:  
  double val;
  double sig;

};	// Measurement

inline
void swap( Measurement & first, Measurement & second ) { first.swap( second ); }

}      // end of namespace HepPDT

#include "CLHEP/HepPDT/Measurement.icc"

#endif // end of codeguard MEASUREMENT_HH
