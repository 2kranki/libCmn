/*
 *	Generated 06/30/2017 09:01:13
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
#include    <trace.h>
#include    <blocks_internal.h>



int         setUp(
    const
    char        *pTestName
)
{
    mem_Init( );
    trace_Shared( ); 
    // Put setup code here. This method is called before the invocation of each
    // test method in the class.
    
    return 1; 
}


int         tearDown(
    const
    char        *pTestName
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






int         test_blocks_OpenClose(
    const
    char            *pTestName
)
{
    BLOCKS_DATA	    *pObj = OBJ_NIL;
   
    fprintf(stderr, "Performing: %s\n", pTestName);
    pObj = blocks_Alloc( );
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    pObj = blocks_Init(pObj, 4096);
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    if (pObj) {
        
        fprintf(stderr, "\tBlockSize  = %d\n", blocks_getBlockSize(pObj));
        fprintf(stderr, "\tBlockAvail = %d\n", blocks_getBlockAvail(pObj));

        obj_Release(pObj);
        pObj = OBJ_NIL;
    }

    fprintf(stderr, "...%s completed.\n\n", pTestName);
    return 1;
}



int         test_blocks_Add(
    const
    char            *pTestName
)
{
    ERESULT         eRc;
    BLOCKS_DATA	    *pObj = OBJ_NIL;
    void            *pBlk1 = NULL;
    void            *pBlk2 = NULL;
    void            *pBlk3 = NULL;
    void            *pBlk4 = NULL;
    void            *pWrk;
    uint8_t         *pBlks[8] = {NULL};
    uint32_t        cBlks = 0;
    BLOCKS_BLOCK    *pGroup;
    int             i;
    ENUM_DATA       *pEnum = OBJ_NIL;
    uint64_t        i64 = 0;
    
    fprintf(stderr, "Performing: %s\n", pTestName);
    pObj = blocks_Alloc( );
    XCTAssertFalse( (OBJ_NIL == pObj) );
    pObj = blocks_Init( pObj, 2048 );
    XCTAssertFalse( (OBJ_NIL == pObj) );
    if (pObj) {
        
        pBlk1 = blocks_Add(pObj);
        XCTAssertFalse( (NULL == pBlk1) );
        pBlk2 = blocks_Add(pObj);
        XCTAssertFalse( (NULL == pBlk2) );
        pBlk3 = blocks_Add(pObj);
        XCTAssertFalse( (NULL == pBlk3) );
        pBlk4 = blocks_Add(pObj);
        XCTAssertFalse( (NULL == pBlk4) );
        XCTAssertTrue( (4 == blocks_getSize(pObj)) );

        eRc = blocks_Enum(pObj, &pEnum);
        XCTAssertFalse( (ERESULT_FAILED(eRc)) );
        eRc = enum_Next(pEnum, 8, (void**)pBlks, &cBlks);
        XCTAssertFalse( (ERESULT_FAILED(eRc)) );
        XCTAssertTrue( (4 == cBlks) );
        XCTAssertTrue( (pBlks[0] == pBlk1) );
        XCTAssertTrue( (pBlks[1] == pBlk2) );
        XCTAssertTrue( (pBlks[2] == pBlk3) );
        XCTAssertTrue( (pBlks[3] == pBlk4) );
        obj_Release(pEnum);
        pEnum = OBJ_NIL;

        pWrk = blocks_Get(pObj, 1);
        XCTAssertTrue( (pWrk == pBlk1) );
        pWrk = blocks_Get(pObj, 2);
        XCTAssertTrue( (pWrk == pBlk2) );
        pWrk = blocks_Get(pObj, 3);
        XCTAssertTrue( (pWrk == pBlk3) );
        pWrk = blocks_Get(pObj, 4);
        XCTAssertTrue( (pWrk == pBlk4) );
        
        obj_Release(pObj);
        pObj = OBJ_NIL;
    }
    
    fprintf(stderr, "...%s completed.\n\n", pTestName);
    return 1;
}




TINYTEST_START_SUITE(test_blocks);
  TINYTEST_ADD_TEST(test_blocks_Add,setUp,tearDown);
  TINYTEST_ADD_TEST(test_blocks_OpenClose,setUp,tearDown);
TINYTEST_END_SUITE();

TINYTEST_MAIN_SINGLE_SUITE(test_blocks);





