# Generated file - Edits will be discarded by next generation!
# (12/ 7/2020  5:08:16.000)

.DEFAULT_GOAL := all
SHELL=/bin/sh

PGMNAM=fileClean
SYS=macos64
TEMP=/tmp
BASE_OBJ = $(TEMP)/$(PGMNAM)
SRCDIR = ./src
TEST_SRC = ./tests
INSTALL_BASE = $(HOME)/Support/bin
LIB_BASE = $(HOME)/Support/lib/$(SYS)

CFLAGS += -g -Werror -I$(SRCDIR)
ifdef  NDEBUG
CFLAGS += -DNDEBUG
else   #DEBUG
CFLAGS += -D_DEBUG
endif  #NDEBUG
CFLAGS += -D__MACOS64_ENV__
CFLAGS_LIBS = 
# libCmn
LIBCMN_BASE = $(LIB_BASE)/libCmn
CFLAGS += -I$(LIBCMN_BASE)/include
CFLAGS_LIBS += -lCmn -L$(LIBCMN_BASE)
CFLAGS_TEST = -I$(TEST_SRC) $(CFLAGS_LIBS) -lcurses -lsqlite3

LIBOBJ = $(BASE_OBJ)/$(SYS)
ifdef  NDEBUG
LIB_FILENAME=$(PGMNAM)R.a
OBJDIR = $(LIBOBJ)/o/r
else   #DEBUG
LIB_FILENAME=$(PGMNAM)D.a
OBJDIR = $(LIBOBJ)/o/d
endif  #NDEBUG
TEST_OBJ = $(OBJDIR)/obj
TEST_BIN = $(OBJDIR)/bin
LIB_PATH = $(LIBOBJ)/$(LIB_FILENAME)

.SUFFIXES:
.SUFFIXES: .asm .c .cpp .o

OBJS =

TESTS =


OBJS += $(OBJDIR)/Main.o

$(OBJDIR)/Main.o: $(SRCDIR)/Main.c $(SRCDIR)/Main.h $(SRCDIR)/Main_internal.h $(SRCDIR)/fileClean_defs.h $(LIBCMN_BASE)/include/cmn_defs.h 
	$(CC) $(CFLAGS) -c -o $(OBJDIR)/$(@F) -I$(SRCDIR) $<

OBJS += $(OBJDIR)/Main_object.o

$(OBJDIR)/Main_object.o: $(SRCDIR)/Main_object.c $(SRCDIR)/Main.h $(SRCDIR)/Main_internal.h $(SRCDIR)/fileClean_defs.h $(LIBCMN_BASE)/include/cmn_defs.h 
	$(CC) $(CFLAGS) -c -o $(OBJDIR)/$(@F) -I$(SRCDIR) $<

TESTS += Main_test

Main_test: $(TEST_SRC)/Main_test.c $(SRCDIR)/Main.h $(SRCDIR)/Main_internal.h $(SRCDIR)/fileClean_defs.h $(LIBCMN_BASE)/include/cmn_defs.h 
	$(CC) $(CFLAGS) $(CFLAGS_TEST) -o $(TEST_BIN)/$(@F) $(OBJS) -I$(TEST_SRC) -I$(SRCDIR) $<
	$(TEST_BIN)/$(@F)

.PHONY: all
all:  clean create_dirs link


.PHONY: build
build:  create_dirs link


.PHONY: check
check: $(TESTS)


.PHONY: clean
clean:
	-cd $(TEMP) ; [ -d $(PGMNAM) ] && rm -fr $(PGMNAM)


.PHONY: create_dirs
create_dirs:
	[ ! -d $(TEST_OBJ) ] && mkdir -p $(TEST_OBJ)
	[ ! -d $(TEST_BIN) ] && mkdir -p $(TEST_BIN)


.PHONY: install
install:
	-cd $(INSTALL_BASE) ; [ -d $(PGMNAM) ] && rm -fr $(PGMNAM)
	cp $(OBJDIR)/$(PGMNAM) $(INSTALL_BASE)/$(PGMNAM)


.PHONY: link
link: $(OBJS) $(SRCDIR)/mainProgram.c
	CC -o $(OBJDIR)/$(PGMNAM) $(CFLAGS) $(CFLAGS_LIBS) $^


.PHONY: test
test: $(TESTS)


