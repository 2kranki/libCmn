/*
 *	Generated 09/19/2016 20:13:13
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


#include    "audioWAV_internal.h"



@interface audioWAVTests : XCTestCase

@end

@implementation audioWAVTests


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
    AUDIOWAV_DATA	*pObj = OBJ_NIL;
   
    pObj = audioWAV_Alloc(0);
    XCTAssertFalse( (OBJ_NIL == pObj) );
    pObj = audioWAV_Init( pObj, 2, 22050, 8 );
    XCTAssertFalse( (OBJ_NIL == pObj) );
    if (pObj) {
        obj_Release(pObj);
        pObj = OBJ_NIL;
    }

}



- (void)testSilence
{
    AUDIOWAV_DATA	*pObj = OBJ_NIL;
    ERESULT         eRc;
    PATH_DATA       *pPath = OBJ_NIL;
    
    pObj = audioWAV_Alloc( );
    XCTAssertFalse( (OBJ_NIL == pObj) );
    pObj = audioWAV_Init(pObj, 2, 44100, 16);
    XCTAssertFalse( (OBJ_NIL == pObj) );
    if (pObj) {
        
        eRc = audioWAV_AppendSilence(pObj, 10000);
        XCTAssertFalse( (ERESULT_FAILED(eRc)) );
        pPath = path_NewA("~/audioTest01.wav");
        eRc = audioWAV_WriteToFile(pObj, pPath);
        XCTAssertFalse( (ERESULT_FAILED(eRc)) );
        obj_Release(pPath);
        pPath = OBJ_NIL;
        
        obj_Release(pObj);
        pObj = OBJ_NIL;
    }
    
}



- (void)testSineWave
{
    AUDIOWAV_DATA	*pObj = OBJ_NIL;
    ERESULT         eRc;
    PATH_DATA       *pPath = OBJ_NIL;
    
    pObj = audioWAV_Alloc( );
    XCTAssertFalse( (OBJ_NIL == pObj) );
    pObj = audioWAV_Init(pObj, 1, 11025, 16);
    XCTAssertFalse( (OBJ_NIL == pObj) );
    if (pObj) {
        
        eRc = audioWAV_AppendSineWave(pObj, 740, 1);
        XCTAssertFalse( (ERESULT_FAILED(eRc)) );
        pPath = path_NewA("~/audioTest02.wav");
        eRc = audioWAV_WriteToFile(pObj, pPath);
        XCTAssertFalse( (ERESULT_FAILED(eRc)) );
        obj_Release(pPath);
        pPath = OBJ_NIL;
        
        obj_Release(pObj);
        pObj = OBJ_NIL;
    }
    
}



@end



