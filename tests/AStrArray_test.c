// vi:nu:et:sts=4 ts=4 sw=4
/*
 *  Generated 04/11/2021 10:41:38
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
#include    <AStrArray_internal.h>
#include    <JsonIn.h>
#ifdef  ASTRARRAY_JSON_SUPPORT
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

#ifdef  ASTRARRAY_JSON_SUPPORT
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






int             test_AStrArray_OpenClose (
    const
    char            *pTestName
)
{
    ERESULT         eRc = ERESULT_SUCCESS;
    ASTRARRAY_DATA       *pObj = OBJ_NIL;
    bool            fRc;
   
    fprintf(stderr, "Performing: %s\n", pTestName);

    pObj = AStrArray_Alloc( );
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    pObj = AStrArray_Init( pObj );
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    if (pObj) {

        //obj_TraceSet(pObj, true);       
        fRc = obj_IsKindOf(pObj, OBJ_IDENT_ASTRARRAY);
        TINYTEST_TRUE( (fRc) );
        
        // Test something.
        TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );

        obj_Release(pObj);
        pObj = OBJ_NIL;
    }

    fprintf(stderr, "...%s completed.\n\n\n", pTestName);
    return 1;
}



int             test_AStrArray_Copy01 (
    const
    char            *pTestName
)
{
    ERESULT         eRc = ERESULT_SUCCESS;
    ASTRARRAY_DATA  *pObj1 = OBJ_NIL;
    ASTRARRAY_DATA  *pObj2 = OBJ_NIL;
    bool            fRc;
    ASTR_DATA       *pStr = OBJ_NIL;
    int             cArg = 5;
    const
    char            *pArgV[] ={
        "abc/def/x.txt",
        "jjj",
        "kk",
        "ll",
        "mm"
    };
    ASTR_DATA       *pWrk = OBJ_NIL;
    int             i;

    fprintf(stderr, "Performing: %s\n", pTestName);

    pObj1 = AStrArray_NewFromArgV(cArg, pArgV);
    TINYTEST_FALSE( (OBJ_NIL == pObj1) );
    if (pObj1) {

        //obj_TraceSet(pObj1, true);       
        fRc = obj_IsKindOf(pObj1, OBJ_IDENT_ASTRARRAY);
        TINYTEST_TRUE( (fRc) );
        i = AStrArray_getSize(pObj1);
        TINYTEST_TRUE( (i == cArg) );
        pWrk = AStrArray_Get(pObj1, 1);
        TINYTEST_FALSE( (OBJ_NIL == pWrk) );
        TINYTEST_TRUE( (0 == AStr_CompareA(pWrk, "abc/def/x.txt")) );
        pWrk = AStrArray_Get(pObj1, 2);
        TINYTEST_FALSE( (OBJ_NIL == pWrk) );
        TINYTEST_TRUE( (0 == AStr_CompareA(pWrk, "jjj")) );
        pWrk = AStrArray_Get(pObj1, 3);
        TINYTEST_FALSE( (OBJ_NIL == pWrk) );
        TINYTEST_TRUE( (0 == AStr_CompareA(pWrk, "kk")) );
        pWrk = AStrArray_Get(pObj1, 4);
        TINYTEST_FALSE( (OBJ_NIL == pWrk) );
        TINYTEST_TRUE( (0 == AStr_CompareA(pWrk, "ll")) );
        pWrk = AStrArray_Get(pObj1, 5);
        TINYTEST_FALSE( (OBJ_NIL == pWrk) );
        TINYTEST_TRUE( (0 == AStr_CompareA(pWrk, "mm")) );

        // Test assign.
        pObj2 = AStrArray_New();
        TINYTEST_FALSE( (OBJ_NIL == pObj2) );
        eRc = AStrArray_Assign(pObj1, pObj2);
        TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );

        fRc = obj_IsKindOf(pObj2, OBJ_IDENT_ASTRARRAY);
        TINYTEST_TRUE( (fRc) );
        i = AStrArray_getSize(pObj2);
        TINYTEST_TRUE( (i == cArg) );
        pWrk = AStrArray_Get(pObj2, 1);
        TINYTEST_FALSE( (OBJ_NIL == pWrk) );
        TINYTEST_TRUE( (0 == AStr_CompareA(pWrk, "abc/def/x.txt")) );
        pWrk = AStrArray_Get(pObj2, 2);
        TINYTEST_FALSE( (OBJ_NIL == pWrk) );
        TINYTEST_TRUE( (0 == AStr_CompareA(pWrk, "jjj")) );
        pWrk = AStrArray_Get(pObj2, 3);
        TINYTEST_FALSE( (OBJ_NIL == pWrk) );
        TINYTEST_TRUE( (0 == AStr_CompareA(pWrk, "kk")) );
        pWrk = AStrArray_Get(pObj2, 4);
        TINYTEST_FALSE( (OBJ_NIL == pWrk) );
        TINYTEST_TRUE( (0 == AStr_CompareA(pWrk, "ll")) );
        pWrk = AStrArray_Get(pObj2, 5);
        TINYTEST_FALSE( (OBJ_NIL == pWrk) );
        TINYTEST_TRUE( (0 == AStr_CompareA(pWrk, "mm")) );

        obj_Release(pObj2);
        pObj2 = OBJ_NIL;

        // Test copy.
        pObj2 = AStrArray_Copy(pObj1);
        TINYTEST_FALSE( (OBJ_NIL == pObj2) );

        fRc = obj_IsKindOf(pObj2, OBJ_IDENT_ASTRARRAY);
        TINYTEST_TRUE( (fRc) );
        i = AStrArray_getSize(pObj2);
        TINYTEST_TRUE( (i == cArg) );
        pWrk = AStrArray_Get(pObj2, 1);
        TINYTEST_FALSE( (OBJ_NIL == pWrk) );
        TINYTEST_TRUE( (0 == AStr_CompareA(pWrk, "abc/def/x.txt")) );
        pWrk = AStrArray_Get(pObj2, 2);
        TINYTEST_FALSE( (OBJ_NIL == pWrk) );
        TINYTEST_TRUE( (0 == AStr_CompareA(pWrk, "jjj")) );
        pWrk = AStrArray_Get(pObj2, 3);
        TINYTEST_FALSE( (OBJ_NIL == pWrk) );
        TINYTEST_TRUE( (0 == AStr_CompareA(pWrk, "kk")) );
        pWrk = AStrArray_Get(pObj2, 4);
        TINYTEST_FALSE( (OBJ_NIL == pWrk) );
        TINYTEST_TRUE( (0 == AStr_CompareA(pWrk, "ll")) );
        pWrk = AStrArray_Get(pObj2, 5);
        TINYTEST_FALSE( (OBJ_NIL == pWrk) );
        TINYTEST_TRUE( (0 == AStr_CompareA(pWrk, "mm")) );

        obj_Release(pObj2);
        pObj2 = OBJ_NIL;

        // Test json support.
        pStr = AStrArray_ToJson(pObj1);
        TINYTEST_FALSE( (OBJ_NIL == pStr) );
        fprintf(stderr, "JSON: %s\n", AStr_getData(pStr));
        pObj2 = AStrArray_NewFromJsonString(pStr);
        TINYTEST_FALSE( (OBJ_NIL == pObj2) );
        fRc = obj_IsKindOf(pObj2, OBJ_IDENT_ASTRARRAY);
        TINYTEST_TRUE( (fRc) );
        obj_Release(pStr);
        pStr = OBJ_NIL;

        i = AStrArray_getSize(pObj2);
        TINYTEST_TRUE( (i == cArg) );
        pWrk = AStrArray_Get(pObj2, 1);
        TINYTEST_FALSE( (OBJ_NIL == pWrk) );
        TINYTEST_TRUE( (0 == AStr_CompareA(pWrk, "abc/def/x.txt")) );
        pWrk = AStrArray_Get(pObj2, 2);
        TINYTEST_FALSE( (OBJ_NIL == pWrk) );
        TINYTEST_TRUE( (0 == AStr_CompareA(pWrk, "jjj")) );
        pWrk = AStrArray_Get(pObj2, 3);
        TINYTEST_FALSE( (OBJ_NIL == pWrk) );
        TINYTEST_TRUE( (0 == AStr_CompareA(pWrk, "kk")) );
        pWrk = AStrArray_Get(pObj2, 4);
        TINYTEST_FALSE( (OBJ_NIL == pWrk) );
        TINYTEST_TRUE( (0 == AStr_CompareA(pWrk, "ll")) );
        pWrk = AStrArray_Get(pObj2, 5);
        TINYTEST_FALSE( (OBJ_NIL == pWrk) );
        TINYTEST_TRUE( (0 == AStr_CompareA(pWrk, "mm")) );

        obj_Release(pObj2);
        pObj2 = OBJ_NIL;

        obj_Release(pObj1);
        pObj1 = OBJ_NIL;
    }

    fprintf(stderr, "...%s completed.\n\n\n", pTestName);
    return 1;
}



int             test_AStrArray_Test01 (
    const
    char            *pTestName
)
{
    //ERESULT         eRc = ERESULT_SUCCESS;
    ASTRARRAY_DATA       *pObj = OBJ_NIL;
    bool            fRc;
   
    fprintf(stderr, "Performing: %s\n", pTestName);

    pObj = AStrArray_New( );
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    if (pObj) {

        //obj_TraceSet(pObj, true);       
        fRc = obj_IsKindOf(pObj, OBJ_IDENT_ASTRARRAY);
        TINYTEST_TRUE( (fRc) );
        //TINYTEST_TRUE( (ERESULT_OK(eRc)) );
        
        {
            ASTR_DATA       *pStr = AStrArray_ToDebugString(pObj, 0);
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



int         test_AStrArray_NewFromArgV(
    const
    char        *pTestName
)
{
    ASTRARRAY_DATA  *pObj = OBJ_NIL;
    int             cArg = 5;
    const
    char            *pArgV[] ={
        "abc/def/x.txt",
        "jjj",
        "kk",
        "ll",
        "mm"
    };
    ASTR_DATA       *pStr = OBJ_NIL;
    int             i;

    fprintf(stderr, "Performing: %s\n", pTestName);

    pObj = AStrArray_NewFromArgV(cArg, pArgV);
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    if (pObj) {

        i = AStrArray_getSize(pObj);
        TINYTEST_TRUE( (i == cArg) );
        pStr = AStrArray_Get(pObj, 1);
        TINYTEST_FALSE( (OBJ_NIL == pStr) );
        TINYTEST_TRUE( (0 == AStr_CompareA(pStr, "abc/def/x.txt")) );
        pStr = AStrArray_Get(pObj, 2);
        TINYTEST_FALSE( (OBJ_NIL == pStr) );
        TINYTEST_TRUE( (0 == AStr_CompareA(pStr, "jjj")) );
        pStr = AStrArray_Get(pObj, 3);
        TINYTEST_FALSE( (OBJ_NIL == pStr) );
        TINYTEST_TRUE( (0 == AStr_CompareA(pStr, "kk")) );
        pStr = AStrArray_Get(pObj, 4);
        TINYTEST_FALSE( (OBJ_NIL == pStr) );
        TINYTEST_TRUE( (0 == AStr_CompareA(pStr, "ll")) );
        pStr = AStrArray_Get(pObj, 5);
        TINYTEST_FALSE( (OBJ_NIL == pStr) );
        TINYTEST_TRUE( (0 == AStr_CompareA(pStr, "mm")) );

        obj_Release(pObj);
        pObj = OBJ_NIL;
    }

    pObj = AStrArray_NewFromArgV((cArg - 1), pArgV);
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    if (pObj) {

        i = AStrArray_getSize(pObj);
        TINYTEST_TRUE( (i == (cArg - 1)) );
        pStr = AStrArray_Get(pObj, 1);
        TINYTEST_FALSE( (OBJ_NIL == pStr) );
        TINYTEST_TRUE( (0 == AStr_CompareA(pStr, "abc/def/x.txt")) );
        pStr = AStrArray_Get(pObj, 2);
        TINYTEST_FALSE( (OBJ_NIL == pStr) );
        TINYTEST_TRUE( (0 == AStr_CompareA(pStr, "jjj")) );
        pStr = AStrArray_Get(pObj, 3);
        TINYTEST_FALSE( (OBJ_NIL == pStr) );
        TINYTEST_TRUE( (0 == AStr_CompareA(pStr, "kk")) );
        pStr = AStrArray_Get(pObj, 4);
        TINYTEST_FALSE( (OBJ_NIL == pStr) );
        TINYTEST_TRUE( (0 == AStr_CompareA(pStr, "ll")) );
        pStr = AStrArray_Get(pObj, 5);
        TINYTEST_TRUE( (OBJ_NIL == pStr) );

        obj_Release(pObj);
        pObj = OBJ_NIL;
    }

    fprintf(stderr, "...%s completed.\n", pTestName);
    return 1;
}



int         test_AStrArray_NewFromArrayA(
    const
    char        *pTestName
)
{
    ASTRARRAY_DATA  *pObj = OBJ_NIL;
    const
    char            *pArgV[] ={
        "abc/def/x.txt",
        "jjj",
        "kk",
        "ll",
        "mm",
        NULL
    };
    ASTR_DATA       *pStr = OBJ_NIL;
    int             i;

    fprintf(stderr, "Performing: %s\n", pTestName);

    pObj = AStrArray_NewFromArrayA(pArgV);
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    if (pObj) {

        i = AStrArray_getSize(pObj);
        TINYTEST_TRUE( (5 == i) );
        pStr = AStrArray_Get(pObj, 1);
        TINYTEST_FALSE( (OBJ_NIL == pStr) );
        TINYTEST_TRUE( (0 == AStr_CompareA(pStr, "abc/def/x.txt")) );
        pStr = AStrArray_Get(pObj, 2);
        TINYTEST_FALSE( (OBJ_NIL == pStr) );
        TINYTEST_TRUE( (0 == AStr_CompareA(pStr, "jjj")) );
        pStr = AStrArray_Get(pObj, 3);
        TINYTEST_FALSE( (OBJ_NIL == pStr) );
        TINYTEST_TRUE( (0 == AStr_CompareA(pStr, "kk")) );
        pStr = AStrArray_Get(pObj, 4);
        TINYTEST_FALSE( (OBJ_NIL == pStr) );
        TINYTEST_TRUE( (0 == AStr_CompareA(pStr, "ll")) );
        pStr = AStrArray_Get(pObj, 5);
        TINYTEST_FALSE( (OBJ_NIL == pStr) );
        TINYTEST_TRUE( (0 == AStr_CompareA(pStr, "mm")) );

        obj_Release(pObj);
        pObj = OBJ_NIL;
    }

    fprintf(stderr, "...%s completed.\n", pTestName);
    return 1;
}




TINYTEST_START_SUITE(test_AStrArray);
    TINYTEST_ADD_TEST(test_AStrArray_NewFromArrayA,setUp,tearDown);
    TINYTEST_ADD_TEST(test_AStrArray_NewFromArgV,setUp,tearDown);
    TINYTEST_ADD_TEST(test_AStrArray_Test01,setUp,tearDown);
    TINYTEST_ADD_TEST(test_AStrArray_Copy01,setUp,tearDown);
    TINYTEST_ADD_TEST(test_AStrArray_OpenClose,setUp,tearDown);
TINYTEST_END_SUITE();

TINYTEST_MAIN_SINGLE_SUITE(test_AStrArray);





