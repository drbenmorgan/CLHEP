# This makefile is used to copy files during the "make install" step

if USE_GMAKE
  MAKE = gmake
endif

# files to distribute
EXTRA_DIST = \
    decay.dec \
    DECAY.EvtGen.DEC \
    evt.pdl \
    pdt.table \
    pythia.tbl

install-data-local:
	$(mkinstalldirs) $(DESTDIR)$(prefix)/examples/@PACKAGE@/data
	for file in $(EXTRA_DIST); do \
	  $(INSTALL_DATA) $(srcdir)/$$file $(DESTDIR)$(prefix)/examples/@PACKAGE@/data/$$file; done
