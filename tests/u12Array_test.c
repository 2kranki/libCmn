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
#include    <JsonIn.h>
#include    <trace.h>
#include    <u12Array_internal.h>



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

    
    JsonIn_RegisterReset();
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






int         test_u12Array_OpenClose(
    const
    char        *pTestName
)
{
    U12ARRAY_DATA	*pObj = OBJ_NIL;
   
    fprintf(stderr, "Performing: %s\n", pTestName);
    
    pObj = u12Array_Alloc( );
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    pObj = u12Array_Init( pObj );
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    if (pObj) {

        // Test something.

        obj_Release(pObj);
        pObj = OBJ_NIL;
    }

    fprintf(stderr, "...%s completed.\n", pTestName);
    return 1;
}



int         test_u12Array_GetPut01(
    const
    char        *pTestName
)
{
    ERESULT         eRc;
    U12ARRAY_DATA   *pObj = OBJ_NIL;
    int             i;
    int             iMax = 12;
    uint16_t        num;
    
    fprintf(stderr, "Performing: %s\n", pTestName);
    
    pObj = u12Array_Alloc( );
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    pObj = u12Array_Init( pObj );
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    if (pObj) {
        
        // Simple Put/Get Verification
        for(i=0; i<iMax; ++i) {
            eRc = u12Array_Put(pObj, (i + 1), i);
            TINYTEST_TRUE( (ERESULT_IS_SUCCESSFUL(eRc)) );
            num = u12Array_Get(pObj, (i + 1));
            eRc = u12Array_getLastError(pObj);
            fprintf(stderr, "\ti=%d num=%d\n", i, num);
            TINYTEST_TRUE( (ERESULT_IS_SUCCESSFUL(eRc)) );
            TINYTEST_TRUE( (num == i) );
        }
        
        obj_Release(pObj);
        pObj = OBJ_NIL;
    }
    
    fprintf(stderr, "...%s completed.\n", pTestName);
    return 1;
}




TINYTEST_START_SUITE(test_u12Array);
    TINYTEST_ADD_TEST(test_u12Array_GetPut01,setUp,tearDown);
    TINYTEST_ADD_TEST(test_u12Array_OpenClose,setUp,tearDown);
TINYTEST_END_SUITE();

TINYTEST_MAIN_SINGLE_SUITE(test_u12Array);





