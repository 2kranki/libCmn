// vi:nu:et:sts=4 ts=4 sw=4
/*
 *	Generated 01/14/2020 18:29:58
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
#include    <szTbl.h>
#include    <trace.h>
#include    <I32Array_internal.h>



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






int             test_I32Array_OpenClose (
    const
    char            *pTestName
)
{
    ERESULT         eRc = ERESULT_SUCCESS;
    I32ARRAY_DATA	    *pObj = OBJ_NIL;
    bool            fRc;
   
    fprintf(stderr, "Performing: %s\n", pTestName);

    pObj = I32Array_Alloc( );
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    pObj = I32Array_Init( pObj );
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    if (pObj) {

        //obj_TraceSet(pObj, true);       
        fRc = obj_IsKindOf(pObj, OBJ_IDENT_I32ARRAY);
        TINYTEST_TRUE( (fRc) );
        
        // Test something.
        TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );

        obj_Release(pObj);
        pObj = OBJ_NIL;
    }

    fprintf(stderr, "...%s completed.\n\n\n", pTestName);
    return 1;
}



int             test_I32Array_Copy01 (
    const
    char            *pTestName
)
{
    //ERESULT         eRc = ERESULT_SUCCESS;
    I32ARRAY_DATA	    *pObj1 = OBJ_NIL;
    I32ARRAY_DATA	    *pObj2 = OBJ_NIL;
    bool            fRc;
   
    fprintf(stderr, "Performing: %s\n", pTestName);

    pObj1 = I32Array_New( );
    TINYTEST_FALSE( (OBJ_NIL == pObj1) );
    if (pObj1) {

        //obj_TraceSet(pObj1, true);       
        fRc = obj_IsKindOf(pObj1, OBJ_IDENT_I32ARRAY);
        TINYTEST_TRUE( (fRc) );
        
        // Test something.
        pObj2 = I32Array_Copy(pObj1);
        TINYTEST_FALSE( (OBJ_NIL == pObj2) );

        fRc = obj_IsKindOf(pObj2, OBJ_IDENT_I32ARRAY);
        TINYTEST_TRUE( (fRc) );
        //TODO: Add More tests here!

        obj_Release(pObj2);
        pObj2 = OBJ_NIL;

        obj_Release(pObj1);
        pObj1 = OBJ_NIL;
    }

    fprintf(stderr, "...%s completed.\n\n\n", pTestName);
    return 1;
}



int             test_I32Array_Test01 (
    const
    char            *pTestName
)
{
    ERESULT         eRc = ERESULT_SUCCESS;
    I32ARRAY_DATA	*pObj = OBJ_NIL;
    I32ARRAY_DATA   *pObj2 = OBJ_NIL;
    bool            fRc;
    uint32_t        i;
    uint32_t        data;
    ASTR_DATA       *pStr = OBJ_NIL;

    fprintf(stderr, "Performing: %s\n", pTestName);

    pObj = I32Array_Alloc( );
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    pObj = I32Array_Init( pObj );
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    if (pObj) {

        //obj_TraceSet(pObj, true);       
        fRc = obj_IsKindOf(pObj, OBJ_IDENT_I32ARRAY);
        TINYTEST_TRUE( (fRc) );
        
        for (i=1; i<=64; ++i) {
            eRc = I32Array_AppendData(pObj, i);
            TINYTEST_TRUE( (ERESULT_IS_SUCCESSFUL(eRc)) );
        }

        for (i=1; i<=64; ++i) {
            data = I32Array_Get(pObj, i);
            TINYTEST_TRUE( (data == i) );
        }

        pStr = I32Array_ToJson(pObj);
        TINYTEST_FALSE( (OBJ_NIL == pObj) );
        fprintf(stderr, "JSON: %s\n", AStr_getData(pStr));
        pObj2 = I32Array_NewFromJsonString(pStr);
        TINYTEST_FALSE( (OBJ_NIL == pObj2) );
        fRc = obj_IsKindOf(pObj2, OBJ_IDENT_I32ARRAY);
        TINYTEST_TRUE( (fRc) );
        obj_Release(pStr);
        pStr = OBJ_NIL;

        for (i=1; i<=64; ++i) {
            data = I32Array_Get(pObj2, i);
            TINYTEST_TRUE( (data == i) );
        }

        obj_Release(pObj2);
        pObj2 = OBJ_NIL;

        obj_Release(pObj);
        pObj = OBJ_NIL;
    }

    fprintf(stderr, "...%s completed.\n\n\n", pTestName);
    return 1;
}




TINYTEST_START_SUITE(test_I32Array);
    TINYTEST_ADD_TEST(test_I32Array_Test01,setUp,tearDown);
    //TINYTEST_ADD_TEST(test_I32Array_Copy01,setUp,tearDown);
    TINYTEST_ADD_TEST(test_I32Array_OpenClose,setUp,tearDown);
TINYTEST_END_SUITE();

TINYTEST_MAIN_SINGLE_SUITE(test_I32Array);





