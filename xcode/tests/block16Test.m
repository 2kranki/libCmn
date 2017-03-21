
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


#include    "block16.h"
#include    "block16_internal.h"           // We cheat!


#define NUM_STR     10

/* Other variables */
static
char        *StrArray[NUM_STR] = {
//   123456789
	"String  1",
	"String  2",
	"String  3",
	"String  4",
	"String  5",
	"String  6",
	"String  7",
	"String  8",
	"String  9",
	"String 10"
};



@interface block16Tests : XCTestCase

@end

@implementation block16Tests


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
	BLOCK16_DATA    *cbp;

    mem_Init( );
    
	cbp = block16_Open( 0, 32 );
    XCTAssertTrue( (block16_Validate(cbp)) );
    XCTAssertFalse( (NULL == cbp) );
    XCTAssertTrue( (0 == block16_DataOffset(cbp)) );
	cbp = block16_Close( cbp );
    XCTAssertTrue( (NULL == cbp) );

	cbp = block16_Open( 7, 32 );
    XCTAssertFalse( (NULL == cbp) );
    XCTAssertTrue( (8 == block16_DataOffset(cbp)) );
	cbp = block16_Close( cbp );
    XCTAssertTrue( (NULL == cbp) );
    
}



- (void)testAddData01
{
	BLOCK16_DATA    *cbp;
    bool            fRc;
    uint32_t        i;
    void            *pData;
    
    mem_Init( );
    
    // BLock without a header.
	cbp = block16_Open( 0, 32 );
    XCTAssertFalse( (NULL == cbp) );
    XCTAssertTrue( (0 == block16_DataOffset(cbp)) );

    i = block16_UnusedDataSize(cbp);
    XCTAssertTrue( (32 == i) );

    fRc = block16_AddData(cbp, 9, StrArray[0] );
    XCTAssertTrue( (fRc), @"block_AddData failed!" );
    XCTAssertTrue( (9 == cbp->dataUsed) );

    pData = block16_DataPtr( cbp );
    XCTAssertTrue( (pData == &cbp->header[0]) );
    i = memcmp( pData, StrArray[0], 9 );
    XCTAssertTrue( (i == 0) );
    
    i = block16_UnusedDataSize(cbp);
    XCTAssertTrue( ((32-9) == i) );

	cbp = block16_Close( cbp );
    XCTAssertTrue( (NULL == cbp) );
    
    
    // Block with a header.
	cbp = block16_Open( 7, 32 );
    XCTAssertFalse( (NULL == cbp) );
    XCTAssertTrue( (8 == block16_DataOffset(cbp)) );
    
    i = block16_UnusedDataSize(cbp);
    XCTAssertTrue( (32 == i) );
    
    fRc = block16_AddData(cbp, 9, StrArray[0] );
    XCTAssertTrue( (fRc) );
    XCTAssertTrue( (9 == cbp->dataUsed) );
    
    pData = block16_DataPtr( cbp );
    XCTAssertTrue( (pData == &cbp->header[8]) );
    i = memcmp( pData, StrArray[0], 9 );
    XCTAssertTrue( (i == 0) );
    
    i = block16_UnusedDataSize(cbp);
    XCTAssertTrue( ((32-9) == i) );
    
	cbp = block16_Close( cbp );
    XCTAssertTrue( (NULL == cbp) );
    
}


@end



