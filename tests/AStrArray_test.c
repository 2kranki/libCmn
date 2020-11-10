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
#include    <AStrArray_internal.h>



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






int         test_AStrArray_OpenClose(
    const
    char        *pTestName
)
{
    ASTRARRAY_DATA	*pObj = OBJ_NIL;
   
    fprintf(stderr, "Performing: %s\n", pTestName);
    
    pObj = AStrArray_Alloc( );
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    pObj = AStrArray_Init( pObj );
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    if (pObj) {

        // Test something.

        obj_Release(pObj);
        pObj = OBJ_NIL;
    }

    fprintf(stderr, "...%s completed.\n", pTestName);
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
    TINYTEST_ADD_TEST(test_AStrArray_OpenClose,setUp,tearDown);
TINYTEST_END_SUITE();

TINYTEST_MAIN_SINGLE_SUITE(test_AStrArray);





