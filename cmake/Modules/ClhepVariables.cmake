#
# clhep_set_compiler_flags()
#    sets the default compiler flags
#    calls clhep_autoconf_variables
#
# clhep_autoconf_variables() defines global variables
#
# clhep_package_config():
#    defines ${PACKAGE}_LIBS
#    processes ${PACKAGE}-config.in
#    processes ${PACKAGE}-deps.in
#
# clhep_package_config_no_lib():
#    processes ${PACKAGE}-config.in
#
# clhep_config():
#    processes clhep-config.in
#
# clhep_lib_suffix();
#    check for -DLIB_SUFFIX=xxx and process intelligently
#
# CMake Extensions
# ----------------
# macro set_ifnot(<var> <value>)
#       If variable var is not set, set its value to that provided
#
# function enum_option(<option>
#                      VALUES <value1> ... <valueN>
#                      TYPE   <valuetype>
#                      DOC    <docstring>
#                      [DEFAULT <elem>]
#                      [CASE_INSENSITIVE])
#          Declare a cache variable <option> that can only take values
#          listed in VALUES. TYPE may be FILEPATH, PATH or STRING.
#          <docstring> should describe that option, and will appear in
#          the interactive CMake interfaces. If DEFAULT is provided,
#          <elem> will be taken as the zero-indexed element in VALUES
#          to which the value of <option> should default to if not
#          provided. Otherwise, the default is taken as the first
#          entry in VALUES. If CASE_INSENSITIVE is present, then
#          checks of the value of <option> against the allowed values
#          will ignore the case when performing string comparison.
#

include(CMakeParseArguments)
include(CheckCXXSourceCompiles)
include(IntelCompileFeatures)


#-----------------------------------------------------------------------
# macro set_ifnot(<var> <value>)
#       If variable var is not set, set its value to that provided
#
macro(set_ifnot _var _value)
  if(NOT ${_var})
    set(${_var} ${_value})
  endif()
endmacro()

#-----------------------------------------------------------------------
# function enum_option(<option>
#                      VALUES <value1> ... <valueN>
#                      TYPE   <valuetype>
#                      DOC    <docstring>
#                      [DEFAULT <elem>]
#                      [CASE_INSENSITIVE])
#          Declare a cache variable <option> that can only take values
#          listed in VALUES. TYPE may be FILEPATH, PATH or STRING.
#          <docstring> should describe that option, and will appear in
#          the interactive CMake interfaces. If DEFAULT is provided,
#          <elem> will be taken as the zero-indexed element in VALUES
#          to which the value of <option> should default to if not
#          provided. Otherwise, the default is taken as the first
#          entry in VALUES. If CASE_INSENSITIVE is present, then
#          checks of the value of <option> against the allowed values
#          will ignore the case when performing string comparison.
#
function(enum_option _var)
  set(options CASE_INSENSITIVE)
  set(oneValueArgs DOC TYPE DEFAULT)
  set(multiValueArgs VALUES)
  cmake_parse_arguments(_ENUMOP "${options}" "${oneValueArgs}" "${multiValueArgs}" ${ARGN})

  # - Validation as needed arguments
  if(NOT _ENUMOP_VALUES)
    message(FATAL_ERROR "enum_option must be called with non-empty VALUES\n(Called for enum_option '${_var}')")
  endif()

  # - Set argument defaults as needed
  if(_ENUMOP_CASE_INSENSITIVE)
    set(_ci_values )
    foreach(_elem ${_ENUMOP_VALUES})
      string(TOLOWER "${_elem}" _ci_elem)
      list(APPEND _ci_values "${_ci_elem}")
    endforeach()
    set(_ENUMOP_VALUES ${_ci_values})
  endif()

  set_ifnot(_ENUMOP_TYPE STRING)
  set_ifnot(_ENUMOP_DEFAULT 0)
  list(GET _ENUMOP_VALUES ${_ENUMOP_DEFAULT} _default)

  if(NOT DEFINED ${_var})
    set(${_var} ${_default} CACHE ${_ENUMOP_TYPE} "${_ENUMOP_DOC} (${_ENUMOP_VALUES})")
  else()
    set(_var_tmp ${${_var}})
    if(_ENUMOP_CASE_INSENSITIVE)
      string(TOLOWER ${_var_tmp} _var_tmp)
    endif()

    list(FIND _ENUMOP_VALUES ${_var_tmp} _elem)
    if(_elem LESS 0)
      message(FATAL_ERROR "Value '${${_var}}' for variable ${_var} is not allowed\nIt must be selected from the set: ${_ENUMOP_VALUES} (DEFAULT: ${_default})\n")

    else()
      # - convert to lowercase
      if(_ENUMOP_CASE_INSENSITIVE)
        set(${_var} ${_var_tmp} CACHE ${_ENUMOP_TYPE} "${_ENUMOP_DOC} (${_ENUMOP_VALUES})" FORCE)
      endif()
    endif()
  endif()
