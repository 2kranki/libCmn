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
#include    <psxThread_internal.h>




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



int         count = 0;

void *      testRoutine(void *pData)
{
    // Pausable
//#ifdef XYZZY
    ++count;
//#endif
    
    // Non-pausable
#ifdef XYZZY
    while (true) {
        ++count;
    }
#endif
    
    return NULL;
}





int         test_psxThread_OpenClose(
    const
    char        *pTestName
)
{
    PSXSEM_DATA	    *pObj = OBJ_NIL;
    bool            fRc;
   
    pObj = psxThread_Alloc( );
    XCTAssertFalse( (OBJ_NIL == pObj) );
    pObj = psxThread_Init(pObj, testRoutine, NULL, 0);
    XCTAssertFalse( (OBJ_NIL == pObj) );
    if (pObj) {

        //fRc = psxThread_IsLocked(pObj);
        //XCTAssertTrue( (!fRc) );
        
        //fRc = psxThread_Lock(pObj);
        //XCTAssertTrue( (fRc) );
        
        //fRc = psxThread_IsLocked(pObj);
        //XCTAssertTrue( (fRc) );
        
        //fRc = psxThread_Unlock(pObj);
        //XCTAssertTrue( (fRc) );

        fprintf(stderr, "Count = %d\n",count);

        obj_Release(pObj);
        pObj = OBJ_NIL;
    }

    return 1;
}



int         test_psxThread_Run01(
    const
    char        *pTestName
)
{
    PSXTHREAD_DATA	*pObj = OBJ_NIL;
    bool            fRc;
    uint32_t        status;
    
    pObj = psxThread_Alloc();
    XCTAssertFalse( (OBJ_NIL == pObj) );
    pObj = psxThread_Init( pObj, testRoutine, NULL, 0 );
    XCTAssertFalse( (OBJ_NIL == pObj) );
    if (pObj) {
        fRc = psxThread_Start(pObj);
        XCTAssertTrue( (fRc) );
        sleep(3);
        status = psxThread_getState(pObj);
        XCTAssertTrue( (status == PSXTHREAD_STATE_RUNNING) );
        fRc = psxThread_Pause(pObj);
        XCTAssertTrue( (fRc) );
        sleep(3);
        status = psxThread_getState(pObj);
        XCTAssertTrue( (status == PSXTHREAD_STATE_PAUSED) );
        fRc = psxThread_Cancel(pObj);
        XCTAssertTrue( (fRc) );
        obj_Release(pObj);
        pObj = OBJ_NIL;
        fprintf(stderr, "Count = %d\n",count);
    }
    
}




TINYTEST_START_SUITE(test_psxThread);
  TINYTEST_ADD_TEST(test_psxThread_OpenClose,setUp,tearDown);
  TINYTEST_ADD_TEST(test_psxThread_Run01,setUp,tearDown);
TINYTEST_END_SUITE();

TINYTEST_MAIN_SINGLE_SUITE(test_psxThread);





