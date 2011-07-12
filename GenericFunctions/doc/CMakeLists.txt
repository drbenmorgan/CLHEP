# build GenericFunctions documentation

include(BuildTex)

clhep_latex( GenericFunctions genericFunctions example.ps
        				       hydrogen.ps
					       PartiallyClosed.ps
					       TotallyClosed.ps
					       WideOpen.ps
					       psfig.sty )
