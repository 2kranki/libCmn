// vi:nu:et:sts=4 ts=4 sw=4
/*
 *  Generated 10/19/2020 16:14:31
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
#include    <SrcFiles_internal.h>
#ifdef  SRCFILES_JSON_SUPPORT
#   include    <SrcErrors.h>
#endif
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

#ifdef  SRCFILES_JSON_SUPPORT
    SrcErrors_SharedReset( );
#endif
    szTbl_SharedReset( );
    trace_SharedReset( );
    if (mem_Dump( ) ) {
        fprintf(
                stderr,
                "\x1b[1m"
                "\x1b[31m"
                "ERROR: "
                "\x1b[0m"
                "Leaked memory areas were found!\n\n\n\n\n"
        );
        exitCode = 4;
        return 0;
    }
    mem_Release( );
    
    return 1; 
}






int             test_SrcFiles_OpenClose (
    const
    char            *pTestName
)
{
    ERESULT         eRc = ERESULT_SUCCESS;
    SRCFILES_DATA       *pObj = OBJ_NIL;
    bool            fRc;
   
    fprintf(stderr, "Performing: %s\n", pTestName);

    pObj = SrcFiles_Alloc( );
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    pObj = SrcFiles_Init( pObj );
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    if (pObj) {

        //obj_TraceSet(pObj, true);       
        fRc = obj_IsKindOf(pObj, OBJ_IDENT_SRCFILES);
        TINYTEST_TRUE( (fRc) );
        
        // Test something.
        TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );

        obj_Release(pObj);
        pObj = OBJ_NIL;
    }

    fprintf(stderr, "...%s completed.\n\n\n", pTestName);
    return 1;
}



int             test_SrcFiles_Copy01 (
    const
    char            *pTestName
)
{
    ERESULT         eRc = ERESULT_SUCCESS;
    SRCFILES_DATA       *pObj1 = OBJ_NIL;
    SRCFILES_DATA       *pObj2 = OBJ_NIL;
    bool            fRc;
#if defined(SRCFILES_JSON_SUPPORT) && defined(XYZZY)
    ASTR_DATA       *pStr = OBJ_NIL;
#endif
   
    fprintf(stderr, "Performing: %s\n", pTestName);

    pObj1 = SrcFiles_New( );
    TINYTEST_FALSE( (OBJ_NIL == pObj1) );
    if (pObj1) {

        //obj_TraceSet(pObj1, true);       
        fRc = obj_IsKindOf(pObj1, OBJ_IDENT_SRCFILES);
        TINYTEST_TRUE( (fRc) );
        
        // Test assign.
        pObj2 = SrcFiles_New();
        TINYTEST_FALSE( (OBJ_NIL == pObj2) );
        eRc = SrcFiles_Assign(pObj1, pObj2);
        TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );

        fRc = obj_IsKindOf(pObj2, OBJ_IDENT_SRCFILES);
        TINYTEST_TRUE( (fRc) );
        //eRc = SrcFiles_Compare(pObj1, pObj2);
        //TINYTEST_TRUE( (ERESULT_SUCCESS_EQUAL == eRc) );
        //TODO: Add More tests here!

        obj_Release(pObj2);
        pObj2 = OBJ_NIL;

        // Test copy.
        pObj2 = SrcFiles_Copy(pObj1);
        TINYTEST_FALSE( (OBJ_NIL == pObj2) );

        fRc = obj_IsKindOf(pObj2, OBJ_IDENT_SRCFILES);
        TINYTEST_TRUE( (fRc) );
        //eRc = SrcFiles_Compare(pObj1, pObj2);
        //TINYTEST_TRUE( (ERESULT_SUCCESS_EQUAL == eRc) );
        //TODO: Add More tests here!

        obj_Release(pObj2);
        pObj2 = OBJ_NIL;

        // Test json support.
#if defined(SRCFILES_JSON_SUPPORT) && defined(XYZZY)
        pStr = SrcFiles_ToJson(pObj1);
        TINYTEST_FALSE( (OBJ_NIL == pStr) );
        fprintf(stderr, "JSON: %s\n", AStr_getData(pStr));
        pObj2 = SrcFiles_NewFromJsonString(pStr);
        TINYTEST_FALSE( (OBJ_NIL == pObj2) );
        fRc = obj_IsKindOf(pObj2, OBJ_IDENT_SRCFILES);
        TINYTEST_TRUE( (fRc) );
        obj_Release(pStr);
        pStr = OBJ_NIL;
        //eRc = SrcFiles_Compare(pObj1, pObj2);
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



int             test_SrcFiles_Test01 (
    const
    char            *pTestName
)
{
    //ERESULT         eRc = ERESULT_SUCCESS;
    SRCFILES_DATA       *pObj = OBJ_NIL;
    bool            fRc;
   
    fprintf(stderr, "Performing: %s\n", pTestName);

    pObj = SrcFiles_New( );
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    if (pObj) {

        //obj_TraceSet(pObj, true);       
        fRc = obj_IsKindOf(pObj, OBJ_IDENT_SRCFILES);
        TINYTEST_TRUE( (fRc) );
        //TINYTEST_TRUE( (ERESULT_OK(eRc)) );
        
        {
            ASTR_DATA       *pStr = SrcFiles_ToDebugString(pObj, 0);
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



int         test_SrcFiles_TestPath01(
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
    pPath = Path_NewA(pPathA);
    TINYTEST_FALSE( (OBJ_NIL == pPath) );

    pObj = SrcFiles_New( );
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    if (pObj) {

        eRc = SrcFiles_NewSrcFromPath(pObj, pPath, 0, 4);
        TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );

        for (;;) {
            pToken = SrcFiles_InputLookAhead(pObj, 1);
            XCTAssertFalse( (OBJ_NIL == pToken) );
            cls = Token_getClass(pToken);
            if (cls == -1)
                break;
            {
                pStr = Token_ToDebugString(pToken, 0);
                fprintf(stderr, "\ttoken text=\"%s\"\n",
                        AStr_getData(pStr));
                obj_Release(pStr);
                pStr = OBJ_NIL;
            }
            pToken = SrcFiles_InputAdvance(pObj, 1);
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



int         test_SrcFiles_TestAStr01(
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
    const
    char            *pStrA = "label opcode\n";

    fprintf(stderr, "Performing: %s\n", pTestName);
    pPath = Path_NewA(pPathA);
    TINYTEST_FALSE( (OBJ_NIL == pPath) );

    pObj = SrcFiles_New( );
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    if (pObj) {

        pStr = AStr_NewA(pStrA);
        TINYTEST_FALSE( (OBJ_NIL == pStr) );
        eRc = SrcFiles_NewSrcFromAStr(pObj, pPath, pStr, 0, 4);
        TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );
        obj_Release(pStr);
        pStr = OBJ_NIL;

        for (;;) {
            pToken = SrcFiles_InputLookAhead(pObj, 1);
            XCTAssertFalse( (OBJ_NIL == pToken) );
            cls = Token_getClass(pToken);
            if (cls == -1)
                break;
            {
                pStr = Token_ToDebugString(pToken, 0);
                fprintf(
                        stderr,
                        "\ttoken text=\"%s\"\n",
                        AStr_getData(pStr)
                );
                obj_Release(pStr);
                pStr = OBJ_NIL;
            }
            pToken = SrcFiles_InputAdvance(pObj, 1);
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




TINYTEST_START_SUITE(test_SrcFiles);
    TINYTEST_ADD_TEST(test_SrcFiles_TestAStr01,setUp,tearDown);
    TINYTEST_ADD_TEST(test_SrcFiles_TestPath01,setUp,tearDown);
    TINYTEST_ADD_TEST(test_SrcFiles_Test01,setUp,tearDown);
    //TINYTEST_ADD_TEST(test_SrcFiles_Copy01,setUp,tearDown);
    TINYTEST_ADD_TEST(test_SrcFiles_OpenClose,setUp,tearDown);
TINYTEST_END_SUITE();

TINYTEST_MAIN_SINGLE_SUITE(test_SrcFiles);





