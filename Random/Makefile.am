## Process this file with automake to produce Makefile.in

if USE_GMAKE
  MAKE = gmake
endif

includedir = $(prefix)/include/CLHEP

# put . first so that CLHEP directory is built before anything else
SUBDIRS = Random . src test
# list all subdirectories - for distribution and cleaning
DIST_SUBDIRS = Random . src test doc

bin_SCRIPTS = Random-config

all-local: $(top_builddir)/CLHEP

# create temporary CLHEP header tree
# we only copy headers for packages listed in @PACKAGE@-deps
# search for header directories in the following order:
#	1.  $(top_builddir)/this-package
#	2.  $(top_builddir)/../other-packages
#	3.  $(CLHEPSOURCE_DIR)/CLHEP
#	4.  $(CLHEP_DIR)/include/CLHEP
#
# abs_ => absolute path
abs_top_builddir = @abs_top_builddir@
abs_top_srcdir = @abs_top_srcdir@
COPY_P = @COPY_P@

$(top_builddir)/CLHEP:  temp-package-dirs
	@list="`cat @PACKAGE@-deps | sed s/CLHEP-@PACKAGE@-@VERSION@// | sed s/CLHEP-// | sed s/-@VERSION@//`"; \
	for pkg in $$list; do \
	  if test -d "$$pkg" ; then \
	    (cd $$pkg && $(MAKE) $(AM_MAKEFLAGS) TEMPDIR=$(abs_top_builddir) install-tmpHEADERS) || exit 1 ; \
	  else \
	    if test -d ../"$$pkg"/"$$pkg" ; then \
	      (cd ../$$pkg/$$pkg && $(MAKE) $(AM_MAKEFLAGS) TEMPDIR=$(abs_top_builddir) install-tmpHEADERS) || exit 1 ; \
	    else \
	      if test -d $(CLHEPSOURCE_DIR)/CLHEP/"$$pkg"/"$$pkg"; then \
	        hdrs=`ls $(CLHEPSOURCE_DIR)/CLHEP/$$pkg/$$pkg`; \
	        for hdr in $$hdrs; do $(COPY_P) $(CLHEPSOURCE_DIR)/CLHEP/$$pkg/$$pkg/$$hdr $(abs_top_builddir)/CLHEP/$$pkg/$$hdr; done; \
	      else \
		if test -n "$(CLHEP_DIR)" && test -d $(CLHEP_DIR)/include/CLHEP; then \
		    if test -d $(CLHEP_DIR)/include/CLHEP/"$$pkg"; then \
		      hdrs=`ls $(CLHEP_DIR)/include/CLHEP/$$pkg`; \
		      for hdr in $$hdrs; do $(COPY_P) $(CLHEP_DIR)/include/CLHEP/$$pkg/$$hdr $(abs_top_builddir)/CLHEP/$$pkg/$$hdr; done; \
		    fi; \
	        fi; \
	      fi; \
	    fi; \
	  fi; \
	done;

temp-package-dirs:
	$(mkinstalldirs) $(abs_top_builddir)/CLHEP;
	@list="`cat @PACKAGE@-deps | sed s/CLHEP-@PACKAGE@-@VERSION@// | sed s/CLHEP-// | sed s/-@VERSION@//`"; \
	for pkg in $$list; do \
	  $(mkinstalldirs) $(abs_top_builddir)/CLHEP/$$pkg; \
	done;

docs:
	cd doc; $(MAKE) $(AM_MAKEFLAGS)

install-docs:
	cd doc; $(MAKE) $(AM_MAKEFLAGS) install-docs

# extra clean rule
clean-local:
	rm -rf $(top_builddir)/CLHEP
