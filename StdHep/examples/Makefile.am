# This makefile is used to copy files during the "make install" step

# files to distribute
EXTRA_DIST = \
    analyzeEvent.cc \
    analyzeEvent.hh \
    bookhist.F \
    dummy.F \
    examHerwigToStdHep.cc \
    examPythiaToStdHep.cc \
    hwghep.F \
    hwtran.F \
    lunhep.F \
    lutran.F \
    readcxx.F \
    readPythia.cc \
    readPythiaHerwig.cc \
    stdflhwxsec.F \
    stdflpyxsec.F \
    stdhwgcxx.F \
    stdpytcxx.F

install-data-local:
	$(mkinstalldirs) $(DESTDIR)$(prefix)/examples/@PACKAGE@
	$(INSTALL_DATA) GNUmakefile.example $(DESTDIR)$(prefix)/examples/@PACKAGE@/GNUmakefile
	for file in $(EXTRA_DIST); do \
	  $(INSTALL_DATA) $(srcdir)/$$file $(DESTDIR)$(prefix)/examples/@PACKAGE@/$$file; done
