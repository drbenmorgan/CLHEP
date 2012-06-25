# since the CLHEP source code installation does not have the
# expected header paths, install headers in the build directory
#
# Recommended use:
# clhep_copy_headers( <package_list> )

include(ClhepParseVersion)

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
       #STRING( REPLACE ${CMAKE_CURRENT_SOURCE_DIR}/${package}  ${CLHEP_BINARY_DIR}/CLHEP output_file ${hdr})
       set(output_dir ${CLHEP_BINARY_DIR}/CLHEP/${package})
       get_filename_component(shorthdr ${hdr} NAME)
       ##message(STATUS "moving ${shorthdr} to ${output_dir}")
       # this copies the file and creates directories if necessary
       CONFIGURE_FILE( ${hdr} ${output_dir}/${shorthdr}  COPYONLY )
     endforeach( hdr )
  endforeach(package)
  # get ClhepVersion.h
  parse_version( CLHEP ${VERSION} )
  CONFIGURE_FILE( ${CLHEP_SOURCE_DIR}/cmake/Templates/ClhepVersion.h.in 
                  ${CLHEP_BINARY_DIR}/CLHEP/ClhepVersion.h  @ONLY )
  INSTALL (FILES ${CLHEP_BINARY_DIR}/CLHEP/ClhepVersion.h
           DESTINATION include/CLHEP )
  
endmacro (clhep_copy_headers)
