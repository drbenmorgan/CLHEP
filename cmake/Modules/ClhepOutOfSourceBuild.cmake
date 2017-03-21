# Throw a fatal error if cmake is invoked from within the source code directory tree
# clhep_ensure_out_of_source_build()
#

# we need the full path here because we check for an out of source build before anything else
include(${CMAKE_CURRENT_SOURCE_DIR}/cmake/Modules/ClhepRegexEscape.cmake)

macro (clhep_ensure_out_of_source_build)

  string(COMPARE EQUAL "${CMAKE_SOURCE_DIR}" "${CMAKE_BINARY_DIR}" in_source)
  clhep_regex_escape( "${CMAKE_SOURCE_DIR}" escaped_path)
  set(my_source_dir "^${escaped_path}$")
  clhep_regex_escape( "${CMAKE_BINARY_DIR}" escaped_path)
  set(my_binary_dir "^${escaped_path}$")
  string( REGEX MATCH "${my_source_dir}/" in_source_subdir "${my_binary_dir}")
  if (in_source OR in_source_subdir)
  message(FATAL_ERROR "
ERROR: In source builds of this project are not allowed.
A separate build directory is required.
Please create one and run cmake from the build directory.
Also note that cmake has just added files to your source code directory.
We suggest getting a new copy of the source code.
Otherwise, delete `CMakeCache.txt' and the directory `CMakeFiles'.
  ")
  endif ()

endmacro (clhep_ensure_out_of_source_build)
