// vi:nu:et:sts=4 ts=4 sw=4
/*
 *	Generated 01/21/2020 22:03:13
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
#include    <test_defs.h>
#include    <trace.h>
#include    <TextIn_internal.h>
#ifdef  TEXTIN_JSON_SUPPORT
#   include    <SrcErrors.h>
#endif
#include    <JsonIn.h>
#include    <szTbl.h>



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

#ifdef  TEXTIN_JSON_SUPPORT
    SrcErrors_SharedReset( );
#endif
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






int             test_TextIn_OpenClose (
    const
    char            *pTestName
)
{
    ERESULT         eRc = ERESULT_SUCCESS;
    TEXTIN_DATA	    *pObj = OBJ_NIL;
    bool            fRc;
   
    fprintf(stderr, "Performing: %s\n", pTestName);

    pObj = TextIn_Alloc( );
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    pObj = TextIn_Init( pObj );
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    if (pObj) {

        obj_TraceSet(pObj, true);
        fRc = obj_IsKindOf(pObj, OBJ_IDENT_TEXTIN);
        TINYTEST_TRUE( (fRc) );
        
        // Test something.
        TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );

        obj_Release(pObj);
        pObj = OBJ_NIL;
    }

    fprintf(stderr, "...%s completed.\n\n\n", pTestName);
    return 1;
}



int             test_TextIn_Copy01 (
    const
    char            *pTestName
)
{
    ERESULT         eRc = ERESULT_SUCCESS;
    TEXTIN_DATA	    *pObj1 = OBJ_NIL;
    TEXTIN_DATA	    *pObj2 = OBJ_NIL;
    bool            fRc;
#if defined(TEXTIN_JSON_SUPPORT) && defined(XYZZY)
    ASTR_DATA	    *pStr = OBJ_NIL;
#endif
   
    fprintf(stderr, "Performing: %s\n", pTestName);

    pObj1 = TextIn_New( );
    TINYTEST_FALSE( (OBJ_NIL == pObj1) );
    if (pObj1) {

        //obj_TraceSet(pObj1, true);       
        fRc = obj_IsKindOf(pObj1, OBJ_IDENT_TEXTIN);
        TINYTEST_TRUE( (fRc) );
        
        // Test assign.
        pObj2 = TextIn_New();
        TINYTEST_FALSE( (OBJ_NIL == pObj2) );
        eRc = TextIn_Assign(pObj1, pObj2);
        TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );

        fRc = obj_IsKindOf(pObj2, OBJ_IDENT_TEXTIN);
        TINYTEST_TRUE( (fRc) );
        //TODO: Add More tests here!

        obj_Release(pObj2);
        pObj2 = OBJ_NIL;

        // Test copy.
        pObj2 = TextIn_Copy(pObj1);
        TINYTEST_FALSE( (OBJ_NIL == pObj2) );

        fRc = obj_IsKindOf(pObj2, OBJ_IDENT_TEXTIN);
        TINYTEST_TRUE( (fRc) );
        //TODO: Add More tests here!

        obj_Release(pObj2);
        pObj2 = OBJ_NIL;

        // Test json support.
#if defined(TEXTIN_JSON_SUPPORT) && defined(XYZZY)
        pStr = TextIn_ToJson(pObj);
        TINYTEST_FALSE( (OBJ_NIL == pStr) );
        fprintf(stderr, "JSON: %s\n", AStr_getData(pStr));
        pObj2 = TextIn_NewFromJsonString(pStr);
        TINYTEST_FALSE( (OBJ_NIL == pObj2) );
        fRc = obj_IsKindOf(pObj2, OBJ_IDENT_TEXTIN);
        TINYTEST_TRUE( (fRc) );
        obj_Release(pStr);
        pStr = OBJ_NIL;

        obj_Release(pObj2);
        pObj2 = OBJ_NIL;
#endif

        obj_Release(pObj1);
        pObj1 = OBJ_NIL;
    }

    fprintf(stderr, "...%s completed.\n\n\n", pTestName);
    return 1;
}



int             test_TextIn_Test01 (
    const
    char            *pTestName
)
{
    //ERESULT         eRc = ERESULT_SUCCESS;
    TEXTIN_DATA	    *pObj = OBJ_NIL;
    bool            fRc;
   
    fprintf(stderr, "Performing: %s\n", pTestName);

    pObj = TextIn_New( );
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    if (pObj) {

        //obj_TraceSet(pObj, true);       
        fRc = obj_IsKindOf(pObj, OBJ_IDENT_TEXTIN);
        TINYTEST_TRUE( (fRc) );
        
        obj_Release(pObj);
        pObj = OBJ_NIL;
    }

    fprintf(stderr, "...%s completed.\n\n\n", pTestName);
    return 1;
}



int             test_TextIn_Input01(
    const
    char            *pTestName
)
{
    TEXTIN_DATA     *pObj = OBJ_NIL;
    ASTR_DATA       *pStr = OBJ_NIL;
    TOKEN_FIELDS    *pTok = NULL;
    //ERESULT         eRc;

    fprintf(stderr, "Performing: %s\n", pTestName);

    pStr = AStr_NewA("abc\n");
    TINYTEST_FALSE( (OBJ_NIL == pStr) );
    pObj = TextIn_NewFromAStr(OBJ_NIL, pStr, 1, 4);
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    if (pObj) {

        obj_TraceSet(pObj, true);

        pTok = TextIn_NextToken(pObj);
        TINYTEST_FALSE( (NULL == pTok) );
        TINYTEST_TRUE( (pTok->w32chr[0] == 'a') );

        pTok = TextIn_NextToken(pObj);
        TINYTEST_FALSE( (NULL == pTok) );
        TINYTEST_TRUE( (pTok->w32chr[0] == 'b') );

        pTok = TextIn_NextToken(pObj);
        TINYTEST_FALSE( (NULL == pTok) );
        TINYTEST_TRUE( (pTok->w32chr[0] == 'c') );

        pTok = TextIn_NextToken(pObj);
        TINYTEST_FALSE( (NULL == pTok) );
        TINYTEST_TRUE( (pTok->w32chr[0] == '\n') );

        pTok = TextIn_NextToken(pObj);
        TINYTEST_FALSE( (NULL == pTok) );
        TINYTEST_TRUE( (pTok->w32chr[0] == EOF) );

        obj_Release(pObj);
        pObj = OBJ_NIL;
    }

    obj_Release(pStr);
    pStr = OBJ_NIL;

    fprintf(stderr, "...%s completed.\n\n", pTestName);
    return 1;
}



int             test_TextIn_Input02(
    const
    char            *pTestName
)
{
    TEXTIN_DATA     *pObj = OBJ_NIL;
    ASTR_DATA       *pStr = OBJ_NIL;
    TOKEN_FIELDS    *pTok = NULL;
    //ERESULT         eRc;

    fprintf(stderr, "Performing: %s\n", pTestName);

    pStr = AStr_NewA("abc\tdef\n");
    TINYTEST_FALSE( (OBJ_NIL == pStr) );
    pObj = TextIn_NewFromAStr(OBJ_NIL, pStr, 1, 4);
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    if (pObj) {

        obj_TraceSet(pObj, true);

        pTok = TextIn_NextToken(pObj);
        TINYTEST_FALSE( (NULL == pTok) );
        TINYTEST_TRUE( (pTok->w32chr[0] == 'a') );

        pTok = TextIn_NextToken(pObj);
        TINYTEST_FALSE( (NULL == pTok) );
        TINYTEST_TRUE( (pTok->w32chr[0] == 'b') );

        pTok = TextIn_NextToken(pObj);
        TINYTEST_FALSE( (NULL == pTok) );
        TINYTEST_TRUE( (pTok->w32chr[0] == 'c') );

        pTok = TextIn_NextToken(pObj);
        TINYTEST_FALSE( (NULL == pTok) );
        TINYTEST_TRUE( (pTok->w32chr[0] == ' ') );

        pTok = TextIn_NextToken(pObj);
        TINYTEST_FALSE( (NULL == pTok) );
        TINYTEST_TRUE( (pTok->w32chr[0] == 'd') );

        pTok = TextIn_NextToken(pObj);
        TINYTEST_FALSE( (NULL == pTok) );
        TINYTEST_TRUE( (pTok->w32chr[0] == 'e') );

        pTok = TextIn_NextToken(pObj);
        TINYTEST_FALSE( (NULL == pTok) );
        TINYTEST_TRUE( (pTok->w32chr[0] == 'f') );

        pTok = TextIn_NextToken(pObj);
        TINYTEST_FALSE( (NULL == pTok) );
        TINYTEST_TRUE( (pTok->w32chr[0] == '\n') );

        pTok = TextIn_NextToken(pObj);
        TINYTEST_FALSE( (NULL == pTok) );
        TINYTEST_TRUE( (pTok->w32chr[0] == EOF) );

        obj_Release(pObj);
        pObj = OBJ_NIL;
    }

    obj_Release(pStr);
    pStr = OBJ_NIL;

    fprintf(stderr, "...%s completed.\n\n", pTestName);
    return 1;
}



int             test_TextIn_GetLine01(
    const
    char            *pTestName
)
{
    TEXTIN_DATA     *pObj = OBJ_NIL;
    ASTR_DATA       *pStr = OBJ_NIL;
    ERESULT         eRc;
    char            buffer[128];
    SRCLOC          loc = {0};

    fprintf(stderr, "Performing: %s\n", pTestName);

    pStr = AStr_NewA("abc\n\ndef\n");
    TINYTEST_FALSE( (OBJ_NIL == pStr) );
    pObj = TextIn_NewFromAStr(OBJ_NIL, pStr, 1, 4);
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    if (pObj) {

        obj_TraceSet(pObj, true);

        eRc = TextIn_GetLineA(pObj, sizeof(buffer), buffer, &loc);
        TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );
        TINYTEST_TRUE( (0 == strcmp(buffer, "abc")) );
        TINYTEST_TRUE( (1 == loc.lineNo) );
        TINYTEST_TRUE( (1 == loc.colNo) );
        TINYTEST_TRUE( (0 == loc.offset) );

        eRc = TextIn_GetLineA(pObj, sizeof(buffer), buffer, &loc);
        TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );
        TINYTEST_TRUE( (buffer[0] == '\0') );
        TINYTEST_TRUE( (2 == loc.lineNo) );
        TINYTEST_TRUE( (0 == loc.colNo) );
        TINYTEST_TRUE( (4 == loc.offset) );

        eRc = TextIn_GetLineA(pObj, sizeof(buffer), buffer, &loc);
        TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );
        TINYTEST_TRUE( (0 == strcmp(buffer, "def")) );
        TINYTEST_TRUE( (3 == loc.lineNo) );
        TINYTEST_TRUE( (1 == loc.colNo) );
        TINYTEST_TRUE( (5 == loc.offset) );

        eRc = TextIn_GetLineA(pObj, sizeof(buffer), buffer, &loc);
        TINYTEST_TRUE( (eRc == ERESULT_EOF_ERROR) );

        obj_Release(pObj);
        pObj = OBJ_NIL;
    }

    obj_Release(pStr);
    pStr = OBJ_NIL;

    fprintf(stderr, "...%s completed.\n\n", pTestName);
    return 1;
}



int             test_TextIn_GetLine02(
    const
    char            *pTestName
)
{
    TEXTIN_DATA     *pObj = OBJ_NIL;
    //ASTR_DATA       *pStr = OBJ_NIL;
    ERESULT         eRc;
    char            buffer[128];
    SRCLOC          loc = {0};
    const
    char            *pFilePathA = TEST_FILES_DIR "/test_hjson_01.txt";
    PATH_DATA       *pFilePath = OBJ_NIL;

    fprintf(stderr, "Performing: %s\n", pTestName);

    pFilePath = Path_NewA(pFilePathA);
    TINYTEST_FALSE( (OBJ_NIL == pFilePath) );
    Path_Clean(pFilePath);
    eRc = Path_IsFile(pFilePath);
    TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );
    pObj = TextIn_NewFromPath(pFilePath, 0, 4);
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    if (pObj) {

        obj_TraceSet(pObj, true);

        eRc = TextIn_GetLineA(pObj, sizeof(buffer), buffer, &loc);
        TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );
        TINYTEST_TRUE( (0 == strcmp(buffer, "{")) );

        eRc = TextIn_GetLineA(pObj, sizeof(buffer), buffer, &loc);
        TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );
        TINYTEST_TRUE( (0 == strcmp(buffer, "    \"one\": {")) );

        obj_Release(pObj);
        pObj = OBJ_NIL;
    }

    obj_Release(pFilePath);
    pFilePath = OBJ_NIL;

    fprintf(stderr, "...%s completed.\n\n", pTestName);
    return 1;
}



int             test_TextIn_GetLine03(
    const
    char            *pTestName
)
{
    TEXTIN_DATA     *pObj = OBJ_NIL;
    ASTR_DATA       *pStr = OBJ_NIL;
    ERESULT         eRc;
    char            buffer[128];
    SRCLOC          loc = {0};

    fprintf(stderr, "Performing: %s\n", pTestName);

    pStr = AStr_NewA("abc\r\n\r\ndef\r\n");
    TINYTEST_FALSE( (OBJ_NIL == pStr) );
    pObj = TextIn_NewFromAStr(OBJ_NIL, pStr, 1, 4);
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    if (pObj) {

        TextIn_setUpperLimit(pObj, 2);

        obj_TraceSet(pObj, true);

        eRc = TextIn_GetLineA(pObj, sizeof(buffer), buffer, &loc);
        TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );
        TINYTEST_TRUE( (0 == strcmp(buffer, "ab")) );

        eRc = TextIn_GetLineA(pObj, sizeof(buffer), buffer, &loc);
        TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );
        TINYTEST_TRUE( (buffer[0] == '\0') );

        eRc = TextIn_GetLineA(pObj, sizeof(buffer), buffer, &loc);
        TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );
        TINYTEST_TRUE( (0 == strcmp(buffer, "de")) );

        eRc = TextIn_GetLineA(pObj, sizeof(buffer), buffer, &loc);
        TINYTEST_TRUE( (eRc == ERESULT_EOF_ERROR) );

        obj_Release(pObj);
        pObj = OBJ_NIL;
    }

    obj_Release(pStr);
    pStr = OBJ_NIL;

    fprintf(stderr, "...%s completed.\n\n", pTestName);
    return 1;
}



int             test_TextIn_GetLine04(
    const
    char            *pTestName
)
{
    TEXTIN_DATA     *pObj = OBJ_NIL;
    ASTR_DATA       *pStr = OBJ_NIL;
    ASTR_DATA       *pLine = OBJ_NIL;
    ERESULT         eRc;
    SRCLOC          loc = {0};

    fprintf(stderr, "Performing: %s\n", pTestName);

    pStr = AStr_NewA("abc\n\ndef\n");
    TINYTEST_FALSE( (OBJ_NIL == pStr) );
    pObj = TextIn_NewFromAStr(OBJ_NIL, pStr, 1, 4);
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    if (pObj) {

        obj_TraceSet(pObj, true);

        eRc = TextIn_GetLineAStr(pObj, &pLine, &loc);
        TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );
        TINYTEST_FALSE( (OBJ_NIL == pLine) );
        TINYTEST_TRUE( (0 == AStr_CompareA(pLine, "abc")) );
        obj_Release(pLine);
        pLine = OBJ_NIL;

        eRc = TextIn_GetLineAStr(pObj, &pLine, &loc);
        TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );
        TINYTEST_FALSE( (OBJ_NIL == pLine) );
        TINYTEST_TRUE( (0 == AStr_getSize(pLine)) );
        obj_Release(pLine);
        pLine = OBJ_NIL;

        eRc = TextIn_GetLineAStr(pObj, &pLine, &loc);
        TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );
        TINYTEST_FALSE( (OBJ_NIL == pLine) );
        TINYTEST_TRUE( (0 == AStr_CompareA(pLine, "def")) );
        obj_Release(pLine);
        pLine = OBJ_NIL;

        eRc = TextIn_GetLineAStr(pObj, &pLine, &loc);
        TINYTEST_TRUE( (ERESULT_EOF_ERROR == eRc) );
        TINYTEST_TRUE( (OBJ_NIL == pLine) );

        obj_Release(pObj);
        pObj = OBJ_NIL;
    }

    obj_Release(pStr);
    pStr = OBJ_NIL;

    fprintf(stderr, "...%s completed.\n\n", pTestName);
    return 1;
}



int             test_TextIn_GetLine05(
    const
    char            *pTestName
)
{
    TEXTIN_DATA     *pObj = OBJ_NIL;
    ASTR_DATA       *pStr = OBJ_NIL;
    ASTR_DATA       *pLine = OBJ_NIL;
    ERESULT         eRc;
    SRCLOC          loc = {0};
    const
    char            *pFileA =
                    TEST_FILES_DIR "/object01.json.txt";
    PATH_DATA       *pPath = OBJ_NIL;
    uint32_t        cnt = 0;

    fprintf(stderr, "Performing: %s\n", pTestName);

    pPath = Path_NewA(pFileA);
    TINYTEST_FALSE( (OBJ_NIL == pPath) );
    pObj = TextIn_NewFromPath(pPath, 1, 4);
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    if (pObj) {

        obj_TraceSet(pObj, true);

        for (;;) {
            eRc = TextIn_GetLineAStr(pObj, &pLine, &loc);
            if (ERESULT_FAILED(eRc)) {
                break;
            }
            TINYTEST_FALSE( (OBJ_NIL == pLine) );
            //TINYTEST_TRUE( (0 == AStr_CompareA(pLine, "abc")) );
            cnt++;
            obj_Release(pLine);
            pLine = OBJ_NIL;
        }
        TINYTEST_TRUE( (ERESULT_EOF_ERROR == eRc) );
        TINYTEST_TRUE( (OBJ_NIL == pLine) );
        fprintf(stderr, "\tRead %d lines.\n", cnt);
        TINYTEST_TRUE( (15 == cnt) );

        obj_Release(pObj);
        pObj = OBJ_NIL;
    }

    obj_Release(pStr);
    pStr = OBJ_NIL;
    obj_Release(pPath);
    pPath = OBJ_NIL;

    fprintf(stderr, "...%s completed.\n\n", pTestName);
    return 1;
}



int             test_TextIn_GetLine06(
    const
    char            *pTestName
)
{
    TEXTIN_DATA     *pObj = OBJ_NIL;
    ASTR_DATA       *pStr = OBJ_NIL;
    ASTR_DATA       *pLine = OBJ_NIL;
    ERESULT         eRc;
    SRCLOC          loc = {0};
    const
    char            *pFileA = TEST_FILES_DIR "/model.obj._internal.h.txt";
    PATH_DATA       *pPath = OBJ_NIL;
    uint32_t        cnt = 0;

    fprintf(stderr, "Performing: %s\n", pTestName);

    pPath = Path_NewA(pFileA);
    TINYTEST_FALSE( (OBJ_NIL == pPath) );
    pObj = TextIn_NewFromPath(pPath, 1, 4);
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    if (pObj) {

        obj_TraceSet(pObj, true);

        for (;;) {
            eRc = TextIn_GetLineAStr(pObj, &pLine, &loc);
            if (ERESULT_FAILED(eRc)) {
                break;
            }
            TINYTEST_FALSE( (OBJ_NIL == pLine) );
            //TINYTEST_TRUE( (0 == AStr_CompareA(pLine, "abc")) );
            cnt++;
            obj_Release(pLine);
            pLine = OBJ_NIL;
        }
        TINYTEST_TRUE( (ERESULT_EOF_ERROR == eRc) );
        TINYTEST_TRUE( (OBJ_NIL == pLine) );
        fprintf(stderr, "\tRead %d lines.\n", cnt);
        TINYTEST_TRUE( (214 == cnt) );
        {
            ASTR_DATA       *pStr = OBJ_NIL;
            pStr = TextIn_ToDebugString(pObj, 4);
            if (pStr) {
                fprintf(stderr, "%s\n", AStr_getData(pStr));
                obj_Release(pStr);
            }
        }

        eRc = TextIn_SeekOffset(pObj, 5380);
        TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );
        TINYTEST_TRUE( (5380 == pObj->curTok.src.offset) );
        TINYTEST_TRUE( (211 == pObj->curTok.src.lineNo) );
        TINYTEST_TRUE( (0 == pObj->curTok.src.colNo) );

        obj_Release(pObj);
        pObj = OBJ_NIL;
    }

    obj_Release(pStr);
    pStr = OBJ_NIL;
    obj_Release(pPath);
    pPath = OBJ_NIL;

    fprintf(stderr, "...%s completed.\n\n", pTestName);
    return 1;
}



int             test_TextIn_GetLine07(
    const
    char            *pTestName
)
{
    TEXTIN_DATA     *pObj = OBJ_NIL;
    //ASTR_DATA       *pStr = OBJ_NIL;
    ASTR_DATA       *pLine = OBJ_NIL;
    ERESULT         eRc;
    SRCLOC          loc = {0};
    const
    char            *pStrA = "abc\n\ndef\n";

    fprintf(stderr, "Performing: %s\n", pTestName);

    pObj = TextIn_NewFromStrA(OBJ_NIL, pStrA, 1, 4);
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    if (pObj) {

        obj_TraceSet(pObj, true);

        eRc = TextIn_GetLineAStr(pObj, &pLine, &loc);
        TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );
        TINYTEST_FALSE( (OBJ_NIL == pLine) );
        TINYTEST_TRUE( (0 == AStr_CompareA(pLine, "abc")) );
        obj_Release(pLine);
        pLine = OBJ_NIL;

        eRc = TextIn_GetLineAStr(pObj, &pLine, &loc);
        TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );
        TINYTEST_FALSE( (OBJ_NIL == pLine) );
        TINYTEST_TRUE( (0 == AStr_getSize(pLine)) );
        obj_Release(pLine);
        pLine = OBJ_NIL;

        eRc = TextIn_GetLineAStr(pObj, &pLine, &loc);
        TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );
        TINYTEST_FALSE( (OBJ_NIL == pLine) );
        TINYTEST_TRUE( (0 == AStr_CompareA(pLine, "def")) );
        obj_Release(pLine);
        pLine = OBJ_NIL;

        eRc = TextIn_GetLineAStr(pObj, &pLine, &loc);
        TINYTEST_TRUE( (ERESULT_EOF_ERROR == eRc) );
        TINYTEST_TRUE( (OBJ_NIL == pLine) );

        obj_Release(pObj);
        pObj = OBJ_NIL;
    }

    fprintf(stderr, "...%s completed.\n\n", pTestName);
    return 1;
}



int             test_TextIn_GetLine08(
    const
    char            *pTestName
)
{
    TEXTIN_DATA     *pObj = OBJ_NIL;
    ASTR_DATA       *pStr = OBJ_NIL;
    W32STR_DATA     *pLine = OBJ_NIL;
    ERESULT         eRc;
    SRCLOC          loc = {0};

    fprintf(stderr, "Performing: %s\n", pTestName);

    pStr = AStr_NewA("abc\n\ndef\n");
    TINYTEST_FALSE( (OBJ_NIL == pStr) );
    pObj = TextIn_NewFromAStr(OBJ_NIL, pStr, 1, 4);
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    if (pObj) {

        obj_TraceSet(pObj, true);

        eRc = TextIn_GetLineW32Str(pObj, &pLine, &loc);
        TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );
        TINYTEST_FALSE( (OBJ_NIL == pLine) );
        TINYTEST_TRUE( (0 == W32Str_CompareA(pLine, "abc")) );
        obj_Release(pLine);
        pLine = OBJ_NIL;

        eRc = TextIn_GetLineW32Str(pObj, &pLine, &loc);
        TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );
        TINYTEST_FALSE( (OBJ_NIL == pLine) );
        TINYTEST_TRUE( (0 == W32Str_getSize(pLine)) );
        obj_Release(pLine);
        pLine = OBJ_NIL;

        eRc = TextIn_GetLineW32Str(pObj, &pLine, &loc);
        TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );
        TINYTEST_FALSE( (OBJ_NIL == pLine) );
        TINYTEST_TRUE( (0 == W32Str_CompareA(pLine, "def")) );
        obj_Release(pLine);
        pLine = OBJ_NIL;

        eRc = TextIn_GetLineW32Str(pObj, &pLine, &loc);
        TINYTEST_TRUE( (ERESULT_EOF_ERROR == eRc) );
        TINYTEST_TRUE( (OBJ_NIL == pLine) );

        obj_Release(pObj);
        pObj = OBJ_NIL;
    }

    obj_Release(pStr);
    pStr = OBJ_NIL;

    fprintf(stderr, "...%s completed.\n\n", pTestName);
    return 1;
}




TINYTEST_START_SUITE(test_TextIn);
    TINYTEST_ADD_TEST(test_TextIn_GetLine08,setUp,tearDown);
    TINYTEST_ADD_TEST(test_TextIn_GetLine07,setUp,tearDown);
    TINYTEST_ADD_TEST(test_TextIn_GetLine06,setUp,tearDown);
    TINYTEST_ADD_TEST(test_TextIn_GetLine05,setUp,tearDown);
    TINYTEST_ADD_TEST(test_TextIn_GetLine04,setUp,tearDown);
    TINYTEST_ADD_TEST(test_TextIn_GetLine03,setUp,tearDown);
    //TINYTEST_ADD_TEST(test_TextIn_GetLine02,setUp,tearDown);
    TINYTEST_ADD_TEST(test_TextIn_GetLine01,setUp,tearDown);
    TINYTEST_ADD_TEST(test_TextIn_Input02,setUp,tearDown);
    TINYTEST_ADD_TEST(test_TextIn_Input01,setUp,tearDown);
    TINYTEST_ADD_TEST(test_TextIn_Test01,setUp,tearDown);
    //TINYTEST_ADD_TEST(test_TextIn_Copy01,setUp,tearDown);
    TINYTEST_ADD_TEST(test_TextIn_OpenClose,setUp,tearDown);
TINYTEST_END_SUITE();

TINYTEST_MAIN_SINGLE_SUITE(test_TextIn);





