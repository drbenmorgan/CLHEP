# Create the tests
#
# if using a shell script:
#  clhep_test( testname [SIMPLE] [FAIL] [NOLIB] )
#   where testname is the base name of the .cc and .sh.in file
#
include(ClhepParseArgs)


macro( clhep_test testname )
  clhep_parse_args( CTST "LIBS" "SIMPLE;FAIL;NOLIB" ${ARGN})
  # automake/autoconf variables for ${testname}.sh.in 
  set(srcdir ${CMAKE_CURRENT_SOURCE_DIR} )
  set(builddir ${CMAKE_CURRENT_BINARY_DIR} )
  if( CTST_NOLIB )
    set ( package_library_list )
  else()
    set ( package_library_list ${PROJECT_BINARY_DIR}/lib/libCLHEP-${PACKAGE}-${VERSION}.a )
  endif()
  if( ${PACKAGE}_DEPS )
     foreach ( dep ${${PACKAGE}_DEPS} )
        ##message( STATUS "clhep_test ${testname} will use ${dep}")
	list(APPEND package_library_list  ${PROJECT_BINARY_DIR}/lib/libCLHEP-${dep}-${VERSION}.a )
     endforeach()
  endif()
  link_libraries( ${package_library_list} )
  ##message( STATUS "building ${testname} from ${CMAKE_CURRENT_SOURCE_DIR} in ${CMAKE_CURRENT_BINARY_DIR}" )
  ADD_EXECUTABLE(${testname} ${testname}.cc)
  if( CTST_SIMPLE )
    add_test( ${testname} ${CMAKE_CURRENT_BINARY_DIR}/${testname} )
  else()
    configure_file( ${testname}.sh.in 
                    ${CMAKE_CURRENT_BINARY_DIR}/${testname}.sh  @ONLY )
    add_test( ${testname}.sh ${CMAKE_CURRENT_BINARY_DIR}/${testname}.sh )
  endif()
  if( CTST_FAIL )
    set_tests_properties( ${testname}.sh PROPERTIES WILL_FAIL TRUE )
  endif()
endmacro( clhep_test )
