## Process this file with automake to produce Makefile.in

TEX = latex

SUFFIXES = .ps .dvi .tex

.dvi.ps:
	dvips -o $@ $(@:.ps=.dvi)

all: Units.ps

install-docs:
	$(mkinstalldirs) $(DESTDIR)$(prefix)/doc/@PACKAGE@
	$(INSTALL_DATA) $(top_builddir)/doc/Units.ps $(DESTDIR)$(prefix)/doc/@PACKAGE@/Units.ps

