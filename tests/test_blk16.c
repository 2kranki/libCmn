/*
 *	Generated 03/10/2017 20:28:51
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
#include    <blk16_internal.h>




int         test_blk16_Calcs(
    const
    char        *test_name
)
{
    uint16_t        size;
    
    size = blk16_CalcBlockSize(
            0,                      // Header Size
            0                       // Data Size
    );
    TINYTEST_TRUE((0 == size));
    
    size = blk16_CalcBlockSize(
            10,                     // Header Size
            64                      // Data Size
    );
    fprintf(stderr,"size=%d\n",size);
    TINYTEST_TRUE((88 == size));
    
    size = blk16_CalcDataSize(
            512,                    // Header Size
            64                      // Data Size
    );
    fprintf(stderr,"size=%d\n",size);
    TINYTEST_TRUE((440 == size));
     return 1;
}



int         test_blk16_OpenClose(
    const
    char        *test_name
)
{
    BLK16_DATA	*pObj = OBJ_NIL;
   
    printf( "Executing %s...\n",test_name);
    pObj = blk16_Alloc(0);
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    pObj = blk16_Init( pObj, 512, 12 );
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    if (pObj) {

        // Test something.

        obj_Release(pObj);
        pObj = OBJ_NIL;
    }

    return 1;
}




TINYTEST_START_SUITE(TestBlk16);
  TINYTEST_ADD_TEST(test_blk16_Calcs);
  TINYTEST_ADD_TEST(test_blk16_OpenClose);
TINYTEST_END_SUITE();

TINYTEST_MAIN_SINGLE_SUITE(TestBlk16);



