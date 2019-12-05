/*
 *	Generated 04/10/2018 10:49:33
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
#include    <genMake_internal.h>



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






int             test_genMake_OpenClose(
    const
    char            *pTestName
)
{
    GENMAKE_DATA	    *pObj = OBJ_NIL;
   
    fprintf(stderr, "Performing: %s\n", pTestName);

    pObj = genMake_New( );
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    if (pObj) {

        // Test something.

        obj_Release(pObj);
        pObj = OBJ_NIL;
    }

    fprintf(stderr, "...%s completed.\n\n", pTestName);
    return 1;
}



int             test_genMake_LibName01(
    const
    char            *pTestName
)
{
    ERESULT         eRc;
    GENMAKE_DATA    *pObj = OBJ_NIL;
    ASTR_DATA       *pStr;
    
    fprintf(stderr, "Performing: %s\n", pTestName);
    
    pObj = genMake_New( );
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    if (pObj) {
        
        pStr = genMake_LibName(pObj, "22", "11");
        TINYTEST_FALSE( (OBJ_NIL == pStr) );
        eRc = AStr_CompareA(pStr, "1122");
        TINYTEST_TRUE( (ERESULT_SUCCESS_EQUAL == eRc) );
        obj_Release(pStr);
        pStr = OBJ_NIL;

        pStr = genMake_LibName(pObj, "22", "");
        TINYTEST_FALSE( (OBJ_NIL == pStr) );
        eRc = AStr_CompareA(pStr, "22");
        TINYTEST_TRUE( (ERESULT_SUCCESS_EQUAL == eRc) );
        obj_Release(pStr);
        pStr = OBJ_NIL;
        
        pStr = genMake_LibName(pObj, "22", NULL);
        TINYTEST_FALSE( (OBJ_NIL == pStr) );
        eRc = AStr_CompareA(pStr, "22");
        TINYTEST_TRUE( (ERESULT_SUCCESS_EQUAL == eRc) );
        obj_Release(pStr);
        pStr = OBJ_NIL;

        eRc = genMake_DictAdd(pObj, "LibNamePrefix", "11");
        pStr = genMake_LibName(pObj, "22", NULL);
        TINYTEST_FALSE( (OBJ_NIL == pStr) );
        eRc = AStr_CompareA(pStr, "1122");
        TINYTEST_TRUE( (ERESULT_SUCCESS_EQUAL == eRc) );
        obj_Release(pStr);
        pStr = OBJ_NIL;
        
        obj_Release(pObj);
        pObj = OBJ_NIL;
    }
    
    fprintf(stderr, "...%s completed.\n\n", pTestName);
    return 1;
}



int             test_genMake_LibIncludePath01(
    const
    char            *pTestName
)
{
    ERESULT         eRc;
    GENMAKE_DATA    *pObj = OBJ_NIL;
    //ASTR_DATA       *pStr;
    PATH_DATA       *pPath;

    fprintf(stderr, "Performing: %s\n", pTestName);
    
    pObj = genMake_New( );
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    if (pObj) {
        
        pPath = genMake_LibIncludePath(pObj, "33", "11", "22");
        TINYTEST_FALSE( (OBJ_NIL == pPath) );
        eRc = AStr_CompareA((ASTR_DATA *)pPath, "11/2233");
        TINYTEST_TRUE( (ERESULT_SUCCESS_EQUAL == eRc) );
        obj_Release(pPath);
        pPath = OBJ_NIL;
        
        pPath = genMake_LibIncludePath(pObj, "22", "11", "");
        TINYTEST_FALSE( (OBJ_NIL == pPath) );
        eRc = AStr_CompareA((ASTR_DATA *)pPath, "11/22");
        TINYTEST_TRUE( (ERESULT_SUCCESS_EQUAL == eRc) );
        obj_Release(pPath);
        pPath = OBJ_NIL;
        
        pPath = genMake_LibIncludePath(pObj, "22", "", "33");
        TINYTEST_FALSE( (OBJ_NIL == pPath) );
        eRc = AStr_CompareA((ASTR_DATA *)pPath, "/3322");
        TINYTEST_TRUE( (ERESULT_SUCCESS_EQUAL == eRc) );
        obj_Release(pPath);
        pPath = OBJ_NIL;
        
        pPath = genMake_LibIncludePath(pObj, "22", "", "");
        TINYTEST_FALSE( (OBJ_NIL == pPath) );
        eRc = AStr_CompareA((ASTR_DATA *)pPath, "/22");
        TINYTEST_TRUE( (ERESULT_SUCCESS_EQUAL == eRc) );
        obj_Release(pPath);
        pPath = OBJ_NIL;
        
        pPath = genMake_LibIncludePath(pObj, "22", NULL, NULL);
        TINYTEST_FALSE( (OBJ_NIL == pPath) );
        eRc = AStr_CompareA((ASTR_DATA *)pPath, "22");
        TINYTEST_TRUE( (ERESULT_SUCCESS_EQUAL == eRc) );
        obj_Release(pPath);
        pPath = OBJ_NIL;
        
        eRc = genMake_DictAdd(pObj, "LibIncludePath", "YY");
        pPath = genMake_LibIncludePath(pObj, "22", NULL, NULL);
        TINYTEST_FALSE( (OBJ_NIL == pPath) );
        eRc = AStr_CompareA((ASTR_DATA *)pPath, "YY/22");
        TINYTEST_TRUE( (ERESULT_SUCCESS_EQUAL == eRc) );
        obj_Release(pPath);
        pPath = OBJ_NIL;

        obj_Release(pObj);
        pObj = OBJ_NIL;
    }
    
    fprintf(stderr, "...%s completed.\n\n", pTestName);
    return 1;
}



int             test_genMake_LibInstalledPath01(
    const
    char            *pTestName
)
{
    ERESULT         eRc;
    GENMAKE_DATA    *pObj = OBJ_NIL;
    //ASTR_DATA       *pStr;
    PATH_DATA       *pPath;
    
    fprintf(stderr, "Performing: %s\n", pTestName);
    
    pObj = genMake_New( );
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    if (pObj) {
        
        pPath = genMake_LibInstalledPath(pObj, "33", "11", "22");
        TINYTEST_FALSE( (OBJ_NIL == pPath) );
        eRc = AStr_CompareA((ASTR_DATA *)pPath, "11/2233");
        TINYTEST_TRUE( (ERESULT_SUCCESS_EQUAL == eRc) );
        obj_Release(pPath);
        pPath = OBJ_NIL;
        
        pPath = genMake_LibInstalledPath(pObj, "22", "11", "");
        TINYTEST_FALSE( (OBJ_NIL == pPath) );
        eRc = AStr_CompareA((ASTR_DATA *)pPath, "11/22");
        TINYTEST_TRUE( (ERESULT_SUCCESS_EQUAL == eRc) );
        obj_Release(pPath);
        pPath = OBJ_NIL;
        
        pPath = genMake_LibInstalledPath(pObj, "22", "", "33");
        TINYTEST_FALSE( (OBJ_NIL == pPath) );
        eRc = AStr_CompareA((ASTR_DATA *)pPath, "/3322");
        TINYTEST_TRUE( (ERESULT_SUCCESS_EQUAL == eRc) );
        obj_Release(pPath);
        pPath = OBJ_NIL;
        
        pPath = genMake_LibInstalledPath(pObj, "22", "", "");
        TINYTEST_FALSE( (OBJ_NIL == pPath) );
        eRc = AStr_CompareA((ASTR_DATA *)pPath, "/22");
        TINYTEST_TRUE( (ERESULT_SUCCESS_EQUAL == eRc) );
        obj_Release(pPath);
        pPath = OBJ_NIL;
        
        pPath = genMake_LibInstalledPath(pObj, "22", NULL, NULL);
        TINYTEST_FALSE( (OBJ_NIL == pPath) );
        eRc = AStr_CompareA((ASTR_DATA *)pPath, "22");
        TINYTEST_TRUE( (ERESULT_SUCCESS_EQUAL == eRc) );
        obj_Release(pPath);
        pPath = OBJ_NIL;
        
        eRc = genMake_DictAdd(pObj, "LibInstalledPath", "YY");
        pPath = genMake_LibInstalledPath(pObj, "22", NULL, NULL);
        TINYTEST_FALSE( (OBJ_NIL == pPath) );
        eRc = AStr_CompareA((ASTR_DATA *)pPath, "YY/22");
        TINYTEST_TRUE( (ERESULT_SUCCESS_EQUAL == eRc) );
        obj_Release(pPath);
        pPath = OBJ_NIL;
        
        obj_Release(pObj);
        pObj = OBJ_NIL;
    }
    
    fprintf(stderr, "...%s completed.\n\n", pTestName);
    return 1;
}




TINYTEST_START_SUITE(test_genMake);
    TINYTEST_ADD_TEST(test_genMake_LibInstalledPath01,setUp,tearDown);
    TINYTEST_ADD_TEST(test_genMake_LibIncludePath01,setUp,tearDown);
    TINYTEST_ADD_TEST(test_genMake_LibName01,setUp,tearDown);
    TINYTEST_ADD_TEST(test_genMake_OpenClose,setUp,tearDown);
TINYTEST_END_SUITE();

TINYTEST_MAIN_SINGLE_SUITE(test_genMake);





