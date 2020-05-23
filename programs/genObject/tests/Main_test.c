// vi:nu:et:sts=4 ts=4 sw=4
/*
 *	Generated 04/28/2020 23:01:38
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
#include    <Main_internal.h>
#include    <SrcErrors.h>
#include    <szTbl.h>



int             setUp (
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


int             tearDown (
    const
    char            *pTestName
)
{
    // Put teardown code here. This method is called after the invocation of each
    // test method in the class.

    SrcErrors_SharedReset( );
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






int             test_Main_OpenClose (
    const
    char            *pTestName
)
{
    ERESULT         eRc = ERESULT_SUCCESS;
    MAIN_DATA	    *pObj = OBJ_NIL;
    bool            fRc;
   
    fprintf(stderr, "Performing: %s\n", pTestName);

    pObj = Main_Alloc( );
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    pObj = Main_Init( pObj );
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    if (pObj) {

        //obj_TraceSet(pObj, true);       
        fRc = obj_IsKindOf(pObj, OBJ_IDENT_MAIN);
        TINYTEST_TRUE( (fRc) );
        
        // Test something.
        TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );

        obj_Release(pObj);
        pObj = OBJ_NIL;
    }

    fprintf(stderr, "...%s completed.\n\n\n", pTestName);
    return 1;
}



int             test_Main_Copy01 (
    const
    char            *pTestName
)
{
    ERESULT         eRc = ERESULT_SUCCESS;
    MAIN_DATA	    *pObj1 = OBJ_NIL;
    MAIN_DATA	    *pObj2 = OBJ_NIL;
    bool            fRc;
#if defined(MAIN_JSON_SUPPORT) && defined(XYZZY)
    ASTR_DATA	    *pStr = OBJ_NIL;
#endif
   
    fprintf(stderr, "Performing: %s\n", pTestName);

    pObj1 = Main_New( );
    TINYTEST_FALSE( (OBJ_NIL == pObj1) );
    if (pObj1) {

        //obj_TraceSet(pObj1, true);       
        fRc = obj_IsKindOf(pObj1, OBJ_IDENT_MAIN);
        TINYTEST_TRUE( (fRc) );
        
        // Test assign.
        pObj2 = Main_New();
        TINYTEST_FALSE( (OBJ_NIL == pObj2) );
        eRc = Main_Assign(pObj1, pObj2);
        TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );

        fRc = obj_IsKindOf(pObj2, OBJ_IDENT_MAIN);
        TINYTEST_TRUE( (fRc) );
        //eRc = Main_Compare(pObj1, pObj2);
        //TINYTEST_TRUE( (ERESULT_SUCCESS_EQUAL == eRc) );
        //TODO: Add More tests here!

        obj_Release(pObj2);
        pObj2 = OBJ_NIL;

        // Test copy.
        pObj2 = Main_Copy(pObj1);
        TINYTEST_FALSE( (OBJ_NIL == pObj2) );

        fRc = obj_IsKindOf(pObj2, OBJ_IDENT_MAIN);
        TINYTEST_TRUE( (fRc) );
        //eRc = Main_Compare(pObj1, pObj2);
        //TINYTEST_TRUE( (ERESULT_SUCCESS_EQUAL == eRc) );
        //TODO: Add More tests here!

        obj_Release(pObj2);
        pObj2 = OBJ_NIL;

        // Test json support.
#if defined(MAIN_JSON_SUPPORT) && defined(XYZZY)
        pStr = Main_ToJson(pObj1);
        TINYTEST_FALSE( (OBJ_NIL == pStr) );
        fprintf(stderr, "JSON: %s\n", AStr_getData(pStr));
        pObj2 = Main_NewFromJsonString(pStr);
        TINYTEST_FALSE( (OBJ_NIL == pObj2) );
        fRc = obj_IsKindOf(pObj2, OBJ_IDENT_MAIN);
        TINYTEST_TRUE( (fRc) );
        obj_Release(pStr);
        pStr = OBJ_NIL;
        //eRc = Main_Compare(pObj1, pObj2);
        //TINYTEST_TRUE( (ERESULT_SUCCESS_EQUAL == eRc) );

        obj_Release(pObj2);
        pObj2 = OBJ_NIL;
#endif

        obj_Release(pObj1);
        pObj1 = OBJ_NIL;
    }

    fprintf(stderr, "...%s completed.\n\n\n", pTestName);
    return 1;
}



int             test_Main_Test01 (
    const
    char            *pTestName
)
{
    //ERESULT         eRc = ERESULT_SUCCESS;
    MAIN_DATA	    *pObj = OBJ_NIL;
    bool            fRc;
   
    fprintf(stderr, "Performing: %s\n", pTestName);

    pObj = Main_New( );
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    if (pObj) {

        //obj_TraceSet(pObj, true);       
        fRc = obj_IsKindOf(pObj, OBJ_IDENT_MAIN);
        TINYTEST_TRUE( (fRc) );
        //TINYTEST_TRUE( (ERESULT_OK(eRc)) );
        
        {
            ASTR_DATA       *pStr = Main_ToDebugString(pObj, 0);
            if (pStr) {
                fprintf(stderr, "Debug: %s\n", AStr_getData(pStr));
                obj_Release(pStr);
                pStr = OBJ_NIL;
            }
        }

        obj_Release(pObj);
        pObj = OBJ_NIL;
    }

    fprintf(stderr, "...%s completed.\n\n\n", pTestName);
    return 1;
}



int             test_Main_ParseArg01 (
    const
    char            *pTestName
)
{
    ERESULT         eRc = ERESULT_SUCCESS;
    MAIN_DATA       *pObj = OBJ_NIL;
    ASTR_DATA       *pStr = OBJ_NIL;
    PATH_DATA       *pPath = OBJ_NIL;
    bool            fRc;
    const
    char            *pTestFileA =
                    "~/git/libCmn/programs/genObject/tests/files/object01.json.txt";

    fprintf(stderr, "Performing: %s\n", pTestName);

    pObj = Main_New( );
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    if (pObj) {

        //obj_TraceSet(pObj, true);
        fRc = obj_IsKindOf(pObj, OBJ_IDENT_MAIN);
        TINYTEST_TRUE( (fRc) );
        //TINYTEST_TRUE( (ERESULT_OK(eRc)) );

        pPath = Path_NewA("/Users/bob/Support/x/Test01.h");
        if (pPath) {
            eRc = Path_Delete(pPath);
            obj_Release(pPath);
            pPath = OBJ_NIL;
        }
        pPath = Path_NewA("/Users/bob/Support/x/Test01.c");
        if (pPath) {
            eRc = Path_Delete(pPath);
            obj_Release(pPath);
            pPath = OBJ_NIL;
        }
        pPath = Path_NewA("/Users/bob/Support/x/Test01_internal.h");
        if (pPath) {
            eRc = Path_Delete(pPath);
            obj_Release(pPath);
            pPath = OBJ_NIL;
        }
        pPath = Path_NewA("/Users/bob/Support/x/Test01_json.c");
        if (pPath) {
            eRc = Path_Delete(pPath);
            obj_Release(pPath);
            pPath = OBJ_NIL;
        }
        pPath = Path_NewA("/Users/bob/Support/x/Test01_object.c");
        if (pPath) {
            eRc = Path_Delete(pPath);
            obj_Release(pPath);
            pPath = OBJ_NIL;
        }
        pPath = Path_NewA("/Users/bob/Support/x/Test01_test.c");
        if (pPath) {
            eRc = Path_Delete(pPath);
            obj_Release(pPath);
            pPath = OBJ_NIL;
        }

        pStr = AStr_NewA(pTestFileA);
        TINYTEST_FALSE( (OBJ_NIL == pStr) );
        eRc = Main_ProcessArg(pObj, pStr);
        TINYTEST_TRUE( (ERESULT_OK(eRc)) );
        obj_Release(pStr);
        pStr = OBJ_NIL;

        pPath = Path_NewA("/Users/bob/Support/x/Test01.h");
        if (pPath) {
            eRc = Path_IsFile(pPath);
            TINYTEST_TRUE( (ERESULT_OK(eRc)) );
            eRc = Path_Delete(pPath);
            obj_Release(pPath);
            pPath = OBJ_NIL;
        }
        pPath = Path_NewA("/Users/bob/Support/x/Test01.c");
        if (pPath) {
            eRc = Path_IsFile(pPath);
            TINYTEST_TRUE( (ERESULT_OK(eRc)) );
            eRc = Path_Delete(pPath);
            obj_Release(pPath);
            pPath = OBJ_NIL;
        }
        pPath = Path_NewA("/Users/bob/Support/x/Test01_internal.h");
        if (pPath) {
            eRc = Path_IsFile(pPath);
            TINYTEST_TRUE( (ERESULT_OK(eRc)) );
            eRc = Path_Delete(pPath);
            obj_Release(pPath);
            pPath = OBJ_NIL;
        }
        pPath = Path_NewA("/Users/bob/Support/x/Test01_json.c");
        if (pPath) {
            eRc = Path_IsFile(pPath);
            TINYTEST_TRUE( (ERESULT_OK(eRc)) );
            eRc = Path_Delete(pPath);
            obj_Release(pPath);
            pPath = OBJ_NIL;
        }
        pPath = Path_NewA("/Users/bob/Support/x/Test01_object.c");
        if (pPath) {
            eRc = Path_IsFile(pPath);
            TINYTEST_TRUE( (ERESULT_OK(eRc)) );
            eRc = Path_Delete(pPath);
            obj_Release(pPath);
            pPath = OBJ_NIL;
        }
        pPath = Path_NewA("/Users/bob/Support/x/Test01_test.c");
        if (pPath) {
            eRc = Path_IsFile(pPath);
            TINYTEST_TRUE( (ERESULT_OK(eRc)) );
            eRc = Path_Delete(pPath);
            obj_Release(pPath);
            pPath = OBJ_NIL;
        }
        obj_Release(pObj);
        pObj = OBJ_NIL;
    }

    fprintf(stderr, "...%s completed.\n\n\n", pTestName);
    return 1;
}



int             test_Main_TestHelp01 (
    const
    char            *pTestName
)
{
    ERESULT         eRc = ERESULT_SUCCESS;
    MAIN_DATA        *pObj = OBJ_NIL;
    bool            fRc;

    fprintf(stderr, "Performing: %s\n", pTestName);

    pObj = Main_New( );
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    if (pObj) {

        //obj_TraceSet(pObj, true);
        fRc = obj_IsKindOf(pObj, OBJ_IDENT_MAIN);
        TINYTEST_TRUE( (fRc) );
        //TINYTEST_TRUE( (ERESULT_OK(eRc)) );

        eRc = Main_UsageOptions(pObj, stderr);

        {
            ASTR_DATA       *pStr = Main_ToDebugString(pObj, 0);
            if (pStr) {
                fprintf(stderr, "Debug: %s\n", AStr_getData(pStr));
                obj_Release(pStr);
                pStr = OBJ_NIL;
            }
        }

        obj_Release(pObj);
        pObj = OBJ_NIL;
    }

    fprintf(stderr, "...%s completed.\n\n\n", pTestName);
    return 1;
}




TINYTEST_START_SUITE(test_Main);
    TINYTEST_ADD_TEST(test_Main_TestHelp01,setUp,tearDown);
    TINYTEST_ADD_TEST(test_Main_ParseArg01,setUp,tearDown);
    TINYTEST_ADD_TEST(test_Main_Test01,setUp,tearDown);
    //TINYTEST_ADD_TEST(test_Main_Copy01,setUp,tearDown);
    TINYTEST_ADD_TEST(test_Main_OpenClose,setUp,tearDown);
TINYTEST_END_SUITE();

TINYTEST_MAIN_SINGLE_SUITE(test_Main);





