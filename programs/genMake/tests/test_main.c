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
#include    <srcErrors.h>
#include    <trace.h>
#include    <main_internal.h>



#include    <test_data.c>




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
    srcErrors_SharedReset( );
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






int         test_main_OpenClose(
    const
    char        *pTestName
)
{
    MAIN_DATA	*pObj = OBJ_NIL;
   
    fprintf(stderr, "Performing: %s\n", pTestName);
    
    pObj = main_Alloc( );
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    pObj = main_Init( pObj );
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    if (pObj) {

        // Test something.

        obj_Release(pObj);
        pObj = OBJ_NIL;
    }

    fprintf(stderr, "...%s completed.\n\n", pTestName);
    return 1;
}



#ifdef XYZZY
int         test_main_MakeFile01(
    const
    char        *pTestName
)
{
    ERESULT         eRc;
    MAIN_DATA       *pObj = OBJ_NIL;
    ASTR_DATA       *pStr = OBJ_NIL;
    ASTR_DATA       *pWrk = OBJ_NIL;
    int             iRc;
    int             offset = 0;
    char            *pArgs[] = {
        "./makeFile01",
        "-v",
        NULL
    };
    static
    const
    char            *pGoodJsonA =
    "{\n"
        "\"library\":{\n"
            "\"name\":\"Cmn\",\n"
            "\"libDeps\":null,\n"
            "\"headers\":null,\n"
        "}\n,"
        "\"objects\": {\n"
            "\"AStr\":{\"srcDeps\":[\"libCmn.h\"], \"json\":true, \"test\":true},\n"
            "\"appl\":{\"srcDeps\":[\"libCmn.h\"], \"test\":true},\n"
        "},\n"
        "\"routines\": [\n"
            "\"dllist.c\",\n"
        "],\n"
    "}\n";
    const
    char            *pOutputA =
    "# Generated file - edits may be discarded!\n\n"
    "LIBNAM=libCmn\n"
    "SYS=macosx\n"
    "TEMP=/tmp\n"
    "BASEDIR = $(TEMP)/$(LIBNAM)\n\n"
    "CFLAGS_LIBS = \n"
    "CFLAGS += -g -Werror -Isrc -Isrc/$(SYS)\n"
    "CFLAGS += -D__MACOSX_ENV__\n\n"
    "TEST_FLGS = -Itests $(CFLAGS_LIBS) -lcurses\n\n"
    "INSTALL_BASE = $(HOME)/Support/lib/$(SYS)\n"
    "INSTALLDIR = $(INSTALL_BASE)/$(LIBNAM)\n"
    "LIBDIR = $(BASEDIR)/$(SYS)\n"
    "SRCDIR = ./src\n"
    "SRCSYSDIR = ./src/$(SYS)\n"
    "TEST_SRC = ./tests\n"
    "ifdef  NDEBUG\n"
    "CFLAGS += -DNDEBUG\n"
    "LIB_FILENAME=$(LIBNAM)R.a\n"
    "OBJDIR = $(LIBDIR)/o/r\n"
    "else   #DEBUG\n"
    "CFLAGS += -D_DEBUG \n"
    "LIB_FILENAME=$(LIBNAM)D.a\n"
    "OBJDIR = $(LIBDIR)/o/d\n"
    "endif  #NDEBUG\n"
    "TEST_OBJ = $(OBJDIR)/tests\n"
    "LIBPATH = $(LIBDIR)/$(LIB_FILENAME)\n\n"
    ".SUFFIXES:\n"
    ".SUFFIXES: .asm .c .o\n\n"
    "OBJS = \n\n"
    "TESTS = \n\n"
    "\n\n\n\n"
    "OBJS += $(OBJDIR)/AStr_object.o\n\n"
    "$(OBJDIR)/AStr_object.o: $(SRCDIR)/AStr_object.c \n"
    "\t$(CC) $(CFLAGS) -c -o $(OBJDIR)/$(@F) $< \n\n"
    "OBJS += $(OBJDIR)/AStr.o\n\n"
    "$(OBJDIR)/AStr.o: $(SRCDIR)/AStr.c $(SRCDIR)/libCmn.h \n"
    "\t$(CC) $(CFLAGS) -c -o $(OBJDIR)/$(@F) $< \n\n"
    "OBJS += $(OBJDIR)/AStr_JSON.o\n\n"
    "$(OBJDIR)/AStr_JSON.o: $(SRCDIR)/AStr_JSON.c \n"
    "\t$(CC) $(CFLAGS) -c -o $(OBJDIR)/$(@F) $< \n\n"
    "TESTS += test_AStr\n\n"
    "test_AStr: $(TEST_SRC)/test_AStr.c \n"
    "\t$(CC) $(CFLAGS) $(TEST_FLGS) -o $(TEST_OBJ)/$(@F) $(OBJS) $< \n"
    "\t$(TEST_OBJ)/$(@F)\n\n"
    "OBJS += $(OBJDIR)/appl_object.o\n\n"
    "$(OBJDIR)/appl_object.o: $(SRCDIR)/appl_object.c \n"
    "\t$(CC) $(CFLAGS) -c -o $(OBJDIR)/$(@F) $< \n\n"
    "OBJS += $(OBJDIR)/appl.o\n\n"
    "$(OBJDIR)/appl.o: $(SRCDIR)/appl.c $(SRCDIR)/libCmn.h \n"
    "\t$(CC) $(CFLAGS) -c -o $(OBJDIR)/$(@F) $< \n\n"
    "TESTS += test_appl\n\n"
    "test_appl: $(TEST_SRC)/test_appl.c \n"
    "\t$(CC) $(CFLAGS) $(TEST_FLGS) -o $(TEST_OBJ)/$(@F) $(OBJS) $< \n"
    "\t$(TEST_OBJ)/$(@F)\n\n"
    "OBJS += $(OBJDIR)/dllist.o\n\n"
    "$(OBJDIR)/dllist.o: $(SRCDIR)/dllist.c \n"
    "\t$(CC) $(CFLAGS) -c -o $(OBJDIR)/$(@F) $< \n\n"
    "\n\n\n"
    "$(LIBPATH):  $(OBJS)\n"
    "\t-cd $(LIBDIR) ; [ -d $(LIB_FILENAME) ] && rm $(LIB_FILENAME)\n"
    "\tar rc $(LIBPATH) $(OBJS)\n\n\n\n"
    ".PHONY: test\n"
    "test: $(TESTS)\n\n\n"
    ".PHONY: clean\n"
    "clean:\n"
    "\t-cd $(TEMP) ; [ -d $(LIBNAM) ] && rm -fr $(LIBNAM)\n\n\n"
    ".PHONY: install\n"
    "install:\n"
    "\t-cd $(INSTALL_BASE) ; [ -d $(LIBNAM) ] && rm -fr $(LIBNAM)\n"
    "\t-cd $(INSTALL_BASE) ; [ ! -d $(LIBNAM)/include ] && mkdir -p $(LIBNAM)/include/$(SYS)\n"
    "\tcp $(LIBPATH) $(INSTALLDIR)/$(LIBNAM).a\n"
    "\tcp src/*.h $(INSTALLDIR)/include/\n"
    "\tif [ -d src/$(SYS) ]; then \\\n"
    "\t\tcp src/$(SYS)/*.h $(INSTALLDIR)/include/$(SYS)/; \\\n"
    "\tfi\n\n\n"
    ".PHONY: create_dirs\n"
    "create_dirs:\n"
    "\t[ ! -d $(OBJDIR) ] && mkdir -p $(OBJDIR)/tests\n\n\n"
    ".PHONY: all\n"
    "all:  clean create_dirs $(LIBPATH)\n"
    "\n\n\n"
    ;
    
    
    fprintf(stderr, "Performing: %s\n", pTestName);
    
    pObj = main_NewFromArgV(2, pArgs, NULL);
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    if (pObj) {
        
        //appl_setDebug((APPL_DATA *)pObj, true);
        eRc = main_ParseInputStr(pObj, pGoodJsonA);
        TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );

        eRc = main_ParseArgsDefault(pObj);
        TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );
        
        pObj->pOutput = textOut_NewAStr();
        TINYTEST_FALSE( (OBJ_NIL == pObj->pOutput) );

        eRc = main_GenMakefile(pObj);
        TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );
        
        pStr = main_getStr(pObj);
        fprintf(stderr, "GEN_BEGIN:\n%sGEN_END:\n\n\n", AStr_getData(pStr));
        pWrk = AStr_ToDebugString(pStr, 4);
        fprintf(stderr, "%s\n\n\n", AStr_getData(pWrk));
        obj_Release(pWrk);
        pWrk = OBJ_NIL;
        iRc = str_CompareSpcl(pOutputA, AStr_getData(pStr), &offset);
        fprintf(stderr, "\tiRc=%d  offset=%04X\n", iRc, offset);
        TINYTEST_TRUE( (0 == iRc) );
        
        obj_Release(pObj);
        pObj = OBJ_NIL;
    }
    
    fprintf(stderr, "...%s completed.\n\n\n", pTestName);
    return 1;
}



