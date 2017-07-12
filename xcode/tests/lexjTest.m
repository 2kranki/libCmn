/*
 *	Generated 07/02/2017 09:15:13
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


#include    <lexj_internal.h>
#include    <trace.h>
#include    <srcFile.h>



static
const
char        *pTestInput01 =
"// Test01 Input\n"
"{ /* test comment */\n\n\n"
    "\t\"one\": 123,\n"
    "\ttwo: \"xyz\",\n"
    "\tthree: [a, b, c] // Another comment\n"
    "\tfour: null,\n"
    "\t\"five\": true,\n"
    "\t\"six\": false\n"
"}\n";




@interface lexjTests : XCTestCase

@end

@implementation lexjTests


- (void)setUp
{
    [super setUp];
    
    mem_Init( );
    
    // Put setup code here. This method is called before the invocation of each
    // test method in the class.
}


- (void)tearDown
{
    // Put teardown code here. This method is called after the invocation of each
    // test method in the class.

    mem_Dump( );
    mem_Release( );

    [super tearDown];
}




- (void)testOpenClose
{
    LEXJ_DATA	*pObj = OBJ_NIL;
   
    pObj = lexj_Alloc(0);
    XCTAssertFalse( (OBJ_NIL == pObj) );
    pObj = lexj_Init( pObj );
    XCTAssertFalse( (OBJ_NIL == pObj) );
    if (pObj) {
        
        obj_Release(pObj);
        pObj = OBJ_NIL;
    }

}



