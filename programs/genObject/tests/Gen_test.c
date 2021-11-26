// vi:nu:et:sts=4 ts=4 sw=4
//****************************************************************
//                      Test Object Program
//****************************************************************
/*
 * Program
 *          Test Object Program
 * Purpose
 *          This program tests a particular object given certain
 *          parameters.
 *
 * Remarks
 *  1.      This relies on the fact that we can add to the Test
 *          Object by simply coding methods that use the Test
 *          Object.
 *
 * History
 *  08/29/2021 Generated
 */


/*
 This is free and unencumbered software released into the public domain.
 
 Anyone is free to copy, modify, publish, use, compile, sell, or
 distribute this software, either in source code form or as a compiled
 binary, for any purpose, commercial or non-commercial, and by any
 means.
 
 In jurisdictions that recognize copyright laws, the author or authors
 of this software dedicate any and all copyright interest in the
 software to the public domain. We make this dedication for the benefit
 of the public at large and to the detriment of our heirs and
 successors. We intend this dedication to be an overt act of
 relinquishment in perpetuity of all present and future rights to this
 software under copyright law.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
 IN NO EVENT SHALL THE AUTHORS BE LIABLE FOR ANY CLAIM, DAMAGES OR
 OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
 ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 OTHER DEALINGS IN THE SOFTWARE.
 
 For more information, please refer to <http://unlicense.org/>
 */




/*
 TestForFail(error_sttring)         <= Tests eRc for failure
 TestForFalse(test, error_sttring)
 TestForNotNull(test, error)
 TestForNull(test, error)
 TestForSuccess(error)              <= Tests eRc for success
 TestForTrue(test, error)
 */





#include    <test_defs.h>
#include    <Test_internal.h>
#include    <trace.h>
#include    <Gen_internal.h>
#include    <JsonIn.h>
#include    <SrcErrors.h>
#include    <szTbl.h>
#include    <utf8.h>






ERESULT         Test_Gen_OpenClose (
    TEST_DATA       *this,
    const
    char            *pTestName
)
{
    ERESULT         eRc = ERESULT_SUCCESS;
    GEN_DATA       *pObj = OBJ_NIL;
    bool            fRc;
   
    fprintf(stderr, "Performing: %s\n", pTestName);

    pObj = Gen_Alloc( );
    TestForNotNull(pObj, "Missing Test Alloc() object");
    pObj = Gen_Init( pObj );
    TestForNotNull(pObj, "Missing Test Init() object");
    if (pObj) {

        //obj_TraceSet(pObj, true);       
        fRc = obj_IsKindOf(pObj, OBJ_IDENT_GEN);
        TestForTrue(fRc, "Failed Ident Test");
        
        // Test something.
        TestForSuccess("test failed");

        obj_Release(pObj);
        pObj = OBJ_NIL;
    }

    fprintf(stderr, "...%s completed.\n\n\n", pTestName);
    return eRc;
}



