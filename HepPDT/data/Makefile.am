## Process this file with automake to produce Makefile.in

PDG_TABLES = PDG_mass_width_1998.mc \
	     PDG_mass_width_1998_withSusy.mc \
	     PDG_mass_width_2000.mc \
	     PDG_mass_width_2001.mc \
	     PDG_mass_width_2002.mc

EXTRA_DIST = $(PDG_TABLES)
      

install-data-local:
	$(mkinstalldirs) $(DESTDIR)$(prefix)/data/HepPDT
	for file in $(PDG_TABLES); do \
	  $(INSTALL_DATA) $(srcdir)/$$file $(DESTDIR)$(prefix)/data/HepPDT/$$file; done

