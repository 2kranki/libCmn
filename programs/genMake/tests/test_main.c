/*
 *	Generated 07/17/2017 14:59:49
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
#include    <main_internal.h>



#include    <test_data.c>




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






int         test_main_OpenClose(
    const
    char        *pTestName
)
{
    MAIN_DATA	*pObj = OBJ_NIL;
   
    fprintf(stderr, "Performing: %s\n", pTestName);
    
    pObj = main_Alloc( );
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    pObj = main_Init( pObj );
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    if (pObj) {

        // Test something.

        obj_Release(pObj);
        pObj = OBJ_NIL;
    }

    fprintf(stderr, "...%s completed.\n\n", pTestName);
    return 1;
}



int         test_main_MakeFile01(
    const
    char        *pTestName
)
{
    ERESULT     eRc;
    MAIN_DATA   *pObj = OBJ_NIL;
    char        *pArgs[] = {
        "./makeFile01",
        "-v",
        NULL
    };
    
    fprintf(stderr, "Performing: %s\n", pTestName);
    
    pObj = main_NewFromArgV(2, pArgs, NULL);
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    pObj = main_Init(pObj);
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    if (pObj) {
        
        eRc = main_ParseInputStr(pObj, pGoodJson1);
        TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );
        eRc = main_GenMakefile(pObj);
        TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );

        obj_Release(pObj);
        pObj = OBJ_NIL;
    }
    
    fprintf(stderr, "...%s completed.\n\n", pTestName);
    return 1;
}




TINYTEST_START_SUITE(test_main);
    TINYTEST_ADD_TEST(test_main_MakeFile01,setUp,tearDown);
    TINYTEST_ADD_TEST(test_main_OpenClose,setUp,tearDown);
TINYTEST_END_SUITE();

TINYTEST_MAIN_SINGLE_SUITE(test_main);





