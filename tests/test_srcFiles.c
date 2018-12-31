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
#include    <srcFiles_internal.h>
#include    <szTbl.h>



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






int         test_srcFiles_OpenClose(
    const
    char        *pTestName
)
{
    SRCFILES_DATA *pObj = OBJ_NIL;
   
    fprintf(stderr, "Performing: %s\n", pTestName);
    
    pObj = srcFiles_Alloc( );
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    pObj = srcFiles_Init( pObj );
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    if (pObj) {

        // Test something.

        obj_Release(pObj);
        pObj = OBJ_NIL;
    }

    fprintf(stderr, "...%s completed.\n", pTestName);
    return 1;
}



int         test_srcFiles_Test01(
    const
    char            *pTestName
)
{
    ERESULT         eRc;
    PATH_DATA       *pPath = OBJ_NIL;
    SRCFILES_DATA   *pObj = OBJ_NIL;
    const
    char            *pPathA = "~/git/libCmn/tests/files/e360_ex1_bal.txt";
    TOKEN_DATA      *pToken;
    int32_t         cls;
    ASTR_DATA       *pStr = OBJ_NIL;

    fprintf(stderr, "Performing: %s\n", pTestName);
    pPath = path_NewA(pPathA);
    TINYTEST_FALSE( (OBJ_NIL == pPath) );

    pObj = srcFiles_New( );
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    if (pObj) {
        
        eRc = srcFiles_NewSrcFromPath(pObj, pPath, 0, 4);
        TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );

        for (;;) {
            pToken = srcFiles_InputLookAhead(pObj, 1);
            XCTAssertFalse( (OBJ_NIL == pToken) );
            cls = token_getClass(pToken);
            if (cls == -1)
                break;
            {
                pStr = token_ToDebugString(pToken, 0);
                fprintf(stderr, "\ttoken text=\"%s\"\n",
                        AStr_getData(pStr));
                obj_Release(pStr);
                pStr = OBJ_NIL;
            }
            pToken = srcFiles_InputAdvance(pObj, 1);
            XCTAssertFalse( (OBJ_NIL == pToken) );
        }
        
        obj_Release(pObj);
        pObj = OBJ_NIL;
    }
    
    obj_Release(pPath);
    pPath = OBJ_NIL;

    fprintf(stderr, "...%s completed.\n", pTestName);
    return 1;
}




TINYTEST_START_SUITE(test_srcFiles);
    TINYTEST_ADD_TEST(test_srcFiles_Test01,setUp,tearDown);
    TINYTEST_ADD_TEST(test_srcFiles_OpenClose,setUp,tearDown);
TINYTEST_END_SUITE();

TINYTEST_MAIN_SINGLE_SUITE(test_srcFiles);





