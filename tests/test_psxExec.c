/*
 *	Generated 06/14/2018 08:13:54
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
#include    <psxExec_internal.h>



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






int             test_psxExec_OpenClose(
    const
    char            *pTestName
)
{
    PSXEXEC_DATA	*pObj = OBJ_NIL;
   
    fprintf(stderr, "Performing: %s\n", pTestName);

    pObj = psxExec_Alloc( );
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    pObj = psxExec_Init( pObj );
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    if (pObj) {

        // Test something.

        obj_Release(pObj);
        pObj = OBJ_NIL;
    }

    fprintf(stderr, "...%s completed.\n\n", pTestName);
    return 1;
}



int             test_psxExec_System01(
    const
    char            *pTestName
)
{
    PSXEXEC_DATA    *pObj = OBJ_NIL;
    int             iRc;
    ASTR_DATA       *pCommand = OBJ_NIL;
    ASTR_DATA       *pOutput = OBJ_NIL;
    
    fprintf(stderr, "Performing: %s\n", pTestName);
    
    pObj = psxExec_Alloc( );
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    pObj = psxExec_Init( pObj );
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    if (pObj) {
        
        pCommand = AStr_NewA("ls -al ~");
        TINYTEST_FALSE( (OBJ_NIL == pCommand) );
        iRc = psxExec_SystemWithOutput(pObj, pCommand, &pOutput);
        if (pOutput) {
            fprintf(stderr, "\tiRc=%d  output=\"%s\"\n\n", iRc, AStr_getData(pOutput));
        }
        
        obj_Release(pOutput);
        pOutput = OBJ_NIL;
        obj_Release(pCommand);
        pCommand = OBJ_NIL;
        obj_Release(pObj);
        pObj = OBJ_NIL;
    }
    
    fprintf(stderr, "...%s completed.\n\n", pTestName);
    return 1;
}




TINYTEST_START_SUITE(test_psxExec);
    TINYTEST_ADD_TEST(test_psxExec_System01,setUp,tearDown);
    TINYTEST_ADD_TEST(test_psxExec_OpenClose,setUp,tearDown);
TINYTEST_END_SUITE();

TINYTEST_MAIN_SINGLE_SUITE(test_psxExec);





