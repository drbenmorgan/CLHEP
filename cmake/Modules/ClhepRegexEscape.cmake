########################################################################
# clhep_regex_escape(<val> <var> [<num>])
#
#   Escape the provided string to prevent interpretation by the CMake
#   regex engine.
#
# The result of escaping characters which would be interpreted by
# CMake's regex engine is passed through clhep_armor_string if <num> is
# specified and non-zero.
#
########################################################################
# clhep_armor_string(<val> <var> <num>)
#
#    Armor the instances of "\" in the string aginst being passed to a
#    macro (and therefore being interpolated).
#
# The <num> argument indicates the expected interpolation level for the
# resulting string (0 is a NOP). Every time the string is expected to be
# passed to a macro, increase <num> to ensure that "\" are correctly
# handled. This is not necessary for a function.
#
########################################################################
# Author: Chris Green
# See ClhepOutOfSourceBuild for usage
########################################################################

function(clhep_regex_escape val var)
  string(REGEX REPLACE "(\\.|\\||\\^|\\$|\\*|\\(|\\)|\\[|\\]|\\+)" "\\\\\\1" val "${val}")
  string(REGEX REPLACE "/+" "/" val "${val}")
  if (ARGN)
    list(GET ARGN 0 count)
  endif()
  if (count)
    clhep_armor_string("${val}" val ${count})
  endif()
  set(${var} "${val}" PARENT_SCOPE)
endfunction()

function(clhep_armor_string val var count)
  while (count GREATER 0) # Extra escapes for passing to macros.
    string(REPLACE "\\" "\\\\" val "${val}")
    math(EXPR count "${count} - 1")
  endwhile()
  set(${var} "${val}" PARENT_SCOPE)
endfunction()