// Revisit this since lex is a virtual object.
- (void)testInput01
{
    ASTR_DATA       *pBuf = OBJ_NIL;
    LEXJ_DATA       *pLexJ = OBJ_NIL;
    TOKEN_DATA      *pToken;
    ASTR_DATA       *pStr = OBJ_NIL;
    
    pBuf = AStr_NewA(pTestInput01);
    XCTAssertFalse( (OBJ_NIL == pBuf) );
    if (pBuf) {
        
        pLexJ = lexj_NewFromAStr(pBuf, 4, true);
        XCTAssertFalse( (OBJ_NIL == pLexJ) );
        obj_TraceSet(pLexJ, true);
        if (pLexJ) {
            
            pToken = lexj_TokenLookAhead(pLexJ, 1);
            XCTAssertFalse( (OBJ_NIL == pToken) );
            XCTAssertTrue( (LEXJ_SEP_LBRACE == token_getClass(pToken)) );
            pToken = lexj_TokenAdvance(pLexJ, 1);
            XCTAssertFalse( (OBJ_NIL == pToken) );
            
            pToken = lexj_TokenLookAhead(pLexJ, 1);
            XCTAssertFalse( (OBJ_NIL == pToken) );
            XCTAssertTrue( (LEXJ_CONSTANT_STRING == token_getClass(pToken)) );
            pStr = token_ToDataString(pToken);
            XCTAssertTrue( (0 == strcmp("one", AStr_getData(pStr))) );
            obj_Release(pStr);
            pStr = OBJ_NIL;
            pToken = lexj_TokenAdvance(pLexJ, 1);
            XCTAssertFalse( (OBJ_NIL == pToken) );
            
            pToken = lexj_TokenLookAhead(pLexJ, 1);
            XCTAssertFalse( (OBJ_NIL == pToken) );
            XCTAssertTrue( (LEXJ_SEP_COLON == token_getClass(pToken)) );
            pToken = lexj_TokenAdvance(pLexJ, 1);
            XCTAssertFalse( (OBJ_NIL == pToken) );
            
            pToken = lexj_TokenLookAhead(pLexJ, 1);
            XCTAssertFalse( (OBJ_NIL == pToken) );
            XCTAssertTrue( (LEXJ_CONSTANT_INTEGER == token_getClass(pToken)) );
            pToken = lexj_TokenAdvance(pLexJ, 1);
            XCTAssertFalse( (OBJ_NIL == pToken) );
            
            pToken = lexj_TokenLookAhead(pLexJ, 1);
            XCTAssertFalse( (OBJ_NIL == pToken) );
            XCTAssertTrue( (LEXJ_SEP_COMMA == token_getClass(pToken)) );
            pToken = lexj_TokenAdvance(pLexJ, 1);
            XCTAssertFalse( (OBJ_NIL == pToken) );
            
            pToken = lexj_TokenLookAhead(pLexJ, 1);
            XCTAssertFalse( (OBJ_NIL == pToken) );
            XCTAssertTrue( (LEXJ_CONSTANT_STRING == token_getClass(pToken)) );
            pStr = token_ToDataString(pToken);
            XCTAssertTrue( (0 == strcmp("two", AStr_getData(pStr))) );
            obj_Release(pStr);
            pStr = OBJ_NIL;
            pToken = lexj_TokenAdvance(pLexJ, 1);
            XCTAssertFalse( (OBJ_NIL == pToken) );
            
            pToken = lexj_TokenLookAhead(pLexJ, 1);
            XCTAssertFalse( (OBJ_NIL == pToken) );
            XCTAssertTrue( (LEXJ_SEP_COLON == token_getClass(pToken)) );
            pToken = lexj_TokenAdvance(pLexJ, 1);
            XCTAssertFalse( (OBJ_NIL == pToken) );
            
            pToken = lexj_TokenLookAhead(pLexJ, 1);
            XCTAssertFalse( (OBJ_NIL == pToken) );
            XCTAssertTrue( (LEXJ_CONSTANT_STRING == token_getClass(pToken)) );
            pStr = token_ToDataString(pToken);
            XCTAssertTrue( (0 == strcmp("xyz", AStr_getData(pStr))) );
            obj_Release(pStr);
            pStr = OBJ_NIL;
            pToken = lexj_TokenAdvance(pLexJ, 1);
            XCTAssertFalse( (OBJ_NIL == pToken) );
            
            pToken = lexj_TokenLookAhead(pLexJ, 1);
            XCTAssertFalse( (OBJ_NIL == pToken) );
            XCTAssertTrue( (LEXJ_SEP_COMMA == token_getClass(pToken)) );
            pToken = lexj_TokenAdvance(pLexJ, 1);
            XCTAssertFalse( (OBJ_NIL == pToken) );
            
            pToken = lexj_TokenLookAhead(pLexJ, 1);
            XCTAssertFalse( (OBJ_NIL == pToken) );
            XCTAssertTrue( (LEXJ_CONSTANT_STRING == token_getClass(pToken)) );
            pStr = token_ToDataString(pToken);
            XCTAssertTrue( (0 == strcmp("three", AStr_getData(pStr))) );
            obj_Release(pStr);
            pStr = OBJ_NIL;
            pToken = lexj_TokenAdvance(pLexJ, 1);
            XCTAssertFalse( (OBJ_NIL == pToken) );
            
            pToken = lexj_TokenLookAhead(pLexJ, 1);
            XCTAssertFalse( (OBJ_NIL == pToken) );
            XCTAssertTrue( (LEXJ_SEP_COLON == token_getClass(pToken)) );
            pToken = lexj_TokenAdvance(pLexJ, 1);
            XCTAssertFalse( (OBJ_NIL == pToken) );
            
            pToken = lexj_TokenLookAhead(pLexJ, 1);
            XCTAssertFalse( (OBJ_NIL == pToken) );
            XCTAssertTrue( (LEXJ_SEP_LBRACKET == token_getClass(pToken)) );
            pToken = lexj_TokenAdvance(pLexJ, 1);
            XCTAssertFalse( (OBJ_NIL == pToken) );
            
            pToken = lexj_TokenLookAhead(pLexJ, 1);
            XCTAssertFalse( (OBJ_NIL == pToken) );
            XCTAssertTrue( (LEXJ_CONSTANT_STRING == token_getClass(pToken)) );
            pStr = token_ToDataString(pToken);
            XCTAssertTrue( (0 == strcmp("a", AStr_getData(pStr))) );
            obj_Release(pStr);
            pStr = OBJ_NIL;
            pToken = lexj_TokenAdvance(pLexJ, 1);
            XCTAssertFalse( (OBJ_NIL == pToken) );
            
            pToken = lexj_TokenLookAhead(pLexJ, 1);
            XCTAssertFalse( (OBJ_NIL == pToken) );
            XCTAssertTrue( (LEXJ_SEP_COMMA == token_getClass(pToken)) );
            pToken = lexj_TokenAdvance(pLexJ, 1);
            XCTAssertFalse( (OBJ_NIL == pToken) );
            
            pToken = lexj_TokenLookAhead(pLexJ, 1);
            XCTAssertFalse( (OBJ_NIL == pToken) );
            XCTAssertTrue( (LEXJ_CONSTANT_STRING == token_getClass(pToken)) );
            pStr = token_ToDataString(pToken);
            XCTAssertTrue( (0 == strcmp("b", AStr_getData(pStr))) );
            obj_Release(pStr);
            pStr = OBJ_NIL;
            pToken = lexj_TokenAdvance(pLexJ, 1);
            XCTAssertFalse( (OBJ_NIL == pToken) );
            
            pToken = lexj_TokenLookAhead(pLexJ, 1);
            XCTAssertFalse( (OBJ_NIL == pToken) );
            XCTAssertTrue( (LEXJ_SEP_COMMA == token_getClass(pToken)) );
            pToken = lexj_TokenAdvance(pLexJ, 1);
            XCTAssertFalse( (OBJ_NIL == pToken) );
            
            pToken = lexj_TokenLookAhead(pLexJ, 1);
            XCTAssertFalse( (OBJ_NIL == pToken) );
            XCTAssertTrue( (LEXJ_CONSTANT_STRING == token_getClass(pToken)) );
            pStr = token_ToDataString(pToken);
            XCTAssertTrue( (0 == strcmp("c", AStr_getData(pStr))) );
            obj_Release(pStr);
            pStr = OBJ_NIL;
            pToken = lexj_TokenAdvance(pLexJ, 1);
            XCTAssertFalse( (OBJ_NIL == pToken) );
            
            pToken = lexj_TokenLookAhead(pLexJ, 1);
            XCTAssertFalse( (OBJ_NIL == pToken) );
            XCTAssertTrue( (LEXJ_SEP_RBRACKET == token_getClass(pToken)) );
            pToken = lexj_TokenAdvance(pLexJ, 1);
            XCTAssertFalse( (OBJ_NIL == pToken) );
            
            pToken = lexj_TokenLookAhead(pLexJ, 1);
            XCTAssertFalse( (OBJ_NIL == pToken) );
            XCTAssertTrue( (LEXJ_CONSTANT_STRING == token_getClass(pToken)) );
            pStr = token_ToDataString(pToken);
            XCTAssertTrue( (0 == strcmp("four", AStr_getData(pStr))) );
            obj_Release(pStr);
            pStr = OBJ_NIL;
            pToken = lexj_TokenAdvance(pLexJ, 1);
            XCTAssertFalse( (OBJ_NIL == pToken) );
            
            pToken = lexj_TokenLookAhead(pLexJ, 1);
            XCTAssertFalse( (OBJ_NIL == pToken) );
            XCTAssertTrue( (LEXJ_SEP_COLON == token_getClass(pToken)) );
            pToken = lexj_TokenAdvance(pLexJ, 1);
            XCTAssertFalse( (OBJ_NIL == pToken) );
            
            pToken = lexj_TokenLookAhead(pLexJ, 1);
            XCTAssertFalse( (OBJ_NIL == pToken) );
            XCTAssertTrue( (LEXJ_KWD_NULL == token_getClass(pToken)) );
            pToken = lexj_TokenAdvance(pLexJ, 1);
            XCTAssertFalse( (OBJ_NIL == pToken) );
            
            pToken = lexj_TokenLookAhead(pLexJ, 1);
            XCTAssertFalse( (OBJ_NIL == pToken) );
            XCTAssertTrue( (LEXJ_SEP_COMMA == token_getClass(pToken)) );
            pToken = lexj_TokenAdvance(pLexJ, 1);
            XCTAssertFalse( (OBJ_NIL == pToken) );
            
            pToken = lexj_TokenLookAhead(pLexJ, 1);
            XCTAssertFalse( (OBJ_NIL == pToken) );
            XCTAssertTrue( (LEXJ_CONSTANT_STRING == token_getClass(pToken)) );
            pStr = token_ToDataString(pToken);
            XCTAssertTrue( (0 == strcmp("five", AStr_getData(pStr))) );
            obj_Release(pStr);
            pStr = OBJ_NIL;
            pToken = lexj_TokenAdvance(pLexJ, 1);
            XCTAssertFalse( (OBJ_NIL == pToken) );
            
            pToken = lexj_TokenLookAhead(pLexJ, 1);
            XCTAssertFalse( (OBJ_NIL == pToken) );
            XCTAssertTrue( (LEXJ_SEP_COLON == token_getClass(pToken)) );
            pToken = lexj_TokenAdvance(pLexJ, 1);
            XCTAssertFalse( (OBJ_NIL == pToken) );
            
            pToken = lexj_TokenLookAhead(pLexJ, 1);
            XCTAssertFalse( (OBJ_NIL == pToken) );
            XCTAssertTrue( (LEXJ_KWD_TRUE == token_getClass(pToken)) );
            pToken = lexj_TokenAdvance(pLexJ, 1);
            XCTAssertFalse( (OBJ_NIL == pToken) );
            
            pToken = lexj_TokenLookAhead(pLexJ, 1);
            XCTAssertFalse( (OBJ_NIL == pToken) );
            XCTAssertTrue( (LEXJ_SEP_COMMA == token_getClass(pToken)) );
            pToken = lexj_TokenAdvance(pLexJ, 1);
            XCTAssertFalse( (OBJ_NIL == pToken) );
            
            pToken = lexj_TokenLookAhead(pLexJ, 1);
            XCTAssertFalse( (OBJ_NIL == pToken) );
            XCTAssertTrue( (LEXJ_CONSTANT_STRING == token_getClass(pToken)) );
            pStr = token_ToDataString(pToken);
            XCTAssertTrue( (0 == strcmp("six", AStr_getData(pStr))) );
            obj_Release(pStr);
            pStr = OBJ_NIL;
            pToken = lexj_TokenAdvance(pLexJ, 1);
            XCTAssertFalse( (OBJ_NIL == pToken) );
            
            pToken = lexj_TokenLookAhead(pLexJ, 1);
            XCTAssertFalse( (OBJ_NIL == pToken) );
            XCTAssertTrue( (LEXJ_SEP_COLON == token_getClass(pToken)) );
            pToken = lexj_TokenAdvance(pLexJ, 1);
            XCTAssertFalse( (OBJ_NIL == pToken) );
            
            pToken = lexj_TokenLookAhead(pLexJ, 1);
            XCTAssertFalse( (OBJ_NIL == pToken) );
            XCTAssertTrue( (LEXJ_KWD_FALSE == token_getClass(pToken)) );
            pToken = lexj_TokenAdvance(pLexJ, 1);
            XCTAssertFalse( (OBJ_NIL == pToken) );
            
            pToken = lexj_TokenLookAhead(pLexJ, 1);
            XCTAssertFalse( (OBJ_NIL == pToken) );
            XCTAssertTrue( (LEXJ_SEP_RBRACE == token_getClass(pToken)) );
            pToken = lexj_TokenAdvance(pLexJ, 1);
            XCTAssertFalse( (OBJ_NIL == pToken) );
            
            pToken = lexj_TokenLookAhead(pLexJ, 1);
            XCTAssertFalse( (OBJ_NIL == pToken) );
            XCTAssertTrue( (LEX_CLASS_EOF == token_getClass(pToken)) );
            pToken = lexj_TokenAdvance(pLexJ, 1);
            XCTAssertFalse( (OBJ_NIL == pToken) );
            
            obj_Release(pLexJ);
            pLexJ = OBJ_NIL;
        }
        
        obj_Release(pBuf);
        pBuf = OBJ_NIL;
    }
    
    szTbl_SharedReset( );
    trace_SharedReset( );
}



@end



