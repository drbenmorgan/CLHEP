## Process this file with automake to produce Makefile.in

if USE_GMAKE
  MAKE = gmake
endif

TEX = latex
doc_srcdir = $(top_srcdir)/doc
doc_builddir = $(top_builddir)/doc
doc_installdir = $(prefix)/doc/@PACKAGE@

DOC_POSTSCRIPT = genericFunctions.ps genericFunctions.pdf
DOC_INCLUDES = example.ps \
               hydrogen.ps \
	       PartiallyClosed.ps \
	       TotallyClosed.ps \
	       WideOpen.ps \
	       psfig.sty

SUFFIXES = .ps .pdf .dvi .tex

.dvi.ps:
	dvips -o $@ $(@:.ps=.dvi)

.dvi.pdf:
	dvipdf $(@:.pdf=.dvi)

all: docs

docs: get-includes $(DOC_POSTSCRIPT)

get-includes:
	list='$(DOC_INCLUDES)'; for file in $$list; do \
	  if test ! -f $$file; then  \
	  (cp $(srcdir)/$$file $(doc_builddir)/$$file); fi; done

install-docs:
	$(mkinstalldirs) $(DESTDIR)$(doc_installdir)
	$(INSTALL_DATA) $(doc_builddir)/genericFunctions.ps $(DESTDIR)$(doc_installdir)/genericFunctions.ps
	$(INSTALL_DATA) $(doc_builddir)/genericFunctions.pdf $(DESTDIR)$(doc_installdir)/genericFunctions.pdf


# Identify generated file(s) to be removed when 'make clean' is requested:
CLEANFILES = $(DOC_POSTSCRIPT) $(DOC_INCLUDES) *.aux *.log *.toc *.dvi
