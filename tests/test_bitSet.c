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
#include    <bitSet_internal.h>



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






int         test_bitSet_OpenClose(
    const
    char        *pTestName
)
{
    BITSET_DATA	*pObj = OBJ_NIL;
   
    fprintf(stderr, "Performing: %s\n", pTestName);
    
    pObj = bitSet_Alloc(0);
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    pObj = bitSet_Init( pObj );
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    if (pObj) {

        // Test something.

        obj_Release(pObj);
        pObj = OBJ_NIL;
    }

    fprintf(stderr, "...%s completed.\n", pTestName);
    return 1;
}



int         test_bitSet_GetPut01(
    const
    char        *pTestName
)
{
    BITSET_DATA	*pObj = OBJ_NIL;
    uint16_t    i;
    ERESULT     eRc;
    ASTR_DATA   *pStr;
    bool        fRc;
    
    fprintf(stderr, "Performing: %s\n", pTestName);
    
    pObj = bitSet_Alloc(16);
    XCTAssertFalse( (OBJ_NIL == pObj) );
    pObj = bitSet_Init( pObj );
    XCTAssertFalse( (OBJ_NIL == pObj) );
    if (pObj) {
        
        pStr = bitSet_ToDebugString(pObj, 0);
        fprintf(stderr, "%s\n\n\n", AStr_getData(pStr));
        obj_Release(pStr);
        pStr = OBJ_NIL;
        for (i=0; i<16; ++i) {
            eRc = bitSet_Set(pObj, i+1, true);
            XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
            fRc = bitSet_Get(pObj, i+1);
            XCTAssertTrue( (fRc) );
        }
        pStr = bitSet_ToDebugString(pObj, 0);
        fprintf(stderr, "%s\n\n\n", AStr_getData(pStr));
        obj_Release(pStr);
        pStr = OBJ_NIL;
        
        obj_Release(pObj);
        pObj = OBJ_NIL;
    }
    
    fprintf(stderr, "...%s completed.\n", pTestName);
    return 1;
}




TINYTEST_START_SUITE(test_bitSet);
  TINYTEST_ADD_TEST(test_bitSet_GetPut01,setUp,tearDown);
  TINYTEST_ADD_TEST(test_bitSet_OpenClose,setUp,tearDown);
TINYTEST_END_SUITE();

TINYTEST_MAIN_SINGLE_SUITE(test_bitSet);





