## Process this file with automake to produce Makefile.in

TEX = latex

SUFFIXES = .ps .dvi .tex

.dvi.ps:
	dvips -o $@ $(@:.ps=.dvi)

all: VectorDefs.ps eulerAngleComputation.ps

install-docs:
	$(mkinstalldirs) $(DESTDIR)$(prefix)/doc/@PACKAGE@
	$(INSTALL_DATA) $(top_builddir)/doc/VectorDefs.ps $(DESTDIR)$(prefix)/doc/@PACKAGE@/VectorDefs.ps
	$(INSTALL_DATA) $(top_builddir)/doc/eulerAngleComputation.ps $(DESTDIR)$(prefix)/doc/@PACKAGE@/eulerAngleComputation.ps
	$(INSTALL_DATA) $(top_srcdir)/doc/keyMergeIssues.doc $(DESTDIR)$(prefix)/doc/@PACKAGE@/keyMergeIssues.doc
	$(INSTALL_DATA) $(top_srcdir)/doc/merge-details.doc $(DESTDIR)$(prefix)/doc/@PACKAGE@/merge-details.doc
	$(INSTALL_DATA) $(top_srcdir)/doc/minorMergeIssues.doc $(DESTDIR)$(prefix)/doc/@PACKAGE@/minorMergeIssues.doc

