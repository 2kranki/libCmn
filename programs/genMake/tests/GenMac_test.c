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
#include    <srcErrors.h>
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
    srcErrors_ExitOnFatal(OBJ_NIL);

    if (pFileNode) {
        pHash = node_getData(pFileNode);
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



int             test_GenMac_CompileRoutine01(
    const
    char            *pTestName
)
{
    //ERESULT         eRc = ERESULT_SUCCESS;
    ERESULT_DATA    *pErr = OBJ_NIL;
    GENMAC_DATA     *pObj = OBJ_NIL;
    NODERTNA_DATA   *pRtn = OBJ_NIL;
    NODE_DATA       *pNodes = OBJ_NIL;
    //ASTR_DATA       *pStr = OBJ_NIL;
    const
    char            *pJsonObject =
        "{name:\"AStr\", "
        "\"deps\":[\"cmn_defs.h\",\"array.h\"],"
        "\"srcs\":[\"str.c\",\"ascii.c\"],"
        "suffix:\"c\","
        "\"test\":{\"arch\":\"X86\",\"os\":\"macos\",srcs:[\"abc.c\"]}"
        "}\n";

    fprintf(stderr, "Performing: %s\n", pTestName);

    pErr = InputStrToJSON(pJsonObject, &pNodes);
    eResult_Fprint(pErr, stderr);
    TINYTEST_TRUE( (OBJ_NIL == pErr) );
    TINYTEST_FALSE( (OBJ_NIL == pNodes) );
    pRtn = NodeRtnA_New();
    TINYTEST_FALSE( (OBJ_NIL == pRtn) );
    pErr = NodeBase_Parse(pNodes, (NODEBASE_DATA **)&pRtn);
    eResult_Fprint(pErr, stderr);
    TINYTEST_TRUE( (OBJ_NIL == pErr) );

    pObj = GenMac_New( );
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    if (pObj) {

        //TODO: Set up this variables.
        pObj->pObjDir = AStrC_NewA("OBJDIR");
        TINYTEST_FALSE( (OBJ_NIL == pObj->pObjDir) );
        pObj->pObjVar = AStrC_NewA("OBJS");
        TINYTEST_FALSE( (OBJ_NIL == pObj->pObjVar) );
        pObj->pSrcDir = AStrC_NewA("SRCDIR");
        TINYTEST_FALSE( (OBJ_NIL == pObj->pSrcDir) );
        pObj->pTstBin = AStrC_NewA("TEST_BIN");
        TINYTEST_FALSE( (OBJ_NIL == pObj->pTstBin) );
        pObj->pTstDir = AStrC_NewA("TEST_DIR");
        TINYTEST_FALSE( (OBJ_NIL == pObj->pTstDir) );
        pObj->pTstVar = AStrC_NewA("TESTS");
        TINYTEST_FALSE( (OBJ_NIL == pObj->pTstVar) );

        //obj_Enable(pRtn);  Routine is disabled by default.
        pErr = GenMac_GenCompileRtn(pObj, pRtn);
        eResult_Fprint(pErr, stderr);
        TINYTEST_TRUE( (OBJ_NIL == pErr) );
        TINYTEST_TRUE( (OBJ_NIL == GenBase_getOutput(GenMac_getGenBase(pObj))) );

        obj_Release(pObj->pObjDir);
        obj_Release(pObj->pObjVar);
        obj_Release(pObj->pSrcDir);
        obj_Release(pObj->pTstBin);
        obj_Release(pObj->pTstDir);
        obj_Release(pObj->pTstVar);

        obj_Release(pObj);
        pObj = OBJ_NIL;
    }
    
    obj_Release(pRtn);
    obj_Release(pNodes);

    fprintf(stderr, "...%s completed.\n\n\n", pTestName);
    return 1;
}



int             test_GenMac_CompileRoutine02(
    const
    char            *pTestName
)
{
    //ERESULT         eRc = ERESULT_SUCCESS;
    ERESULT_DATA    *pErr = OBJ_NIL;
    GENMAC_DATA     *pObj = OBJ_NIL;
    NODERTNA_DATA   *pRtn = OBJ_NIL;
    NODE_DATA       *pNodes = OBJ_NIL;
    ASTR_DATA       *pStr = OBJ_NIL;
    bool            fDumpNodes = false;

    const
    char            *pJsonObject =
        "{name:\"AStr\", "
        "\"deps\":[\"cmn_defs.h\",\"array.h\"],"
        "\"srcs\":[\"str.c\",\"ascii.c\"],"
        "suffix:\"c\","
        "\"test\":{\"arch\":\"X86\",\"os\":\"macos\",srcs:[\"abc.c\"]}"
        "}\n";
    const
    char            *pGenCheck =
        "OBJS += $(OBJDIR)/AStr.o\n\n"
        "$(OBJDIR)/AStr.o: $(SRCDIR)/AStr.c $(SRCDIR)/array.h $(SRCDIR)/cmn_defs.h\n"
        "\t$(CC) $(CFLAGS) -c -o $(OBJDIR)/$(@F) $< $(SRCDIR)/ascii.c $(SRCDIR)/str.c\n"
        "\n";

    fprintf(stderr, "Performing: %s\n", pTestName);

    pErr = InputStrToJSON(pJsonObject, &pNodes);
    eResult_Fprint(pErr, stderr);
    TINYTEST_TRUE( (OBJ_NIL == pErr) );
    TINYTEST_FALSE( (OBJ_NIL == pNodes) );
    pRtn = NodeRtnA_New();
    TINYTEST_FALSE( (OBJ_NIL == pRtn) );
    pErr = NodeBase_Parse(pNodes, (NODEBASE_DATA **)&pRtn);
    eResult_Fprint(pErr, stderr);
    TINYTEST_TRUE( (OBJ_NIL == pErr) );
    if (fDumpNodes) {
        ASTR_DATA       *pWrk = OBJ_NIL;
        pWrk = NodeRtnA_ToDebugString(pRtn, 0);
        fprintf(stderr, "\n====> RTNA Input:\n%s\n\n\n", AStr_getData(pWrk));
        obj_Release(pWrk);
        pWrk = OBJ_NIL;
    }

    pObj = GenMac_New( );
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    if (pObj) {

        //TODO: Set up this variables.
        pObj->pObjDir = AStrC_NewA("OBJDIR");
        TINYTEST_FALSE( (OBJ_NIL == pObj->pObjDir) );
        pObj->pObjVar = AStrC_NewA("OBJS");
        TINYTEST_FALSE( (OBJ_NIL == pObj->pObjVar) );
        pObj->pSrcDir = AStrC_NewA("SRCDIR");
        TINYTEST_FALSE( (OBJ_NIL == pObj->pSrcDir) );
        pObj->pTstBin = AStrC_NewA("TEST_BIN");
        TINYTEST_FALSE( (OBJ_NIL == pObj->pTstBin) );
        pObj->pTstDir = AStrC_NewA("TEST_DIR");
        TINYTEST_FALSE( (OBJ_NIL == pObj->pTstDir) );
        pObj->pTstVar = AStrC_NewA("TESTS");
        TINYTEST_FALSE( (OBJ_NIL == pObj->pTstVar) );

        obj_Enable(pRtn);
        pErr = GenMac_GenCompileRtn(pObj, pRtn);
        eResult_Fprint(pErr, stderr);
        TINYTEST_TRUE( (OBJ_NIL == pErr) );

        TINYTEST_FALSE( (OBJ_NIL == GenBase_getOutput(GenMac_getGenBase(pObj))) );
        pStr = TextOut_getStr(GenBase_getOutput(GenMac_getGenBase(pObj)));
        TINYTEST_FALSE( (OBJ_NIL == pStr) );
        if (pStr) {
            fprintf(stderr, "Generated:\n%s...End of Generated\n\n", AStr_getData(pStr));
        }
        TINYTEST_TRUE( (AStr_CompareA(pStr, pGenCheck) == ERESULT_SUCCESS_EQUAL) );

        obj_Release(pObj->pObjDir);
        obj_Release(pObj->pObjVar);
        obj_Release(pObj->pSrcDir);
        obj_Release(pObj->pTstBin);
        obj_Release(pObj->pTstDir);
        obj_Release(pObj->pTstVar);

        obj_Release(pObj);
        pObj = OBJ_NIL;
    }
    
    obj_Release(pRtn);
    obj_Release(pNodes);

    fprintf(stderr, "...%s completed.\n\n\n", pTestName);
    return 1;
}



int             test_GenMac_BuildTest01(
    const
    char            *pTestName
)
{
    //ERESULT         eRc = ERESULT_SUCCESS;
    ERESULT_DATA    *pErr = OBJ_NIL;
    GENMAC_DATA     *pObj = OBJ_NIL;
    NODETSTA_DATA   *pTest = OBJ_NIL;
    NODE_DATA       *pNodes = OBJ_NIL;
    //ASTR_DATA       *pStr = OBJ_NIL;
    const
    char            *pJsonObject =
        "{name:\"AStr\", "
        "\"deps\":[\"cmn_defs.h\",\"array.h\"],"
        "\"srcs\":[\"str.c\",\"ascii.c\"],"
        "suffix:\"c\","
        "\"test\":{\"arch\":\"X86\",\"os\":\"macos\",srcs:[\"abc.c\"]}"
        "}\n";

    fprintf(stderr, "Performing: %s\n", pTestName);

    pErr = InputStrToJSON(pJsonObject, &pNodes);
    eResult_Fprint(pErr, stderr);
    TINYTEST_TRUE( (OBJ_NIL == pErr) );
    TINYTEST_FALSE( (OBJ_NIL == pNodes) );
    pTest = NodeTstA_New();
    TINYTEST_FALSE( (OBJ_NIL == pTest) );
    pErr = NodeBase_Parse(pNodes, (NODEBASE_DATA **)&pTest);
    eResult_Fprint(pErr, stderr);
    TINYTEST_TRUE( (OBJ_NIL == pErr) );

    pObj = GenMac_New( );
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    if (pObj) {

        //TODO: Set up this variables.
        pObj->pObjDir = AStrC_NewA("OBJDIR");
        TINYTEST_FALSE( (OBJ_NIL == pObj->pObjDir) );
        pObj->pObjVar = AStrC_NewA("OBJS");
        TINYTEST_FALSE( (OBJ_NIL == pObj->pObjVar) );
        pObj->pSrcDir = AStrC_NewA("SRCDIR");
        TINYTEST_FALSE( (OBJ_NIL == pObj->pSrcDir) );
        pObj->pTstBin = AStrC_NewA("TEST_BIN");
        TINYTEST_FALSE( (OBJ_NIL == pObj->pTstBin) );
        pObj->pTstDir = AStrC_NewA("TEST_DIR");
        TINYTEST_FALSE( (OBJ_NIL == pObj->pTstDir) );
        pObj->pTstVar = AStrC_NewA("TESTS");
        TINYTEST_FALSE( (OBJ_NIL == pObj->pTstVar) );

        //obj_Enable(pRtn);  Routine is disabled by default.
        pErr = GenMac_GenBuildTest(pObj, pTest);
        eResult_Fprint(pErr, stderr);
        TINYTEST_TRUE( (OBJ_NIL == pErr) );
        TINYTEST_TRUE( (OBJ_NIL == GenBase_getOutput(GenMac_getGenBase(pObj))) );

        obj_Release(pObj->pObjDir);
        obj_Release(pObj->pObjVar);
        obj_Release(pObj->pSrcDir);
        obj_Release(pObj->pTstBin);
        obj_Release(pObj->pTstDir);
        obj_Release(pObj->pTstVar);

        obj_Release(pObj);
        pObj = OBJ_NIL;
    }
    
    obj_Release(pTest);
    obj_Release(pNodes);

    fprintf(stderr, "...%s completed.\n\n\n", pTestName);
    return 1;
}



int             test_GenMac_BuildTest02(
    const
    char            *pTestName
)
{
    //ERESULT         eRc = ERESULT_SUCCESS;
    ERESULT_DATA    *pErr = OBJ_NIL;
    GENMAC_DATA     *pObj = OBJ_NIL;
    NODETSTA_DATA   *pTest = OBJ_NIL;
    NODE_DATA       *pNodes = OBJ_NIL;
    ASTR_DATA       *pStr = OBJ_NIL;
    bool            fDumpNodes = false;
    int             iRc;
    int             offset = 0;

    const
    char            *pJsonObject =
        "{name:\"AStr_test\", "
        "\"srcs\":[\"data1.c\"],"
        "suffix:\"c\","
        "\"test\":{\"arch\":\"X86\",\"os\":\"macos\",srcs:[\"abc.c\"]}"
        "}\n";
    const
    char            *pGenCheck =
        "TESTS += AStr_test\n\n"
        "AStr_test: $(TEST_SRC)/AStr_test.c \n"
        "\t$(CC) $(CFLAGS) $(CFLAGS_TEST) -o $(TEST_BIN)/$(@F) $(OBJS) $(TEST_SRC)/data1.c $<\n"
        "\t$(TEST_BIN)/$(@F)\n\n";

    fprintf(stderr, "Performing: %s\n", pTestName);

    pErr = InputStrToJSON(pJsonObject, &pNodes);
    eResult_Fprint(pErr, stderr);
    TINYTEST_TRUE( (OBJ_NIL == pErr) );
    TINYTEST_FALSE( (OBJ_NIL == pNodes) );
    pTest = NodeTstA_New();
    TINYTEST_FALSE( (OBJ_NIL == pTest) );
    pErr = NodeBase_Parse(pNodes, (NODEBASE_DATA **)&pTest);
    eResult_Fprint(pErr, stderr);
    TINYTEST_TRUE( (OBJ_NIL == pErr) );
    if (fDumpNodes) {
        ASTR_DATA       *pWrk = OBJ_NIL;
        pWrk = NodeTstA_ToDebugString(pTest, 0);
        fprintf(stderr, "\n====> TSTA Input:\n%s\n\n\n", AStr_getData(pWrk));
        obj_Release(pWrk);
        pWrk = OBJ_NIL;
    }

    pObj = GenMac_New( );
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    if (pObj) {

        //TODO: Set up this variables.
        pObj->pObjDir = AStrC_NewA("OBJDIR");
        TINYTEST_FALSE( (OBJ_NIL == pObj->pObjDir) );
        pObj->pObjVar = AStrC_NewA("OBJS");
        TINYTEST_FALSE( (OBJ_NIL == pObj->pObjVar) );
        pObj->pSrcDir = AStrC_NewA("SRCDIR");
        TINYTEST_FALSE( (OBJ_NIL == pObj->pSrcDir) );
        pObj->pTstBin = AStrC_NewA("TEST_BIN");
        TINYTEST_FALSE( (OBJ_NIL == pObj->pTstBin) );
        pObj->pTstDir = AStrC_NewA("TEST_SRC");
        TINYTEST_FALSE( (OBJ_NIL == pObj->pTstDir) );
        pObj->pTstVar = AStrC_NewA("TESTS");
        TINYTEST_FALSE( (OBJ_NIL == pObj->pTstVar) );

        obj_Enable(pTest);
        pErr = GenMac_GenBuildTest(pObj, pTest);
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

        obj_Release(pObj->pObjDir);
        obj_Release(pObj->pObjVar);
        obj_Release(pObj->pSrcDir);
        obj_Release(pObj->pTstBin);
        obj_Release(pObj->pTstDir);
        obj_Release(pObj->pTstVar);

        obj_Release(pObj);
        pObj = OBJ_NIL;
    }
    
    obj_Release(pTest);
    obj_Release(pNodes);

    fprintf(stderr, "...%s completed.\n\n\n", pTestName);
    return 1;
}



int             test_GenMac_LibBegin01(
    const
    char            *pTestName
)
{
    //ERESULT         eRc = ERESULT_SUCCESS;
    ERESULT_DATA    *pErr = OBJ_NIL;
    GENMAC_DATA     *pObj = OBJ_NIL;
    NODELIB_DATA    *pLib = OBJ_NIL;
    NODE_DATA       *pNodes = OBJ_NIL;
    ASTR_DATA       *pStr = OBJ_NIL;
    bool            fDumpNodes = true;
    //int             iRc;
    //int             offset = 0;

    const
    char            *pJsonObject =
        "{name:\"Cmn\", "
        "\"deps\":[], "
        "\"hdrs\":[\"cmn_defs.h\"] "
        "}\n";
    const
    char            *pGenCheck =
    "# Generated file - edits may be discarded!\n"
    "# (11/30/2019  4:09:40.000)\n\n\n"
    "LIBNAM=libCmn\n"
    "SYS=macos64\n"
    "TEMP=/tmp\n"
    "BASEDIR = $(TEMP)/$(LIBNAM)\n\n"
    "CFLAGS_LIBS = \n"
    "CFLAGS += -g -Werror -Isrc -Isrc/$(SYS)\n"
    "CFLAGS += -D__MACOS64_ENV__\n"
    "CFLAGS_TEST = -Itests $(CFLAGS_LIBS) -lcurses\n\n"
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
    "CFLAGS += -D_DEBUG\n"
    "LIB_FILENAME=$(LIBNAM)D.a\n"
    "OBJDIR = $(LIBDIR)/o/d\n"
    "endif  #NDEBUG\n"
    "TEST_OBJ = $(OBJDIR)/tests\n"
    "TEST_BIN = $(OBJDIR)/tests\n"
    "LIBPATH = $(LIBDIR)/$(LIB_FILENAME)\n\n"
    ".SUFFIXES:\n"
    ".SUFFIXES: .asm .c .cpp .o\n\n"
    "OBJS =\n\n"
    "TESTS =\n\n\n";

    fprintf(stderr, "Performing: %s\n", pTestName);

    pErr = InputStrToJSON(pJsonObject, &pNodes);
    eResult_Fprint(pErr, stderr);
    TINYTEST_TRUE( (OBJ_NIL == pErr) );
    TINYTEST_FALSE( (OBJ_NIL == pNodes) );
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

        //TODO: Set up this variables.
        pObj->pObjDir = AStrC_NewA("OBJDIR");
        TINYTEST_FALSE( (OBJ_NIL == pObj->pObjDir) );
        pObj->pObjVar = AStrC_NewA("OBJS");
        TINYTEST_FALSE( (OBJ_NIL == pObj->pObjVar) );
        pObj->pSrcDir = AStrC_NewA("SRCDIR");
        TINYTEST_FALSE( (OBJ_NIL == pObj->pSrcDir) );
        pObj->pTstBin = AStrC_NewA("TEST_BIN");
        TINYTEST_FALSE( (OBJ_NIL == pObj->pTstBin) );
        pObj->pTstDir = AStrC_NewA("TEST_SRC");
        TINYTEST_FALSE( (OBJ_NIL == pObj->pTstDir) );
        pObj->pTstVar = AStrC_NewA("TESTS");
        TINYTEST_FALSE( (OBJ_NIL == pObj->pTstVar) );

        pErr = GenMac_GenLibBegin(pObj, pLib);
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
        // Because output has date/time in it, this comparison will not work.
        //iRc = str_CompareSpcl(AStr_getData(pStr), pGenCheck, &offset);
        //TINYTEST_TRUE( (0 == iRc) );

        obj_Release(pObj->pObjDir);
        obj_Release(pObj->pObjVar);
        obj_Release(pObj->pSrcDir);
        obj_Release(pObj->pTstBin);
        obj_Release(pObj->pTstDir);
        obj_Release(pObj->pTstVar);

        obj_Release(pObj);
        pObj = OBJ_NIL;
    }
    
    obj_Release(pLib);
    obj_Release(pNodes);

    fprintf(stderr, "...%s completed.\n\n\n", pTestName);
    return 1;
}



