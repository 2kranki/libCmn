// vi:nu:et:sts=4 ts=4 sw=4
/*
 *  Generated 12/09/2020 23:26:59
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
#include    <LexJ_internal.h>
#include    <JsonIn.h>
#include    <SrcErrors.h>
#include    <szTbl.h>



static
const
char        *pTestInput01 =
"// Test01 Input\n"
"{ /* test comment */\n\n\n"
    "\t\"one\": -123,\n"
    "\ttwo: \"xyz\",\n"
    "\tthree: [a, b, c] // Another comment\n"
    "\tfour: null,\n"
    "\t\"five\": true,\n"
    "\t\"six\": false\n"
"}\n";



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






int             test_LexJ_OpenClose (
    const
    char            *pTestName
)
{
    ERESULT         eRc = ERESULT_SUCCESS;
    LEXJ_DATA       *pObj = OBJ_NIL;
    bool            fRc;
   
    fprintf(stderr, "Performing: %s\n", pTestName);

    pObj = LexJ_Alloc( );
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    pObj = LexJ_Init( pObj );
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    if (pObj) {

        //obj_TraceSet(pObj, true);       
        fRc = obj_IsKindOf(pObj, OBJ_IDENT_LEXJ);
        TINYTEST_TRUE( (fRc) );
        
        // Test something.
        TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );

        obj_Release(pObj);
        pObj = OBJ_NIL;
    }

    fprintf(stderr, "...%s completed.\n\n\n", pTestName);
    return 1;
}



int             test_LexJ_Copy01 (
    const
    char            *pTestName
)
{
    ERESULT         eRc = ERESULT_SUCCESS;
    LEXJ_DATA       *pObj1 = OBJ_NIL;
    LEXJ_DATA       *pObj2 = OBJ_NIL;
    bool            fRc;
#if defined(LEXJ_JSON_SUPPORT) && defined(XYZZY)
    ASTR_DATA       *pStr = OBJ_NIL;
#endif
   
    fprintf(stderr, "Performing: %s\n", pTestName);

    pObj1 = LexJ_New( );
    TINYTEST_FALSE( (OBJ_NIL == pObj1) );
    if (pObj1) {

        //obj_TraceSet(pObj1, true);       
        fRc = obj_IsKindOf(pObj1, OBJ_IDENT_LEXJ);
        TINYTEST_TRUE( (fRc) );
        
        // Test assign.
        pObj2 = LexJ_New();
        TINYTEST_FALSE( (OBJ_NIL == pObj2) );
        eRc = LexJ_Assign(pObj1, pObj2);
        TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );

        fRc = obj_IsKindOf(pObj2, OBJ_IDENT_LEXJ);
        TINYTEST_TRUE( (fRc) );
        //eRc = LexJ_Compare(pObj1, pObj2);
        //TINYTEST_TRUE( (ERESULT_SUCCESS_EQUAL == eRc) );
        //TODO: Add More tests here!

        obj_Release(pObj2);
        pObj2 = OBJ_NIL;

        // Test copy.
        pObj2 = LexJ_Copy(pObj1);
        TINYTEST_FALSE( (OBJ_NIL == pObj2) );

        fRc = obj_IsKindOf(pObj2, OBJ_IDENT_LEXJ);
        TINYTEST_TRUE( (fRc) );
        //eRc = LexJ_Compare(pObj1, pObj2);
        //TINYTEST_TRUE( (ERESULT_SUCCESS_EQUAL == eRc) );
        //TODO: Add More tests here!

        obj_Release(pObj2);
        pObj2 = OBJ_NIL;

        // Test json support.
#if defined(LEXJ_JSON_SUPPORT) && defined(XYZZY)
        pStr = LexJ_ToJson(pObj1);
        TINYTEST_FALSE( (OBJ_NIL == pStr) );
        fprintf(stderr, "JSON: %s\n", AStr_getData(pStr));
        pObj2 = LexJ_NewFromJsonString(pStr);
        TINYTEST_FALSE( (OBJ_NIL == pObj2) );
        fRc = obj_IsKindOf(pObj2, OBJ_IDENT_LEXJ);
        TINYTEST_TRUE( (fRc) );
        obj_Release(pStr);
        pStr = OBJ_NIL;
        //eRc = LexJ_Compare(pObj1, pObj2);
        //TINYTEST_TRUE( (ERESULT_SUCCESS_EQUAL == eRc) );

        obj_Release(pObj2);
        pObj2 = OBJ_NIL;
#endif

        obj_Release(pObj1);
        pObj1 = OBJ_NIL;
    }

    fprintf(stderr, "...%s completed.\n\n\n", pTestName);
    return 1;
}



