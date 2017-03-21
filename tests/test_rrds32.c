/*
 *	Generated 03/17/2017 11:12:35
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
#include    <rrds32_internal.h>





int         test_rrds32_OpenClose(
    const
    char        *test_name
)
{
    RRDS32_DATA	*pObj = OBJ_NIL;
   
    pObj = rrds32_Alloc(0);
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    pObj = rrds32_Init( pObj );
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    if (pObj) {

        // Test something.

        obj_Release(pObj);
        pObj = OBJ_NIL;
    }

    return 1;
}




TINYTEST_START_SUITE(test_rrds32);
  TINYTEST_ADD_TEST(test_rrds32_OpenClose);
TINYTEST_END_SUITE();

TINYTEST_MAIN_SINGLE_SUITE(test_rrds32);





