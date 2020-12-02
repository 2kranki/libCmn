// vi:nu:et:sts=4 ts=4 sw=4
/*
 *	Generated 07/17/2017 14:59:49
 */





// All code under test must be linked into the Unit Test bundle
// Test Macros:
//      TINYTEST_ASSERT(condition)
//      TINYTEST_ASSERT_MSG(condition,msg)
//      TINYTEST_EQUAL(expected, actual)
//      TINYTEST_EQUAL_MSG(expected, actual, msg)
//      TINYTEST_FALSE_MSG(condition,msg)
//      TINYTEST_FALSE(condition)
//      TINYTEST_TRUE_MSG(pointer,msg)
//      TINYTEST_TRUE(condition)





#include    <tinytest.h>
#include    <cmn_defs.h>
#include    <SrcErrors.h>
#include    <trace.h>
#include    <Main_internal.h>



#include    <data_test.c>

// pGoodJsonA needs to match libJson01.txt in tests subdirectory.
static
const
char            *pGoodJsonA =
"{\n"
    "library:{\n"
        "name:\"Cmn\"\n"
    "}\n,"
    "objects: [\n"
        "{name:\"AStr\", json:true},\n"
        "{name:\"appl\"},\n"
        "{name:\"Xyzzy\", os:[\"win32\"]}\n"          // Should not be generated!
    "],\n"
    "routines: [\n"
            "{name:\"dllist\"}\n"
    "]\n"
"}\n";
const
char            *pOutputA =
".DEFAULT_GOAL := all\n"
"SHELL=/bin/sh\n\n"
"LIBNAM=libCmn\n"
"SYS=macos64\n"
"TEMP=/tmp\n"
"BASE_OBJ = $(TEMP)/$(LIBNAM)\n"
"SRCDIR = ./src\n"
"TEST_SRC = ./tests\n"
"INSTALL_BASE = $(HOME)/Support/lib/$(SYS)\n"
"LIB_BASE = $(HOME)/Support/lib/$(SYS)\n\n"

"CFLAGS += -g -Werror -I$(SRCDIR)\n"
"ifdef  NDEBUG\n"
"CFLAGS += -DNDEBUG\n"
"else   #DEBUG\n"
"CFLAGS += -D_DEBUG\n"
"endif  #NDEBUG\n"
"CFLAGS += -D__MACOS64_ENV__\n"
"CFLAGS_LIBS = \n"
"CFLAGS_TEST = -I$(TEST_SRC) $(CFLAGS_LIBS) -lcurses -lsqlite3\n\n"

"INSTALL_DIR = $(INSTALL_BASE)/$(LIBNAM)\n"
"LIBOBJ = $(BASE_OBJ)/$(SYS)\n"
"ifdef  NDEBUG\n"
"LIB_FILENAME=$(LIBNAM)R.a\n"
"OBJDIR = $(LIBOBJ)/o/r\n"
"else   #DEBUG\n"
"LIB_FILENAME=$(LIBNAM)D.a\n"
"OBJDIR = $(LIBOBJ)/o/d\n"
"endif  #NDEBUG\n"
"TEST_OBJ = $(OBJDIR)/obj\n"
"TEST_BIN = $(OBJDIR)/bin\n"
"LIB_PATH = $(LIBOBJ)/$(LIB_FILENAME)\n\n"

".SUFFIXES:\n"
".SUFFIXES: .asm .c .cpp .o\n\n"

"OBJS =\n\n"
"TESTS =\n\n\n"

"OBJS += $(OBJDIR)/AStr.o\n\n"
"$(OBJDIR)/AStr.o: $(SRCDIR)/AStr.c $(SRCDIR)/AStr.h $(SRCDIR)/AStr_internal.h \n"
"\t$(CC) $(CFLAGS) -c -o $(OBJDIR)/$(@F) -I$(SRCDIR) $<\n\n"
"OBJS += $(OBJDIR)/AStr_json.o\n\n"
"$(OBJDIR)/AStr_json.o: $(SRCDIR)/AStr_json.c $(SRCDIR)/AStr.h $(SRCDIR)/AStr_internal.h \n"
"\t$(CC) $(CFLAGS) -c -o $(OBJDIR)/$(@F) -I$(SRCDIR) $<\n\n"
"OBJS += $(OBJDIR)/AStr_object.o\n\n"
"$(OBJDIR)/AStr_object.o: $(SRCDIR)/AStr_object.c $(SRCDIR)/AStr.h $(SRCDIR)/AStr_internal.h \n"
"\t$(CC) $(CFLAGS) -c -o $(OBJDIR)/$(@F) -I$(SRCDIR) $<\n\n"

"OBJS += $(OBJDIR)/appl.o\n\n"
"$(OBJDIR)/appl.o: $(SRCDIR)/appl.c $(SRCDIR)/appl.h $(SRCDIR)/appl_internal.h \n"
"\t$(CC) $(CFLAGS) -c -o $(OBJDIR)/$(@F) -I$(SRCDIR) $<\n\n"
"OBJS += $(OBJDIR)/appl_object.o\n\n"
"$(OBJDIR)/appl_object.o: $(SRCDIR)/appl_object.c $(SRCDIR)/appl.h $(SRCDIR)/appl_internal.h \n"
"\t$(CC) $(CFLAGS) -c -o $(OBJDIR)/$(@F) -I$(SRCDIR) $<\n\n"

"OBJS += $(OBJDIR)/dllist.o\n\n"
"$(OBJDIR)/dllist.o: $(SRCDIR)/dllist.c \n"
"\t$(CC) $(CFLAGS) -c -o $(OBJDIR)/$(@F) -I$(SRCDIR) $<\n\n"

