# $Id: link_Exceptions.mk,v 1.1.2.1 2003/12/16 23:15:12 garren Exp $
#
# Makefile fragment for PackageList linking system
#
override LINK_ZMutility   += Exceptions
override LINK_STLUtility  += HepTuple
ifeq (BABAR,$(EXPERIMENT))
     override CPPFLAGS += -DDEFECT_NO_MUTABLE
endif
