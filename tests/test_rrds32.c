/*
 *	Generated 03/17/2017 11:12:35
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
#include    <rrds32_internal.h>



int         setUp(
    const
    char        *pTestName
)
{
    mem_Init( );
    
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

    
    mem_Dump( );
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







int         test_rrds32_OpenClose(
    const
    char        *pTestName
)
{
    RRDS32_DATA	*pObj = OBJ_NIL;
   
    fprintf(stderr, "Performing: %s\n", pTestName);
    pObj = rrds32_Alloc( );
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    pObj = rrds32_Init( pObj, 0 );
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    if (pObj) {

        // Test something.

        obj_Release(pObj);
        pObj = OBJ_NIL;
    }

    fprintf(stderr, "...%s completed.\n", pTestName);
    return 1;
}



int         test_rrds32_NoBuffers(
    const
    char        *pTestName
)
{
	RRDS32_DATA		*cbp;
    uint32_t        i;
    //bool            fRc;
	char			*pPath     = "/tmp/test.rrds";
    char            block[12]  = "            ";
    char            block2[12] = "            ";
    uint32_t        numRcds = 512;
    uint32_t        cBlock;
    char            *pBlock;
    ERESULT         eRc;

    fprintf(stderr, "Performing: %s\n", pTestName);
    cbp = rrds32_Alloc();
    XCTAssertFalse( (NULL == cbp));
    cbp = rrds32_Init(cbp, 0);
    XCTAssertFalse( (NULL == cbp));

	eRc = rrds32_Create(cbp, pPath, 12, 0);
    XCTAssertFalse( (ERESULT_FAILED(eRc)) );
    XCTAssertTrue( (12 == rrds32_getRecordSize(cbp)));
    
    if (!ERESULT_FAILED(eRc)) {
        for (i=0; i<numRcds; ++i) {
            cBlock = 12;
            pBlock = block;
            dec_putInt32A( i, &cBlock, &pBlock );
            eRc = rrds32_BlockWrite(cbp, i+1, (uint8_t *)block);
            XCTAssertFalse( (ERESULT_FAILED(eRc)) );
            eRc = rrds32_BlockRead(cbp, i+1, (uint8_t *)block2);
            XCTAssertFalse( (ERESULT_FAILED(eRc)) );
            XCTAssertTrue( (0 == memcmp(block, block2, 12)) );
        }
        
        eRc = rrds32_Close( cbp );
        XCTAssertFalse( (ERESULT_FAILED(eRc)) );
        
    }
    
	eRc = rrds32_Open( cbp, pPath );
    XCTAssertFalse( (ERESULT_FAILED(eRc)) );
    XCTAssertTrue( (12 == rrds32_getRecordSize(cbp)) );
    XCTAssertTrue( ('\0' == rrds32_getFillChar(cbp)) );
    
    for (i=0; i<numRcds; ++i) {
        cBlock = 12;
        pBlock = block;
        dec_putInt32A( i, &cBlock, &pBlock );
        //fRc = rrds_BlockWrite(cbp, i+1, block);
        //STAssertTrue( (fRc), @"rrds_BlockWrite failed!" );
        eRc = rrds32_BlockRead(cbp, i+1, (uint8_t *)block2);
        XCTAssertFalse( (ERESULT_FAILED(eRc)) );
        XCTAssertTrue( (0 == memcmp(block, block2, 12)) );
    }
    
	eRc = rrds32_Destroy( cbp );
    XCTAssertFalse( (ERESULT_FAILED(eRc)) );

    obj_Release(cbp);
    cbp = OBJ_NIL;

    fprintf(stderr, "...%s completed.\n", pTestName);
    return 1;
}




TINYTEST_START_SUITE(test_rrds32);
  TINYTEST_ADD_TEST(test_rrds32_NoBuffers,setUp,tearDown);
  TINYTEST_ADD_TEST(test_rrds32_OpenClose,setUp,tearDown);
TINYTEST_END_SUITE();

TINYTEST_MAIN_SINGLE_SUITE(test_rrds32);