int             test_LexJ_Test01 (
    const
    char            *pTestName
)
{
    //ERESULT         eRc = ERESULT_SUCCESS;
    LEXJ_DATA       *pObj = OBJ_NIL;
    bool            fRc;
   
    fprintf(stderr, "Performing: %s\n", pTestName);

    pObj = LexJ_New( );
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    if (pObj) {

        //obj_TraceSet(pObj, true);       
        fRc = obj_IsKindOf(pObj, OBJ_IDENT_LEXJ);
        TINYTEST_TRUE( (fRc) );
        //TINYTEST_TRUE( (ERESULT_OK(eRc)) );
        
        {
            ASTR_DATA       *pStr = LexJ_ToDebugString(pObj, 0);
            if (pStr) {
                fprintf(stderr, "Debug: %s\n", AStr_getData(pStr));
                obj_Release(pStr);
                pStr = OBJ_NIL;
            }
        }

        obj_Release(pObj);
        pObj = OBJ_NIL;
    }

    fprintf(stderr, "...%s completed.\n\n\n", pTestName);
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
    const
    char            *pTestInput =
    "// Test01 Input\n"
    "{ /* test comment */\n\n\n"
        "\t\"one\": 123,\n"
        "\ttwo: \"xyz\",\n"
        "\tthree: [a, b, c] // Another comment\n"
        "\tfour: null,\n"
        "\t\"five\": true,\n"
        "\t\"six\": false\n"
    "}\n";

    fprintf(stderr, "Performing: %s\n", pTestName);
    pBuf = AStr_NewA(pTestInput);
    XCTAssertFalse( (OBJ_NIL == pBuf) );
    if (pBuf) {
        fprintf(stderr, "\tTest Data: \"%s\"\n", pTestInput);


        pLexJ = LexJ_NewFromAStr(pBuf, 4, true);
        XCTAssertFalse( (OBJ_NIL == pLexJ) );
        obj_TraceSet(pLexJ, true);
        if (pLexJ) {

            pToken = LexJ_TokenLookAhead(pLexJ, 1);
            XCTAssertFalse( (OBJ_NIL == pToken) );
            {
                ASTR_DATA       *pStr2 = Token_ToDataString(pToken);
                int32_t         cls = Token_getClass(pToken);
                fprintf(
                        stderr,
                        "\tToken Class  = %d - %s\n",
                        cls,
                        LexJ_Class2Str(cls)
                );
                fprintf(stderr, "\tToken String = \"%s\"\n", AStr_getData(pStr2));
                obj_Release(pStr2);
            }
            XCTAssertTrue( (LEXJ_SEP_LBRACE == Token_getClass(pToken)) );
            pToken = LexJ_TokenAdvance(pLexJ, 1);
            XCTAssertFalse( (OBJ_NIL == pToken) );

            pToken = LexJ_TokenLookAhead(pLexJ, 1);
            XCTAssertFalse( (OBJ_NIL == pToken) );
            {
                ASTR_DATA       *pStr2 = Token_ToDataString(pToken);
                int32_t         cls = Token_getClass(pToken);
                fprintf(
                        stderr,
                        "\tToken Class  = %d - %s\n",
                        cls,
                        LexJ_Class2Str(cls)
                );
                fprintf(stderr, "\tToken String = \"%s\"\n", AStr_getData(pStr2));
                obj_Release(pStr2);
            }
            XCTAssertTrue( (LEXJ_CONSTANT_STRING == Token_getClass(pToken)) );
            pStr = Token_ToDataString(pToken);
            XCTAssertTrue( (0 == strcmp("one", AStr_getData(pStr))) );
            obj_Release(pStr);
            pStr = OBJ_NIL;
            pToken = LexJ_TokenAdvance(pLexJ, 1);
            XCTAssertFalse( (OBJ_NIL == pToken) );

            pToken = LexJ_TokenLookAhead(pLexJ, 1);
            XCTAssertFalse( (OBJ_NIL == pToken) );
            {
                ASTR_DATA       *pStr2 = Token_ToDataString(pToken);
                int32_t         cls = Token_getClass(pToken);
                fprintf(
                        stderr,
                        "\tToken Class  = %d - %s\n",
                        cls,
                        LexJ_Class2Str(cls)
                );
                fprintf(stderr, "\tToken String = \"%s\"\n", AStr_getData(pStr2));
                obj_Release(pStr2);
            }
            XCTAssertTrue( (LEXJ_SEP_COLON == Token_getClass(pToken)) );
            pToken = LexJ_TokenAdvance(pLexJ, 1);
            XCTAssertFalse( (OBJ_NIL == pToken) );

            pToken = LexJ_TokenLookAhead(pLexJ, 1);
            XCTAssertFalse( (OBJ_NIL == pToken) );
            {
                ASTR_DATA       *pStr2 = Token_ToDataString(pToken);
                int32_t         cls = Token_getClass(pToken);
                fprintf(
                        stderr,
                        "\tToken Class  = %d - %s\n",
                        cls,
                        LexJ_Class2Str(cls)
                );
                fprintf(stderr, "\tToken String = \"%s\"\n", AStr_getData(pStr2));
                obj_Release(pStr2);
            }
            XCTAssertTrue( (LEXJ_CONSTANT_INTEGER == Token_getClass(pToken)) );
            pToken = LexJ_TokenAdvance(pLexJ, 1);
            XCTAssertFalse( (OBJ_NIL == pToken) );

            pToken = LexJ_TokenLookAhead(pLexJ, 1);
            XCTAssertFalse( (OBJ_NIL == pToken) );
            {
                ASTR_DATA       *pStr2 = Token_ToDataString(pToken);
                int32_t         cls = Token_getClass(pToken);
                fprintf(
                        stderr,
                        "\tToken Class  = %d - %s\n",
                        cls,
                        LexJ_Class2Str(cls)
                );
                fprintf(stderr, "\tToken String = \"%s\"\n", AStr_getData(pStr2));
                obj_Release(pStr2);
            }
            XCTAssertTrue( (LEXJ_SEP_COMMA == Token_getClass(pToken)) );
            pToken = LexJ_TokenAdvance(pLexJ, 1);
            XCTAssertFalse( (OBJ_NIL == pToken) );

            pToken = LexJ_TokenLookAhead(pLexJ, 1);
            XCTAssertFalse( (OBJ_NIL == pToken) );
            {
                ASTR_DATA       *pStr2 = Token_ToDataString(pToken);
                int32_t         cls = Token_getClass(pToken);
                fprintf(
                        stderr,
                        "\tToken Class  = %d - %s\n",
                        cls,
                        LexJ_Class2Str(cls)
                );
                fprintf(stderr, "\tToken String = \"%s\"\n", AStr_getData(pStr2));
                obj_Release(pStr2);
            }
            XCTAssertTrue( (LEXJ_CONSTANT_STRING == Token_getClass(pToken)) );
            pStr = Token_ToDataString(pToken);
            XCTAssertTrue( (0 == strcmp("two", AStr_getData(pStr))) );
            obj_Release(pStr);
            pStr = OBJ_NIL;
            pToken = LexJ_TokenAdvance(pLexJ, 1);
            XCTAssertFalse( (OBJ_NIL == pToken) );

            pToken = LexJ_TokenLookAhead(pLexJ, 1);
            XCTAssertFalse( (OBJ_NIL == pToken) );
            {
                ASTR_DATA       *pStr2 = Token_ToDataString(pToken);
                int32_t         cls = Token_getClass(pToken);
                fprintf(
                        stderr,
                        "\tToken Class  = %d - %s\n",
                        cls,
                        LexJ_Class2Str(cls)
                );
                fprintf(stderr, "\tToken String = \"%s\"\n", AStr_getData(pStr2));
                obj_Release(pStr2);
            }
            XCTAssertTrue( (LEXJ_SEP_COLON == Token_getClass(pToken)) );
            pToken = LexJ_TokenAdvance(pLexJ, 1);
            XCTAssertFalse( (OBJ_NIL == pToken) );

            pToken = LexJ_TokenLookAhead(pLexJ, 1);
            XCTAssertFalse( (OBJ_NIL == pToken) );
            {
                ASTR_DATA       *pStr2 = Token_ToDataString(pToken);
                int32_t         cls = Token_getClass(pToken);
                fprintf(
                        stderr,
                        "\tToken Class  = %d - %s\n",
                        cls,
                        LexJ_Class2Str(cls)
                );
                fprintf(stderr, "\tToken String = \"%s\"\n", AStr_getData(pStr2));
                obj_Release(pStr2);
            }
            XCTAssertTrue( (LEXJ_CONSTANT_STRING == Token_getClass(pToken)) );
            pStr = Token_ToDataString(pToken);
            XCTAssertTrue( (0 == strcmp("xyz", AStr_getData(pStr))) );
            obj_Release(pStr);
            pStr = OBJ_NIL;
            pToken = LexJ_TokenAdvance(pLexJ, 1);
            XCTAssertFalse( (OBJ_NIL == pToken) );

            pToken = LexJ_TokenLookAhead(pLexJ, 1);
            XCTAssertFalse( (OBJ_NIL == pToken) );
            {
                ASTR_DATA       *pStr2 = Token_ToDataString(pToken);
                int32_t         cls = Token_getClass(pToken);
                fprintf(
                        stderr,
                        "\tToken Class  = %d - %s\n",
                        cls,
                        LexJ_Class2Str(cls)
                );
                fprintf(stderr, "\tToken String = \"%s\"\n", AStr_getData(pStr2));
                obj_Release(pStr2);
            }
            XCTAssertTrue( (LEXJ_SEP_COMMA == Token_getClass(pToken)) );
            pToken = LexJ_TokenAdvance(pLexJ, 1);
            XCTAssertFalse( (OBJ_NIL == pToken) );

            pToken = LexJ_TokenLookAhead(pLexJ, 1);
            XCTAssertFalse( (OBJ_NIL == pToken) );
            {
                ASTR_DATA       *pStr2 = Token_ToDataString(pToken);
                int32_t         cls = Token_getClass(pToken);
                fprintf(
                        stderr,
                        "\tToken Class  = %d - %s\n",
                        cls,
                        LexJ_Class2Str(cls)
                );
                fprintf(stderr, "\tToken String = \"%s\"\n", AStr_getData(pStr2));
                obj_Release(pStr2);
            }
            XCTAssertTrue( (LEXJ_CONSTANT_STRING == Token_getClass(pToken)) );
            pStr = Token_ToDataString(pToken);
            XCTAssertTrue( (0 == strcmp("three", AStr_getData(pStr))) );
            obj_Release(pStr);
            pStr = OBJ_NIL;
            pToken = LexJ_TokenAdvance(pLexJ, 1);
            XCTAssertFalse( (OBJ_NIL == pToken) );

            pToken = LexJ_TokenLookAhead(pLexJ, 1);
            XCTAssertFalse( (OBJ_NIL == pToken) );
            {
                ASTR_DATA       *pStr2 = Token_ToDataString(pToken);
                int32_t         cls = Token_getClass(pToken);
                fprintf(
                        stderr,
                        "\tToken Class  = %d - %s\n",
                        cls,
                        LexJ_Class2Str(cls)
                );
                fprintf(stderr, "\tToken String = \"%s\"\n", AStr_getData(pStr2));
                obj_Release(pStr2);
            }
            XCTAssertTrue( (LEXJ_SEP_COLON == Token_getClass(pToken)) );
            pToken = LexJ_TokenAdvance(pLexJ, 1);
            XCTAssertFalse( (OBJ_NIL == pToken) );

            pToken = LexJ_TokenLookAhead(pLexJ, 1);
            XCTAssertFalse( (OBJ_NIL == pToken) );
            {
                ASTR_DATA       *pStr2 = Token_ToDataString(pToken);
                int32_t         cls = Token_getClass(pToken);
                fprintf(
                        stderr,
                        "\tToken Class  = %d - %s\n",
                        cls,
                        LexJ_Class2Str(cls)
                );
                fprintf(stderr, "\tToken String = \"%s\"\n", AStr_getData(pStr2));
                obj_Release(pStr2);
            }
            XCTAssertTrue( (LEXJ_SEP_LBRACKET == Token_getClass(pToken)) );
            pToken = LexJ_TokenAdvance(pLexJ, 1);
            XCTAssertFalse( (OBJ_NIL == pToken) );

            pToken = LexJ_TokenLookAhead(pLexJ, 1);
            XCTAssertFalse( (OBJ_NIL == pToken) );
            {
                ASTR_DATA       *pStr2 = Token_ToDataString(pToken);
                int32_t         cls = Token_getClass(pToken);
                fprintf(
                        stderr,
                        "\tToken Class  = %d - %s\n",
                        cls,
                        LexJ_Class2Str(cls)
                );
                fprintf(stderr, "\tToken String = \"%s\"\n", AStr_getData(pStr2));
                obj_Release(pStr2);
            }
            XCTAssertTrue( (LEXJ_CONSTANT_STRING == Token_getClass(pToken)) );
            pStr = Token_ToDataString(pToken);
            XCTAssertTrue( (0 == strcmp("a", AStr_getData(pStr))) );
            obj_Release(pStr);
            pStr = OBJ_NIL;
            pToken = LexJ_TokenAdvance(pLexJ, 1);
            XCTAssertFalse( (OBJ_NIL == pToken) );

            pToken = LexJ_TokenLookAhead(pLexJ, 1);
            XCTAssertFalse( (OBJ_NIL == pToken) );
            XCTAssertTrue( (LEXJ_SEP_COMMA == Token_getClass(pToken)) );
            pToken = LexJ_TokenAdvance(pLexJ, 1);
            XCTAssertFalse( (OBJ_NIL == pToken) );

            pToken = LexJ_TokenLookAhead(pLexJ, 1);
            XCTAssertFalse( (OBJ_NIL == pToken) );
            XCTAssertTrue( (LEXJ_CONSTANT_STRING == Token_getClass(pToken)) );
            pStr = Token_ToDataString(pToken);
            XCTAssertTrue( (0 == strcmp("b", AStr_getData(pStr))) );
            obj_Release(pStr);
            pStr = OBJ_NIL;
            pToken = LexJ_TokenAdvance(pLexJ, 1);
            XCTAssertFalse( (OBJ_NIL == pToken) );

            pToken = LexJ_TokenLookAhead(pLexJ, 1);
            XCTAssertFalse( (OBJ_NIL == pToken) );
            XCTAssertTrue( (LEXJ_SEP_COMMA == Token_getClass(pToken)) );
            pToken = LexJ_TokenAdvance(pLexJ, 1);
            XCTAssertFalse( (OBJ_NIL == pToken) );

            pToken = LexJ_TokenLookAhead(pLexJ, 1);
            XCTAssertFalse( (OBJ_NIL == pToken) );
            XCTAssertTrue( (LEXJ_CONSTANT_STRING == Token_getClass(pToken)) );
            pStr = Token_ToDataString(pToken);
            XCTAssertTrue( (0 == strcmp("c", AStr_getData(pStr))) );
            obj_Release(pStr);
            pStr = OBJ_NIL;
            pToken = LexJ_TokenAdvance(pLexJ, 1);
            XCTAssertFalse( (OBJ_NIL == pToken) );

            pToken = LexJ_TokenLookAhead(pLexJ, 1);
            XCTAssertFalse( (OBJ_NIL == pToken) );
            XCTAssertTrue( (LEXJ_SEP_RBRACKET == Token_getClass(pToken)) );
            pToken = LexJ_TokenAdvance(pLexJ, 1);
            XCTAssertFalse( (OBJ_NIL == pToken) );

            pToken = LexJ_TokenLookAhead(pLexJ, 1);
            XCTAssertFalse( (OBJ_NIL == pToken) );
            XCTAssertTrue( (LEXJ_CONSTANT_STRING == Token_getClass(pToken)) );
            pStr = Token_ToDataString(pToken);
            XCTAssertTrue( (0 == strcmp("four", AStr_getData(pStr))) );
            obj_Release(pStr);
            pStr = OBJ_NIL;
            pToken = LexJ_TokenAdvance(pLexJ, 1);
            XCTAssertFalse( (OBJ_NIL == pToken) );

            pToken = LexJ_TokenLookAhead(pLexJ, 1);
            XCTAssertFalse( (OBJ_NIL == pToken) );
            XCTAssertTrue( (LEXJ_SEP_COLON == Token_getClass(pToken)) );
            pToken = LexJ_TokenAdvance(pLexJ, 1);
            XCTAssertFalse( (OBJ_NIL == pToken) );

            pToken = LexJ_TokenLookAhead(pLexJ, 1);
            XCTAssertFalse( (OBJ_NIL == pToken) );
            XCTAssertTrue( (LEXJ_KWD_NULL == Token_getClass(pToken)) );
            pToken = LexJ_TokenAdvance(pLexJ, 1);
            XCTAssertFalse( (OBJ_NIL == pToken) );

            pToken = LexJ_TokenLookAhead(pLexJ, 1);
            XCTAssertFalse( (OBJ_NIL == pToken) );
            XCTAssertTrue( (LEXJ_SEP_COMMA == Token_getClass(pToken)) );
            pToken = LexJ_TokenAdvance(pLexJ, 1);
            XCTAssertFalse( (OBJ_NIL == pToken) );

            pToken = LexJ_TokenLookAhead(pLexJ, 1);
            XCTAssertFalse( (OBJ_NIL == pToken) );
            XCTAssertTrue( (LEXJ_CONSTANT_STRING == Token_getClass(pToken)) );
            pStr = Token_ToDataString(pToken);
            XCTAssertTrue( (0 == strcmp("five", AStr_getData(pStr))) );
            obj_Release(pStr);
            pStr = OBJ_NIL;
            pToken = LexJ_TokenAdvance(pLexJ, 1);
            XCTAssertFalse( (OBJ_NIL == pToken) );

            pToken = LexJ_TokenLookAhead(pLexJ, 1);
            XCTAssertFalse( (OBJ_NIL == pToken) );
            XCTAssertTrue( (LEXJ_SEP_COLON == Token_getClass(pToken)) );
            pToken = LexJ_TokenAdvance(pLexJ, 1);
            XCTAssertFalse( (OBJ_NIL == pToken) );

            pToken = LexJ_TokenLookAhead(pLexJ, 1);
            XCTAssertFalse( (OBJ_NIL == pToken) );
            XCTAssertTrue( (LEXJ_KWD_TRUE == Token_getClass(pToken)) );
            pToken = LexJ_TokenAdvance(pLexJ, 1);
            XCTAssertFalse( (OBJ_NIL == pToken) );

            pToken = LexJ_TokenLookAhead(pLexJ, 1);
            XCTAssertFalse( (OBJ_NIL == pToken) );
            XCTAssertTrue( (LEXJ_SEP_COMMA == Token_getClass(pToken)) );
            pToken = LexJ_TokenAdvance(pLexJ, 1);
            XCTAssertFalse( (OBJ_NIL == pToken) );

            pToken = LexJ_TokenLookAhead(pLexJ, 1);
            XCTAssertFalse( (OBJ_NIL == pToken) );
            XCTAssertTrue( (LEXJ_CONSTANT_STRING == Token_getClass(pToken)) );
            pStr = Token_ToDataString(pToken);
            XCTAssertTrue( (0 == strcmp("six", AStr_getData(pStr))) );
            obj_Release(pStr);
            pStr = OBJ_NIL;
            pToken = LexJ_TokenAdvance(pLexJ, 1);
            XCTAssertFalse( (OBJ_NIL == pToken) );

            pToken = LexJ_TokenLookAhead(pLexJ, 1);
            XCTAssertFalse( (OBJ_NIL == pToken) );
            XCTAssertTrue( (LEXJ_SEP_COLON == Token_getClass(pToken)) );
            pToken = LexJ_TokenAdvance(pLexJ, 1);
            XCTAssertFalse( (OBJ_NIL == pToken) );

            pToken = LexJ_TokenLookAhead(pLexJ, 1);
            XCTAssertFalse( (OBJ_NIL == pToken) );
            XCTAssertTrue( (LEXJ_KWD_FALSE == Token_getClass(pToken)) );
            pToken = LexJ_TokenAdvance(pLexJ, 1);
            XCTAssertFalse( (OBJ_NIL == pToken) );

            pToken = LexJ_TokenLookAhead(pLexJ, 1);
            XCTAssertFalse( (OBJ_NIL == pToken) );
            XCTAssertTrue( (LEXJ_SEP_RBRACE == Token_getClass(pToken)) );
            pToken = LexJ_TokenAdvance(pLexJ, 1);
            XCTAssertFalse( (OBJ_NIL == pToken) );

            pToken = LexJ_TokenLookAhead(pLexJ, 1);
            XCTAssertFalse( (OBJ_NIL == pToken) );
            XCTAssertTrue( (LEX_CLASS_EOF == Token_getClass(pToken)) );
            pToken = LexJ_TokenAdvance(pLexJ, 1);
            XCTAssertFalse( (OBJ_NIL == pToken) );

            obj_Release(pLexJ);
            pLexJ = OBJ_NIL;
        }

        obj_Release(pBuf);
        pBuf = OBJ_NIL;
    }

    szTbl_SharedReset( );
    trace_SharedReset( );
    fprintf(stderr, "...%s completed.\n\n\n", pTestName);
    return 1;
}



