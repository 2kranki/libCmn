/*
 *	Generated 06/06/2017 23:20:26
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
#include    <timer_internal.h>


static
int             count = 0;


void *          timerRoutine(
)
{
    ++count;
    //fprintf(stderr, "timerCounter = %d\n", count);
    return NULL;
}



int         setUp(
    const
    char        *pTestName
)
{
    mem_Init( );
    trace_Shared( ); 
    // Put setup code here. This method is called before the invocation of each
    // test method in the class.
    count = 0;
    
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






int         test_timer_OpenClose(
    const
    char        *pTestName
)
{
    TIMER_DATA      *pObj = OBJ_NIL;
    uint32_t        status;
#if defined(__MACOSX_ENV__)
    struct timeval  startTime;
    struct timeval  endTime;
    int             iRc;
#endif
   
    fprintf(stderr, "Performing: %s\n", pTestName);
    fprintf(stderr, "timerRoutine = %p\n", timerRoutine);
    pObj = timer_Alloc( );
    XCTAssertFalse( (OBJ_NIL == pObj) );
    pObj = timer_Init(pObj, 500, timerRoutine, NULL);
    // 500ms or 2 counts per second
    XCTAssertFalse( (OBJ_NIL == pObj) );
    if (pObj) {
        
#if defined(__MACOSX_ENV__)
        if (0 == gettimeofday(&startTime, NULL)) {
        }
        else {
            XCTAssertFalse( (1) );
        }
        while ((status = psxThread_getState(pObj->pThread)) == PSXTHREAD_STATE_STARTING) {
        }
        if (0 == gettimeofday(&endTime, NULL)) {
        }
        else {
            XCTAssertFalse( (1) );
        }
        fprintf(stderr, "Start Time = %ld:%d\n",
                (endTime.tv_sec - startTime.tv_sec),
                (endTime.tv_usec - startTime.tv_usec)
        );
#endif
        status = psxThread_getState(pObj->pThread);
        fprintf(stderr, "status = %d\n", status);
        XCTAssertTrue( ((status == PSXTHREAD_STATE_RUNNING) || (status == PSXTHREAD_STATE_DELAYING)) );
        {
            int         save = count;
            ASTR_DATA       *pStr = psxThread_ToDebugString(pObj->pThread, 0);
            fprintf(stderr, "After Start:  %s\n", AStr_getData(pStr));
            obj_Release(pStr);
            fprintf(stderr, "Count = %d\n", save);
            XCTAssertTrue( ((save >= 1) && (save < 3)) );
        }
        
#if defined(__MACOSX_ENV__)
        if (0 == gettimeofday(&startTime, NULL)) {
        }
        else {
            XCTAssertFalse( (1) );
        }
        iRc = usleep(10*1000*1000);
        if (-1 == iRc) {
            iRc = errno;
        }
        if (0 == gettimeofday(&endTime, NULL)) {
        }
        else {
            XCTAssertFalse( (1) );
        }
        fprintf(stderr, "Sleep Time(rc=%d) = %ld:%d\n",
                iRc,
                (endTime.tv_sec - startTime.tv_sec),
                (endTime.tv_usec - startTime.tv_usec)
                );
#endif
#if defined(__WIN32_ENV__) || defined(__WIN64_ENV__)
        Sleep(10000);
#endif
#if defined(__MACOSX_ENV__)
        if (0 == gettimeofday(&startTime, NULL)) {
        }
        else {
            XCTAssertFalse( (1) );
        }
        while ((status = psxThread_getState(pObj->pThread)) == PSXTHREAD_STATE_DELAYING) {
        }
        if (0 == gettimeofday(&endTime, NULL)) {
        }
        else {
            XCTAssertFalse( (1) );
        }
        fprintf(stderr, "Delaying Time = %ld:%d\n",
                (endTime.tv_sec - startTime.tv_sec),
                (endTime.tv_usec - startTime.tv_usec)
                );
#endif
        status = psxThread_getState(pObj->pThread);
        XCTAssertTrue( ((status == PSXTHREAD_STATE_RUNNING) || (status == PSXTHREAD_STATE_DELAYING)) );
        {
            int         save = count;
            ASTR_DATA       *pStr = psxThread_ToDebugString(pObj->pThread, 0);
            fprintf(stderr, "After Sleep(10 sec):  %s\n", AStr_getData(pStr));
            obj_Release(pStr);
            fprintf(stderr, "Count = %d\n", save);
            XCTAssertTrue( ((save > 18) && (save < 22)) );
        }
#if defined(__MACOSX_ENV__)
        if (0 == gettimeofday(&startTime, NULL)) {
        }
        else {
            XCTAssertFalse( (1) );
        }
        while ((status = psxThread_getState(pObj->pThread)) == PSXTHREAD_STATE_DELAYING) {
        }
        if (0 == gettimeofday(&endTime, NULL)) {
        }
        else {
            XCTAssertFalse( (1) );
        }
        fprintf(stderr, "Delaying Time = %ld:%d\n",
                (endTime.tv_sec - startTime.tv_sec),
                (endTime.tv_usec - startTime.tv_usec)
                );
#endif
        
        obj_Release(pObj);
        pObj = OBJ_NIL;
    }


    fprintf(stderr, "...%s completed.\n", pTestName);
    return 1;
}




TINYTEST_START_SUITE(test_timer);
  TINYTEST_ADD_TEST(test_timer_OpenClose,setUp,tearDown);
TINYTEST_END_SUITE();

TINYTEST_MAIN_SINGLE_SUITE(test_timer);





