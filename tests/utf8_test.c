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
#include    <JsonIn.h>
#include    <SrcErrors.h>
#include    <szTbl.h>
#include    <trace.h>
#include    <utf8_internal.h>


// Faked UTF-8 of 0x01..0x04 in 1..4 bytes
static
const
char        *pString1 = "\x01\xC0\x82\xE0\x80\x83\xF8\x80\x80\x84\x00";
static
const
int32_t     string1W32[5] = {0x01, 0x02, 0x03, 0x04, 0};
static
const
char        string1A[5] = {0x01, 0x02, 0x03, 0x04, 0};
static
const
char        string2A[5] = {0x01, 0x02, 0x03, 0x03, 0};
static
const
char        string3A[5] = {0x01, 0x02, 0x03, 0x05, 0};


#ifdef XYZZY
static
const
int32_t         whiteSpace[12] = {
    ' ',
    '\f',
    '\n',
    '\r',
    '\t',
    0x0085,     // Next New Line (Paragraph break)
    0x00A0,     // no-break space
    0x200B,     // zero width space
    0x2060,     // word joiner
    0x3000,     // ideographic space
    0xFEFF,     // zero width no-break space
    0
};
#endif


#ifdef XYZZY
static
const
char        whiteSpaceA[22] = {
    ' ','\f','\n','\r','\t',
    0xC2,0x85,          // Next New Line (Paragraph break)
    0xC2,0xA0,          // no-break space
    0xE2,0x80,0x8B,     // zero width space
    0xE2,0x81,0xA0,     // word joiner
    0xE3,0x80,0x80,     // ideographic space
    0xEF,0xBB,0xBF,     // zero width no-break space
    0
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

    
    SrcErrors_SharedReset( ); 
    szTbl_SharedReset( ); 
    JsonIn_RegisterReset();
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






int         test_utf8_OpenClose(
    const
    char        *pTestName
)
{
    UTF8_DATA	*pObj = OBJ_NIL;
   
    fprintf(stderr, "Performing: %s\n", pTestName);
    
    pObj = utf8_Alloc( );
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    pObj = utf8_Init( pObj );
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    if (pObj) {

        // Test something.

        obj_Release(pObj);
        pObj = OBJ_NIL;
    }

    fprintf(stderr, "...%s completed.\n", pTestName);
    return 1;
}



int         test_utf8_Scan01(
    const
    char        *pTestName
)
{
    uint32_t    i = 0;
    uint32_t    j = 0;
    const
    char        *pStr;
    
    fprintf(stderr, "Performing: %s\n", pTestName);
    
    pStr = pString1;
    for (i=1; i<=4; ++i) {
        j = utf8_Utf8ToW32_Scan(&pStr);
        XCTAssertTrue( (i == j) );
    }
    
    fprintf(stderr, "...%s completed.\n", pTestName);
    return 1;
}



int         test_utf8_ChrLen01(
    const
    char        *pTestName
)
{
    int         len = 0;
    
    fprintf(stderr, "Performing: %s\n", pTestName);
    
    len = utf8_ChrLen(pString1[0]);
    XCTAssertTrue( (1 == len) );
    len = utf8_ChrLen(pString1[1]);
    XCTAssertTrue( (2 == len) );
    len = utf8_ChrLen(pString1[3]);
    XCTAssertTrue( (3 == len) );
    len = utf8_ChrLen(pString1[6]);
    XCTAssertTrue( (4 == len) );
    
    fprintf(stderr, "...%s completed.\n", pTestName);
    return 1;
}



int         test_utf8_StrOffset01(
    const
    char        *pTestName
)
{
    int32_t     len = 0;
    
    fprintf(stderr, "Performing: %s\n", pTestName);
    
    len = utf8_StrOffset(pString1,1);
    XCTAssertTrue( (1 == len) );
    len = utf8_StrOffset(pString1,2);
    XCTAssertTrue( (2 == len) );
    len = utf8_StrOffset(pString1,3);
    XCTAssertTrue( (4 == len) );
    len = utf8_StrOffset(pString1,4);
    XCTAssertTrue( (7 == len) );
    len = utf8_StrOffset(pString1,5);
    XCTAssertTrue( (11 == len) );
    len = utf8_StrOffset(pString1,6);
    XCTAssertTrue( (-1 == len) );
    
    fprintf(stderr, "...%s completed.\n", pTestName);
    return 1;
}



int         test_utf8_JSON01(
    const
    char        *pTestName
)
{
    ASTR_DATA	*pAStr = OBJ_NIL;
    static
    const
    char        *pJson2 = "{ \"objectType\":\"utf8\", \"len\":0, \"crc\":0, \"data\":null }\n";
    static
    const
    char        *pJson3 = "{ \"objectType\":\"utf8\", "
                            "\"len\":3, "
                            "\"crc\":891568578, "
                            "\"data\":\"abc\" "
                            "}\n";

    fprintf(stderr, "Performing: %s\n", pTestName);
    
    pAStr = utf8_DataToJson(NULL);
    TINYTEST_TRUE( (OBJ_NIL == pAStr) );

    pAStr = utf8_DataToJson("");
    TINYTEST_FALSE( (OBJ_NIL == pAStr) );
    if (pAStr) {
        fprintf(stderr, "\tdata2 = \"%s\"\n", AStr_getData(pAStr));
        TINYTEST_TRUE( (0 == strcmp(pJson2, AStr_getData(pAStr))) );
        obj_Release(pAStr);
        pAStr = OBJ_NIL;
    }

    pAStr = utf8_DataToJson("abc");
    TINYTEST_FALSE( (OBJ_NIL == pAStr) );
    if (pAStr) {
        fprintf(stderr, "\tdata3 = \"%s\"\n", AStr_getData(pAStr));
        TINYTEST_TRUE( (0 == strcmp(pJson3, AStr_getData(pAStr))) );
        obj_Release(pAStr);
        pAStr = OBJ_NIL;
    }

    fprintf(stderr, "...%s completed.\n", pTestName);
    return 1;
}



int         test_utf8_JSON02(
   const
   char        *pTestName
)
{
    ASTR_DATA    *pAStr = OBJ_NIL;
    static
    const
    char        *pJson1 = "{ \"objectType\":\"utf8\", "
                            "\"len\":3, "
                            "\"crc\":891568578, "
                            "\"data\":\"abc\" "
                            "}\n";
    uint32_t    len = 0;
    uint8_t     *pBuffer = NULL;
    
    fprintf(stderr, "Performing: %s\n", pTestName);
    
    pAStr = utf8_DataToJson("abc");
    TINYTEST_FALSE( (OBJ_NIL == pAStr) );
    if (pAStr) {
        fprintf(stderr, "\tdata3 = \"%s\"\n", AStr_getData(pAStr));
        TINYTEST_TRUE( (0 == strcmp(pJson1, AStr_getData(pAStr))) );
    }
    
    pBuffer = utf8_DataFromJsonString(pAStr, &len);
    TINYTEST_FALSE( (NULL == pBuffer) );
    TINYTEST_TRUE( (3 == len) );
    TINYTEST_TRUE( (0 == memcmp("abc", pBuffer, len)) );
    mem_Free(pBuffer);
    pBuffer = NULL;
    
    if (pAStr) {
        obj_Release(pAStr);
        pAStr = OBJ_NIL;
    }
    
    fprintf(stderr, "...%s completed.\n", pTestName);
    return 1;
}



int         test_utf8_StrW32_01(
    const
    char        *pTestName
)
{
    int32_t     len = 0;
    W32CHR_T    strW32[9];
    char        strA[25];

    fprintf(stderr, "Performing: %s\n", pTestName);
    
    len = utf8_StrLenA(string1A);
    XCTAssertTrue( (4 == len) );
    len = utf8_StrLenW32(string1W32);
    XCTAssertTrue( (4 == len) );
    len = utf8_StrCmpAW32((const char *)string1A, (const int32_t *)string1W32);
    XCTAssertTrue( (0 == len) );
    len = utf8_StrCmpAW32((const char *)string2A, (const int32_t *)string1W32);
    XCTAssertTrue( (0 > len) );
    len = utf8_StrCmpAW32((const char *)string3A, (const int32_t *)string1W32);
    XCTAssertTrue( (0 < len) );

    len = utf8_W32StrToUtf8Str(0, string1W32, 0, NULL);
    XCTAssertTrue( (len == 5) );
    len = utf8_W32StrToUtf8Str(0, string1W32, 25, strA);
    XCTAssertTrue( (len == 4) );
    len = utf8_StrCmpAW32((const char *)strA, (const int32_t *)string1W32);
    XCTAssertTrue( (0 == len) );

    len = utf8_Utf8StrToW32Str(0, strA, 0, NULL);
    XCTAssertTrue( (5 == len) );
    len = utf8_Utf8StrToW32Str(0, strA, 9, strW32);
    XCTAssertTrue( (4 == len) );
    len = utf8_StrCmpAW32((const char *)strA, (const int32_t *)strW32);
    XCTAssertTrue( (0 == len) );

    strA[0] = '\0';
    len = utf8_Utf8StrToW32Str(0, strA, 0, NULL);
    XCTAssertTrue( (1 == len) );
    strW32[0] = '\0';
    len = utf8_W32StrToUtf8Str(0, strW32, 0, NULL);
    XCTAssertTrue( (1 == len) );

    fprintf(stderr, "...%s completed.\n", pTestName);
    return 1;
}



int         test_utf8_StrW32_02(
    const
    char        *pTestName
)
{
    int32_t     len = 0;
    W32CHR_T    *pW32Str = NULL;
    int         rc;

    
    fprintf(stderr, "Performing: %s\n", pTestName);
    
    len = utf8_StrLenA(string1A);
    fprintf(stderr, "\tlen = %d\n", len);
    XCTAssertTrue( (4 == len) );
    pW32Str = utf8_ChrConToW32Str(string1A);
    XCTAssertFalse( (NULL == pW32Str) );
    len = utf8_StrLenW32(pW32Str);
    XCTAssertTrue( (4 == len) );
    rc = utf8_StrCmpAW32(string1A, pW32Str);
    XCTAssertTrue( (0 == rc) );
    mem_Free(pW32Str);
    pW32Str = NULL;
    
    fprintf(stderr, "...%s completed.\n", pTestName);
    return 1;
}



int         test_utf8_Utf8_01(
    const
    char        *pTestName
)
{
    uint32_t    len = 0;
    int         rc;
    char        str[128];


    fprintf(stderr, "Performing: %s\n", pTestName);

    len = utf8_Utf8ToChrConStr(0, string1A, 128, str);
    fprintf(stderr, "\tlen = %d\n", len);
    fprintf(stderr, "\tstr = %s\n", str);
    XCTAssertTrue( (16 == len) );
    rc = strcmp(str, "\\x01\\x02\\x03\\x04");
    XCTAssertTrue( (0 == rc) );

    fprintf(stderr, "...%s completed.\n", pTestName);
    return 1;
}




TINYTEST_START_SUITE(test_utf8);
  TINYTEST_ADD_TEST(test_utf8_Utf8_01,setUp,tearDown);
  TINYTEST_ADD_TEST(test_utf8_StrW32_02,setUp,tearDown);
  TINYTEST_ADD_TEST(test_utf8_StrW32_01,setUp,tearDown);
  TINYTEST_ADD_TEST(test_utf8_JSON02,setUp,tearDown);
  TINYTEST_ADD_TEST(test_utf8_JSON01,setUp,tearDown);
  TINYTEST_ADD_TEST(test_utf8_StrOffset01,setUp,tearDown);
  TINYTEST_ADD_TEST(test_utf8_ChrLen01,setUp,tearDown);
  TINYTEST_ADD_TEST(test_utf8_Scan01,setUp,tearDown);
  TINYTEST_ADD_TEST(test_utf8_OpenClose,setUp,tearDown);
TINYTEST_END_SUITE();

TINYTEST_MAIN_SINGLE_SUITE(test_utf8);





