/*
 *	Generated 08/21/2017 13:02:16
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
#include    <macro_internal.h>
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

    szTbl_SharedReset( );    
    trace_SharedReset( ); 
    mem_Dump( );
    mem_Release( );
    
    return 1; 
}






int         test_macro_OpenClose(
    const
    char        *pTestName
)
{
    MACRO_DATA	*pObj = OBJ_NIL;
    NAME_DATA   *pName;
   
    pObj = macro_Alloc( );
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    pObj = macro_InitWithUTF8Con( pObj, "abc" );
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    if (pObj) {

        pName = macro_getName(pObj);
        XCTAssertTrue( (0 == name_CompareA(pName, "abc")) );
        
        obj_Release(pObj);
        pObj = OBJ_NIL;
    }

    return 1;
}




TINYTEST_START_SUITE(test_macro);
  TINYTEST_ADD_TEST(test_macro_OpenClose,setUp,tearDown);
TINYTEST_END_SUITE();

TINYTEST_MAIN_SINGLE_SUITE(test_macro);