int         test_LexJ_Number01(
    const
    char        *pTestName
)
{
    LEXJ_DATA       *pLexJ = OBJ_NIL;
    TOKEN_DATA      *pToken;
    ASTR_DATA       *pStr = OBJ_NIL;
    const
    char            *pStringToParse = "123";

    fprintf(stderr, "Performing: %s\n", pTestName);
    pLexJ = LexJ_NewA(pStringToParse, 4, true);
    XCTAssertFalse( (OBJ_NIL == pLexJ) );
    if (pLexJ) {

        obj_TraceSet(pLexJ, true);
        pToken = LexJ_TokenLookAhead(pLexJ, 1);
        XCTAssertFalse( (OBJ_NIL == pToken) );
        XCTAssertTrue( (LEXJ_CONSTANT_INTEGER == Token_getClass(pToken)) );
        pStr = Token_ToDataString(pToken);
        XCTAssertTrue( (0 == strcmp(pStringToParse, AStr_getData(pStr))) );
        obj_Release(pStr);
        pStr = OBJ_NIL;
        pToken = LexJ_TokenAdvance(pLexJ, 1);

        obj_Release(pLexJ);
        pLexJ = OBJ_NIL;
    }

    fprintf(stderr, "...%s completed.\n\n\n", pTestName);
    return 1;
}



