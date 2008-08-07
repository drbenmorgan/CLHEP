## Process this file with automake to produce Makefile.in

if USE_GMAKE
  MAKE = gmake
endif

TEX = latex
doc_srcdir = $(top_srcdir)/doc
doc_builddir = $(top_builddir)/doc
doc_installdir = $(prefix)/doc/@PACKAGE@

install-docs:
	$(mkinstalldirs) $(DESTDIR)$(doc_installdir)
	$(INSTALL_DATA) $(doc_srcdir)/HepTuple-exceptions $(DESTDIR)$(doc_installdir)/HepTuple-exceptions
	$(INSTALL_DATA) $(doc_srcdir)/ZMthrow_event_sequence.txt $(DESTDIR)$(doc_installdir)/ZMthrow_event_sequence.txt
	$(INSTALL_DATA) $(doc_srcdir)/ex-design-1 $(DESTDIR)$(doc_installdir)/ex-design-1
	$(INSTALL_DATA) $(doc_srcdir)/ex-design-2 $(DESTDIR)$(doc_installdir)/ex-design-2
	$(INSTALL_DATA) $(doc_srcdir)/ex-design-3 $(DESTDIR)$(doc_installdir)/ex-design-3
	$(INSTALL_DATA) $(doc_srcdir)/ex-design-5 $(DESTDIR)$(doc_installdir)/ex-design-5
	$(INSTALL_DATA) $(doc_srcdir)/ex-design-6 $(DESTDIR)$(doc_installdir)/ex-design-6
	$(INSTALL_DATA) $(doc_srcdir)/how-ZMxTop-is-setup $(DESTDIR)$(doc_installdir)/how-ZMxTop-is-setup
	$(INSTALL_DATA) $(doc_srcdir)/m-pcanal-1 $(DESTDIR)$(doc_installdir)/m-pcanal-1
	$(INSTALL_DATA) $(doc_srcdir)/m-pcanal-2 $(DESTDIR)$(doc_installdir)/m-pcanal-2
	$(INSTALL_DATA) $(doc_srcdir)/m-pcanal-3 $(DESTDIR)$(doc_installdir)/m-pcanal-3
	$(INSTALL_DATA) $(doc_srcdir)/mechanics_ZMx.txt $(DESTDIR)$(doc_installdir)/mechanics_ZMx.txt
	$(INSTALL_DATA) $(doc_srcdir)/reply-pcanal-1 $(DESTDIR)$(doc_installdir)/reply-pcanal-1
	$(INSTALL_DATA) $(doc_srcdir)/reply-pcanal-2 $(DESTDIR)$(doc_installdir)/reply-pcanal-2
	$(INSTALL_DATA) $(doc_srcdir)/whyZMthrowRethrows.txt $(DESTDIR)$(doc_installdir)/whyZMthrowRethrows.txt


# Identify generated file(s) to be removed when 'make clean' is requested:
#CLEANFILES = *.aux *.log *.toc *.dvi
