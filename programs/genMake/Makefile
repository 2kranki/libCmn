# Generated file - Edits will be discarded by next generation!
# ( 1/13/2022 18:58:52.000)

.DEFAULT_GOAL := all
SHELL=/bin/sh

PGMNAM=genMake
SYS=macos64
BUILD=./.build
BASE_OBJ = $(BUILD)/$(PGMNAM)
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

$(OBJDIR)/Dict.o: $(SRCDIR)/Dict.c $(SRCDIR)/Dict.h $(SRCDIR)/Dict_internal.h $(SRCDIR)/genMake.h $(LIBCMN_BASE)/include/cmn_defs.h 
	$(CC) $(CFLAGS) -c -o $(OBJDIR)/$(@F) -I$(SRCDIR) $<

OBJS += $(OBJDIR)/Dict_object.o

$(OBJDIR)/Dict_object.o: $(SRCDIR)/Dict_object.c $(SRCDIR)/Dict.h $(SRCDIR)/Dict_internal.h $(SRCDIR)/genMake.h $(LIBCMN_BASE)/include/cmn_defs.h 
	$(CC) $(CFLAGS) -c -o $(OBJDIR)/$(@F) -I$(SRCDIR) $<

OBJS += $(OBJDIR)/ExpandNodes.o

$(OBJDIR)/ExpandNodes.o: $(SRCDIR)/ExpandNodes.c $(SRCDIR)/ExpandNodes.h $(SRCDIR)/ExpandNodes_internal.h $(SRCDIR)/genMake.h $(LIBCMN_BASE)/include/cmn_defs.h 
	$(CC) $(CFLAGS) -c -o $(OBJDIR)/$(@F) -I$(SRCDIR) $<

OBJS += $(OBJDIR)/ExpandNodes_object.o

$(OBJDIR)/ExpandNodes_object.o: $(SRCDIR)/ExpandNodes_object.c $(SRCDIR)/ExpandNodes.h $(SRCDIR)/ExpandNodes_internal.h $(SRCDIR)/genMake.h $(LIBCMN_BASE)/include/cmn_defs.h 
	$(CC) $(CFLAGS) -c -o $(OBJDIR)/$(@F) -I$(SRCDIR) $<

OBJS += $(OBJDIR)/GenBase.o

$(OBJDIR)/GenBase.o: $(SRCDIR)/GenBase.c $(SRCDIR)/GenBase.h $(SRCDIR)/GenBase_internal.h $(SRCDIR)/genMake.h $(LIBCMN_BASE)/include/cmn_defs.h 
	$(CC) $(CFLAGS) -c -o $(OBJDIR)/$(@F) -I$(SRCDIR) $<

OBJS += $(OBJDIR)/GenBase_object.o

$(OBJDIR)/GenBase_object.o: $(SRCDIR)/GenBase_object.c $(SRCDIR)/GenBase.h $(SRCDIR)/GenBase_internal.h $(SRCDIR)/genMake.h $(LIBCMN_BASE)/include/cmn_defs.h 
	$(CC) $(CFLAGS) -c -o $(OBJDIR)/$(@F) -I$(SRCDIR) $<

OBJS += $(OBJDIR)/GenMac.o

$(OBJDIR)/GenMac.o: $(SRCDIR)/GenMac.c $(SRCDIR)/GenMac.h $(SRCDIR)/GenMac_internal.h $(SRCDIR)/genMake.h $(LIBCMN_BASE)/include/cmn_defs.h 
	$(CC) $(CFLAGS) -c -o $(OBJDIR)/$(@F) -I$(SRCDIR) $<

OBJS += $(OBJDIR)/GenMac_object.o

$(OBJDIR)/GenMac_object.o: $(SRCDIR)/GenMac_object.c $(SRCDIR)/GenMac.h $(SRCDIR)/GenMac_internal.h $(SRCDIR)/genMake.h $(LIBCMN_BASE)/include/cmn_defs.h 
	$(CC) $(CFLAGS) -c -o $(OBJDIR)/$(@F) -I$(SRCDIR) $<

OBJS += $(OBJDIR)/GenWin.o

$(OBJDIR)/GenWin.o: $(SRCDIR)/GenWin.c $(SRCDIR)/GenWin.h $(SRCDIR)/GenWin_internal.h $(SRCDIR)/genMake.h $(LIBCMN_BASE)/include/cmn_defs.h 
	$(CC) $(CFLAGS) -c -o $(OBJDIR)/$(@F) -I$(SRCDIR) $<

