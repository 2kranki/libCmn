# Generated file - Edits will be discarded by next generation!
# ( 1/15/2022 20:14:17.000)

.DEFAULT_GOAL := all
SHELL=/bin/sh

PGMNAM=genObject
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


OBJS += $(OBJDIR)/ClassFile.o

$(OBJDIR)/ClassFile.o: $(SRCDIR)/ClassFile.c $(SRCDIR)/ClassFile.h $(SRCDIR)/ClassFile_internal.h $(SRCDIR)/genObject_defs.h $(LIBCMN_BASE)/include/cmn_defs.h 
	$(CC) $(CFLAGS) -c -o $(OBJDIR)/$(@F) -I$(SRCDIR) $<

OBJS += $(OBJDIR)/ClassFile_object.o

$(OBJDIR)/ClassFile_object.o: $(SRCDIR)/ClassFile_object.c $(SRCDIR)/ClassFile.h $(SRCDIR)/ClassFile_internal.h $(SRCDIR)/genObject_defs.h $(LIBCMN_BASE)/include/cmn_defs.h 
	$(CC) $(CFLAGS) -c -o $(OBJDIR)/$(@F) -I$(SRCDIR) $<

OBJS += $(OBJDIR)/ClassItem.o

$(OBJDIR)/ClassItem.o: $(SRCDIR)/ClassItem.c $(SRCDIR)/ClassItem.h $(SRCDIR)/ClassItem_internal.h $(SRCDIR)/genObject_defs.h $(LIBCMN_BASE)/include/cmn_defs.h 
	$(CC) $(CFLAGS) -c -o $(OBJDIR)/$(@F) -I$(SRCDIR) $<

OBJS += $(OBJDIR)/ClassItem_json.o

$(OBJDIR)/ClassItem_json.o: $(SRCDIR)/ClassItem_json.c $(SRCDIR)/ClassItem.h $(SRCDIR)/ClassItem_internal.h $(SRCDIR)/genObject_defs.h $(LIBCMN_BASE)/include/cmn_defs.h 
	$(CC) $(CFLAGS) -c -o $(OBJDIR)/$(@F) -I$(SRCDIR) $<

OBJS += $(OBJDIR)/ClassItem_object.o

$(OBJDIR)/ClassItem_object.o: $(SRCDIR)/ClassItem_object.c $(SRCDIR)/ClassItem.h $(SRCDIR)/ClassItem_internal.h $(SRCDIR)/genObject_defs.h $(LIBCMN_BASE)/include/cmn_defs.h 
	$(CC) $(CFLAGS) -c -o $(OBJDIR)/$(@F) -I$(SRCDIR) $<

OBJS += $(OBJDIR)/ClassItems.o

$(OBJDIR)/ClassItems.o: $(SRCDIR)/ClassItems.c $(SRCDIR)/ClassItems.h $(SRCDIR)/ClassItems_internal.h $(SRCDIR)/genObject_defs.h $(LIBCMN_BASE)/include/cmn_defs.h 
	$(CC) $(CFLAGS) -c -o $(OBJDIR)/$(@F) -I$(SRCDIR) $<

OBJS += $(OBJDIR)/ClassItems_json.o

$(OBJDIR)/ClassItems_json.o: $(SRCDIR)/ClassItems_json.c $(SRCDIR)/ClassItems.h $(SRCDIR)/ClassItems_internal.h $(SRCDIR)/genObject_defs.h $(LIBCMN_BASE)/include/cmn_defs.h 
	$(CC) $(CFLAGS) -c -o $(OBJDIR)/$(@F) -I$(SRCDIR) $<

OBJS += $(OBJDIR)/ClassItems_object.o

$(OBJDIR)/ClassItems_object.o: $(SRCDIR)/ClassItems_object.c $(SRCDIR)/ClassItems.h $(SRCDIR)/ClassItems_internal.h $(SRCDIR)/genObject_defs.h $(LIBCMN_BASE)/include/cmn_defs.h 
	$(CC) $(CFLAGS) -c -o $(OBJDIR)/$(@F) -I$(SRCDIR) $<

OBJS += $(OBJDIR)/Dict.o

$(OBJDIR)/Dict.o: $(SRCDIR)/Dict.c $(SRCDIR)/Dict.h $(SRCDIR)/Dict_internal.h $(SRCDIR)/genObject_defs.h $(LIBCMN_BASE)/include/cmn_defs.h 
	$(CC) $(CFLAGS) -c -o $(OBJDIR)/$(@F) -I$(SRCDIR) $<

