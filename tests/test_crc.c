/*
 *	Generated 07/25/2017 10:42:33
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
#include    <crc_internal.h>


const
char        *pMsg1 = "123456789";
const
uint32_t    cMsg1 = 9;

/*
 * 1 byte checksum	    221
 * CRC-16	            0xBB3D
 * CRC-CCITT (XModem)	0x31C3
 * CRC-CCITT (Kermit)	0x8921
 * CRC-DNP	            0x82EA
 * CRC-32	            0xCBF43926 (PKZIP Compatible)
 */

// From stackoverflow:
uint16_t        crc16_ccitt(
    char            *ptr, 
    int             count
)
{
    int             crc;
    char            i;

    crc = 0;
    while (--count >= 0)
    {
        crc = crc ^ (int) *ptr++ << 8;
        i = 8;
        do
        {
            if (crc & 0x8000)
                crc = crc << 1 ^ 0x1021;
            else
                crc = crc << 1;
        } while(--i);
    }
    return (crc);
}


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






int         test_crc_16_1(
    const
    char        *pTestName
)
{
    CRC_DATA	*pObj = OBJ_NIL;
    ERESULT     eRc;
    uint32_t    i32;
    uint32_t    crc;
   
    pObj = crc_Alloc( );
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    pObj = crc_Init(pObj, CRC_TYPE_16);
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    if (pObj) {

        crc = crc_AccumBlock(pObj, cMsg1, (void *)pMsg1);  
        fprintf(stderr, "CRC_TYPE_16 = 0x%04X\n", i32);
        i32 = crc_getCheck(pObj);
        fprintf(stderr, "CRC_TYPE_16(check) = 0x%04X\n", i32);
        TINYTEST_TRUE( (crc == i32) );

        obj_Release(pObj);
        pObj = OBJ_NIL;
    }

    return 1;
}



int         test_crc_16_2(
    const
    char        *pTestName
)
{
    CRC_DATA	*pObj = OBJ_NIL;
    ERESULT     eRc;
    uint32_t    i32;
    uint32_t    crc;
   
    pObj = crc_Alloc( );
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    pObj = crc_Init(pObj, CRC_TYPE_CCITT_16);
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    if (pObj) {
        
        crc = crc_AccumBlock(pObj, cMsg1, (void *)pMsg1);  
        fprintf(stderr, "CRC_TYPE_CCITT_16 = 0x%04X\n", i32);
        i32 = crc_getCheck(pObj);
        TINYTEST_TRUE( (crc == i32) );

        obj_Release(pObj);
        pObj = OBJ_NIL;
    }

    return 1;
}



int         test_crc_32_1(
    const
    char        *pTestName
)
{
    CRC_DATA	*pObj = OBJ_NIL;
    ERESULT     eRc;
    uint32_t    i32;
    uint32_t    crc;
   
    pObj = crc_Alloc( );
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    pObj = crc_Init(pObj, CRC_TYPE_32);
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    if (pObj) {

        crc = crc_AccumBlock(pObj, cMsg1, (void *)pMsg1);  
        fprintf(stderr, "CRC_TYPE_32 = 0x%08X\n", crc);
        i32 = crc_getCheck(pObj);
        TINYTEST_TRUE( (crc == i32) );

        obj_Release(pObj);
        pObj = OBJ_NIL;
    }

    return 1;
}



int         test_crc_32_2(
    const
    char        *pTestName
)
{
    CRC_DATA	*pObj = OBJ_NIL;
    ERESULT     eRc;
    uint32_t    i32;
    uint32_t    crc;
   
    pObj = crc_Alloc( );
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    pObj = crc_Init(pObj, CRC_TYPE_IEEE_32);
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    if (pObj) {

        crc = crc_AccumBlock(pObj, cMsg1, (void *)pMsg1);  
        fprintf(stderr, "CRC_TYPE_IEEE_32 = 0x%08X\n", crc);
        i32 = crc_getCheck(pObj);
        TINYTEST_TRUE( (crc == i32) );

        obj_Release(pObj);
        pObj = OBJ_NIL;
    }

    return 1;
}




TINYTEST_START_SUITE(test_crc);
  TINYTEST_ADD_TEST(test_crc_32_2,setUp,tearDown);
  TINYTEST_ADD_TEST(test_crc_32_1,setUp,tearDown);
  TINYTEST_ADD_TEST(test_crc_16_2,setUp,tearDown);
  TINYTEST_ADD_TEST(test_crc_16_1,setUp,tearDown);
TINYTEST_END_SUITE();

TINYTEST_MAIN_SINGLE_SUITE(test_crc);





