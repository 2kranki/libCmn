/*
 *	Generated 02/11/2016 10:46:18
 */


/*
 This is free and unencumbered software released into the public domain.
 
 Anyone is free to copy, modify, publish, use, compile, sell, or
 distribute this software, either in source code form or as a compiled
 binary, for any purpose, commercial or non-commercial, and by any
 means.
 
 In jurisdictions that recognize copyright laws, the author or authors
 of this software dedicate any and all copyright interest in the
 software to the public domain. We make this dedication for the benefit
 of the public at large and to the detriment of our heirs and
 successors. We intend this dedication to be an overt act of
 relinquishment in perpetuity of all present and future rights to this
 software under copyright law.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
 IN NO EVENT SHALL THE AUTHORS BE LIABLE FOR ANY CLAIM, DAMAGES OR
 OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
 ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 OTHER DEALINGS IN THE SOFTWARE.
 
 For more information, please refer to <http://unlicense.org/>
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


#include    "psxThread_internal.h"


int         count = 0;

void *      testPausable(void *pData)
{

    ++count;
    
    return NULL;
}


void *      testNonpausable(void *pData)
{
    
    while (true) {
        ++count;
    }
    
    return NULL;
}




@interface psxThreadTests : XCTestCase

@end

@implementation psxThreadTests


- (void)setUp
{
    [super setUp];
    // Put setup code here. This method is called before the invocation of each
    // test method in the class.
    
    mem_Init( );
    
}


- (void)tearDown
{
    mem_Dump( );
    mem_Release( );
    
    // Put teardown code here. This method is called after the invocation of each
    // test method in the class.
    [super tearDown];
}




- (void)testOpenClose
{
    PSXTHREAD_DATA	*pObj = OBJ_NIL;
   
    pObj = psxThread_Alloc();
    XCTAssertFalse( (OBJ_NIL == pObj) );
    pObj = psxThread_Init( pObj, testPausable, NULL, 0 );
    XCTAssertFalse( (OBJ_NIL == pObj) );
    if (pObj) {
        obj_Release(pObj);
        pObj = OBJ_NIL;
        fprintf(stderr, "Count = %d\n",count);
    }

}



- (void)testRun01
{
    PSXTHREAD_DATA	*pObj = OBJ_NIL;
    bool            fRc;
    uint32_t        status;
    
    pObj = psxThread_Alloc();
    XCTAssertFalse( (OBJ_NIL == pObj) );
    pObj = psxThread_Init( pObj, testPausable, NULL, 0 );
    XCTAssertFalse( (OBJ_NIL == pObj) );
    if (pObj) {

#if defined(__MACOSX_ENV__)
        sleep(3);
#endif
#if defined(__WIN32_ENV__) || defined(__WIN64_ENV__)
        Sleep(3000);
#endif
        {
            ASTR_DATA       *pStr = psxThread_ToDebugString(pObj, 0);
            fprintf(stderr, "After Start:  %s\n", AStr_getData(pStr));
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
        Sleep(3000);
#endif
        {
            ASTR_DATA       *pStr = psxThread_ToDebugString(pObj, 0);
            fprintf(stderr, "After Pause:  %s\n", AStr_getData(pStr));
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
        Sleep(3000);
#endif
        {
            ASTR_DATA       *pStr = psxThread_ToDebugString(pObj, 0);
            fprintf(stderr, "After Resume:  %s\n", AStr_getData(pStr));
            obj_Release(pStr);
            fprintf(stderr, "Count = %d\n",count);
        }

        fRc = psxThread_Terminate(pObj);
        XCTAssertTrue( (fRc) );
#if defined(__MACOSX_ENV__)
        sleep(3);
#endif
#if defined(__WIN32_ENV__) || defined(__WIN64_ENV__)
        Sleep(3000);
#endif
        {
            ASTR_DATA       *pStr = psxThread_ToDebugString(pObj, 0);
            fprintf(stderr, "After Stop:  %s\n", AStr_getData(pStr));
            obj_Release(pStr);
            fprintf(stderr, "Count = %d\n",count);
        }
        
        fRc = psxThread_Join(pObj, NULL);
        XCTAssertTrue( (fRc) );

        obj_Release(pObj);
        pObj = OBJ_NIL;
        fprintf(stderr, "Count = %d\n",count);
    }
    
}



@end



