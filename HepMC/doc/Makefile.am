## Process this file with automake to produce Makefile.in

doc_srcdir = $(top_srcdir)/doc
doc_builddir = $(top_builddir)/doc
doc_installdir = $(prefix)/doc/@PACKAGE@

install-docs:
	$(mkinstalldirs) $(DESTDIR)$(doc_installdir)
	$(INSTALL_DATA) $(doc_srcdir)/HepMC_user_manual.ps $(DESTDIR)$(doc_installdir)/HepMC_user_manual.ps

