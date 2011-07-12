
set( Exceptions_tests testExceptions
		      testThrowFrom
		      exctest1 	
		      exctest2 	
		      exctest3 	
		      exctest4 	
 		      exctestNothrow )

foreach ( test ${Exceptions_tests} )
  clhep_test( ${test} )
endforeach ( test ${Exceptions_tests} )

clhep_test( testzmex FAIL )