OBJS += $(OBJDIR)/Dict_object.o

$(OBJDIR)/Dict_object.o: $(SRCDIR)/Dict_object.c $(SRCDIR)/Dict.h $(SRCDIR)/Dict_internal.h $(SRCDIR)/genObject_defs.h $(LIBCMN_BASE)/include/cmn_defs.h 
	$(CC) $(CFLAGS) -c -o $(OBJDIR)/$(@F) -I$(SRCDIR) $<

OBJS += $(OBJDIR)/EnumFile.o

$(OBJDIR)/EnumFile.o: $(SRCDIR)/EnumFile.c $(SRCDIR)/EnumFile.h $(SRCDIR)/EnumFile_internal.h $(SRCDIR)/genObject_defs.h $(LIBCMN_BASE)/include/cmn_defs.h 
	$(CC) $(CFLAGS) -c -o $(OBJDIR)/$(@F) -I$(SRCDIR) $<

OBJS += $(OBJDIR)/EnumFile_object.o

$(OBJDIR)/EnumFile_object.o: $(SRCDIR)/EnumFile_object.c $(SRCDIR)/EnumFile.h $(SRCDIR)/EnumFile_internal.h $(SRCDIR)/genObject_defs.h $(LIBCMN_BASE)/include/cmn_defs.h 
	$(CC) $(CFLAGS) -c -o $(OBJDIR)/$(@F) -I$(SRCDIR) $<

OBJS += $(OBJDIR)/EnumItem.o

$(OBJDIR)/EnumItem.o: $(SRCDIR)/EnumItem.c $(SRCDIR)/EnumItem.h $(SRCDIR)/EnumItem_internal.h $(SRCDIR)/genObject_defs.h $(LIBCMN_BASE)/include/cmn_defs.h 
	$(CC) $(CFLAGS) -c -o $(OBJDIR)/$(@F) -I$(SRCDIR) $<

OBJS += $(OBJDIR)/EnumItem_json.o

$(OBJDIR)/EnumItem_json.o: $(SRCDIR)/EnumItem_json.c $(SRCDIR)/EnumItem.h $(SRCDIR)/EnumItem_internal.h $(SRCDIR)/genObject_defs.h $(LIBCMN_BASE)/include/cmn_defs.h 
	$(CC) $(CFLAGS) -c -o $(OBJDIR)/$(@F) -I$(SRCDIR) $<

OBJS += $(OBJDIR)/EnumItem_object.o

$(OBJDIR)/EnumItem_object.o: $(SRCDIR)/EnumItem_object.c $(SRCDIR)/EnumItem.h $(SRCDIR)/EnumItem_internal.h $(SRCDIR)/genObject_defs.h $(LIBCMN_BASE)/include/cmn_defs.h 
	$(CC) $(CFLAGS) -c -o $(OBJDIR)/$(@F) -I$(SRCDIR) $<

OBJS += $(OBJDIR)/EnumItems.o

$(OBJDIR)/EnumItems.o: $(SRCDIR)/EnumItems.c $(SRCDIR)/EnumItems.h $(SRCDIR)/EnumItems_internal.h $(SRCDIR)/genObject_defs.h $(LIBCMN_BASE)/include/cmn_defs.h 
	$(CC) $(CFLAGS) -c -o $(OBJDIR)/$(@F) -I$(SRCDIR) $<

OBJS += $(OBJDIR)/EnumItems_json.o

$(OBJDIR)/EnumItems_json.o: $(SRCDIR)/EnumItems_json.c $(SRCDIR)/EnumItems.h $(SRCDIR)/EnumItems_internal.h $(SRCDIR)/genObject_defs.h $(LIBCMN_BASE)/include/cmn_defs.h 
	$(CC) $(CFLAGS) -c -o $(OBJDIR)/$(@F) -I$(SRCDIR) $<

OBJS += $(OBJDIR)/EnumItems_object.o

$(OBJDIR)/EnumItems_object.o: $(SRCDIR)/EnumItems_object.c $(SRCDIR)/EnumItems.h $(SRCDIR)/EnumItems_internal.h $(SRCDIR)/genObject_defs.h $(LIBCMN_BASE)/include/cmn_defs.h 
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

OBJS += $(OBJDIR)/PropFile.o

