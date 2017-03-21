/*
 *	Generated 08/25/2015 20:42:16
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


#include    "pwr2Array_internal.h"



@interface pwr2ArrayTests : XCTestCase

@end

@implementation pwr2ArrayTests


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
    PWR2ARRAY_DATA	*pObj = OBJ_NIL;
    ERESULT         eRc;
    char            *pStr;
    uint32_t        i;
   
    pObj = pwr2Array_Alloc(0);
    XCTAssertFalse( (OBJ_NIL == pObj), @"" );
    pObj = pwr2Array_Init( pObj, 0 );           // 1 byte per element
    XCTAssertFalse( (OBJ_NIL == pObj), @"" );
    if (pObj) {
        
        i = pwr2Array_ElemSize(pObj);
        XCTAssertTrue( (1 == i), @"" );
        
        eRc = pwr2Array_InsertData(pObj, 1, 3, "abc");
        XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
        
        i = pwr2Array_getSize(pObj);
        XCTAssertTrue( (3 == i), @"" );
        
        pStr = pwr2Array_Ptr(pObj,1);
        XCTAssertTrue( (0 == strcmp("abc", pStr)), @"" );
        
        obj_Release(pObj);
        pObj = OBJ_NIL;
    }

}



- (void)testInsert02
{
    PWR2ARRAY_DATA	*pObj = OBJ_NIL;
    ERESULT         eRc;
    char            *pStr;
    uint32_t        i;
    
    pObj = pwr2Array_Alloc(0);
    XCTAssertFalse( (OBJ_NIL == pObj), @"" );
    pObj = pwr2Array_Init( pObj, 0 );           // 1 byte per element
    XCTAssertFalse( (OBJ_NIL == pObj), @"" );
    if (pObj) {
        
        i = pwr2Array_ElemSize(pObj);
        XCTAssertTrue( (1 == i), @"" );
        
        eRc = pwr2Array_InsertData(pObj, 1, 3, "abc");
        XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
        
        eRc = pwr2Array_InsertData(pObj, 1, 3, "def");
        XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
        
        i = pwr2Array_getSize(pObj);
        XCTAssertTrue( (6 == i), @"" );
        
        pStr = pwr2Array_Ptr(pObj,1);
        XCTAssertTrue( (0 == strcmp("defabc", pStr)), @"" );
        
        obj_Release(pObj);
        pObj = OBJ_NIL;
    }
    
}



- (void)testInsert03
{
    PWR2ARRAY_DATA	*pObj = OBJ_NIL;
    ERESULT         eRc;
    char            *pStr;
    uint32_t        i;
    
    pObj = pwr2Array_Alloc(0);
    XCTAssertFalse( (OBJ_NIL == pObj), @"" );
    pObj = pwr2Array_Init( pObj, 0 );           // 1 byte per element
    XCTAssertFalse( (OBJ_NIL == pObj), @"" );
    if (pObj) {
        
        i = pwr2Array_ElemSize(pObj);
        XCTAssertTrue( (1 == i), @"" );
        
        eRc = pwr2Array_InsertData(pObj, 1, 3, "abc");
        XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
        
        i = pwr2Array_getSize(pObj);
        XCTAssertTrue( (3 == i), @"" );
        
        pStr = pwr2Array_Ptr(pObj,1);
        XCTAssertTrue( (0 == strcmp("abc", pStr)), @"" );
        
        eRc = pwr2Array_InsertData(pObj, 3, 3, "def");
        XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
        
        i = pwr2Array_getSize(pObj);
        XCTAssertTrue( (6 == i), @"" );
        
        pStr = pwr2Array_Ptr(pObj,1);
        XCTAssertTrue( (0 == strcmp("abdefc", pStr)), @"" );
        
        obj_Release(pObj);
        pObj = OBJ_NIL;
    }
    
}



- (void)testInsert04
{
    PWR2ARRAY_DATA	*pObj = OBJ_NIL;
    ERESULT         eRc;
    char            *pStr;
    uint32_t        i;
    
    pObj = pwr2Array_Alloc(0);
    XCTAssertFalse( (OBJ_NIL == pObj), @"" );
    pObj = pwr2Array_Init( pObj, 0 );           // 1 byte per element
    XCTAssertFalse( (OBJ_NIL == pObj), @"" );
    if (pObj) {
        
        i = pwr2Array_ElemSize(pObj);
        XCTAssertTrue( (1 == i), @"" );
        
        eRc = pwr2Array_InsertData(pObj, 1, 3, "abc");
        XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
        
        i = pwr2Array_getSize(pObj);
        XCTAssertTrue( (3 == i), @"" );
        
        pStr = pwr2Array_Ptr(pObj,1);
        XCTAssertTrue( (0 == strcmp("abc", pStr)), @"" );
        
        eRc = pwr2Array_InsertData(pObj, 4, 3, "def");
        XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
        
        i = pwr2Array_getSize(pObj);
        XCTAssertTrue( (6 == i), @"" );
        
        pStr = pwr2Array_Ptr(pObj,1);
        XCTAssertTrue( (0 == strcmp("abcdef", pStr)), @"" );
        
        obj_Release(pObj);
        pObj = OBJ_NIL;
    }
    
}



- (void)testGet01
{
    PWR2ARRAY_DATA	*pObj = OBJ_NIL;
    ERESULT         eRc;
    char            *pStr;
    uint32_t        i;
    char            chr;
    char            chrs[7];
    
    pObj = pwr2Array_Alloc(0);
    XCTAssertFalse( (OBJ_NIL == pObj), @"" );
    pObj = pwr2Array_Init( pObj, 0 );           // 1 byte per element
    XCTAssertFalse( (OBJ_NIL == pObj), @"" );
    if (pObj) {
        
        i = pwr2Array_ElemSize(pObj);
        XCTAssertTrue( (1 == i), @"" );
        
        eRc = pwr2Array_InsertData(pObj, 1, 6, "abcdef");
        XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
        
        i = pwr2Array_getSize(pObj);
        XCTAssertTrue( (6 == i), @"" );
        
        pStr = pwr2Array_Ptr(pObj,1);
        XCTAssertTrue( (0 == strcmp("abcdef", pStr)), @"" );
        
        eRc = pwr2Array_Get(pObj, 1, 1, &chr);
        XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
        XCTAssertTrue( (chr == 'a'), @"" );
        
        eRc = pwr2Array_Get(pObj, 3, 1, &chr);
        XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
        XCTAssertTrue( (chr == 'c'), @"" );
        
        eRc = pwr2Array_Get(pObj, 6, 1, &chr);
        XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
        XCTAssertTrue( (chr == 'f'), @"" );
        
        eRc = pwr2Array_Get(pObj, 7, 1, &chr);
        XCTAssertFalse( (ERESULT_IS_SUCCESSFUL(eRc)) );
        
        eRc = pwr2Array_Get(pObj, 6, 2, &chr);
        XCTAssertFalse( (ERESULT_IS_SUCCESSFUL(eRc)) );
        
        for (i=0; i<7; ++i) {
            chrs[i] = '\0';
        }
        
        eRc = pwr2Array_Get(pObj, 5, 2, &chrs);
        XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
        XCTAssertTrue( (0 == strcmp("ef", chrs)), @"" );
        
        obj_Release(pObj);
        pObj = OBJ_NIL;
    }
    
}



- (void)testDelete01
{
    PWR2ARRAY_DATA	*pObj = OBJ_NIL;
    ERESULT         eRc;
    char            *pStr;
    uint32_t        i;
    
    pObj = pwr2Array_Alloc(0);
    XCTAssertFalse( (OBJ_NIL == pObj), @"" );
    pObj = pwr2Array_Init( pObj, 0 );           // 1 byte per element
    XCTAssertFalse( (OBJ_NIL == pObj), @"" );
    if (pObj) {
        
        i = pwr2Array_ElemSize(pObj);
        XCTAssertTrue( (1 == i), @"" );
        
        eRc = pwr2Array_InsertData(pObj, 1, 6, "abcdef");
        XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
        
        i = pwr2Array_getSize(pObj);
        XCTAssertTrue( (6 == i), @"" );
        
        pStr = pwr2Array_Ptr(pObj,1);
        XCTAssertTrue( (0 == strncmp("abcdef", pStr, 6)), @"" );
        
        eRc = pwr2Array_Delete(pObj, 1, 1);
        XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
        
        i = pwr2Array_getSize(pObj);
        XCTAssertTrue( (5 == i), @"" );
        
        pStr = pwr2Array_Ptr(pObj,1);
        XCTAssertTrue( (0 == strncmp("bcdef", pStr, 5)), @"" );

        eRc = pwr2Array_Delete(pObj, 4, 2);
        XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
        
        i = pwr2Array_getSize(pObj);
        XCTAssertTrue( (3 == i), @"" );
        
        pStr = pwr2Array_Ptr(pObj,1);
        XCTAssertTrue( (0 == strncmp("bcd", pStr, 3)), @"" );
        
        eRc = pwr2Array_Delete(pObj, 3, 2);
        XCTAssertFalse( (ERESULT_IS_SUCCESSFUL(eRc)) );
        
        obj_Release(pObj);
        pObj = OBJ_NIL;
    }
    
}



- (void)testCopyAssign01
{
    PWR2ARRAY_DATA	*pObj = OBJ_NIL;
    PWR2ARRAY_DATA	*pOther = OBJ_NIL;
    ERESULT         eRc;
    char            *pStr;
    uint32_t        i;
    
    pObj = pwr2Array_Alloc(0);
    XCTAssertFalse( (OBJ_NIL == pObj), @"" );
    pObj = pwr2Array_Init( pObj, 0 );           // 1 byte per element
    XCTAssertFalse( (OBJ_NIL == pObj), @"" );
    if (pObj) {
        
        i = pwr2Array_ElemSize(pObj);
        XCTAssertTrue( (1 == i), @"" );
        
        eRc = pwr2Array_InsertData(pObj, 1, 6, "abcdef");
        XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
        
        i = pwr2Array_getSize(pObj);
        XCTAssertTrue( (6 == i), @"" );
        
        pStr = pwr2Array_Ptr(pObj,1);
        XCTAssertTrue( (0 == strncmp("abcdef", pStr, 6)), @"" );
        
        pOther = pwr2Array_Copy(pObj);
        XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
        
        i = pwr2Array_getSize(pObj);
        XCTAssertTrue( (6 == i), @"" );
        
        pStr = pwr2Array_Ptr(pObj,1);
        XCTAssertTrue( (0 == strncmp("abcdef", pStr, 6)), @"" );
        
        eRc = pwr2Array_InsertData(pOther, 7, 3, "ghi");
        XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
        
        i = pwr2Array_getSize(pOther);
        XCTAssertTrue( (9 == i), @"" );
        
        pStr = pwr2Array_Ptr(pOther,1);
        XCTAssertTrue( (0 == strncmp("abcdefghi", pStr, 9)), @"" );
        
        eRc = pwr2Array_Assign(pOther, pObj);
        XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
        
        i = pwr2Array_getSize(pObj);
        XCTAssertTrue( (9 == i), @"" );
        
        pStr = pwr2Array_Ptr(pObj,1);
        XCTAssertTrue( (0 == strncmp("abcdefghi", pStr, 9)), @"" );
        
        obj_Release(pOther);
        pOther = OBJ_NIL;
        obj_Release(pObj);
        pObj = OBJ_NIL;
    }
    
}



@end



