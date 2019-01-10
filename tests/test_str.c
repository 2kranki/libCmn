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
#include    <str_internal.h>



#define NUM_STR     10

/* Other variables */
#ifdef XYZZY
static
char        *StrArray[NUM_STR] = {
	"String 1",
	"String 2",
	"String 3",
	"String 4",
	"String 5",
	"String 6",
	"String 7",
	"String 8",
	"String 9",
	"String 10"
};
#endif



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






int         test_str_Concat(
    const
    char        *pTestName
)
{
	char			test[10];
    bool            fRc;
    int             i;
   
    fprintf(stderr, "Performing: %s\n", pTestName);
    
	fRc = str_Copy( test, sizeof(test), "abc" );
    XCTAssertTrue( (fRc) );
	fRc = str_Concat( test, 10, "def" );
    XCTAssertTrue( (fRc) );
    i = str_Compare(test, "abcdef");
    XCTAssertTrue( (0 == i) );

    fprintf(stderr, "...%s completed.\n", pTestName);
    return 1;
}



int         test_str_CopyFill01(
    const
    char        *pTestName
)
{
    char            test[8];
    bool            fRc;
    int             i;
    
    fprintf(stderr, "Performing: %s\n", pTestName);
    
    fRc = str_CopyFill( test, sizeof(test), "abc", 3, ' ' );
    XCTAssertTrue( (fRc) );
    //                     01234567
    i = str_Compare(test, "abc    ");
    XCTAssertTrue( (0 == i) );
    
    fRc = str_CopyFill( test, sizeof(test), "abc", 5, ' ' );
    XCTAssertTrue( (fRc) );
    //                     01234567
    i = str_Compare(test, "abc    ");
    XCTAssertTrue( (0 == i) );

    fRc = str_CopyFill( test, sizeof(test), "abc", 2, ' ' );
    XCTAssertTrue( (!fRc) );
    //                     01234567
    i = str_Compare(test, "ab     ");
    XCTAssertTrue( (0 == i) );

    fRc = str_CopyFill( test, sizeof(test), "", 0, ' ' );
    XCTAssertTrue( (fRc) );
    //                     01234567
    i = str_Compare(test, "       ");
    XCTAssertTrue( (0 == i) );
    
    fRc = str_CopyFill( test, sizeof(test), NULL, 0, ' ' );
    XCTAssertTrue( (fRc) );
    //                     01234567
    i = str_Compare(test, "       ");
    XCTAssertTrue( (0 == i) );
    
    fprintf(stderr, "...%s completed.\n", pTestName);
    return 1;
}



int         test_str_DupA(
    const
    char        *pTestName
)
{
    int             iRc;
    const
    char            *pStr1;
    const
    char            *pStr2;
    const
    char            *pCon1 = "a";
    
    fprintf(stderr, "Performing: %s\n", pTestName);
    
    pStr1 = str_DupA(pCon1);
    XCTAssertFalse( (NULL == pStr1) );
    iRc = str_Compare(pCon1, pStr1);
    XCTAssertTrue( (iRc == 0) );
    pStr2 = str_DupA(pCon1);
    XCTAssertFalse( (NULL == pStr2) );
    iRc = str_Compare(pCon1, pStr2);
    XCTAssertTrue( (iRc == 0) );
    fprintf(stderr, "str1=%s\n",pStr1);
    iRc = str_Compare(pStr1, pStr2);
    XCTAssertTrue( (iRc == 0) );
    mem_Free((void *)pStr2);
    mem_Free((void *)pStr1);
    
    fprintf(stderr, "...%s completed.\n", pTestName);
    return 1;
}



int         test_str_DupLeft(
    const
    char        *pTestName
)
{
    char            *pszStr;
    
    fprintf(stderr, "Performing: %s\n", pTestName);
    
	pszStr = str_DupLeft(NULL, 3);
    XCTAssertTrue( (NULL == pszStr) );
	pszStr = str_DupLeft("abcdef", 0);
    XCTAssertTrue( (NULL == pszStr) );
	pszStr = str_DupLeft("abcdef", 3);
    XCTAssertFalse( (NULL == pszStr) );
    XCTAssertTrue( (0 == str_Compare("abc", pszStr)) );
    mem_Free(pszStr);
    pszStr = NULL;
	pszStr = str_DupLeft("abc", 3);
    XCTAssertFalse( (NULL == pszStr) );
    XCTAssertTrue( (0 == str_Compare("abc", pszStr)) );
    mem_Free(pszStr);
    pszStr = NULL;
	pszStr = str_DupLeft("ab", 3);
    XCTAssertFalse( (NULL == pszStr) );
    XCTAssertTrue( (0 == str_Compare("ab", pszStr)) );
    mem_Free(pszStr);
    pszStr = NULL;

    fprintf(stderr, "...%s completed.\n", pTestName);
    return 1;
}


int         test_str_DupRight(
    const
    char        *pTestName
)
{
    char            *pszStr;
    
    fprintf(stderr, "Performing: %s\n", pTestName);
    
	pszStr = str_DupRight(NULL, 3);
    XCTAssertTrue( (NULL == pszStr) );
	pszStr = str_DupRight("abcdef", 0);
    XCTAssertTrue( (NULL == pszStr) );
	pszStr = str_DupRight("abcdef", 3);
    XCTAssertTrue( (0 == str_Compare("def", pszStr)) );
    mem_Free(pszStr);
    pszStr = NULL;
	pszStr = str_DupRight("abc", 1);
    XCTAssertTrue( (0 == str_Compare("c", pszStr)) );
    mem_Free(pszStr);
    pszStr = NULL;
	pszStr = str_DupRight("ab", 3);
    XCTAssertTrue( (0 == str_Compare("ab", pszStr)) );
    mem_Free(pszStr);
    pszStr = NULL;

    fprintf(stderr, "...%s completed.\n", pTestName);
    return 1;
}


int         test_str_Lindex(
    const
    char        *pTestName
)
{
    int             iRc;
    
    fprintf(stderr, "Performing: %s\n", pTestName);
    
    iRc = str_Lindex(NULL, '=');
    XCTAssertTrue( (iRc == -1) );
    iRc = str_Lindex("abcdef", '=');
    XCTAssertTrue( (iRc == -1) );
    iRc = str_Lindex("abc=def", '=');
    XCTAssertTrue( (iRc == 3) );
    
    fprintf(stderr, "...%s completed.\n", pTestName);
    return 1;
}




TINYTEST_START_SUITE(test_str);
    TINYTEST_ADD_TEST(test_str_Lindex,setUp,tearDown);
    TINYTEST_ADD_TEST(test_str_DupRight,setUp,tearDown);
    TINYTEST_ADD_TEST(test_str_DupLeft,setUp,tearDown);
    TINYTEST_ADD_TEST(test_str_DupA,setUp,tearDown);
    TINYTEST_ADD_TEST(test_str_CopyFill01,setUp,tearDown);
    TINYTEST_ADD_TEST(test_str_Concat,setUp,tearDown);
TINYTEST_END_SUITE();

TINYTEST_MAIN_SINGLE_SUITE(test_str);





