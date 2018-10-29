/*
 *	Generated 12/17/2017 07:12:35
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
#include    <srcErrors_internal.h>



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

    
    srcErrors_SharedReset( );
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






int         test_srcErrors_OpenClose(
    const
    char        *pTestName
)
{
    SRCERRORS_DATA	*pObj = OBJ_NIL;
   
    fprintf(stderr, "Performing: %s\n", pTestName);

    pObj = srcErrors_Alloc( );
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    pObj = srcErrors_Init( pObj );
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    if (pObj) {

        // Test something.

        obj_Release(pObj);
        pObj = OBJ_NIL;
    }

    fprintf(stderr, "...%s completed.\n\n", pTestName);
    return 1;
}



int         test_srcErrors_Fatal01(
    const
    char        *pTestName
)
{
    SRCERRORS_DATA  *pObj = OBJ_NIL;
    SRCLOC          location = {1,3,2,200};
    
    
    fprintf(stderr, "Performing: %s\n", pTestName);
    
    pObj = srcErrors_Alloc( );
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    pObj = srcErrors_Init( pObj );
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    if (pObj) {
        
        srcErrors_AddFatalA(
                            pObj,
                            &location,
                            "Expecting '}', but found nothing"
        );
        srcErrors_Print(pObj);
        
        obj_Release(pObj);
        pObj = OBJ_NIL;
    }
    
    fprintf(stderr, "...%s completed.\n\n", pTestName);
    return 1;
}




TINYTEST_START_SUITE(test_srcErrors);
    TINYTEST_ADD_TEST(test_srcErrors_Fatal01,setUp,tearDown);
    TINYTEST_ADD_TEST(test_srcErrors_OpenClose,setUp,tearDown);
TINYTEST_END_SUITE();

TINYTEST_MAIN_SINGLE_SUITE(test_srcErrors);





