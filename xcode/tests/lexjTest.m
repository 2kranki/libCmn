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
#include    <srcFile.h>



static
const
char        *pTestInput01 =
"// Test01 Input\n"
"{ /* test comment */\n"
    "\"one\": 123,\n"
    "\"two\":\"xyz\",\n"
    "\"three\":[a, b, c],\n"
    "\"four\":null,\n"
    "\"five\":true,\n"
    "\"six\":false\n"
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
    PATH_DATA       *pPath = path_NewA("source is a string");
    
    pBuf = AStr_NewA(pTestInput01);
    XCTAssertFalse( (OBJ_NIL == pBuf) );
    if (pBuf) {
        
        pLexJ = lexj_NewAStr(pBuf, 4, true);
        XCTAssertFalse( (OBJ_NIL == pLexJ) );
        if (pLexJ) {
            
            pToken = lexj_TokenLookAhead(pLexJ, 1);
            XCTAssertFalse( (OBJ_NIL == pToken) );
            XCTAssertTrue( (LEXJ_SEP_LBRACE == token_getClass(pToken)) );
            pToken = lexj_TokenAdvance(pLexJ, 1);
            XCTAssertFalse( (OBJ_NIL == pToken) );
            
            pToken = lexj_TokenLookAhead(pLexJ, 1);
            XCTAssertFalse( (OBJ_NIL == pToken) );
            XCTAssertTrue( (LEXJ_CONSTANT_STRING == token_getClass(pToken)) );
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
            
            obj_Release(pLexJ);
            pLexJ = OBJ_NIL;
        }
        
        obj_Release(pBuf);
        pBuf = OBJ_NIL;
    }
    
    obj_Release(pPath);
    pPath = OBJ_NIL;
    szTbl_SharedReset();
}



@end



