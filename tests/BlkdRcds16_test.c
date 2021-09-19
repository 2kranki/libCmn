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
#include    <BlkdRcds16_internal.h>
#include    <JsonIn.h>
#include    <SrcErrors.h>
#include    <szTbl.h>



static
const
char    *pWord2 = "ab";
static
const
char    *pWord3 = "cde";
static
const
char    *pWord4 = "fghi";
static
const
char    *pWord5 = "jklmn";
static
const
char    *pWord6 = "opqrst";
static
const
char    *pWord2h = "AB";
static
const
char    *pWord3h = "CDE";
#ifdef XYZZY
static
const
char    *pWord4h = "FGHI";
#endif
static
const
char    *pWord5h = "JKLMN";
#ifdef XYZZY
static
const
char    *pWord6h = "OPQRST";
#endif






ERESULT         Test_BlkdRcds16_OpenClose (
    TEST_DATA       *this,
    const
    char            *pTestName
)
{
    ERESULT         eRc = ERESULT_SUCCESS;
    BLKDRCDS16_DATA *pObj = OBJ_NIL;
    bool            fRc;
    uint16_t        size = 0;

    fprintf(stderr, "Performing: %s\n", pTestName);

    pObj = BlkdRcds16_Alloc( );
    TestForNotNull(pObj, "Missing Test Alloc() object");
    pObj = BlkdRcds16_Init( pObj );
    TestForNotNull(pObj, "Missing Test Init() object");
    if (pObj) {

        //obj_TraceSet(pObj, true);       
        fRc = obj_IsKindOf(pObj, OBJ_IDENT_BLKDRCDS16);
        TestForTrue(fRc, "Failed Ident Test");
        
        // Test something.
        TestForSuccess("test failed");

        size = BlkdRcds16_CalcFromRecordSize(10, 8, 64);
        fprintf(stderr, "\tSize = %d\n", size);
        TestForTrue((562 == size),  "Blocksize miscalculation");

        size = BlkdRcds16_CalcUseableSizeFromBlockSize(1024, 0);
        fprintf(stderr, "\tSize = %d\n", size);
        TestForTrue((1016 == size), "Useable space miscalculation");

        eRc = BlkdRcds16_SetupWithBlockSize(pObj, 1024, 0, NULL);
        TestForSuccess("Setup failed");
        TestForTrue((1024 == pObj->pBlock->cbSize), "blocksize - bad setup");
        TestForTrue((0    == pObj->pBlock->rsvdSize), "reserved size - bad setup");
        TestForTrue((1016 == pObj->pBlock->unusedSize), "Useable space - bad setup");
        TestForTrue((0    == pObj->pBlock->numRecords), "number of records - bad setup");

        {
            ASTR_DATA       *pStr = BlkdRcds16_ToDebugString(pObj, 4);
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



ERESULT         Test_BlkdRcds16_Copy01 (
    TEST_DATA       *this,
    const
    char            *pTestName
)
{
    ERESULT         eRc = ERESULT_SUCCESS;
    BLKDRCDS16_DATA       *pObj1 = OBJ_NIL;
    BLKDRCDS16_DATA       *pObj2 = OBJ_NIL;
    bool            fRc;
#if defined(BLKDRCDS16_JSON_SUPPORT) && defined(XYZZY)
    ASTR_DATA       *pStr = OBJ_NIL;
#endif
    //int             iRc;
   
    fprintf(stderr, "Performing: %s\n", pTestName);

    pObj1 = BlkdRcds16_New( );
    TestForNotNull(pObj1, "Missing Test object");
    if (pObj1) {

        //obj_TraceSet(pObj1, true);       
        fRc = obj_IsKindOf(pObj1, OBJ_IDENT_BLKDRCDS16);
        TestForTrue(fRc, "Failed Ident Test");
        
        // Test assign.
        pObj2 = BlkdRcds16_New();
        TestForNotNull(pObj2, "Missing copied object");
        eRc = BlkdRcds16_Assign(pObj1, pObj2);
        TestForFalse((ERESULT_FAILED(eRc)), "Assignment failed");

        fRc = obj_IsKindOf(pObj2, OBJ_IDENT_BLKDRCDS16);
        TestForTrue(fRc, "Failed Ident Test");
        //iRc = BlkdRcds16_Compare(pObj1, pObj2);
        //TestForTrue((0 == iRc), "Failed Compare");
        //TODO: Add More tests here!

        obj_Release(pObj2);
        pObj2 = OBJ_NIL;

        // Test copy.
        pObj2 = BlkdRcds16_Copy(pObj1);
        TestForNotNull(pObj2, "Missing copied object");

        fRc = obj_IsKindOf(pObj2, OBJ_IDENT_BLKDRCDS16);
        TestForTrue(fRc, "Failed Ident Test");
        //iRc = BlkdRcds16_Compare(pObj1, pObj2);
        //TestForTrue((0 == iRc), "Failed Compare");
        //TODO: Add More tests here!

        obj_Release(pObj2);
        pObj2 = OBJ_NIL;

        // Test json support.
#if defined(BLKDRCDS16_JSON_SUPPORT) && defined(XYZZY)
        pStr = BlkdRcds16_ToJson(pObj1);
        TestForNotNull(pStr, "Missing JSON output");
        fprintf(stderr, "JSON: %s\n", AStr_getData(pStr));
        pObj2 = BlkdRcds16_NewFromJsonString(pStr);
        TestForNotNull(pObj2, "Missing JSON created object");
        fRc = obj_IsKindOf(pObj2, OBJ_IDENT_BLKDRCDS16);
        TestForTrue(fRc, "Failed Ident Test");
        obj_Release(pStr);
        pStr = OBJ_NIL;
        //iRc = BlkdRcds16_Compare(pObj1, pObj2);
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



ERESULT         Test_BlkdRcds16_Test01 (
    TEST_DATA       *this,
    const
    char            *pTestName
)
{
    ERESULT         eRc = ERESULT_SUCCESS;
    BLKDRCDS16_DATA *pObj = OBJ_NIL;
    bool            fRc;
    uint16_t        size = 0;
    uint16_t        used = 0;
    uint16_t        rcdSize = 0;
    uint32_t        index = 0;
    char            data[16];
    const
    char            *pData;
    ASTR_DATA       *pStr;

    fprintf(stderr, "Performing: %s\n", pTestName);

    pObj = BlkdRcds16_NewWithBlockSize(40, 0);
    TestForNotNull(pObj, "Missing Test object");
    if (pObj) {

        //obj_TraceSet(pObj, true);       
        fRc = obj_IsKindOf(pObj, OBJ_IDENT_BLKDRCDS16);
        TestForTrue(fRc, "Failed Ident Test");
        {
            ASTR_DATA       *pStr = BlkdRcds16_ToDebugString(pObj, 4);
            if (pStr) {
                fprintf(stderr, "After New(): %s\n", AStr_getData(pStr));
                obj_Release(pStr);
                pStr = OBJ_NIL;
            }
        }
        TestForNotNull(pObj->pBlock, "Missing Block");
        TestForTrue((40 == pObj->pBlock->cbSize), "blocksize - bad setup");
        TestForTrue((0  == pObj->pBlock->rsvdSize), "reserved size - bad setup");
        TestForTrue((32 == pObj->pBlock->unusedSize), "Useable space - bad setup");
        TestForTrue((0  == pObj->pBlock->numRecords), "number of records - bad setup");

        size = BlkdRcds16_getNumRecords(pObj);
        TestForTrue((0 == size), "Invalid number of records");

        fprintf(stderr, "\n\n\t*** Appending Word06 ***\n");
        {
            ASTR_DATA       *pStr = BlkdRcds16_ToDebugString(pObj, 4);
            if (pStr) {
                fprintf(stderr, "Before: %s\n", AStr_getData(pStr));
                obj_Release(pStr);
                pStr = OBJ_NIL;
            }
        }
        size = strlen(pWord6) + 1;
        pData = pWord6;
        eRc = BlkdRcds16_RecordAppend(pObj, size, (void *)pData, &index);
        TestForSuccess("Append failed");
        TestForTrue((1 == index), "Invalid index number");
        TestForTrue((size == BlkdRcds16_RecordGetSize(pObj, index)), "Invalid index number");
        {
            ASTR_DATA       *pStr = BlkdRcds16_ToDebugString(pObj, 4);
            if (pStr) {
                fprintf(stderr, "After: %s\n", AStr_getData(pStr));
                obj_Release(pStr);
                pStr = OBJ_NIL;
            }
        }
        TestForNotNull(pObj->pBlock, "Missing Block");
        TestForTrue((40 == pObj->pBlock->cbSize), "blocksize - bad setup");
        TestForTrue((0  == pObj->pBlock->rsvdSize), "reserved size - bad setup");
        TestForTrue((21 == pObj->pBlock->unusedSize), "Useable space - bad setup");
        TestForTrue((1  == pObj->pBlock->numRecords), "number of records - bad setup");
        eRc = BlkdRcds16_RecordGet(pObj, index, sizeof(data), (void *)data, &used);
        TestForSuccess("Get failed");
        TestForTrue((0  == strcmp(pData, data)), "Get compare failed");
        TestForTrue((strlen(pWord6) + 1  == used), "Get used failed");

        fprintf(stderr, "\n\n\t*** Appending Word04 ***\n");
        {
            ASTR_DATA       *pStr = BlkdRcds16_ToDebugString(pObj, 4);
            if (pStr) {
                fprintf(stderr, "Before: %s\n", AStr_getData(pStr));
                obj_Release(pStr);
                pStr = OBJ_NIL;
            }
        }
        size = strlen(pWord4) + 1;
        pData = pWord4;
        eRc = BlkdRcds16_RecordAppend(pObj, size, (void *)pData, &index);
        TestForSuccess("Append failed");
        TestForTrue((2 == index), "Invalid index number");
        TestForTrue((size == BlkdRcds16_RecordGetSize(pObj, index)), "Invalid index number");
        {
            ASTR_DATA       *pStr = BlkdRcds16_ToDebugString(pObj, 4);
            if (pStr) {
                fprintf(stderr, "After: %s\n", AStr_getData(pStr));
                obj_Release(pStr);
                pStr = OBJ_NIL;
            }
        }
        TestForNotNull(pObj->pBlock, "Missing Block");
        TestForTrue((40 == pObj->pBlock->cbSize), "blocksize - bad setup");
        TestForTrue((0  == pObj->pBlock->rsvdSize), "reserved size - bad setup");
        TestForTrue((12 == pObj->pBlock->unusedSize), "Useable space - bad setup");
        TestForTrue((2  == pObj->pBlock->numRecords), "number of records - bad setup");
        eRc = BlkdRcds16_RecordGet(pObj, index, sizeof(data), (void *)data, &used);
        TestForSuccess("Get failed");
        TestForTrue((0  == strcmp(pData, data)), "Get compare failed");
        TestForTrue((strlen(pWord4) + 1  == used), "Get used failed");
        eRc = BlkdRcds16_RecordGet(pObj, 1, sizeof(data), (void *)data, &used);
        TestForSuccess("Get failed");
        TestForTrue((0  == strcmp(pWord6, data)), "Get compare failed");
        TestForTrue((strlen(pWord6) + 1  == used), "Get used failed");

        fprintf(stderr, "\n\n\t*** Appending Word02 ***\n");
        {
            ASTR_DATA       *pStr = BlkdRcds16_ToDebugString(pObj, 4);
            if (pStr) {
                fprintf(stderr, "Before: %s\n", AStr_getData(pStr));
                obj_Release(pStr);
                pStr = OBJ_NIL;
            }
        }
        size = strlen(pWord2) + 1;
        pData = pWord2;
        eRc = BlkdRcds16_RecordAppend(pObj, size, (void *)pData, &index);
        TestForSuccess("Append failed");
        TestForTrue((3 == index), "Invalid index number");
        TestForTrue((size == BlkdRcds16_RecordGetSize(pObj, index)), "Invalid index number");
        {
            ASTR_DATA       *pStr = BlkdRcds16_ToDebugString(pObj, 4);
            if (pStr) {
                fprintf(stderr, "After: %s\n", AStr_getData(pStr));
                obj_Release(pStr);
                pStr = OBJ_NIL;
            }
        }
        TestForNotNull(pObj->pBlock, "Missing Block");
        TestForTrue((40 == pObj->pBlock->cbSize), "blocksize - bad setup");
        TestForTrue((0  == pObj->pBlock->rsvdSize), "reserved size - bad setup");
        TestForTrue((5  == pObj->pBlock->unusedSize), "Useable space - bad setup");
        TestForTrue((3  == pObj->pBlock->numRecords), "number of records - bad setup");
        eRc = BlkdRcds16_RecordGet(pObj, index, sizeof(data), (void *)data, &used);
        TestForSuccess("Get failed");
        TestForTrue((0  == strcmp(pData, data)), "Get compare failed");
        TestForTrue((strlen(pWord2) + 1  == used), "Get used failed");
        eRc = BlkdRcds16_RecordGet(pObj, 1, sizeof(data), (void *)data, &used);
        TestForSuccess("Get failed");
        TestForTrue((0  == strcmp(pWord6, data)), "Get compare failed");
        TestForTrue((strlen(pWord6) + 1  == used), "Get used failed");
        eRc = BlkdRcds16_RecordGet(pObj, 2, sizeof(data), (void *)data, &used);
        TestForSuccess("Get failed");
        TestForTrue((0  == strcmp(pWord4, data)), "Get compare failed");
        TestForTrue((strlen(pWord4) + 1  == used), "Get used failed");

        size = strlen(pWord2) + 1;
        pData = pWord2;
        eRc = BlkdRcds16_RecordAppend(pObj, size, (void *)pData, &index);
        TestForFail("Append worked");
        eRc = ERESULT_SUCCESS;

        fprintf(stderr, "\n\n\t*** Deleting Record 2 ***\n");
        {
            ASTR_DATA       *pStr = BlkdRcds16_ToDebugString(pObj, 4);
            if (pStr) {
                fprintf(stderr, "Before: %s\n", AStr_getData(pStr));
                obj_Release(pStr);
                pStr = OBJ_NIL;
            }
        }
        eRc = BlkdRcds16_RecordDelete(pObj, 2);
        TestForSuccess("Delete failed");
        {
            ASTR_DATA       *pStr = BlkdRcds16_ToDebugString(pObj, 4);
            if (pStr) {
                fprintf(stderr, "After: %s\n", AStr_getData(pStr));
                obj_Release(pStr);
                pStr = OBJ_NIL;
            }
        }
        TestForNotNull(pObj->pBlock, "Missing Block");
        TestForTrue((40 == pObj->pBlock->cbSize), "blocksize - bad setup");
        TestForTrue((0  == pObj->pBlock->rsvdSize), "reserved size - bad setup");
        TestForTrue((14  == pObj->pBlock->unusedSize), "Useable space - bad setup");
        TestForTrue((2  == pObj->pBlock->numRecords), "number of records - bad setup");
        eRc = BlkdRcds16_RecordGet(pObj, 1, sizeof(data), (void *)data, &used);
        TestForSuccess("Get failed");
        TestForTrue((0  == strcmp(pWord6, data)), "Get compare failed");
        TestForTrue((strlen(pWord6) + 1  == used), "Get used failed");
        eRc = BlkdRcds16_RecordGet(pObj, 2, sizeof(data), (void *)data, &used);
        TestForSuccess("Get failed");
        TestForTrue((0  == strcmp(pWord2, data)), "Get compare failed");
        TestForTrue((strlen(pWord2) + 1  == used), "Get used failed");

        {
            ASTR_DATA       *pStr = BlkdRcds16_ToDebugString(pObj, 4);
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
    TestExec("OpenClose", Test_BlkdRcds16_OpenClose, NULL, NULL);
    //TestExec("Copy01", Test_BlkdRcds16_Copy01, pTest, NULL, NULL);
    TestExec("Test01", Test_BlkdRcds16_Test01, NULL, NULL);

    obj_Release(pTest);
    pTest = OBJ_NIL;

    // Return to Operating System.
    return 0;
}



