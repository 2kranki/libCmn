/*
 *	Generated 06/05/2017 10:38:38
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
#include    <appl_internal.h>
#include    <szTbl.h>



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






int         test_node_Utf8(
    const
    char        *pTestName
)
{
    NODE_DATA	*pObj = OBJ_NIL;
   
    pObj = node_Alloc( );
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    pObj = node_InitWithUTF8(pObj, "abc", NULL);
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    if (pObj) {

        // Test something.

        obj_Release(pObj);
        pObj = OBJ_NIL;
    }

    szTbl_SharedReset();    
    return 1;
}



int         test_node_Utf8Con(
    const
    char        *pTestName
)
{
    NODE_DATA	*pObj = OBJ_NIL;
    
    pObj = node_Alloc();
    XCTAssertFalse( (OBJ_NIL == pObj) );
    pObj = node_InitWithUTF8Con( pObj, "abc", OBJ_NIL );
    XCTAssertFalse( (OBJ_NIL == pObj) );
    if (pObj) {
        
        obj_Release(pObj);
        pObj = OBJ_NIL;
    }
    
    szTbl_SharedReset();    
    return 1;
}



int         test_node_Ptr(
    const
    char        *pTestName
)
{
    NODE_DATA	*pObj = OBJ_NIL;
    
    pObj = node_Alloc();
    XCTAssertFalse( (OBJ_NIL == pObj) );
    pObj = node_InitWithPtr( pObj, test_node_Ptr, OBJ_NIL );
    XCTAssertFalse( (OBJ_NIL == pObj) );
    if (pObj) {
        
        obj_Release(pObj);
        pObj = OBJ_NIL;
    }
    
    szTbl_SharedReset();    
    return 1;
}




TINYTEST_START_SUITE(test_node);
  TINYTEST_ADD_TEST(test_node_Ptr,setUp,tearDown);
  TINYTEST_ADD_TEST(test_node_Utf8Con,setUp,tearDown);
  TINYTEST_ADD_TEST(test_node_Utf8,setUp,tearDown);
TINYTEST_END_SUITE();

TINYTEST_MAIN_SINGLE_SUITE(test_node);




