## Process this file with automake to produce Makefile.in

includedir = $(prefix)/include/CLHEP
tempincludedir = $(TEMPDIR)/CLHEP/@PACKAGE@
COPY_P = @COPY_P@

pkginclude_HEADERS = \
	DiagMatrix.h	\
	DiagMatrix.icc	\
	GenMatrix.h	\
	GenMatrix.icc	\
	Matrix.h	\
	Matrix.icc	\
	Pile.h		\
	SymMatrix.h	\
	SymMatrix.icc	\
	Vector.h	\
	Vector.icc	\
	defs.h

# Identify generated file(s) to be removed when 'make clean' is requested:
CLEANFILES = defs.h

# copy headers into $(tempincludedir)
install-tmpHEADERS:
	@echo " install headers in $(TEMPDIR)/CLHEP "
	@list='$(pkginclude_HEADERS)'; \
	if test $(TEMPDIR); then \
	  for p in $$list; do \
	    if test -f "$$p"; then d=; else d="$(srcdir)/"; fi; \
	    f="`echo $$p | sed -e 's|^.*/||'`"; \
	    echo " $(COPY_P) $$d$$p $(tempincludedir)/$$f"; \
	    $(COPY_P) $$d$$p $(tempincludedir)/$$f; \
	  done; \
	fi; test -z "$$fail"
