// vi:nu:et:sts=4 ts=4 sw=4
/*
 *	Generated 11/23/2019 09:50:49
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
#include    <Dict_internal.h>



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






int             test_Dict_OpenClose(
    const
    char            *pTestName
)
{
    ERESULT         eRc = ERESULT_SUCCESS;
    DICT_DATA	    *pObj = OBJ_NIL;
   
    fprintf(stderr, "Performing: %s\n", pTestName);

    pObj = Dict_Alloc( );
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    pObj = Dict_Init( pObj );
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    if (pObj) {

        //obj_TraceSet(pObj, true);       
        
        obj_Release(pObj);
        pObj = OBJ_NIL;
    }

    fprintf(stderr, "...%s completed.\n\n", pTestName);
    return 1;
}



int             test_Dict_test01(
    const
    char            *pTestName
)
{
    DICT_DATA       *pObj = OBJ_NIL;
    ERESULT         eRc = ERESULT_SUCCESS;
    ASTR_DATA       *pStr = OBJ_NIL;
    const
    char            *pResult = "LIBNAM=libTest\n";
    
    fprintf(stderr, "Performing: %s\n", pTestName);
    
    pObj = Dict_New( );
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    if (pObj) {
        
        // Test something.
        eRc = Dict_AddA(pObj, "lib_prefix", "lib");
        TINYTEST_TRUE( (!ERESULT_FAILED(eRc)) );
        eRc = Dict_AddA(pObj, "name", "Test");
        TINYTEST_TRUE( (!ERESULT_FAILED(eRc)) );

        pStr = AStr_NewA("LIBNAM=%[lib_prefix]%[name]\n");
        TINYTEST_FALSE( (OBJ_NIL == pStr) );
        if (pStr) {
            eRc = Dict_Expand(pObj, pStr);
            fprintf(stderr, "\tResult=\"%s\"\n", AStr_getData(pStr));
            TINYTEST_TRUE( (0 == strcmp(AStr_getData(pStr), pResult)) );
            obj_Release(pStr);
            pStr = OBJ_NIL;
        }

        pStr = AStr_NewA("LIBNAM=%lib_prefix%name\n");
        TINYTEST_FALSE( (OBJ_NIL == pStr) );
        if (pStr) {
            eRc = Dict_Expand(pObj, pStr);
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




TINYTEST_START_SUITE(test_Dict);
    TINYTEST_ADD_TEST(test_Dict_test01,setUp,tearDown);
    TINYTEST_ADD_TEST(test_Dict_OpenClose,setUp,tearDown);
TINYTEST_END_SUITE();

TINYTEST_MAIN_SINGLE_SUITE(test_Dict);





