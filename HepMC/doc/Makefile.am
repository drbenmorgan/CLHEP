## Process this file with automake to produce Makefile.in

TEX = latex
doc_srcdir = $(top_srcdir)/doc/latex_user_manual
doc_builddir = $(top_builddir)/doc
doc_installdir = $(prefix)/doc/@PACKAGE@

DOC_POSTSCRIPT = HepMC_user_manual.ps
DOC_SOURCE = $(doc_srcdir)/HepMC_user_manual.tex
DOC_INCLUDES = graph_interpretation.eps \
	       physicist_visualization.eps \
               HepMC_UML.eps \
	       html.sty

SUFFIXES = .ps .tex

all-local: docs

install-data-local: install-docs

docs: $(DOC_POSTSCRIPT)

$(DOC_POSTSCRIPT): $(DOC_SOURCE)
	list='$(DOC_INCLUDES)'; for file in $$list; do \
	  if test ! -f $$file; then  \
	  (cp $(doc_srcdir)/$$file $(doc_builddir)/$$file); fi; done
	$(TEX)	$(DOC_SOURCE)
	dvips -o HepMC_user_manual.dvi

install-docs: $(DOC_POSTSCRIPT)
	$(mkinstalldirs) $(DESTDIR)$(doc_installdir)
	$(INSTALL_DATA) $(doc_builddir)/HepMC_user_manual.ps $(DESTDIR)$(doc_installdir)/HepMC_user_manual.ps

# Identify generated file(s) to be removed when 'make clean' is requested:
CLEANFILES = $(DOC_POSTSCRIPT) $(DOC_INCLUDES) *.aux *.log *.toc *.dvi
