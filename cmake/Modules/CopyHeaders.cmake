# since the CLHEP source code installation does not have the
# expected header paths, install headers in the build directory
#
# Recommended use:
# clhep_copy_headers( <package_list> )

include(ParseVersion)

macro (clhep_copy_headers )
  foreach( package ${ARGN} )
     message(STATUS "checking for headers in ${package}")
     string(TOUPPER ${package} UPACKAGE )
     set( PACKAGE ${package} )
     if( found_drand48 )
       set( DRAND48_DEF "#define HAVE_DRAND48 1" )
     else()
       set( DRAND48_DEF "#undef HAVE_DRAND48" )
     endif()
     FILE( GLOB headers 
                ${CLHEP_SOURCE_DIR}/${package}/${package}/*.h
                ${CLHEP_SOURCE_DIR}/${package}/${package}/*.hh
                ${CLHEP_SOURCE_DIR}/${package}/${package}/*.icc )
     FILE( GLOB defs ${CLHEP_SOURCE_DIR}/${package}/${package}/cmake-defs.h.in )
     foreach( defhdr ${defs} )
       ##message(STATUS "process ${defhdr} to create ${CLHEP_BINARY_DIR}/CLHEP/${package}/defs.h")
       # this copies the file and creates directories if necessary
       CONFIGURE_FILE( ${defhdr} ${CLHEP_BINARY_DIR}/CLHEP/${package}/defs.h  @ONLY )
       # install defs.h from here
       INSTALL (FILES ${CLHEP_BINARY_DIR}/CLHEP/${package}/defs.h
        	DESTINATION include/CLHEP/${package} )
     endforeach( defhdr )

     foreach( hdr ${headers} )
       STRING( REGEX REPLACE "^(${CMAKE_CURRENT_SOURCE_DIR})/${package}(.*)$"  "${CLHEP_BINARY_DIR}/CLHEP\\2" output_file "${hdr}")
       ##message(STATUS "moving ${hdr} to ${output_file}")
       # this copies the file and creates directories if necessary
       CONFIGURE_FILE( ${hdr} ${output_file}  COPYONLY)
     endforeach( hdr )
  endforeach(package)
  # get ClhepVersion.h
  parse_version( CLHEP ${VERSION} )
  CONFIGURE_FILE( ${CLHEP_SOURCE_DIR}/cmake/Templates/ClhepVersion.h.in 
                  ${CLHEP_BINARY_DIR}/CLHEP/ClhepVersion.h  @ONLY )
  INSTALL (FILES ${CLHEP_BINARY_DIR}/CLHEP/ClhepVersion.h
           DESTINATION include/CLHEP )
  
endmacro (clhep_copy_headers)
