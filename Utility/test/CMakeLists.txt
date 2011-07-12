
set( Utility_simple_tests testNoncopyable
			  testPrimaryTraits
			  testCategories
			  testIsSame
			  testIsConvertible
			  testSharedPtrBasic
			  testSharedPtrConvertible
			  testSharedPtr
			  testWeakPtr )

foreach ( test ${Utility_simple_tests} )
  clhep_test( ${test} SIMPLE NOLIB )
endforeach ( test ${Utility_simple_tests} )
