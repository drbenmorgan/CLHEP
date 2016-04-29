#------------------------------------------------------------------------------
# Top Level CMakeLists.txt for CLHEP
#  cmake [-DCMAKE_INSTALL_PREFIX=/install/path]
#        [-DCMAKE_BUILD_TYPE=Debug|Release|RelWithDebInfo|MinSizeRel]
#        [-DCMAKE_C_COMPILER=...] [-DCMAKE_CXX_COMPILER=...]
#        [-DCMAKE_CXX_FLAGS=...]
#        [-DCLHEP_BUILD_CXXSTD="-std=c++NN"] (use specified c++ extension)
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

# project name
project(CLHEP VERSION 2.3.1.1)

# If Policy CMP0042 exists, use NEW to prefer the use of @rpath on
# OS X
if(POLICY CMP0042)
  cmake_policy(SET CMP0042 NEW)
endif()

list(INSERT CMAKE_MODULE_PATH 0 "${PROJECT_SOURCE_DIR}/cmake/Modules")

# enable use of LIB_SUFFIX
include(ClhepVariables)
clhep_lib_suffix()

# TEMPORARY HACK - set CMAKE_INSTALL_{BIN,LIB,INCLUDE}DIR directly instead
# of using GNUInstallDirs (UNTIL: work out how/where install is used)
set(CMAKE_INSTALL_BINDIR bin)
set(CMAKE_INSTALL_LIBDIR "lib${LIB_SUFFIX}")
set(CMAKE_INSTALL_INCLUDEDIR "include")
set(CMAKE_INSTALL_DATAROOTDIR "share")

#-----------------------------------------------------------------------
# Build docs
# Doxygen here, modules may install additional docs, so perform
# option here before build recurses into these
option(CLHEP_BUILD_DOCS "Build and install CLHEP documentation" OFF)
if(CLHEP_BUILD_DOCS)
  # Build Doxygen
  # Require 1.8.8 or better to allow use of MD file as mainpage
  find_package(Doxygen 1.8.8 REQUIRED)
  configure_file(doxygen.conf "${PROJECT_BINARY_DIR}/doxygen.conf" @ONLY)
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
    DESTINATION "${CMAKE_INSTALL_DATAROOTDIR}/CLHEP/doc"
    )
endif()

# Configure output directories
# Put all library build products in standard locations under build tree
# - Single root dir of all products
set(BASE_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}/BuildProducts")

# - Default outputs for different products, will be used by single mode
#   generators. Creates the structure:
# BuildProducts/
# +- bin/
# +- lib/
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${BASE_OUTPUT_DIRECTORY}/${CMAKE_INSTALL_BINDIR}")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${BASE_OUTPUT_DIRECTORY}/${CMAKE_INSTALL_LIBDIR}")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${BASE_OUTPUT_DIRECTORY}/${CMAKE_INSTALL_LIBDIR}")

# - For multiconfig generators, we create the same structure once for each
#   mode. Results in the structure:
# BuildProducts/
# +- Release/
# |  +- bin/
# |  +- lib/
# +- Debug/
# |  +- bin/
# |  +- lib/
# | ...
#
foreach(_conftype ${CMAKE_CONFIGURATION_TYPES})
  string(TOUPPER ${_conftype} _conftype_uppercase)
  set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_${_conftype_uppercase}
    "${BASE_OUTPUT_DIRECTORY}/${_conftype}/${CMAKE_INSTALL_BINDIR}"
    )
  set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_${_conftype_uppercase}
    "${BASE_OUTPUT_DIRECTORY}/${_conftype}/${CMAKE_INSTALL_LIBDIR}"
    )
  set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_${_conftype_uppercase}
    "${BASE_OUTPUT_DIRECTORY}/${_conftype}/${CMAKE_INSTALL_LIBDIR}"
    )
endforeach()

# CLHEP custom modules
include(ClhepCopyHeaders)
include(ClhepBuildTest)
include(ClhepBuildLibrary)
include(CheckFunctionExists)
include(ClhepToolchain)

enable_testing()

# Create general build include paths
# - Headers are copied to binary dir
# - Random dir of source tree must be present so gaussTables.cdat is found
include_directories("${PROJECT_BINARY_DIR}" "${PROJECT_SOURCE_DIR}/Random")

# set our preferred compiler flags
clhep_set_compiler_flags()

# the main CLHEP config script
clhep_config()

# check for required functions
check_function_exists(drand48 HAVE_DRAND48)

# all the packages
set(CLHEP_subdirs
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
set(CLHEP_libraries
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

clhep_copy_headers(${CLHEP_subdirs})

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
clhep_build_libclhep(${CLHEP_libraries})

# provide tools for other packages to include CLHEP easily
clhep_toolchain()

# Custom Packaging
include(ClhepPackaging)
