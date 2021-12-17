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






int         test_scanString_Test01(
    const
    char        *pTestName
)
{
	char        *testString;
    bool        fRc;
    char        *pCurChr;
    uint32_t    cScanned = 0;
    char        string[64];
   
    fprintf(stderr, "Performing: %s\n", pTestName);
    
   testString = " abc";
    pCurChr = testString;
	fRc = scanString( &pCurChr, 64, &cScanned, string );
    XCTAssertTrue( (fRc) );
    XCTAssertTrue( ((testString + 4) == pCurChr) );
    XCTAssertTrue( (3 == cScanned) );
    XCTAssertTrue( (0 == strncmp(testString+1, string, cScanned)) );
    XCTAssertTrue( (*pCurChr == '\0') );

    fprintf(stderr, "...%s completed.\n", pTestName);
    return 1;
}



int         test_scanString_Test02(
    const
    char        *pTestName
)
{
	char        *testString;
    bool        fRc;
    char        *pCurChr;
    uint32_t    cScanned = 0;
    char        string[64];
   
    fprintf(stderr, "Performing: %s\n", pTestName);
    
    testString = " abc ";
    pCurChr = testString;
	fRc = scanString( &pCurChr, 64, &cScanned, string );
    XCTAssertTrue( (fRc) );
    XCTAssertTrue( ((testString + 4) == pCurChr) );
    XCTAssertTrue( (3 == cScanned) );
    XCTAssertTrue( (0 == strncmp(testString+1, string, cScanned)) );
    XCTAssertTrue( (*pCurChr == ' ') );

    fprintf(stderr, "...%s completed.\n", pTestName);
    return 1;
}



int         test_scanString_Test03(
    const
    char        *pTestName
)
{
	char        *testString;
    bool        fRc;
    char        *pCurChr;
    uint32_t    cScanned = 0;
    char        string[64];
   
    fprintf(stderr, "Performing: %s\n", pTestName);
    
    testString = " abc,";
    pCurChr = testString;
	fRc = scanString( &pCurChr, 64, &cScanned, string );
    XCTAssertTrue( (fRc) );
    XCTAssertTrue( ((testString + 4) == pCurChr) );
    XCTAssertTrue( (3 == cScanned) );
    XCTAssertTrue( (0 == strncmp(testString+1, string, cScanned)) );
    XCTAssertTrue( (*pCurChr == ',') );

    fprintf(stderr, "...%s completed.\n", pTestName);
    return 1;
}



int         test_scanString_Test04(
    const
    char        *pTestName
)
{
	char        *testString;
    bool        fRc;
    char        *pCurChr;
    uint32_t    cScanned = 0;
    char        string[64];
   
    fprintf(stderr, "Performing: %s\n", pTestName);
    
    testString = " abc=";
    pCurChr = testString;
	fRc = scanString( &pCurChr, 64, &cScanned, string );
    XCTAssertTrue( (fRc) );
    XCTAssertTrue( ((testString + 4) == pCurChr) );
    XCTAssertTrue( (3 == cScanned) );
    XCTAssertTrue( (0 == strncmp(testString+1, string, cScanned)) );
    XCTAssertTrue( (*pCurChr == '=') );

    fprintf(stderr, "...%s completed.\n", pTestName);
    return 1;
}



int         test_scanString_Test05(
    const
    char        *pTestName
)
{
	char        *testString;
    bool        fRc;
    char        *pCurChr;
    uint32_t    cScanned = 0;
    char        string[64];
   
    fprintf(stderr, "Performing: %s\n", pTestName);
    
    testString = " 'abc' ";
    pCurChr = testString;
	fRc = scanString( &pCurChr, 64, &cScanned, string );
    XCTAssertTrue( (fRc) );
    XCTAssertTrue( ((testString + 6) == pCurChr) );
    XCTAssertTrue( (3 == cScanned) );
    XCTAssertTrue( (0 == strncmp(testString+2, string, cScanned)) );

    fprintf(stderr, "...%s completed.\n", pTestName);
    return 1;
}



int         test_scanString_Test06(
    const
    char        *pTestName
)
{
	char        *testString;
    bool        fRc;
    char        *pCurChr;
    uint32_t    cScanned = 0;
    char        string[64];
   
    fprintf(stderr, "Performing: %s\n", pTestName);
    
    testString = " 'abc\\n\\r' ";
    pCurChr = testString;
	fRc = scanString( &pCurChr, 64, &cScanned, string );
    XCTAssertTrue( (fRc) );
    XCTAssertTrue( (5 == cScanned) );
    XCTAssertTrue( (0 == strncmp("abc\n\r", string, cScanned)) );
    XCTAssertTrue( ((testString + 10) == pCurChr) );

    fprintf(stderr, "...%s completed.\n", pTestName);
    return 1;
}



int         test_scanString_Test07(
    const
    char        *pTestName
)
{
	char        *testString;
    bool        fRc;
    char        *pCurChr;
    uint32_t    cScanned = 0;
    char        string[64];
   
    fprintf(stderr, "Performing: %s\n", pTestName);
    
    testString = " 'abc\\x11' ";
    pCurChr = testString;
	fRc = scanString( &pCurChr, 64, &cScanned, string );
    XCTAssertTrue( (fRc) );
    XCTAssertTrue( (4 == cScanned) );
    XCTAssertTrue( (0 == strncmp("abc\x11", string, cScanned)) );
    XCTAssertTrue( ((testString + 10) == pCurChr) );

    fprintf(stderr, "...%s completed.\n", pTestName);
    return 1;
}




TINYTEST_START_SUITE(test_scanString);
  TINYTEST_ADD_TEST(test_scanString_Test07,setUp,tearDown);
  TINYTEST_ADD_TEST(test_scanString_Test06,setUp,tearDown);
  TINYTEST_ADD_TEST(test_scanString_Test05,setUp,tearDown);
  TINYTEST_ADD_TEST(test_scanString_Test04,setUp,tearDown);
  TINYTEST_ADD_TEST(test_scanString_Test03,setUp,tearDown);
  TINYTEST_ADD_TEST(test_scanString_Test02,setUp,tearDown);
  TINYTEST_ADD_TEST(test_scanString_Test01,setUp,tearDown);
TINYTEST_END_SUITE();

TINYTEST_MAIN_SINGLE_SUITE(test_scanString);





