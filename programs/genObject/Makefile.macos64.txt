# Generated file - Edits will be discarded by next generation!
# (11/21/2021 16:19:14.000)

.DEFAULT_GOAL := all
SHELL=/bin/sh

PGMNAM=genObject
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






#------------------------------------------------
#         Compile Objects and Routines
#------------------------------------------------


OBJS += $(OBJDIR)/Dict.o

$(OBJDIR)/Dict.o: $(SRCDIR)/Dict.c $(SRCDIR)/Dict.h $(SRCDIR)/Dict_internal.h $(SRCDIR)/genObject_defs.h $(LIBCMN_BASE)/include/cmn_defs.h 
	$(CC) $(CFLAGS) -c -o $(OBJDIR)/$(@F) -I$(SRCDIR) $<

OBJS += $(OBJDIR)/Dict_object.o

$(OBJDIR)/Dict_object.o: $(SRCDIR)/Dict_object.c $(SRCDIR)/Dict.h $(SRCDIR)/Dict_internal.h $(SRCDIR)/genObject_defs.h $(LIBCMN_BASE)/include/cmn_defs.h 
	$(CC) $(CFLAGS) -c -o $(OBJDIR)/$(@F) -I$(SRCDIR) $<

OBJS += $(OBJDIR)/Gen.o

$(OBJDIR)/Gen.o: $(SRCDIR)/Gen.c $(SRCDIR)/Gen.h $(SRCDIR)/Gen_internal.h $(SRCDIR)/genObject_defs.h $(LIBCMN_BASE)/include/cmn_defs.h 
	$(CC) $(CFLAGS) -c -o $(OBJDIR)/$(@F) -I$(SRCDIR) $<

OBJS += $(OBJDIR)/GenItem.o

$(OBJDIR)/GenItem.o: $(SRCDIR)/GenItem.c $(SRCDIR)/GenItem.h $(SRCDIR)/GenItem_internal.h $(SRCDIR)/genObject_defs.h $(LIBCMN_BASE)/include/cmn_defs.h 
	$(CC) $(CFLAGS) -c -o $(OBJDIR)/$(@F) -I$(SRCDIR) $<

OBJS += $(OBJDIR)/GenItem_object.o

$(OBJDIR)/GenItem_object.o: $(SRCDIR)/GenItem_object.c $(SRCDIR)/GenItem.h $(SRCDIR)/GenItem_internal.h $(SRCDIR)/genObject_defs.h $(LIBCMN_BASE)/include/cmn_defs.h 
	$(CC) $(CFLAGS) -c -o $(OBJDIR)/$(@F) -I$(SRCDIR) $<

OBJS += $(OBJDIR)/Gen_object.o

$(OBJDIR)/Gen_object.o: $(SRCDIR)/Gen_object.c $(SRCDIR)/Gen.h $(SRCDIR)/Gen_internal.h $(SRCDIR)/genObject_defs.h $(LIBCMN_BASE)/include/cmn_defs.h 
	$(CC) $(CFLAGS) -c -o $(OBJDIR)/$(@F) -I$(SRCDIR) $<

OBJS += $(OBJDIR)/Main.o

$(OBJDIR)/Main.o: $(SRCDIR)/Main.c $(SRCDIR)/Main.h $(SRCDIR)/Main_internal.h $(SRCDIR)/genObject_defs.h $(LIBCMN_BASE)/include/cmn_defs.h 
	$(CC) $(CFLAGS) -c -o $(OBJDIR)/$(@F) -I$(SRCDIR) $<

OBJS += $(OBJDIR)/Main_object.o

$(OBJDIR)/Main_object.o: $(SRCDIR)/Main_object.c $(SRCDIR)/Main.h $(SRCDIR)/Main_internal.h $(SRCDIR)/genObject_defs.h $(LIBCMN_BASE)/include/cmn_defs.h 
	$(CC) $(CFLAGS) -c -o $(OBJDIR)/$(@F) -I$(SRCDIR) $<

OBJS += $(OBJDIR)/NodeClass.o

$(OBJDIR)/NodeClass.o: $(SRCDIR)/NodeClass.c $(SRCDIR)/NodeClass.h $(SRCDIR)/NodeClass_internal.h $(SRCDIR)/genObject_defs.h $(LIBCMN_BASE)/include/cmn_defs.h 
	$(CC) $(CFLAGS) -c -o $(OBJDIR)/$(@F) -I$(SRCDIR) $<

OBJS += $(OBJDIR)/NodeClass_json.o

$(OBJDIR)/NodeClass_json.o: $(SRCDIR)/NodeClass_json.c $(SRCDIR)/NodeClass.h $(SRCDIR)/NodeClass_internal.h $(SRCDIR)/genObject_defs.h $(LIBCMN_BASE)/include/cmn_defs.h 
	$(CC) $(CFLAGS) -c -o $(OBJDIR)/$(@F) -I$(SRCDIR) $<

OBJS += $(OBJDIR)/NodeClass_object.o