int         test_main_MakeFile02(
    const
    char        *pTestName
)
{
    ERESULT     eRc;
    int         iRc;
    MAIN_DATA   *pObj = OBJ_NIL;
    ASTR_DATA   *pStr = OBJ_NIL;
    char        *pArgs[] = {
        "./makeFile01",
        "~/git/libCmn/programs/genMake/tests/goodJson01.txt",
        NULL
    };
    const
    char        *pFilepath = "~/git/libCmn/programs/"
                             "genMake/tests/Makefile.macos.txt";
    
    fprintf(stderr, "Performing: %s\n", pTestName);
    
    pObj = main_New( );
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    if (pObj) {
        
        //appl_setDebug((APPL_DATA *)pObj, true);
        eRc = main_SetupFromArgV(pObj, 2, pArgs, NULL);
        TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );
        
        iRc = main_Exec(pObj);
        TINYTEST_TRUE( (0 == iRc) );
        
        pStr = main_getStr(pObj);
        if (pStr) {
            fprintf(stderr, "GEN_BEGIN:\n%sGEN_END:\n\n\n", AStr_getData(pStr));
        }
        
        obj_Release(pObj);
        pObj = OBJ_NIL;
    }
    
    fprintf(stderr, "...%s completed.\n\n\n", pTestName);
    return 1;
}



