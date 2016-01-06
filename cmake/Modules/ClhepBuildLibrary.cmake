# Build package libraries.
# Build the main CLHEP source code list as we go.
#
# Recommended use:
# clhep_build_library( <package> <source code files> )
#

macro(clhep_build_library package)
  set(CLHEP_${package}_SOURCES ${ARGN})

  # build up the source list for CLHEP
  set(CLHEP_${package}_list CACHE INTERNAL "${package} sources" FORCE)
  foreach(file ${ARGN})
    set(CLHEP_${package}_list
        ${CLHEP_${package}_list} ${CMAKE_CURRENT_SOURCE_DIR}/${file}
        CACHE INTERNAL "${package} sources"
        )
  endforeach()

  # check for dependencies
  set(package_library_list)
  set(package_library_list_static)
  if(${PACKAGE}_DEPS)
    foreach(dep ${${PACKAGE}_DEPS})
      list(APPEND package_library_list ${dep})
      list(APPEND package_library_list_static ${dep}S)
     endforeach()
  endif()

  # Add the libraries and set properties
  add_library(${package}  SHARED ${CLHEP_${package}_SOURCES})
  add_library(${package}S STATIC ${CLHEP_${package}_SOURCES})

  set_target_properties(${package} ${package}S
    PROPERTIES
      OUTPUT_NAME CLHEP-${package}-${CLHEP_VERSION}
      COMPILE_FEATURES "${CLHEP_CXX_COMPILE_FEATURES}"
      INTERFACE_COMPILE_FEATURES "${CLHEP_CXX_COMPILE_FEATURES}"
      )

  target_link_libraries(${package}  ${package_library_list})
  target_link_libraries(${package}S ${package_library_list_static})

  # Install the libraries
  install(TARGETS ${package} ${package}S
    EXPORT CLHEPLibraryDepends
    RUNTIME DESTINATION bin
    LIBRARY DESTINATION lib${LIB_SUFFIX}
    ARCHIVE DESTINATION lib${LIB_SUFFIX}
    )
endmacro()


macro(clhep_build_libclhep)
  foreach(pkg ${ARGN})
    list(APPEND CLHEP_DEPS ${LIBRARY_OUTPUT_PATH}/${CMAKE_STATIC_LIBRARY_PREFIX}CLHEP-${pkg}-${CLHEP_VERSION}${CMAKE_STATIC_LIBRARY_SUFFIX})
    list(APPEND clhep_sources ${CLHEP_${pkg}_list})
  endforeach()

  add_library(CLHEP  SHARED ${clhep_sources})
  add_library(CLHEPS STATIC ${clhep_sources})

  set_target_properties(CLHEP CLHEPS
    PROPERTIES
      COMPILE_FEATURES "${CLHEP_CXX_COMPILE_FEATURES}"
      INTERFACE_COMPILE_FEATURES "${CLHEP_CXX_COMPILE_FEATURES}"
      OUTPUT_NAME CLHEP-${CLHEP_VERSION}
      )

  # export creates library dependency files for CLHEPConfig.cmake
  install(TARGETS CLHEP CLHEPS
    EXPORT CLHEPLibraryDepends
    RUNTIME DESTINATION bin
    LIBRARY DESTINATION lib${LIB_SUFFIX}
    ARCHIVE DESTINATION lib${LIB_SUFFIX}
    )

  if(${CMAKE_SYSTEM_NAME} MATCHES "Windows")
    file(WRITE ${CMAKE_CURRENT_BINARY_DIR}/clhep_static_symlink
        "execute_process(COMMAND \"${CMAKE_COMMAND}\" -E copy ${CMAKE_STATIC_LIBRARY_PREFIX}CLHEP-${CLHEP_VERSION}${CMAKE_STATIC_LIBRARY_SUFFIX} ${CMAKE_STATIC_LIBRARY_PREFIX}CLHEP${CMAKE_STATIC_LIBRARY_SUFFIX} WORKING_DIRECTORY \"$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib${LIB_SUFFIX}\" )" )
    file(WRITE ${CMAKE_CURRENT_BINARY_DIR}/clhep_shared_symlink
        "execute_process(COMMAND \"${CMAKE_COMMAND}\" -E copy ${CMAKE_SHARED_LIBRARY_PREFIX}CLHEP-${CLHEP_VERSION}${CMAKE_SHARED_LIBRARY_SUFFIX} ${CMAKE_SHARED_LIBRARY_PREFIX}CLHEP${CMAKE_SHARED_LIBRARY_SUFFIX} WORKING_DIRECTORY \"$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin\" )" )
  else()
    file(WRITE ${CMAKE_CURRENT_BINARY_DIR}/clhep_static_symlink
        "execute_process(COMMAND \"${CMAKE_COMMAND}\" -E create_symlink ${CMAKE_STATIC_LIBRARY_PREFIX}CLHEP-${CLHEP_VERSION}${CMAKE_STATIC_LIBRARY_SUFFIX} ${CMAKE_STATIC_LIBRARY_PREFIX}CLHEP${CMAKE_STATIC_LIBRARY_SUFFIX} WORKING_DIRECTORY \"\$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib${LIB_SUFFIX}\" )" )
    file(WRITE ${CMAKE_CURRENT_BINARY_DIR}/clhep_shared_symlink
        "execute_process(COMMAND \"${CMAKE_COMMAND}\" -E create_symlink ${CMAKE_SHARED_LIBRARY_PREFIX}CLHEP-${CLHEP_VERSION}${CMAKE_SHARED_LIBRARY_SUFFIX} ${CMAKE_SHARED_LIBRARY_PREFIX}CLHEP${CMAKE_SHARED_LIBRARY_SUFFIX} WORKING_DIRECTORY \"\$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib${LIB_SUFFIX}\" )" )
  endif()

  install(SCRIPT ${CMAKE_CURRENT_BINARY_DIR}/clhep_static_symlink)
  install(SCRIPT ${CMAKE_CURRENT_BINARY_DIR}/clhep_shared_symlink)
endmacro()

