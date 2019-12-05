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
#include    <ascii_internal.h>



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






int         test_ascii_OpenClose(
    const
    char        *pTestName
)
{
    ASCII_DATA	*pObj = OBJ_NIL;
   
    fprintf(stderr, "Performing: %s\n", pTestName);
 
    pObj = ascii_Alloc( );
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    pObj = ascii_Init( pObj );
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    if (pObj) {

        // Test something.

        obj_Release(pObj);
        pObj = OBJ_NIL;
    }

    fprintf(stderr, "...%s completed.\n", pTestName);
    return 1;
}



int         test_ascii_Lexical01(
    const
    char        *pTestName
)
{
    
    
    fprintf(stderr, "Performing: %s\n", pTestName);
 
    XCTAssertTrue( (ASCII_LEXICAL_WHITESPACE == ascii_toLexicalClassA(' ')) );
    XCTAssertTrue( (ASCII_LEXICAL_WHITESPACE == ascii_toLexicalClassA('\r')) );
    XCTAssertTrue( (ASCII_LEXICAL_EOL == ascii_toLexicalClassA('\n')) );
    XCTAssertTrue( (ASCII_LEXICAL_WHITESPACE == ascii_toLexicalClassA('\t')) );
    XCTAssertTrue( (ASCII_LEXICAL_WHITESPACE == ascii_toLexicalClassA('\f')) );
    XCTAssertTrue( (ASCII_LEXICAL_NUMBER == ascii_toLexicalClassA('0')) );
    XCTAssertTrue( (ASCII_LEXICAL_NUMBER == ascii_toLexicalClassA('9')) );
    XCTAssertTrue( (ASCII_LEXICAL_ALPHA_UPPER == ascii_toLexicalClassA('A')) );
    XCTAssertTrue( (ASCII_LEXICAL_ALPHA_UPPER == ascii_toLexicalClassA('Z')) );
    XCTAssertTrue( (ASCII_LEXICAL_ALPHA_LOWER == ascii_toLexicalClassA('a')) );
    XCTAssertTrue( (ASCII_LEXICAL_ALPHA_LOWER == ascii_toLexicalClassA('z')) );
    XCTAssertTrue( ('!' == ascii_toLexicalClassA('!')) );
    XCTAssertTrue( (')' == ascii_toLexicalClassA(')')) );
    XCTAssertTrue( ('(' == ascii_toLexicalClassA('(')) );
    XCTAssertTrue( ('/' == ascii_toLexicalClassA('/')) );
    XCTAssertTrue( (':' == ascii_toLexicalClassA(':')) );
    XCTAssertTrue( ('@' == ascii_toLexicalClassA('@')) );
    XCTAssertTrue( ('[' == ascii_toLexicalClassA('[')) );
    XCTAssertTrue( (']' == ascii_toLexicalClassA(']')) );
    XCTAssertTrue( ('`' == ascii_toLexicalClassA('`')) );
    XCTAssertTrue( ('{' == ascii_toLexicalClassA('{')) );
    XCTAssertTrue( ('|' == ascii_toLexicalClassA('|')) );
    XCTAssertTrue( ('}' == ascii_toLexicalClassA('}')) );
    XCTAssertTrue( ('-' == ascii_toLexicalClassA('-')) );
    
    fprintf(stderr, "...%s completed.\n", pTestName);
    return 1;
}




TINYTEST_START_SUITE(test_ascii);
  TINYTEST_ADD_TEST(test_ascii_Lexical01,setUp,tearDown);
  TINYTEST_ADD_TEST(test_ascii_OpenClose,setUp,tearDown);
TINYTEST_END_SUITE();

TINYTEST_MAIN_SINGLE_SUITE(test_ascii);





