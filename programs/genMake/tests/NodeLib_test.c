// vi:nu:et:sts=4 ts=4 sw=4
/*
 *	Generated 11/03/2019 08:12:07
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
#include    <SrcErrors.h>
#include    <szTbl.h>
#include    <trace.h>
#include    <NodeLib_internal.h>



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






int             test_NodeLib_OpenClose(
    const
    char            *pTestName
)
{
    ERESULT         eRc = ERESULT_SUCCESS;
    NODELIB_DATA	    *pObj = OBJ_NIL;
   
    fprintf(stderr, "Performing: %s\n", pTestName);

    pObj = NodeLib_Alloc( );
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    pObj = NodeLib_Init( pObj );
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    if (pObj) {

        //obj_TraceSet(pObj, true);       
        
        // Test something.
        TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );

        obj_Release(pObj);
        pObj = OBJ_NIL;
    }

    fprintf(stderr, "...%s completed.\n\n", pTestName);
    return 1;
}



int             test_NodeLib_Parse01(
    const
    char            *pTestName
)
{
    ERESULT_DATA    *pErr = OBJ_NIL;
    //NODE_DATA       *pNode = OBJ_NIL;
    NODE_DATA       *pNodes = OBJ_NIL;
    NODEHASH_DATA   *pHash = OBJ_NIL;
    ASTRARRAY_DATA  *pStrArray = OBJ_NIL;
    ASTR_DATA       *pStr = OBJ_NIL;
    NODELIB_DATA    *pLib = OBJ_NIL;
    ASTRCARRAY_DATA *pStrCArray = OBJ_NIL;
    ASTRC_DATA      *pStrC = OBJ_NIL;
    const
    char            *pGoodJsonObject1 =
        "{name:\"Cmn\", "
        "\"deps\":[], "
        "\"hdrs\":[\"cmn_defs.h\"] "
        "}\n";
    bool            fDumpNodes = true;

    fprintf(stderr, "Performing: %s\n", pTestName);

    // Process the JSON data.
    pErr = InputStrToJSON(pGoodJsonObject1, &pNodes);
    TINYTEST_TRUE( (OBJ_NIL == pErr) );
    TINYTEST_FALSE( (OBJ_NIL == pNodes) );
    TINYTEST_TRUE( (obj_IsKindOf(pNodes, OBJ_IDENT_NODE)) );
    pHash = Node_getData(pNodes);
    TINYTEST_FALSE( (OBJ_NIL == pHash) );
    TINYTEST_TRUE( (obj_IsKindOf(pHash, OBJ_IDENT_NODEHASH)) );

    if (fDumpNodes) {
        ASTR_DATA       *pWrk = OBJ_NIL;
        pWrk = Node_ToDebugString(pNodes, 0);
        fprintf(stderr, "Parsed JSON:\n%s\n\n\n", AStr_getData(pWrk));
        obj_Release(pWrk);
        pWrk = OBJ_NIL;
    }

    // Parse the Object.
    //obj_TraceSet(pBase, true);
    pErr = NodeLib_Parse(pNodes, &pLib);
    if (pErr) {
        fprintf(stderr, "%s\n", eResult_getErrorA(pErr));
    }
    TINYTEST_TRUE((OBJ_NIL == pErr));
    
    // Display the Output.
    if (pLib) {
        fprintf(stderr, "===> NodeObj:\n\n");
        ASTR_DATA   *pStr = NodeLib_ToDebugString(pLib, 0);
        fprintf(stderr, "%s\n", AStr_getData(pStr));
        obj_Release(pStr);
        pStr = OBJ_NIL;
    }

    // Validate the output.
    pStrC = NodeLib_getName(pLib);
    TINYTEST_FALSE( (OBJ_NIL == pStrC) );
    TINYTEST_TRUE((ERESULT_SUCCESS_EQUAL == AStrC_CompareA(pStrC,"Cmn")));
    pStrCArray = NodeLib_getArches(pLib);
    TINYTEST_FALSE( (OBJ_NIL == pStrCArray) );
    if (pStrCArray) {
        TINYTEST_TRUE((0 == AStrCArray_getSize(pStrCArray)));
    }
    pStrCArray = NodeLib_getOSs(pLib);
    TINYTEST_FALSE( (OBJ_NIL == pStrCArray) );
    if (pStrCArray) {
        TINYTEST_TRUE((0 == AStrCArray_getSize(pStrCArray)));
    }
    pStrCArray = NodeLib_getDeps(pLib);
    TINYTEST_FALSE( (OBJ_NIL == pStrCArray) );
    if (pStrCArray) {
        TINYTEST_TRUE((0 == AStrCArray_getSize(pStrCArray)));
    }
    pStrCArray = NodeLib_getHdrs(pLib);
    TINYTEST_FALSE( (OBJ_NIL == pStrCArray) );
    if (pStrCArray) {
        TINYTEST_TRUE((1 == AStrCArray_getSize(pStrCArray)));
        pStrC = AStrCArray_Get(pStrCArray, 1);
        TINYTEST_TRUE((ERESULT_SUCCESS_EQUAL == AStrC_CompareA(pStrC,"$(SRCDIR)/cmn_defs.h")));
    }
    pStrCArray = NodeLib_getSrcs(pLib);
    TINYTEST_FALSE( (OBJ_NIL == pStrCArray) );
    if (pStrCArray) {
        TINYTEST_TRUE((0 == AStrCArray_getSize(pStrCArray)));
    }

    obj_Release(pNodes);
    pNodes = OBJ_NIL;
    
    obj_Release(pLib);
    pLib = OBJ_NIL;

    fprintf(stderr, "...%s completed.\n\n\n\n", pTestName);
    return 1;
}



int             test_NodeLib_Begin01(
    const
    char            *pTestName
)
{
    ERESULT         eRc = ERESULT_SUCCESS;
    ERESULT_DATA    *pErr = OBJ_NIL;
    DICT_DATA       *pDict = OBJ_NIL;
    NODELIB_DATA    *pLib = OBJ_NIL;
    NODE_DATA       *pNodes = OBJ_NIL;
    ASTR_DATA       *pStr = OBJ_NIL;
    bool            fDump = true;
    int             iRc;
    int             offset = 0;
    uint32_t        i;
    const
    char            *pChr;

    const
    char            *pJsonObject =
        "{name:\"Cmn\" "
        "}\n";
    const
    char            *pGenCheck =
    //"# Generated file - edits may be discarded!\n"
    //"# (11/30/2019  4:09:40.000)\n\n\n"
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
    "CFLAGS_TEST = -I$(TEST_SRC) $(CFLAGS_LIBS) -lcurses\n\n"
    
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
    if (fDump) {
        ASTR_DATA       *pWrk = OBJ_NIL;
        pWrk = NodeLib_ToDebugString(pLib, 0);
        fprintf(stderr, "\n====> TSTA Input:\n%s\n\n\n", AStr_getData(pWrk));
        obj_Release(pWrk);
        pWrk = OBJ_NIL;
    }

    pStr = NodeLib_GenMacBegin(pLib, pDict);
    TINYTEST_FALSE( (OBJ_NIL == pStr) );

    if (pStr && fDump) {
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
    fprintf(stderr, "\toffset = %d\n", offset);
    TINYTEST_TRUE( (0 == iRc) );

    obj_Release(pStr);
    obj_Release(pLib);
    obj_Release(pDict);
    obj_Release(pNodes);

    fprintf(stderr, "...%s completed.\n\n\n", pTestName);
    return 1;
}



int             test_NodeLib_Begin02(
    const
    char            *pTestName
)
{
    ERESULT         eRc = ERESULT_SUCCESS;
    ERESULT_DATA    *pErr = OBJ_NIL;
    DICT_DATA       *pDict = OBJ_NIL;
    NODELIB_DATA    *pLib = OBJ_NIL;
    NODE_DATA       *pNodes = OBJ_NIL;
    ASTR_DATA       *pStr = OBJ_NIL;
    bool            fDump = true;
    int             iRc;
    int             offset = 0;
    uint32_t        i;
    const
    char            *pChr;

    const
    char            *pJsonObject =
        "{name:\"Emu\", "
        "\"deps\":[Cmn] "
        //"\"hdrs\":[\"cmn_defs.h\"] "
        "}\n";
    const
    char            *pGenCheck =
    //"# Generated file - edits may be discarded!\n"
    //"# (11/30/2019  4:09:40.000)\n\n\n"
    ".DEFAULT_GOAL := all\n"
    "SHELL=/bin/sh\n\n"
    "LIBNAM=libEmu\n"
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
    "# libCmn\n"
    "LIBCMN_BASE = $(LIB_BASE)/libCmn\n"
    "CFLAGS += -I$(LIBCMN_BASE)/include\n"
    "CFLAGS_LIBS += -lCmn -L$(LIBCMN_BASE)\n"
    "CFLAGS_TEST = -I$(TEST_SRC) $(CFLAGS_LIBS) -lcurses\n\n"
    
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
    if (fDump) {
        ASTR_DATA       *pWrk = OBJ_NIL;
        pWrk = NodeLib_ToDebugString(pLib, 0);
        fprintf(stderr, "\n====> TSTA Input:\n%s\n\n\n", AStr_getData(pWrk));
        obj_Release(pWrk);
        pWrk = OBJ_NIL;
    }

    pStr = NodeLib_GenMacBegin(pLib, pDict);
    TINYTEST_FALSE( (OBJ_NIL == pStr) );

    if (pStr && fDump) {
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
    fprintf(stderr, "\toffset = %d\n", offset);
    TINYTEST_TRUE( (0 == iRc) );

    obj_Release(pStr);
    obj_Release(pLib);
    obj_Release(pDict);
    obj_Release(pNodes);

    fprintf(stderr, "...%s completed.\n\n\n", pTestName);
    return 1;
}



int             test_NodeLib_End01(
    const
    char            *pTestName
)
{
    ERESULT         eRc = ERESULT_SUCCESS;
    ERESULT_DATA    *pErr = OBJ_NIL;
    DICT_DATA       *pDict = OBJ_NIL;
    NODELIB_DATA    *pLib = OBJ_NIL;
    NODE_DATA       *pNodes = OBJ_NIL;
    ASTR_DATA       *pStr = OBJ_NIL;
    bool            fDump = true;
    int             iRc;
    int             offset = 0;

    const
    char            *pJsonObject =
        "{name:\"genMake\", "
        "\"deps\":[Cmn] "
        "}\n";
    const
    char            *pGenCheck =
        "\n\n$(LIB_PATH):  $(OBJS)\n"
        "\t-cd $(LIBOBJ) ; [ -d $(LIB_FILENAME) ] && rm $(LIB_FILENAME)\n"
        "\tar rc $(LIB_PATH) $(OBJS)\n\n\n"
        ".PHONY: test\n"
        "test: $(TESTS)\n\n\n"
        ".PHONY: check\n"
        "check: $(TESTS)\n\n\n"
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
        "all:  clean create_dirs $(LIB_PATH)\n\n\n";

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
    
    if (fDump) {
        ASTR_DATA       *pWrk = OBJ_NIL;
        pWrk = NodeLib_ToDebugString(pLib, 0);
        fprintf(stderr, "\n====> TSTA Input:\n%s\n\n\n", AStr_getData(pWrk));
        obj_Release(pWrk);
        pWrk = OBJ_NIL;
    }

    pStr = NodeLib_GenMacEnd(pLib, pDict);
    TINYTEST_FALSE( (OBJ_NIL == pStr) );

    if (pStr && fDump) {
        fprintf(stderr, "0         1         2         3\n");
        fprintf(stderr, "0123456789012345678901234567890\n");
        fprintf(stderr, "Generated:\n%s...End of Generated\n\n", AStr_getData(pStr));
    }
    iRc = str_CompareSpcl(AStr_getData(pStr), pGenCheck, &offset);
    fprintf(stderr, "\toffset = %d\n", offset);
    TINYTEST_TRUE( (0 == iRc) );

    obj_Release(pStr);
    obj_Release(pLib);
    obj_Release(pDict);
    obj_Release(pNodes);

    fprintf(stderr, "...%s completed.\n\n\n", pTestName);
    return 1;
}




TINYTEST_START_SUITE(test_NodeLib);
    TINYTEST_ADD_TEST(test_NodeLib_End01,setUp,tearDown);
    TINYTEST_ADD_TEST(test_NodeLib_Begin02,setUp,tearDown);
    TINYTEST_ADD_TEST(test_NodeLib_Begin01,setUp,tearDown);
    TINYTEST_ADD_TEST(test_NodeLib_Parse01,setUp,tearDown);
    TINYTEST_ADD_TEST(test_NodeLib_OpenClose,setUp,tearDown);
TINYTEST_END_SUITE();

TINYTEST_MAIN_SINGLE_SUITE(test_NodeLib);





