# determine the compiler and version
# this code is more or less lifted from FindBoost

#
# Runs compiler with "-dumpversion" and parses major/minor
# version with a regex.
#
function(_My_COMPILER_DUMPVERSION _OUTPUT_VERSION)
  execute_process(
    COMMAND ${CMAKE_CXX_COMPILER}
            ${CMAKE_CXX_COMPILER_ARG1}
            -dumpversion
    OUTPUT_VARIABLE _my_COMPILER_VERSION
    OUTPUT_STRIP_TRAILING_WHITESPACE
    )

  set(COMPILER_VERSION ${_my_COMPILER_VERSION} PARENT_SCOPE)

  string(REGEX REPLACE
    "([0-9])\\.([0-9])(\\.[0-9])?"
    "\\1\\2"
    _my_COMPILER_VERSION
    ${_my_COMPILER_VERSION}
    )

  set(${_OUTPUT_VERSION} ${_my_COMPILER_VERSION} PARENT_SCOPE)
endfunction()

#
# End functions/macros
#
macro(clhep_package_compiler)
  if(My_COMPILER)
    set(CPack_COMPILER_STRING ${My_COMPILER})
    message(STATUS
      "[ ${CMAKE_CURRENT_LIST_FILE}:${CMAKE_CURRENT_LIST_LINE} ] "
      "using user-specified My_COMPILER = ${CPack_COMPILER_STRING}"
      )
  else()
    # Attempt to guess the compiler suffix
    # NOTE: this is not perfect yet, if you experience any issues
    # please report them and use the My_COMPILER variable
    # to work around the problems.
    if(MSVC90)
      set(CPack_COMPILER_STRING "-vc90")
    elseif(MSVC80)
      set(CPack_COMPILER_STRING "-vc80")
    elseif(MSVC71)
      set(CPack_COMPILER_STRING "-vc71")
    elseif(MSVC70) # Good luck!
      set(CPack_COMPILER_STRING "-vc7") # yes, this is correct
    elseif (MSVC60) # Good luck!
      set(CPack_COMPILER_STRING "-vc6") # yes, this is correct
    elseif(BORLAND)
      set(CPack_COMPILER_STRING "-bcb")
    elseif("${CMAKE_CXX_COMPILER}" MATCHES "icl"
        OR "${CMAKE_CXX_COMPILER}" MATCHES "icpc")
      if(WIN32)
        set(CPack_COMPILER_STRING "-iw")
      else()
        set(CPack_COMPILER_STRING "-il")
      endif()
    elseif(MINGW)
      _My_COMPILER_DUMPVERSION(CPack_COMPILER_STRING_VERSION)
      set(CPack_COMPILER_STRING "-mgw${CPack_COMPILER_STRING_VERSION}")
    elseif(UNIX)
      if(CMAKE_COMPILER_IS_GNUCXX)
        _My_COMPILER_DUMPVERSION(CPack_COMPILER_STRING_VERSION)
        # Determine which version of GCC we have.
        if(APPLE)
          set(CPack_COMPILER_STRING "-gcc${CPack_COMPILER_STRING_VERSION}")
        else()
          set(CPack_COMPILER_STRING "-gcc${CPack_COMPILER_STRING_VERSION}")
	      endif()
      elseif(${CMAKE_CXX_COMPILER_ID} STREQUAL "Intel")
        string(REGEX REPLACE
          "^([0-9]+)\\.+.*"
          "\\1"
          CPack_COMPILER_STRING_VERSION
          "${CMAKE_CXX_COMPILER_VERSION}"
          )
        set(CPack_COMPILER_STRING "-icc${CPack_COMPILER_STRING_VERSION}")
      endif()
    endif()
  endif(My_COMPILER)
endmacro()


macro(clhep_package_compiler_status)
  clhep_package_compiler()
  message(STATUS " ")
  message(STATUS "C++ compiler: ${CMAKE_CXX_COMPILER}")
  message(STATUS "Compiler version: ${COMPILER_VERSION}")
  message(STATUS "Compiler string for cpack: ${CPack_COMPILER_STRING}")
  message(STATUS " ")
endmacro()