int         test_LexJ_Number02(
    const
    char        *pTestName
)
{
    LEXJ_DATA       *pLexJ = OBJ_NIL;
    TOKEN_DATA      *pToken;
    ASTR_DATA       *pStr = OBJ_NIL;
    const
    char            *pStringToParse = "+123";

    fprintf(stderr, "Performing: %s\n", pTestName);
    pLexJ = LexJ_NewA(pStringToParse, 4, true);
    XCTAssertFalse( (OBJ_NIL == pLexJ) );
    if (pLexJ) {

        obj_TraceSet(pLexJ, true);
        pToken = LexJ_TokenLookAhead(pLexJ, 1);
        XCTAssertFalse( (OBJ_NIL == pToken) );
        pStr = Token_ToDataString(pToken);
        fprintf(stderr, "\tToken String = \"%s\"\n", AStr_getData(pStr));
        XCTAssertTrue( (0 == strcmp("+", AStr_getData(pStr))) );
        obj_Release(pStr);
        pStr = OBJ_NIL;
        XCTAssertTrue( (LEXJ_SEP_PLUS == Token_getClass(pToken)) );
        pToken = LexJ_TokenAdvance(pLexJ, 1);

        obj_TraceSet(pLexJ, true);
        pToken = LexJ_TokenLookAhead(pLexJ, 1);
        XCTAssertFalse( (OBJ_NIL == pToken) );
        pStr = Token_ToDataString(pToken);
        fprintf(stderr, "\tToken String = \"%s\"\n", AStr_getData(pStr));
        XCTAssertTrue( (0 == strcmp(pStringToParse+1, AStr_getData(pStr))) );
        obj_Release(pStr);
        pStr = OBJ_NIL;
        XCTAssertTrue( (LEXJ_CONSTANT_INTEGER == Token_getClass(pToken)) );
        pToken = LexJ_TokenAdvance(pLexJ, 1);

        obj_Release(pLexJ);
        pLexJ = OBJ_NIL;
    }

    fprintf(stderr, "...%s completed.\n\n\n", pTestName);
    return 1;
}



int         test_LexJ_Number03(
    const
    char        *pTestName
)
{
    LEXJ_DATA       *pLexJ = OBJ_NIL;
    TOKEN_DATA      *pToken;
    ASTR_DATA       *pStr = OBJ_NIL;
    const
    char            *pStringToParse = "-123";

    fprintf(stderr, "Performing: %s\n", pTestName);
    pLexJ = LexJ_NewA(pStringToParse, 4, true);
    XCTAssertFalse( (OBJ_NIL == pLexJ) );
    if (pLexJ) {

        obj_TraceSet(pLexJ, true);
        pToken = LexJ_TokenLookAhead(pLexJ, 1);
        XCTAssertFalse( (OBJ_NIL == pToken) );
        pStr = Token_ToDataString(pToken);
        fprintf(stderr, "\tToken String = \"%s\"\n", AStr_getData(pStr));
        XCTAssertTrue( (0 == strcmp("-", AStr_getData(pStr))) );
        obj_Release(pStr);
        pStr = OBJ_NIL;
        XCTAssertTrue( (LEXJ_SEP_MINUS == Token_getClass(pToken)) );
        pToken = LexJ_TokenAdvance(pLexJ, 1);

        obj_TraceSet(pLexJ, true);
        pToken = LexJ_TokenLookAhead(pLexJ, 1);
        XCTAssertFalse( (OBJ_NIL == pToken) );
        pStr = Token_ToDataString(pToken);
        fprintf(stderr, "\tToken String = \"%s\"\n", AStr_getData(pStr));
        XCTAssertTrue( (0 == strcmp(pStringToParse+1, AStr_getData(pStr))) );
        obj_Release(pStr);
        pStr = OBJ_NIL;
        XCTAssertTrue( (LEXJ_CONSTANT_INTEGER == Token_getClass(pToken)) );
        pToken = LexJ_TokenAdvance(pLexJ, 1);

        obj_Release(pLexJ);
        pLexJ = OBJ_NIL;
    }

    fprintf(stderr, "...%s completed.\n\n\n", pTestName);
    return 1;
}



int         test_LexJ_Number04(
    const
    char        *pTestName
)
{
    LEXJ_DATA       *pLexJ = OBJ_NIL;
    TOKEN_DATA      *pToken;
    ASTR_DATA       *pStr = OBJ_NIL;
    const
    char            *pStringToParse = "0";

    fprintf(stderr, "Performing: %s\n", pTestName);
    pLexJ = LexJ_NewA(pStringToParse, 4, true);
    XCTAssertFalse( (OBJ_NIL == pLexJ) );
    if (pLexJ) {

        obj_TraceSet(pLexJ, true);
        pToken = LexJ_TokenLookAhead(pLexJ, 1);
        XCTAssertFalse( (OBJ_NIL == pToken) );
        XCTAssertTrue( (LEXJ_CONSTANT_INTEGER == Token_getClass(pToken)) );
        pStr = Token_ToDataString(pToken);
        XCTAssertTrue( (0 == strcmp(pStringToParse, AStr_getData(pStr))) );
        obj_Release(pStr);
        pStr = OBJ_NIL;
        pToken = LexJ_TokenAdvance(pLexJ, 1);

        obj_Release(pLexJ);
        pLexJ = OBJ_NIL;
    }

    fprintf(stderr, "...%s completed.\n\n\n", pTestName);
    return 1;
}



