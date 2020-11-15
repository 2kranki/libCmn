// vi:nu:et:sts=4 ts=4 sw=4
/*
 *  Generated 05/30/2020 14:51:55
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
#include    <Lex01_internal.h>
#include    <ascii.h>
#include    <Lex.h>
#include    <SrcErrors.h>
#include    <SrcFile.h>
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






int             test_Lex01_OpenClose (
    const
    char            *pTestName
)
{
    ERESULT         eRc = ERESULT_SUCCESS;
    LEX01_DATA       *pObj = OBJ_NIL;
    bool            fRc;
   
    fprintf(stderr, "Performing: %s\n", pTestName);

    pObj = Lex01_Alloc( );
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    pObj = Lex01_Init( pObj );
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    if (pObj) {

        //obj_TraceSet(pObj, true);       
        fRc = obj_IsKindOf(pObj, OBJ_IDENT_LEX01);
        TINYTEST_TRUE( (fRc) );
        
        // Test something.
        TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );

        obj_Release(pObj);
        pObj = OBJ_NIL;
    }

    fprintf(stderr, "...%s completed.\n\n\n", pTestName);
    return 1;
}



int             test_Lex01_Copy01 (
    const
    char            *pTestName
)
{
    ERESULT         eRc = ERESULT_SUCCESS;
    LEX01_DATA       *pObj1 = OBJ_NIL;
    LEX01_DATA       *pObj2 = OBJ_NIL;
    bool            fRc;
#if defined(LEX01_JSON_SUPPORT) && defined(XYZZY)
    ASTR_DATA       *pStr = OBJ_NIL;
#endif
   
    fprintf(stderr, "Performing: %s\n", pTestName);

    pObj1 = Lex01_New( );
    TINYTEST_FALSE( (OBJ_NIL == pObj1) );
    if (pObj1) {

        //obj_TraceSet(pObj1, true);       
        fRc = obj_IsKindOf(pObj1, OBJ_IDENT_LEX01);
        TINYTEST_TRUE( (fRc) );
        
        // Test assign.
        pObj2 = Lex01_New();
        TINYTEST_FALSE( (OBJ_NIL == pObj2) );
        eRc = Lex01_Assign(pObj1, pObj2);
        TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );

        fRc = obj_IsKindOf(pObj2, OBJ_IDENT_LEX01);
        TINYTEST_TRUE( (fRc) );
        //eRc = Lex01_Compare(pObj1, pObj2);
        //TINYTEST_TRUE( (0 == eRc) );
        //TODO: Add More tests here!

        obj_Release(pObj2);
        pObj2 = OBJ_NIL;

        // Test copy.
        pObj2 = Lex01_Copy(pObj1);
        TINYTEST_FALSE( (OBJ_NIL == pObj2) );

        fRc = obj_IsKindOf(pObj2, OBJ_IDENT_LEX01);
        TINYTEST_TRUE( (fRc) );
        //eRc = Lex01_Compare(pObj1, pObj2);
        //TINYTEST_TRUE( (0 == eRc) );
        //TODO: Add More tests here!

        obj_Release(pObj2);
        pObj2 = OBJ_NIL;

        // Test json support.
#if defined(LEX01_JSON_SUPPORT) && defined(XYZZY)
        pStr = Lex01_ToJson(pObj1);
        TINYTEST_FALSE( (OBJ_NIL == pStr) );
        fprintf(stderr, "JSON: %s\n", AStr_getData(pStr));
        pObj2 = Lex01_NewFromJsonString(pStr);
        TINYTEST_FALSE( (OBJ_NIL == pObj2) );
        fRc = obj_IsKindOf(pObj2, OBJ_IDENT_LEX01);
        TINYTEST_TRUE( (fRc) );
        obj_Release(pStr);
        pStr = OBJ_NIL;
        //eRc = Lex01_Compare(pObj1, pObj2);
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



int             test_Lex01_Test01 (
    const
    char            *pTestName
)
{
    //ERESULT         eRc = ERESULT_SUCCESS;
    LEX01_DATA       *pObj = OBJ_NIL;
    bool            fRc;
   
    fprintf(stderr, "Performing: %s\n", pTestName);

    pObj = Lex01_New( );
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    if (pObj) {

        //obj_TraceSet(pObj, true);       
        fRc = obj_IsKindOf(pObj, OBJ_IDENT_LEX01);
        TINYTEST_TRUE( (fRc) );
        //TINYTEST_TRUE( (ERESULT_OK(eRc)) );
        
        {
            ASTR_DATA       *pStr = Lex01_ToDebugString(pObj, 0);
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



int         test_Lex01_Input01(
    const
    char        *test_name
)
{
    SRCFILE_DATA    *pSrc = OBJ_NIL;
    ASTR_DATA       *pBuf = OBJ_NIL;
    LEX_DATA        *pLex = OBJ_NIL;
    TOKEN_DATA      *pToken;
    bool            fRc;
    PATH_DATA       *pPath = Path_NewA("abc");
    int32_t         cls;
    W32CHR_T        chr;

    fprintf(stderr, "Scanning:\n%s\n\n", pTestInput01);
    pBuf = AStr_NewA(pTestInput01);
    XCTAssertFalse( (OBJ_NIL == pBuf) );
    if (pBuf) {

        pSrc = SrcFile_NewFromAStr(pPath, pBuf, 1, 4);
        XCTAssertFalse( (OBJ_NIL == pSrc) );
        if (pSrc) {

            obj_TraceSet(pSrc, true);

            pLex = (LEX_DATA *)Lex01_New();
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

                // 1st Line - "+ ??( ??)\n"
                pToken = Lex_TokenLookAhead(pLex, 1);
                XCTAssertFalse( (OBJ_NIL == pToken) );
                cls = Token_getClass(pToken);
                fprintf(stderr, "\tcls = (%d) %s\n", cls, Lex_ClassToString(cls));
                chr = Token_getChrW32(pToken);
                fprintf(stderr, "\tchr = '%c' (0x%04X)\n", ascii_toPrintW32(chr), chr);
                XCTAssertTrue( ('+' == Token_getClass(pToken)) );
                XCTAssertTrue( ('+' == Token_getChrW32(pToken)) );
                pToken = Lex_TokenAdvance(pLex, 1);
                XCTAssertFalse( (OBJ_NIL == pToken) );

                pToken = Lex_TokenLookAhead(pLex, 1);
                XCTAssertFalse( (OBJ_NIL == pToken) );
                cls = Token_getClass(pToken);
                fprintf(stderr, "\tcls = (%d)-%s\n", cls, Lex_ClassToString(cls));
                XCTAssertTrue( (ASCII_LEXICAL_WHITESPACE == Token_getClass(pToken)) );
                pToken = Lex_TokenAdvance(pLex, 1);
                XCTAssertFalse( (OBJ_NIL == pToken) );

                pToken = Lex_TokenLookAhead(pLex, 1);
                XCTAssertFalse( (OBJ_NIL == pToken) );
                cls = Token_getClass(pToken);
                fprintf(stderr, "\tcls = (%d) %s\n", cls, Lex_ClassToString(cls));
                chr = Token_getChrW32(pToken);
                fprintf(stderr, "\tchr = '%c' (0x%04X)\n", ascii_toPrintW32(chr), chr);
                fprintf(stderr, "[ == %c\n", Token_getClass(pToken));
                XCTAssertTrue( ('[' == Token_getClass(pToken)) );
                XCTAssertTrue( ('[' == Token_getChrW32(pToken)) );
                pToken = Lex_TokenAdvance(pLex, 1);
                XCTAssertFalse( (OBJ_NIL == pToken) );

                pToken = Lex_TokenLookAhead(pLex, 1);
                XCTAssertFalse( (OBJ_NIL == pToken) );
                cls = Token_getClass(pToken);
                fprintf(stderr, "\tcls = (%d)-%s\n", cls, Lex_ClassToString(cls));
                XCTAssertTrue( (ASCII_LEXICAL_WHITESPACE == Token_getClass(pToken)) );
                pToken = Lex_TokenAdvance(pLex, 1);
                XCTAssertFalse( (OBJ_NIL == pToken) );

                pToken = Lex_TokenLookAhead(pLex, 1);
                XCTAssertFalse( (OBJ_NIL == pToken) );
                cls = Token_getClass(pToken);
                fprintf(stderr, "\tcls = (%d) %s\n", cls, Lex_ClassToString(cls));
                chr = Token_getChrW32(pToken);
                fprintf(stderr, "\tchr = '%c' (0x%04X)\n", ascii_toPrintW32(chr), chr);
                XCTAssertTrue( (']' == Token_getClass(pToken)) );
                XCTAssertTrue( (']' == Token_getChrW32(pToken)) );
                pToken = Lex_TokenAdvance(pLex, 1);
                XCTAssertFalse( (OBJ_NIL == pToken) );

                pToken = Lex_TokenLookAhead(pLex, 1);
                XCTAssertFalse( (OBJ_NIL == pToken) );
                cls = Token_getClass(pToken);
                fprintf(stderr, "\tcls = (%d)-%s\n", cls, Lex_ClassToString(cls));
                XCTAssertTrue( (ASCII_LEXICAL_EOL == Token_getClass(pToken)) );
                pToken = Lex_TokenAdvance(pLex, 1);
                XCTAssertFalse( (OBJ_NIL == pToken) );

                // 2nd Line - "\ta??/b??'??<??>\n"
                pToken = Lex_TokenLookAhead(pLex, 1);
                XCTAssertFalse( (OBJ_NIL == pToken) );
                cls = Token_getClass(pToken);
                fprintf(stderr, "\tcls = (%d)-%s\n", cls, Lex_ClassToString(cls));
                XCTAssertTrue( (ASCII_LEXICAL_WHITESPACE == Token_getClass(pToken)) );
                pToken = Lex_TokenAdvance(pLex, 1);
                XCTAssertFalse( (OBJ_NIL == pToken) );

                pToken = Lex_TokenLookAhead(pLex, 1);
                XCTAssertFalse( (OBJ_NIL == pToken) );
                cls = Token_getClass(pToken);
                fprintf(stderr, "\tcls = (%d)-%s\n", cls, Lex_ClassToString(cls));
                XCTAssertTrue( (ASCII_LEXICAL_WHITESPACE == Token_getClass(pToken)) );
                pToken = Lex_TokenAdvance(pLex, 1);
                XCTAssertFalse( (OBJ_NIL == pToken) );

                pToken = Lex_TokenLookAhead(pLex, 1);
                XCTAssertFalse( (OBJ_NIL == pToken) );
                cls = Token_getClass(pToken);
                fprintf(stderr, "\tcls = (%d)-%s\n", cls, Lex_ClassToString(cls));
                XCTAssertTrue( (ASCII_LEXICAL_WHITESPACE == Token_getClass(pToken)) );
                pToken = Lex_TokenAdvance(pLex, 1);
                XCTAssertFalse( (OBJ_NIL == pToken) );

                pToken = Lex_TokenLookAhead(pLex, 1);
                XCTAssertFalse( (OBJ_NIL == pToken) );
                cls = Token_getClass(pToken);
                fprintf(stderr, "\tcls = (%d)-%s\n", cls, Lex_ClassToString(cls));
                XCTAssertTrue( (ASCII_LEXICAL_WHITESPACE == Token_getClass(pToken)) );
                pToken = Lex_TokenAdvance(pLex, 1);
                XCTAssertFalse( (OBJ_NIL == pToken) );

                pToken = Lex_TokenLookAhead(pLex, 1);
                XCTAssertFalse( (OBJ_NIL == pToken) );
                cls = Token_getClass(pToken);
                fprintf(stderr, "\tcls = (%d)-%s\n", cls, Lex_ClassToString(cls));
                XCTAssertTrue( (ASCII_LEXICAL_ALPHA_LOWER == Token_getClass(pToken)) );
                XCTAssertTrue( ('a' == Token_getChrW32(pToken)) );
                pToken = Lex_TokenAdvance(pLex, 1);
                XCTAssertFalse( (OBJ_NIL == pToken) );

                pToken = Lex_TokenLookAhead(pLex, 1);
                XCTAssertFalse( (OBJ_NIL == pToken) );
                cls = Token_getClass(pToken);
                fprintf(stderr, "\tcls = (%d)-%s\n", cls, Lex_ClassToString(cls));
                XCTAssertTrue( ('\\' == cls) );
                XCTAssertTrue( ('\\' == Token_getChrW32(pToken)) );
                pToken = Lex_TokenAdvance(pLex, 1);
                XCTAssertFalse( (OBJ_NIL == pToken) );

                pToken = Lex_TokenLookAhead(pLex, 1);
                XCTAssertFalse( (OBJ_NIL == pToken) );
                cls = Token_getClass(pToken);
                fprintf(stderr, "\tcls = (%d)-%s\n", cls, Lex_ClassToString(cls));
                XCTAssertTrue( (ASCII_LEXICAL_ALPHA_LOWER == Token_getClass(pToken)) );
                XCTAssertTrue( ('b' == Token_getChrW32(pToken)) );
                pToken = Lex_TokenAdvance(pLex, 1);
                XCTAssertFalse( (OBJ_NIL == pToken) );

                pToken = Lex_TokenLookAhead(pLex, 1);
                XCTAssertFalse( (OBJ_NIL == pToken) );
                XCTAssertTrue( ('^' == Token_getClass(pToken)) );
                XCTAssertTrue( ('^' == Token_getChrW32(pToken)) );
                pToken = Lex_TokenAdvance(pLex, 1);
                XCTAssertFalse( (OBJ_NIL == pToken) );

                pToken = Lex_TokenLookAhead(pLex, 1);
                XCTAssertFalse( (OBJ_NIL == pToken) );
                XCTAssertTrue( ('{' == Token_getClass(pToken)) );
                XCTAssertTrue( ('{' == Token_getChrW32(pToken)) );
                pToken = Lex_TokenAdvance(pLex, 1);
                XCTAssertFalse( (OBJ_NIL == pToken) );

                pToken = Lex_TokenLookAhead(pLex, 1);
                XCTAssertFalse( (OBJ_NIL == pToken) );
                XCTAssertTrue( ('}' == Token_getClass(pToken)) );
                XCTAssertTrue( ('}' == Token_getChrW32(pToken)) );
                pToken = Lex_TokenAdvance(pLex, 1);
                XCTAssertFalse( (OBJ_NIL == pToken) );

                pToken = Lex_TokenLookAhead(pLex, 1);
                XCTAssertFalse( (OBJ_NIL == pToken) );
                XCTAssertTrue( (ASCII_LEXICAL_EOL == Token_getClass(pToken)) );
                pToken = Lex_TokenAdvance(pLex, 1);
                XCTAssertFalse( (OBJ_NIL == pToken) );

                // 3rd Line - "??!??-ab??=\n"
                pToken = Lex_TokenLookAhead(pLex, 1);
                XCTAssertFalse( (OBJ_NIL == pToken) );
                XCTAssertTrue( ('|' == Token_getClass(pToken)) );
                XCTAssertTrue( ('|' == Token_getChrW32(pToken)) );
                pToken = Lex_TokenAdvance(pLex, 1);
                XCTAssertFalse( (OBJ_NIL == pToken) );

                pToken = Lex_TokenLookAhead(pLex, 1);
                XCTAssertFalse( (OBJ_NIL == pToken) );
                XCTAssertTrue( ('~' == Token_getClass(pToken)) );
                XCTAssertTrue( ('~' == Token_getChrW32(pToken)) );
                pToken = Lex_TokenAdvance(pLex, 1);
                XCTAssertFalse( (OBJ_NIL == pToken) );

                pToken = Lex_TokenLookAhead(pLex, 1);
                XCTAssertFalse( (OBJ_NIL == pToken) );
                XCTAssertTrue( (ASCII_LEXICAL_ALPHA_LOWER == Token_getClass(pToken)) );
                XCTAssertTrue( ('a' == Token_getChrW32(pToken)) );
                pToken = Lex_TokenAdvance(pLex, 1);
                XCTAssertFalse( (OBJ_NIL == pToken) );

                pToken = Lex_TokenLookAhead(pLex, 1);
                XCTAssertFalse( (OBJ_NIL == pToken) );
                XCTAssertTrue( (ASCII_LEXICAL_ALPHA_LOWER == Token_getClass(pToken)) );
                XCTAssertTrue( ('b' == Token_getChrW32(pToken)) );
                pToken = Lex_TokenAdvance(pLex, 1);
                XCTAssertFalse( (OBJ_NIL == pToken) );

                pToken = Lex_TokenLookAhead(pLex, 1);
                XCTAssertFalse( (OBJ_NIL == pToken) );
                XCTAssertTrue( ('#' == Token_getClass(pToken)) );
                XCTAssertTrue( ('#' == Token_getChrW32(pToken)) );
                pToken = Lex_TokenAdvance(pLex, 1);
                XCTAssertFalse( (OBJ_NIL == pToken) );

                pToken = Lex_TokenLookAhead(pLex, 1);
                XCTAssertFalse( (OBJ_NIL == pToken) );
                XCTAssertTrue( (ASCII_LEXICAL_EOL == Token_getClass(pToken)) );
                pToken = Lex_TokenAdvance(pLex, 1);
                XCTAssertFalse( (OBJ_NIL == pToken) );

                pToken = Lex_TokenLookAhead(pLex, 1);
                XCTAssertFalse( (OBJ_NIL == pToken) );
                XCTAssertTrue( (LEX_CLASS_EOF == Token_getClass(pToken)) );
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




TINYTEST_START_SUITE(test_Lex01);
    TINYTEST_ADD_TEST(test_Lex01_Input01,setUp,tearDown);
    TINYTEST_ADD_TEST(test_Lex01_Test01,setUp,tearDown);
    //TINYTEST_ADD_TEST(test_Lex01_Copy01,setUp,tearDown);
    TINYTEST_ADD_TEST(test_Lex01_OpenClose,setUp,tearDown);
TINYTEST_END_SUITE();

TINYTEST_MAIN_SINGLE_SUITE(test_Lex01);





