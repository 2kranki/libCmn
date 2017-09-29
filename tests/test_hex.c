


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

    fprintf(stderr, "...%s completed.\n", pTestName);
    return 1;
}



int         test_hex_DataFromJSON01(
    const
    char        *pTestName
)
{
    ASTR_DATA	*pStr = OBJ_NIL;
    char        *pData = "\x00\x01\x02\x03\x04\x05\x06\x07";
    char        *pOutput =  "{\"objectType\":\"hex\", "
                            "\"len\":8, "
                            "\"crc\":-2002098017, "
                            "\"data\":\"0001020304050607\""
                            "}\n";
    ERESULT     eRc;
    uint32_t    length = 0;
    uint8_t     *pData2 = NULL;
   
    fprintf(stderr, "Performing: %s\n", pTestName);
    eRc = hex_DataFromJSONStringA(pOutput, &length, (void **)&pData2);
    TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );
    fprintf(stderr, "returned length = %d\n", length);
    TINYTEST_TRUE( (8 == length) );
    TINYTEST_TRUE( (0 == strncmp((char *)pData2, pData, 8)) );
    mem_Free(pData2);
    pData2 = NULL;

    fprintf(stderr, "...%s completed.\n", pTestName);
    return 1;
}




int         test_hex_DataToJSON01(
    const
    char        *pTestName
)
{
    ASTR_DATA	*pStr = OBJ_NIL;
    char        *pData = "\x00\x01\x02\x03\x04\x05\x06\x07";
    char        *pOutput =  "{\"objectType\":\"hex\", "
                            "\"len\":8, "
                            "\"crc\":-2002098017, "
                            "\"data\":\"0001020304050607\""
                            "}\n";
   
    fprintf(stderr, "Performing: %s\n", pTestName);
    pStr = hex_DataToJSON(8, pData);
    TINYTEST_TRUE( (0 == strcmp(pOutput, AStr_getData(pStr))) );
    fprintf(stderr, "JSON='%s'\n", AStr_getData(pStr));
    obj_Release(pStr);
    pStr = OBJ_NIL;

    fprintf(stderr, "...%s completed.\n", pTestName);
    return 1;
}




TINYTEST_START_SUITE(test_hex);
  TINYTEST_ADD_TEST(test_hex_DataToJSON01,setUp,tearDown);
  TINYTEST_ADD_TEST(test_hex_DataFromJSON01,setUp,tearDown);
  TINYTEST_ADD_TEST(test_hex_OpenClose,setUp,tearDown);
TINYTEST_END_SUITE();

TINYTEST_MAIN_SINGLE_SUITE(test_hex);





