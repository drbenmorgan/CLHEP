# - ClhepPackaging
#
# This module provides CPack configuration for CLHEP
#

# original code supplied by Ben Morgan Ben.Morgan@warwick.ac.uk
# modifications by Lynn Garren garren@fnal.gov

# the binary tarball should, e.g., have this format:
# x86_64-slc5-gcc46-opt/include
#                      /bin
#                      /lib
#                      /doc (optional)
# basically, the tarball should mirror the install directory, 
# but with the appropriate top level directory
# tarball names: clhep-2.1.1.0-x86_64-slc5-gcc46-opt.tgz
#                clhep-2.1.1.0-x86_64-slc5-gcc41-opt.tgz
#                clhep-2.1.1.0-x86_64-mac106-gcc42-opt.tgz

# result of lsb_release -s -i on various platforms
# Scientific Linux Fermi 5.x: ScientificSLF
# Scientific Linux Fermi 6.x: ScientificFermi
# Scientific Linux CERN 5.x: ScientificCERNSLC
# Scientific Linux CERN 6.x: ScientificFermi
# no lsb_release on lx64slc6.cern.ch machines?

include(ClhepPackageCompiler)

#----------------------------------------------------------------------------
# Package up needed system libraries - seems to only be needed on Windows
#
if("${CPACK_SYSTEM_NAME}" MATCHES Windows)
  include(InstallRequiredSystemLibraries)
endif()

#----------------------------------------------------------------------------
# General packaging setup - variables relevant to all package formats
# CLHEP use of version variables is non-standard
set(CPACK_PACKAGE_VERSION ${VERSION})

set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "Class Library for High Energy Physics")
set(CPACK_PACKAGE_VENDOR "CLHEP Project")

# add a top level directory with the same name as the package tarball
set( CPACK_INCLUDE_TOPLEVEL_DIRECTORY 1 )
set( CPACK_GENERATOR TGZ )
set( CPACK_PACKAGE_NAME clhep )

clhep_package_compiler()

