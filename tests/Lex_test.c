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
        //TINYTEST_TRUE( (ERESULT_SUCCESS_EQUAL == eRc) );
        //TODO: Add More tests here!

        obj_Release(pObj2);
        pObj2 = OBJ_NIL;

        // Test copy.
        pObj2 = Lex_Copy(pObj1);
        TINYTEST_FALSE( (OBJ_NIL == pObj2) );

        fRc = obj_IsKindOf(pObj2, OBJ_IDENT_LEX);
        TINYTEST_TRUE( (fRc) );
        //eRc = Lex_Compare(pObj1, pObj2);
        //TINYTEST_TRUE( (ERESULT_SUCCESS_EQUAL == eRc) );
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



int             test_Lex_Test01 (
    const
    char            *pTestName
)
{
    //ERESULT         eRc = ERESULT_SUCCESS;
    LEX_DATA       *pObj = OBJ_NIL;
    bool            fRc;
   
    fprintf(stderr, "Performing: %s\n", pTestName);

    pObj = Lex_New( );
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    if (pObj) {

        //obj_TraceSet(pObj, true);       
        fRc = obj_IsKindOf(pObj, OBJ_IDENT_LEX);
        TINYTEST_TRUE( (fRc) );
        //TINYTEST_TRUE( (ERESULT_OK(eRc)) );
        
        {
            ASTR_DATA       *pStr = Lex_ToDebugString(pObj, 0);
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



int         test_Lex_Number01(
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
    uint16_t        newClass;
    ERESULT         eRc;

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

                pToken = SrcFile_InputLookAhead(pSrc, 1);
                eRc = Lex_ParseTokenSetup(pLex, pToken);
                XCTAssertFalse( (ERESULT_FAILED(eRc)) );
                newClass = Lex_ParseNumber(pLex);
                XCTAssertTrue( (LEX_CONSTANT_INTEGER == newClass) );
                eRc = W32Str_CompareA(pLex->pStr, "123");
                XCTAssertTrue( (ERESULT_SUCCESS_EQUAL == eRc) );

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
    bool            fRc;
    PATH_DATA       *pPath = Path_NewA("abc");
    uint16_t        newClass;
    ERESULT         eRc;

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

                pToken = SrcFile_InputLookAhead(pSrc, 1);
                eRc = Lex_ParseTokenSetup(pLex, pToken);
                newClass = Lex_ParseNumber(pLex);
                XCTAssertTrue( (LEX_CONSTANT_FLOAT == newClass) );
                eRc = W32Str_CompareA(pLex->pStr, "123.456");
                XCTAssertTrue( (ERESULT_SUCCESS_EQUAL == eRc) );

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
    bool            fRc;
    PATH_DATA       *pPath = Path_NewA("abc");
    uint16_t        newClass;
    ERESULT         eRc;

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

                pToken = SrcFile_InputLookAhead(pSrc, 1);
                eRc = Lex_ParseTokenSetup(pLex, pToken);
                newClass = Lex_ParseNumber(pLex);
                XCTAssertTrue( (LEX_CONSTANT_INTEGER == newClass) );
                eRc = W32Str_CompareA(pLex->pStr, "0");
                XCTAssertTrue( (ERESULT_SUCCESS_EQUAL == eRc) );

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
    bool            fRc;
    PATH_DATA       *pPath = Path_NewA("abc");
    uint16_t        newClass;
    ERESULT         eRc;

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

                pToken = SrcFile_InputLookAhead(pSrc, 1);
                eRc = Lex_ParseTokenSetup(pLex, pToken);
                newClass = Lex_ParseNumber(pLex);
                if (pLex->pStr) {
                    ASTR_DATA       *pStr = W32Str_ToChrCon(pLex->pStr);
                    fprintf(stderr, "Scanned: %s\n", AStr_getData(pStr));
                    obj_Release(pStr);
                }
                XCTAssertTrue( (LEX_CONSTANT_FLOAT == newClass) );
                eRc = W32Str_CompareA(pLex->pStr, "3.141600E+00");
                XCTAssertTrue( (ERESULT_SUCCESS_EQUAL == eRc) );

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
    LEX_DATA        *pObj = OBJ_NIL;
    ERESULT         eRc;
    TOKEN_DATA      *pToken;
    ASTR_DATA       *pStr;
    int32_t         cls;
    TOKEN_DATA      *pWork = OBJ_NIL;
    SRCLOC          src = {1,2,3,4};

    fprintf(stderr, "Performing: %s\n", pTestName);
    pObj = Lex_New( );
    XCTAssertFalse( (OBJ_NIL == pObj) );
    if (pObj) {

        pWork = Token_NewCharW32(&src, 'd', 'd');
        eRc = Lex_ParseTokenSetup(pObj, pWork);
        XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
        obj_Release(pWork);
        pWork = OBJ_NIL;

        pWork = Token_NewCharW32(&src, 'e', 'e');
        eRc = Lex_ParseTokenAppendString(pObj, pWork);
        XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
        obj_Release(pWork);
        pWork = OBJ_NIL;

        pWork = Token_NewCharW32(&src, 'f', 'f');
        eRc = Lex_ParseTokenAppendString(pObj, pWork);
        XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
        obj_Release(pWork);
        pWork = OBJ_NIL;

        eRc = Lex_ParseTokenFinalize(pObj,'a',true);
        XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
        pToken = Lex_getToken(pObj);
        pStr = Token_getTextAStr(pToken);
        eRc = AStr_CompareA(pStr, "def");
        XCTAssertTrue( (ERESULT_SUCCESS_EQUAL == eRc) );
        obj_Release(pStr);
        cls = Token_getClass(pToken);
        XCTAssertTrue( ('a' == cls) );

        obj_Release(pObj);
        pObj = OBJ_NIL;
    }

    fprintf(stderr, "...%s completed.\n\n\n", pTestName);
    return 1;
}



int         test_Lex_Strings02(
    const
    char        *pTestName
)
{
    LEX_DATA        *pObj = OBJ_NIL;
    ERESULT         eRc;
    TOKEN_DATA      *pToken;
    ASTR_DATA       *pStr;
    int32_t         cls;
    TOKEN_DATA      *pWork = OBJ_NIL;
    SRCLOC          src = {1,2,3,4};

    fprintf(stderr, "Performing: %s\n", pTestName);
    pObj = Lex_New( );
    XCTAssertFalse( (OBJ_NIL == pObj) );
    if (pObj) {

        pWork = Token_NewStrA(&src, 510, "\n  \n");
        XCTAssertFalse( (OBJ_NIL == pWork) );

        eRc = Lex_ParseTokenSetup(pObj, pWork);
        XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
        obj_Release(pWork);
        pWork = OBJ_NIL;

        eRc = Lex_ParseTokenFinalize(pObj, 512, true);
        XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
        pToken = Lex_getToken(pObj);
        pStr = Token_getTextAStr(pToken);
        XCTAssertFalse( (OBJ_NIL == pObj) );
        if (pStr) {
            fprintf(stderr, "\toutput = \"%s\"\n", AStr_getData(pStr));
            eRc = AStr_CompareA(pStr, "\n  \n");
            XCTAssertTrue( (ERESULT_SUCCESS_EQUAL == eRc) );
        }
        obj_Release(pStr);
        cls = Token_getClass(pToken);
        fprintf(stderr, "\tclass = %d\n", cls);
        XCTAssertTrue( (512 == cls) );

        obj_Release(pObj);
        pObj = OBJ_NIL;
    }

    fprintf(stderr, "...%s completed.\n\n\n", pTestName);
    return 1;
}



int         test_Lex_Strings03(
    const
    char        *pTestName
)
{
    LEX_DATA        *pObj = OBJ_NIL;
    ERESULT         eRc;
    TOKEN_DATA      *pToken;
    ASTR_DATA       *pStr;
    int32_t         cls;
    TOKEN_DATA      *pWork = OBJ_NIL;
    SRCLOC          src = {1,2,3,4};

    fprintf(stderr, "Performing: %s\n", pTestName);
    pObj = Lex_New( );
    XCTAssertFalse( (OBJ_NIL == pObj) );
    if (pObj) {

        pWork = Token_NewStrA(&src, 510, "@interface");
        XCTAssertFalse( (OBJ_NIL == pWork) );

        eRc = Lex_ParseTokenSetup(pObj, pWork);
        XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
        obj_Release(pWork);
        pWork = OBJ_NIL;

        eRc = Lex_ParseTokenFinalize(pObj, 512, true);
        XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
        pToken = Lex_getToken(pObj);
        pStr = Token_getTextAStr(pToken);
        XCTAssertFalse( (OBJ_NIL == pObj) );
        if (pStr) {
            fprintf(stderr, "\toutput = \"%s\"\n", AStr_getData(pStr));
            eRc = AStr_CompareA(pStr, "@interface");
            XCTAssertTrue( (ERESULT_SUCCESS_EQUAL == eRc) );
        }
        obj_Release(pStr);
        cls = Token_getClass(pToken);
        fprintf(stderr, "\tclass = %d\n", cls);
        XCTAssertTrue( (512 == cls) );


        pWork = Token_NewStrA(&src, 510, "@end");

        eRc = Lex_ParseTokenSetup(pObj, pWork);
        XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
        obj_Release(pWork);
        pWork = OBJ_NIL;

        eRc = Lex_ParseTokenFinalize(pObj, 512, true);
        XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
        pToken = Lex_getToken(pObj);
        pStr = Token_getTextAStr(pToken);
        XCTAssertFalse( (OBJ_NIL == pObj) );
        if (pStr) {
            fprintf(stderr, "\toutput = \"%s\"\n", AStr_getData(pStr));
            eRc = AStr_CompareA(pStr, "@end");
            XCTAssertTrue( (ERESULT_SUCCESS_EQUAL == eRc) );
        }
        obj_Release(pStr);
        cls = Token_getClass(pToken);
        fprintf(stderr, "\tclass = %d\n", cls);
        XCTAssertTrue( (512 == cls) );

        obj_Release(pObj);
        pObj = OBJ_NIL;
    }

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
                while (Lex_ParseChrCon(pLex, '\"'))
                    ;
                pToken = Lex_InputLookAhead(pLex, 1);
                ch = Token_getChrW32(pToken);
                XCTAssertTrue( (ch == '"') );
                Lex_ParseTokenAppendString(pLex, pToken);
                {
                    ASTR_DATA       *pWrk2 = W32Str_ToChrCon(pLex->pStr);
                    fprintf(stderr, "\tDATA=\"%s\"\n", AStr_getData(pWrk2));
                    obj_Release(pWrk2);
                }
                eRc = W32Str_CompareA(pLex->pStr, "\"\\x01\\x02\"");
                XCTAssertTrue( (ERESULT_SUCCESS_EQUAL == eRc) );

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
    ASTR_DATA       *pInput = OBJ_NIL;
    LEX_DATA        *pLex = OBJ_NIL;
    TOKEN_DATA      *pToken;
    bool            fRc;
    PATH_DATA       *pPath = Path_NewA("abc");

    fprintf(stderr, "Performing: %s\n", pTestName);
    pInput = AStr_NewA("class xyzzy {\n\tint\ta;\n\tchar\t*pA;\n};\n");
    XCTAssertFalse( (OBJ_NIL == pInput) );
    if (pInput) {

        pSrc = SrcFile_NewFromAStr(pPath, pInput, 1, 4);
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

                // 1st Line - "class xyzzy {\n"
                pToken = Lex_TokenLookAhead(pLex, 1);
                XCTAssertFalse( (OBJ_NIL == pToken) );
                XCTAssertTrue( (Token_Validate(pToken)) );
                {
                    ASTR_DATA       *pStr = Token_ToDebugString(pToken, 0);
                    fprintf(stderr, "token=\"%s\"\n",  AStr_getData(pStr));
                    obj_Release(pStr);
                    pStr = OBJ_NIL;
                }
                XCTAssertTrue( (LEX_IDENTIFIER == Token_getClass(pToken)) );
                {
                    ASTR_DATA *pWrk = Token_ToDataString(pToken);
                    XCTAssertTrue( (ERESULT_SUCCESS_EQUAL == AStr_CompareA(pWrk, "class")) );
                    obj_Release(pWrk);
                    pWrk = OBJ_NIL;
                }
                pToken = Lex_TokenAdvance(pLex, 1);
                XCTAssertFalse( (OBJ_NIL == pToken) );

                pToken = Lex_TokenLookAhead(pLex, 1);
                XCTAssertFalse( (OBJ_NIL == pToken) );
                XCTAssertTrue( (Token_Validate(pToken)) );
                {
                    ASTR_DATA       *pStr = Token_ToDebugString(pToken, 0);
                    fprintf(stderr, "token=\"%s\"\n",  AStr_getData(pStr));
                    obj_Release(pStr);
                    pStr = OBJ_NIL;
                }
                XCTAssertTrue( (LEX_IDENTIFIER == Token_getClass(pToken)) );
                {
                    ASTR_DATA *pWrk = Token_ToDataString(pToken);
                    XCTAssertTrue( (ERESULT_SUCCESS_EQUAL == AStr_CompareA(pWrk, "xyzzy")) );
                    obj_Release(pWrk);
                    pWrk = OBJ_NIL;
                }
                pToken = Lex_TokenAdvance(pLex, 1);
                XCTAssertFalse( (OBJ_NIL == pToken) );

                obj_Release(pLex);
                pLex = OBJ_NIL;
            }

            obj_Release(pSrc);
            pSrc = OBJ_NIL;
        }

        obj_Release(pInput);
        pInput = OBJ_NIL;
    }

    obj_Release(pPath);
    pPath = OBJ_NIL;

    fprintf(stderr, "...%s completed.\n\n\n", pTestName);
    return 1;
}



int         test_Lex_Input02(
    const
    char        *pTestName
)
{
    SRCFILE_DATA    *pSrc = OBJ_NIL;
    ASTR_DATA       *pInput = OBJ_NIL;
    LEX_DATA        *pLex = OBJ_NIL;
    TOKEN_DATA      *pToken;
    bool            fRc;
    PATH_DATA       *pPath = Path_NewA("abc");

    fprintf(stderr, "Performing: %s\n", pTestName);
    pInput = AStr_NewA("a += b + c * d / e;\n");
    XCTAssertFalse( (OBJ_NIL == pInput) );
    if (pInput) {

        pSrc = SrcFile_NewFromAStr(pPath, pInput, 1, 4);
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

                pToken = Lex_TokenLookAhead(pLex, 1);
                XCTAssertFalse( (OBJ_NIL == pToken) );
                XCTAssertTrue( (Token_Validate(pToken)) );
                {
                    ASTR_DATA       *pStr = Token_ToDebugString(pToken, 0);
                    fprintf(stderr, "token=\"%s\"\n",  AStr_getData(pStr));
                    obj_Release(pStr);
                    pStr = OBJ_NIL;
                }
                XCTAssertTrue( (LEX_IDENTIFIER == Token_getClass(pToken)) );
                {
                    ASTR_DATA *pWrk = Token_ToDataString(pToken);
                    XCTAssertTrue( (ERESULT_SUCCESS_EQUAL == AStr_CompareA(pWrk, "a")) );
                    obj_Release(pWrk);
                    pWrk = OBJ_NIL;
                }
                pToken = Lex_TokenAdvance(pLex, 1);
                XCTAssertFalse( (OBJ_NIL == pToken) );

                pToken = Lex_TokenLookAhead(pLex, 1);
                XCTAssertFalse( (OBJ_NIL == pToken) );
                XCTAssertTrue( (Token_Validate(pToken)) );
                {
                    ASTR_DATA       *pStr = Token_ToDebugString(pToken, 0);
                    fprintf(stderr, "token=\"%s\"\n",  AStr_getData(pStr));
                    obj_Release(pStr);
                    pStr = OBJ_NIL;
                }
                XCTAssertTrue( (LEX_OP_ASSIGN_ADD == Token_getClass(pToken)) );
                {
                    ASTR_DATA *pWrk = Token_ToDataString(pToken);
                    XCTAssertTrue( (ERESULT_SUCCESS_EQUAL == AStr_CompareA(pWrk, "+=")) );
                    obj_Release(pWrk);
                    pWrk = OBJ_NIL;
                }
                pToken = Lex_TokenAdvance(pLex, 1);
                XCTAssertFalse( (OBJ_NIL == pToken) );

                pToken = Lex_TokenLookAhead(pLex, 1);
                XCTAssertFalse( (OBJ_NIL == pToken) );
                XCTAssertTrue( (Token_Validate(pToken)) );
                {
                    ASTR_DATA       *pStr = Token_ToDebugString(pToken, 0);
                    fprintf(stderr, "token=\"%s\"\n",  AStr_getData(pStr));
                    obj_Release(pStr);
                    pStr = OBJ_NIL;
                }
                XCTAssertTrue( (LEX_IDENTIFIER == Token_getClass(pToken)) );
                {
                    ASTR_DATA *pWrk = Token_ToDataString(pToken);
                    XCTAssertTrue( (ERESULT_SUCCESS_EQUAL == AStr_CompareA(pWrk, "b")) );
                    obj_Release(pWrk);
                    pWrk = OBJ_NIL;
                }
                pToken = Lex_TokenAdvance(pLex, 1);
                XCTAssertFalse( (OBJ_NIL == pToken) );

                pToken = Lex_TokenLookAhead(pLex, 1);
                XCTAssertFalse( (OBJ_NIL == pToken) );
                XCTAssertTrue( (Token_Validate(pToken)) );
                {
                    ASTR_DATA       *pStr = Token_ToDebugString(pToken, 0);
                    fprintf(stderr, "token=\"%s\"\n",  AStr_getData(pStr));
                    obj_Release(pStr);
                    pStr = OBJ_NIL;
                }
                XCTAssertTrue( (LEX_OP_ADD == Token_getClass(pToken)) );
                {
                    ASTR_DATA *pWrk = Token_ToDataString(pToken);
                    XCTAssertTrue( (ERESULT_SUCCESS_EQUAL == AStr_CompareA(pWrk, "+")) );
                    obj_Release(pWrk);
                    pWrk = OBJ_NIL;
                }
                pToken = Lex_TokenAdvance(pLex, 1);
                XCTAssertFalse( (OBJ_NIL == pToken) );

                obj_Release(pLex);
                pLex = OBJ_NIL;
            }

            obj_Release(pSrc);
            pSrc = OBJ_NIL;
        }

        obj_Release(pInput);
        pInput = OBJ_NIL;
    }

    obj_Release(pPath);
    pPath = OBJ_NIL;

    fprintf(stderr, "...%s completed.\n\n\n", pTestName);
    return 1;
}




