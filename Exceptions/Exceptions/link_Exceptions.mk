# $Id: link_Exceptions.mk,v 1.2.2.1 2004/04/29 00:20:35 garren Exp $
#
# Makefile fragment for PackageList linking system
#
override LINK_ZMutility   += Exceptions
override LINK_STLUtility  += HepTuple
ifeq (BABAR,$(EXPERIMENT))
     override CPPFLAGS += -DDEFECT_NO_MUTABLE
endif
