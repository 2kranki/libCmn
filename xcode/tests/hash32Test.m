/*
 *	Generated 06/07/2015 08:07:00
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


#include    "hash32_internal.h"



@interface hash32Tests : XCTestCase

@end

@implementation hash32Tests


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
    HASH32_DATA	*pObj = OBJ_NIL;
   
    pObj = hash32_Alloc(0);
    XCTAssertFalse( (OBJ_NIL == pObj), @"Could not alloc  HASH32_DATA" );
    pObj = hash32_Init( pObj, 17 );
    XCTAssertFalse( (OBJ_NIL == pObj), @"Could not init  HASH32_DATA" );
    if (pObj) {
        obj_Release(pObj);
        pObj = OBJ_NIL;
    }

}



- (void)testAddFindDelete_1
{
    HASH32_DATA     *pObj = OBJ_NIL;
    uint32_t        i;
    uint32_t        cnt;
    bool            fRc;
    void            *pVoid;
    
    pObj = hash32_Alloc(0);
    XCTAssertFalse( (OBJ_NIL == pObj), @"Could not alloc  HASH32_DATA" );
    pObj = hash32_Init( pObj, 3 );
    XCTAssertFalse( (OBJ_NIL == pObj), @"Could not init  HASH32_DATA" );
    if (pObj) {
        
        for (i=0; i<10; ++i) {
            fRc = hash32_Add(pObj, i+1, (void *)(size_t)(i+1));
            XCTAssertTrue( (fRc), @"Could not Add()" );
            cnt = hash32_getCount(pObj);
            XCTAssertTrue( (cnt == (i+1)), @"Could not Count()" );
        }
        
        for (i=0; i<10; ++i) {
            pVoid = hash32_Find(pObj, i+1);
            XCTAssertTrue( ((uint32_t)pVoid == i+1), @"Could not Find()" );
        }
        
        pVoid = hash32_Find(pObj, 3);
        XCTAssertTrue( ((uint32_t)pVoid == 3), @"Could not Find()" );
        pVoid = hash32_Find(pObj, 9);
        XCTAssertTrue( ((uint32_t)pVoid == 9), @"Could not Find()" );
        pVoid = hash32_Find(pObj, 6);
        XCTAssertTrue( ((uint32_t)pVoid == 6), @"Could not Find()" );
        
        fRc = hash32_Delete(pObj, 5);
        XCTAssertTrue( (fRc), @"Could not Delete()" );
        cnt = hash32_getCount(pObj);
        XCTAssertTrue( (cnt == 9), @"Could not Count()" );
        
        fRc = hash32_Delete(pObj, 10);
        XCTAssertTrue( (fRc), @"Could not Delete()" );
        cnt = hash32_getCount(pObj);
        XCTAssertTrue( (cnt == 8), @"Could not Count()" );
        
        obj_Release(pObj);
        pObj = OBJ_NIL;
    }
    
}



@end



