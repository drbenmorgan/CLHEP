

clhep_enable_asserts()

set( Utility_simple_tests testNoncopyable
			  testSharedPtrConvertible )

foreach ( test ${Utility_simple_tests} )
  clhep_test( ${test} SIMPLE NOLIB )
endforeach ( test ${Utility_simple_tests} )
