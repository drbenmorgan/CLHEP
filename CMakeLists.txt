#------------------------------------------------------------------------------
# Top Level CMakeLists.txt for CLHEP
#  cmake [-DCMAKE_INSTALL_PREFIX=/install/path] 
#        [-DCMAKE_BUILD_TYPE=Debug|Release|RelWithDebInfo|MinSizeRel]
#        [-Dbuild_docs] 
#        /path/to/source
#  make
#  make test
#  make install
#
# The default CLHEP build type is CMAKE_BUILD_TYPE=RelWithDebInfo,
# which matches the default CLHEP autoconf flags
#------------------------------------------------------------------------------

# use cmake 2.6 or later
cmake_minimum_required (VERSION 2.6)
# project name
project(CLHEP)
set( VERSION 2.1.0.1 )

set(CMAKE_MODULE_PATH "${CMAKE_ROOT}/Modules")
set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake/Modules ${CMAKE_MODULE_PATH})
message(STATUS "module path is ${CMAKE_MODULE_PATH}" )
if ( build_docs )
   message(STATUS "documents WILL be built and installed" )
else()
   message(STATUS "documents WILL NOT be installed" )
endif()
# various handy macros
include(EnsureOutOfSourceBuild)
include(CopyHeaders)
include(BuildTest)
include(BuildLibrary)
include(ClhepVariables)

# make sure we are not building in source
clhep_ensure_out_of_source_build()

# because we want to move these libraries about,
# do not embed full path in shared libraries or executables
set (CMAKE_SKIP_RPATH)

ENABLE_TESTING()

# include search path
include_directories ("${PROJECT_BINARY_DIR}")

#build all libraries in a single directory to facilitate testing
SET(LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR}/lib)

# define common flags
set( CMAKE_INCLUDE_PATH  ${CLHEP_BINARY_DIR} )
# set our preferred compiler flags
clhep_set_compiler_flags()
# get automake/autoconf variables
clhep_autoconf_variables()


clhep_copy_headers( Units Utility Vector Evaluator GenericFunctions Geometry
                    Random Matrix RandomObjects Cast RefCount Exceptions )

subdirs(Units)
subdirs(Utility) 
subdirs(Vector) 
subdirs(Evaluator) 
subdirs(GenericFunctions) 
subdirs(Geometry) 
subdirs(Random) 
subdirs(Matrix) 
subdirs(RandomObjects) 
subdirs(Cast) 
subdirs(RefCount) 
subdirs(Exceptions)
