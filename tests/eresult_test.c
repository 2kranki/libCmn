// vi:nu:et:sts=4 ts=4 sw=4
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
#include    <eResult_internal.h>



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






int             test_eResult_OpenClose(
    const
    char            *pTestName
)
{
    ERESULT_DATA    *pObj = OBJ_NIL;
   
    fprintf(stderr, "Performing: %s\n", pTestName);
    
    pObj = eResult_Alloc( );
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    pObj = eResult_Init( pObj );
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    if (pObj) {

        // Test something.

        obj_Release(pObj);
        pObj = OBJ_NIL;
    }

    fprintf(stderr, "...%s completed.\n\n\n", pTestName);
    return 1;
}



int         	test_eResult_PERR1(
    const
    char        	*pTestName
)
{
    ERESULT_DATA 	*pObj = OBJ_NIL;
   
    fprintf(stderr, "Performing: %s\n", pTestName);
    
    pObj = eResult_NewAStr(ERESULT_NOT_IMPLEMENTED, OBJ_NIL);
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    if (pObj) {

        fprintf(stderr, "You should see an error message following this\n"
                "similar to: \"Error: Not Implemented (-6)\"\n");
        eResult_Fprint(pObj, stderr);

        obj_Release(pObj);
        pObj = OBJ_NIL;
    }

    fprintf(stderr, "...%s completed.\n\n\n", pTestName);
    return 1;
}



int             test_eResult_PERR2(
    const
    char            *pTestName
)
{
    ERESULT_DATA     *pObj = OBJ_NIL;
   
    fprintf(stderr, "Performing: %s\n", pTestName);
    
    pObj = eResult_NewStrA(ERESULT_NOT_IMPLEMENTED, "Test Message!");
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    if (pObj) {

        fprintf(stderr, "You should see an error message following this\n"
                "similar to: \"Error: Not Implemented (-6) - Test Message!\"\n");
        eResult_Fprint(pObj, stderr);

        obj_Release(pObj);
        pObj = OBJ_NIL;
    }

    fprintf(stderr, "...%s completed.\n\n\n", pTestName);
    return 1;
}




TINYTEST_START_SUITE(test_eResult);
  TINYTEST_ADD_TEST(test_eResult_PERR2,setUp,tearDown);
  TINYTEST_ADD_TEST(test_eResult_PERR1,setUp,tearDown);
  TINYTEST_ADD_TEST(test_eResult_OpenClose,setUp,tearDown);
TINYTEST_END_SUITE();

TINYTEST_MAIN_SINGLE_SUITE(test_eResult);