"TESTS += AStr_test\n\n"
"AStr_test: $(TEST_SRC)/AStr_test.c $(SRCDIR)/AStr.h $(SRCDIR)/AStr_internal.h \n"
"\t$(CC) $(CFLAGS) $(CFLAGS_TEST) -o $(TEST_BIN)/$(@F) $(OBJS) -I$(TEST_SRC) -I$(SRCDIR) $<\n"
"\t$(TEST_BIN)/$(@F)\n\n"
"TESTS += appl_test\n\n"
"appl_test: $(TEST_SRC)/appl_test.c $(SRCDIR)/appl.h $(SRCDIR)/appl_internal.h \n"
"\t$(CC) $(CFLAGS) $(CFLAGS_TEST) -o $(TEST_BIN)/$(@F) $(OBJS) -I$(TEST_SRC) -I$(SRCDIR) $<\n"
"\t$(TEST_BIN)/$(@F)\n\n"

"\n\n$(LIB_PATH):  $(OBJS)\n"
"\t-cd $(LIBOBJ) ; [ -d $(LIB_FILENAME) ] && rm $(LIB_FILENAME)\n"
"\tar rc $(LIB_PATH) $(OBJS)\n\n\n"
".PHONY: all\n"
"all:  clean create_dirs $(LIB_PATH)\n\n\n"
".PHONY: build\n"
"build:  create_dirs $(LIB_PATH)\n\n\n"
".PHONY: check\n"
"check: $(TESTS)\n\n\n"
".PHONY: clean\n"
"clean:\n"
"\t-cd $(TEMP) ; [ -d $(LIBNAM) ] && rm -fr $(LIBNAM)\n\n\n"
".PHONY: create_dirs\n"
"create_dirs:\n"
"\t[ ! -d $(TEST_OBJ) ] && mkdir -p $(TEST_OBJ)\n"
"\t[ ! -d $(TEST_BIN) ] && mkdir -p $(TEST_BIN)\n\n\n"
".PHONY: install\n"
"install:\n"
"\t-cd $(INSTALL_BASE) ; [ -d $(LIBNAM) ] && rm -fr $(LIBNAM)\n"
"\t-cd $(INSTALL_BASE) ; [ ! -d $(LIBNAM)/include ] && mkdir -p $(LIBNAM)/include/$(SYS)\n"
"\tcp $(LIB_PATH) $(INSTALL_DIR)/$(LIBNAM).a\n"
"\tcp src/*.h $(INSTALL_DIR)/include/\n"
"\tif [ -d src/$(SYS) ]; then \\\n"
"\t\tcp src/$(SYS)/*.h $(INSTALL_DIR)/include/$(SYS)/; \\\n"
"\tfi\n\n\n"
".PHONY: test\n"
"test: $(TESTS)\n\n\n"
;


// pGoodJsonB needs to match libJson02.txt in tests subdirectory.
static
const
char            *pGoodJsonB =
"{\n"
    "\"library\":{\n"
        "\"name\":\"Cmn\"\n"
    "}\n,"
    "\"objects\": [\n"
        "{name:\"AStr\", \"json\":true},\n"
        "{name:\"appl\"},\n"
        "{name:\"Xyzzy\", os:[\"win32\"]}\n"            // Should not be generated!
    "],\n"
    "\"routines\": [\n"
            "{name:\"dllist\", \"os\":[\"win32\"]},\n"  // Should not be generated!
            "{name:\"str\", \"arch\":[\"x86\"]},\n"     // Should not be generated!
    "]\n"
"}\n";
const
char            *pOutputB =
".DEFAULT_GOAL := all\n"
"SHELL=/bin/sh\n\n"
"LIBNAM=libCmn\n"
"SYS=macos64\n"
"TEMP=/tmp\n"
"BASE_OBJ = $(TEMP)/$(LIBNAM)\n"
"SRCDIR = ./src\n"
"TEST_SRC = ./tests\n"
"INSTALL_BASE = $(HOME)/Support/lib/$(SYS)\n"
"LIB_BASE = $(HOME)/Support/lib/$(SYS)\n\n"

"CFLAGS += -g -Werror -I$(SRCDIR)\n"
"ifdef  NDEBUG\n"
"CFLAGS += -DNDEBUG\n"
"else   #DEBUG\n"
"CFLAGS += -D_DEBUG\n"
"endif  #NDEBUG\n"
"CFLAGS += -D__MACOS64_ENV__\n"
"CFLAGS_LIBS = \n"
"CFLAGS_TEST = -I$(TEST_SRC) $(CFLAGS_LIBS) -lcurses -lsqlite3\n\n"

"INSTALL_DIR = $(INSTALL_BASE)/$(LIBNAM)\n"
"LIBOBJ = $(BASE_OBJ)/$(SYS)\n"
"ifdef  NDEBUG\n"
"LIB_FILENAME=$(LIBNAM)R.a\n"
"OBJDIR = $(LIBOBJ)/o/r\n"
"else   #DEBUG\n"
"LIB_FILENAME=$(LIBNAM)D.a\n"
"OBJDIR = $(LIBOBJ)/o/d\n"
"endif  #NDEBUG\n"
"TEST_OBJ = $(OBJDIR)/obj\n"
"TEST_BIN = $(OBJDIR)/bin\n"
"LIB_PATH = $(LIBOBJ)/$(LIB_FILENAME)\n\n"

".SUFFIXES:\n"
".SUFFIXES: .asm .c .cpp .o\n\n"

"OBJS =\n\n"
"TESTS =\n\n\n"