int         test_LexJ_Number05(
    const
    char        *pTestName
)
{
    LEXJ_DATA       *pLexJ = OBJ_NIL;
    TOKEN_DATA      *pToken;
    ASTR_DATA       *pStr = OBJ_NIL;
    const
    char            *pStringToParse = "1.23";

    fprintf(stderr, "Performing: %s\n", pTestName);
    pLexJ = LexJ_NewA(pStringToParse, 4, true);
    XCTAssertFalse( (OBJ_NIL == pLexJ) );
    if (pLexJ) {

        obj_TraceSet(pLexJ, true);
        pToken = LexJ_TokenLookAhead(pLexJ, 1);
        XCTAssertFalse( (OBJ_NIL == pToken) );
        XCTAssertTrue( (LEXJ_CONSTANT_FLOAT == Token_getClass(pToken)) );
        pStr = Token_ToDataString(pToken);
        XCTAssertTrue( (0 == strcmp(pStringToParse, AStr_getData(pStr))) );
        obj_Release(pStr);
        pStr = OBJ_NIL;
        pToken = LexJ_TokenAdvance(pLexJ, 1);

        obj_Release(pLexJ);
        pLexJ = OBJ_NIL;
    }

    fprintf(stderr, "...%s completed.\n\n\n", pTestName);
    return 1;
}



int         test_LexJ_Number06(
    const
    char        *pTestName
)
{
    LEXJ_DATA       *pLexJ = OBJ_NIL;
    TOKEN_DATA      *pToken;
    ASTR_DATA       *pStr = OBJ_NIL;
    const
    char            *pStringToParse = "0";

    fprintf(stderr, "Performing: %s\n", pTestName);
    pLexJ = LexJ_NewA(pStringToParse, 4, true);
    XCTAssertFalse( (OBJ_NIL == pLexJ) );
    if (pLexJ) {

        obj_TraceSet(pLexJ, true);
        pToken = LexJ_TokenLookAhead(pLexJ, 1);
        XCTAssertFalse( (OBJ_NIL == pToken) );
        XCTAssertTrue( (LEXJ_CONSTANT_INTEGER == Token_getClass(pToken)) );
        pStr = Token_ToDataString(pToken);
        XCTAssertTrue( (0 == strcmp(pStringToParse, AStr_getData(pStr))) );
        obj_Release(pStr);
        pStr = OBJ_NIL;
        pToken = LexJ_TokenAdvance(pLexJ, 1);

        obj_Release(pLexJ);
        pLexJ = OBJ_NIL;
    }

    fprintf(stderr, "...%s completed.\n\n\n", pTestName);
    return 1;
}



int         test_LexJ_Number07(
   const
   char        *pTestName
)
{
    LEXJ_DATA       *pLexJ = OBJ_NIL;
    TOKEN_DATA      *pToken;
    ASTR_DATA       *pStr = OBJ_NIL;
    const
    char            *pStringToParse = "{\"one\" : -123}";

    fprintf(stderr, "Performing: %s\n", pTestName);
    pLexJ = LexJ_NewA(pStringToParse, 4, true);
    XCTAssertFalse( (OBJ_NIL == pLexJ) );
    obj_TraceSet(pLexJ, true);
    if (pLexJ) {

        pToken = LexJ_TokenLookAhead(pLexJ, 1);
        XCTAssertFalse( (OBJ_NIL == pToken) );
        XCTAssertTrue( (LEXJ_SEP_LBRACE == Token_getClass(pToken)) );
        pToken = LexJ_TokenAdvance(pLexJ, 1);
        XCTAssertFalse( (OBJ_NIL == pToken) );

        pToken = LexJ_TokenLookAhead(pLexJ, 1);
        XCTAssertFalse( (OBJ_NIL == pToken) );
        XCTAssertTrue( (LEXJ_CONSTANT_STRING == Token_getClass(pToken)) );
        pStr = Token_ToDataString(pToken);
        XCTAssertTrue( (0 == strcmp("one", AStr_getData(pStr))) );
        obj_Release(pStr);
        pStr = OBJ_NIL;
        pToken = LexJ_TokenAdvance(pLexJ, 1);
        XCTAssertFalse( (OBJ_NIL == pToken) );

        pToken = LexJ_TokenLookAhead(pLexJ, 1);
        XCTAssertFalse( (OBJ_NIL == pToken) );
        XCTAssertTrue( (LEXJ_SEP_COLON == Token_getClass(pToken)) );
        pToken = LexJ_TokenAdvance(pLexJ, 1);
        XCTAssertFalse( (OBJ_NIL == pToken) );

        pToken = LexJ_TokenLookAhead(pLexJ, 1);
        XCTAssertFalse( (OBJ_NIL == pToken) );
        XCTAssertTrue( (LEXJ_SEP_MINUS == Token_getClass(pToken)) );
        pStr = Token_ToDataString(pToken);
        XCTAssertTrue( (0 == strcmp("-", AStr_getData(pStr))) );
        obj_Release(pStr);
        pStr = OBJ_NIL;
        pToken = LexJ_TokenAdvance(pLexJ, 1);

        pToken = LexJ_TokenLookAhead(pLexJ, 1);
        XCTAssertFalse( (OBJ_NIL == pToken) );
        XCTAssertTrue( (LEXJ_CONSTANT_INTEGER == Token_getClass(pToken)) );
        pStr = Token_ToDataString(pToken);
        XCTAssertTrue( (0 == strcmp("123", AStr_getData(pStr))) );
        obj_Release(pStr);
        pStr = OBJ_NIL;
        pToken = LexJ_TokenAdvance(pLexJ, 1);

        pToken = LexJ_TokenLookAhead(pLexJ, 1);
        XCTAssertFalse( (OBJ_NIL == pToken) );
        XCTAssertTrue( (LEXJ_SEP_RBRACE == Token_getClass(pToken)) );
        pToken = LexJ_TokenAdvance(pLexJ, 1);
        XCTAssertFalse( (OBJ_NIL == pToken) );

        pToken = LexJ_TokenLookAhead(pLexJ, 1);
        XCTAssertFalse( (OBJ_NIL == pToken) );
        XCTAssertTrue( (LEX_CLASS_EOF == Token_getClass(pToken)) );
        pToken = LexJ_TokenAdvance(pLexJ, 1);
        XCTAssertFalse( (OBJ_NIL == pToken) );

        obj_Release(pLexJ);
        pLexJ = OBJ_NIL;
    }

    fprintf(stderr, "...%s completed.\n\n\n", pTestName);
    return 1;
}



