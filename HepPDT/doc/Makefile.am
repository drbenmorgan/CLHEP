## Process this file with automake to produce Makefile.in

TEX = latex

SUFFIXES = .ps .dvi .tex

.dvi.ps:
	dvips -o $@ $(@:.ps=.dvi)

all: get-includes HepPDT.ps ParticleIDapp.ps

get-includes:
	cp $(srcdir)/*.eps .

install-docs:
	$(mkinstalldirs) $(DESTDIR)$(prefix)/doc/@PACKAGE@
	$(INSTALL_DATA) $(top_builddir)/doc/HepPDT.ps $(DESTDIR)$(prefix)/doc/@PACKAGE@/HepPDT.ps
	$(INSTALL_DATA) $(top_builddir)/doc/ParticleIDapp.ps $(DESTDIR)$(prefix)/doc/@PACKAGE@/ParticleIDapp.ps
	$(INSTALL_DATA) $(top_builddir)/doc/PDT_DesignSpecialIssues.txt $(DESTDIR)$(prefix)/doc/@PACKAGE@/PDT_DesignSpecialIssues.txt
	$(INSTALL_DATA) $(top_builddir)/doc/PDT_DesignSummary.txt $(DESTDIR)$(prefix)/doc/@PACKAGE@/PDT_DesignSummary.txt
	$(INSTALL_DATA) $(top_builddir)/doc/PDT_TemplateDecision.txt $(DESTDIR)$(prefix)/doc/@PACKAGE@/PDT_TemplateDecision.txt

