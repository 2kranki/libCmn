

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


#include    "cmn_defs.h"





@interface scanDec32Tests : XCTestCase

@end

@implementation scanDec32Tests


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




- (void)test01
{
	char        *testString = " 1";
    bool        fRc;
    char        *pCurChr = testString;
    uint32_t    cScanned = 0;
    uint32_t    value = 0;
    
    
	fRc = scanDec32( &pCurChr, &cScanned, &value );
    XCTAssertTrue( (fRc), @"fRc should be true" );
    XCTAssertTrue( ('\0' == *pCurChr), @"Invalid pCurChr" );
    XCTAssertTrue( (2 == cScanned), @"cScanned is %d, should be 2", cScanned );
    XCTAssertTrue( (1 == value), @"value is %d, should be 1", value );

}


- (void)test02
{
	char        *testString = " -1 ";
    bool        fRc;
    char        *pCurChr = testString;
    uint32_t    cScanned = 0;
    uint32_t    value = 0;
    
    
	fRc = scanDec32( &pCurChr, &cScanned, &value );
    XCTAssertTrue( (fRc), @"fRc should be true" );
    XCTAssertTrue( (' ' == *pCurChr), @"Invalid pCurChr" );
    XCTAssertTrue( (3 == cScanned), @"cScanned is %d, should be 3", cScanned );
    XCTAssertTrue( (0xFFFFFFFF == value), @"value is %d, should be 0xFFFFFFFF", value );
    
}


@end



