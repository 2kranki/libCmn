/*
 *	Generated 06/06/2017 23:20:26
 */


#import <XCTest/XCTest.h>



// All code under test must be linked into the Unit Test bundle
// Test Macros:
//      XCTAssert(expression, failure_description, ...)
//      XCTFail(failure_description, ...)
//      XCTAssertEqualObjects(object_1, object_2, failure_description, ...) uses isEqualTo:
//      XCTAssertEquals(value_1, value_2, failure_description, ...)
//      XCTAssertEqualsWithAccuracy(value_1, value_2, accuracy, failure_description, ...)
//      XCTAssertNil(expression, failure_description, ...)
//      XCTAssertNotNil(expression, failure_description, ...)
//      XCTAssertTrue(expression, failure_description, ...)
//      XCTAssertFalse(expression, failure_description, ...)
//      XCTAssertThrows(expression, failure_description, ...)
//      XCTAssertThrowsSpecific(expression, exception_class, failure_description, ...)
//      XCTAssertThrowsSpecificNamed(expression, exception_class, exception_name, failure_description, ...)
//      XCTAssertNoThrow(expression, failure_description, ...)
//      XCTAssertNoThrowSpecific(expression, exception_class, failure_description, ...)
//      XCTAssertNoThrowSpecificNamed(expression, exception_class, exception_name, failure_description, ...)


#include    <timer_internal.h>


static
int             count = 0;


void *          timerRoutine(
)
{
    ++count;
    fprintf(stderr, "timerCounter = %d\n", count);
    return NULL;
}






@interface timerTests : XCTestCase

@end

@implementation timerTests


- (void)setUp
{
    [super setUp];
    
    mem_Init( );
    
    // Put setup code here. This method is called before the invocation of each
    // test method in the class.
    count = 0;
}


- (void)tearDown
{
    // Put teardown code here. This method is called after the invocation of each
    // test method in the class.

    mem_Dump( );
    mem_Release( );

    [super tearDown];
}




- (void)testOpenClose
{
    TIMER_DATA      *pObj = OBJ_NIL;
    uint32_t        status;
#if defined(__MACOSX_ENV__)
    struct timeval  startTime;
    struct timeval  endTime;
    int             iRc;
#endif

    fprintf(stderr, "WARNING: this does not run correctly in the Obj-C environment!\n");
    fprintf(stderr, "(Probably, because the Obj-C environment has its own threading)\n");
    fprintf(stderr, "\n");
    
    fprintf(stderr, "timerRoutine = %p\n", timerRoutine);
    pObj = timer_Alloc(0);
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
        iRc = usleep(5*1000*1000);
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
            XCTAssertTrue( ((save > 8) && (save < 12)) );
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

}



@end



