## Process this file with automake to produce Makefile.in

#EXTRA_DIST = \
#        pdg_mass.tbl

install-data-local:
	$(mkinstalldirs) $(DESTDIR)$(prefix)/data/HepPDT
	$(INSTALL_DATA) $(srcdir)/pdg_mass.tbl $(DESTDIR)$(prefix)/data/HepPDT/pdg_mass.tbl

