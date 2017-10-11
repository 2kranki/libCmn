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
    mem_Dump( );
    mem_Release( );
    
    return 1; 
}






int         test_scanDec32_Test01(
    const
    char        *pTestName
)
{
	char        *testString = " 1";
    bool        fRc;
    char        *pCurChr = testString;
    uint32_t    cScanned = 0;
    uint32_t    value = 0;
   
    fprintf(stderr, "Performing: %s\n", pTestName);
    
	fRc = scanDec32( &pCurChr, &cScanned, &value );
    XCTAssertTrue( (fRc) );
    XCTAssertTrue( ('\0' == *pCurChr) );
    XCTAssertTrue( (2 == cScanned) );
    XCTAssertTrue( (1 == value) );

    fprintf(stderr, "...%s completed.\n", pTestName);
    return 1;
}



int         test_scanDec32_Test02(
    const
    char        *pTestName
)
{
	char        *testString = " -1 ";
    bool        fRc;
    char        *pCurChr = testString;
    uint32_t    cScanned = 0;
    uint32_t    value = 0;
   
    fprintf(stderr, "Performing: %s\n", pTestName);
    
	fRc = scanDec32( &pCurChr, &cScanned, &value );
    XCTAssertTrue( (fRc) );
    XCTAssertTrue( (' ' == *pCurChr) );
    XCTAssertTrue( (3 == cScanned) );
    XCTAssertTrue( (0xFFFFFFFF == value) );

    fprintf(stderr, "...%s completed.\n", pTestName);
    return 1;
}




TINYTEST_START_SUITE(test_scanDec32);
  TINYTEST_ADD_TEST(test_scanDec32_Test02,setUp,tearDown);
  TINYTEST_ADD_TEST(test_scanDec32_Test01,setUp,tearDown);
TINYTEST_END_SUITE();

TINYTEST_MAIN_SINGLE_SUITE(test_scanDec32);





