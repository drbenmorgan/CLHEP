# This makefile is used to copy files during the "make install" step

# files to distribute
EXTRA_DIST = \
    example_EventSelection.cc \
    example_MyHerwig.cc \
    example_MyPythia.cc \
    example_MyPythiaOnlyToHepMC.cc \
    example_MyPythiaWithEventSelection.cc \
    examplePythiaWriteHepMC.cc \
    exampleReadHepMC.cc \
    example_UsingIterators.cc \
    initpydata.F \
    IO_Ascii.cc \
    IO_Ascii.h \
    pythia.tbl \
    RunAllExamples.job \
    test_MakeUsingIteratorsInput.cc \
    testMethods.cc 

install-data-local:
	$(mkinstalldirs) $(DESTDIR)$(prefix)/examples/@PACKAGE@
	$(INSTALL_DATA) GNUmakefile.example $(DESTDIR)$(prefix)/examples/@PACKAGE@/GNUmakefile
	for file in $(EXTRA_DIST); do \
	  $(INSTALL_DATA) $(srcdir)/$$file $(DESTDIR)$(prefix)/examples/@PACKAGE@/$$file; done
