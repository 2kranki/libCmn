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
#include    "str.h"
#include    "str_internal.h"


#define NUM_STR     10

/* Other variables */
#ifdef XYZZY
static
char        *StrArray[NUM_STR] = {
	"String 1",
	"String 2",
	"String 3",
	"String 4",
	"String 5",
	"String 6",
	"String 7",
	"String 8",
	"String 9",
	"String 10"
};
#endif



@interface strTests : XCTestCase

@end

@implementation strTests


- (void)setUp
{
    [super setUp];
    // Put setup code here. This method is called before the invocation of each test method in the class.
    mem_Init();
}


- (void)tearDown
{
    mem_Dump();
    mem_Release( );

    // Put teardown code here. This method is called after the invocation of each test method in the class.
    [super tearDown];
}




- (void)testConcat
{
	char			test[10];
    bool            fRc;
    int             i;

	fRc = str_Copy( test, sizeof(test), "abc" );
    XCTAssertTrue( (fRc), @"Copy did not work!" );
	fRc = str_Concat( test, 10, "def" );
    XCTAssertTrue( (fRc), @"Concat did not work!" );
    i = str_Compare(test, "abcdef");
    XCTAssertTrue( (0 == i), @"Compare did not work!" );

}



- (void)testDupA
{
    int             iRc;
    const
    char            *pStr1;
    const
    char            *pStr2;
    const
    char            *pCon1 = "a";
    
    pStr1 = str_DupA(pCon1);
    XCTAssertFalse( (NULL == pStr1), @"" );
    iRc = str_Compare(pCon1, pStr1);
    XCTAssertTrue( (iRc == 0), @"" );
    pStr2 = str_DupA(pCon1);
    XCTAssertFalse( (NULL == pStr2), @"" );
    iRc = str_Compare(pCon1, pStr2);
    XCTAssertTrue( (iRc == 0), @"" );
    fprintf(stderr, "str1=%s\n",pStr1);
    iRc = str_Compare(pStr1, pStr2);
    XCTAssertTrue( (iRc == 0), @"" );
    mem_Free((void *)pStr2);
    mem_Free((void *)pStr1);
    
}



- (void)testDupLeft
{
    char            *pszStr;
    
	pszStr = str_DupLeft(NULL, 3);
    XCTAssertTrue( (NULL == pszStr), @"" );
	pszStr = str_DupLeft("abcdef", 0);
    XCTAssertTrue( (NULL == pszStr), @"" );
	pszStr = str_DupLeft("abcdef", 3);
    XCTAssertFalse( (NULL == pszStr), @"" );
    XCTAssertTrue( (0 == str_Compare("abc", pszStr)), @"" );
    mem_Free(pszStr);
    pszStr = NULL;
	pszStr = str_DupLeft("abc", 3);
    XCTAssertFalse( (NULL == pszStr), @"" );
    XCTAssertTrue( (0 == str_Compare("abc", pszStr)), @"" );
    mem_Free(pszStr);
    pszStr = NULL;
	pszStr = str_DupLeft("ab", 3);
    XCTAssertFalse( (NULL == pszStr), @"" );
    XCTAssertTrue( (0 == str_Compare("ab", pszStr)), @"" );
    mem_Free(pszStr);
    pszStr = NULL;
}


- (void)testDupRight{
    char            *pszStr;
    
	pszStr = str_DupRight(NULL, 3);
    XCTAssertTrue( (NULL == pszStr), @"" );
	pszStr = str_DupRight("abcdef", 0);
    XCTAssertTrue( (NULL == pszStr), @"" );
	pszStr = str_DupRight("abcdef", 3);
    XCTAssertTrue( (0 == str_Compare("def", pszStr)), @"" );
    mem_Free(pszStr);
    pszStr = NULL;
	pszStr = str_DupRight("abc", 1);
    XCTAssertTrue( (0 == str_Compare("c", pszStr)), @"" );
    mem_Free(pszStr);
    pszStr = NULL;
	pszStr = str_DupRight("ab", 3);
    XCTAssertTrue( (0 == str_Compare("ab", pszStr)), @"" );
    mem_Free(pszStr);
    pszStr = NULL;
}


- (void)testLindex
{
    int             iRc;
    
    iRc = str_Lindex(NULL, '=');
    XCTAssertTrue( (iRc == -1), @"" );
    iRc = str_Lindex("abcdef", '=');
    XCTAssertTrue( (iRc == -1), @"" );
    iRc = str_Lindex("abc=def", '=');
    XCTAssertTrue( (iRc == 3), @"" );
    
}


@end