endfunction()

#-----------------------------------------------------------------------
# - Print info on variables
macro(clhep_check_variable_names)
  message(STATUS "clhep_check_variable_names: CMAKE_SYSTEM_NAME is ${CMAKE_SYSTEM_NAME}")
  message(STATUS "clhep_check_variable_names: CMAKE_BASE_NAME is ${CMAKE_BASE_NAME}")
  message(STATUS "clhep_check_variable_names: CMAKE_CXX_COMPILER_ID is ${CMAKE_CXX_COMPILER_ID}")
  message(STATUS "clhep_check_variable_names: CMAKE_COMPILER_IS_GNUCXX is ${CMAKE_COMPILER_IS_GNUCXX}")
  message(STATUS "clhep_check_variable_names: CMAKE_COMPILER_IS_MINGW is ${CMAKE_COMPILER_IS_MINGW}")
  message(STATUS "clhep_check_variable_names: CMAKE_COMPILER_IS_CYGWIN is ${CMAKE_COMPILER_IS_CYGWIN}")
  message(STATUS "clhep_check_variable_names: CMAKE_AR is ${CMAKE_AR}")
  message(STATUS "clhep_check_variable_names: CMAKE_RANLIB is ${CMAKE_RANLIB}")
  message(STATUS "clhep_check_variable_names: CMAKE_CXX_OUTPUT_EXTENSION is ${CMAKE_CXX_OUTPUT_EXTENSION}")
  message(STATUS "clhep_check_variable_names: CMAKE_SHARED_LIBRARY_CXX_FLAGS is ${CMAKE_SHARED_LIBRARY_CXX_FLAGS}")
  message(STATUS "clhep_check_variable_names: CMAKE_SHARED_MODULE_CXX_FLAGS is ${CMAKE_SHARED_MODULE_CXX_FLAGS}")
  message(STATUS "clhep_check_variable_names: CMAKE_SHARED_LIBRARY_LINK_CXX_FLAGS is ${CMAKE_SHARED_LIBRARY_LINK_CXX_FLAGS}")
  message(STATUS "clhep_check_variable_names: CMAKE_CXX_FLAGS is ${CMAKE_CXX_FLAGS}")
  message(STATUS "clhep_check_variable_names: CMAKE_CXX_FLAGS_DEBUG is ${CMAKE_CXX_FLAGS_DEBUG}")
  message(STATUS "clhep_check_variable_names: CMAKE_CXX_FLAGS_RELEASE is ${CMAKE_CXX_FLAGS_RELEASE}")
  message(STATUS "clhep_check_variable_names: CMAKE_CXX_FLAGS_RELWITHDEBINFO is ${CMAKE_CXX_FLAGS_RELWITHDEBINFO}")
  message(STATUS "clhep_check_variable_names: CMAKE_CXX_STANDARD_LIBRARIES is ${CMAKE_CXX_STANDARD_LIBRARIES}")
  message(STATUS "clhep_check_variable_names: CMAKE_CXX_LINK_FLAGS is ${CMAKE_CXX_LINK_FLAGS}")