ERESULT         Test_Gen_Copy01 (
    TEST_DATA       *this,
    const
    char            *pTestName
)
{
    ERESULT         eRc = ERESULT_SUCCESS;
    GEN_DATA       *pObj1 = OBJ_NIL;
    GEN_DATA       *pObj2 = OBJ_NIL;
    bool            fRc;
#if defined(GEN_JSON_SUPPORT) && defined(XYZZY)
    ASTR_DATA       *pStr = OBJ_NIL;
#endif
    //int             iRc;
   
    fprintf(stderr, "Performing: %s\n", pTestName);

    pObj1 = Gen_New( );
    TestForNotNull(pObj1, "Missing Test object");
    if (pObj1) {

        //obj_TraceSet(pObj1, true);       
        fRc = obj_IsKindOf(pObj1, OBJ_IDENT_GEN);
        TestForTrue(fRc, "Failed Ident Test");
        
        // Test assign.
        pObj2 = Gen_New();
        TestForNotNull(pObj2, "Missing copied object");
        eRc = Gen_Assign(pObj1, pObj2);
        TestForFalse((ERESULT_FAILED(eRc)), "Assignment failed");

        fRc = obj_IsKindOf(pObj2, OBJ_IDENT_GEN);
        TestForTrue(fRc, "Failed Ident Test");
        //iRc = Gen_Compare(pObj1, pObj2);
        //TestForTrue((0 == iRc), "Failed Compare");
        //TODO: Add More tests here!

        obj_Release(pObj2);
        pObj2 = OBJ_NIL;

        // Test copy.
        pObj2 = Gen_Copy(pObj1);
        TestForNotNull(pObj2, "Missing copied object");

        fRc = obj_IsKindOf(pObj2, OBJ_IDENT_GEN);
        TestForTrue(fRc, "Failed Ident Test");
        //iRc = Gen_Compare(pObj1, pObj2);
        //TestForTrue((0 == iRc), "Failed Compare");
        //TODO: Add More tests here!

        obj_Release(pObj2);
        pObj2 = OBJ_NIL;

        // Test json support.
#if defined(GEN_JSON_SUPPORT) && defined(XYZZY)
        pStr = Gen_ToJson(pObj1);
        TestForNotNull(pStr, "Missing JSON output");
        fprintf(stderr, "JSON: %s\n", AStr_getData(pStr));
        pObj2 = Gen_NewFromJsonString(pStr);
        TestForNotNull(pObj2, "Missing JSON created object");
        fRc = obj_IsKindOf(pObj2, OBJ_IDENT_GEN);
        TestForTrue(fRc, "Failed Ident Test");
        obj_Release(pStr);
        pStr = OBJ_NIL;
        //iRc = Gen_Compare(pObj1, pObj2);
        //TestForTrue((0 == iRc), "Failed Compare");

        obj_Release(pObj2);
        pObj2 = OBJ_NIL;
#endif

        obj_Release(pObj1);
        pObj1 = OBJ_NIL;
    }

    fprintf(stderr, "...%s completed.\n\n\n", pTestName);
    return eRc;
}



