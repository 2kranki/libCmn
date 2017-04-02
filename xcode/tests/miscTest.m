/*
 *	Generated 11/25/2015 16:57:23
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


#include    "misc_internal.h"



@interface miscTests : XCTestCase

@end

@implementation miscTests


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
    MISC_DATA	*pObj = OBJ_NIL;
   
    pObj = misc_Alloc(0);
    XCTAssertFalse( (OBJ_NIL == pObj), @"" );
    pObj = misc_Init( pObj );
    XCTAssertFalse( (OBJ_NIL == pObj), @"" );
    if (pObj) {
        obj_Release(pObj);
        pObj = OBJ_NIL;
    }

}



- (void)testAbbrev
{
    uint32_t        u32;
    uint64_t        u64;
    
    u32 = misc_BitReversal32(0x00000001);
    XCTAssertTrue( (u32 == 0x80000000) );
    u32 = misc_BitReversal32(0x80000000);
    XCTAssertTrue( (u32 == 0x00000001) );
    u32 = misc_BitReversal32(0x80000001);
    XCTAssertTrue( (u32 == 0x80000001) );
    
    u64 = misc_BitReversal64(0x0000000000000001);
    XCTAssertTrue( (u64 == 0x8000000000000000) );
    u64 = misc_BitReversal64(0x8000000000000000);
    XCTAssertTrue( (u64 == 0x0000000000000001) );

}



- (void)testBitReversal
{
    bool        fRc;
    
    fRc = misc_AbbrevA("EXACT", "EXACT");
    XCTAssertTrue( (fRc) );
    fRc = misc_AbbrevA("EXACT", "exact");
    XCTAssertTrue( (fRc) );
    fRc = misc_AbbrevA("EXACT", "e");
    XCTAssertTrue( (!fRc) );
    fRc = misc_AbbrevA("Exact", "e");
    XCTAssertTrue( (fRc) );
    fRc = misc_AbbrevA("eXact", "x");
    XCTAssertTrue( (fRc) );
    fRc = misc_AbbrevA("eXact", "ext");
    XCTAssertTrue( (fRc) );
    fRc = misc_AbbrevA("eXact", "xray");
    XCTAssertTrue( (!fRc) );
    
}



- (void)testParity
{
    bool        fRc;
    //char        *pEquiv;
    //char        test[64];
    
    fRc = misc_ComputeEvenParity8(0x01);
    XCTAssertTrue( (!fRc) );
    fRc = misc_ComputeEvenParity8(0x02);
    XCTAssertTrue( (!fRc) );
    fRc = misc_ComputeEvenParity8(0x04);
    XCTAssertTrue( (!fRc) );
    fRc = misc_ComputeEvenParity8(0x08);
    XCTAssertTrue( (!fRc) );
    fRc = misc_ComputeEvenParity8(0x10);
    XCTAssertTrue( (!fRc) );
    fRc = misc_ComputeEvenParity8(0x20);
    XCTAssertTrue( (!fRc) );
    fRc = misc_ComputeEvenParity8(0x40);
    XCTAssertTrue( (!fRc) );
    fRc = misc_ComputeEvenParity8(0x80);
    XCTAssertTrue( (!fRc) );
    
    fRc = misc_ComputeEvenParity8(0x00);
    XCTAssertTrue( (fRc) );
    fRc = misc_ComputeEvenParity8(0x11);
    XCTAssertTrue( (fRc) );
    fRc = misc_ComputeEvenParity8(0x22);
    XCTAssertTrue( (fRc) );
    fRc = misc_ComputeEvenParity8(0x44);
    XCTAssertTrue( (fRc) );
    fRc = misc_ComputeEvenParity8(0x88);
    XCTAssertTrue( (fRc) );
    
}



- (void)testMatch
{
    bool        fRc;
    //char        *pEquiv;
    //char        test[64];
    
    fRc = misc_PatternMatchA("*.dmg","xyzzy.dmg",NULL,NULL);
    XCTAssertTrue( (fRc), @"" );
    fRc = misc_PatternMatchA("*.dmg","xyzzy.txt",NULL,NULL);
    XCTAssertTrue( (!fRc), @"" );
    fRc = misc_PatternMatchA("x?zz?.dmg","xyzzy.dmg",NULL,NULL);
    XCTAssertTrue( (fRc), @"" );
    fRc = misc_PatternMatchA("x?zy?.dmg","xyzzy.dmg",NULL,NULL);
    XCTAssertTrue( (!fRc), @"" );
    fRc = misc_PatternMatchA("x?zz?.*","xyzzy.dmg",NULL,NULL);
    XCTAssertTrue( (fRc), @"" );
    
}



@end