"OBJS += $(OBJDIR)/AStr.o\n\n"
"$(OBJDIR)/AStr.o: $(SRCDIR)/AStr.c $(SRCDIR)/AStr.h $(SRCDIR)/AStr_internal.h \n"
"\t$(CC) $(CFLAGS) -c -o $(OBJDIR)/$(@F) -I$(SRCDIR) $<\n\n"
"OBJS += $(OBJDIR)/AStr_json.o\n\n"
"$(OBJDIR)/AStr_json.o: $(SRCDIR)/AStr_json.c $(SRCDIR)/AStr.h $(SRCDIR)/AStr_internal.h \n"
"\t$(CC) $(CFLAGS) -c -o $(OBJDIR)/$(@F) -I$(SRCDIR) $<\n\n"
"OBJS += $(OBJDIR)/AStr_object.o\n\n"
"$(OBJDIR)/AStr_object.o: $(SRCDIR)/AStr_object.c $(SRCDIR)/AStr.h $(SRCDIR)/AStr_internal.h \n"
"\t$(CC) $(CFLAGS) -c -o $(OBJDIR)/$(@F) -I$(SRCDIR) $<\n\n"

"OBJS += $(OBJDIR)/appl.o\n\n"
"$(OBJDIR)/appl.o: $(SRCDIR)/appl.c $(SRCDIR)/appl.h $(SRCDIR)/appl_internal.h \n"
"\t$(CC) $(CFLAGS) -c -o $(OBJDIR)/$(@F) -I$(SRCDIR) $<\n\n"
"OBJS += $(OBJDIR)/appl_object.o\n\n"
"$(OBJDIR)/appl_object.o: $(SRCDIR)/appl_object.c $(SRCDIR)/appl.h $(SRCDIR)/appl_internal.h \n"
"\t$(CC) $(CFLAGS) -c -o $(OBJDIR)/$(@F) -I$(SRCDIR) $<\n\n"

"TESTS += AStr_test\n\n"
"AStr_test: $(TEST_SRC)/AStr_test.c $(SRCDIR)/AStr.h $(SRCDIR)/AStr_internal.h \n"
"\t$(CC) $(CFLAGS) $(CFLAGS_TEST) -o $(TEST_BIN)/$(@F) $(OBJS) -I$(TEST_SRC) -I$(SRCDIR) $<\n"
"\t$(TEST_BIN)/$(@F)\n\n"
"TESTS += appl_test\n\n"
"appl_test: $(TEST_SRC)/appl_test.c $(SRCDIR)/appl.h $(SRCDIR)/appl_internal.h \n"
"\t$(CC) $(CFLAGS) $(CFLAGS_TEST) -o $(TEST_BIN)/$(@F) $(OBJS) -I$(TEST_SRC) -I$(SRCDIR) $<\n"
"\t$(TEST_BIN)/$(@F)\n\n"

"\n\n$(LIB_PATH):  $(OBJS)\n"
"\t-cd $(LIBOBJ) ; [ -d $(LIB_FILENAME) ] && rm $(LIB_FILENAME)\n"
"\tar rc $(LIB_PATH) $(OBJS)\n\n\n"
".PHONY: all\n"
"all:  clean create_dirs $(LIB_PATH)\n\n\n"
".PHONY: build\n"
"build:  create_dirs $(LIB_PATH)\n\n\n"
".PHONY: check\n"
"check: $(TESTS)\n\n\n"
".PHONY: clean\n"
"clean:\n"
"\t-cd $(TEMP) ; [ -d $(LIBNAM) ] && rm -fr $(LIBNAM)\n\n\n"
".PHONY: create_dirs\n"
"create_dirs:\n"
"\t[ ! -d $(TEST_OBJ) ] && mkdir -p $(TEST_OBJ)\n"
"\t[ ! -d $(TEST_BIN) ] && mkdir -p $(TEST_BIN)\n\n\n"
".PHONY: install\n"
"install:\n"
"\t-cd $(INSTALL_BASE) ; [ -d $(LIBNAM) ] && rm -fr $(LIBNAM)\n"
"\t-cd $(INSTALL_BASE) ; [ ! -d $(LIBNAM)/include ] && mkdir -p $(LIBNAM)/include/$(SYS)\n"
"\tcp $(LIB_PATH) $(INSTALL_DIR)/$(LIBNAM).a\n"
"\tcp src/*.h $(INSTALL_DIR)/include/\n"
"\tif [ -d src/$(SYS) ]; then \\\n"
"\t\tcp src/$(SYS)/*.h $(INSTALL_DIR)/include/$(SYS)/; \\\n"
"\tfi\n\n\n"
".PHONY: test\n"
"test: $(TESTS)\n\n\n"
;


static
const
char            *pGoodJsonC =
"{\n"
    "\"program\":{\n"
        "\"name\":\"genMake\",\n"
        "\"deps\":\"Cmn\",\n"
        "\"hdrs\":\"genMake.h\",\n"
    "}\n,"
    "\"objects\": [\n"
        "{name:\"NodeBase\", \"json\":true},\n"
        "{name:\"NodeLib\"},\n"
        "{name:\"Xyzzy\", os:[\"win32\"]}\n"            // Should not be generated!
    "],\n"
    "\"routines\": [\n"
            "{name:\"dllist\", \"os\":[\"win32\"]},\n"  // Should not be generated!
            "{name:\"str\", \"arch\":[\"x86\"]},\n"     // Should not be generated!
    "]\n"
"}\n";
const
char            *pOutputC =
".DEFAULT_GOAL := all\n"
"SHELL=/bin/sh\n\n"
"PGMNAM=genMake\n"
"SYS=macos64\n"
"TEMP=/tmp\n"
"BASE_OBJ = $(TEMP)/$(PGMNAM)\n"
"SRCDIR = ./src\n"
"TEST_SRC = ./tests\n"
"INSTALL_BASE = $(HOME)/Support/bin\n"
"LIB_BASE = $(HOME)/Support/lib/$(SYS)\n\n"

