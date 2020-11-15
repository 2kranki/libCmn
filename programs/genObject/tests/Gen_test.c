// vi:nu:et:sts=4 ts=4 sw=4
/*
 *	Generated 05/05/2020 09:59:00
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
#include    <Gen_internal.h>
#include    <SrcErrors.h>
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






int             test_Gen_OpenClose (
    const
    char            *pTestName
)
{
    ERESULT         eRc = ERESULT_SUCCESS;
    GEN_DATA	    *pObj = OBJ_NIL;
    bool            fRc;
   
    fprintf(stderr, "Performing: %s\n", pTestName);

    pObj = Gen_Alloc( );
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    pObj = Gen_Init( pObj );
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    if (pObj) {

        //obj_TraceSet(pObj, true);       
        fRc = obj_IsKindOf(pObj, OBJ_IDENT_GEN);
        TINYTEST_TRUE( (fRc) );
        
        // Test something.
        TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );

        obj_Release(pObj);
        pObj = OBJ_NIL;
    }

    fprintf(stderr, "...%s completed.\n\n\n", pTestName);
    return 1;
}



int             test_Gen_Copy01 (
    const
    char            *pTestName
)
{
    ERESULT         eRc = ERESULT_SUCCESS;
    GEN_DATA	    *pObj1 = OBJ_NIL;
    GEN_DATA	    *pObj2 = OBJ_NIL;
    DICT_DATA       *pDict = OBJ_NIL;
    bool            fRc;
#if defined(GEN_JSON_SUPPORT) && defined(XYZZY)
    ASTR_DATA	    *pStr = OBJ_NIL;
#endif
   
    fprintf(stderr, "Performing: %s\n", pTestName);

    pObj1 = Gen_New( );
    TINYTEST_FALSE( (OBJ_NIL == pObj1) );
    if (pObj1) {

        //obj_TraceSet(pObj1, true);       
        fRc = obj_IsKindOf(pObj1, OBJ_IDENT_GEN);
        TINYTEST_TRUE( (fRc) );
        pDict = Dict_New( );
        TINYTEST_FALSE( (OBJ_NIL == pDict) );
        Gen_setDict(pObj1, pDict);

        // Test assign.
        pObj2 = Gen_New();
        TINYTEST_FALSE( (OBJ_NIL == pObj2) );
        eRc = Gen_Assign(pObj1, pObj2);
        TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );

        fRc = obj_IsKindOf(pObj2, OBJ_IDENT_GEN);
        TINYTEST_TRUE( (fRc) );
        Gen_setDict(pObj2, pDict);
        //eRc = Gen_Compare(pObj1, pObj2);
        //TINYTEST_TRUE( (0 == eRc) );
        //TODO: Add More tests here!

        obj_Release(pObj2);
        pObj2 = OBJ_NIL;

        // Test copy.
        pObj2 = Gen_Copy(pObj1);
        TINYTEST_FALSE( (OBJ_NIL == pObj2) );

        fRc = obj_IsKindOf(pObj2, OBJ_IDENT_GEN);
        TINYTEST_TRUE( (fRc) );
        Gen_setDict(pObj2, pDict);
        //eRc = Gen_Compare(pObj1, pObj2);
        //TINYTEST_TRUE( (0 == eRc) );
        //TODO: Add More tests here!

        obj_Release(pObj2);
        pObj2 = OBJ_NIL;

        // Test json support.
#if defined(GEN_JSON_SUPPORT) && defined(XYZZY)
        pStr = Gen_ToJson(pObj1);
        TINYTEST_FALSE( (OBJ_NIL == pStr) );
        fprintf(stderr, "JSON: %s\n", AStr_getData(pStr));
        pObj2 = Gen_NewFromJsonString(pStr);
        TINYTEST_FALSE( (OBJ_NIL == pObj2) );
        fRc = obj_IsKindOf(pObj2, OBJ_IDENT_GEN);
        TINYTEST_TRUE( (fRc) );
        obj_Release(pStr);
        pStr = OBJ_NIL;
        Gen_setDict(pObj2, pDict);
        //eRc = Gen_Compare(pObj1, pObj2);
        //TINYTEST_TRUE( (0 == eRc) );

        obj_Release(pObj2);
        pObj2 = OBJ_NIL;
#endif

        obj_Release(pObj1);
        pObj1 = OBJ_NIL;
        obj_Release(pDict);
        pDict = OBJ_NIL;
    }

    fprintf(stderr, "...%s completed.\n\n\n", pTestName);
    return 1;
}



int             test_Gen_Test01 (
    const
    char            *pTestName
)
{
    ERESULT         eRc = ERESULT_SUCCESS;
    GEN_DATA	    *pObj = OBJ_NIL;
    DICT_DATA       *pDict = OBJ_NIL;
    ASTR_DATA       *pStr = OBJ_NIL;
    ASTR_DATA       *pStr2 = OBJ_NIL;
    PATH_DATA       *pPath = OBJ_NIL;
    bool            fRc;
    int             iRc;
    const
    char            *pStrA;
   
    fprintf(stderr, "Performing: %s\n", pTestName);

    pObj = Gen_New( );
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    if (pObj) {

        //obj_TraceSet(pObj, true);       
        fRc = obj_IsKindOf(pObj, OBJ_IDENT_GEN);
        TINYTEST_TRUE( (fRc) );
        pDict = Dict_New( );
        TINYTEST_FALSE( (OBJ_NIL == pDict) );
        Gen_setDict(pObj, pDict);

        pStr = AStr_NewA("Xyzzy");
        TINYTEST_FALSE( (OBJ_NIL == pStr) );
        eRc = Dict_AddAStr(pObj->pDict, OBJECT_NAME, pStr);
        TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );
        obj_Release(pStr);
        pStr = OBJ_NIL;
        pStr2 = Dict_FindA(pObj->pDict, OBJECT_NAME);
        TINYTEST_FALSE( (OBJ_NIL == pStr2) );
        fRc = obj_IsKindOf(pStr2, OBJ_IDENT_ASTR);
        TINYTEST_TRUE( (fRc) );
        eRc = AStr_CompareA(pStr2, "Xyzzy");
        TINYTEST_TRUE( (0 == eRc) );
        eRc = Gen_SetDefaults(pObj);
        TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );
        pStrA = Dict_GetA(pObj->pDict, MODEL_DRIVE);
        TINYTEST_TRUE( (NULL == pStrA) );
        pStrA = Dict_GetA(pObj->pDict, MODEL_DIR);
        TINYTEST_FALSE( (NULL == pStrA) );
        iRc = strcmp(pStrA, "/Users/bob/Support/genObject");
        TINYTEST_TRUE( (0 == iRc) );
        pStrA = Dict_GetA(pObj->pDict, OUTPUT_DRIVE);
        TINYTEST_TRUE( (NULL == pStrA) );
        pStrA = Dict_GetA(pObj->pDict, OUTPUT_DIR);
        TINYTEST_FALSE( (NULL == pStrA) );
        iRc = strcmp(pStrA, "/Users/bob/Support/x");
        TINYTEST_TRUE( (0 == iRc) );

        pStr2 = AStr_NewA("model.obj.h.txt");
        pPath = Gen_CreateModelPath(pObj, pStr2);
        TINYTEST_FALSE( (OBJ_NIL == pPath) );
        fprintf(stderr, "\tmodel: %s -> %s\n", AStr_getData(pStr2), Path_getData(pPath));
        eRc = AStr_CompareA(Path_getAStr(pPath), "/Users/bob/Support/genObject/model.obj.h.txt");
        TINYTEST_TRUE( (0 == eRc) );
        obj_Release(pPath);
        pPath = OBJ_NIL;
        obj_Release(pStr2);
        pStr2 = OBJ_NIL;

        pStr2 = AStr_NewA("model.obj.h.txt");
        pPath = Gen_CreateOutputPath(pObj, pStr2);
        TINYTEST_FALSE( (OBJ_NIL == pPath) );
        fprintf(stderr, "\toutput: %s -> %s\n", AStr_getData(pStr2), Path_getData(pPath));
        eRc = AStr_CompareA(Path_getAStr(pPath), "/Users/bob/Support/x/Xyzzy.h");
        TINYTEST_TRUE( (0 == eRc) );
        obj_Release(pPath);
        pPath = OBJ_NIL;
        obj_Release(pStr2);
        pStr2 = OBJ_NIL;

        pStr2 = AStr_NewA("model.obj._internal.h.txt");
        pPath = Gen_CreateOutputPath(pObj, pStr2);
        TINYTEST_FALSE( (OBJ_NIL == pPath) );
        fprintf(stderr, "\toutput: %s -> %s\n", AStr_getData(pStr2), Path_getData(pPath));
        eRc = AStr_CompareA(Path_getAStr(pPath), "/Users/bob/Support/x/Xyzzy_internal.h");
        TINYTEST_TRUE( (0 == eRc) );
        obj_Release(pPath);
        pPath = OBJ_NIL;
        obj_Release(pStr2);
        pStr2 = OBJ_NIL;

        {
            ASTR_DATA       *pStr = Gen_ToDebugString(pObj, 0);
            if (pStr) {
                fprintf(stderr, "Debug: %s\n", AStr_getData(pStr));
                obj_Release(pStr);
                pStr = OBJ_NIL;
            }
        }

        obj_Release(pObj);
        pObj = OBJ_NIL;
        obj_Release(pDict);
        pDict = OBJ_NIL;
    }

    fprintf(stderr, "...%s completed.\n\n\n", pTestName);
    return 1;
}



int             test_Gen_ExpandData01 (
    const
    char            *pTestName
)
{
    ERESULT         eRc = ERESULT_SUCCESS;
    GEN_DATA        *pObj = OBJ_NIL;
    DICT_DATA       *pDict = OBJ_NIL;
    ASTR_DATA       *pStr = OBJ_NIL;
    //ASTR_DATA       *pStr2 = OBJ_NIL;
    //PATH_DATA       *pPath = OBJ_NIL;
    bool            fRc;
    TEXTIN_DATA     *pInput = OBJ_NIL;
    TEXTOUT_DATA    *pOutput = OBJ_NIL;
    const
    char            *pLinesA = "LNAME:${LNAME} UNAME:${UNAME}\n"
                    "${UNAME} ${LNAME} ${UNAME}\n"
                    "${XX} ${UNAME} ${XX}\n";
    ASTR_DATA       *pLines;
    uint32_t        cnt = 0;

    fprintf(stderr, "Performing: %s\n", pTestName);

    pLines = AStr_NewA(pLinesA);
    TINYTEST_FALSE( (OBJ_NIL == pLines) );
    pInput = TextIn_NewFromAStr(
                        OBJ_NIL,        // Path for Doc
                        pLines,         // Data AStr
                        1,              // FileNo for Doc
                        4               // Tab spacing
            );
    TINYTEST_FALSE( (OBJ_NIL == pInput) );
    pOutput = TextOut_NewAStr();
    TINYTEST_FALSE( (OBJ_NIL == pOutput) );

    pObj = Gen_New( );
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    if (pObj) {

        //obj_TraceSet(pObj, true);
        fRc = obj_IsKindOf(pObj, OBJ_IDENT_GEN);
        TINYTEST_TRUE( (fRc) );
        pDict = Dict_New( );
        TINYTEST_FALSE( (OBJ_NIL == pDict) );
        Gen_setDict(pObj, pDict);

        // Setup Expansion Variables.
        pStr = AStr_NewA("Xyzzy");
        TINYTEST_FALSE( (OBJ_NIL == pStr) );
        eRc = Dict_AddAStr(pObj->pDict, OBJECT_NAME, pStr);
        TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );
        obj_Release(pStr);
        pStr = OBJ_NIL;
        pStr = AStr_NewA("XYZZY");
        TINYTEST_FALSE( (OBJ_NIL == pStr) );
        eRc = Dict_AddAStr(pObj->pDict, OBJECT_NAME_UPPER, pStr);
        TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );
        obj_Release(pStr);
        pStr = OBJ_NIL;
        pStr = AStr_NewA("${LNAME}");
        TINYTEST_FALSE( (OBJ_NIL == pStr) );
        eRc = Dict_AddAStr(pObj->pDict, "XX", pStr);
        TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );
        obj_Release(pStr);
        pStr = OBJ_NIL;
        // Note use of expansion within expansion for XX.

        eRc = Gen_ExpandData(pObj, pInput, pOutput, &cnt);
        TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );
        pStr = TextOut_getStr(pOutput);
        TINYTEST_FALSE( (OBJ_NIL == pStr) );
        fprintf(stderr, "\tExpanded:\n%s\n", AStr_getData(pStr));
        eRc = AStr_CompareLeftA(pStr, "LNAME:Xyzzy UNAME:XYZZY\n");
        TINYTEST_TRUE( (0 == eRc) );
        eRc = AStr_CompareRightA(pStr, "Xyzzy XYZZY Xyzzy\n");
        TINYTEST_TRUE( (0 == eRc) );
        fprintf(stderr, "\tLines: %d\n", cnt);

        obj_Release(pObj);
        pObj = OBJ_NIL;
        obj_Release(pDict);
        pDict = OBJ_NIL;
    }

    obj_Release(pOutput);
    pOutput = OBJ_NIL;
    obj_Release(pInput);
    pInput = OBJ_NIL;
    obj_Release(pLines);
    pLines = OBJ_NIL;

    fprintf(stderr, "...%s completed.\n\n\n", pTestName);
    return 1;
}



int             test_Gen_ExpandFile01 (
    const
    char            *pTestName
)
{
    ERESULT         eRc = ERESULT_SUCCESS;
    GEN_DATA        *pObj = OBJ_NIL;
    DICT_DATA       *pDict = OBJ_NIL;
    ASTR_DATA       *pStr = OBJ_NIL;
    //ASTR_DATA       *pStr2 = OBJ_NIL;
    PATH_DATA       *pPath = OBJ_NIL;
    bool            fRc;
    TEXTIN_DATA     *pInput = OBJ_NIL;
    TEXTOUT_DATA    *pOutput = OBJ_NIL;
    const
    char            *pPathA =
                    "~/git/libCmn/programs/genObject/tests/files/test_expand_01.txt";
    uint32_t        cnt = 0;

    fprintf(stderr, "Performing: %s\n", pTestName);

    pPath = Path_NewA(pPathA);
    TINYTEST_FALSE( (OBJ_NIL == pPath) );
    pInput = TextIn_NewFromPath(
                        pPath,          // Data File
                        1,              // FileNo for Doc
                        4               // Tab spacing
            );
    TINYTEST_FALSE( (OBJ_NIL == pInput) );
    pOutput = TextOut_NewAStr();
    TINYTEST_FALSE( (OBJ_NIL == pOutput) );

    pObj = Gen_New( );
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    if (pObj) {

        //obj_TraceSet(pObj, true);
        fRc = obj_IsKindOf(pObj, OBJ_IDENT_GEN);
        TINYTEST_TRUE( (fRc) );
        pDict = Dict_New( );
        TINYTEST_FALSE( (OBJ_NIL == pDict) );
        Gen_setDict(pObj, pDict);

        // Setup Expansion Variables.
        pStr = AStr_NewA("Xyzzy");
        TINYTEST_FALSE( (OBJ_NIL == pStr) );
        eRc = Dict_AddAStr(pObj->pDict, OBJECT_NAME, pStr);
        TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );
        obj_Release(pStr);
        pStr = OBJ_NIL;
        pStr = AStr_NewA("XYZZY");
        TINYTEST_FALSE( (OBJ_NIL == pStr) );
        eRc = Dict_AddAStr(pObj->pDict, OBJECT_NAME_UPPER, pStr);
        TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );
        obj_Release(pStr);
        pStr = OBJ_NIL;
        pStr = AStr_NewA("${LNAME}");
        TINYTEST_FALSE( (OBJ_NIL == pStr) );
        eRc = Dict_AddAStr(pObj->pDict, "XX", pStr);
        TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );
        obj_Release(pStr);
        pStr = OBJ_NIL;
        // Note use of expansion within expansion for XX.

        eRc = Gen_ExpandData(pObj, pInput, pOutput, &cnt);
        TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );
        pStr = TextOut_getStr(pOutput);
        TINYTEST_FALSE( (OBJ_NIL == pStr) );
        fprintf(stderr, "\tExpanded:\n%s\n", AStr_getData(pStr));
        fprintf(stderr, "\tLines: %d\n", cnt);
        eRc = AStr_CompareLeftA(pStr, "LNAME:Xyzzy UNAME:XYZZY\n");
        TINYTEST_TRUE( (0 == eRc) );
        eRc = AStr_CompareRightA(pStr, "Xyzzy XYZZY Xyzzy\n\n");
        TINYTEST_TRUE( (0 == eRc) );

        obj_Release(pDict);
        pDict = OBJ_NIL;
        obj_Release(pObj);
        pObj = OBJ_NIL;
    }

    obj_Release(pOutput);
    pOutput = OBJ_NIL;
    obj_Release(pInput);
    pInput = OBJ_NIL;
    obj_Release(pPath);
    pPath = OBJ_NIL;

    fprintf(stderr, "...%s completed.\n\n\n", pTestName);
    return 1;
}



int             test_Gen_ExpandFile02 (
    const
    char            *pTestName
)
{
    ERESULT         eRc = ERESULT_SUCCESS;
    GEN_DATA        *pObj = OBJ_NIL;
    DICT_DATA       *pDict = OBJ_NIL;
    ASTR_DATA       *pStr = OBJ_NIL;
    //ASTR_DATA       *pStr2 = OBJ_NIL;
    PATH_DATA       *pPath = OBJ_NIL;
    bool            fRc;
    TEXTIN_DATA     *pInput = OBJ_NIL;
    TEXTOUT_DATA    *pOutput = OBJ_NIL;
    const
    char            *pPathA =
                    "~/git/Support/genObject/model.obj._internal.h.txt";
    uint32_t        cnt = 0;

    fprintf(stderr, "Performing: %s\n", pTestName);

    pPath = Path_NewA(pPathA);
    TINYTEST_FALSE( (OBJ_NIL == pPath) );
    pInput = TextIn_NewFromPath(
                        pPath,          // Data File
                        1,              // FileNo for Doc
                        4               // Tab spacing
            );
    TINYTEST_FALSE( (OBJ_NIL == pInput) );
    pOutput = TextOut_NewAStr();
    TINYTEST_FALSE( (OBJ_NIL == pOutput) );

    pObj = Gen_New( );
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    if (pObj) {

        //obj_TraceSet(pObj, true);
        fRc = obj_IsKindOf(pObj, OBJ_IDENT_GEN);
        TINYTEST_TRUE( (fRc) );
        pDict = Dict_New( );
        TINYTEST_FALSE( (OBJ_NIL == pDict) );
        Gen_setDict(pObj, pDict);

        // Setup Expansion Variables.
        pStr = AStr_NewA("Test01");
        TINYTEST_FALSE( (OBJ_NIL == pStr) );
        eRc = Dict_AddAStr(pObj->pDict, OBJECT_NAME, pStr);
        TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );
        obj_Release(pStr);
        pStr = OBJ_NIL;
        pStr = AStr_NewA("TEST01");
        TINYTEST_FALSE( (OBJ_NIL == pStr) );
        eRc = Dict_AddAStr(pObj->pDict, OBJECT_NAME_UPPER, pStr);
        TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );
        obj_Release(pStr);
        pStr = OBJ_NIL;
        eRc = Gen_SetDefaults(pObj);
        TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );

        eRc = Gen_ExpandData(pObj, pInput, pOutput, &cnt);
        TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );
        pStr = TextOut_getStr(pOutput);
        TINYTEST_FALSE( (OBJ_NIL == pStr) );
        fprintf(stderr, "\tExpanded:\n%s\n", AStr_getData(pStr));
        fprintf(stderr, "\tLines: %d\n", cnt);

        obj_Release(pDict);
        pDict = OBJ_NIL;
        obj_Release(pObj);
        pObj = OBJ_NIL;
    }

    obj_Release(pOutput);
    pOutput = OBJ_NIL;
    obj_Release(pInput);
    pInput = OBJ_NIL;
    obj_Release(pPath);
    pPath = OBJ_NIL;

    fprintf(stderr, "...%s completed.\n\n\n", pTestName);
    return 1;
}




TINYTEST_START_SUITE(test_Gen);
    TINYTEST_ADD_TEST(test_Gen_ExpandFile02,setUp,tearDown);
    TINYTEST_ADD_TEST(test_Gen_ExpandFile01,setUp,tearDown);
    TINYTEST_ADD_TEST(test_Gen_ExpandData01,setUp,tearDown);
    TINYTEST_ADD_TEST(test_Gen_Test01,setUp,tearDown);
    //TINYTEST_ADD_TEST(test_Gen_Copy01,setUp,tearDown);
    TINYTEST_ADD_TEST(test_Gen_OpenClose,setUp,tearDown);
TINYTEST_END_SUITE();

TINYTEST_MAIN_SINGLE_SUITE(test_Gen);





