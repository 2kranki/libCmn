// vi:nu:et:sts=4 ts=4 sw=4
/*
 *	Generated 11/10/2019 10:31:05
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
#include    <NodeRtnA_internal.h>



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






int             test_NodeRtnA_OpenClose(
    const
    char            *pTestName
)
{
    ERESULT         eRc = ERESULT_SUCCESS;
    NODERTNA_DATA	    *pObj = OBJ_NIL;
   
    fprintf(stderr, "Performing: %s\n", pTestName);

    pObj = NodeRtnA_Alloc( );
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    pObj = NodeRtnA_Init( pObj );
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



int             test_NodeRtnA_CompileRoutine01(
    const
    char            *pTestName
)
{
    ERESULT         eRc = ERESULT_SUCCESS;
    ERESULT_DATA    *pErr = OBJ_NIL;
    NODERTNA_DATA   *pRtn = OBJ_NIL;
    NODE_DATA       *pNodes = OBJ_NIL;
    DICT_DATA       *pDict = OBJ_NIL;
    ASTR_DATA       *pStr = OBJ_NIL;
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
    
    pDict = Dict_New();
    TINYTEST_FALSE( (OBJ_NIL == pDict) );
    eRc = Dict_Defaults(pDict);
    TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );

    pRtn = NodeRtnA_New();
    TINYTEST_FALSE( (OBJ_NIL == pRtn) );
    pErr = NodeBase_Parse(pNodes, (NODEBASE_DATA **)&pRtn);
    eResult_Fprint(pErr, stderr);
    TINYTEST_TRUE( (OBJ_NIL == pErr) );

    //obj_Enable(pRtn);  Routine is disabled by default.
    pStr = NodeRtnA_GenMac(pRtn, pDict);
    TINYTEST_TRUE( (OBJ_NIL == pStr) );

    obj_Release(pRtn);
    obj_Release(pDict);
    obj_Release(pNodes);

    fprintf(stderr, "...%s completed.\n\n\n", pTestName);
    return 1;
}



int             test_NodeRtnA_CompileRoutine02(
    const
    char            *pTestName
)
{
    ERESULT         eRc = ERESULT_SUCCESS;
    ERESULT_DATA    *pErr = OBJ_NIL;
    NODERTNA_DATA   *pRtn = OBJ_NIL;
    NODE_DATA       *pNodes = OBJ_NIL;
    DICT_DATA       *pDict = OBJ_NIL;
    ASTR_DATA       *pStr = OBJ_NIL;
    int             iRc;
    int             offset = 0;
    bool            fDump = true;

    const
    char            *pJsonObject =
        "{name:\"AStr\", "
        "\"deps\":[\"$(SRCDIR)/cmn_defs.h\",\"$(SRCDIR)/array.h\"],"
        "\"srcs\":[\"str.c\",\"ascii.c\"],"
        "ext:\"c\","
        "\"test\":{\"arch\":\"X86\",\"os\":\"macos\",srcs:[\"abc.c\"]}"
        "}\n";
    const
    char            *pGenCheck =
        "OBJS += $(OBJDIR)/AStr.o\n\n"
        "$(OBJDIR)/AStr.o: $(SRCDIR)/AStr.c $(SRCDIR)/array.h $(SRCDIR)/cmn_defs.h \n"
        "\t$(CC) $(CFLAGS) -c -o $(OBJDIR)/$(@F) -I$(SRCDIR) "
                            "$(SRCDIR)/ascii.c $(SRCDIR)/str.c $<\n"
        "\n";

    fprintf(stderr, "Performing: %s\n", pTestName);

    pErr = InputStrToJSON(pJsonObject, &pNodes);
    eResult_Fprint(pErr, stderr);
    TINYTEST_TRUE( (OBJ_NIL == pErr) );
    TINYTEST_FALSE( (OBJ_NIL == pNodes) );
    
    pDict = Dict_New();
    TINYTEST_FALSE( (OBJ_NIL == pDict) );
    eRc = Dict_Defaults(pDict);
    TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );

    pRtn = NodeRtnA_New();
    TINYTEST_FALSE( (OBJ_NIL == pRtn) );
    pErr = NodeBase_Parse(pNodes, (NODEBASE_DATA **)&pRtn);
    eResult_Fprint(pErr, stderr);
    TINYTEST_TRUE( (OBJ_NIL == pErr) );
    if (fDump) {
        ASTR_DATA       *pWrk = OBJ_NIL;
        pWrk = NodeRtnA_ToDebugString(pRtn, 0);
        fprintf(stderr, "\n====> RTNA Input:\n%s\n\n\n", AStr_getData(pWrk));
        obj_Release(pWrk);
        pWrk = OBJ_NIL;
    }

    obj_Enable(pRtn);
    pStr = NodeRtnA_GenMac(pRtn, pDict);
    TINYTEST_FALSE( (OBJ_NIL == pStr) );

    if (pStr && fDump) {
        fprintf(stderr, "===> Generated:\n%s...End of Generated\n\n", AStr_getData(pStr));
        fprintf(stderr, "===> Looking for:\n%s...End of Looking for\n\n", pGenCheck);
    }
    iRc = str_CompareSpcl(AStr_getData(pStr), pGenCheck, &offset);
    TINYTEST_TRUE( (0 == iRc) );
    obj_Release(pStr);

    obj_Release(pRtn);
    obj_Release(pDict);
    obj_Release(pNodes);

    fprintf(stderr, "...%s completed.\n\n\n", pTestName);
    return 1;
}




TINYTEST_START_SUITE(test_NodeRtnA);
    TINYTEST_ADD_TEST(test_NodeRtnA_CompileRoutine02,setUp,tearDown);
    TINYTEST_ADD_TEST(test_NodeRtnA_CompileRoutine01,setUp,tearDown);
    TINYTEST_ADD_TEST(test_NodeRtnA_OpenClose,setUp,tearDown);
TINYTEST_END_SUITE();

TINYTEST_MAIN_SINGLE_SUITE(test_NodeRtnA);





