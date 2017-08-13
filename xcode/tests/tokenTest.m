/*
 *	Generated 05/26/2015 13:40:16
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


#include    "token_internal.h"
#include    "szTbl.h"



@interface tokenTests : XCTestCase

@end

@implementation tokenTests


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
    TOKEN_DATA	*pObj = OBJ_NIL;
   
    pObj = token_Alloc();
    XCTAssertFalse( (OBJ_NIL == pObj) );
    pObj = token_Init( pObj );
    XCTAssertFalse( (OBJ_NIL == pObj) );
    if (pObj) {
        obj_Release(pObj);
        pObj = OBJ_NIL;
    }

    szTbl_SharedReset();
}



- (void)testOpenClose01
{
    TOKEN_DATA	*pObj = OBJ_NIL;
    ASTR_DATA   *pStr;
    const
    char        *pJSON_Con = "{\"objectType\":\"token\","
                                "\"fileName\":\"abc\","
                                "\"lineNo\":52,"
                                "\"colNo\":22,"
                                "\"cls\":11,"
                                "\"type\":\"NUMBER\","
                                "\"data\":64}\n";
    ERESULT     eRc;
    TOKEN_DATA  *pToken;
    
    pObj = token_Alloc();
    XCTAssertFalse( (OBJ_NIL == pObj) );
    pObj = token_InitInteger(pObj, "abc", 52, 22, 11, 64);
    XCTAssertFalse( (OBJ_NIL == pObj) );
    if (pObj) {
        
        XCTAssertTrue( (0 == strcmp("abc", token_getFileName(pObj))) );
        XCTAssertTrue( (52 == token_getLineNo(pObj)) );
        XCTAssertTrue( (22 == token_getColNo(pObj)) );
        XCTAssertTrue( (11 == token_getClass(pObj)) );
        XCTAssertTrue( (64 == token_getInteger(pObj)) );
        
        pStr = token_ToJSON(pObj);
        XCTAssertFalse( (OBJ_NIL == pStr) );
        //fprintf(stderr, "%s\n", AStr_getData(pStr));
        eRc = AStr_CompareA(pStr, pJSON_Con);
        XCTAssertTrue( (ERESULT_SUCCESS_EQUAL == eRc) );
        
        pToken = token_NewFromJSONString(pStr);
        XCTAssertFalse( (OBJ_NIL == pToken) );
        XCTAssertTrue( (0 == strcmp("abc", token_getFileName(pToken))) );
        XCTAssertTrue( (52 == token_getLineNo(pToken)) );
        XCTAssertTrue( (22 == token_getColNo(pToken)) );
        XCTAssertTrue( (11 == token_getClass(pToken)) );
        XCTAssertTrue( (64 == token_getInteger(pToken)) );
        obj_Release(pStr);
        pStr = OBJ_NIL;

        pStr = token_ToJSON(pToken);
        XCTAssertFalse( (OBJ_NIL == pStr) );
        //fprintf(stderr, "%s\n", AStr_getData(pStr));
        eRc = AStr_CompareA(pStr, pJSON_Con);
        XCTAssertTrue( (ERESULT_SUCCESS_EQUAL == eRc) );
        
        obj_Release(pToken);
        pToken = OBJ_NIL;
        obj_Release(pStr);
        pStr = OBJ_NIL;
        obj_Release(pObj);
        pObj = OBJ_NIL;
    }
    
    szTbl_SharedReset();
}



- (void)testOpenClose02
{
    TOKEN_DATA	*pObj = OBJ_NIL;
    ASTR_DATA   *pStr;
    const
    char        *pJSON_Con = "{\"objectType\":\"token\","
    "\"fileName\":\"abc\","
    "\"lineNo\":52,"
    "\"colNo\":22,"
    "\"cls\":11,"
    "\"type\":\"CHAR\","
    "\"data\":90}\n";
    ERESULT     eRc;
    TOKEN_DATA  *pToken;
    
    pObj = token_Alloc();
    XCTAssertFalse( (OBJ_NIL == pObj), @"Could not alloc  TOKEN_DATA" );
    pObj = token_InitCharW(pObj, "abc", 52, 22, 11, 'Z');
    XCTAssertFalse( (OBJ_NIL == pObj), @"" );
    if (pObj) {
        
        XCTAssertTrue( (0 == strcmp("abc", token_getFileName(pObj))), @"" );
        XCTAssertTrue( (52 == token_getLineNo(pObj)), @"" );
        XCTAssertTrue( (22 == token_getColNo(pObj)), @"" );
        XCTAssertTrue( (11 == token_getClass(pObj)), @"" );
        XCTAssertTrue( ('Z' == token_getChrW(pObj)), @"" );
        
        pStr = token_ToJSON(pObj);
        XCTAssertFalse( (OBJ_NIL == pStr), @"" );
        fprintf(stderr, "%s\n", AStr_getData(pStr));
        eRc = AStr_CompareA(pStr, pJSON_Con);
        XCTAssertTrue( (ERESULT_SUCCESS_EQUAL == eRc), @"" );
        
        pToken = token_NewFromJSONString(pStr);
        XCTAssertFalse( (OBJ_NIL == pToken), @"" );
        XCTAssertTrue( (0 == strcmp("abc", token_getFileName(pToken))), @"" );
        XCTAssertTrue( (52 == token_getLineNo(pToken)), @"" );
        XCTAssertTrue( (22 == token_getColNo(pToken)), @"" );
        XCTAssertTrue( (11 == token_getClass(pToken)), @"" );
        XCTAssertTrue( ('Z' == token_getChrW(pObj)), @"" );
        obj_Release(pStr);
        pStr = OBJ_NIL;
        
        pStr = token_ToJSON(pToken);
        XCTAssertFalse( (OBJ_NIL == pStr), @"" );
        //fprintf(stderr, "%s\n", AStr_getData(pStr));
        eRc = AStr_CompareA(pStr, pJSON_Con);
        XCTAssertTrue( (ERESULT_SUCCESS_EQUAL == eRc), @"" );
        
        obj_Release(pToken);
        pToken = OBJ_NIL;
        obj_Release(pStr);
        pStr = OBJ_NIL;
        obj_Release(pObj);
        pObj = OBJ_NIL;
    }
    
    szTbl_SharedReset();
}



- (void)testOpenClose03
{
    TOKEN_DATA	*pObj = OBJ_NIL;
    ASTR_DATA   *pStr;
    const
    char        *pJSON_Con = "{\"objectType\":\"token\","
    "\"fileName\":\"abc\","
    "\"lineNo\":52,"
    "\"colNo\":22,"
    "\"cls\":11,"
    "\"type\":\"STRING\","
    "\"data\":\"12345\"}\n";
    ERESULT     eRc;
    TOKEN_DATA  *pToken;
    WSTR_DATA   *pStrW;
    
    pObj = token_Alloc();
    XCTAssertFalse( (OBJ_NIL == pObj) );
    pObj = token_InitStrW(pObj, "abc", 52, 22, 11, L"12345");
    XCTAssertFalse( (OBJ_NIL == pObj) );
    if (pObj) {
        
        XCTAssertTrue( (0 == strcmp("abc", token_getFileName(pObj))) );
        XCTAssertTrue( (52 == token_getLineNo(pObj)) );
        XCTAssertTrue( (22 == token_getColNo(pObj)) );
        XCTAssertTrue( (11 == token_getClass(pObj)) );
        pStrW = token_getStringW(pObj);
        XCTAssertFalse( (OBJ_NIL == pStrW) );
        XCTAssertTrue( (OBJ_IDENT_WSTR == obj_getType(pStrW)) );
        eRc = WStr_CompareW(pStrW,L"12345");
        XCTAssertTrue( (ERESULT_SUCCESS_EQUAL == eRc), @"" );
        
        pStr = token_ToJSON(pObj);
        XCTAssertFalse( (OBJ_NIL == pStr), @"" );
        fprintf(stderr, "%s\n", AStr_getData(pStr));
        eRc = AStr_CompareA(pStr, pJSON_Con);
        XCTAssertTrue( (ERESULT_SUCCESS_EQUAL == eRc), @"" );
        
        pToken = token_NewFromJSONString(pStr);
        XCTAssertFalse( (OBJ_NIL == pToken), @"" );
        XCTAssertTrue( (0 == strcmp("abc", token_getFileName(pToken))), @"" );
        XCTAssertTrue( (52 == token_getLineNo(pToken)), @"" );
        XCTAssertTrue( (22 == token_getColNo(pToken)), @"" );
        XCTAssertTrue( (11 == token_getClass(pToken)), @"" );
        eRc = WStr_CompareW(token_getStringW(pObj),L"12345");
        XCTAssertTrue( (ERESULT_SUCCESS_EQUAL == eRc), @"" );
        obj_Release(pStr);
        pStr = OBJ_NIL;
        
        pStr = token_ToJSON(pToken);
        XCTAssertFalse( (OBJ_NIL == pStr), @"" );
        //fprintf(stderr, "%s\n", AStr_getData(pStr));
        eRc = AStr_CompareA(pStr, pJSON_Con);
        XCTAssertTrue( (ERESULT_SUCCESS_EQUAL == eRc), @"" );
        
        obj_Release(pToken);
        pToken = OBJ_NIL;
        obj_Release(pStr);
        pStr = OBJ_NIL;
        obj_Release(pObj);
        pObj = OBJ_NIL;
    }
    
    szTbl_SharedReset();
}



- (void)testOpenClose04
{
    TOKEN_DATA	*pObj = OBJ_NIL;
    ASTR_DATA   *pStr;
    const
    char        *pJSON_Con = "{\"objectType\":\"token\","
    "\"fileName\":\"abc\","
    "\"lineNo\":52,"
    "\"colNo\":22,"
    "\"cls\":11,"
    "\"type\":\"STRING\","
    "\"data\":\"12345\"}\n";
    ERESULT     eRc;
    TOKEN_DATA  *pToken;
    WSTR_DATA   *pStrW;
    
    pObj = token_Alloc();
    XCTAssertFalse( (OBJ_NIL == pObj) );
    pObj = token_InitStrA(pObj, "abc", 52, 22, 11, "12345");
    XCTAssertFalse( (OBJ_NIL == pObj) );
    if (pObj) {
        
        XCTAssertTrue( (0 == strcmp("abc", token_getFileName(pObj))) );
        XCTAssertTrue( (52 == token_getLineNo(pObj)) );
        XCTAssertTrue( (22 == token_getColNo(pObj)) );
        XCTAssertTrue( (11 == token_getClass(pObj)) );
        pStrW = token_getStringW(pObj);
        XCTAssertFalse( (OBJ_NIL == pStrW) );
        XCTAssertTrue( (OBJ_IDENT_WSTR == obj_getType(pStrW)) );
        eRc = WStr_CompareW(pStrW,L"12345");
        XCTAssertTrue( (ERESULT_SUCCESS_EQUAL == eRc) );
        
        pStr = token_ToJSON(pObj);
        XCTAssertFalse( (OBJ_NIL == pStr) );
        fprintf(stderr, "%s\n", AStr_getData(pStr));
        eRc = AStr_CompareA(pStr, pJSON_Con);
        XCTAssertTrue( (ERESULT_SUCCESS_EQUAL == eRc) );
        
        pToken = token_NewFromJSONString(pStr);
        XCTAssertFalse( (OBJ_NIL == pToken) );
        XCTAssertTrue( (0 == strcmp("abc", token_getFileName(pToken))) );
        XCTAssertTrue( (52 == token_getLineNo(pToken)) );
        XCTAssertTrue( (22 == token_getColNo(pToken)) );
        XCTAssertTrue( (11 == token_getClass(pToken)) );
        eRc = WStr_CompareW(token_getStringW(pObj),L"12345");
        XCTAssertTrue( (ERESULT_SUCCESS_EQUAL == eRc) );
        obj_Release(pStr);
        pStr = OBJ_NIL;
        
        pStr = token_ToJSON(pToken);
        XCTAssertFalse( (OBJ_NIL == pStr) );
        //fprintf(stderr, "%s\n", AStr_getData(pStr));
        eRc = AStr_CompareA(pStr, pJSON_Con);
        XCTAssertTrue( (ERESULT_SUCCESS_EQUAL == eRc) );
        
        obj_Release(pToken);
        pToken = OBJ_NIL;
        obj_Release(pStr);
        pStr = OBJ_NIL;
        obj_Release(pObj);
        pObj = OBJ_NIL;
    }
    
    szTbl_SharedReset();
}



@end



