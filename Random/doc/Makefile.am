## Process this file with automake to produce Makefile.in

if USE_GMAKE
  MAKE = gmake
endif

doc_srcdir = $(top_srcdir)/doc
doc_builddir = $(top_builddir)/doc
doc_installdir = $(prefix)/doc/@PACKAGE@

install-docs:
	$(mkinstalldirs) $(DESTDIR)$(doc_installdir)
	$(INSTALL_DATA) $(doc_srcdir)/Random.html $(DESTDIR)$(doc_installdir)/Random.html
	$(INSTALL_DATA) $(doc_srcdir)/validation.doc $(DESTDIR)$(doc_installdir)/validation.doc
	$(INSTALL_DATA) $(doc_srcdir)/html/CLHEP-random.html $(DESTDIR)$(doc_installdir)/CLHEP-random.html

