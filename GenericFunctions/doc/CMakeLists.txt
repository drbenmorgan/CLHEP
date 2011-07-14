# build GenericFunctions documentation

include(ClhepBuildTex)

clhep_latex( GenericFunctions genericFunctions example.ps
        				       hydrogen.ps
					       PartiallyClosed.ps
					       TotallyClosed.ps
					       WideOpen.ps
					       psfig.sty )
