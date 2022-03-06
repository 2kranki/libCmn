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
#include    <Appl_internal.h>
#include    <JsonIn.h>
#include    <objTest_internal.h>
#include    <SrcErrors.h>
#include    <szTbl.h>



typedef     struct args_s {
    uint16_t        fArchive;
    NUMBER_DATA     *pArgLen;
    PATH_DATA       *pInFilePath;      // ("-f" | "--file=")<string> or ("-f" | "--file") <string>
    PATH_DATA       *pOutFilePath;     // ("-o" | "--out=")<string> or ("-o" | "--out") <string>
} ARGS;




ARGS                args = {
    0,                  // fArchive
    0,                  // argLen
    OBJ_NIL,            // pInFilePath
    OBJ_NIL             // pOutFilePath
};


CMDUTL_OPTION       pPgmArgs1[] = {
    {
        "archive",
        'a',
        CMDUTL_ARG_OPTION_NONE,
        CMDUTL_TYPE_BOOL,
        0,
        offsetof(ARGS, fArchive),
        NULL,
        "Set Archive Mode"
    },
    {
        "arglength",
        'l',
        CMDUTL_ARG_OPTION_REQUIRED,
        CMDUTL_TYPE_NUMBER,
        0,
        offsetof(ARGS, pArgLen),
        NULL,
        "Set Argument Length"
    },
    {
        "input",
        'i',
        CMDUTL_ARG_OPTION_REQUIRED,
        CMDUTL_TYPE_PATH,
        0,
        offsetof(ARGS, pInFilePath),
        NULL,
        "Set Input File Path"
    },
    {
        "output",
        'o',
        CMDUTL_ARG_OPTION_REQUIRED,
        CMDUTL_TYPE_PATH,
        0,
        offsetof(ARGS, pOutFilePath),
        NULL,
        "Set Output File Path"
    },
    {NULL,0,0,0,0,0,NULL,NULL}                    // End of Table
};



/*!
 Print the program description with a trailing '\n' and leading "  ".
 @param     pObj        Object Pointer
 @param     pOutput     File to write to
 @param     pPgmPath    Program's Path
 @return    ERESULT_SUCCESS if successful, otherwise, an ERESULT_*
            error code.
 */
ERESULT         usageDesc(
    OBJ_ID          pObj,
    FILE            *pOutput,
    PATH_DATA       *pPgmPath
)
{
    fprintf(pOutput, "  This program does blah blah blah.\n");
    return ERESULT_SUCCESS;
}



/*!
 Print the program usage line with a trailing '\n' and leading "  ".
 @param     pObj        Object Pointer
 @param     pOutput     File to write to
 @param     pPgmPath    Program's Path
 @param     pNameA      Program's name
 @return    ERESULT_SUCCESS if successful, otherwise, an ERESULT_*
            error code.
 */
ERESULT         usageProgLine(
    OBJ_ID          pObj,
    FILE            *pOutput,
    PATH_DATA       *pPgmPath,
    const
    char            *pNameA
)
{
    fprintf(pOutput, "  %s [options] other_stuff\n", pNameA);

    return ERESULT_SUCCESS;
}



int         processArg(
    OBJ_ID      pObj,
    const
    char        *pArg
)
{
    fprintf(stderr, "processArg arg:\"%s\"\n", pArg);
    return 0;
}






ERESULT         Test_Appl_OpenClose (
    TEST_DATA       *this,
    const
    char            *pTestName
)
{
    ERESULT         eRc = ERESULT_SUCCESS;
    APPL_DATA       *pObj = OBJ_NIL;
    bool            fRc;
   
    fprintf(stderr, "Performing: %s\n", pTestName);

    pObj = Appl_Alloc( );
    TestForNotNull(pObj, "Missing Test Alloc() object");
    pObj = Appl_Init( pObj );
    TestForNotNull(pObj, "Missing Test Init() object");
    if (pObj) {

        //obj_TraceSet(pObj, true);       
        fRc = obj_IsKindOf(pObj, OBJ_IDENT_APPL);
        TestForTrue(fRc, "Failed Ident Test");
#ifdef   APPL_MSGS
        Appl_setMsg(pObj, (void *)Test_MsgInfo, (void *)Test_MsgWarn, this);
#endif
        
        // Test something.
        TestForSuccess("test failed");

        obj_Release(pObj);
        pObj = OBJ_NIL;
    }

    fprintf(stderr, "...%s completed.\n\n\n", pTestName);
    return eRc;
}



