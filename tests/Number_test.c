// vi:nu:et:sts=4 ts=4 sw=4
/*
 *  Generated 05/23/11 11:24:01
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
#include    <Number_internal.h>
#ifdef  NUMBER_JSON_SUPPORT
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

#ifdef  NUMBER_JSON_SUPPORT
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






int             test_Number_OpenClose (
    const
    char            *pTestName
)
{
    ERESULT         eRc = ERESULT_SUCCESS;
    NUMBER_DATA       *pObj = OBJ_NIL;
    bool            fRc;
   
    fprintf(stderr, "Performing: %s\n", pTestName);

    pObj = Number_Alloc( );
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    pObj = Number_Init( pObj );
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    if (pObj) {

        //obj_TraceSet(pObj, true);       
        fRc = obj_IsKindOf(pObj, OBJ_IDENT_NUMBER);
        TINYTEST_TRUE( (fRc) );
        
        // Test something.
        TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );

        obj_Release(pObj);
        pObj = OBJ_NIL;
    }

    fprintf(stderr, "...%s completed.\n\n\n", pTestName);
    return 1;
}



int             test_Number_Copy01 (
    const
    char            *pTestName
)
{
    ERESULT         eRc = ERESULT_SUCCESS;
    NUMBER_DATA       *pObj1 = OBJ_NIL;
    NUMBER_DATA       *pObj2 = OBJ_NIL;
    bool            fRc;
#if defined(NUMBER_JSON_SUPPORT)
    ASTR_DATA       *pStr = OBJ_NIL;
#endif
   
    fprintf(stderr, "Performing: %s\n", pTestName);

    pObj1 = Number_NewUint64(123);
    TINYTEST_FALSE( (OBJ_NIL == pObj1) );
    if (pObj1) {

        //obj_TraceSet(pObj1, true);       
        fRc = obj_IsKindOf(pObj1, OBJ_IDENT_NUMBER);
        TINYTEST_TRUE( (fRc) );
        TINYTEST_TRUE( (NUMBER_TYPE_UINT64 == pObj1->type) );
        TINYTEST_TRUE( (123 == pObj1->u64) );

        // Test assign.
        pObj2 = Number_New();
        TINYTEST_FALSE( (OBJ_NIL == pObj2) );
        eRc = Number_Assign(pObj1, pObj2);
        TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );

        fRc = obj_IsKindOf(pObj2, OBJ_IDENT_NUMBER);
        TINYTEST_TRUE( (fRc) );
        TINYTEST_TRUE( (NUMBER_TYPE_UINT64 == pObj2->type) );
        TINYTEST_TRUE( (123 == pObj2->u64) );

        obj_Release(pObj2);
        pObj2 = OBJ_NIL;

        // Test copy.
        pObj2 = Number_Copy(pObj1);
        TINYTEST_FALSE( (OBJ_NIL == pObj2) );

        fRc = obj_IsKindOf(pObj2, OBJ_IDENT_NUMBER);
        TINYTEST_TRUE( (fRc) );
        TINYTEST_TRUE( (NUMBER_TYPE_UINT64 == pObj2->type) );
        TINYTEST_TRUE( (123 == pObj2->u64) );

        obj_Release(pObj2);
        pObj2 = OBJ_NIL;

        // Test json support.
#if defined(NUMBER_JSON_SUPPORT)
        pStr = Number_ToJson(pObj1);
        TINYTEST_FALSE( (OBJ_NIL == pStr) );
        fprintf(stderr, "JSON: %s\n", AStr_getData(pStr));
        pObj2 = Number_NewFromJsonString(pStr);
        TINYTEST_FALSE( (OBJ_NIL == pObj2) );
        fRc = obj_IsKindOf(pObj2, OBJ_IDENT_NUMBER);
        TINYTEST_TRUE( (fRc) );
        obj_Release(pStr);
        pStr = OBJ_NIL;
        TINYTEST_TRUE( (NUMBER_TYPE_UINT64 == pObj2->type) );
        TINYTEST_TRUE( (123 == pObj2->u64) );

        obj_Release(pObj2);
        pObj2 = OBJ_NIL;
#endif

        obj_Release(pObj1);
        pObj1 = OBJ_NIL;
    }

    fprintf(stderr, "...%s completed.\n\n\n", pTestName);
    return 1;
}



int             test_Number_Test01 (
    const
    char            *pTestName
)
{
    //ERESULT         eRc = ERESULT_SUCCESS;
    NUMBER_DATA       *pObj = OBJ_NIL;
    bool            fRc;
   
    fprintf(stderr, "Performing: %s\n", pTestName);

    pObj = Number_NewUint16(123);
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    if (pObj) {

        //obj_TraceSet(pObj, true);       
        fRc = obj_IsKindOf(pObj, OBJ_IDENT_NUMBER);
        TINYTEST_TRUE( (fRc) );
        TINYTEST_TRUE( (NUMBER_TYPE_UINT16 == pObj->type) );
        TINYTEST_TRUE( (123 == pObj->u16) );

        {
            ASTR_DATA       *pStr = Number_ToDebugString(pObj, 0);
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



int             test_Number_Test02 (
    const
    char            *pTestName
)
{
    //ERESULT         eRc = ERESULT_SUCCESS;
    NUMBER_DATA       *pObj = OBJ_NIL;
    bool            fRc;

    fprintf(stderr, "Performing: %s\n", pTestName);

    pObj = Number_NewUint32(123);
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    if (pObj) {

        //obj_TraceSet(pObj, true);
        fRc = obj_IsKindOf(pObj, OBJ_IDENT_NUMBER);
        TINYTEST_TRUE( (fRc) );
        TINYTEST_TRUE( (NUMBER_TYPE_UINT32 == pObj->type) );
        TINYTEST_TRUE( (123 == pObj->u32) );

        {
            ASTR_DATA       *pStr = Number_ToDebugString(pObj, 0);
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



int             test_Number_Test03 (
    const
    char            *pTestName
)
{
    //ERESULT         eRc = ERESULT_SUCCESS;
    NUMBER_DATA       *pObj = OBJ_NIL;
    bool            fRc;

    fprintf(stderr, "Performing: %s\n", pTestName);

    pObj = Number_NewInt16(123);
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    if (pObj) {

        //obj_TraceSet(pObj, true);
        fRc = obj_IsKindOf(pObj, OBJ_IDENT_NUMBER);
        TINYTEST_TRUE( (fRc) );
        TINYTEST_TRUE( (NUMBER_TYPE_INT16 == pObj->type) );
        TINYTEST_TRUE( (123 == pObj->i16) );

        {
            ASTR_DATA       *pStr = Number_ToDebugString(pObj, 0);
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



int             test_Number_Test04 (
    const
    char            *pTestName
)
{
    //ERESULT         eRc = ERESULT_SUCCESS;
    NUMBER_DATA       *pObj = OBJ_NIL;
    bool            fRc;

    fprintf(stderr, "Performing: %s\n", pTestName);

    pObj = Number_NewInt32(123);
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    if (pObj) {

        //obj_TraceSet(pObj, true);
        fRc = obj_IsKindOf(pObj, OBJ_IDENT_NUMBER);
        TINYTEST_TRUE( (fRc) );
        TINYTEST_TRUE( (NUMBER_TYPE_INT32 == pObj->type) );
        TINYTEST_TRUE( (123 == pObj->i32) );

        {
            ASTR_DATA       *pStr = Number_ToDebugString(pObj, 0);
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



int             test_Number_Test05 (
    const
    char            *pTestName
)
{
    //ERESULT         eRc = ERESULT_SUCCESS;
    NUMBER_DATA       *pObj = OBJ_NIL;
    bool            fRc;

    fprintf(stderr, "Performing: %s\n", pTestName);

    pObj = Number_NewInt64(123);
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    if (pObj) {

        //obj_TraceSet(pObj, true);
        fRc = obj_IsKindOf(pObj, OBJ_IDENT_NUMBER);
        TINYTEST_TRUE( (fRc) );
        TINYTEST_TRUE( (NUMBER_TYPE_INT64 == pObj->type) );
        TINYTEST_TRUE( (123 == pObj->i64) );

        {
            ASTR_DATA       *pStr = Number_ToDebugString(pObj, 0);
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




TINYTEST_START_SUITE(test_Number);
    TINYTEST_ADD_TEST(test_Number_Test05,setUp,tearDown);
    TINYTEST_ADD_TEST(test_Number_Test04,setUp,tearDown);
    TINYTEST_ADD_TEST(test_Number_Test03,setUp,tearDown);
    TINYTEST_ADD_TEST(test_Number_Test02,setUp,tearDown);
    TINYTEST_ADD_TEST(test_Number_Test01,setUp,tearDown);
    //TINYTEST_ADD_TEST(test_Number_Copy01,setUp,tearDown);
    TINYTEST_ADD_TEST(test_Number_OpenClose,setUp,tearDown);
TINYTEST_END_SUITE();

TINYTEST_MAIN_SINGLE_SUITE(test_Number);