int             test_GenMac_LibEnd01(
    const
    char            *pTestName
)
{
    //ERESULT         eRc = ERESULT_SUCCESS;
    ERESULT_DATA    *pErr = OBJ_NIL;
    GENMAC_DATA     *pObj = OBJ_NIL;
    NODELIB_DATA    *pLib = OBJ_NIL;
    NODE_DATA       *pNodes = OBJ_NIL;
    ASTR_DATA       *pStr = OBJ_NIL;
    bool            fDumpNodes = true;
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
        "all:  clean create_dirs $(LIBPATH)\n\n\n\n";

    fprintf(stderr, "Performing: %s\n", pTestName);

    pErr = InputStrToJSON(pJsonObject, &pNodes);
    eResult_Fprint(pErr, stderr);
    TINYTEST_TRUE( (OBJ_NIL == pErr) );
    TINYTEST_FALSE( (OBJ_NIL == pNodes) );
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

        //TODO: Set up this variables.
        pObj->pObjDir = AStrC_NewA("OBJDIR");
        TINYTEST_FALSE( (OBJ_NIL == pObj->pObjDir) );
        pObj->pObjVar = AStrC_NewA("OBJS");
        TINYTEST_FALSE( (OBJ_NIL == pObj->pObjVar) );
        pObj->pSrcDir = AStrC_NewA("SRCDIR");
        TINYTEST_FALSE( (OBJ_NIL == pObj->pSrcDir) );
        pObj->pTstBin = AStrC_NewA("TEST_BIN");
        TINYTEST_FALSE( (OBJ_NIL == pObj->pTstBin) );
        pObj->pTstDir = AStrC_NewA("TEST_SRC");
        TINYTEST_FALSE( (OBJ_NIL == pObj->pTstDir) );
        pObj->pTstVar = AStrC_NewA("TESTS");
        TINYTEST_FALSE( (OBJ_NIL == pObj->pTstVar) );

        pErr = GenMac_GenLibEnd(pObj, pLib);
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

        obj_Release(pObj->pObjDir);
        obj_Release(pObj->pObjVar);
        obj_Release(pObj->pSrcDir);
        obj_Release(pObj->pTstBin);
        obj_Release(pObj->pTstDir);
        obj_Release(pObj->pTstVar);

        obj_Release(pObj);
        pObj = OBJ_NIL;
    }
    
    obj_Release(pLib);
    obj_Release(pNodes);

    fprintf(stderr, "...%s completed.\n\n\n", pTestName);
    return 1;
}




TINYTEST_START_SUITE(test_GenMac);
    TINYTEST_ADD_TEST(test_GenMac_LibEnd01,setUp,tearDown);
    TINYTEST_ADD_TEST(test_GenMac_LibBegin01,setUp,tearDown);
    TINYTEST_ADD_TEST(test_GenMac_BuildTest02,setUp,tearDown);
    TINYTEST_ADD_TEST(test_GenMac_BuildTest01,setUp,tearDown);
    TINYTEST_ADD_TEST(test_GenMac_CompileRoutine02,setUp,tearDown);
    TINYTEST_ADD_TEST(test_GenMac_CompileRoutine01,setUp,tearDown);
    TINYTEST_ADD_TEST(test_GenMac_OpenClose,setUp,tearDown);
TINYTEST_END_SUITE();

TINYTEST_MAIN_SINGLE_SUITE(test_GenMac);





