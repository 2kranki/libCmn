/*
 *	Generated 10/09/2017 16:11:52
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
#include    <dec_internal.h>



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






int         test_dec_OpenClose(
    const
    char        *pTestName
)
{
    DEC_DATA	*pObj = OBJ_NIL;
   
    fprintf(stderr, "Performing: %s\n", pTestName);

    pObj = dec_Alloc( );
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    pObj = dec_Init( pObj );
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    if (pObj) {

        // Test something.

        obj_Release(pObj);
        pObj = OBJ_NIL;
    }

    fprintf(stderr, "...%s completed.\n", pTestName);
    return 1;
}



int         test_dec_Unsigned32(
    const
    char        *pTestName
)
{
	char            num[11];
    char            *pStr;
    uint32_t        i;
    int32_t         j;

    fprintf(stderr, "Performing: %s\n", pTestName);

    i = 11;
    pStr = num;
    dec_putUint32A( 0, &i, &pStr );
    j = strcmp(num, "0000000000" );
    XCTAssertTrue( (0 == j) );
    j = dec_getInt32A(num);
    XCTAssertTrue( (0 == j) );

    i = 11;
    pStr = num;
    dec_putUint32A( 1, &i, &pStr );
    j = strcmp(num, "0000000001" );
    XCTAssertTrue( (0 == j) );
    j = dec_getInt32A(num);
    XCTAssertTrue( (1 == j) );
    
    i = 11;
    pStr = num;
    dec_putUint32A( -1, &i, &pStr );
    j = strcmp(num, "4294967295" );
    XCTAssertTrue( (0 == j) );
    j = dec_getInt32A(num);
    XCTAssertTrue( (-1 == j) );
    
    fprintf(stderr, "...%s completed.\n", pTestName);
    return 1;
}


int         test_dec_Signed32(
    const
    char        *pTestName
)
{
	char            num[12];
    char            *pStr;
    uint32_t        i;
    int32_t         j;
    
    fprintf(stderr, "Performing: %s\n", pTestName);

    i = 12;
    pStr = num;
    dec_putInt32A( 0, &i, &pStr );
    j = strcmp(num, " 0000000000" );
    XCTAssertTrue( (0 == j) );
    
    i = 12;
    pStr = num;
    dec_putInt32A( 1, &i, &pStr );
    j = strcmp(num, " 0000000001" );
    XCTAssertTrue( (0 == j) );
    
    i = 12;
    pStr = num;
    dec_putInt32A( -1, &i, &pStr );
    j = strcmp(num, "-0000000001" );
    XCTAssertTrue( (0 == j) );
    
    i = 12;
    pStr = num;
    dec_putInt32A( 0x7FFFFFFF, &i, &pStr );
    j = strcmp(num, " 2147483647" );
    XCTAssertTrue( (0 == j) );
    
    i = 12;
    pStr = num;
    dec_putInt32A( 0x80000000, &i, &pStr );
    j = strcmp(num, "-2147483648" );
    XCTAssertTrue( (0 == j) );
    
    fprintf(stderr, "...%s completed.\n", pTestName);
    return 1;
}



int         test_dec_Unsigned64(
    const
    char        *pTestName
)
{
	char            num[32];
    char            *pStr;
    uint32_t        len = 32;
    int64_t         j;

    fprintf(stderr, "Performing: %s\n", pTestName);

    len = 32;
    pStr = num;
    dec_putUint64A( -1, &len, &pStr );
    fprintf(stderr, "num = \"%s\"\n", num);
    j = strcmp(num, "18446744073709551615" );
    XCTAssertTrue( (0 == j) );
    j = dec_getInt64A(num);
    XCTAssertTrue( (-1 == j) );

    len = 32;
    pStr = num;
    dec_putUint64A( 1, &len, &pStr );
    fprintf(stderr, "num = \"%s\"\n", num);
    j = strcmp(num, "00000000000000000001" );
    XCTAssertTrue( (0 == j) );
    j = dec_getInt64A(num);
    XCTAssertTrue( (1 == j) );
    
    len = 32;
    pStr = num;
    dec_putUint64A( 0, &len, &pStr );
    fprintf(stderr, "num = \"%s\"\n", num);
    j = strcmp(num, "00000000000000000000" );
    XCTAssertTrue( (0 == j) );
    j = dec_getInt64A(num);
    XCTAssertTrue( (0 == j) );
    
    fprintf(stderr, "...%s completed.\n", pTestName);
    return 1;
}


int         test_dec_Signed64(
    const
    char        *pTestName
)
{
	char            num[32];
    char            *pStr;
    uint32_t        i;
    int32_t         j;
    
    fprintf(stderr, "Performing: %s\n", pTestName);

    i = 32;
    pStr = num;
    dec_putInt64A( 0x7FFFFFFFFFFFFFFF, &i, &pStr );
    fprintf(stderr, "num = \"%s\"\n", num);
    j = strcmp(num, " 9223372036854775807" );
    XCTAssertTrue( (0 == j) );
    
    i = 32;
    pStr = num;
    dec_putInt64A( 0, &i, &pStr );
    fprintf(stderr, "num = \"%s\"\n", num);
    j = strcmp(num, " 0000000000000000000" );
    XCTAssertTrue( (0 == j) );
    
    i = 32;
    pStr = num;
    dec_putInt64A( 1, &i, &pStr );
    fprintf(stderr, "num = \"%s\"\n", num);
    j = strcmp(num, " 0000000000000000001" );
    XCTAssertTrue( (0 == j) );
    
    i = 32;
    pStr = num;
    dec_putInt64A( -1, &i, &pStr );
    fprintf(stderr, "num = \"%s\"\n", num);
    j = strcmp(num, "-0000000000000000001" );
    XCTAssertTrue( (0 == j) );
    
    i = 32;
    pStr = num;
    dec_putInt64A( 0x8000000000000000, &i, &pStr );
    fprintf(stderr, "num = \"%s\"\n", num);
    j = strcmp(num, "-9223372036854775808" );
    XCTAssertTrue( (0 == j) );
    
    fprintf(stderr, "...%s completed.\n", pTestName);
    return 1;
}



int         test_dec_Int64Dec(
    const
    char        *pTestName
)
{
    char            num[32] = {0};
    uint32_t        cNum = 32;
    char            *pStr = num;
    int32_t         j;
    bool            fRc;
    
    
    fprintf(stderr, "Performing: %s\n", pTestName);

    fRc =   dec_putInt64DecA(
                    -123,                       // Input Number
                    0,                          // Sign: -1 == leading, 0 == none, 1 == trailing
                    false,                      // Align: false == left, true == right
                    false,                      // Fill: false == space fill, true == zero fill
                    8,                          // Field Width
                    2,                          // Decimal Point Position
                    &cNum,                      // Buffer Length
                    &pStr                       // Buffer Ptr
            );
    XCTAssertTrue( (fRc) );
    pStr = num;
    fprintf(stderr, "Need: |1.23    |  Got: |%s|\n", pStr);
    j = strcmp(pStr, "1.23    ");
    XCTAssertTrue( (0 == j) );

    
    // Reset buffer for next.
    for (j=0; j<32; ++j) {
        num[j] = 0;
    }
    cNum = 32;
    pStr = num;
    
    fRc =   dec_putInt64DecA(
                    -123,                       // Input Number
                    -1,                         // Sign: -1 == leading, 0 == none, 1 == trailing
                    false,                      // Align: false == left, true == right
                    false,                      // Fill: false == space fill, true == zero fill
                    8,                          // Field Width
                    2,                          // Decimal Point Position
                    &cNum,                      // Buffer Length
                    &pStr                       // Buffer Ptr
            );
    XCTAssertTrue( (fRc) );
    fprintf(stderr, "Need: |-1.23   | is |%s|\n", num);
    j = strcmp(num, "-1.23   ");
    XCTAssertTrue( (0 == j) );
    
    
    // Reset buffer for next.
    for (j=0; j<32; ++j) {
        num[j] = 0;
    }
    cNum = 32;
    pStr = num;
    
    fRc =   dec_putInt64DecA(
                    -123,                       // Input Number
                    1,                          // Sign: -1 == leading, 0 == none, 1 == trailing
                    false,                      // Align: false == left, true == right
                    false,                      // Fill: false == space fill, true == zero fill
                    8,                          // Field Width
                    2,                          // Decimal Point Position
                    &cNum,                      // Buffer Length
                    &pStr                       // Buffer Ptr
            );
    XCTAssertTrue( (fRc) );
    fprintf(stderr, "Need: |1.23-   | = |%s|\n", num);
    j = strcmp(num, "1.23-   ");
    XCTAssertTrue( (0 == j) );

    
    // Reset buffer for next.
    for (j=0; j<32; ++j) {
        num[j] = 0;
    }
    cNum = 32;
    pStr = num;
    
    fRc =   dec_putInt64DecA(
                    0,                          // Input Number
                    -1,                         // Sign: -1 == leading, 0 == none, 1 == trailing
                    true,                       // Align: false == left, true == right
                    false,                      // Fill: false == space fill, true == zero fill
                    8,                          // Field Width
                    2,                          // Decimal Point Position
                    &cNum,                      // Buffer Length
                    &pStr                       // Buffer Ptr
            );
    XCTAssertTrue( (fRc) );
    fprintf(stderr, "Need: |    0.00|  Got: |%s|\n", num);
    j = strcmp(num, "    0.00");
    XCTAssertTrue( (0 == j) );

    
    // Reset buffer for next.
    for (j=0; j<32; ++j) {
        num[j] = 0;
    }
    cNum = 32;
    pStr = num;
    
    fRc =   dec_putInt64DecA(
                    0,                          // Input Number
                    -1,                         // Sign: -1 == leading, 0 == none, 1 == trailing
                    false,                      // Align: false == left, true == right
                    false,                      // Fill: false == space fill, true == zero fill
                    8,                          // Field Width
                    2,                          // Decimal Point Position
                    &cNum,                      // Buffer Length
                    &pStr                       // Buffer Ptr
            );
    XCTAssertTrue( (fRc) );
    fprintf(stderr, "Need: | 0.00   |  Got: |%s|\n", num);
    j = strcmp(num, " 0.00   ");
    XCTAssertTrue( (0 == j) );

    
    // Reset buffer for next.
    for (j=0; j<32; ++j) {
        num[j] = 0;
    }
    cNum = 32;
    pStr = num;
    
    fRc =   dec_putInt64DecA(
                             0,                          // Input Number
                             0,                          // Sign: -1 == leading, 0 == none, 1 == trailing
                             false,                      // Align: false == left, true == right
                             false,                      // Fill: false == space fill, true == zero fill
                             8,                          // Field Width
                             0,                          // Decimal Point Position
                             &cNum,                      // Buffer Length
                             &pStr                       // Buffer Ptr
                             );
    XCTAssertTrue( (fRc) );
    fprintf(stderr, "Need: |0       |  Got: |%s|\n", num);
    j = strcmp(num, "0       ");
    XCTAssertTrue( (0 == j) );
    
    
    // Reset buffer for next.
    for (j=0; j<32; ++j) {
        num[j] = 0;
    }
    cNum = 32;
    pStr = num;
    
    fRc =   dec_putInt64DecA(
                             0,                          // Input Number
                             0,                          // Sign: -1 == leading, 0 == none, 1 == trailing
                             true,                       // Align: false == left, true == right
                             false,                      // Fill: false == space fill, true == zero fill
                             8,                          // Field Width
                             0,                          // Decimal Point Position
                             &cNum,                      // Buffer Length
                             &pStr                       // Buffer Ptr
                             );
    XCTAssertTrue( (fRc) );
    fprintf(stderr, "Need: |       0|  Got: |%s|\n", num);
    j = strcmp(num, "       0");
    XCTAssertTrue( (0 == j) );
    
    
    // Reset buffer for next.
    for (j=0; j<32; ++j) {
        num[j] = 0;
    }
    cNum = 32;
    pStr = num;
    
    fRc =   dec_putInt64DecA(
                             1300000,                    // Input Number
                             0,                          // Sign: -1 == leading, 0 == none, 1 == trailing
                             true,                       // Align: false == left, true == right
                             false,                      // Fill: false == space fill, true == zero fill
                             10,                         // Field Width
                             3,                          // Decimal Point Position
                             &cNum,                      // Buffer Length
                             &pStr                       // Buffer Ptr
                             );
    XCTAssertTrue( (fRc) );
    fprintf(stderr, "Need: |  1300.000|  Got: |%s|\n", num);
    j = strcmp(num, "  1300.000");
    XCTAssertTrue( (0 == j) );
    
    fprintf(stderr, "...%s completed.\n", pTestName);
    return 1;
}





TINYTEST_START_SUITE(test_dec);
    TINYTEST_ADD_TEST(test_dec_Int64Dec,setUp,tearDown);
    TINYTEST_ADD_TEST(test_dec_Signed64,setUp,tearDown);
    TINYTEST_ADD_TEST(test_dec_Unsigned64,setUp,tearDown);
    TINYTEST_ADD_TEST(test_dec_Signed32,setUp,tearDown);
    TINYTEST_ADD_TEST(test_dec_Unsigned32,setUp,tearDown);
    TINYTEST_ADD_TEST(test_dec_OpenClose,setUp,tearDown);
TINYTEST_END_SUITE();

TINYTEST_MAIN_SINGLE_SUITE(test_dec);





