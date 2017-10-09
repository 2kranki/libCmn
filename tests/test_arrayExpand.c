/*
 *	Generated 06/05/2017 21:57:10
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
#include    <arrayExpand_internal.h>



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






int         test_arrayExpand_OpenClose(
    const
    char        *pTestName
)
{
    ARRAYEXPAND_DATA *pObj = OBJ_NIL;
   
    fprintf(stderr, "Performing: %s\n", pTestName);

    pObj = arrayExpand_Alloc( );
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    pObj = arrayExpand_Init( pObj, 4 );
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    if (pObj) {

        // Test something.

        obj_Release(pObj);
        pObj = OBJ_NIL;
    }

    fprintf(stderr, "...%s completed.\n", pTestName);
    return 1;
}



int         test_arrayExpand_Elem1(
    const
    char        *pTestName
)
{
    ARRAYEXPAND_DATA *pObj = OBJ_NIL;
    uint8_t         *pData;
    
    fprintf(stderr, "Performing: %s\n", pTestName);

    pObj = arrayExpand_Alloc( );
    XCTAssertFalse( (OBJ_NIL == pObj) );
    pObj = arrayExpand_Init(pObj, 1);
    XCTAssertFalse( (OBJ_NIL == pObj) );
    if (pObj) {
        
        pData = arrayExpand_Elem(pObj, 2);
        XCTAssertFalse( (pData == NULL) );
        XCTAssertFalse( (ERESULT_HAS_FAILED(arrayExpand_getLastError(pObj))) );
        XCTAssertTrue( (pData == (pObj->pArray + 2-1)) );
        
        pData = arrayExpand_Elem(pObj, 4);
        XCTAssertFalse( (pData == NULL) );
        XCTAssertFalse( (ERESULT_HAS_FAILED(arrayExpand_getLastError(pObj))) );
        XCTAssertTrue( (pData == (pObj->pArray + 4-1)) );
        
        pData = arrayExpand_Elem(pObj, 2);
        XCTAssertFalse( (pData == NULL) );
        XCTAssertFalse( (ERESULT_HAS_FAILED(arrayExpand_getLastError(pObj))) );
        XCTAssertTrue( (pData == (pObj->pArray + 2-1)) );
        
        obj_Release(pObj);
        pObj = OBJ_NIL;
    }
    
    fprintf(stderr, "...%s completed.\n", pTestName);
    return 1;
}



int         test_arrayExpand_ExpandTo(
    const
    char        *pTestName
)
{
    ARRAYEXPAND_DATA *pObj = OBJ_NIL;
    ERESULT         eRc;
    
    fprintf(stderr, "Performing: %s\n", pTestName);

    pObj = arrayExpand_Alloc( );
    XCTAssertFalse( (OBJ_NIL == pObj) );
    pObj = arrayExpand_Init(pObj, 1);
    XCTAssertFalse( (OBJ_NIL == pObj) );
    if (pObj) {
        
        eRc = arrayExpand_ExpandTo(pObj, 2);
        XCTAssertFalse( (ERESULT_HAS_FAILED(eRc)) );
        XCTAssertTrue( (pObj->max == 2) );
        
        eRc = arrayExpand_ExpandTo(pObj, 4);
        XCTAssertFalse( (ERESULT_HAS_FAILED(eRc)) );
        XCTAssertTrue( (pObj->max == 4) );
        
        eRc = arrayExpand_ExpandTo(pObj, 512);
        XCTAssertFalse( (ERESULT_HAS_FAILED(eRc)) );
        XCTAssertTrue( (pObj->max == 512) );
        
        obj_Release(pObj);
        pObj = OBJ_NIL;
    }
    
    fprintf(stderr, "...%s completed.\n", pTestName);
    return 1;
}




TINYTEST_START_SUITE(test_arrayExpand);
  TINYTEST_ADD_TEST(test_arrayExpand_ExpandTo,setUp,tearDown);
  TINYTEST_ADD_TEST(test_arrayExpand_Elem1,setUp,tearDown);
  TINYTEST_ADD_TEST(test_arrayExpand_OpenClose,setUp,tearDown);
TINYTEST_END_SUITE();

TINYTEST_MAIN_SINGLE_SUITE(test_arrayExpand);





