# Create the tests
#
# clhep_test( testname
#                [LIBS] <library_list>
#                [DEPENDS] <another_testname>
#                [SIMPLE] - this test does not require a shell script
#                [FAIL] - test is epected to fail
#                [NOLIB] - no library dependencies
#            )
# testname is the base name of the .cc file
#
# if the test requires running a shell script:
#   clhep_test( testname )
# testname is the base name of the .cc and .sh.in file
#
include(ClhepParseArgs)

# - Create "dummy" target so we can use a generator expression to
# determine working directory for shell script based tests. This works
# for all build tools, and guarantees the correct executable is
# run when working with multimode tools like Xcode/MSVC
file(WRITE "${PROJECT_BINARY_DIR}/testWorkingDirMarker.cc" "int main(){return 0;}\n")
add_executable(testWorkingDirMarker ${PROJECT_BINARY_DIR}/testWorkingDirMarker.cc)

macro(clhep_test testname)
  clhep_parse_args( CTST "LIBS;DEPENDS" "SIMPLE;FAIL;NOLIB" ${ARGN})

  # automake/autoconf variables for ${testname}.sh.in
  set(srcdir ${CMAKE_CURRENT_SOURCE_DIR})
  set(builddir ${CMAKE_CURRENT_BINARY_DIR})

  if(CTST_NOLIB)
    set(package_library_list)
  else()
    set(package_library_list ${PACKAGE}S)
  endif()

  add_executable(${testname} ${testname}.cc)
  target_compile_features(${testname} PRIVATE ${CLHEP_CXX_COMPILE_FEATURES})
  target_link_libraries(${testname} ${package_library_list})

  if(CTST_SIMPLE)
    add_test(NAME ${testname} COMMAND ${testname})
    if(CTST_FAIL)
      set_tests_properties(${testname} PROPERTIES WILL_FAIL TRUE)
    endif()
    if(CTST_DEPENDS)
      set_tests_properties(${testname} PROPERTIES DEPENDS ${CTST_DEPENDS})
    endif()
  else()
    if(${CMAKE_SYSTEM_NAME} MATCHES "Windows")
      message( STATUS "skipping ${testname}.sh on ${CMAKE_SYSTEM_NAME}")
    else()
      configure_file(${testname}.sh.in
                     ${CMAKE_CURRENT_BINARY_DIR}/${testname}.sh  @ONLY
                     )
      add_test(NAME ${testname}.sh
        COMMAND ${CMAKE_CURRENT_BINARY_DIR}/${testname}.sh
        WORKING_DIRECTORY $<TARGET_FILE_DIR:testWorkingDirMarker>
        )
      if(CTST_FAIL)
        set_tests_properties(${testname}.sh PROPERTIES WILL_FAIL TRUE)
      endif()
      if(CTST_DEPENDS)
        add_custom_target(check COMMAND ${testname} DEPENDS ${CTST_DEPENDS})
      endif()
    endif()
  endif()
endmacro()
