# Throw a fatal error if cmake is invoked from the source code directory tree
# clhep_ensure_out_of_source_build()
#

macro (clhep_ensure_out_of_source_build)
  string(FIND "${CMAKE_BINARY_DIR}" "${CMAKE_SOURCE_DIR}" is_subdir_pos)

  if ((CMAKE_BINARY_DIR STREQUAL CMAKE_SOURCE_DIR)
      OR (is_subdir_pos EQUAL 0))
  message(FATAL_ERROR "
ERROR: In source builds of this project are not allowed.
A separate build directory outside of `${CMAKE_SOURCE_DIR}' is required.
Please create one and run cmake from the build directory.
Also note that cmake has just added files to your source code directory.
We suggest getting a new copy of the source code.
Otherwise, delete `CMakeCache.txt' and the directory `CMakeFiles'.
  ")
  endif ()

endmacro ()
