# run latex

# clhep_latex( package main_tex_file [other tex or sty files to include] )

# for documentation
find_package(LATEX)

macro(clhep_latex package main_tex_file)
  if(LATEX_COMPILER)
    foreach(arg ${ARGN})
      configure_file(${CMAKE_CURRENT_SOURCE_DIR}/${arg}
                     ${CMAKE_CURRENT_BINARY_DIR}/${arg} COPYONLY)
      set(depend_list ${arg} ${depend_list})
    endforeach()

    add_custom_command(
      OUTPUT    ${CMAKE_CURRENT_BINARY_DIR}/${main_tex_file}.aux
      COMMAND   ${LATEX_COMPILER}
                -interaction=batchmode
                ${CMAKE_CURRENT_SOURCE_DIR}/${main_tex_file}
      DEPENDS   ${CMAKE_CURRENT_SOURCE_DIR}/${main_tex_file}.tex
                ${depend_list}
      COMMENT   "Latex - first pass"
      )

    add_custom_command(
      OUTPUT    ${CMAKE_CURRENT_BINARY_DIR}/${main_tex_file}.dvi
      COMMAND   ${LATEX_COMPILER}
                -interaction=batchmode
                ${CMAKE_CURRENT_SOURCE_DIR}/${main_tex_file}
      DEPENDS   ${CMAKE_CURRENT_BINARY_DIR}/${main_tex_file}.aux
      COMMENT   "Latex - second pass"
      )

    add_custom_command(
      OUTPUT    ${CMAKE_CURRENT_BINARY_DIR}/${main_tex_file}.log
      COMMAND   ${LATEX_COMPILER}
                -interaction=batchmode
                ${CMAKE_CURRENT_SOURCE_DIR}/${main_tex_file}
      DEPENDS   ${CMAKE_CURRENT_BINARY_DIR}/${main_tex_file}.dvi
      COMMENT   "Latex - third pass"
      )

    add_custom_target(${main_tex_file} ALL echo
      DEPENDS  ${CMAKE_CURRENT_BINARY_DIR}/${main_tex_file}.log
      )

    if(DVIPS_CONVERTER)
      add_custom_command(
        OUTPUT    ${CMAKE_CURRENT_BINARY_DIR}/${main_tex_file}.ps
        COMMAND   ${DVIPS_CONVERTER}
                  ${CMAKE_CURRENT_BINARY_DIR}/${main_tex_file}.dvi
                  -o ${CMAKE_CURRENT_BINARY_DIR}/${main_tex_file}.ps
        DEPENDS   ${CMAKE_CURRENT_BINARY_DIR}/${main_tex_file}.dvi
        COMMENT   "dvi2ps"
        )

      if(PS2PDF_CONVERTER)
        add_custom_command(
          OUTPUT    ${CMAKE_CURRENT_BINARY_DIR}/${main_tex_file}.pdf
          COMMAND   ${PS2PDF_CONVERTER}
                    ${CMAKE_CURRENT_BINARY_DIR}/${main_tex_file}.ps
          DEPENDS   ${CMAKE_CURRENT_BINARY_DIR}/${main_tex_file}.ps
          COMMENT   "ps2pdf"
          )

        add_custom_target(${package}${main_tex_file}Document ALL echo
          DEPENDS  ${CMAKE_CURRENT_BINARY_DIR}/${main_tex_file}.pdf
          )
      endif()
    endif()

    install(FILES ${CMAKE_CURRENT_BINARY_DIR}/${main_tex_file}.pdf
            DESTINATION doc/${package})
  endif()
endmacro()