OBJS += $(OBJDIR)/GenWin_object.o

$(OBJDIR)/GenWin_object.o: $(SRCDIR)/GenWin_object.c $(SRCDIR)/GenWin.h $(SRCDIR)/GenWin_internal.h $(SRCDIR)/genMake.h $(LIBCMN_BASE)/include/cmn_defs.h 
	$(CC) $(CFLAGS) -c -o $(OBJDIR)/$(@F) -I$(SRCDIR) $<

OBJS += $(OBJDIR)/Main.o

$(OBJDIR)/Main.o: $(SRCDIR)/Main.c $(SRCDIR)/Main.h $(SRCDIR)/Main_internal.h $(SRCDIR)/genMake.h $(LIBCMN_BASE)/include/cmn_defs.h 
	$(CC) $(CFLAGS) -c -o $(OBJDIR)/$(@F) -I$(SRCDIR) $<

OBJS += $(OBJDIR)/Main_object.o

$(OBJDIR)/Main_object.o: $(SRCDIR)/Main_object.c $(SRCDIR)/Main.h $(SRCDIR)/Main_internal.h $(SRCDIR)/genMake.h $(LIBCMN_BASE)/include/cmn_defs.h 
	$(CC) $(CFLAGS) -c -o $(OBJDIR)/$(@F) -I$(SRCDIR) $<

OBJS += $(OBJDIR)/NodeBase.o

$(OBJDIR)/NodeBase.o: $(SRCDIR)/NodeBase.c $(SRCDIR)/NodeBase.h $(SRCDIR)/NodeBase_internal.h $(SRCDIR)/genMake.h $(LIBCMN_BASE)/include/cmn_defs.h 
	$(CC) $(CFLAGS) -c -o $(OBJDIR)/$(@F) -I$(SRCDIR) $<

OBJS += $(OBJDIR)/NodeBase_object.o

$(OBJDIR)/NodeBase_object.o: $(SRCDIR)/NodeBase_object.c $(SRCDIR)/NodeBase.h $(SRCDIR)/NodeBase_internal.h $(SRCDIR)/genMake.h $(LIBCMN_BASE)/include/cmn_defs.h 
	$(CC) $(CFLAGS) -c -o $(OBJDIR)/$(@F) -I$(SRCDIR) $<

OBJS += $(OBJDIR)/NodeHdr.o

$(OBJDIR)/NodeHdr.o: $(SRCDIR)/NodeHdr.c $(SRCDIR)/NodeHdr.h $(SRCDIR)/NodeHdr_internal.h $(SRCDIR)/genMake.h $(LIBCMN_BASE)/include/cmn_defs.h 
	$(CC) $(CFLAGS) -c -o $(OBJDIR)/$(@F) -I$(SRCDIR) $<

OBJS += $(OBJDIR)/NodeHdr_object.o

$(OBJDIR)/NodeHdr_object.o: $(SRCDIR)/NodeHdr_object.c $(SRCDIR)/NodeHdr.h $(SRCDIR)/NodeHdr_internal.h $(SRCDIR)/genMake.h $(LIBCMN_BASE)/include/cmn_defs.h 
	$(CC) $(CFLAGS) -c -o $(OBJDIR)/$(@F) -I$(SRCDIR) $<

OBJS += $(OBJDIR)/NodeLib.o

$(OBJDIR)/NodeLib.o: $(SRCDIR)/NodeLib.c $(SRCDIR)/NodeLib.h $(SRCDIR)/NodeLib_internal.h $(SRCDIR)/genMake.h $(LIBCMN_BASE)/include/cmn_defs.h 
	$(CC) $(CFLAGS) -c -o $(OBJDIR)/$(@F) -I$(SRCDIR) $<

OBJS += $(OBJDIR)/NodeLib_object.o

$(OBJDIR)/NodeLib_object.o: $(SRCDIR)/NodeLib_object.c $(SRCDIR)/NodeLib.h $(SRCDIR)/NodeLib_internal.h $(SRCDIR)/genMake.h $(LIBCMN_BASE)/include/cmn_defs.h 
	$(CC) $(CFLAGS) -c -o $(OBJDIR)/$(@F) -I$(SRCDIR) $<

OBJS += $(OBJDIR)/NodeObj.o

