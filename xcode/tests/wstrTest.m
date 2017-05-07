/*
 *	Generated 06/08/2015 18:39:43
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


#include    "WStr_internal.h"
#include    "utf8.h"
#include    <wchar.h>



// Faked UTF-8 of 0x01..0x04 in 1..4 bytes
#ifdef XYZZY
static
const
char            *pString1 = "\x01\xC0\x82\xE0\x80\x83\xF8\x80\x80\x84\x00";
#endif

// WStr of "xyz"
static
const
int32_t         string2[4] = { 'x', 'y', 'z', 0 };


static
const
int32_t         whiteSpace[11] = {
    ' ',
    '\f',
    '\n',
    '\r',
    '\t',
    0x00A0,     // no-break space
    0x200B,     // zero width space
    0x2060,     // word joiner
    0x3000,     // ideographic space
    0xFEFF,     // zero width no-break space
    0
};



#ifdef XYZZY
static
const
char        whiteSpaceA[20] = {
    ' ','\f','\n','\r','\t',
    0xC2,0xA0,          // no-break space
    0xE2,0x80,0x8B,     // zero width space
    0xE2,0x81,0xA0,     // word joiner
    0xE3,0x80,0x80,     // ideographic space
    0xEF,0xBB,0xBF,     // zero width no-break space
    0
};
#endif







@interface WStrTests : XCTestCase

@end

@implementation WStrTests


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
    WSTR_DATA	*pObj = OBJ_NIL;
    ERESULT     eRc;
    const
    int32_t     *pData;
    int32_t     chr;
   
    pObj = WStr_Alloc( );
    XCTAssertFalse( (OBJ_NIL == pObj) );
    pObj = WStr_Init( pObj );
    XCTAssertFalse( (OBJ_NIL == pObj) );
    if (pObj) {
        
        pData = WStr_getData(pObj);
        XCTAssertTrue( (pData), @"" );
        XCTAssertTrue( (pData[0] == 0), @"" );
        
        eRc = WStr_AppendA( pObj, "abc" );
        XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
        XCTAssertTrue( (3 == WStr_getLength(pObj)), @"" );
        
        chr = WStr_CharGetW(pObj, 2);
        XCTAssertTrue( ('b' == chr), @"" );
        
        eRc = WStr_CharPutW(pObj, 2, 'x');
        XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
        
        eRc = WStr_CompareA( pObj, "axc" );
        XCTAssertTrue( (ERESULT_SUCCESSFUL_COMPLETION == eRc), @"" );
        
        eRc = WStr_IsOnlyASCII(pObj);
        XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
        
        eRc = WStr_CharPutW(pObj, 2, 0xFEFF);
        XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
        
        eRc = WStr_IsOnlyASCII(pObj);
        XCTAssertFalse( (ERESULT_IS_SUCCESSFUL(eRc)) );
        
       obj_Release(pObj);
        pObj = OBJ_NIL;
    }

}



- (void)testSpan
{
    WSTR_DATA	*pObj = OBJ_NIL;
    ERESULT     eRc;
    uint32_t    index = 0;
    int32_t     scanStr[4] = {'x','y','z',0};
    
    pObj = WStr_Alloc( );
    XCTAssertFalse( (OBJ_NIL == pObj), @"" );
    pObj = WStr_Init( pObj );
    XCTAssertFalse( (OBJ_NIL == pObj), @"" );
    if (pObj) {
        
        eRc = WStr_AppendA( pObj, "xABCyDEFzGHI" );
        XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
        XCTAssertTrue( (12 == WStr_getLength(pObj)), @"" );
        
        eRc = WStr_CompareA( pObj, "xABCyDEFzGHI" );
        XCTAssertTrue( (ERESULT_SUCCESSFUL_COMPLETION == eRc), @"" );
        
        eRc = WStr_IndexUntil(pObj, scanStr, &index);
        XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
        XCTAssertTrue( (1 == index), @"" );
        
        ++index;
        eRc = WStr_IndexUntil(pObj, scanStr, &index);
        XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
        XCTAssertTrue( (5 == index), @"" );
        
        ++index;
        eRc = WStr_IndexUntil(pObj, scanStr, &index);
        XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
        XCTAssertTrue( (9 == index), @"" );
        
        ++index;
        eRc = WStr_IndexUntil(pObj, scanStr, &index);
        XCTAssertTrue( (ERESULT_OUT_OF_RANGE == eRc), @"" );
        XCTAssertTrue( (0 == index), @"" );
        
        obj_Release(pObj);
        pObj = OBJ_NIL;
    }
    
}



- (void)testAssignCopy
{
    WSTR_DATA	*pObj = OBJ_NIL;
    WSTR_DATA	*pOther = OBJ_NIL;
    ERESULT     eRc;
    const
    int32_t     *pData1;
    const
    int32_t     *pData2;
    
    pObj = WStr_Alloc( );
    XCTAssertFalse( (OBJ_NIL == pObj), @"" );
    pObj = WStr_Init( pObj );
    XCTAssertFalse( (OBJ_NIL == pObj), @"" );
    if (pObj) {
        
        eRc = WStr_AppendA( pObj, "abcdefghi" );
        XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
        XCTAssertTrue( (9 == WStr_getLength(pObj)), @"" );
        
        pOther = WStr_Copy(pObj);
        XCTAssertFalse( (OBJ_NIL == pObj), @"" );
        
        eRc = WStr_CompareA( pObj, "abcdefghi" );
        XCTAssertTrue( (ERESULT_SUCCESSFUL_COMPLETION == eRc), @"" );
        
        eRc = WStr_Compare( pOther, pObj );
        XCTAssertTrue( (ERESULT_SUCCESSFUL_COMPLETION == eRc), @"" );
        
        eRc = WStr_IsOnlyASCII(pObj);
        XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
        
        pData1 = WStr_getData(pObj);
        pData2 = WStr_getData(pOther);
        XCTAssertTrue( (!(pData1 == pData2)), @"" );
        
        obj_Release(pOther);
        pOther = OBJ_NIL;
        
        obj_Release(pObj);
        pObj = OBJ_NIL;
    }
    
}



- (void)testCompareA
{
    WSTR_DATA	*pObj = OBJ_NIL;
    ERESULT     eRc;
    const
    int32_t     *pData;
    
    pObj = WStr_Alloc( );
    XCTAssertFalse( (OBJ_NIL == pObj), @"" );
    pObj = WStr_Init( pObj );
    XCTAssertFalse( (OBJ_NIL == pObj), @"" );
    if (pObj) {
        
        pData = WStr_getData(pObj);
        XCTAssertTrue( (pData), @"" );
        XCTAssertTrue( (pData[0] == 0), @"" );
        
        eRc = WStr_AppendA( pObj, "abc" );
        XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
        XCTAssertTrue( (3 == WStr_getLength(pObj)), @"" );
        
        pData = WStr_getData(pObj);
        XCTAssertTrue( (pData), @"" );
        XCTAssertTrue( (pData[0] == 'a'), @"" );
        XCTAssertTrue( (pData[1] == 'b'), @"" );
        XCTAssertTrue( (pData[2] == 'c'), @"" );
        XCTAssertTrue( (pData[3] == 0), @"" );
        
        eRc = WStr_CompareA( pObj, "abc" );
        XCTAssertTrue( (ERESULT_SUCCESSFUL_COMPLETION == eRc), @"" );
        
        eRc = WStr_CompareA( pObj, "000" );
        XCTAssertTrue( (ERESULT_SUCCESS_GREATER_THAN == eRc), @"" );
        
        eRc = WStr_CompareA( pObj, "def" );
        XCTAssertTrue( (ERESULT_SUCCESS_LESS_THAN == eRc), @"" );
        
        eRc = WStr_CompareA( pObj, "\xC0\x82" );
        XCTAssertTrue( (ERESULT_SUCCESS_GREATER_THAN == eRc), @"" );
        
        eRc = WStr_AppendW( pObj, 0, string2 );
        XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
        XCTAssertTrue( (6 == WStr_getLength(pObj)), @"" );
        
        eRc = WStr_CompareA( pObj, "abcxyz" );
        XCTAssertTrue( (ERESULT_SUCCESSFUL_COMPLETION == eRc), @"" );
        
        eRc = WStr_Truncate(pObj, 0);
        XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
        XCTAssertTrue( (0 == WStr_getLength(pObj)), @"" );
        
        eRc = WStr_AppendA( pObj, "xABCxDEFxG" );
        XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
        XCTAssertTrue( (10 == WStr_getLength(pObj)), @"" );
        
        eRc = WStr_CompareA( pObj, "xABCxDEFxG" );
        XCTAssertTrue( (ERESULT_SUCCESSFUL_COMPLETION == eRc), @"" );
        
        obj_Release(pObj);
        pObj = OBJ_NIL;
    }
    
}



- (void)testCompareW
{
    WSTR_DATA	*pObj = OBJ_NIL;
    ERESULT     eRc;
    const
    int32_t     *pData;
    char        *pStr = NULL;
    uint32_t    lenStr;
    uint32_t    len;
    
    pObj = WStr_Alloc( );
    XCTAssertFalse( (OBJ_NIL == pObj) );
    pObj = WStr_Init( pObj );
    XCTAssertFalse( (OBJ_NIL == pObj) );
    if (pObj) {
        
        pData = WStr_getData(pObj);
        XCTAssertTrue( (pData) );
        XCTAssertTrue( (pData[0] == 0) );
        
        eRc = WStr_AppendW( pObj, 10, whiteSpace );
        XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
        XCTAssertTrue( (10 == WStr_getLength(pObj)) );
        
        pData = WStr_getData(pObj);
        XCTAssertTrue( (pData) );
        XCTAssertTrue( (pData[0] == ' ') );
        XCTAssertTrue( (pData[1] == '\f') );
        XCTAssertTrue( (pData[2] == '\n') );
        XCTAssertTrue( (pData[3] == '\r') );
        XCTAssertTrue( (pData[4] == '\t') );
        XCTAssertTrue( (pData[5] == 0xA0) );
        XCTAssertTrue( (pData[6] == 0x200B) );
        XCTAssertTrue( (pData[7] == 0x2060) );
        XCTAssertTrue( (pData[8] == 0x3000) );
        XCTAssertTrue( (pData[9] == 0xFEFF) );
        XCTAssertTrue( (pData[10] == 0) );
        
        eRc = WStr_CompareW( pObj, whiteSpace );
        XCTAssertTrue( (ERESULT_SUCCESS_EQUAL == eRc) );
        
        pStr = WStr_CStringA(pObj, &len);
        XCTAssertTrue( (ERESULT_SUCCESS == eRc) );
        XCTAssertTrue( (19 == len) );
        lenStr = utf8_StrLenA(pStr);
        XCTAssertTrue( (10 == lenStr) );
        XCTAssertTrue( (10 == WStr_getLength(pObj)) );

        obj_Release(pObj);
        pObj = OBJ_NIL;

        pObj = WStr_NewA(pStr);
        XCTAssertFalse( (OBJ_NIL == pObj) );
        XCTAssertTrue( (10 == WStr_getLength(pObj)) );

        eRc = WStr_CompareW( pObj, whiteSpace );
        XCTAssertTrue( (ERESULT_SUCCESSFUL_COMPLETION == eRc) );
        
        obj_Release(pObj);
        pObj = OBJ_NIL;
        
        mem_Free(pStr);
        pStr = NULL;

        pObj = WStr_NewW(0, whiteSpace);
        XCTAssertFalse( (OBJ_NIL == pObj) );
        XCTAssertTrue( (10 == WStr_getLength(pObj)) );
        
        eRc = WStr_CompareW( pObj, whiteSpace );
        XCTAssertTrue( (ERESULT_SUCCESSFUL_COMPLETION == eRc) );
        
        eRc = WStr_Compare( pObj, pObj );
        XCTAssertTrue( (ERESULT_SUCCESSFUL_COMPLETION == eRc) );
        
        obj_Release(pObj);
        pObj = OBJ_NIL;
        
    }
    
}



- (void)testAppendChr
{
    WSTR_DATA	*pObj = OBJ_NIL;
    WSTR_DATA	*pOther = OBJ_NIL;
    ERESULT     eRc;
    
    pObj = WStr_Alloc( );
    XCTAssertFalse( (OBJ_NIL == pObj), @"" );
    pObj = WStr_Init( pObj );
    XCTAssertFalse( (OBJ_NIL == pObj), @"" );
    if (pObj) {
        
        eRc = WStr_AppendCharW( pObj, 3, 'a' );
        XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
        XCTAssertTrue( (3 == WStr_getLength(pObj)), @"" );
        
        eRc = WStr_IsOnlyASCII(pObj);
        XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
        
        eRc = WStr_CompareA( pObj, "aaa" );
        XCTAssertTrue( (ERESULT_SUCCESSFUL_COMPLETION == eRc), @"" );
        
        eRc = WStr_Upper( pObj );
        XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
        XCTAssertTrue( (3 == WStr_getLength(pObj)), @"" );
        
        eRc = WStr_CompareA( pObj, "AAA" );
        XCTAssertTrue( (ERESULT_SUCCESSFUL_COMPLETION == eRc), @"" );
        
        eRc = WStr_Lower( pObj );
        XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
        XCTAssertTrue( (3 == WStr_getLength(pObj)), @"" );
        
        eRc = WStr_CompareA( pObj, "aaa" );
        XCTAssertTrue( (ERESULT_SUCCESSFUL_COMPLETION == eRc), @"" );
        
        eRc = WStr_InsertA( pObj, 2, "bb" );
        XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
        XCTAssertTrue( (5 == WStr_getLength(pObj)), @"" );
        
        eRc = WStr_CompareA( pObj, "abbaa" );
        XCTAssertTrue( (ERESULT_SUCCESSFUL_COMPLETION == eRc), @"" );
        
        eRc = WStr_InsertA( pObj, 1, "c" );
        XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
        XCTAssertTrue( (6 == WStr_getLength(pObj)), @"" );
        
        eRc = WStr_CompareA( pObj, "cabbaa" );
        XCTAssertTrue( (ERESULT_SUCCESSFUL_COMPLETION == eRc), @"" );
        
        eRc = WStr_InsertA( pObj, 7, "d" );
        XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
        XCTAssertTrue( (7 == WStr_getLength(pObj)), @"" );
        
        eRc = WStr_CompareA( pObj, "cabbaad" );
        XCTAssertTrue( (ERESULT_SUCCESSFUL_COMPLETION == eRc), @"" );
        
        eRc = WStr_AppendA( pObj, "eee" );
        XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
        XCTAssertTrue( (10 == WStr_getLength(pObj)), @"" );
        
        eRc = WStr_CompareA( pObj, "cabbaadeee" );
        XCTAssertTrue( (ERESULT_SUCCESSFUL_COMPLETION == eRc), @"" );
        
        eRc = WStr_IsOnlyASCII(pObj);
        XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
       
        eRc = WStr_Mid(pObj, 1, 2, &pOther);
        XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
        XCTAssertTrue( (2 == WStr_getLength(pOther)), @"" );
        eRc = WStr_CompareA( pOther, "ca" );
        XCTAssertTrue( (ERESULT_SUCCESSFUL_COMPLETION == eRc), @"" );
        obj_Release(pOther);
        pOther = OBJ_NIL;
        
        eRc = WStr_Mid(pObj, 8, 3, &pOther);
        XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
        XCTAssertTrue( (3 == WStr_getLength(pOther)), @"" );
        eRc = WStr_CompareA( pOther, "eee" );
        XCTAssertTrue( (ERESULT_SUCCESSFUL_COMPLETION == eRc), @"" );
        obj_Release(pOther);
        pOther = OBJ_NIL;
        
        eRc = WStr_Left(pObj, 2, &pOther);
        XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
        XCTAssertTrue( (2 == WStr_getLength(pOther)), @"" );
        eRc = WStr_CompareA( pOther, "ca" );
        XCTAssertTrue( (ERESULT_SUCCESSFUL_COMPLETION == eRc), @"" );
        obj_Release(pOther);
        pOther = OBJ_NIL;
        
        eRc = WStr_Right(pObj, 3, &pOther);
        XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
        XCTAssertTrue( (3 == WStr_getLength(pOther)), @"" );
        eRc = WStr_CompareA( pOther, "eee" );
        XCTAssertTrue( (ERESULT_SUCCESSFUL_COMPLETION == eRc), @"" );
        obj_Release(pOther);
        pOther = OBJ_NIL;
        
        eRc = WStr_Remove(pObj, 1, 1);
        XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
        XCTAssertTrue( (9 == WStr_getLength(pObj)), @"" );
        eRc = WStr_CompareA( pObj, "abbaadeee" );
        XCTAssertTrue( (ERESULT_SUCCESSFUL_COMPLETION == eRc), @"" );
        
        eRc = WStr_Remove(pObj, 7, 3);
        XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
        XCTAssertTrue( (6 == WStr_getLength(pObj)), @"" );
        eRc = WStr_CompareA( pObj, "abbaad" );
        XCTAssertTrue( (ERESULT_SUCCESSFUL_COMPLETION == eRc), @"" );
        
        eRc = WStr_Remove(pObj, 4, 2);
        XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
        XCTAssertTrue( (4 == WStr_getLength(pObj)), @"" );
        eRc = WStr_CompareA( pObj, "abbd" );
        XCTAssertTrue( (ERESULT_SUCCESSFUL_COMPLETION == eRc), @"" );
        
        obj_Release(pObj);
        pObj = OBJ_NIL;
    }
    
}



- (void)testAppend
{
    WSTR_DATA	*pObj = OBJ_NIL;
    WSTR_DATA	*pObj2 = OBJ_NIL;
    WSTR_DATA	*pObj3 = OBJ_NIL;
    ERESULT     eRc;
    
    pObj = WStr_Alloc( );
    XCTAssertFalse( (OBJ_NIL == pObj), @"" );
    pObj = WStr_Init( pObj );
    XCTAssertFalse( (OBJ_NIL == pObj), @"" );
    if (pObj) {
        
        pObj2 = WStr_NewA("abc");
        XCTAssertFalse( (OBJ_NIL == pObj2), @"" );
        pObj3 = WStr_NewA("def");
        XCTAssertFalse( (OBJ_NIL == pObj3), @"" );
        
        eRc = WStr_Append( pObj, pObj2 );
        XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
        XCTAssertTrue( (3 == WStr_getLength(pObj)), @"" );
        XCTAssertTrue( (0 == wcscmp(L"abc",WStr_getData(pObj))), @"" );
        
        eRc = WStr_Append( pObj, pObj3 );
        XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
        XCTAssertTrue( (6 == WStr_getLength(pObj)), @"" );
        XCTAssertTrue( (0 == wcscmp(L"abcdef",WStr_getData(pObj))), @"" );
        
        obj_Release(pObj3);
        pObj3 = OBJ_NIL;
        
        obj_Release(pObj2);
        pObj2 = OBJ_NIL;
        
        obj_Release(pObj);
        pObj = OBJ_NIL;
        
    }
    
}



- (void)testCharFindNext
{
    WSTR_DATA	*pObj = OBJ_NIL;
    ERESULT     eRc;
    uint32_t    index;
    
    pObj = WStr_Alloc( );
    XCTAssertFalse( (OBJ_NIL == pObj), @"" );
    pObj = WStr_Init( pObj );
    XCTAssertFalse( (OBJ_NIL == pObj), @"" );
    if (pObj) {

        eRc = WStr_AppendA( pObj, "xABCxDEFxG" );
        XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
        
        index = 0;      // Start at the beginning.
        eRc = WStr_CharFindNextW(pObj, &index, 'x');
        XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
        XCTAssertTrue( (1 == index), @"" );
        
        ++index;
        eRc = WStr_CharFindNextW(pObj, &index, 'x');
        XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
        XCTAssertTrue( (5 == index), @"" );
        
        ++index;
        eRc = WStr_CharFindNextW(pObj, &index, 'x');
        XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
        XCTAssertTrue( (9 == index), @"" );
        
        ++index;
        eRc = WStr_CharFindNextW(pObj, &index, 'x');
        XCTAssertFalse( (ERESULT_IS_SUCCESSFUL(eRc)) );
        XCTAssertTrue( (0 == index), @"" );
        
        obj_Release(pObj);
        pObj = OBJ_NIL;
    }
    
}



- (void)testCharFindPrev
{
    WSTR_DATA	*pObj = OBJ_NIL;
    ERESULT     eRc;
    uint32_t    index;
    
    pObj = WStr_Alloc( );
    XCTAssertFalse( (OBJ_NIL == pObj), @"" );
    pObj = WStr_Init( pObj );
    XCTAssertFalse( (OBJ_NIL == pObj), @"" );
    if (pObj) {
        
        eRc = WStr_AppendA( pObj, "xABCxDEFxG" );
        XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
        
        index = 0;      // Start at the beginning.
        eRc = WStr_CharFindPrevW(pObj, &index, 'x');
        XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
        XCTAssertTrue( (9 == index), @"" );
        
        --index;
        eRc = WStr_CharFindPrevW(pObj, &index, 'x');
        XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
        XCTAssertTrue( (5 == index), @"" );
        
        --index;
        eRc = WStr_CharFindPrevW(pObj, &index, 'x');
        XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
        XCTAssertTrue( (1 == index), @"" );
        
        obj_Release(pObj);
        pObj = OBJ_NIL;
    }
    
}



- (void)testCompare
{
    WSTR_DATA	*pObj = OBJ_NIL;
    ERESULT     eRc;
    
    pObj = WStr_Alloc( );
    XCTAssertFalse( (OBJ_NIL == pObj), @"" );
    pObj = WStr_Init( pObj );
    XCTAssertFalse( (OBJ_NIL == pObj), @"" );
    if (pObj) {
        
        eRc = WStr_AppendA( pObj, "xABCxDEFxG" );
        XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
        
        eRc = WStr_CompareA(pObj, "xABCxDEFxG");
        XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
        
        eRc = WStr_CompareA(pObj, "xABCxDEFxA");
        XCTAssertTrue( (eRc == ERESULT_SUCCESS_GREATER_THAN), @"" );

        eRc = WStr_CompareA(pObj, "xABCxDEFxZ");
        XCTAssertTrue( (eRc == ERESULT_SUCCESS_LESS_THAN), @"" );
        
        eRc = WStr_CompareA(pObj, "xABCxDEF");
        XCTAssertTrue( (eRc == ERESULT_SUCCESS_GREATER_THAN), @"" );
        
        eRc = WStr_CompareA(pObj, "xABCxDEFxGx");
        XCTAssertTrue( (eRc == ERESULT_SUCCESS_LESS_THAN), @"" );
        
        obj_Release(pObj);
        pObj = OBJ_NIL;
    }
    
}



- (void)testLeftRightMid
{
    WSTR_DATA	*pObj = OBJ_NIL;
    ERESULT     eRc;
    WSTR_DATA	*pOther = OBJ_NIL;
    
    pObj = WStr_Alloc( );
    XCTAssertFalse( (OBJ_NIL == pObj), @"" );
    pObj = WStr_Init( pObj );
    XCTAssertFalse( (OBJ_NIL == pObj), @"" );
    if (pObj) {
        
        eRc = WStr_AppendA( pObj, "xABCxDEFxG" );
        XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
        
        eRc = WStr_Left(pObj, 4, &pOther);
        XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
        XCTAssertTrue( (4 == WStr_getLength(pOther)), @"" );
        eRc = WStr_CompareA( pOther, "xABC" );
        XCTAssertTrue( (ERESULT_SUCCESSFUL_COMPLETION == eRc), @"" );
        obj_Release(pOther);
        pOther = OBJ_NIL;
        
        eRc = WStr_Right(pObj, 2, &pOther);
        XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
        XCTAssertTrue( (2 == WStr_getLength(pOther)), @"" );
        eRc = WStr_CompareA( pOther, "xG" );
        XCTAssertTrue( (ERESULT_SUCCESSFUL_COMPLETION == eRc), @"" );
        obj_Release(pOther);
        pOther = OBJ_NIL;
        
        obj_Release(pObj);
        pObj = OBJ_NIL;
    }
    
}



- (void)testNewFromEnv
{
    WSTR_DATA	*pObj = OBJ_NIL;
    ERESULT     eRc;
    
    pObj = WStr_NewFromEnv("HOME");
    XCTAssertFalse( (OBJ_NIL == pObj), @"" );
    if (pObj) {
        
        eRc = WStr_CompareA(pObj, "/Users/bob");
        XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
        
        obj_Release(pObj);
        pObj = OBJ_NIL;
    }
    
}



- (void)testFile
{
    WSTR_DATA	*pObj = OBJ_NIL;
    ERESULT     eRc;
    PATH_DATA   *pPath = OBJ_NIL;
    WSTR_DATA	*pOther = OBJ_NIL;
    
    pObj = WStr_NewFromEnv("HOME");
    XCTAssertFalse( (OBJ_NIL == pObj) );
    if (pObj) {
        
        eRc = WStr_CompareA(pObj, "/Users/bob");
        XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
        eRc = WStr_AppendA(pObj, "/test.txt");
        
        pPath = path_NewFromWStr(pObj);
        XCTAssertFalse( (OBJ_NIL == pPath) );
        if (pPath) {
            eRc = WStr_ToUtf8File(pObj, pPath);
            XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
            pOther = WStr_NewFromUtf8File(pPath);
            XCTAssertFalse( (OBJ_NIL == pOther) );
            if (pOther) {
                eRc = WStr_Compare(pObj, pOther);
                XCTAssertTrue( (ERESULT_SUCCESS_EQUAL == eRc) );
                obj_Release(pOther);
                pOther = OBJ_NIL;
            }
            obj_Release(pPath);
            pPath = OBJ_NIL;
        }
        
        obj_Release(pObj);
        pObj = OBJ_NIL;
    }
    
}



- (void)testTrim
{
    WSTR_DATA	*pObj = OBJ_NIL;
    ERESULT     eRc;
    
    pObj = WStr_Alloc( );
    XCTAssertFalse( (OBJ_NIL == pObj), @"" );
    pObj = WStr_Init( pObj );
    XCTAssertFalse( (OBJ_NIL == pObj), @"" );
    if (pObj) {
        
        // Leading Spaces
        eRc = WStr_AppendA( pObj, "   bb" );
        XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
        XCTAssertTrue( (5 == WStr_getLength(pObj)), @"" );
        
        eRc = WStr_Trim( pObj );
        XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
        XCTAssertTrue( (2 == WStr_getLength(pObj)), @"" );
        eRc = WStr_CompareA( pObj, "bb" );
        XCTAssertTrue( (ERESULT_SUCCESSFUL_COMPLETION == eRc), @"" );
        
        // Trailing spaces
        eRc = WStr_AppendA( pObj, "   " );
        XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
        XCTAssertTrue( (5 == WStr_getLength(pObj)), @"" );
        
        eRc = WStr_Trim( pObj );
        XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
        XCTAssertTrue( (2 == WStr_getLength(pObj)), @"" );
        eRc = WStr_CompareA( pObj, "bb" );
        XCTAssertTrue( (ERESULT_SUCCESSFUL_COMPLETION == eRc), @"" );
        
        eRc = WStr_Truncate( pObj, 0 );
        XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
        XCTAssertTrue( (0 == WStr_getLength(pObj)), @"" );

        // Leading and Trailing spaces
        eRc = WStr_AppendA( pObj, "   bb   " );
        XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
        XCTAssertTrue( (8 == WStr_getLength(pObj)), @"" );
        
        eRc = WStr_Trim( pObj );
        XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
        XCTAssertTrue( (2 == WStr_getLength(pObj)), @"" );
        eRc = WStr_CompareA( pObj, "bb" );
        XCTAssertTrue( (ERESULT_SUCCESSFUL_COMPLETION == eRc), @"" );
        
        obj_Release(pObj);
        pObj = OBJ_NIL;
    }
    
}



- (void)testEscapeForC
{
    WSTR_DATA	*pObj = OBJ_NIL;
    ERESULT     eRc;
    uint32_t    i;
    
    pObj = WStr_NewA("\\");
    XCTAssertFalse( (OBJ_NIL == pObj) );
    if (pObj) {
        
        i = WStr_getLength( pObj );
        XCTAssertTrue( (i == 1) );
        eRc = WStr_EscapeForC(pObj);
        XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
        i = WStr_getLength( pObj );
        XCTAssertTrue( (i == 2) );
        fprintf(stderr, "string=(%d)\"%ls\"\n",i,WStr_getData(pObj));
        eRc = WStr_CompareA(pObj, "\\\\");
        XCTAssertTrue( (eRc == ERESULT_SUCCESS_EQUAL), @"" );
        
        obj_Release(pObj);
        pObj = OBJ_NIL;
    }
    
    pObj = WStr_NewA("\"a\"");
    XCTAssertFalse( (OBJ_NIL == pObj) );
    if (pObj) {
        
        i = WStr_getLength( pObj );
        XCTAssertTrue( (i == 3) );
        eRc = WStr_EscapeForC(pObj);
        XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
        i = WStr_getLength( pObj );
        XCTAssertTrue( (i == 5) );
        fprintf(stderr, "string=(%d)\"%ls\"\n",i,WStr_getData(pObj));
        eRc = WStr_CompareA(pObj, "\\\"a\\\"");
        XCTAssertTrue( (eRc == ERESULT_SUCCESS_EQUAL), @"" );
        
        obj_Release(pObj);
        pObj = OBJ_NIL;
    }
    
    pObj = WStr_NewA("\t\t\n");
    XCTAssertFalse( (OBJ_NIL == pObj) );
    if (pObj) {
        
        i = WStr_getLength( pObj );
        XCTAssertTrue( (i == 3) );
        eRc = WStr_EscapeForC(pObj);
        XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
        i = WStr_getLength( pObj );
        XCTAssertTrue( (i == 6) );
        fprintf(stderr, "string=(%d)\"%ls\"\n",i,WStr_getData(pObj));
        eRc = WStr_CompareA(pObj, "\\t\\t\\n");
        XCTAssertTrue( (eRc == ERESULT_SUCCESS_EQUAL), @"" );
        
        obj_Release(pObj);
        pObj = OBJ_NIL;
    }
    
}



@end