$(OBJDIR)/PropFile.o: $(SRCDIR)/PropFile.c $(SRCDIR)/PropFile.h $(SRCDIR)/PropFile_internal.h $(SRCDIR)/genObject_defs.h $(LIBCMN_BASE)/include/cmn_defs.h 
	$(CC) $(CFLAGS) -c -o $(OBJDIR)/$(@F) -I$(SRCDIR) $<

OBJS += $(OBJDIR)/PropFile_object.o

$(OBJDIR)/PropFile_object.o: $(SRCDIR)/PropFile_object.c $(SRCDIR)/PropFile.h $(SRCDIR)/PropFile_internal.h $(SRCDIR)/genObject_defs.h $(LIBCMN_BASE)/include/cmn_defs.h 
	$(CC) $(CFLAGS) -c -o $(OBJDIR)/$(@F) -I$(SRCDIR) $<

OBJS += $(OBJDIR)/PropItem.o

$(OBJDIR)/PropItem.o: $(SRCDIR)/PropItem.c $(SRCDIR)/PropItem.h $(SRCDIR)/PropItem_internal.h $(SRCDIR)/genObject_defs.h $(LIBCMN_BASE)/include/cmn_defs.h 
	$(CC) $(CFLAGS) -c -o $(OBJDIR)/$(@F) -I$(SRCDIR) $<

OBJS += $(OBJDIR)/PropItem_json.o

$(OBJDIR)/PropItem_json.o: $(SRCDIR)/PropItem_json.c $(SRCDIR)/PropItem.h $(SRCDIR)/PropItem_internal.h $(SRCDIR)/genObject_defs.h $(LIBCMN_BASE)/include/cmn_defs.h 
	$(CC) $(CFLAGS) -c -o $(OBJDIR)/$(@F) -I$(SRCDIR) $<

OBJS += $(OBJDIR)/PropItem_object.o

$(OBJDIR)/PropItem_object.o: $(SRCDIR)/PropItem_object.c $(SRCDIR)/PropItem.h $(SRCDIR)/PropItem_internal.h $(SRCDIR)/genObject_defs.h $(LIBCMN_BASE)/include/cmn_defs.h 
	$(CC) $(CFLAGS) -c -o $(OBJDIR)/$(@F) -I$(SRCDIR) $<

OBJS += $(OBJDIR)/PropItems.o

$(OBJDIR)/PropItems.o: $(SRCDIR)/PropItems.c $(SRCDIR)/PropItems.h $(SRCDIR)/PropItems_internal.h $(SRCDIR)/genObject_defs.h $(LIBCMN_BASE)/include/cmn_defs.h 
	$(CC) $(CFLAGS) -c -o $(OBJDIR)/$(@F) -I$(SRCDIR) $<

OBJS += $(OBJDIR)/PropItems_json.o

$(OBJDIR)/PropItems_json.o: $(SRCDIR)/PropItems_json.c $(SRCDIR)/PropItems.h $(SRCDIR)/PropItems_internal.h $(SRCDIR)/genObject_defs.h $(LIBCMN_BASE)/include/cmn_defs.h 
	$(CC) $(CFLAGS) -c -o $(OBJDIR)/$(@F) -I$(SRCDIR) $<

OBJS += $(OBJDIR)/PropItems_object.o

$(OBJDIR)/PropItems_object.o: $(SRCDIR)/PropItems_object.c $(SRCDIR)/PropItems.h $(SRCDIR)/PropItems_internal.h $(SRCDIR)/genObject_defs.h $(LIBCMN_BASE)/include/cmn_defs.h 
	$(CC) $(CFLAGS) -c -o $(OBJDIR)/$(@F) -I$(SRCDIR) $<





#------------------------------------------------
#      Compile and execute Tests
#------------------------------------------------


TESTS += ClassFile_test

ClassFile_test: $(TEST_SRC)/ClassFile_test.c $(SRCDIR)/ClassFile.h $(SRCDIR)/ClassFile_internal.h $(SRCDIR)/genObject_defs.h $(LIBCMN_BASE)/include/cmn_defs.h 
	$(CC) $(CFLAGS) $(CFLAGS_TEST) -o $(TEST_BIN)/$(@F) $(OBJS) -I$(TEST_SRC) -I$(SRCDIR) $<
	$(TEST_BIN)/$(@F) --no_int3

TESTS += ClassItem_test

