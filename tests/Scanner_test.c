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
#include    <Scanner_internal.h>
#include    <JsonIn.h>
#include    <SrcErrors.h>
#include    <szTbl.h>






ERESULT         Test_Scanner_OpenClose (
    TEST_DATA       *this,
    const
    char            *pTestName
)
{
    ERESULT         eRc = ERESULT_SUCCESS;
    SCANNER_DATA       *pObj = OBJ_NIL;
    bool            fRc;
   
    fprintf(stderr, "Performing: %s\n", pTestName);

    pObj = Scanner_Alloc( );
    TestForNotNull(pObj, "Missing Test Alloc() object");
    pObj = Scanner_Init( pObj );
    TestForNotNull(pObj, "Missing Test Init() object");
    if (pObj) {

        //obj_TraceSet(pObj, true);       
        fRc = obj_IsKindOf(pObj, OBJ_IDENT_SCANNER);
        TestForTrue(fRc, "Failed Ident Test");
        
        // Test something.
        TestForSuccess("test failed");

        obj_Release(pObj);
        pObj = OBJ_NIL;
    }

    fprintf(stderr, "...%s completed.\n\n\n", pTestName);
    return eRc;
}



ERESULT         Test_Scanner_Copy01 (
    TEST_DATA       *this,
    const
    char            *pTestName
)
{
    ERESULT         eRc = ERESULT_SUCCESS;
    SCANNER_DATA       *pObj1 = OBJ_NIL;
    SCANNER_DATA       *pObj2 = OBJ_NIL;
    bool            fRc;
#if defined(SCANNER_JSON_SUPPORT) && defined(XYZZY)
    ASTR_DATA       *pStr = OBJ_NIL;
#endif
    //int             iRc;
   
    fprintf(stderr, "Performing: %s\n", pTestName);

    pObj1 = Scanner_New( );
    TestForNotNull(pObj1, "Missing Test object");
    if (pObj1) {

        //obj_TraceSet(pObj1, true);       
        fRc = obj_IsKindOf(pObj1, OBJ_IDENT_SCANNER);
        TestForTrue(fRc, "Failed Ident Test");
        
        // Test assign.
        pObj2 = Scanner_New();
        TestForNotNull(pObj2, "Missing copied object");
        eRc = Scanner_Assign(pObj1, pObj2);
        TestForFalse((ERESULT_FAILED(eRc)), "Assignment failed");

        fRc = obj_IsKindOf(pObj2, OBJ_IDENT_SCANNER);
        TestForTrue(fRc, "Failed Ident Test");
        //iRc = Scanner_Compare(pObj1, pObj2);
        //TestForTrue((0 == iRc), "Failed Compare");
        //TODO: Add More tests here!

        obj_Release(pObj2);
        pObj2 = OBJ_NIL;

        // Test copy.
        pObj2 = Scanner_Copy(pObj1);
        TestForNotNull(pObj2, "Missing copied object");

        fRc = obj_IsKindOf(pObj2, OBJ_IDENT_SCANNER);
        TestForTrue(fRc, "Failed Ident Test");
        //iRc = Scanner_Compare(pObj1, pObj2);
        //TestForTrue((0 == iRc), "Failed Compare");
        //TODO: Add More tests here!

        obj_Release(pObj2);
        pObj2 = OBJ_NIL;

        // Test json support.
#if defined(SCANNER_JSON_SUPPORT) && defined(XYZZY)
        pStr = Scanner_ToJson(pObj1);
        TestForNotNull(pStr, "Missing JSON output");
        fprintf(stderr, "JSON: %s\n", AStr_getData(pStr));
        pObj2 = Scanner_NewFromJsonString(pStr);
        TestForNotNull(pObj2, "Missing JSON created object");
        fRc = obj_IsKindOf(pObj2, OBJ_IDENT_SCANNER);
        TestForTrue(fRc, "Failed Ident Test");
        obj_Release(pStr);
        pStr = OBJ_NIL;
        //iRc = Scanner_Compare(pObj1, pObj2);
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



ERESULT         Test_Scanner_Test01 (
    TEST_DATA       *this,
    const
    char            *pTestName
)
{
    ERESULT         eRc = ERESULT_SUCCESS;
    SCANNER_DATA    *pObj = OBJ_NIL;
    bool            fRc;
    const
    char            *pTest01A = " 100";
    const
    char            *pTest02A = "-123";
    const
    char            *pTest03A = "+123";
    const
    char            *pTest04A = "0x0A";
    const
    char            *pTest05A = " 100 ";
    const
    char            *pTest06A = " 10,";
    const
    char            *pTest07A = " 0x,";
    const
    char            *pTest08A = " x,";
    const
    char            *pTest09A = " 0277 ";
    int32_t         value = 0;

    fprintf(stderr, "Performing: %s\n", pTestName);
    fprintf(stderr, "\tTest the signed integer 32-bit method...\n");

    pObj = Scanner_New( );
    TestForNotNull(pObj, "Missing Test object");
    if (pObj) {

        //obj_TraceSet(pObj, true);       
        fRc = obj_IsKindOf(pObj, OBJ_IDENT_SCANNER);
        TestForTrue(fRc, "Failed Ident Test");

        value = 0;
        eRc = Scanner_SetupA(pObj, pTest01A);
        TestForSuccess("");
        fRc = Scanner_ScanInteger32(pObj, &value);
        TestForTrue(fRc, "");
        TestForTrue((4 == obj_getMisc(pObj)), "");
        TestForTrue((100 == value), "");

        value = 0;
        eRc = Scanner_SetupA(pObj, pTest02A);
        TestForSuccess("");
        fRc = Scanner_ScanInteger32(pObj, &value);
        TestForTrue(fRc, "");
        TestForTrue((4 == obj_getMisc(pObj)), "");
        TestForTrue((-123 == value), "");

        value = 0;
        eRc = Scanner_SetupA(pObj, pTest03A);
        TestForSuccess("");
        fRc = Scanner_ScanInteger32(pObj, &value);
        TestForTrue(fRc, "");
        TestForTrue((4 == obj_getMisc(pObj)), "");
        TestForTrue((123 == value), "");

        value = 0;
        eRc = Scanner_SetupA(pObj, pTest04A);
        TestForSuccess("");
        fRc = Scanner_ScanInteger32(pObj, &value);
        TestForTrue(fRc, "");
        TestForTrue((4 == obj_getMisc(pObj)), "");
        TestForTrue((10 == value), "");

        value = 0;
        eRc = Scanner_SetupA(pObj, pTest05A);
        TestForSuccess("");
        fRc = Scanner_ScanInteger32(pObj, &value);
        TestForTrue(fRc, "");
        TestForTrue((4 == obj_getMisc(pObj)), "");
        TestForTrue((100 == value), "");

        value = 0;
        eRc = Scanner_SetupA(pObj, pTest06A);
        TestForSuccess("");
        fRc = Scanner_ScanInteger32(pObj, &value);
        TestForTrue(fRc, "");
        //fprintf(stderr, "\tScan end: %d\n", obj_getMisc(pObj));
        TestForTrue((3 == obj_getMisc(pObj)), "");
        TestForTrue((10 == value), "");

        value = 0;
        eRc = Scanner_SetupA(pObj, pTest07A);
        TestForSuccess("");
        fRc = Scanner_ScanInteger32(pObj, &value);
        TestForTrue(!fRc, "");
        //fprintf(stderr, "\tScan end: %d\n", obj_getMisc(pObj));
        TestForTrue((1 == obj_getMisc(pObj)), "");
        TestForTrue((0 == value), "");

        value = 0;
        eRc = Scanner_SetupA(pObj, pTest08A);
        TestForSuccess("");
        fRc = Scanner_ScanInteger32(pObj, &value);
        TestForTrue(!fRc, "");
        //fprintf(stderr, "\tScan end: %d\n", obj_getMisc(pObj));
        TestForTrue((1 == obj_getMisc(pObj)), "");
        TestForTrue((0 == value), "");

        value = 0;
        eRc = Scanner_SetupA(pObj, pTest09A);
        TestForSuccess("");
        fRc = Scanner_ScanInteger32(pObj, &value);
        TestForTrue(fRc, "");
        //fprintf(stderr, "\tScan end: %d\n", obj_getMisc(pObj));
        TestForTrue((5 == obj_getMisc(pObj)), "");
        TestForTrue((191 == value), "");

        value = 0;
        eRc = Scanner_SetupA(pObj, " 0123 ");
        TestForSuccess("");
        fRc = Scanner_ScanInteger32(pObj, &value);
        TestForTrue(fRc, "");
        //fprintf(stderr, "\tScan end: %d\n", obj_getMisc(pObj));
        TestForTrue((5 == obj_getMisc(pObj)), "");
        TestForTrue((83 == value), "");

        {
            ASTR_DATA       *pStr = Scanner_ToDebugString(pObj, 4);
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



ERESULT         Test_Scanner_Test02 (
    TEST_DATA       *this,
    const
    char            *pTestName
)
{
    ERESULT         eRc = ERESULT_SUCCESS;
    SCANNER_DATA    *pObj = OBJ_NIL;
    bool            fRc;
    ASTR_DATA       *pStr = OBJ_NIL;
    W32CHR_T        chrw32;

    fprintf(stderr, "Performing: %s\n", pTestName);
    fprintf(stderr, "\tTest the internal string scan method...\n");

    pObj = Scanner_New( );
    TestForNotNull(pObj, "Missing Test object");
    if (pObj) {

        eRc = Scanner_SetupA(pObj, " abc ");
        TestForSuccess("");
        pStr = Scanner_ScanStringToAStrInt(pObj, false);
        TestForNotNull(pStr, "");
        //fprintf(stderr, "\tScan end: %d\n", obj_getMisc(pObj));
        TestForTrue((5 == obj_getMisc(pObj)), "");
        TestForTrue((0 == AStr_CompareA(pStr, "abc ")), "");
        obj_Release(pStr);
        pStr = OBJ_NIL;

        eRc = Scanner_SetupA(pObj, " abc ");
        TestForSuccess("");
        pStr = Scanner_ScanStringToAStrInt(pObj, true);
        TestForNotNull(pStr, "");
        //fprintf(stderr, "\tScan end: %d\n", obj_getMisc(pObj));
        TestForTrue((4 == obj_getMisc(pObj)), "");
        TestForTrue((0 == AStr_CompareA(pStr, "abc")), "");
        obj_Release(pStr);
        pStr = OBJ_NIL;
        chrw32 = Scanner_LookAhead(pObj, 1);
        TestForTrue((' ' == chrw32), "");

        eRc = Scanner_SetupA(pObj, " \"abc \" ");
        TestForSuccess("");
        pStr = Scanner_ScanStringToAStrInt(pObj, false);
        TestForNotNull(pStr, "");
        //fprintf(stderr, "\tScan end: %d\n", obj_getMisc(pObj));
        TestForTrue((7 == obj_getMisc(pObj)), "");
        TestForTrue((0 == AStr_CompareA(pStr, "abc ")), "");
        obj_Release(pStr);
        pStr = OBJ_NIL;

        eRc = Scanner_SetupA(pObj, " \"abc \",");
        TestForSuccess("");
        pStr = Scanner_ScanStringToAStrInt(pObj, true);
        TestForNotNull(pStr, "");
        //fprintf(stderr, "\tScan end: %d\n", obj_getMisc(pObj));
        TestForTrue((7 == obj_getMisc(pObj)), "");
        TestForTrue((0 == AStr_CompareA(pStr, "abc ")), "");
        obj_Release(pStr);
        pStr = OBJ_NIL;
        chrw32 = Scanner_LookAhead(pObj, 1);
        TestForTrue((',' == chrw32), "");

        obj_Release(pObj);
        pObj = OBJ_NIL;
    }

    fprintf(stderr, "...%s completed.\n\n\n", pTestName);
    return eRc;
}



ERESULT         Test_Scanner_Test03 (
    TEST_DATA       *this,
    const
    char            *pTestName
)
{
    ERESULT         eRc = ERESULT_SUCCESS;
    SCANNER_DATA    *pObj = OBJ_NIL;
    bool            fRc;
    ASTR_DATA       *pStr = OBJ_NIL;

    fprintf(stderr, "Performing: %s\n", pTestName);
    fprintf(stderr, "\tTest the idenifier scan method...\n");

    pObj = Scanner_New( );
    TestForNotNull(pObj, "Missing Test object");
    if (pObj) {

        //obj_TraceSet(pObj, true);
        fRc = obj_IsKindOf(pObj, OBJ_IDENT_SCANNER);
        TestForTrue(fRc, "Failed Ident Test");

        eRc = Scanner_SetupA(pObj, " abc123 ");
        TestForSuccess("");
        pStr = Scanner_ScanIdentifierToAStr(pObj);
        TestForNotNull(pStr, "");
        fprintf(stderr, "\tScan end: %d\n", obj_getMisc(pObj));
        TestForTrue((7 == obj_getMisc(pObj)), "");
        TestForTrue((0 == AStr_CompareA(pStr, "abc123")), "");
        obj_Release(pStr);
        pStr = OBJ_NIL;

        eRc = Scanner_SetupA(pObj, " 0abc123 ");
        TestForSuccess("");
        pStr = Scanner_ScanIdentifierToAStr(pObj);
        TestForNull(pStr, "");
        fprintf(stderr, "\tScan end: %d\n", obj_getMisc(pObj));
        TestForTrue((1 == obj_getMisc(pObj)), "");
        //TestForTrue((0 == AStr_CompareA(pStr, "abc123")), "");
        //obj_Release(pStr);
        //pStr = OBJ_NIL;

        {
            ASTR_DATA       *pStr = Scanner_ToDebugString(pObj, 4);
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



ERESULT         Test_Scanner_Test04 (
    TEST_DATA       *this,
    const
    char            *pTestName
)
{
    ERESULT         eRc = ERESULT_SUCCESS;
    SCANNER_DATA    *pObj = OBJ_NIL;
    bool            fRc;
    ASTR_DATA       *pStr = OBJ_NIL;
    ASTRARRAY_DATA  *pArray = OBJ_NIL;

    fprintf(stderr, "Performing: %s\n", pTestName);
    fprintf(stderr, "\tTest the AStr Array method...\n");

    pObj = Scanner_New( );
    TestForNotNull(pObj, "Missing Test object");
    if (pObj) {

        //obj_TraceSet(pObj, true);
        fRc = obj_IsKindOf(pObj, OBJ_IDENT_SCANNER);
        TestForTrue(fRc, "Failed Ident Test");

        fprintf(stderr, "\tTest:\"%s\"\n", " a b ");
        eRc = Scanner_SetupA(pObj, " a b ");
        TestForSuccess("");
        pArray = Scanner_ScanStringToAstrArray(pObj);
        TestForNotNull(pArray, "");
        fprintf(stderr, "\tScan end: %d\n", obj_getMisc(pObj));
        TestForTrue((5 == obj_getMisc(pObj)), "");
        fprintf(stderr, "\tArray size: %d\n", AStrArray_getSize(pArray));
        TestForTrue((3 == AStrArray_getSize(pArray)), "");
        pStr = AStrArray_Get(pArray, 1);
        TestForNotNull(pStr, "");
        fprintf(stderr, "\tArray 1: \"%s\"\n", AStr_getData(pStr));
        TestForTrue((0 == AStr_CompareA(pStr, "")), "");
        pStr = AStrArray_Get(pArray, 2);
        TestForNotNull(pStr, "");
        fprintf(stderr, "\tArray 2: \"%s\"\n", AStr_getData(pStr));
        TestForTrue((0 == AStr_CompareA(pStr, "a")), "");
        pStr = AStrArray_Get(pArray, 3);
        TestForNotNull(pStr, "");
        fprintf(stderr, "\tArray 3: \"%s\"\n", AStr_getData(pStr));
        TestForTrue((0 == AStr_CompareA(pStr, "b")), "");
        obj_Release(pArray);
        pArray = OBJ_NIL;

        {
            ASTR_DATA       *pStr = Scanner_ToDebugString(pObj, 4);
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



ERESULT         Test_Scanner_Test05 (
    TEST_DATA       *this,
    const
    char            *pTestName
)
{
    ERESULT         eRc = ERESULT_SUCCESS;
    SCANNER_DATA    *pObj = OBJ_NIL;
    bool            fRc;
    int32_t         value;

    fprintf(stderr, "Performing: %s\n", pTestName);
    fprintf(stderr, "\tTesting Expression scanning...\n");

    pObj = Scanner_New( );
    TestForNotNull(pObj, "Missing Test object");
    if (pObj) {

        //obj_TraceSet(pObj, true);
        fRc = obj_IsKindOf(pObj, OBJ_IDENT_SCANNER);
        TestForTrue(fRc, "Failed Ident Test");

        value = 0;
        fprintf(stderr, "\tInput: \"%s\"\n", "2*5+1");
        eRc = Scanner_SetupA(pObj, "2*5+1,");
        TestForSuccess("");
        eRc = Scanner_ScanExpr(pObj, &value);
        TestForSuccess("");
        fprintf(stderr, "\tScan end: %d\n", obj_getMisc(pObj));
        TestForTrue((5 == obj_getMisc(pObj)), "");
        fprintf(stderr, "\tValue: %d\n\n", value);
        TestForTrue((11 == value), "");

        value = 0;
        fprintf(stderr, "\tInput: \"%s\"\n", "1+2*5");
        eRc = Scanner_SetupA(pObj, "1+2*5 ");
        TestForSuccess("");
        eRc = Scanner_ScanExpr(pObj, &value);
        TestForSuccess("");
        fprintf(stderr, "\tScan end: %d\n", obj_getMisc(pObj));
        TestForTrue((5 == obj_getMisc(pObj)), "");
        fprintf(stderr, "\tValue: %d\n\n", value);
        TestForTrue((11 == value), "");

        value = 0;
        fprintf(stderr, "\tInput: \"%s\"\n", "1+(2*5)");
        eRc = Scanner_SetupA(pObj, "1+(2*5) ");
        TestForSuccess("");
        eRc = Scanner_ScanExpr(pObj, &value);
        TestForSuccess("");
        fprintf(stderr, "\tScan end: %d\n", obj_getMisc(pObj));
        TestForTrue((7 == obj_getMisc(pObj)), "");
        fprintf(stderr, "\tValue: %d\n\n", value);
        TestForTrue((11 == value), "");

        value = 0;
        fprintf(stderr, "\tInput: \"%s\"\n", "(1+2)*5,");
        eRc = Scanner_SetupA(pObj, "(1+2)*5 ");
        TestForSuccess("");
        eRc = Scanner_ScanExpr(pObj, &value);
        TestForSuccess("");
        fprintf(stderr, "\tScan end: %d\n", obj_getMisc(pObj));
        TestForTrue((7 == obj_getMisc(pObj)), "");
        fprintf(stderr, "\tValue: %d\n\n", value);
        TestForTrue((15 == value), "");

        {
            ASTR_DATA       *pStr = Scanner_ToDebugString(pObj, 4);
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



ERESULT         Test_Scanner_Test06 (
    TEST_DATA       *this,
    const
    char            *pTestName
)
{
    ERESULT         eRc = ERESULT_SUCCESS;
    SCANNER_DATA    *pObj = OBJ_NIL;
    bool            fRc;

    fprintf(stderr, "Performing: %s\n", pTestName);

    pObj = Scanner_New( );
    TestForNotNull(pObj, "Missing Test object");
    if (pObj) {

        //obj_TraceSet(pObj, true);
        fRc = obj_IsKindOf(pObj, OBJ_IDENT_SCANNER);
        TestForTrue(fRc, "Failed Ident Test");

        {
            ASTR_DATA       *pStr = Scanner_ToDebugString(pObj, 4);
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
    TestExec("OpenClose", Test_Scanner_OpenClose, NULL, NULL);
    //TestExec("Copy01", Test_Scanner_Copy01, NULL, NULL);
    TestExec("Test01", Test_Scanner_Test01, NULL, NULL);
    TestExec("Test02", Test_Scanner_Test02, NULL, NULL);
    TestExec("Test03", Test_Scanner_Test03, NULL, NULL);
    TestExec("Test04", Test_Scanner_Test04, NULL, NULL);
    TestExec("Test05", Test_Scanner_Test05, NULL, NULL);
    TestExec("Test06", Test_Scanner_Test06, NULL, NULL);

    obj_Release(pTest);
    pTest = OBJ_NIL;

    // Return to Operating System.
    return 0;
}



