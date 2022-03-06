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
#include    <AStrArray_internal.h>
#include    <JsonIn.h>
#include    <SrcErrors.h>
#include    <szTbl.h>






ERESULT         Test_AStrArray_OpenClose (
    TEST_DATA       *this,
    const
    char            *pTestName
)
{
    ERESULT         eRc = ERESULT_SUCCESS;
    ASTRARRAY_DATA  *pObj = OBJ_NIL;
    bool            fRc;
   
    fprintf(stderr, "Performing: %s\n", pTestName);

    pObj = AStrArray_Alloc( );
    TestForNotNull(pObj, "Missing Test Alloc() object");
    pObj = AStrArray_Init( pObj );
    TestForNotNull(pObj, "Missing Test Init() object");
    if (pObj) {

        //obj_TraceSet(pObj, true);       
        fRc = obj_IsKindOf(pObj, OBJ_IDENT_ASTRARRAY);
        TestForTrue(fRc, "Failed Ident Test");
#ifdef   ASTRARRAY_MSGS
        AStrArray_setMsg(pObj, (void *)Test_MsgInfo, (void *)Test_MsgWarn, this);
#endif
        
        // Test something.
        TestForSuccess("test failed");

        obj_Release(pObj);
        pObj = OBJ_NIL;
    }

    fprintf(stderr, "...%s completed.\n\n\n", pTestName);
    return eRc;
}



