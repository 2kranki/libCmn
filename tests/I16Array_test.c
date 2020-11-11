// vi:nu:et:sts=4 ts=4 sw=4
/*
 *	Generated 02/19/2020 09:52:11
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
#include    <I16Array_internal.h>
#ifdef  I16ARRAY_JSON_SUPPORT
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

#ifdef  I16ARRAY_JSON_SUPPORT
    SrcErrors_SharedReset( );
    szTbl_SharedReset( );
#endif
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






int             test_I16Array_OpenClose (
    const
    char            *pTestName
)
{
    ERESULT         eRc = ERESULT_SUCCESS;
    I16ARRAY_DATA	    *pObj = OBJ_NIL;
    bool            fRc;
   
    fprintf(stderr, "Performing: %s\n", pTestName);

    pObj = I16Array_Alloc( );
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    pObj = I16Array_Init( pObj );
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    if (pObj) {

        //obj_TraceSet(pObj, true);       
        fRc = obj_IsKindOf(pObj, OBJ_IDENT_I16ARRAY);
        TINYTEST_TRUE( (fRc) );
        
        // Test something.
        TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );

        obj_Release(pObj);
        pObj = OBJ_NIL;
    }

    fprintf(stderr, "...%s completed.\n\n\n", pTestName);
    return 1;
}



int             test_I16Array_Copy01 (
    const
    char            *pTestName
)
{
    ERESULT         eRc = ERESULT_SUCCESS;
    I16ARRAY_DATA	*pObj1 = OBJ_NIL;
    I16ARRAY_DATA	*pObj2 = OBJ_NIL;
    bool            fRc;
    ASTR_DATA	    *pStr = OBJ_NIL;
    int             i;
    int16_t         data;

    fprintf(stderr, "Performing: %s\n", pTestName);

    pObj1 = I16Array_New( );
    TINYTEST_FALSE( (OBJ_NIL == pObj1) );
    if (pObj1) {

        //obj_TraceSet(pObj1, true);       
        fRc = obj_IsKindOf(pObj1, OBJ_IDENT_I16ARRAY);
        TINYTEST_TRUE( (fRc) );
        
        for (i=1; i<=64; ++i) {
            eRc = I16Array_AppendData(pObj1, i);
            XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
        }

        // Test assign.
        pObj2 = I16Array_New();
        TINYTEST_FALSE( (OBJ_NIL == pObj2) );
        eRc = I16Array_Assign(pObj1, pObj2);
        TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );

        fRc = obj_IsKindOf(pObj2, OBJ_IDENT_I16ARRAY);
        TINYTEST_TRUE( (fRc) );
        eRc = I16Array_Compare(pObj1, pObj2);
        TINYTEST_TRUE( (0 == eRc) );

        obj_Release(pObj2);
        pObj2 = OBJ_NIL;

        // Test copy.
        pObj2 = I16Array_Copy(pObj1);
        TINYTEST_FALSE( (OBJ_NIL == pObj2) );

        fRc = obj_IsKindOf(pObj2, OBJ_IDENT_I16ARRAY);
        TINYTEST_TRUE( (fRc) );
        eRc = I16Array_Compare(pObj1, pObj2);
        TINYTEST_TRUE( (0 == eRc) );

        obj_Release(pObj2);
        pObj2 = OBJ_NIL;

        // Test json support.
        pStr = I16Array_ToJson(pObj1);
        TINYTEST_FALSE( (OBJ_NIL == pStr) );
        fprintf(stderr, "JSON: %s\n", AStr_getData(pStr));
        pObj2 = I16Array_NewFromJsonString(pStr);
        TINYTEST_FALSE( (OBJ_NIL == pObj2) );
        fRc = obj_IsKindOf(pObj2, OBJ_IDENT_I16ARRAY);
        TINYTEST_TRUE( (fRc) );
        obj_Release(pStr);
        pStr = OBJ_NIL;
        eRc = I16Array_Compare(pObj1, pObj2);
        TINYTEST_TRUE( (0 == eRc) );

        obj_Release(pObj2);
        pObj2 = OBJ_NIL;

        obj_Release(pObj1);
        pObj1 = OBJ_NIL;
    }

    fprintf(stderr, "...%s completed.\n\n\n", pTestName);
    return 1;
}



int             test_I16Array_Test01 (
    const
    char            *pTestName
)
{
    ERESULT         eRc = ERESULT_SUCCESS;
    I16ARRAY_DATA	*pObj = OBJ_NIL;
    bool            fRc;
    int             i;
    int16_t         data;

    fprintf(stderr, "Performing: %s\n", pTestName);

    pObj = I16Array_New( );
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    if (pObj) {

        //obj_TraceSet(pObj, true);       
        fRc = obj_IsKindOf(pObj, OBJ_IDENT_I16ARRAY);
        TINYTEST_TRUE( (fRc) );
        
        for (i=1; i<=64; ++i) {
            eRc = I16Array_AppendData(pObj, i);
            XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
        }

        for (i=1; i<=64; ++i) {
            data = I16Array_Get(pObj, i);
            XCTAssertTrue( (data == i) );
        }

        obj_Release(pObj);
        pObj = OBJ_NIL;
    }

    fprintf(stderr, "...%s completed.\n\n\n", pTestName);
    return 1;
}




TINYTEST_START_SUITE(test_I16Array);
    TINYTEST_ADD_TEST(test_I16Array_Test01,setUp,tearDown);
    TINYTEST_ADD_TEST(test_I16Array_Copy01,setUp,tearDown);
    TINYTEST_ADD_TEST(test_I16Array_OpenClose,setUp,tearDown);
TINYTEST_END_SUITE();

TINYTEST_MAIN_SINGLE_SUITE(test_I16Array);





