

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


#include    "cb32.h"
#include    "cb32_internal.h"           // We cheat!





@interface cb32Tests : XCTestCase

@end

@implementation cb32Tests


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
	CB32_DATA       *cbp;

	cbp = cb32_Alloc(8);
    XCTAssertFalse( (NULL == cbp), @"Could not alloc" );
	cbp = cb32_Init( cbp );
    XCTAssertFalse( (NULL == cbp), @"Could not init" );
    if (cbp) {
        obj_Release(cbp);
        cbp = NULL;
    }

}



- (void)testPutGet01
{
	CB32_DATA       *cbp;
    uint32_t        i;
    uint32_t        data;
    bool            fRc;
    
	cbp = cb32_Alloc(8);
    XCTAssertFalse( (NULL == cbp), @"Could not alloc" );
	cbp = cb32_Init( cbp );
    XCTAssertFalse( (NULL == cbp), @"Could not init" );
    if (cbp) {
        
        for (i=0; i<8; ++i) {
            fRc = cb32_Put(cbp, i, 0);
            XCTAssertTrue( (fRc), @"" );
        }
        // Can't test this properly because TNeo simulation does not work well enough.
        //fRc = cb32_Put(cbp, i, 0);          // One too many
        //STAssertFalse( (fRc), @"" );
        
        for (i=0; i<8; ++i) {
            fRc = cb32_Get(cbp, &data, 0);
            XCTAssertTrue( (fRc), @"" );
            XCTAssertTrue( (i == data), @"" );
        }
        //fRc = cb32_Get(cbp, &data16, 0);    // One too many
        //STAssertFalse( (fRc), @"" );
        
        obj_Release(cbp);
        cbp = NULL;
    }
    
}



@end



