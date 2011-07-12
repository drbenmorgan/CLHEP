
set( Geometry_tests testBasicVector3D
	            testBug6740 )

foreach ( test ${Geometry_tests} )
  clhep_test( ${test} )
endforeach ( test ${Geometry_tests} )
