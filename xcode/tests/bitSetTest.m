/*
 *	Generated 06/21/2015 14:16:25
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


#include    "cmn_defs.h"
#include    "bitSet_internal.h"




@interface bitSetTests : XCTestCase

@end

@implementation bitSetTests


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
    BITSET_DATA	*pObj = OBJ_NIL;
   
    pObj = bitSet_Alloc(0);
    XCTAssertFalse( (OBJ_NIL == pObj), @"Could not alloc  BITSET_DATA" );
    pObj = bitSet_Init( pObj );
    XCTAssertFalse( (OBJ_NIL == pObj), @"Could not init  BITSET_DATA" );
    if (pObj) {
        obj_Release(pObj);
        pObj = OBJ_NIL;
    }

}



- (void)testGetPut01
{
    BITSET_DATA	*pObj = OBJ_NIL;
    uint16_t    i;
    ERESULT     eRc;
    ASTR_DATA   *pStr;
    bool        fRc;
    
    pObj = bitSet_Alloc(16);
    XCTAssertFalse( (OBJ_NIL == pObj), @"" );
    pObj = bitSet_Init( pObj );
    XCTAssertFalse( (OBJ_NIL == pObj), @"" );
    if (pObj) {
        
        pStr = bitSet_ToDebugString(pObj, 0);
        fprintf(stderr, "%s\n\n\n", AStr_getData(pStr));
        obj_Release(pStr);
        pStr = OBJ_NIL;
        for (i=0; i<16; ++i) {
            eRc = bitSet_Set(pObj, i+1, true);
            XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)), @"" );
            fRc = bitSet_Get(pObj, i+1);
            XCTAssertTrue( (fRc), @"" );
        }
        pStr = bitSet_ToDebugString(pObj, 0);
        fprintf(stderr, "%s\n\n\n", AStr_getData(pStr));
        obj_Release(pStr);
        pStr = OBJ_NIL;
        
        obj_Release(pObj);
        pObj = OBJ_NIL;
    }
    
}



@end



