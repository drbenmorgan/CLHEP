## Process this file with automake to produce Makefile.in

if USE_GMAKE
  MAKE = gmake
endif

includedir = $(prefix)/include/CLHEP
pkgincludedir = $(prefix)/include/CLHEP/@PACKAGE@

install-data-local:
	$(mkinstalldirs) $(DESTDIR)$(pkgincludedir)/include
	$(INSTALL_DATA) $(srcdir)/HerwigWrapper.h $(DESTDIR)$(pkgincludedir)/include/HerwigWrapper.h
	$(INSTALL_DATA) $(srcdir)/HerwigWrapper6_4.h $(DESTDIR)$(pkgincludedir)/include/HerwigWrapper6_4.h
	$(INSTALL_DATA) $(srcdir)/PythiaWrapper.h $(DESTDIR)$(pkgincludedir)/include/PythiaWrapper.h
	$(INSTALL_DATA) $(srcdir)/PythiaWrapper5_720.h $(DESTDIR)$(pkgincludedir)/include/PythiaWrapper5_720.h
	$(INSTALL_DATA) $(srcdir)/PythiaWrapper6_152.h $(DESTDIR)$(pkgincludedir)/include/PythiaWrapper6_152.h
	$(INSTALL_DATA) $(srcdir)/PythiaWrapper6_152_WIN32.h $(DESTDIR)$(pkgincludedir)/include/PythiaWrapper6_152_WIN32.h
	$(INSTALL_DATA) $(srcdir)/PythiaWrapper6_2.h $(DESTDIR)$(pkgincludedir)/include/PythiaWrapper6_2.h
	$(INSTALL_DATA) $(srcdir)/PythiaWrapper6_2_WIN32.h $(DESTDIR)$(pkgincludedir)/include/PythiaWrapper6_2_WIN32.h
	$(INSTALL_DATA) $(srcdir)/hepev4.h $(DESTDIR)$(pkgincludedir)/include/hepev4.h
	$(INSTALL_DATA) $(srcdir)/hepev4.inc $(DESTDIR)$(pkgincludedir)/include/hepev4.inc
	$(INSTALL_DATA) $(srcdir)/stdhep.h $(DESTDIR)$(pkgincludedir)/include/stdhep.h
	$(INSTALL_DATA) $(srcdir)/stdhep.inc $(DESTDIR)$(pkgincludedir)/include/stdhep.inc
