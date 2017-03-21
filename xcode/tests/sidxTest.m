/*
 *	Generated 09/07/2015 14:04:21
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
#import <libCmn/libCmn.h>



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


#include    "sidx_internal.h"



@interface sidxTests : XCTestCase

@end

@implementation sidxTests


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
    SIDX_DATA       *pObj = OBJ_NIL;
    uint32_t        i;
    uint32_t        iMax;
    bool            fRc;
    ASTR_DATA       *pStr;
    uint32_t        index;
    uint32_t        offset;
   
    pObj = sidx_Alloc(4);
    XCTAssertFalse( (OBJ_NIL == pObj), @"" );
    pObj = sidx_Init( pObj, 2 );
    XCTAssertFalse( (OBJ_NIL == pObj), @"" );
    if (pObj) {
        
        XCTAssertTrue( (4 == sidx_getSize(pObj)), @"" );
        
        iMax = 8;
        for (i=0; i<iMax; ++i) {
            fRc = sidx_AddIndex(pObj, i, (i*2));
            XCTAssertTrue( (fRc), @"" );
            XCTAssertTrue( (2 == sidx_getInterval(pObj)), @"" );
        }
        XCTAssertTrue( (4 == pObj->used), @"" );
        XCTAssertTrue( (6 == pObj->max), @"" );
        
        pStr = sidx_ToDebugString(pObj, 0);
        fprintf(stderr, "%s\n\n", AStr_getData(pStr));
        obj_Release(pStr);
        pStr = OBJ_NIL;
        
        iMax = 16;
        for (i=8; i<iMax; ++i) {
            fRc = sidx_AddIndex(pObj, i, (i*2));
            XCTAssertTrue( (fRc), @"" );
            XCTAssertTrue( (4 == sidx_getInterval(pObj)), @"" );
        }
        XCTAssertTrue( (4 == pObj->used), @"" );
        
        pStr = sidx_ToDebugString(pObj, 0);
        fprintf(stderr, "%s\n\n", AStr_getData(pStr));
        obj_Release(pStr);
        pStr = OBJ_NIL;
        
        fRc = sidx_FindIndex(pObj, 3, &index, &offset);
        XCTAssertTrue( (fRc), @"" );
        XCTAssertTrue( (0 == index), @"" );
        XCTAssertTrue( (0 == offset), @"" );
        
        fRc = sidx_FindIndex(pObj, 5, &index, &offset);
        XCTAssertTrue( (fRc), @"" );
        XCTAssertTrue( (4 == index), @"" );
        XCTAssertTrue( (8 == offset), @"" );
        
        fRc = sidx_FindIndex(pObj, 15, &index, &offset);
        XCTAssertTrue( (fRc), @"" );
        XCTAssertTrue( (12 == index), @"" );
        XCTAssertTrue( (24 == offset), @"" );
        
        obj_Release(pObj);
        pObj = OBJ_NIL;
    }

}



@end



