/*
 *	Generated 06/30/2017 09:01:13
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
#include    <ternary_internal.h>



int         setUp(
    const
    char        *pTestName
)
{
    mem_Init( );
    trace_Shared( ); 
    // Put setup code here. This method is called before the invocation of each
    // test method in the class.
    
    return 1; 
}


int         tearDown(
    const
    char        *pTestName
)
{
    // Put teardown code here. This method is called after the invocation of each
    // test method in the class.

    
    trace_SharedReset( ); 
    mem_Dump( );
    mem_Release( );
    
    return 1; 
}






int         test_ternary_OpenClose(
    const
    char        *pTestName
)
{
    TERNARY_DATA *pObj = OBJ_NIL;
   
    pObj = ternary_Alloc( );
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    pObj = ternary_Init( pObj, 16 );
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    if (pObj) {

        // Test something.

        obj_Release(pObj);
        pObj = OBJ_NIL;
    }

    return 1;
}



int         test_ternary_AddFind(
    const
    char        *pTestName
)
{
    TERNARY_DATA	*pObj = OBJ_NIL;
    ERESULT         eRc;
    void            *pResult;
    
    pObj = ternary_Alloc(0);
    XCTAssertFalse( (OBJ_NIL == pObj) );
    pObj = ternary_Init( pObj, 16 );
    XCTAssertFalse( (OBJ_NIL == pObj) );
    obj_TraceSet(pObj, true);
    if (pObj) {
        
        fprintf(stderr, "\n\n** add sea\n");
        eRc = ternary_Add(pObj, L"sea", "sea");
        XCTAssertFalse( (ERESULT_FAILED(eRc)) );
        eRc = ternaryTree_VisitPreorder(pObj, NULL, NULL);
        XCTAssertFalse( (ERESULT_FAILED(eRc)) );
        pResult = ternary_Find(pObj, L"sea");
        XCTAssertFalse( (NULL == pResult) );
        
        fprintf(stderr, "\n\n** add sells\n");
        eRc = ternary_Add(pObj, L"sells", "sells");
        XCTAssertFalse( (ERESULT_FAILED(eRc)) );
        eRc = ternaryTree_VisitPreorder(pObj, NULL, NULL);
        XCTAssertFalse( (ERESULT_FAILED(eRc)) );
        pResult = ternary_Find(pObj, L"sea");
        XCTAssertFalse( (NULL == pResult) );
        pResult = ternary_Find(pObj, L"sells");
        XCTAssertFalse( (NULL == pResult) );
        
        fprintf(stderr, "\n\n** add she\n");
        eRc = ternary_Add(pObj, L"she", "she");
        XCTAssertFalse( (ERESULT_FAILED(eRc)) );
        eRc = ternaryTree_VisitPreorder(pObj, NULL, NULL);
        XCTAssertFalse( (ERESULT_FAILED(eRc)) );
        pResult = ternary_Find(pObj, L"sea");
        XCTAssertFalse( (NULL == pResult) );
        pResult = ternary_Find(pObj, L"sells");
        XCTAssertFalse( (NULL == pResult) );
        pResult = ternary_Find(pObj, L"she");
        XCTAssertFalse( (NULL == pResult) );
        
        fprintf(stderr, "\n\n** add shells\n");
        eRc = ternary_Add(pObj, L"shells", "shells");
        XCTAssertFalse( (ERESULT_FAILED(eRc)) );
        eRc = ternaryTree_VisitPreorder(pObj, NULL, NULL);
        XCTAssertFalse( (ERESULT_FAILED(eRc)) );
        pResult = ternary_Find(pObj, L"sea");
        XCTAssertFalse( (NULL == pResult) );
        pResult = ternary_Find(pObj, L"sells");
        XCTAssertFalse( (NULL == pResult) );
        pResult = ternary_Find(pObj, L"she");
        XCTAssertFalse( (NULL == pResult) );
        pResult = ternary_Find(pObj, L"shells");
        XCTAssertFalse( (NULL == pResult) );
        
        fprintf(stderr, "\n\n** add shore\n");
        eRc = ternary_Add(pObj, L"shore", "shore");
        XCTAssertFalse( (ERESULT_FAILED(eRc)) );
        eRc = ternaryTree_VisitPreorder(pObj, NULL, NULL);
        XCTAssertFalse( (ERESULT_FAILED(eRc)) );
        pResult = ternary_Find(pObj, L"sea");
        XCTAssertFalse( (NULL == pResult) );
        pResult = ternary_Find(pObj, L"sells");
        XCTAssertFalse( (NULL == pResult) );
        pResult = ternary_Find(pObj, L"she");
        XCTAssertFalse( (NULL == pResult) );
        pResult = ternary_Find(pObj, L"shells");
        XCTAssertFalse( (NULL == pResult) );
        pResult = ternary_Find(pObj, L"shore");
        XCTAssertFalse( (NULL == pResult) );
        
        fprintf(stderr, "\n\n** add by\n");
        eRc = ternary_Add(pObj, L"by", "by");
        XCTAssertFalse( (ERESULT_FAILED(eRc)) );
        eRc = ternaryTree_VisitPreorder(pObj, NULL, NULL);
        XCTAssertFalse( (ERESULT_FAILED(eRc)) );
        pResult = ternary_Find(pObj, L"sea");
        XCTAssertFalse( (NULL == pResult) );
        pResult = ternary_Find(pObj, L"sells");
        XCTAssertFalse( (NULL == pResult) );
        pResult = ternary_Find(pObj, L"she");
        XCTAssertFalse( (NULL == pResult) );
        pResult = ternary_Find(pObj, L"shells");
        XCTAssertFalse( (NULL == pResult) );
        pResult = ternary_Find(pObj, L"shore");
        XCTAssertFalse( (NULL == pResult) );
        pResult = ternary_Find(pObj, L"by");
        XCTAssertFalse( (NULL == pResult) );
        
        fprintf(stderr, "\n\n** add the\n");
        eRc = ternary_Add(pObj, L"the", "the");
        XCTAssertFalse( (ERESULT_FAILED(eRc)) );
        eRc = ternaryTree_VisitPreorder(pObj, NULL, NULL);
        XCTAssertFalse( (ERESULT_FAILED(eRc)) );
        pResult = ternary_Find(pObj, L"sea");
        XCTAssertFalse( (NULL == pResult) );
        pResult = ternary_Find(pObj, L"sells");
        XCTAssertFalse( (NULL == pResult) );
        pResult = ternary_Find(pObj, L"she");
        XCTAssertFalse( (NULL == pResult) );
        pResult = ternary_Find(pObj, L"shells");
        XCTAssertFalse( (NULL == pResult) );
        pResult = ternary_Find(pObj, L"shore");
        XCTAssertFalse( (NULL == pResult) );
        pResult = ternary_Find(pObj, L"by");
        XCTAssertFalse( (NULL == pResult) );
        pResult = ternary_Find(pObj, L"the");
        XCTAssertFalse( (NULL == pResult) );
        
        obj_Release(pObj);
        pObj = OBJ_NIL;
    }
    
    return 1;
}




TINYTEST_START_SUITE(test_ternary);
  TINYTEST_ADD_TEST(test_ternary_AddFind,setUp,tearDown);
  TINYTEST_ADD_TEST(test_ternary_OpenClose,setUp,tearDown);
TINYTEST_END_SUITE();

TINYTEST_MAIN_SINGLE_SUITE(test_ternary);