ERESULT         Test_AStrArray_Copy01 (
    TEST_DATA       *this,
    const
    char            *pTestName
)
{
    ERESULT         eRc = ERESULT_SUCCESS;
    ASTRARRAY_DATA  *pObj1 = OBJ_NIL;
    ASTRARRAY_DATA  *pObj2 = OBJ_NIL;
    bool            fRc;
    ASTR_DATA       *pStr = OBJ_NIL;
    //int             iRc;
    int             cArg = 5;
    const
    char            *pArgV[] ={
        "abc/def/x.txt",
        "jjj",
        "kk",
        "ll",
        "mm"
    };
    ASTR_DATA       *pWrk = OBJ_NIL;
    int             i;
   
    fprintf(stderr, "Performing: %s\n", pTestName);

    pObj1 = AStrArray_NewFromArgV(cArg, pArgV);
    TestForNotNull(pObj1, "Missing Test object");
    if (pObj1) {

        //obj_TraceSet(pObj1, true);       
        fRc = obj_IsKindOf(pObj1, OBJ_IDENT_ASTRARRAY);
        TestForTrue(fRc, "Failed Ident Test");
#ifdef   ASTRARRAY_MSGS
        AStrArray_setMsg(pObj1, (void *)Test_MsgInfo, (void *)Test_MsgWarn, this);
#endif
        i = AStrArray_getSize(pObj1);
        TestForTrue((i == cArg), "");
        pWrk = AStrArray_Get(pObj1, 1);
        TestForFalse( (OBJ_NIL == pWrk), "");
        TestForTrue( (0 == AStr_CompareA(pWrk, "abc/def/x.txt")), "");
        pWrk = AStrArray_Get(pObj1, 2);
        TestForFalse( (OBJ_NIL == pWrk), "");
        TestForTrue( (0 == AStr_CompareA(pWrk, "jjj")), "");
        pWrk = AStrArray_Get(pObj1, 3);
        TestForFalse( (OBJ_NIL == pWrk), "");
        TestForTrue( (0 == AStr_CompareA(pWrk, "kk")), "");
        pWrk = AStrArray_Get(pObj1, 4);
        TestForFalse( (OBJ_NIL == pWrk), "");
        TestForTrue( (0 == AStr_CompareA(pWrk, "ll")), "");
        pWrk = AStrArray_Get(pObj1, 5);
        TestForFalse( (OBJ_NIL == pWrk), "");
        TestForTrue( (0 == AStr_CompareA(pWrk, "mm")), "");
        
        // Test assign.
        pObj2 = AStrArray_New();
        TestForNotNull(pObj2, "Missing copied object");
        eRc = AStrArray_Assign(pObj1, pObj2);
        TestForFalse((ERESULT_FAILED(eRc)), "Assignment failed");

        fRc = obj_IsKindOf(pObj2, OBJ_IDENT_ASTRARRAY);
        TestForTrue(fRc, "Failed Ident Test");
        //iRc = AStrArray_Compare(pObj1, pObj2);
        //TestForTrue((0 == iRc), "Failed Compare");
        i = AStrArray_getSize(pObj2);
        TestForTrue((i == cArg), "");
        pWrk = AStrArray_Get(pObj2, 1);
        TestForFalse( (OBJ_NIL == pWrk), "");
        TestForTrue( (0 == AStr_CompareA(pWrk, "abc/def/x.txt")), "");
        pWrk = AStrArray_Get(pObj2, 2);
        TestForFalse( (OBJ_NIL == pWrk), "");
        TestForTrue( (0 == AStr_CompareA(pWrk, "jjj")), "");
        pWrk = AStrArray_Get(pObj2, 3);
        TestForFalse( (OBJ_NIL == pWrk), "");
        TestForTrue( (0 == AStr_CompareA(pWrk, "kk")), "");
        pWrk = AStrArray_Get(pObj2, 4);
        TestForFalse( (OBJ_NIL == pWrk), "");
        TestForTrue( (0 == AStr_CompareA(pWrk, "ll")), "");
        pWrk = AStrArray_Get(pObj2, 5);
        TestForFalse( (OBJ_NIL == pWrk), "");
        TestForTrue( (0 == AStr_CompareA(pWrk, "mm")), "");

        obj_Release(pObj2);
        pObj2 = OBJ_NIL;

        // Test copy.
        pObj2 = AStrArray_Copy(pObj1);
        TestForNotNull(pObj2, "Missing copied object");

        fRc = obj_IsKindOf(pObj2, OBJ_IDENT_ASTRARRAY);
        TestForTrue(fRc, "Failed Ident Test");
        //iRc = AStrArray_Compare(pObj1, pObj2);
        //TestForTrue((0 == iRc), "Failed Compare");
        i = AStrArray_getSize(pObj2);
        TestForTrue((i == cArg), "");
        pWrk = AStrArray_Get(pObj2, 1);
        TestForFalse( (OBJ_NIL == pWrk), "");
        TestForTrue( (0 == AStr_CompareA(pWrk, "abc/def/x.txt")), "");
        pWrk = AStrArray_Get(pObj2, 2);
        TestForFalse( (OBJ_NIL == pWrk), "");
        TestForTrue( (0 == AStr_CompareA(pWrk, "jjj")), "");
        pWrk = AStrArray_Get(pObj2, 3);
        TestForFalse( (OBJ_NIL == pWrk), "");
        TestForTrue( (0 == AStr_CompareA(pWrk, "kk")), "");
        pWrk = AStrArray_Get(pObj2, 4);
        TestForFalse( (OBJ_NIL == pWrk), "");
        TestForTrue( (0 == AStr_CompareA(pWrk, "ll")), "");
        pWrk = AStrArray_Get(pObj2, 5);
        TestForFalse( (OBJ_NIL == pWrk), "");
        TestForTrue( (0 == AStr_CompareA(pWrk, "mm")), "");

        obj_Release(pObj2);
        pObj2 = OBJ_NIL;

        // Test json support.
        pStr = AStrArray_ToJson(pObj1);
        TestForNotNull(pStr, "Missing JSON output");
        fprintf(stderr, "JSON: %s\n", AStr_getData(pStr));
        pObj2 = AStrArray_NewFromJsonString(pStr);
        TestForNotNull(pObj2, "Missing JSON created object");
        fRc = obj_IsKindOf(pObj2, OBJ_IDENT_ASTRARRAY);
        TestForTrue(fRc, "Failed Ident Test");
        obj_Release(pStr);
        pStr = OBJ_NIL;

        i = AStrArray_getSize(pObj2);
        TestForTrue((i == cArg), "");
        pWrk = AStrArray_Get(pObj2, 1);
        TestForFalse( (OBJ_NIL == pWrk), "");
        TestForTrue( (0 == AStr_CompareA(pWrk, "abc/def/x.txt")), "");
        pWrk = AStrArray_Get(pObj2, 2);
        TestForFalse( (OBJ_NIL == pWrk), "");
        TestForTrue( (0 == AStr_CompareA(pWrk, "jjj")), "");
        pWrk = AStrArray_Get(pObj2, 3);
        TestForFalse( (OBJ_NIL == pWrk), "");
        TestForTrue( (0 == AStr_CompareA(pWrk, "kk")), "");
        pWrk = AStrArray_Get(pObj2, 4);
        TestForFalse( (OBJ_NIL == pWrk), "");
        TestForTrue( (0 == AStr_CompareA(pWrk, "ll")), "");
        pWrk = AStrArray_Get(pObj2, 5);
        TestForFalse( (OBJ_NIL == pWrk), "");
        TestForTrue( (0 == AStr_CompareA(pWrk, "mm")), "");

        obj_Release(pObj2);
        pObj2 = OBJ_NIL;

        obj_Release(pObj1);
        pObj1 = OBJ_NIL;
    }

    fprintf(stderr, "...%s completed.\n\n\n", pTestName);
    return eRc;
}