ClassItem_test: $(TEST_SRC)/ClassItem_test.c $(SRCDIR)/ClassItem.h $(SRCDIR)/ClassItem_internal.h $(SRCDIR)/genObject_defs.h $(LIBCMN_BASE)/include/cmn_defs.h 
	$(CC) $(CFLAGS) $(CFLAGS_TEST) -o $(TEST_BIN)/$(@F) $(OBJS) -I$(TEST_SRC) -I$(SRCDIR) $<
	$(TEST_BIN)/$(@F) --no_int3

TESTS += ClassItems_test

ClassItems_test: $(TEST_SRC)/ClassItems_test.c $(SRCDIR)/ClassItems.h $(SRCDIR)/ClassItems_internal.h $(SRCDIR)/genObject_defs.h $(LIBCMN_BASE)/include/cmn_defs.h 
	$(CC) $(CFLAGS) $(CFLAGS_TEST) -o $(TEST_BIN)/$(@F) $(OBJS) -I$(TEST_SRC) -I$(SRCDIR) $<
	$(TEST_BIN)/$(@F) --no_int3

TESTS += Dict_test

Dict_test: $(TEST_SRC)/Dict_test.c $(SRCDIR)/Dict.h $(SRCDIR)/Dict_internal.h $(SRCDIR)/genObject_defs.h $(LIBCMN_BASE)/include/cmn_defs.h 
	$(CC) $(CFLAGS) $(CFLAGS_TEST) -o $(TEST_BIN)/$(@F) $(OBJS) -I$(TEST_SRC) -I$(SRCDIR) $<
	$(TEST_BIN)/$(@F) --no_int3

TESTS += EnumFile_test

EnumFile_test: $(TEST_SRC)/EnumFile_test.c $(SRCDIR)/EnumFile.h $(SRCDIR)/EnumFile_internal.h $(SRCDIR)/genObject_defs.h $(LIBCMN_BASE)/include/cmn_defs.h 
	$(CC) $(CFLAGS) $(CFLAGS_TEST) -o $(TEST_BIN)/$(@F) $(OBJS) -I$(TEST_SRC) -I$(SRCDIR) $<
	$(TEST_BIN)/$(@F) --no_int3

TESTS += EnumItem_test

EnumItem_test: $(TEST_SRC)/EnumItem_test.c $(SRCDIR)/EnumItem.h $(SRCDIR)/EnumItem_internal.h $(SRCDIR)/genObject_defs.h $(LIBCMN_BASE)/include/cmn_defs.h 
	$(CC) $(CFLAGS) $(CFLAGS_TEST) -o $(TEST_BIN)/$(@F) $(OBJS) -I$(TEST_SRC) -I$(SRCDIR) $<
	$(TEST_BIN)/$(@F) --no_int3

TESTS += EnumItems_test

EnumItems_test: $(TEST_SRC)/EnumItems_test.c $(SRCDIR)/EnumItems.h $(SRCDIR)/EnumItems_internal.h $(SRCDIR)/genObject_defs.h $(LIBCMN_BASE)/include/cmn_defs.h 
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

TESTS += PropFile_test

PropFile_test: $(TEST_SRC)/PropFile_test.c $(SRCDIR)/PropFile.h $(SRCDIR)/PropFile_internal.h $(SRCDIR)/genObject_defs.h $(LIBCMN_BASE)/include/cmn_defs.h 
	$(CC) $(CFLAGS) $(CFLAGS_TEST) -o $(TEST_BIN)/$(@F) $(OBJS) -I$(TEST_SRC) -I$(SRCDIR) $<
	$(TEST_BIN)/$(@F) --no_int3

TESTS += PropItem_test

PropItem_test: $(TEST_SRC)/PropItem_test.c $(SRCDIR)/PropItem.h $(SRCDIR)/PropItem_internal.h $(SRCDIR)/genObject_defs.h $(LIBCMN_BASE)/include/cmn_defs.h 
	$(CC) $(CFLAGS) $(CFLAGS_TEST) -o $(TEST_BIN)/$(@F) $(OBJS) -I$(TEST_SRC) -I$(SRCDIR) $<
	$(TEST_BIN)/$(@F) --no_int3

TESTS += PropItems_test

PropItems_test: $(TEST_SRC)/PropItems_test.c $(SRCDIR)/PropItems.h $(SRCDIR)/PropItems_internal.h $(SRCDIR)/genObject_defs.h $(LIBCMN_BASE)/include/cmn_defs.h 
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


