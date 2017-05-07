/*
 *	Generated 10/07/2016 10:36:42
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


#include    "arrayExpand_internal.h"



@interface arrayExpandTests : XCTestCase

@end

@implementation arrayExpandTests


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
    ARRAYEXPAND_DATA	*pObj = OBJ_NIL;
   
    pObj = arrayExpand_Alloc(0);
    XCTAssertFalse( (OBJ_NIL == pObj) );
    pObj = arrayExpand_Init(pObj, 4);
    XCTAssertFalse( (OBJ_NIL == pObj) );
    if (pObj) {
        
        obj_Release(pObj);
        pObj = OBJ_NIL;
    }

}



- (void)testElem1
{
    ARRAYEXPAND_DATA *pObj = OBJ_NIL;
    uint8_t         *pData;
    
    pObj = arrayExpand_Alloc(0);
    XCTAssertFalse( (OBJ_NIL == pObj) );
    pObj = arrayExpand_Init(pObj, 1);
    XCTAssertFalse( (OBJ_NIL == pObj) );
    if (pObj) {
        
        pData = arrayExpand_Elem(pObj, 2);
        XCTAssertFalse( (pData == NULL) );
        XCTAssertFalse( (ERESULT_HAS_FAILED(arrayExpand_getLastError(pObj))) );
        XCTAssertTrue( (pData == (pObj->pArray + 2-1)) );
        
        pData = arrayExpand_Elem(pObj, 4);
        XCTAssertFalse( (pData == NULL) );
        XCTAssertFalse( (ERESULT_HAS_FAILED(arrayExpand_getLastError(pObj))) );
        XCTAssertTrue( (pData == (pObj->pArray + 4-1)) );
        
        pData = arrayExpand_Elem(pObj, 2);
        XCTAssertFalse( (pData == NULL) );
        XCTAssertFalse( (ERESULT_HAS_FAILED(arrayExpand_getLastError(pObj))) );
        XCTAssertTrue( (pData == (pObj->pArray + 2-1)) );
        
        obj_Release(pObj);
        pObj = OBJ_NIL;
    }
    
}



- (void)testExpandTo
{
    ARRAYEXPAND_DATA *pObj = OBJ_NIL;
    ERESULT         eRc;
    
    pObj = arrayExpand_Alloc(0);
    XCTAssertFalse( (OBJ_NIL == pObj) );
    pObj = arrayExpand_Init(pObj, 1);
    XCTAssertFalse( (OBJ_NIL == pObj) );
    if (pObj) {
        
        eRc = arrayExpand_ExpandTo(pObj, 2);
        XCTAssertFalse( (ERESULT_HAS_FAILED(eRc)) );
        XCTAssertTrue( (pObj->max == 2) );
        
        eRc = arrayExpand_ExpandTo(pObj, 4);
        XCTAssertFalse( (ERESULT_HAS_FAILED(eRc)) );
        XCTAssertTrue( (pObj->max == 4) );
        
        eRc = arrayExpand_ExpandTo(pObj, 512);
        XCTAssertFalse( (ERESULT_HAS_FAILED(eRc)) );
        XCTAssertTrue( (pObj->max == 512) );
        
        obj_Release(pObj);
        pObj = OBJ_NIL;
    }
    
}



@end



