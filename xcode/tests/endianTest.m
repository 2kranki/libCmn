/*
 *	Generated 10/25/2016 14:29:27
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


#include    "endian_internal.h"



@interface endianTests : XCTestCase

@end

@implementation endianTests


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




- (void)testGetPut
{
    ENDIAN_DATA	*pObj = OBJ_NIL;
    const
    uint16_t    cu16 = 0x0102;
    const
    uint32_t    cu24 = 0x00010203;
    const
    uint32_t    cu32 = 0x01020304;
    const
    uint64_t    cu64 = 0x0102030405060708;
    uint8_t     uout[9];
    int         i;
    uint16_t    u16 = 0x0102;
    uint32_t    u24 = 0x00010203;
    uint32_t    u32 = 0x01020304;
    uint64_t    u64 = 0x0102030405060708;
   
    pObj = endian_Alloc(0);
    XCTAssertFalse( (OBJ_NIL == pObj) );
    pObj = endian_Init( pObj );
    XCTAssertFalse( (OBJ_NIL == pObj) );
    if (pObj) {
        
        for (i=0; i<9; ++i) {
            uout[i] = 0;
        }
        endian_PutU16Big(pObj, cu16, uout);
        XCTAssertTrue( (uout[0] == 0x01) );
        XCTAssertTrue( (uout[1] == 0x02) );
        XCTAssertTrue( (uout[2] == 0x00) );
        u16 = endian_GetU16Big(pObj, uout);
        XCTAssertTrue( (u16 == cu16) );
        uout[0] = 0;
        uout[1] = 0;
        
        endian_PutU24Big(pObj, cu24, uout);
        XCTAssertTrue( (uout[0] == 0x01) );
        XCTAssertTrue( (uout[1] == 0x02) );
        XCTAssertTrue( (uout[2] == 0x03) );
        XCTAssertTrue( (uout[3] == 0x00) );
        u24 = endian_GetU24Big(pObj, uout);
        XCTAssertTrue( (u24 == cu24) );
        uout[0] = 0;
        uout[1] = 0;
        uout[2] = 0;

        endian_PutU32Big(pObj, cu32, uout);
        XCTAssertTrue( (uout[0] == 0x01) );
        XCTAssertTrue( (uout[1] == 0x02) );
        XCTAssertTrue( (uout[2] == 0x03) );
        XCTAssertTrue( (uout[3] == 0x04) );
        XCTAssertTrue( (uout[4] == 0x00) );
        u32 = endian_GetU32Big(pObj, uout);
        XCTAssertTrue( (u32 == cu32) );
        uout[0] = 0;
        uout[1] = 0;
        uout[2] = 0;
        uout[3] = 0;
        uout[4] = 0;
        
        endian_PutU64Big(pObj, cu64, uout);
        XCTAssertTrue( (uout[0] == 0x01) );
        XCTAssertTrue( (uout[1] == 0x02) );
        XCTAssertTrue( (uout[2] == 0x03) );
        XCTAssertTrue( (uout[3] == 0x04) );
        XCTAssertTrue( (uout[4] == 0x05) );
        XCTAssertTrue( (uout[5] == 0x06) );
        XCTAssertTrue( (uout[6] == 0x07) );
        XCTAssertTrue( (uout[7] == 0x08) );
        XCTAssertTrue( (uout[8] == 0x00) );
        u64 = endian_GetU64Big(pObj, uout);
        XCTAssertTrue( (u64 == cu64) );
        
        for (i=0; i<9; ++i) {
            uout[i] = 0;
        }
        endian_PutU16Little(pObj, cu16, uout);
        XCTAssertTrue( (uout[0] == 0x02) );
        XCTAssertTrue( (uout[1] == 0x01) );
        XCTAssertTrue( (uout[2] == 0x00) );
        u16 = endian_GetU16Little(pObj, uout);
        XCTAssertTrue( (u16 == cu16) );
        uout[0] = 0;
        uout[1] = 0;
        
        endian_PutU24Little(pObj, cu24, uout);
        XCTAssertTrue( (uout[0] == 0x03) );
        XCTAssertTrue( (uout[1] == 0x02) );
        XCTAssertTrue( (uout[2] == 0x01) );
        XCTAssertTrue( (uout[3] == 0x00) );
        u24 = endian_GetU24Little(pObj, uout);
        XCTAssertTrue( (u16 == cu16) );
        uout[0] = 0;
        uout[1] = 0;
        uout[2] = 0;
        
        endian_PutU32Little(pObj, cu32, uout);
        XCTAssertTrue( (uout[0] == 0x04) );
        XCTAssertTrue( (uout[1] == 0x03) );
        XCTAssertTrue( (uout[2] == 0x02) );
        XCTAssertTrue( (uout[3] == 0x01) );
        XCTAssertTrue( (uout[4] == 0x00) );
        u32 = endian_GetU32Little(pObj, uout);
        XCTAssertTrue( (u32 == cu32) );
        uout[0] = 0;
        uout[1] = 0;
        uout[2] = 0;
        uout[3] = 0;
        uout[4] = 0;
        
        endian_PutU64Little(pObj, cu64, uout);
        XCTAssertTrue( (uout[0] == 0x08) );
        XCTAssertTrue( (uout[1] == 0x07) );
        XCTAssertTrue( (uout[2] == 0x06) );
        XCTAssertTrue( (uout[3] == 0x05) );
        XCTAssertTrue( (uout[4] == 0x04) );
        XCTAssertTrue( (uout[5] == 0x03) );
        XCTAssertTrue( (uout[6] == 0x02) );
        XCTAssertTrue( (uout[7] == 0x01) );
        XCTAssertTrue( (uout[8] == 0x00) );
        u64 = endian_GetU64Little(pObj, uout);
        XCTAssertTrue( (u64 == cu64) );
        
        obj_Release(pObj);
        pObj = OBJ_NIL;
    }

}



@end



