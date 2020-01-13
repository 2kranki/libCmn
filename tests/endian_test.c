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
#include    <endian_internal.h>



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






int         test_endian_OpenClose(
    const
    char        *pTestName
)
{
    ENDIAN_DATA	*pObj = OBJ_NIL;
   
    fprintf(stderr, "Performing: %s\n", pTestName);
    
    pObj = endian_Alloc( );
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    pObj = endian_Init( pObj );
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    if (pObj) {

        // Test something.

        obj_Release(pObj);
        pObj = OBJ_NIL;
    }

    fprintf(stderr, "...%s completed.\n", pTestName);
    return 1;
}



int         test_endian_GetPut(
    const
    char        *pTestName
)
{
    ENDIAN_DATA	*pObj = OBJ_NIL;
    const
    uint16_t    cu16 = 0x0102;
    const
    uint32_t    cu24 = 0x00010203;
    const
    uint32_t    cu32 = 0x01020304;
    const
    uint64_t    cu64 = 0x0102030405060708;
    uint8_t     uout[9];
    int         i;
    uint16_t    u16 = 0x0102;
    uint32_t    u24 = 0x00010203;
    uint32_t    u32 = 0x01020304;
    uint64_t    u64 = 0x0102030405060708;
   
    fprintf(stderr, "Performing: %s\n", pTestName);
    
    pObj = endian_Alloc( );
    XCTAssertFalse( (OBJ_NIL == pObj) );
    pObj = endian_Init( pObj );
    XCTAssertFalse( (OBJ_NIL == pObj) );
    if (pObj) {
        
        for (i=0; i<9; ++i) {
            uout[i] = 0;
        }
        endian_PutU16Big(pObj, cu16, uout);
        XCTAssertTrue( (uout[0] == 0x01) );
        XCTAssertTrue( (uout[1] == 0x02) );
        XCTAssertTrue( (uout[2] == 0x00) );
        u16 = endian_GetU16Big(pObj, uout);
        XCTAssertTrue( (u16 == cu16) );
        uout[0] = 0;
        uout[1] = 0;
        
        endian_PutU24Big(pObj, cu24, uout);
        XCTAssertTrue( (uout[0] == 0x01) );
        XCTAssertTrue( (uout[1] == 0x02) );
        XCTAssertTrue( (uout[2] == 0x03) );
        XCTAssertTrue( (uout[3] == 0x00) );
        u24 = endian_GetU24Big(pObj, uout);
        XCTAssertTrue( (u24 == cu24) );
        uout[0] = 0;
        uout[1] = 0;
        uout[2] = 0;

        endian_PutU32Big(pObj, cu32, uout);
        XCTAssertTrue( (uout[0] == 0x01) );
        XCTAssertTrue( (uout[1] == 0x02) );
        XCTAssertTrue( (uout[2] == 0x03) );
        XCTAssertTrue( (uout[3] == 0x04) );
        XCTAssertTrue( (uout[4] == 0x00) );
        u32 = endian_GetU32Big(pObj, uout);
        XCTAssertTrue( (u32 == cu32) );
        uout[0] = 0;
        uout[1] = 0;
        uout[2] = 0;
        uout[3] = 0;
        uout[4] = 0;
        
        endian_PutU64Big(pObj, cu64, uout);
        XCTAssertTrue( (uout[0] == 0x01) );
        XCTAssertTrue( (uout[1] == 0x02) );
        XCTAssertTrue( (uout[2] == 0x03) );
        XCTAssertTrue( (uout[3] == 0x04) );
        XCTAssertTrue( (uout[4] == 0x05) );
        XCTAssertTrue( (uout[5] == 0x06) );
        XCTAssertTrue( (uout[6] == 0x07) );
        XCTAssertTrue( (uout[7] == 0x08) );
        XCTAssertTrue( (uout[8] == 0x00) );
        u64 = endian_GetU64Big(pObj, uout);
        XCTAssertTrue( (u64 == cu64) );
        
        for (i=0; i<9; ++i) {
            uout[i] = 0;
        }
        endian_PutU16Little(pObj, cu16, uout);
        XCTAssertTrue( (uout[0] == 0x02) );
        XCTAssertTrue( (uout[1] == 0x01) );
        XCTAssertTrue( (uout[2] == 0x00) );
        u16 = endian_GetU16Little(pObj, uout);
        XCTAssertTrue( (u16 == cu16) );
        uout[0] = 0;
        uout[1] = 0;
        
        endian_PutU24Little(pObj, cu24, uout);
        XCTAssertTrue( (uout[0] == 0x03) );
        XCTAssertTrue( (uout[1] == 0x02) );
        XCTAssertTrue( (uout[2] == 0x01) );
        XCTAssertTrue( (uout[3] == 0x00) );
        u24 = endian_GetU24Little(pObj, uout);
        XCTAssertTrue( (u16 == cu16) );
        uout[0] = 0;
        uout[1] = 0;
        uout[2] = 0;
        
        endian_PutU32Little(pObj, cu32, uout);
        XCTAssertTrue( (uout[0] == 0x04) );
        XCTAssertTrue( (uout[1] == 0x03) );
        XCTAssertTrue( (uout[2] == 0x02) );
        XCTAssertTrue( (uout[3] == 0x01) );
        XCTAssertTrue( (uout[4] == 0x00) );
        u32 = endian_GetU32Little(pObj, uout);
        XCTAssertTrue( (u32 == cu32) );
        uout[0] = 0;
        uout[1] = 0;
        uout[2] = 0;
        uout[3] = 0;
        uout[4] = 0;
        
        endian_PutU64Little(pObj, cu64, uout);
        XCTAssertTrue( (uout[0] == 0x08) );
        XCTAssertTrue( (uout[1] == 0x07) );
        XCTAssertTrue( (uout[2] == 0x06) );
        XCTAssertTrue( (uout[3] == 0x05) );
        XCTAssertTrue( (uout[4] == 0x04) );
        XCTAssertTrue( (uout[5] == 0x03) );
        XCTAssertTrue( (uout[6] == 0x02) );
        XCTAssertTrue( (uout[7] == 0x01) );
        XCTAssertTrue( (uout[8] == 0x00) );
        u64 = endian_GetU64Little(pObj, uout);
        XCTAssertTrue( (u64 == cu64) );
        
        obj_Release(pObj);
        pObj = OBJ_NIL;
    }

    fprintf(stderr, "...%s completed.\n", pTestName);
    return 1;
}




TINYTEST_START_SUITE(test_endian);
  TINYTEST_ADD_TEST(test_endian_GetPut,setUp,tearDown);
  TINYTEST_ADD_TEST(test_endian_OpenClose,setUp,tearDown);
TINYTEST_END_SUITE();

TINYTEST_MAIN_SINGLE_SUITE(test_endian);





