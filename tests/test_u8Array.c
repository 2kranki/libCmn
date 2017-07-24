/*
 *	Generated 06/30/2017 09:01:13
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
#include    <u8Array_internal.h>



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






int         test_u8Array_OpenClose(
    const
    char        *pTestName
)
{
    U8ARRAY_DATA *pObj = OBJ_NIL;
   
    pObj = u8Array_Alloc(0);
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    pObj = u8Array_Init( pObj );
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    if (pObj) {

        // Test something.

        obj_Release(pObj);
        pObj = OBJ_NIL;
    }

    return 1;
}



int         test_u8Array_AddGet01(
    const
    char        *pTestName
)
{
    U8ARRAY_DATA	*pObj = OBJ_NIL;
    uint32_t        i;
    ERESULT         eRc;
    uint8_t         data;
    
    pObj = u8Array_Alloc(0);
    XCTAssertFalse( (OBJ_NIL == pObj) );
    pObj = u8Array_Init( pObj );
    XCTAssertFalse( (OBJ_NIL == pObj) );
    if (pObj) {
        
        data = 0;
        for (i=1; i<=64; ++i) {
            eRc = u8Array_AppendData(pObj, i);
            XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
        }
        
        for (i=1; i<=64; ++i) {
            data = u8Array_Get(pObj, i);
            XCTAssertTrue( (data == i) );
        }
        
        obj_Release(pObj);
        pObj = OBJ_NIL;
    }
    
    return 1;
}



int         test_u8Array_InsertData01(
    const
    char        *pTestName
)
{
    U8ARRAY_DATA	*pObj = OBJ_NIL;
    uint32_t        i;
    ERESULT         eRc;
    uint8_t         data;
    const
    char            *pTest1 = "abc";
    const
    char            *pTest2 = "def";
    const
    char            *pTest3 = "abdefc";
    
    pObj = u8Array_Alloc(0);
    XCTAssertFalse( (OBJ_NIL == pObj) );
    pObj = u8Array_Init( pObj );
    XCTAssertFalse( (OBJ_NIL == pObj) );
    if (pObj) {
        
        eRc = u8Array_InsertData(
                        pObj,
                        1,
                        (uint32_t)strlen(pTest1),
                        (const uint8_t *)pTest1
            );
        XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
        
        eRc = u8Array_InsertData(
                                 pObj,
                                 u8Array_getSize(pObj),
                                 (uint32_t)strlen(pTest2),
                                 (const uint8_t *)pTest2
                                 );
        XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
        
        i = (uint32_t)(strlen(pTest1) + strlen(pTest2));
        XCTAssertTrue( (i == u8Array_getSize(pObj)) );
        
        for (i=1; i<=strlen(pTest3); ++i) {
            data = u8Array_Get(pObj, i);
            XCTAssertTrue( (data == pTest3[i-1]) );
        }
        
        obj_Release(pObj);
        pObj = OBJ_NIL;
    }
    
    return 1;
}



int         test_u8Array_InsertData02(
    const
    char        *pTestName
)
{
    U8ARRAY_DATA	*pObj = OBJ_NIL;
    uint32_t        i;
    ERESULT         eRc;
    uint8_t         data;
    const
    char            *pTest1 = "abc";
    const
    char            *pTest2 = "def";
    const
    char            *pTest3 = "abcdef";
    
    pObj = u8Array_Alloc(0);
    XCTAssertFalse( (OBJ_NIL == pObj) );
    pObj = u8Array_Init( pObj );
    XCTAssertFalse( (OBJ_NIL == pObj) );
    if (pObj) {
        
        eRc = u8Array_InsertData(
                                 pObj,
                                 1,
                                 (uint32_t)strlen(pTest1),
                                 (const uint8_t *)pTest1
                                 );
        XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
        
        eRc = u8Array_InsertData(
                                 pObj,
                                 (u8Array_getSize(pObj)+1),
                                 (uint32_t)strlen(pTest2),
                                 (const uint8_t *)pTest2
                                 );
        XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
        
        i = (uint32_t)(strlen(pTest1) + strlen(pTest2));
        XCTAssertTrue( (i == u8Array_getSize(pObj)) );
        
        for (i=1; i<=strlen(pTest3); ++i) {
            data = u8Array_Get(pObj, i);
            XCTAssertTrue( (data == pTest3[i-1]) );
        }
        
        obj_Release(pObj);
        pObj = OBJ_NIL;
    }
    
    return 1;
}



int         test_u8Array_InsertData03(
    const
    char        *pTestName
)
{
    U8ARRAY_DATA	*pObj = OBJ_NIL;
    uint32_t        i;
    ERESULT         eRc;
    uint8_t         data;
    const
    char            *pTest1 = "abc";
    const
    char            *pTest2 = "def";
    const
    char            *pTest3 = "defabc";
    
    pObj = u8Array_Alloc(0);
    XCTAssertFalse( (OBJ_NIL == pObj) );
    pObj = u8Array_Init( pObj );
    XCTAssertFalse( (OBJ_NIL == pObj) );
    if (pObj) {
        
        eRc = u8Array_InsertData(
                                 pObj,
                                 1,
                                 (uint32_t)strlen(pTest1),
                                 (const uint8_t *)pTest1
                                 );
        XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
        
        eRc = u8Array_InsertData(
                                 pObj,
                                 1,
                                 (uint32_t)strlen(pTest2),
                                 (const uint8_t *)pTest2
                                 );
        XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
        
        i = (uint32_t)(strlen(pTest1) + strlen(pTest2));
        XCTAssertTrue( (i == u8Array_getSize(pObj)) );
        
        for (i=1; i<=strlen(pTest3); ++i) {
            data = u8Array_Get(pObj, i);
            XCTAssertTrue( (data == pTest3[i-1]) );
        }
        
        obj_Release(pObj);
        pObj = OBJ_NIL;
    }
    
    return 1;
}



int         test_u8Array_PutGet01(
    const
    char        *pTestName
)
{
    U8ARRAY_DATA	*pObj = OBJ_NIL;
    uint32_t        i;
    ERESULT         eRc;
    uint16_t        data16 = 0;
    uint32_t        data32 = 0;
    
    pObj = u8Array_Alloc( );
    XCTAssertFalse( (OBJ_NIL == pObj) );
    pObj = u8Array_Init( pObj );
    XCTAssertFalse( (OBJ_NIL == pObj) );
    if (pObj) {
        
        eRc = u8Array_PutU16(pObj, 1, 12345);
        XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
        i = u8Array_getSize(pObj);
        XCTAssertTrue( (i == 2) );
        
        data16 = 0;
        eRc = u8Array_GetU16(pObj, 1, &data16);
        fprintf(stderr, "data = %d\n", data16);
        XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
        XCTAssertTrue( (data16 == 12345) );
        
        eRc = u8Array_PutU24(pObj, 1, 12345678);
        XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
        i = u8Array_getSize(pObj);
        XCTAssertTrue( (i == 3) );
        
        data32 = 0;
        eRc = u8Array_GetU24(pObj, 1, &data32);
        fprintf(stderr, "data = %d\n", data32);
        XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
        XCTAssertTrue( (data32 == 12345678) );
        
        eRc = u8Array_PutU32(pObj, 1, 12345678);
        XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
        i = u8Array_getSize(pObj);
        XCTAssertTrue( (i == 4) );
        
        data32 = 0;
        eRc = u8Array_GetU32(pObj, 1, &data32);
        fprintf(stderr, "data = %d\n", data32);
        XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
        XCTAssertTrue( (data32 == 12345678) );
        
        obj_Release(pObj);
        pObj = OBJ_NIL;
    }
    
    return 1;
}



int         test_u8Array_ToCostantString01(
    const
    char        *pTestName
)
{
    U8ARRAY_DATA	*pObj = OBJ_NIL;
    uint32_t        i;
    ERESULT         eRc;
    uint8_t         data;
    ASTR_DATA       *pStr = OBJ_NIL;
    const
    char            *pStrCon =  "\\x00\\x01\\x02\\x03\\x04\\x05\\x06\\x07\\x08"
                                "\\t\\n\\x0B\\f\\r\\x0E\\x0F"
                                "\\x10\\x11\\x12\\x13\\x14\\x15\\x16\\x17"
                                "\\x18\\x19\\x1A\\x1B\\x1C\\x1D\\x1E\\x1F"
                                " !\"#$%&'()*+,-./0123456789:;<=>?"
                                "@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]^_"
                                "`abcdefghijklmnopqrstuvwxyz{|}~\\x7F";
    
    pObj = u8Array_Alloc(0);
    XCTAssertFalse( (OBJ_NIL == pObj) );
    pObj = u8Array_Init( pObj );
    XCTAssertFalse( (OBJ_NIL == pObj) );
    if (pObj) {
        
        data = 0;
        for (i=0; i<128; ++i) {
            eRc = u8Array_AppendData(pObj, i);
            XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
        }
        fprintf(stderr, "u8Array length = %u\n",  u8Array_getSize(pObj));
        XCTAssertTrue( (128 == u8Array_getSize(pObj)) );
        
        for (i=0; i<128; ++i) {
            data = u8Array_Get(pObj, i+1);
            XCTAssertTrue( (data == i) );
        }
        
        pStr = u8Array_ToConstantString(pObj);
        XCTAssertFalse( (OBJ_NIL == pStr) );
        i = AStr_getLength(pStr);
        XCTAssertTrue( (219 == i) );
        fprintf(stderr, "constant length = %d\n", i);
        fprintf(stderr, "constant = \"%s\"\n", AStr_getData(pStr));
        fprintf(stderr, "strcon length = %zu\n", str_LengthA(pStrCon));
        XCTAssertTrue( (0 == strcmp(pStrCon, AStr_getData(pStr))) );
        obj_Release(pStr);
        pStr = OBJ_NIL;
        
        obj_Release(pObj);
        pObj = OBJ_NIL;
    }
    
    return 1;
}




TINYTEST_START_SUITE(test_u8Array);
  TINYTEST_ADD_TEST(test_u8Array_ToCostantString01,setUp,tearDown);
  TINYTEST_ADD_TEST(test_u8Array_PutGet01,setUp,tearDown);
  TINYTEST_ADD_TEST(test_u8Array_InsertData03,setUp,tearDown);
  TINYTEST_ADD_TEST(test_u8Array_InsertData02,setUp,tearDown);
  TINYTEST_ADD_TEST(test_u8Array_InsertData01,setUp,tearDown);
  TINYTEST_ADD_TEST(test_u8Array_AddGet01,setUp,tearDown);
  TINYTEST_ADD_TEST(test_u8Array_OpenClose,setUp,tearDown);
TINYTEST_END_SUITE();

TINYTEST_MAIN_SINGLE_SUITE(test_u8Array);





