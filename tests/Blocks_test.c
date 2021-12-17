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
#include    <Blocks_internal.h>
#include    <JsonIn.h>
#include    <SrcErrors.h>
#include    <szTbl.h>



static
char    *pStringTable[] = {
//   1234567890
    "iryna",
    "rain",
    "clouds",
    "sun",
    "now",
    "xray",
    "before",
    "after",
    "bob",
//   1234567890
    "tomorrow",
    "today",
    "someday"
};
static
int             cStringTable = (sizeof(pStringTable) / sizeof(char *));





ERESULT         Test_Blocks_OpenClose (
    TEST_DATA       *this,
    const
    char            *pTestName
)
{
    ERESULT         eRc = ERESULT_SUCCESS;
    BLOCKS_DATA       *pObj = OBJ_NIL;
    bool            fRc;
   
    fprintf(stderr, "Performing: %s\n", pTestName);

    pObj = Blocks_Alloc( );
    TestForNotNull(pObj, "Missing Test Alloc() object");
    pObj = Blocks_Init( pObj );
    TestForNotNull(pObj, "Missing Test Init() object");
    if (pObj) {

        //obj_TraceSet(pObj, true);       
        fRc = obj_IsKindOf(pObj, OBJ_IDENT_BLOCKS);
        TestForTrue(fRc, "Failed Ident Test");
#ifdef   BLOCKS_MSGS
        Blocks_setMsg(pObj, (void *)Test_MsgInfo, (void *)Test_MsgWarn, this);
#endif
        
        // Test something.
        TestForSuccess("test failed");

        obj_Release(pObj);
        pObj = OBJ_NIL;
    }

    fprintf(stderr, "...%s completed.\n\n\n", pTestName);
    return eRc;
}