int         test_LexJ_Number08(
    const
    char        *pTestName
)
{
    LEXJ_DATA       *pLexJ = OBJ_NIL;
    TOKEN_DATA      *pToken;
    ASTR_DATA       *pStr = OBJ_NIL;
    const
    char            *pStringToParse = "{\"one\" : +123}";
    ASTR_DATA       *pAStr = OBJ_NIL;

    fprintf(stderr, "Performing: %s\n", pTestName);
    pLexJ = LexJ_NewA(pStringToParse, 4, true);
    XCTAssertFalse( (OBJ_NIL == pLexJ) );
    obj_TraceSet(pLexJ, true);
    if (pLexJ) {

        pToken = LexJ_TokenLookAhead(pLexJ, 1);
        XCTAssertFalse( (OBJ_NIL == pToken) );
        XCTAssertTrue( (LEXJ_SEP_LBRACE == Token_getClass(pToken)) );
        pToken = LexJ_TokenAdvance(pLexJ, 1);
        XCTAssertFalse( (OBJ_NIL == pToken) );

        pToken = LexJ_TokenLookAhead(pLexJ, 1);
        XCTAssertFalse( (OBJ_NIL == pToken) );
        XCTAssertTrue( (LEXJ_CONSTANT_STRING == Token_getClass(pToken)) );
        pStr = Token_ToDataString(pToken);
        XCTAssertTrue( (0 == strcmp("one", AStr_getData(pStr))) );
        obj_Release(pStr);
        pStr = OBJ_NIL;
        pToken = LexJ_TokenAdvance(pLexJ, 1);
        XCTAssertFalse( (OBJ_NIL == pToken) );

        pToken = LexJ_TokenLookAhead(pLexJ, 1);
        XCTAssertFalse( (OBJ_NIL == pToken) );
        XCTAssertTrue( (LEXJ_SEP_COLON == Token_getClass(pToken)) );
        pToken = LexJ_TokenAdvance(pLexJ, 1);
        XCTAssertFalse( (OBJ_NIL == pToken) );

        pToken = LexJ_TokenLookAhead(pLexJ, 1);
        XCTAssertFalse( (OBJ_NIL == pToken) );
        XCTAssertTrue( (LEXJ_SEP_PLUS == Token_getClass(pToken)) );
        pAStr = Token_getTextAStr(pToken);
        XCTAssertTrue( (0 == strcmp("+", AStr_getData(pAStr))) );
        obj_Release(pAStr);
        pAStr = OBJ_NIL;
        pStr = Token_ToDataString(pToken);
        XCTAssertTrue( (0 == strcmp("+", AStr_getData(pStr))) );
        obj_Release(pStr);
        pStr = OBJ_NIL;
        pToken = LexJ_TokenAdvance(pLexJ, 1);

        pToken = LexJ_TokenLookAhead(pLexJ, 1);
        XCTAssertFalse( (OBJ_NIL == pToken) );
        XCTAssertTrue( (LEXJ_CONSTANT_INTEGER == Token_getClass(pToken)) );
        pStr = Token_ToDataString(pToken);
        XCTAssertTrue( (0 == strcmp("123", AStr_getData(pStr))) );
        obj_Release(pStr);
        pStr = OBJ_NIL;
        pToken = LexJ_TokenAdvance(pLexJ, 1);

        pToken = LexJ_TokenLookAhead(pLexJ, 1);
        XCTAssertFalse( (OBJ_NIL == pToken) );
        XCTAssertTrue( (LEXJ_SEP_RBRACE == Token_getClass(pToken)) );
        pToken = LexJ_TokenAdvance(pLexJ, 1);
        XCTAssertFalse( (OBJ_NIL == pToken) );

        pToken = LexJ_TokenLookAhead(pLexJ, 1);
        XCTAssertFalse( (OBJ_NIL == pToken) );
        XCTAssertTrue( (LEX_CLASS_EOF == Token_getClass(pToken)) );
        pToken = LexJ_TokenAdvance(pLexJ, 1);
        XCTAssertFalse( (OBJ_NIL == pToken) );

        obj_Release(pLexJ);
        pLexJ = OBJ_NIL;
    }

    fprintf(stderr, "...%s completed.\n\n\n", pTestName);
    return 1;
}



int         test_LexJ_Number09(
    const
    char        *pTestName
)
{
    LEXJ_DATA       *pLexJ = OBJ_NIL;
    TOKEN_DATA      *pToken;
    ASTR_DATA       *pStr = OBJ_NIL;
    const
    char            *pStringToParse = "0";

    fprintf(stderr, "Performing: %s\n", pTestName);
    pLexJ = LexJ_NewA(pStringToParse, 4, true);
    XCTAssertFalse( (OBJ_NIL == pLexJ) );
    if (pLexJ) {

        obj_TraceSet(pLexJ, true);
        pToken = LexJ_TokenLookAhead(pLexJ, 1);
        XCTAssertFalse( (OBJ_NIL == pToken) );
        XCTAssertTrue( (LEXJ_CONSTANT_INTEGER == Token_getClass(pToken)) );
        pStr = Token_ToDataString(pToken);
        XCTAssertTrue( (0 == strcmp(pStringToParse, AStr_getData(pStr))) );
        obj_Release(pStr);
        pStr = OBJ_NIL;
        pToken = LexJ_TokenAdvance(pLexJ, 1);

        obj_Release(pLexJ);
        pLexJ = OBJ_NIL;
    }

    fprintf(stderr, "...%s completed.\n\n\n", pTestName);
    return 1;
}



int         test_LexJ_Number10(
    const
    char        *pTestName
)
{
    LEXJ_DATA       *pLexJ = OBJ_NIL;
    TOKEN_DATA      *pToken;
    ASTR_DATA       *pStr = OBJ_NIL;
    const
    char            *pStringToParse = "{\"one\" : 0x11}";
    //ASTR_DATA       *pAStr = OBJ_NIL;

    fprintf(stderr, "Performing: %s\n", pTestName);
    pLexJ = LexJ_NewA(pStringToParse, 4, true);
    XCTAssertFalse( (OBJ_NIL == pLexJ) );
    obj_TraceSet(pLexJ, true);
    if (pLexJ) {

        pToken = LexJ_TokenLookAhead(pLexJ, 1);
        XCTAssertFalse( (OBJ_NIL == pToken) );
        XCTAssertTrue( (LEXJ_SEP_LBRACE == Token_getClass(pToken)) );
        pToken = LexJ_TokenAdvance(pLexJ, 1);
        XCTAssertFalse( (OBJ_NIL == pToken) );

        pToken = LexJ_TokenLookAhead(pLexJ, 1);
        XCTAssertFalse( (OBJ_NIL == pToken) );
        XCTAssertTrue( (LEXJ_CONSTANT_STRING == Token_getClass(pToken)) );
        pStr = Token_ToDataString(pToken);
        XCTAssertTrue( (0 == strcmp("one", AStr_getData(pStr))) );
        obj_Release(pStr);
        pStr = OBJ_NIL;
        pToken = LexJ_TokenAdvance(pLexJ, 1);
        XCTAssertFalse( (OBJ_NIL == pToken) );

        pToken = LexJ_TokenLookAhead(pLexJ, 1);
        XCTAssertFalse( (OBJ_NIL == pToken) );
        XCTAssertTrue( (LEXJ_SEP_COLON == Token_getClass(pToken)) );
        pToken = LexJ_TokenAdvance(pLexJ, 1);
        XCTAssertFalse( (OBJ_NIL == pToken) );

        pToken = LexJ_TokenLookAhead(pLexJ, 1);
        XCTAssertFalse( (OBJ_NIL == pToken) );
        XCTAssertTrue( (LEXJ_CONSTANT_INTEGER == Token_getClass(pToken)) );
        pStr = Token_ToDataString(pToken);
        XCTAssertTrue( (0 == strcmp("0x11", AStr_getData(pStr))) );
        obj_Release(pStr);
        pStr = OBJ_NIL;
        pToken = LexJ_TokenAdvance(pLexJ, 1);

        pToken = LexJ_TokenLookAhead(pLexJ, 1);
        XCTAssertFalse( (OBJ_NIL == pToken) );
        XCTAssertTrue( (LEXJ_SEP_RBRACE == Token_getClass(pToken)) );
        pToken = LexJ_TokenAdvance(pLexJ, 1);
        XCTAssertFalse( (OBJ_NIL == pToken) );

        pToken = LexJ_TokenLookAhead(pLexJ, 1);
        XCTAssertFalse( (OBJ_NIL == pToken) );
        XCTAssertTrue( (LEX_CLASS_EOF == Token_getClass(pToken)) );
        pToken = LexJ_TokenAdvance(pLexJ, 1);
        XCTAssertFalse( (OBJ_NIL == pToken) );

        obj_Release(pLexJ);
        pLexJ = OBJ_NIL;
    }

    fprintf(stderr, "...%s completed.\n\n\n", pTestName);
    return 1;
}



