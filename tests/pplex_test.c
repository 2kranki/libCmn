/*
 *	Generated 08/21/2017 13:03:15
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
#include    <pplex_internal.h>
#include    <SrcErrors.h>
#include    <szTbl.h>



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

    SrcErrors_SharedReset( );
    szTbl_SharedReset( );
    trace_SharedReset( ); 
    mem_Release( );
    
    return 1; 
}






int         test_pplex_OpenClose(
    const
    char        *pTestName
)
{
    PPLEX_DATA	*pObj = OBJ_NIL;

    fprintf(stderr, "Performing: %s\n", pTestName);

    pObj = pplex_Alloc( );
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    pObj = pplex_Init(pObj, 4);
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    if (pObj) {

        // Test something.

        obj_Release(pObj);
        pObj = OBJ_NIL;
    }

    fprintf(stderr, "PPLEX_OP_ADD=%d\n",PPLEX_OP_ADD);
    fprintf(stderr, "PPLEX_SPCL_COLON=%d\n",PPLEX_SPCL_COLON);
    fprintf(stderr, "PPLEX_KWD_GOAL=%d\n",PPLEX_KWD_GOAL);
    fprintf(stderr, "PPLEX_IDENTIFIER=%d\n",PPLEX_IDENTIFIER);
    fprintf(stderr, "PPLEX_KWD_INTERNAL=%d\n",PPLEX_KWD_INTERNAL);
    fprintf(stderr, "PPLEX_SEP_LPAREN=%d\n",PPLEX_SEP_LPAREN);
    fprintf(stderr, "PPLEX_OP_MUL=%d\n",PPLEX_OP_MUL);
    fprintf(stderr, "PPLEX_OP_QUESTION=%d\n",PPLEX_OP_QUESTION);
    fprintf(stderr, "PPLEX_SEP_RPAREN=%d\n",PPLEX_SEP_RPAREN);
    fprintf(stderr, "PPLEX_SEP_SEMICOLON=%d\n",PPLEX_SEP_SEMICOLON);
    fprintf(stderr, "PPLEX_KWD_TERM=%d\n",PPLEX_KWD_TERM);
    fprintf(stderr, "PPLEX_SPCL_WHITESPACE=%d\n",PPLEX_SPCL_WHITESPACE);

    fprintf(stderr, "...%s completed.\n\n", pTestName);
    return 1;
}



int         test_pplex_Input01(
    const
    char        *pTestName
)
{
    ASTR_DATA       *pBuf = OBJ_NIL;
    LEX_DATA        *pLex = OBJ_NIL;
    TOKEN_DATA      *pToken;
    bool            fRc;
    PATH_DATA       *pPath = path_NewA("abc");
    ASTR_DATA       *pStr = OBJ_NIL;
    ERESULT         eRc;
    int32_t         cls;
    
    fprintf(stderr, "Performing: %s\n", pTestName);
    
    pBuf =  AStr_NewA(
                "@interface xyz\n"
                //"@property int a;\n"
                "@end\n"            
            );
    XCTAssertFalse( (OBJ_NIL == pBuf) );
    if (pBuf) {
        
        pLex = (LEX_DATA *)pplex_New(4);
        XCTAssertFalse( (OBJ_NIL == pLex) );
        if (OBJ_NIL == pLex) {
            return 0;
        }

        pplex_setReturnNL((PPLEX_DATA *)pLex, true);
        pplex_setReturnWS((PPLEX_DATA *)pLex, true);
        
        eRc = pplex_CreateLexers((PPLEX_DATA *)pLex, false, true);
        XCTAssertFalse( (ERESULT_FAILED(eRc)) );
        
        eRc =   pplex_CreateSourceFromAStr(
                                      (PPLEX_DATA *)pLex,
                                      pPath,
                                      pBuf
                );
        XCTAssertFalse( (ERESULT_FAILED(eRc)) );
        
        // 1st Line - "@interface xyz\n"
        pToken = lex_TokenLookAhead(pLex, 1);
        XCTAssertFalse( (OBJ_NIL == pToken) );
        {
            pStr = Token_ToDataString(pToken);
            fprintf(stderr, "token text=\"%s\"\n",
                            AStr_getData(pStr));
            obj_Release(pStr);
            pStr = OBJ_NIL;
            fprintf(stderr, "token class = %s\n",
                            pplex_ClassToString(Token_getClass(pToken)));
        }
        XCTAssertTrue( (PPLEX_KWD_AT_INTERFACE == Token_getClass(pToken)) );
        pStr = Token_ToDataString(pToken);
        XCTAssertTrue( (ERESULT_SUCCESS_EQUAL == AStr_CompareA(pStr, "@interface")) );
        obj_Release(pStr);
        pStr = OBJ_NIL;
        pToken = lex_TokenAdvance(pLex, 1);
        XCTAssertFalse( (OBJ_NIL == pToken) );
        
        pToken = lex_TokenLookAhead(pLex, 1);
        XCTAssertFalse( (OBJ_NIL == pToken) );
        {
            pStr = Token_ToDataString(pToken);
            fprintf(stderr, "text=\"%s\"\n",  AStr_getData(pStr));
            obj_Release(pStr);
            pStr = OBJ_NIL;
        }
        XCTAssertTrue( (PPLEX_SEP_WHITESPACE == Token_getClass(pToken)) );
        pToken = lex_TokenAdvance(pLex, 1);
        XCTAssertFalse( (OBJ_NIL == pToken) );
        
        pToken = lex_TokenLookAhead(pLex, 1);
        XCTAssertFalse( (OBJ_NIL == pToken) );
        {
            pStr = Token_ToDataString(pToken);
            fprintf(stderr, "text=\"%s\"\n",  AStr_getData(pStr));
            obj_Release(pStr);
            pStr = OBJ_NIL;
        }
        XCTAssertTrue( (PPLEX_IDENTIFIER == Token_getClass(pToken)) );
        pStr = Token_ToDataString(pToken);
        XCTAssertTrue( (ERESULT_SUCCESS_EQUAL == AStr_CompareA(pStr, "xyz")) );
        obj_Release(pStr);
        pStr = OBJ_NIL;
        pToken = lex_TokenAdvance(pLex, 1);
        XCTAssertFalse( (OBJ_NIL == pToken) );
        
        pToken = lex_TokenLookAhead(pLex, 1);
        XCTAssertFalse( (OBJ_NIL == pToken) );
        XCTAssertTrue( (PPLEX_SEP_NL == Token_getClass(pToken)) );
        pToken = lex_TokenAdvance(pLex, 1);
        XCTAssertFalse( (OBJ_NIL == pToken) );

        // 3rd Line - "@end\n"
        pToken = lex_TokenLookAhead(pLex, 1);
        XCTAssertFalse( (OBJ_NIL == pToken) );
        pStr = Token_ToDataString(pToken);
        fprintf(stderr, "@end class = %s\n", pplex_ClassToString(Token_getClass(pToken)));
        fprintf(stderr, "@end string = \"%s\"\n", AStr_getData(pStr));
        XCTAssertTrue( (PPLEX_KWD_AT_END == Token_getClass(pToken)) );
        XCTAssertTrue( (ERESULT_SUCCESS_EQUAL == AStr_CompareA(pStr, "@end")) );
        obj_Release(pStr);
        pStr = OBJ_NIL;
        pToken = lex_TokenAdvance(pLex, 1);
        XCTAssertFalse( (OBJ_NIL == pToken) );
        
        pToken = lex_TokenLookAhead(pLex, 1);
        XCTAssertFalse( (OBJ_NIL == pToken) );
        XCTAssertTrue( (PPLEX_SEP_NL == Token_getClass(pToken)) );
        pToken = lex_TokenAdvance(pLex, 1);
        XCTAssertFalse( (OBJ_NIL == pToken) );
        
        obj_Release(pLex);
        pLex = OBJ_NIL;
            
        obj_Release(pBuf);
        pBuf = OBJ_NIL;
    }
    
    obj_Release(pPath);
    pPath = OBJ_NIL;
    
    cls = SrcErrors_getNumErrors(SrcErrors_Shared());
    if (cls) {
        fprintf(stderr, "\n\n\n\t%d ERRORS Occurred:\n", cls);
        pStr = SrcErrors_ToDebugString(SrcErrors_Shared(), 0);
        if (pStr) {
            fprintf(stderr, "\t%s\n", AStr_getData(pStr));
            obj_Release(pStr);
            pStr = OBJ_NIL;
        }
    }
    
    fprintf(stderr, "...%s completed.\n\n", pTestName);
    return 1;
}



int         test_pplex_Input02(
    const
    char        *pTestName
)
{
    LEX_DATA        *pLex = OBJ_NIL;
    TOKEN_DATA      *pToken;
    PATH_DATA       *pPath = path_NewA("~/Support/ll1/tests/test_gmr01.txt");
    ASTR_DATA       *pStr = OBJ_NIL;
    ERESULT         eRc;
    int32_t         cls;
    
    fprintf(stderr, "Performing: %s\n", pTestName);
    
    pLex = (LEX_DATA *)pplex_New(4);
    XCTAssertFalse( (OBJ_NIL == pLex) );
    if (OBJ_NIL == pLex) {
        return 0;
    }
        
    pplex_setReturnNL((PPLEX_DATA *)pLex, false);
    pplex_setReturnWS((PPLEX_DATA *)pLex, false);
    
    eRc = pplex_CreateLexers((PPLEX_DATA *)pLex, false, true);
    XCTAssertFalse( (ERESULT_FAILED(eRc)) );
    
    path_Clean(pPath);
    eRc =   pplex_CreateSourceFromPath(
                                       (PPLEX_DATA *)pLex,
                                       pPath
            );
    XCTAssertFalse( (ERESULT_FAILED(eRc)) );
    
    pToken = lex_TokenLookAhead(pLex, 1);
    XCTAssertFalse( (OBJ_NIL == pToken) );
    {
        pStr = Token_ToDataString(pToken);
        fprintf(stderr, "token text=\"%s\"\n",
                AStr_getData(pStr));
        obj_Release(pStr);
        pStr = OBJ_NIL;
        fprintf(stderr, "token class = %s\n",
                pplex_ClassToString(Token_getClass(pToken)));
    }
    XCTAssertTrue( (PPLEX_KWD_TERM == Token_getClass(pToken)) );
    {
        pStr = Token_ToDataString(pToken);
        //FIXME: XCTAssertTrue( (ERESULT_SUCCESS_EQUAL == AStr_CompareA(pStr, "@interface")) );
        obj_Release(pStr);
        pStr = OBJ_NIL;
    }
    pToken = lex_TokenAdvance(pLex, 1);
    XCTAssertFalse( (OBJ_NIL == pToken) );
    
    pToken = lex_TokenLookAhead(pLex, 1);
    XCTAssertFalse( (OBJ_NIL == pToken) );
    {
        pStr = Token_ToDataString(pToken);
        fprintf(stderr, "text=\"%s\"\n",  AStr_getData(pStr));
        obj_Release(pStr);
        pStr = OBJ_NIL;
        fprintf(stderr, "token class = %s\n",
                pplex_ClassToString(Token_getClass(pToken)));
    }
    XCTAssertTrue( (PPLEX_IDENTIFIER == Token_getClass(pToken)) );
    {
        pStr = Token_ToDataString(pToken);
        XCTAssertTrue( (ERESULT_SUCCESS_EQUAL == AStr_CompareA(pStr, "a")) );
        obj_Release(pStr);
        pStr = OBJ_NIL;
    }
    pToken = lex_TokenAdvance(pLex, 1);
    XCTAssertFalse( (OBJ_NIL == pToken) );
    
    pToken = lex_TokenLookAhead(pLex, 1);
    XCTAssertFalse( (OBJ_NIL == pToken) );
    {
        pStr = Token_ToDataString(pToken);
        fprintf(stderr, "text=\"%s\"\n",  AStr_getData(pStr));
        obj_Release(pStr);
        pStr = OBJ_NIL;
        fprintf(stderr, "token class = %s\n",
                pplex_ClassToString(Token_getClass(pToken)));
    }
    XCTAssertTrue( (PPLEX_KWD_TERM == Token_getClass(pToken)) );
    pToken = lex_TokenAdvance(pLex, 1);
    XCTAssertFalse( (OBJ_NIL == pToken) );
    
    pToken = lex_TokenLookAhead(pLex, 1);
    XCTAssertFalse( (OBJ_NIL == pToken) );
    {
        pStr = Token_ToDataString(pToken);
        fprintf(stderr, "text=\"%s\"\n",  AStr_getData(pStr));
        obj_Release(pStr);
        pStr = OBJ_NIL;
        fprintf(stderr, "token class = %s\n",
                pplex_ClassToString(Token_getClass(pToken)));
    }
    XCTAssertTrue( (PPLEX_IDENTIFIER == Token_getClass(pToken)) );
    {
        pStr = Token_ToDataString(pToken);
        XCTAssertTrue( (ERESULT_SUCCESS_EQUAL == AStr_CompareA(pStr, "b")) );
        obj_Release(pStr);
        pStr = OBJ_NIL;
    }
    pToken = lex_TokenAdvance(pLex, 1);
    XCTAssertFalse( (OBJ_NIL == pToken) );
    
    pToken = lex_TokenLookAhead(pLex, 1);
    XCTAssertFalse( (OBJ_NIL == pToken) );
    {
        pStr = Token_ToDataString(pToken);
        fprintf(stderr, "text=\"%s\"\n",  AStr_getData(pStr));
        obj_Release(pStr);
        pStr = OBJ_NIL;
        fprintf(stderr, "token class = %s\n",
                pplex_ClassToString(Token_getClass(pToken)));
    }
    XCTAssertTrue( (PPLEX_KWD_TERM == Token_getClass(pToken)) );
    pToken = lex_TokenAdvance(pLex, 1);
    XCTAssertFalse( (OBJ_NIL == pToken) );
    
    pToken = lex_TokenLookAhead(pLex, 1);
    XCTAssertFalse( (OBJ_NIL == pToken) );
    {
        pStr = Token_ToDataString(pToken);
        fprintf(stderr, "text=\"%s\"\n",  AStr_getData(pStr));
        obj_Release(pStr);
        pStr = OBJ_NIL;
        fprintf(stderr, "token class = %s\n",
                pplex_ClassToString(Token_getClass(pToken)));
    }
    XCTAssertTrue( (PPLEX_IDENTIFIER == Token_getClass(pToken)) );
    {
        pStr = Token_ToDataString(pToken);
        XCTAssertTrue( (ERESULT_SUCCESS_EQUAL == AStr_CompareA(pStr, "c")) );
        obj_Release(pStr);
        pStr = OBJ_NIL;
    }
    pToken = lex_TokenAdvance(pLex, 1);
    XCTAssertFalse( (OBJ_NIL == pToken) );
    
    pToken = lex_TokenLookAhead(pLex, 1);
    XCTAssertFalse( (OBJ_NIL == pToken) );
    {
        pStr = Token_ToDataString(pToken);
        fprintf(stderr, "text=\"%s\"\n",  AStr_getData(pStr));
        obj_Release(pStr);
        pStr = OBJ_NIL;
        fprintf(stderr, "token class = %s\n",
                pplex_ClassToString(Token_getClass(pToken)));
    }
    XCTAssertTrue( (PPLEX_KWD_TERM == Token_getClass(pToken)) );
    pToken = lex_TokenAdvance(pLex, 1);
    XCTAssertFalse( (OBJ_NIL == pToken) );
    
    pToken = lex_TokenLookAhead(pLex, 1);
    XCTAssertFalse( (OBJ_NIL == pToken) );
    {
        pStr = Token_ToDataString(pToken);
        fprintf(stderr, "text=\"%s\"\n",  AStr_getData(pStr));
        obj_Release(pStr);
        pStr = OBJ_NIL;
        fprintf(stderr, "token class = %s\n",
                pplex_ClassToString(Token_getClass(pToken)));
    }
    XCTAssertTrue( (PPLEX_IDENTIFIER == Token_getClass(pToken)) );
    {
        pStr = Token_ToDataString(pToken);
        XCTAssertTrue( (ERESULT_SUCCESS_EQUAL == AStr_CompareA(pStr, "d")) );
        obj_Release(pStr);
        pStr = OBJ_NIL;
    }
    pToken = lex_TokenAdvance(pLex, 1);
    XCTAssertFalse( (OBJ_NIL == pToken) );
    
    pToken = lex_TokenLookAhead(pLex, 1);
    XCTAssertFalse( (OBJ_NIL == pToken) );
    {
        pStr = Token_ToDataString(pToken);
        fprintf(stderr, "text=\"%s\"\n",  AStr_getData(pStr));
        obj_Release(pStr);
        pStr = OBJ_NIL;
        fprintf(stderr, "token class = %s\n",
                pplex_ClassToString(Token_getClass(pToken)));
    }
    XCTAssertTrue( (PPLEX_KWD_TERM == Token_getClass(pToken)) );
    pToken = lex_TokenAdvance(pLex, 1);
    XCTAssertFalse( (OBJ_NIL == pToken) );
    
    pToken = lex_TokenLookAhead(pLex, 1);
    XCTAssertFalse( (OBJ_NIL == pToken) );
    {
        pStr = Token_ToDataString(pToken);
        fprintf(stderr, "text=\"%s\"\n",  AStr_getData(pStr));
        obj_Release(pStr);
        pStr = OBJ_NIL;
        fprintf(stderr, "token class = %s\n",
                pplex_ClassToString(Token_getClass(pToken)));
    }
    XCTAssertTrue( (PPLEX_IDENTIFIER == Token_getClass(pToken)) );
    {
        pStr = Token_ToDataString(pToken);
        XCTAssertTrue( (ERESULT_SUCCESS_EQUAL == AStr_CompareA(pStr, "e")) );
        obj_Release(pStr);
        pStr = OBJ_NIL;
    }
    pToken = lex_TokenAdvance(pLex, 1);
    XCTAssertFalse( (OBJ_NIL == pToken) );
    
    pToken = lex_TokenLookAhead(pLex, 1);
    XCTAssertFalse( (OBJ_NIL == pToken) );
    {
        pStr = Token_ToDataString(pToken);
        fprintf(stderr, "text=\"%s\"\n",  AStr_getData(pStr));
        obj_Release(pStr);
        pStr = OBJ_NIL;
        fprintf(stderr, "token class = %s\n",
                pplex_ClassToString(Token_getClass(pToken)));
    }
    XCTAssertTrue( (PPLEX_KWD_TERM == Token_getClass(pToken)) );
    pToken = lex_TokenAdvance(pLex, 1);
    XCTAssertFalse( (OBJ_NIL == pToken) );
    
    pToken = lex_TokenLookAhead(pLex, 1);
    XCTAssertFalse( (OBJ_NIL == pToken) );
    {
        pStr = Token_ToDataString(pToken);
        fprintf(stderr, "text=\"%s\"\n",  AStr_getData(pStr));
        obj_Release(pStr);
        pStr = OBJ_NIL;
        fprintf(stderr, "token class = %s\n",
                pplex_ClassToString(Token_getClass(pToken)));
    }
    XCTAssertTrue( (PPLEX_IDENTIFIER == Token_getClass(pToken)) );
    {
        pStr = Token_ToDataString(pToken);
        XCTAssertTrue( (ERESULT_SUCCESS_EQUAL == AStr_CompareA(pStr, "f")) );
        obj_Release(pStr);
        pStr = OBJ_NIL;
    }
    pToken = lex_TokenAdvance(pLex, 1);
    XCTAssertFalse( (OBJ_NIL == pToken) );
    
    pToken = lex_TokenLookAhead(pLex, 1);
    XCTAssertFalse( (OBJ_NIL == pToken) );
    {
        pStr = Token_ToDataString(pToken);
        fprintf(stderr, "text=\"%s\"\n",  AStr_getData(pStr));
        obj_Release(pStr);
        pStr = OBJ_NIL;
        fprintf(stderr, "token class = %s\n",
                pplex_ClassToString(Token_getClass(pToken)));
    }
    XCTAssertTrue( (PPLEX_SPCL_SEPARATOR == Token_getClass(pToken)) );
    pToken = lex_TokenAdvance(pLex, 1);
    XCTAssertFalse( (OBJ_NIL == pToken) );
    
    pToken = lex_TokenLookAhead(pLex, 1);
    XCTAssertFalse( (OBJ_NIL == pToken) );
    {
        pStr = Token_ToDataString(pToken);
        fprintf(stderr, "text=\"%s\"\n",  AStr_getData(pStr));
        obj_Release(pStr);
        pStr = OBJ_NIL;
        fprintf(stderr, "token class = %s\n",
                pplex_ClassToString(Token_getClass(pToken)));
    }
    XCTAssertTrue( (PPLEX_IDENTIFIER == Token_getClass(pToken)) );
    {
        pStr = Token_ToDataString(pToken);
        XCTAssertTrue( (ERESULT_SUCCESS_EQUAL == AStr_CompareA(pStr, "A")) );
        obj_Release(pStr);
        pStr = OBJ_NIL;
    }
    pToken = lex_TokenAdvance(pLex, 1);
    XCTAssertFalse( (OBJ_NIL == pToken) );
    
    pToken = lex_TokenLookAhead(pLex, 1);
    XCTAssertFalse( (OBJ_NIL == pToken) );
    {
        pStr = Token_ToDataString(pToken);
        fprintf(stderr, "text=\"%s\"\n",  AStr_getData(pStr));
        obj_Release(pStr);
        pStr = OBJ_NIL;
        fprintf(stderr, "token class = %s\n",
                pplex_ClassToString(Token_getClass(pToken)));
    }
    XCTAssertTrue( (PPLEX_SPCL_COLON == Token_getClass(pToken)) );
    pToken = lex_TokenAdvance(pLex, 1);
    XCTAssertFalse( (OBJ_NIL == pToken) );
    
    pToken = lex_TokenLookAhead(pLex, 1);
    XCTAssertFalse( (OBJ_NIL == pToken) );
    {
        pStr = Token_ToDataString(pToken);
        fprintf(stderr, "text=\"%s\"\n",  AStr_getData(pStr));
        obj_Release(pStr);
        pStr = OBJ_NIL;
        fprintf(stderr, "token class = %s\n",
                pplex_ClassToString(Token_getClass(pToken)));
    }
    XCTAssertTrue( (PPLEX_IDENTIFIER == Token_getClass(pToken)) );
    {
        pStr = Token_ToDataString(pToken);
        XCTAssertTrue( (ERESULT_SUCCESS_EQUAL == AStr_CompareA(pStr, "B")) );
        obj_Release(pStr);
        pStr = OBJ_NIL;
    }
    pToken = lex_TokenAdvance(pLex, 1);
    XCTAssertFalse( (OBJ_NIL == pToken) );
    
    pToken = lex_TokenLookAhead(pLex, 1);
    XCTAssertFalse( (OBJ_NIL == pToken) );
    {
        pStr = Token_ToDataString(pToken);
        fprintf(stderr, "text=\"%s\"\n",  AStr_getData(pStr));
        obj_Release(pStr);
        pStr = OBJ_NIL;
        fprintf(stderr, "token class = %s\n",
                pplex_ClassToString(Token_getClass(pToken)));
    }
    XCTAssertTrue( (PPLEX_IDENTIFIER == Token_getClass(pToken)) );
    {
        pStr = Token_ToDataString(pToken);
        XCTAssertTrue( (ERESULT_SUCCESS_EQUAL == AStr_CompareA(pStr, "C")) );
        obj_Release(pStr);
        pStr = OBJ_NIL;
    }
    pToken = lex_TokenAdvance(pLex, 1);
    XCTAssertFalse( (OBJ_NIL == pToken) );
    
    pToken = lex_TokenLookAhead(pLex, 1);
    XCTAssertFalse( (OBJ_NIL == pToken) );
    {
        pStr = Token_ToDataString(pToken);
        fprintf(stderr, "text=\"%s\"\n",  AStr_getData(pStr));
        obj_Release(pStr);
        pStr = OBJ_NIL;
        fprintf(stderr, "token class = %s\n",
                pplex_ClassToString(Token_getClass(pToken)));
    }
    XCTAssertTrue( (PPLEX_IDENTIFIER == Token_getClass(pToken)) );
    {
        pStr = Token_ToDataString(pToken);
        XCTAssertTrue( (ERESULT_SUCCESS_EQUAL == AStr_CompareA(pStr, "c")) );
        obj_Release(pStr);
        pStr = OBJ_NIL;
    }
    pToken = lex_TokenAdvance(pLex, 1);
    XCTAssertFalse( (OBJ_NIL == pToken) );
    
    pToken = lex_TokenLookAhead(pLex, 1);
    XCTAssertFalse( (OBJ_NIL == pToken) );
    {
        pStr = Token_ToDataString(pToken);
        fprintf(stderr, "text=\"%s\"\n",  AStr_getData(pStr));
        obj_Release(pStr);
        pStr = OBJ_NIL;
        fprintf(stderr, "token class = %s\n",
                pplex_ClassToString(Token_getClass(pToken)));
    }
    XCTAssertTrue( (PPLEX_OP_OR == Token_getClass(pToken)) );
    pToken = lex_TokenAdvance(pLex, 1);
    XCTAssertFalse( (OBJ_NIL == pToken) );
    
    pToken = lex_TokenLookAhead(pLex, 1);
    XCTAssertFalse( (OBJ_NIL == pToken) );
    {
        pStr = Token_ToDataString(pToken);
        fprintf(stderr, "text=\"%s\"\n",  AStr_getData(pStr));
        obj_Release(pStr);
        pStr = OBJ_NIL;
        fprintf(stderr, "token class = %s\n",
                pplex_ClassToString(Token_getClass(pToken)));
    }
    XCTAssertTrue( (PPLEX_IDENTIFIER == Token_getClass(pToken)) );
    {
        pStr = Token_ToDataString(pToken);
        XCTAssertTrue( (ERESULT_SUCCESS_EQUAL == AStr_CompareA(pStr, "e")) );
        obj_Release(pStr);
        pStr = OBJ_NIL;
    }
    pToken = lex_TokenAdvance(pLex, 1);
    XCTAssertFalse( (OBJ_NIL == pToken) );
    
    pToken = lex_TokenLookAhead(pLex, 1);
    XCTAssertFalse( (OBJ_NIL == pToken) );
    {
        pStr = Token_ToDataString(pToken);
        fprintf(stderr, "text=\"%s\"\n",  AStr_getData(pStr));
        obj_Release(pStr);
        pStr = OBJ_NIL;
        fprintf(stderr, "token class = %s\n",
                pplex_ClassToString(Token_getClass(pToken)));
    }
    XCTAssertTrue( (PPLEX_IDENTIFIER == Token_getClass(pToken)) );
    {
        pStr = Token_ToDataString(pToken);
        XCTAssertTrue( (ERESULT_SUCCESS_EQUAL == AStr_CompareA(pStr, "D")) );
        obj_Release(pStr);
        pStr = OBJ_NIL;
    }
    pToken = lex_TokenAdvance(pLex, 1);
    XCTAssertFalse( (OBJ_NIL == pToken) );
    
    pToken = lex_TokenLookAhead(pLex, 1);
    XCTAssertFalse( (OBJ_NIL == pToken) );
    {
        pStr = Token_ToDataString(pToken);
        fprintf(stderr, "text=\"%s\"\n",  AStr_getData(pStr));
        obj_Release(pStr);
        pStr = OBJ_NIL;
        fprintf(stderr, "token class = %s\n",
                pplex_ClassToString(Token_getClass(pToken)));
    }
    XCTAssertTrue( (PPLEX_IDENTIFIER == Token_getClass(pToken)) );
    {
        pStr = Token_ToDataString(pToken);
        XCTAssertTrue( (ERESULT_SUCCESS_EQUAL == AStr_CompareA(pStr, "B")) );
        obj_Release(pStr);
        pStr = OBJ_NIL;
    }
    pToken = lex_TokenAdvance(pLex, 1);
    XCTAssertFalse( (OBJ_NIL == pToken) );
    
    pToken = lex_TokenLookAhead(pLex, 1);
    XCTAssertFalse( (OBJ_NIL == pToken) );
    {
        pStr = Token_ToDataString(pToken);
        fprintf(stderr, "text=\"%s\"\n",  AStr_getData(pStr));
        obj_Release(pStr);
        pStr = OBJ_NIL;
        fprintf(stderr, "token class = %s\n",
                pplex_ClassToString(Token_getClass(pToken)));
    }
    XCTAssertTrue( (PPLEX_SEP_SEMICOLON == Token_getClass(pToken)) );
    pToken = lex_TokenAdvance(pLex, 1);
    XCTAssertFalse( (OBJ_NIL == pToken) );
    
    pToken = lex_TokenLookAhead(pLex, 1);
    XCTAssertFalse( (OBJ_NIL == pToken) );
    {
        pStr = Token_ToDataString(pToken);
        fprintf(stderr, "text=\"%s\"\n",  AStr_getData(pStr));
        obj_Release(pStr);
        pStr = OBJ_NIL;
        fprintf(stderr, "token class = %s\n",
                pplex_ClassToString(Token_getClass(pToken)));
    }
    XCTAssertTrue( (PPLEX_IDENTIFIER == Token_getClass(pToken)) );
    {
        pStr = Token_ToDataString(pToken);
        XCTAssertTrue( (ERESULT_SUCCESS_EQUAL == AStr_CompareA(pStr, "B")) );
        obj_Release(pStr);
        pStr = OBJ_NIL;
    }
    pToken = lex_TokenAdvance(pLex, 1);
    XCTAssertFalse( (OBJ_NIL == pToken) );
    
    pToken = lex_TokenLookAhead(pLex, 1);
    XCTAssertFalse( (OBJ_NIL == pToken) );
    {
        pStr = Token_ToDataString(pToken);
        fprintf(stderr, "text=\"%s\"\n",  AStr_getData(pStr));
        obj_Release(pStr);
        pStr = OBJ_NIL;
        fprintf(stderr, "token class = %s\n",
                pplex_ClassToString(Token_getClass(pToken)));
    }
    XCTAssertTrue( (PPLEX_SPCL_COLON == Token_getClass(pToken)) );
    pToken = lex_TokenAdvance(pLex, 1);
    XCTAssertFalse( (OBJ_NIL == pToken) );
    
    pToken = lex_TokenLookAhead(pLex, 1);
    XCTAssertFalse( (OBJ_NIL == pToken) );
    {
        pStr = Token_ToDataString(pToken);
        fprintf(stderr, "text=\"%s\"\n",  AStr_getData(pStr));
        obj_Release(pStr);
        pStr = OBJ_NIL;
        fprintf(stderr, "token class = %s\n",
                pplex_ClassToString(Token_getClass(pToken)));
    }
    XCTAssertTrue( (PPLEX_OP_OR == Token_getClass(pToken)) );
    pToken = lex_TokenAdvance(pLex, 1);
    XCTAssertFalse( (OBJ_NIL == pToken) );
    
    pToken = lex_TokenLookAhead(pLex, 1);
    XCTAssertFalse( (OBJ_NIL == pToken) );
    {
        pStr = Token_ToDataString(pToken);
        fprintf(stderr, "text=\"%s\"\n",  AStr_getData(pStr));
        obj_Release(pStr);
        pStr = OBJ_NIL;
        fprintf(stderr, "token class = %s\n",
                pplex_ClassToString(Token_getClass(pToken)));
    }
    XCTAssertTrue( (PPLEX_IDENTIFIER == Token_getClass(pToken)) );
    {
        pStr = Token_ToDataString(pToken);
        XCTAssertTrue( (ERESULT_SUCCESS_EQUAL == AStr_CompareA(pStr, "b")) );
        obj_Release(pStr);
        pStr = OBJ_NIL;
    }
    pToken = lex_TokenAdvance(pLex, 1);
    XCTAssertFalse( (OBJ_NIL == pToken) );
    
    pToken = lex_TokenLookAhead(pLex, 1);
    XCTAssertFalse( (OBJ_NIL == pToken) );
    {
        pStr = Token_ToDataString(pToken);
        fprintf(stderr, "text=\"%s\"\n",  AStr_getData(pStr));
        obj_Release(pStr);
        pStr = OBJ_NIL;
        fprintf(stderr, "token class = %s\n",
                pplex_ClassToString(Token_getClass(pToken)));
    }
    XCTAssertTrue( (PPLEX_IDENTIFIER == Token_getClass(pToken)) );
    {
        pStr = Token_ToDataString(pToken);
        //FIXME: XCTAssertTrue( (ERESULT_SUCCESS_EQUAL == AStr_CompareA(pStr, "C")) );
        obj_Release(pStr);
        pStr = OBJ_NIL;
    }
    pToken = lex_TokenAdvance(pLex, 1);
    XCTAssertFalse( (OBJ_NIL == pToken) );
    
    pToken = lex_TokenLookAhead(pLex, 1);
    XCTAssertFalse( (OBJ_NIL == pToken) );
    {
        pStr = Token_ToDataString(pToken);
        fprintf(stderr, "text=\"%s\"\n",  AStr_getData(pStr));
        obj_Release(pStr);
        pStr = OBJ_NIL;
        fprintf(stderr, "token class = %s\n",
                pplex_ClassToString(Token_getClass(pToken)));
    }
    XCTAssertTrue( (PPLEX_IDENTIFIER == Token_getClass(pToken)) );
    {
        pStr = Token_ToDataString(pToken);
        XCTAssertTrue( (ERESULT_SUCCESS_EQUAL == AStr_CompareA(pStr, "D")) );
        obj_Release(pStr);
        pStr = OBJ_NIL;
    }
    pToken = lex_TokenAdvance(pLex, 1);
    XCTAssertFalse( (OBJ_NIL == pToken) );
    
    pToken = lex_TokenLookAhead(pLex, 1);
    XCTAssertFalse( (OBJ_NIL == pToken) );
    {
        pStr = Token_ToDataString(pToken);
        fprintf(stderr, "text=\"%s\"\n",  AStr_getData(pStr));
        obj_Release(pStr);
        pStr = OBJ_NIL;
        fprintf(stderr, "token class = %s\n",
                pplex_ClassToString(Token_getClass(pToken)));
    }
    XCTAssertTrue( (PPLEX_IDENTIFIER == Token_getClass(pToken)) );
    {
        pStr = Token_ToDataString(pToken);
        XCTAssertTrue( (ERESULT_SUCCESS_EQUAL == AStr_CompareA(pStr, "E")) );
        obj_Release(pStr);
        pStr = OBJ_NIL;
    }
    pToken = lex_TokenAdvance(pLex, 1);
    XCTAssertFalse( (OBJ_NIL == pToken) );
    
    pToken = lex_TokenLookAhead(pLex, 1);
    XCTAssertFalse( (OBJ_NIL == pToken) );
    {
        pStr = Token_ToDataString(pToken);
        fprintf(stderr, "text=\"%s\"\n",  AStr_getData(pStr));
        obj_Release(pStr);
        pStr = OBJ_NIL;
        fprintf(stderr, "token class = %s\n",
                pplex_ClassToString(Token_getClass(pToken)));
    }
    XCTAssertTrue( (PPLEX_SEP_SEMICOLON == Token_getClass(pToken)) );
    pToken = lex_TokenAdvance(pLex, 1);
    XCTAssertFalse( (OBJ_NIL == pToken) );
    
    pToken = lex_TokenLookAhead(pLex, 1);
    XCTAssertFalse( (OBJ_NIL == pToken) );
    {
        pStr = Token_ToDataString(pToken);
        fprintf(stderr, "text=\"%s\"\n",  AStr_getData(pStr));
        obj_Release(pStr);
        pStr = OBJ_NIL;
        fprintf(stderr, "token class = %s\n",
                pplex_ClassToString(Token_getClass(pToken)));
    }
    XCTAssertTrue( (PPLEX_IDENTIFIER == Token_getClass(pToken)) );
    {
        pStr = Token_ToDataString(pToken);
        XCTAssertTrue( (ERESULT_SUCCESS_EQUAL == AStr_CompareA(pStr, "C")) );
        obj_Release(pStr);
        pStr = OBJ_NIL;
    }
    pToken = lex_TokenAdvance(pLex, 1);
    XCTAssertFalse( (OBJ_NIL == pToken) );
    
    pToken = lex_TokenLookAhead(pLex, 1);
    XCTAssertFalse( (OBJ_NIL == pToken) );
    {
        pStr = Token_ToDataString(pToken);
        fprintf(stderr, "text=\"%s\"\n",  AStr_getData(pStr));
        obj_Release(pStr);
        pStr = OBJ_NIL;
        fprintf(stderr, "token class = %s\n",
                pplex_ClassToString(Token_getClass(pToken)));
    }
    XCTAssertTrue( (PPLEX_SPCL_COLON == Token_getClass(pToken)) );
    pToken = lex_TokenAdvance(pLex, 1);
    XCTAssertFalse( (OBJ_NIL == pToken) );
    
    pToken = lex_TokenLookAhead(pLex, 1);
    XCTAssertFalse( (OBJ_NIL == pToken) );
    {
        pStr = Token_ToDataString(pToken);
        fprintf(stderr, "text=\"%s\"\n",  AStr_getData(pStr));
        obj_Release(pStr);
        pStr = OBJ_NIL;
        fprintf(stderr, "token class = %s\n",
                pplex_ClassToString(Token_getClass(pToken)));
    }
    XCTAssertTrue( (PPLEX_IDENTIFIER == Token_getClass(pToken)) );
    {
        pStr = Token_ToDataString(pToken);
        XCTAssertTrue( (ERESULT_SUCCESS_EQUAL == AStr_CompareA(pStr, "D")) );
        obj_Release(pStr);
        pStr = OBJ_NIL;
    }
    pToken = lex_TokenAdvance(pLex, 1);
    XCTAssertFalse( (OBJ_NIL == pToken) );
    
    pToken = lex_TokenLookAhead(pLex, 1);
    XCTAssertFalse( (OBJ_NIL == pToken) );
    {
        pStr = Token_ToDataString(pToken);
        fprintf(stderr, "text=\"%s\"\n",  AStr_getData(pStr));
        obj_Release(pStr);
        pStr = OBJ_NIL;
        fprintf(stderr, "token class = %s\n",
                pplex_ClassToString(Token_getClass(pToken)));
    }
    XCTAssertTrue( (PPLEX_IDENTIFIER == Token_getClass(pToken)) );
    {
        pStr = Token_ToDataString(pToken);
        XCTAssertTrue( (ERESULT_SUCCESS_EQUAL == AStr_CompareA(pStr, "a")) );
        obj_Release(pStr);
        pStr = OBJ_NIL;
    }
    pToken = lex_TokenAdvance(pLex, 1);
    XCTAssertFalse( (OBJ_NIL == pToken) );
    
    pToken = lex_TokenLookAhead(pLex, 1);
    XCTAssertFalse( (OBJ_NIL == pToken) );
    {
        pStr = Token_ToDataString(pToken);
        fprintf(stderr, "text=\"%s\"\n",  AStr_getData(pStr));
        obj_Release(pStr);
        pStr = OBJ_NIL;
        fprintf(stderr, "token class = %s\n",
                pplex_ClassToString(Token_getClass(pToken)));
    }
    XCTAssertTrue( (PPLEX_IDENTIFIER == Token_getClass(pToken)) );
    {
        pStr = Token_ToDataString(pToken);
        XCTAssertTrue( (ERESULT_SUCCESS_EQUAL == AStr_CompareA(pStr, "B")) );
        obj_Release(pStr);
        pStr = OBJ_NIL;
    }
    pToken = lex_TokenAdvance(pLex, 1);
    XCTAssertFalse( (OBJ_NIL == pToken) );
    
    pToken = lex_TokenLookAhead(pLex, 1);
    XCTAssertFalse( (OBJ_NIL == pToken) );
    {
        pStr = Token_ToDataString(pToken);
        fprintf(stderr, "text=\"%s\"\n",  AStr_getData(pStr));
        obj_Release(pStr);
        pStr = OBJ_NIL;
        fprintf(stderr, "token class = %s\n",
                pplex_ClassToString(Token_getClass(pToken)));
    }
    XCTAssertTrue( (PPLEX_OP_OR == Token_getClass(pToken)) );
    pToken = lex_TokenAdvance(pLex, 1);
    XCTAssertFalse( (OBJ_NIL == pToken) );
    
    pToken = lex_TokenLookAhead(pLex, 1);
    XCTAssertFalse( (OBJ_NIL == pToken) );
    {
        pStr = Token_ToDataString(pToken);
        fprintf(stderr, "text=\"%s\"\n",  AStr_getData(pStr));
        obj_Release(pStr);
        pStr = OBJ_NIL;
        fprintf(stderr, "token class = %s\n",
                pplex_ClassToString(Token_getClass(pToken)));
    }
    XCTAssertTrue( (PPLEX_IDENTIFIER == Token_getClass(pToken)) );
    {
        pStr = Token_ToDataString(pToken);
        XCTAssertTrue( (ERESULT_SUCCESS_EQUAL == AStr_CompareA(pStr, "c")) );
        obj_Release(pStr);
        pStr = OBJ_NIL;
    }
    pToken = lex_TokenAdvance(pLex, 1);
    XCTAssertFalse( (OBJ_NIL == pToken) );
    
    pToken = lex_TokenLookAhead(pLex, 1);
    XCTAssertFalse( (OBJ_NIL == pToken) );
    {
        pStr = Token_ToDataString(pToken);
        fprintf(stderr, "text=\"%s\"\n",  AStr_getData(pStr));
        obj_Release(pStr);
        pStr = OBJ_NIL;
        fprintf(stderr, "token class = %s\n",
                pplex_ClassToString(Token_getClass(pToken)));
    }
    XCTAssertTrue( (PPLEX_IDENTIFIER == Token_getClass(pToken)) );
    {
        pStr = Token_ToDataString(pToken);
        XCTAssertTrue( (ERESULT_SUCCESS_EQUAL == AStr_CompareA(pStr, "a")) );
        obj_Release(pStr);
        pStr = OBJ_NIL;
    }
    pToken = lex_TokenAdvance(pLex, 1);
    XCTAssertFalse( (OBJ_NIL == pToken) );
    
    pToken = lex_TokenLookAhead(pLex, 1);
    XCTAssertFalse( (OBJ_NIL == pToken) );
    {
        pStr = Token_ToDataString(pToken);
        fprintf(stderr, "text=\"%s\"\n",  AStr_getData(pStr));
        obj_Release(pStr);
        pStr = OBJ_NIL;
        fprintf(stderr, "token class = %s\n",
                pplex_ClassToString(Token_getClass(pToken)));
    }
    XCTAssertTrue( (PPLEX_SEP_SEMICOLON == Token_getClass(pToken)) );
    pToken = lex_TokenAdvance(pLex, 1);
    XCTAssertFalse( (OBJ_NIL == pToken) );
    
    pToken = lex_TokenLookAhead(pLex, 1);
    XCTAssertFalse( (OBJ_NIL == pToken) );
    {
        pStr = Token_ToDataString(pToken);
        fprintf(stderr, "text=\"%s\"\n",  AStr_getData(pStr));
        obj_Release(pStr);
        pStr = OBJ_NIL;
        fprintf(stderr, "token class = %s\n",
                pplex_ClassToString(Token_getClass(pToken)));
    }
    XCTAssertTrue( (PPLEX_IDENTIFIER == Token_getClass(pToken)) );
    {
        pStr = Token_ToDataString(pToken);
        XCTAssertTrue( (ERESULT_SUCCESS_EQUAL == AStr_CompareA(pStr, "D")) );
        obj_Release(pStr);
        pStr = OBJ_NIL;
    }
    pToken = lex_TokenAdvance(pLex, 1);
    XCTAssertFalse( (OBJ_NIL == pToken) );
    
    pToken = lex_TokenLookAhead(pLex, 1);
    XCTAssertFalse( (OBJ_NIL == pToken) );
    {
        pStr = Token_ToDataString(pToken);
        fprintf(stderr, "text=\"%s\"\n",  AStr_getData(pStr));
        obj_Release(pStr);
        pStr = OBJ_NIL;
        fprintf(stderr, "token class = %s\n",
                pplex_ClassToString(Token_getClass(pToken)));
    }
    XCTAssertTrue( (PPLEX_SPCL_COLON == Token_getClass(pToken)) );
    pToken = lex_TokenAdvance(pLex, 1);
    XCTAssertFalse( (OBJ_NIL == pToken) );
    
    pToken = lex_TokenLookAhead(pLex, 1);
    XCTAssertFalse( (OBJ_NIL == pToken) );
    {
        pStr = Token_ToDataString(pToken);
        fprintf(stderr, "text=\"%s\"\n",  AStr_getData(pStr));
        obj_Release(pStr);
        pStr = OBJ_NIL;
        fprintf(stderr, "token class = %s\n",
                pplex_ClassToString(Token_getClass(pToken)));
    }
    XCTAssertTrue( (PPLEX_OP_OR == Token_getClass(pToken)) );
    pToken = lex_TokenAdvance(pLex, 1);
    XCTAssertFalse( (OBJ_NIL == pToken) );
    
    pToken = lex_TokenLookAhead(pLex, 1);
    XCTAssertFalse( (OBJ_NIL == pToken) );
    {
        pStr = Token_ToDataString(pToken);
        fprintf(stderr, "text=\"%s\"\n",  AStr_getData(pStr));
        obj_Release(pStr);
        pStr = OBJ_NIL;
        fprintf(stderr, "token class = %s\n",
                pplex_ClassToString(Token_getClass(pToken)));
    }
    XCTAssertTrue( (PPLEX_IDENTIFIER == Token_getClass(pToken)) );
    {
        pStr = Token_ToDataString(pToken);
        XCTAssertTrue( (ERESULT_SUCCESS_EQUAL == AStr_CompareA(pStr, "d")) );
        obj_Release(pStr);
        pStr = OBJ_NIL;
    }
    pToken = lex_TokenAdvance(pLex, 1);
    XCTAssertFalse( (OBJ_NIL == pToken) );
    
    pToken = lex_TokenLookAhead(pLex, 1);
    XCTAssertFalse( (OBJ_NIL == pToken) );
    {
        pStr = Token_ToDataString(pToken);
        fprintf(stderr, "text=\"%s\"\n",  AStr_getData(pStr));
        obj_Release(pStr);
        pStr = OBJ_NIL;
        fprintf(stderr, "token class = %s\n",
                pplex_ClassToString(Token_getClass(pToken)));
    }
    XCTAssertTrue( (PPLEX_IDENTIFIER == Token_getClass(pToken)) );
    {
        pStr = Token_ToDataString(pToken);
        XCTAssertTrue( (ERESULT_SUCCESS_EQUAL == AStr_CompareA(pStr, "D")) );
        obj_Release(pStr);
        pStr = OBJ_NIL;
    }
    pToken = lex_TokenAdvance(pLex, 1);
    XCTAssertFalse( (OBJ_NIL == pToken) );
    
    pToken = lex_TokenLookAhead(pLex, 1);
    XCTAssertFalse( (OBJ_NIL == pToken) );
    {
        pStr = Token_ToDataString(pToken);
        fprintf(stderr, "text=\"%s\"\n",  AStr_getData(pStr));
        obj_Release(pStr);
        pStr = OBJ_NIL;
        fprintf(stderr, "token class = %s\n",
                pplex_ClassToString(Token_getClass(pToken)));
    }
    XCTAssertTrue( (PPLEX_SEP_SEMICOLON == Token_getClass(pToken)) );
    pToken = lex_TokenAdvance(pLex, 1);
    XCTAssertFalse( (OBJ_NIL == pToken) );
    
    pToken = lex_TokenLookAhead(pLex, 1);
    XCTAssertFalse( (OBJ_NIL == pToken) );
    {
        pStr = Token_ToDataString(pToken);
        fprintf(stderr, "text=\"%s\"\n",  AStr_getData(pStr));
        obj_Release(pStr);
        pStr = OBJ_NIL;
        fprintf(stderr, "token class = %s\n",
                pplex_ClassToString(Token_getClass(pToken)));
    }
    XCTAssertTrue( (PPLEX_IDENTIFIER == Token_getClass(pToken)) );
    {
        pStr = Token_ToDataString(pToken);
        XCTAssertTrue( (ERESULT_SUCCESS_EQUAL == AStr_CompareA(pStr, "E")) );
        obj_Release(pStr);
        pStr = OBJ_NIL;
    }
    pToken = lex_TokenAdvance(pLex, 1);
    XCTAssertFalse( (OBJ_NIL == pToken) );
    
    pToken = lex_TokenLookAhead(pLex, 1);
    XCTAssertFalse( (OBJ_NIL == pToken) );
    {
        pStr = Token_ToDataString(pToken);
        fprintf(stderr, "text=\"%s\"\n",  AStr_getData(pStr));
        obj_Release(pStr);
        pStr = OBJ_NIL;
        fprintf(stderr, "token class = %s\n",
                pplex_ClassToString(Token_getClass(pToken)));
    }
    XCTAssertTrue( (PPLEX_SPCL_COLON == Token_getClass(pToken)) );
    pToken = lex_TokenAdvance(pLex, 1);
    XCTAssertFalse( (OBJ_NIL == pToken) );
    
    pToken = lex_TokenLookAhead(pLex, 1);
    XCTAssertFalse( (OBJ_NIL == pToken) );
    {
        pStr = Token_ToDataString(pToken);
        fprintf(stderr, "text=\"%s\"\n",  AStr_getData(pStr));
        obj_Release(pStr);
        pStr = OBJ_NIL;
        fprintf(stderr, "token class = %s\n",
                pplex_ClassToString(Token_getClass(pToken)));
    }
    XCTAssertTrue( (PPLEX_IDENTIFIER == Token_getClass(pToken)) );
    {
        pStr = Token_ToDataString(pToken);
        XCTAssertTrue( (ERESULT_SUCCESS_EQUAL == AStr_CompareA(pStr, "e")) );
        obj_Release(pStr);
        pStr = OBJ_NIL;
    }
    pToken = lex_TokenAdvance(pLex, 1);
    XCTAssertFalse( (OBJ_NIL == pToken) );
    
    pToken = lex_TokenLookAhead(pLex, 1);
    XCTAssertFalse( (OBJ_NIL == pToken) );
    {
        pStr = Token_ToDataString(pToken);
        fprintf(stderr, "text=\"%s\"\n",  AStr_getData(pStr));
        obj_Release(pStr);
        pStr = OBJ_NIL;
        fprintf(stderr, "token class = %s\n",
                pplex_ClassToString(Token_getClass(pToken)));
    }
    XCTAssertTrue( (PPLEX_IDENTIFIER == Token_getClass(pToken)) );
    {
        pStr = Token_ToDataString(pToken);
        XCTAssertTrue( (ERESULT_SUCCESS_EQUAL == AStr_CompareA(pStr, "A")) );
        obj_Release(pStr);
        pStr = OBJ_NIL;
    }
    pToken = lex_TokenAdvance(pLex, 1);
    XCTAssertFalse( (OBJ_NIL == pToken) );
    
    pToken = lex_TokenLookAhead(pLex, 1);
    XCTAssertFalse( (OBJ_NIL == pToken) );
    {
        pStr = Token_ToDataString(pToken);
        fprintf(stderr, "text=\"%s\"\n",  AStr_getData(pStr));
        obj_Release(pStr);
        pStr = OBJ_NIL;
        fprintf(stderr, "token class = %s\n",
                pplex_ClassToString(Token_getClass(pToken)));
    }
    XCTAssertTrue( (PPLEX_IDENTIFIER == Token_getClass(pToken)) );
    {
        pStr = Token_ToDataString(pToken);
        XCTAssertTrue( (ERESULT_SUCCESS_EQUAL == AStr_CompareA(pStr, "f")) );
        obj_Release(pStr);
        pStr = OBJ_NIL;
    }
    pToken = lex_TokenAdvance(pLex, 1);
    XCTAssertFalse( (OBJ_NIL == pToken) );
    
    pToken = lex_TokenLookAhead(pLex, 1);
    XCTAssertFalse( (OBJ_NIL == pToken) );
    {
        pStr = Token_ToDataString(pToken);
        fprintf(stderr, "text=\"%s\"\n",  AStr_getData(pStr));
        obj_Release(pStr);
        pStr = OBJ_NIL;
        fprintf(stderr, "token class = %s\n",
                pplex_ClassToString(Token_getClass(pToken)));
    }
    XCTAssertTrue( (PPLEX_OP_OR == Token_getClass(pToken)) );
    pToken = lex_TokenAdvance(pLex, 1);
    XCTAssertFalse( (OBJ_NIL == pToken) );
    
    pToken = lex_TokenLookAhead(pLex, 1);
    XCTAssertFalse( (OBJ_NIL == pToken) );
    {
        pStr = Token_ToDataString(pToken);
        fprintf(stderr, "text=\"%s\"\n",  AStr_getData(pStr));
        obj_Release(pStr);
        pStr = OBJ_NIL;
        fprintf(stderr, "token class = %s\n",
                pplex_ClassToString(Token_getClass(pToken)));
    }
    XCTAssertTrue( (PPLEX_IDENTIFIER == Token_getClass(pToken)) );
    {
        pStr = Token_ToDataString(pToken);
        XCTAssertTrue( (ERESULT_SUCCESS_EQUAL == AStr_CompareA(pStr, "c")) );
        obj_Release(pStr);
        pStr = OBJ_NIL;
    }
    pToken = lex_TokenAdvance(pLex, 1);
    XCTAssertFalse( (OBJ_NIL == pToken) );
    
    pToken = lex_TokenLookAhead(pLex, 1);
    XCTAssertFalse( (OBJ_NIL == pToken) );
    {
        pStr = Token_ToDataString(pToken);
        fprintf(stderr, "text=\"%s\"\n",  AStr_getData(pStr));
        obj_Release(pStr);
        pStr = OBJ_NIL;
        fprintf(stderr, "token class = %s\n",
                pplex_ClassToString(Token_getClass(pToken)));
    }
    XCTAssertTrue( (PPLEX_SEP_SEMICOLON == Token_getClass(pToken)) );
    pToken = lex_TokenAdvance(pLex, 1);
    XCTAssertFalse( (OBJ_NIL == pToken) );
    
    pToken = lex_TokenLookAhead(pLex, 1);
    XCTAssertFalse( (OBJ_NIL == pToken) );
    {
        pStr = Token_ToDataString(pToken);
        fprintf(stderr, "text=\"%s\"\n",  AStr_getData(pStr));
        obj_Release(pStr);
        pStr = OBJ_NIL;
        fprintf(stderr, "token class = %s\n",
                pplex_ClassToString(Token_getClass(pToken)));
    }
    XCTAssertTrue( (PPLEX_SPCL_SEPARATOR == Token_getClass(pToken)) );
    pToken = lex_TokenAdvance(pLex, 1);
    XCTAssertFalse( (OBJ_NIL == pToken) );
    
   pToken = lex_TokenLookAhead(pLex, 1);
    XCTAssertFalse( (OBJ_NIL == pToken) );
    {
        pStr = Token_ToDataString(pToken);
        fprintf(stderr, "text=\"%s\"\n",  AStr_getData(pStr));
        obj_Release(pStr);
        pStr = OBJ_NIL;
        fprintf(stderr, "token class = %s\n",
                pplex_ClassToString(Token_getClass(pToken)));
    }
    XCTAssertTrue( (PPLEX_CLASS_EOF == Token_getClass(pToken)) );
    pToken = lex_TokenAdvance(pLex, 1);
    XCTAssertFalse( (OBJ_NIL == pToken) );
    
    obj_Release(pLex);
    pLex = OBJ_NIL;
        
    obj_Release(pPath);
    pPath = OBJ_NIL;
    
    cls = SrcErrors_getNumErrors(SrcErrors_Shared());
    if (cls) {
        fprintf(stderr, "\n\n\n\t%d ERRORS Occurred:\n", cls);
        pStr = SrcErrors_ToDebugString(SrcErrors_Shared(), 0);
        if (pStr) {
            fprintf(stderr, "\t%s\n", AStr_getData(pStr));
            obj_Release(pStr);
            pStr = OBJ_NIL;
        }
    }
    
    fprintf(stderr, "...%s completed.\n\n", pTestName);
    return 1;
}




TINYTEST_START_SUITE(test_pplex);
    TINYTEST_ADD_TEST(test_pplex_Input02,setUp,tearDown);
    TINYTEST_ADD_TEST(test_pplex_Input01,setUp,tearDown);
    TINYTEST_ADD_TEST(test_pplex_OpenClose,setUp,tearDown);
TINYTEST_END_SUITE();

TINYTEST_MAIN_SINGLE_SUITE(test_pplex);





