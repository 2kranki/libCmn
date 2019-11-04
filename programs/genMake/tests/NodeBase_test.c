/*
 *	Generated 11/03/2019 08:11:17
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
#include    <trace.h>
#include    <NodeBase_internal.h>



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



ERESULT         InputStrToJSON(
    const
    char            *pStrA,
    NODE_DATA       **ppNodes
)
{
    HJSON_DATA      *pObj = OBJ_NIL;
    NODEHASH_DATA   *pHash;
    NODE_DATA       *pFileNode = OBJ_NIL;

    // Do initialization.
#ifdef NDEBUG
#else
    if (NULL == pStrA) {
        DEBUG_BREAK();
        return ERESULT_INVALID_PARAMETER;
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
    return ERESULT_SUCCESS;
}






int             test_NodeBase_OpenClose(
    const
    char            *pTestName
)
{
    ERESULT         eRc = ERESULT_SUCCESS;
    NODEBASE_DATA	    *pObj = OBJ_NIL;
   
    fprintf(stderr, "Performing: %s\n", pTestName);

    pObj = NodeBase_Alloc( );
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    pObj = NodeBase_Init( pObj );
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



int             test_NodeBase_Parse01(
    const
    char            *pTestName
)
{
    ERESULT         eRc;
    NODE_DATA       *pNode = OBJ_NIL;
    NODE_DATA       *pNodes = OBJ_NIL;
    NODEHASH_DATA   *pHash;
    NODEHASH_DATA   *pHashOut;
    NODEARRAY_DATA  *pOutNodes = OBJ_NIL;
    NODEBASE_DATA   *pBase = OBJ_NIL;
    uint32_t        i;
    uint32_t        iMax;
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

    //pObj = dbprs_New( );
    //TINYTEST_FALSE( (OBJ_NIL == pObj) );
    //if (pObj) {

        // Process the JSON data.
        //obj_TraceSet(pObj, true);
        eRc = InputStrToJSON(pGoodJsonObject1, &pNodes);
        TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );
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
        pNode = nodeHash_FindA(pHash, 0, "AStr");
        TINYTEST_FALSE( (OBJ_NIL == pNode) );
        TINYTEST_TRUE((obj_IsKindOf(pNode, OBJ_IDENT_NODE)));
        pHash = node_getData(pNode);
        TINYTEST_FALSE( (OBJ_NIL == pNode) );
        TINYTEST_TRUE((obj_IsKindOf(pNode, OBJ_IDENT_NODEHASH)));
        eRc = NodeBase_ParseSubObj(pNode, &pBase, &pHashOut);
        TINYTEST_FALSE((ERESULT_FAILED(eRc)));
        TINYTEST_FALSE( (OBJ_NIL == pOutNodes) );
        TINYTEST_TRUE((4 == nodeArray_getSize(pOutNodes)));

        // Display the Output.
#ifdef XYZZY
        {
            fprintf(stderr, "===> OutNodes:\n\n");
            ASTR_DATA   *pStr = nodeArray_ToDebugString(pOutNodes, 0);
            fprintf(stderr, "%s\n", AStr_getData(pStr));
            obj_Release(pStr);
            pStr = OBJ_NIL;
        }
#endif
        fprintf(stderr, "===> OutNodes:\n\n");
        iMax = nodeArray_getSize(pOutNodes);
        for (i=0; i<iMax; i++) {
            NODE_DATA   *pNode = nodeArray_Get(pOutNodes, i+1);
            ASTR_DATA   *pStr = NodeBase_ToString((NODEBASE_DATA *)pNode);
            fprintf(stderr, "%s\n", AStr_getData(pStr));
            obj_Release(pStr);
        }

#ifdef XYZZY
        // Validate the output.
        pNode = nodeArray_Get(pOutNodes, 1);
        TINYTEST_FALSE( (OBJ_NIL == pNode) );
        TINYTEST_TRUE((obj_IsKindOf(pNode, MAIN_IDENT_RTNNODE)));
        pBase = rtnNode_getBase((RTNNODE_DATA *)pNode);
        TINYTEST_TRUE((ERESULT_SUCCESS_EQUAL == AStr_CompareA(baseNode_getName(pBase),
                                                              "AStr")));
        TINYTEST_TRUE((4 == AStrArray_getSize(baseNode_getDeps(pBase))));
        TINYTEST_TRUE((2 == AStrArray_getSize(baseNode_getSrcs(pBase))));

        pNode = nodeArray_Get(pOutNodes, 2);
        TINYTEST_FALSE( (OBJ_NIL == pNode) );
        TINYTEST_TRUE((obj_IsKindOf(pNode, MAIN_IDENT_RTNNODE)));
        pBase = rtnNode_getBase((RTNNODE_DATA *)pNode);
        TINYTEST_TRUE((ERESULT_SUCCESS_EQUAL == AStr_CompareA(baseNode_getName(pBase),
                                                              "AStr_object")));
        TINYTEST_TRUE((2 == AStrArray_getSize(baseNode_getDeps(pBase))));
        TINYTEST_TRUE((0 == AStrArray_getSize(baseNode_getSrcs(pBase))));
#endif

        obj_Release(pOutNodes);
        pOutNodes = OBJ_NIL;

        obj_Release(pNodes);
        pNodes = OBJ_NIL;
    //}

    fprintf(stderr, "...%s completed.\n\n\n\n", pTestName);
    return 1;
}




TINYTEST_START_SUITE(test_NodeBase);
    TINYTEST_ADD_TEST(test_NodeBase_Parse01,setUp,tearDown);
    TINYTEST_ADD_TEST(test_NodeBase_OpenClose,setUp,tearDown);
TINYTEST_END_SUITE();

TINYTEST_MAIN_SINGLE_SUITE(test_NodeBase);





