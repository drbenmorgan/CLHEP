# $Id: link_Exceptions.mk,v 1.2 2004/04/27 17:08:42 garren Exp $
#
# Makefile fragment for PackageList linking system
#
override LINK_ZMutility   += Exceptions
override LINK_STLUtility  += HepTuple
ifeq (BABAR,$(EXPERIMENT))
     override CPPFLAGS += -DDEFECT_NO_MUTABLE
endif
