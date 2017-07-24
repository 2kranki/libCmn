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
#include    <blocks_internal.h>



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






int         test_blocks_OpenClose(
    const
    char            *pTestName
)
{
    BLOCKS_DATA	    *pObj = OBJ_NIL;
    uint32_t        wrk;
   
    pObj = blocks_Alloc(0);
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    pObj = blocks_Init( pObj, 2048 );
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    if (pObj) {

        wrk = blocks_Overhead();
        fprintf(stderr, "overhead = %d\n", wrk);
        XCTAssertTrue( (16 == wrk) );
        wrk = blocks_Useable(2048);
        fprintf(stderr, "useable = %d\n", wrk);
        XCTAssertTrue( (2032 == wrk) );

        obj_Release(pObj);
        pObj = OBJ_NIL;
    }

    return 1;
}



int         test_blocks_Add(
    const
    char            *pTestName
)
{
    BLOCKS_DATA	*pObj = OBJ_NIL;
    void        *pBlk1 = NULL;
    void        *pBlk2 = NULL;
    void        *pBlk3 = NULL;
    void        *pBlk4 = NULL;
    
    pObj = blocks_Alloc(0);
    XCTAssertFalse( (OBJ_NIL == pObj) );
    pObj = blocks_Init( pObj, 2048 );
    XCTAssertFalse( (OBJ_NIL == pObj) );
    if (pObj) {
        
        pBlk1 = blocks_Add(pObj);
        XCTAssertFalse( (NULL == pBlk1) );
        XCTAssertTrue( (blocks_getSize(pObj) == 1) );
        pBlk2 = blocks_Add(pObj);
        XCTAssertFalse( (NULL == pBlk2) );
        XCTAssertTrue( (blocks_getSize(pObj) == 2) );
        pBlk3 = blocks_Add(pObj);
        XCTAssertFalse( (NULL == pBlk3) );
        XCTAssertTrue( (blocks_getSize(pObj) == 3) );
        pBlk4 = blocks_Add(pObj);
        XCTAssertFalse( (NULL == pBlk4) );
        XCTAssertTrue( (blocks_getSize(pObj) == 4) );
        
        XCTAssertTrue( (blocks_Block(pObj, 1) == pBlk1) );
        XCTAssertTrue( (blocks_Block(pObj, 2) == pBlk2) );
        XCTAssertTrue( (blocks_Block(pObj, 3) == pBlk3) );
        XCTAssertTrue( (blocks_Block(pObj, 4) == pBlk4) );
        
        obj_Release(pObj);
        pObj = OBJ_NIL;
    }
    
    return 1;
}



int         test_blocks_Delete(
    const
    char            *pTestName
)
{
    BLOCKS_DATA	*pObj = OBJ_NIL;
    ERESULT     eRc;
    void        *pBlk1 = NULL;
    void        *pBlk2 = NULL;
    void        *pBlk3 = NULL;
    void        *pBlk4 = NULL;
    
    pObj = blocks_Alloc(0);
    XCTAssertFalse( (OBJ_NIL == pObj) );
    pObj = blocks_Init( pObj, 2048 );
    XCTAssertFalse( (OBJ_NIL == pObj) );
    if (pObj) {
        
        pBlk1 = blocks_Add(pObj);
        XCTAssertFalse( (NULL == pBlk1) );
        XCTAssertTrue( (blocks_getSize(pObj) == 1) );
        pBlk2 = blocks_Add(pObj);
        XCTAssertFalse( (NULL == pBlk2) );
        XCTAssertTrue( (blocks_getSize(pObj) == 2) );
        pBlk3 = blocks_Add(pObj);
        XCTAssertFalse( (NULL == pBlk3) );
        XCTAssertTrue( (blocks_getSize(pObj) == 3) );
        pBlk4 = blocks_Add(pObj);
        XCTAssertFalse( (NULL == pBlk4) );
        XCTAssertTrue( (blocks_getSize(pObj) == 4) );
        
        XCTAssertTrue( (blocks_Block(pObj, 1) == pBlk1) );
        XCTAssertTrue( (blocks_Block(pObj, 2) == pBlk2) );
        XCTAssertTrue( (blocks_Block(pObj, 3) == pBlk3) );
        XCTAssertTrue( (blocks_Block(pObj, 4) == pBlk4) );
        
        eRc = blocks_Delete(pObj, pBlk2);
        XCTAssertFalse( (ERESULT_FAILED(eRc)) );
        XCTAssertTrue( (blocks_getSize(pObj) == 3) );
        
        eRc = blocks_Delete(pObj, pBlk3);
        XCTAssertFalse( (ERESULT_FAILED(eRc)) );
        XCTAssertTrue( (blocks_getSize(pObj) == 2) );
        
        eRc = blocks_Delete(pObj, pBlk1);
        XCTAssertFalse( (ERESULT_FAILED(eRc)) );
        XCTAssertTrue( (blocks_getSize(pObj) == 1) );
        
        eRc = blocks_Delete(pObj, pBlk4);
        XCTAssertFalse( (ERESULT_FAILED(eRc)) );
        XCTAssertTrue( (blocks_getSize(pObj) == 0) );
        
        obj_Release(pObj);
        pObj = OBJ_NIL;
    }
    
    return 1;
}




TINYTEST_START_SUITE(test_blocks);
  TINYTEST_ADD_TEST(test_blocks_Delete,setUp,tearDown);
  TINYTEST_ADD_TEST(test_blocks_Add,setUp,tearDown);
  TINYTEST_ADD_TEST(test_blocks_OpenClose,setUp,tearDown);
TINYTEST_END_SUITE();

TINYTEST_MAIN_SINGLE_SUITE(test_blocks);





