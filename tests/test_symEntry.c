/*
 *	Generated 03/27/2017 21:41:19
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
#include    <symEntry_internal.h>
#include    <trace.h>
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






int         test_symEntry_OpenClose(
    const
    char        *test_name
)
{
    SYMENTRY_DATA	*pObj = OBJ_NIL;
    NAME_DATA	    *pName = OBJ_NIL;
   
    pName = name_NewUTF8Con("test");

    pObj = symEntry_Alloc( );
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    pObj = symEntry_Init(pObj);
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    if (pObj) {

        // Test something.

        obj_Release(pObj);
        pObj = OBJ_NIL;
    }

    pObj = symEntry_NewA("test", 24);
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    if (pObj) {
        
        // Test something.
        
        obj_Release(pObj);
        pObj = OBJ_NIL;
    }
    
    obj_Release(pName);
    pName = OBJ_NIL;

    return 1;
}




TINYTEST_START_SUITE(test_symEntry);
  TINYTEST_ADD_TEST(test_symEntry_OpenClose,setUp,tearDown);
TINYTEST_END_SUITE();

TINYTEST_MAIN_SINGLE_SUITE(test_symEntry);