"CFLAGS += -g -Werror -I$(SRCDIR)\n"
"ifdef  NDEBUG\n"
"CFLAGS += -DNDEBUG\n"
"else   #DEBUG\n"
"CFLAGS += -D_DEBUG\n"
"endif  #NDEBUG\n"
"CFLAGS += -D__MACOS64_ENV__\n"
"CFLAGS_LIBS = \n"
"# libCmn\n"
"LIBCMN_BASE = $(LIB_BASE)/libCmn\n"
"CFLAGS += -I$(LIBCMN_BASE)/include\n"
"CFLAGS_LIBS += -lCmn -L$(LIBCMN_BASE)\n"
"CFLAGS_TEST = -I$(TEST_SRC) $(CFLAGS_LIBS) -lcurses -lsqlite3\n\n"

"LIBOBJ = $(BASE_OBJ)/$(SYS)\n"
"ifdef  NDEBUG\n"
"LIB_FILENAME=$(PGMNAM)R.a\n"
"OBJDIR = $(LIBOBJ)/o/r\n"
"else   #DEBUG\n"
"LIB_FILENAME=$(PGMNAM)D.a\n"
"OBJDIR = $(LIBOBJ)/o/d\n"
"endif  #NDEBUG\n"
"TEST_OBJ = $(OBJDIR)/obj\n"
"TEST_BIN = $(OBJDIR)/bin\n"
"LIB_PATH = $(LIBOBJ)/$(LIB_FILENAME)\n\n"

".SUFFIXES:\n"
".SUFFIXES: .asm .c .cpp .o\n\n"

"OBJS =\n\n"
"TESTS =\n\n\n"

"OBJS += $(OBJDIR)/NodeBase.o\n\n"
"$(OBJDIR)/NodeBase.o: $(SRCDIR)/NodeBase.c $(SRCDIR)/NodeBase.h $(SRCDIR)/NodeBase_internal.h $(SRCDIR)/genMake.h $(LIBCMN_BASE)/include/cmn_defs.h \n"
"\t$(CC) $(CFLAGS) -c -o $(OBJDIR)/$(@F) -I$(SRCDIR) $<\n\n"
"OBJS += $(OBJDIR)/NodeBase_json.o\n\n"
"$(OBJDIR)/NodeBase_json.o: $(SRCDIR)/NodeBase_json.c $(SRCDIR)/NodeBase.h $(SRCDIR)/NodeBase_internal.h $(SRCDIR)/genMake.h $(LIBCMN_BASE)/include/cmn_defs.h \n"
"\t$(CC) $(CFLAGS) -c -o $(OBJDIR)/$(@F) -I$(SRCDIR) $<\n\n"
"OBJS += $(OBJDIR)/NodeBase_object.o\n\n"
"$(OBJDIR)/NodeBase_object.o: $(SRCDIR)/NodeBase_object.c $(SRCDIR)/NodeBase.h $(SRCDIR)/NodeBase_internal.h $(SRCDIR)/genMake.h $(LIBCMN_BASE)/include/cmn_defs.h \n"
"\t$(CC) $(CFLAGS) -c -o $(OBJDIR)/$(@F) -I$(SRCDIR) $<\n\n"

"OBJS += $(OBJDIR)/NodeLib.o\n\n"
"$(OBJDIR)/NodeLib.o: $(SRCDIR)/NodeLib.c $(SRCDIR)/NodeLib.h $(SRCDIR)/NodeLib_internal.h $(SRCDIR)/genMake.h $(LIBCMN_BASE)/include/cmn_defs.h \n"
"\t$(CC) $(CFLAGS) -c -o $(OBJDIR)/$(@F) -I$(SRCDIR) $<\n\n"
"OBJS += $(OBJDIR)/NodeLib_object.o\n\n"
"$(OBJDIR)/NodeLib_object.o: $(SRCDIR)/NodeLib_object.c $(SRCDIR)/NodeLib.h $(SRCDIR)/NodeLib_internal.h $(SRCDIR)/genMake.h $(LIBCMN_BASE)/include/cmn_defs.h \n"
"\t$(CC) $(CFLAGS) -c -o $(OBJDIR)/$(@F) -I$(SRCDIR) $<\n\n"

"TESTS += NodeBase_test\n\n"
"NodeBase_test: $(TEST_SRC)/NodeBase_test.c $(SRCDIR)/NodeBase.h $(SRCDIR)/NodeBase_internal.h $(SRCDIR)/genMake.h $(LIBCMN_BASE)/include/cmn_defs.h \n"
"\t$(CC) $(CFLAGS) $(CFLAGS_TEST) -o $(TEST_BIN)/$(@F) $(OBJS) -I$(TEST_SRC) -I$(SRCDIR) $<\n"
"\t$(TEST_BIN)/$(@F)\n\n"
"TESTS += NodeLib_test\n\n"
"NodeLib_test: $(TEST_SRC)/NodeLib_test.c $(SRCDIR)/NodeLib.h $(SRCDIR)/NodeLib_internal.h $(SRCDIR)/genMake.h $(LIBCMN_BASE)/include/cmn_defs.h \n"
"\t$(CC) $(CFLAGS) $(CFLAGS_TEST) -o $(TEST_BIN)/$(@F) $(OBJS) -I$(TEST_SRC) -I$(SRCDIR) $<\n"
"\t$(TEST_BIN)/$(@F)\n\n"
".PHONY: all\n"
"all:  clean create_dirs link\n\n\n"
".PHONY: build\n"
"build:  create_dirs link\n\n\n"
".PHONY: check\n"
"check: $(TESTS)\n\n\n"
".PHONY: clean\n"
"clean:\n"
"\t-cd $(TEMP) ; [ -d $(PGMNAM) ] && rm -fr $(PGMNAM)\n\n\n"
".PHONY: create_dirs\n"
"create_dirs:\n"
"\t[ ! -d $(TEST_OBJ) ] && mkdir -p $(TEST_OBJ)\n"
"\t[ ! -d $(TEST_BIN) ] && mkdir -p $(TEST_BIN)\n\n\n"
".PHONY: install\n"
"install:\n"
"\t-cd $(INSTALL_BASE) ; [ -d $(PGMNAM) ] && rm -fr $(PGMNAM)\n"
"\tcp $(OBJDIR)/$(PGMNAM) $(INSTALL_BASE)/$(PGMNAM)\n\n\n"
".PHONY: link\n"
"link: $(OBJS) $(SRCDIR)/mainProgram.c\n"
"\tCC -o $(OBJDIR)/$(PGMNAM) $(CFLAGS) $(CFLAGS_LIBS) $^\n\n\n"
".PHONY: test\n"
"test: $(TESTS)\n\n\n"
;



