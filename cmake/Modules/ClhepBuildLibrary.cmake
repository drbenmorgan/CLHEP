# Build package libraries.
# Build the main CLHEP source code list as we go.
#
# Recommended use:
# clhep_build_library( <package> <source code files> )
# 

macro(clhep_build_library package)
  set( CLHEP_${package}_SOURCES ${ARGN} )

  # build up the source list for CLHEP
  set( CLHEP_${package}_list CACHE INTERNAL "${package} sources" FORCE )
  foreach( file ${ARGN} )
    set( CLHEP_${package}_list 
         ${CLHEP_${package}_list} ${CMAKE_CURRENT_SOURCE_DIR}/${file}
         CACHE INTERNAL "${package} sources" 
	 )
  endforeach(file)
  ##message( STATUS "in ${package}, clheplib source list ${CLHEP_${package}_list}" )

  # check for dependencies
  set( package_library_list )
  if( ${PACKAGE}_DEPS )
     foreach ( dep ${${PACKAGE}_DEPS} )
        ##message( STATUS "clhep_build_library ${package} will use ${dep}")
	list(APPEND package_library_list ${dep})
     endforeach()
  endif()

  # Add the libraries and set properties
  ADD_LIBRARY(${package}  SHARED ${CLHEP_${package}_SOURCES})
  ADD_LIBRARY(${package}S STATIC ${CLHEP_${package}_SOURCES})
  SET_TARGET_PROPERTIES (${package}
      PROPERTIES 
        OUTPUT_NAME CLHEP-${package}-${VERSION}
	CLEAN_DIRECT_OUTPUT 1
      )
  SET_TARGET_PROPERTIES(${package}S
      PROPERTIES 
        OUTPUT_NAME CLHEP-${package}-${VERSION}
	CLEAN_DIRECT_OUTPUT 1
      )

  target_link_libraries(${package}  ${package_library_list} )
  target_link_libraries(${package}S ${package_library_list} )

  # Install the libraries
  INSTALL (TARGETS ${package} ${package}S
      RUNTIME DESTINATION bin
      LIBRARY DESTINATION lib${LIB_SUFFIX}
      ARCHIVE DESTINATION lib${LIB_SUFFIX}
      ) 
endmacro(clhep_build_library)

macro(clhep_build_libclhep )
  foreach( pkg ${ARGN} )
     ##message( STATUS "${pkg} sources are ${CLHEP_${pkg}_list}" )
     list(APPEND CLHEP_DEPS ${LIBRARY_OUTPUT_PATH}/${CMAKE_STATIC_LIBRARY_PREFIX}CLHEP-${pkg}-${VERSION}${CMAKE_STATIC_LIBRARY_SUFFIX} )
     list(APPEND clhep_sources ${CLHEP_${pkg}_list} )
  endforeach()
  ##message( STATUS "clheplib source list ${clhep_sources}" )

  ADD_LIBRARY (CLHEP  SHARED ${clhep_sources})
  ADD_LIBRARY (CLHEPS STATIC ${clhep_sources})

  SET_TARGET_PROPERTIES(CLHEP
      PROPERTIES 
        OUTPUT_NAME CLHEP-${VERSION}
        CLEAN_DIRECT_OUTPUT 1
      )
  SET_TARGET_PROPERTIES(CLHEPS
      PROPERTIES 
        OUTPUT_NAME CLHEP-${VERSION}
        CLEAN_DIRECT_OUTPUT 1
      )

  # export creates library dependency files for CLHEPConfig.cmake
  INSTALL(TARGETS CLHEP CLHEPS
      EXPORT CLHEPLibraryDepends
      RUNTIME DESTINATION bin
      LIBRARY DESTINATION lib${LIB_SUFFIX}
      ARCHIVE DESTINATION lib${LIB_SUFFIX}
      ) 

  if( ${CMAKE_SYSTEM_NAME} MATCHES "Windows" )
      # copy
      file(WRITE ${CMAKE_CURRENT_BINARY_DIR}/clhep_static_symlink 
        	 "execute_process(COMMAND \"${CMAKE_COMMAND}\" -E copy ${CMAKE_STATIC_LIBRARY_PREFIX}CLHEP-${VERSION}${CMAKE_STATIC_LIBRARY_SUFFIX} ${CMAKE_STATIC_LIBRARY_PREFIX}CLHEP${CMAKE_STATIC_LIBRARY_SUFFIX} WORKING_DIRECTORY \"$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib${LIB_SUFFIX}\" )" )
      file(WRITE ${CMAKE_CURRENT_BINARY_DIR}/clhep_shared_symlink 
        	 "execute_process(COMMAND \"${CMAKE_COMMAND}\" -E copy ${CMAKE_SHARED_LIBRARY_PREFIX}CLHEP-${VERSION}${CMAKE_SHARED_LIBRARY_SUFFIX} ${CMAKE_SHARED_LIBRARY_PREFIX}CLHEP${CMAKE_SHARED_LIBRARY_SUFFIX} WORKING_DIRECTORY \"$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin\" )" )
  else()
      # create the symbolic links
      file(WRITE ${CMAKE_CURRENT_BINARY_DIR}/clhep_static_symlink 
        	 "execute_process(COMMAND \"${CMAKE_COMMAND}\" -E create_symlink ${CMAKE_STATIC_LIBRARY_PREFIX}CLHEP-${VERSION}${CMAKE_STATIC_LIBRARY_SUFFIX} ${CMAKE_STATIC_LIBRARY_PREFIX}CLHEP${CMAKE_STATIC_LIBRARY_SUFFIX} WORKING_DIRECTORY \"\$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib${LIB_SUFFIX}\" )" )
      file(WRITE ${CMAKE_CURRENT_BINARY_DIR}/clhep_shared_symlink 
        	 "execute_process(COMMAND \"${CMAKE_COMMAND}\" -E create_symlink ${CMAKE_SHARED_LIBRARY_PREFIX}CLHEP-${VERSION}${CMAKE_SHARED_LIBRARY_SUFFIX} ${CMAKE_SHARED_LIBRARY_PREFIX}CLHEP${CMAKE_SHARED_LIBRARY_SUFFIX} WORKING_DIRECTORY \"\$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib${LIB_SUFFIX}\" )" )
  endif()

  INSTALL(SCRIPT ${CMAKE_CURRENT_BINARY_DIR}/clhep_static_symlink )
  INSTALL(SCRIPT ${CMAKE_CURRENT_BINARY_DIR}/clhep_shared_symlink )

endmacro(clhep_build_libclhep )
