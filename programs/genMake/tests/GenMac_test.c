// vi:nu:et:sts=4 ts=4 sw=4
/*
 *	Generated 11/23/2019 12:07:26
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
#include    <hjson.h>
#include    <JsonIn.h>
#include    <SrcErrors.h>
#include    <szTbl.h>
#include    <str.h>
#include    <trace.h>
#include    <GenMac_internal.h>



int             setUp(
    const
    char            *pTestName
)
{
    mem_Init( );
    trace_Shared( ); 
    // Put setup code here. This method is called before the invocation of each
    // test method in the class.
    
    return 1; 
}


int             tearDown(
    const
    char            *pTestName
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



ERESULT_DATA *  InputStrToJSON(
    const
    char            *pStrA,
    NODE_DATA       **ppNodes
)
{
    ERESULT_DATA    *pErr = OBJ_NIL;
    HJSON_DATA      *pObj = OBJ_NIL;
    NODEHASH_DATA   *pHash;
    NODE_DATA       *pFileNode = OBJ_NIL;

    // Do initialization.
#ifdef NDEBUG
#else
    if (NULL == pStrA) {
        DEBUG_BREAK();
        pErr = eResult_NewStrA(ERESULT_INVALID_PARAMETER, "Error: Missing String!");
        return pErr;
    }
#endif

    pObj = hjson_NewA(pStrA, 4);
    if (pObj) {
        pFileNode = hjson_ParseFileValue(pObj);
        obj_Release(pObj);
        pObj = OBJ_NIL;
    }
    SrcErrors_ExitOnFatal(OBJ_NIL);

    if (pFileNode) {
        pHash = Node_getData(pFileNode);
        if (OBJ_NIL == pHash) {
            fprintf(stderr, "ERROR - No JSON Nodes to process\n\n\n");
            exit(12);
        }
        if (!obj_IsKindOf(pHash, OBJ_IDENT_NODEHASH)) {
            fprintf(stderr, "ERROR - Missing JSON Hash to process\n\n\n");
            exit(12);
        }
    }
    else {
        fprintf(stderr, "ERROR - No JSON Nodes to process\n\n\n");
        exit(12);
    }

    // Return to caller.
    if (ppNodes) {
        *ppNodes = pFileNode;
    }
    return pErr;
}



int             test_GenMac_OpenClose(
    const
    char            *pTestName
)
{
    ERESULT         eRc = ERESULT_SUCCESS;
    GENMAC_DATA	    *pObj = OBJ_NIL;
   
    fprintf(stderr, "Performing: %s\n", pTestName);

    pObj = GenMac_Alloc( );
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    pObj = GenMac_Init( pObj );
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    if (pObj) {

        //obj_TraceSet(pObj, true);       
        
        // Test something.
        TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );

        obj_Release(pObj);
        pObj = OBJ_NIL;
    }

    fprintf(stderr, "...%s completed.\n\n\n", pTestName);
    return 1;
}



int             test_GenMac_LibBegin01(
    const
    char            *pTestName
)
{
    ERESULT         eRc = ERESULT_SUCCESS;
    ERESULT_DATA    *pErr = OBJ_NIL;
    GENMAC_DATA     *pObj = OBJ_NIL;
    NODELIB_DATA    *pLib = OBJ_NIL;
    NODE_DATA       *pNodes = OBJ_NIL;
    DICT_DATA       *pDict = OBJ_NIL;
    ASTR_DATA       *pStr = OBJ_NIL;
    bool            fDumpNodes = true;
    int             iRc;
    int             offset = 0;
    uint32_t        i;
    const
    char            *pChr;

    const
    char            *pJsonObject =
        "{name:\"Cmn\", "
        "\"deps\":[], "
        "\"hdrs\":[\"cmn_defs.h\"] "
        "}\n";
    const
    char            *pGenCheck =
    //"# Generated file - edits may be discarded!\n"
    //"# (11/30/2019  4:09:40.000)\n\n\n"
    "LIBNAM=libCmn\n"
    "SYS=macos64\n"
    "TEMP=/tmp\n"
    "BASE_OBJ = $(TEMP)/$(LIBNAM)\n"
    "SRCDIR = ./src\n"
    "TEST_SRC = ./tests\n\n"
    
    "CFLAGS += -g -Werror\n"
    "ifdef  NDEBUG\n"
    "CFLAGS += -DNDEBUG\n"
    "else   #DEBUG\n"
    "CFLAGS += -D_DEBUG\n"
    "endif  #NDEBUG\n"
    "CFLAGS += -D__MACOS64_ENV__\n"
    "CFLAGS_LIBS = \n"
    "CFLAGS_TEST = -I$(TEST_SRC) $(CFLAGS_LIBS) -lcurses\n\n"
    
    "INSTALL_BASE = $(HOME)/Support/lib/$(SYS)\n"
    "INSTALL_DIR = $(INSTALL_BASE)/$(LIBNAM)\n"
    "LIBOBJ = $(BASE_OBJ)/$(SYS)\n"
    "ifdef  NDEBUG\n"
    "LIB_FILENAME=$(LIBNAM)R.a\n"
    "OBJDIR = $(LIBOBJ)/o/r\n"
    "else   #DEBUG\n"
    "LIB_FILENAME=$(LIBNAM)D.a\n"
    "OBJDIR = $(LIBOBJ)/o/d\n"
    "endif  #NDEBUG\n"
    "TEST_OBJ = $(OBJDIR)/tests\n"
    "TEST_BIN = $(OBJDIR)/tests\n"
    "LIB_PATH = $(LIBOBJ)/$(LIB_FILENAME)\n\n"
    ".SUFFIXES:\n"
    ".SUFFIXES: .asm .c .cpp .o\n\n"
    "OBJS =\n\n"
    "TESTS =\n\n\n";

    fprintf(stderr, "Performing: %s\n", pTestName);

    pErr = InputStrToJSON(pJsonObject, &pNodes);
    eResult_Fprint(pErr, stderr);
    TINYTEST_TRUE( (OBJ_NIL == pErr) );
    TINYTEST_FALSE( (OBJ_NIL == pNodes) );
    
    pDict = Dict_New();
    TINYTEST_FALSE( (OBJ_NIL == pDict) );
    eRc = Dict_Defaults(pDict);
    TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );

    pLib = NodeLib_New();
    TINYTEST_FALSE( (OBJ_NIL == pLib) );
    pErr = NodeBase_Parse(pNodes, (NODEBASE_DATA **)&pLib);
    eResult_Fprint(pErr, stderr);
    TINYTEST_TRUE( (OBJ_NIL == pErr) );
    if (fDumpNodes) {
        ASTR_DATA       *pWrk = OBJ_NIL;
        pWrk = NodeLib_ToDebugString(pLib, 0);
        fprintf(stderr, "\n====> TSTA Input:\n%s\n\n\n", AStr_getData(pWrk));
        obj_Release(pWrk);
        pWrk = OBJ_NIL;
    }

    pObj = GenMac_New( );
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    if (pObj) {

        pErr = GenMac_GenLibBegin(pObj, pLib, pDict);
        eResult_Fprint(pErr, stderr);
        TINYTEST_TRUE( (OBJ_NIL == pErr) );

        TINYTEST_FALSE( (OBJ_NIL == GenBase_getOutput(GenMac_getGenBase(pObj))) );
        pStr = TextOut_getStr(GenBase_getOutput(GenMac_getGenBase(pObj)));
        TINYTEST_FALSE( (OBJ_NIL == pStr) );
        if (pStr) {
            fprintf(stderr, "0         1         2         3\n");
            fprintf(stderr, "0123456789012345678901234567890\n");
            fprintf(stderr, "Generated:\n%s...End of Generated\n\n", AStr_getData(pStr));
        }

        // Skip first 3 lines of output.
        pChr = AStr_getData(pStr);
        for (i=0; i<3; i++) {
            while (*pChr && (*pChr != '\n')) {
                pChr++;
            }
            pChr++;
        }
        
        // Compare the remainder.
        iRc = str_CompareSpcl(pChr, pGenCheck, &offset);
        TINYTEST_TRUE( (0 == iRc) );

        obj_Release(pObj);
        pObj = OBJ_NIL;
    }
    
    obj_Release(pLib);
    obj_Release(pDict);
    obj_Release(pNodes);

    fprintf(stderr, "...%s completed.\n\n\n", pTestName);
    return 1;
}



int             test_GenMac_LibEnd01(
    const
    char            *pTestName
)
{
    ERESULT         eRc = ERESULT_SUCCESS;
    ERESULT_DATA    *pErr = OBJ_NIL;
    GENMAC_DATA     *pObj = OBJ_NIL;
    NODELIB_DATA    *pLib = OBJ_NIL;
    NODE_DATA       *pNodes = OBJ_NIL;
    DICT_DATA       *pDict = OBJ_NIL;
    ASTR_DATA       *pStr = OBJ_NIL;
    bool            fDumpNodes = false;
    int             iRc;
    int             offset = 0;

    const
    char            *pJsonObject =
        "{name:\"Cmn\", "
        "\"deps\":[], "
        "\"hdrs\":[\"cmn_defs.h\"] "
        "}\n";
    const
    char            *pGenCheck =
        "\n\n$(LIB_PATH):  $(OBJS)\n"
        "\t-cd $(LIBOBJ) ; [ -d $(LIB_FILENAME) ] && rm $(LIB_FILENAME)\n"
        "\tar rc $(LIB_PATH) $(OBJS)\n\n\n\n"
        ".PHONY: test\n"
        "test: $(TESTS)\n\n\n"
        ".PHONY: clean\n"
        "clean:\n"
        "\t-cd $(TEMP) ; [ -d $(LIBNAM) ] && rm -fr $(LIBNAM)\n\n\n"
        ".PHONY: install\n"
        "install:\n"
        "\t-cd $(INSTALL_BASE) ; [ -d $(LIBNAM) ] && rm -fr $(LIBNAM)\n"
        "\t-cd $(INSTALL_BASE) ; [ ! -d $(LIBNAM)/include ] && mkdir -p $(LIBNAM)/include/$(SYS)\n"
        "\tcp $(LIB_PATH) $(INSTALL_DIR)/$(LIBNAM).a\n"
        "\tcp src/*.h $(INSTALL_DIR)/include/\n"
        "\tif [ -d src/$(SYS) ]; then \\\n"
        "\t\tcp src/$(SYS)/*.h $(INSTALL_DIR)/include/$(SYS)/; \\\n"
        "\tfi\n\n\n"
        ".PHONY: create_dirs\n"
        "create_dirs:\n"
        "\t[ ! -d $(OBJDIR) ] && mkdir -p $(OBJDIR)/tests\n\n\n"
        ".PHONY: all\n"
        "all:  clean create_dirs $(LIB_PATH)\n\n\n\n";

    fprintf(stderr, "Performing: %s\n", pTestName);

    pErr = InputStrToJSON(pJsonObject, &pNodes);
    eResult_Fprint(pErr, stderr);
    TINYTEST_TRUE( (OBJ_NIL == pErr) );
    TINYTEST_FALSE( (OBJ_NIL == pNodes) );
    
    pDict = Dict_New();
    TINYTEST_FALSE( (OBJ_NIL == pDict) );
    eRc = Dict_Defaults(pDict);
    TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );

    pLib = NodeLib_New();
    TINYTEST_FALSE( (OBJ_NIL == pLib) );
    pErr = NodeBase_Parse(pNodes, (NODEBASE_DATA **)&pLib);
    eResult_Fprint(pErr, stderr);
    TINYTEST_TRUE( (OBJ_NIL == pErr) );
    if (fDumpNodes) {
        ASTR_DATA       *pWrk = OBJ_NIL;
        pWrk = NodeLib_ToDebugString(pLib, 0);
        fprintf(stderr, "\n====> TSTA Input:\n%s\n\n\n", AStr_getData(pWrk));
        obj_Release(pWrk);
        pWrk = OBJ_NIL;
    }

    pObj = GenMac_New( );
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    if (pObj) {

        pErr = GenMac_GenLibEnd(pObj, pLib, pDict);
        eResult_Fprint(pErr, stderr);
        TINYTEST_TRUE( (OBJ_NIL == pErr) );

        TINYTEST_FALSE( (OBJ_NIL == GenBase_getOutput(GenMac_getGenBase(pObj))) );
        pStr = TextOut_getStr(GenBase_getOutput(GenMac_getGenBase(pObj)));
        TINYTEST_FALSE( (OBJ_NIL == pStr) );
        if (pStr) {
            fprintf(stderr, "0         1         2         3\n");
            fprintf(stderr, "0123456789012345678901234567890\n");
            fprintf(stderr, "Generated:\n%s...End of Generated\n\n", AStr_getData(pStr));
        }
        iRc = str_CompareSpcl(AStr_getData(pStr), pGenCheck, &offset);
        TINYTEST_TRUE( (0 == iRc) );

        obj_Release(pObj);
        pObj = OBJ_NIL;
    }
    
    obj_Release(pLib);
    obj_Release(pDict);
    obj_Release(pNodes);

    fprintf(stderr, "...%s completed.\n\n\n", pTestName);
    return 1;
}



int             test_GenMac_PgmBegin01(
    const
    char            *pTestName
)
{
    ERESULT         eRc = ERESULT_SUCCESS;
    ERESULT_DATA    *pErr = OBJ_NIL;
    GENMAC_DATA     *pObj = OBJ_NIL;
    NODEPGM_DATA    *pPgm = OBJ_NIL;
    NODE_DATA       *pNodes = OBJ_NIL;
    DICT_DATA       *pDict = OBJ_NIL;
    ASTR_DATA       *pStr = OBJ_NIL;
    bool            fDumpNodes = true;
    int             iRc;
    int             offset = 0;
    uint32_t        i;
    const
    char            *pChr;

    const
    char            *pJsonObject =
        "{name:\"genMake\", "
        "\"deps\":[], "
        "\"hdrs\":[\"cmn_defs.h\"] "
        "}\n";
    const
    char            *pGenCheck =
    //"# Generated file - edits may be discarded!\n"
    //"# (11/30/2019  4:09:40.000)\n\n\n"
    "PGMNAM=genMake\n"
    "SYS=macos64\n"
    "TEMP=/tmp\n"
    "BASE_OBJ = $(TEMP)/$(PGMNAM)\n"
    "SRCDIR = ./src\n"
    "TEST_SRC = ./tests\n\n"
    
    "CFLAGS += -g -Werror\n"
    "ifdef  NDEBUG\n"
    "CFLAGS += -DNDEBUG\n"
    "else   #DEBUG\n"
    "CFLAGS += -D_DEBUG\n"
    "endif  #NDEBUG\n"
    "CFLAGS += -D__MACOS64_ENV__\n"
    "CFLAGS_LIBS = \n"
    "CFLAGS_TEST = -I$(TEST_SRC) $(CFLAGS_LIBS) -lcurses\n\n"
    
    "INSTALL_BASE = $(HOME)/Support/lib/$(SYS)\n"
    "INSTALL_DIR = $(INSTALL_BASE)/$(PGMNAM)\n"
    "LIBOBJ = $(BASE_OBJ)/$(SYS)\n"
    "ifdef  NDEBUG\n"
    "LIB_FILENAME=$(PGMNAM)R.a\n"
    "OBJDIR = $(LIBOBJ)/o/r\n"
    "else   #DEBUG\n"
    "LIB_FILENAME=$(PGMNAM)D.a\n"
    "OBJDIR = $(LIBOBJ)/o/d\n"
    "endif  #NDEBUG\n"
    "TEST_OBJ = $(OBJDIR)/tests\n"
    "TEST_BIN = $(OBJDIR)/tests\n"
    "LIB_PATH = $(LIBOBJ)/$(LIB_FILENAME)\n\n"
    
    ".SUFFIXES:\n"
    ".SUFFIXES: .asm .c .cpp .o\n\n"
    
    "OBJS =\n\n"
    "TESTS =\n\n\n";

    fprintf(stderr, "Performing: %s\n", pTestName);

    pErr = InputStrToJSON(pJsonObject, &pNodes);
    eResult_Fprint(pErr, stderr);
    TINYTEST_TRUE( (OBJ_NIL == pErr) );
    TINYTEST_FALSE( (OBJ_NIL == pNodes) );
    
    pDict = Dict_New();
    TINYTEST_FALSE( (OBJ_NIL == pDict) );
    eRc = Dict_Defaults(pDict);
    TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );

    pPgm = NodePgm_New();
    TINYTEST_FALSE( (OBJ_NIL == pPgm) );
    pErr = NodeBase_Parse(pNodes, (NODEBASE_DATA **)&pPgm);
    eResult_Fprint(pErr, stderr);
    TINYTEST_TRUE( (OBJ_NIL == pErr) );
    
    if (fDumpNodes) {
        ASTR_DATA       *pWrk = OBJ_NIL;
        pWrk = NodePgm_ToDebugString(pPgm, 0);
        fprintf(stderr, "\n====> TSTA Input:\n%s\n\n\n", AStr_getData(pWrk));
        obj_Release(pWrk);
        pWrk = OBJ_NIL;
    }

    pObj = GenMac_New( );
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    if (pObj) {

        pErr = GenMac_GenPgmBegin(pObj, pPgm, pDict);
        eResult_Fprint(pErr, stderr);
        TINYTEST_TRUE( (OBJ_NIL == pErr) );

        TINYTEST_FALSE( (OBJ_NIL == GenBase_getOutput(GenMac_getGenBase(pObj))) );
        pStr = TextOut_getStr(GenBase_getOutput(GenMac_getGenBase(pObj)));
        TINYTEST_FALSE( (OBJ_NIL == pStr) );
        if (pStr) {
            fprintf(stderr, "0         1         2         3\n");
            fprintf(stderr, "0123456789012345678901234567890\n");
            fprintf(stderr, "Generated:\n%s...End of Generated\n\n", AStr_getData(pStr));
        }
        
        // Skip first 3 lines of output.
        pChr = AStr_getData(pStr);
        for (i=0; i<3; i++) {
            while (*pChr && (*pChr != '\n')) {
                pChr++;
            }
            pChr++;
        }
        
        // Compare the remainder.
        iRc = str_CompareSpcl(pChr, pGenCheck, &offset);
        TINYTEST_TRUE( (0 == iRc) );

        obj_Release(pObj);
        pObj = OBJ_NIL;
    }
    
    obj_Release(pPgm);
    obj_Release(pDict);
    obj_Release(pNodes);

    fprintf(stderr, "...%s completed.\n\n\n", pTestName);
    return 1;
}



int             test_GenMac_PgmEnd01(
    const
    char            *pTestName
)
{
    ERESULT         eRc = ERESULT_SUCCESS;
    ERESULT_DATA    *pErr = OBJ_NIL;
    GENMAC_DATA     *pObj = OBJ_NIL;
    NODEPGM_DATA    *pPgm = OBJ_NIL;
    DICT_DATA       *pDict = OBJ_NIL;
    NODE_DATA       *pNodes = OBJ_NIL;
    ASTR_DATA       *pStr = OBJ_NIL;
    bool            fDumpNodes = false;
    int             iRc;
    int             offset = 0;

    const
    char            *pJsonObject =
        "{name:\"Cmn\", "
        "\"deps\":[], "
        "\"hdrs\":[\"cmn_defs.h\"] "
        "}\n";
    const
    char            *pGenCheck =
        "\n\n.PHONY: test\n"
        "test: $(TESTS)\n\n\n"
        ".PHONY: clean\n"
        "clean:\n"
        "\t-cd $(TEMP) ; [ -d $(PGMNAM) ] && rm -fr $(PGMNAM)\n\n\n"
        ".PHONY: install\n"
        "install:\n"
        "\t-cd $(INSTALL_BASE) ; [ -d $(PGMNAM) ] && rm -fr $(PGMNAM)\n"
        "\tcp $(OBJDIR)/$(PGMNAM) $(INSTALL_BASE)/$(PGMNAM)\n\n\n"
        ".PHONY: link\n"
        "link: $(OBJS) $(SRCDIR)/mainProgram.c\n"
        "\tCC -o $(OBJDIR)/$(PGMNAM) $(CFLAGS) $(CFLAGS_LIBS) $^\n\n\n"
        ".PHONY: create_dirs\n"
        "create_dirs:\n"
        "\t[ ! -d $(OBJDIR) ] && mkdir -p $(OBJDIR)/tests\n\n\n"
        ".PHONY: all\n"
        "all:  clean create_dirs link\n\n\n";

    fprintf(stderr, "Performing: %s\n", pTestName);

    pErr = InputStrToJSON(pJsonObject, &pNodes);
    eResult_Fprint(pErr, stderr);
    TINYTEST_TRUE( (OBJ_NIL == pErr) );
    TINYTEST_FALSE( (OBJ_NIL == pNodes) );
    
    pDict = Dict_New();
    TINYTEST_FALSE( (OBJ_NIL == pDict) );
    eRc = Dict_Defaults(pDict);
    TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );

    pPgm = NodePgm_New();
    TINYTEST_FALSE( (OBJ_NIL == pPgm) );
    pErr = NodeBase_Parse(pNodes, (NODEBASE_DATA **)&pPgm);
    eResult_Fprint(pErr, stderr);
    TINYTEST_TRUE( (OBJ_NIL == pErr) );
    
    if (fDumpNodes) {
        ASTR_DATA       *pWrk = OBJ_NIL;
        pWrk = NodePgm_ToDebugString(pPgm, 0);
        fprintf(stderr, "\n====> TSTA Input:\n%s\n\n\n", AStr_getData(pWrk));
        obj_Release(pWrk);
        pWrk = OBJ_NIL;
    }

    pObj = GenMac_New( );
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    if (pObj) {

        pErr = GenMac_GenPgmEnd(pObj, pPgm, pDict);
        eResult_Fprint(pErr, stderr);
        TINYTEST_TRUE( (OBJ_NIL == pErr) );

        TINYTEST_FALSE( (OBJ_NIL == GenBase_getOutput(GenMac_getGenBase(pObj))) );
        pStr = TextOut_getStr(GenBase_getOutput(GenMac_getGenBase(pObj)));
        TINYTEST_FALSE( (OBJ_NIL == pStr) );
        if (pStr) {
            fprintf(stderr, "0         1         2         3\n");
            fprintf(stderr, "0123456789012345678901234567890\n");
            fprintf(stderr, "Generated:\n%s...End of Generated\n\n", AStr_getData(pStr));
        }
        iRc = str_CompareSpcl(AStr_getData(pStr), pGenCheck, &offset);
        TINYTEST_TRUE( (0 == iRc) );

        obj_Release(pObj);
        pObj = OBJ_NIL;
    }
    
    obj_Release(pPgm);
    obj_Release(pDict);
    obj_Release(pNodes);

    fprintf(stderr, "...%s completed.\n\n\n", pTestName);
    return 1;
}




TINYTEST_START_SUITE(test_GenMac);
    //TINYTEST_ADD_TEST(test_GenMac_PgmEnd01,setUp,tearDown);
    //TINYTEST_ADD_TEST(test_GenMac_PgmBegin01,setUp,tearDown);
    //TINYTEST_ADD_TEST(test_GenMac_LibEnd01,setUp,tearDown);
    //TINYTEST_ADD_TEST(test_GenMac_LibBegin01,setUp,tearDown);
    TINYTEST_ADD_TEST(test_GenMac_OpenClose,setUp,tearDown);
TINYTEST_END_SUITE();

TINYTEST_MAIN_SINGLE_SUITE(test_GenMac);





