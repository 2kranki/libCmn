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
#include    <RRDS_internal.h>
#include    <JsonIn.h>
#include    <SrcErrors.h>
#include    <szTbl.h>






ERESULT         Test_RRDS_OpenClose (
    TEST_DATA       *this,
    const
    char            *pTestName
)
{
    ERESULT         eRc = ERESULT_SUCCESS;
    RRDS_DATA       *pObj = OBJ_NIL;
    bool            fRc;
   
    fprintf(stderr, "Performing: %s\n", pTestName);

    pObj = RRDS_Alloc( );
    TestForNotNull(pObj, "Missing Test Alloc() object");
    pObj = RRDS_Init( pObj );
    TestForNotNull(pObj, "Missing Test Init() object");
    if (pObj) {

        //obj_TraceSet(pObj, true);       
        fRc = obj_IsKindOf(pObj, OBJ_IDENT_RRDS);
        TestForTrue(fRc, "Failed Ident Test");
        
        // Test something.
        TestForSuccess("test failed");

        obj_Release(pObj);
        pObj = OBJ_NIL;
    }

    fprintf(stderr, "...%s completed.\n\n\n", pTestName);
    return eRc;
}



ERESULT         Test_RRDS_Copy01 (
    TEST_DATA       *this,
    const
    char            *pTestName
)
{
    ERESULT         eRc = ERESULT_SUCCESS;
    RRDS_DATA       *pObj1 = OBJ_NIL;
    RRDS_DATA       *pObj2 = OBJ_NIL;
    bool            fRc;
#if defined(RRDS_JSON_SUPPORT) && defined(XYZZY)
    ASTR_DATA       *pStr = OBJ_NIL;
#endif
    //int             iRc;
   
    fprintf(stderr, "Performing: %s\n", pTestName);

    pObj1 = RRDS_New( );
    TestForNotNull(pObj1, "Missing Test object");
    if (pObj1) {

        //obj_TraceSet(pObj1, true);       
        fRc = obj_IsKindOf(pObj1, OBJ_IDENT_RRDS);
        TestForTrue(fRc, "Failed Ident Test");
        
        // Test assign.
        pObj2 = RRDS_New();
        TestForNotNull(pObj2, "Missing copied object");
        eRc = RRDS_Assign(pObj1, pObj2);
        TestForFalse((ERESULT_FAILED(eRc)), "Assignment failed");

        fRc = obj_IsKindOf(pObj2, OBJ_IDENT_RRDS);
        TestForTrue(fRc, "Failed Ident Test");
        //iRc = RRDS_Compare(pObj1, pObj2);
        //TestForTrue((0 == iRc), "Failed Compare");
        //TODO: Add More tests here!

        obj_Release(pObj2);
        pObj2 = OBJ_NIL;

        // Test copy.
        pObj2 = RRDS_Copy(pObj1);
        TestForNotNull(pObj2, "Missing copied object");

        fRc = obj_IsKindOf(pObj2, OBJ_IDENT_RRDS);
        TestForTrue(fRc, "Failed Ident Test");
        //iRc = RRDS_Compare(pObj1, pObj2);
        //TestForTrue((0 == iRc), "Failed Compare");
        //TODO: Add More tests here!

        obj_Release(pObj2);
        pObj2 = OBJ_NIL;

        // Test json support.
#if defined(RRDS_JSON_SUPPORT) && defined(XYZZY)
        pStr = RRDS_ToJson(pObj1);
        TestForNotNull(pStr, "Missing JSON output");
        fprintf(stderr, "JSON: %s\n", AStr_getData(pStr));
        pObj2 = RRDS_NewFromJsonString(pStr);
        TestForNotNull(pObj2, "Missing JSON created object");
        fRc = obj_IsKindOf(pObj2, OBJ_IDENT_RRDS);
        TestForTrue(fRc, "Failed Ident Test");
        obj_Release(pStr);
        pStr = OBJ_NIL;
        //iRc = RRDS_Compare(pObj1, pObj2);
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



ERESULT         Test_RRDS_Test01 (
    TEST_DATA       *this,
    const
    char            *pTestName
)
{
    ERESULT         eRc = ERESULT_SUCCESS;
    RRDS_DATA       *pObj = OBJ_NIL;
    bool            fRc;
   
    fprintf(stderr, "Performing: %s\n", pTestName);

    pObj = RRDS_New( );
    TestForNotNull(pObj, "Missing Test object");
    if (pObj) {

        //obj_TraceSet(pObj, true);       
        fRc = obj_IsKindOf(pObj, OBJ_IDENT_RRDS);
        TestForTrue(fRc, "Failed Ident Test");
        
        {
            ASTR_DATA       *pStr = RRDS_ToDebugString(pObj, 4);
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



ERESULT         Test_RRDS_Read01 (
    TEST_DATA       *this,
    const
    char            *pTestName
)
{
    ERESULT         eRc = ERESULT_SUCCESS;
    RRDS_DATA       *pDS80 = OBJ_NIL;
    bool            fRc;
    uint32_t        i;
    //bool            fRc;
    const
    char            *pPathA    = TEST_FILES_DIR "/regequ.asm.txt";
    char            block[80]  = {0};
    char            block2[80] = {0};
    uint32_t        numRcds = 19;
    uint32_t        cBlock;
    char            *pBlock;
    PATH_DATA       *pPath = OBJ_NIL;
    DATETIME_DATA   *pTime = OBJ_NIL;

    fprintf(stderr, "Performing: %s\n", pTestName);

    pTime = DateTime_NewCurrent();
    TestForNotNull(pTime, "");

    pPath = Path_NewA(pPathA);
    TestForNotNull(pPath, "");
    fprintf(stderr, "\tPath = \"%s\"\n", Path_getData(pPath));

    pDS80 = RRDS_New( );
    TestForNotNull(pDS80, "");
    TestForTrue((80 == RRDS_getRecordSize(pDS80)), "");
#if defined(__MACOSX_ENV__)
    fprintf(stderr, "\tRecordSize = %d\n",  pDS80->recordSize);
    TestForTrue((81 == pDS80->recordSize, ""));
    TestForTrue((RRDS_RCD_TRM_NL == pDS80->recordTerm), "");
#endif
#if defined(__WIN32_ENV__) || defined(__WIN64_ENV__)
    TestForTrue((82 == pDS80->recordSize), "");
    TestForTrue((RRDS_RCD_TRM_CRNL == pDS80->recordTerm), "");
#endif
#if defined(__PIC32MX_TNEO_ENV__)
    TestForTrue((81 == pDS80->recordSize), "");
    TestForTrue((RRDS_RCD_TRM_NL == pDS80->recordTerm), "");
#endif
    if (pDS80) {

        //obj_TraceSet(pObj, true);
        fRc = obj_IsKindOf(pDS80, OBJ_IDENT_RRDS);
        TestForTrue(fRc, "Failed Ident Test");

        eRc = RRDS_SetupSizes(pDS80, 80, RRDS_RCD_TRM_NL, 1, 11);
        TestForSuccess("");

        eRc = RRDS_Open(pDS80, pPath, false);
        if (ERESULT_FAILED(eRc)) {
            fprintf(stderr, "\tFailed eRc = %d\n", eRc);
        }
        TestForSuccess("");

        fprintf(stderr, "\trecordSize = %d\n", RRDS_getRecordSize(pDS80));
        fprintf(stderr, "\tnumRecords = %d\n", RRDS_getSize(pDS80));
        TestForTrue((80 == RRDS_getRecordSize(pDS80)), "");
    #if defined(__MACOSX_ENV__)
        TestForTrue((81 == pDS80->recordSize), "");
        TestForTrue((RRDS_RCD_TRM_NL == pDS80->recordTerm), "");
    #endif
    #if defined(__WIN32_ENV__) || defined(__WIN64_ENV__)
        TestForTrue((82 == pDS80->recordSize), "");
    #endif
    #if defined(__PIC32MX_TNEO_ENV__)
        TestForTrue((81 == pDS80->recordSize), "");
        TestForTrue((RRDS_RCD_TRM_NL == pDS80->recordTerm), "");
    #endif
        TestForTrue((19 == RRDS_getSize(pDS80)), "");

        for (i=0; i<numRcds; ++i) {
            cBlock = 80;
            pBlock = block;
            //dec_putInt32A( i, &cBlock, &pBlock );
            //eRc = RRDS_RecordWrite(cbp, i+1, block);
            //STAssertTrue( (fRc), @"RRDS_BlockWrite failed!" );
            eRc = RRDS_RecordRead(pDS80, i+1, (uint8_t *)block2);
            TestForSuccess("");
            fprintf(stderr, "\t%3d = \"%s\"\n", i+1, block2);
            //XCTAssertTrue( (0 == memcmp(block, block2, 80)) );
        }

        eRc = RRDS_Close(pDS80, false);
        TestForSuccess("");

        {
            ASTR_DATA       *pStr = RRDS_ToDebugString(pDS80, 4);
            if (pStr) {
                fprintf(stderr, "Debug: %s\n", AStr_getData(pStr));
                obj_Release(pStr);
                pStr = OBJ_NIL;
            }
        }

        obj_Release(pDS80);
        pDS80 = OBJ_NIL;
    }

    obj_Release(pPath);
    pPath = OBJ_NIL;

    obj_Release(pTime);
    pTime = OBJ_NIL;

    fprintf(stderr, "...%s completed.\n\n\n", pTestName);
    return eRc;
}



ERESULT         Test_RRDS_Read02 (
    TEST_DATA       *this,
    const
    char            *pTestName
)
{
    ERESULT         eRc = ERESULT_SUCCESS;
    RRDS_DATA       *pDS80 = OBJ_NIL;
    bool            fRc;
    //uint32_t        i;
    //bool            fRc;
    const
    char            *pPathA    = TEST_FILES_DIR "/mvsobj.object360";
    //uint8_t         block[80]  = {0};
    uint8_t         block2[80] = {0};
    //uint32_t        numRcds = 19;
    //uint32_t        cBlock;
    //char            *pBlock;
    PATH_DATA       *pPath = OBJ_NIL;
    DATETIME_DATA   *pTime = OBJ_NIL;

    fprintf(stderr, "Performing: %s\n", pTestName);

    pTime = DateTime_NewCurrent();
    TestForNotNull(pTime, "");

    pPath = Path_NewA(pPathA);
    TestForNotNull(pPath, "");
    fprintf(stderr, "\tPath = \"%s\"\n", Path_getData(pPath));

    pDS80 = RRDS_New( );
    TestForNotNull(pDS80, "");
    TestForTrue((80 == RRDS_getRecordSize(pDS80)), "");
#if defined(__MACOSX_ENV__)
    fprintf(stderr, "\tRecordSize = %d\n",  pDS80->recordSize);
    TestForTrue((81 == pDS80->recordSize, ""));
    TestForTrue((RRDS_RCD_TRM_NL == pDS80->recordTerm), "");
#endif
#if defined(__WIN32_ENV__) || defined(__WIN64_ENV__)
    TestForTrue((82 == pDS80->recordSize), "");
    TestForTrue((RRDS_RCD_TRM_CRNL == pDS80->recordTerm), "");
#endif
#if defined(__PIC32MX_TNEO_ENV__)
    TestForTrue((81 == pDS80->recordSize), "");
    TestForTrue((RRDS_RCD_TRM_NL == pDS80->recordTerm), "");
#endif
    if (pDS80) {

        //obj_TraceSet(pObj, true);
        fRc = obj_IsKindOf(pDS80, OBJ_IDENT_RRDS);
        TestForTrue(fRc, "Failed Ident Test");

        eRc = RRDS_SetupSizes(pDS80, 80, RRDS_RCD_TRM_NL, 1, 11);
        TestForSuccess("");

        eRc = RRDS_Open(pDS80, pPath, false);
        if (ERESULT_FAILED(eRc)) {
            fprintf(stderr, "\tFailed eRc = %d\n", eRc);
        }
        TestForSuccess("");

        fprintf(stderr, "\trecordSize = %d\n", RRDS_getRecordSize(pDS80));
        fprintf(stderr, "\tnumRecords = %d\n", RRDS_getSize(pDS80));
        TestForTrue((80 == RRDS_getRecordSize(pDS80)), "");
    #if defined(__MACOSX_ENV__)
        TestForTrue((81 == pDS80->recordSize), "");
        TestForTrue((RRDS_RCD_TRM_NL == pDS80->recordTerm), "");
    #endif
    #if defined(__WIN32_ENV__) || defined(__WIN64_ENV__)
        TestForTrue((82 == pDS80->recordSize), "");
    #endif
    #if defined(__PIC32MX_TNEO_ENV__)
        TestForTrue((81 == pDS80->recordSize), "");
        TestForTrue((RRDS_RCD_TRM_NL == pDS80->recordTerm), "");
    #endif
        TestForTrue((48 == RRDS_getSize(pDS80)), "");

        eRc = RRDS_RecordRead(pDS80, 1, (uint8_t *)block2);
        TestForSuccess("");
        TestForTrue((block2[0] == 0x02), "");
        TestForTrue((block2[1] == 0xC5), "");
        TestForTrue((block2[2] == 0xE2), "");
        TestForTrue((block2[3] == 0xC4), "");

        eRc = RRDS_RecordRead(pDS80, 2, (uint8_t *)block2);
        TestForSuccess("");
        TestForTrue((block2[0] == 0x02), "");
        TestForTrue((block2[1] == 0xC5), "");
        TestForTrue((block2[2] == 0xE2), "");
        TestForTrue((block2[3] == 0xC4), "");

        eRc = RRDS_RecordRead(pDS80, 3, (uint8_t *)block2);
        TestForSuccess("");
        TestForTrue((block2[0] == 0x02), "");
        TestForTrue((block2[1] == 0xC5), "");
        TestForTrue((block2[2] == 0xE2), "");
        TestForTrue((block2[3] == 0xC4), "");

        eRc = RRDS_RecordRead(pDS80, 4, (uint8_t *)block2);
        TestForSuccess("");
        TestForTrue((block2[0] == 0x02), "");
        TestForTrue((block2[1] == 0xE3), "");
        TestForTrue((block2[2] == 0xE7), "");
        TestForTrue((block2[3] == 0xE3), "");

        eRc = RRDS_Close(pDS80, false);
        TestForSuccess("");

        {
            ASTR_DATA       *pStr = RRDS_ToDebugString(pDS80, 4);
            if (pStr) {
                fprintf(stderr, "Debug: %s\n", AStr_getData(pStr));
                obj_Release(pStr);
                pStr = OBJ_NIL;
            }
        }

        obj_Release(pDS80);
        pDS80 = OBJ_NIL;
    }

    obj_Release(pPath);
    pPath = OBJ_NIL;

    obj_Release(pTime);
    pTime = OBJ_NIL;

    fprintf(stderr, "...%s completed.\n\n\n", pTestName);
    return eRc;
}



ERESULT         Test_RRDS_Insert01 (
    TEST_DATA       *this,
    const
    char            *pTestName
)
{
    ERESULT         eRc = ERESULT_SUCCESS;
    RRDS_DATA       *pObj = OBJ_NIL;
    bool            fRc;
    //uint32_t        i;
    //uint32_t        index;
    uint8_t         data[8];
    uint8_t         *pData = data;
    const
    char            *pPathA    = "/tmp/test.rrds";
    PATH_DATA       *pPath = OBJ_NIL;

    fprintf(stderr, "Performing: %s\n", pTestName);

    pPath = Path_NewA(pPathA);
    TestForNotNull(pPath, "");
    fprintf(stderr, "\tPath = \"%s\"\n", Path_getData(pPath));

    pObj = RRDS_New( );
    TestForNotNull(pObj, "Missing Test object");
    if (pObj) {

        //obj_TraceSet(pObj, true);
        fRc = obj_IsKindOf(pObj, OBJ_IDENT_RRDS);
        TestForTrue(fRc, "Failed Ident Test");

        eRc = RRDS_SetupSizes(pObj, 8, RRDS_RCD_TRM_NONE, 1, 11);
        TestForSuccess("");

        // Create a memory-based file.
        eRc = RRDS_Create(pObj, pPath, true);
        if (ERESULT_FAILED(eRc)) {
            fprintf(stderr, "\tFailed eRc = %d\n", eRc);
        }
        TestForSuccess("");
        RRDS_setFillChar(pObj, '1');

        str_Copy((char *)data, sizeof(data), "2222222");
        eRc = RRDS_RecordWrite(pObj, 2, pData);
        TestForSuccess("");

        str_Copy((char *)data, sizeof(data), "0000000");
        eRc = RRDS_RecordRead(pObj, 1, pData);
        TestForSuccess("");
        TestForTrue((0 == strncmp((char *)pData, "11111111", 8)), "");

        str_Copy((char *)data, sizeof(data), "0000000");
        pData = data;
        eRc = RRDS_RecordRead(pObj, 2, pData);
        TestForSuccess("");
        TestForTrue((0 == strcmp((char *)pData, "2222222")), "");

        eRc = RRDS_Close(pObj, true);
        TestForSuccess("");

        {
            ASTR_DATA       *pStr = RRDS_ToDebugString(pObj, 4);
            if (pStr) {
                fprintf(stderr, "Debug: %s\n", AStr_getData(pStr));
                obj_Release(pStr);
                pStr = OBJ_NIL;
            }
        }

        obj_Release(pObj);
        pObj = OBJ_NIL;
    }

    obj_Release(pPath);
    pPath = OBJ_NIL;

    {
        FILEIO_CLASS_VTBL   *pVtbl = (void *)obj_getVtbl(FileIO_Class());
        pVtbl->pMemFileReset();
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
    TestExec("OpenClose", Test_RRDS_OpenClose, NULL, NULL);
    //TestExec("Copy01", Test_RRDS_Copy01, pTest, NULL, NULL);
    TestExec("Test01", Test_RRDS_Test01, NULL, NULL);
    TestExec("Read01", Test_RRDS_Read01, NULL, NULL);
    TestExec("Read02", Test_RRDS_Read02, NULL, NULL);
    TestExec("Insert01", Test_RRDS_Insert01, NULL, NULL);

    obj_Release(pTest);
    pTest = OBJ_NIL;

    // Return to Operating System.
    return 0;
}