ERESULT         Test_Gen_Test01 (
    TEST_DATA       *this,
    const
    char            *pTestName
)
{
    ERESULT         eRc = ERESULT_SUCCESS;
    GEN_DATA       *pObj = OBJ_NIL;
    bool            fRc;
   
    fprintf(stderr, "Performing: %s\n", pTestName);

    pObj = Gen_New( );
    TestForNotNull(pObj, "Missing Test object");
    if (pObj) {

        //obj_TraceSet(pObj, true);       
        fRc = obj_IsKindOf(pObj, OBJ_IDENT_GEN);
        TestForTrue(fRc, "Failed Ident Test");
        Test_setVerbose(this, 1);
        Gen_setMsg(pObj, (void *)Test_MsgInfo, (void *)Test_MsgWarn, this);
        
        {
            ASTR_DATA       *pStr = Gen_ToDebugString(pObj, 4);
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
    return eRc;
}



// Test Gen_ExpandVars().
ERESULT         Test_Gen_Test02 (
    TEST_DATA       *this,
    const
    char            *pTestName
)
{
    ERESULT         eRc = ERESULT_SUCCESS;
    GEN_DATA       *pObj = OBJ_NIL;
    bool            fRc;
    const
    char            *pHome = NULL;
    int             len = 0;
    ASTR_DATA       *pStr1 = OBJ_NIL;
    ASTR_DATA       *pStr2 = OBJ_NIL;

    fprintf(stderr, "Performing: %s\n", pTestName);
    fprintf(stderr, "Test Gen_ExpandVars().\n");

    pObj = Gen_New( );
    TestForNotNull(pObj, "Missing Test object");
    if (pObj) {

        //obj_TraceSet(pObj, true);
        fRc = obj_IsKindOf(pObj, OBJ_IDENT_GEN);
        TestForTrue(fRc, "Failed Ident Test");
        Test_setVerbose(this, 1);
        Gen_setMsg(pObj, (void *)Test_MsgInfo, (void *)Test_MsgWarn, this);

        pHome = getenv("HOME");
        TestForNotNull(((char *)pHome), "");
        if (pHome) {
            len = (int)strlen(pHome);
            pStr1 = AStr_NewA(pHome);
            eRc = AStr_AppendA(pStr1, "$");
            TestForSuccess("");
            eRc = AStr_AppendA(pStr1, pHome);
            TestForSuccess("");
        }

        pStr2 = AStr_NewA("${HOME}$${HOME}");
        TestForNotNull(pStr2, "");
        if (pStr2) {

            eRc = Gen_ExpandVars(pObj, pStr2);
            TestForSuccess("");
            TestForTrue((AStr_getLength(pStr1) == AStr_getLength(pStr2)), "");
            TestForTrue((0 == AStr_Compare(pStr1, pStr2)), "");

            obj_Release(pStr1);
            pStr1 = OBJ_NIL;
            obj_Release(pStr2);
            pStr2 = OBJ_NIL;
        }

        obj_Release(pObj);
        pObj = OBJ_NIL;
    }

    fprintf(stderr, "...%s completed.\n\n\n", pTestName);
    return eRc;
}



ERESULT         Test_Gen_Test03 (
    TEST_DATA       *this,
    const
    char            *pTestName
)
{
    ERESULT         eRc = ERESULT_SUCCESS;
    GEN_DATA       *pObj = OBJ_NIL;
    bool            fRc;
    DICT_DATA       *pDict = OBJ_NIL;
    ASTR_DATA       *pStr  = OBJ_NIL;
    ASTR_DATA       *pStr2 = OBJ_NIL;
    PATH_DATA       *pPath = OBJ_NIL;
    PATH_DATA       *pPathReal = OBJ_NIL;
    int             iRc;
    const
    char            *pStrA;
    const
    char            *pMdlDirA = TEST_MODELS_DIR "/";
    const
    char            *pTestDirA = TEST_FILES_DIR "/x/";
    char            *pFileNameA;

    fprintf(stderr, "Performing: %s\n", pTestName);
    fprintf(stderr, "Test Gen_CreateModelPath().\n");

    pDict = Dict_New( );
    TestForNotNull(pDict, "");

    pObj = Gen_New( );
    TestForNotNull(pObj, "Missing Test object");
    if (pObj) {

        //obj_TraceSet(pObj, true);
        fRc = obj_IsKindOf(pObj, OBJ_IDENT_GEN);
        TestForTrue(fRc, "Failed Ident Test");
        Test_setVerbose(this, 1);
        Gen_setMsg(pObj, (void *)Test_MsgInfo, (void *)Test_MsgWarn, this);
        Gen_setDict(pObj, pDict);

        // Override default file locations.
        Gen_setModelDrvDirA(pObj, pMdlDirA);
        Gen_setOutputDrvDirA(pObj, pTestDirA);
        Gen_SetDefaults(pObj);

        pStr = AStr_NewA("Xyzzy");
        TestForNotNull(pStr, "");
        eRc = Dict_AddAStr(pObj->pDict, OBJECT_NAME, pStr);
        TestForSuccess("");
        obj_Release(pStr);
        pStr = OBJ_NIL;
        pStr2 = Dict_FindA(pObj->pDict, OBJECT_NAME);
        TestForNotNull(pStr2, "");
        fRc = obj_IsKindOf(pStr2, OBJ_IDENT_ASTR);
        TestForTrue(fRc, "");
        iRc = AStr_CompareA(pStr2, "Xyzzy");
        TestForTrue((0 == iRc), "");
        eRc = Gen_SetDefaults(pObj);
        TestForSuccess("");
        pStrA = Dict_GetA(pObj->pDict, MODEL_DRIVE);
        TestForNull((char *)pStrA, "");
        pStrA = Dict_GetA(pObj->pDict, MODEL_DIR);
        TestForNotNull((char *)pStrA, "");
        pPathReal = Path_NewA(pMdlDirA);
        TestForNotNull(pPathReal, "");
        Path_Clean(pPathReal);
        iRc = Path_CompareA(pPathReal, pStrA);
        TestForTrue(fRc, "");
        obj_Release(pPathReal);
        pPathReal = OBJ_NIL;
        pStrA = Dict_GetA(pObj->pDict, OUTPUT_DRIVE);
        TestForNull((char *)pStrA, "");
        pStrA = Dict_GetA(pObj->pDict, OUTPUT_DIR);
        TestForNotNull((char *)pStrA, "");
        pPathReal = Path_NewA(pTestDirA);
        TestForNotNull(pPathReal, "");
        Path_Clean(pPathReal);
        iRc = Path_CompareA(pPathReal, pStrA);
        TestForTrue(fRc, "");
        obj_Release(pPathReal);
        pPathReal = OBJ_NIL;

        pFileNameA = "model.obj.h.txt";
        pStr2 = AStr_NewA(pFileNameA);
        pPath = Gen_CreateModelPath(pObj, pStr2);
        TestForNotNull(pPath, "");
        pPathReal = Path_NewA(pMdlDirA);
        TestForNotNull(pPathReal, "");
        eRc = Path_AppendFileNameA(pPathReal, pFileNameA);
        TestForSuccess("");
        Path_Clean(pPathReal);
        fprintf(stderr, "\tmodel: %s -> %s\n", AStr_getData(pStr2), Path_getData(pPath));
        iRc = Path_Compare(pPath, pPathReal);
        TestForTrue(fRc, "");
        obj_Release(pPathReal);
        pPathReal = OBJ_NIL;
        obj_Release(pPath);
        pPath = OBJ_NIL;
        obj_Release(pStr2);
        pStr2 = OBJ_NIL;
        pFileNameA = NULL;

        pFileNameA = "src/Xyzzy.h";
        pStr2 = AStr_NewA(pFileNameA);
        pPath = Gen_CreateOutputPath(pObj, "src", ".h");
        TestForNotNull(pPath, "");
        pPathReal = Path_NewA(pTestDirA);
        TestForNotNull(pPathReal, "");
        eRc = Path_AppendFileNameA(pPathReal, pFileNameA);
        TestForSuccess("");
        Path_Clean(pPathReal);
        fprintf(stderr, "\toutput: %s -> %s\n", AStr_getData(pStr2), Path_getData(pPath));
        iRc = Path_Compare(pPath, pPathReal);
        TestForTrue(fRc, "");
        obj_Release(pPathReal);
        pPathReal = OBJ_NIL;
        obj_Release(pPath);
        pPath = OBJ_NIL;
        obj_Release(pStr2);
        pStr2 = OBJ_NIL;
        pFileNameA = NULL;

        pFileNameA = "src/Xyzzy_internal.h";
        pStr2 = AStr_NewA(pFileNameA);
        pPath = Gen_CreateOutputPath(pObj, "src", "_internal.h");
        TestForNotNull(pPath, "");
        pPathReal = Path_NewA(pTestDirA);
        TestForNotNull(pPathReal, "");
        eRc = Path_AppendFileNameA(pPathReal, pFileNameA);
        TestForSuccess("");
        Path_Clean(pPathReal);
        fprintf(stderr, "\toutput: %s -> %s\n", AStr_getData(pStr2), Path_getData(pPath));
        iRc = Path_Compare(pPath, pPathReal);
        TestForTrue(fRc, "");
        obj_Release(pPathReal);
        pPathReal = OBJ_NIL;
        obj_Release(pPath);
        pPath = OBJ_NIL;
        obj_Release(pStr2);
        pStr2 = OBJ_NIL;
        pFileNameA = NULL;

        obj_Release(pObj);
        pObj = OBJ_NIL;
    }

    obj_Release(pDict);
    pDict = OBJ_NIL;
    fprintf(stderr, "...%s completed.\n\n\n", pTestName);
    return eRc;
}



ERESULT         Test_Gen_Test04_DONT_USE (
    TEST_DATA       *this,
    const
    char            *pTestName
)
{
    ERESULT         eRc = ERESULT_SUCCESS;
    GEN_DATA        *pObj = OBJ_NIL;
    bool            fRc;
    int             iRc;
    DICT_DATA       *pDict = OBJ_NIL;
    TEXTIN_DATA     *pInput = OBJ_NIL;
    TEXTOUT_DATA    *pOutput = OBJ_NIL;
    const
    char            *pLinesA = "LNAME:${LNAME} UNAME:${UNAME}\n"
                    "${UNAME} ${LNAME} ${UNAME}\n"
                    "${XX} ${UNAME} ${XX}\n";
    ASTR_DATA       *pLines;
    ASTR_DATA       *pStr;
    uint32_t        cnt = 0;

    fprintf(stderr, "Performing: %s\n", pTestName);
    fprintf(stderr, "Testing: Gen_ExpandData()\n");

    pDict = Dict_New( );
    TestForNotNull(pDict, "");

    pLines = AStr_NewA(pLinesA);
    TestForNotNull(pLines, "");
    pInput = TextIn_NewFromAStr(
                        OBJ_NIL,        // Path for Doc
                        pLines,         // Data AStr
                        1,              // FileNo for Doc
                        4               // Tab spacing
            );
    TestForNotNull(pInput, "");
    pOutput = TextOut_NewAStr();
    TestForNotNull(pOutput, "");

    pObj = Gen_New( );
    TestForNotNull(pObj, "Missing Test object");
    if (pObj) {

        //obj_TraceSet(pObj, true);
        fRc = obj_IsKindOf(pObj, OBJ_IDENT_GEN);
        TestForTrue(fRc, "Failed Ident Test");
        Test_setVerbose(this, 1);
        Gen_setMsg(pObj, (void *)Test_MsgInfo, (void *)Test_MsgWarn, this);
        Gen_setDict(pObj, pDict);

        // Setup Expansion Variables.
        pStr = AStr_NewA("Xyzzy");
        TestForNotNull(pStr, "");
        eRc = Dict_AddAStr(pObj->pDict, OBJECT_NAME, pStr);
        TestForSuccess("");
        obj_Release(pStr);
        pStr = OBJ_NIL;
        pStr = AStr_NewA("XYZZY");
        TestForNotNull(pStr, "");
        eRc = Dict_AddAStr(pObj->pDict, OBJECT_NAME_UPPER, pStr);
        TestForSuccess("");
        obj_Release(pStr);
        pStr = OBJ_NIL;
        pStr = AStr_NewA("${LNAME}");
        TestForNotNull(pStr, "");
        eRc = Dict_AddAStr(pObj->pDict, "XX", pStr);
        TestForSuccess("");
        obj_Release(pStr);
        pStr = OBJ_NIL;
        // Note use of expansion within expansion for XX.

        eRc = Gen_ExpandData(pObj, pInput, pOutput, &cnt);
        TestForSuccess("");
        pStr = TextOut_getStr(pOutput);
        TestForNotNull(pStr, "");
        fprintf(stderr, "\tExpanded:\n%s\n", AStr_getData(pStr));
        iRc = AStr_CompareLeftA(pStr, "LNAME:Xyzzy UNAME:XYZZY\n");
        TestForTrue((0 == iRc), "");
        iRc = AStr_CompareRightA(pStr, "Xyzzy XYZZY Xyzzy\n");
        TestForTrue((0 == iRc), "");
        fprintf(stderr, "\tLines: %d\n", cnt);
        TestForTrue((3 == cnt), "");

        obj_Release(pObj);
        pObj = OBJ_NIL;
    }

    obj_Release(pOutput);
    pOutput = OBJ_NIL;
    obj_Release(pInput);
    pInput = OBJ_NIL;
    obj_Release(pLines);
    pLines = OBJ_NIL;
    obj_Release(pDict);
    pDict = OBJ_NIL;
    fprintf(stderr, "...%s completed.\n\n\n", pTestName);
    return eRc;
}



ERESULT         Test_Gen_Test05_DONT_USE (
    TEST_DATA       *this,
    const
    char            *pTestName
)
{
    ERESULT         eRc = ERESULT_SUCCESS;
    GEN_DATA        *pObj = OBJ_NIL;
    bool            fRc;
    int             iRc;
    DICT_DATA       *pDict = OBJ_NIL;
    TEXTIN_DATA     *pInput = OBJ_NIL;
    TEXTOUT_DATA    *pOutput = OBJ_NIL;
    ASTR_DATA       *pStr;
    uint32_t        cnt = 0;
    const
    char            *pPathA = TEST_FILES_DIR "/test_expand_01.txt";
    PATH_DATA       *pPath = OBJ_NIL;

    fprintf(stderr, "Performing: %s\n", pTestName);
    fprintf(stderr, "Testing: Gen_ExpandFile()\n");

    pDict = Dict_New( );
    TestForNotNull(pDict, "");

    pPath = Path_NewA(pPathA);
    TestForNotNull(pPath, "");
    pInput = TextIn_NewFromPath(
                        pPath,          // Data File
                        1,              // FileNo for Doc
                        4               // Tab spacing
            );
    TestForNotNull(pInput, "");
    obj_Release(pPath);
    pPath = OBJ_NIL;
    pOutput = TextOut_NewAStr();
    TestForNotNull(pOutput, "");

    pObj = Gen_New( );
    TestForNotNull(pObj, "Missing Test object");
    if (pObj) {

        //obj_TraceSet(pObj, true);
        fRc = obj_IsKindOf(pObj, OBJ_IDENT_GEN);
        TestForTrue(fRc, "Failed Ident Test");
        Test_setVerbose(this, 1);
        Gen_setMsg(pObj, (void *)Test_MsgInfo, (void *)Test_MsgWarn, this);
        Gen_setDict(pObj, pDict);

        // Setup Expansion Variables.
        pStr = AStr_NewA("Xyzzy");
        TestForNotNull(pStr, "");
        eRc = Dict_AddAStr(pObj->pDict, OBJECT_NAME, pStr);
        TestForSuccess("");
        obj_Release(pStr);
        pStr = OBJ_NIL;
        pStr = AStr_NewA("XYZZY");
        TestForNotNull(pStr, "");
        eRc = Dict_AddAStr(pObj->pDict, OBJECT_NAME_UPPER, pStr);
        TestForSuccess("");
        obj_Release(pStr);
        pStr = OBJ_NIL;
        pStr = AStr_NewA("${LNAME}");
        TestForNotNull(pStr, "");
        eRc = Dict_AddAStr(pObj->pDict, "XX", pStr);
        TestForSuccess("");
        obj_Release(pStr);
        pStr = OBJ_NIL;
        // Note use of expansion within expansion for XX.

        eRc = Gen_ExpandData(pObj, pInput, pOutput, &cnt);
        TestForSuccess("");
        pStr = TextOut_getStr(pOutput);
        TestForNotNull(pStr, "");
        fprintf(stderr, "\tExpanded:\n%s\n", AStr_getData(pStr));
        iRc = AStr_CompareLeftA(pStr, "LNAME:Xyzzy UNAME:XYZZY\n");
        TestForTrue((0 == iRc), "");
        iRc = AStr_CompareRightA(pStr, "Xyzzy XYZZY Xyzzy\n\n");
        TestForTrue((0 == iRc), "");
        fprintf(stderr, "\tLines: %d\n", cnt);
        TestForTrue((4 == cnt), "");

        obj_Release(pObj);
        pObj = OBJ_NIL;
    }

    obj_Release(pOutput);
    pOutput = OBJ_NIL;
    obj_Release(pInput);
    pInput = OBJ_NIL;
    obj_Release(pDict);
    pDict = OBJ_NIL;
    fprintf(stderr, "...%s completed.\n\n\n", pTestName);
    return eRc;
}




int     main (
    int         cArgs,
    const
    char        *ppArgs[],
    const
    char        *ppEnv[]
)
{
    ERESULT     eRc;
    TEST_DATA   test = {0};
    TEST_DATA   *pTest = OBJ_NIL;
    int         i;
    const
    char        *pTestNameA = NULL;

    pTest = Test_Init(&test);
    if (OBJ_NIL == pTest) {
        fprintf(
                stderr,
                "\x1b[1m\x1b[31mFATAL\x1b[0m: Could not create Test object!\n\n\n"
        );
        exit(201);
    }

    // Scan args.
    for (i=0; i<cArgs; i++) {
        if (0 == strcmp("--no_int3", ppArgs[i])) {
            Test_setAllowInt3(pTest, false);
        }
    }

    // Execute tests.
    TestExec("OpenClose", Test_Gen_OpenClose, NULL, NULL);
    //TestExec("Copy01", Test_Gen_Copy01, pTest, NULL, NULL);
    TestExec("Test01", Test_Gen_Test01, NULL, NULL);
    TestExec("Test02", Test_Gen_Test02, NULL, NULL);
    TestExec("Test03", Test_Gen_Test03, NULL, NULL);

    obj_Release(pTest);
    pTest = OBJ_NIL;

    // Return to Operating System.
    return 0;
}



