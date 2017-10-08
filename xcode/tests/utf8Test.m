/*
 *	Generated 08/06/2015 20:23:35
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


#include    "utf8_internal.h"


// Faked UTF-8 of 0x01..0x04 in 1..4 bytes
static
const
char        *pString1 = "\x01\xC0\x82\xE0\x80\x83\xF8\x80\x80\x84\x00";


#ifdef XYZZY
static
const
int32_t         whiteSpace[12] = {
    ' ',
    '\f',
    '\n',
    '\r',
    '\t',
    0x0085,     // Next New Line (Paragraph break)
    0x00A0,     // no-break space
    0x200B,     // zero width space
    0x2060,     // word joiner
    0x3000,     // ideographic space
    0xFEFF,     // zero width no-break space
    0
};
#endif


#ifdef XYZZY
static
const
char        whiteSpaceA[22] = {
    ' ','\f','\n','\r','\t',
    0xC2,0x85,          // Next New Line (Paragraph break)
    0xC2,0xA0,          // no-break space
    0xE2,0x80,0x8B,     // zero width space
    0xE2,0x81,0xA0,     // word joiner
    0xE3,0x80,0x80,     // ideographic space
    0xEF,0xBB,0xBF,     // zero width no-break space
    0
};
#endif






@interface utf8Tests : XCTestCase

@end

@implementation utf8Tests


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
    UTF8_DATA	*pObj = OBJ_NIL;
   
    pObj = utf8_Alloc(0);
    XCTAssertFalse( (OBJ_NIL == pObj) );
    pObj = utf8_Init( pObj );
    XCTAssertFalse( (OBJ_NIL == pObj) );
    if (pObj) {
        obj_Release(pObj);
        pObj = OBJ_NIL;
    }

}



- (void)testScan01
{
    uint32_t    i = 0;
    uint32_t    j = 0;
    const
    char        *pStr;
    
    pStr = pString1;
    for (i=1; i<=4; ++i) {
        j = utf8_Utf8ToWC_Scan(&pStr);
        XCTAssertTrue( (i == j) );
    }
    
}



- (void)testChrLen01
{
    int         len = 0;
    
    len = utf8_ChrLen(pString1[0]);
    XCTAssertTrue( (1 == len) );
    len = utf8_ChrLen(pString1[1]);
    XCTAssertTrue( (2 == len) );
    len = utf8_ChrLen(pString1[3]);
    XCTAssertTrue( (3 == len) );
    len = utf8_ChrLen(pString1[6]);
    XCTAssertTrue( (4 == len) );
    
}



- (void)testStrOffset01
{
    int32_t     len = 0;
    
    len = utf8_StrOffset(pString1,1);
    XCTAssertTrue( (1 == len) );
    len = utf8_StrOffset(pString1,2);
    XCTAssertTrue( (2 == len) );
    len = utf8_StrOffset(pString1,3);
    XCTAssertTrue( (4 == len) );
    len = utf8_StrOffset(pString1,4);
    XCTAssertTrue( (7 == len) );
    len = utf8_StrOffset(pString1,5);
    XCTAssertTrue( (11 == len) );
    len = utf8_StrOffset(pString1,6);
    XCTAssertTrue( (-1 == len) );
    
}



@end



