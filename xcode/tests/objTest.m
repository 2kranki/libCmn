
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
//      STAssert(expression, failure_description, ...)
//      STFail(failure_description, ...)
//      STAssertEqualObjects(object_1, object_2, failure_description, ...) uses isEqualTo:
//      STAssertEquals(value_1, value_2, failure_description, ...)
//      STAssertEqualsWithAccuracy(value_1, value_2, accuracy, failure_description, ...)
//      STAssertNil(expression, failure_description, ...)
//      STAssertNotNil(expression, failure_description, ...)
//      STAssertTrue(expression, failure_description, ...)
//      STAssertFalse(expression, failure_description, ...)
//      STAssertThrows(expression, failure_description, ...)
//      STAssertThrowsSpecific(expression, exception_class, failure_description, ...)
//      STAssertThrowsSpecificNamed(expression, exception_class, exception_name, failure_description, ...)
//      STAssertNoThrow(expression, failure_description, ...)
//      STAssertNoThrowSpecific(expression, exception_class, failure_description, ...)
//      STAssertNoThrowSpecificNamed(expression, exception_class, exception_name, failure_description, ...)


#include    "obj.h"



@interface objTests : XCTestCase

@end

@implementation objTests


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




- (void)testOpenClose_1
{
	OBJ_DATA    *pObj;
    uint16_t    size = 200;
    bool        fRc;

    pObj = obj_Alloc(size);
    XCTAssertFalse( (OBJ_NIL == pObj) );
    XCTAssertTrue( (1 == obj_getRetainCount(pObj)) );
    XCTAssertTrue( (OBJ_IDENT_OBJ == obj_getIdent(pObj)) );
    XCTAssertTrue( (size == obj_getSize(pObj)) );
    XCTAssertTrue( (obj_IsFlag(pObj, OBJ_FLAG_ALLOC)) );

    pObj = obj_Init(pObj, size, OBJ_IDENT_CON);
    XCTAssertFalse( (OBJ_NIL == pObj) );
    XCTAssertTrue( (1 == obj_getRetainCount(pObj)) );
    XCTAssertTrue( (OBJ_IDENT_CON == obj_getIdent(pObj)) );
    XCTAssertTrue( (size == obj_getSize(pObj)) );
    XCTAssertTrue( (obj_IsFlag(pObj, OBJ_FLAG_ALLOC)) );
    XCTAssertTrue( (obj_IsFlag(pObj, OBJ_FLAG_INIT)) );
    
    fRc = obj_FlagOn(pObj, 5);
    XCTAssertTrue( (fRc) );
    fRc = obj_IsFlag(pObj, 5);
    XCTAssertTrue( (fRc) );
    fRc = obj_FlagOff(pObj, 5);
    XCTAssertTrue( (fRc) );
    fRc = obj_IsFlag(pObj, 5);
    XCTAssertTrue( (!fRc) );
    XCTAssertTrue( (obj_IsFlag(pObj, OBJ_FLAG_ALLOC)) );
    XCTAssertTrue( (obj_IsFlag(pObj, OBJ_FLAG_INIT)) );
    
    fRc = obj_FlagOn(pObj, 15);
    XCTAssertTrue( (fRc) );
    fRc = obj_IsFlag(pObj, 15);
    XCTAssertTrue( (fRc) );
    fRc = obj_FlagOff(pObj, 15);
    XCTAssertTrue( (fRc) );
    fRc = obj_IsFlag(pObj, 15);
    XCTAssertTrue( (!fRc) );
    XCTAssertTrue( (obj_IsFlag(pObj, OBJ_FLAG_ALLOC)) );
    XCTAssertTrue( (obj_IsFlag(pObj, OBJ_FLAG_INIT)) );
    
    pObj = obj_Release(pObj);
    // At this point, the object should have been de-allocated.
    
}



- (void)testSetVtbl
{
	OBJ_DATA    *pObj;
    uint16_t    size = 200;
    bool        fRc;
    
    pObj = obj_Alloc(size);
    XCTAssertFalse( (OBJ_NIL == pObj) );
    XCTAssertTrue( (1 == obj_getRetainCount(pObj)) );
    XCTAssertTrue( (OBJ_IDENT_OBJ == obj_getIdent(pObj)) );
    XCTAssertTrue( (size == obj_getSize(pObj)) );
    
    pObj = obj_Init(pObj, size, OBJ_IDENT_CON);
    XCTAssertFalse( (OBJ_NIL == pObj) );
    XCTAssertTrue( (1 == obj_getRetainCount(pObj)) );
    XCTAssertTrue( (OBJ_IDENT_CON == obj_getIdent(pObj)) );
    XCTAssertTrue( (size == obj_getSize(pObj)) );
    
    fRc = pObj->pVtbl->pIsKindOf(OBJ_IDENT_OBJ);
    XCTAssertTrue( (fRc) );
    fRc = pObj->pVtbl->pIsKindOf(OBJ_IDENT_CON);
    XCTAssertFalse( (fRc) );
    fRc = pObj->pVtbl->pIsKindOf(OBJ_IDENT_ASTR);
    XCTAssertFalse( (fRc) );
    
    pObj = obj_Release(pObj);
	pObj = OBJ_NIL;
    
}



@end



