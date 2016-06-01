# run latex 

# clhep_latex( package main_tex_file [other tex or sty files to include] )

# for documentation
FIND_PACKAGE(LATEX)

macro( clhep_latex package main_tex_file )
IF(PDFLATEX_COMPILER)
   FOREACH(arg ${ARGN})  
     CONFIGURE_FILE( ${CMAKE_CURRENT_SOURCE_DIR}/${arg} 
                     ${CMAKE_CURRENT_BINARY_DIR}/${arg}  COPYONLY)
     set( depend_list ${arg} ${depend_list} )
   ENDFOREACH(arg) 
   ##message(STATUS "${package} ${main_tex_file} depends on ${depend_list}" )
   ADD_CUSTOM_COMMAND( 
    OUTPUT    ${CMAKE_CURRENT_BINARY_DIR}/${main_tex_file}.aux
    COMMAND   ${PDFLATEX_COMPILER}
              -interaction=batchmode ${CMAKE_CURRENT_SOURCE_DIR}/${main_tex_file}
    DEPENDS   ${CMAKE_CURRENT_SOURCE_DIR}/${main_tex_file}.tex ${depend_list}
    COMMENT   "Latex - first pass"
  )
   ADD_CUSTOM_COMMAND( 
    OUTPUT    ${CMAKE_CURRENT_BINARY_DIR}/${main_tex_file}.log
    COMMAND   ${PDFLATEX_COMPILER}
              -interaction=batchmode ${CMAKE_CURRENT_SOURCE_DIR}/${main_tex_file}
    DEPENDS   ${CMAKE_CURRENT_BINARY_DIR}/${main_tex_file}.aux
    COMMENT   "Latex - second pass"
  )
   ADD_CUSTOM_COMMAND( 
    OUTPUT    ${CMAKE_CURRENT_BINARY_DIR}/${main_tex_file}.pdf
    COMMAND   ${PDFLATEX_COMPILER}
              -interaction=batchmode ${CMAKE_CURRENT_SOURCE_DIR}/${main_tex_file}
    DEPENDS   ${CMAKE_CURRENT_BINARY_DIR}/${main_tex_file}.log
    COMMENT   "Latex - third pass"
  )
  ADD_CUSTOM_TARGET(${main_tex_file} ALL echo
    DEPENDS   ${CMAKE_CURRENT_BINARY_DIR}/${main_tex_file}.pdf
    )

 INSTALL (FILES ${CMAKE_CURRENT_BINARY_DIR}/${main_tex_file}.pdf
          DESTINATION share/doc/CLHEP/${package} )
ENDIF(PDFLATEX_COMPILER)

endmacro( clhep_latex )
