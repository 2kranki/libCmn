// vi:nu:et:sts=4 ts=4 sw=4
/*
 *	Generated 11/03/2019 08:11:26
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
#include    <nodeHash.h>
#include    <srcErrors.h>
#include    <szTbl.h>
#include    <trace.h>
#include    <NodeObj_internal.h>



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

    if (OBJ_NIL == pFileNode) {
        fprintf(stderr, "ERROR - No JSON Nodes to process\n\n\n");
        exit(12);
    }
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

    // Return to caller.
    if (ppNodes) {
        *ppNodes = pFileNode;
    }
    return pErr;
}







int             test_NodeObj_OpenClose(
    const
    char            *pTestName
)
{
    ERESULT         eRc = ERESULT_SUCCESS;
    NODEOBJ_DATA	    *pObj = OBJ_NIL;
   
    fprintf(stderr, "Performing: %s\n", pTestName);

    pObj = NodeObj_Alloc( );
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    pObj = NodeObj_Init( pObj );
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



int             test_NodeObj_Parse01(
    const
    char            *pTestName
)
{
    ERESULT         eRc;
    ERESULT_DATA    *pErr = OBJ_NIL;
    //NODE_DATA       *pNode = OBJ_NIL;
    NODE_DATA       *pNodes = OBJ_NIL;
    NODEHASH_DATA   *pHash = OBJ_NIL;
    NODEOBJ_DATA    *pObj = OBJ_NIL;
    NODERTN_DATA    *pJson = OBJ_NIL;
    NODETEST_DATA   *pTest = OBJ_NIL;
    ASTRCARRAY_DATA *pStrCArray = OBJ_NIL;
    ASTRC_DATA      *pStrC = OBJ_NIL;
    const
    char            *pGoodJsonObject1 =
        "{name:\"AStr\", "
        "\"deps\":[\"cmn_defs.h\",\"array.h\"],"
        "\"srcs\":[\"str.c\",\"ascii.c\"],"
        "\"json\":true,"
        "\"test\":{\"arch\":\"X86\",\"os\":\"macos\",srcs:[\"abc.c\"]}"
        "}\n";
    bool            fDumpNodes = true;
    uint32_t        size;

    fprintf(stderr, "Performing: %s\n", pTestName);

    // Process the JSON data.
    pErr = InputStrToJSON(pGoodJsonObject1, &pNodes);
    TINYTEST_TRUE( (OBJ_NIL == pErr) );
    TINYTEST_FALSE( (OBJ_NIL == pNodes) );
    TINYTEST_TRUE( (obj_IsKindOf(pNodes, OBJ_IDENT_NODE)) );
    pHash = node_getData(pNodes);
    TINYTEST_FALSE( (OBJ_NIL == pHash) );
    TINYTEST_TRUE( (obj_IsKindOf(pHash, OBJ_IDENT_NODEHASH)) );
    
    if (fDumpNodes) {
        ASTR_DATA       *pWrk = OBJ_NIL;
        pWrk = node_ToDebugString(pNodes, 0);
        fprintf(stderr, "Parsed JSON:\n%s\n\n\n", AStr_getData(pWrk));
        obj_Release(pWrk);
        pWrk = OBJ_NIL;
    }

    // Parse the Object.
    //obj_TraceSet(pBase, true);
    pErr = NodeObj_Parse(pNodes, &pObj);
    if (pErr) {
        fprintf(stderr, "%s\n", eResult_getErrorA(pErr));
    }
    TINYTEST_TRUE((OBJ_NIL == pErr));
    // Note: pHashOut is only valid until you release pNodes.
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    TINYTEST_TRUE((obj_IsKindOf(pObj, OBJ_IDENT_NODEOBJ)));

    // Display the Output.
    if (pObj) {
        fprintf(stderr, "=====> NodeObj:\n\n");
        ASTR_DATA   *pStr = NodeObj_ToDebugString(pObj, 0);
        fprintf(stderr, "%s\n", AStr_getData(pStr));
        obj_Release(pStr);
        pStr = OBJ_NIL;
    }

    // Validate the output.
    pStrC = NodeObj_getName(pObj);
    TINYTEST_FALSE( (OBJ_NIL == pStrC) );
    TINYTEST_TRUE((ERESULT_SUCCESS_EQUAL == AStrC_CompareA(pStrC, "AStr")));
    pStrCArray = NodeObj_getArches(pObj);
    TINYTEST_FALSE( (OBJ_NIL == pStrCArray) );
    if (pStrCArray) {
        TINYTEST_TRUE((0 == AStrCArray_getSize(pStrCArray)));
    }
    pStrCArray = NodeObj_getOSs(pObj);
    TINYTEST_FALSE( (OBJ_NIL == pStrCArray) );
    if (pStrCArray) {
        TINYTEST_TRUE((0 == AStrCArray_getSize(pStrCArray)));
    }
    pStrCArray = NodeObj_getDeps(pObj);
    TINYTEST_FALSE( (OBJ_NIL == pStrCArray) );
    if (pStrCArray) {
        size = AStrCArray_getSize(pStrCArray);
        fprintf(stderr, "Deps Size: %d\n", size);
        TINYTEST_TRUE((4 == size));
        pStrC = AStrCArray_Get(pStrCArray, 1);
        fprintf(stderr, "dep1: %s\n", AStrC_getData(pStrC));
        eRc = AStrC_CompareA(pStrC,"$(SRCDIR)/AStr.h");
        TINYTEST_TRUE((ERESULT_SUCCESS_EQUAL == eRc));
        pStrC = AStrCArray_Get(pStrCArray, 2);
        fprintf(stderr, "dep2: %s\n", AStrC_getData(pStrC));
        eRc = AStrC_CompareA(pStrC,"$(SRCDIR)/AStr_internal.h");
        TINYTEST_TRUE((ERESULT_SUCCESS_EQUAL == eRc));
        pStrC = AStrCArray_Get(pStrCArray, 3);
        fprintf(stderr, "dep3: %s\n", AStrC_getData(pStrC));
        eRc = AStrC_CompareA(pStrC,"$(SRCDIR)/array.h");
        TINYTEST_TRUE((ERESULT_SUCCESS_EQUAL == eRc));
        pStrC = AStrCArray_Get(pStrCArray, 4);
        fprintf(stderr, "dep4: %s\n", AStrC_getData(pStrC));
        eRc = AStrC_CompareA(pStrC,"$(SRCDIR)/cmn_defs.h");
        TINYTEST_TRUE((ERESULT_SUCCESS_EQUAL == eRc));
    }
    pStrCArray = NodeObj_getSrcs(pObj);
    TINYTEST_FALSE( (OBJ_NIL == pStrCArray) );
    if (pStrCArray) {
        size = AStrCArray_getSize(pStrCArray);
        fprintf(stderr, "Srcs Size: %d\n", size);
        TINYTEST_TRUE((2 == size));
        pStrC = AStrCArray_Get(pStrCArray, 1);
        fprintf(stderr, "src1: %s\n", AStrC_getData(pStrC));
        eRc = AStrC_CompareA(pStrC,"$(SRCDIR)/ascii.c");
        TINYTEST_TRUE((ERESULT_SUCCESS_EQUAL == eRc));
        pStrC = AStrCArray_Get(pStrCArray, 2);
        fprintf(stderr, "src2: %s\n", AStrC_getData(pStrC));
        eRc = AStrC_CompareA(pStrC,"$(SRCDIR)/str.c");
        TINYTEST_TRUE((ERESULT_SUCCESS_EQUAL == eRc));
    }
    pJson = NodeObj_getJson(pObj);
    TINYTEST_FALSE( (OBJ_NIL == pJson) );
    if (pJson) {
        pStrC = NodeRtn_getName(pJson);
        TINYTEST_TRUE((ERESULT_SUCCESS_EQUAL == AStrC_CompareA(pStrC,"AStr_json")));
    }
    pTest = NodeObj_getTest(pObj);
    TINYTEST_FALSE( (OBJ_NIL == pTest) );
    if (pTest) {
        pStrC = NodeTest_getName(pTest);
        TINYTEST_TRUE((ERESULT_SUCCESS_EQUAL == AStrC_CompareA(pStrC,"AStr_test")));
    }

    obj_Release(pNodes);
    pNodes = OBJ_NIL;
    
    obj_Release(pObj);
    pObj = OBJ_NIL;

    fprintf(stderr, "...%s completed.\n\n\n\n", pTestName);
    return 1;
}




TINYTEST_START_SUITE(test_NodeObj);
    TINYTEST_ADD_TEST(test_NodeObj_Parse01,setUp,tearDown);
    TINYTEST_ADD_TEST(test_NodeObj_OpenClose,setUp,tearDown);
TINYTEST_END_SUITE();

TINYTEST_MAIN_SINGLE_SUITE(test_NodeObj);





