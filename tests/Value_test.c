// vi:nu:et:sts=4 ts=4 sw=4
/*
 *	Generated 12/31/2019 15:27:11
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
#include    <Value_internal.h>



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






int             test_Value_OpenClose(
    const
    char            *pTestName
)
{
    ERESULT         eRc = ERESULT_SUCCESS;
    VALUE_DATA	    *pObj = OBJ_NIL;
    bool            fRc;
   
    fprintf(stderr, "Performing: %s\n", pTestName);

    pObj = Value_Alloc( );
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    pObj = Value_Init( pObj );
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    if (pObj) {

        //obj_TraceSet(pObj, true);       
        fRc = obj_IsKindOf(pObj, OBJ_IDENT_VALUE);
        TINYTEST_TRUE( (fRc) );
        
        // Test something.
        TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );

        obj_Release(pObj);
        pObj = OBJ_NIL;
    }

    fprintf(stderr, "...%s completed.\n\n\n", pTestName);
    return 1;
}



int             test_Value_Test01(
    const
    char            *pTestName
)
{
    //ERESULT         eRc = ERESULT_SUCCESS;
    VALUE_DATA      *pObj = OBJ_NIL;

    fprintf(stderr, "Performing: %s\n", pTestName);

    pObj = Value_NewI8(24);
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    if (pObj) {
        TINYTEST_TRUE( (pObj->type == VALUE_TYPE_INT8) );
        TINYTEST_TRUE( (pObj->value.i8 == 24) );
        obj_Release(pObj);
        pObj = OBJ_NIL;
    }

    pObj = Value_NewI16(257);
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    if (pObj) {
        TINYTEST_TRUE( (pObj->type == VALUE_TYPE_INT16) );
        TINYTEST_TRUE( (pObj->value.i16 == 257) );
        obj_Release(pObj);
        pObj = OBJ_NIL;
    }

    pObj = Value_NewI32(70000);
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    if (pObj) {
        TINYTEST_TRUE( (pObj->type == VALUE_TYPE_INT32) );
        TINYTEST_TRUE( (pObj->value.i32 == 70000) );
        obj_Release(pObj);
        pObj = OBJ_NIL;
    }

    pObj = Value_NewI64(6666666666666);
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    if (pObj) {
        TINYTEST_TRUE( (pObj->type == VALUE_TYPE_INT64) );
        TINYTEST_TRUE( (pObj->value.i64 == 6666666666666) );
        obj_Release(pObj);
        pObj = OBJ_NIL;
    }

    pObj = Value_NewU8(24);
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    if (pObj) {
        TINYTEST_TRUE( (pObj->type == VALUE_TYPE_UINT8) );
        TINYTEST_TRUE( (pObj->value.u8 == 24) );
        obj_Release(pObj);
        pObj = OBJ_NIL;
    }

    pObj = Value_NewU16(257);
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    if (pObj) {
        TINYTEST_TRUE( (pObj->type == VALUE_TYPE_UINT16) );
        TINYTEST_TRUE( (pObj->value.u16 == 257) );
        obj_Release(pObj);
        pObj = OBJ_NIL;
    }

    pObj = Value_NewU32(70000);
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    if (pObj) {
        TINYTEST_TRUE( (pObj->type == VALUE_TYPE_UINT32) );
        TINYTEST_TRUE( (pObj->value.u32 == 70000) );
        obj_Release(pObj);
        pObj = OBJ_NIL;
    }

    pObj = Value_NewU64(6666666666666);
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    if (pObj) {
        TINYTEST_TRUE( (pObj->type == VALUE_TYPE_UINT64) );
        TINYTEST_TRUE( (pObj->value.u64 == 6666666666666) );
        obj_Release(pObj);
        pObj = OBJ_NIL;
    }

    fprintf(stderr, "...%s completed.\n\n\n", pTestName);
    return 1;
}



int             test_Value_Float01(
    const
    char            *pTestName
)
{
    //ERESULT         eRc = ERESULT_SUCCESS;
    VALUE_DATA      *pObj = OBJ_NIL;
    VALUE_DATA      *pObj2 = OBJ_NIL;
    ASTR_DATA       *pStr = OBJ_NIL;

    fprintf(stderr, "Performing: %s\n", pTestName);

    pObj = Value_NewDouble(3.1416);
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    if (pObj) {
        TINYTEST_TRUE( (pObj->type == VALUE_TYPE_DOUBLE) );
        TINYTEST_TRUE( (pObj->value.flt == 3.1416) );

        pStr = Value_ToJson(pObj);
        TINYTEST_FALSE( (OBJ_NIL == pStr) );
        fprintf(stderr, "Json: %s\n", AStr_getData(pStr));
        pObj2 = Value_NewFromJsonString(pStr);
        TINYTEST_TRUE( (pObj2->type == VALUE_TYPE_DOUBLE) );
        TINYTEST_TRUE( (pObj2->value.flt == 3.1416) );
        obj_Release(pObj2);
        pObj2 = OBJ_NIL;
        obj_Release(pStr);
        pStr = OBJ_NIL;

        obj_Release(pObj);
        pObj = OBJ_NIL;
    }

    fprintf(stderr, "...%s completed.\n\n\n", pTestName);
    return 1;
}




TINYTEST_START_SUITE(test_Value);
    TINYTEST_ADD_TEST(test_Value_Float01,setUp,tearDown);
    TINYTEST_ADD_TEST(test_Value_Test01,setUp,tearDown);
    TINYTEST_ADD_TEST(test_Value_OpenClose,setUp,tearDown);
TINYTEST_END_SUITE();

TINYTEST_MAIN_SINGLE_SUITE(test_Value);