int         setUp(
    const
    char        *pTestName
)
{
    mem_Init( );
    trace_Shared( ); 
    // Put setup code here. This method is called before the invocation of each
    // test method in the class.
    
    return 1; 
}


int         tearDown(
    const
    char        *pTestName
)
{
    // Put teardown code here. This method is called after the invocation of each
    // test method in the class.

    
    szTbl_SharedReset( );
    SrcErrors_SharedReset( );
    JsonIn_RegisterReset();
    trace_SharedReset( );
    if (mem_Dump( ) ) {
        fprintf(
                stderr,
                "\x1b[1m"
                "\x1b[31m"
                "ERROR: "
                "\x1b[0m"
                "Leaked memory areas were found!\n"
                );
        exitCode = 4;
        return 0;
    }

    mem_Release( );
    
    return 1; 
}






int         test_Main_OpenClose(
    const
    char        *pTestName
)
{
    MAIN_DATA	*pObj = OBJ_NIL;
   
    fprintf(stderr, "Performing: %s\n", pTestName);
    
    pObj = Main_New( );
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    if (pObj) {

        // Test something.

        obj_Release(pObj);
        pObj = OBJ_NIL;
    }

    fprintf(stderr, "...%s completed.\n\n", pTestName);
    return 1;
}



int         test_Main_Generation01(
    const
    char        *pTestName
)
{
    ERESULT         eRc;
    MAIN_DATA       *pObj = OBJ_NIL;
    ASTR_DATA       *pStr = OBJ_NIL;
    //ASTR_DATA       *pWrk = OBJ_NIL;
    int             iRc;
    int             offset = 0;
    bool            fDump = true;
    NODELIB_DATA    *pLib = OBJ_NIL;
    //NODELIB_DATA    *pPgm = OBJ_NIL;
    uint32_t        i;
    const
    char            *pChr;
    
    fprintf(stderr, "Performing: %s\n", pTestName);
    
    pObj = Main_New();
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    if (pObj) {
        
        pObj->pOutput = TextOut_NewAStr();
        TINYTEST_FALSE( (OBJ_NIL == pObj->pOutput) );

        //appl_setDebug((APPL_DATA *)pObj, true);
        eRc = Main_ParseInputStr(pObj, pGoodJsonA);
        TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );
        TINYTEST_FALSE( (OBJ_NIL == pObj->pParser) );

        pLib = SrcParse_getLib(pObj->pParser);
        TINYTEST_FALSE( (OBJ_NIL == pLib) );

        pObj->osType = OSTYPE_MACOS64;
        eRc = Main_SetupOsArch(pObj);
        TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );
        eRc = Main_GenMakefile(pObj);
        TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );
        
        if (fDump) {
            pStr = Main_getStr(pObj);
            TINYTEST_FALSE( (OBJ_NIL == pStr) );
            fprintf(stderr, "GEN_BEGIN:\n%sGEN_END:\n\n\n", AStr_getData(pStr));
        }
        
        // Skip first 3 lines of output.
        pChr = AStr_getData(Main_getStr(pObj));
        for (i=0; i<3; i++) {
            while (*pChr && (*pChr != '\n')) {
                pChr++;
            }
            pChr++;
        }
        
        iRc = str_CompareSpcl(pChr, pOutputA, &offset);
        fprintf(stderr, "\tiRc=%d  offset=%04X\n", iRc, offset);
        TINYTEST_TRUE( (0 == iRc) );
        
        obj_Release(pObj);
        pObj = OBJ_NIL;
    }
    
    fprintf(stderr, "...%s completed.\n\n\n", pTestName);
    return 1;
}



