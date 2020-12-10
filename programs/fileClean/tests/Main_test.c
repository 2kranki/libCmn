// vi:nu:et:sts=4 ts=4 sw=4
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
#include    <SrcErrors.h>
#include    <trace.h>
#include    <Main_internal.h>



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
    SrcErrors_SharedReset( );
    JsonIn_RegisterReset();
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






int         test_Main_OpenClose(
    const
    char        *pTestName
)
{
    MAIN_DATA	*pObj = OBJ_NIL;
   
    fprintf(stderr, "Performing: %s\n", pTestName);
    
    pObj = Main_New( );
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    if (pObj) {

        // Test something.

        obj_Release(pObj);
        pObj = OBJ_NIL;
    }

    fprintf(stderr, "...%s completed.\n\n", pTestName);
    return 1;
}



int         test_Main_Clean01(
    const
    char        *pTestName
)
{
    ERESULT         eRc;
    MAIN_DATA       *pObj = OBJ_NIL;
    ASTR_DATA       *pStr = OBJ_NIL;
    PATH_DATA       *pPath = OBJ_NIL;
    //ASTR_DATA       *pWrk = OBJ_NIL;
    int             iRc;
    int             offset = 0;
    bool            fDump = true;
    uint32_t        i;
    const
    char            *pChr;
    const
    //char            *pPathA = "~/git/libCmn/programs/fileClean/tests/files/Test.txt";
    char            *pPathA = "~/git/libCmn/programs/fileClean/tests/files/HARDWARE.DOC.txt";
    const
    char            *pResultPathA = "~/git/libCmn/programs/fileClean/tests/files/TestResult.txt";

    fprintf(stderr, "Performing: %s\n", pTestName);
    
    pObj = Main_New();
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    if (pObj) {

        Appl_setDebug(Main_getAppl(pObj), true);
        pPath = Path_NewA(pPathA);
        TINYTEST_FALSE( (OBJ_NIL == pPath) );

        eRc = Main_CleanFile(pObj, pPath);
        TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );

/**************
        if (fDump) {
            pStr = Main_getStr(pObj);
            TINYTEST_FALSE( (OBJ_NIL == pStr) );
            fprintf(stderr, "GEN_BEGIN:\n%sGEN_END:\n\n\n", AStr_getData(pStr));
        }
        
        // Skip first 3 lines of output.
        pChr = AStr_getData(Main_getStr(pObj));
        for (i=0; i<3; i++) {
            while (*pChr && (*pChr != '\n')) {
                pChr++;
            }
            pChr++;
        }
        
        iRc = str_CompareSpcl(pChr, pOutputA, &offset);
        fprintf(stderr, "\tiRc=%d  offset=%04X\n", iRc, offset);
        TINYTEST_TRUE( (0 == iRc) );
         */

        obj_Release(pPath);
        pPath = OBJ_NIL;

        obj_Release(pObj);
        pObj = OBJ_NIL;
    }
    
    fprintf(stderr, "...%s completed.\n\n\n", pTestName);
    return 1;
}




TINYTEST_START_SUITE(test_Main);
    TINYTEST_ADD_TEST(test_Main_Clean01,setUp,tearDown);
    TINYTEST_ADD_TEST(test_Main_OpenClose,setUp,tearDown);
TINYTEST_END_SUITE();

TINYTEST_MAIN_SINGLE_SUITE(test_Main);





