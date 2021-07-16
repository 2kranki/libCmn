// vi:nu:et:sts=4 ts=4 sw=4
/*
 *  Generated 07/15/2021 10:35:28
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
#include    <test_defs.h>
#include    <trace.h>
#include    <W32Array_internal.h>
#include    <JsonIn.h>
#ifdef  W32ARRAY_JSON_SUPPORT
#   include    <SrcErrors.h>
#   include    <szTbl.h>
#endif



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

#ifdef  W32ARRAY_JSON_SUPPORT
    SrcErrors_SharedReset( );
    szTbl_SharedReset( );
#endif
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






int             test_W32Array_OpenClose (
    const
    char            *pTestName
)
{
    ERESULT         eRc = ERESULT_SUCCESS;
    W32ARRAY_DATA       *pObj = OBJ_NIL;
    bool            fRc;
   
    fprintf(stderr, "Performing: %s\n", pTestName);

    pObj = W32Array_Alloc( );
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    pObj = W32Array_Init( pObj );
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    if (pObj) {

        //obj_TraceSet(pObj, true);       
        fRc = obj_IsKindOf(pObj, OBJ_IDENT_W32ARRAY);
        TINYTEST_TRUE( (fRc) );
        
        // Test something.
        TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );

        obj_Release(pObj);
        pObj = OBJ_NIL;
    }

    fprintf(stderr, "...%s completed.\n\n\n", pTestName);
    return 1;
}



int             test_W32Array_Copy01 (
    const
    char            *pTestName
)
{
    ERESULT         eRc = ERESULT_SUCCESS;
    W32ARRAY_DATA   *pObj1 = OBJ_NIL;
    W32ARRAY_DATA   *pObj2 = OBJ_NIL;
    bool            fRc;
    ASTR_DATA       *pStr = OBJ_NIL;
    W32STR_DATA     *pW32Str = OBJ_NIL;
    int             cArg = 5;
    const
    char            *pArgV[] ={
        "abc/def/x.txt",
        "jjj",
        "kk",
        "ll",
        "mm"
    };
    W32STR_DATA     *pWrk = OBJ_NIL;
    int             i;

    fprintf(stderr, "Performing: %s\n", pTestName);

    pObj1 = W32Array_NewFromArgV(cArg, pArgV);
    TINYTEST_FALSE( (OBJ_NIL == pObj1) );
    if (pObj1) {

        obj_TraceSet(pObj1, true);       
        fRc = obj_IsKindOf(pObj1, OBJ_IDENT_W32ARRAY);
        TINYTEST_TRUE( (fRc) );
        i = W32Array_getSize(pObj1);
        TINYTEST_TRUE( (i == cArg) );
        pWrk = W32Array_Get(pObj1, 1);
        TINYTEST_FALSE( (OBJ_NIL == pWrk) );
        TINYTEST_TRUE( (0 == W32Str_CompareA(pWrk, "abc/def/x.txt")) );
        pWrk = W32Array_Get(pObj1, 2);
        TINYTEST_FALSE( (OBJ_NIL == pWrk) );
        TINYTEST_TRUE( (0 == W32Str_CompareA(pWrk, "jjj")) );
        pWrk = W32Array_Get(pObj1, 3);
        TINYTEST_FALSE( (OBJ_NIL == pWrk) );
        TINYTEST_TRUE( (0 == W32Str_CompareA(pWrk, "kk")) );
        pWrk = W32Array_Get(pObj1, 4);
        TINYTEST_FALSE( (OBJ_NIL == pWrk) );
        TINYTEST_TRUE( (0 == W32Str_CompareA(pWrk, "ll")) );
        pWrk = W32Array_Get(pObj1, 5);
        TINYTEST_FALSE( (OBJ_NIL == pWrk) );
        TINYTEST_TRUE( (0 == W32Str_CompareA(pWrk, "mm")) );

        // Test assign.
        pObj2 = W32Array_New();
        TINYTEST_FALSE( (OBJ_NIL == pObj2) );
        eRc = W32Array_Assign(pObj1, pObj2);
        TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );

        fRc = obj_IsKindOf(pObj2, OBJ_IDENT_W32ARRAY);
        TINYTEST_TRUE( (fRc) );
        i = W32Array_getSize(pObj2);
        TINYTEST_TRUE( (i == cArg) );
        pWrk = W32Array_Get(pObj2, 1);
        TINYTEST_FALSE( (OBJ_NIL == pWrk) );
        TINYTEST_TRUE( (0 == W32Str_CompareA(pWrk, "abc/def/x.txt")) );
        pWrk = W32Array_Get(pObj2, 2);
        TINYTEST_FALSE( (OBJ_NIL == pWrk) );
        TINYTEST_TRUE( (0 == W32Str_CompareA(pWrk, "jjj")) );
        pWrk = W32Array_Get(pObj2, 3);
        TINYTEST_FALSE( (OBJ_NIL == pWrk) );
        TINYTEST_TRUE( (0 == W32Str_CompareA(pWrk, "kk")) );
        pWrk = W32Array_Get(pObj2, 4);
        TINYTEST_FALSE( (OBJ_NIL == pWrk) );
        TINYTEST_TRUE( (0 == W32Str_CompareA(pWrk, "ll")) );
        pWrk = W32Array_Get(pObj2, 5);
        TINYTEST_FALSE( (OBJ_NIL == pWrk) );
        TINYTEST_TRUE( (0 == W32Str_CompareA(pWrk, "mm")) );
        obj_Release(pObj2);
        pObj2 = OBJ_NIL;

        // Test copy.
        pObj2 = W32Array_Copy(pObj1);
        TINYTEST_FALSE( (OBJ_NIL == pObj2) );

        fRc = obj_IsKindOf(pObj2, OBJ_IDENT_W32ARRAY);
        TINYTEST_TRUE( (fRc) );
        i = W32Array_getSize(pObj2);
        TINYTEST_TRUE( (i == cArg) );
        pWrk = W32Array_Get(pObj2, 1);
        TINYTEST_FALSE( (OBJ_NIL == pWrk) );
        TINYTEST_TRUE( (0 == W32Str_CompareA(pWrk, "abc/def/x.txt")) );
        pWrk = W32Array_Get(pObj2, 2);
        TINYTEST_FALSE( (OBJ_NIL == pWrk) );
        TINYTEST_TRUE( (0 == W32Str_CompareA(pWrk, "jjj")) );
        pWrk = W32Array_Get(pObj2, 3);
        TINYTEST_FALSE( (OBJ_NIL == pWrk) );
        TINYTEST_TRUE( (0 == W32Str_CompareA(pWrk, "kk")) );
        pWrk = W32Array_Get(pObj2, 4);
        TINYTEST_FALSE( (OBJ_NIL == pWrk) );
        TINYTEST_TRUE( (0 == W32Str_CompareA(pWrk, "ll")) );
        pWrk = W32Array_Get(pObj2, 5);
        TINYTEST_FALSE( (OBJ_NIL == pWrk) );
        TINYTEST_TRUE( (0 == W32Str_CompareA(pWrk, "mm")) );

        obj_Release(pObj2);
        pObj2 = OBJ_NIL;

        // Test json support.
        pStr = W32Array_ToJson(pObj1);
        TINYTEST_FALSE( (OBJ_NIL == pStr) );
        fprintf(stderr, "JSON: %s\n", AStr_getData(pStr));
        pObj2 = W32Array_NewFromJsonString(pStr);
        TINYTEST_FALSE( (OBJ_NIL == pObj2) );
        fRc = obj_IsKindOf(pObj2, OBJ_IDENT_W32ARRAY);
        TINYTEST_TRUE( (fRc) );
        obj_Release(pStr);
        pStr = OBJ_NIL;
        i = W32Array_getSize(pObj2);
        TINYTEST_TRUE( (i == cArg) );
        pWrk = W32Array_Get(pObj2, 1);
        TINYTEST_FALSE( (OBJ_NIL == pWrk) );
        TINYTEST_TRUE( (0 == W32Str_CompareA(pWrk, "abc/def/x.txt")) );
        pWrk = W32Array_Get(pObj2, 2);
        TINYTEST_FALSE( (OBJ_NIL == pWrk) );
        TINYTEST_TRUE( (0 == W32Str_CompareA(pWrk, "jjj")) );
        pWrk = W32Array_Get(pObj2, 3);
        TINYTEST_FALSE( (OBJ_NIL == pWrk) );
        TINYTEST_TRUE( (0 == W32Str_CompareA(pWrk, "kk")) );
        pWrk = W32Array_Get(pObj2, 4);
        TINYTEST_FALSE( (OBJ_NIL == pWrk) );
        TINYTEST_TRUE( (0 == W32Str_CompareA(pWrk, "ll")) );
        pWrk = W32Array_Get(pObj2, 5);
        TINYTEST_FALSE( (OBJ_NIL == pWrk) );
        TINYTEST_TRUE( (0 == W32Str_CompareA(pWrk, "mm")) );

        obj_Release(pObj2);
        pObj2 = OBJ_NIL;

        obj_Release(pObj1);
        pObj1 = OBJ_NIL;
    }

    fprintf(stderr, "...%s completed.\n\n\n", pTestName);
    return 1;
}



int             test_W32Array_Test01 (
    const
    char            *pTestName
)
{
    //ERESULT         eRc = ERESULT_SUCCESS;
    W32ARRAY_DATA   *pObj = OBJ_NIL;
    bool            fRc;
   
    fprintf(stderr, "Performing: %s\n", pTestName);

    pObj = W32Array_New( );
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    if (pObj) {

        //obj_TraceSet(pObj, true);       
        fRc = obj_IsKindOf(pObj, OBJ_IDENT_W32ARRAY);
        TINYTEST_TRUE( (fRc) );
        //TINYTEST_TRUE( (ERESULT_OK(eRc)) );
        
        {
            ASTR_DATA       *pStr = W32Array_ToDebugString(pObj, 4);
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




TINYTEST_START_SUITE(test_W32Array);
    TINYTEST_ADD_TEST(test_W32Array_Test01,setUp,tearDown);
    TINYTEST_ADD_TEST(test_W32Array_Copy01,setUp,tearDown);
    TINYTEST_ADD_TEST(test_W32Array_OpenClose,setUp,tearDown);
TINYTEST_END_SUITE();

TINYTEST_MAIN_SINGLE_SUITE(test_W32Array);





