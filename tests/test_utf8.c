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
#include    <szTbl.h>
#include    <trace.h>
#include    <utf8_internal.h>


// Faked UTF-8 of 0x01..0x04 in 1..4 bytes
static
const
char        *pString1 = "\x01\xC0\x82\xE0\x80\x83\xF8\x80\x80\x84\x00";


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

    
    szTbl_SharedReset( ); 
    trace_SharedReset( ); 
    mem_Dump( );
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



int         test_utf8_ToJSON01(
    const
    char        *pTestName
)
{
    ASTR_DATA	*pAStr = OBJ_NIL;
    static
    const
    char        *pJson2 = "{\"objectType\":\"utf8\", \"crc\":0, \"len\":0, \"data\":null }\n";
    static
    const
    char        *pJson3 = "{\"objectType\":\"utf8\", "
                            "\"crc\":891568578, "
                            "\"len\":3, "
                            "\"data\":[ 97, 98, 99] "
                            "}\n";

    fprintf(stderr, "Performing: %s\n", pTestName);
    
    pAStr = utf8_DataToJSON(NULL);
    TINYTEST_TRUE( (OBJ_NIL == pAStr) );

    pAStr = utf8_DataToJSON("");
    TINYTEST_FALSE( (OBJ_NIL == pAStr) );
    if (pAStr) {
        fprintf(stderr, "\tdata2 = \"%s\"\n", AStr_getData(pAStr));
        TINYTEST_TRUE( (0 == strcmp(pJson2, AStr_getData(pAStr))) );
        obj_Release(pAStr);
        pAStr = OBJ_NIL;
    }

    pAStr = utf8_DataToJSON("abc");
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



int         test_utf8_FromJSON01(
   const
   char        *pTestName
)
{
    ASTR_DATA    *pAStr = OBJ_NIL;
    static
    const
    char        *pJson2 = "{\"objectType\":\"utf8\", \"crc\":0, \"len\":0, \"data\":null }\n";
    static
    const
    char        *pJson3 = "{\"objectType\":\"utf8\", "
                            "\"crc\":891568578, "
                            "\"len\":3, "
                            "\"data\":[ 97, 98, 99] "
                            "}\n";
    ERESULT     eRc;
    uint32_t    len = 0;
    char        *pBuffer = NULL;
    
    fprintf(stderr, "Performing: %s\n", pTestName);
    
    eRc = utf8_DataFromJSONStringA(pJson3, &len, (void **)&pBuffer);
    TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );
    if (!ERESULT_FAILED(eRc)) {
        TINYTEST_TRUE( (3 == len) );
        TINYTEST_TRUE( (0 == strcmp("abc", pBuffer)) );
        mem_Free(pBuffer);
        pBuffer = NULL;
    }
    
    fprintf(stderr, "...%s completed.\n", pTestName);
    return 1;
}




TINYTEST_START_SUITE(test_utf8);
  TINYTEST_ADD_TEST(test_utf8_FromJSON01,setUp,tearDown);
  TINYTEST_ADD_TEST(test_utf8_ToJSON01,setUp,tearDown);
  TINYTEST_ADD_TEST(test_utf8_StrOffset01,setUp,tearDown);
  TINYTEST_ADD_TEST(test_utf8_ChrLen01,setUp,tearDown);
  TINYTEST_ADD_TEST(test_utf8_Scan01,setUp,tearDown);
  TINYTEST_ADD_TEST(test_utf8_OpenClose,setUp,tearDown);
TINYTEST_END_SUITE();

TINYTEST_MAIN_SINGLE_SUITE(test_utf8);





