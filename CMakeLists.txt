#------------------------------------------------------------------------------
# Top Level CMakeLists.txt for CLHEP
#  cmake [-DCMAKE_INSTALL_PREFIX=/install/path] 
#        [-DCMAKE_BUILD_TYPE=Debug|Release|RelWithDebInfo|MinSizeRel]
#        [-DCMAKE_C_COMPILER=...] [-DCMAKE_CXX_COMPILER=...]
#        [-DCMAKE_CXX_FLAGS=...]
#        [-DCLHEP_BUILD_CXXSTD="-std=c++NN"] (use specified c++ extension)
#        [-DCLHEP_SINGLE_THREAD=ON] (disable multi threading)
#        [-DCLHEP_DEBUG_MESSAGES=ON] (see more verbose output)
#        [-DCLHEP_BUILD_DOCS=ON]
#        [-DLIB_SUFFIX=64]
#        /path/to/source
#  make
#  make test
#  make install
#
# mac i386:   -DCMAKE_CXX_FLAGS="-m32" -DCMAKE_OSX_ARCHITECTURES="i386"
# mac x86_64: -DCMAKE_CXX_FLAGS="-m64" -DCMAKE_OSX_ARCHITECTURES="x86_64"
#
# Use -DLIB_SUFFIX=64 to install the libraries in a lib64 subdirectory
# instead of the default lib subdirectory.  
#
# The default CLHEP build type is CMAKE_BUILD_TYPE=RelWithDebInfo,
# which matches the default CLHEP autoconf flags
#------------------------------------------------------------------------------

# Ensure out of source build before anything else
include(${CMAKE_CURRENT_SOURCE_DIR}/cmake/Modules/ClhepOutOfSourceBuild.cmake)
clhep_ensure_out_of_source_build()

# use cmake 3.2 or later
cmake_minimum_required(VERSION 3.2)
# Project setup
project(CLHEP VERSION 2.4.4.1)
# - needed for (temporary) back compatibility
set(VERSION ${PROJECT_VERSION})

set(CMAKE_MODULE_PATH 
      ${CMAKE_CURRENT_SOURCE_DIR}/cmake/Modules 
      ${CMAKE_MODULE_PATH}
      )

# enable use of LIB_SUFFIX
include(ClhepVariables)
clhep_lib_suffix()

# CLHEP custom modules
include(ClhepCopyHeaders)
include(ClhepBuildTest)
include(ClhepBuildLibrary)
include(CheckFunctionExists)
include(ClhepToolchain)

ENABLE_TESTING()

# include search path
include_directories ("${PROJECT_BINARY_DIR}")
# add CLHEP/Random to search path so we find gaussTables.cdat
include_directories ("${PROJECT_SOURCE_DIR}/Random")

# Put all library build products in standard locations under build tree
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/lib)

# set our preferred compiler flags
clhep_set_compiler_flags()

# the main CLHEP config script
clhep_config()

# check for required functions
CHECK_FUNCTION_EXISTS(drand48 found_drand48)

# all the packages
set( CLHEP_subdirs
        Units
	Utility
	Vector
	Evaluator
	GenericFunctions
	Geometry
        Random
	Matrix
	RandomObjects
	Cast
	RefCount
	Exceptions
	)

# The Units and Utility packages are just headers.
set( CLHEP_libraries
       Vector
       Evaluator
       GenericFunctions
       Geometry
       Random
       Matrix
       RandomObjects
       Cast
       RefCount
       Exceptions
       )

clhep_copy_headers( ${CLHEP_subdirs} )

add_subdirectory(Units)
add_subdirectory(Utility) 
add_subdirectory(Vector) 
add_subdirectory(Evaluator) 
add_subdirectory(GenericFunctions) 
add_subdirectory(Geometry) 
add_subdirectory(Random) 
add_subdirectory(Matrix) 
add_subdirectory(RandomObjects) 
add_subdirectory(Cast) 
add_subdirectory(RefCount) 
add_subdirectory(Exceptions)

# libCLHEP.a and libCLHEP.so
clhep_build_libclhep( ${CLHEP_libraries} )

# provide tools for other packages to include CLHEP easily
clhep_toolchain()

# - Build docucumentation if required
if(CLHEP_BUILD_DOCS)
  message(STATUS "Enabled build and install of documents")
  # Build Doxygen
  # Require 1.8.8 or better to allow use of MD file as mainpage
  find_package(Doxygen 1.8.8 REQUIRED)
  configure_file(doxygen.conf.in "${PROJECT_BINARY_DIR}/doxygen.conf" @ONLY)
  add_custom_command(
    OUTPUT "${PROJECT_BINARY_DIR}/Doxygen/html/index.html"
    COMMAND ${DOXYGEN_EXECUTABLE} "${PROJECT_BINARY_DIR}/doxygen.conf"
    WORKING_DIRECTORY "${PROJECT_BINARY_DIR}"
    DEPENDS
    "${PROJECT_BINARY_DIR}/doxygen.conf"
    CLHEP
    "${PROJECT_SOURCE_DIR}/README.md"
    COMMENT "Generating Doxygen docs for CLHEP"
    )
  add_custom_target(doc ALL DEPENDS "${PROJECT_BINARY_DIR}/Doxygen/html/index.html")

  install(DIRECTORY ${PROJECT_BINARY_DIR}/Doxygen
    DESTINATION "share/doc/CLHEP"
    )
endif()

# Custom Packaging
include(ClhepPackaging)