$(OBJDIR)/NodeObj.o: $(SRCDIR)/NodeObj.c $(SRCDIR)/NodeBase.h $(SRCDIR)/NodeObj.h $(SRCDIR)/NodeObj_internal.h $(SRCDIR)/NodeRtn.h $(SRCDIR)/NodeTest.h $(SRCDIR)/genMake.h $(LIBCMN_BASE)/include/cmn_defs.h 
	$(CC) $(CFLAGS) -c -o $(OBJDIR)/$(@F) -I$(SRCDIR) $<

OBJS += $(OBJDIR)/NodeObj_object.o

$(OBJDIR)/NodeObj_object.o: $(SRCDIR)/NodeObj_object.c $(SRCDIR)/NodeBase.h $(SRCDIR)/NodeObj.h $(SRCDIR)/NodeObj_internal.h $(SRCDIR)/NodeRtn.h $(SRCDIR)/NodeTest.h $(SRCDIR)/genMake.h $(LIBCMN_BASE)/include/cmn_defs.h 
	$(CC) $(CFLAGS) -c -o $(OBJDIR)/$(@F) -I$(SRCDIR) $<

OBJS += $(OBJDIR)/NodePgm.o

$(OBJDIR)/NodePgm.o: $(SRCDIR)/NodePgm.c $(SRCDIR)/NodePgm.h $(SRCDIR)/NodePgm_internal.h $(SRCDIR)/genMake.h $(LIBCMN_BASE)/include/cmn_defs.h 
	$(CC) $(CFLAGS) -c -o $(OBJDIR)/$(@F) -I$(SRCDIR) $<

OBJS += $(OBJDIR)/NodePgm_object.o

$(OBJDIR)/NodePgm_object.o: $(SRCDIR)/NodePgm_object.c $(SRCDIR)/NodePgm.h $(SRCDIR)/NodePgm_internal.h $(SRCDIR)/genMake.h $(LIBCMN_BASE)/include/cmn_defs.h 
	$(CC) $(CFLAGS) -c -o $(OBJDIR)/$(@F) -I$(SRCDIR) $<

OBJS += $(OBJDIR)/NodeRtn.o

$(OBJDIR)/NodeRtn.o: $(SRCDIR)/NodeRtn.c $(SRCDIR)/NodeBase.h $(SRCDIR)/NodeRtn.h $(SRCDIR)/NodeRtn_internal.h $(SRCDIR)/NodeTest.h $(SRCDIR)/genMake.h $(LIBCMN_BASE)/include/cmn_defs.h 
	$(CC) $(CFLAGS) -c -o $(OBJDIR)/$(@F) -I$(SRCDIR) $<

OBJS += $(OBJDIR)/NodeRtnA.o

$(OBJDIR)/NodeRtnA.o: $(SRCDIR)/NodeRtnA.c $(SRCDIR)/NodeBase.h $(SRCDIR)/NodeRtnA.h $(SRCDIR)/NodeRtnA_internal.h $(SRCDIR)/genMake.h $(LIBCMN_BASE)/include/cmn_defs.h 
	$(CC) $(CFLAGS) -c -o $(OBJDIR)/$(@F) -I$(SRCDIR) $<

OBJS += $(OBJDIR)/NodeRtnA_object.o

$(OBJDIR)/NodeRtnA_object.o: $(SRCDIR)/NodeRtnA_object.c $(SRCDIR)/NodeBase.h $(SRCDIR)/NodeRtnA.h $(SRCDIR)/NodeRtnA_internal.h $(SRCDIR)/genMake.h $(LIBCMN_BASE)/include/cmn_defs.h 
	$(CC) $(CFLAGS) -c -o $(OBJDIR)/$(@F) -I$(SRCDIR) $<

OBJS += $(OBJDIR)/NodeRtn_object.o

$(OBJDIR)/NodeRtn_object.o: $(SRCDIR)/NodeRtn_object.c $(SRCDIR)/NodeBase.h $(SRCDIR)/NodeRtn.h $(SRCDIR)/NodeRtn_internal.h $(SRCDIR)/NodeTest.h $(SRCDIR)/genMake.h $(LIBCMN_BASE)/include/cmn_defs.h 
	$(CC) $(CFLAGS) -c -o $(OBJDIR)/$(@F) -I$(SRCDIR) $<

OBJS += $(OBJDIR)/NodeTest.o

