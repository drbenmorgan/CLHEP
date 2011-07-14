# build Vector documentation

include(ClhepBuildTex)

clhep_latex( Vector eulerAngleComputation )
clhep_latex( Vector VectorDefs )


INSTALL (FILES keyMergeIssues.doc
               merge-details.doc
	       minorMergeIssues.doc
         DESTINATION doc/Vector )