int         test_LexJ_String01(
    const
    char        *pTestName
)
{
    LEXJ_DATA       *pLexJ = OBJ_NIL;
    TOKEN_DATA      *pToken;
    ASTR_DATA       *pStr = OBJ_NIL;
    const
    char            *pStringToParse = "{\"one\" : \"\"}";

    fprintf(stderr, "Performing: %s\n", pTestName);
    pLexJ = LexJ_NewA(pStringToParse, 4, true);
    XCTAssertFalse( (OBJ_NIL == pLexJ) );
    obj_TraceSet(pLexJ, true);
    if (pLexJ) {

        pToken = LexJ_TokenLookAhead(pLexJ, 1);
        XCTAssertFalse( (OBJ_NIL == pToken) );
        XCTAssertTrue( (LEXJ_SEP_LBRACE == Token_getClass(pToken)) );
        pToken = LexJ_TokenAdvance(pLexJ, 1);
        XCTAssertFalse( (OBJ_NIL == pToken) );

        pToken = LexJ_TokenLookAhead(pLexJ, 1);
        XCTAssertFalse( (OBJ_NIL == pToken) );
        XCTAssertTrue( (LEXJ_CONSTANT_STRING == Token_getClass(pToken)) );
        pStr = Token_ToDataString(pToken);
        XCTAssertTrue( (0 == strcmp("one", AStr_getData(pStr))) );
        obj_Release(pStr);
        pStr = OBJ_NIL;
        pToken = LexJ_TokenAdvance(pLexJ, 1);
        XCTAssertFalse( (OBJ_NIL == pToken) );

        pToken = LexJ_TokenLookAhead(pLexJ, 1);
        XCTAssertFalse( (OBJ_NIL == pToken) );
        XCTAssertTrue( (LEXJ_SEP_COLON == Token_getClass(pToken)) );
        pToken = LexJ_TokenAdvance(pLexJ, 1);
        XCTAssertFalse( (OBJ_NIL == pToken) );

        pToken = LexJ_TokenLookAhead(pLexJ, 1);
        XCTAssertFalse( (OBJ_NIL == pToken) );
        XCTAssertTrue( (LEXJ_CONSTANT_STRING == Token_getClass(pToken)) );
        pStr = Token_ToDataString(pToken);
        XCTAssertTrue( (0 == strcmp("", AStr_getData(pStr))) );
        obj_Release(pStr);
        pStr = OBJ_NIL;
        pToken = LexJ_TokenAdvance(pLexJ, 1);

        pToken = LexJ_TokenLookAhead(pLexJ, 1);
        XCTAssertFalse( (OBJ_NIL == pToken) );
        XCTAssertTrue( (LEXJ_SEP_RBRACE == Token_getClass(pToken)) );
        pToken = LexJ_TokenAdvance(pLexJ, 1);
        XCTAssertFalse( (OBJ_NIL == pToken) );

        pToken = LexJ_TokenLookAhead(pLexJ, 1);
        XCTAssertFalse( (OBJ_NIL == pToken) );
        XCTAssertTrue( (LEX_CLASS_EOF == Token_getClass(pToken)) );
        pToken = LexJ_TokenAdvance(pLexJ, 1);
        XCTAssertFalse( (OBJ_NIL == pToken) );

        obj_Release(pLexJ);
        pLexJ = OBJ_NIL;
    }

    fprintf(stderr, "...%s completed.\n\n\n", pTestName);
    return 1;
}



int         test_LexJ_String02(
    const
    char        *pTestName
)
{
    LEXJ_DATA       *pLexJ = OBJ_NIL;
    TOKEN_DATA      *pToken;
    ASTR_DATA       *pStr = OBJ_NIL;
    const
    char            *pStringToParse = "{\"one\" : \"\n  \n\"}";

    fprintf(stderr, "Performing: %s\n", pTestName);
    pLexJ = LexJ_NewA(pStringToParse, 4, true);
    XCTAssertFalse( (OBJ_NIL == pLexJ) );
    obj_TraceSet(pLexJ, true);
    if (pLexJ) {

        pToken = LexJ_TokenLookAhead(pLexJ, 1);
        XCTAssertFalse( (OBJ_NIL == pToken) );
        XCTAssertTrue( (LEXJ_SEP_LBRACE == Token_getClass(pToken)) );
        pToken = LexJ_TokenAdvance(pLexJ, 1);
        XCTAssertFalse( (OBJ_NIL == pToken) );

        pToken = LexJ_TokenLookAhead(pLexJ, 1);
        XCTAssertFalse( (OBJ_NIL == pToken) );
        XCTAssertTrue( (LEXJ_CONSTANT_STRING == Token_getClass(pToken)) );
        pStr = Token_ToDataString(pToken);
        XCTAssertTrue( (0 == strcmp("one", AStr_getData(pStr))) );
        obj_Release(pStr);
        pStr = OBJ_NIL;
        pToken = LexJ_TokenAdvance(pLexJ, 1);
        XCTAssertFalse( (OBJ_NIL == pToken) );

        pToken = LexJ_TokenLookAhead(pLexJ, 1);
        XCTAssertFalse( (OBJ_NIL == pToken) );
        XCTAssertTrue( (LEXJ_SEP_COLON == Token_getClass(pToken)) );
        pToken = LexJ_TokenAdvance(pLexJ, 1);
        XCTAssertFalse( (OBJ_NIL == pToken) );

        pToken = LexJ_TokenLookAhead(pLexJ, 1);
        XCTAssertFalse( (OBJ_NIL == pToken) );
        XCTAssertTrue( (LEXJ_CONSTANT_STRING == Token_getClass(pToken)) );
        pStr = Token_ToDataString(pToken);
        fprintf(stderr, "\tString = (%d) \"%s\"\n",AStr_getLength(pStr), AStr_getData(pStr));
        XCTAssertTrue( (0 == strcmp("\\n  \\n", AStr_getData(pStr))) );
        obj_Release(pStr);
        pStr = OBJ_NIL;
        pToken = LexJ_TokenAdvance(pLexJ, 1);

        pToken = LexJ_TokenLookAhead(pLexJ, 1);
        XCTAssertFalse( (OBJ_NIL == pToken) );
        XCTAssertTrue( (LEXJ_SEP_RBRACE == Token_getClass(pToken)) );
        pToken = LexJ_TokenAdvance(pLexJ, 1);
        XCTAssertFalse( (OBJ_NIL == pToken) );

        pToken = LexJ_TokenLookAhead(pLexJ, 1);
        XCTAssertFalse( (OBJ_NIL == pToken) );
        XCTAssertTrue( (LEX_CLASS_EOF == Token_getClass(pToken)) );
        pToken = LexJ_TokenAdvance(pLexJ, 1);
        XCTAssertFalse( (OBJ_NIL == pToken) );

        obj_Release(pLexJ);
        pLexJ = OBJ_NIL;
    }

    fprintf(stderr, "...%s completed.\n\n\n", pTestName);
    return 1;
}



int         test_LexJ_String03(
    const
    char        *pTestName
)
{
    LEXJ_DATA       *pLexJ = OBJ_NIL;
    TOKEN_DATA      *pToken;
    ASTR_DATA       *pStr = OBJ_NIL;
    const
    char            *pStringToParse = "{\"data\" : \"\\x01\\x02\\n\"}";

    fprintf(stderr, "Performing: %s\n", pTestName);
    pLexJ = LexJ_NewA(pStringToParse, 4, true);
    XCTAssertFalse( (OBJ_NIL == pLexJ) );
    obj_TraceSet(pLexJ, true);
    if (pLexJ) {

        pToken = LexJ_TokenLookAhead(pLexJ, 1);
        XCTAssertFalse( (OBJ_NIL == pToken) );
        XCTAssertTrue( (LEXJ_SEP_LBRACE == Token_getClass(pToken)) );
        pToken = LexJ_TokenAdvance(pLexJ, 1);
        XCTAssertFalse( (OBJ_NIL == pToken) );

        pToken = LexJ_TokenLookAhead(pLexJ, 1);
        XCTAssertFalse( (OBJ_NIL == pToken) );
        XCTAssertTrue( (LEXJ_CONSTANT_STRING == Token_getClass(pToken)) );
        pStr = Token_ToDataString(pToken);
        XCTAssertTrue( (0 == strcmp("data", AStr_getData(pStr))) );
        obj_Release(pStr);
        pStr = OBJ_NIL;
        pToken = LexJ_TokenAdvance(pLexJ, 1);
        XCTAssertFalse( (OBJ_NIL == pToken) );

        pToken = LexJ_TokenLookAhead(pLexJ, 1);
        XCTAssertFalse( (OBJ_NIL == pToken) );
        XCTAssertTrue( (LEXJ_SEP_COLON == Token_getClass(pToken)) );
        pToken = LexJ_TokenAdvance(pLexJ, 1);
        XCTAssertFalse( (OBJ_NIL == pToken) );

        pToken = LexJ_TokenLookAhead(pLexJ, 1);
        XCTAssertFalse( (OBJ_NIL == pToken) );
        {
            ASTR_DATA           *pWrk2 = Token_ToDebugString(pToken, 0);
            fprintf(stderr, "\tToken = %s\n", AStr_getData(pWrk2));
            obj_Release(pWrk2);
            pWrk2 = OBJ_NIL;
        }
        XCTAssertTrue( (LEXJ_CONSTANT_STRING == Token_getClass(pToken)) );
        pStr = Token_ToDataString(pToken);
        fprintf(stderr, "\tString = (%d) \"%s\"\n",AStr_getLength(pStr), AStr_getData(pStr));
        XCTAssertTrue( (0 == strcmp("\\x01\\x02\\n", AStr_getData(pStr))) );
        obj_Release(pStr);
        pStr = OBJ_NIL;
        pToken = LexJ_TokenAdvance(pLexJ, 1);

        pToken = LexJ_TokenLookAhead(pLexJ, 1);
        XCTAssertFalse( (OBJ_NIL == pToken) );
        XCTAssertTrue( (LEXJ_SEP_RBRACE == Token_getClass(pToken)) );
        pToken = LexJ_TokenAdvance(pLexJ, 1);
        XCTAssertFalse( (OBJ_NIL == pToken) );

        pToken = LexJ_TokenLookAhead(pLexJ, 1);
        XCTAssertFalse( (OBJ_NIL == pToken) );
        XCTAssertTrue( (LEX_CLASS_EOF == Token_getClass(pToken)) );
        pToken = LexJ_TokenAdvance(pLexJ, 1);
        XCTAssertFalse( (OBJ_NIL == pToken) );

        obj_Release(pLexJ);
        pLexJ = OBJ_NIL;
    }

    fprintf(stderr, "...%s completed.\n\n\n", pTestName);
    return 1;
}



