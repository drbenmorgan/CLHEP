## Process this file with automake to produce Makefile.in

##  WARNING - this is not yet working - tex is invoked instead of latex

SUFFIXES = .ps .dvi .tex

$(srcdir)/%.tex: %.dvi
	latex -o $@ $<

.dvi.ps:
	dvips -o $@ $(@:.ps=.dvi)

all: Units.ps

install-data-local:
	$(mkinstalldirs) $(DESTDIR)$(datadir)
	$(INSTALL_DATA) $(top_builddir)/doc/Units.ps $(DESTDIR)$(datadir)/Units.ps

