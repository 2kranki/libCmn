/*
 *	Generated 03/27/2017 21:41:19
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
#include    <pplex1_internal.h>
#include    <srcFile.h>
#include    <szTbl.h>



#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wtrigraphs"
static
const
char        *pTestInput01 =
"+ ??( ??)\n"
"\ta??/b??'??<??>\n"
"??!??-ab??=\n";
#pragma GCC diagnostic pop






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

    
    szTbl_SharedReset( );
    trace_SharedReset( ); 
    mem_Dump( );
    mem_Release( );
    
    return 1; 
}







int         test_pplex1_OpenClose(
    const
    char        *test_name
)
{
    LEX_DATA	*pObj = OBJ_NIL;
   
    pObj = (LEX_DATA *)pplex1_Alloc( );
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    pObj = (LEX_DATA *)pplex1_Init((PPLEX1_DATA *)pObj, 4);
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    if (pObj) {

        // Test something.

        obj_Release(pObj);
        pObj = OBJ_NIL;
    }

    return 1;
}



int         test_pplex1_Input01(
    const
    char        *test_name
)
{
    SRCFILE_DATA	*pSrc = OBJ_NIL;
    ASTR_DATA       *pBuf = OBJ_NIL;
    LEX_DATA        *pLex = OBJ_NIL;
    TOKEN_DATA      *pToken;
    bool            fRc;
    PATH_DATA       *pPath = path_NewA("abc");
    int32_t         cls;
    
    pBuf = AStr_NewA(pTestInput01);
    XCTAssertFalse( (OBJ_NIL == pBuf) );
    if (pBuf) {
        
        pSrc = srcFile_NewFromAStr(pBuf, pPath, 1, 4);
        XCTAssertFalse( (OBJ_NIL == pSrc) );
        if (pSrc) {
            
            pLex = (LEX_DATA *)pplex1_New(4);
            XCTAssertFalse( (OBJ_NIL == pLex) );
            if (pLex) {
                
                obj_TraceSet(pLex, true);
                
                fRc =   lex_setSourceFunction(
                                              pLex,
                                              (void *)srcFile_InputAdvance,
                                              (void *)srcFile_InputLookAhead,
                                              pSrc
                        );
                XCTAssertTrue( (fRc) );
                
                // 1st Line - "+ ??( ??)\n"
                pToken = lex_TokenLookAhead(pLex, 1);
                XCTAssertFalse( (OBJ_NIL == pToken) );
                cls = token_getClass(pToken);
                fprintf(stderr, "\tcls = (%d)-%s\n", cls, pplex_ClassToString(cls));
                fprintf(stderr, "\tchr = %c\n", token_getChrW32(pToken));
                XCTAssertTrue( ('+' == token_getClass(pToken)) );
                XCTAssertTrue( ('+' == token_getChrW32(pToken)) );
                pToken = lex_TokenAdvance(pLex, 1);
                XCTAssertFalse( (OBJ_NIL == pToken) );
                
                pToken = lex_TokenLookAhead(pLex, 1);
                XCTAssertFalse( (OBJ_NIL == pToken) );
                cls = token_getClass(pToken);
                fprintf(stderr, "\tcls = (%d)-%s\n", cls, pplex_ClassToString(cls));
                XCTAssertTrue( (ASCII_LEXICAL_WHITESPACE == token_getClass(pToken)) );
                pToken = lex_TokenAdvance(pLex, 1);
                XCTAssertFalse( (OBJ_NIL == pToken) );
                
                pToken = lex_TokenLookAhead(pLex, 1);
                XCTAssertFalse( (OBJ_NIL == pToken) );
                fprintf(stderr, "[ == %c\n", token_getClass(pToken));
                XCTAssertTrue( ('[' == token_getClass(pToken)) );
                XCTAssertTrue( ('[' == token_getChrW32(pToken)) );
                pToken = lex_TokenAdvance(pLex, 1);
                XCTAssertFalse( (OBJ_NIL == pToken) );
                
                pToken = lex_TokenLookAhead(pLex, 1);
                XCTAssertFalse( (OBJ_NIL == pToken) );
                cls = token_getClass(pToken);
                fprintf(stderr, "\tcls = (%d)-%s\n", cls, pplex_ClassToString(cls));
                XCTAssertTrue( (ASCII_LEXICAL_WHITESPACE == token_getClass(pToken)) );
                pToken = lex_TokenAdvance(pLex, 1);
                XCTAssertFalse( (OBJ_NIL == pToken) );
                
                pToken = lex_TokenLookAhead(pLex, 1);
                XCTAssertFalse( (OBJ_NIL == pToken) );
                XCTAssertTrue( (']' == token_getClass(pToken)) );
                pToken = lex_TokenAdvance(pLex, 1);
                XCTAssertFalse( (OBJ_NIL == pToken) );
                
                pToken = lex_TokenLookAhead(pLex, 1);
                XCTAssertFalse( (OBJ_NIL == pToken) );
                cls = token_getClass(pToken);
                fprintf(stderr, "\tcls = (%d)-%s\n", cls, pplex_ClassToString(cls));
                XCTAssertTrue( (ASCII_LEXICAL_EOL == token_getClass(pToken)) );
                pToken = lex_TokenAdvance(pLex, 1);
                XCTAssertFalse( (OBJ_NIL == pToken) );
                
                // 2nd Line - "\ta??/b??'??<??>\n"
                pToken = lex_TokenLookAhead(pLex, 1);
                XCTAssertFalse( (OBJ_NIL == pToken) );
                cls = token_getClass(pToken);
                fprintf(stderr, "\tcls = (%d)-%s\n", cls, pplex_ClassToString(cls));
                XCTAssertTrue( (ASCII_LEXICAL_WHITESPACE == token_getClass(pToken)) );
                pToken = lex_TokenAdvance(pLex, 1);
                XCTAssertFalse( (OBJ_NIL == pToken) );
                
                pToken = lex_TokenLookAhead(pLex, 1);
                XCTAssertFalse( (OBJ_NIL == pToken) );
                cls = token_getClass(pToken);
                fprintf(stderr, "\tcls = (%d)-%s\n", cls, pplex_ClassToString(cls));
                XCTAssertTrue( (ASCII_LEXICAL_WHITESPACE == token_getClass(pToken)) );
                pToken = lex_TokenAdvance(pLex, 1);
                XCTAssertFalse( (OBJ_NIL == pToken) );
                
                pToken = lex_TokenLookAhead(pLex, 1);
                XCTAssertFalse( (OBJ_NIL == pToken) );
                cls = token_getClass(pToken);
                fprintf(stderr, "\tcls = (%d)-%s\n", cls, pplex_ClassToString(cls));
                XCTAssertTrue( (ASCII_LEXICAL_WHITESPACE == token_getClass(pToken)) );
                pToken = lex_TokenAdvance(pLex, 1);
                XCTAssertFalse( (OBJ_NIL == pToken) );
                
                pToken = lex_TokenLookAhead(pLex, 1);
                XCTAssertFalse( (OBJ_NIL == pToken) );
                cls = token_getClass(pToken);
                fprintf(stderr, "\tcls = (%d)-%s\n", cls, pplex_ClassToString(cls));
                XCTAssertTrue( (ASCII_LEXICAL_WHITESPACE == token_getClass(pToken)) );
                pToken = lex_TokenAdvance(pLex, 1);
                XCTAssertFalse( (OBJ_NIL == pToken) );
                
                pToken = lex_TokenLookAhead(pLex, 1);
                XCTAssertFalse( (OBJ_NIL == pToken) );
                cls = token_getClass(pToken);
                fprintf(stderr, "\tcls = (%d)-%s\n", cls, pplex_ClassToString(cls));
                XCTAssertTrue( (ASCII_LEXICAL_ALPHA_LOWER == token_getClass(pToken)) );
                XCTAssertTrue( ('a' == token_getChrW32(pToken)) );
                pToken = lex_TokenAdvance(pLex, 1);
                XCTAssertFalse( (OBJ_NIL == pToken) );
                
                pToken = lex_TokenLookAhead(pLex, 1);
                XCTAssertFalse( (OBJ_NIL == pToken) );
                cls = token_getClass(pToken);
                fprintf(stderr, "\tcls = (%d)-%s\n", cls, pplex_ClassToString(cls));
                XCTAssertTrue( ('\\' == cls) );
                XCTAssertTrue( ('\\' == token_getChrW32(pToken)) );
                pToken = lex_TokenAdvance(pLex, 1);
                XCTAssertFalse( (OBJ_NIL == pToken) );
                
                pToken = lex_TokenLookAhead(pLex, 1);
                XCTAssertFalse( (OBJ_NIL == pToken) );
                cls = token_getClass(pToken);
                fprintf(stderr, "\tcls = (%d)-%s\n", cls, pplex_ClassToString(cls));
                XCTAssertTrue( (ASCII_LEXICAL_ALPHA_LOWER == token_getClass(pToken)) );
                XCTAssertTrue( ('b' == token_getChrW32(pToken)) );
                pToken = lex_TokenAdvance(pLex, 1);
                XCTAssertFalse( (OBJ_NIL == pToken) );
                
                pToken = lex_TokenLookAhead(pLex, 1);
                XCTAssertFalse( (OBJ_NIL == pToken) );
                XCTAssertTrue( ('^' == token_getClass(pToken)) );
                XCTAssertTrue( ('^' == token_getChrW32(pToken)) );
                pToken = lex_TokenAdvance(pLex, 1);
                XCTAssertFalse( (OBJ_NIL == pToken) );
                
                pToken = lex_TokenLookAhead(pLex, 1);
                XCTAssertFalse( (OBJ_NIL == pToken) );
                XCTAssertTrue( ('{' == token_getClass(pToken)) );
                XCTAssertTrue( ('{' == token_getChrW32(pToken)) );
                pToken = lex_TokenAdvance(pLex, 1);
                XCTAssertFalse( (OBJ_NIL == pToken) );
                
                pToken = lex_TokenLookAhead(pLex, 1);
                XCTAssertFalse( (OBJ_NIL == pToken) );
                XCTAssertTrue( ('}' == token_getClass(pToken)) );
                XCTAssertTrue( ('}' == token_getChrW32(pToken)) );
                pToken = lex_TokenAdvance(pLex, 1);
                XCTAssertFalse( (OBJ_NIL == pToken) );
                
                pToken = lex_TokenLookAhead(pLex, 1);
                XCTAssertFalse( (OBJ_NIL == pToken) );
                XCTAssertTrue( (ASCII_LEXICAL_EOL == token_getClass(pToken)) );
                pToken = lex_TokenAdvance(pLex, 1);
                XCTAssertFalse( (OBJ_NIL == pToken) );
                
                // 3rd Line - "??!??-ab??=\n"
                pToken = lex_TokenLookAhead(pLex, 1);
                XCTAssertFalse( (OBJ_NIL == pToken) );
                XCTAssertTrue( ('|' == token_getClass(pToken)) );
                XCTAssertTrue( ('|' == token_getChrW32(pToken)) );
                pToken = lex_TokenAdvance(pLex, 1);
                XCTAssertFalse( (OBJ_NIL == pToken) );
                
                pToken = lex_TokenLookAhead(pLex, 1);
                XCTAssertFalse( (OBJ_NIL == pToken) );
                XCTAssertTrue( ('~' == token_getClass(pToken)) );
                XCTAssertTrue( ('~' == token_getChrW32(pToken)) );
                pToken = lex_TokenAdvance(pLex, 1);
                XCTAssertFalse( (OBJ_NIL == pToken) );
                
                pToken = lex_TokenLookAhead(pLex, 1);
                XCTAssertFalse( (OBJ_NIL == pToken) );
                XCTAssertTrue( (ASCII_LEXICAL_ALPHA_LOWER == token_getClass(pToken)) );
                XCTAssertTrue( ('a' == token_getChrW32(pToken)) );
                pToken = lex_TokenAdvance(pLex, 1);
                XCTAssertFalse( (OBJ_NIL == pToken) );
                
                pToken = lex_TokenLookAhead(pLex, 1);
                XCTAssertFalse( (OBJ_NIL == pToken) );
                XCTAssertTrue( (ASCII_LEXICAL_ALPHA_LOWER == token_getClass(pToken)) );
                XCTAssertTrue( ('b' == token_getChrW32(pToken)) );
                pToken = lex_TokenAdvance(pLex, 1);
                XCTAssertFalse( (OBJ_NIL == pToken) );
                
                pToken = lex_TokenLookAhead(pLex, 1);
                XCTAssertFalse( (OBJ_NIL == pToken) );
                XCTAssertTrue( ('#' == token_getClass(pToken)) );
                XCTAssertTrue( ('#' == token_getChrW32(pToken)) );
                pToken = lex_TokenAdvance(pLex, 1);
                XCTAssertFalse( (OBJ_NIL == pToken) );
                
                pToken = lex_TokenLookAhead(pLex, 1);
                XCTAssertFalse( (OBJ_NIL == pToken) );
                XCTAssertTrue( (ASCII_LEXICAL_EOL == token_getClass(pToken)) );
                pToken = lex_TokenAdvance(pLex, 1);
                XCTAssertFalse( (OBJ_NIL == pToken) );
                
                pToken = lex_TokenLookAhead(pLex, 1);
                XCTAssertFalse( (OBJ_NIL == pToken) );
                XCTAssertTrue( (LEX_CLASS_EOF == token_getClass(pToken)) );
                pToken = lex_TokenAdvance(pLex, 1);
                XCTAssertFalse( (OBJ_NIL == pToken) );
                
                obj_Release(pLex);
                pLex = OBJ_NIL;
            }
            
            obj_Release(pSrc);
            pSrc = OBJ_NIL;
        }
        
        obj_Release(pBuf);
        pBuf = OBJ_NIL;
    }
    
    obj_Release(pPath);
    pPath = OBJ_NIL;
    szTbl_SharedReset();

    return 1;
}




TINYTEST_START_SUITE(test_pplex1);
  TINYTEST_ADD_TEST(test_pplex1_Input01,setUp,tearDown);
  TINYTEST_ADD_TEST(test_pplex1_OpenClose,setUp,tearDown);
TINYTEST_END_SUITE();

TINYTEST_MAIN_SINGLE_SUITE(test_pplex1);





