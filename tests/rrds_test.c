/*
 *	Generated 01/05/2019 23:32:40
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
#include    <cmn_defs.h>
#include    <dec.h>
#include    <trace.h>
#include    <rrds_internal.h>



int             setUp(
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


int             tearDown(
    const
    char            *pTestName
)
{
    // Put teardown code here. This method is called after the invocation of each
    // test method in the class.

    
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






int             test_rrds_OpenClose(
    const
    char            *pTestName
)
{
    ERESULT         eRc = ERESULT_SUCCESS;
    RRDS_DATA	    *pObj = OBJ_NIL;
   
    fprintf(stderr, "Performing: %s\n", pTestName);

    pObj = rrds_Alloc( );
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    pObj = rrds_Init( pObj );
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    if (pObj) {

        //obj_TraceSet(pObj, true);       
        
        // Test something.
        TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );

        obj_Release(pObj);
        pObj = OBJ_NIL;
    }

    fprintf(stderr, "...%s completed.\n\n\n", pTestName);
    return 1;
}



int         test_rrds_Read01(
    const
    char        *pTestName
)
{
    RRDS_DATA     *pDS80;
    uint32_t        i;
    //bool            fRc;
    const
    char            *pPathA    = "~/git/libCmn/tests/files/regequ.asm.txt";
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
    
    pTime = dateTime_NewCurrent();
    TINYTEST_FALSE( (OBJ_NIL == pTime) );
    
    pPath = path_NewA(pPathA);
    TINYTEST_FALSE( (OBJ_NIL == pPath) );
    fprintf(stderr, "\tPath = \"%s\"\n", path_getData(pPath));
    
    pDS80 = rrds_New();
    XCTAssertFalse( (NULL == pDS80));
    XCTAssertTrue( (80 == rrds_getRecordSize(pDS80)));
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
    
    eRc = rrds_SetupSizes(pDS80, 80, RRDS_RCD_TRM_NL, 1, 11);
    XCTAssertFalse( (ERESULT_FAILED(eRc)) );
    
    eRc = rrds_Open(pDS80, pPath);
    if (ERESULT_FAILED(eRc)) {
        fprintf(stderr, "\tFailed eRc = %d\n", eRc);
    }
    XCTAssertFalse( (ERESULT_FAILED(eRc)) );
    fprintf(stderr, "\trecordSize = %d\n", rrds_getRecordSize(pDS80));
    fprintf(stderr, "\tnumRecords = %d\n", rrds_getSize(pDS80));
    XCTAssertTrue( (80 == rrds_getRecordSize(pDS80)));
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
    XCTAssertTrue( (19 == rrds_getSize(pDS80)));

    for (i=0; i<numRcds; ++i) {
        cBlock = 80;
        pBlock = block;
        //dec_putInt32A( i, &cBlock, &pBlock );
        //eRc = rrds_RecordWrite(cbp, i+1, block);
        //STAssertTrue( (fRc), @"rrds_BlockWrite failed!" );
        eRc = rrds_RecordRead(pDS80, i+1, (uint8_t *)block2);
        XCTAssertFalse( (ERESULT_FAILED(eRc)) );
        fprintf(stderr, "\t%3d = \"%s\"\n", i+1, block2);
        //XCTAssertTrue( (0 == memcmp(block, block2, 80)) );
    }
    
    eRc = rrds_Close(pDS80, false);
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




TINYTEST_START_SUITE(test_rrds);
    TINYTEST_ADD_TEST(test_rrds_Read01,setUp,tearDown);
    TINYTEST_ADD_TEST(test_rrds_OpenClose,setUp,tearDown);
TINYTEST_END_SUITE();

TINYTEST_MAIN_SINGLE_SUITE(test_rrds);





