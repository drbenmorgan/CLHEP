
set( Vector_tests testThreeVector 
                  testLorentzVector )
set( Vector_simple_tests testRotation 
		         testSubscripts )

foreach ( test ${Vector_tests} )
  clhep_test( ${test} )
endforeach ( test ${Vector_tests} )

foreach ( test ${Vector_simple_tests} )
  clhep_test( ${test} SIMPLE )
endforeach ( test ${Vector_simple_tests} )
