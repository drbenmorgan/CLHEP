## Process this file with automake to produce Makefile.in

TEX = latex
doc_srcdir = $(top_srcdir)/doc
doc_builddir = $(top_builddir)/doc
doc_installdir = $(prefix)/doc/@PACKAGE@

DOC_POSTSCRIPT = genericFunctions.ps
DOC_INCLUDES = example.ps \
               hydrogen.ps \
	       PartiallyClosed.ps \
	       TotallyClosed.ps \
	       WideOpen.ps

SUFFIXES = .ps .dvi .tex

.dvi.ps:
	dvips -o $@ $(@:.ps=.dvi)

all: docs

docs: get-includes $(DOC_POSTSCRIPT)

get-includes:
	list='$(DOC_INCLUDES)'; for file in $$list; do \
	  if test ! -f $$file; then  \
	  (cp $(srcdir)/$$file $(doc_builddir)/$$file); fi; done

install-docs:
	$(mkinstalldirs) $(DESTDIR)$(doc_installdir)
	$(INSTALL_DATA) $(doc_builddir)/genericFunctions.ps $(DESTDIR)$(doc_installdir)/genericFunctions.ps


# Identify generated file(s) to be removed when 'make clean' is requested:
CLEANFILES = $(DOC_POSTSCRIPT) $(DOC_INCLUDES) *.aux *.log *.toc *.dvi
