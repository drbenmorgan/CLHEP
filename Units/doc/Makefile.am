## Process this file with automake to produce Makefile.in

TEX = latex
doc_srcdir = $(top_srcdir)/doc
doc_builddir = $(top_builddir)/doc
doc_installdir = $(prefix)/doc/@PACKAGE@

DOC_POSTSCRIPT = Units.ps

SUFFIXES = .ps .dvi .tex

.dvi.ps:
	dvips -o $@ $(@:.ps=.dvi)

all: docs

docs: $(DOC_POSTSCRIPT)

install-docs:
	$(mkinstalldirs) $(DESTDIR)$(doc_installdir)
	$(INSTALL_DATA) $(doc_builddir)/Units.ps $(DESTDIR)$(doc_installdir)/Units.ps

# Identify generated file(s) to be removed when 'make clean' is requested:
CLEANFILES = $(DOC_POSTSCRIPT) *.aux *.log *.toc *.dvi
