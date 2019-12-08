// vi:nu:et:sts=4 ts=4 sw=4
/*
 *	Generated 11/03/2019 08:11:38
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
#include    <trace.h>
#include    <NodeRtn_internal.h>



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






int             test_NodeRtn_OpenClose(
    const
    char            *pTestName
)
{
    ERESULT         eRc = ERESULT_SUCCESS;
    NODERTN_DATA	    *pObj = OBJ_NIL;
   
    fprintf(stderr, "Performing: %s\n", pTestName);

    pObj = NodeRtn_Alloc( );
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    pObj = NodeRtn_Init( pObj );
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



int             test_NodeRtn_Parse01(
    const
    char            *pTestName
)
{
    ERESULT         eRc;
    ERESULT_DATA    *pErr = OBJ_NIL;
    //NODE_DATA       *pNode = OBJ_NIL;
    NODE_DATA       *pNodes = OBJ_NIL;
    NODEHASH_DATA   *pHash = OBJ_NIL;
    ASTRARRAY_DATA  *pStrArray = OBJ_NIL;
    ASTR_DATA       *pStr = OBJ_NIL;
    ASTRCARRAY_DATA *pStrCArray = OBJ_NIL;
    ASTRC_DATA      *pStrC = OBJ_NIL;
    NODERTN_DATA    *pRtn = OBJ_NIL;
    NODETEST_DATA   *pTest = OBJ_NIL;
    const
    char            *pGoodJsonObject1 =
        "{name:\"AStr\", "
        "ext:c, "
        "deps:[\"cmn_defs.h\",\"array.h\"],"
        "\"srcs\":[\"str.c\",\"ascii.c\"],"
        "\"test\":{\"arch\":\"X86\",\"os\":\"macos\",srcs:[\"abc.c\"]}"
        "}\n";
    bool            fDump = true;

    fprintf(stderr, "Performing: %s\n", pTestName);

    // Process the JSON data.
    pErr = InputStrToJSON(pGoodJsonObject1, &pNodes);
    TINYTEST_TRUE( (OBJ_NIL == pErr) );
    TINYTEST_FALSE( (OBJ_NIL == pNodes) );
    TINYTEST_TRUE( (obj_IsKindOf(pNodes, OBJ_IDENT_NODE)) );
    pHash = node_getData(pNodes);
    TINYTEST_FALSE( (OBJ_NIL == pHash) );
    TINYTEST_TRUE( (obj_IsKindOf(pHash, OBJ_IDENT_NODEHASH)) );

    if (fDump) {
        ASTR_DATA       *pWrk = OBJ_NIL;
        pWrk = node_ToDebugString(pNodes, 0);
        fprintf(stderr, "Parsed JSON:\n%s\n\n\n", AStr_getData(pWrk));
        obj_Release(pWrk);
        pWrk = OBJ_NIL;
    }

    // Parse the Object.
    //obj_TraceSet(pBase, true);
    pErr = NodeRtn_Parse(pNodes, &pRtn);
    if (pErr) {
        fprintf(stderr, "%s\n", eResult_getErrorA(pErr));
    }
    TINYTEST_TRUE((OBJ_NIL == pErr));
    
    // Display the Output.
    if (pRtn && fDump) {
        fprintf(stderr, "===> NodeObj:\n\n");
        ASTR_DATA   *pStr = NodeRtn_ToDebugString(pRtn, 0);
        fprintf(stderr, "%s\n", AStr_getData(pStr));
        obj_Release(pStr);
        pStr = OBJ_NIL;
    }

    // Validate the output.
    pStrC = NodeRtn_getName(pRtn);
    TINYTEST_FALSE( (OBJ_NIL == pStrC) );
    TINYTEST_TRUE((ERESULT_SUCCESS_EQUAL == AStrC_CompareA(pStrC,"AStr")));
    pStrCArray = NodeRtn_getArches(pRtn);
    TINYTEST_FALSE( (OBJ_NIL == pStrCArray) );
    if (pStrCArray) {
        TINYTEST_TRUE((0 == AStrCArray_getSize(pStrCArray)));
    }
    pStrCArray = NodeRtn_getOSs(pRtn);
    TINYTEST_FALSE( (OBJ_NIL == pStrCArray) );
    if (pStrCArray) {
        TINYTEST_TRUE((0 == AStrCArray_getSize(pStrCArray)));
    }
    pStrCArray = NodeRtn_getDeps(pRtn);
    TINYTEST_FALSE( (OBJ_NIL == pStrCArray) );
    if (pStrCArray) {
        TINYTEST_TRUE((2 == AStrCArray_getSize(pStrCArray)));
        pStrC = AStrCArray_Get(pStrCArray, 1);
        eRc = AStrC_CompareA(pStrC,"$(SRCDIR)/array.h");
        TINYTEST_TRUE((ERESULT_SUCCESS_EQUAL == eRc));
        pStrC = AStrCArray_Get(pStrCArray, 2);
        eRc = AStrC_CompareA(pStrC,"$(SRCDIR)/cmn_defs.h");
        TINYTEST_TRUE((ERESULT_SUCCESS_EQUAL == eRc));
    }
    pStrCArray = NodeRtn_getSrcs(pRtn);
    TINYTEST_FALSE( (OBJ_NIL == pStrCArray) );
    if (pStrCArray) {
        TINYTEST_TRUE((2 == AStrCArray_getSize(pStrCArray)));
        pStrC = AStrCArray_Get(pStrCArray, 1);
        eRc = AStrC_CompareA(pStrC,"$(SRCDIR)/ascii.c");
        TINYTEST_TRUE((ERESULT_SUCCESS_EQUAL == eRc));
        pStrC = AStrCArray_Get(pStrCArray, 2);
        eRc = AStrC_CompareA(pStrC,"$(SRCDIR)/str.c");
        TINYTEST_TRUE((ERESULT_SUCCESS_EQUAL == eRc));
    }
    pTest = NodeRtn_getTest(pRtn);
    TINYTEST_FALSE( (OBJ_NIL == pTest) );
    if (pTest) {
        pStrC = NodeTest_getName(pTest);
        TINYTEST_TRUE((ERESULT_SUCCESS_EQUAL == AStrC_CompareA(pStrC,"AStr_test")));
    }
    pStrCArray = NodeTest_getArches(pTest);
    TINYTEST_FALSE( (OBJ_NIL == pStrCArray) );
    if (pStrCArray) {
        TINYTEST_TRUE((1 == AStrCArray_getSize(pStrCArray)));
        pStrC = AStrCArray_Get(pStrCArray, 1);
        TINYTEST_TRUE((ERESULT_SUCCESS_EQUAL == AStrC_CompareA(pStrC,"X86")));
    }
    pStrCArray = NodeTest_getOSs(pTest);
    TINYTEST_FALSE( (OBJ_NIL == pStrCArray) );
    if (pStrCArray) {
        TINYTEST_TRUE((1 == AStrCArray_getSize(pStrCArray)));
        pStrC = AStrCArray_Get(pStrCArray, 1);
        TINYTEST_TRUE((ERESULT_SUCCESS_EQUAL == AStrC_CompareA(pStrC,"macos")));
    }
    pStrCArray = NodeTest_getSrcs(pTest);
    TINYTEST_FALSE( (OBJ_NIL == pStrCArray) );
    if (pStrCArray) {
        TINYTEST_TRUE((1 == AStrCArray_getSize(pStrCArray)));
        pStrC = AStrCArray_Get(pStrCArray, 1);
        eRc = AStrC_CompareA(pStrC,"$(TEST_SRC)/abc.c");
        TINYTEST_TRUE((ERESULT_SUCCESS_EQUAL == eRc));
    }

    obj_Release(pNodes);
    pNodes = OBJ_NIL;
    
    obj_Release(pRtn);
    pRtn = OBJ_NIL;

    fprintf(stderr, "...%s completed.\n\n\n\n", pTestName);
    return 1;
}



int             test_NodeRtn_Parse02(
    const
    char            *pTestName
)
{
    ERESULT_DATA    *pErr = OBJ_NIL;
    //NODE_DATA       *pNode = OBJ_NIL;
    NODE_DATA       *pNodes = OBJ_NIL;
    NODEHASH_DATA   *pHash = OBJ_NIL;
    ASTRCARRAY_DATA *pStrCArray = OBJ_NIL;
    ASTRC_DATA      *pStrC = OBJ_NIL;
    NODERTN_DATA    *pRtn = OBJ_NIL;
    NODETEST_DATA   *pTest = OBJ_NIL;
    const
    char            *pGoodJsonObject1 =
        "{name:\"dllist\", "
        "\"os\":[\"win32\",\"win64\"]"
        "}\n";
    bool            fDump = true;

    fprintf(stderr, "Performing: %s\n", pTestName);

    // Process the JSON data.
    pErr = InputStrToJSON(pGoodJsonObject1, &pNodes);
    TINYTEST_TRUE( (OBJ_NIL == pErr) );
    TINYTEST_FALSE( (OBJ_NIL == pNodes) );
    TINYTEST_TRUE( (obj_IsKindOf(pNodes, OBJ_IDENT_NODE)) );
    pHash = node_getData(pNodes);
    TINYTEST_FALSE( (OBJ_NIL == pHash) );
    TINYTEST_TRUE( (obj_IsKindOf(pHash, OBJ_IDENT_NODEHASH)) );

    if (fDump) {
        ASTR_DATA       *pWrk = OBJ_NIL;
        pWrk = node_ToDebugString(pNodes, 0);
        fprintf(stderr, "Parsed JSON:\n%s\n\n\n", AStr_getData(pWrk));
        obj_Release(pWrk);
        pWrk = OBJ_NIL;
    }

    // Parse the Object.
    //obj_TraceSet(pBase, true);
    pErr = NodeRtn_Parse(pNodes, &pRtn);
    if (pErr) {
        fprintf(stderr, "%s\n", eResult_getErrorA(pErr));
    }
    TINYTEST_TRUE((OBJ_NIL == pErr));
    
    // Display the Output.
    if (pRtn && fDump) {
        fprintf(stderr, "===> NodeObj:\n\n");
        ASTR_DATA   *pStr = NodeRtn_ToDebugString(pRtn, 0);
        fprintf(stderr, "%s\n", AStr_getData(pStr));
        obj_Release(pStr);
        pStr = OBJ_NIL;
    }

    // Validate the output.
    pStrC = NodeRtn_getName(pRtn);
    TINYTEST_FALSE( (OBJ_NIL == pStrC) );
    TINYTEST_TRUE((ERESULT_SUCCESS_EQUAL == AStrC_CompareA(pStrC,"dllist")));
    pStrCArray = NodeRtn_getArches(pRtn);
    TINYTEST_FALSE( (OBJ_NIL == pStrCArray) );
    if (pStrCArray) {
        TINYTEST_TRUE((0 == AStrCArray_getSize(pStrCArray)));
    }
    pStrCArray = NodeRtn_getOSs(pRtn);
    TINYTEST_FALSE( (OBJ_NIL == pStrCArray) );
    if (pStrCArray) {
        TINYTEST_TRUE((2 == AStrCArray_getSize(pStrCArray)));
        pStrC = AStrCArray_Get(pStrCArray, 1);
        TINYTEST_TRUE((ERESULT_SUCCESS_EQUAL == AStrC_CompareA(pStrC,"win32")));
        pStrC = AStrCArray_Get(pStrCArray, 2);
        TINYTEST_TRUE((ERESULT_SUCCESS_EQUAL == AStrC_CompareA(pStrC,"win64")));
    }
    pStrCArray = NodeRtn_getDeps(pRtn);
    TINYTEST_FALSE( (OBJ_NIL == pStrCArray) );
    if (pStrCArray) {
        TINYTEST_TRUE((0 == AStrCArray_getSize(pStrCArray)));
    }
    pStrCArray = NodeRtn_getSrcs(pRtn);
    TINYTEST_FALSE( (OBJ_NIL == pStrCArray) );
    if (pStrCArray) {
        TINYTEST_TRUE((0 == AStrCArray_getSize(pStrCArray)));
    }
    pTest = NodeRtn_getTest(pRtn);
    TINYTEST_TRUE( (OBJ_NIL == pTest) );

    obj_Release(pNodes);
    pNodes = OBJ_NIL;
    
    obj_Release(pRtn);
    pRtn = OBJ_NIL;

    fprintf(stderr, "...%s completed.\n\n\n\n", pTestName);
    return 1;
}




TINYTEST_START_SUITE(test_NodeRtn);
    TINYTEST_ADD_TEST(test_NodeRtn_Parse02,setUp,tearDown);
    TINYTEST_ADD_TEST(test_NodeRtn_Parse01,setUp,tearDown);
    TINYTEST_ADD_TEST(test_NodeRtn_OpenClose,setUp,tearDown);
TINYTEST_END_SUITE();

TINYTEST_MAIN_SINGLE_SUITE(test_NodeRtn);





