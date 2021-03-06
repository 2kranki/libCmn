// vi:nu:et:sts=4 ts=4 sw=4
/*
 *  Generated 05/30/2020 14:52:09
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
#include    <Lex02_internal.h>
#include    <SrcErrors.h>
#include    <szTbl.h>
#include    <SrcFile.h>
#include    <Token.h>



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






int             test_Lex02_OpenClose (
    const
    char            *pTestName
)
{
    ERESULT         eRc = ERESULT_SUCCESS;
    LEX02_DATA      *pObj = OBJ_NIL;
    bool            fRc;
   
    fprintf(stderr, "Performing: %s\n", pTestName);

    pObj = Lex02_Alloc( );
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    pObj = Lex02_Init( pObj );
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    if (pObj) {

        //obj_TraceSet(pObj, true);       
        fRc = obj_IsKindOf(pObj, OBJ_IDENT_LEX02);
        TINYTEST_TRUE( (fRc) );

        // Test something.
        TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );

        obj_Release(pObj);
        pObj = OBJ_NIL;
    }

    fprintf(stderr, "...%s completed.\n\n\n", pTestName);
    return 1;
}



int             test_Lex02_Copy01 (
    const
    char            *pTestName
)
{
    ERESULT         eRc = ERESULT_SUCCESS;
    LEX02_DATA      *pObj1 = OBJ_NIL;
    LEX02_DATA      *pObj2 = OBJ_NIL;
    bool            fRc;
#if defined(LEX02_JSON_SUPPORT) && defined(XYZZY)
    ASTR_DATA       *pStr = OBJ_NIL;
#endif
   
    fprintf(stderr, "Performing: %s\n", pTestName);

    pObj1 = Lex02_New( );
    TINYTEST_FALSE( (OBJ_NIL == pObj1) );
    if (pObj1) {

        //obj_TraceSet(pObj1, true);       
        fRc = obj_IsKindOf(pObj1, OBJ_IDENT_LEX02);
        TINYTEST_TRUE( (fRc) );
        
        // Test assign.
        pObj2 = Lex02_New();
        TINYTEST_FALSE( (OBJ_NIL == pObj2) );
        eRc = Lex02_Assign(pObj1, pObj2);
        TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );

        fRc = obj_IsKindOf(pObj2, OBJ_IDENT_LEX02);
        TINYTEST_TRUE( (fRc) );
        //eRc = Lex02_Compare(pObj1, pObj2);
        //TINYTEST_TRUE( (0 == eRc) );
        //TODO: Add More tests here!

        obj_Release(pObj2);
        pObj2 = OBJ_NIL;

        // Test copy.
        pObj2 = Lex02_Copy(pObj1);
        TINYTEST_FALSE( (OBJ_NIL == pObj2) );

        fRc = obj_IsKindOf(pObj2, OBJ_IDENT_LEX02);
        TINYTEST_TRUE( (fRc) );
        //eRc = Lex02_Compare(pObj1, pObj2);
        //TINYTEST_TRUE( (0 == eRc) );
        //TODO: Add More tests here!

        obj_Release(pObj2);
        pObj2 = OBJ_NIL;

        // Test json support.
#if defined(LEX02_JSON_SUPPORT) && defined(XYZZY)
        pStr = Lex02_ToJson(pObj1);
        TINYTEST_FALSE( (OBJ_NIL == pStr) );
        fprintf(stderr, "JSON: %s\n", AStr_getData(pStr));
        pObj2 = Lex02_NewFromJsonString(pStr);
        TINYTEST_FALSE( (OBJ_NIL == pObj2) );
        fRc = obj_IsKindOf(pObj2, OBJ_IDENT_LEX02);
        TINYTEST_TRUE( (fRc) );
        obj_Release(pStr);
        pStr = OBJ_NIL;
        //eRc = Lex02_Compare(pObj1, pObj2);
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



int             test_Lex02_Test01 (
    const
    char            *pTestName
)
{
    //ERESULT         eRc = ERESULT_SUCCESS;
    bool            fRc;
    LEX02_DATA      *pObj = OBJ_NIL;
    const
    char            *pInputA = "unsigned int  a;";
    SRCFILE_DATA    *pSrc = OBJ_NIL;
    PATH_DATA       *pPath = OBJ_NIL;
    TOKEN_DATA      *pToken;

    fprintf(stderr, "Performing: %s\n", pTestName);
    fprintf(stderr, "\tTokenizing(Advance): \"%s\"\n", pInputA);

    pSrc = SrcFile_NewFromStrA(pPath, pInputA, 1, 4);
    XCTAssertFalse( (OBJ_NIL == pSrc) );

    pObj = Lex02_New( );
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    if (pObj) {

        obj_TraceSet(pObj, true);
        fRc = obj_IsKindOf(pObj, OBJ_IDENT_LEX02);
        TINYTEST_TRUE( (fRc) );
        //TINYTEST_TRUE( (ERESULT_OK(eRc)) );


        fRc =   Lex_setSourceInput(
                                      Lex02_getLex(pObj),
                                      (void *)SrcFile_InputAdvance,
                                      (void *)SrcFile_InputLookAhead,
                                      pSrc
                );
        XCTAssertTrue( (fRc) );

        pToken = Lex_TokenAdvance(Lex02_getLex(pObj), 0);
        XCTAssertFalse( (OBJ_NIL == pToken) );
        {
            ASTR_DATA       *pStr = Token_ToDebugString(pToken, 0);
            if (pStr) {
                fprintf(stderr, "Token 1 (unsigned): %s\n", AStr_getData(pStr));
                obj_Release(pStr);
                pStr = OBJ_NIL;
            }
        }
        XCTAssertTrue( (LEX_IDENTIFIER == Token_getClass(pToken)) );
        {
            char            *pStrA = Token_getTextA(pToken);
            XCTAssertTrue( (0 == strcmp(pStrA, "unsigned")) );
            mem_Free(pStrA);
        }

        pToken = Lex_TokenAdvance(Lex02_getLex(pObj), 1);
        XCTAssertFalse( (OBJ_NIL == pToken) );
        {
            ASTR_DATA       *pStr = Token_ToDebugString(pToken, 0);
            if (pStr) {
                fprintf(stderr, "Token 2 (int): %s\n", AStr_getData(pStr));
                obj_Release(pStr);
                pStr = OBJ_NIL;
            }
        }
        XCTAssertTrue( (LEX_IDENTIFIER == Token_getClass(pToken)) );
        {
            char            *pStrA = Token_getTextA(pToken);
            XCTAssertTrue( (0 == strcmp(pStrA, "int")) );
            mem_Free(pStrA);
        }

        pToken = Lex_TokenAdvance(Lex02_getLex(pObj), 1);
        XCTAssertFalse( (OBJ_NIL == pToken) );
        {
            ASTR_DATA       *pStr = Token_ToDebugString(pToken, 0);
            if (pStr) {
                fprintf(stderr, "Token 3 (a): %s\n", AStr_getData(pStr));
                obj_Release(pStr);
                pStr = OBJ_NIL;
            }
        }
        XCTAssertTrue( (LEX_IDENTIFIER == Token_getClass(pToken)) );
        {
            char            *pStrA = Token_getTextA(pToken);
            XCTAssertTrue( (0 == strcmp(pStrA, "a")) );
            mem_Free(pStrA);
        }

        pToken = Lex_TokenAdvance(Lex02_getLex(pObj), 1);
        XCTAssertFalse( (OBJ_NIL == pToken) );
        {
            ASTR_DATA       *pStr = Token_ToDebugString(pToken, 0);
            if (pStr) {
                fprintf(stderr, "Token 4 (;): %s\n", AStr_getData(pStr));
                obj_Release(pStr);
                pStr = OBJ_NIL;
            }
        }
        XCTAssertTrue( (LEX_SEP_SEMICOLON == Token_getClass(pToken)) );
        {
            char            *pStrA = Token_getTextA(pToken);
            XCTAssertTrue( (0 == strcmp(pStrA, ";")) );
            mem_Free(pStrA);
        }

        pToken = Lex_TokenAdvance(Lex02_getLex(pObj), 1);
        XCTAssertFalse( (OBJ_NIL == pToken) );
        {
            ASTR_DATA       *pStr = Token_ToDebugString(pToken, 0);
            if (pStr) {
                fprintf(stderr, "Token 4 (EOF): %s\n", AStr_getData(pStr));
                obj_Release(pStr);
                pStr = OBJ_NIL;
            }
        }
        XCTAssertTrue( (LEX_CLASS_EOF == Token_getClass(pToken)) );

        obj_Release(pObj);
        pObj = OBJ_NIL;
    }

    obj_Release(pSrc);
    pSrc = OBJ_NIL;

    fprintf(stderr, "...%s completed.\n\n\n", pTestName);
    return 1;
}



int             test_Lex02_Test02 (
    const
    char            *pTestName
)
{
    //ERESULT         eRc = ERESULT_SUCCESS;
    bool            fRc;
    LEX02_DATA      *pObj = OBJ_NIL;
    const
    char            *pInputA = "unsigned int  a;";
    PATH_DATA       *pPath = OBJ_NIL;
    TOKEN_DATA      *pToken;

    fprintf(stderr, "Performing: %s\n", pTestName);
    fprintf(stderr, "\tTokenizing(LookAhead): \"%s\"\n", pInputA);

    pObj = Lex02_NewFromStrA(pPath, pInputA);
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    if (pObj) {

        obj_TraceSet(pObj, true);
        fRc = obj_IsKindOf(pObj, OBJ_IDENT_LEX02);
        TINYTEST_TRUE( (fRc) );
        //TINYTEST_TRUE( (ERESULT_OK(eRc)) );

        pToken = Lex_TokenLookAhead(Lex02_getLex(pObj), 1);
        XCTAssertFalse( (OBJ_NIL == pToken) );
        {
            ASTR_DATA       *pStr = Token_ToDebugString(pToken, 0);
            if (pStr) {
                fprintf(stderr, "Token 1 (unsigned): %s\n", AStr_getData(pStr));
                obj_Release(pStr);
                pStr = OBJ_NIL;
            }
        }
        XCTAssertTrue( (LEX_IDENTIFIER == Token_getClass(pToken)) );
        {
            char            *pStrA = Token_getTextA(pToken);
            XCTAssertTrue( (0 == strcmp(pStrA, "unsigned")) );
            mem_Free(pStrA);
        }
        Lex_TokenAdvance(Lex02_getLex(pObj), 1);

        pToken = Lex_TokenLookAhead(Lex02_getLex(pObj), 1);
        XCTAssertFalse( (OBJ_NIL == pToken) );
        {
            ASTR_DATA       *pStr = Token_ToDebugString(pToken, 0);
            if (pStr) {
                fprintf(stderr, "Token 2 (int): %s\n", AStr_getData(pStr));
                obj_Release(pStr);
                pStr = OBJ_NIL;
            }
        }
        XCTAssertTrue( (LEX_IDENTIFIER == Token_getClass(pToken)) );
        {
            char            *pStrA = Token_getTextA(pToken);
            XCTAssertTrue( (0 == strcmp(pStrA, "int")) );
            mem_Free(pStrA);
        }
        Lex_TokenAdvance(Lex02_getLex(pObj), 1);

        pToken = Lex_TokenLookAhead(Lex02_getLex(pObj), 1);
        XCTAssertFalse( (OBJ_NIL == pToken) );
        {
            ASTR_DATA       *pStr = Token_ToDebugString(pToken, 0);
            if (pStr) {
                fprintf(stderr, "Token 3 (a): %s\n", AStr_getData(pStr));
                obj_Release(pStr);
                pStr = OBJ_NIL;
            }
        }
        XCTAssertTrue( (LEX_IDENTIFIER == Token_getClass(pToken)) );
        {
            char            *pStrA = Token_getTextA(pToken);
            XCTAssertTrue( (0 == strcmp(pStrA, "a")) );
            mem_Free(pStrA);
        }
        Lex_TokenAdvance(Lex02_getLex(pObj), 1);

        pToken = Lex_TokenLookAhead(Lex02_getLex(pObj), 1);
        XCTAssertFalse( (OBJ_NIL == pToken) );
        {
            ASTR_DATA       *pStr = Token_ToDebugString(pToken, 0);
            if (pStr) {
                fprintf(stderr, "Token 4 (;): %s\n", AStr_getData(pStr));
                obj_Release(pStr);
                pStr = OBJ_NIL;
            }
        }
        XCTAssertTrue( (LEX_SEP_SEMICOLON == Token_getClass(pToken)) );
        {
            char            *pStrA = Token_getTextA(pToken);
            XCTAssertTrue( (0 == strcmp(pStrA, ";")) );
            mem_Free(pStrA);
        }
        Lex_TokenAdvance(Lex02_getLex(pObj), 1);

        pToken = Lex_TokenLookAhead(Lex02_getLex(pObj), 1);
        XCTAssertFalse( (OBJ_NIL == pToken) );
        {
            ASTR_DATA       *pStr = Token_ToDebugString(pToken, 0);
            if (pStr) {
                fprintf(stderr, "Token 4 (EOF): %s\n", AStr_getData(pStr));
                obj_Release(pStr);
                pStr = OBJ_NIL;
            }
        }
        XCTAssertTrue( (LEX_CLASS_EOF == Token_getClass(pToken)) );
        Lex_TokenAdvance(Lex02_getLex(pObj), 1);

        obj_Release(pObj);
        pObj = OBJ_NIL;
    }

    fprintf(stderr, "...%s completed.\n\n\n", pTestName);
    return 1;
}



int             test_Lex02_Test03 (
    const
    char            *pTestName
)
{
    //ERESULT         eRc = ERESULT_SUCCESS;
    bool            fRc;
    LEX02_DATA      *pObj = OBJ_NIL;
    const
    char            *pInputA = ">> ++ -- <<";
    PATH_DATA       *pPath = OBJ_NIL;
    TOKEN_DATA      *pToken;

    fprintf(stderr, "Performing: %s\n", pTestName);
    fprintf(stderr, "\tTokenizing(LookAhead): \"%s\"\n", pInputA);

    pObj = Lex02_NewFromStrA(pPath, pInputA);
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    if (pObj) {

        //obj_TraceSet(pObj, true);
        fRc = obj_IsKindOf(pObj, OBJ_IDENT_LEX02);
        TINYTEST_TRUE( (fRc) );
        //TINYTEST_TRUE( (ERESULT_OK(eRc)) );

        pToken = Lex_TokenLookAhead(Lex02_getLex(pObj), 1);
        XCTAssertFalse( (OBJ_NIL == pToken) );
        {
            ASTR_DATA       *pStr = Token_ToDebugString(pToken, 0);
            if (pStr) {
                fprintf(stderr, "Token 1 (>>): %s\n", AStr_getData(pStr));
                obj_Release(pStr);
                pStr = OBJ_NIL;
            }
        }
        XCTAssertTrue( (LEX_OP_RIGHT == Token_getClass(pToken)) );
        {
            char            *pStrA = Token_getTextA(pToken);
            XCTAssertTrue( (0 == strcmp(pStrA, ">>")) );
            mem_Free(pStrA);
        }
        Lex_TokenAdvance(Lex02_getLex(pObj), 1);

        pToken = Lex_TokenLookAhead(Lex02_getLex(pObj), 1);
        XCTAssertFalse( (OBJ_NIL == pToken) );
        {
            ASTR_DATA       *pStr = Token_ToDebugString(pToken, 0);
            if (pStr) {
                fprintf(stderr, "Token 2 (++): %s\n", AStr_getData(pStr));
                obj_Release(pStr);
                pStr = OBJ_NIL;
            }
        }
        XCTAssertTrue( (LEX_OP_INC == Token_getClass(pToken)) );
        {
            char            *pStrA = Token_getTextA(pToken);
            XCTAssertTrue( (0 == strcmp(pStrA, "++")) );
            mem_Free(pStrA);
        }
        Lex_TokenAdvance(Lex02_getLex(pObj), 1);

        pToken = Lex_TokenLookAhead(Lex02_getLex(pObj), 1);
        XCTAssertFalse( (OBJ_NIL == pToken) );
        {
            ASTR_DATA       *pStr = Token_ToDebugString(pToken, 0);
            if (pStr) {
                fprintf(stderr, "Token 3 (--): %s\n", AStr_getData(pStr));
                obj_Release(pStr);
                pStr = OBJ_NIL;
            }
        }
        XCTAssertTrue( (LEX_OP_DEC == Token_getClass(pToken)) );
        {
            char            *pStrA = Token_getTextA(pToken);
            XCTAssertTrue( (0 == strcmp(pStrA, "--")) );
            mem_Free(pStrA);
        }
        Lex_TokenAdvance(Lex02_getLex(pObj), 1);

        pToken = Lex_TokenLookAhead(Lex02_getLex(pObj), 1);
        XCTAssertFalse( (OBJ_NIL == pToken) );
        {
            ASTR_DATA       *pStr = Token_ToDebugString(pToken, 0);
            if (pStr) {
                fprintf(stderr, "Token 4 (<<): %s\n", AStr_getData(pStr));
                obj_Release(pStr);
                pStr = OBJ_NIL;
            }
        }
        XCTAssertTrue( (LEX_OP_LEFT == Token_getClass(pToken)) );
        {
            char            *pStrA = Token_getTextA(pToken);
            XCTAssertTrue( (0 == strcmp(pStrA, "<<")) );
            mem_Free(pStrA);
        }
        Lex_TokenAdvance(Lex02_getLex(pObj), 1);

        pToken = Lex_TokenLookAhead(Lex02_getLex(pObj), 1);
        XCTAssertFalse( (OBJ_NIL == pToken) );
        {
            ASTR_DATA       *pStr = Token_ToDebugString(pToken, 0);
            if (pStr) {
                fprintf(stderr, "Token 4 (EOF): %s\n", AStr_getData(pStr));
                obj_Release(pStr);
                pStr = OBJ_NIL;
            }
        }
        XCTAssertTrue( (LEX_CLASS_EOF == Token_getClass(pToken)) );
        Lex_TokenAdvance(Lex02_getLex(pObj), 1);

        obj_Release(pObj);
        pObj = OBJ_NIL;
    }

    fprintf(stderr, "...%s completed.\n\n\n", pTestName);
    return 1;
}




TINYTEST_START_SUITE(test_Lex02);
    TINYTEST_ADD_TEST(test_Lex02_Test03,setUp,tearDown);
    TINYTEST_ADD_TEST(test_Lex02_Test02,setUp,tearDown);
    TINYTEST_ADD_TEST(test_Lex02_Test01,setUp,tearDown);
    //TINYTEST_ADD_TEST(test_Lex02_Copy01,setUp,tearDown);
    TINYTEST_ADD_TEST(test_Lex02_OpenClose,setUp,tearDown);
TINYTEST_END_SUITE();

TINYTEST_MAIN_SINGLE_SUITE(test_Lex02);





