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
#include    <pplex.h>
#include    <Token_internal.h>
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
    PATH_DATA       *pPath = Path_NewA("abc");
    ASTR_DATA       *pWrkA = OBJ_NIL;
    int32_t         cls;
    const
    char            *pTestInput01 =
                        "class xyz {\n"
			"\ta += b + 10;\n"
			"}\n";
    
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
                
                fRc =   Lex_setSourceInput(
                                              pLex,
                                              (void *)srcFile_InputAdvance,
                                              (void *)srcFile_InputLookAhead,
                                              pSrc
                        );
                XCTAssertTrue( (fRc) );
                
                // 1st Line - "class xyz {\n"
                pToken = Lex_TokenLookAhead(pLex, 1);
                XCTAssertFalse( (OBJ_NIL == pToken) );
                XCTAssertTrue( (Token_Validate(pToken)) );
                XCTAssertTrue( (PPLEX_IDENTIFIER == Token_getClass(pToken)) );
                pWrkA = Token_ToDataString(pToken);
                XCTAssertTrue( (ERESULT_SUCCESS_EQUAL == AStr_CompareA(pWrkA, "class")) );
                obj_Release(pWrkA);
                pWrkA = OBJ_NIL;
                pToken = Lex_TokenAdvance(pLex, 1);
                XCTAssertFalse( (OBJ_NIL == pToken) );
                
                pToken = Lex_TokenLookAhead(pLex, 1);
                XCTAssertFalse( (OBJ_NIL == pToken) );
                XCTAssertTrue( (PPLEX_SEP_WHITESPACE == Token_getClass(pToken)) );
                pToken = Lex_TokenAdvance(pLex, 1);
                XCTAssertFalse( (OBJ_NIL == pToken) );
                
                pToken = Lex_TokenLookAhead(pLex, 1);
                XCTAssertFalse( (OBJ_NIL == pToken) );
                XCTAssertTrue( (PPLEX_IDENTIFIER == Token_getClass(pToken)) );
                pWrkA = Token_ToDataString(pToken);
                XCTAssertTrue( (ERESULT_SUCCESS_EQUAL == AStr_CompareA(pWrkA, "xyz")) );
                obj_Release(pWrkA);
                pWrkA = OBJ_NIL;
                pToken = Lex_TokenAdvance(pLex, 1);
                XCTAssertFalse( (OBJ_NIL == pToken) );
                
                pToken = Lex_TokenLookAhead(pLex, 1);
                XCTAssertFalse( (OBJ_NIL == pToken) );
                XCTAssertTrue( (PPLEX_SEP_WHITESPACE == Token_getClass(pToken)) );
                pToken = Lex_TokenAdvance(pLex, 1);
                XCTAssertFalse( (OBJ_NIL == pToken) );
                
                pToken = Lex_TokenLookAhead(pLex, 1);
                XCTAssertFalse( (OBJ_NIL == pToken) );
                XCTAssertTrue( (PPLEX_SEP_LBRACE == Token_getClass(pToken)) );
                pToken = Lex_TokenAdvance(pLex, 1);
                XCTAssertFalse( (OBJ_NIL == pToken) );
                
                pToken = Lex_TokenLookAhead(pLex, 1);
                XCTAssertFalse( (OBJ_NIL == pToken) );
                XCTAssertTrue( (PPLEX_SEP_NL == Token_getClass(pToken)) );
                pToken = Lex_TokenAdvance(pLex, 1);
                XCTAssertFalse( (OBJ_NIL == pToken) );
                
                // 2nd Line - "\ta += b + c;\n"
                pToken = Lex_TokenLookAhead(pLex, 1);
                XCTAssertFalse( (OBJ_NIL == pToken) );
                XCTAssertTrue( (PPLEX_SEP_WHITESPACE == Token_getClass(pToken)) );
                pToken = Lex_TokenAdvance(pLex, 1);
                XCTAssertFalse( (OBJ_NIL == pToken) );
                
                pToken = Lex_TokenLookAhead(pLex, 1);
                XCTAssertFalse( (OBJ_NIL == pToken) );
                XCTAssertTrue( (PPLEX_IDENTIFIER == Token_getClass(pToken)) );
                pWrkA = Token_ToDataString(pToken);
                XCTAssertTrue( (ERESULT_SUCCESS_EQUAL == AStr_CompareA(pWrkA, "a")) );
                obj_Release(pWrkA);
                pWrkA = OBJ_NIL;
                pToken = Lex_TokenAdvance(pLex, 1);
                XCTAssertFalse( (OBJ_NIL == pToken) );
                
                pToken = Lex_TokenLookAhead(pLex, 1);
                XCTAssertFalse( (OBJ_NIL == pToken) );
                XCTAssertTrue( (PPLEX_SEP_WHITESPACE == Token_getClass(pToken)) );
                pToken = Lex_TokenAdvance(pLex, 1);
                XCTAssertFalse( (OBJ_NIL == pToken) );
                
                pToken = Lex_TokenLookAhead(pLex, 1);
                XCTAssertFalse( (OBJ_NIL == pToken) );
                XCTAssertTrue( (PPLEX_OP_ASSIGN_ADD == Token_getClass(pToken)) );
                pToken = Lex_TokenAdvance(pLex, 1);
                XCTAssertFalse( (OBJ_NIL == pToken) );
                
                pToken = Lex_TokenLookAhead(pLex, 1);
                XCTAssertFalse( (OBJ_NIL == pToken) );
                XCTAssertTrue( (PPLEX_SEP_WHITESPACE == Token_getClass(pToken)) );
                pToken = Lex_TokenAdvance(pLex, 1);
                XCTAssertFalse( (OBJ_NIL == pToken) );
                
                pToken = Lex_TokenLookAhead(pLex, 1);
                XCTAssertFalse( (OBJ_NIL == pToken) );
                XCTAssertTrue( (PPLEX_IDENTIFIER == Token_getClass(pToken)) );
                pWrkA = Token_ToDataString(pToken);
                XCTAssertTrue( (ERESULT_SUCCESS_EQUAL == AStr_CompareA(pWrkA, "b")) );
                obj_Release(pWrkA);
                pWrkA = OBJ_NIL;
                pToken = Lex_TokenAdvance(pLex, 1);
                XCTAssertFalse( (OBJ_NIL == pToken) );
                
                pToken = Lex_TokenLookAhead(pLex, 1);
                XCTAssertFalse( (OBJ_NIL == pToken) );
                XCTAssertTrue( (PPLEX_SEP_WHITESPACE == Token_getClass(pToken)) );
                pToken = Lex_TokenAdvance(pLex, 1);
                XCTAssertFalse( (OBJ_NIL == pToken) );
                
                pToken = Lex_TokenLookAhead(pLex, 1);
                XCTAssertFalse( (OBJ_NIL == pToken) );
                XCTAssertTrue( (PPLEX_OP_ADD == Token_getClass(pToken)) );
                pToken = Lex_TokenAdvance(pLex, 1);
                XCTAssertFalse( (OBJ_NIL == pToken) );
                
                pToken = Lex_TokenLookAhead(pLex, 1);
                XCTAssertFalse( (OBJ_NIL == pToken) );
                XCTAssertTrue( (PPLEX_SEP_WHITESPACE == Token_getClass(pToken)) );
                pToken = Lex_TokenAdvance(pLex, 1);
                XCTAssertFalse( (OBJ_NIL == pToken) );
                
                pToken = Lex_TokenLookAhead(pLex, 1);
                XCTAssertFalse( (OBJ_NIL == pToken) );
                XCTAssertTrue( (PPLEX_CONSTANT_INTEGER == Token_getClass(pToken)) );
                pWrkA = Token_ToDataString(pToken);
                XCTAssertTrue( (ERESULT_SUCCESS_EQUAL == AStr_CompareA(pWrkA, "10")) );
                obj_Release(pWrkA);
                pWrkA = OBJ_NIL;
                pToken = Lex_TokenAdvance(pLex, 1);
                XCTAssertFalse( (OBJ_NIL == pToken) );
                
                pToken = Lex_TokenLookAhead(pLex, 1);
                XCTAssertFalse( (OBJ_NIL == pToken) );
                XCTAssertTrue( (PPLEX_SEP_SEMICOLON == Token_getClass(pToken)) );
                pToken = Lex_TokenAdvance(pLex, 1);
                XCTAssertFalse( (OBJ_NIL == pToken) );
                
                pToken = Lex_TokenLookAhead(pLex, 1);
                XCTAssertFalse( (OBJ_NIL == pToken) );
                XCTAssertTrue( (PPLEX_SEP_NL == Token_getClass(pToken)) );
                pToken = Lex_TokenAdvance(pLex, 1);
                XCTAssertFalse( (OBJ_NIL == pToken) );
                
                // 3rd Line - "}\n"
                pToken = Lex_TokenLookAhead(pLex, 1);
                XCTAssertFalse( (OBJ_NIL == pToken) );
                XCTAssertTrue( (PPLEX_SEP_RBRACE == Token_getClass(pToken)) );
                pToken = Lex_TokenAdvance(pLex, 1);
                XCTAssertFalse( (OBJ_NIL == pToken) );
                
                pToken = Lex_TokenLookAhead(pLex, 1);
                XCTAssertFalse( (OBJ_NIL == pToken) );
                cls = Token_getClass(pToken);
                fprintf(stderr, "\tcls = (%d)-%s\n", cls, pplex_ClassToString(cls));
                XCTAssertTrue( (PPLEX_SEP_NL == cls) );
                pToken = Lex_TokenAdvance(pLex, 1);
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
    PATH_DATA       *pPath = Path_NewA("abc");
    ASTR_DATA       *pWrkA = OBJ_NIL;
    int32_t         cls;
    
    pBuf = AStr_NewA("@class xyz %{\n\ta += b + c;\n%}\n");
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
                
                fRc =   Lex_setSourceInput(
                                              pLex,
                                              (void *)srcFile_InputAdvance,
                                              (void *)srcFile_InputLookAhead,
                                              pSrc
                                              );
                XCTAssertTrue( (fRc) );
                
                // 1st Line - "@class xyz %{\n"
                pToken = Lex_TokenLookAhead(pLex, 1);
                XCTAssertFalse( (OBJ_NIL == pToken) );
                XCTAssertTrue( (PPLEX_IDENTIFIER == Token_getClass(pToken)) );
                pWrkA = Token_ToDataString(pToken);
                XCTAssertTrue( (ERESULT_SUCCESS_EQUAL == AStr_CompareA(pWrkA, "@class")) );
                obj_Release(pWrkA);
                pWrkA = OBJ_NIL;
                pToken = Lex_TokenAdvance(pLex, 1);
                XCTAssertFalse( (OBJ_NIL == pToken) );
                
                pToken = Lex_TokenLookAhead(pLex, 1);
                XCTAssertFalse( (OBJ_NIL == pToken) );
                XCTAssertTrue( (PPLEX_SEP_WHITESPACE == Token_getClass(pToken)) );
                pToken = Lex_TokenAdvance(pLex, 1);
                XCTAssertFalse( (OBJ_NIL == pToken) );
                
                pToken = Lex_TokenLookAhead(pLex, 1);
                XCTAssertFalse( (OBJ_NIL == pToken) );
                pWrkA = Token_ToDataString(pToken);
                cls = Token_getClass(pToken);
                fprintf(stderr, "\tcls = (%d)-%s %s\n",
                        cls,
                        pplex_ClassToString(cls),
                        AStr_getData(pWrkA)
                );
                XCTAssertTrue( (PPLEX_IDENTIFIER == cls) );
                XCTAssertTrue( (ERESULT_SUCCESS_EQUAL == AStr_CompareA(pWrkA, "xyz")) );
                obj_Release(pWrkA);
                pWrkA = OBJ_NIL;
                pToken = Lex_TokenAdvance(pLex, 1);
                XCTAssertFalse( (OBJ_NIL == pToken) );
                
                pToken = Lex_TokenLookAhead(pLex, 1);
                XCTAssertFalse( (OBJ_NIL == pToken) );
                cls = Token_getClass(pToken);
                fprintf(stderr, "\tcls = (%d)-%s\n", cls, pplex_ClassToString(cls));
                XCTAssertTrue( (PPLEX_SEP_WHITESPACE == cls) );
                pToken = Lex_TokenAdvance(pLex, 1);
                XCTAssertFalse( (OBJ_NIL == pToken) );
                
                // 2nd Line - "\ta += b + c;\n"
                // 3rd Line - "%}\n"
                pToken = Lex_TokenLookAhead(pLex, 1);
                XCTAssertFalse( (OBJ_NIL == pToken) );
                cls = Token_getClass(pToken);
                fprintf(stderr, "\tcls = (%d)-%s\n", cls, pplex_ClassToString(cls));
                XCTAssertTrue( (PPLEX_CONSTANT_TEXT == cls) );
                pWrkA = Token_ToDataString(pToken);
                XCTAssertTrue( (ERESULT_SUCCESS_EQUAL == AStr_CompareA(pWrkA, "\n    a += b + c;\n\n")) );
                obj_Release(pWrkA);
                pWrkA = OBJ_NIL;
                pToken = Lex_TokenAdvance(pLex, 1);
                XCTAssertFalse( (OBJ_NIL == pToken) );
                
                pToken = Lex_TokenLookAhead(pLex, 1);
                XCTAssertFalse( (OBJ_NIL == pToken) );
                XCTAssertTrue( (PPLEX_SEP_NL == Token_getClass(pToken)) );
                pToken = Lex_TokenAdvance(pLex, 1);
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
    PATH_DATA       *pPath = Path_NewA("abc");
    ASTR_DATA       *pWrkA = OBJ_NIL;
    int32_t         cls;
    
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
                
                fRc =   Lex_setSourceInput(
                                              pLex,
                                              (void *)srcFile_InputAdvance,
                                              (void *)srcFile_InputLookAhead,
                                              pSrc
                                              );
                XCTAssertTrue( (fRc) );
                
                pToken = Lex_TokenLookAhead(pLex, 1);
                XCTAssertFalse( (OBJ_NIL == pToken) );
                XCTAssertTrue( (PPLEX_SEP_LPAREN == Token_getClass(pToken)) );
                pToken = Lex_TokenAdvance(pLex, 1);
                XCTAssertFalse( (OBJ_NIL == pToken) );
                
                pToken = Lex_TokenLookAhead(pLex, 1);
                XCTAssertFalse( (OBJ_NIL == pToken) );
                XCTAssertTrue( (PPLEX_CONSTANT_CHAR == Token_getClass(pToken)) );
                pWrkA = Token_ToDataString(pToken);
                XCTAssertTrue( (ERESULT_SUCCESS_EQUAL == AStr_CompareA(pWrkA, "'='")) );
                obj_Release(pWrkA);
                pWrkA = OBJ_NIL;
                pToken = Lex_TokenAdvance(pLex, 1);
                XCTAssertFalse( (OBJ_NIL == pToken) );
                
                pToken = Lex_TokenLookAhead(pLex, 1);
                XCTAssertFalse( (OBJ_NIL == pToken) );
                XCTAssertTrue( (PPLEX_OP_OR == Token_getClass(pToken)) );
                pToken = Lex_TokenAdvance(pLex, 1);
                XCTAssertFalse( (OBJ_NIL == pToken) );
                
                pToken = Lex_TokenLookAhead(pLex, 1);
                XCTAssertFalse( (OBJ_NIL == pToken) );
                XCTAssertTrue( (PPLEX_CONSTANT_CHAR == Token_getClass(pToken)) );
                pWrkA = Token_ToDataString(pToken);
                XCTAssertTrue( (ERESULT_SUCCESS_EQUAL == AStr_CompareA(pWrkA, "':'")) );
                obj_Release(pWrkA);
                pWrkA = OBJ_NIL;
                pToken = Lex_TokenAdvance(pLex, 1);
                XCTAssertFalse( (OBJ_NIL == pToken) );
                
                pToken = Lex_TokenLookAhead(pLex, 1);
                XCTAssertFalse( (OBJ_NIL == pToken) );
                XCTAssertTrue( (PPLEX_SEP_RPAREN == Token_getClass(pToken)) );
                pToken = Lex_TokenAdvance(pLex, 1);
                XCTAssertFalse( (OBJ_NIL == pToken) );
                
                pToken = Lex_TokenLookAhead(pLex, 1);
                XCTAssertFalse( (OBJ_NIL == pToken) );
                XCTAssertTrue( (PPLEX_SEP_SEMICOLON == Token_getClass(pToken)) );
                pToken = Lex_TokenAdvance(pLex, 1);
                XCTAssertFalse( (OBJ_NIL == pToken) );
                
                pToken = Lex_TokenLookAhead(pLex, 1);
                XCTAssertFalse( (OBJ_NIL == pToken) );
                XCTAssertTrue( (PPLEX_CLASS_EOF == Token_getClass(pToken)) );
                pToken = Lex_TokenAdvance(pLex, 1);
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
    PATH_DATA       *pPath = Path_NewA("abc");
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
                Lex_setMultiCharConstant(pLex, true);

                fRc =   Lex_setSourceInput(
                                              pLex,
                                              (void *)srcFile_InputAdvance,
                                              (void *)srcFile_InputLookAhead,
                                              pSrc
                                              );
                XCTAssertTrue( (fRc) );
                
                pToken = Lex_TokenLookAhead(pLex, 1);
                XCTAssertFalse( (OBJ_NIL == pToken) );
                XCTAssertTrue( (PPLEX_IDENTIFIER == Token_getClass(pToken)) );
                pWrkA = Token_ToDataString(pToken);
                XCTAssertTrue( (ERESULT_SUCCESS_EQUAL == AStr_CompareA(pWrkA, "a")) );
                obj_Release(pWrkA);
                pWrkA = OBJ_NIL;
                pToken = Lex_TokenAdvance(pLex, 1);
                XCTAssertFalse( (OBJ_NIL == pToken) );
                
                pToken = Lex_TokenLookAhead(pLex, 1);
                XCTAssertFalse( (OBJ_NIL == pToken) );
                XCTAssertTrue( (PPLEX_OP_ASSIGN_ADD == Token_getClass(pToken)) );
                pToken = Lex_TokenAdvance(pLex, 1);
                XCTAssertFalse( (OBJ_NIL == pToken) );
                
                pToken = Lex_TokenLookAhead(pLex, 1);
                XCTAssertFalse( (OBJ_NIL == pToken) );
                XCTAssertTrue( (PPLEX_CONSTANT_STRING == Token_getClass(pToken)) );
                pWrkA = Token_ToDataString(pToken);
                XCTAssertTrue( (ERESULT_SUCCESS_EQUAL == AStr_CompareA(pWrkA, "'+=+'")) );
                obj_Release(pWrkA);
                pWrkA = OBJ_NIL;
                pToken = Lex_TokenAdvance(pLex, 1);
                XCTAssertFalse( (OBJ_NIL == pToken) );
                
                pToken = Lex_TokenLookAhead(pLex, 1);
                XCTAssertFalse( (OBJ_NIL == pToken) );
                XCTAssertTrue( (PPLEX_SEP_SEMICOLON == Token_getClass(pToken)) );
                pToken = Lex_TokenAdvance(pLex, 1);
                XCTAssertFalse( (OBJ_NIL == pToken) );
                
                pToken = Lex_TokenLookAhead(pLex, 1);
                XCTAssertFalse( (OBJ_NIL == pToken) );
                XCTAssertTrue( (PPLEX_CLASS_EOF == Token_getClass(pToken)) );
                pToken = Lex_TokenAdvance(pLex, 1);
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





