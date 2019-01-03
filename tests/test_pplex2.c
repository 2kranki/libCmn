/*
 *	Generated 08/21/2017 13:03:23
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
#include    <pplex2_internal.h>
#include    <token_internal.h>
#include    <szTbl.h>



static
const
char        *pTestInput01 =
"class xyz {\n"
"\ta += b + 10;\n"
"}\n";


static
const
char        *pTestInput02 =
"@class xyz %{\n"
"\ta += b + c;\n"
"%}\n";


static
const
char        *pTestInput03 =
"\ta += =a'71';\n";




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
    mem_Release( );
    
    return 1; 
}






int         test_pplex2_OpenClose(
    const
    char        *pTestName
)
{
    PPLEX2_DATA	*pObj = OBJ_NIL;
   
    pObj = pplex2_Alloc( );
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    pObj = pplex2_Init(pObj, 4);
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    if (pObj) {

        // Test something.

        obj_Release(pObj);
        pObj = OBJ_NIL;
    }

    return 1;
}



int         test_pplex2_Input01(
    const
    char        *pTestName
)
{
    SRCFILE_DATA	*pSrc = OBJ_NIL;
    ASTR_DATA       *pBuf = OBJ_NIL;
    LEX_DATA        *pLex = OBJ_NIL;
    TOKEN_DATA      *pToken;
    bool            fRc;
    PATH_DATA       *pPath = path_NewA("abc");
    ASTR_DATA       *pWrkA = OBJ_NIL;
    
    pBuf = AStr_NewA(pTestInput01);
    XCTAssertFalse( (OBJ_NIL == pBuf) );
    if (pBuf) {
        
        pSrc = srcFile_NewFromAStr(pPath, pBuf, 1, 4);
        XCTAssertFalse( (OBJ_NIL == pSrc) );
        if (pSrc) {
            
            pLex = (LEX_DATA *)pplex2_New(4);
            XCTAssertFalse( (OBJ_NIL == pLex) );
            fRc = pplex2_setKwdSelection((PPLEX2_DATA *)pLex, -1);
            XCTAssertTrue( (fRc) );
            if (pLex) {
                
                obj_TraceSet(pLex, true);
                pplex2_setReturnNL((PPLEX2_DATA *)pLex, true);
                pplex2_setReturnWS((PPLEX2_DATA *)pLex, true);
                
                fRc =   lex_setSourceFunction(
                                              pLex,
                                              (void *)srcFile_InputAdvance,
                                              (void *)srcFile_InputLookAhead,
                                              pSrc
                        );
                XCTAssertTrue( (fRc) );
                
                // 1st Line - "class xyz {\n"
                pToken = lex_TokenLookAhead(pLex, 1);
                XCTAssertFalse( (OBJ_NIL == pToken) );
                XCTAssertTrue( (token_Validate(pToken)) );
                XCTAssertTrue( (PPLEX_IDENTIFIER == token_getClass(pToken)) );
                pWrkA = token_ToDataString(pToken);
                XCTAssertTrue( (ERESULT_SUCCESS_EQUAL == AStr_CompareA(pWrkA, "class")) );
                obj_Release(pWrkA);
                pWrkA = OBJ_NIL;
                pToken = lex_TokenAdvance(pLex, 1);
                XCTAssertFalse( (OBJ_NIL == pToken) );
                
                pToken = lex_TokenLookAhead(pLex, 1);
                XCTAssertFalse( (OBJ_NIL == pToken) );
                XCTAssertTrue( (PPLEX_SEP_WHITESPACE == token_getClass(pToken)) );
                pToken = lex_TokenAdvance(pLex, 1);
                XCTAssertFalse( (OBJ_NIL == pToken) );
                
                pToken = lex_TokenLookAhead(pLex, 1);
                XCTAssertFalse( (OBJ_NIL == pToken) );
                XCTAssertTrue( (PPLEX_IDENTIFIER == token_getClass(pToken)) );
                pWrkA = token_ToDataString(pToken);
                XCTAssertTrue( (ERESULT_SUCCESS_EQUAL == AStr_CompareA(pWrkA, "xyz")) );
                obj_Release(pWrkA);
                pWrkA = OBJ_NIL;
                pToken = lex_TokenAdvance(pLex, 1);
                XCTAssertFalse( (OBJ_NIL == pToken) );
                
                pToken = lex_TokenLookAhead(pLex, 1);
                XCTAssertFalse( (OBJ_NIL == pToken) );
                XCTAssertTrue( (PPLEX_SEP_WHITESPACE == token_getClass(pToken)) );
                pToken = lex_TokenAdvance(pLex, 1);
                XCTAssertFalse( (OBJ_NIL == pToken) );
                
                pToken = lex_TokenLookAhead(pLex, 1);
                XCTAssertFalse( (OBJ_NIL == pToken) );
                XCTAssertTrue( (PPLEX_SEP_LBRACE == token_getClass(pToken)) );
                pToken = lex_TokenAdvance(pLex, 1);
                XCTAssertFalse( (OBJ_NIL == pToken) );
                
                pToken = lex_TokenLookAhead(pLex, 1);
                XCTAssertFalse( (OBJ_NIL == pToken) );
                XCTAssertTrue( (PPLEX_SEP_NL == token_getClass(pToken)) );
                pToken = lex_TokenAdvance(pLex, 1);
                XCTAssertFalse( (OBJ_NIL == pToken) );
                
                // 2nd Line - "\ta += b + c;\n"
                pToken = lex_TokenLookAhead(pLex, 1);
                XCTAssertFalse( (OBJ_NIL == pToken) );
                XCTAssertTrue( (PPLEX_SEP_WHITESPACE == token_getClass(pToken)) );
                pToken = lex_TokenAdvance(pLex, 1);
                XCTAssertFalse( (OBJ_NIL == pToken) );
                
                pToken = lex_TokenLookAhead(pLex, 1);
                XCTAssertFalse( (OBJ_NIL == pToken) );
                XCTAssertTrue( (PPLEX_IDENTIFIER == token_getClass(pToken)) );
                pWrkA = token_ToDataString(pToken);
                XCTAssertTrue( (ERESULT_SUCCESS_EQUAL == AStr_CompareA(pWrkA, "a")) );
                obj_Release(pWrkA);
                pWrkA = OBJ_NIL;
                pToken = lex_TokenAdvance(pLex, 1);
                XCTAssertFalse( (OBJ_NIL == pToken) );
                
                pToken = lex_TokenLookAhead(pLex, 1);
                XCTAssertFalse( (OBJ_NIL == pToken) );
                XCTAssertTrue( (PPLEX_SEP_WHITESPACE == token_getClass(pToken)) );
                pToken = lex_TokenAdvance(pLex, 1);
                XCTAssertFalse( (OBJ_NIL == pToken) );
                
                pToken = lex_TokenLookAhead(pLex, 1);
                XCTAssertFalse( (OBJ_NIL == pToken) );
                XCTAssertTrue( (PPLEX_OP_ASSIGN_ADD == token_getClass(pToken)) );
                pToken = lex_TokenAdvance(pLex, 1);
                XCTAssertFalse( (OBJ_NIL == pToken) );
                
                pToken = lex_TokenLookAhead(pLex, 1);
                XCTAssertFalse( (OBJ_NIL == pToken) );
                XCTAssertTrue( (PPLEX_SEP_WHITESPACE == token_getClass(pToken)) );
                pToken = lex_TokenAdvance(pLex, 1);
                XCTAssertFalse( (OBJ_NIL == pToken) );
                
                pToken = lex_TokenLookAhead(pLex, 1);
                XCTAssertFalse( (OBJ_NIL == pToken) );
                XCTAssertTrue( (PPLEX_IDENTIFIER == token_getClass(pToken)) );
                pWrkA = token_ToDataString(pToken);
                XCTAssertTrue( (ERESULT_SUCCESS_EQUAL == AStr_CompareA(pWrkA, "b")) );
                obj_Release(pWrkA);
                pWrkA = OBJ_NIL;
                pToken = lex_TokenAdvance(pLex, 1);
                XCTAssertFalse( (OBJ_NIL == pToken) );
                
                pToken = lex_TokenLookAhead(pLex, 1);
                XCTAssertFalse( (OBJ_NIL == pToken) );
                XCTAssertTrue( (PPLEX_SEP_WHITESPACE == token_getClass(pToken)) );
                pToken = lex_TokenAdvance(pLex, 1);
                XCTAssertFalse( (OBJ_NIL == pToken) );
                
                pToken = lex_TokenLookAhead(pLex, 1);
                XCTAssertFalse( (OBJ_NIL == pToken) );
                XCTAssertTrue( (PPLEX_OP_ADD == token_getClass(pToken)) );
                pToken = lex_TokenAdvance(pLex, 1);
                XCTAssertFalse( (OBJ_NIL == pToken) );
                
                pToken = lex_TokenLookAhead(pLex, 1);
                XCTAssertFalse( (OBJ_NIL == pToken) );
                XCTAssertTrue( (PPLEX_SEP_WHITESPACE == token_getClass(pToken)) );
                pToken = lex_TokenAdvance(pLex, 1);
                XCTAssertFalse( (OBJ_NIL == pToken) );
                
                pToken = lex_TokenLookAhead(pLex, 1);
                XCTAssertFalse( (OBJ_NIL == pToken) );
                XCTAssertTrue( (PPLEX_CONSTANT_INTEGER == token_getClass(pToken)) );
                pWrkA = token_ToDataString(pToken);
                XCTAssertTrue( (ERESULT_SUCCESS_EQUAL == AStr_CompareA(pWrkA, "10")) );
                obj_Release(pWrkA);
                pWrkA = OBJ_NIL;
                pToken = lex_TokenAdvance(pLex, 1);
                XCTAssertFalse( (OBJ_NIL == pToken) );
                
                pToken = lex_TokenLookAhead(pLex, 1);
                XCTAssertFalse( (OBJ_NIL == pToken) );
                XCTAssertTrue( (PPLEX_SEP_SEMICOLON == token_getClass(pToken)) );
                pToken = lex_TokenAdvance(pLex, 1);
                XCTAssertFalse( (OBJ_NIL == pToken) );
                
                pToken = lex_TokenLookAhead(pLex, 1);
                XCTAssertFalse( (OBJ_NIL == pToken) );
                XCTAssertTrue( (PPLEX_SEP_NL == token_getClass(pToken)) );
                pToken = lex_TokenAdvance(pLex, 1);
                XCTAssertFalse( (OBJ_NIL == pToken) );
                
                // 3rd Line - "}\n"
                pToken = lex_TokenLookAhead(pLex, 1);
                XCTAssertFalse( (OBJ_NIL == pToken) );
                XCTAssertTrue( (PPLEX_SEP_RBRACE == token_getClass(pToken)) );
                pToken = lex_TokenAdvance(pLex, 1);
                XCTAssertFalse( (OBJ_NIL == pToken) );
                
                pToken = lex_TokenLookAhead(pLex, 1);
                XCTAssertFalse( (OBJ_NIL == pToken) );
                XCTAssertTrue( (PPLEX_SEP_NL == token_getClass(pToken)) );
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



int         test_pplex2_Input02(
    const
    char        *pTestName
)
{
    SRCFILE_DATA	*pSrc = OBJ_NIL;
    ASTR_DATA       *pBuf = OBJ_NIL;
    LEX_DATA        *pLex = OBJ_NIL;
    TOKEN_DATA      *pToken;
    bool            fRc;
    PATH_DATA       *pPath = path_NewA("abc");
    ASTR_DATA       *pWrkA = OBJ_NIL;
    
    pBuf = AStr_NewA(pTestInput02);
    XCTAssertFalse( (OBJ_NIL == pBuf) );
    if (pBuf) {
        
        pSrc = srcFile_NewFromAStr(pPath, pBuf, 1, 4);
        XCTAssertFalse( (OBJ_NIL == pSrc) );
        if (pSrc) {
            
            pLex = (LEX_DATA *)pplex2_New(4);
            XCTAssertFalse( (OBJ_NIL == pLex) );
            fRc = pplex2_setKwdSelection((PPLEX2_DATA *)pLex,-1);
            XCTAssertTrue( (fRc) );
            if (pLex) {
                
                obj_TraceSet(pLex, true);
                pplex2_setReturnNL((PPLEX2_DATA *)pLex, true);
                pplex2_setReturnWS((PPLEX2_DATA *)pLex, true);
                
                fRc =   lex_setSourceFunction(
                                              pLex,
                                              (void *)srcFile_InputAdvance,
                                              (void *)srcFile_InputLookAhead,
                                              pSrc
                                              );
                XCTAssertTrue( (fRc) );
                
                // 1st Line - "@class xyz %{\n"
                pToken = lex_TokenLookAhead(pLex, 1);
                XCTAssertFalse( (OBJ_NIL == pToken) );
                XCTAssertTrue( (PPLEX_IDENTIFIER == token_getClass(pToken)) );
                pWrkA = token_ToDataString(pToken);
                XCTAssertTrue( (ERESULT_SUCCESS_EQUAL == AStr_CompareA(pWrkA, "@class")) );
                obj_Release(pWrkA);
                pWrkA = OBJ_NIL;
                pToken = lex_TokenAdvance(pLex, 1);
                XCTAssertFalse( (OBJ_NIL == pToken) );
                
                pToken = lex_TokenLookAhead(pLex, 1);
                XCTAssertFalse( (OBJ_NIL == pToken) );
                XCTAssertTrue( (PPLEX_SEP_WHITESPACE == token_getClass(pToken)) );
                pToken = lex_TokenAdvance(pLex, 1);
                XCTAssertFalse( (OBJ_NIL == pToken) );
                
                pToken = lex_TokenLookAhead(pLex, 1);
                XCTAssertFalse( (OBJ_NIL == pToken) );
                XCTAssertTrue( (PPLEX_IDENTIFIER == token_getClass(pToken)) );
                pWrkA = token_ToDataString(pToken);
                XCTAssertTrue( (ERESULT_SUCCESS_EQUAL == AStr_CompareA(pWrkA, "xyz")) );
                obj_Release(pWrkA);
                pWrkA = OBJ_NIL;
                pToken = lex_TokenAdvance(pLex, 1);
                XCTAssertFalse( (OBJ_NIL == pToken) );
                
                pToken = lex_TokenLookAhead(pLex, 1);
                XCTAssertFalse( (OBJ_NIL == pToken) );
                XCTAssertTrue( (PPLEX_SEP_WHITESPACE == token_getClass(pToken)) );
                pToken = lex_TokenAdvance(pLex, 1);
                XCTAssertFalse( (OBJ_NIL == pToken) );
                
                // 2nd Line - "\ta += b + c;\n"
                // 3rd Line - "%}\n"
                pToken = lex_TokenLookAhead(pLex, 1);
                XCTAssertFalse( (OBJ_NIL == pToken) );
                XCTAssertTrue( (PPLEX_CONSTANT_TEXT == token_getClass(pToken)) );
                pWrkA = token_ToDataString(pToken);
                XCTAssertTrue( (ERESULT_SUCCESS_EQUAL == AStr_CompareA(pWrkA, "\n    a += b + c;\n\n")) );
                obj_Release(pWrkA);
                pWrkA = OBJ_NIL;
                pToken = lex_TokenAdvance(pLex, 1);
                XCTAssertFalse( (OBJ_NIL == pToken) );
                
                pToken = lex_TokenLookAhead(pLex, 1);
                XCTAssertFalse( (OBJ_NIL == pToken) );
                XCTAssertTrue( (PPLEX_SEP_NL == token_getClass(pToken)) );
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



int         test_pplex2_Input03(
    const
    char        *pTestName
)
{
    SRCFILE_DATA    *pSrc = OBJ_NIL;
    ASTR_DATA       *pBuf = OBJ_NIL;
    LEX_DATA        *pLex = OBJ_NIL;
    TOKEN_DATA      *pToken;
    bool            fRc;
    PATH_DATA       *pPath = path_NewA("abc");
    ASTR_DATA       *pWrkA = OBJ_NIL;
    
    pBuf = AStr_NewA("('=' | ':') ;");
    XCTAssertFalse( (OBJ_NIL == pBuf) );
    if (pBuf) {
        
        pSrc = srcFile_NewFromAStr(pPath, pBuf, 1, 4);
        XCTAssertFalse( (OBJ_NIL == pSrc) );
        if (pSrc) {
            
            pLex = (LEX_DATA *)pplex2_New(8);
            XCTAssertFalse( (OBJ_NIL == pLex) );
            fRc = pplex2_setKwdSelection((PPLEX2_DATA *)pLex,-1);
            XCTAssertTrue( (fRc) );
            if (pLex) {
                
                obj_TraceSet(pLex, true);
                pplex2_setReturnNL((PPLEX2_DATA *)pLex, false);
                pplex2_setReturnWS((PPLEX2_DATA *)pLex, false);
                
                fRc =   lex_setSourceFunction(
                                              pLex,
                                              (void *)srcFile_InputAdvance,
                                              (void *)srcFile_InputLookAhead,
                                              pSrc
                                              );
                XCTAssertTrue( (fRc) );
                
                pToken = lex_TokenLookAhead(pLex, 1);
                XCTAssertFalse( (OBJ_NIL == pToken) );
                XCTAssertTrue( (PPLEX_SEP_LPAREN == token_getClass(pToken)) );
                pToken = lex_TokenAdvance(pLex, 1);
                XCTAssertFalse( (OBJ_NIL == pToken) );
                
                pToken = lex_TokenLookAhead(pLex, 1);
                XCTAssertFalse( (OBJ_NIL == pToken) );
                XCTAssertTrue( (PPLEX_CONSTANT_CHAR == token_getClass(pToken)) );
                pWrkA = token_ToDataString(pToken);
                XCTAssertTrue( (ERESULT_SUCCESS_EQUAL == AStr_CompareA(pWrkA, "'='")) );
                obj_Release(pWrkA);
                pWrkA = OBJ_NIL;
                pToken = lex_TokenAdvance(pLex, 1);
                XCTAssertFalse( (OBJ_NIL == pToken) );
                
                pToken = lex_TokenLookAhead(pLex, 1);
                XCTAssertFalse( (OBJ_NIL == pToken) );
                XCTAssertTrue( (PPLEX_OP_OR == token_getClass(pToken)) );
                pToken = lex_TokenAdvance(pLex, 1);
                XCTAssertFalse( (OBJ_NIL == pToken) );
                
                pToken = lex_TokenLookAhead(pLex, 1);
                XCTAssertFalse( (OBJ_NIL == pToken) );
                XCTAssertTrue( (PPLEX_CONSTANT_CHAR == token_getClass(pToken)) );
                pWrkA = token_ToDataString(pToken);
                XCTAssertTrue( (ERESULT_SUCCESS_EQUAL == AStr_CompareA(pWrkA, "':'")) );
                obj_Release(pWrkA);
                pWrkA = OBJ_NIL;
                pToken = lex_TokenAdvance(pLex, 1);
                XCTAssertFalse( (OBJ_NIL == pToken) );
                
                pToken = lex_TokenLookAhead(pLex, 1);
                XCTAssertFalse( (OBJ_NIL == pToken) );
                XCTAssertTrue( (PPLEX_SEP_RPAREN == token_getClass(pToken)) );
                pToken = lex_TokenAdvance(pLex, 1);
                XCTAssertFalse( (OBJ_NIL == pToken) );
                
                pToken = lex_TokenLookAhead(pLex, 1);
                XCTAssertFalse( (OBJ_NIL == pToken) );
                XCTAssertTrue( (PPLEX_SEP_SEMICOLON == token_getClass(pToken)) );
                pToken = lex_TokenAdvance(pLex, 1);
                XCTAssertFalse( (OBJ_NIL == pToken) );
                
                pToken = lex_TokenLookAhead(pLex, 1);
                XCTAssertFalse( (OBJ_NIL == pToken) );
                XCTAssertTrue( (PPLEX_CLASS_EOF == token_getClass(pToken)) );
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



int         test_pplex2_Input04(
    const
    char            *pTestName
)
{
    SRCFILE_DATA    *pSrc = OBJ_NIL;
    ASTR_DATA       *pBuf = OBJ_NIL;
    LEX_DATA        *pLex = OBJ_NIL;
    TOKEN_DATA      *pToken;
    bool            fRc;
    PATH_DATA       *pPath = path_NewA("abc");
    ASTR_DATA       *pWrkA = OBJ_NIL;
    
    pBuf = AStr_NewA("a += '+=+';");
    XCTAssertFalse( (OBJ_NIL == pBuf) );
    if (pBuf) {
        
        pSrc = srcFile_NewFromAStr(pPath, pBuf, 1, 4);
        XCTAssertFalse( (OBJ_NIL == pSrc) );
        if (pSrc) {
            
            pLex = (LEX_DATA *)pplex2_New(2);
            XCTAssertFalse( (OBJ_NIL == pLex) );
            fRc = pplex2_setKwdSelection((PPLEX2_DATA *)pLex,-1);
            XCTAssertTrue( (fRc) );
            if (pLex) {
                
                obj_TraceSet(pLex, true);
                pplex2_setReturnNL((PPLEX2_DATA *)pLex, true);
                pplex2_setReturnWS((PPLEX2_DATA *)pLex, false);
                lex_setMultiCharConstant(pLex, true);

                fRc =   lex_setSourceFunction(
                                              pLex,
                                              (void *)srcFile_InputAdvance,
                                              (void *)srcFile_InputLookAhead,
                                              pSrc
                                              );
                XCTAssertTrue( (fRc) );
                
                pToken = lex_TokenLookAhead(pLex, 1);
                XCTAssertFalse( (OBJ_NIL == pToken) );
                XCTAssertTrue( (PPLEX_IDENTIFIER == token_getClass(pToken)) );
                pWrkA = token_ToDataString(pToken);
                XCTAssertTrue( (ERESULT_SUCCESS_EQUAL == AStr_CompareA(pWrkA, "a")) );
                obj_Release(pWrkA);
                pWrkA = OBJ_NIL;
                pToken = lex_TokenAdvance(pLex, 1);
                XCTAssertFalse( (OBJ_NIL == pToken) );
                
                pToken = lex_TokenLookAhead(pLex, 1);
                XCTAssertFalse( (OBJ_NIL == pToken) );
                XCTAssertTrue( (PPLEX_OP_ASSIGN_ADD == token_getClass(pToken)) );
                pToken = lex_TokenAdvance(pLex, 1);
                XCTAssertFalse( (OBJ_NIL == pToken) );
                
                pToken = lex_TokenLookAhead(pLex, 1);
                XCTAssertFalse( (OBJ_NIL == pToken) );
                XCTAssertTrue( (PPLEX_CONSTANT_STRING == token_getClass(pToken)) );
                pWrkA = token_ToDataString(pToken);
                XCTAssertTrue( (ERESULT_SUCCESS_EQUAL == AStr_CompareA(pWrkA, "'+=+'")) );
                obj_Release(pWrkA);
                pWrkA = OBJ_NIL;
                pToken = lex_TokenAdvance(pLex, 1);
                XCTAssertFalse( (OBJ_NIL == pToken) );
                
                pToken = lex_TokenLookAhead(pLex, 1);
                XCTAssertFalse( (OBJ_NIL == pToken) );
                XCTAssertTrue( (PPLEX_SEP_SEMICOLON == token_getClass(pToken)) );
                pToken = lex_TokenAdvance(pLex, 1);
                XCTAssertFalse( (OBJ_NIL == pToken) );
                
                pToken = lex_TokenLookAhead(pLex, 1);
                XCTAssertFalse( (OBJ_NIL == pToken) );
                XCTAssertTrue( (PPLEX_CLASS_EOF == token_getClass(pToken)) );
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




TINYTEST_START_SUITE(test_pplex2);
    TINYTEST_ADD_TEST(test_pplex2_Input04,setUp,tearDown);
    TINYTEST_ADD_TEST(test_pplex2_Input03,setUp,tearDown);
    TINYTEST_ADD_TEST(test_pplex2_Input02,setUp,tearDown);
    TINYTEST_ADD_TEST(test_pplex2_Input01,setUp,tearDown);
    TINYTEST_ADD_TEST(test_pplex2_OpenClose,setUp,tearDown);
TINYTEST_END_SUITE();

TINYTEST_MAIN_SINGLE_SUITE(test_pplex2);





