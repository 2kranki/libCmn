/*
 *	Generated 05/31/2017 20:00:00
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
#include    <trace_internal.h>



int         setUp(
    const
    char        *pTestName
)
{
    mem_Init( );
    
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
    mem_Release( );
    
    return 1; 
}






int         test_trace_OpenClose(
    const
    char        *pTestName
)
{
    TRACE_DATA	*pObj = OBJ_NIL;
   
    fprintf(stderr, "Performing: %s\n", pTestName);
    pObj = trace_Shared( );
    //TINYTEST_FALSE( (1) );
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    TINYTEST_TRUE( (obj_getRetainCount(pObj) == 1) );
    fprintf(stderr, "pObj = %p\n", pObj);
    fprintf(stderr, "pLock = %p\n", &pObj->lock);
    if (pObj) {

        // Should not be displayed
        obj_TraceSet(pObj, false);
        TRC_OBJ(pObj, "Test 1\n");

        // Should be displayed
        obj_TraceSet(pObj, true);
        TRC_OBJ(pObj, "Test 2\n");

        trace_SharedReset( );
        pObj = OBJ_NIL;
    }

    fprintf(stderr, "...%s completed.\n", pTestName);
    return 1;
}




TINYTEST_START_SUITE(test_trace);
  TINYTEST_ADD_TEST(test_trace_OpenClose,setUp,tearDown);
TINYTEST_END_SUITE();

TINYTEST_MAIN_SINGLE_SUITE(test_trace);





