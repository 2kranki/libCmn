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
#include    <BlockF16_internal.h>
#include    <JsonIn.h>
#include    <SrcErrors.h>
#include    <szTbl.h>






ERESULT         Test_BlockF16_OpenClose (
    TEST_DATA       *this,
    const
    char            *pTestName
)
{
    ERESULT         eRc = ERESULT_SUCCESS;
    BLOCKF16_DATA       *pObj = OBJ_NIL;
    bool            fRc;
   
    fprintf(stderr, "Performing: %s\n", pTestName);

    pObj = BlockF16_Alloc( );
    TestForNotNull(pObj, "Missing Test Alloc() object");
    pObj = BlockF16_Init( pObj );
    TestForNotNull(pObj, "Missing Test Init() object");
    if (pObj) {

        //obj_TraceSet(pObj, true);       
        fRc = obj_IsKindOf(pObj, OBJ_IDENT_BLOCKF16);
        TestForTrue(fRc, "Failed Ident Test");
        
        // Test something.
        TestForSuccess("test failed");

        obj_Release(pObj);
        pObj = OBJ_NIL;
    }

    fprintf(stderr, "...%s completed.\n\n\n", pTestName);
    return eRc;
}



ERESULT         Test_BlockF16_Copy01 (
    TEST_DATA       *this,
    const
    char            *pTestName
)
{
    ERESULT         eRc = ERESULT_SUCCESS;
    BLOCKF16_DATA       *pObj1 = OBJ_NIL;
    BLOCKF16_DATA       *pObj2 = OBJ_NIL;
    bool            fRc;
#if defined(BLOCKF16_JSON_SUPPORT) && defined(XYZZY)
    ASTR_DATA       *pStr = OBJ_NIL;
#endif
    //int             iRc;
   
    fprintf(stderr, "Performing: %s\n", pTestName);

    pObj1 = BlockF16_New( );
    TestForNotNull(pObj1, "Missing Test object");
    if (pObj1) {

        //obj_TraceSet(pObj1, true);       
        fRc = obj_IsKindOf(pObj1, OBJ_IDENT_BLOCKF16);
        TestForTrue(fRc, "Failed Ident Test");
        
        // Test assign.
        pObj2 = BlockF16_New();
        TestForNotNull(pObj2, "Missing copied object");
        eRc = BlockF16_Assign(pObj1, pObj2);
        TestForFalse((ERESULT_FAILED(eRc)), "Assignment failed");

        fRc = obj_IsKindOf(pObj2, OBJ_IDENT_BLOCKF16);
        TestForTrue(fRc, "Failed Ident Test");
        //iRc = BlockF16_Compare(pObj1, pObj2);
        //TestForTrue((0 == iRc), "Failed Compare");
        //TODO: Add More tests here!

        obj_Release(pObj2);
        pObj2 = OBJ_NIL;

        // Test copy.
        pObj2 = BlockF16_Copy(pObj1);
        TestForNotNull(pObj2, "Missing copied object");

        fRc = obj_IsKindOf(pObj2, OBJ_IDENT_BLOCKF16);
        TestForTrue(fRc, "Failed Ident Test");
        //iRc = BlockF16_Compare(pObj1, pObj2);
        //TestForTrue((0 == iRc), "Failed Compare");
        //TODO: Add More tests here!

        obj_Release(pObj2);
        pObj2 = OBJ_NIL;

        // Test json support.
#if defined(BLOCKF16_JSON_SUPPORT) && defined(XYZZY)
        pStr = BlockF16_ToJson(pObj1);
        TestForNotNull(pStr, "Missing JSON output");
        fprintf(stderr, "JSON: %s\n", AStr_getData(pStr));
        pObj2 = BlockF16_NewFromJsonString(pStr);
        TestForNotNull(pObj2, "Missing JSON created object");
        fRc = obj_IsKindOf(pObj2, OBJ_IDENT_BLOCKF16);
        TestForTrue(fRc, "Failed Ident Test");
        obj_Release(pStr);
        pStr = OBJ_NIL;
        //iRc = BlockF16_Compare(pObj1, pObj2);
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



ERESULT         Test_BlockF16_Test01 (
    TEST_DATA       *this,
    const
    char            *pTestName
)
{
    ERESULT         eRc = ERESULT_SUCCESS;
    BLOCKF16_DATA       *pObj = OBJ_NIL;
    bool            fRc;
   
    fprintf(stderr, "Performing: %s\n", pTestName);

    pObj = BlockF16_New( );
    TestForNotNull(pObj, "Missing Test object");
    if (pObj) {

        //obj_TraceSet(pObj, true);       
        fRc = obj_IsKindOf(pObj, OBJ_IDENT_BLOCKF16);
        TestForTrue(fRc, "Failed Ident Test");
        
        {
            ASTR_DATA       *pStr = BlockF16_ToDebugString(pObj, 4);
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



ERESULT         Test_BlockF16_Insert01 (
    TEST_DATA       *this,
    const
    char            *pTestName
)
{
    ERESULT         eRc = ERESULT_SUCCESS;
    BLOCKF16_DATA   *pObj = OBJ_NIL;
    bool            fRc;
    uint32_t        d;
    uint32_t        k;
    //uint32_t        i;
    //uint32_t        max;
    const
    uint16_t        blockSize = 48;
    const
    uint16_t        dataSize = sizeof(uint32_t);
    const
    uint16_t        rsvdSize = 12;

    fprintf(stderr, "Performing: %s\n", pTestName);

    pObj = BlockF16_NewWithSizes(blockSize, rsvdSize, dataSize);
    TestForNotNull(pObj, "Missing Test object");
    if (pObj) {

        obj_TraceSet(pObj, true);
        fRc = obj_IsKindOf(pObj, OBJ_IDENT_BLOCKF16);
        TestForTrue(fRc, "Failed Ident Test");
        Test_Dump(blockSize, pObj->pBlock, "Init:");
        TestForTrue((blockSize == BlockF16_getBlockSize(pObj)), "");
        TestForTrue((rsvdSize == BlockF16_getReservedSize(pObj)), "");
        TestForTrue((dataSize == BlockF16_getDataSize(pObj)), "");
        TestForTrue((6 == BlockF16_getMaxRecords(pObj)), "");
        TestForTrue((0 == BlockF16_getNumRecords(pObj)), "");
        {
            ASTR_DATA       *pStr = BlockF16_ToDebugString(pObj, 4);
            if (pStr) {
                fprintf(stderr, "Debug: %s\n", AStr_getData(pStr));
                obj_Release(pStr);
                pStr = OBJ_NIL;
            }
        }

        k = 3;
        fprintf(stderr, "\tAdding: %d\n", k);
        eRc = BlockF16_Add(pObj, &k);
        TestForSuccess("");
        {
            ASTR_DATA       *pStr = BlockF16_ToDebugString(pObj, 4);
            if (pStr) {
                fprintf(stderr, "Debug: %s\n", AStr_getData(pStr));
                obj_Release(pStr);
                pStr = OBJ_NIL;
            }
        }
        TestForTrue((6 == BlockF16_getMaxRecords(pObj)), "");
        TestForTrue((1 == BlockF16_getNumRecords(pObj)), "");

        k = 1;
        fprintf(stderr, "\tAdding: %d\n", k);
        eRc = BlockF16_Add(pObj, &k);
        TestForSuccess("");
        {
            ASTR_DATA       *pStr = BlockF16_ToDebugString(pObj, 4);
            if (pStr) {
                fprintf(stderr, "Debug: %s\n", AStr_getData(pStr));
                obj_Release(pStr);
                pStr = OBJ_NIL;
            }
        }
        TestForTrue((6 == BlockF16_getMaxRecords(pObj)), "");
        TestForTrue((2 == BlockF16_getNumRecords(pObj)), "");

        k = 4;
        fprintf(stderr, "\tAdding: %d\n", k);
        eRc = BlockF16_Add(pObj, &k);
        TestForSuccess("");
        {
            ASTR_DATA       *pStr = BlockF16_ToDebugString(pObj, 4);
            if (pStr) {
                fprintf(stderr, "Debug: %s\n", AStr_getData(pStr));
                obj_Release(pStr);
                pStr = OBJ_NIL;
            }
        }
        TestForTrue((6 == BlockF16_getMaxRecords(pObj)), "");
        TestForTrue((3 == BlockF16_getNumRecords(pObj)), "");

        k = 2;
        fprintf(stderr, "\tAdding: %d\n", k);
        eRc = BlockF16_Add(pObj, &k);
        TestForSuccess("");
        {
            ASTR_DATA       *pStr = BlockF16_ToDebugString(pObj, 4);
            if (pStr) {
                fprintf(stderr, "Debug: %s\n", AStr_getData(pStr));
                obj_Release(pStr);
                pStr = OBJ_NIL;
            }
        }
        TestForTrue((6 == BlockF16_getMaxRecords(pObj)), "");
        TestForTrue((4 == BlockF16_getNumRecords(pObj)), "");

        k = 5;
        fprintf(stderr, "\tAdding: %d\n", k);
        eRc = BlockF16_Add(pObj, &k);
        TestForSuccess("");
        {
            ASTR_DATA       *pStr = BlockF16_ToDebugString(pObj, 4);
            if (pStr) {
                fprintf(stderr, "Debug: %s\n", AStr_getData(pStr));
                obj_Release(pStr);
                pStr = OBJ_NIL;
            }
        }
        TestForTrue((6 == BlockF16_getMaxRecords(pObj)), "");
        TestForTrue((5 == BlockF16_getNumRecords(pObj)), "");

        d = 0;
        k = 1;
        fprintf(stderr, "\tGetting: %d\n", k);
        eRc = BlockF16_Get(pObj, k, &d);
        TestForSuccess("");
        TestForTrue((3 == d), "");

        d = 0;
        k = 2;
        fprintf(stderr, "\tGetting: %d\n", k);
        eRc = BlockF16_Get(pObj, k, &d);
        TestForSuccess("");
        TestForTrue((1 == d), "");

        d = 0;
        k = 3;
        fprintf(stderr, "\tGetting: %d\n", k);
        eRc = BlockF16_Get(pObj, k, &d);
        TestForSuccess("");
        TestForTrue((4 == d), "");

        d = 0;
        k = 4;
        fprintf(stderr, "\tGetting: %d\n", k);
        eRc = BlockF16_Get(pObj, k, &d);
        TestForSuccess("");
        TestForTrue((2 == d), "");

        d = 0;
        k = 5;
        fprintf(stderr, "\tGetting: %d\n", k);
        eRc = BlockF16_Get(pObj, k, &d);
        TestForSuccess("");
        TestForTrue((5 == d), "");

        {
            ASTR_DATA       *pStr = BlockF16_ToDebugString(pObj, 4);
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



ERESULT         Test_BlockF16_Insert02 (
    TEST_DATA       *this,
    const
    char            *pTestName
)
{
    ERESULT         eRc = ERESULT_SUCCESS;
    BLOCKF16_DATA   *pObj = OBJ_NIL;
    bool            fRc;
    uint32_t        d;
    uint32_t        k;
    uint32_t        i;
    //uint32_t        max;
    const
    uint16_t        blockSize = 48;
    const
    uint16_t        dataSize = sizeof(uint32_t);
    const
    uint16_t        rsvdSize = 12;

    fprintf(stderr, "Performing: %s\n", pTestName);

    pObj = BlockF16_NewWithSizes(blockSize, rsvdSize, dataSize);
    TestForNotNull(pObj, "Missing Test object");
    if (pObj) {

        obj_TraceSet(pObj, true);
        fRc = obj_IsKindOf(pObj, OBJ_IDENT_BLOCKF16);
        TestForTrue(fRc, "Failed Ident Test");
        Test_Dump(blockSize, pObj->pBlock, "Init:");
        TestForTrue((blockSize == BlockF16_getBlockSize(pObj)), "");
        TestForTrue((rsvdSize == BlockF16_getReservedSize(pObj)), "");
        TestForTrue((dataSize == BlockF16_getDataSize(pObj)), "");
        TestForTrue((6 == BlockF16_getMaxRecords(pObj)), "");
        TestForTrue((0 == BlockF16_getNumRecords(pObj)), "");
        {
            ASTR_DATA       *pStr = BlockF16_ToDebugString(pObj, 4);
            if (pStr) {
                fprintf(stderr, "Debug: %s\n", AStr_getData(pStr));
                obj_Release(pStr);
                pStr = OBJ_NIL;
            }
        }

        d = 4;
        k = 0;
        fprintf(stderr, "\tInserting: %d\n", k);
        eRc = BlockF16_Insert(pObj, k, &d);
        TestForSuccess("");
        {
            ASTR_DATA       *pStr = BlockF16_ToDebugString(pObj, 4);
            if (pStr) {
                fprintf(stderr, "Debug: %s\n", AStr_getData(pStr));
                obj_Release(pStr);
                pStr = OBJ_NIL;
            }
        }
        TestForTrue((6 == BlockF16_getMaxRecords(pObj)), "");
        TestForTrue((1 == BlockF16_getNumRecords(pObj)), "");

        d = 1;
        k = 0;
        fprintf(stderr, "\tInserting: %d\n", k);
        eRc = BlockF16_Insert(pObj, k, &d);
        TestForSuccess("");
        {
            ASTR_DATA       *pStr = BlockF16_ToDebugString(pObj, 4);
            if (pStr) {
                fprintf(stderr, "Debug: %s\n", AStr_getData(pStr));
                obj_Release(pStr);
                pStr = OBJ_NIL;
            }
        }
        TestForTrue((6 == BlockF16_getMaxRecords(pObj)), "");
        TestForTrue((2 == BlockF16_getNumRecords(pObj)), "");

        d = 2;
        k = 1;
        fprintf(stderr, "\tInserting: %d\n", k);
        eRc = BlockF16_Insert(pObj, k, &d);
        TestForSuccess("");
        {
            ASTR_DATA       *pStr = BlockF16_ToDebugString(pObj, 4);
            if (pStr) {
                fprintf(stderr, "Debug: %s\n", AStr_getData(pStr));
                obj_Release(pStr);
                pStr = OBJ_NIL;
            }
        }
        TestForTrue((6 == BlockF16_getMaxRecords(pObj)), "");
        TestForTrue((3 == BlockF16_getNumRecords(pObj)), "");

        d = 3;
        k = 2;
        fprintf(stderr, "\tInserting: %d\n", k);
        eRc = BlockF16_Insert(pObj, k, &d);
        TestForSuccess("");
        {
            ASTR_DATA       *pStr = BlockF16_ToDebugString(pObj, 4);
            if (pStr) {
                fprintf(stderr, "Debug: %s\n", AStr_getData(pStr));
                obj_Release(pStr);
                pStr = OBJ_NIL;
            }
        }
        TestForTrue((6 == BlockF16_getMaxRecords(pObj)), "");
        TestForTrue((4 == BlockF16_getNumRecords(pObj)), "");

        d = 5;
        k = 4;
        fprintf(stderr, "\tInserting: %d\n", k);
        eRc = BlockF16_Insert(pObj, k, &d);
        TestForSuccess("");
        {
            ASTR_DATA       *pStr = BlockF16_ToDebugString(pObj, 4);
            if (pStr) {
                fprintf(stderr, "Debug: %s\n", AStr_getData(pStr));
                obj_Release(pStr);
                pStr = OBJ_NIL;
            }
        }
        TestForTrue((6 == BlockF16_getMaxRecords(pObj)), "");
        TestForTrue((5 == BlockF16_getNumRecords(pObj)), "");

        for (i=0; i<pObj->pBlock->numRecords; i++) {
            d = 0;
            k = i+1;
            fprintf(stderr, "\tGetting: %d\n", k);
            eRc = BlockF16_Get(pObj, k, &d);
            TestForSuccess("");
            TestForTrue((k == d), "");
        }

        {
            ASTR_DATA       *pStr = BlockF16_ToDebugString(pObj, 4);
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



ERESULT         Test_BlockF16_Insert03 (
    TEST_DATA       *this,
    const
    char            *pTestName
)
{
    ERESULT         eRc = ERESULT_SUCCESS;
    BLOCKF16_DATA   *pObj = OBJ_NIL;
    BLOCKF16_DATA   *pObj2 = OBJ_NIL;
    bool            fRc;
    uint32_t        d;
    uint32_t        k;
    uint32_t        i;
    //uint32_t        max;
    const
    uint16_t        blockSize = 48;
    const
    uint16_t        dataSize = sizeof(uint32_t);
    const
    uint16_t        rsvdSize = 12;
    uint8_t         *pRcd;

    fprintf(stderr, "Performing: %s\n", pTestName);

    pObj = BlockF16_NewWithSizes(blockSize, rsvdSize, dataSize);
    TestForNotNull(pObj, "Missing Test object");
    if (pObj) {

        obj_TraceSet(pObj, true);
        fRc = obj_IsKindOf(pObj, OBJ_IDENT_BLOCKF16);
        TestForTrue(fRc, "Failed Ident Test");
        Test_Dump(blockSize, pObj->pBlock, "Init:");
        TestForTrue((blockSize == BlockF16_getBlockSize(pObj)), "");
        TestForTrue((rsvdSize == BlockF16_getReservedSize(pObj)), "");
        TestForTrue((dataSize == BlockF16_getDataSize(pObj)), "");
        TestForTrue((6 == BlockF16_getMaxRecords(pObj)), "");
        TestForTrue((0 == BlockF16_getNumRecords(pObj)), "");
        {
            ASTR_DATA       *pStr = BlockF16_ToDebugString(pObj, 4);
            if (pStr) {
                fprintf(stderr, "Debug: %s\n", AStr_getData(pStr));
                obj_Release(pStr);
                pStr = OBJ_NIL;
            }
        }

        for (i=0; i<pObj->pBlock->maxRecords; i++) {
            d = i+1;
            k = i+1;
            fprintf(stderr, "\tAdding: %d\n", k);
            eRc = BlockF16_Add(pObj, &d);
            TestForSuccess("");
            TestForTrue((k == BlockF16_getNumRecords(pObj)), "");
        }

        {
            ASTR_DATA       *pStr = BlockF16_ToDebugString(pObj, 4);
            if (pStr) {
                fprintf(stderr, "Debug: %s\n", AStr_getData(pStr));
                obj_Release(pStr);
                pStr = OBJ_NIL;
            }
        }

        for (i=0; i<pObj->pBlock->numRecords; i++) {
            d = 0;
            k = i+1;
            fprintf(stderr, "\tGetting: %d\n", k);
            eRc = BlockF16_Get(pObj, k, &d);
            TestForSuccess("");
            TestForTrue((k == d), "");
        }

        eRc = BlockF16_Split(pObj, &pObj2, NULL);
        TestForSuccess("");
        TestForTrue(pObj2, "");
        fRc = obj_IsKindOf(pObj, OBJ_IDENT_BLOCKF16);
        TestForTrue(fRc, "");
        TestForTrue((6 == BlockF16_getMaxRecords(pObj)), "");
        TestForTrue((3 == BlockF16_getNumRecords(pObj)), "");
        pRcd = BlockF16_RecordAddress(pObj, 0);
        TestForTrue(((uint32_t)*pRcd == 1), "");
        pRcd = BlockF16_RecordAddress(pObj, 1);
        TestForTrue(((uint32_t)*pRcd == 2), "");
        pRcd = BlockF16_RecordAddress(pObj, 2);
        TestForTrue(((uint32_t)*pRcd == 3), "");
        TestForTrue((6 == BlockF16_getMaxRecords(pObj2)), "");
        TestForTrue((3 == BlockF16_getNumRecords(pObj2)), "");
        pRcd = BlockF16_RecordAddress(pObj2, 0);
        TestForTrue(((uint32_t)*pRcd == 4), "");
        pRcd = BlockF16_RecordAddress(pObj2, 1);
        TestForTrue(((uint32_t)*pRcd == 5), "");
        pRcd = BlockF16_RecordAddress(pObj2, 2);
        TestForTrue(((uint32_t)*pRcd == 6), "");

        obj_Release(pObj2);
        pObj2 = OBJ_NIL;
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
    TestExec("OpenClose", Test_BlockF16_OpenClose, NULL, NULL);
    //TestExec("Copy01", Test_BlockF16_Copy01, pTest, NULL, NULL);
    TestExec("Test01", Test_BlockF16_Test01, NULL, NULL);
    TestExec("Insert01", Test_BlockF16_Insert01, NULL, NULL);
    TestExec("Insert02", Test_BlockF16_Insert02, NULL, NULL);
    TestExec("Insert03", Test_BlockF16_Insert03, NULL, NULL);

    obj_Release(pTest);
    pTest = OBJ_NIL;

    // Return to Operating System.
    return 0;
}