$(OBJDIR)/NodeTest.o: $(SRCDIR)/NodeTest.c $(SRCDIR)/NodeBase.h $(SRCDIR)/NodeTest.h $(SRCDIR)/NodeTest_internal.h $(SRCDIR)/genMake.h $(LIBCMN_BASE)/include/cmn_defs.h 
	$(CC) $(CFLAGS) -c -o $(OBJDIR)/$(@F) -I$(SRCDIR) $<

OBJS += $(OBJDIR)/NodeTest_object.o

$(OBJDIR)/NodeTest_object.o: $(SRCDIR)/NodeTest_object.c $(SRCDIR)/NodeBase.h $(SRCDIR)/NodeTest.h $(SRCDIR)/NodeTest_internal.h $(SRCDIR)/genMake.h $(LIBCMN_BASE)/include/cmn_defs.h 
	$(CC) $(CFLAGS) -c -o $(OBJDIR)/$(@F) -I$(SRCDIR) $<

OBJS += $(OBJDIR)/NodeTstA.o

$(OBJDIR)/NodeTstA.o: $(SRCDIR)/NodeTstA.c $(SRCDIR)/NodeBase.h $(SRCDIR)/NodeTstA.h $(SRCDIR)/NodeTstA_internal.h $(SRCDIR)/genMake.h $(LIBCMN_BASE)/include/cmn_defs.h 
	$(CC) $(CFLAGS) -c -o $(OBJDIR)/$(@F) -I$(SRCDIR) $<

OBJS += $(OBJDIR)/NodeTstA_object.o

$(OBJDIR)/NodeTstA_object.o: $(SRCDIR)/NodeTstA_object.c $(SRCDIR)/NodeBase.h $(SRCDIR)/NodeTstA.h $(SRCDIR)/NodeTstA_internal.h $(SRCDIR)/genMake.h $(LIBCMN_BASE)/include/cmn_defs.h 
	$(CC) $(CFLAGS) -c -o $(OBJDIR)/$(@F) -I$(SRCDIR) $<

OBJS += $(OBJDIR)/SrcParse.o

$(OBJDIR)/SrcParse.o: $(SRCDIR)/SrcParse.c $(SRCDIR)/SrcParse.h $(SRCDIR)/SrcParse_internal.h $(SRCDIR)/genMake.h $(LIBCMN_BASE)/include/cmn_defs.h 
	$(CC) $(CFLAGS) -c -o $(OBJDIR)/$(@F) -I$(SRCDIR) $<

OBJS += $(OBJDIR)/SrcParse_object.o

$(OBJDIR)/SrcParse_object.o: $(SRCDIR)/SrcParse_object.c $(SRCDIR)/SrcParse.h $(SRCDIR)/SrcParse_internal.h $(SRCDIR)/genMake.h $(LIBCMN_BASE)/include/cmn_defs.h 
	$(CC) $(CFLAGS) -c -o $(OBJDIR)/$(@F) -I$(SRCDIR) $<





#------------------------------------------------
#      Compile and execute Tests
#------------------------------------------------


TESTS += Dict_test

Dict_test: $(TEST_SRC)/Dict_test.c $(SRCDIR)/Dict.h $(SRCDIR)/Dict_internal.h $(SRCDIR)/genMake.h $(LIBCMN_BASE)/include/cmn_defs.h 
	$(CC) $(CFLAGS) $(CFLAGS_TEST) -o $(TEST_BIN)/$(@F) $(OBJS) -I$(TEST_SRC) -I$(SRCDIR) $<
	$(TEST_BIN)/$(@F) --no_int3

TESTS += ExpandNodes_test

ExpandNodes_test: $(TEST_SRC)/ExpandNodes_test.c $(SRCDIR)/ExpandNodes.h $(SRCDIR)/ExpandNodes_internal.h $(SRCDIR)/genMake.h $(LIBCMN_BASE)/include/cmn_defs.h 
	$(CC) $(CFLAGS) $(CFLAGS_TEST) -o $(TEST_BIN)/$(@F) $(OBJS) -I$(TEST_SRC) -I$(SRCDIR) $<
	$(TEST_BIN)/$(@F) --no_int3

TESTS += GenBase_test

GenBase_test: $(TEST_SRC)/GenBase_test.c $(SRCDIR)/GenBase.h $(SRCDIR)/GenBase_internal.h $(SRCDIR)/genMake.h $(LIBCMN_BASE)/include/cmn_defs.h 
	$(CC) $(CFLAGS) $(CFLAGS_TEST) -o $(TEST_BIN)/$(@F) $(OBJS) -I$(TEST_SRC) -I$(SRCDIR) $<
	$(TEST_BIN)/$(@F) --no_int3

