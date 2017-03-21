/*
 *	Generated 06/12/2015 10:58:21
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


#include    "szTbl_internal.h"

static
char        *strings[] = {
    "bob",
    "bobby",
    "iryana",
    "dashsa",
    "dasha",
    "name",
    "way",
    "bigger",
    "Now",
    "is",
    "the",
    "time",
    "for",
    "all",
    "good",
    "men",
    "to",
    "come",
    "aid",
    "of",
    "their",
    "country",
    "We",
    "need",
    "another",
    "item",
    "in",
    "here",
    "Are",
    "you",
    "alright",
    "with",
    "this",
    (char *)NULL
};





@interface szTblTests : XCTestCase

@end

@implementation szTblTests


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
    SZTBL_DATA	*pObj = OBJ_NIL;
   
    pObj = szTbl_Shared();
    XCTAssertFalse( (OBJ_NIL == pObj) );
    if (pObj) {
        obj_Release(pObj);
        pObj = OBJ_NIL;
    }

}



- (void)testAdd
{
    SZTBL_DATA	*pObj = OBJ_NIL;
    ERESULT     eRc;
    uint32_t    i = 0;
    uint32_t    token;
    uint32_t    tokenW;
    char        **ppStr;
    const
    char        *pStr;
    
    pObj = szTbl_Shared();
    XCTAssertFalse( (OBJ_NIL == pObj) );
    if (pObj) {
        
        ppStr = strings;
        while (*ppStr) {
            ++i;
            eRc = szTbl_StringToToken(pObj, *ppStr, &token);
            XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
            if (ERESULT_HAS_FAILED(eRc)) {
                fprintf( stderr, "error word = %s\n", *ppStr );
            }
            XCTAssertTrue( (token == i) );
            eRc = szTbl_TokenToString(pObj, token, &pStr);
            XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
            XCTAssertFalse( (NULL == pStr) );
            if (pStr) {
                XCTAssertTrue( (0 == strcmp(*ppStr,pStr)) );
            }
            ++ppStr;
        }
        
        eRc = szTbl_StringToToken(pObj, "item", &token);
        XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
        eRc = szTbl_StringWToToken(pObj, L"item", &tokenW);
        XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
        XCTAssertTrue( (token == tokenW) );
        
        eRc = szTbl_StringWToToken(pObj, L"item size", &tokenW);
        XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
        eRc = szTbl_StringToToken(pObj, "item size", &token);
        XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
        XCTAssertTrue( (token == tokenW) );
        
        obj_Release(pObj);
        pObj = OBJ_NIL;
    }
    
}



@end



