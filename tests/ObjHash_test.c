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
#include    <ObjHash_internal.h>
#include    <JsonIn.h>
#include    <SrcErrors.h>
#include    <szTbl.h>



static
char    *pStringTable[] = {
    "iryna",
    "rain",
    "now",
    "time",
    "for",
    "all",
    "good",
    "men",
    "come",
    "aid",
    "their",
    "country",
    "sun",
    "moon",
    "mars",
    "mercury",
    "jupiter",
    "saturn",
    "neptune",
    "pluto",
    "clouds",
    "infared",
    "now",
    "xray",
    "before",
    "along",
    "ride",
    "after",
    "bob",
    "tomorrow",
    "today",
    "someday"
};
static
int             cStringTable = (sizeof(pStringTable) / sizeof(char *));






ERESULT         Test_ObjHash_OpenClose (
    TEST_DATA       *this,
    const
    char            *pTestName
)
{
    ERESULT         eRc = ERESULT_SUCCESS;
    OBJHASH_DATA       *pObj = OBJ_NIL;
    bool            fRc;
   
    fprintf(stderr, "Performing: %s\n", pTestName);

    pObj = ObjHash_Alloc( );
    TestForNotNull(pObj, "Missing Test Alloc() object");
    pObj = ObjHash_Init( pObj );
    TestForNotNull(pObj, "Missing Test Init() object");
    if (pObj) {

        //obj_TraceSet(pObj, true);       
        fRc = obj_IsKindOf(pObj, OBJ_IDENT_OBJHASH);
        TestForTrue(fRc, "Failed Ident Test");
#ifdef   OBJHASH_MSGS
        ObjHash_setMsg(pObj, (void *)Test_MsgInfo, (void *)Test_MsgWarn, this);
#endif
        
        // Test something.
        TestForSuccess("test failed");

        obj_Release(pObj);
        pObj = OBJ_NIL;
    }

    fprintf(stderr, "...%s completed.\n\n\n", pTestName);
    return eRc;
}



