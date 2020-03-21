


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
#include    <hex_internal.h>
#include    <SrcErrors.h>
#include    <szTbl.h>



int         setUp(
    const
    char        *pTestName
)
{
    mem_Init( );
    //trace_Shared( );
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
    //trace_SharedReset( );
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






int         test_hex_OpenClose(
    const
    char        *pTestName
)
{
    HEX_DATA	*pObj = OBJ_NIL;
   
    fprintf(stderr, "Performing: %s\n", pTestName);
    pObj = hex_Alloc( );
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    pObj = hex_Init( pObj );
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    if (pObj) {

        // Test something.

        obj_Release(pObj);
        pObj = OBJ_NIL;
    }

    fprintf(stderr, "...%s completed.\n\n\n", pTestName);
    return 1;
}



int         test_hex_JSON01(
    const
    char        *pTestName
)
{
    ASTR_DATA	*pStr = OBJ_NIL;
    char        *pData = "\x00\x01\x02\x03\x04\x05\x06\x07";
    char        *pOutput =  "{\"objectType\":\"hex\", "
                            "\"len\":8, "
                            "\"crc\":2292869279, "
                            "\"data\":\"0001020304050607\""
                            "}\n";
    uint32_t    length = 0;
    uint8_t     *pData2 = NULL;
   
    fprintf(stderr, "Performing: %s\n", pTestName);

    fprintf(stderr, "\tTesting ToJSON...\n");
    pStr = hex_DataToJSON( 8, (void *)pData);
    fprintf(stderr, "\tJSON='%s'\n", AStr_getData(pStr));
    TINYTEST_TRUE( (0 == strcmp(pOutput, AStr_getData(pStr))) );
    fprintf(stderr, "\tToJSON passed!\n");

    fprintf(stderr, "\n\tTesting FromJSON...\n");
    pData2 = hex_DataFromJSONString(pStr, &length);
    fprintf(stderr, "\treturned length = %d\n", length);
    fprintf(stderr, "\treturned data = %p\n", pData2);
    TINYTEST_TRUE( (8 == length) );
    TINYTEST_TRUE( (0 == memcmp(pData2, pData, 8)) );
    fprintf(stderr, "\tFromJSON passed!\n");

    mem_Free(pData2);
    pData2 = NULL;
    obj_Release(pStr);
    pStr = OBJ_NIL;

    fprintf(stderr, "...%s completed.\n\n\n", pTestName);
    return 1;
}




int         test_hex_Shared01(
    const
    char            *pTestName
)
{
    char            buffer[2048];
    char            *pBuffer = buffer;
    uint32_t        cBuffer = 2048;
    uint32_t        used = 0;
    static
    const
    char            *pOutput = "00000000  30313233 34353637 38394142 43444546"
                                "  *0123456789ABCDEF*";

    fprintf(stderr, "Performing: %s\n", pTestName);
    
    used =  hex_put16Bytes_32(
                hex_Shared(),
                0,
                16,
                (void *)"0123456789ABCDEF",
                &cBuffer,
                &pBuffer
            );
    *pBuffer = '\0';
    fprintf(stderr, "\t(%d) \"%s\"\n", used, buffer);
    TINYTEST_TRUE( (65 == used) );
    TINYTEST_TRUE( (0 == strcmp(buffer, pOutput)) );

    hex_SharedReset();
    fprintf(stderr, "...%s completed.\n\n\n", pTestName);
    return 1;
}



int         test_hex_Shared02(
    const
    char            *pTestName
)
{
    char            buffer[2048];
    char            *pBuffer = buffer;
    uint32_t        cBuffer = 2048;
    uint32_t        used = 0;
    static
    const
    char            *pOutput =  "00000000  30313233 34353637 3839               "
                                "*0123456789      *";
    
    fprintf(stderr, "Performing: %s\n", pTestName);
    
    used =  hex_put16Bytes_32(
                              hex_Shared(),
                              0,
                              10,
                              (void *)"0123456789ABCDEF",
                              &cBuffer,
                              &pBuffer
                              );
    *pBuffer = '\0';
    fprintf(stderr, "\t(%d) \"%s\"\n", used, buffer);
    TINYTEST_TRUE( (65 == used) );
    TINYTEST_TRUE( (0 == strcmp(buffer, pOutput)) );
    
    hex_SharedReset();
    fprintf(stderr, "...%s completed.\n\n\n", pTestName);
    return 1;
}



int         test_hex_Shared03(
    const
    char            *pTestName
)
{
    char            buffer[2048];
    char            *pBuffer = buffer;
    uint32_t        cBuffer = 2048;
    uint32_t        used = 0;
    static
    const
    char            *pOutput =  "0000000000000000  30313233 34353637 3839               "
    "*0123456789      *";
    
    fprintf(stderr, "Performing: %s\n", pTestName);
    
    used =  hex_put16Bytes_64(
                              hex_Shared(),
                              0,
                              10,
                              (void *)"0123456789ABCDEF",
                              &cBuffer,
                              &pBuffer
                              );
    *pBuffer = '\0';
    fprintf(stderr, "\t(%d) \"%s\"\n", used, buffer);
    TINYTEST_TRUE( (73 == used) );
    TINYTEST_TRUE( (0 == strcmp(buffer, pOutput)) );
    
    hex_SharedReset();
    fprintf(stderr, "...%s completed.\n\n\n", pTestName);
    return 1;
}



int         test_hex_ScanData01(
    const
    char            *pTestName
)
{
    ERESULT         eRc;
    char            *pBuffer = NULL;
    static
    const
    char            *pInput =  "0123456789abcdef";
    const
    char            *pOutputCheck =  "\x01\x23\x45\x67\x89\xab\xcd\xef";
    const
    int             outputLength = 8;
    VALUE_DATA      *pValue = OBJ_NIL;
    
    fprintf(stderr, "Performing: %s\n", pTestName);
    
    eRc =   hex_ScanData(
                16,
                pInput,
                &pValue
            );
    TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );
    TINYTEST_TRUE( (pValue) );
    TINYTEST_TRUE( (outputLength == Value_getDataLen(pValue)) );
    pBuffer = (char *)Value_getData(pValue);
    TINYTEST_TRUE( (0 == memcmp(pBuffer, pOutputCheck, outputLength)) );
    obj_Release(pValue);
    pValue = OBJ_NIL;
    
    fprintf(stderr, "...%s completed.\n\n\n", pTestName);
    return 1;
}




TINYTEST_START_SUITE(test_hex);
    TINYTEST_ADD_TEST(test_hex_ScanData01,setUp,tearDown);
    TINYTEST_ADD_TEST(test_hex_Shared03,setUp,tearDown);
    TINYTEST_ADD_TEST(test_hex_Shared02,setUp,tearDown);
    TINYTEST_ADD_TEST(test_hex_Shared01,setUp,tearDown);
    TINYTEST_ADD_TEST(test_hex_JSON01,setUp,tearDown);
    TINYTEST_ADD_TEST(test_hex_OpenClose,setUp,tearDown);
TINYTEST_END_SUITE();

TINYTEST_MAIN_SINGLE_SUITE(test_hex);





