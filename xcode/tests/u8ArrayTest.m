/*
 *	Generated 08/07/2015 09:47:23
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


#include    "u8Array_internal.h"



@interface u8ArrayTests : XCTestCase

@end

@implementation u8ArrayTests


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
    U8ARRAY_DATA	*pObj = OBJ_NIL;
   
    pObj = u8Array_Alloc(0);
    XCTAssertFalse( (OBJ_NIL == pObj) );
    pObj = u8Array_Init( pObj );
    XCTAssertFalse( (OBJ_NIL == pObj) );
    if (pObj) {
        obj_Release(pObj);
        pObj = OBJ_NIL;
    }

}



- (void)testAddGet01
{
    U8ARRAY_DATA	*pObj = OBJ_NIL;
    uint32_t        i;
    ERESULT         eRc;
    uint8_t         data;
    
    pObj = u8Array_Alloc(0);
    XCTAssertFalse( (OBJ_NIL == pObj), @"" );
    pObj = u8Array_Init( pObj );
    XCTAssertFalse( (OBJ_NIL == pObj), @"" );
    if (pObj) {
        
        data = 0;
        for (i=1; i<=64; ++i) {
            eRc = u8Array_AppendData(pObj, i, NULL);
            XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
        }
        
        for (i=1; i<=64; ++i) {
            data = u8Array_Get(pObj, i);
            XCTAssertTrue( (data == i), @"" );
        }
        
        obj_Release(pObj);
        pObj = OBJ_NIL;
    }
    
}



- (void)testInsertData01
{
    U8ARRAY_DATA	*pObj = OBJ_NIL;
    uint32_t        i;
    ERESULT         eRc;
    uint8_t         data;
    const
    char            *pTest1 = "abc";
    const
    char            *pTest2 = "def";
    const
    char            *pTest3 = "abdefc";
    
    pObj = u8Array_Alloc(0);
    XCTAssertFalse( (OBJ_NIL == pObj), @"" );
    pObj = u8Array_Init( pObj );
    XCTAssertFalse( (OBJ_NIL == pObj), @"" );
    if (pObj) {
        
        eRc = u8Array_InsertData(
                        pObj,
                        1,
                        (uint32_t)strlen(pTest1),
                        (const uint8_t *)pTest1
            );
        XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
        
        eRc = u8Array_InsertData(
                                 pObj,
                                 u8Array_getSize(pObj),
                                 (uint32_t)strlen(pTest2),
                                 (const uint8_t *)pTest2
                                 );
        XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
        
        i = (uint32_t)(strlen(pTest1) + strlen(pTest2));
        XCTAssertTrue( (i == u8Array_getSize(pObj)), @"" );
        
        for (i=1; i<=strlen(pTest3); ++i) {
            data = u8Array_Get(pObj, i);
            XCTAssertTrue( (data == pTest3[i-1]), @"" );
        }
        
        obj_Release(pObj);
        pObj = OBJ_NIL;
    }
    
}



- (void)testInsertData02
{
    U8ARRAY_DATA	*pObj = OBJ_NIL;
    uint32_t        i;
    ERESULT         eRc;
    uint8_t         data;
    const
    char            *pTest1 = "abc";
    const
    char            *pTest2 = "def";
    const
    char            *pTest3 = "abcdef";
    
    pObj = u8Array_Alloc(0);
    XCTAssertFalse( (OBJ_NIL == pObj), @"" );
    pObj = u8Array_Init( pObj );
    XCTAssertFalse( (OBJ_NIL == pObj), @"" );
    if (pObj) {
        
        eRc = u8Array_InsertData(
                                 pObj,
                                 1,
                                 (uint32_t)strlen(pTest1),
                                 (const uint8_t *)pTest1
                                 );
        XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
        
        eRc = u8Array_InsertData(
                                 pObj,
                                 (u8Array_getSize(pObj)+1),
                                 (uint32_t)strlen(pTest2),
                                 (const uint8_t *)pTest2
                                 );
        XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
        
        i = (uint32_t)(strlen(pTest1) + strlen(pTest2));
        XCTAssertTrue( (i == u8Array_getSize(pObj)), @"" );
        
        for (i=1; i<=strlen(pTest3); ++i) {
            data = u8Array_Get(pObj, i);
            XCTAssertTrue( (data == pTest3[i-1]), @"" );
        }
        
        obj_Release(pObj);
        pObj = OBJ_NIL;
    }
    
}



- (void)testInsertData03
{
    U8ARRAY_DATA	*pObj = OBJ_NIL;
    uint32_t        i;
    ERESULT         eRc;
    uint8_t         data;
    const
    char            *pTest1 = "abc";
    const
    char            *pTest2 = "def";
    const
    char            *pTest3 = "defabc";
    
    pObj = u8Array_Alloc(0);
    XCTAssertFalse( (OBJ_NIL == pObj), @"" );
    pObj = u8Array_Init( pObj );
    XCTAssertFalse( (OBJ_NIL == pObj), @"" );
    if (pObj) {
        
        eRc = u8Array_InsertData(
                                 pObj,
                                 1,
                                 (uint32_t)strlen(pTest1),
                                 (const uint8_t *)pTest1
                                 );
        XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
        
        eRc = u8Array_InsertData(
                                 pObj,
                                 1,
                                 (uint32_t)strlen(pTest2),
                                 (const uint8_t *)pTest2
                                 );
        XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
        
        i = (uint32_t)(strlen(pTest1) + strlen(pTest2));
        XCTAssertTrue( (i == u8Array_getSize(pObj)), @"" );
        
        for (i=1; i<=strlen(pTest3); ++i) {
            data = u8Array_Get(pObj, i);
            XCTAssertTrue( (data == pTest3[i-1]), @"" );
        }
        
        obj_Release(pObj);
        pObj = OBJ_NIL;
    }
    
}



- (void)testPutGet01
{
    U8ARRAY_DATA	*pObj = OBJ_NIL;
    uint32_t        i;
    ERESULT         eRc;
    uint16_t        data16 = 0;
    uint32_t        data32 = 0;
    
    pObj = u8Array_Alloc( );
    XCTAssertFalse( (OBJ_NIL == pObj) );
    pObj = u8Array_Init( pObj );
    XCTAssertFalse( (OBJ_NIL == pObj) );
    if (pObj) {
        
        eRc = u8Array_PutU16(pObj, 1, 12345);
        XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
        i = u8Array_getSize(pObj);
        XCTAssertTrue( (i == 2) );
        
        data16 = 0;
        eRc = u8Array_GetU16(pObj, 1, &data16);
        fprintf(stderr, "data = %d\n", data16);
        XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
        XCTAssertTrue( (data16 == 12345) );
        
        eRc = u8Array_PutU24(pObj, 1, 12345678);
        XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
        i = u8Array_getSize(pObj);
        XCTAssertTrue( (i == 3) );
        
        data32 = 0;
        eRc = u8Array_GetU24(pObj, 1, &data32);
        fprintf(stderr, "data = %d\n", data32);
        XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
        XCTAssertTrue( (data32 == 12345678) );
        
        eRc = u8Array_PutU32(pObj, 1, 12345678);
        XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
        i = u8Array_getSize(pObj);
        XCTAssertTrue( (i == 4) );
        
        data32 = 0;
        eRc = u8Array_GetU32(pObj, 1, &data32);
        fprintf(stderr, "data = %d\n", data32);
        XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
        XCTAssertTrue( (data32 == 12345678) );
        
        obj_Release(pObj);
        pObj = OBJ_NIL;
    }
    
}



@end



