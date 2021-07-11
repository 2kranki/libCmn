// vi:nu:et:sts=4 ts=4 sw=4
/*
 *  Generated 07/10/2021 09:44:02
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
#include    <test_defs.h>
#include    <trace.h>
#include    <RRDS_internal.h>
#include    <JsonIn.h>
#ifdef  RRDS_JSON_SUPPORT
#   include    <SrcErrors.h>
#   include    <szTbl.h>
#endif



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

#ifdef  RRDS_JSON_SUPPORT
    SrcErrors_SharedReset( );
    szTbl_SharedReset( );
#endif
    JsonIn_RegisterReset();
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






int             test_RRDS_OpenClose (
    const
    char            *pTestName
)
{
    ERESULT         eRc = ERESULT_SUCCESS;
    RRDS_DATA       *pObj = OBJ_NIL;
    bool            fRc;
   
    fprintf(stderr, "Performing: %s\n", pTestName);

    pObj = RRDS_Alloc( );
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    pObj = RRDS_Init( pObj );
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    if (pObj) {

        //obj_TraceSet(pObj, true);       
        fRc = obj_IsKindOf(pObj, OBJ_IDENT_RRDS);
        TINYTEST_TRUE( (fRc) );
        
        // Test something.
        TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );

        obj_Release(pObj);
        pObj = OBJ_NIL;
    }

    fprintf(stderr, "...%s completed.\n\n\n", pTestName);
    return 1;
}



int             test_RRDS_Copy01 (
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
    TINYTEST_FALSE( (OBJ_NIL == pObj1) );
    if (pObj1) {

        //obj_TraceSet(pObj1, true);       
        fRc = obj_IsKindOf(pObj1, OBJ_IDENT_RRDS);
        TINYTEST_TRUE( (fRc) );
        
        // Test assign.
        pObj2 = RRDS_New();
        TINYTEST_FALSE( (OBJ_NIL == pObj2) );
        eRc = RRDS_Assign(pObj1, pObj2);
        TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );

        fRc = obj_IsKindOf(pObj2, OBJ_IDENT_RRDS);
        TINYTEST_TRUE( (fRc) );
        //iRc = RRDS_Compare(pObj1, pObj2);
        //TINYTEST_TRUE( (0 == iRc) );
        //TODO: Add More tests here!

        obj_Release(pObj2);
        pObj2 = OBJ_NIL;

        // Test copy.
        pObj2 = RRDS_Copy(pObj1);
        TINYTEST_FALSE( (OBJ_NIL == pObj2) );

        fRc = obj_IsKindOf(pObj2, OBJ_IDENT_RRDS);
        TINYTEST_TRUE( (fRc) );
        //iRc = RRDS_Compare(pObj1, pObj2);
        //TINYTEST_TRUE( (0 == iRc) );
        //TODO: Add More tests here!

        obj_Release(pObj2);
        pObj2 = OBJ_NIL;

        // Test json support.
#if defined(RRDS_JSON_SUPPORT) && defined(XYZZY)
        pStr = RRDS_ToJson(pObj1);
        TINYTEST_FALSE( (OBJ_NIL == pStr) );
        fprintf(stderr, "JSON: %s\n", AStr_getData(pStr));
        pObj2 = RRDS_NewFromJsonString(pStr);
        TINYTEST_FALSE( (OBJ_NIL == pObj2) );
        fRc = obj_IsKindOf(pObj2, OBJ_IDENT_RRDS);
        TINYTEST_TRUE( (fRc) );
        obj_Release(pStr);
        pStr = OBJ_NIL;
        //iRc = RRDS_Compare(pObj1, pObj2);
        //TINYTEST_TRUE( (0 == iRc) );

        obj_Release(pObj2);
        pObj2 = OBJ_NIL;
#endif

        obj_Release(pObj1);
        pObj1 = OBJ_NIL;
    }

    fprintf(stderr, "...%s completed.\n\n\n", pTestName);
    return 1;
}



int             test_RRDS_Test01 (
    const
    char            *pTestName
)
{
    //ERESULT         eRc = ERESULT_SUCCESS;
    RRDS_DATA       *pObj = OBJ_NIL;
    bool            fRc;
   
    fprintf(stderr, "Performing: %s\n", pTestName);

    pObj = RRDS_New( );
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    if (pObj) {

        //obj_TraceSet(pObj, true);       
        fRc = obj_IsKindOf(pObj, OBJ_IDENT_RRDS);
        TINYTEST_TRUE( (fRc) );
        //TINYTEST_TRUE( (ERESULT_OK(eRc)) );
        
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
    return 1;
}



int         test_RRDS_Read01(
    const
    char        *pTestName
)
{
    RRDS_DATA     *pDS80;
    uint32_t        i;
    //bool            fRc;
    const
    char            *pPathA    = TEST_FILES_DIR "/regequ.asm.txt";
    char            block[80]  = {0};
    char            block2[80] = {0};
    uint32_t        numRcds = 19;
    uint32_t        cBlock;
    char            *pBlock;
    ERESULT         eRc;
    PATH_DATA       *pPath = OBJ_NIL;
    DATETIME_DATA   *pTime = OBJ_NIL;
    //ASTR_DATA       *pStr = OBJ_NIL;

    fprintf(stderr, "Performing: %s\n", pTestName);

    pTime = DateTime_NewCurrent();
    TINYTEST_FALSE( (OBJ_NIL == pTime) );

    pPath = Path_NewA(pPathA);
    TINYTEST_FALSE( (OBJ_NIL == pPath) );
    fprintf(stderr, "\tPath = \"%s\"\n", Path_getData(pPath));

    pDS80 = RRDS_New();
    XCTAssertFalse( (NULL == pDS80));
    XCTAssertTrue( (80 == RRDS_getRecordSize(pDS80)));
#if defined(__MACOSX_ENV__)
    fprintf(stderr, "\tRecordSize = %d\n",  pDS80->recordSize);
    XCTAssertTrue( (81 == pDS80->recordSize));
    XCTAssertTrue( (RRDS_RCD_TRM_NL == pDS80->recordTerm));
#endif
#if defined(__WIN32_ENV__) || defined(__WIN64_ENV__)
    XCTAssertTrue( (82 == pDS80->recordSize));
    XCTAssertTrue( (RRDS_RCD_TRM_CRNL == pDS80->recordTerm));
#endif
#if defined(__PIC32MX_TNEO_ENV__)
    XCTAssertTrue( (81 == pDS80->recordSize));
    XCTAssertTrue( (RRDS_RCD_TRM_NL == pDS80->recordTerm));
#endif

    eRc = RRDS_SetupSizes(pDS80, 80, RRDS_RCD_TRM_NL, 1, 11);
    XCTAssertFalse( (ERESULT_FAILED(eRc)) );

    eRc = RRDS_Open(pDS80, pPath, false);
    if (ERESULT_FAILED(eRc)) {
        fprintf(stderr, "\tFailed eRc = %d\n", eRc);
    }
    XCTAssertFalse( (ERESULT_FAILED(eRc)) );
    fprintf(stderr, "\trecordSize = %d\n", RRDS_getRecordSize(pDS80));
    fprintf(stderr, "\tnumRecords = %d\n", RRDS_getSize(pDS80));
    XCTAssertTrue( (80 == RRDS_getRecordSize(pDS80)));
#if defined(__MACOSX_ENV__)
    XCTAssertTrue( (81 == pDS80->recordSize));
    XCTAssertTrue( (RRDS_RCD_TRM_NL == pDS80->recordTerm));
#endif
#if defined(__WIN32_ENV__) || defined(__WIN64_ENV__)
    XCTAssertTrue( (82 == pDS80->recordSize));
#endif
#if defined(__PIC32MX_TNEO_ENV__)
    XCTAssertTrue( (81 == pDS80->recordSize));
    XCTAssertTrue( (RRDS_RCD_TRM_NL == pDS80->recordTerm));
#endif
    XCTAssertTrue( (19 == RRDS_getSize(pDS80)));

    for (i=0; i<numRcds; ++i) {
        cBlock = 80;
        pBlock = block;
        //dec_putInt32A( i, &cBlock, &pBlock );
        //eRc = RRDS_RecordWrite(cbp, i+1, block);
        //STAssertTrue( (fRc), @"RRDS_BlockWrite failed!" );
        eRc = RRDS_RecordRead(pDS80, i+1, (uint8_t *)block2);
        XCTAssertFalse( (ERESULT_FAILED(eRc)) );
        fprintf(stderr, "\t%3d = \"%s\"\n", i+1, block2);
        //XCTAssertTrue( (0 == memcmp(block, block2, 80)) );
    }

    eRc = RRDS_Close(pDS80, false);
    XCTAssertFalse( (ERESULT_FAILED(eRc)) );

    obj_Release(pDS80);
    pDS80 = OBJ_NIL;

    obj_Release(pPath);
    pPath = OBJ_NIL;

    obj_Release(pTime);
    pTime = OBJ_NIL;

    fprintf(stderr, "...%s completed.\n\n\n", pTestName);
    return 1;
}



int         test_RRDS_Read02(
    const
    char        *pTestName
)
{
    RRDS_DATA     *pDS80;
    uint32_t        i;
    //bool            fRc;
    const
    char            *pPathA    = TEST_FILES_DIR "/mvsobj.object360";
    uint8_t         block[80]  = {0};
    uint8_t         block2[80] = {0};
    uint32_t        numRcds = 19;
    uint32_t        cBlock;
    uint8_t         *pBlock;
    ERESULT         eRc;
    PATH_DATA       *pPath = OBJ_NIL;
    DATETIME_DATA   *pTime = OBJ_NIL;
    //ASTR_DATA       *pStr = OBJ_NIL;

    fprintf(stderr, "Performing: %s\n", pTestName);

    pTime = DateTime_NewCurrent();
    TINYTEST_FALSE( (OBJ_NIL == pTime) );

    pPath = Path_NewA(pPathA);
    TINYTEST_FALSE( (OBJ_NIL == pPath) );
    fprintf(stderr, "\tPath = \"%s\"\n", Path_getData(pPath));

    pDS80 = RRDS_New();
    XCTAssertFalse( (NULL == pDS80));
    XCTAssertTrue( (80 == RRDS_getRecordSize(pDS80)));
#if defined(__MACOSX_ENV__)
    fprintf(stderr, "\tRecordSize = %d\n",  pDS80->recordSize);
    XCTAssertTrue( (81 == pDS80->recordSize));
    XCTAssertTrue( (RRDS_RCD_TRM_NL == pDS80->recordTerm));
#endif
#if defined(__WIN32_ENV__) || defined(__WIN64_ENV__)
    XCTAssertTrue( (82 == pDS80->recordSize));
    XCTAssertTrue( (RRDS_RCD_TRM_CRNL == pDS80->recordTerm));
#endif
#if defined(__PIC32MX_TNEO_ENV__)
    XCTAssertTrue( (81 == pDS80->recordSize));
    XCTAssertTrue( (RRDS_RCD_TRM_NL == pDS80->recordTerm));
#endif

    eRc = RRDS_SetupSizes(pDS80, 80, RRDS_RCD_TRM_NL, 1, 11);
    XCTAssertFalse( (ERESULT_FAILED(eRc)) );

    eRc = RRDS_Open(pDS80, pPath, false);
    if (ERESULT_FAILED(eRc)) {
        fprintf(stderr, "\tFailed eRc = %d\n", eRc);
    }
    XCTAssertFalse( (ERESULT_FAILED(eRc)) );
    fprintf(stderr, "\trecordSize = %d\n", RRDS_getRecordSize(pDS80));
    fprintf(stderr, "\tnumRecords = %d\n", RRDS_getSize(pDS80));
    XCTAssertTrue( (80 == RRDS_getRecordSize(pDS80)));
    XCTAssertTrue( (80 == pDS80->recordSize));
    XCTAssertTrue( (RRDS_RCD_TRM_NONE == pDS80->recordTerm));
    XCTAssertTrue( (48 == RRDS_getSize(pDS80)));

    eRc = RRDS_RecordRead(pDS80, 1, (uint8_t *)block2);
    XCTAssertFalse( (ERESULT_FAILED(eRc)) );
    XCTAssertTrue( (block2[0] == 0x02) );
    XCTAssertTrue( (block2[1] == 0xC5) );
    XCTAssertTrue( (block2[2] == 0xE2) );
    XCTAssertTrue( (block2[3] == 0xC4) );

    eRc = RRDS_RecordRead(pDS80, 2, (uint8_t *)block2);
    XCTAssertFalse( (ERESULT_FAILED(eRc)) );
    XCTAssertTrue( (block2[0] == 0x02) );
    XCTAssertTrue( (block2[1] == 0xC5) );
    XCTAssertTrue( (block2[2] == 0xE2) );
    XCTAssertTrue( (block2[3] == 0xC4) );

    eRc = RRDS_RecordRead(pDS80, 3, (uint8_t *)block2);
    XCTAssertFalse( (ERESULT_FAILED(eRc)) );
    XCTAssertTrue( (block2[0] == 0x02) );
    XCTAssertTrue( (block2[1] == 0xC5) );
    XCTAssertTrue( (block2[2] == 0xE2) );
    XCTAssertTrue( (block2[3] == 0xC4) );

    eRc = RRDS_RecordRead(pDS80, 4, (uint8_t *)block2);
    XCTAssertFalse( (ERESULT_FAILED(eRc)) );
    XCTAssertTrue( (block2[0] == 0x02) );
    XCTAssertTrue( (block2[1] == 0xE3) );
    XCTAssertTrue( (block2[2] == 0xE7) );
    XCTAssertTrue( (block2[3] == 0xE3) );

    eRc = RRDS_Close(pDS80, false);
    XCTAssertFalse( (ERESULT_FAILED(eRc)) );

    obj_Release(pDS80);
    pDS80 = OBJ_NIL;

    obj_Release(pPath);
    pPath = OBJ_NIL;

    obj_Release(pTime);
    pTime = OBJ_NIL;

    fprintf(stderr, "...%s completed.\n\n\n", pTestName);
    return 1;
}



int             test_RRDS_Insert01(
    const
    char            *pTestName
)
{
    ERESULT         eRc = ERESULT_SUCCESS;
    RRDS_DATA       *pObj = OBJ_NIL;
    //uint32_t        i;
    //uint32_t        index;
    uint8_t         data[8];
    uint8_t         *pData = data;

    fprintf(stderr, "Performing: %s\n", pTestName);

    pObj = RRDS_New( );
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    if (pObj) {

        //obj_TraceSet(pObj, true);
        eRc = RRDS_SetupSizes(pObj, 8, RRDS_RCD_TRM_NONE, 1, 11);
        TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );

        // Create a memory-based file.
        eRc = RRDS_Create(pObj, OBJ_NIL, true);
        if (ERESULT_FAILED(eRc)) {
            fprintf(stderr, "\tFailed eRc = %d\n", eRc);
        }
        XCTAssertFalse( (ERESULT_FAILED(eRc)) );
        RRDS_setFillChar(pObj, '1');

        str_Copy((char *)data, sizeof(data), "2222222");
        eRc = RRDS_RecordWrite(pObj, 2, pData);
        TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );

        str_Copy((char *)data, sizeof(data), "0000000");
        eRc = RRDS_RecordRead(pObj, 1, pData);
        TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );
        TINYTEST_TRUE((0 == strncmp((char *)pData, "11111111", 8)));

        str_Copy((char *)data, sizeof(data), "0000000");
        pData = data;
        eRc = RRDS_RecordRead(pObj, 2, pData);
        TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );
        TINYTEST_TRUE((0 == strcmp((char *)pData, "2222222")));

        obj_Release(pObj);
        pObj = OBJ_NIL;
    }

    fprintf(stderr, "...%s completed.\n\n", pTestName);
    return 1;
}




TINYTEST_START_SUITE(test_RRDS);
    TINYTEST_ADD_TEST(test_RRDS_Insert01,setUp,tearDown);
    TINYTEST_ADD_TEST(test_RRDS_Read02,setUp,tearDown);
    TINYTEST_ADD_TEST(test_RRDS_Read01,setUp,tearDown);
    TINYTEST_ADD_TEST(test_RRDS_Test01,setUp,tearDown);
    //TINYTEST_ADD_TEST(test_RRDS_Copy01,setUp,tearDown);
    TINYTEST_ADD_TEST(test_RRDS_OpenClose,setUp,tearDown);
TINYTEST_END_SUITE();

TINYTEST_MAIN_SINGLE_SUITE(test_RRDS);





