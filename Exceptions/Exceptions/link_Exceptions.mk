# $Id: link_Exceptions.mk,v 1.3 2004/04/29 02:47:30 garren Exp $
#
# Makefile fragment for PackageList linking system
#
override LINK_ZMutility   += Exceptions
override LINK_STLUtility  += HepTuple
ifeq (BABAR,$(EXPERIMENT))
     override CPPFLAGS += -DDEFECT_NO_MUTABLE
endif
