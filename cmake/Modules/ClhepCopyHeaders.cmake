# since the CLHEP source code installation does not have the
# expected header paths, install headers in the build directory
#
# Recommended use:
# clhep_copy_headers( <package_list> )

macro(clhep_copy_headers)
  foreach(package ${ARGN})
    message(STATUS "checking for headers in ${package}")
    string(TOUPPER ${package} UPACKAGE)
    set(PACKAGE ${package})

    file(GLOB headers
      ${CLHEP_SOURCE_DIR}/${package}/${package}/*.h
      ${CLHEP_SOURCE_DIR}/${package}/${package}/*.hh
      ${CLHEP_SOURCE_DIR}/${package}/${package}/*.icc
      )
    file(GLOB defs ${CLHEP_SOURCE_DIR}/${package}/${package}/cmake-defs.h.in)

    foreach(defhdr ${defs})
      configure_file(${defhdr} ${CLHEP_BINARY_DIR}/CLHEP/${package}/defs.h  @ONLY)
      # install defs.h from here
      install(FILES ${CLHEP_BINARY_DIR}/CLHEP/${package}/defs.h
        DESTINATION include/CLHEP/${package}
        )
    endforeach()

    foreach(hdr ${headers})
      set(output_dir ${CLHEP_BINARY_DIR}/CLHEP/${package})
      get_filename_component(shorthdr ${hdr} NAME)
      # this copies the file and creates directories if necessary
      configure_file(${hdr} ${output_dir}/${shorthdr}  COPYONLY)
    endforeach()
  endforeach()

  # get ClhepVersion.h
  configure_file(${CLHEP_SOURCE_DIR}/cmake/Templates/ClhepVersion.h.in
                 ${CLHEP_BINARY_DIR}/CLHEP/ClhepVersion.h
                 @ONLY
                 )
  install(FILES ${CLHEP_BINARY_DIR}/CLHEP/ClhepVersion.h
          DESTINATION include/CLHEP
          )
endmacro()