#----------------------------------------------------------------------------
# Set name of CPACK_SYSTEM_NAME based on platform and architecture where 
# needed. We do this because we may want to produce packages for, say,
# 32 and 64 bit arches on linux.
#
# N.B. This is all UNTESTED for the cross-compile case!!!
#
if(NOT DEFINED CPACK_SYSTEM_NAME)
  # Cygwin is always Cygwin...
  if("${CMAKE_SYSTEM_NAME}" MATCHES "CYGWIN")
    set(CPACK_SYSTEM_NAME Cygwin)
  else()
    if(UNIX AND NOT APPLE)
      # On Linux, try and find lsb_release
      find_program(LSB_RELEASE_PROGRAM lsb_release DOC "The Linux Standard Base system query tool")

      if(LSB_RELEASE_PROGRAM)
        # We have linux, so incorporate Vendor info into package name
        # - Distributor ID
	execute_process(COMMAND ${LSB_RELEASE_PROGRAM} -s -i OUTPUT_VARIABLE LSB_VENDOR OUTPUT_STRIP_TRAILING_WHITESPACE)
        string(REGEX REPLACE " " "-" LSB_VENDOR ${LSB_VENDOR})
        string(TOLOWER ${LSB_VENDOR} LSB_VENDOR)
	if("${LSB_VENDOR}" MATCHES "scientificslf")
	   set(LSB_VENDOR "slf")
	elseif("${LSB_VENDOR}" MATCHES "scientificfermilts")
	   set(LSB_VENDOR "slf")
	elseif("${LSB_VENDOR}" MATCHES "scientificfermi")
	   set(LSB_VENDOR "slf")
	elseif("${LSB_VENDOR}" MATCHES "scientificcernslc")
	   set(LSB_VENDOR "slc")
	else()
	   set(LSB_VENDOR ${LSB_VENDOR})
	endif()

        # - Distributor release
	execute_process(COMMAND ${LSB_RELEASE_PROGRAM} -s -r OUTPUT_VARIABLE LSB_RELEASE OUTPUT_STRIP_TRAILING_WHITESPACE)
        string(TOLOWER ${LSB_RELEASE} LSB_RELEASE)
	string(REGEX REPLACE "([0-9])\\.([0-9])?" "\\1" LSB_RELEASE ${LSB_RELEASE})

        # Cache the vendor tag, because users might want to edit it
        set(LSB_VENDOR_TAG ${LSB_VENDOR}${LSB_RELEASE} 
          CACHE STRING "LSB vendor tag for use in packaging")

	if( NOT CPack_COMPILER_STRING )
          set(CPACK_SYSTEM_NAME
            ${CMAKE_SYSTEM_PROCESSOR}-${LSB_VENDOR_TAG})
	else()
          set(CPACK_SYSTEM_NAME
            ${CMAKE_SYSTEM_PROCESSOR}-${LSB_VENDOR_TAG}${CPack_COMPILER_STRING})
	endif()
        mark_as_advanced(LSB_RELEASE_PROGRAM LSB_VENDOR_TAG)
      else()
        # Fallback to using NAME-ARCH on other UNICES other than Apple
        set(CPACK_SYSTEM_NAME ${CMAKE_SYSTEM_PROCESSOR}-${CMAKE_SYSTEM_NAME}${CPack_COMPILER_STRING})
      endif()
    else()
      # On Mac, we use NAME-ARCH, but ARCH is 'Universal' if more than
      # one arch is built for. Note that falling back to use
      # CMAKE_SYSTEM_PROCESSOR may *not* be 100% reliable.
      list(LENGTH CMAKE_OSX_ARCHITECTURES _number_of_arches)

      # CERN uses mac106 for Snow Leopard
      string(REGEX REPLACE "([0-9])\\.([0-9])?" "\\1\\2" LSB_RELEASE ${CMAKE_SYSTEM_VERSION})
      if("${LSB_RELEASE}" MATCHES "108")
         set(BASE_SYSTEM_NAME mac106)
      else()
         set(BASE_SYSTEM_NAME mac${LSB_RELEASE})
      endif()

      if(NOT _number_of_arches)
        # - Default
        set(CPACK_SYSTEM_NAME ${CMAKE_SYSTEM_PROCESSOR}-${BASE_SYSTEM_NAME}${CPack_COMPILER_STRING})
      elseif(_number_of_arches GREATER 1)
        # - Universal
        set(CPACK_SYSTEM_NAME ${BASE_SYSTEM_NAME}-Universal)
      else()
        # - Use what the user specified
        set(CPACK_SYSTEM_NAME ${CMAKE_OSX_ARCHITECTURES}-${BASE_SYSTEM_NAME}${CPack_COMPILER_STRING})
      endif()
    endif()
  endif()
endif()

# On Windows, distinguish x64 and x86 - not sure this is really needed yet!!!
if("${CPACK_SYSTEM_NAME}" MATCHES Windows)
  if(CMAKE_CL_64)
    set(CPACK_SYSTEM_NAME win64-x64)
  else()
    set(CPACK_SYSTEM_NAME win32-x86)
  endif()
endif()

# check for extra qualifiers
if( NOT  CMAKE_BUILD_TYPE )
   SET( CMAKE_BUILD_TYPE_TOLOWER default )
else()
   STRING(TOLOWER ${CMAKE_BUILD_TYPE} CMAKE_BUILD_TYPE_TOLOWER)
   if( ${CMAKE_BUILD_TYPE_TOLOWER} MATCHES "debug")
      set(CPACK_SYSTEM_NAME ${CPACK_SYSTEM_NAME}-debug )
   elseif( ${CMAKE_BUILD_TYPE_TOLOWER} MATCHES "relwithdebinfo")
      set(CPACK_SYSTEM_NAME ${CPACK_SYSTEM_NAME}-opt )
   else()
      set(CPACK_SYSTEM_NAME ${CPACK_SYSTEM_NAME}-${CMAKE_BUILD_TYPE_TOLOWER} )
   endif()   
endif()

message(STATUS "clhep CPACK_PACKAGE_NAME:    ${CPACK_PACKAGE_NAME} " )
message(STATUS "clhep CPACK_PACKAGE_VERSION: ${CPACK_PACKAGE_VERSION} " )
message(STATUS "clhep CPACK_SYSTEM_NAME:     ${CPACK_SYSTEM_NAME}" )

#----------------------------------------------------------------------------
# Finally, include the base CPack configuration
#
include(CPack)