int         test_Main_Generation02(
    const
    char        *pTestName
)
{
    ERESULT         eRc;
    MAIN_DATA       *pObj = OBJ_NIL;
    ASTR_DATA       *pStr = OBJ_NIL;
    //ASTR_DATA       *pWrk = OBJ_NIL;
    int             iRc;
    int             offset = 0;
    bool            fDump = false;
    NODELIB_DATA    *pLib = OBJ_NIL;
    //NODELIB_DATA    *pPgm = OBJ_NIL;
    uint32_t        i;
    const
    char            *pChr;
    
    fprintf(stderr, "Performing: %s\n", pTestName);
    
    pObj = Main_New();
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    if (pObj) {
        
        pObj->pOutput = TextOut_NewAStr();
        TINYTEST_FALSE( (OBJ_NIL == pObj->pOutput) );

        //appl_setDebug((APPL_DATA *)pObj, true);
        eRc = Main_ParseInputStr(pObj, pGoodJsonB);
        TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );
        TINYTEST_FALSE( (OBJ_NIL == pObj->pParser) );

        pLib = SrcParse_getLib(pObj->pParser);
        TINYTEST_FALSE( (OBJ_NIL == pLib) );

        pObj->osType = OSTYPE_MACOS64;
        eRc = Main_SetupOsArch(pObj);
        TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );
        eRc = Main_GenMakefile(pObj);
        TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );
        
        if (fDump) {
            pStr = Main_getStr(pObj);
            TINYTEST_FALSE( (OBJ_NIL == pStr) );
            fprintf(stderr, "GEN_BEGIN:\n%sGEN_END:\n\n\n", AStr_getData(pStr));
        }
        
        // Skip first 3 lines of output.
        pChr = AStr_getData(Main_getStr(pObj));
        for (i=0; i<3; i++) {
            while (*pChr && (*pChr != '\n')) {
                pChr++;
            }
            pChr++;
        }
        
        iRc = str_CompareSpcl(pChr, pOutputB, &offset);
        fprintf(stderr, "\tiRc=%d  offset=%04X\n", iRc, offset);
        TINYTEST_TRUE( (0 == iRc) );
        
        obj_Release(pObj);
        pObj = OBJ_NIL;
    }
    
    fprintf(stderr, "...%s completed.\n\n\n", pTestName);
    return 1;
}



int         test_Main_Generation03(
    const
    char        *pTestName
)
{
    ERESULT         eRc;
    MAIN_DATA       *pObj = OBJ_NIL;
    ASTR_DATA       *pStr = OBJ_NIL;
    //ASTR_DATA       *pWrk = OBJ_NIL;
    int             iRc;
    int             offset = 0;
    bool            fDumpNodes = false;
    bool            fDump = true;
    //NODELIB_DATA    *pLib = OBJ_NIL;
    NODEPGM_DATA    *pPgm = OBJ_NIL;
    uint32_t        i;
    const
    char            *pChr;
    
    fprintf(stderr, "Performing: %s\n", pTestName);
    
    pObj = Main_New();
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    if (pObj) {
        
        pObj->pOutput = TextOut_NewAStr();
        TINYTEST_FALSE( (OBJ_NIL == pObj->pOutput) );

        //appl_setDebug((APPL_DATA *)pObj, true);
        eRc = Main_ParseInputStr(pObj, pGoodJsonC);
        TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );
        TINYTEST_FALSE( (OBJ_NIL == pObj->pParser) );

        pPgm = SrcParse_getPgm(pObj->pParser);
        TINYTEST_FALSE( (OBJ_NIL == pPgm) );

        if (fDump) {
            ASTR_DATA       *pWrk = OBJ_NIL;
            pWrk = SrcParse_ToString(pObj->pParser);
            if (pWrk) {
                fprintf(stderr, "\n%s\n\n\n", AStr_getData(pWrk));
                obj_Release(pWrk);
                pWrk = OBJ_NIL;
            }
        }

        pObj->osType = OSTYPE_MACOS64;
        eRc = Main_SetupOsArch(pObj);
        TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );
        eRc = Main_GenMakefile(pObj);
        TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );
        
        if (fDump) {
            ASTR_DATA       *pWrk = OBJ_NIL;
            pWrk = ExpandNodes_ToString(pObj->pExpand);
            if (pWrk) {
                fprintf(stderr, "\n%s\n\n\n", AStr_getData(pWrk));
                obj_Release(pWrk);
                pWrk = OBJ_NIL;
            }
        }
        
        if (fDump) {
            pStr = Main_getStr(pObj);
            TINYTEST_FALSE( (OBJ_NIL == pStr) );
            fprintf(stderr, "GEN_BEGIN:\n%sGEN_END:\n\n\n", AStr_getData(pStr));
        }
        
        // Skip first 3 lines of output.
        pChr = AStr_getData(Main_getStr(pObj));
        for (i=0; i<3; i++) {
            while (*pChr && (*pChr != '\n')) {
                pChr++;
            }
            pChr++;
        }
        
        iRc = str_CompareSpcl(pChr, pOutputC, &offset);
        fprintf(stderr, "\tiRc=%d  offset=%04X\n", iRc, offset);
        TINYTEST_TRUE( (0 == iRc) );
        
        obj_Release(pObj);
        pObj = OBJ_NIL;
    }
    
    fprintf(stderr, "...%s completed.\n\n\n", pTestName);
    return 1;
}



int         test_Main_CheckInputFilePath01(
    const
    char        *pTestName
)
{
    ERESULT         eRc;
    MAIN_DATA       *pObj = OBJ_NIL;
    ASTR_DATA       *pStr = OBJ_NIL;
    PATH_DATA       *pPath = OBJ_NIL;
    PATH_DATA       *pPathCheck = OBJ_NIL;
    static
    const
    char            *pGoodPathA = "~/git/libCmn/objects.json.txt";
    const
    char            *pOutputA = "~/git/libCmn/objects.json.txt";
    int             iRc;
    int             offset = 0;
    
    
    fprintf(stderr, "Performing: %s\n", pTestName);
    
    pObj = Main_New();
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    if (pObj) {
        
        pStr = AStr_NewA(pGoodPathA);
        TINYTEST_FALSE( (OBJ_NIL == pStr) );

        pObj->osType = OSTYPE_MACOS64;
        eRc = Main_SetupOsArch(pObj);
        TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );

        pPath = Main_CheckInputPath(pObj, pStr);
        TINYTEST_FALSE( (OBJ_NIL == pPath) );

        pPathCheck = Path_NewA(pOutputA);
        TINYTEST_FALSE( (OBJ_NIL == pPathCheck) );
        eRc = Path_Clean(pPathCheck);
        TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );

        iRc = str_CompareSpcl(Path_getData(pPath), Path_getData(pPathCheck), &offset);
        fprintf(stderr, "\tiRc=%d  offset=%04X\n", iRc, offset);
        TINYTEST_TRUE( (0 == iRc) );
        
        obj_Release(pPathCheck);
        pPathCheck = OBJ_NIL;
        obj_Release(pPath);
        pPath = OBJ_NIL;
        obj_Release(pStr);
        pStr = OBJ_NIL;
        obj_Release(pObj);
        pObj = OBJ_NIL;
    }
    
    fprintf(stderr, "...%s completed.\n\n\n", pTestName);
    return 1;
}