int         test_LexJ_String04(
    const
    char        *pTestName
)
{
    LEXJ_DATA       *pLexJ = OBJ_NIL;
    TOKEN_DATA      *pToken;
    ASTR_DATA       *pStr = OBJ_NIL;
    const
    char            *pStringToParse = "{\"m\" : 2, \"n\" : 3}";

    fprintf(stderr, "Performing: %s\n", pTestName);
    pLexJ = LexJ_NewA(pStringToParse, 4, true);
    XCTAssertFalse( (OBJ_NIL == pLexJ) );
    obj_TraceSet(pLexJ, true);
    if (pLexJ) {

        pToken = LexJ_TokenLookAhead(pLexJ, 1);
        XCTAssertFalse( (OBJ_NIL == pToken) );
        XCTAssertTrue( (LEXJ_SEP_LBRACE == Token_getClass(pToken)) );
        pToken = LexJ_TokenAdvance(pLexJ, 1);
        XCTAssertFalse( (OBJ_NIL == pToken) );

        pToken = LexJ_TokenLookAhead(pLexJ, 1);
        XCTAssertFalse( (OBJ_NIL == pToken) );
        XCTAssertTrue( (LEXJ_CONSTANT_STRING == Token_getClass(pToken)) );
        pStr = Token_ToDataString(pToken);
        XCTAssertTrue( (0 == strcmp("m", AStr_getData(pStr))) );
        obj_Release(pStr);
        pStr = OBJ_NIL;
        pToken = LexJ_TokenAdvance(pLexJ, 1);
        XCTAssertFalse( (OBJ_NIL == pToken) );

        pToken = LexJ_TokenLookAhead(pLexJ, 1);
        XCTAssertFalse( (OBJ_NIL == pToken) );
        XCTAssertTrue( (LEXJ_SEP_COLON == Token_getClass(pToken)) );
        pToken = LexJ_TokenAdvance(pLexJ, 1);
        XCTAssertFalse( (OBJ_NIL == pToken) );

        pToken = LexJ_TokenLookAhead(pLexJ, 1);
        XCTAssertFalse( (OBJ_NIL == pToken) );
        XCTAssertTrue( (LEXJ_CONSTANT_INTEGER == Token_getClass(pToken)) );
        pStr = Token_ToDataString(pToken);
        XCTAssertTrue( (0 == strcmp("2", AStr_getData(pStr))) );
        obj_Release(pStr);
        pStr = OBJ_NIL;
        pToken = LexJ_TokenAdvance(pLexJ, 1);

        pToken = LexJ_TokenLookAhead(pLexJ, 1);
        XCTAssertFalse( (OBJ_NIL == pToken) );
        XCTAssertTrue( (LEXJ_SEP_COMMA == Token_getClass(pToken)) );
        pToken = LexJ_TokenAdvance(pLexJ, 1);
        XCTAssertFalse( (OBJ_NIL == pToken) );

        pToken = LexJ_TokenLookAhead(pLexJ, 1);
        XCTAssertFalse( (OBJ_NIL == pToken) );
        XCTAssertTrue( (LEXJ_CONSTANT_STRING == Token_getClass(pToken)) );
        pStr = Token_ToDataString(pToken);
        XCTAssertTrue( (0 == strcmp("n", AStr_getData(pStr))) );
        obj_Release(pStr);
        pStr = OBJ_NIL;
        pToken = LexJ_TokenAdvance(pLexJ, 1);
        XCTAssertFalse( (OBJ_NIL == pToken) );

        pToken = LexJ_TokenLookAhead(pLexJ, 1);
        XCTAssertFalse( (OBJ_NIL == pToken) );
        XCTAssertTrue( (LEXJ_SEP_COLON == Token_getClass(pToken)) );
        pToken = LexJ_TokenAdvance(pLexJ, 1);
        XCTAssertFalse( (OBJ_NIL == pToken) );

        pToken = LexJ_TokenLookAhead(pLexJ, 1);
        XCTAssertFalse( (OBJ_NIL == pToken) );
        XCTAssertTrue( (LEXJ_CONSTANT_INTEGER == Token_getClass(pToken)) );
        pStr = Token_ToDataString(pToken);
        XCTAssertTrue( (0 == strcmp("3", AStr_getData(pStr))) );
        obj_Release(pStr);
        pStr = OBJ_NIL;
        pToken = LexJ_TokenAdvance(pLexJ, 1);

        pToken = LexJ_TokenLookAhead(pLexJ, 1);
        XCTAssertFalse( (OBJ_NIL == pToken) );
        XCTAssertTrue( (LEXJ_SEP_RBRACE == Token_getClass(pToken)) );
        pToken = LexJ_TokenAdvance(pLexJ, 1);
        XCTAssertFalse( (OBJ_NIL == pToken) );

        pToken = LexJ_TokenLookAhead(pLexJ, 1);
        XCTAssertFalse( (OBJ_NIL == pToken) );
        XCTAssertTrue( (LEX_CLASS_EOF == Token_getClass(pToken)) );
        pToken = LexJ_TokenAdvance(pLexJ, 1);
        XCTAssertFalse( (OBJ_NIL == pToken) );

        obj_Release(pLexJ);
        pLexJ = OBJ_NIL;
    }

    fprintf(stderr, "...%s completed.\n\n\n", pTestName);
    return 1;
}




TINYTEST_START_SUITE(test_LexJ);
    TINYTEST_ADD_TEST(test_LexJ_String04,setUp,tearDown);
    TINYTEST_ADD_TEST(test_LexJ_String03,setUp,tearDown);
    TINYTEST_ADD_TEST(test_LexJ_String02,setUp,tearDown);
    TINYTEST_ADD_TEST(test_LexJ_String01,setUp,tearDown);
    //TINYTEST_ADD_TEST(test_LexJ_Number10,setUp,tearDown);
    //TINYTEST_ADD_TEST(test_LexJ_Number09,setUp,tearDown);
    TINYTEST_ADD_TEST(test_LexJ_Number08,setUp,tearDown);
    TINYTEST_ADD_TEST(test_LexJ_Number07,setUp,tearDown);
    TINYTEST_ADD_TEST(test_LexJ_Number06,setUp,tearDown);
    TINYTEST_ADD_TEST(test_LexJ_Number05,setUp,tearDown);
    TINYTEST_ADD_TEST(test_LexJ_Number04,setUp,tearDown);
    TINYTEST_ADD_TEST(test_LexJ_Number03,setUp,tearDown);
    TINYTEST_ADD_TEST(test_LexJ_Number02,setUp,tearDown);
    TINYTEST_ADD_TEST(test_LexJ_Number01,setUp,tearDown);
    TINYTEST_ADD_TEST(test_lexj01,setUp,tearDown);
    TINYTEST_ADD_TEST(test_LexJ_Test01,setUp,tearDown);
    //TINYTEST_ADD_TEST(test_LexJ_Copy01,setUp,tearDown);
    TINYTEST_ADD_TEST(test_LexJ_OpenClose,setUp,tearDown);
TINYTEST_END_SUITE();

TINYTEST_MAIN_SINGLE_SUITE(test_LexJ);





