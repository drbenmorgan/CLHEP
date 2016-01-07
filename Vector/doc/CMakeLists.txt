# build Vector documentation

include(ClhepBuildTex)

clhep_latex(Vector eulerAngleComputation)
clhep_latex(Vector VectorDefs)

install(
  FILES
    keyMergeIssues.doc
    merge-details.doc
    minorMergeIssues.doc
  DESTINATION
    ${CMAKE_INSTALL_DATAROOTDIR}/${PROJECT_NAME}/doc/Vector
  )

