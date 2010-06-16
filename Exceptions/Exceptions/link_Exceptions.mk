# $Id: link_Exceptions.mk,v 1.4 2010/06/16 15:29:29 garren Exp $
#
# Makefile fragment for PackageList linking system
#
override LINK_ZMutility   += Exceptions
override LINK_STLUtility  += HepTuple
ifeq (BABAR,$(EXPERIMENT))
     override CPPFLAGS += -DDEFECT_NO_MUTABLE
endif
