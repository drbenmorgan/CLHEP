## Process this file with automake to produce Makefile.in

TEX = latex

SUFFIXES = .ps .dvi .tex

.dvi.ps:
	dvips -o $@ $(@:.ps=.dvi)

all: get-includes genericFunctions.ps

get-includes:
	cp $(srcdir)/*.ps .

install-docs:
	$(mkinstalldirs) $(DESTDIR)$(prefix)/doc/@PACKAGE@
	$(INSTALL_DATA) $(top_builddir)/doc/genericFunctions.ps $(DESTDIR)$(prefix)/doc/@PACKAGE@/genericFunctions.ps

