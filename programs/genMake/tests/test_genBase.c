/*
 *	Generated 04/18/2018 09:07:03
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
#include    <genBase_internal.h>


#include    <test_data.c>



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






int             test_genBase_OpenClose(
    const
    char            *pTestName
)
{
    ERESULT         eRc = ERESULT_SUCCESS;
    GENBASE_DATA	*pObj = OBJ_NIL;
   
    fprintf(stderr, "Performing: %s\n", pTestName);

    pObj = genBase_Alloc( );
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    pObj = genBase_Init( pObj );
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    if (pObj) {

        // Test something.
        TINYTEST_TRUE( (!ERESULT_FAILED(eRc)) );

        obj_Release(pObj);
        pObj = OBJ_NIL;
    }

    fprintf(stderr, "...%s completed.\n\n\n", pTestName);
    return 1;
}



int             test_genBase_Dict01(
    const
    char            *pTestName
)
{
    GENBASE_DATA    *pObj = OBJ_NIL;
    ERESULT         eRc = ERESULT_SUCCESS;
    ASTR_DATA       *pStr = OBJ_NIL;
    const
    char            *pResult = "LIBNAM=libTest\n";
    
    fprintf(stderr, "Performing: %s\n", pTestName);
    
    pObj = genBase_Alloc( );
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    pObj = genBase_Init( pObj );
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    if (pObj) {
        
        // Test something.
        eRc = genBase_DictAddA(pObj, "lib_prefix", "lib");
        TINYTEST_TRUE( (!ERESULT_FAILED(eRc)) );
        eRc = genBase_DictAddA(pObj, "name", "Test");
        TINYTEST_TRUE( (!ERESULT_FAILED(eRc)) );

        pStr = AStr_NewA("LIBNAM=${lib_prefix}${name}\n");
        TINYTEST_FALSE( (OBJ_NIL == pStr) );
        if (pStr) {
            eRc = genBase_DictExpand(pObj, pStr);
            fprintf(stderr, "\tResult=\"%s\"\n", AStr_getData(pStr));
            TINYTEST_TRUE( (0 == strcmp(AStr_getData(pStr), pResult)) );
            obj_Release(pStr);
            pStr = OBJ_NIL;
        }

        pStr = AStr_NewA("LIBNAM=$lib_prefix$name\n");
        TINYTEST_FALSE( (OBJ_NIL == pStr) );
        if (pStr) {
            eRc = genBase_DictExpand(pObj, pStr);
            fprintf(stderr, "\tResult=\"%s\"\n", AStr_getData(pStr));
            TINYTEST_TRUE( (0 == strcmp(AStr_getData(pStr), pResult)) );
            obj_Release(pStr);
            pStr = OBJ_NIL;
        }
        
        obj_Release(pObj);
        pObj = OBJ_NIL;
    }
    
    fprintf(stderr, "...%s completed.\n\n\n", pTestName);
    return 1;
}




TINYTEST_START_SUITE(test_genBase);
    TINYTEST_ADD_TEST(test_genBase_Dict01,setUp,tearDown);
    TINYTEST_ADD_TEST(test_genBase_OpenClose,setUp,tearDown);
TINYTEST_END_SUITE();

TINYTEST_MAIN_SINGLE_SUITE(test_genBase);





