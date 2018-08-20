/*
 *	Generated 08/12/2018 14:34:38
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
#include    <trace.h>
#include    <sgraph_internal.h>



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






int             test_sgraph_OpenClose(
    const
    char            *pTestName
)
{
    SGRAPH_DATA	    *pObj = OBJ_NIL;
   
    fprintf(stderr, "Performing: %s\n", pTestName);

    pObj = sgraph_Alloc( );
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    pObj = sgraph_Init( pObj );
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    if (pObj) {

        // Test something.

        obj_Release(pObj);
        pObj = OBJ_NIL;
    }

    fprintf(stderr, "...%s completed.\n\n", pTestName);
    return 1;
}



int             test_sgraph_Nodes01(
    const
    char            *pTestName
)
{
    ERESULT         eRc;
    SGRAPH_DATA     *pObj = OBJ_NIL;
    NODE_DATA       *pNode = OBJ_NIL;
    U32ARRAY_DATA   *pSet = OBJ_NIL;
    
    fprintf(stderr, "Performing: %s\n", pTestName);
    
    pObj = sgraph_Alloc( );
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    pObj = sgraph_Init( pObj );
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    if (pObj) {
        
        pNode = node_NewWithInt(1, OBJ_NIL);
        eRc = sgraph_NodeAdd(pObj, pNode);
        obj_Release(pNode);
        pNode = OBJ_NIL;
        TINYTEST_TRUE( (1 == bitMatrix_getXSize(pObj->pEdges)) );
        TINYTEST_TRUE( (1 == bitMatrix_getYSize(pObj->pEdges)) );

        pNode = node_NewWithInt(2, OBJ_NIL);
        eRc = sgraph_NodeAdd(pObj, pNode);
        obj_Release(pNode);
        pNode = OBJ_NIL;
        TINYTEST_TRUE( (2 == bitMatrix_getXSize(pObj->pEdges)) );
        TINYTEST_TRUE( (2 == bitMatrix_getYSize(pObj->pEdges)) );

        eRc = sgraph_EdgeAdd(pObj, 1, 1);
        TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );
        eRc = sgraph_EdgeExists(pObj, 1, 1);
        TINYTEST_TRUE( (ERESULT_SUCCESS_TRUE == eRc) );
        eRc = sgraph_EdgeExists(pObj, 1, 2);
        TINYTEST_TRUE( (ERESULT_SUCCESS_FALSE == eRc) );
        eRc = sgraph_EdgeExists(pObj, 1, 3);
        TINYTEST_TRUE( (ERESULT_FAILED(eRc)) );
        eRc = sgraph_EdgeAdd(pObj, 1, 2);
        TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );
        eRc = sgraph_EdgeExists(pObj, 1, 1);
        TINYTEST_TRUE( (ERESULT_SUCCESS_TRUE == eRc) );
        eRc = sgraph_EdgeExists(pObj, 1, 2);
        TINYTEST_TRUE( (ERESULT_SUCCESS_TRUE == eRc) );
        eRc = sgraph_EdgeExists(pObj, 1, 3);
        TINYTEST_TRUE( (ERESULT_FAILED(eRc)) );
#ifdef NDEBUG
#else
        {
            ASTR_DATA       *pStr = OBJ_NIL;
            pStr = bitMatrix_ToDebugString(pObj->pEdges, 8);
            fprintf(stderr, "\tEdges:\n%s\n", AStr_getData(pStr));
            obj_Release(pStr);
            pStr = OBJ_NIL;
        }
#endif

        pSet = sgraph_NodePred(pObj, 1);
        TINYTEST_FALSE( (OBJ_NIL == pSet) );
#ifdef NDEBUG
#else
        {
            ASTR_DATA       *pStr = OBJ_NIL;
            pStr = u32Array_ToDebugString(pSet, 8);
            fprintf(stderr, "\tPred 1 Set:\n%s\n", AStr_getData(pStr));
            obj_Release(pStr);
            pStr = OBJ_NIL;
        }
#endif
        TINYTEST_TRUE( (1 == u32Array_getSize(pSet)) );
        TINYTEST_TRUE( (1 == u32Array_Get(pSet, 1)) );
        obj_Release(pSet);
        pSet = OBJ_NIL;
        
        pSet = sgraph_NodeSucc(pObj, 1);
        TINYTEST_FALSE( (OBJ_NIL == pSet) );
#ifdef NDEBUG
#else
        {
            ASTR_DATA       *pStr = OBJ_NIL;
            pStr = u32Array_ToDebugString(pSet, 8);
            fprintf(stderr, "\tSucc 1 Set:\n%s\n", AStr_getData(pStr));
            obj_Release(pStr);
            pStr = OBJ_NIL;
        }
#endif
        TINYTEST_TRUE( (2 == u32Array_getSize(pSet)) );
        TINYTEST_TRUE( (1 == u32Array_Get(pSet, 1)) );
        TINYTEST_TRUE( (2 == u32Array_Get(pSet, 2)) );
        obj_Release(pSet);
        pSet = OBJ_NIL;
        
        pSet = sgraph_NodePred(pObj, 2);
        TINYTEST_FALSE( (OBJ_NIL == pSet) );
#ifdef NDEBUG
#else
        {
            ASTR_DATA       *pStr = OBJ_NIL;
            pStr = u32Array_ToDebugString(pSet, 8);
            fprintf(stderr, "\tPred 2 Set:\n%s\n", AStr_getData(pStr));
            obj_Release(pStr);
            pStr = OBJ_NIL;
        }
#endif
        TINYTEST_TRUE( (1 == u32Array_getSize(pSet)) );
        TINYTEST_TRUE( (1 == u32Array_Get(pSet, 1)) );
        obj_Release(pSet);
        pSet = OBJ_NIL;

        pSet = sgraph_NodeSucc(pObj, 2);
        TINYTEST_FALSE( (OBJ_NIL == pSet) );
#ifdef NDEBUG
#else
        {
            ASTR_DATA       *pStr = OBJ_NIL;
            pStr = u32Array_ToDebugString(pSet, 8);
            fprintf(stderr, "\tSucc 2 Set:\n%s\n", AStr_getData(pStr));
            obj_Release(pStr);
            pStr = OBJ_NIL;
        }
#endif
        TINYTEST_TRUE( (0 == u32Array_getSize(pSet)) );
        obj_Release(pSet);
        pSet = OBJ_NIL;
        
        pSet = sgraph_NodeAdj(pObj, 1);
        TINYTEST_FALSE( (OBJ_NIL == pSet) );
#ifdef NDEBUG
#else
        {
            ASTR_DATA       *pStr = OBJ_NIL;
            pStr = u32Array_ToDebugString(pSet, 8);
            fprintf(stderr, "\tAdj 1 Set:\n%s\n", AStr_getData(pStr));
            obj_Release(pStr);
            pStr = OBJ_NIL;
        }
#endif
        TINYTEST_TRUE( (2 == u32Array_getSize(pSet)) );
        TINYTEST_TRUE( (1 == u32Array_Get(pSet, 1)) );
        TINYTEST_TRUE( (2 == u32Array_Get(pSet, 2)) );
        obj_Release(pSet);
        pSet = OBJ_NIL;
        
        obj_Release(pObj);
        pObj = OBJ_NIL;
    }
    
    fprintf(stderr, "...%s completed.\n\n", pTestName);
    return 1;
}




TINYTEST_START_SUITE(test_sgraph);
    TINYTEST_ADD_TEST(test_sgraph_Nodes01,setUp,tearDown);
    TINYTEST_ADD_TEST(test_sgraph_OpenClose,setUp,tearDown);
TINYTEST_END_SUITE();

TINYTEST_MAIN_SINGLE_SUITE(test_sgraph);





