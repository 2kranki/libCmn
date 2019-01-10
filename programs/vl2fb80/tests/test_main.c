/*
 *	Generated 12/06/2018 08:18:28
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


static
char        *ppArgs1[] = {
    "vl2fb80",
    "--help",
    NULL
};
static
int         cArgs1 = 2;


static
char        *ppArgs2[] = {
    "vl2fb80",
    "--debug",
    "--verbose",
    "--backup",
    "--out",
    "/tmp/",
    "~/git/libCmn/tests/files/e360_ex1_bal.txt",
    NULL
};
static
int         cArgs2 = 7;




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






int             test_main_OpenClose(
    const
    char            *pTestName
)
{
    MAIN_DATA	    *pObj = OBJ_NIL;
   
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



int             test_main_Test01(
    const
    char            *pTestName
)
{
    ERESULT         eRc;
    MAIN_DATA       *pObj = OBJ_NIL;
    const
    char            *pPathInA = "~/git/libCmn/tests/files/e360_ex1_bal.txt";
    const
    char            *pPathChkA = "~/git/libCmn/tests/files/e360_ex1_bal.seq.txt";
    PATH_DATA       *pPathIn = OBJ_NIL;
    const
    char            *pPathOutA = "/tmp/e360_ex1_bal.txt";
    PATH_DATA       *pPathOut = OBJ_NIL;
    ASTR_DATA       *pStr = OBJ_NIL;
    int             iRc;

    fprintf(stderr, "Performing: %s\n", pTestName);
    
    pObj = main_Alloc( );
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    pObj = main_Init( pObj );
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    if (pObj) {
        
        pPathIn = path_NewA(pPathInA);
        TINYTEST_FALSE( (OBJ_NIL == pPathIn) );
        path_Clean(pPathIn);
        eRc = path_IsFile(pPathIn);
        TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );
        
        pPathOut = path_NewA(pPathOutA);
        TINYTEST_FALSE( (OBJ_NIL == pPathOut) );
        path_Clean(pPathOut);
        eRc = path_Delete(pPathOut);

        pObj->fSeq = 1;
        pObj->seqBgn = 1000;
        pObj->seqInc = 1000;
        eRc = main_ProcessRecords(pObj, pPathIn, pPathOut);
        TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );

        obj_Release(pPathIn);
        pPathIn = OBJ_NIL;
        pPathIn = path_NewA(pPathChkA);
        TINYTEST_FALSE( (OBJ_NIL == pPathIn) );
        path_Clean(pPathIn);
        eRc = path_IsFile(pPathIn);
        TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );

        pStr = AStr_NewA("diff ");
        TINYTEST_FALSE( (OBJ_NIL == pStr) );
        AStr_Append(pStr, (ASTR_DATA *)pPathOut);
        AStr_AppendA(pStr, "  ");
        AStr_Append(pStr, (ASTR_DATA *)pPathIn);
        iRc = system(AStr_getData(pStr));
        obj_Release(pStr);
        pStr = OBJ_NIL;
        
        obj_Release(pPathIn);
        pPathIn = OBJ_NIL;
        obj_Release(pPathOut);
        pPathOut = OBJ_NIL;
        
        obj_Release(pObj);
        pObj = OBJ_NIL;
    }
    
    fprintf(stderr, "...%s completed.\n\n", pTestName);
    return 1;
}



int             test_main_Test02(
    const
    char            *pTestName
)
{
    ERESULT         eRc;
    MAIN_DATA       *pObj = OBJ_NIL;
    const
    char            *pPathInA = "~/git/libCmn/tests/files/e360_ex1_bal.txt";
    const
    char            *pPathChkA = "~/git/libCmn/tests/files/e360_ex1_bal.seq.txt";
    PATH_DATA       *pPathIn = OBJ_NIL;
    const
    char            *pPathOutA = "/tmp/e360_ex1_bal.txt";
    PATH_DATA       *pPathOut = OBJ_NIL;
    ASTR_DATA       *pStr = OBJ_NIL;
    int             iRc;
    
    fprintf(stderr, "Performing: %s\n", pTestName);
    
    pObj = main_New( );
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    if (pObj) {
        
        eRc = main_SetupFromArgV(pObj, cArgs2, ppArgs2, NULL);
        TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );

        iRc = main_Exec(pObj);
        
        pPathOut = path_NewA(pPathOutA);
        TINYTEST_FALSE( (OBJ_NIL == pPathOut) );
        path_Clean(pPathOut);
        eRc = path_Delete(pPathOut);
        
        pPathIn = path_NewA(pPathChkA);
        TINYTEST_FALSE( (OBJ_NIL == pPathIn) );
        path_Clean(pPathIn);
        eRc = path_IsFile(pPathIn);
        TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );
        
        pStr = AStr_NewA("diff ");
        TINYTEST_FALSE( (OBJ_NIL == pStr) );
        AStr_Append(pStr, (ASTR_DATA *)pPathOut);
        AStr_AppendA(pStr, "  ");
        AStr_Append(pStr, (ASTR_DATA *)pPathIn);
        iRc = system(AStr_getData(pStr));
        obj_Release(pStr);
        pStr = OBJ_NIL;
        
        obj_Release(pPathIn);
        pPathIn = OBJ_NIL;
        obj_Release(pPathOut);
        pPathOut = OBJ_NIL;
        
        obj_Release(pObj);
        pObj = OBJ_NIL;
    }
    
    fprintf(stderr, "...%s completed.\n\n", pTestName);
    return 1;
}




TINYTEST_START_SUITE(test_main);
    TINYTEST_ADD_TEST(test_main_Test02,setUp,tearDown);
    TINYTEST_ADD_TEST(test_main_Test01,setUp,tearDown);
    TINYTEST_ADD_TEST(test_main_OpenClose,setUp,tearDown);
TINYTEST_END_SUITE();

TINYTEST_MAIN_SINGLE_SUITE(test_main);





