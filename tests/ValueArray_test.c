// vi:nu:et:sts=4 ts=4 sw=4
/*
 *  Generated 06/17/2021 14:31:59
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
#include    <ValueArray_internal.h>
#include    <JsonIn.h>
#ifdef  VALUEARRAY_JSON_SUPPORT
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

    SrcErrors_SharedReset( );
    szTbl_SharedReset( );
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






int             test_ValueArray_OpenClose (
    const
    char            *pTestName
)
{
    ERESULT         eRc = ERESULT_SUCCESS;
    VALUEARRAY_DATA       *pObj = OBJ_NIL;
    bool            fRc;
   
    fprintf(stderr, "Performing: %s\n", pTestName);

    pObj = ValueArray_Alloc( );
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    pObj = ValueArray_Init( pObj );
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    if (pObj) {

        //obj_TraceSet(pObj, true);       
        fRc = obj_IsKindOf(pObj, OBJ_IDENT_VALUEARRAY);
        TINYTEST_TRUE( (fRc) );
        
        // Test something.
        TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );

        obj_Release(pObj);
        pObj = OBJ_NIL;
    }

    fprintf(stderr, "...%s completed.\n\n\n", pTestName);
    return 1;
}



int             test_ValueArray_Copy01 (
    const
    char            *pTestName
)
{
    ERESULT         eRc = ERESULT_SUCCESS;
    VALUEARRAY_DATA       *pObj1 = OBJ_NIL;
    VALUEARRAY_DATA       *pObj2 = OBJ_NIL;
    bool            fRc;
#if defined(VALUEARRAY_JSON_SUPPORT) && defined(XYZZY)
    ASTR_DATA       *pStr = OBJ_NIL;
#endif
    //int             iRc;
   
    fprintf(stderr, "Performing: %s\n", pTestName);

    pObj1 = ValueArray_New( );
    TINYTEST_FALSE( (OBJ_NIL == pObj1) );
    if (pObj1) {

        //obj_TraceSet(pObj1, true);       
        fRc = obj_IsKindOf(pObj1, OBJ_IDENT_VALUEARRAY);
        TINYTEST_TRUE( (fRc) );
        
        // Test assign.
        pObj2 = ValueArray_New();
        TINYTEST_FALSE( (OBJ_NIL == pObj2) );
        eRc = ValueArray_Assign(pObj1, pObj2);
        TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );

        fRc = obj_IsKindOf(pObj2, OBJ_IDENT_VALUEARRAY);
        TINYTEST_TRUE( (fRc) );
        //iRc = ValueArray_Compare(pObj1, pObj2);
        //TINYTEST_TRUE( (0 == iRc) );
        //TODO: Add More tests here!

        obj_Release(pObj2);
        pObj2 = OBJ_NIL;

        // Test copy.
        pObj2 = ValueArray_Copy(pObj1);
        TINYTEST_FALSE( (OBJ_NIL == pObj2) );

        fRc = obj_IsKindOf(pObj2, OBJ_IDENT_VALUEARRAY);
        TINYTEST_TRUE( (fRc) );
        //iRc = ValueArray_Compare(pObj1, pObj2);
        //TINYTEST_TRUE( (0 == iRc) );
        //TODO: Add More tests here!

        obj_Release(pObj2);
        pObj2 = OBJ_NIL;

        // Test json support.
#if defined(VALUEARRAY_JSON_SUPPORT) && defined(XYZZY)
        pStr = ValueArray_ToJson(pObj1);
        TINYTEST_FALSE( (OBJ_NIL == pStr) );
        fprintf(stderr, "JSON: %s\n", AStr_getData(pStr));
        pObj2 = ValueArray_NewFromJsonString(pStr);
        TINYTEST_FALSE( (OBJ_NIL == pObj2) );
        fRc = obj_IsKindOf(pObj2, OBJ_IDENT_VALUEARRAY);
        TINYTEST_TRUE( (fRc) );
        obj_Release(pStr);
        pStr = OBJ_NIL;
        //iRc = ValueArray_Compare(pObj1, pObj2);
        //TINYTEST_TRUE( (0 == iRc) );

        obj_Release(pObj2);
        pObj2 = OBJ_NIL;
#endif

        obj_Release(pObj1);
        pObj1 = OBJ_NIL;
    }

    fprintf(stderr, "...%s completed.\n\n\n", pTestName);
    return 1;
}



int             test_ValueArray_Test01 (
    const
    char            *pTestName
)
{
    ERESULT         eRc = ERESULT_SUCCESS;
    VALUEARRAY_DATA *pObj = OBJ_NIL;
    VALUE_DATA      *pVal = OBJ_NIL;
    bool            fRc;
    int             i;
    int             iMax;
    uint32_t        idx;

    fprintf(stderr, "Performing: %s\n", pTestName);

    pObj = ValueArray_New( );
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    if (pObj) {

        //obj_TraceSet(pObj, true);       
        fRc = obj_IsKindOf(pObj, OBJ_IDENT_VALUEARRAY);
        TINYTEST_TRUE( (fRc) );
        //TINYTEST_TRUE( (ERESULT_OK(eRc)) );

        for (i=0; i<10; i++) {
            pVal = Value_NewI32(i+1);
            TINYTEST_FALSE( (OBJ_NIL == pVal) );
            eRc = ValueArray_AppendValue(pObj, pVal, &idx);
            TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );
            TINYTEST_TRUE( ((i+1) == idx) );
            obj_Release(pVal);
            pVal = OBJ_NIL;

        }

        iMax = ValueArray_getSize(pObj);
        TINYTEST_TRUE( (10 == iMax) );
        for (i=0; i<10; i++) {
            pVal = ValueArray_Get(pObj, i+1);
            TINYTEST_FALSE( (OBJ_NIL == pVal) );
            idx = Value_getI32(pVal);
            TINYTEST_TRUE( ((i+1) == idx) );
            //obj_Release(pVal);
            pVal = OBJ_NIL;

        }

        {
            ASTR_DATA       *pStr = ValueArray_ToDebugString(pObj, 4);
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




TINYTEST_START_SUITE(test_ValueArray);
    TINYTEST_ADD_TEST(test_ValueArray_Test01,setUp,tearDown);
    //TINYTEST_ADD_TEST(test_ValueArray_Copy01,setUp,tearDown);
    TINYTEST_ADD_TEST(test_ValueArray_OpenClose,setUp,tearDown);
TINYTEST_END_SUITE();

TINYTEST_MAIN_SINGLE_SUITE(test_ValueArray);





