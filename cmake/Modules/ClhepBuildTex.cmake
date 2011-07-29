# run latex 

# clhep_latex( package main_tex_file [other tex or sty files to include] )

# for documentation
FIND_PACKAGE(LATEX)

macro( clhep_latex package main_tex_file )
IF(LATEX_COMPILER)
   FOREACH(arg ${ARGN})  
     CONFIGURE_FILE( ${CMAKE_CURRENT_SOURCE_DIR}/${arg} 
                     ${CMAKE_CURRENT_BINARY_DIR}/${arg}  COPYONLY)
     set( depend_list ${arg} ${depend_list} )
   ENDFOREACH(arg) 
   ##message(STATUS "${package} ${main_tex_file} depends on ${depend_list}" )
   ADD_CUSTOM_COMMAND( 
    OUTPUT    ${CMAKE_CURRENT_BINARY_DIR}/${main_tex_file}.aux
    COMMAND   ${LATEX_COMPILER}
              -interaction=batchmode ${CMAKE_CURRENT_SOURCE_DIR}/${main_tex_file}
    DEPENDS   ${CMAKE_CURRENT_SOURCE_DIR}/${main_tex_file}.tex ${depend_list}
    COMMENT   "Latex - first pass"
  )
   ADD_CUSTOM_COMMAND( 
    OUTPUT    ${CMAKE_CURRENT_BINARY_DIR}/${main_tex_file}.dvi
    COMMAND   ${LATEX_COMPILER}
              -interaction=batchmode ${CMAKE_CURRENT_SOURCE_DIR}/${main_tex_file}
    DEPENDS   ${CMAKE_CURRENT_BINARY_DIR}/${main_tex_file}.aux
    COMMENT   "Latex - second pass"
  )
   ADD_CUSTOM_COMMAND( 
    OUTPUT    ${CMAKE_CURRENT_BINARY_DIR}/${main_tex_file}.log
    COMMAND   ${LATEX_COMPILER}
              -interaction=batchmode ${CMAKE_CURRENT_SOURCE_DIR}/${main_tex_file}
    DEPENDS   ${CMAKE_CURRENT_BINARY_DIR}/${main_tex_file}.dvi
    COMMENT   "Latex - third pass"
  )
  ADD_CUSTOM_TARGET(${main_tex_file} ALL echo
    DEPENDS   ${CMAKE_CURRENT_BINARY_DIR}/${main_tex_file}.log
    )

IF(DVIPS_CONVERTER)
    ADD_CUSTOM_COMMAND( 
      OUTPUT    ${CMAKE_CURRENT_BINARY_DIR}/${main_tex_file}.ps
      COMMAND   ${DVIPS_CONVERTER}
                ${CMAKE_CURRENT_BINARY_DIR}/${main_tex_file}.dvi
                -o ${CMAKE_CURRENT_BINARY_DIR}/${main_tex_file}.ps
      DEPENDS   ${CMAKE_CURRENT_BINARY_DIR}/${main_tex_file}.dvi
      COMMENT   "dvi2ps"
   )

 IF(PS2PDF_CONVERTER)
    ADD_CUSTOM_COMMAND( 
      OUTPUT    ${CMAKE_CURRENT_BINARY_DIR}/${main_tex_file}.pdf
      COMMAND   ${PS2PDF_CONVERTER}
                ${CMAKE_CURRENT_BINARY_DIR}/${main_tex_file}.ps
      DEPENDS   ${CMAKE_CURRENT_BINARY_DIR}/${main_tex_file}.ps
      COMMENT   "ps2pdf"
    )

 ADD_CUSTOM_TARGET( ${package}${main_tex_file}Document ALL echo
      DEPENDS   ${CMAKE_CURRENT_BINARY_DIR}/${main_tex_file}.pdf
    )
    ENDIF(PS2PDF_CONVERTER)
  ENDIF(DVIPS_CONVERTER)
ENDIF(LATEX_COMPILER)

INSTALL (FILES ${CMAKE_CURRENT_BINARY_DIR}/${main_tex_file}.pdf
         DESTINATION doc/${package} )
endmacro( clhep_latex )
