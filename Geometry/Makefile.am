## Process this file with automake to produce Makefile.in

includedir = $(prefix)/include/CLHEP

# put . first so that CLHEP directory is built before anything else
SUBDIRS = Geometry . src test

all-local: $(top_builddir)/CLHEP

# create temporary CLHEP header tree
# search for header directories in the following order:
#	1.  $(top_srcdir)/..
#	2.  $(CLHEPSOURCE_DIR)/CLHEP
#	3.  $(CLHEP_DIR)/CLHEP
#
# abs_ => absolute path
abs_top_builddir = @abs_top_builddir@
abs_top_srcdir = @abs_top_srcdir@

$(top_builddir)/CLHEP:
	mkdir $(top_builddir)/CLHEP;
	cd $(abs_top_builddir); list=`ls $(abs_top_srcdir)/..`;  \
	for pkg in $$list; do \
	  if test -d $(abs_top_srcdir)/../"$$pkg"/"$$pkg"; then \
	    (cd $(abs_top_builddir)/CLHEP; mkdir $$pkg; cd $$pkg; \
	    hdrs=`ls $(abs_top_srcdir)/../$$pkg/$$pkg`; \
	    for hdr in $$hdrs; do $(LN_S) $(abs_top_srcdir)/../$$pkg/$$pkg/$$hdr $$hdr; done; \
	    if test -f $(abs_top_builddir)/../"$$pkg"/"$$pkg"/defs.h; then $(LN_S) $(abs_top_builddir)/../$$pkg/$$pkg/defs.h defs.h; fi; \
	    if test -f $(abs_top_builddir)/"$$pkg"/defs.h && test ! -e defs.h ; then $(LN_S) $(abs_top_builddir)/$$pkg/defs.h defs.h; fi); \
	  fi; done
	cd $(abs_top_builddir);  \
	if test -n $(CLHEPSOURCE_DIR) && test -d $(CLHEPSOURCE_DIR)/CLHEP; then \
	  (list=`ls $(CLHEPSOURCE_DIR)/CLHEP`;  \
	  for pkg in $$list; do cd $(abs_top_builddir)/CLHEP; \
	    if test -d $(CLHEPSOURCE_DIR)/CLHEP/"$$pkg"/"$$pkg" && test ! -d "$$pkg"; then \
	      (mkdir $$pkg; cd $$pkg; \
	      hdrs=`ls $(CLHEPSOURCE_DIR)/CLHEP/$$pkg/$$pkg`; \
	      for hdr in $$hdrs; do $(LN_S) $(CLHEPSOURCE_DIR)/CLHEP/$$pkg/$$pkg/$$hdr $$hdr; done); \
	    fi; done); fi
	cd $(abs_top_builddir);  \
	if test -n $(CLHEP_DIR) && test -d $(CLHEP_DIR)/CLHEP; then \
	  (list=`ls $(CLHEP_DIR)/CLHEP`;  \
	  for pkg in $$list; do cd $(abs_top_builddir)/CLHEP; \
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