TINYTEST_START_SUITE(test_Lex);
    TINYTEST_ADD_TEST(test_Lex_Input02,setUp,tearDown);
    TINYTEST_ADD_TEST(test_Lex_Input01,setUp,tearDown);
    TINYTEST_ADD_TEST(test_Lex_Strings04,setUp,tearDown);
    TINYTEST_ADD_TEST(test_Lex_Strings03,setUp,tearDown);
    TINYTEST_ADD_TEST(test_Lex_Strings02,setUp,tearDown);
    TINYTEST_ADD_TEST(test_Lex_Strings01,setUp,tearDown);
    TINYTEST_ADD_TEST(test_Lex_Number04,setUp,tearDown);
    TINYTEST_ADD_TEST(test_Lex_Number03,setUp,tearDown);
    TINYTEST_ADD_TEST(test_Lex_Number02,setUp,tearDown);
    TINYTEST_ADD_TEST(test_Lex_Number01,setUp,tearDown);
    TINYTEST_ADD_TEST(test_Lex_Test01,setUp,tearDown);
    //TINYTEST_ADD_TEST(test_Lex_Copy01,setUp,tearDown);
    TINYTEST_ADD_TEST(test_Lex_OpenClose,setUp,tearDown);
TINYTEST_END_SUITE();

TINYTEST_MAIN_SINGLE_SUITE(test_Lex);





