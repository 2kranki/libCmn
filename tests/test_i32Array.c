/*
 *	Generated 01/20/2018 22:51:51
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
#include    <i32Array_internal.h>



int             setUp(
    const
    char            *pTestName
)
{
    mem_Init( );
    trace_Shared( ); 
    // Put setup code here. This method is called before the invocation of each
    // test method in the class.
    
    return 1; 
}


int             tearDown(
    const
    char            *pTestName
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






int             test_i32Array_OpenClose(
    const
    char            *pTestName
)
{
    I32ARRAY_DATA	    *pObj = OBJ_NIL;
   
    fprintf(stderr, "Performing: %s\n", pTestName);

    pObj = i32Array_Alloc( );
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    pObj = i32Array_Init( pObj );
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    if (pObj) {

        // Test something.

        obj_Release(pObj);
        pObj = OBJ_NIL;
    }

    fprintf(stderr, "...%s completed.\n\n", pTestName);
    return 1;
}



int         test_i32Array_AddGet01(
    const
    char            *pTestName
)
{
    I32ARRAY_DATA	*pObj = OBJ_NIL;
    uint32_t        i;
    ERESULT         eRc;
    uint32_t        data;
    
    fprintf(stderr, "Performing: %s\n", pTestName);
    
    pObj = i32Array_Alloc( );
    XCTAssertFalse( (OBJ_NIL == pObj) );
    pObj = i32Array_Init( pObj );
    XCTAssertFalse( (OBJ_NIL == pObj) );
    if (pObj) {
        
        for (i=1; i<=64; ++i) {
            eRc = i32Array_AppendData(pObj, i);
            XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
        }
        
        for (i=1; i<=64; ++i) {
            data = i32Array_Get(pObj, i);
            XCTAssertTrue( (data == i) );
        }
        
        obj_Release(pObj);
        pObj = OBJ_NIL;
    }
    
    fprintf(stderr, "...%s completed.\n", pTestName);
    return 1;
}




TINYTEST_START_SUITE(test_i32Array);
    TINYTEST_ADD_TEST(test_i32Array_AddGet01,setUp,tearDown);
    TINYTEST_ADD_TEST(test_i32Array_OpenClose,setUp,tearDown);
TINYTEST_END_SUITE();

TINYTEST_MAIN_SINGLE_SUITE(test_i32Array);





