#------------------------------------------------------------------------------
# Top Level CMakeLists.txt for CLHEP
#  cmake [-DCMAKE_INSTALL_PREFIX=/install/path] 
#        [-DCMAKE_BUILD_TYPE=Debug|Release|RelWithDebInfo|MinSizeRel]
#        [-DCMAKE_C_COMPILER=...] [-DCMAKE_CXX_COMPILER=...]
#        [-DCLHEP_BUILD_CXXSTD=ON] (c++11 extensions and thread support)
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

# use cmake 2.6 or later
cmake_minimum_required(VERSION 2.6)

# project name
project(CLHEP)
set( VERSION 2.2.0.4 )

set(CMAKE_MODULE_PATH 
      ${CMAKE_CURRENT_SOURCE_DIR}/cmake/Modules 
      ${CMAKE_MODULE_PATH}
      )

# CLHEP_BUILD_DOCS is OFF (false) by default
option(CLHEP_BUILD_DOCS "Build and install CLHEP documentation" OFF)
if(CLHEP_BUILD_DOCS)
  # backwards compatibility variable
  set(build_docs ON)
  message(STATUS "Enabled build and install of documents")
endif()

# enable use of LIB_SUFFIX
include(ClhepVariables)
clhep_lib_suffix()

# CLHEP custom modules
include(ClhepCopyHeaders)
include(ClhepBuildTest)
include(ClhepBuildLibrary)
include(CheckFunctionExists)
include(ClhepToolchain)

# because we want to move these libraries about,
# do not embed full path in shared libraries or executables
set(CMAKE_SKIP_RPATH)

ENABLE_TESTING()

# include search path
include_directories ("${PROJECT_BINARY_DIR}")
# add CLHEP/Random to search path so we find gaussTables.cdat
include_directories ("${CMAKE_SOURCE_DIR}/Random")

# Put all library build products in standard locations under build tree
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/lib)

# define common flags
set( CMAKE_INCLUDE_PATH  ${CLHEP_BINARY_DIR} )

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

# Custom Packaging
include(ClhepPackaging)
