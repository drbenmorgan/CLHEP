## Process this file with automake to produce Makefile.in

includedir = $(prefix)/include/CLHEP

# put . first so that CLHEP directory is built before anything else
SUBDIRS = . HepMC src

all-local: $(top_builddir)/CLHEP

$(top_builddir)/CLHEP:
	$(top_srcdir)/makeCLHEPdir  $(top_srcdir)/..

