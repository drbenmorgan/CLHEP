# since the CLHEP source code installation does not have the
# expected header paths, install headers in the build directory
#
# Recommended use:
# clhep_build_library( <package> <source code files> )

macro (clhep_build_library package )
  set ( libCLHEP_${package}_SOURCES ${ARGN} )
  set ( package_library_list )
  if( ${PACKAGE}_DEPS )
     foreach ( dep ${${PACKAGE}_DEPS} )
        message( STATUS "clhep_build_library ${package} will use ${dep}")
	list(APPEND package_library_list ${dep} )
     endforeach()
  endif()
  ADD_LIBRARY (${package}  SHARED ${libCLHEP_${package}_SOURCES})
  ADD_LIBRARY (${package}S STATIC ${libCLHEP_${package}_SOURCES})
  SET_TARGET_PROPERTIES (${package}
      PROPERTIES OUTPUT_NAME CLHEP_${package}-${VERSION}
      )
  SET_TARGET_PROPERTIES (${package}S
      PROPERTIES OUTPUT_NAME CLHEP_${package}-${VERSION}
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
