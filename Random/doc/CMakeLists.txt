# install Random documentation

install(
  FILES
    Random.html
    validation.doc
    JamesRandomSeeding.txt
    html/CLHEP-random.html
    html/onSavingRandomStates.html
  DESTINATION
    ${CMAKE_INSTALL_DATAROOTDIR}/${PROJECT_NAME}/doc/Random
  )

