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
#include    <null_internal.h>



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






int         test_null_OpenClose(
    const
    char            *pTestName
)
{
    NULL_DATA	    *pObj = OBJ_NIL;
   
    fprintf(stderr, "Performing: %s\n", pTestName);
    pObj = null_Alloc( );
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    pObj = null_Init( pObj );
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    if (pObj) {

        // Test something.

        obj_Release(pObj);
        pObj = OBJ_NIL;
    }

    fprintf(stderr, "...%s completed.\n", pTestName);
    return 1;
}



int         test_null_ToJSON(
    const
    char            *pTestName
)
{
    NULL_DATA       *pObj = OBJ_NIL;
    ASTR_DATA       *pAStr = OBJ_NIL;
    
    fprintf(stderr, "Performing: %s\n", pTestName);
    pObj = null_Alloc();
    XCTAssertFalse( (OBJ_NIL == pObj) );
    pObj = null_Init( pObj );
    XCTAssertFalse( (OBJ_NIL == pObj) );
    if (pObj) {
        
        pAStr = null_ToJSON(pObj);
        XCTAssertFalse( (OBJ_NIL == pAStr) );
        fprintf(stderr, "JSON = '%s'\n", AStr_getData(pAStr));
        XCTAssertTrue( (0 == strcmp("{\"objectType\":\"null\"}\n", AStr_getData(pAStr))) );
        obj_Release(pAStr);
        pAStr = OBJ_NIL;

        obj_Release(pObj);
        pObj = OBJ_NIL;
    }
    
    fprintf(stderr, "...%s completed.\n", pTestName);
    return 1;
}




TINYTEST_START_SUITE(test_null);
  TINYTEST_ADD_TEST(test_null_ToJSON,setUp,tearDown);
  TINYTEST_ADD_TEST(test_null_OpenClose,setUp,tearDown);
TINYTEST_END_SUITE();

TINYTEST_MAIN_SINGLE_SUITE(test_null);




