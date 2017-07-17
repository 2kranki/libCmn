/*
 *	Generated 07/02/2017 09:15:13
 */





// All code under test must be linked into the Unit Test bundle
// Test Macros:
//      TINYTEST_ASSERT(condition)
//      TINYTEST_ASSERT_MSG(condition,msg)
//      TINYTEST_EQUAL(expected, actual)
//      TINYTEST_EQUAL_MSG(expected, actual, msg)
//      TINYTEST_FALSE_MSG(condition,msg)
//      TINYTEST_FALSE(condition)
//      TINYTEST_TRUE_MSG(pointer,msg)
//      TINYTEST_TRUE(condition)





#include    <tinytest.h>
#include    <cmn_defs.h>
#include    <trace.h>
#include    <lexj_internal.h>
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





int         setUp(
    const
    char        *pTestName
)
{
    mem_Init( );
    trace_Shared( ); 
    // Put setup code here. This method is called before the invocation of each
    // test method in the class.
    
    return 1; 
}


int         tearDown(
    const
    char        *pTestName
)
{
    // Put teardown code here. This method is called after the invocation of each
    // test method in the class.

    
    trace_SharedReset( ); 
    mem_Dump( );
    mem_Release( );
    
    return 1; 
}






int         test_lexj_OpenClose(
    const
    char        *pTestName
)
{
    LEXJ_DATA	*pObj = OBJ_NIL;
   
    pObj = lexj_Alloc(0);
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    pObj = lexj_Init( pObj );
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    if (pObj) {

        // Test something.

        obj_Release(pObj);
        pObj = OBJ_NIL;
    }

    return 1;
}



int         test_lexj01(
    const
    char        *pTestName
)
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
    return 1;
}




TINYTEST_START_SUITE(test_lexj);
  TINYTEST_ADD_TEST(test_lexj01,setUp,tearDown);
  TINYTEST_ADD_TEST(test_lexj_OpenClose,setUp,tearDown);
TINYTEST_END_SUITE();

TINYTEST_MAIN_SINGLE_SUITE(test_lexj);





