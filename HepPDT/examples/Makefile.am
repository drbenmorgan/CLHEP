# This makefile is used to copy files during the "make install" step

# files to distribute
EXTRA_DIST = \
    examDMF.cc \
    examListHerwig.cc \
    examListHerwigInterface.F \
    examListHerwig.out.save \
    examListIsajet.cc \
    examListIsajetInterface.F \
    examListIsajet.out.save \
    examListPythia.cc \
    examListPythiaInterface.F \
    examListPythia.out.save \
    examListPythia.lpt.save \
    examMyPDT.cc \
    examMyPDT.out.save \
    examReadEvtGen.cc \
    examReadEvtGen.out.save \
    examReadPDG.cc \
    examReadPDG.out.save \
    examReadPythia.cc \
    examReadPythia.out.save \
    examReadQQ.cc \
    examReadQQ.out.save \
    ModeA.cpp \
    ModeA.hh \
    ModeAT.hh \
    ModeB.cpp \
    ModeB.hh

install-data-local:
	$(mkinstalldirs) $(DESTDIR)$(prefix)/examples/@PACKAGE@
	$(INSTALL_DATA) GNUmakefile.example $(DESTDIR)$(prefix)/examples/@PACKAGE@/GNUmakefile
	$(INSTALL_DATA) examReadPDG.cc $(DESTDIR)$(prefix)/examples/@PACKAGE@/examReadPDG.cc
	for file in $(EXTRA_DIST); do \
	  $(INSTALL_DATA) $(srcdir)/$$file $(DESTDIR)$(prefix)/examples/@PACKAGE@/$$file; done