int         test_Main_CreateOutputFilePath01(
    const
    char        *pTestName
)
{
    ERESULT         eRc;
    MAIN_DATA       *pObj = OBJ_NIL;
    ASTR_DATA       *pStr = OBJ_NIL;
    PATH_DATA       *pPath = OBJ_NIL;
    PATH_DATA       *pPathCheck = OBJ_NIL;
    static
    const
    char            *pGoodPathA = "~/git/libCmn/objects.json.txt";
    const
    char            *pOutputA = "~/git/libCmn/Makefile.macos64.txt";
    int             iRc;
    int             offset = 0;
    
    
    fprintf(stderr, "Performing: %s\n", pTestName);
    
    pObj = Main_New();
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    if (pObj) {
        
        pStr = AStr_NewA(pGoodPathA);
        TINYTEST_FALSE( (OBJ_NIL == pStr) );

        pObj->osType = OSTYPE_MACOS64;
        eRc = Main_SetupOsArch(pObj);
        TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );

        pPath = Main_CreateOutputPath(pObj, pStr, pObj->pOsName);
        TINYTEST_FALSE( (OBJ_NIL == pPath) );

        pPathCheck = Path_NewA(pOutputA);
        TINYTEST_FALSE( (OBJ_NIL == pPathCheck) );
        eRc = Path_Clean(pPathCheck);
        TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );

        iRc = str_CompareSpcl(Path_getData(pPath), Path_getData(pPathCheck), &offset);
        fprintf(stderr, "\tiRc=%d  offset=%04X\n", iRc, offset);
        TINYTEST_TRUE( (0 == iRc) );
        
        obj_Release(pPathCheck);
        pPathCheck = OBJ_NIL;
        obj_Release(pPath);
        pPath = OBJ_NIL;
        obj_Release(pStr);
        pStr = OBJ_NIL;
        obj_Release(pObj);
        pObj = OBJ_NIL;
    }
    
    fprintf(stderr, "...%s completed.\n\n\n", pTestName);
    return 1;
}



int         test_Main_Generation04(
    const
    char        *pTestName
)
{
    ERESULT         eRc;
    MAIN_DATA       *pObj = OBJ_NIL;
    ASTR_DATA       *pStr = OBJ_NIL;
    PATH_DATA       *pInputPath = OBJ_NIL;
    PATH_DATA       *pOutputPath = OBJ_NIL;
    //ASTR_DATA       *pWrk = OBJ_NIL;
    int             iRc;
    int             offset = 0;
    bool            fDump = false;
    uint32_t        i;
    const
    char            *pChr;
    static
    const
    char            *pInputPathA = "~/git/libCmn/programs/genMake/tests/libJson01.txt";
    
    fprintf(stderr, "Performing: %s\n", pTestName);
    
    pObj = Main_New();
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    if (pObj) {
        
        pInputPath = Path_NewA(pInputPathA);
        TINYTEST_FALSE( (OBJ_NIL == pInputPath) );

        pObj->osType = OSTYPE_MACOS64;
        eRc = Main_SetupOsArch(pObj);
        TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );
        eRc = Main_ProcessArg(pObj, Path_getAStr(pInputPath));
        TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );
        
        pOutputPath =   Main_CreateOutputPath(
                                            pObj,
                                            Path_getAStr(pInputPath),
                                            pObj->pOsName
                        );
        TINYTEST_FALSE( (OBJ_NIL == pOutputPath) );
        
        pStr = AStr_NewFromUtf8File(pOutputPath);
        TINYTEST_FALSE( (OBJ_NIL == pStr) );
        if (fDump) {
            fprintf(stderr, "GEN_BEGIN:\n%sGEN_END:\n\n\n", AStr_getData(pStr));
        }
        
        // Skip first 3 lines of output.
        pChr = AStr_getData(pStr);
        for (i=0; i<3; i++) {
            while (*pChr && (*pChr != '\n')) {
                pChr++;
            }
            pChr++;
        }
        
        iRc = str_CompareSpcl(pChr, pOutputA, &offset);
        fprintf(stderr, "\tiRc=%d  offset=%04X\n", iRc, offset);
        TINYTEST_TRUE( (0 == iRc) );
        
        eRc = Path_Delete(pOutputPath);
        TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );

        obj_Release(pOutputPath);
        pOutputPath = OBJ_NIL;
        obj_Release(pStr);
        pStr = OBJ_NIL;
        obj_Release(pInputPath);
        pInputPath = OBJ_NIL;
        obj_Release(pObj);
        pObj = OBJ_NIL;
    }
    
    fprintf(stderr, "...%s completed.\n\n\n", pTestName);
    return 1;
}



