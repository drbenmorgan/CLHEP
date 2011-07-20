
# add -D needed by testInversion
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DINSTALLATION_CHECK")

set( Matrix_tests testMatrix 
                  testInversion
	          testBug6176 )

# leak test (bug 7328) does not work on MacOSX or DOS
if( ${CMAKE_SYSTEM_NAME} MATCHES "Darwin" )
  set( Matrix_simple_tests testBug6181 )
elseif( ${CMAKE_SYSTEM_NAME} MATCHES "Windows" )
  set( Matrix_simple_tests testBug6181 )
else()
  set( Matrix_simple_tests testBug6181
                           testBug7328 )
endif()

foreach ( test ${Matrix_tests} )
  clhep_test( ${test} )
endforeach ( test ${Matrix_tests} )

foreach ( test ${Matrix_simple_tests} )
  clhep_test( ${test} SIMPLE )
endforeach ( test ${Matrix_simple_tests} )
