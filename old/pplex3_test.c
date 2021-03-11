// vi: nu:noai:ts=4:sw=4

/*
 *	Generated 08/21/2017 13:03:31
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
#include    <pplex3_internal.h>
#include    <pplex.h>
#include    <szTbl.h>
#include    <srcFile.h>
#include    <wchar.h>



static
const
char        *pTestInput01 =
"@interface xyz\n"
//"@property int a;\n"
"@end\n";



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
    if (mem_Dump( ) ) {
        fprintf(
                stderr,
                "\x1b[1m"
                "\x1b[31m"
                "ERROR: "
                "\x1b[0m"
                "Leaked memory areas were found!\n"
                );
        exitCode = 4;
        return 0;
    }
    mem_Release( );

    return 1; 
}






int         test_pplex3_OpenClose(
    const
    char        *pTestName
)
{
    PPLEX3_DATA	*pObj = OBJ_NIL;
   
    fprintf(stderr, "Performing: %s\n", pTestName);
    pObj = pplex3_Alloc( );
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    pObj = pplex3_Init(pObj, 4);
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    if (pObj) {

        // Test something.

        obj_Release(pObj);
        pObj = OBJ_NIL;
    }

    fprintf(stderr, "...%s completed.\n", pTestName);
    return 1;
}



int         test_pplex3_Input01(
    const
    char        *pTestName
)
{
    SRCFILE_DATA	*pSrc = OBJ_NIL;
    ASTR_DATA       *pBuf = OBJ_NIL;
    LEX_DATA        *pLex3 = OBJ_NIL;
    LEX_DATA        *pLex2 = OBJ_NIL;
    TOKEN_DATA      *pToken;
    bool            fRc;
    PATH_DATA       *pPath = Path_NewA("abc");
    ASTR_DATA       *pStr = OBJ_NIL;
    
    fprintf(stderr, "Performing: %s\n", pTestName);
    pBuf =  AStr_NewA(
                "@interface xyz\n"
                //"@property int a;\n"
                "@end\n"            
            );
    XCTAssertFalse( (OBJ_NIL == pBuf) );
    if (pBuf) {
        
        pSrc = srcFile_NewFromAStr(pPath, pBuf, 1, 4);
        XCTAssertFalse( (OBJ_NIL == pSrc) );
        if (pSrc) {
            
            pLex2 = (LEX_DATA *)pplex2_New(4);
            XCTAssertFalse( (OBJ_NIL == pLex2) );
            if (OBJ_NIL == pLex2) {
                return 0;
            }
            pplex2_setReturnNL((PPLEX2_DATA *)pLex2, true);
            pplex2_setReturnWS((PPLEX2_DATA *)pLex2, true);
            obj_TraceSet(pLex2, true);
            
            fRc = pplex2_setKwdSelection((PPLEX2_DATA *)pLex2, -1);
            XCTAssertTrue( (fRc) );
            
            fRc =   lex_setSourceFunction(
                                          pLex2,
                                          (void *)srcFile_InputAdvance,
                                          (void *)srcFile_InputLookAhead,
                                          pSrc
                    );
            XCTAssertTrue( (fRc) );
            
            pLex3 = (LEX_DATA *)pplex3_New(4);
            XCTAssertFalse( (OBJ_NIL == pLex3) );
            if (OBJ_NIL == pLex3) {
                return 0;
            }
            
            obj_TraceSet(pLex3, true);
            fRc = pplex3_setKwdSelection((PPLEX3_DATA *)pLex3, -1);
            XCTAssertTrue( (fRc) );
            
            fRc =   lex_setSourceFunction(
                                          pLex3,
                                          (void *)lex_TokenAdvance,
                                          (void *)lex_TokenLookAhead,
                                          pLex2
                    );
            XCTAssertTrue( (fRc) );
            
            // 1st Line - "@interface xyz\n"
            pToken = lex_TokenLookAhead(pLex3, 1);
            XCTAssertFalse( (OBJ_NIL == pToken) );
            {
                pStr = Token_ToDataString(pToken);
                fprintf(stderr, "text=\"%s\"\n",  AStr_getData(pStr));
                obj_Release(pStr);
                pStr = OBJ_NIL;
            }
            XCTAssertTrue( (PPLEX_KWD_AT_INTERFACE == Token_getClass(pToken)) );
            pStr = Token_ToDataString(pToken);
            XCTAssertTrue( (ERESULT_SUCCESS_EQUAL == AStr_CompareA(pStr, "@interface")) );
            obj_Release(pStr);
            pStr = OBJ_NIL;
            pToken = lex_TokenAdvance(pLex3, 1);
            XCTAssertFalse( (OBJ_NIL == pToken) );
            
            pToken = lex_TokenLookAhead(pLex3, 1);
            XCTAssertFalse( (OBJ_NIL == pToken) );
            {
                pStr = Token_ToDataString(pToken);
                fprintf(stderr, "text=\"%s\"\n",  AStr_getData(pStr));
                obj_Release(pStr);
                pStr = OBJ_NIL;
            }
            XCTAssertTrue( (PPLEX_SEP_WHITESPACE == Token_getClass(pToken)) );
            pToken = lex_TokenAdvance(pLex3, 1);
            XCTAssertFalse( (OBJ_NIL == pToken) );
            
            pToken = lex_TokenLookAhead(pLex3, 1);
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
            pToken = lex_TokenAdvance(pLex3, 1);
            XCTAssertFalse( (OBJ_NIL == pToken) );
            
            pToken = lex_TokenLookAhead(pLex3, 1);
            XCTAssertFalse( (OBJ_NIL == pToken) );
            XCTAssertTrue( (PPLEX_SEP_NL == Token_getClass(pToken)) );
            pToken = lex_TokenAdvance(pLex3, 1);
            XCTAssertFalse( (OBJ_NIL == pToken) );

            // 3rd Line - "@end\n"
            pToken = lex_TokenLookAhead(pLex3, 1);
            XCTAssertFalse( (OBJ_NIL == pToken) );
            pStr = Token_ToDataString(pToken);
            fprintf(stderr, "@end class = %s\n", pplex_ClassToString(Token_getClass(pToken)));
            fprintf(stderr, "@end string = \"%s\"\n", AStr_getData(pStr));
            XCTAssertTrue( (PPLEX_KWD_AT_END == Token_getClass(pToken)) );
            XCTAssertTrue( (ERESULT_SUCCESS_EQUAL == AStr_CompareA(pStr, "@end")) );
            obj_Release(pStr);
            pStr = OBJ_NIL;
            pToken = lex_TokenAdvance(pLex3, 1);
            XCTAssertFalse( (OBJ_NIL == pToken) );
            
            pToken = lex_TokenLookAhead(pLex3, 1);
            XCTAssertFalse( (OBJ_NIL == pToken) );
            XCTAssertTrue( (PPLEX_SEP_NL == Token_getClass(pToken)) );
            pToken = lex_TokenAdvance(pLex3, 1);
            XCTAssertFalse( (OBJ_NIL == pToken) );
            
            obj_Release(pLex3);
            pLex3 = OBJ_NIL;
            
            obj_Release(pLex2);
            pLex2 = OBJ_NIL;
        }
        
        obj_Release(pSrc);
        pSrc = OBJ_NIL;

        obj_Release(pBuf);
        pBuf = OBJ_NIL;
    }
    
    obj_Release(pPath);
    pPath = OBJ_NIL;
    fprintf(stderr, "...%s completed.\n", pTestName);
    return 1;
}



int         test_pplex3_Input02(
    const
    char        *pTestName
)
{
    SRCFILE_DATA	*pSrc = OBJ_NIL;
    ASTR_DATA       *pBuf = OBJ_NIL;
    LEX_DATA        *pLex3 = OBJ_NIL;
    LEX_DATA        *pLex2 = OBJ_NIL;
    TOKEN_DATA      *pToken;
    bool            fRc;
    PATH_DATA       *pPath = Path_NewA("abc");
    ASTR_DATA       *pStr = OBJ_NIL;
    
    fprintf(stderr, "Performing: %s\n", pTestName);
    pBuf =  AStr_NewA(
                "%goal xyz\n"
                "%term STRING\n"            
                "def : STRING | 'c';\n"            
            );
    XCTAssertFalse( (OBJ_NIL == pBuf) );
    if (pBuf) {
        
        pSrc = srcFile_NewFromAStr(pPath, pBuf, 1, 4);
        XCTAssertFalse( (OBJ_NIL == pSrc) );
        if (pSrc) {
            
            pLex2 = (LEX_DATA *)pplex2_New(4);
            XCTAssertFalse( (OBJ_NIL == pLex2) );
            if (OBJ_NIL == pLex2) {
                return 0;
            }
            pplex2_setReturnNL((PPLEX2_DATA *)pLex2, true);
            pplex2_setReturnWS((PPLEX2_DATA *)pLex2, false);
            obj_TraceSet(pLex2, true);
            
            fRc = pplex2_setKwdSelection((PPLEX2_DATA *)pLex2, PPLEX_LANG_LL1);
            XCTAssertTrue( (fRc) );
            
            fRc =   lex_setSourceFunction(
                                          pLex2,
                                          (void *)srcFile_InputAdvance,
                                          (void *)srcFile_InputLookAhead,
                                          pSrc
                    );
            XCTAssertTrue( (fRc) );
            
            pLex3 = (LEX_DATA *)pplex3_New(4);
            XCTAssertFalse( (OBJ_NIL == pLex3) );
            if (OBJ_NIL == pLex3) {
                return 0;
            }
            
            obj_TraceSet(pLex3, true);
            fRc = pplex3_setKwdSelection((PPLEX3_DATA *)pLex3, PPLEX_LANG_LL1);
            XCTAssertTrue( (fRc) );
            
            fRc =   lex_setSourceFunction(
                                          pLex3,
                                          (void *)lex_TokenAdvance,
                                          (void *)lex_TokenLookAhead,
                                          pLex2
                    );
            XCTAssertTrue( (fRc) );
            
            // 1st Line - "%goal xyz\n"
            pToken = lex_TokenLookAhead(pLex3, 1);
            XCTAssertFalse( (OBJ_NIL == pToken) );
            {
                pStr = Token_ToDataString(pToken);
                fprintf(stderr, "text=\"%s\"\n",  AStr_getData(pStr));
                obj_Release(pStr);
                pStr = OBJ_NIL;
            }
            XCTAssertTrue( (PPLEX_KWD_GOAL == Token_getClass(pToken)) );
            pStr = Token_ToDataString(pToken);
            XCTAssertTrue( (ERESULT_SUCCESS_EQUAL == AStr_CompareA(pStr, "%g")) );
            obj_Release(pStr);
            pStr = OBJ_NIL;
            pToken = lex_TokenAdvance(pLex3, 1);
            XCTAssertFalse( (OBJ_NIL == pToken) );
            
            pToken = lex_TokenLookAhead(pLex3, 1);
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
            pToken = lex_TokenAdvance(pLex3, 1);
            XCTAssertFalse( (OBJ_NIL == pToken) );
            
            pToken = lex_TokenLookAhead(pLex3, 1);
            XCTAssertFalse( (OBJ_NIL == pToken) );
            {
                pStr = Token_ToDataString(pToken);
                fprintf(stderr, "\ttext=\"%s\"\n",  AStr_getData(pStr));
                obj_Release(pStr);
                pStr = OBJ_NIL;
            }
            XCTAssertTrue( (PPLEX_SEP_NL == Token_getClass(pToken)) );
            pStr = Token_getTextAStr(pToken);
            fprintf(stderr, "\tSEP_NL=\"%s\"\n", AStr_getData(pStr));
            obj_Release(pStr);
            pStr = OBJ_NIL;
            pStr = Token_ToDataString(pToken);
            XCTAssertTrue( (ERESULT_SUCCESS_EQUAL == AStr_CompareA(pStr, "\\n")) );
            obj_Release(pStr);
            pStr = OBJ_NIL;
            pToken = lex_TokenAdvance(pLex3, 1);
            XCTAssertFalse( (OBJ_NIL == pToken) );
            
#ifdef XYZZY
            pToken = lex_TokenLookAhead(pLex3, 1);
            XCTAssertFalse( (OBJ_NIL == pToken) );
            XCTAssertTrue( (PPLEX_SEP_NL == Token_getClass(pToken)) );
            pToken = lex_TokenAdvance(pLex3, 1);
            XCTAssertFalse( (OBJ_NIL == pToken) );

            // 2nd Line - "\ta += b + c;\n"
            pToken = lex_TokenLookAhead(pLex3, 1);
            XCTAssertFalse( (OBJ_NIL == pToken) );
            XCTAssertTrue( (PPLEX_SEP_WHITESPACE == Token_getClass(pToken)) );
            pToken = lex_TokenAdvance(pLex3, 1);
            XCTAssertFalse( (OBJ_NIL == pToken) );
            
            pToken = lex_TokenLookAhead(pLex3, 1);
            XCTAssertFalse( (OBJ_NIL == pToken) );
            XCTAssertTrue( (PPLEX_IDENTIFIER == Token_getClass(pToken)) );
            pStr = Token_ToDataString(pToken);
            XCTAssertTrue( (ERESULT_SUCCESS_EQUAL == AStr_CompareA(pStr, "a")) );
            obj_Release(pStr);
            pStr = OBJ_NIL;
            pToken = lex_TokenAdvance(pLex3, 1);
            XCTAssertFalse( (OBJ_NIL == pToken) );
            
            pToken = lex_TokenLookAhead(pLex3, 1);
            XCTAssertFalse( (OBJ_NIL == pToken) );
            XCTAssertTrue( (PPLEX_SEP_WHITESPACE == Token_getClass(pToken)) );
            pToken = lex_TokenAdvance(pLex3, 1);
            XCTAssertFalse( (OBJ_NIL == pToken) );
            
            pToken = lex_TokenLookAhead(pLex3, 1);
            XCTAssertFalse( (OBJ_NIL == pToken) );
            XCTAssertTrue( (PPLEX_OP_ASSIGN_ADD == Token_getClass(pToken)) );
            pToken = lex_TokenAdvance(pLex3, 1);
            XCTAssertFalse( (OBJ_NIL == pToken) );
            
            pToken = lex_TokenLookAhead(pLex3, 1);
            XCTAssertFalse( (OBJ_NIL == pToken) );
            XCTAssertTrue( (PPLEX_SEP_WHITESPACE == Token_getClass(pToken)) );
            pToken = lex_TokenAdvance(pLex3, 1);
            XCTAssertFalse( (OBJ_NIL == pToken) );
            
            pToken = lex_TokenLookAhead(pLex3, 1);
            XCTAssertFalse( (OBJ_NIL == pToken) );
            XCTAssertTrue( (PPLEX_IDENTIFIER == Token_getClass(pToken)) );
            pStr = Token_ToDataString(pToken);
            XCTAssertTrue( (ERESULT_SUCCESS_EQUAL == AStr_CompareA(pStr, "b")) );
            obj_Release(pStr);
            pStr = OBJ_NIL;
            pToken = lex_TokenAdvance(pLex3, 1);
            XCTAssertFalse( (OBJ_NIL == pToken) );
            
            pToken = lex_TokenLookAhead(pLex3, 1);
            XCTAssertFalse( (OBJ_NIL == pToken) );
            XCTAssertTrue( (PPLEX_SEP_WHITESPACE == Token_getClass(pToken)) );
            pToken = lex_TokenAdvance(pLex3, 1);
            XCTAssertFalse( (OBJ_NIL == pToken) );
            
            pToken = lex_TokenLookAhead(pLex3, 1);
            XCTAssertFalse( (OBJ_NIL == pToken) );
            XCTAssertTrue( (PPLEX_OP_ADD == Token_getClass(pToken)) );
            pToken = lex_TokenAdvance(pLex3, 1);
            XCTAssertFalse( (OBJ_NIL == pToken) );
            
            pToken = lex_TokenLookAhead(pLex3, 1);
            XCTAssertFalse( (OBJ_NIL == pToken) );
            XCTAssertTrue( (PPLEX_SEP_WHITESPACE == Token_getClass(pToken)) );
            pToken = lex_TokenAdvance(pLex3, 1);
            XCTAssertFalse( (OBJ_NIL == pToken) );
            
            pToken = lex_TokenLookAhead(pLex3, 1);
            XCTAssertFalse( (OBJ_NIL == pToken) );
            XCTAssertTrue( (PPLEX_IDENTIFIER == Token_getClass(pToken)) );
            pStr = Token_ToDataString(pToken);
            XCTAssertTrue( (ERESULT_SUCCESS_EQUAL == AStr_CompareA(pStr, "c")) );
            obj_Release(pStr);
            pStr = OBJ_NIL;
            pToken = lex_TokenAdvance(pLex3, 1);
            XCTAssertFalse( (OBJ_NIL == pToken) );
            
            pToken = lex_TokenLookAhead(pLex3, 1);
            XCTAssertFalse( (OBJ_NIL == pToken) );
            XCTAssertTrue( (PPLEX_SEP_SEMICOLON == Token_getClass(pToken)) );
            pToken = lex_TokenAdvance(pLex3, 1);
            XCTAssertFalse( (OBJ_NIL == pToken) );
            
            pToken = lex_TokenLookAhead(pLex3, 1);
            XCTAssertFalse( (OBJ_NIL == pToken) );
            XCTAssertTrue( (PPLEX_SEP_NL == Token_getClass(pToken)) );
            pToken = lex_TokenAdvance(pLex3, 1);
            XCTAssertFalse( (OBJ_NIL == pToken) );
            
            // 3rd Line - "@end\n"
            pToken = lex_TokenLookAhead(pLex3, 1);
            XCTAssertFalse( (OBJ_NIL == pToken) );
            XCTAssertTrue( (PPLEX_KWD_AT_END == Token_getClass(pToken)) );
            pStr = Token_ToDataString(pToken);
            XCTAssertTrue( (ERESULT_SUCCESS_EQUAL == AStr_CompareA(pStr, "@end")) );
            obj_Release(pStr);
            pStr = OBJ_NIL;
            pToken = lex_TokenAdvance(pLex3, 1);
            XCTAssertFalse( (OBJ_NIL == pToken) );
            
            pToken = lex_TokenLookAhead(pLex3, 1);
            XCTAssertFalse( (OBJ_NIL == pToken) );
            XCTAssertTrue( (PPLEX_SEP_NL == Token_getClass(pToken)) );
            pToken = lex_TokenAdvance(pLex3, 1);
            XCTAssertFalse( (OBJ_NIL == pToken) );
#endif
            
            obj_Release(pLex3);
            pLex3 = OBJ_NIL;
            
            obj_Release(pLex2);
            pLex2 = OBJ_NIL;
        }
        
        obj_Release(pSrc);
        pSrc = OBJ_NIL;

        obj_Release(pBuf);
        pBuf = OBJ_NIL;
    }
    
    obj_Release(pPath);
    pPath = OBJ_NIL;
    fprintf(stderr, "...%s completed.\n", pTestName);
    return 1;
}




TINYTEST_START_SUITE(test_pplex3);
  TINYTEST_ADD_TEST(test_pplex3_Input02,setUp,tearDown);
  TINYTEST_ADD_TEST(test_pplex3_Input01,setUp,tearDown);
  TINYTEST_ADD_TEST(test_pplex3_OpenClose,setUp,tearDown);
TINYTEST_END_SUITE();

TINYTEST_MAIN_SINGLE_SUITE(test_pplex3);