$(OBJDIR)/NodeClass_object.o: $(SRCDIR)/NodeClass_object.c $(SRCDIR)/NodeClass.h $(SRCDIR)/NodeClass_internal.h $(SRCDIR)/genObject_defs.h $(LIBCMN_BASE)/include/cmn_defs.h 
	$(CC) $(CFLAGS) -c -o $(OBJDIR)/$(@F) -I$(SRCDIR) $<

OBJS += $(OBJDIR)/NodeProp.o

$(OBJDIR)/NodeProp.o: $(SRCDIR)/NodeProp.c $(SRCDIR)/NodeProp.h $(SRCDIR)/NodeProp_internal.h $(SRCDIR)/genObject_defs.h $(LIBCMN_BASE)/include/cmn_defs.h 
	$(CC) $(CFLAGS) -c -o $(OBJDIR)/$(@F) -I$(SRCDIR) $<

OBJS += $(OBJDIR)/NodeProp_json.o

$(OBJDIR)/NodeProp_json.o: $(SRCDIR)/NodeProp_json.c $(SRCDIR)/NodeProp.h $(SRCDIR)/NodeProp_internal.h $(SRCDIR)/genObject_defs.h $(LIBCMN_BASE)/include/cmn_defs.h 
	$(CC) $(CFLAGS) -c -o $(OBJDIR)/$(@F) -I$(SRCDIR) $<

OBJS += $(OBJDIR)/NodeProp_object.o

$(OBJDIR)/NodeProp_object.o: $(SRCDIR)/NodeProp_object.c $(SRCDIR)/NodeProp.h $(SRCDIR)/NodeProp_internal.h $(SRCDIR)/genObject_defs.h $(LIBCMN_BASE)/include/cmn_defs.h 
	$(CC) $(CFLAGS) -c -o $(OBJDIR)/$(@F) -I$(SRCDIR) $<





#------------------------------------------------
#      Compile and execute Tests
#------------------------------------------------


TESTS += Dict_test

Dict_test: $(TEST_SRC)/Dict_test.c $(SRCDIR)/Dict.h $(SRCDIR)/Dict_internal.h $(SRCDIR)/genObject_defs.h $(LIBCMN_BASE)/include/cmn_defs.h 
	$(CC) $(CFLAGS) $(CFLAGS_TEST) -o $(TEST_BIN)/$(@F) $(OBJS) -I$(TEST_SRC) -I$(SRCDIR) $<
	$(TEST_BIN)/$(@F) --no_int3

TESTS += GenItem_test

GenItem_test: $(TEST_SRC)/GenItem_test.c $(SRCDIR)/GenItem.h $(SRCDIR)/GenItem_internal.h $(SRCDIR)/genObject_defs.h $(LIBCMN_BASE)/include/cmn_defs.h 
	$(CC) $(CFLAGS) $(CFLAGS_TEST) -o $(TEST_BIN)/$(@F) $(OBJS) -I$(TEST_SRC) -I$(SRCDIR) $<
	$(TEST_BIN)/$(@F) --no_int3

TESTS += Gen_test

Gen_test: $(TEST_SRC)/Gen_test.c $(SRCDIR)/Gen.h $(SRCDIR)/Gen_internal.h $(SRCDIR)/genObject_defs.h $(LIBCMN_BASE)/include/cmn_defs.h 
	$(CC) $(CFLAGS) $(CFLAGS_TEST) -o $(TEST_BIN)/$(@F) $(OBJS) -I$(TEST_SRC) -I$(SRCDIR) $<
	$(TEST_BIN)/$(@F) --no_int3

TESTS += Main_test

Main_test: $(TEST_SRC)/Main_test.c $(SRCDIR)/Main.h $(SRCDIR)/Main_internal.h $(SRCDIR)/genObject_defs.h $(LIBCMN_BASE)/include/cmn_defs.h 
	$(CC) $(CFLAGS) $(CFLAGS_TEST) -o $(TEST_BIN)/$(@F) $(OBJS) -I$(TEST_SRC) -I$(SRCDIR) $<
	$(TEST_BIN)/$(@F) --no_int3

TESTS += NodeClass_test

NodeClass_test: $(TEST_SRC)/NodeClass_test.c $(SRCDIR)/NodeClass.h $(SRCDIR)/NodeClass_internal.h $(SRCDIR)/genObject_defs.h $(LIBCMN_BASE)/include/cmn_defs.h 
	$(CC) $(CFLAGS) $(CFLAGS_TEST) -o $(TEST_BIN)/$(@F) $(OBJS) -I$(TEST_SRC) -I$(SRCDIR) $<
	$(TEST_BIN)/$(@F) --no_int3

TESTS += NodeProp_test

NodeProp_test: $(TEST_SRC)/NodeProp_test.c $(SRCDIR)/NodeProp.h $(SRCDIR)/NodeProp_internal.h $(SRCDIR)/genObject_defs.h $(LIBCMN_BASE)/include/cmn_defs.h 
	$(CC) $(CFLAGS) $(CFLAGS_TEST) -o $(TEST_BIN)/$(@F) $(OBJS) -I$(TEST_SRC) -I$(SRCDIR) $<
	$(TEST_BIN)/$(@F) --no_int3





#------------------------------------------------
#              Phony Targets
#------------------------------------------------


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


