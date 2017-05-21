/*
 *	Generated 05/19/2017 21:15:36
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
#include    <psxSem_internal.h>




int         setUp(
    const
    char        *pTestName
)
{
    mem_Init( );
    
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

    
    mem_Dump( );
    mem_Release( );
    return 1; 
}





int         test_psxSem_OpenClose(
    const
    char        *pTestName
)
{
    PSXSEM_DATA	    *pObj = OBJ_NIL;
    bool            fRc;
   
    pObj = psxSem_Alloc( );
    XCTAssertFalse( (OBJ_NIL == pObj) );
    pObj = psxSem_Init( pObj );
    XCTAssertFalse( (OBJ_NIL == pObj) );
    if (pObj) {

        //fRc = psxSem_IsLocked(pObj);
        //XCTAssertTrue( (!fRc) );
        
        //fRc = psxSem_Lock(pObj);
        //XCTAssertTrue( (fRc) );
        
        //fRc = psxSem_IsLocked(pObj);
        //XCTAssertTrue( (fRc) );
        
        //fRc = psxSem_Unlock(pObj);
        //XCTAssertTrue( (fRc) );
        
        obj_Release(pObj);
        pObj = OBJ_NIL;
    }

    return 1;
}




TINYTEST_START_SUITE(test_psxSem);
  TINYTEST_ADD_TEST(test_psxSem_OpenClose,setUp,tearDown);
TINYTEST_END_SUITE();

TINYTEST_MAIN_SINGLE_SUITE(test_psxSem);





