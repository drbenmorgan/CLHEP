## Process this file with automake to produce Makefile.in

if USE_GMAKE
  MAKE = gmake
endif

TEX = latex
doc_srcdir = $(top_srcdir)/doc
doc_builddir = $(top_builddir)/doc
doc_installdir = $(prefix)/doc/@PACKAGE@

DOC_POSTSCRIPT = VectorDefs.ps eulerAngleComputation.ps \
                 VectorDefs.pdf eulerAngleComputation.pdf

SUFFIXES = .dvi .tex .ps .pdf

.dvi.ps:
	dvips -o $@ $(@:.ps=.dvi)

.dvi.pdf:
	dvipdf $(@:.pdf=.dvi)

all: docs

docs: $(DOC_POSTSCRIPT)

install-docs:
	$(mkinstalldirs) $(DESTDIR)$(doc_installdir)
	$(INSTALL_DATA) $(doc_builddir)/VectorDefs.ps $(DESTDIR)$(doc_installdir)/VectorDefs.ps
	$(INSTALL_DATA) $(doc_builddir)/eulerAngleComputation.ps $(DESTDIR)$(doc_installdir)/eulerAngleComputation.ps
	$(INSTALL_DATA) $(doc_builddir)/VectorDefs.pdf $(DESTDIR)$(doc_installdir)/VectorDefs.pdf
	$(INSTALL_DATA) $(doc_builddir)/eulerAngleComputation.pdf $(DESTDIR)$(doc_installdir)/eulerAngleComputation.pdf
	$(INSTALL_DATA) $(doc_srcdir)/keyMergeIssues.doc $(DESTDIR)$(doc_installdir)/keyMergeIssues.doc
	$(INSTALL_DATA) $(doc_srcdir)/merge-details.doc $(DESTDIR)$(doc_installdir)/merge-details.doc
	$(INSTALL_DATA) $(doc_srcdir)/minorMergeIssues.doc $(DESTDIR)$(doc_installdir)/minorMergeIssues.doc


# Identify generated file(s) to be removed when 'make clean' is requested:
CLEANFILES = $(DOC_POSTSCRIPT) *.aux *.log *.toc *.dvi
