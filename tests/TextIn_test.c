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
#include    <cmn_defs.h>
#include    <trace.h>
#include    <TextIn_internal.h>
#ifdef  TEXTIN_JSON_SUPPORT
#   include    <SrcErrors.h>
#endif
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

        //obj_TraceSet(pObj, true);       
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
    W32CHR_T        chr = 0;
    //ERESULT         eRc;

    fprintf(stderr, "Performing: %s\n", pTestName);

    pStr = AStr_NewA("abc\n");
    TINYTEST_FALSE( (OBJ_NIL == pStr) );
    pObj = TextIn_NewFromAStr(OBJ_NIL, pStr, 1, 4);
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    if (pObj) {

        chr = TextIn_NextChar(pObj);
        TINYTEST_TRUE( (chr == 'a') );

        chr = TextIn_NextChar(pObj);
        TINYTEST_TRUE( (chr == 'b') );

        chr = TextIn_NextChar(pObj);
        TINYTEST_TRUE( (chr == 'c') );

        chr = TextIn_NextChar(pObj);
        TINYTEST_TRUE( (chr == '\n') );

        chr = TextIn_NextChar(pObj);
        TINYTEST_TRUE( (chr == EOF) );

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
    W32CHR_T        chr = 0;
    //ERESULT         eRc;

    fprintf(stderr, "Performing: %s\n", pTestName);

    pStr = AStr_NewA("abc\tdef\n");
    TINYTEST_FALSE( (OBJ_NIL == pStr) );
    pObj = TextIn_NewFromAStr(OBJ_NIL, pStr, 1, 4);
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    if (pObj) {

        chr = TextIn_NextChar(pObj);
        TINYTEST_TRUE( (chr == 'a') );

        chr = TextIn_NextChar(pObj);
        TINYTEST_TRUE( (chr == 'b') );

        chr = TextIn_NextChar(pObj);
        TINYTEST_TRUE( (chr == 'c') );

        chr = TextIn_NextChar(pObj);
        TINYTEST_TRUE( (chr == ' ') );

        chr = TextIn_NextChar(pObj);
        TINYTEST_TRUE( (chr == 'd') );

        chr = TextIn_NextChar(pObj);
        TINYTEST_TRUE( (chr == 'e') );

        chr = TextIn_NextChar(pObj);
        TINYTEST_TRUE( (chr == 'f') );

        chr = TextIn_NextChar(pObj);
        TINYTEST_TRUE( (chr == '\n') );

        chr = TextIn_NextChar(pObj);
        TINYTEST_TRUE( (chr == EOF) );

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

        eRc = TextIn_GetLineA(pObj, buffer, 128, &loc);
        TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );
        TINYTEST_TRUE( (0 == strcmp(buffer, "abc")) );

        eRc = TextIn_GetLineA(pObj, buffer, 128, &loc);
        TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );
        TINYTEST_TRUE( (buffer[0] == '\0') );

        eRc = TextIn_GetLineA(pObj, buffer, 128, &loc);
        TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );
        TINYTEST_TRUE( (0 == strcmp(buffer, "def")) );

        eRc = TextIn_GetLineA(pObj, buffer, 128, &loc);
        TINYTEST_FALSE( (eRc == ERESULT_EOF_ERROR) );

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
    char            *pFilePathA = "~/git/libCmn/tests/files/test_hjson_01.txt";
    PATH_DATA       *pFilePath = OBJ_NIL;

    fprintf(stderr, "Performing: %s\n", pTestName);

    pFilePath = path_NewA(pFilePathA);
    TINYTEST_FALSE( (OBJ_NIL == pFilePath) );
    path_Clean(pFilePath);
    eRc = path_IsFile(pFilePath);
    TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );
    pObj = TextIn_NewFromPath(pFilePath, 0, 4);
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    if (pObj) {

        eRc = TextIn_GetLineA(pObj, buffer, 128, &loc);
        TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );
        TINYTEST_TRUE( (0 == strcmp(buffer, "{")) );

        eRc = TextIn_GetLineA(pObj, buffer, 128, &loc);
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

    pStr = AStr_NewA("abc\n\ndef\n");
    TINYTEST_FALSE( (OBJ_NIL == pStr) );
    pObj = TextIn_NewFromAStr(OBJ_NIL, pStr, 1, 4);
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    if (pObj) {

        TextIn_setUpperLimit(pObj, 2);

        eRc = TextIn_GetLineA(pObj, buffer, 128, &loc);
        TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );
        TINYTEST_TRUE( (0 == strcmp(buffer, "ab")) );

        eRc = TextIn_GetLineA(pObj, buffer, 128, &loc);
        TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );
        TINYTEST_TRUE( (buffer[0] == '\0') );

        eRc = TextIn_GetLineA(pObj, buffer, 128, &loc);
        TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );
        TINYTEST_TRUE( (0 == strcmp(buffer, "de")) );

        eRc = TextIn_GetLineA(pObj, buffer, 128, &loc);
        TINYTEST_FALSE( (eRc == ERESULT_EOF_ERROR) );

        obj_Release(pObj);
        pObj = OBJ_NIL;
    }

    obj_Release(pStr);
    pStr = OBJ_NIL;

    fprintf(stderr, "...%s completed.\n\n", pTestName);
    return 1;
}




TINYTEST_START_SUITE(test_TextIn);
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





