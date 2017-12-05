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


static
const
char        *ppArgs2[] = {
    "program_name",
    "--debug",
    "1",
    "2",
    "3",
    NULL
};
static
int         cArgs2 = 5;



int         processArg(
    OBJ_ID      pObj,
    const
    char        *pArg
)
{
    fprintf(stderr, "processArg arg:\"%s\"\n", pArg);
    return 0;
}



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






int         test_appl_OpenClose(
    const
    char        *pTestName
)
{
    APPL_DATA	*pObj = OBJ_NIL;
    int         iRc;
   
    fprintf(stderr, "Performing: %s\n", pTestName);
    pObj = appl_Alloc( );
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    pObj = appl_Init(pObj, cArgs2, ppArgs2);
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    if (pObj) {

        appl_Usage(pObj, "xyzzy");
        iRc = appl_ParseArgs(pObj);
        appl_setProcessArgs(pObj, &processArg);
        iRc = appl_ProcessArgs(pObj);
        TINYTEST_TRUE( (0 == iRc) );

        obj_Release(pObj);
        pObj = OBJ_NIL;
    }

    fprintf(stderr, "...%s completed.\n", pTestName);
    return 1;
}




TINYTEST_START_SUITE(test_appl);
  TINYTEST_ADD_TEST(test_appl_OpenClose,setUp,tearDown);
TINYTEST_END_SUITE();

TINYTEST_MAIN_SINGLE_SUITE(test_appl);





