/*
 *	Generated 11/07/2019 08:58:19
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
#include    <AStrCArray_internal.h>



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






int             test_AStrCArray_OpenClose(
    const
    char            *pTestName
)
{
    ERESULT         eRc = ERESULT_SUCCESS;
    ASTRCARRAY_DATA	    *pObj = OBJ_NIL;
   
    fprintf(stderr, "Performing: %s\n", pTestName);

    pObj = AStrCArray_Alloc( );
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    pObj = AStrCArray_Init( pObj );
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    if (pObj) {

        //obj_TraceSet(pObj, true);       
        
        // Test something.
        TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );

        obj_Release(pObj);
        pObj = OBJ_NIL;
    }

    fprintf(stderr, "...%s completed.\n\n", pTestName);
    return 1;
}



int         test_AStrCArray_NewFromArgV(
    const
    char        *pTestName
)
{
    ASTRCARRAY_DATA *pObj = OBJ_NIL;
    int             cArg = 5;
    const
    char            *pArgV[] ={
        "abc/def/x.txt",
        "jjj",
        "kk",
        "ll",
        "mm"
    };
    ASTRC_DATA      *pStr = OBJ_NIL;
    int             i;
    
    fprintf(stderr, "Performing: %s\n", pTestName);
    
    pObj = AStrCArray_NewFromArgV(cArg, pArgV);
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    if (pObj) {
        
        i = AStrCArray_getSize(pObj);
        TINYTEST_TRUE( (i == cArg) );
        pStr = AStrCArray_Get(pObj, 1);
        TINYTEST_FALSE( (OBJ_NIL == pStr) );
        TINYTEST_TRUE( (ERESULT_SUCCESS_EQUAL == AStrC_CompareA(pStr, "abc/def/x.txt")) );
        pStr = AStrCArray_Get(pObj, 2);
        TINYTEST_FALSE( (OBJ_NIL == pStr) );
        TINYTEST_TRUE( (ERESULT_SUCCESS_EQUAL == AStrC_CompareA(pStr, "jjj")) );
        pStr = AStrCArray_Get(pObj, 3);
        TINYTEST_FALSE( (OBJ_NIL == pStr) );
        TINYTEST_TRUE( (ERESULT_SUCCESS_EQUAL == AStrC_CompareA(pStr, "kk")) );
        pStr = AStrCArray_Get(pObj, 4);
        TINYTEST_FALSE( (OBJ_NIL == pStr) );
        TINYTEST_TRUE( (ERESULT_SUCCESS_EQUAL == AStrC_CompareA(pStr, "ll")) );
        pStr = AStrCArray_Get(pObj, 5);
        TINYTEST_FALSE( (OBJ_NIL == pStr) );
        TINYTEST_TRUE( (ERESULT_SUCCESS_EQUAL == AStrC_CompareA(pStr, "mm")) );

        obj_Release(pObj);
        pObj = OBJ_NIL;
    }
    
    pObj = AStrCArray_NewFromArgV((cArg - 1), pArgV);
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    if (pObj) {
        
        i = AStrCArray_getSize(pObj);
        TINYTEST_TRUE( (i == (cArg - 1)) );
        pStr = AStrCArray_Get(pObj, 1);
        TINYTEST_FALSE( (OBJ_NIL == pStr) );
        TINYTEST_TRUE( (ERESULT_SUCCESS_EQUAL == AStrC_CompareA(pStr, "abc/def/x.txt")) );
        pStr = AStrCArray_Get(pObj, 2);
        TINYTEST_FALSE( (OBJ_NIL == pStr) );
        TINYTEST_TRUE( (ERESULT_SUCCESS_EQUAL == AStrC_CompareA(pStr, "jjj")) );
        pStr = AStrCArray_Get(pObj, 3);
        TINYTEST_FALSE( (OBJ_NIL == pStr) );
        TINYTEST_TRUE( (ERESULT_SUCCESS_EQUAL == AStrC_CompareA(pStr, "kk")) );
        pStr = AStrCArray_Get(pObj, 4);
        TINYTEST_FALSE( (OBJ_NIL == pStr) );
        TINYTEST_TRUE( (ERESULT_SUCCESS_EQUAL == AStrC_CompareA(pStr, "ll")) );
        pStr = AStrCArray_Get(pObj, 5);
        TINYTEST_TRUE( (OBJ_NIL == pStr) );
        
        obj_Release(pObj);
        pObj = OBJ_NIL;
    }
    
    fprintf(stderr, "...%s completed.\n", pTestName);
    return 1;
}



int         test_AStrCArray_NewFromArrayA(
    const
    char        *pTestName
)
{
    ASTRCARRAY_DATA *pObj = OBJ_NIL;
    const
    char            *pArgV[] ={
        "abc/def/x.txt",
        "jjj",
        "kk",
        "ll",
        "mm",
        NULL
    };
    ASTRC_DATA      *pStr = OBJ_NIL;
    int             i;
    
    fprintf(stderr, "Performing: %s\n", pTestName);
    
    pObj = AStrCArray_NewFromArrayA(pArgV);
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    if (pObj) {
        
        i = AStrCArray_getSize(pObj);
        TINYTEST_TRUE( (5 == i) );
        pStr = AStrCArray_Get(pObj, 1);
        TINYTEST_FALSE( (OBJ_NIL == pStr) );
        TINYTEST_TRUE( (ERESULT_SUCCESS_EQUAL == AStrC_CompareA(pStr, "abc/def/x.txt")) );
        pStr = AStrCArray_Get(pObj, 2);
        TINYTEST_FALSE( (OBJ_NIL == pStr) );
        TINYTEST_TRUE( (ERESULT_SUCCESS_EQUAL == AStrC_CompareA(pStr, "jjj")) );
        pStr = AStrCArray_Get(pObj, 3);
        TINYTEST_FALSE( (OBJ_NIL == pStr) );
        TINYTEST_TRUE( (ERESULT_SUCCESS_EQUAL == AStrC_CompareA(pStr, "kk")) );
        pStr = AStrCArray_Get(pObj, 4);
        TINYTEST_FALSE( (OBJ_NIL == pStr) );
        TINYTEST_TRUE( (ERESULT_SUCCESS_EQUAL == AStrC_CompareA(pStr, "ll")) );
        pStr = AStrCArray_Get(pObj, 5);
        TINYTEST_FALSE( (OBJ_NIL == pStr) );
        TINYTEST_TRUE( (ERESULT_SUCCESS_EQUAL == AStrC_CompareA(pStr, "mm")) );
        
        obj_Release(pObj);
        pObj = OBJ_NIL;
    }
    
    fprintf(stderr, "...%s completed.\n", pTestName);
    return 1;
}




TINYTEST_START_SUITE(test_AStrCArray);
    TINYTEST_ADD_TEST(test_AStrCArray_NewFromArrayA,setUp,tearDown);
    TINYTEST_ADD_TEST(test_AStrCArray_NewFromArgV,setUp,tearDown);
    TINYTEST_ADD_TEST(test_AStrCArray_OpenClose,setUp,tearDown);
TINYTEST_END_SUITE();

TINYTEST_MAIN_SINGLE_SUITE(test_AStrCArray);