endmacro()

#-----------------------------------------------------------------------
# - Map CMake -> Autoconf variables for script expansion compatibility
macro(clhep_autoconf_variables)
  # these variables are used by <package>-config.in
  # typical values from autoconf:
  #   AM_CXXFLAGS = -O -ansi -pedantic -Wall -D_GNU_SOURCE
  #   CXXFLAGS = -g -O2
  #   CXX = g++
  #   CXXCPP = g++ -E
  #   CPPFLAGS =
  #   CXXLD = $(CXX)
  #   AM_LDFLAGS =
  #   LDFLAGS =
  #   LIBS =

  # automake/autoconf variables
  set(prefix          "${CMAKE_INSTALL_PREFIX}")
  set(exec_prefix     "\${prefix}")
  set(includedir      "\${prefix}/include")
  set(configure_input "Generated by cmake")

  # autoconf variables typically do not have the path
  set(CXX ${CMAKE_BASE_NAME})
  set(CXXCPP "${CXX} -E")
  if(CMAKE_BUILD_TYPE)
    set(CXXFLAGS "${CMAKE_CXX_FLAGS_${CMAKE_BUILD_TYPE}}")

  endif()

  set(AM_CXXFLAGS  ${CMAKE_CXX_FLAGS} )
  set(LDFLAGS      ${CMAKE_MODULE_LINKER_FLAGS})
  set(LIBS         "" )
  set(DIFF_Q       "diff -q -b" )

  if(CLHEP_DEBUG_MESSAGES)
    clhep_check_variable_names()

  endif()
endmacro()


#-----------------------------------------------------------------------
# -
macro(_clhep_check_cxxstd)
  if(CLHEP_DEBUG_MESSAGES)
    message(STATUS "_clhep_check_cxxstd debug: CMAKE_CXX_COMPILER: ${CMAKE_CXX_COMPILER}")
    message(STATUS "_clhep_check_cxxstd debug: CMAKE_CXX_COMPILER_ID: ${CMAKE_CXX_COMPILER_ID}")
    message(STATUS "_clhep_check_cxxstd debug: CMAKE_CXX_COMPILER_VERSION: ${CMAKE_CXX_COMPILER_VERSION}")
    message(STATUS "_clhep_check_cxxstd debug: CMAKE_CXX_FLAGS: ${CMAKE_CXX_FLAGS}")
    message(STATUS "_clhep_check_cxxstd debug: CLHEP_BUILD_CXXSTD: ${CLHEP_BUILD_CXXSTD}")
  endif()

  enum_option(CLHEP_BUILD_CXXSTD
    DOC "C++ Standard to compile against"
    VALUES 11 14 c++11 c++14
    CASE_INSENSITIVE
    )

  string(REGEX REPLACE "^c\\+\\+" "" CLHEP_BUILD_CXXSTD "${CLHEP_BUILD_CXXSTD}")
  mark_as_advanced(CLHEP_BUILD_CXXSTD)

  # - Language features
  set(CMAKE_CXX_EXTENSIONS OFF)
  set(CLHEP_CXX_COMPILE_FEATURES
    # Not completely clear what is used yet, so just most common
    cxx_alias_templates
    cxx_auto_type
    cxx_lambdas
    cxx_nullptr
    cxx_range_for
    cxx_strong_enums
    )

  # - If a higher standard than the default is requested, check that
  #   compile features are available for that standard and add them
  #   to the list
  if(CLHEP_BUILD_CXXSTD GREATER 11)
    if(CMAKE_CXX${CLHEP_BUILD_CXXSTD}_COMPILE_FEATURES)
      list(APPEND CLHEP_CXX_COMPILE_FEATURES ${CMAKE_CXX${CLHEP_BUILD_CXXSTD}_COMPILE_FEATURES})

    else()
      message(FATAL_ERROR "CLHEP requested to be compiled against C++ Standard '${CLHEP_BUILD_CXXSTD}'\nbut detected compiler '${CMAKE_CXX_COMPILER_ID}', version '${CMAKE_CXX_COMPILER_VERSION}'\ndoes not support any features of that standard")
    endif()
  endif()


  # - Stdlib features
  set(CMAKE_REQUIRED_FLAGS "${CMAKE_CXX${CLHEP_BUILD_CXXSTD}_STANDARD_COMPILE_OPTION}")
  # - std::shared_ptr
  check_cxx_source_compiles("
  #include <memory>
  int main() {std::shared_ptr<int> foo(new int(42)); return 0;}
  "
  HAVE_CXX_MEMORY_SHARED_PTR
  )
  if(NOT HAVE_CXX_MEMORY_SHARED_PTR)
    message(FATAL_ERROR "${CMAKE_CXX_COMPILER_ID} ${CMAKE_CXX_COMPILER_VERSION} does not provide std::shared_ptr in linked C++ Standard Library")
  endif()

  # - std::weak_ptr
  check_cxx_source_compiles("
  #include <memory>
  int main() {std::weak_ptr<int> foo; return 0;}
  "
  HAVE_CXX_MEMORY_WEAK_PTR
  )
  if(NOT HAVE_CXX_MEMORY_WEAK_PTR)
    message(FATAL_ERROR "${CMAKE_CXX_COMPILER_ID} ${CMAKE_CXX_COMPILER_VERSION} does not provide std::weak_ptr in linked C++ Standard Library")
  endif()

  unset(CMAKE_REQUIRED_FLAGS)