int         test_Main_Generation05(
    const
    char        *pTestName
)
{
    ERESULT         eRc;
    MAIN_DATA       *pObj = OBJ_NIL;
    ASTR_DATA       *pStr = OBJ_NIL;
    PATH_DATA       *pInputPath = OBJ_NIL;
    PATH_DATA       *pOutputPath = OBJ_NIL;
    int             iRc;
    int             offset = 0;
    bool            fDump = false;
    uint32_t        i;
    const
    char            *pChr;
    static
    const
    char            *pInputPathA = "~/git/libCmn/programs/genMake/tests/libJson02.txt";

    fprintf(stderr, "Performing: %s\n", pTestName);
    
    pObj = Main_New();
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    if (pObj) {
        
        pInputPath = Path_NewA(pInputPathA);
        TINYTEST_FALSE( (OBJ_NIL == pInputPath) );

        pObj->osType = OSTYPE_MACOS64;
        eRc = Main_SetupOsArch(pObj);
        TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );
        eRc = Main_ProcessArg(pObj, Path_getAStr(pInputPath));
        TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );
        
        pOutputPath =   Main_CreateOutputPath(
                                            pObj,
                                            Path_getAStr(pInputPath),
                                            pObj->pOsName
                        );
        TINYTEST_FALSE( (OBJ_NIL == pOutputPath) );
        
        pStr = AStr_NewFromUtf8File(pOutputPath);
        TINYTEST_FALSE( (OBJ_NIL == pStr) );
        if (fDump) {
            fprintf(stderr, "GEN_BEGIN:\n%sGEN_END:\n\n\n", AStr_getData(pStr));
        }
        
        // Skip first 3 lines of output.
        pChr = AStr_getData(pStr);
        for (i=0; i<3; i++) {
            while (*pChr && (*pChr != '\n')) {
                pChr++;
            }
            pChr++;
        }
        
        iRc = str_CompareSpcl(pChr, pOutputB, &offset);
        fprintf(stderr, "\tiRc=%d  offset=%04X\n", iRc, offset);
        TINYTEST_TRUE( (0 == iRc) );
        
        eRc = Path_Delete(pOutputPath);
        TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );

        obj_Release(pOutputPath);
        pOutputPath = OBJ_NIL;
        obj_Release(pStr);
        pStr = OBJ_NIL;
        obj_Release(pInputPath);
        pInputPath = OBJ_NIL;
        obj_Release(pObj);
        pObj = OBJ_NIL;
    }
    
    fprintf(stderr, "...%s completed.\n\n\n", pTestName);
    return 1;
}



int         test_Main_Generation06(
    const
    char        *pTestName
)
{
    ERESULT         eRc;
    MAIN_DATA       *pObj = OBJ_NIL;
    ASTR_DATA       *pStr = OBJ_NIL;
    PATH_DATA       *pInputPath = OBJ_NIL;
    PATH_DATA       *pOutputPath = OBJ_NIL;
    int             iRc;
    int             offset = 0;
    bool            fDump = true;
    uint32_t        i;
    const
    char            *pChr;
    static
    const
    char            *pInputPathA = "~/git/libCmn/objects.json.txt";

    fprintf(stderr, "Performing: %s\n", pTestName);
    
    pObj = Main_New();
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    if (pObj) {
        
        pInputPath = Path_NewA(pInputPathA);
        TINYTEST_FALSE( (OBJ_NIL == pInputPath) );

        pObj->osType = OSTYPE_MACOS64;
        eRc = Main_SetupOsArch(pObj);
        TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );
        eRc = Main_ProcessArg(pObj, Path_getAStr(pInputPath));
        TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );
        
        pOutputPath =   Main_CreateOutputPath(
                                            pObj,
                                            Path_getAStr(pInputPath),
                                            pObj->pOsName
                        );
        TINYTEST_FALSE( (OBJ_NIL == pOutputPath) );
        
        pStr = AStr_NewFromUtf8File(pOutputPath);
        TINYTEST_FALSE( (OBJ_NIL == pStr) );
        if (fDump) {
            fprintf(stderr, "GEN_BEGIN:\n%sGEN_END:\n\n\n", AStr_getData(pStr));
        }
        
#ifdef XYZZY
        // Skip first 3 lines of output.
        pChr = AStr_getData(pStr);
        for (i=0; i<3; i++) {
            while (*pChr && (*pChr != '\n')) {
                pChr++;
            }
            pChr++;
        }
        
        iRc = str_CompareSpcl(pChr, pOutputB, &offset);
        fprintf(stderr, "\tiRc=%d  offset=%04X\n", iRc, offset);
        TINYTEST_TRUE( (0 == iRc) );
#endif
        
        eRc = Path_Delete(pOutputPath);
        TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );

        obj_Release(pOutputPath);
        pOutputPath = OBJ_NIL;
        obj_Release(pStr);
        pStr = OBJ_NIL;
        obj_Release(pInputPath);
        pInputPath = OBJ_NIL;
        obj_Release(pObj);
        pObj = OBJ_NIL;
    }
    
    fprintf(stderr, "...%s completed.\n\n\n", pTestName);
    return 1;
}




TINYTEST_START_SUITE(test_Main);
    TINYTEST_ADD_TEST(test_Main_Generation06,setUp,tearDown);
    TINYTEST_ADD_TEST(test_Main_Generation05,setUp,tearDown);
    TINYTEST_ADD_TEST(test_Main_Generation04,setUp,tearDown);
    TINYTEST_ADD_TEST(test_Main_Generation03,setUp,tearDown);
    TINYTEST_ADD_TEST(test_Main_CreateOutputFilePath01,setUp,tearDown);
    TINYTEST_ADD_TEST(test_Main_CheckInputFilePath01,setUp,tearDown);
    TINYTEST_ADD_TEST(test_Main_Generation02,setUp,tearDown);
    TINYTEST_ADD_TEST(test_Main_Generation01,setUp,tearDown);
    TINYTEST_ADD_TEST(test_Main_OpenClose,setUp,tearDown);
TINYTEST_END_SUITE();

TINYTEST_MAIN_SINGLE_SUITE(test_Main);





