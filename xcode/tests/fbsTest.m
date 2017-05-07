/*
 *	Generated 07/01/2015 10:14:52
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


#include    "fbsi_internal.h"
#include    "fbso_internal.h"



@interface fbsTests : XCTestCase

@end

@implementation fbsTests


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




- (void)testFbsoFbsi
{
    FBSI_DATA	*pObjI = OBJ_NIL;
    FBSO_DATA	*pObjO = OBJ_NIL;
    const
    char        *pFilePathStr = "/Users/bob/Support/x/test.txt";
    PATH_DATA   *pFilePath = OBJ_NIL;
    
    pFilePath = path_NewA(pFilePathStr);
    XCTAssertFalse( (OBJ_NIL == pFilePath), @"" );
    
    pObjO = fbso_Alloc();
    XCTAssertFalse( (OBJ_NIL == pObjO), @"" );
    pObjO = fbso_Init( pObjO, pFilePath );
    XCTAssertFalse( (OBJ_NIL == pObjO), @"" );
    if (pObjO) {
        obj_Release(pObjO);
        pObjO = OBJ_NIL;
    }
    
    pObjI = fbsi_Alloc();
    XCTAssertFalse( (OBJ_NIL == pObjI), @"" );
    pObjI = fbsi_Init( pObjI, pFilePath );
    XCTAssertFalse( (OBJ_NIL == pObjI), @"" );
    if (pObjI) {
        obj_Release(pObjI);
        pObjI = OBJ_NIL;
    }
    
    obj_Release(pFilePath);
    
}



@end