ERESULT         Test_ObjHash_Copy01 (
    TEST_DATA       *this,
    const
    char            *pTestName
)
{
    ERESULT         eRc = ERESULT_SUCCESS;
    OBJHASH_DATA    *pObj1 = OBJ_NIL;
    OBJHASH_DATA    *pObj2 = OBJ_NIL;
    bool            fRc;
    ASTR_DATA       *pStr = OBJ_NIL;
    //int             iRc;
    uint32_t        i;
    uint32_t        size;
    uint32_t        index;

    fprintf(stderr, "Performing: %s\n", pTestName);

    pObj1 = ObjHash_New( );
    TestForNotNull(pObj1, "Missing Test object");
    if (pObj1) {

        //obj_TraceSet(pObj1, true);       
        fRc = obj_IsKindOf(pObj1, OBJ_IDENT_OBJHASH);
        TestForTrue(fRc, "Failed Ident Test");
#ifdef   OBJHASH_MSGS
        ObjHash_setMsg(pObj1, (void *)Test_MsgInfo, (void *)Test_MsgWarn, this);
#endif
        
        for (i=0; i<cStringTable; ++i) {
            if (pStringTable[i]) {
                pStr = AStr_NewA(pStringTable[i]);
                TestForNotNull(pStr, "");
                index = 0;
                eRc = ObjHash_Add(pObj1, pStr, &index);
                TestForSuccess("");
                fprintf(stderr, "i=%d  index=%d  %s\n", i, index, pStringTable[i]);
                TestForTrue((index == (i + 1)), "");
                obj_Release(pStr);
                pStr = OBJ_NIL;
            }
        }
        size = ObjHash_getSize(pObj1);
        TestForTrue((size == cStringTable), "");

        // Test assign.
        pObj2 = ObjHash_New();
        TestForNotNull(pObj2, "Missing copied object");
        eRc = ObjHash_Assign(pObj1, pObj2);
        TestForFalse((ERESULT_FAILED(eRc)), "Assignment failed");

        fRc = obj_IsKindOf(pObj2, OBJ_IDENT_OBJHASH);
        TestForTrue(fRc, "Failed Ident Test");
        //iRc = ObjHash_Compare(pObj1, pObj2);
        //TestForTrue((0 == iRc), "Failed Compare");
        //TODO: Add More tests here!

        obj_Release(pObj2);
        pObj2 = OBJ_NIL;

        // Test copy.
        pObj2 = ObjHash_Copy(pObj1);
        TestForNotNull(pObj2, "Missing copied object");

        fRc = obj_IsKindOf(pObj2, OBJ_IDENT_OBJHASH);
        TestForTrue(fRc, "Failed Ident Test");
        //iRc = ObjHash_Compare(pObj1, pObj2);
        //TestForTrue((0 == iRc), "Failed Compare");
        //TODO: Add More tests here!

        obj_Release(pObj2);
        pObj2 = OBJ_NIL;

        // Test json support.
#if defined(OBJHASH_JSON_SUPPORT) && defined(XYZZY)
        pStr = ObjHash_ToJson(pObj1);
        TestForNotNull(pStr, "Missing JSON output");
        fprintf(stderr, "JSON: %s\n", AStr_getData(pStr));
        pObj2 = ObjHash_NewFromJsonString(pStr);
        TestForNotNull(pObj2, "Missing JSON created object");
        fRc = obj_IsKindOf(pObj2, OBJ_IDENT_OBJHASH);
        TestForTrue(fRc, "Failed Ident Test");
        obj_Release(pStr);
        pStr = OBJ_NIL;
        //iRc = ObjHash_Compare(pObj1, pObj2);
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



ERESULT         Test_ObjHash_Test01 (
    TEST_DATA       *this,
    const
    char            *pTestName
)
{
    ERESULT         eRc = ERESULT_SUCCESS;
    OBJHASH_DATA    *pObj = OBJ_NIL;
    bool            fRc;
#ifdef XXXXX
    uint32_t        i;
    uint32_t        size;
    uint32_t        index;
    ASTR_DATA       *pStr = OBJ_NIL;
#endif

    fprintf(stderr, "Performing: %s\n", pTestName);

    pObj = ObjHash_NewWithSize(3);
    TestForNotNull(pObj, "Missing Test object");
    if (pObj) {

        //obj_TraceSet(pObj, true);       
        fRc = obj_IsKindOf(pObj, OBJ_IDENT_OBJHASH);
        TestForTrue(fRc, "Failed Ident Test");
        TestForSuccess("");
#ifdef   OBJHASH_LOG
        ObjHash_setLog(pObj, this);
#endif

#ifdef XXXXX
        for (i=0; i<cStringTable; ++i) {
            if (pStringTable[i]) {
                pStr = AStr_NewA(pStringTable[i]);
                TestForNotNull(pStr, "");
                index = 0;
                eRc = ObjHash_Add(pObj, pStr, &index);
                TestForSuccess("");
                fprintf(stderr, "\tAdding i=%2d  index=%2d  %s\n", i, index, pStringTable[i]);
                TestForTrue((index == (i + 1)), "");
                obj_Release(pStr);
                pStr = OBJ_NIL;
            }
        }
        size = ObjHash_getSize(pObj);
        TestForTrue((size == cStringTable), "");

        {
            ASTR_DATA       *pStr = ObjHash_ToDebugString(pObj, 4);
            if (pStr) {
                fprintf(stderr, "Debug: %s\n", AStr_getData(pStr));
                obj_Release(pStr);
                pStr = OBJ_NIL;
            }
        }
#endif

        obj_Release(pObj);
        pObj = OBJ_NIL;
    }

    fprintf(stderr, "...%s completed.\n\n\n", pTestName);
    return eRc;
}



ERESULT         Test_ObjHash_Test02 (
    TEST_DATA       *this,
    const
    char            *pTestName
)
{
    ERESULT         eRc = ERESULT_SUCCESS;
    OBJHASH_DATA    *pObj = OBJ_NIL;
    bool            fRc;
    uint32_t        i;
    uint32_t        size;
    uint32_t        index;
    ASTR_DATA       *pStr = OBJ_NIL;
    OBJENUM_DATA    *pEnum = OBJ_NIL;

    fprintf(stderr, "Performing: %s\n", pTestName);

    pObj = ObjHash_New( );
    TestForNotNull(pObj, "Missing Test object");
    if (pObj) {

        //obj_TraceSet(pObj, true);
        fRc = obj_IsKindOf(pObj, OBJ_IDENT_OBJHASH);
        TestForTrue(fRc, "Failed Ident Test");
        TestForSuccess("");
#ifdef   OBJHASH_LOG
        ObjHash_setLog(pObj, this);
#endif
        eRc = ObjHash_Setup(pObj, 3);

        for (i=0; i<cStringTable; ++i) {
            if (pStringTable[i]) {
                pStr = AStr_NewA(pStringTable[i]);
                TestForNotNull(pStr, "");
                index = 0;
                eRc = ObjHash_Add(pObj, pStr, &index);
                TestForSuccess("");
                fprintf(stderr, "\tAdded i=%2d  index=%2d  %s\n", i, index, pStringTable[i]);
                TestForTrue((index == (i + 1)), "");
                obj_Release(pStr);
                pStr = OBJ_NIL;
            }
        }
        size = ObjHash_getSize(pObj);
        TestForTrue((size == cStringTable), "");

        pStr = ObjHash_FindIndex(pObj, 1);
        TestForNotNull(pStr, "");
        TestForTrue((0 == strcmp(AStr_getData(pStr), pStringTable[0])), "");
        pStr = ObjHash_FindIndex(pObj, cStringTable);
        TestForNotNull(pStr, "");
        TestForTrue((0 == strcmp(AStr_getData(pStr), pStringTable[cStringTable-1])), "");
        pStr = OBJ_NIL;

        pEnum = ObjHash_Enum(pObj);
        TestForNotNull(pEnum, "");
        TestForTrue((cStringTable == ObjEnum_getSize(pEnum)), "");
        fprintf(stderr, "\tEnumerate data:\n");
        for (i=0; ; ++i) {
            eRc = ObjEnum_Next(pEnum, 1, (OBJ_ID *)&pStr, &size);
            if (ERESULT_FAILED(eRc)) {
                break;
            }
            fprintf(stderr, "\t\t%2d - %s\n", i, AStr_getData(pStr));
        }
        obj_Release(pEnum);
        pEnum = OBJ_NIL;
        eRc = ERESULT_SUCCESS;

        {
            ASTR_DATA       *pStr = ObjHash_ToDebugString(pObj, 4);
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



ERESULT         Test_ObjHash_Test03 (
    TEST_DATA       *this,
    const
    char            *pTestName
)
{
    ERESULT         eRc = ERESULT_SUCCESS;
    OBJHASH_DATA    *pObj = OBJ_NIL;
    bool            fRc;
    uint32_t        i;
    uint32_t        size;
    uint32_t        index;
    ASTR_DATA       *pStr = OBJ_NIL;
    OBJENUM_DATA    *pEnum = OBJ_NIL;

    fprintf(stderr, "Performing: %s\n", pTestName);

    pObj = ObjHash_NewWithSize(3);
    TestForNotNull(pObj, "Missing Test object");
    if (pObj) {

        //obj_TraceSet(pObj, true);
        fRc = obj_IsKindOf(pObj, OBJ_IDENT_OBJHASH);
        TestForTrue(fRc, "Failed Ident Test");
        TestForSuccess("");
#ifdef   OBJHASH_LOG
        ObjHash_setLog(pObj, this);
#endif

        for (i=0; i<cStringTable; ++i) {
            if (pStringTable[i]) {
                pStr = AStr_NewA(pStringTable[i]);
                TestForNotNull(pStr, "");
                index = 0;
                eRc = ObjHash_Add(pObj, pStr, &index);
                TestForSuccess("");
                fprintf(stderr, "\tAdding i=%2d  index=%2d  %s\n", i, index, pStringTable[i]);
                TestForTrue((index == (i + 1)), "");
                obj_Release(pStr);
                pStr = OBJ_NIL;
            }
        }
        size = ObjHash_getSize(pObj);
        TestForTrue((size == cStringTable), "");

        pStr = ObjHash_FindIndex(pObj, 1);
        TestForNotNull(pStr, "");
        TestForTrue((0 == strcmp(AStr_getData(pStr), pStringTable[0])), "");
        pStr = ObjHash_FindIndex(pObj, cStringTable);
        TestForNotNull(pStr, "");
        TestForTrue((0 == strcmp(AStr_getData(pStr), pStringTable[cStringTable-1])), "");
        pStr = OBJ_NIL;

        pEnum = ObjHash_Enum(pObj);
        TestForNotNull(pEnum, "");
        TestForTrue((cStringTable == ObjEnum_getSize(pEnum)), "");

        fprintf(stderr, "\tEnumerate data:\n");
        for (i=0; ; ++i) {
            eRc = ObjEnum_Next(pEnum, 1, (OBJ_ID *)&pStr, &size);
            if (ERESULT_FAILED(eRc)) {
                break;
            }
            fprintf(stderr, "\t\t%2d - %s\n", i, AStr_getData(pStr));
        }
        obj_Release(pEnum);
        pEnum = OBJ_NIL;
        eRc = ERESULT_SUCCESS;

        pEnum = ObjHash_ScopeEnum(pObj, 0);
        TestForNotNull(pEnum, "");
        TestForTrue((cStringTable == ObjEnum_getSize(pEnum)), "");

        fprintf(stderr, "\tEnumerate Scope data:\n");
        for (i=0; ; ++i) {
            eRc = ObjEnum_Next(pEnum, 1, (OBJ_ID *)&pStr, &size);
            if (ERESULT_FAILED(eRc)) {
                break;
            }
            fprintf(stderr, "\t\t%2d - %s\n", i, AStr_getData(pStr));
        }
        obj_Release(pEnum);
        pEnum = OBJ_NIL;
        eRc = ERESULT_SUCCESS;

        {
            ASTR_DATA       *pStr = ObjHash_ToDebugString(pObj, 4);
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



ERESULT         Test_ObjHash_Test04 (
    TEST_DATA       *this,
    const
    char            *pTestName
)
{
    ERESULT         eRc = ERESULT_SUCCESS;
    OBJHASH_DATA    *pObj = OBJ_NIL;
    bool            fRc;
    uint32_t        i;
    uint32_t        size;
    uint32_t        index;
    uint32_t        scope;
    uint32_t        scopeMax;
    ASTR_DATA       *pStr = OBJ_NIL;
    OBJENUM_DATA    *pEnum = OBJ_NIL;

    fprintf(stderr, "Performing: %s\n", pTestName);

    pObj = ObjHash_NewWithSize(17);
    TestForNotNull(pObj, "Missing Test object");
    if (pObj) {

        //obj_TraceSet(pObj, true);
        fRc = obj_IsKindOf(pObj, OBJ_IDENT_OBJHASH);
        TestForTrue(fRc, "Failed Ident Test");
        TestForSuccess("");
#ifdef   OBJHASH_LOG
        ObjHash_setLog(pObj, this);
#endif

        for (i=0; i<10; ++i) {
            if (pStringTable[i]) {
                pStr = AStr_NewA(pStringTable[i]);
                TestForNotNull(pStr, "");
                index = 0;
                eRc = ObjHash_Add(pObj, pStr, &index);
                TestForSuccess("");
                fprintf(stderr, "\tAdding i=%2d  index=%2d  %s\n", i, index, pStringTable[i]);
                TestForTrue((index == (i + 1)), "");
                obj_Release(pStr);
                pStr = OBJ_NIL;
            }
        }
        size = ObjHash_getSize(pObj);
        TestForTrue((size == 10), "");

        i = ObjHash_ScopeOpen(pObj);
        TestForTrue((i == 1), "");

        for (i=10; i<20; ++i) {
            if (pStringTable[i]) {
                pStr = AStr_NewA(pStringTable[i]);
                TestForNotNull(pStr, "");
                index = 0;
                eRc = ObjHash_Add(pObj, pStr, &index);
                TestForSuccess("");
                fprintf(stderr, "\tAdding i=%2d  index=%2d  %s\n", i, index, pStringTable[i]);
                TestForTrue((index == (i + 1)), "");
                obj_Release(pStr);
                pStr = OBJ_NIL;
            }
        }
        size = ObjHash_getSize(pObj);
        TestForTrue((size == 20), "");

        i = ObjHash_ScopeOpen(pObj);
        TestForTrue((i == 2), "");

        for (i=20; i<30; ++i) {
            if (pStringTable[i]) {
                pStr = AStr_NewA(pStringTable[i]);
                TestForNotNull(pStr, "");
                index = 0;
                eRc = ObjHash_Add(pObj, pStr, &index);
                TestForSuccess("");
                fprintf(stderr, "\tAdding i=%2d  index=%2d  %s\n", i, index, pStringTable[i]);
                TestForTrue((index == (i + 1)), "");
                obj_Release(pStr);
                pStr = OBJ_NIL;
            }
        }
        size = ObjHash_getSize(pObj);
        TestForTrue((size == 30), "");

        scopeMax = ObjHash_getScopeSize(pObj);
        for (scope=0; scope < scopeMax; scope++) {
            pEnum = ObjHash_ScopeEnum(pObj, scope);
            TestForNotNull(pEnum, "");
            TestForTrue((10 == ObjEnum_getSize(pEnum)), "");
            if (pEnum) {
                fprintf(stderr, "\n\tEnumerate Scope %d data:\n", scope);
                for (i=0; ; ++i) {
                    eRc = ObjEnum_Next(pEnum, 1, (OBJ_ID *)&pStr, &size);
                    if (ERESULT_FAILED(eRc)) {
                        break;
                    }
                    fprintf(stderr, "\t\t%2d - %s\n", i, AStr_getData(pStr));
                }
                obj_Release(pEnum);
                pEnum = OBJ_NIL;
            }
        }
        fprintf(stderr, "\n\n");
        eRc = ERESULT_SUCCESS;

        {
            ASTR_DATA       *pStr = ObjHash_ToDebugString(pObj, 4);
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
    TestExec("OpenClose", Test_ObjHash_OpenClose, NULL, NULL);
    //TestExec("Copy01", Test_ObjHash_Copy01, NULL, NULL);
    TestExec("Test01", Test_ObjHash_Test01, NULL, NULL);
    TestExec("Test02", Test_ObjHash_Test02, NULL, NULL);
    TestExec("Test03", Test_ObjHash_Test03, NULL, NULL);
    TestExec("Test04", Test_ObjHash_Test04, NULL, NULL);

    obj_Release(pTest);
    pTest = OBJ_NIL;

    // Return to Operating System.
    return 0;
}