ERESULT         Test_Appl_Copy01 (
    TEST_DATA       *this,
    const
    char            *pTestName
)
{
    ERESULT         eRc = ERESULT_SUCCESS;
    APPL_DATA       *pObj1 = OBJ_NIL;
    APPL_DATA       *pObj2 = OBJ_NIL;
    bool            fRc;
#if defined(APPL_JSON_SUPPORT) && defined(XYZZY)
    ASTR_DATA       *pStr = OBJ_NIL;
#endif
    //int             iRc;
   
    fprintf(stderr, "Performing: %s\n", pTestName);

    pObj1 = Appl_New( );
    TestForNotNull(pObj1, "Missing Test object");
    if (pObj1) {

        //obj_TraceSet(pObj1, true);       
        fRc = obj_IsKindOf(pObj1, OBJ_IDENT_APPL);
        TestForTrue(fRc, "Failed Ident Test");
#ifdef   APPL_MSGS
        Appl_setMsg(pObj1, (void *)Test_MsgInfo, (void *)Test_MsgWarn, this);
#endif
        
        // Test assign.
        pObj2 = Appl_New();
        TestForNotNull(pObj2, "Missing copied object");
        eRc = Appl_Assign(pObj1, pObj2);
        TestForFalse((ERESULT_FAILED(eRc)), "Assignment failed");

        fRc = obj_IsKindOf(pObj2, OBJ_IDENT_APPL);
        TestForTrue(fRc, "Failed Ident Test");
        //iRc = Appl_Compare(pObj1, pObj2);
        //TestForTrue((0 == iRc), "Failed Compare");
        //TODO: Add More tests here!

        obj_Release(pObj2);
        pObj2 = OBJ_NIL;

        // Test copy.
        pObj2 = Appl_Copy(pObj1);
        TestForNotNull(pObj2, "Missing copied object");

        fRc = obj_IsKindOf(pObj2, OBJ_IDENT_APPL);
        TestForTrue(fRc, "Failed Ident Test");
        //iRc = Appl_Compare(pObj1, pObj2);
        //TestForTrue((0 == iRc), "Failed Compare");
        //TODO: Add More tests here!

        obj_Release(pObj2);
        pObj2 = OBJ_NIL;

        // Test json support.
#if defined(APPL_JSON_SUPPORT) && defined(XYZZY)
        pStr = Appl_ToJson(pObj1);
        TestForNotNull(pStr, "Missing JSON output");
        fprintf(stderr, "JSON: %s\n", AStr_getData(pStr));
        pObj2 = Appl_NewFromJsonString(pStr);
        TestForNotNull(pObj2, "Missing JSON created object");
        fRc = obj_IsKindOf(pObj2, OBJ_IDENT_APPL);
        TestForTrue(fRc, "Failed Ident Test");
        obj_Release(pStr);
        pStr = OBJ_NIL;
        //iRc = Appl_Compare(pObj1, pObj2);
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



ERESULT         Test_Appl_Test01 (
    TEST_DATA       *this,
    const
    char            *pTestName
)
{
    ERESULT         eRc = ERESULT_SUCCESS;
    APPL_DATA       *pObj = OBJ_NIL;
    bool            fRc;
   
    fprintf(stderr, "Performing: %s\n", pTestName);

    pObj = Appl_New( );
    TestForNotNull(pObj, "Missing Test object");
    if (pObj) {

        obj_TraceSet(pObj, true);
        fRc = obj_IsKindOf(pObj, OBJ_IDENT_APPL);
        TestForTrue(fRc, "Failed Ident Test");
#ifdef   APPL_MSGS
        Appl_setMsg(pObj, (void *)Test_MsgInfo, (void *)Test_MsgWarn, this);
#endif
        Appl_setArgDefs(pObj, pPgmArgs1);

        {
            ASTR_DATA       *pStr = Appl_ToDebugString(pObj, 4);
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



ERESULT         Test_Appl_Test02 (
    TEST_DATA       *this,
    const
    char            *pTestName
)
{
    ERESULT         eRc = ERESULT_SUCCESS;
    APPL_DATA       *pObj = OBJ_NIL;
    bool            fRc;
    char            *pChrStr = NULL;
    char            *ppArgs1[] = {
        "./program_name",
        "--debug",
        "-v",
        "1st_Arg",
        "2nd_Arg",
        NULL
    };
    int             cArgs1 = 5;

    fprintf(stderr, "Performing: %s\n", pTestName);

    pObj = Appl_New( );
    TestForNotNull(pObj, "Missing Test object");
    if (pObj) {

        obj_TraceSet(pObj, true);
        fRc = obj_IsKindOf(pObj, OBJ_IDENT_APPL);
        TestForTrue(fRc, "Failed Ident Test");
#ifdef   APPL_MSGS
        Appl_setMsg(pObj, (void *)Test_MsgInfo, (void *)Test_MsgWarn, this);
#endif
        Appl_setArgDefs(pObj, pPgmArgs1);

        eRc = Appl_SetupFromArgV((APPL_DATA *)pObj, cArgs1, ppArgs1, NULL);
        TestForSuccess("");

        fRc = Appl_IsMore((APPL_DATA *)pObj);
        TestForTrue((fRc), "");

        eRc = Appl_ProcessOptions((APPL_DATA *)pObj);
        TestForSuccess("");
        TestForTrue((true == Appl_getDebug((APPL_DATA *)pObj)), "");
        TestForTrue((1 == Appl_getVerbose((APPL_DATA *)pObj)), "");

        fRc = Appl_IsMore((APPL_DATA *)pObj);
        TestForTrue((fRc), "");

        pChrStr = Appl_NextArg((APPL_DATA *)pObj);
        TestForNotNull(pChrStr, "");
        TestForTrue((0 == strcmp("1st_Arg", pChrStr)), "");

        fRc = Appl_IsMore((APPL_DATA *)pObj);
        TestForTrue((fRc), "");

        pChrStr = Appl_NextArg((APPL_DATA *)pObj);
        TestForNotNull(pChrStr, "");
        TestForTrue((0 == strcmp("2nd_Arg", pChrStr)), "");

        fRc = Appl_IsMore((APPL_DATA *)pObj);
        TestForFalse((fRc), "");

        obj_Release(pObj);
        pObj = OBJ_NIL;
    }

    fprintf(stderr, "...%s completed.\n\n\n", pTestName);
    return eRc;
}



ERESULT         Test_Appl_Test03 (
    TEST_DATA       *this,
    const
    char            *pTestName
)
{
    ERESULT         eRc = ERESULT_SUCCESS;
    APPL_DATA       *pObj = OBJ_NIL;
    bool            fRc;
    int             iRc;
    ASTRCARRAY_DATA *pArgV = OBJ_NIL;
    char            *ppArgs1[] = {
        "./program_name",
        "--debug",
        "-v",
        "1st_Arg",
        "2nd_Arg",
        NULL
    };
    int             cArgs1 = 5;
    const
    char            *pCmd = "./program_name --debug -v 1st_Arg 2nd_Arg";
    uint32_t        i;

    fprintf(stderr, "Performing: %s\n", pTestName);

    pObj = Appl_New( );
    TestForNotNull(pObj, "Missing Test object");
    if (pObj) {

        obj_TraceSet(pObj, true);
        fRc = obj_IsKindOf(pObj, OBJ_IDENT_APPL);
        TestForTrue(fRc, "Failed Ident Test");
#ifdef   APPL_MSGS
        Appl_setMsg(pObj, (void *)Test_MsgInfo, (void *)Test_MsgWarn, this);
#endif

        Appl_setArgDefs(pObj, pPgmArgs1);

        eRc = Appl_ParseProgramLine(pCmd, &pArgV);
        TestForSuccess("");
        TestForNotNull(pArgV, "");

        fprintf(stderr, "\tNum Args = %d\n", AStrCArray_getSize(pArgV));
        {
            ASTR_DATA           *pStr = AStrCArray_ToDebugString(pArgV, 4);
            fprintf(stderr, "%s\n", AStr_getData(pStr));
            obj_Release(pStr);
            pStr = OBJ_NIL;
        }

        i = AStrCArray_getSize(pArgV);
        TestForTrue((cArgs1 == i), "");
        for (i=0; i<cArgs1; i++) {
            iRc = AStrC_CompareA(AStrCArray_Get(pArgV, i+1), ppArgs1[i]);
            TestForTrue((0 == iRc), "");
        }

        obj_Release(pArgV);
        pArgV = OBJ_NIL;

        obj_Release(pObj);
        pObj = OBJ_NIL;
    }

    fprintf(stderr, "...%s completed.\n\n\n", pTestName);
    return eRc;
}



ERESULT         Test_Appl_Test04 (
    TEST_DATA       *this,
    const
    char            *pTestName
)
{
    ERESULT         eRc = ERESULT_SUCCESS;
    APPL_DATA       *pObj = OBJ_NIL;
    bool            fRc;
    int             iRc;
    ASTRCARRAY_DATA *pArgV = OBJ_NIL;
    char            *ppArgs1[] = {
        "./program_name",
        "--debug='true'",
        "-v",
        "1st_Arg",
        "\"2nd_Arg\"",
        NULL
    };
    int             cArgs1 = 5;
    const
    char            *pCmd = "./program_name --debug='true' -v 1st_Arg \"2nd_Arg\"";
    uint32_t        i;

    fprintf(stderr, "Performing: %s\n", pTestName);

    pObj = Appl_New( );
    TestForNotNull(pObj, "Missing Test object");
    if (pObj) {

        //obj_TraceSet(pObj, true);
        fRc = obj_IsKindOf(pObj, OBJ_IDENT_APPL);
        TestForTrue(fRc, "Failed Ident Test");
#ifdef   APPL_MSGS
        Appl_setMsg(pObj, (void *)Test_MsgInfo, (void *)Test_MsgWarn, this);
#endif

        Appl_setArgDefs(pObj, pPgmArgs1);

        eRc = Appl_ParseProgramLine(pCmd, &pArgV);
        TestForSuccess("");
        TestForNotNull(pArgV, "");

        fprintf(stderr, "\tNum Args = %d\n", AStrCArray_getSize(pArgV));
        {
            ASTR_DATA           *pStr = AStrCArray_ToDebugString(pArgV, 4);
            fprintf(stderr, "%s\n", AStr_getData(pStr));
            obj_Release(pStr);
            pStr = OBJ_NIL;
        }

        i = AStrCArray_getSize(pArgV);
        TestForTrue((cArgs1 == i), "");
        for (i=0; i<cArgs1; i++) {
            iRc = AStrC_CompareA(AStrCArray_Get(pArgV, i+1), ppArgs1[i]);
            TestForTrue((0 == iRc), "");
        }

        obj_Release(pArgV);
        pArgV = OBJ_NIL;

        obj_Release(pObj);
        pObj = OBJ_NIL;
    }

    fprintf(stderr, "...%s completed.\n\n\n", pTestName);
    return eRc;
}



ERESULT         Test_Appl_Test05 (
    TEST_DATA       *this,
    const
    char            *pTestName
)
{
    ERESULT         eRc = ERESULT_SUCCESS;
    APPL_DATA       *pObj = OBJ_NIL;
    bool            fRc;

    fprintf(stderr, "Performing: %s\n", pTestName);

    pObj = Appl_New( );
    TestForNotNull(pObj, "Missing Test object");
    if (pObj) {

        //obj_TraceSet(pObj, true);
        fRc = obj_IsKindOf(pObj, OBJ_IDENT_APPL);
        TestForTrue(fRc, "Failed Ident Test");
#ifdef   APPL_MSGS
        Appl_setMsg(pObj, (void *)Test_MsgInfo, (void *)Test_MsgWarn, this);
#endif

        fRc = Appl_setArgDefs(pObj, pPgmArgs1);
        TestForTrue(fRc, "");

        Appl_UsageNoMsg(pObj);

        obj_Release(pObj);
        pObj = OBJ_NIL;
    }

    fprintf(stderr, "...%s completed.\n\n\n", pTestName);
    return eRc;
}



ERESULT         Test_Appl_Test06 (
    TEST_DATA       *this,
    const
    char            *pTestName
)
{
    ERESULT         eRc = ERESULT_SUCCESS;
    APPL_DATA       *pObj = OBJ_NIL;
    bool            fRc;
    int             iRc;
    ASTR_DATA       *pStr = OBJ_NIL;
    OBJ_ID          pProp;
   
    fprintf(stderr, "Performing: %s - Checking Properties\n", pTestName);

    pObj = Appl_New( );
    TestForNotNull(pObj, "Missing Test object");
    if (pObj) {

        obj_TraceSet(pObj, true);
        fRc = obj_IsKindOf(pObj, OBJ_IDENT_APPL);
        TestForTrue(fRc, "Failed Ident Test");
#ifdef   APPL_MSGS
        Appl_setMsg(pObj, (void *)Test_MsgInfo, (void *)Test_MsgWarn, this);
#endif
        Appl_setArgDefs(pObj, pPgmArgs1);

        pStr = AStr_NewA("a");
        TestForNotNull(pStr, "");
        fRc = obj_IsKindOf(pStr, OBJ_IDENT_ASTR);
        TestForTrue(fRc, "");
        eRc = Appl_PropertyAddA(pObj, "1", pStr);
        TestForSuccess("");
        fRc = Appl_PropertyExistsA(pObj, "1");
        TestForTrue(fRc, "");
        pProp = Appl_PropertyFindA(pObj, "1");
        TestForNotNull(pProp, "");
        fRc = obj_IsKindOf(pProp, OBJ_IDENT_ASTR);
        TestForTrue(fRc, "");
        iRc = AStr_CompareA(pProp, "a");
        TestForTrue((0 == iRc), "");
        obj_Release(pStr);
        pStr = OBJ_NIL;

        pStr = AStr_NewA("b");
        TestForNotNull(pStr, "");
        fRc = obj_IsKindOf(pStr, OBJ_IDENT_ASTR);
        TestForTrue(fRc, "");
        eRc = Appl_PropertyAddA(pObj, "2", pStr);
        TestForSuccess("");
        fRc = Appl_PropertyExistsA(pObj, "2");
        TestForTrue(fRc, "");
        pProp = Appl_PropertyFindA(pObj, "2");
        TestForNotNull(pProp, "");
        fRc = obj_IsKindOf(pProp, OBJ_IDENT_ASTR);
        TestForTrue(fRc, "");
        iRc = AStr_CompareA(pProp, "b");
        TestForTrue((0 == iRc), "");
        obj_Release(pStr);
        pStr = OBJ_NIL;

        eRc = Appl_PropertyAddA(pObj, "3", pStr);
        TestForSuccess("");
        pProp = Appl_PropertyFindA(pObj, "3");
        TestForNull(pProp, "");
        fRc = Appl_PropertyExistsA(pObj, "3");
        TestForTrue(fRc, "");

        {
            ASTR_DATA       *pStr = Appl_ToDebugString(pObj, 4);
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
    TestExec("OpenClose", Test_Appl_OpenClose, NULL, NULL);
    //TestExec("Copy01", Test_Appl_Copy01, NULL, NULL);
    TestExec("Test01", Test_Appl_Test01, NULL, NULL);
    TestExec("Test02", Test_Appl_Test02, NULL, NULL);
    TestExec("Test03", Test_Appl_Test03, NULL, NULL);
    TestExec("Test04", Test_Appl_Test04, NULL, NULL);
    TestExec("Test05", Test_Appl_Test05, NULL, NULL);
    TestExec("Test06", Test_Appl_Test06, NULL, NULL);

    obj_Release(pTest);
    pTest = OBJ_NIL;

    // Return to Operating System.
    return 0;
}