ERESULT         Test_AStrArray_Test01 (
    TEST_DATA       *this,
    const
    char            *pTestName
)
{
    ERESULT         eRc = ERESULT_SUCCESS;
    ASTRARRAY_DATA  *pObj = OBJ_NIL;
    bool            fRc;
    const
    char            *pArgV[] ={
        "abc/def/x.txt",
        "jjj",
        "kk",
        "ll",
        "mm",
        NULL
    };
    ASTR_DATA       *pStr = OBJ_NIL;
    int             i;
    ASTR_DATA       *pWrk = OBJ_NIL;
    char            **ppArray = NULL;
    char            *pStrA;
   
    fprintf(stderr, "Performing: %s\n", pTestName);

    pObj = AStrArray_NewFromArrayA(pArgV);
    TestForNotNull(pObj, "");
    if (pObj) {

        //obj_TraceSet(pObj, true);       
        fRc = obj_IsKindOf(pObj, OBJ_IDENT_ASTRARRAY);
        TestForFalse(!fRc, "");
        TestForTrue(fRc, "");
#ifdef   ASTRARRAY_MSGS
        AStrArray_setMsg(pObj, (void *)Test_MsgInfo, (void *)Test_MsgWarn, this);
#endif
                
        i = AStrArray_getSize(pObj);
        TestForTrue((i == 5), "");
        pWrk = AStrArray_Get(pObj, 1);
        TestForFalse( (OBJ_NIL == pWrk), "");
        TestForTrue( (0 == AStr_CompareA(pWrk, "abc/def/x.txt")), "");
        pWrk = AStrArray_Get(pObj, 2);
        TestForFalse( (OBJ_NIL == pWrk), "");
        TestForTrue( (0 == AStr_CompareA(pWrk, "jjj")), "");
        pWrk = AStrArray_Get(pObj, 3);
        TestForFalse( (OBJ_NIL == pWrk), "");
        TestForTrue( (0 == AStr_CompareA(pWrk, "kk")), "");
        pWrk = AStrArray_Get(pObj, 4);
        TestForFalse( (OBJ_NIL == pWrk), "");
        TestForTrue( (0 == AStr_CompareA(pWrk, "ll")), "");
        pWrk = AStrArray_Get(pObj, 5);
        TestForFalse( (OBJ_NIL == pWrk), "");
        TestForTrue( (0 == AStr_CompareA(pWrk, "mm")), "");

        ppArray = AStrArray_ToStrArray(pObj);
        TestForNotNull(ppArray, "");
        pStrA = ppArray[0];
        TestForFalse( (NULL == pStrA), "");
        TestForTrue( (0 == strcmp(pStrA, "abc/def/x.txt")), "");
        pStrA = ppArray[1];
        TestForFalse( (NULL == pStrA), "");
        TestForTrue( (0 == strcmp(pStrA, "jjj")), "");
        pStrA = ppArray[2];
        TestForFalse( (NULL == pStrA), "");
        TestForTrue( (0 == strcmp(pStrA, "kk")), "");
        pStrA = ppArray[3];
        TestForFalse( (NULL == pStrA), "");
        TestForTrue( (0 == strcmp(pStrA, "ll")), "");
        pStrA = ppArray[4];
        TestForFalse( (NULL == pStrA), "");
        TestForTrue( (0 == strcmp(pStrA, "mm")), "");
        pStrA = ppArray[5];
        TestForTrue( (NULL == pStrA), "");
        mem_Free(ppArray);
        ppArray = NULL;

        {
            ASTR_DATA       *pStr = AStrArray_ToDebugString(pObj, 4);
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



ERESULT         Test_AStrArray_Test02 (
    TEST_DATA       *this,
    const
    char            *pTestName
)
{
    ERESULT         eRc = ERESULT_SUCCESS;
    ASTRARRAY_DATA  *pObj = OBJ_NIL;
    bool            fRc;
   
    fprintf(stderr, "Performing: %s\n", pTestName);

    pObj = AStrArray_New( );
    TestForNotNull(pObj, "");
    if (pObj) {

        //obj_TraceSet(pObj, true);       
        fRc = obj_IsKindOf(pObj, OBJ_IDENT_ASTRARRAY);
        TestForFalse(!fRc, "");
        TestForTrue(fRc, "");
#ifdef   ASTRARRAY_MSGS
        AStrArray_setMsg(pObj, (void *)Test_MsgInfo, (void *)Test_MsgWarn, this);
#endif
                
        {
            ASTR_DATA       *pStr = AStrArray_ToDebugString(pObj, 4);
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



ERESULT         Test_AStrArray_Test03 (
    TEST_DATA       *this,
    const
    char            *pTestName
)
{
    ERESULT         eRc = ERESULT_SUCCESS;
    ASTRARRAY_DATA  *pObj = OBJ_NIL;
    bool            fRc;
   
    fprintf(stderr, "Performing: %s\n", pTestName);

    pObj = AStrArray_New( );
    TestForNotNull(pObj, "");
    if (pObj) {

        //obj_TraceSet(pObj, true);       
        fRc = obj_IsKindOf(pObj, OBJ_IDENT_ASTRARRAY);
        TestForFalse(!fRc, "");
        TestForTrue(fRc, "");
#ifdef   ASTRARRAY_MSGS
        AStrArray_setMsg(pObj, (void *)Test_MsgInfo, (void *)Test_MsgWarn, this);
#endif
                
        {
            ASTR_DATA       *pStr = AStrArray_ToDebugString(pObj, 4);
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



ERESULT         Test_AStrArray_Test04 (
    TEST_DATA       *this,
    const
    char            *pTestName
)
{
    ERESULT         eRc = ERESULT_SUCCESS;
    ASTRARRAY_DATA  *pObj = OBJ_NIL;
    bool            fRc;
   
    fprintf(stderr, "Performing: %s\n", pTestName);

    pObj = AStrArray_New( );
    TestForNotNull(pObj, "");
    if (pObj) {

        //obj_TraceSet(pObj, true);       
        fRc = obj_IsKindOf(pObj, OBJ_IDENT_ASTRARRAY);
        TestForFalse(!fRc, "");
        TestForTrue(fRc, "");
#ifdef   ASTRARRAY_MSGS
        AStrArray_setMsg(pObj, (void *)Test_MsgInfo, (void *)Test_MsgWarn, this);
#endif
                
        {
            ASTR_DATA       *pStr = AStrArray_ToDebugString(pObj, 4);
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
    TestExec("OpenClose", Test_AStrArray_OpenClose, NULL, NULL);
    //TestExec("Copy01", Test_AStrArray_Copy01, NULL, NULL);
    TestExec("Test01", Test_AStrArray_Test01, NULL, NULL);
    TestExec("Test02", Test_AStrArray_Test02, NULL, NULL);
    TestExec("Test03", Test_AStrArray_Test03, NULL, NULL);
    TestExec("Test04", Test_AStrArray_Test04, NULL, NULL);

    obj_Release(pTest);
    pTest = OBJ_NIL;

    // Return to Operating System.
    return 0;
}