TESTS += GenMac_test

GenMac_test: $(TEST_SRC)/GenMac_test.c $(SRCDIR)/GenMac.h $(SRCDIR)/GenMac_internal.h $(SRCDIR)/genMake.h $(LIBCMN_BASE)/include/cmn_defs.h 
	$(CC) $(CFLAGS) $(CFLAGS_TEST) -o $(TEST_BIN)/$(@F) $(OBJS) -I$(TEST_SRC) -I$(SRCDIR) $<
	$(TEST_BIN)/$(@F) --no_int3

TESTS += GenWin_test

GenWin_test: $(TEST_SRC)/GenWin_test.c $(SRCDIR)/GenWin.h $(SRCDIR)/GenWin_internal.h $(SRCDIR)/genMake.h $(LIBCMN_BASE)/include/cmn_defs.h 
	$(CC) $(CFLAGS) $(CFLAGS_TEST) -o $(TEST_BIN)/$(@F) $(OBJS) -I$(TEST_SRC) -I$(SRCDIR) $<
	$(TEST_BIN)/$(@F) --no_int3

TESTS += Main_test

Main_test: $(TEST_SRC)/Main_test.c $(SRCDIR)/Main.h $(SRCDIR)/Main_internal.h $(SRCDIR)/genMake.h $(LIBCMN_BASE)/include/cmn_defs.h 
	$(CC) $(CFLAGS) $(CFLAGS_TEST) -o $(TEST_BIN)/$(@F) $(OBJS) -I$(TEST_SRC) -I$(SRCDIR) $<
	$(TEST_BIN)/$(@F) --no_int3

TESTS += NodeBase_test

NodeBase_test: $(TEST_SRC)/NodeBase_test.c $(SRCDIR)/NodeBase.h $(SRCDIR)/NodeBase_internal.h $(SRCDIR)/genMake.h $(LIBCMN_BASE)/include/cmn_defs.h 
	$(CC) $(CFLAGS) $(CFLAGS_TEST) -o $(TEST_BIN)/$(@F) $(OBJS) -I$(TEST_SRC) -I$(SRCDIR) $<
	$(TEST_BIN)/$(@F) --no_int3

TESTS += NodeHdr_test

NodeHdr_test: $(TEST_SRC)/NodeHdr_test.c $(SRCDIR)/NodeHdr.h $(SRCDIR)/NodeHdr_internal.h $(SRCDIR)/genMake.h $(LIBCMN_BASE)/include/cmn_defs.h 
	$(CC) $(CFLAGS) $(CFLAGS_TEST) -o $(TEST_BIN)/$(@F) $(OBJS) -I$(TEST_SRC) -I$(SRCDIR) $<
	$(TEST_BIN)/$(@F) --no_int3

TESTS += NodeLib_test

NodeLib_test: $(TEST_SRC)/NodeLib_test.c $(SRCDIR)/NodeLib.h $(SRCDIR)/NodeLib_internal.h $(SRCDIR)/genMake.h $(LIBCMN_BASE)/include/cmn_defs.h 
	$(CC) $(CFLAGS) $(CFLAGS_TEST) -o $(TEST_BIN)/$(@F) $(OBJS) -I$(TEST_SRC) -I$(SRCDIR) $<
	$(TEST_BIN)/$(@F) --no_int3

TESTS += NodeObj_test

NodeObj_test: $(TEST_SRC)/NodeObj_test.c $(SRCDIR)/NodeObj.h $(SRCDIR)/NodeObj_internal.h $(SRCDIR)/NodeBase.h $(SRCDIR)/NodeRtn.h $(SRCDIR)/NodeTest.h $(SRCDIR)/genMake.h $(LIBCMN_BASE)/include/cmn_defs.h 
	$(CC) $(CFLAGS) $(CFLAGS_TEST) -o $(TEST_BIN)/$(@F) $(OBJS) -I$(TEST_SRC) -I$(SRCDIR) $<
	$(TEST_BIN)/$(@F) --no_int3

TESTS += NodePgm_test

