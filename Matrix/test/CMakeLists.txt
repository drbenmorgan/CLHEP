
# add -D needed by testInversion
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DINSTALLATION_CHECK")

set( Matrix_tests testMatrix 
                  testInversion
	          testBug6176 )
set( Matrix_simple_tests testBug6181
                         testBug7328 )

foreach ( test ${Matrix_tests} )
  clhep_test( ${test} )
endforeach ( test ${Matrix_tests} )

foreach ( test ${Matrix_simple_tests} )
  clhep_test( ${test} SIMPLE )
endforeach ( test ${Matrix_simple_tests} )
