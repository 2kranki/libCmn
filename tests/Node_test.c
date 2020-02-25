// vi:nu:et:sts=4 ts=4 sw=4
/*
 *	Generated 01/12/2020 16:09:18
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
#include    <SrcErrors.h>
#include    <szTbl.h>
#include    <trace.h>
#include    <Node_internal.h>
#include    <NodeArray.h>



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

    SrcErrors_SharedReset( );
    szTbl_SharedReset( );
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






int             test_Node_OpenClose (
    const
    char            *pTestName
)
{
    ERESULT         eRc = ERESULT_SUCCESS;
    NODE_DATA	    *pObj = OBJ_NIL;
    bool            fRc;
   
    fprintf(stderr, "Performing: %s\n", pTestName);

    pObj = Node_Alloc( );
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    pObj = Node_Init( pObj );
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    if (pObj) {

        //obj_TraceSet(pObj, true);       
        fRc = obj_IsKindOf(pObj, OBJ_IDENT_NODE);
        TINYTEST_TRUE( (fRc) );
        
        // Test something.
        TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );

        obj_Release(pObj);
        pObj = OBJ_NIL;
    }

    fprintf(stderr, "...%s completed.\n\n\n", pTestName);
    return 1;
}



int             test_Node_Test01 (
    const
    char            *pTestName
)
{
    ERESULT         eRc = ERESULT_SUCCESS;
    NODE_DATA	    *pObj = OBJ_NIL;
    bool            fRc;
   
    fprintf(stderr, "Performing: %s\n", pTestName);

    pObj = Node_Alloc( );
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    pObj = Node_Init( pObj );
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    if (pObj) {

        //obj_TraceSet(pObj, true);       
        fRc = obj_IsKindOf(pObj, OBJ_IDENT_NODE);
        TINYTEST_TRUE( (fRc) );
        
        // Test something.
        TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );

        obj_Release(pObj);
        pObj = OBJ_NIL;
    }

    fprintf(stderr, "...%s completed.\n\n\n", pTestName);
    return 1;
}



int         test_Node_Utf8(
    const
    char            *pTestName
)
{
    NODE_DATA        *pObj = OBJ_NIL;

    fprintf(stderr, "Performing: %s\n", pTestName);
    pObj = Node_NewWithUTF8AndClass(0, "abc", NULL);
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    if (pObj) {

        // Test something.

        obj_Release(pObj);
        pObj = OBJ_NIL;
    }

    szTbl_SharedReset();
    fprintf(stderr, "...%s completed.\n", pTestName);
    return 1;
}



int         test_Node_Utf8Con(
    const
    char            *pTestName
)
{
    NODE_DATA        *pObj = OBJ_NIL;

    fprintf(stderr, "Performing: %s\n", pTestName);
    pObj = Node_NewWithUTF8ConAndClass(0, "abc", OBJ_NIL);
    XCTAssertFalse( (OBJ_NIL == pObj) );
    if (pObj) {

        obj_Release(pObj);
        pObj = OBJ_NIL;
    }

    szTbl_SharedReset();
    fprintf(stderr, "...%s completed.\n", pTestName);
    return 1;
}



int         test_Node_Property01(
    const
    char            *pTestName
)
{
    ERESULT         eRc;
    NODE_DATA       *pObj = OBJ_NIL;
    ASTR_DATA       *pAStr = OBJ_NIL;
    const
    char            *pStrA = NULL;
    ASTR_DATA       *pAWrk = OBJ_NIL;
    NODEARRAY_DATA  *pKeys = OBJ_NIL;
    uint32_t        i;
    NODE_DATA       *pNode = OBJ_NIL;

    fprintf(stderr, "Performing: %s\n", pTestName);
    pObj = Node_NewWithUTF8ConAndClass(0, "abc", OBJ_NIL);
    XCTAssertFalse( (OBJ_NIL == pObj) );
    if (pObj) {

        pStrA = "c";
        pAStr = AStr_NewA(pStrA);
        XCTAssertFalse( (OBJ_NIL == pAStr) );
        eRc = Node_PropertyAddA(pObj, pStrA, pAStr);
        XCTAssertFalse( (ERESULT_FAILED(eRc)) );
        pAWrk = Node_PropertyA(pObj, pStrA);
        XCTAssertTrue( (ERESULT_SUCCESS_EQUAL == AStr_CompareA(pAWrk, pStrA)) );
        obj_Release(pAStr);
        pAStr = OBJ_NIL;

        pStrA = "a";
        pAStr = AStr_NewA(pStrA);
        XCTAssertFalse( (OBJ_NIL == pAStr) );
        eRc = Node_PropertyAddA(pObj, pStrA, pAStr);
        XCTAssertFalse( (ERESULT_FAILED(eRc)) );
        pAWrk = Node_PropertyA(pObj, pStrA);
        XCTAssertTrue( (ERESULT_SUCCESS_EQUAL == AStr_CompareA(pAWrk, pStrA)) );
        obj_Release(pAStr);
        pAStr = OBJ_NIL;

        pStrA = "b";
        pAStr = AStr_NewA(pStrA);
        XCTAssertFalse( (OBJ_NIL == pAStr) );
        eRc = Node_PropertyAddA(pObj, pStrA, pAStr);
        XCTAssertFalse( (ERESULT_FAILED(eRc)) );
        pAWrk = Node_PropertyA(pObj, pStrA);
        XCTAssertTrue( (ERESULT_SUCCESS_EQUAL == AStr_CompareA(pAWrk, pStrA)) );
        obj_Release(pAStr);
        pAStr = OBJ_NIL;

        pStrA = "a";
        pAWrk = Node_PropertyA(pObj, pStrA);
        XCTAssertTrue( (ERESULT_SUCCESS_EQUAL == AStr_CompareA(pAWrk, pStrA)) );

        pKeys = Node_Properties(pObj);
        XCTAssertFalse( (OBJ_NIL == pKeys) );
        i = NodeArray_getSize(pKeys);
        XCTAssertTrue( (3 == i) );
        pNode = NodeArray_Get(pKeys, 1);
        XCTAssertFalse( (OBJ_NIL == pNode) );
        XCTAssertTrue( (ERESULT_SUCCESS_EQUAL == AStr_CompareA(Node_getData(pNode), "a")) );
        pNode = NodeArray_Get(pKeys, 2);
        XCTAssertFalse( (OBJ_NIL == pNode) );
        XCTAssertTrue( (ERESULT_SUCCESS_EQUAL == AStr_CompareA(Node_getData(pNode), "b")) );
        pNode = NodeArray_Get(pKeys, 3);
        XCTAssertFalse( (OBJ_NIL == pNode) );
        XCTAssertTrue( (ERESULT_SUCCESS_EQUAL == AStr_CompareA(Node_getData(pNode), "c")) );
        obj_Release(pKeys);
        pKeys = OBJ_NIL;

        obj_Release(pObj);
        pObj = OBJ_NIL;
    }

    szTbl_SharedReset();
    fprintf(stderr, "...%s completed.\n", pTestName);
    return 1;
}



int             test_Node_Copy01 (
    const
    char            *pTestName
)
{
    ERESULT         eRc = ERESULT_SUCCESS;
    NODE_DATA       *pObj1 = OBJ_NIL;
    NODE_DATA       *pObj2 = OBJ_NIL;
    bool            fRc;
    ASTR_DATA       *pStr = OBJ_NIL;

    fprintf(stderr, "Performing: %s\n", pTestName);

    pObj1 = Node_NewWithUTF8ConAndClass(0, "abc", OBJ_NIL);
    TINYTEST_FALSE( (OBJ_NIL == pObj1) );
    if (pObj1) {

        //obj_TraceSet(pObj1, true);
        fRc = obj_IsKindOf(pObj1, OBJ_IDENT_NODE);
        TINYTEST_TRUE( (fRc) );

        // Test assign.
        pObj2 = Node_New();
        TINYTEST_FALSE( (OBJ_NIL == pObj2) );
        eRc = Node_Assign(pObj1, pObj2);
        TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );

        fRc = obj_IsKindOf(pObj2, OBJ_IDENT_NODE);
        TINYTEST_TRUE( (fRc) );
        eRc = Node_Compare(pObj1, pObj2);
        TINYTEST_TRUE( (ERESULT_SUCCESS_EQUAL == eRc) );

        obj_Release(pObj2);
        pObj2 = OBJ_NIL;

        // Test copy.
        pObj2 = Node_Copy(pObj1);
        TINYTEST_FALSE( (OBJ_NIL == pObj2) );

        fRc = obj_IsKindOf(pObj2, OBJ_IDENT_NODE);
        TINYTEST_TRUE( (fRc) );
        eRc = Node_Compare(pObj1, pObj2);
        TINYTEST_TRUE( (ERESULT_SUCCESS_EQUAL == eRc) );

        obj_Release(pObj2);
        pObj2 = OBJ_NIL;

        // Test json support.
        pStr = Node_ToJson(pObj1);
        TINYTEST_FALSE( (OBJ_NIL == pStr) );
        fprintf(stderr, "JSON: %s\n", AStr_getData(pStr));
        pObj2 = Node_NewFromJsonString(pStr);
        TINYTEST_FALSE( (OBJ_NIL == pObj2) );
        fRc = obj_IsKindOf(pObj2, OBJ_IDENT_NODE);
        TINYTEST_TRUE( (fRc) );
        obj_Release(pStr);
        pStr = OBJ_NIL;
        eRc = Node_Compare(pObj1, pObj2);
        TINYTEST_TRUE( (ERESULT_SUCCESS_EQUAL == eRc) );

        obj_Release(pObj2);
        pObj2 = OBJ_NIL;

        obj_Release(pObj1);
        pObj1 = OBJ_NIL;
    }

    fprintf(stderr, "...%s completed.\n\n\n", pTestName);
    return 1;
}




TINYTEST_START_SUITE(test_Node);
    TINYTEST_ADD_TEST(test_Node_Copy01,setUp,tearDown);
    TINYTEST_ADD_TEST(test_Node_Property01,setUp,tearDown);
    TINYTEST_ADD_TEST(test_Node_Utf8Con,setUp,tearDown);
    TINYTEST_ADD_TEST(test_Node_Utf8,setUp,tearDown);
    TINYTEST_ADD_TEST(test_Node_Test01,setUp,tearDown);
    TINYTEST_ADD_TEST(test_Node_OpenClose,setUp,tearDown);
TINYTEST_END_SUITE();

TINYTEST_MAIN_SINGLE_SUITE(test_Node);





