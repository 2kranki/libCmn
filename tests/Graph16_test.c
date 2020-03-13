// vi:nu:et:sts=4 ts=4 sw=4
/*
 *	Generated 03/11/2020 17:37:49
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
#include    <Graph16_internal.h>
#ifdef  GRAPH16_JSON_SUPPORT
#   include    <SrcErrors.h>
#   include    <szTbl.h>
#endif



int             setUp (
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


int             tearDown (
    const
    char            *pTestName
)
{
    // Put teardown code here. This method is called after the invocation of each
    // test method in the class.

#ifdef  GRAPH16_JSON_SUPPORT
    SrcErrors_SharedReset( );
    szTbl_SharedReset( );
#endif
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






int             test_Graph16_OpenClose (
    const
    char            *pTestName
)
{
    ERESULT         eRc = ERESULT_SUCCESS;
    GRAPH16_DATA	    *pObj = OBJ_NIL;
    bool            fRc;
   
    fprintf(stderr, "Performing: %s\n", pTestName);

    pObj = Graph16_Alloc( );
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    pObj = Graph16_Init( pObj );
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    if (pObj) {

        //obj_TraceSet(pObj, true);       
        fRc = obj_IsKindOf(pObj, OBJ_IDENT_GRAPH16);
        TINYTEST_TRUE( (fRc) );
        
        // Test something.
        TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );

        obj_Release(pObj);
        pObj = OBJ_NIL;
    }

    fprintf(stderr, "...%s completed.\n\n\n", pTestName);
    return 1;
}



int             test_Graph16_Copy01 (
    const
    char            *pTestName
)
{
    ERESULT         eRc = ERESULT_SUCCESS;
    GRAPH16_DATA	    *pObj1 = OBJ_NIL;
    GRAPH16_DATA	    *pObj2 = OBJ_NIL;
    bool            fRc;
    ASTR_DATA	    *pStr = OBJ_NIL;

    fprintf(stderr, "Performing: %s\n", pTestName);

    pObj1 = Graph16_NewWithSizes(4, 6);
    TINYTEST_FALSE( (OBJ_NIL == pObj1) );
    if (pObj1) {

        //obj_TraceSet(pObj1, true);       
        fRc = obj_IsKindOf(pObj1, OBJ_IDENT_GRAPH16);
        TINYTEST_TRUE( (fRc) );
        eRc = Graph16_EdgeSet(pObj1, 1, 1, 2);
        TINYTEST_TRUE( (ERESULT_OK(eRc)) );
        eRc = Graph16_EdgeSet(pObj1, 2, 1, 3);
        TINYTEST_TRUE( (ERESULT_OK(eRc)) );
        eRc = Graph16_EdgeSet(pObj1, 3, 2, 4);
        TINYTEST_TRUE( (ERESULT_OK(eRc)) );
        eRc = Graph16_EdgeSet(pObj1, 4, 3, 4);
        TINYTEST_TRUE( (ERESULT_OK(eRc)) );
        eRc = Graph16_EdgeSet(pObj1, 5, 3, 2);
        TINYTEST_TRUE( (ERESULT_OK(eRc)) );
        eRc = Graph16_EdgeSet(pObj1, 6, 2, 3);
        TINYTEST_TRUE( (ERESULT_OK(eRc)) );
        TINYTEST_TRUE( (6 == pObj1->edgesMax) );
        TINYTEST_TRUE( (6 == pObj1->edgesUsed) );
        TINYTEST_TRUE( (2 == Graph16_EdgeFrom(pObj1, 3)) );
        TINYTEST_TRUE( (4 == Graph16_EdgeTo(pObj1, 3)) );
        TINYTEST_TRUE( (2 == Graph16_EdgeFrom(pObj1, 6)) );
        TINYTEST_TRUE( (3 == Graph16_EdgeTo(pObj1, 6)) );

        // Test assign.
        pObj2 = Graph16_New();
        TINYTEST_FALSE( (OBJ_NIL == pObj2) );
        eRc = Graph16_Assign(pObj1, pObj2);
        TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );

        fRc = obj_IsKindOf(pObj2, OBJ_IDENT_GRAPH16);
        TINYTEST_TRUE( (fRc) );
        TINYTEST_TRUE( (6 == pObj2->edgesMax) );
        TINYTEST_TRUE( (6 == pObj2->edgesUsed) );
        TINYTEST_TRUE( (2 == Graph16_EdgeFrom(pObj2, 3)) );
        TINYTEST_TRUE( (4 == Graph16_EdgeTo(pObj2, 3)) );
        TINYTEST_TRUE( (2 == Graph16_EdgeFrom(pObj2, 6)) );
        TINYTEST_TRUE( (3 == Graph16_EdgeTo(pObj2, 6)) );

        obj_Release(pObj2);
        pObj2 = OBJ_NIL;

        // Test copy.
        pObj2 = Graph16_Copy(pObj1);
        TINYTEST_FALSE( (OBJ_NIL == pObj2) );

        fRc = obj_IsKindOf(pObj2, OBJ_IDENT_GRAPH16);
        TINYTEST_TRUE( (fRc) );
        TINYTEST_TRUE( (6 == pObj2->edgesMax) );
        TINYTEST_TRUE( (6 == pObj2->edgesUsed) );
        TINYTEST_TRUE( (2 == Graph16_EdgeFrom(pObj2, 3)) );
        TINYTEST_TRUE( (4 == Graph16_EdgeTo(pObj2, 3)) );
        TINYTEST_TRUE( (2 == Graph16_EdgeFrom(pObj2, 6)) );
        TINYTEST_TRUE( (3 == Graph16_EdgeTo(pObj2, 6)) );

        obj_Release(pObj2);
        pObj2 = OBJ_NIL;

        // Test json support.
        pStr = Graph16_ToJson(pObj1);
        TINYTEST_FALSE( (OBJ_NIL == pStr) );
        fprintf(stderr, "JSON: %s\n", AStr_getData(pStr));
        pObj2 = Graph16_NewFromJsonString(pStr);
        TINYTEST_FALSE( (OBJ_NIL == pObj2) );
        fRc = obj_IsKindOf(pObj2, OBJ_IDENT_GRAPH16);
        TINYTEST_TRUE( (fRc) );
        obj_Release(pStr);
        pStr = OBJ_NIL;
        //eRc = Graph16_Compare(pObj1, pObj2);
        //TINYTEST_TRUE( (ERESULT_SUCCESS_EQUAL == eRc) );

        obj_Release(pObj2);
        pObj2 = OBJ_NIL;

        obj_Release(pObj1);
        pObj1 = OBJ_NIL;
    }

    fprintf(stderr, "...%s completed.\n\n\n", pTestName);
    return 1;
}



int             test_Graph16_Test01 (
    const
    char            *pTestName
)
{
    ERESULT         eRc = ERESULT_SUCCESS;
    GRAPH16_DATA	*pObj = OBJ_NIL;
    bool            fRc;
    ASTR_DATA       *pStr = OBJ_NIL;
    int16_t         e;
    int16_t         v;

    fprintf(stderr, "Performing: %s\n", pTestName);

    pObj = Graph16_NewWithSizes(4/*vertices*/, 6/*edges*/);
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    if (pObj) {

        //obj_TraceSet(pObj, true);
        fRc = obj_IsKindOf(pObj, OBJ_IDENT_GRAPH16);
        TINYTEST_TRUE( (fRc) );
        eRc = Graph16_EdgeSet(pObj, 1, 1, 2);
        TINYTEST_TRUE( (ERESULT_OK(eRc)) );
        eRc = Graph16_EdgeSet(pObj, 2, 1, 3);
        TINYTEST_TRUE( (ERESULT_OK(eRc)) );
        eRc = Graph16_EdgeSet(pObj, 3, 2, 4);
        TINYTEST_TRUE( (ERESULT_OK(eRc)) );
        eRc = Graph16_EdgeSet(pObj, 4, 3, 4);
        TINYTEST_TRUE( (ERESULT_OK(eRc)) );
        eRc = Graph16_EdgeSet(pObj, 5, 3, 2);
        TINYTEST_TRUE( (ERESULT_OK(eRc)) );
        eRc = Graph16_EdgeSet(pObj, 6, 2, 3);
        TINYTEST_TRUE( (ERESULT_OK(eRc)) );
        TINYTEST_TRUE( (6 == pObj->edgesMax) );
        TINYTEST_TRUE( (6 == pObj->edgesUsed) );
        TINYTEST_TRUE( (2 == Graph16_EdgeFrom(pObj, 3)) );
        TINYTEST_TRUE( (4 == Graph16_EdgeTo(pObj, 3)) );
        TINYTEST_TRUE( (2 == Graph16_EdgeFrom(pObj, 6)) );
        TINYTEST_TRUE( (3 == Graph16_EdgeTo(pObj, 6)) );
        {
            ASTR_DATA       *pStr = Graph16_ToDebugString(pObj, 0);
            if (pStr) {
                fprintf(stderr, "After EdgeSets:\n%s\n", AStr_getData(pStr));
                obj_Release(pStr);
                pStr = OBJ_NIL;
            }
        }
        Graph16_RebuildIndex(pObj);
        {
            ASTR_DATA       *pStr = Graph16_ToDebugString(pObj, 0);
            if (pStr) {
                fprintf(stderr, "After Rebuild:\n%s\n", AStr_getData(pStr));
                obj_Release(pStr);
                pStr = OBJ_NIL;
            }
        }
        TINYTEST_TRUE( (6 == pObj->edgesMax) );
        TINYTEST_TRUE( (6 == pObj->edgesUsed) );
        TINYTEST_TRUE( (2 == Graph16_EdgeFrom(pObj, 3)) );
        TINYTEST_TRUE( (4 == Graph16_EdgeTo(pObj, 3)) );
        TINYTEST_TRUE( (2 == Graph16_EdgeFrom(pObj, 6)) );
        TINYTEST_TRUE( (3 == Graph16_EdgeTo(pObj, 6)) );

        eRc = Graph16_ExpandEdges(pObj, 12);
        TINYTEST_TRUE( (ERESULT_OK(eRc)) );
        pStr = Graph16_ToDebugString(pObj, 0);
        if (pStr) {
            fprintf(stderr, "After expand(12):\n%s\n", AStr_getData(pStr));
            obj_Release(pStr);
            pStr = OBJ_NIL;
        }
        TINYTEST_TRUE( (12 == pObj->edgesMax) );
        TINYTEST_TRUE( (6 == pObj->edgesUsed) );
        TINYTEST_TRUE( (2 == Graph16_EdgeFrom(pObj, 3)) );
        TINYTEST_TRUE( (4 == Graph16_EdgeTo(pObj, 3)) );
        TINYTEST_TRUE( (2 == Graph16_EdgeFrom(pObj, 6)) );
        TINYTEST_TRUE( (3 == Graph16_EdgeTo(pObj, 6)) );

        for (v=Graph16_VertexFirst(pObj); v; v=Graph16_VertexNext(pObj, v)) {
            for (e=Graph16_VertexFromFirst(pObj,v); e; e=Graph16_VertexFromNext(pObj,e)) {
                fprintf(stderr, "v: %d  From e: %d\n", v, e);
            }
        }
        for (v=Graph16_VertexFirst(pObj); v; v=Graph16_VertexNext(pObj, v)) {
            for (e=Graph16_VertexToFirst(pObj,v); e; e=Graph16_VertexToNext(pObj,e)) {
                fprintf(stderr, "v: %d  To e: %d\n", v, e);
            }
        }

        obj_Release(pObj);
        pObj = OBJ_NIL;
    }

    fprintf(stderr, "...%s completed.\n\n\n", pTestName);
    return 1;
}




TINYTEST_START_SUITE(test_Graph16);
    TINYTEST_ADD_TEST(test_Graph16_Test01,setUp,tearDown);
    TINYTEST_ADD_TEST(test_Graph16_Copy01,setUp,tearDown);
    TINYTEST_ADD_TEST(test_Graph16_OpenClose,setUp,tearDown);
TINYTEST_END_SUITE();

TINYTEST_MAIN_SINGLE_SUITE(test_Graph16);