endmacro()


#-----------------------------------------------------------------------
# - Configure and set CLHEP compiler flags
macro(clhep_set_compiler_flags)
  if(NOT CMAKE_CONFIGURATION_TYPES)
    if(NOT CMAKE_BUILD_TYPE)
      set(CMAKE_BUILD_TYPE RelWithDebInfo CACHE STRING "" FORCE)
    endif()
    message(STATUS "cmake build type is ${CMAKE_BUILD_TYPE}")
  endif()

  _clhep_check_cxxstd()

  if(CLHEP_DEBUG_MESSAGES)
    message(STATUS "clhep_set_compiler_flags debug: CMAKE_CXX_FLAGS: ${CMAKE_CXX_FLAGS}")
    message(STATUS "clhep_set_compiler_flags debug: cmake compilers ${CMAKE_CXX_COMPILER} ${CMAKE_C_COMPILER}")
  endif()

  if(${CMAKE_C_COMPILER_ID} MATCHES "(Apple)?Clang")
    set(CMAKE_C_FLAGS "-O -pedantic -Wall -pthread ${CMAKE_C_FLAGS}")
  elseif(${CMAKE_C_COMPILER_ID} STREQUAL "Intel")
    set(CMAKE_C_FLAGS "-O -ansi -pedantic -Wall -pthread ${CMAKE_C_FLAGS}")
    set(CMAKE_CXX_FLAGS "-O -ansi -pedantic -Wall -pthread ${CMAKE_CXX_FLAGS}")
  elseif(CMAKE_COMPILER_IS_GNUCC)
    set(CMAKE_C_FLAGS "-O -ansi -pedantic -Wall -D_GNU_SOURCE -pthread ${CMAKE_C_FLAGS}")
  endif()

  if(${CMAKE_CXX_COMPILER_ID} MATCHES "(Apple)?Clang")
    set(CMAKE_CXX_FLAGS "-O -pedantic -Wall -pthread ${CMAKE_CXX_FLAGS}")
  elseif(CMAKE_COMPILER_IS_GNUCXX)
    set(CMAKE_CXX_FLAGS "-O -ansi -pedantic -Wall -D_GNU_SOURCE -pthread ${CMAKE_CXX_FLAGS}")
  elseif(CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
    set(CMAKE_C_FLAGS "/EHsc /nologo /GR /MD /D USING_VISUAL")
    set(CMAKE_CXX_FLAGS "/EHsc /nologo /GR /MD /D USING_VISUAL")

  endif()

  clhep_autoconf_variables()
endmacro()

#-----------------------------------------------------------------------
# - Generate/Install per-package (header only) -config programs
macro(clhep_package_config_no_lib)
  set(${PACKAGE}_CPPFLAGS "-I${includedir}")
  set(${PACKAGE}_LDFLAGS  " ")
  set(${PACKAGE}_LIBS     " ")
  configure_file(${CLHEP_SOURCE_DIR}/${PACKAGE}/${PACKAGE}-config.in
                 ${CLHEP_BINARY_DIR}/${PACKAGE}/${PACKAGE}-config @ONLY)

  # don't install <package>-config on Windows
  if(${CMAKE_SYSTEM_NAME} MATCHES "Windows" )
    install(PROGRAMS ${CLHEP_BINARY_DIR}/${PACKAGE}/${PACKAGE}-config
            DESTINATION bin
            )
  endif()
endmacro()

#-----------------------------------------------------------------------
# - Generate/Install per-package (binary lib) -config programs
macro(clhep_package_config)
  set(${PACKAGE}_CPPFLAGS "-I${includedir}")
  set(${PACKAGE}_LDFLAGS  "-L\${exec_prefix}/lib${LIB_SUFFIX}")
  set(${PACKAGE}_LIBS     "-lCLHEP-${PACKAGE}-${CLHEP_VERSION}")
  if(${PACKAGE}_DEPS)
    foreach(dep ${${PACKAGE}_DEPS})
      message(STATUS "${PACKAGE} depends on ${dep}")
      set(${PACKAGE}_LIBS "${${PACKAGE}_LIBS} -lCLHEP-${dep}-${CLHEP_VERSION}" )
    endforeach()
  endif()

  configure_file(${CLHEP_SOURCE_DIR}/${PACKAGE}/${PACKAGE}-config.in
                 ${CLHEP_BINARY_DIR}/${PACKAGE}/${PACKAGE}-config @ONLY )
  configure_file(${CLHEP_SOURCE_DIR}/${PACKAGE}/${PACKAGE}-deps.in
                 ${CLHEP_BINARY_DIR}/${PACKAGE}/${PACKAGE}-deps @ONLY)

  ## don't install <package>-config on Windows
  if(NOT ${CMAKE_SYSTEM_NAME} MATCHES "Windows")
    install(PROGRAMS ${CLHEP_BINARY_DIR}/${PACKAGE}/${PACKAGE}-config
            DESTINATION bin
            )
  endif()
endmacro()

#-----------------------------------------------------------------------
# - Generate and install `clhep-config` program
macro(clhep_config)
  configure_file(${CLHEP_SOURCE_DIR}/clhep-config.in
                 ${CLHEP_BINARY_DIR}/clhep-config @ONLY )
  ## don't install clhep-config on Windows
  if(NOT ${CMAKE_SYSTEM_NAME} MATCHES "Windows")
    install(PROGRAMS ${CLHEP_BINARY_DIR}/clhep-config
            DESTINATION bin
            )
  endif()
endmacro()

#-----------------------------------------------------------------------
# - libsuffix
macro(_clhep_lib_suffix_64)
  if(APPLE)
    # On Mac, we use NAME-ARCH, but ARCH is 'Universal' if more than
    # one arch is built for. Note that falling back to use
    # CMAKE_SYSTEM_PROCESSOR may *not* be 100% reliable.
    list(LENGTH CMAKE_OSX_ARCHITECTURES _number_of_arches)
    if(NOT _number_of_arches)
      # - Default
      if(${CMAKE_SYSTEM_PROCESSOR} STREQUAL "x86_64")
        # building for 64bit
      else()
        message(STATUS "WARNING: LIB_SUFFIX ${LIB_SUFFIX} inappropriate for this build")
        set(LIB_SUFFIX "")
      endif()
    elseif(_number_of_arches GREATER 1)
      # - Universal
    else()
      # - Use what the user specified
      if(${CMAKE_OSX_ARCHITECTURES} STREQUAL "x86_64")
        # building for 64bit
      else()
        message(STATUS "WARNING: LIB_SUFFIX ${LIB_SUFFIX} inappropriate for this build")
	      set(LIB_SUFFIX "")
      endif()
    endif()
  elseif(${CMAKE_SYSTEM_NAME} MATCHES "Windows")
    if(${CMAKE_SYSTEM_PROCESSOR} STREQUAL "x86")
      # building for 64bit
    else()
      message(STATUS "WARNING: LIB_SUFFIX ${LIB_SUFFIX} inappropriate for this build")
      set(LIB_SUFFIX "")
    endif()
  else()
    if(${CMAKE_SYSTEM_PROCESSOR} STREQUAL "x86_64")
      # building for 64bit
    else()
      message(STATUS "WARNING: LIB_SUFFIX ${LIB_SUFFIX} inappropriate for this build")
      set(LIB_SUFFIX "")
    endif()
  endif()
endmacro()

#-----------------------------------------------------------------------
# - libsuffix
macro(_clhep_lib_suffix_32)
  if(APPLE)
    # On Mac, we use NAME-ARCH, but ARCH is 'Universal' if more than
    # one arch is built for. Note that falling back to use
    # CMAKE_SYSTEM_PROCESSOR may *not* be 100% reliable.
    list(LENGTH CMAKE_OSX_ARCHITECTURES _number_of_arches)
    if(NOT _number_of_arches)
      # - Default
      if(${CMAKE_SYSTEM_PROCESSOR} STREQUAL "i386")
        # building for 32bit
      else()
        message(STATUS "WARNING: LIB_SUFFIX ${LIB_SUFFIX} inappropriate for this build")
	      set(LIB_SUFFIX "")
      endif()
    elseif(_number_of_arches GREATER 1)
      # - Universal
    else()
      # - Use what the user specified
      if(${CMAKE_OSX_ARCHITECTURES} STREQUAL "i386")
        # building for 32bit
      else()
        message(STATUS "WARNING: LIB_SUFFIX ${LIB_SUFFIX} inappropriate for this build")
	      set(LIB_SUFFIX "")
      endif()
    endif()
  else()
    if(${CMAKE_SYSTEM_PROCESSOR} STREQUAL "i686")
      # building for 32bit
    elseif(${CMAKE_SYSTEM_PROCESSOR} STREQUAL "i386")
      # building for 32bit
    else()
      message(STATUS "WARNING: LIB_SUFFIX ${LIB_SUFFIX} inappropriate for this build")
      set(LIB_SUFFIX "")
    endif()
  endif()
endmacro()

#-----------------------------------------------------------------------
# - Construct libsuffix
macro(clhep_lib_suffix)
  if(LIB_SUFFIX)
    if(${LIB_SUFFIX} STREQUAL "64")
      _clhep_lib_suffix_64()
    elseif(${LIB_SUFFIX} STREQUAL "32")
      _clhep_lib_suffix_32()
    endif()
  endif()
  message(STATUS "libraries will be installed in $ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib${LIB_SUFFIX}")
endmacro()

#-----------------------------------------------------------------------
# - Strip debugs
macro(clhep_enable_asserts)
  string(REGEX REPLACE "-DNDEBUG" " " CXXFLAGS "${CXXFLAGS}")
  list(APPEND CLHEP_BUILD_TYPES ${CMAKE_BUILD_TYPE} ${CMAKE_CONFIGURATION_TYPES})

  foreach(_btype ${CLHEP_BUILD_TYPES})
    string(TOUPPER ${_btype} BTYPE_UC)
    string(REGEX REPLACE "-DNDEBUG" " " CMAKE_CXX_FLAGS_${BTYPE_UC} "${CMAKE_CXX_FLAGS_${BTYPE_UC}}")
  endforeach()
endmacro()
