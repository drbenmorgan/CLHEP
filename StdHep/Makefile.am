## Process this file with automake to produce Makefile.in


includedir = $(prefix)/include/CLHEP

# put . first so that CLHEP directory is built before anything else
SUBDIRS = StdHep . src
# list all subdirectories - for distribution and cleaning
DIST_SUBDIRS = StdHep . src examples

all-local: $(top_builddir)/CLHEP

# create temporary CLHEP header tree
# search for header directories in the following order:
#	1.  $(top_srcdir)/..
#	2.  $(CLHEPSOURCE_DIR)/CLHEP
#	3.  $(CLHEP_DIR)/CLHEP
$(top_builddir)/CLHEP:
	mkdir $(top_builddir)/CLHEP; linktree=`pwd`;  \
	cd $(top_srcdir)/..; linksource=`pwd`;  \
	list=`ls $$linksource`;  \
	for pkg in $$list; do \
	  if test -d "$$linksource"/"$$pkg"/"$$pkg"; then \
	    (cd $$linktree/CLHEP; mkdir $$pkg; cd $$pkg; \
	    hdrs=`ls $$linksource/$$pkg/$$pkg`; \
	    for hdr in $$hdrs; do $(LN_S) $$linksource/$$pkg/$$pkg/$$hdr $$hdr; done; \
	    if test -f "$$linktree"/../"$$pkg"/"$$pkg"/defs.h; then $(LN_S) $$linktree/../$$pkg/$$pkg/defs.h defs.h; fi; \
	    if test -f "$$linktree/$$pkg"/defs.h && test ! -l defs.h ; then $(LN_S) $$linktree/$$pkg/defs.h defs.h; fi); \
	  fi; done
	cd $(top_builddir); linktree=`pwd`; \
	if test -n $(CLHEPSOURCE_DIR) && test -d $(CLHEPSOURCE_DIR)/CLHEP; then \
	  (list=`ls $(CLHEPSOURCE_DIR)/CLHEP`;  \
	  for pkg in $$list; do cd $$linktree/CLHEP; \
	    if test -d $(CLHEPSOURCE_DIR)/CLHEP/"$$pkg"/"$$pkg" && test ! -d "$$pkg"; then \
	      (mkdir $$pkg; cd $$pkg; \
	      hdrs=`ls $(CLHEPSOURCE_DIR)/CLHEP/$$pkg/$$pkg`; \
	      for hdr in $$hdrs; do $(LN_S) $(CLHEPSOURCE_DIR)/CLHEP/$$pkg/$$pkg/$$hdr $$hdr; done); \
	    fi; done); fi
	cd $(top_builddir); linktree=`pwd`; \
	if test -n $(CLHEP_DIR) && test -d $(CLHEP_DIR)/CLHEP; then \
	  (list=`ls $(CLHEP_DIR)/CLHEP`;  \
	  for pkg in $$list; do cd $$linktree/CLHEP; \
	    if test -d $(CLHEP_DIR)/CLHEP/"$$pkg"/"$$pkg" && test ! -d "$$pkg"; then \
	      (mkdir $$pkg; cd $$pkg; \
	      hdrs=`ls $(CLHEP_DIR)/CLHEP/$$pkg/$$pkg`; \
	      for hdr in $$hdrs; do $(LN_S) $(CLHEP_DIR)/CLHEP/$$pkg/$$pkg/$$hdr $$hdr; done); \
	    fi; done); fi

docs:
	cd doc; $(MAKE) $(AM_MAKEFLAGS)

install-docs:
	cd doc; $(MAKE) $(AM_MAKEFLAGS) install-docs

# extra clean rule
clean-local:
	rm -rf $(top_builddir)/CLHEP
