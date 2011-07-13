# Build package libraries.
# Build the main libCLHEP source code list as we go.
#
# Recommended use:
# clhep_build_library( <package> <source code files> )
# 

macro (clhep_build_library package )
  set ( libCLHEP_${package}_SOURCES ${ARGN} )
  # build up the source list for libCLHEP
  set( CLHEP_${package}_list CACHE INTERNAL "${package} sources" FORCE )
  foreach( file ${ARGN} )
    set( CLHEP_${package}_list ${CLHEP_${package}_list} ${CMAKE_CURRENT_SOURCE_DIR}/${file}
                             CACHE INTERNAL "${package} sources" )
  endforeach(file)
  ##message( STATUS "in ${package}, clheplib source list ${CLHEP_${package}_list}" )
  # check for dependencies
  set ( package_library_list )
  if( ${PACKAGE}_DEPS )
     foreach ( dep ${${PACKAGE}_DEPS} )
        ##message( STATUS "clhep_build_library ${package} will use ${dep}")
	list(APPEND package_library_list ${dep} )
     endforeach()
  endif()
  ADD_LIBRARY (${package}  SHARED ${libCLHEP_${package}_SOURCES})
  ADD_LIBRARY (${package}S STATIC ${libCLHEP_${package}_SOURCES})
  SET_TARGET_PROPERTIES (${package}
      PROPERTIES OUTPUT_NAME CLHEP-${package}-${VERSION}
      )
  SET_TARGET_PROPERTIES (${package}S
      PROPERTIES OUTPUT_NAME CLHEP-${package}-${VERSION}
      )
  SET_TARGET_PROPERTIES(${package}  PROPERTIES CLEAN_DIRECT_OUTPUT 1)
  SET_TARGET_PROPERTIES(${package}S PROPERTIES CLEAN_DIRECT_OUTPUT 1)
  target_link_libraries(${package}  ${package_library_list} )
  target_link_libraries(${package}S ${package_library_list} )

  INSTALL (TARGETS ${package} ${package}S
      RUNTIME DESTINATION bin
      LIBRARY DESTINATION lib
      ARCHIVE DESTINATION lib
      ) 
endmacro (clhep_build_library)

macro (clhep_build_libclhep )
  foreach( pkg ${ARGN} )
     ##message( STATUS "${pkg} sources are ${CLHEP_${pkg}_list}" )
     list(APPEND CLHEP_DEPS ${LIBRARY_OUTPUT_PATH}/libCLHEP-${pkg}-${VERSION}.a )
     list(APPEND clhep_sources ${CLHEP_${pkg}_list} )
  endforeach()
  ##message( STATUS "clheplib source list ${clhep_sources}" )
  ADD_LIBRARY (CLHEP  SHARED ${clhep_sources})
  ADD_LIBRARY (CLHEPS STATIC ${clhep_sources})
  SET_TARGET_PROPERTIES (CLHEP
      PROPERTIES OUTPUT_NAME CLHEP-${VERSION}
                 CLEAN_DIRECT_OUTPUT 1
      )
  SET_TARGET_PROPERTIES (CLHEPS
      PROPERTIES OUTPUT_NAME CLHEP-${VERSION}
                 CLEAN_DIRECT_OUTPUT 1
      )

  INSTALL (TARGETS CLHEP CLHEPS
      RUNTIME DESTINATION bin
      LIBRARY DESTINATION lib
      ARCHIVE DESTINATION lib
      ) 
endmacro (clhep_build_libclhep )
