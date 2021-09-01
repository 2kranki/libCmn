// vi:nu:et:sts=4 ts=4 sw=4
/*
 *  Generated 05/28/16 16:45:58
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
#include    <JsonIn.h>
#include    <trace.h>
#include    <Lex_internal.h>
#include    <SrcErrors.h>
#include    <szTbl.h>
#include    <SrcFile.h>



int             setUp (
    const
    char            *pTestName
)
{
    mem_Init( );
    trace_Shared( ); 
    // Put setup code here. This method is called before the invocation of each
    // test method in the class.
    
    return 1; 
}


int             tearDown (
    const
    char            *pTestName
)
{
    // Put teardown code here. This method is called after the invocation of each
    // test method in the class.

    SrcErrors_SharedReset( );
    szTbl_SharedReset( );
    JsonIn_RegisterReset();
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






int             test_Lex_OpenClose (
    const
    char            *pTestName
)
{
    ERESULT         eRc = ERESULT_SUCCESS;
    LEX_DATA       *pObj = OBJ_NIL;
    bool            fRc;
   
    fprintf(stderr, "Performing: %s\n", pTestName);

    pObj = Lex_Alloc( );
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    pObj = Lex_Init( pObj );
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    if (pObj) {

        //obj_TraceSet(pObj, true);       
        fRc = obj_IsKindOf(pObj, OBJ_IDENT_LEX);
        TINYTEST_TRUE( (fRc) );
        
        // Test something.
        TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );

        obj_Release(pObj);
        pObj = OBJ_NIL;
    }

    fprintf(stderr, "...%s completed.\n\n\n", pTestName);
    return 1;
}



int             test_Lex_Copy01 (
    const
    char            *pTestName
)
{
    ERESULT         eRc = ERESULT_SUCCESS;
    LEX_DATA       *pObj1 = OBJ_NIL;
    LEX_DATA       *pObj2 = OBJ_NIL;
    bool            fRc;
#if defined(LEX_JSON_SUPPORT) && defined(XYZZY)
    ASTR_DATA       *pStr = OBJ_NIL;
#endif
   
    fprintf(stderr, "Performing: %s\n", pTestName);

    pObj1 = Lex_New( );
    TINYTEST_FALSE( (OBJ_NIL == pObj1) );
    if (pObj1) {

        //obj_TraceSet(pObj1, true);       
        fRc = obj_IsKindOf(pObj1, OBJ_IDENT_LEX);
        TINYTEST_TRUE( (fRc) );
        
        // Test assign.
        pObj2 = Lex_New();
        TINYTEST_FALSE( (OBJ_NIL == pObj2) );
        eRc = Lex_Assign(pObj1, pObj2);
        TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );

        fRc = obj_IsKindOf(pObj2, OBJ_IDENT_LEX);
        TINYTEST_TRUE( (fRc) );
        //eRc = Lex_Compare(pObj1, pObj2);
        //TINYTEST_TRUE( (0 == eRc) );
        //TODO: Add More tests here!

        obj_Release(pObj2);
        pObj2 = OBJ_NIL;

        // Test copy.
        pObj2 = Lex_Copy(pObj1);
        TINYTEST_FALSE( (OBJ_NIL == pObj2) );

        fRc = obj_IsKindOf(pObj2, OBJ_IDENT_LEX);
        TINYTEST_TRUE( (fRc) );
        //eRc = Lex_Compare(pObj1, pObj2);
        //TINYTEST_TRUE( (0 == eRc) );
        //TODO: Add More tests here!

        obj_Release(pObj2);
        pObj2 = OBJ_NIL;

        // Test json support.
#if defined(LEX_JSON_SUPPORT) && defined(XYZZY)
        pStr = Lex_ToJson(pObj1);
        TINYTEST_FALSE( (OBJ_NIL == pStr) );
        fprintf(stderr, "JSON: %s\n", AStr_getData(pStr));
        pObj2 = Lex_NewFromJsonString(pStr);
        TINYTEST_FALSE( (OBJ_NIL == pObj2) );
        fRc = obj_IsKindOf(pObj2, OBJ_IDENT_LEX);
        TINYTEST_TRUE( (fRc) );
        obj_Release(pStr);
        pStr = OBJ_NIL;
        //eRc = Lex_Compare(pObj1, pObj2);
        //TINYTEST_TRUE( (0 == eRc) );

        obj_Release(pObj2);
        pObj2 = OBJ_NIL;
#endif

        obj_Release(pObj1);
        pObj1 = OBJ_NIL;
    }

    fprintf(stderr, "...%s completed.\n\n\n", pTestName);
    return 1;
}



int             test_Lex_Test01 (
    const
    char            *pTestName
)
{
    //ERESULT         eRc = ERESULT_SUCCESS;
    SRCFILE_DATA    *pSrc = OBJ_NIL;
    ASTR_DATA       *pBuf = OBJ_NIL;
    LEX_DATA        *pLex = OBJ_NIL;
    TOKEN_DATA      *pToken;
    TOKEN_DATA      *pTokenLA;
    bool            fRc;
    PATH_DATA       *pPath = Path_NewA("abc");
    LEX_PARSE_DATA  *pData = NULL;
    LEX_PARSE_DATA  data = {0};

    fprintf(stderr, "Performing: %s\n", pTestName);
    pBuf = AStr_NewA("abc123");
    XCTAssertFalse( (OBJ_NIL == pBuf) );
    if (pBuf) {

        pSrc = SrcFile_NewFromAStr(pPath, pBuf, 1, 4);
        XCTAssertFalse( (OBJ_NIL == pSrc) );
        if (pSrc) {

            pLex = (LEX_DATA *)Lex_New();
            XCTAssertFalse( (OBJ_NIL == pLex) );
            if (pLex) {

                obj_TraceSet(pLex, true);
                fRc =   Lex_setSourceInput(
                                              pLex,
                                              (void *)SrcFile_InputAdvance,
                                              (void *)SrcFile_InputLookAhead,
                                              pSrc
                                              );
                XCTAssertTrue( (fRc) );

                data.pOutput = Lex_getToken(pLex);
                data.pStr = pLex->pStr;
                data.clsNew = LEX_CLASS_UNKNOWN;
                data.fFinalize = true;
                data.fSavStr = true;
                Token_Init(&data.token1);
                Token_Init(&data.token2);

                fRc = Lex_NextInput(pLex, &data, true);
                XCTAssertTrue( (fRc) );
                XCTAssertTrue( (Token_Validate(&data.token1)) );
                XCTAssertTrue( (Token_Validate(&data.token2)) );
                {
                    char            *pStrA = Token_getTextA(&data.token1);
                    fprintf(stderr, "1 Should be: \"a\"\n");
                    fprintf(stderr, "1 Got:       \"%s\"\n",  pStrA);
                    XCTAssertTrue( (0 == strcmp(pStrA, "a")) );
                    mem_Free(pStrA);
                    pStrA = NULL;
                    pStrA = Token_getTextA(&data.token2);
                    fprintf(stderr, "2 Should be: \"b\"\n");
                    fprintf(stderr, "2 Got:       \"%s\"\n",  pStrA);
                    XCTAssertTrue( (0 == strcmp(pStrA, "b")) );
                    mem_Free(pStrA);
                    pStrA = NULL;
                }

                fRc = Lex_NextInput(pLex, &data, false);
                XCTAssertTrue( (fRc) );
                XCTAssertTrue( (Token_Validate(&data.token1)) );
                XCTAssertTrue( (Token_Validate(&data.token2)) );
                {
                    char            *pStrA = Token_getTextA(&data.token1);
                    fprintf(stderr, "1 Should be: \"b\"\n");
                    fprintf(stderr, "1 Got:       \"%s\"\n",  pStrA);
                    XCTAssertTrue( (0 == strcmp(pStrA, "b")) );
                    mem_Free(pStrA);
                    pStrA = NULL;
                    pStrA = Token_getTextA(&data.token2);
                    fprintf(stderr, "2 Should be: \"c\"\n");
                    fprintf(stderr, "2 Got:       \"%s\"\n",  pStrA);
                    XCTAssertTrue( (0 == strcmp(pStrA, "c")) );
                    mem_Free(pStrA);
                    pStrA = NULL;
                }

                fRc = Lex_NextInput(pLex, &data, false);
                XCTAssertTrue( (fRc) );
                XCTAssertTrue( (Token_Validate(&data.token1)) );
                XCTAssertTrue( (Token_Validate(&data.token2)) );
                {
                    char            *pStrA = Token_getTextA(&data.token1);
                    fprintf(stderr, "1 Should be: \"c\"\n");
                    fprintf(stderr, "1 Got:       \"%s\"\n",  pStrA);
                    XCTAssertTrue( (0 == strcmp(pStrA, "c")) );
                    mem_Free(pStrA);
                    pStrA = NULL;
                    pStrA = Token_getTextA(&data.token2);
                    fprintf(stderr, "2 Should be: \"1\"\n");
                    fprintf(stderr, "2 Got:       \"%s\"\n",  pStrA);
                    XCTAssertTrue( (0 == strcmp(pStrA, "1")) );
                    mem_Free(pStrA);
                    pStrA = NULL;
                }

                fRc = Lex_NextInput(pLex, &data, false);
                XCTAssertTrue( (fRc) );
                XCTAssertTrue( (Token_Validate(&data.token1)) );
                XCTAssertTrue( (Token_Validate(&data.token2)) );
                {
                    char            *pStrA = Token_getTextA(&data.token1);
                    fprintf(stderr, "1 Should be: \"1\"\n");
                    fprintf(stderr, "1 Got:       \"%s\"\n",  pStrA);
                    XCTAssertTrue( (0 == strcmp(pStrA, "1")) );
                    mem_Free(pStrA);
                    pStrA = NULL;
                    pStrA = Token_getTextA(&data.token2);
                    fprintf(stderr, "2 Should be: \"2\"\n");
                    fprintf(stderr, "2 Got:       \"%s\"\n",  pStrA);
                    XCTAssertTrue( (0 == strcmp(pStrA, "2")) );
                    mem_Free(pStrA);
                    pStrA = NULL;
                }

                fRc = Lex_NextInput(pLex, &data, false);
                XCTAssertTrue( (fRc) );
                XCTAssertTrue( (Token_Validate(&data.token1)) );
                XCTAssertTrue( (Token_Validate(&data.token2)) );
                {
                    char            *pStrA = Token_getTextA(&data.token1);
                    fprintf(stderr, "1 Should be: \"2\"\n");
                    fprintf(stderr, "1 Got:       \"%s\"\n",  pStrA);
                    XCTAssertTrue( (0 == strcmp(pStrA, "2")) );
                    mem_Free(pStrA);
                    pStrA = NULL;
                    pStrA = Token_getTextA(&data.token2);
                    fprintf(stderr, "2 Should be: \"3\"\n");
                    fprintf(stderr, "2 Got:       \"%s\"\n",  pStrA);
                    XCTAssertTrue( (0 == strcmp(pStrA, "3")) );
                    mem_Free(pStrA);
                    pStrA = NULL;
                }

                fRc = Lex_NextInput(pLex, &data, false);
                XCTAssertTrue( (fRc) );
                XCTAssertTrue( (Token_Validate(&data.token1)) );
                XCTAssertTrue( (Token_Validate(&data.token2)) );
                {
                    char            *pStrA = Token_getTextA(&data.token1);
                    fprintf(stderr, "1 Should be: \"3\"\n");
                    fprintf(stderr, "1 Got:       \"%s\"\n",  pStrA);
                    XCTAssertTrue( (0 == strcmp(pStrA, "3")) );
                    mem_Free(pStrA);
                    pStrA = NULL;
                    pStrA = Token_getTextA(&data.token2);
                    fprintf(stderr, "2 Should be: \"<<EOF>>\"\n");
                    fprintf(stderr, "2 Got:       \"%s\"\n",  pStrA);
                    XCTAssertTrue( (*pStrA == (char)-1) );
                    mem_Free(pStrA);
                    pStrA = NULL;
                }

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

    fprintf(stderr, "...%s completed.\n\n\n", pTestName);
    return 1;
}



int         test_Lex_Identifier01(
    const
    char        *pTestName
)
{
    SRCFILE_DATA    *pSrc = OBJ_NIL;
    ASTR_DATA       *pBuf = OBJ_NIL;
    LEX_DATA        *pLex = OBJ_NIL;
    TOKEN_DATA      *pToken;
    TOKEN_DATA      *pTokenLA;
    bool            fRc;
    PATH_DATA       *pPath = Path_NewA("abc");

    fprintf(stderr, "Performing: %s\n", pTestName);
    pBuf = AStr_NewA("__abc_def2");
    XCTAssertFalse( (OBJ_NIL == pBuf) );
    if (pBuf) {

        pSrc = SrcFile_NewFromAStr(pPath, pBuf, 1, 4);
        XCTAssertFalse( (OBJ_NIL == pSrc) );
        if (pSrc) {

            pLex = (LEX_DATA *)Lex_New();
            XCTAssertFalse( (OBJ_NIL == pLex) );
            if (pLex) {

                obj_TraceSet(pLex, true);
                fRc =   Lex_setSourceInput(
                                              pLex,
                                              (void *)SrcFile_InputAdvance,
                                              (void *)SrcFile_InputLookAhead,
                                              pSrc
                                              );
                XCTAssertTrue( (fRc) );

                pTokenLA = Lex_TokenLookAhead(pLex, 1);
                XCTAssertFalse( (OBJ_NIL == pTokenLA) );
                XCTAssertTrue( (Token_Validate(pTokenLA)) );
                {
                    char            *pStrA = Token_getTextA(pTokenLA);
                    fprintf(stderr, "Should be: \"__abc_def2\"\n");
                    fprintf(stderr, "Got:       \"%s\"\n",  pStrA);
                    mem_Free(pStrA);
                    pStrA = NULL;
                    fprintf(stderr, "class=%s\n\n", Lex_ClassToString(Token_getClass(pTokenLA)));
                }
                XCTAssertTrue( (LEX_IDENTIFIER == Token_getClass(pTokenLA)) );
                {
                    ASTR_DATA *pWrk = Token_ToDataString(pTokenLA);
                    XCTAssertTrue( (0 == AStr_CompareA(pWrk, "__abc_def2")) );
                    obj_Release(pWrk);
                    pWrk = OBJ_NIL;
                }
                pToken = Lex_TokenAdvance(pLex, 1);
                XCTAssertFalse( (OBJ_NIL == pToken) );
                XCTAssertTrue(  (pTokenLA == pToken) );

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

    fprintf(stderr, "...%s completed.\n\n\n", pTestName);
    return 1;
}



int         test_Lex_Number01(
     const
     char        *pTestName
)
{
    SRCFILE_DATA    *pSrc = OBJ_NIL;
    ASTR_DATA       *pBuf = OBJ_NIL;
    LEX_DATA        *pLex = OBJ_NIL;
    TOKEN_DATA      *pToken;
    TOKEN_DATA      *pTokenLA;
    bool            fRc;
    PATH_DATA       *pPath = Path_NewA("abc");

    fprintf(stderr, "Performing: %s\n", pTestName);
    pBuf = AStr_NewA("123");
    XCTAssertFalse( (OBJ_NIL == pBuf) );
    if (pBuf) {

        pSrc = SrcFile_NewFromAStr(pPath, pBuf, 1, 4);
        XCTAssertFalse( (OBJ_NIL == pSrc) );
        if (pSrc) {

            pLex = (LEX_DATA *)Lex_New();
            XCTAssertFalse( (OBJ_NIL == pLex) );
            if (pLex) {

                obj_TraceSet(pLex, true);
                fRc =   Lex_setSourceInput(
                            pLex,
                            (void *)SrcFile_InputAdvance,
                            (void *)SrcFile_InputLookAhead,
                            pSrc
                        );
                XCTAssertTrue( (fRc) );

                pTokenLA = Lex_TokenLookAhead(pLex, 1);
                XCTAssertFalse( (OBJ_NIL == pTokenLA) );
                XCTAssertTrue( (Token_Validate(pTokenLA)) );
                {
                    char            *pStrA = Token_getTextA(pTokenLA);
                    fprintf(stderr, "Should be: \"123\"\n");
                    fprintf(stderr, "Got:       \"%s\"\n",  pStrA);
                    mem_Free(pStrA);
                    pStrA = NULL;
                    fprintf(stderr, "class=%s\n\n", Lex_ClassToString(Token_getClass(pTokenLA)));
                }
                XCTAssertTrue( (LEX_CONSTANT_INTEGER == Token_getClass(pTokenLA)) );
                {
                    ASTR_DATA *pWrk = Token_ToDataString(pTokenLA);
                    XCTAssertTrue( (0 == AStr_CompareA(pWrk, "123")) );
                    obj_Release(pWrk);
                    pWrk = OBJ_NIL;
                }
                pToken = Lex_TokenAdvance(pLex, 1);
                XCTAssertFalse( (OBJ_NIL == pToken) );
                XCTAssertTrue(  (pTokenLA == pToken) );

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

    fprintf(stderr, "...%s completed.\n\n\n", pTestName);
    return 1;
}



int         test_Lex_Number02(
      const
      char        *pTestName
)
{
    SRCFILE_DATA    *pSrc = OBJ_NIL;
    ASTR_DATA       *pBuf = OBJ_NIL;
    LEX_DATA        *pLex = OBJ_NIL;
    TOKEN_DATA      *pToken;
    TOKEN_DATA      *pTokenLA;
    bool            fRc;
    PATH_DATA       *pPath = Path_NewA("abc");

    fprintf(stderr, "Performing: %s\n", pTestName);
    pBuf = AStr_NewA("123.456");
    XCTAssertFalse( (OBJ_NIL == pBuf) );
    if (pBuf) {

        pSrc = SrcFile_NewFromAStr(pPath, pBuf, 1, 4);
        XCTAssertFalse( (OBJ_NIL == pSrc) );
        if (pSrc) {

            pLex = (LEX_DATA *)Lex_New();
            XCTAssertFalse( (OBJ_NIL == pLex) );
            if (pLex) {

                obj_TraceSet(pLex, true);
                fRc =   Lex_setSourceInput(
                                              pLex,
                                              (void *)SrcFile_InputAdvance,
                                              (void *)SrcFile_InputLookAhead,
                                              pSrc
                                              );
                XCTAssertTrue( (fRc) );

                pTokenLA = Lex_TokenLookAhead(pLex, 1);
                XCTAssertFalse( (OBJ_NIL == pTokenLA) );
                XCTAssertTrue( (Token_Validate(pTokenLA)) );
                {
                    char            *pStrA = Token_getTextA(pTokenLA);
                    fprintf(stderr, "Should be: \"123.456\"\n");
                    fprintf(stderr, "Got:       \"%s\"\n",  pStrA);
                    mem_Free(pStrA);
                    pStrA = NULL;
                    fprintf(stderr, "class=%s\n\n", Lex_ClassToString(Token_getClass(pTokenLA)));
                }
                XCTAssertTrue( (LEX_CONSTANT_FLOAT == Token_getClass(pTokenLA)) );
                {
                    ASTR_DATA *pWrk = Token_ToDataString(pTokenLA);
                    XCTAssertTrue( (0 == AStr_CompareA(pWrk, "123.456")) );
                    obj_Release(pWrk);
                    pWrk = OBJ_NIL;
                }
                pToken = Lex_TokenAdvance(pLex, 1);
                XCTAssertFalse( (OBJ_NIL == pToken) );
                XCTAssertTrue(  (pTokenLA == pToken) );

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

    fprintf(stderr, "...%s completed.\n\n\n", pTestName);
    return 1;
}



int         test_Lex_Number03(
    const
    char        *pTestName
)
{
    SRCFILE_DATA    *pSrc = OBJ_NIL;
    ASTR_DATA       *pBuf = OBJ_NIL;
    LEX_DATA        *pLex = OBJ_NIL;
    TOKEN_DATA      *pToken;
    TOKEN_DATA      *pTokenLA;
    bool            fRc;
    PATH_DATA       *pPath = Path_NewA("abc");

    fprintf(stderr, "Performing: %s\n", pTestName);
    pBuf = AStr_NewA("0");
    XCTAssertFalse( (OBJ_NIL == pBuf) );
    if (pBuf) {

        pSrc = SrcFile_NewFromAStr(pPath, pBuf, 1, 4);
        XCTAssertFalse( (OBJ_NIL == pSrc) );
        if (pSrc) {

            pLex = (LEX_DATA *)Lex_New();
            XCTAssertFalse( (OBJ_NIL == pLex) );
            if (pLex) {

                obj_TraceSet(pLex, true);
                fRc =   Lex_setSourceInput(
                                              pLex,
                                              (void *)SrcFile_InputAdvance,
                                              (void *)SrcFile_InputLookAhead,
                                              pSrc
                                              );
                XCTAssertTrue( (fRc) );

                pTokenLA = Lex_TokenLookAhead(pLex, 1);
                XCTAssertFalse( (OBJ_NIL == pTokenLA) );
                XCTAssertTrue( (Token_Validate(pTokenLA)) );
                {
                    char            *pStrA = Token_getTextA(pTokenLA);
                    fprintf(stderr, "Should be: \"0\"\n");
                    fprintf(stderr, "Got:       \"%s\"\n",  pStrA);
                    mem_Free(pStrA);
                    pStrA = NULL;
                    fprintf(stderr, "class=%s\n\n", Lex_ClassToString(Token_getClass(pTokenLA)));
                }
                XCTAssertTrue( (LEX_CONSTANT_INTEGER == Token_getClass(pTokenLA)) );
                {
                    ASTR_DATA *pWrk = Token_ToDataString(pTokenLA);
                    XCTAssertTrue( (0 == AStr_CompareA(pWrk, "0")) );
                    obj_Release(pWrk);
                    pWrk = OBJ_NIL;
                }
                pToken = Lex_TokenAdvance(pLex, 1);
                XCTAssertFalse( (OBJ_NIL == pToken) );
                XCTAssertTrue(  (pTokenLA == pToken) );

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

    fprintf(stderr, "...%s completed.\n\n\n", pTestName);
    return 1;
}



int         test_Lex_Number04(
      const
      char        *pTestName
)
{
    SRCFILE_DATA    *pSrc = OBJ_NIL;
    ASTR_DATA       *pBuf = OBJ_NIL;
    LEX_DATA        *pLex = OBJ_NIL;
    TOKEN_DATA      *pToken;
    TOKEN_DATA      *pTokenLA;
    bool            fRc;
    PATH_DATA       *pPath = Path_NewA("abc");

    fprintf(stderr, "Performing: %s\n", pTestName);
    pBuf = AStr_NewA("3.141600E+00");
    XCTAssertFalse( (OBJ_NIL == pBuf) );
    if (pBuf) {

        pSrc = SrcFile_NewFromAStr(pPath, pBuf, 1, 4);
        XCTAssertFalse( (OBJ_NIL == pSrc) );
        if (pSrc) {

            pLex = (LEX_DATA *)Lex_New();
            XCTAssertFalse( (OBJ_NIL == pLex) );
            if (pLex) {

                obj_TraceSet(pLex, true);
                fRc =   Lex_setSourceInput(
                                              pLex,
                                              (void *)SrcFile_InputAdvance,
                                              (void *)SrcFile_InputLookAhead,
                                              pSrc
                                              );
                XCTAssertTrue( (fRc) );

                pTokenLA = Lex_TokenLookAhead(pLex, 1);
                XCTAssertFalse( (OBJ_NIL == pTokenLA) );
                XCTAssertTrue( (Token_Validate(pTokenLA)) );
                {
                    char            *pStrA = Token_getTextA(pTokenLA);
                    fprintf(stderr, "Should be: \"3.141600E+00\"\n");
                    fprintf(stderr, "Got:       \"%s\"\n",  pStrA);
                    mem_Free(pStrA);
                    pStrA = NULL;
                    fprintf(stderr, "class=%s\n\n", Lex_ClassToString(Token_getClass(pTokenLA)));
                }
                XCTAssertTrue( (LEX_CONSTANT_FLOAT == Token_getClass(pTokenLA)) );
                {
                    ASTR_DATA *pWrk = Token_ToDataString(pTokenLA);
                    XCTAssertTrue( (0 == AStr_CompareA(pWrk, "3.141600E+00")) );
                    obj_Release(pWrk);
                    pWrk = OBJ_NIL;
                }
                pToken = Lex_TokenAdvance(pLex, 1);
                XCTAssertFalse( (OBJ_NIL == pToken) );
                XCTAssertTrue(  (pTokenLA == pToken) );

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

    fprintf(stderr, "...%s completed.\n\n\n", pTestName);
    return 1;
}



int         test_Lex_Number05(
    const
    char        *pTestName
)
{
    SRCFILE_DATA    *pSrc = OBJ_NIL;
    ASTR_DATA       *pBuf = OBJ_NIL;
    LEX_DATA        *pLex = OBJ_NIL;
    TOKEN_DATA      *pToken;
    TOKEN_DATA      *pTokenLA;
    bool            fRc;
    PATH_DATA       *pPath = Path_NewA("abc");

    fprintf(stderr, "Performing: %s\n", pTestName);
    pBuf = AStr_NewA("0b0110");
    XCTAssertFalse( (OBJ_NIL == pBuf) );
    if (pBuf) {

        pSrc = SrcFile_NewFromAStr(pPath, pBuf, 1, 4);
        XCTAssertFalse( (OBJ_NIL == pSrc) );
        if (pSrc) {

            pLex = (LEX_DATA *)Lex_New();
            XCTAssertFalse( (OBJ_NIL == pLex) );
            if (pLex) {

                obj_TraceSet(pLex, true);
                fRc =   Lex_setSourceInput(
                                              pLex,
                                              (void *)SrcFile_InputAdvance,
                                              (void *)SrcFile_InputLookAhead,
                                              pSrc
                                              );
                XCTAssertTrue( (fRc) );

                pTokenLA = Lex_TokenLookAhead(pLex, 1);
                XCTAssertFalse( (OBJ_NIL == pTokenLA) );
                XCTAssertTrue( (Token_Validate(pTokenLA)) );
                {
                    char            *pStrA = Token_getTextA(pTokenLA);
                    fprintf(stderr, "Should be: \"0b0110\"\n");
                    fprintf(stderr, "Got:       \"%s\"\n",  pStrA);
                    mem_Free(pStrA);
                    pStrA = NULL;
                    fprintf(stderr, "class=%s\n\n", Lex_ClassToString(Token_getClass(pTokenLA)));
                }
                XCTAssertTrue( (LEX_CONSTANT_INTEGER == Token_getClass(pTokenLA)) );
                {
                    ASTR_DATA *pWrk = Token_ToDataString(pTokenLA);
                    XCTAssertTrue( (0 == AStr_CompareA(pWrk, "0b0110")) );
                    obj_Release(pWrk);
                    pWrk = OBJ_NIL;
                }
                pToken = Lex_TokenAdvance(pLex, 1);
                XCTAssertFalse( (OBJ_NIL == pToken) );
                XCTAssertTrue(  (pTokenLA == pToken) );

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

    fprintf(stderr, "...%s completed.\n\n\n", pTestName);
    return 1;
}



int         test_Lex_Number06(
    const
    char        *pTestName
)
{
    SRCFILE_DATA    *pSrc = OBJ_NIL;
    ASTR_DATA       *pBuf = OBJ_NIL;
    LEX_DATA        *pLex = OBJ_NIL;
    TOKEN_DATA      *pToken;
    TOKEN_DATA      *pTokenLA;
    bool            fRc;
    PATH_DATA       *pPath = Path_NewA("abc");

    fprintf(stderr, "Performing: %s\n", pTestName);
    pBuf = AStr_NewA("0x0110");
    XCTAssertFalse( (OBJ_NIL == pBuf) );
    if (pBuf) {

        pSrc = SrcFile_NewFromAStr(pPath, pBuf, 1, 4);
        XCTAssertFalse( (OBJ_NIL == pSrc) );
        if (pSrc) {

            pLex = (LEX_DATA *)Lex_New();
            XCTAssertFalse( (OBJ_NIL == pLex) );
            if (pLex) {

                obj_TraceSet(pLex, true);
                fRc =   Lex_setSourceInput(
                                              pLex,
                                              (void *)SrcFile_InputAdvance,
                                              (void *)SrcFile_InputLookAhead,
                                              pSrc
                                              );
                XCTAssertTrue( (fRc) );

                pTokenLA = Lex_TokenLookAhead(pLex, 1);
                XCTAssertFalse( (OBJ_NIL == pTokenLA) );
                XCTAssertTrue( (Token_Validate(pTokenLA)) );
                {
                    char            *pStrA = Token_getTextA(pTokenLA);
                    fprintf(stderr, "Should be: \"0x0110\"\n");
                    fprintf(stderr, "Got:       \"%s\"\n",  pStrA);
                    mem_Free(pStrA);
                    pStrA = NULL;
                    fprintf(stderr, "class=%s\n\n", Lex_ClassToString(Token_getClass(pTokenLA)));
                }
                XCTAssertTrue( (LEX_CONSTANT_INTEGER == Token_getClass(pTokenLA)) );
                {
                    ASTR_DATA *pWrk = Token_ToDataString(pTokenLA);
                    XCTAssertTrue( (0 == AStr_CompareA(pWrk, "0x0110")) );
                    obj_Release(pWrk);
                    pWrk = OBJ_NIL;
                }
                pToken = Lex_TokenAdvance(pLex, 1);
                XCTAssertFalse( (OBJ_NIL == pToken) );
                XCTAssertTrue(  (pTokenLA == pToken) );

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

    fprintf(stderr, "...%s completed.\n\n\n", pTestName);
    return 1;
}



int         test_Lex_Number07(
    const
    char        *pTestName
)
{
    SRCFILE_DATA    *pSrc = OBJ_NIL;
    ASTR_DATA       *pBuf = OBJ_NIL;
    LEX_DATA        *pLex = OBJ_NIL;
    TOKEN_DATA      *pToken;
    TOKEN_DATA      *pTokenLA;
    bool            fRc;
    PATH_DATA       *pPath = Path_NewA("abc");

    fprintf(stderr, "Performing: %s\n", pTestName);
    pBuf = AStr_NewA("0117");
    XCTAssertFalse( (OBJ_NIL == pBuf) );
    if (pBuf) {

        pSrc = SrcFile_NewFromAStr(pPath, pBuf, 1, 4);
        XCTAssertFalse( (OBJ_NIL == pSrc) );
        if (pSrc) {

            pLex = (LEX_DATA *)Lex_New();
            XCTAssertFalse( (OBJ_NIL == pLex) );
            if (pLex) {

                obj_TraceSet(pLex, true);
                fRc =   Lex_setSourceInput(
                                              pLex,
                                              (void *)SrcFile_InputAdvance,
                                              (void *)SrcFile_InputLookAhead,
                                              pSrc
                                              );
                XCTAssertTrue( (fRc) );

                pTokenLA = Lex_TokenLookAhead(pLex, 1);
                XCTAssertFalse( (OBJ_NIL == pTokenLA) );
                XCTAssertTrue( (Token_Validate(pTokenLA)) );
                {
                    char            *pStrA = Token_getTextA(pTokenLA);
                    fprintf(stderr, "Should be: \"0117\"\n");
                    fprintf(stderr, "Got:       \"%s\"\n",  pStrA);
                    mem_Free(pStrA);
                    pStrA = NULL;
                    fprintf(stderr, "class=%s\n\n", Lex_ClassToString(Token_getClass(pTokenLA)));
                }
                XCTAssertTrue( (LEX_CONSTANT_INTEGER == Token_getClass(pTokenLA)) );
                {
                    ASTR_DATA *pWrk = Token_ToDataString(pTokenLA);
                    XCTAssertTrue( (0 == AStr_CompareA(pWrk, "0117")) );
                    obj_Release(pWrk);
                    pWrk = OBJ_NIL;
                }
                pToken = Lex_TokenAdvance(pLex, 1);
                XCTAssertFalse( (OBJ_NIL == pToken) );
                XCTAssertTrue(  (pTokenLA == pToken) );

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

    fprintf(stderr, "...%s completed.\n\n\n", pTestName);
    return 1;
}



int         test_Lex_Strings01(
    const
    char        *pTestName
)
{
    SRCFILE_DATA    *pSrc = OBJ_NIL;
    ASTR_DATA       *pBuf = OBJ_NIL;
    LEX_DATA        *pLex = OBJ_NIL;
    TOKEN_DATA      *pToken;
    TOKEN_DATA      *pTokenLA;
    bool            fRc;
    PATH_DATA       *pPath = Path_NewA("abc");

    fprintf(stderr, "Performing: %s\n", pTestName);
    pBuf = AStr_NewA("\"\"");
    XCTAssertFalse( (OBJ_NIL == pBuf) );
    if (pBuf) {

        pSrc = SrcFile_NewFromAStr(pPath, pBuf, 1, 4);
        XCTAssertFalse( (OBJ_NIL == pSrc) );
        if (pSrc) {

            pLex = (LEX_DATA *)Lex_New();
            XCTAssertFalse( (OBJ_NIL == pLex) );
            if (pLex) {

                obj_TraceSet(pLex, true);
                fRc =   Lex_setSourceInput(
                                              pLex,
                                              (void *)SrcFile_InputAdvance,
                                              (void *)SrcFile_InputLookAhead,
                                              pSrc
                                              );
                XCTAssertTrue( (fRc) );

                pTokenLA = Lex_TokenLookAhead(pLex, 1);
                XCTAssertFalse( (OBJ_NIL == pTokenLA) );
                XCTAssertTrue( (Token_Validate(pTokenLA)) );
                {
                    char            *pStrA = Token_getTextA(pTokenLA);
                    fprintf(stderr, "Should be: \"\"\"\"\n");
                    fprintf(stderr, "Got:       \"%s\"\n",  pStrA);
                    mem_Free(pStrA);
                    pStrA = NULL;
                    fprintf(stderr, "class=%s\n\n", Lex_ClassToString(Token_getClass(pTokenLA)));
                }
                XCTAssertTrue( (LEX_CONSTANT_STRING == Token_getClass(pTokenLA)) );
                {
                    ASTR_DATA *pWrk = Token_ToDataString(pTokenLA);
                    XCTAssertTrue( (0 == AStr_CompareA(pWrk, "")) );
                    obj_Release(pWrk);
                    pWrk = OBJ_NIL;
                }
                pToken = Lex_TokenAdvance(pLex, 1);
                XCTAssertFalse( (OBJ_NIL == pToken) );
                XCTAssertTrue(  (pTokenLA == pToken) );

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

    fprintf(stderr, "...%s completed.\n\n\n", pTestName);
    return 1;
}



int         test_Lex_Strings02(
    const
    char        *pTestName
)
{
    SRCFILE_DATA    *pSrc = OBJ_NIL;
    ASTR_DATA       *pBuf = OBJ_NIL;
    LEX_DATA        *pLex = OBJ_NIL;
    TOKEN_DATA      *pToken;
    TOKEN_DATA      *pTokenLA;
    bool            fRc;
    PATH_DATA       *pPath = Path_NewA("abc");

    fprintf(stderr, "Performing: %s\n", pTestName);
    pBuf = AStr_NewA("\"def\\n\"");
    XCTAssertFalse( (OBJ_NIL == pBuf) );
    if (pBuf) {

        pSrc = SrcFile_NewFromAStr(pPath, pBuf, 1, 4);
        XCTAssertFalse( (OBJ_NIL == pSrc) );
        if (pSrc) {

            pLex = (LEX_DATA *)Lex_New();
            XCTAssertFalse( (OBJ_NIL == pLex) );
            if (pLex) {

                obj_TraceSet(pLex, true);
                fRc =   Lex_setSourceInput(
                                              pLex,
                                              (void *)SrcFile_InputAdvance,
                                              (void *)SrcFile_InputLookAhead,
                                              pSrc
                                              );
                XCTAssertTrue( (fRc) );

                pTokenLA = Lex_TokenLookAhead(pLex, 1);
                XCTAssertFalse( (OBJ_NIL == pTokenLA) );
                XCTAssertTrue( (Token_Validate(pTokenLA)) );
                {
                    char            *pStrA = Token_getTextA(pTokenLA);
                    fprintf(stderr, "Should be: \"\"def\\n\"\"\n");
                    fprintf(stderr, "Got:       \"%s\"\n",  pStrA);
                    mem_Free(pStrA);
                    pStrA = NULL;
                    fprintf(stderr, "class=%s\n\n", Lex_ClassToString(Token_getClass(pTokenLA)));
                }
                XCTAssertTrue( (LEX_CONSTANT_STRING == Token_getClass(pTokenLA)) );
                {
                    ASTR_DATA *pWrk = Token_ToDataString(pTokenLA);
                    XCTAssertTrue( (0 == AStr_CompareA(pWrk, "def\\n")) );
                    obj_Release(pWrk);
                    pWrk = OBJ_NIL;
                }
                pToken = Lex_TokenAdvance(pLex, 1);
                XCTAssertFalse( (OBJ_NIL == pToken) );
                XCTAssertTrue(  (pTokenLA == pToken) );

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

    fprintf(stderr, "...%s completed.\n\n\n", pTestName);
    return 1;
}



int         test_Lex_Strings03(
    const
    char        *pTestName
)
{
    SRCFILE_DATA    *pSrc = OBJ_NIL;
    ASTR_DATA       *pBuf = OBJ_NIL;
    LEX_DATA        *pLex = OBJ_NIL;
    TOKEN_DATA      *pToken;
    TOKEN_DATA      *pTokenLA;
    bool            fRc;
    PATH_DATA       *pPath = Path_NewA("abc");

    fprintf(stderr, "Performing: %s\n", pTestName);
    pBuf = AStr_NewA("\"\\x01\\x02\"");
    XCTAssertFalse( (OBJ_NIL == pBuf) );
    if (pBuf) {

        pSrc = SrcFile_NewFromAStr(pPath, pBuf, 1, 4);
        XCTAssertFalse( (OBJ_NIL == pSrc) );
        if (pSrc) {

            pLex = (LEX_DATA *)Lex_New();
            XCTAssertFalse( (OBJ_NIL == pLex) );
            if (pLex) {

                obj_TraceSet(pLex, true);
                fRc =   Lex_setSourceInput(
                                              pLex,
                                              (void *)SrcFile_InputAdvance,
                                              (void *)SrcFile_InputLookAhead,
                                              pSrc
                                              );
                XCTAssertTrue( (fRc) );

                pTokenLA = Lex_TokenLookAhead(pLex, 1);
                XCTAssertFalse( (OBJ_NIL == pTokenLA) );
                XCTAssertTrue( (Token_Validate(pTokenLA)) );
                {
                    char            *pStrA = Token_getTextA(pTokenLA);
                    fprintf(stderr, "Should be: \"\"\\x01\\x02\"\"\n");
                    fprintf(stderr, "Got:       \"%s\"\n",  pStrA);
                    mem_Free(pStrA);
                    pStrA = NULL;
                    fprintf(stderr, "class=%s\n\n", Lex_ClassToString(Token_getClass(pTokenLA)));
                }
                XCTAssertTrue( (LEX_CONSTANT_STRING == Token_getClass(pTokenLA)) );
                {
                    ASTR_DATA *pWrk = Token_ToDataString(pTokenLA);
                    XCTAssertTrue( (0 == AStr_CompareA(pWrk, "\\x01\\x02")) );
                    obj_Release(pWrk);
                    pWrk = OBJ_NIL;
                }
                pToken = Lex_TokenAdvance(pLex, 1);
                XCTAssertFalse( (OBJ_NIL == pToken) );
                XCTAssertTrue(  (pTokenLA == pToken) );

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

    fprintf(stderr, "...%s completed.\n\n\n", pTestName);
    return 1;
}



int         test_Lex_Strings04(
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
    ERESULT         eRc;
    W32CHR_T        ch;

    fprintf(stderr, "Performing: %s\n", pTestName);
    pBuf = AStr_NewA("\"\\x01\\x02\"");
    XCTAssertFalse( (OBJ_NIL == pBuf) );
    if (pBuf) {

        pSrc = SrcFile_NewFromAStr(pPath, pBuf, 1, 4);
        XCTAssertFalse( (OBJ_NIL == pSrc) );
        if (pSrc) {

            pLex = (LEX_DATA *)Lex_New();
            XCTAssertFalse( (OBJ_NIL == pLex) );
            if (pLex) {

                obj_TraceSet(pLex, true);
                fRc =   Lex_setSourceInput(
                                              pLex,
                                              (void *)SrcFile_InputAdvance,
                                              (void *)SrcFile_InputLookAhead,
                                              pSrc
                        );
                XCTAssertTrue( (fRc) );

                pToken = Lex_InputLookAhead(pLex, 1);
                XCTAssertFalse( (OBJ_NIL == pToken) );
                eRc = Lex_ParseTokenSetup(pLex, pToken);
                XCTAssertFalse( (ERESULT_FAILED(eRc)) );

                // The following tests Lex_ParseChrCon() as found in ppLex2.
                Lex_InputAdvance(pLex, 1);
                while (Lex_ParseChrCon(pLex, NULL, '\"'))
                    ;
                pToken = Lex_InputLookAhead(pLex, 1);
                ch = Token_getChrW32(pToken);
                XCTAssertTrue( (ch == '"') );
                Lex_ParseTokenAppendString(pLex, pToken);
                {
                    ASTR_DATA       *pWrk2 = W32Str_ToAStr(pLex->pStr);
                    fprintf(stderr, "\tDATA=\"%s\"\n", AStr_getData(pWrk2));
                    obj_Release(pWrk2);
                }
                eRc = W32Str_CompareA(pLex->pStr, "\"\\x01\\x02\"");
                XCTAssertTrue( (0 == eRc) );

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

    fprintf(stderr, "...%s completed.\n\n\n", pTestName);
    return 1;
}



int         test_Lex_Input01(
    const
    char        *pTestName
)
{
    SRCFILE_DATA    *pSrc = OBJ_NIL;
    LEX_DATA        *pLex = OBJ_NIL;
    TOKEN_DATA      *pToken;
    TOKEN_DATA      *pTokenLA;
    bool            fRc;
    PATH_DATA       *pPath = Path_NewA("abc");
    const
    char            *pStrA = "class xyzzy{ int a; char *pA; };";
    ASTR_DATA       *pStr = OBJ_NIL;

    fprintf(stderr, "Performing: %s\n", pTestName);

    pStr = AStr_NewA(pStrA);
    XCTAssertFalse( (OBJ_NIL == pStr) );

    pSrc = SrcFile_NewFromAStr(pPath, pStr, 1, 4);
    XCTAssertFalse( (OBJ_NIL == pSrc) );
    if (pSrc) {

        pLex = (LEX_DATA *)Lex_New();
        XCTAssertFalse( (OBJ_NIL == pLex) );
        if (pLex) {

            //obj_TraceSet(pSrc, true);
            obj_TraceSet(pLex, true);
            fRc =   Lex_setSourceInput(
                                          pLex,
                                          (void *)SrcFile_InputAdvance,
                                          (void *)SrcFile_InputLookAhead,
                                          pSrc
                    );
            XCTAssertTrue( (fRc) );

            pTokenLA = Lex_TokenLookAhead(pLex, 1);
            XCTAssertFalse( (OBJ_NIL == pTokenLA) );
            XCTAssertTrue( (Token_Validate(pTokenLA)) );
            {
                char            *pStrA = Token_getTextA(pTokenLA);
                fprintf(stderr, "Should be: \"class\"\n");
                fprintf(stderr, "Got:       \"%s\"\n",  pStrA);
                mem_Free(pStrA);
                pStrA = NULL;
                fprintf(stderr, "class=%s\n\n", Lex_ClassToString(Token_getClass(pTokenLA)));
            }
            XCTAssertTrue( (LEX_IDENTIFIER == Token_getClass(pTokenLA)) );
            {
                ASTR_DATA *pWrk = Token_ToDataString(pTokenLA);
                XCTAssertTrue( (0 == AStr_CompareA(pWrk, "class")) );
                obj_Release(pWrk);
                pWrk = OBJ_NIL;
            }
            pToken = Lex_TokenAdvance(pLex, 1);
            XCTAssertFalse( (OBJ_NIL == pToken) );
            XCTAssertTrue(  (pTokenLA == pToken) );

            pTokenLA = Lex_TokenLookAhead(pLex, 1);
            XCTAssertFalse( (OBJ_NIL == pTokenLA) );
            XCTAssertTrue( (Token_Validate(pTokenLA)) );
            {
                char            *pStrA = Token_getTextA(pTokenLA);
                fprintf(stderr, "Should be: \"xyzzy\"\n");
                fprintf(stderr, "Got:       \"%s\"\n",  pStrA);
                mem_Free(pStrA);
                pStrA = NULL;
                fprintf(stderr, "class=%s\n\n", Lex_ClassToString(Token_getClass(pTokenLA)));
            }
            XCTAssertTrue( (LEX_IDENTIFIER == Token_getClass(pTokenLA)) );
            {
                ASTR_DATA *pWrk = Token_ToDataString(pTokenLA);
                XCTAssertTrue( (0 == AStr_CompareA(pWrk, "xyzzy")) );
                obj_Release(pWrk);
                pWrk = OBJ_NIL;
            }
            pToken = Lex_TokenAdvance(pLex, 1);
            XCTAssertFalse( (OBJ_NIL == pToken) );
            XCTAssertTrue(  (pTokenLA == pToken) );

            pTokenLA = Lex_TokenLookAhead(pLex, 1);
            XCTAssertFalse( (OBJ_NIL == pTokenLA) );
            XCTAssertTrue( (Token_Validate(pTokenLA)) );
            {
                char            *pStrA = Token_getTextA(pTokenLA);
                fprintf(stderr, "Should be: \"{\"\n");
                fprintf(stderr, "Got:       \"%s\"\n",  pStrA);
                mem_Free(pStrA);
                pStrA = NULL;
                fprintf(stderr, "class=%s\n\n", Lex_ClassToString(Token_getClass(pTokenLA)));
            }
            XCTAssertTrue( (LEX_SEP_LBRACE == Token_getClass(pTokenLA)) );
            pToken = Lex_TokenAdvance(pLex, 1);
            XCTAssertFalse( (OBJ_NIL == pToken) );
            XCTAssertTrue(  (pTokenLA == pToken) );

            pTokenLA = Lex_TokenLookAhead(pLex, 1);
            XCTAssertFalse( (OBJ_NIL == pTokenLA) );
            XCTAssertTrue( (Token_Validate(pTokenLA)) );
            {
                char            *pStrA = Token_getTextA(pTokenLA);
                fprintf(stderr, "Should be: \"int\"\n");
                fprintf(stderr, "Got:       \"%s\"\n",  pStrA);
                mem_Free(pStrA);
                pStrA = NULL;
                fprintf(stderr, "class=%s\n\n", Lex_ClassToString(Token_getClass(pTokenLA)));
            }
            XCTAssertTrue( (LEX_IDENTIFIER == Token_getClass(pTokenLA)) );
            {
                ASTR_DATA *pWrk = Token_ToDataString(pTokenLA);
                XCTAssertTrue( (0 == AStr_CompareA(pWrk, "int")) );
                obj_Release(pWrk);
                pWrk = OBJ_NIL;
            }
            pToken = Lex_TokenAdvance(pLex, 1);
            XCTAssertFalse( (OBJ_NIL == pToken) );
            XCTAssertTrue(  (pTokenLA == pToken) );

            pTokenLA = Lex_TokenLookAhead(pLex, 1);
            XCTAssertFalse( (OBJ_NIL == pTokenLA) );
            XCTAssertTrue( (Token_Validate(pTokenLA)) );
            {
                char            *pStrA = Token_getTextA(pTokenLA);
                fprintf(stderr, "Should be: \"a\"\n");
                fprintf(stderr, "Got:       \"%s\"\n",  pStrA);
                mem_Free(pStrA);
                pStrA = NULL;
                fprintf(stderr, "class=%s\n\n", Lex_ClassToString(Token_getClass(pTokenLA)));
            }
            XCTAssertTrue( (LEX_IDENTIFIER == Token_getClass(pTokenLA)) );
            {
                ASTR_DATA *pWrk = Token_ToDataString(pTokenLA);
                XCTAssertTrue( (0 == AStr_CompareA(pWrk, "a")) );
                obj_Release(pWrk);
                pWrk = OBJ_NIL;
            }
            pToken = Lex_TokenAdvance(pLex, 1);
            XCTAssertFalse( (OBJ_NIL == pToken) );
            XCTAssertTrue(  (pTokenLA == pToken) );

            pTokenLA = Lex_TokenLookAhead(pLex, 1);
            XCTAssertFalse( (OBJ_NIL == pTokenLA) );
            XCTAssertTrue( (Token_Validate(pTokenLA)) );
            {
                char            *pStrA = Token_getTextA(pTokenLA);
                fprintf(stderr, "Should be: \";\"\n");
                fprintf(stderr, "Got:       \"%s\"\n",  pStrA);
                mem_Free(pStrA);
                pStrA = NULL;
                fprintf(stderr, "class=%s\n\n", Lex_ClassToString(Token_getClass(pTokenLA)));
            }
            XCTAssertTrue( (LEX_SEP_SEMICOLON == Token_getClass(pTokenLA)) );
            pToken = Lex_TokenAdvance(pLex, 1);
            XCTAssertFalse( (OBJ_NIL == pToken) );
            XCTAssertTrue(  (pTokenLA == pToken) );

            pTokenLA = Lex_TokenLookAhead(pLex, 1);
            XCTAssertFalse( (OBJ_NIL == pTokenLA) );
            XCTAssertTrue( (Token_Validate(pTokenLA)) );
            {
                char            *pStrA = Token_getTextA(pTokenLA);
                fprintf(stderr, "Should be: \"char\"\n");
                fprintf(stderr, "Got:       \"%s\"\n",  pStrA);
                mem_Free(pStrA);
                pStrA = NULL;
                fprintf(stderr, "class=%s\n\n", Lex_ClassToString(Token_getClass(pTokenLA)));
            }
            XCTAssertTrue( (LEX_IDENTIFIER == Token_getClass(pTokenLA)) );
            pToken = Lex_TokenAdvance(pLex, 1);
            XCTAssertFalse( (OBJ_NIL == pToken) );
            XCTAssertTrue(  (pTokenLA == pToken) );

            pTokenLA = Lex_TokenLookAhead(pLex, 1);
            XCTAssertFalse( (OBJ_NIL == pTokenLA) );
            XCTAssertTrue( (Token_Validate(pTokenLA)) );
            {
                char            *pStrA = Token_getTextA(pTokenLA);
                fprintf(stderr, "Should be: \"*\"\n");
                fprintf(stderr, "Got:       \"%s\"\n",  pStrA);
                mem_Free(pStrA);
                pStrA = NULL;
                fprintf(stderr, "class=%s\n\n", Lex_ClassToString(Token_getClass(pTokenLA)));
            }
            XCTAssertTrue( (LEX_OP_MUL == Token_getClass(pTokenLA)) );
            pToken = Lex_TokenAdvance(pLex, 1);
            XCTAssertFalse( (OBJ_NIL == pToken) );
            XCTAssertTrue(  (pTokenLA == pToken) );

            pTokenLA = Lex_TokenLookAhead(pLex, 1);
            XCTAssertFalse( (OBJ_NIL == pTokenLA) );
            XCTAssertTrue( (Token_Validate(pTokenLA)) );
            {
                char            *pStrA = Token_getTextA(pTokenLA);
                fprintf(stderr, "Should be: \"pA\"\n");
                fprintf(stderr, "Got:       \"%s\"\n",  pStrA);
                mem_Free(pStrA);
                pStrA = NULL;
                fprintf(stderr, "class=%s\n\n", Lex_ClassToString(Token_getClass(pTokenLA)));
            }
            XCTAssertTrue( (LEX_IDENTIFIER == Token_getClass(pTokenLA)) );
            pToken = Lex_TokenAdvance(pLex, 1);
            XCTAssertFalse( (OBJ_NIL == pToken) );
            XCTAssertTrue(  (pTokenLA == pToken) );

            pTokenLA = Lex_TokenLookAhead(pLex, 1);
            XCTAssertFalse( (OBJ_NIL == pTokenLA) );
            XCTAssertTrue( (Token_Validate(pTokenLA)) );
            {
                char            *pStrA = Token_getTextA(pTokenLA);
                fprintf(stderr, "Should be: \";\"\n");
                fprintf(stderr, "Got:       \"%s\"\n",  pStrA);
                mem_Free(pStrA);
                pStrA = NULL;
                fprintf(stderr, "class=%s\n\n", Lex_ClassToString(Token_getClass(pTokenLA)));
            }
            XCTAssertTrue( (LEX_SEP_SEMICOLON == Token_getClass(pTokenLA)) );
            pToken = Lex_TokenAdvance(pLex, 1);
            XCTAssertFalse( (OBJ_NIL == pToken) );
            XCTAssertTrue(  (pTokenLA == pToken) );

            pTokenLA = Lex_TokenLookAhead(pLex, 1);
            XCTAssertFalse( (OBJ_NIL == pTokenLA) );
            XCTAssertTrue( (Token_Validate(pTokenLA)) );
            {
                char            *pStrA = Token_getTextA(pTokenLA);
                fprintf(stderr, "Should be: \"}\"\n");
                fprintf(stderr, "Got:       \"%s\"\n",  pStrA);
                mem_Free(pStrA);
                pStrA = NULL;
                fprintf(stderr, "class=%s\n\n", Lex_ClassToString(Token_getClass(pTokenLA)));
            }
            XCTAssertTrue( (LEX_SEP_RBRACE == Token_getClass(pTokenLA)) );
            pToken = Lex_TokenAdvance(pLex, 1);
            XCTAssertFalse( (OBJ_NIL == pToken) );
            XCTAssertTrue(  (pTokenLA == pToken) );

            pTokenLA = Lex_TokenLookAhead(pLex, 1);
            XCTAssertFalse( (OBJ_NIL == pTokenLA) );
            XCTAssertTrue( (Token_Validate(pTokenLA)) );
            {
                char            *pStrA = Token_getTextA(pTokenLA);
                fprintf(stderr, "Should be: \";\"\n");
                fprintf(stderr, "Got:       \"%s\"\n",  pStrA);
                mem_Free(pStrA);
                pStrA = NULL;
                fprintf(stderr, "class=%s\n\n", Lex_ClassToString(Token_getClass(pTokenLA)));
            }
            XCTAssertTrue( (LEX_SEP_SEMICOLON == Token_getClass(pTokenLA)) );
            pToken = Lex_TokenAdvance(pLex, 1);
            XCTAssertFalse( (OBJ_NIL == pToken) );
            XCTAssertTrue(  (pTokenLA == pToken) );

            obj_Release(pLex);
            pLex = OBJ_NIL;
        }

        obj_Release(pSrc);
        pSrc = OBJ_NIL;
    }

    obj_Release(pPath);
    pPath = OBJ_NIL;

    obj_Release(pStr);
    pStr = OBJ_NIL;

    fprintf(stderr, "...%s completed.\n\n\n", pTestName);
    return 1;
}



int         test_Lex_Input02(
    const
    char        *pTestName
)
{
    SRCFILE_DATA    *pSrc = OBJ_NIL;
    LEX_DATA        *pLex = OBJ_NIL;
    TOKEN_DATA      *pToken;
    TOKEN_DATA      *pTokenLA;
    bool            fRc;
    PATH_DATA       *pPath = Path_NewA("abc");
    const
    char            *pStrA = "a += b + c * d / e;";
    ASTR_DATA       *pStr = OBJ_NIL;

    fprintf(stderr, "Performing: %s\n", pTestName);

    pStr = AStr_NewA(pStrA);
    XCTAssertFalse( (OBJ_NIL == pStr) );

    pSrc = SrcFile_NewFromAStr(pPath, pStr, 1, 4);
    XCTAssertFalse( (OBJ_NIL == pSrc) );
    if (pSrc) {

        pLex = (LEX_DATA *)Lex_New();
        XCTAssertFalse( (OBJ_NIL == pLex) );
        if (pLex) {

            //obj_TraceSet(pSrc, true);
            obj_TraceSet(pLex, true);
            fRc =   Lex_setSourceInput(
                                          pLex,
                                          (void *)SrcFile_InputAdvance,
                                          (void *)SrcFile_InputLookAhead,
                                          pSrc
                    );
            XCTAssertTrue( (fRc) );

            pTokenLA = Lex_TokenLookAhead(pLex, 1);
            XCTAssertFalse( (OBJ_NIL == pTokenLA) );
            XCTAssertTrue( (Token_Validate(pTokenLA)) );
            {
                char            *pStrA = Token_getTextA(pTokenLA);
                fprintf(stderr, "Should be: \"a\"\n");
                fprintf(stderr, "Got:       \"%s\"\n",  pStrA);
                mem_Free(pStrA);
                pStrA = NULL;
                fprintf(stderr, "class=%s\n\n", Lex_ClassToString(Token_getClass(pTokenLA)));
            }
            XCTAssertTrue( (LEX_IDENTIFIER == Token_getClass(pTokenLA)) );
            {
                ASTR_DATA *pWrk = Token_ToDataString(pTokenLA);
                XCTAssertTrue( (0 == AStr_CompareA(pWrk, "a")) );
                obj_Release(pWrk);
                pWrk = OBJ_NIL;
            }
            pToken = Lex_TokenAdvance(pLex, 1);
            XCTAssertFalse( (OBJ_NIL == pToken) );
            XCTAssertTrue(  (pTokenLA == pToken) );

            pTokenLA = Lex_TokenLookAhead(pLex, 1);
            XCTAssertFalse( (OBJ_NIL == pTokenLA) );
            XCTAssertTrue( (Token_Validate(pTokenLA)) );
            {
                char            *pStrA = Token_getTextA(pTokenLA);
                fprintf(stderr, "Should be: \"+=\"\n");
                fprintf(stderr, "Got:       \"%s\"\n",  pStrA);
                mem_Free(pStrA);
                pStrA = NULL;
                fprintf(stderr, "class=%s\n\n", Lex_ClassToString(Token_getClass(pTokenLA)));
            }
            XCTAssertTrue( (LEX_OP_ASSIGN_ADD == Token_getClass(pTokenLA)) );
            {
                ASTR_DATA *pWrk = Token_ToDataString(pTokenLA);
                XCTAssertTrue( (0 == AStr_CompareA(pWrk, "+=")) );
                obj_Release(pWrk);
                pWrk = OBJ_NIL;
            }
            pToken = Lex_TokenAdvance(pLex, 1);
            XCTAssertFalse( (OBJ_NIL == pToken) );
            XCTAssertTrue(  (pTokenLA == pToken) );

            pTokenLA = Lex_TokenLookAhead(pLex, 1);
            XCTAssertFalse( (OBJ_NIL == pTokenLA) );
            XCTAssertTrue( (Token_Validate(pTokenLA)) );
            {
                char            *pStrA = Token_getTextA(pTokenLA);
                fprintf(stderr, "Should be: \"b\"\n");
                fprintf(stderr, "Got:       \"%s\"\n",  pStrA);
                mem_Free(pStrA);
                pStrA = NULL;
                fprintf(stderr, "class=%s\n\n", Lex_ClassToString(Token_getClass(pTokenLA)));
            }
            XCTAssertTrue( (LEX_IDENTIFIER == Token_getClass(pTokenLA)) );
            {
                ASTR_DATA *pWrk = Token_ToDataString(pTokenLA);
                XCTAssertTrue( (0 == AStr_CompareA(pWrk, "b")) );
                obj_Release(pWrk);
                pWrk = OBJ_NIL;
            }
            pToken = Lex_TokenAdvance(pLex, 1);
            XCTAssertFalse( (OBJ_NIL == pToken) );
            XCTAssertTrue(  (pTokenLA == pToken) );

            pTokenLA = Lex_TokenLookAhead(pLex, 1);
            XCTAssertFalse( (OBJ_NIL == pTokenLA) );
            XCTAssertTrue( (Token_Validate(pTokenLA)) );
            {
                char            *pStrA = Token_getTextA(pTokenLA);
                fprintf(stderr, "Should be: \"+\"\n");
                fprintf(stderr, "Got:       \"%s\"\n",  pStrA);
                mem_Free(pStrA);
                pStrA = NULL;
                fprintf(stderr, "class=%s\n\n", Lex_ClassToString(Token_getClass(pTokenLA)));
            }
            XCTAssertTrue( (LEX_OP_ADD == Token_getClass(pTokenLA)) );
            {
                ASTR_DATA *pWrk = Token_ToDataString(pTokenLA);
                XCTAssertTrue( (0 == AStr_CompareA(pWrk, "+")) );
                obj_Release(pWrk);
                pWrk = OBJ_NIL;
            }
            pToken = Lex_TokenAdvance(pLex, 1);
            XCTAssertFalse( (OBJ_NIL == pToken) );
            XCTAssertTrue(  (pTokenLA == pToken) );

            pTokenLA = Lex_TokenLookAhead(pLex, 1);
            XCTAssertFalse( (OBJ_NIL == pTokenLA) );
            XCTAssertTrue( (Token_Validate(pTokenLA)) );
            {
                char            *pStrA = Token_getTextA(pTokenLA);
                fprintf(stderr, "Should be: \"c\"\n");
                fprintf(stderr, "Got:       \"%s\"\n",  pStrA);
                mem_Free(pStrA);
                pStrA = NULL;
                fprintf(stderr, "class=%s\n\n", Lex_ClassToString(Token_getClass(pTokenLA)));
            }
            XCTAssertTrue( (LEX_IDENTIFIER == Token_getClass(pTokenLA)) );
            {
                ASTR_DATA *pWrk = Token_ToDataString(pTokenLA);
                XCTAssertTrue( (0 == AStr_CompareA(pWrk, "c")) );
                obj_Release(pWrk);
                pWrk = OBJ_NIL;
            }
            pToken = Lex_TokenAdvance(pLex, 1);
            XCTAssertFalse( (OBJ_NIL == pToken) );
            XCTAssertTrue(  (pTokenLA == pToken) );

            pTokenLA = Lex_TokenLookAhead(pLex, 1);
            XCTAssertFalse( (OBJ_NIL == pTokenLA) );
            XCTAssertTrue( (Token_Validate(pTokenLA)) );
            {
                char            *pStrA = Token_getTextA(pTokenLA);
                fprintf(stderr, "Should be: \"*\"\n");
                fprintf(stderr, "Got:       \"%s\"\n",  pStrA);
                mem_Free(pStrA);
                pStrA = NULL;
                fprintf(stderr, "class=%s\n\n", Lex_ClassToString(Token_getClass(pTokenLA)));
            }
            XCTAssertTrue( (LEX_OP_MUL == Token_getClass(pTokenLA)) );
            pToken = Lex_TokenAdvance(pLex, 1);
            XCTAssertFalse( (OBJ_NIL == pToken) );
            XCTAssertTrue(  (pTokenLA == pToken) );

            pTokenLA = Lex_TokenLookAhead(pLex, 1);
            XCTAssertFalse( (OBJ_NIL == pTokenLA) );
            XCTAssertTrue( (Token_Validate(pTokenLA)) );
            {
                char            *pStrA = Token_getTextA(pTokenLA);
                fprintf(stderr, "Should be: \"d\"\n");
                fprintf(stderr, "Got:       \"%s\"\n",  pStrA);
                mem_Free(pStrA);
                pStrA = NULL;
                fprintf(stderr, "class=%s\n\n", Lex_ClassToString(Token_getClass(pTokenLA)));
            }
            XCTAssertTrue( (LEX_IDENTIFIER == Token_getClass(pTokenLA)) );
            pToken = Lex_TokenAdvance(pLex, 1);
            XCTAssertFalse( (OBJ_NIL == pToken) );
            XCTAssertTrue(  (pTokenLA == pToken) );

            pTokenLA = Lex_TokenLookAhead(pLex, 1);
            XCTAssertFalse( (OBJ_NIL == pTokenLA) );
            XCTAssertTrue( (Token_Validate(pTokenLA)) );
            {
                char            *pStrA = Token_getTextA(pTokenLA);
                fprintf(stderr, "Should be: \"/\"\n");
                fprintf(stderr, "Got:       \"%s\"\n",  pStrA);
                mem_Free(pStrA);
                pStrA = NULL;
                fprintf(stderr, "class=%s\n\n", Lex_ClassToString(Token_getClass(pTokenLA)));
            }
            XCTAssertTrue( (LEX_OP_DIV == Token_getClass(pTokenLA)) );
            pToken = Lex_TokenAdvance(pLex, 1);
            XCTAssertFalse( (OBJ_NIL == pToken) );
            XCTAssertTrue(  (pTokenLA == pToken) );

            pTokenLA = Lex_TokenLookAhead(pLex, 1);
            XCTAssertFalse( (OBJ_NIL == pTokenLA) );
            XCTAssertTrue( (Token_Validate(pTokenLA)) );
            {
                char            *pStrA = Token_getTextA(pTokenLA);
                fprintf(stderr, "Should be: \"e\"\n");
                fprintf(stderr, "Got:       \"%s\"\n",  pStrA);
                mem_Free(pStrA);
                pStrA = NULL;
                fprintf(stderr, "class=%s\n\n", Lex_ClassToString(Token_getClass(pTokenLA)));
            }
            XCTAssertTrue( (LEX_IDENTIFIER == Token_getClass(pTokenLA)) );
            pToken = Lex_TokenAdvance(pLex, 1);
            XCTAssertFalse( (OBJ_NIL == pToken) );
            XCTAssertTrue(  (pTokenLA == pToken) );

            pTokenLA = Lex_TokenLookAhead(pLex, 1);
            XCTAssertFalse( (OBJ_NIL == pTokenLA) );
            XCTAssertTrue( (Token_Validate(pTokenLA)) );
            {
                char            *pStrA = Token_getTextA(pTokenLA);
                fprintf(stderr, "Should be: \";\"\n");
                fprintf(stderr, "Got:       \"%s\"\n",  pStrA);
                mem_Free(pStrA);
                pStrA = NULL;
                fprintf(stderr, "class=%s\n\n", Lex_ClassToString(Token_getClass(pTokenLA)));
            }
            XCTAssertTrue( (LEX_SEP_SEMICOLON == Token_getClass(pTokenLA)) );
            pToken = Lex_TokenAdvance(pLex, 1);
            XCTAssertFalse( (OBJ_NIL == pToken) );
            XCTAssertTrue(  (pTokenLA == pToken) );

            obj_Release(pLex);
            pLex = OBJ_NIL;
        }

        obj_Release(pSrc);
        pSrc = OBJ_NIL;
    }

    obj_Release(pPath);
    pPath = OBJ_NIL;

    obj_Release(pStr);
    pStr = OBJ_NIL;

    fprintf(stderr, "...%s completed.\n\n\n", pTestName);
    return 1;
}



int         test_Lex_Input03(
    const
    char        *pTestName
)
{
    SRCFILE_DATA    *pSrc = OBJ_NIL;
    LEX_DATA        *pLex = OBJ_NIL;
    TOKEN_DATA      *pToken;
    TOKEN_DATA      *pTokenLA;
    bool            fRc;
    PATH_DATA       *pPath = Path_NewA("abc");
    const
    char            *pStrA = "-= *= /= %= |= &= ^= <<= >>= ;";
    ASTR_DATA       *pStr = OBJ_NIL;

    fprintf(stderr, "Performing: %s\n", pTestName);

    pStr = AStr_NewA(pStrA);
    XCTAssertFalse( (OBJ_NIL == pStr) );

    pSrc = SrcFile_NewFromAStr(pPath, pStr, 1, 4);
    XCTAssertFalse( (OBJ_NIL == pSrc) );
    if (pSrc) {

        pLex = (LEX_DATA *)Lex_New();
        XCTAssertFalse( (OBJ_NIL == pLex) );
        if (pLex) {

            //obj_TraceSet(pSrc, true);
            obj_TraceSet(pLex, true);
            fRc =   Lex_setSourceInput(
                                          pLex,
                                          (void *)SrcFile_InputAdvance,
                                          (void *)SrcFile_InputLookAhead,
                                          pSrc
                    );
            XCTAssertTrue( (fRc) );

            pTokenLA = Lex_TokenLookAhead(pLex, 1);
            XCTAssertFalse( (OBJ_NIL == pTokenLA) );
            XCTAssertTrue( (Token_Validate(pTokenLA)) );
            {
                char            *pStrA = Token_getTextA(pTokenLA);
                fprintf(stderr, "Should be: \"-=\"\n");
                fprintf(stderr, "Got:       \"%s\"\n",  pStrA);
                mem_Free(pStrA);
                pStrA = NULL;
                fprintf(stderr, "class=%s\n\n", Lex_ClassToString(Token_getClass(pTokenLA)));
            }
            XCTAssertTrue( (LEX_OP_ASSIGN_SUB == Token_getClass(pTokenLA)) );
            {
                ASTR_DATA *pWrk = Token_ToDataString(pTokenLA);
                XCTAssertTrue( (0 == AStr_CompareA(pWrk, "-=")) );
                obj_Release(pWrk);
                pWrk = OBJ_NIL;
            }
            pToken = Lex_TokenAdvance(pLex, 1);
            XCTAssertFalse( (OBJ_NIL == pToken) );
            XCTAssertTrue(  (pTokenLA == pToken) );

            pTokenLA = Lex_TokenLookAhead(pLex, 1);
            XCTAssertFalse( (OBJ_NIL == pTokenLA) );
            XCTAssertTrue( (Token_Validate(pTokenLA)) );
            {
                char            *pStrA = Token_getTextA(pTokenLA);
                fprintf(stderr, "Should be: \"*=\"\n");
                fprintf(stderr, "Got:       \"%s\"\n",  pStrA);
                mem_Free(pStrA);
                pStrA = NULL;
                fprintf(stderr, "class=%s\n\n", Lex_ClassToString(Token_getClass(pTokenLA)));
            }
            XCTAssertTrue( (LEX_OP_ASSIGN_MUL == Token_getClass(pTokenLA)) );
            {
                ASTR_DATA *pWrk = Token_ToDataString(pTokenLA);
                XCTAssertTrue( (0 == AStr_CompareA(pWrk, "*=")) );
                obj_Release(pWrk);
                pWrk = OBJ_NIL;
            }
            pToken = Lex_TokenAdvance(pLex, 1);
            XCTAssertFalse( (OBJ_NIL == pToken) );
            XCTAssertTrue(  (pTokenLA == pToken) );

            pTokenLA = Lex_TokenLookAhead(pLex, 1);
            XCTAssertFalse( (OBJ_NIL == pTokenLA) );
            XCTAssertTrue( (Token_Validate(pTokenLA)) );
            {
                char            *pStrA = Token_getTextA(pTokenLA);
                fprintf(stderr, "Should be: \"/=\"\n");
                fprintf(stderr, "Got:       \"%s\"\n",  pStrA);
                mem_Free(pStrA);
                pStrA = NULL;
                fprintf(stderr, "class=%s\n\n", Lex_ClassToString(Token_getClass(pTokenLA)));
            }
            XCTAssertTrue( (LEX_OP_ASSIGN_DIV == Token_getClass(pTokenLA)) );
            {
                ASTR_DATA *pWrk = Token_ToDataString(pTokenLA);
                XCTAssertTrue( (0 == AStr_CompareA(pWrk, "/=")) );
                obj_Release(pWrk);
                pWrk = OBJ_NIL;
            }
            pToken = Lex_TokenAdvance(pLex, 1);
            XCTAssertFalse( (OBJ_NIL == pToken) );
            XCTAssertTrue(  (pTokenLA == pToken) );

            pTokenLA = Lex_TokenLookAhead(pLex, 1);
            XCTAssertFalse( (OBJ_NIL == pTokenLA) );
            XCTAssertTrue( (Token_Validate(pTokenLA)) );
            {
                char            *pStrA = Token_getTextA(pTokenLA);
                fprintf(stderr, "Should be: \"%%=\"\n");
                fprintf(stderr, "Got:       \"%s\"\n",  pStrA);
                mem_Free(pStrA);
                pStrA = NULL;
                fprintf(stderr, "class=%s\n\n", Lex_ClassToString(Token_getClass(pTokenLA)));
            }
            XCTAssertTrue( (LEX_OP_ASSIGN_MOD == Token_getClass(pTokenLA)) );
            {
                ASTR_DATA *pWrk = Token_ToDataString(pTokenLA);
                XCTAssertTrue( (0 == AStr_CompareA(pWrk, "%=")) );
                obj_Release(pWrk);
                pWrk = OBJ_NIL;
            }
            pToken = Lex_TokenAdvance(pLex, 1);
            XCTAssertFalse( (OBJ_NIL == pToken) );
            XCTAssertTrue(  (pTokenLA == pToken) );

            pTokenLA = Lex_TokenLookAhead(pLex, 1);
            XCTAssertFalse( (OBJ_NIL == pTokenLA) );
            XCTAssertTrue( (Token_Validate(pTokenLA)) );
            {
                char            *pStrA = Token_getTextA(pTokenLA);
                fprintf(stderr, "Should be: \"|=\"\n");
                fprintf(stderr, "Got:       \"%s\"\n",  pStrA);
                mem_Free(pStrA);
                pStrA = NULL;
                fprintf(stderr, "class=%s\n\n", Lex_ClassToString(Token_getClass(pTokenLA)));
            }
            XCTAssertTrue( (LEX_OP_ASSIGN_OR == Token_getClass(pTokenLA)) );
            {
                ASTR_DATA *pWrk = Token_ToDataString(pTokenLA);
                XCTAssertTrue( (0 == AStr_CompareA(pWrk, "|=")) );
                obj_Release(pWrk);
                pWrk = OBJ_NIL;
            }
            pToken = Lex_TokenAdvance(pLex, 1);
            XCTAssertFalse( (OBJ_NIL == pToken) );
            XCTAssertTrue(  (pTokenLA == pToken) );

            pTokenLA = Lex_TokenLookAhead(pLex, 1);
            XCTAssertFalse( (OBJ_NIL == pTokenLA) );
            XCTAssertTrue( (Token_Validate(pTokenLA)) );
            {
                char            *pStrA = Token_getTextA(pTokenLA);
                fprintf(stderr, "Should be: \"&=\"\n");
                fprintf(stderr, "Got:       \"%s\"\n",  pStrA);
                mem_Free(pStrA);
                pStrA = NULL;
                fprintf(stderr, "class=%s\n\n", Lex_ClassToString(Token_getClass(pTokenLA)));
            }
            XCTAssertTrue( (LEX_OP_ASSIGN_AND == Token_getClass(pTokenLA)) );
            pToken = Lex_TokenAdvance(pLex, 1);
            XCTAssertFalse( (OBJ_NIL == pToken) );
            XCTAssertTrue(  (pTokenLA == pToken) );

            pTokenLA = Lex_TokenLookAhead(pLex, 1);
            XCTAssertFalse( (OBJ_NIL == pTokenLA) );
            XCTAssertTrue( (Token_Validate(pTokenLA)) );
            {
                char            *pStrA = Token_getTextA(pTokenLA);
                fprintf(stderr, "Should be: \"^=\"\n");
                fprintf(stderr, "Got:       \"%s\"\n",  pStrA);
                mem_Free(pStrA);
                pStrA = NULL;
                fprintf(stderr, "class=%s\n\n", Lex_ClassToString(Token_getClass(pTokenLA)));
            }
            XCTAssertTrue( (LEX_OP_ASSIGN_XOR == Token_getClass(pTokenLA)) );
            pToken = Lex_TokenAdvance(pLex, 1);
            XCTAssertFalse( (OBJ_NIL == pToken) );
            XCTAssertTrue(  (pTokenLA == pToken) );

            pTokenLA = Lex_TokenLookAhead(pLex, 1);
            XCTAssertFalse( (OBJ_NIL == pTokenLA) );
            XCTAssertTrue( (Token_Validate(pTokenLA)) );
            {
                char            *pStrA = Token_getTextA(pTokenLA);
                fprintf(stderr, "Should be: \"<<=\"\n");
                fprintf(stderr, "Got:       \"%s\"\n",  pStrA);
                mem_Free(pStrA);
                pStrA = NULL;
                fprintf(stderr, "class=%s\n\n", Lex_ClassToString(Token_getClass(pTokenLA)));
            }
            XCTAssertTrue( (LEX_OP_ASSIGN_LEFT == Token_getClass(pTokenLA)) );
            pToken = Lex_TokenAdvance(pLex, 1);
            XCTAssertFalse( (OBJ_NIL == pToken) );
            XCTAssertTrue(  (pTokenLA == pToken) );

            pTokenLA = Lex_TokenLookAhead(pLex, 1);
            XCTAssertFalse( (OBJ_NIL == pTokenLA) );
            XCTAssertTrue( (Token_Validate(pTokenLA)) );
            {
                char            *pStrA = Token_getTextA(pTokenLA);
                fprintf(stderr, "Should be: \">>=\"\n");
                fprintf(stderr, "Got:       \"%s\"\n",  pStrA);
                mem_Free(pStrA);
                pStrA = NULL;
                fprintf(stderr, "class=%s\n\n", Lex_ClassToString(Token_getClass(pTokenLA)));
            }
            XCTAssertTrue( (LEX_OP_ASSIGN_RIGHT == Token_getClass(pTokenLA)) );
            pToken = Lex_TokenAdvance(pLex, 1);
            XCTAssertFalse( (OBJ_NIL == pToken) );
            XCTAssertTrue(  (pTokenLA == pToken) );

            pTokenLA = Lex_TokenLookAhead(pLex, 1);
            XCTAssertFalse( (OBJ_NIL == pTokenLA) );
            XCTAssertTrue( (Token_Validate(pTokenLA)) );
            {
                char            *pStrA = Token_getTextA(pTokenLA);
                fprintf(stderr, "Should be: \";\"\n");
                fprintf(stderr, "Got:       \"%s\"\n",  pStrA);
                mem_Free(pStrA);
                pStrA = NULL;
                fprintf(stderr, "class=%s\n\n", Lex_ClassToString(Token_getClass(pTokenLA)));
            }
            XCTAssertTrue( (LEX_SEP_SEMICOLON == Token_getClass(pTokenLA)) );
            pToken = Lex_TokenAdvance(pLex, 1);
            XCTAssertFalse( (OBJ_NIL == pToken) );
            XCTAssertTrue(  (pTokenLA == pToken) );

            obj_Release(pLex);
            pLex = OBJ_NIL;
        }

        obj_Release(pSrc);
        pSrc = OBJ_NIL;
    }

    obj_Release(pPath);
    pPath = OBJ_NIL;

    obj_Release(pStr);
    pStr = OBJ_NIL;

    fprintf(stderr, "...%s completed.\n\n\n", pTestName);
    return 1;
}



int         test_Lex_Comment01(
    const
    char        *pTestName
)
{
    SRCFILE_DATA    *pSrc = OBJ_NIL;
    ASTR_DATA       *pBuf = OBJ_NIL;
    LEX_DATA        *pLex = OBJ_NIL;
    TOKEN_DATA      *pToken;
    TOKEN_DATA      *pTokenLA;
    bool            fRc;
    PATH_DATA       *pPath = Path_NewA("abc");

    fprintf(stderr, "Performing: %s\n", pTestName);
    pBuf = AStr_NewA("// hi\n");
    XCTAssertFalse( (OBJ_NIL == pBuf) );
    if (pBuf) {

        pSrc = SrcFile_NewFromAStr(pPath, pBuf, 1, 4);
        XCTAssertFalse( (OBJ_NIL == pSrc) );
        if (pSrc) {

            pLex = (LEX_DATA *)Lex_New();
            XCTAssertFalse( (OBJ_NIL == pLex) );
            if (pLex) {

                obj_TraceSet(pLex, true);
                fRc =   Lex_setSourceInput(
                                              pLex,
                                              (void *)SrcFile_InputAdvance,
                                              (void *)SrcFile_InputLookAhead,
                                              pSrc
                                              );
                XCTAssertTrue( (fRc) );
                Lex_setFlags(pLex, (Lex_getFlags(pLex) | LEX_FLAG_NL));

                pTokenLA = Lex_TokenLookAhead(pLex, 1);
                XCTAssertFalse( (OBJ_NIL == pTokenLA) );
                XCTAssertTrue( (Token_Validate(pTokenLA)) );
                {
                    char            *pStrA = Token_getTextA(pTokenLA);
                    fprintf(stderr, "Should be: \"\\n\"\n");
                    fprintf(stderr, "Got:       \"%s\"\n",  pStrA);
                    mem_Free(pStrA);
                    pStrA = NULL;
                    fprintf(stderr, "class=%s\n\n", Lex_ClassToString(Token_getClass(pTokenLA)));
                }
                XCTAssertTrue( (LEX_SEP_NL == Token_getClass(pTokenLA)) );
                {
                    ASTR_DATA *pWrk = Token_ToDataString(pTokenLA);
                    XCTAssertTrue( (0 == AStr_CompareA(pWrk, "\\n")) );
                    obj_Release(pWrk);
                    pWrk = OBJ_NIL;
                }
                pToken = Lex_TokenAdvance(pLex, 1);
                XCTAssertFalse( (OBJ_NIL == pToken) );
                XCTAssertTrue(  (pTokenLA == pToken) );

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

    fprintf(stderr, "...%s completed.\n\n\n", pTestName);
    return 1;
}



int         test_Lex_Comment02(
    const
    char        *pTestName
)
{
    SRCFILE_DATA    *pSrc = OBJ_NIL;
    ASTR_DATA       *pBuf = OBJ_NIL;
    LEX_DATA        *pLex = OBJ_NIL;
    TOKEN_DATA      *pToken;
    TOKEN_DATA      *pTokenLA;
    bool            fRc;
    PATH_DATA       *pPath = Path_NewA("abc");

    fprintf(stderr, "Performing: %s\n", pTestName);
    pBuf = AStr_NewA("// hi\n");
    XCTAssertFalse( (OBJ_NIL == pBuf) );
    if (pBuf) {

        pSrc = SrcFile_NewFromAStr(pPath, pBuf, 1, 4);
        XCTAssertFalse( (OBJ_NIL == pSrc) );
        if (pSrc) {

            pLex = (LEX_DATA *)Lex_New();
            XCTAssertFalse( (OBJ_NIL == pLex) );
            if (pLex) {

                obj_TraceSet(pLex, true);
                fRc =   Lex_setSourceInput(
                                              pLex,
                                              (void *)SrcFile_InputAdvance,
                                              (void *)SrcFile_InputLookAhead,
                                              pSrc
                                              );
                XCTAssertTrue( (fRc) );

                Lex_setFlags(pLex, (Lex_getFlags(pLex) | LEX_FLAG_CMT | LEX_FLAG_NL));
                pTokenLA = Lex_TokenLookAhead(pLex, 1);
                XCTAssertFalse( (OBJ_NIL == pTokenLA) );
                XCTAssertTrue( (Token_Validate(pTokenLA)) );
                {
                    char            *pStrA = Token_getTextA(pTokenLA);
                    fprintf(stderr, "Should be: \"// hi\"\n");
                    fprintf(stderr, "Got:       \"%s\"\n",  pStrA);
                    mem_Free(pStrA);
                    pStrA = NULL;
                    fprintf(stderr, "class=%s\n\n", Lex_ClassToString(Token_getClass(pTokenLA)));
                }
                XCTAssertTrue( (LEX_COMMENT_SINGLE == Token_getClass(pTokenLA)) );
                {
                    ASTR_DATA *pWrk = Token_ToDataString(pTokenLA);
                    XCTAssertTrue( (0 == AStr_CompareA(pWrk, "// hi")) );
                    obj_Release(pWrk);
                    pWrk = OBJ_NIL;
                }
                pToken = Lex_TokenAdvance(pLex, 1);
                XCTAssertFalse( (OBJ_NIL == pToken) );
                XCTAssertTrue(  (pTokenLA == pToken) );

                Lex_setFlags(pLex, (Lex_getFlags(pLex) | LEX_FLAG_CMT));
                pTokenLA = Lex_TokenLookAhead(pLex, 1);
                XCTAssertFalse( (OBJ_NIL == pTokenLA) );
                XCTAssertTrue( (Token_Validate(pTokenLA)) );
                {
                    char            *pStrA = Token_getTextA(pTokenLA);
                    fprintf(stderr, "Should be: \"\\n\"\n");
                    fprintf(stderr, "Got:       \"%s\"\n",  pStrA);
                    mem_Free(pStrA);
                    pStrA = NULL;
                    fprintf(stderr, "class=%s\n\n", Lex_ClassToString(Token_getClass(pTokenLA)));
                }
                XCTAssertTrue( (LEX_SEP_NL == Token_getClass(pTokenLA)) );
                {
                    ASTR_DATA *pWrk = Token_ToDataString(pTokenLA);
                    XCTAssertTrue( (0 == AStr_CompareA(pWrk, "\\n")) );
                    obj_Release(pWrk);
                    pWrk = OBJ_NIL;
                }
                pToken = Lex_TokenAdvance(pLex, 1);
                XCTAssertFalse( (OBJ_NIL == pToken) );
                XCTAssertTrue(  (pTokenLA == pToken) );

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

    fprintf(stderr, "...%s completed.\n\n\n", pTestName);
    return 1;
}



int         test_Lex_Comment03(
    const
    char        *pTestName
)
{
    SRCFILE_DATA    *pSrc = OBJ_NIL;
    ASTR_DATA       *pBuf = OBJ_NIL;
    LEX_DATA        *pLex = OBJ_NIL;
    TOKEN_DATA      *pToken;
    TOKEN_DATA      *pTokenLA;
    bool            fRc;
    PATH_DATA       *pPath = Path_NewA("abc");

    fprintf(stderr, "Performing: %s\n", pTestName);
    pBuf = AStr_NewA("/* hi */\n");
    XCTAssertFalse( (OBJ_NIL == pBuf) );
    if (pBuf) {

        pSrc = SrcFile_NewFromAStr(pPath, pBuf, 1, 4);
        XCTAssertFalse( (OBJ_NIL == pSrc) );
        if (pSrc) {

            pLex = (LEX_DATA *)Lex_New();
            XCTAssertFalse( (OBJ_NIL == pLex) );
            if (pLex) {

                obj_TraceSet(pLex, true);
                fRc =   Lex_setSourceInput(
                                              pLex,
                                              (void *)SrcFile_InputAdvance,
                                              (void *)SrcFile_InputLookAhead,
                                              pSrc
                                              );
                XCTAssertTrue( (fRc) );

                Lex_setFlags(pLex, (Lex_getFlags(pLex) | LEX_FLAG_CMT | LEX_FLAG_NL));
                pTokenLA = Lex_TokenLookAhead(pLex, 1);
                XCTAssertFalse( (OBJ_NIL == pTokenLA) );
                XCTAssertTrue( (Token_Validate(pTokenLA)) );
                {
                    char            *pStrA = Token_getTextA(pTokenLA);
                    fprintf(stderr, "Should be: \"/* hi */\"\n");
                    fprintf(stderr, "Got:       \"%s\"\n",  pStrA);
                    mem_Free(pStrA);
                    pStrA = NULL;
                    fprintf(stderr, "class=%s\n\n", Lex_ClassToString(Token_getClass(pTokenLA)));
                }
                XCTAssertTrue( (LEX_COMMENT_MULTI == Token_getClass(pTokenLA)) );
                {
                    ASTR_DATA *pWrk = Token_ToDataString(pTokenLA);
                    XCTAssertTrue( (0 == AStr_CompareA(pWrk, "/* hi */")) );
                    obj_Release(pWrk);
                    pWrk = OBJ_NIL;
                }
                pToken = Lex_TokenAdvance(pLex, 1);
                XCTAssertFalse( (OBJ_NIL == pToken) );
                XCTAssertTrue(  (pTokenLA == pToken) );

                Lex_setFlags(pLex, (Lex_getFlags(pLex) | LEX_FLAG_CMT));
                pTokenLA = Lex_TokenLookAhead(pLex, 1);
                XCTAssertFalse( (OBJ_NIL == pTokenLA) );
                XCTAssertTrue( (Token_Validate(pTokenLA)) );
                {
                    char            *pStrA = Token_getTextA(pTokenLA);
                    fprintf(stderr, "Should be: \"\\n\"\n");
                    fprintf(stderr, "Got:       \"%s\"\n",  pStrA);
                    mem_Free(pStrA);
                    pStrA = NULL;
                    fprintf(stderr, "class=%s\n\n", Lex_ClassToString(Token_getClass(pTokenLA)));
                }
                XCTAssertTrue( (LEX_SEP_NL == Token_getClass(pTokenLA)) );
                {
                    ASTR_DATA *pWrk = Token_ToDataString(pTokenLA);
                    XCTAssertTrue( (0 == AStr_CompareA(pWrk, "\\n")) );
                    obj_Release(pWrk);
                    pWrk = OBJ_NIL;
                }
                pToken = Lex_TokenAdvance(pLex, 1);
                XCTAssertFalse( (OBJ_NIL == pToken) );
                XCTAssertTrue(  (pTokenLA == pToken) );

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

    fprintf(stderr, "...%s completed.\n\n\n", pTestName);
    return 1;
}



int         test_Lex_Comment04(
    const
    char        *pTestName
)
{
    SRCFILE_DATA    *pSrc = OBJ_NIL;
    ASTR_DATA       *pBuf = OBJ_NIL;
    LEX_DATA        *pLex = OBJ_NIL;
    TOKEN_DATA      *pToken;
    TOKEN_DATA      *pTokenLA;
    bool            fRc;
    PATH_DATA       *pPath = Path_NewA("abc");
    static
    const
    char            *pInput = "/*** /** /* // */ **/ ***/";

    fprintf(stderr, "Performing: %s\n", pTestName);
    pBuf = AStr_NewA(pInput);
    XCTAssertFalse( (OBJ_NIL == pBuf) );
    AStr_AppendA(pBuf, "\n");
    if (pBuf) {

        pSrc = SrcFile_NewFromAStr(pPath, pBuf, 1, 4);
        XCTAssertFalse( (OBJ_NIL == pSrc) );
        if (pSrc) {

            pLex = (LEX_DATA *)Lex_New();
            XCTAssertFalse( (OBJ_NIL == pLex) );
            if (pLex) {

                obj_TraceSet(pLex, true);
                fRc =   Lex_setSourceInput(
                                              pLex,
                                              (void *)SrcFile_InputAdvance,
                                              (void *)SrcFile_InputLookAhead,
                                              pSrc
                                              );
                XCTAssertTrue( (fRc) );

                Lex_setFlags(pLex, (Lex_getFlags(pLex) | LEX_FLAG_CMT | LEX_FLAG_NL));
                pTokenLA = Lex_TokenLookAhead(pLex, 1);
                XCTAssertFalse( (OBJ_NIL == pTokenLA) );
                XCTAssertTrue( (Token_Validate(pTokenLA)) );
                {
                    char            *pStrA = Token_getTextA(pTokenLA);
                    fprintf(stderr, "Should be: \"%s\"\n", pInput);
                    fprintf(stderr, "Got:       \"%s\"\n",  pStrA);
                    mem_Free(pStrA);
                    pStrA = NULL;
                    fprintf(stderr, "class=%s\n\n", Lex_ClassToString(Token_getClass(pTokenLA)));
                }
                XCTAssertTrue( (LEX_COMMENT_MULTI == Token_getClass(pTokenLA)) );
                {
                    ASTR_DATA *pWrk = Token_ToDataString(pTokenLA);
                    XCTAssertTrue( (0 == AStr_CompareA(pWrk, pInput)) );
                    obj_Release(pWrk);
                    pWrk = OBJ_NIL;
                }
                pToken = Lex_TokenAdvance(pLex, 1);
                XCTAssertFalse( (OBJ_NIL == pToken) );
                XCTAssertTrue(  (pTokenLA == pToken) );

                Lex_setFlags(pLex, (Lex_getFlags(pLex) | LEX_FLAG_CMT));
                pTokenLA = Lex_TokenLookAhead(pLex, 1);
                XCTAssertFalse( (OBJ_NIL == pTokenLA) );
                XCTAssertTrue( (Token_Validate(pTokenLA)) );
                {
                    char            *pStrA = Token_getTextA(pTokenLA);
                    fprintf(stderr, "Should be: \"\\n\"\n");
                    fprintf(stderr, "Got:       \"%s\"\n",  pStrA);
                    mem_Free(pStrA);
                    pStrA = NULL;
                    fprintf(stderr, "class=%s\n\n", Lex_ClassToString(Token_getClass(pTokenLA)));
                }
                XCTAssertTrue( (LEX_SEP_NL == Token_getClass(pTokenLA)) );
                {
                    ASTR_DATA *pWrk = Token_ToDataString(pTokenLA);
                    XCTAssertTrue( (0 == AStr_CompareA(pWrk, "\\n")) );
                    obj_Release(pWrk);
                    pWrk = OBJ_NIL;
                }
                pToken = Lex_TokenAdvance(pLex, 1);
                XCTAssertFalse( (OBJ_NIL == pToken) );
                XCTAssertTrue(  (pTokenLA == pToken) );

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

    fprintf(stderr, "...%s completed.\n\n\n", pTestName);
    return 1;
}




TINYTEST_START_SUITE(test_Lex);
    TINYTEST_ADD_TEST(test_Lex_Comment04,setUp,tearDown);
    TINYTEST_ADD_TEST(test_Lex_Comment03,setUp,tearDown);
    TINYTEST_ADD_TEST(test_Lex_Comment02,setUp,tearDown);
    TINYTEST_ADD_TEST(test_Lex_Comment01,setUp,tearDown);
    TINYTEST_ADD_TEST(test_Lex_Input03,setUp,tearDown);
    TINYTEST_ADD_TEST(test_Lex_Input02,setUp,tearDown);
    TINYTEST_ADD_TEST(test_Lex_Input01,setUp,tearDown);
    //TINYTEST_ADD_TEST(test_Lex_Strings04,setUp,tearDown);
    TINYTEST_ADD_TEST(test_Lex_Strings03,setUp,tearDown);
    TINYTEST_ADD_TEST(test_Lex_Strings02,setUp,tearDown);
    TINYTEST_ADD_TEST(test_Lex_Strings01,setUp,tearDown);
    TINYTEST_ADD_TEST(test_Lex_Number07,setUp,tearDown);
    TINYTEST_ADD_TEST(test_Lex_Number06,setUp,tearDown);
    TINYTEST_ADD_TEST(test_Lex_Number05,setUp,tearDown);
    TINYTEST_ADD_TEST(test_Lex_Number04,setUp,tearDown);
    TINYTEST_ADD_TEST(test_Lex_Number03,setUp,tearDown);
    TINYTEST_ADD_TEST(test_Lex_Number02,setUp,tearDown);
    TINYTEST_ADD_TEST(test_Lex_Number01,setUp,tearDown);
    TINYTEST_ADD_TEST(test_Lex_Identifier01,setUp,tearDown);
    TINYTEST_ADD_TEST(test_Lex_Test01,setUp,tearDown);
    //TINYTEST_ADD_TEST(test_Lex_Copy01,setUp,tearDown);
    TINYTEST_ADD_TEST(test_Lex_OpenClose,setUp,tearDown);
TINYTEST_END_SUITE();

TINYTEST_MAIN_SINGLE_SUITE(test_Lex);