ERESULT         Test_Blocks_Copy01 (
    TEST_DATA       *this,
    const
    char            *pTestName
)
{
    ERESULT         eRc = ERESULT_SUCCESS;
    BLOCKS_DATA       *pObj1 = OBJ_NIL;
    BLOCKS_DATA       *pObj2 = OBJ_NIL;
    bool            fRc;
#if defined(BLOCKS_JSON_SUPPORT) && defined(XYZZY)
    ASTR_DATA       *pStr = OBJ_NIL;
#endif
    //int             iRc;
   
    fprintf(stderr, "Performing: %s\n", pTestName);

    pObj1 = Blocks_New( );
    TestForNotNull(pObj1, "Missing Test object");
    if (pObj1) {

        //obj_TraceSet(pObj1, true);       
        fRc = obj_IsKindOf(pObj1, OBJ_IDENT_BLOCKS);
        TestForTrue(fRc, "Failed Ident Test");
#ifdef   BLOCKS_MSGS
        Blocks_setMsg(pObj1, (void *)Test_MsgInfo, (void *)Test_MsgWarn, this);
#endif
        
        // Test assign.
        pObj2 = Blocks_New();
        TestForNotNull(pObj2, "Missing copied object");
        eRc = Blocks_Assign(pObj1, pObj2);
        TestForFalse((ERESULT_FAILED(eRc)), "Assignment failed");

        fRc = obj_IsKindOf(pObj2, OBJ_IDENT_BLOCKS);
        TestForTrue(fRc, "Failed Ident Test");
        //iRc = Blocks_Compare(pObj1, pObj2);
        //TestForTrue((0 == iRc), "Failed Compare");
        //TODO: Add More tests here!

        obj_Release(pObj2);
        pObj2 = OBJ_NIL;

        // Test copy.
        pObj2 = Blocks_Copy(pObj1);
        TestForNotNull(pObj2, "Missing copied object");

        fRc = obj_IsKindOf(pObj2, OBJ_IDENT_BLOCKS);
        TestForTrue(fRc, "Failed Ident Test");
        //iRc = Blocks_Compare(pObj1, pObj2);
        //TestForTrue((0 == iRc), "Failed Compare");
        //TODO: Add More tests here!

        obj_Release(pObj2);
        pObj2 = OBJ_NIL;

        // Test json support.
#if defined(BLOCKS_JSON_SUPPORT) && defined(XYZZY)
        pStr = Blocks_ToJson(pObj1);
        TestForNotNull(pStr, "Missing JSON output");
        fprintf(stderr, "JSON: %s\n", AStr_getData(pStr));
        pObj2 = Blocks_NewFromJsonString(pStr);
        TestForNotNull(pObj2, "Missing JSON created object");
        fRc = obj_IsKindOf(pObj2, OBJ_IDENT_BLOCKS);
        TestForTrue(fRc, "Failed Ident Test");
        obj_Release(pStr);
        pStr = OBJ_NIL;
        //iRc = Blocks_Compare(pObj1, pObj2);
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



ERESULT         Test_Blocks_Test01 (
    TEST_DATA       *this,
    const
    char            *pTestName
)
{
    ERESULT         eRc = ERESULT_SUCCESS;
    BLOCKS_DATA     *pObj = OBJ_NIL;
    bool            fRc;
   
    fprintf(stderr, "Performing: %s\n", pTestName);

    pObj = Blocks_New( );
    TestForNotNull(pObj, "Missing Test object");
    if (pObj) {

        //obj_TraceSet(pObj, true);       
        fRc = obj_IsKindOf(pObj, OBJ_IDENT_BLOCKS);
        TestForTrue(fRc, "Failed Ident Test");
        TestForSuccess("");
#ifdef   BLOCKS_LOG
        Blocks_setLog(pObj, this);
#endif
                
        {
            ASTR_DATA       *pStr = Blocks_ToDebugString(pObj, 4);
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



ERESULT         Test_Blocks_Test02 (
    TEST_DATA       *this,
    const
    char            *pTestName
)
{
    ERESULT         eRc = ERESULT_SUCCESS;
    BLOCKS_DATA     *pObj = OBJ_NIL;
    bool            fRc;
    void            *pRcd1 = NULL;
    void            *pRcd2 = NULL;
    void            *pRcd3 = NULL;
    void            *pRcd4 = NULL;
    void            *pWrk;
    uint8_t         *pRcds[8] = {NULL};
    uint32_t        cRcds = 0;
    uint32_t        unique = 0;
   
    fprintf(stderr, "Performing: %s\n", pTestName);

    pObj = Blocks_New( );
    TestForNotNull(pObj, "Missing Test object");
    if (pObj) {

        //obj_TraceSet(pObj, true);       
        fRc = obj_IsKindOf(pObj, OBJ_IDENT_BLOCKS);
        TestForTrue(fRc, "Failed Ident Test");
        TestForSuccess("");
#ifdef   BLOCKS_LOG
        Blocks_setLog(pObj, this);
#endif
                
        eRc = Blocks_SetupSizes(pObj, 0, 32);
        TestForSuccess("");
        fprintf(stderr, "\tBlockSize  = %d\n", Blocks_getBlockSize(pObj));
        TestForTrue((4096 == Blocks_getBlockSize(pObj)), "");
        fprintf(stderr, "\tBlockAvail = %d\n", Blocks_getBlockAvail(pObj));
        TestForTrue((4080 == Blocks_getBlockAvail(pObj)), "");
        fprintf(stderr, "\tRecordSize  = %d\n", Blocks_getRecordSize(pObj));
#if defined(__MACOSX_ENV__)
        TestForTrue((48 == Blocks_getRecordSize(pObj)), "");
#endif
#if defined(__WIN32_ENV__)
        TestForTrue((36 == Blocks_getRecordSize(pObj)), "");
#endif
#if defined(__WIN64_ENV__)
        TestForTrue((48 == Blocks_getRecordSize(pObj)), "");
#endif
        fprintf(stderr, "\tRecordsPerBlock  = %d\n", Blocks_getRecordsPerBlock(pObj));
#if defined(__MACOSX_ENV__)
        TestForTrue((85 == Blocks_getRecordsPerBlock(pObj)), "");
#endif
#if defined(__WIN32_ENV__)
        TestForTrue((127 == Blocks_getRecordsPerBlock(pObj)), "");
#endif
#if defined(__WIN64_ENV__)
        TestForTrue((85 == Blocks_getRecordsPerBlock(pObj)), "");
#endif

        pRcd1 = Blocks_RecordNew(pObj, &unique);
        TestForTrue((1 == unique), "");
        pWrk = pObj->blocks.pHead;
        fprintf(stderr, "\tBlock 1  = %p\n", pWrk);
        fprintf(stderr, "\tRecord 1  = %p\n", pRcd1);
        fprintf(stderr, "\tOffset 1  = %d\n", (int)(pRcd1 - pWrk));
#if defined(__MACOSX_ENV__)
        TestForTrue((32 == (int)(pRcd1 - pWrk)), "");
#endif
#if defined(__WIN32_ENV__)
        TestForTrue((20 == (int)(pRcd1 - pWrk)), "");
#endif
#if defined(__WIN64_ENV__)
        TestForTrue((32 == (int)(pRcd1 - pWrk)), "");
#endif
        pRcd2 = Blocks_RecordNew(pObj, &unique);
        TestForTrue((2 == unique), "");
        fprintf(stderr, "\tRecord 2  = %p\n", pRcd2);
        fprintf(stderr, "\tOffset 2  = %d\n", (int)(pRcd2 - pWrk));
#if defined(__MACOSX_ENV__)
        TestForTrue((80 == (int)(pRcd2 - pWrk)), "");
#endif
#if defined(__WIN32_ENV__)
        TestForTrue((52 == (int)(pRcd2 - pWrk)), "");
#endif
#if defined(__WIN64_ENV__)
        TestForTrue((80 == (int)(pRcd2 - pWrk)), "");
#endif
        pRcd3 = Blocks_RecordNew(pObj, &unique);
        TestForTrue((3 == unique), "");
        fprintf(stderr, "\tRecord 3  = %p\n", pRcd3);
        eRc = Blocks_RecordFree(pObj, pRcd2);
        TestForSuccess("");
        fprintf(stderr, "\tFreed Record 2  = %p\n", pRcd2);
        pRcd4 = Blocks_RecordNew(pObj, &unique);
        TestForTrue((4 == unique), "");
        fprintf(stderr, "\tRecord 4  = %p\n", pRcd4);
        TestForTrue((pRcd2 == pRcd4), "");
        pRcd2 = NULL;

        {
            ASTR_DATA       *pStr = Blocks_ToDebugString(pObj, 4);
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



ERESULT         Test_Blocks_Test03 (
    TEST_DATA       *this,
    const
    char            *pTestName
)
{
    ERESULT         eRc = ERESULT_SUCCESS;
    BLOCKS_DATA     *pObj = OBJ_NIL;
    bool            fRc;
    int             iRc;
    int             i;
    void            *pRcd1 = NULL;
    void            *pRcd2 = NULL;
    uint32_t        cRcds = 0;
    uint32_t        unique = 0;
   
    fprintf(stderr, "Performing: %s\n", pTestName);

    pObj = Blocks_New( );
    TestForNotNull(pObj, "Missing Test object");
    if (pObj) {

        //obj_TraceSet(pObj, true);       
        fRc = obj_IsKindOf(pObj, OBJ_IDENT_BLOCKS);
        TestForTrue(fRc, "Failed Ident Test");
        TestForSuccess("");
#ifdef   BLOCKS_LOG
        Blocks_setLog(pObj, this);
#endif
                
        eRc = Blocks_SetupSizes(pObj, 0, 16);
        TestForSuccess("");
        eRc = Blocks_SetupIndex(pObj);
        TestForSuccess("");

        for (i=0; i<cStringTable; i++) {
            fprintf(stderr, "\tAdding %s\n", pStringTable[i]);
            pRcd1 = Blocks_RecordNew(pObj, &unique);
            TestForTrue((i+1 == unique), "");
            strcpy(pRcd1, pStringTable[i]);
            {
                ASTR_DATA       *pStr = Blocks_ToDebugString(pObj, 4);
                if (pStr) {
                    fprintf(stderr, "Debug: %s\n", AStr_getData(pStr));
                    obj_Release(pStr);
                    pStr = OBJ_NIL;
                }
            }
            pRcd2 = Blocks_RecordGetUnique(pObj, i+1);
            TestForNotNull(pRcd2, "");
            fprintf(
                    stderr,
                    "\trcd1:%p %s   rcd2:%p %s\n",
                    pRcd1,
                    (char *)pRcd1,
                    pRcd2,
                    (char *)pRcd2
            );
            iRc = strcmp(pRcd1, pRcd2);
            TestForTrue((0 == iRc), "");
        }

        {
            ASTR_DATA       *pStr = Blocks_ToDebugString(pObj, 4);
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



ERESULT         Test_Blocks_Test04 (
    TEST_DATA       *this,
    const
    char            *pTestName
)
{
    ERESULT         eRc = ERESULT_SUCCESS;
    BLOCKS_DATA     *pObj = OBJ_NIL;
    bool            fRc;
   
    fprintf(stderr, "Performing: %s\n", pTestName);

    pObj = Blocks_New( );
    TestForNotNull(pObj, "Missing Test object");
    if (pObj) {

        //obj_TraceSet(pObj, true);       
        fRc = obj_IsKindOf(pObj, OBJ_IDENT_BLOCKS);
        TestForTrue(fRc, "Failed Ident Test");
        TestForSuccess("");
#ifdef   BLOCKS_LOG
        Blocks_setLog(pObj, this);
#endif
                
        {
            ASTR_DATA       *pStr = Blocks_ToDebugString(pObj, 4);
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
    TestExec("OpenClose", Test_Blocks_OpenClose, NULL, NULL);
    //TestExec("Copy01", Test_Blocks_Copy01, NULL, NULL);
    TestExec("Test01", Test_Blocks_Test01, NULL, NULL);
    TestExec("Test02", Test_Blocks_Test02, NULL, NULL);
    TestExec("Test03", Test_Blocks_Test03, NULL, NULL);
    TestExec("Test04", Test_Blocks_Test04, NULL, NULL);

    obj_Release(pTest);
    pTest = OBJ_NIL;

    // Return to Operating System.
    return 0;
}



