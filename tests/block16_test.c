/*
 *	Generated 06/05/2017 21:57:10
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
#include    <block16_internal.h>



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






int         test_cfa_OpenClose(
    const
    char        *pTestName
)
{
    BLOCK16_DATA    *pObj = OBJ_NIL;
    uint32_t        size = 0;
    bool            fRc;
    uint8_t         *pData;
   
    fprintf(stderr, "Performing: %s\n", pTestName);
    
    pObj = block16_NewWithSizes(0, 32);
    XCTAssertFalse( (OBJ_NIL == pObj) );
    if (pObj) {
        size = block16_getHeaderSize(pObj);
        XCTAssertTrue( (0 == size) );
        size = block16_getDataOffset(pObj);
        XCTAssertTrue( (0 == size) );
        size = block16_getDataSize(pObj);
        XCTAssertTrue( (32 == size) );

        obj_Release(pObj);
        pObj = OBJ_NIL;
    }

    pObj = block16_NewWithSizes(8, 31);
    XCTAssertFalse( (OBJ_NIL == pObj) );
    if (pObj) {
        size = block16_getHeaderSize(pObj);
        XCTAssertTrue( (8 == size) );
        size = block16_getDataOffset(pObj);
        XCTAssertTrue( (8 == size) );
        size = block16_getDataSize(pObj);
        XCTAssertTrue( (32 == size) );

        fRc = block16_AddData(pObj, 4, "abcd");
        XCTAssertTrue( (fRc) );
        size = block16_getDataUsed(pObj);
        XCTAssertTrue( (4 == size) );
        
        fRc = block16_AddData(pObj, 4, "abcd");
        XCTAssertTrue( (fRc) );
        size = block16_getDataUsed(pObj);
        XCTAssertTrue( (8 == size) );
        pData = block16_getData(pObj);
        XCTAssertTrue( (0 == strncmp("abcdabcd", (void *)pData, size)) );
        
        obj_Release(pObj);
        pObj = OBJ_NIL;
    }

    fprintf(stderr, "...%s completed.\n", pTestName);
    return 1;
}




TINYTEST_START_SUITE(test_cfa);
  TINYTEST_ADD_TEST(test_cfa_OpenClose,setUp,tearDown);
TINYTEST_END_SUITE();

TINYTEST_MAIN_SINGLE_SUITE(test_cfa);





