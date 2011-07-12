# since the CLHEP source code installation does not have the
# expected header paths, install headers in the build directory
#
# Recommended use:
# clhep_copy_headers( <package_list> )

macro (clhep_copy_headers )
  foreach( package ${ARGN} )
     message(STATUS "checking for headers in ${package}")
     FILE( GLOB headers 
                ${CLHEP_SOURCE_DIR}/${package}/${package}/*.h
                ${CLHEP_SOURCE_DIR}/${package}/${package}/*.hh
                ${CLHEP_SOURCE_DIR}/${package}/${package}/*.icc )
     FILE( GLOB defs ${CLHEP_SOURCE_DIR}/${package}/${package}/cmake-defs.h.in )
     foreach( defhdr ${defs} )
       set( PACKAGE ${package} )
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
 
endmacro (clhep_copy_headers)
