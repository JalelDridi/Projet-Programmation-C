## Process this file with automake to produce Makefile.in

INCLUDES = \
	-DPACKAGE_DATA_DIR=\""$(datadir)"\" \
	-DPACKAGE_LOCALE_DIR=\""$(prefix)/$(DATADIRNAME)/locale"\" \
	@PACKAGE_CFLAGS@

bin_PROGRAMS = projetc

projetc_SOURCES = \
	main.c \
	support.c support.h \
	interface.c interface.h \
	callbacks.c callbacks.h \
	election.c election.h   \
	bv.c bv.h               \
	utilisateur.c utilisateur.h \
	reclamation.c reclamation.h \
	list.c listelectoral.h \
	CRUD.c CRUD.h \
	tree.c tree.h

projetc_LDADD = @PACKAGE_LIBS@ $(INTLLIBS)

