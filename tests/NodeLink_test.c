// vi:nu:et:sts=4 ts=4 sw=4
/*
 *  Generated 02/03/2021 18:58:16
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
#include    <NodeLink_internal.h>
#include    <JsonIn.h>
#ifdef  NODELINK_JSON_SUPPORT
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

#ifdef  NODELINK_JSON_SUPPORT
    SrcErrors_SharedReset( );
    szTbl_SharedReset( );
#endif
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






int             test_NodeLink_OpenClose (
    const
    char            *pTestName
)
{
    ERESULT         eRc = ERESULT_SUCCESS;
    NODELINK_DATA       *pObj = OBJ_NIL;
    bool            fRc;
   
    fprintf(stderr, "Performing: %s\n", pTestName);

    pObj = NodeLink_Alloc( );
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    pObj = NodeLink_Init( pObj );
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    if (pObj) {

        //obj_TraceSet(pObj, true);       
        fRc = obj_IsKindOf(pObj, OBJ_IDENT_NODELINK);
        TINYTEST_TRUE( (fRc) );
        
        // Test something.
        TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );

        obj_Release(pObj);
        pObj = OBJ_NIL;
    }

    fprintf(stderr, "...%s completed.\n\n\n", pTestName);
    return 1;
}



int             test_NodeLink_Copy01 (
    const
    char            *pTestName
)
{
    ERESULT         eRc = ERESULT_SUCCESS;
    NODELINK_DATA   *pObj1 = OBJ_NIL;
    NODELINK_DATA   *pObj2 = OBJ_NIL;
    bool            fRc;
#if defined(NODELINK_JSON_SUPPORT)
    ASTR_DATA       *pStr = OBJ_NIL;
#endif
    int             iRc;
   
    fprintf(stderr, "Performing: %s\n", pTestName);

    pObj1 = NodeLink_NewWithUTF8AndClass('A', "abc", OBJ_NIL);
    TINYTEST_FALSE( (OBJ_NIL == pObj1) );
    if (pObj1) {

        //obj_TraceSet(pObj1, true);       
        fRc = obj_IsKindOf(pObj1, OBJ_IDENT_NODELINK);
        TINYTEST_TRUE( (fRc) );
        NodeLink_setLeftLink(pObj1, 1);
        NodeLink_setRightLink(pObj1, 2);
        NodeLink_setParent(pObj1, 3);

        // Test assign.
        pObj2 = NodeLink_New();
        TINYTEST_FALSE( (OBJ_NIL == pObj2) );
        eRc = NodeLink_Assign(pObj1, pObj2);
        TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );

        fRc = obj_IsKindOf(pObj2, OBJ_IDENT_NODELINK);
        TINYTEST_TRUE( (fRc) );
        iRc = NodeLink_Compare(pObj1, pObj2);
        TINYTEST_TRUE( (0 == eRc) );
        TINYTEST_TRUE( (1 == NodeLink_getChild(pObj2)) );
        TINYTEST_TRUE( (2 == NodeLink_getSibling(pObj2)) );
        TINYTEST_TRUE( (3 == NodeLink_getParent(pObj2)) );

        obj_Release(pObj2);
        pObj2 = OBJ_NIL;

        // Test copy.
        pObj2 = NodeLink_Copy(pObj1);
        TINYTEST_FALSE( (OBJ_NIL == pObj2) );

        fRc = obj_IsKindOf(pObj2, OBJ_IDENT_NODELINK);
        TINYTEST_TRUE( (fRc) );
        iRc = NodeLink_Compare(pObj1, pObj2);
        TINYTEST_TRUE( (0 == iRc) );

        obj_Release(pObj2);
        pObj2 = OBJ_NIL;

        // Test json support.
#if defined(NODELINK_JSON_SUPPORT)
        pStr = NodeLink_ToJson(pObj1);
        TINYTEST_FALSE( (OBJ_NIL == pStr) );
        fprintf(stderr, "JSON: %s\n", AStr_getData(pStr));
        pObj2 = NodeLink_NewFromJsonString(pStr);
        TINYTEST_FALSE( (OBJ_NIL == pObj2) );
        fRc = obj_IsKindOf(pObj2, OBJ_IDENT_NODELINK);
        TINYTEST_TRUE( (fRc) );
        fRc = obj_IsKindOf(NodeLink_getNode(pObj2), OBJ_IDENT_NODE);
        TINYTEST_TRUE( (fRc) );
        obj_Release(pStr);
        pStr = OBJ_NIL;
        iRc = NodeLink_Compare(pObj1, pObj2);
        TINYTEST_TRUE( (0 == iRc) );

        obj_Release(pObj2);
        pObj2 = OBJ_NIL;
#endif

        obj_Release(pObj1);
        pObj1 = OBJ_NIL;
    }

    fprintf(stderr, "...%s completed.\n\n\n", pTestName);
    return 1;
}



int             test_NodeLink_Test01 (
    const
    char            *pTestName
)
{
    ERESULT         eRc = ERESULT_SUCCESS;
    NODELINK_DATA   *pLink1 = OBJ_NIL;
    NODELINK_DATA   *pLink2 = OBJ_NIL;
    bool            fRc;
    ASTR_DATA       *pStr = OBJ_NIL;

    fprintf(stderr, "Performing: %s\n", pTestName);

    pLink1 = NodeLink_NewWithUTF8AndClass('A', "abc", OBJ_NIL);
    TINYTEST_FALSE( (OBJ_NIL == pLink1) );
    if (pLink1) {

        //obj_TraceSet(pObj, true);       
        fRc = obj_IsKindOf(pLink1, OBJ_IDENT_NODELINK);
        TINYTEST_TRUE( (fRc) );
        //TINYTEST_TRUE( (ERESULT_OK(eRc)) );
        
        eRc = NodeLink_CompareA(pLink1, 'A', "abc");
        TINYTEST_TRUE( (0 == eRc) );

        NodeLink_setLeftLink(pLink1, 1);
        NodeLink_setRightLink(pLink1, 2);
        NodeLink_setParent(pLink1, 3);
        pStr = NodeLink_ToJson(pLink1);
        TINYTEST_FALSE( (OBJ_NIL == pStr) );
        fprintf(stderr, "\tJSON1: %s\n", AStr_getData(pStr));

        pLink2 = NodeLink_NewFromJsonString(pStr);
        obj_Release(pStr);
        pStr = OBJ_NIL;
        TINYTEST_FALSE( (OBJ_NIL == pLink2) );

        pStr = NodeLink_ToJson(pLink1);
        TINYTEST_FALSE( (OBJ_NIL == pStr) );
        fprintf(stderr, "\tJSON2: %s\n", AStr_getData(pStr));
        obj_Release(pStr);
        pStr = OBJ_NIL;
        obj_Release(pLink2);
        pLink2 = OBJ_NIL;

        {
            ASTR_DATA       *pStr = NodeLink_ToDebugString(pLink1, 0);
            if (pStr) {
                fprintf(stderr, "Debug: %s\n", AStr_getData(pStr));
                obj_Release(pStr);
                pStr = OBJ_NIL;
            }
        }

        obj_Release(pLink1);
        pLink1 = OBJ_NIL;
    }

    fprintf(stderr, "...%s completed.\n\n\n", pTestName);
    return 1;
}




TINYTEST_START_SUITE(test_NodeLink);
    TINYTEST_ADD_TEST(test_NodeLink_Test01,setUp,tearDown);
    TINYTEST_ADD_TEST(test_NodeLink_Copy01,setUp,tearDown);
    TINYTEST_ADD_TEST(test_NodeLink_OpenClose,setUp,tearDown);
TINYTEST_END_SUITE();

TINYTEST_MAIN_SINGLE_SUITE(test_NodeLink);





