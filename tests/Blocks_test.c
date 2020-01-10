// vi:nu:et:sts=4 ts=4 sw=4
/*
 *	Generated 01/10/2020 11:54:27
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
//#include    <szTbl.h>
#include    <trace.h>
#include    <Blocks_internal.h>



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

    //szTbl_SharedReset( );
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






int             test_Blocks_OpenClose (
    const
    char            *pTestName
)
{
    ERESULT         eRc = ERESULT_SUCCESS;
    BLOCKS_DATA	    *pObj = OBJ_NIL;
    bool            fRc;
   
    fprintf(stderr, "Performing: %s\n", pTestName);

    pObj = Blocks_Alloc( );
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    pObj = Blocks_Init( pObj );
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    if (pObj) {

        //obj_TraceSet(pObj, true);       
        fRc = obj_IsKindOf(pObj, OBJ_IDENT_BLOCKS);
        TINYTEST_TRUE( (fRc) );
        
        fprintf(stderr, "\tBlockSize  = %d\n", Blocks_getBlockSize(pObj));
        fprintf(stderr, "\tBlockAvail = %d\n", Blocks_getBlockAvail(pObj));

        // Test something.
        TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );

        obj_Release(pObj);
        pObj = OBJ_NIL;
    }

    fprintf(stderr, "...%s completed.\n\n\n", pTestName);
    return 1;
}



int             test_Blocks_Test01 (
    const
    char            *pTestName
)
{
    ERESULT         eRc = ERESULT_SUCCESS;
    BLOCKS_DATA	    *pObj = OBJ_NIL;
    bool            fRc;
   
    fprintf(stderr, "Performing: %s\n", pTestName);

    pObj = Blocks_Alloc( );
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    pObj = Blocks_Init( pObj );
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    if (pObj) {

        //obj_TraceSet(pObj, true);       
        fRc = obj_IsKindOf(pObj, OBJ_IDENT_BLOCKS);
        TINYTEST_TRUE( (fRc) );
        
        // Test something.
        TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );

        obj_Release(pObj);
        pObj = OBJ_NIL;
    }

    fprintf(stderr, "...%s completed.\n\n\n", pTestName);
    return 1;
}



int         test_Blocks_Add(
    const
    char            *pTestName
)
{
    ERESULT         eRc;
    BLOCKS_DATA        *pObj = OBJ_NIL;
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
    XCTAssertFalse( (OBJ_NIL == pObj) );
    if (pObj) {

        eRc = Blocks_SetupSizes(pObj, 0, 32);
        XCTAssertFalse( (ERESULT_FAILED(eRc)) );
        fprintf(stderr, "\tBlockSize  = %d\n", Blocks_getBlockSize(pObj));
        XCTAssertTrue( (4096 == Blocks_getBlockSize(pObj)) );
        fprintf(stderr, "\tBlockAvail = %d\n", Blocks_getBlockAvail(pObj));
        XCTAssertTrue( (4080 == Blocks_getBlockAvail(pObj)) );
        fprintf(stderr, "\tRecordSize  = %d\n", Blocks_getRecordSize(pObj));
#if defined(__MACOSX_ENV__)
        XCTAssertTrue( (48 == Blocks_getRecordSize(pObj)) );
#endif
#if defined(__WIN32_ENV__)
        XCTAssertTrue( (36 == Blocks_getRecordSize(pObj)) );
#endif
#if defined(__WIN64_ENV__)
        XCTAssertTrue( (48 == Blocks_getRecordSize(pObj)) );
#endif
        fprintf(stderr, "\tRecordsPerBlock  = %d\n", Blocks_getRecordsPerBlock(pObj));
#if defined(__MACOSX_ENV__)
        XCTAssertTrue( (85 == Blocks_getRecordsPerBlock(pObj)) );
#endif
#if defined(__WIN32_ENV__)
        XCTAssertTrue( (127 == Blocks_getRecordsPerBlock(pObj)) );
#endif
#if defined(__WIN64_ENV__)
        XCTAssertTrue( (85 == Blocks_getRecordsPerBlock(pObj)) );
#endif

        pRcd1 = Blocks_RecordNew(pObj, &unique);
        XCTAssertTrue( (1 == unique) );
        pWrk = pObj->blocks.pHead;
        fprintf(stderr, "\tBlock 1  = %p\n", pWrk);
        fprintf(stderr, "\tRecord 1  = %p\n", pRcd1);
        fprintf(stderr, "\tOffset 1  = %d\n", (int)(pRcd1 - pWrk));
#if defined(__MACOSX_ENV__)
        XCTAssertTrue( (32 == (int)(pRcd1 - pWrk)) );
#endif
#if defined(__WIN32_ENV__)
        XCTAssertTrue( (20 == (int)(pRcd1 - pWrk)) );
#endif
#if defined(__WIN64_ENV__)
        XCTAssertTrue( (32 == (int)(pRcd1 - pWrk)) );
#endif
        pRcd2 = Blocks_RecordNew(pObj, &unique);
        XCTAssertTrue( (2 == unique) );
        fprintf(stderr, "\tRecord 2  = %p\n", pRcd2);
        fprintf(stderr, "\tOffset 2  = %d\n", (int)(pRcd2 - pWrk));
#if defined(__MACOSX_ENV__)
        XCTAssertTrue( (80 == (int)(pRcd2 - pWrk)) );
#endif
#if defined(__WIN32_ENV__)
        XCTAssertTrue( (52 == (int)(pRcd2 - pWrk)) );
#endif
#if defined(__WIN64_ENV__)
        XCTAssertTrue( (80 == (int)(pRcd2 - pWrk)) );
#endif
        pRcd3 = Blocks_RecordNew(pObj, &unique);
        XCTAssertTrue( (3 == unique) );
        fprintf(stderr, "\tRecord 3  = %p\n", pRcd3);
        eRc = Blocks_RecordFree(pObj, pRcd2);
        XCTAssertFalse( (ERESULT_FAILED(eRc)) );
        fprintf(stderr, "\tFreed Record 2  = %p\n", pRcd2);
        pRcd4 = Blocks_RecordNew(pObj, &unique);
        XCTAssertTrue( (4 == unique) );
        fprintf(stderr, "\tRecord 4  = %p\n", pRcd4);
        XCTAssertTrue( (pRcd2 == pRcd4) );
        pRcd2 = NULL;

        obj_Release(pObj);
        pObj = OBJ_NIL;
    }

    fprintf(stderr, "...%s completed.\n\n", pTestName);
    return 1;
}




TINYTEST_START_SUITE(test_Blocks);
    TINYTEST_ADD_TEST(test_Blocks_Add,setUp,tearDown);
    TINYTEST_ADD_TEST(test_Blocks_Test01,setUp,tearDown);
    TINYTEST_ADD_TEST(test_Blocks_OpenClose,setUp,tearDown);
TINYTEST_END_SUITE();

TINYTEST_MAIN_SINGLE_SUITE(test_Blocks);