NodePgm_test: $(TEST_SRC)/NodePgm_test.c $(SRCDIR)/NodePgm.h $(SRCDIR)/NodePgm_internal.h $(SRCDIR)/genMake.h $(LIBCMN_BASE)/include/cmn_defs.h 
	$(CC) $(CFLAGS) $(CFLAGS_TEST) -o $(TEST_BIN)/$(@F) $(OBJS) -I$(TEST_SRC) -I$(SRCDIR) $<
	$(TEST_BIN)/$(@F) --no_int3

TESTS += NodeRtnA_test

NodeRtnA_test: $(TEST_SRC)/NodeRtnA_test.c $(SRCDIR)/NodeRtnA.h $(SRCDIR)/NodeRtnA_internal.h $(SRCDIR)/NodeBase.h $(SRCDIR)/genMake.h $(LIBCMN_BASE)/include/cmn_defs.h 
	$(CC) $(CFLAGS) $(CFLAGS_TEST) -o $(TEST_BIN)/$(@F) $(OBJS) -I$(TEST_SRC) -I$(SRCDIR) $<
	$(TEST_BIN)/$(@F) --no_int3

TESTS += NodeRtn_test

NodeRtn_test: $(TEST_SRC)/NodeRtn_test.c $(SRCDIR)/NodeRtn.h $(SRCDIR)/NodeRtn_internal.h $(SRCDIR)/NodeBase.h $(SRCDIR)/NodeTest.h $(SRCDIR)/genMake.h $(LIBCMN_BASE)/include/cmn_defs.h 
	$(CC) $(CFLAGS) $(CFLAGS_TEST) -o $(TEST_BIN)/$(@F) $(OBJS) -I$(TEST_SRC) -I$(SRCDIR) $<
	$(TEST_BIN)/$(@F) --no_int3

TESTS += NodeTest_test

NodeTest_test: $(TEST_SRC)/NodeTest_test.c $(SRCDIR)/NodeTest.h $(SRCDIR)/NodeTest_internal.h $(SRCDIR)/NodeBase.h $(SRCDIR)/genMake.h $(LIBCMN_BASE)/include/cmn_defs.h 
	$(CC) $(CFLAGS) $(CFLAGS_TEST) -o $(TEST_BIN)/$(@F) $(OBJS) -I$(TEST_SRC) -I$(SRCDIR) $<
	$(TEST_BIN)/$(@F) --no_int3

TESTS += NodeTstA_test

NodeTstA_test: $(TEST_SRC)/NodeTstA_test.c $(SRCDIR)/NodeTstA.h $(SRCDIR)/NodeTstA_internal.h $(SRCDIR)/NodeBase.h $(SRCDIR)/genMake.h $(LIBCMN_BASE)/include/cmn_defs.h 
	$(CC) $(CFLAGS) $(CFLAGS_TEST) -o $(TEST_BIN)/$(@F) $(OBJS) -I$(TEST_SRC) -I$(SRCDIR) $<
	$(TEST_BIN)/$(@F) --no_int3

TESTS += SrcParse_test

SrcParse_test: $(TEST_SRC)/SrcParse_test.c $(SRCDIR)/SrcParse.h $(SRCDIR)/SrcParse_internal.h $(SRCDIR)/genMake.h $(LIBCMN_BASE)/include/cmn_defs.h 
	$(CC) $(CFLAGS) $(CFLAGS_TEST) -o $(TEST_BIN)/$(@F) $(OBJS) -I$(TEST_SRC) -I$(SRCDIR) $<
	$(TEST_BIN)/$(@F) --no_int3





#------------------------------------------------
#              Phony Targets
#------------------------------------------------


.PHONY: all
all:  create_dirs link


.PHONY: build
build:  create_dirs link


.PHONY: check
check: $(TESTS)


.PHONY: clean
clean:
	-rm -fr $(BUILD)/$(PGMNAM)


.PHONY: create_dirs
create_dirs:
	-mkdir -p $(BUILD)
	-mkdir -p $(TEST_OBJ)
	-mkdir -p $(TEST_BIN)


.PHONY: install
install:
	-cd $(INSTALL_BASE) ; [ -d $(PGMNAM) ] && rm -fr $(PGMNAM)
	cp $(OBJDIR)/$(PGMNAM) $(INSTALL_BASE)/$(PGMNAM)


.PHONY: link
link: $(OBJS) $(SRCDIR)/mainProgram.c
	CC -o $(OBJDIR)/$(PGMNAM) $(CFLAGS) $(CFLAGS_LIBS) $^


.PHONY: test
test: $(TESTS)