int         test_main_MakeFile03(
    const
    char        *pTestName
)
{
    ERESULT     eRc;
    int         iRc;
    MAIN_DATA   *pObj = OBJ_NIL;
    ASTR_DATA   *pStr = OBJ_NIL;
    char        *pArgs[] = {
        "./makeFile01",
        "~/git/libCmn/programs/genMake/tests/goodJson02.txt",
        NULL
    };
    const
    char        *pFilepath = "~/git/libCmn/programs/"
                            "genMake/tests/Makefile.macos.txt";
    
    fprintf(stderr, "Performing: %s\n", pTestName);
    
    pObj = main_New( );
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    if (pObj) {
        
        //appl_setDebug((APPL_DATA *)pObj, true);
        eRc = main_SetupFromArgV(pObj, 2, pArgs, NULL);
        TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );
        
        iRc = main_Exec(pObj);
        TINYTEST_TRUE( (0 == iRc) );
        
        pStr = main_getStr(pObj);
        if (pStr) {
            fprintf(stderr, "GEN_BEGIN:\n%sGEN_END:\n\n\n", AStr_getData(pStr));
        }
        
        obj_Release(pObj);
        pObj = OBJ_NIL;
    }
    
    fprintf(stderr, "...%s completed.\n\n\n", pTestName);
    return 1;
}



int         test_main_MakeFile04(
    const
    char        *pTestName
)
{
    ERESULT     eRc;
    int         iRc;
    MAIN_DATA   *pObj = OBJ_NIL;
    ASTR_DATA   *pStr = OBJ_NIL;
    char        *pArgs[] = {
        "./makeFile01",
        "~/git/libCmn/programs/genMake/tests/program.json.txt",
        NULL
    };
    const
    char        *pFilepath = "~/git/libCmn/programs/"
                            "genMake/tests/Makefile.macos.txt";
    
    fprintf(stderr, "Performing: %s\n", pTestName);
    
    pObj = main_New( );
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    if (pObj) {
        
        //appl_setDebug((APPL_DATA *)pObj, true);
        eRc = main_SetupFromArgV(pObj, 2, pArgs, NULL);
        TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );
        
        iRc = main_Exec(pObj);
        TINYTEST_TRUE( (0 == iRc) );
        
        pStr = main_getStr(pObj);
        if (pStr) {
            fprintf(stderr, "GEN_BEGIN:\n%sGEN_END:\n\n\n", AStr_getData(pStr));
        }
        
        obj_Release(pObj);
        pObj = OBJ_NIL;
    }
    
    fprintf(stderr, "...%s completed.\n\n\n", pTestName);
    return 1;
}
#endif




TINYTEST_START_SUITE(test_main);
#ifdef XYZZY
    TINYTEST_ADD_TEST(test_main_MakeFile04,setUp,tearDown);
    TINYTEST_ADD_TEST(test_main_MakeFile03,setUp,tearDown);
    TINYTEST_ADD_TEST(test_main_MakeFile02,setUp,tearDown);
    TINYTEST_ADD_TEST(test_main_MakeFile01,setUp,tearDown);
#endif
    TINYTEST_ADD_TEST(test_main_OpenClose,setUp,tearDown);
TINYTEST_END_SUITE();

TINYTEST_MAIN_SINGLE_SUITE(test_main);





