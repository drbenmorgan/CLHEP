## Process this file with automake to produce Makefile.in

TEX = latex
doc_srcdir = $(top_srcdir)/doc
doc_builddir = $(top_builddir)/doc
doc_installdir = $(prefix)/doc/@PACKAGE@

DOC_POSTSCRIPT = HepPDT.ps ParticleIDapp.ps
DOC_INCLUDES = HepPDT-class.eps \
               intro.tex \
	       body.tex \
	       refer.tex \
	       readdata.tex \
	       elem.tex \
	       meson.tex \
	       baryon.tex

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
	$(INSTALL_DATA) $(doc_builddir)/HepPDT.ps $(DESTDIR)$(doc_installdir)/HepPDT.ps
	$(INSTALL_DATA) $(doc_builddir)/ParticleIDapp.ps $(DESTDIR)$(doc_installdir)/ParticleIDapp.ps
	$(INSTALL_DATA) $(doc_srcdir)/PDT_DesignSpecialIssues.txt $(DESTDIR)$(doc_installdir)/PDT_DesignSpecialIssues.txt
	$(INSTALL_DATA) $(doc_srcdir)/PDT_DesignSummary.txt $(DESTDIR)$(doc_installdir)/PDT_DesignSummary.txt
	$(INSTALL_DATA) $(doc_srcdir)/PDT_TemplateDecision.txt $(DESTDIR)$(doc_installdir)/PDT_TemplateDecision.txt

# Identify generated file(s) to be removed when 'make clean' is requested:
CLEANFILES = $(DOC_POSTSCRIPT) $(DOC_INCLUDES) *.aux *.log *.toc *.dvi

