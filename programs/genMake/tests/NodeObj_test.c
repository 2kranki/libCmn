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
        pFileNode = hjson_ParseFileHash(pObj);
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
    ERESULT_DATA    *pErr = OBJ_NIL;
    NODE_DATA       *pNode = OBJ_NIL;
    NODE_DATA       *pNodeAStr = OBJ_NIL;
    NODE_DATA       *pNodes = OBJ_NIL;
    NODEHASH_DATA   *pHash;
    NODEHASH_DATA   *pHashOut;
    ASTRARRAY_DATA  *pStrArray = OBJ_NIL;
    ASTR_DATA       *pStr = OBJ_NIL;
    NODEBASE_DATA   *pBase = OBJ_NIL;
    const
    char            *pGoodJsonObject1 =
        "{\n"
        "\"AStr\":{"
        "\"deps\":[\"cmn_defs.h\",\"array.h\"],"
        "\"srcs\":[\"str.c\",\"ascii.c\"],"
        "\"json\":true,"
        "\"test\":{\"reqArch\":\"X86\",\"reqOS\":\"macos\",srcs:[\"abc.c\"]}"
        "}\n"
        "}\n";

    fprintf(stderr, "Performing: %s\n", pTestName);

    pBase = NodeBase_New( );
    TINYTEST_FALSE( (OBJ_NIL == pBase) );
    if (pBase) {

        // Process the JSON data.
        pErr = InputStrToJSON(pGoodJsonObject1, &pNodes);
        TINYTEST_TRUE( (OBJ_NIL == pErr) );
        TINYTEST_FALSE( (OBJ_NIL == pNodes) );
        TINYTEST_TRUE( (obj_IsKindOf(pNodes, OBJ_IDENT_NODE)) );
        pHash = node_getData(pNodes);
        TINYTEST_FALSE( (OBJ_NIL == pHash) );
        if (pHash) {
            ASTR_DATA       *pWrk = OBJ_NIL;
            pWrk = nodeHash_ToDebugString(pHash, 0);
            fprintf(stderr, "Parsed JSON:\n%s\n\n\n", AStr_getData(pWrk));
            obj_Release(pWrk);
            pWrk = OBJ_NIL;
        }

        // Parse the Object.
        //obj_TraceSet(pBase, true);
        pNodeAStr = nodeHash_FindA(pHash, 0, "AStr");
        TINYTEST_FALSE( (OBJ_NIL == pNodeAStr) );
        TINYTEST_TRUE((obj_IsKindOf(pNodeAStr, OBJ_IDENT_NODE)));
        pNode = node_getData(pNodeAStr);
        TINYTEST_FALSE( (OBJ_NIL == pNode) );
        TINYTEST_TRUE((obj_IsKindOf(pNode, OBJ_IDENT_NODE)));
        pErr = NodeBase_ParseSubObj(pNode, &pBase, &pHashOut);
        if (pErr) {
            fprintf(stderr, "%s\n", eResult_getErrorA(pErr));
        }
        TINYTEST_TRUE((OBJ_NIL == pErr));
        // Note: pHashOut is only valid until you release pNodes.
        TINYTEST_FALSE( (OBJ_NIL == pHashOut) );
        pHash = jsonIn_CheckNodeDataForHash(pNodeAStr);
        TINYTEST_TRUE((pHash == pHashOut));
        
        // Display the Output.
        if (pBase) {
            fprintf(stderr, "===> NodeBase:\n\n");
            ASTR_DATA   *pStr = NodeBase_ToDebugString(pBase, 0);
            fprintf(stderr, "%s\n", AStr_getData(pStr));
            obj_Release(pStr);
            pStr = OBJ_NIL;
        }

        // Validate the output.
        pErr = NodeBase_SortArrays(pBase);
        TINYTEST_TRUE( (OBJ_NIL == pErr) );
        pStr = NodeBase_getName(pBase);
        TINYTEST_TRUE( (OBJ_NIL == pStr) );
        pStr = NodeBase_getReqArch(pBase);
        TINYTEST_TRUE( (OBJ_NIL == pStr) );
        pStr = NodeBase_getReqOS(pBase);
        TINYTEST_TRUE( (OBJ_NIL == pStr) );
        pStrArray = NodeBase_getDeps(pBase);
        TINYTEST_FALSE( (OBJ_NIL == pStrArray) );
        if (pStrArray) {
            TINYTEST_TRUE((2 == AStrArray_getSize(pStrArray)));
            pStr = AStrArray_Get(pStrArray, 1);
            TINYTEST_TRUE((ERESULT_SUCCESS_EQUAL == AStr_CompareA(pStr,"array.h")));
            pStr = AStrArray_Get(pStrArray, 2);
            TINYTEST_TRUE((ERESULT_SUCCESS_EQUAL == AStr_CompareA(pStr,"cmn_defs.h")));
        }
        pStrArray = NodeBase_getSrcs(pBase);
        TINYTEST_FALSE( (OBJ_NIL == pStrArray) );
        if (pStrArray) {
            TINYTEST_TRUE((2 == AStrArray_getSize(pStrArray)));
            pStr = AStrArray_Get(pStrArray, 1);
            TINYTEST_TRUE((ERESULT_SUCCESS_EQUAL == AStr_CompareA(pStr,"ascii.c")));
            pStr = AStrArray_Get(pStrArray, 2);
            TINYTEST_TRUE((ERESULT_SUCCESS_EQUAL == AStr_CompareA(pStr,"str.c")));
        }

        obj_Release(pNodes);
        pNodes = OBJ_NIL;
        
        obj_Release(pBase);
        pBase = OBJ_NIL;
    }

    fprintf(stderr, "...%s completed.\n\n\n\n", pTestName);
    return 1;
}




TINYTEST_START_SUITE(test_NodeObj);
    TINYTEST_ADD_TEST(test_NodeObj_Parse01,setUp,tearDown);
    TINYTEST_ADD_TEST(test_NodeObj_OpenClose,setUp,tearDown);
TINYTEST_END_SUITE();

TINYTEST_MAIN_SINGLE_SUITE(test_NodeObj);





