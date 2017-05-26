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


volatile
int         count = 0;



int         setUp(
    const
    char        *pTestName
)
{
    mem_Init( );
    count = 0;
    
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


void *      testRoutine(void *pData)
{
    int         whatever = 1000;
    
    // Non-pausable
    while (whatever--) {
        ++count;
    }
    
    return NULL;
}





int         test_psxThread_OpenClose(
    const
    char        *pTestName
)
{
    PSXTHREAD_DATA	*pObj = OBJ_NIL;
    bool            fRc;
    uint32_t        status;
#if defined(__WIN32_ENV__) || defined(__WIN64_ENV__)
    uint32_t        start;
#endif
   
    fprintf(stderr, "OpenClose_StartCount = %d\n",count);
    pObj = psxThread_Alloc( );
    XCTAssertFalse( (OBJ_NIL == pObj) );
    pObj = psxThread_Init(pObj, testRoutine, NULL, 0);
    XCTAssertFalse( (OBJ_NIL == pObj) );
    if (pObj) {

#if defined(__MACOSX_ENV__)
        sleep(3);
#endif
#if defined(__WIN32_ENV__) || defined(__WIN64_ENV__)
        start = GetTickCount();
        Sleep(3000);
        fprintf(stderr, "Delayed %d ticks\n", GetTickCount()-start);
#endif
        {
            ASTR_DATA       *pStr = psxThread_ToDebugString(pObj, 0);
            fprintf(stderr, "After Start:  %s\n", AStr_getData(pStr));
            obj_Release(pStr);
        }
        status = psxThread_getState(pObj);
        XCTAssertTrue( (status == PSXTHREAD_STATE_RUNNING) );
        
        obj_Release(pObj);
        pObj = OBJ_NIL;
        fprintf(stderr, "OpenClose_EndCount = %d\n",count);
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
#if defined(__WIN32_ENV__) || defined(__WIN64_ENV__)
    uint32_t        start;
#endif
      
    fprintf(stderr, "Run01_StartCount = %d\n",count);
    pObj = psxThread_Alloc();
    XCTAssertFalse( (OBJ_NIL == pObj) );
    pObj = psxThread_Init( pObj, testRoutine, NULL, 0 );
    XCTAssertFalse( (OBJ_NIL == pObj) );
    if (pObj) {

        fprintf(stderr, "Count = %d\n",count);
#if defined(__MACOSX_ENV__)
        sleep(3);
#endif
#if defined(__WIN32_ENV__) || defined(__WIN64_ENV__)
        start = GetTickCount();
        Sleep(3000);
        fprintf(stderr, "Delayed %d ticks\n", GetTickCount()-start);
#endif
        {
            ASTR_DATA       *pStr = psxThread_ToDebugString(pObj, 0);
            fprintf(stderr, "==> After Start:  %s\n", AStr_getData(pStr));
            obj_Release(pStr);
            fprintf(stderr, "Count = %d\n",count);
        }
        status = psxThread_getState(pObj);
        XCTAssertTrue( (status == PSXTHREAD_STATE_RUNNING) );
        
        fRc = psxThread_Pause(pObj);
        XCTAssertTrue( (fRc) );
#if defined(__MACOSX_ENV__)
        sleep(3);
#endif
#if defined(__WIN32_ENV__) || defined(__WIN64_ENV__)
        start = GetTickCount();
        Sleep(3000);
        fprintf(stderr, "Delayed %d ticks\n", GetTickCount()-start);
#endif
        {
            ASTR_DATA       *pStr = psxThread_ToDebugString(pObj, 0);
            fprintf(stderr, "==> After Pause:  %s\n", AStr_getData(pStr));
            obj_Release(pStr);
            fprintf(stderr, "Count = %d\n",count);
        }
        status = psxThread_getState(pObj);
        XCTAssertTrue( (status == PSXTHREAD_STATE_PAUSED) );
        
        fRc = psxThread_Resume(pObj);
        XCTAssertTrue( (fRc) );
#if defined(__MACOSX_ENV__)
        sleep(3);
#endif
#if defined(__WIN32_ENV__) || defined(__WIN64_ENV__)
        start = GetTickCount();
        Sleep(3000);
        fprintf(stderr, "Delayed %d ticks\n", GetTickCount()-start);
#endif
        {
            ASTR_DATA       *pStr = psxThread_ToDebugString(pObj, 0);
            fprintf(stderr, "==> After Resume:  %s\n", AStr_getData(pStr));
            obj_Release(pStr);
            fprintf(stderr, "Count = %d\n",count);
        }

        fRc = psxThread_Terminate(pObj);
        XCTAssertTrue( (fRc) );
#if defined(__MACOSX_ENV__)
        sleep(3);
#endif
#if defined(__WIN32_ENV__) || defined(__WIN64_ENV__)
        start = GetTickCount();
        Sleep(3000);
        fprintf(stderr, "Delayed %d ticks\n", GetTickCount()-start);
#endif
        {
            ASTR_DATA       *pStr = psxThread_ToDebugString(pObj, 0);
            fprintf(stderr, "==> After Stop:  %s\n", AStr_getData(pStr));
            obj_Release(pStr);
            fprintf(stderr, "Count = %d\n",count);
        }
        
        fRc = psxThread_Join(pObj, NULL);
        XCTAssertTrue( (fRc) );

        obj_Release(pObj);
        pObj = OBJ_NIL;
        fprintf(stderr, "Run01_EndCount = %d\n",count);
    }
    
}




TINYTEST_START_SUITE(test_psxThread);
  TINYTEST_ADD_TEST(test_psxThread_OpenClose,setUp,tearDown);
  TINYTEST_ADD_TEST(test_psxThread_Run01,setUp,tearDown);
TINYTEST_END_SUITE();

TINYTEST_MAIN_SINGLE_SUITE(test_psxThread);





