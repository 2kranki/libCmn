// vi:nu:et:sts=4 ts=4 sw=4
/*
 *	Generated 04/25/2020 18:28:59
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
#include    <SqlCol_internal.h>
#include    <SrcErrors.h>
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






int             test_SqlCol_OpenClose (
    const
    char            *pTestName
)
{
    ERESULT         eRc = ERESULT_SUCCESS;
    SQLCOL_DATA	    *pObj = OBJ_NIL;
    bool            fRc;
   
    fprintf(stderr, "Performing: %s\n", pTestName);

    pObj = SqlCol_Alloc( );
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    pObj = SqlCol_Init( pObj );
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    if (pObj) {

        //obj_TraceSet(pObj, true);       
        fRc = obj_IsKindOf(pObj, OBJ_IDENT_SQLCOL);
        TINYTEST_TRUE( (fRc) );
        
        // Test something.
        TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );

        obj_Release(pObj);
        pObj = OBJ_NIL;
    }

    fprintf(stderr, "...%s completed.\n\n\n", pTestName);
    return 1;
}



int             test_SqlCol_Copy01 (
    const
    char            *pTestName
)
{
    ERESULT         eRc = ERESULT_SUCCESS;
    int             iRc;
    SQLCOL_DATA	    *pObj1 = OBJ_NIL;
    SQLCOL_DATA	    *pObj2 = OBJ_NIL;
    bool            fRc;
    ASTR_DATA	    *pStr = OBJ_NIL;
    SQLCOL_STRUCT   ex1 = {
        "ex_name",
        "Example Name",
        SQLCOL_TYPE_DECIMAL,
        0,                  // Key Sequence
        2,                  // Decimal Places
        5,                  // Column Sequence
        9,                  // Length
        9,                  // Min Length
        0,                  // Flags
        "0.00",             // Default Value
        NULL                // Check Expression
    };

    fprintf(stderr, "Performing: %s\n", pTestName);

    pObj1 = SqlCol_NewFromStruct(&ex1);
    TINYTEST_FALSE( (OBJ_NIL == pObj1) );
    if (pObj1) {

        //obj_TraceSet(pObj1, true);       
        fRc = obj_IsKindOf(pObj1, OBJ_IDENT_SQLCOL);
        TINYTEST_TRUE( (fRc) );
        // Verify new object.
        pStr = SqlCol_getName(pObj1);
        TINYTEST_FALSE( (OBJ_NIL == pStr) );
        iRc = AStr_CompareA(pStr, "ex_name");
        TINYTEST_TRUE( (0 == iRc) );
        pStr = SqlCol_getDesc(pObj1);
        TINYTEST_FALSE( (OBJ_NIL == pStr) );
        iRc = AStr_CompareA(pStr, "Example Name");
        TINYTEST_TRUE( (0 == iRc) );
        pStr = SqlCol_getDefVal(pObj1);
        TINYTEST_FALSE( (OBJ_NIL == pStr) );
        iRc = AStr_CompareA(pStr, "0.00");
        TINYTEST_TRUE( (0 == iRc) );
        pStr = SqlCol_getCheckExpr(pObj1);
        TINYTEST_TRUE( (OBJ_NIL == pStr) );
        TINYTEST_TRUE( (SQLCOL_TYPE_DECIMAL == SqlCol_getType(pObj1)) );
        TINYTEST_TRUE( (0 == SqlCol_getKeySeq(pObj1)) );
        TINYTEST_TRUE( (2 == SqlCol_getDecimalPlaces(pObj1)) );
        TINYTEST_TRUE( (5 == SqlCol_getColSeq(pObj1)) );
        TINYTEST_TRUE( (9 == SqlCol_getLength(pObj1)) );
        TINYTEST_TRUE( (9 == SqlCol_getLengthMin(pObj1)) );
        TINYTEST_TRUE( (0 == SqlCol_getFlags(pObj1)) );

        // Test assign.
        pObj2 = SqlCol_New();
        TINYTEST_FALSE( (OBJ_NIL == pObj2) );
        eRc = SqlCol_Assign(pObj1, pObj2);
        TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );

        fRc = obj_IsKindOf(pObj2, OBJ_IDENT_SQLCOL);
        TINYTEST_TRUE( (fRc) );
        // Verify new object.
        pStr = SqlCol_getName(pObj2);
        TINYTEST_FALSE( (OBJ_NIL == pStr) );
        iRc = AStr_CompareA(pStr, "ex_name");
        TINYTEST_TRUE( (0 == iRc) );
        pStr = SqlCol_getDesc(pObj2);
        TINYTEST_FALSE( (OBJ_NIL == pStr) );
        iRc = AStr_CompareA(pStr, "Example Name");
        TINYTEST_TRUE( (0 == iRc) );
        pStr = SqlCol_getDefVal(pObj2);
        TINYTEST_FALSE( (OBJ_NIL == pStr) );
        iRc = AStr_CompareA(pStr, "0.00");
        TINYTEST_TRUE( (0 == iRc) );
        pStr = SqlCol_getCheckExpr(pObj2);
        TINYTEST_TRUE( (OBJ_NIL == pStr) );
        TINYTEST_TRUE( (SQLCOL_TYPE_DECIMAL == SqlCol_getType(pObj2)) );
        TINYTEST_TRUE( (0 == SqlCol_getKeySeq(pObj2)) );
        TINYTEST_TRUE( (2 == SqlCol_getDecimalPlaces(pObj2)) );
        TINYTEST_TRUE( (5 == SqlCol_getColSeq(pObj2)) );
        TINYTEST_TRUE( (9 == SqlCol_getLength(pObj2)) );
        TINYTEST_TRUE( (9 == SqlCol_getLengthMin(pObj2)) );
        TINYTEST_TRUE( (0 == SqlCol_getFlags(pObj2)) );

        obj_Release(pObj2);
        pObj2 = OBJ_NIL;

        // Test copy.
        pObj2 = SqlCol_Copy(pObj1);
        TINYTEST_FALSE( (OBJ_NIL == pObj2) );

        fRc = obj_IsKindOf(pObj2, OBJ_IDENT_SQLCOL);
        TINYTEST_TRUE( (fRc) );
        // Verify new object.
        pStr = SqlCol_getName(pObj2);
        TINYTEST_FALSE( (OBJ_NIL == pStr) );
        iRc = AStr_CompareA(pStr, "ex_name");
        TINYTEST_TRUE( (0 == iRc) );
        pStr = SqlCol_getDesc(pObj2);
        TINYTEST_FALSE( (OBJ_NIL == pStr) );
        iRc = AStr_CompareA(pStr, "Example Name");
        TINYTEST_TRUE( (0 == iRc) );
        pStr = SqlCol_getDefVal(pObj2);
        TINYTEST_FALSE( (OBJ_NIL == pStr) );
        iRc = AStr_CompareA(pStr, "0.00");
        TINYTEST_TRUE( (0 == iRc) );
        pStr = SqlCol_getCheckExpr(pObj2);
        TINYTEST_TRUE( (OBJ_NIL == pStr) );
        TINYTEST_TRUE( (SQLCOL_TYPE_DECIMAL == SqlCol_getType(pObj2)) );
        TINYTEST_TRUE( (0 == SqlCol_getKeySeq(pObj2)) );
        TINYTEST_TRUE( (2 == SqlCol_getDecimalPlaces(pObj2)) );
        TINYTEST_TRUE( (5 == SqlCol_getColSeq(pObj2)) );
        TINYTEST_TRUE( (9 == SqlCol_getLength(pObj2)) );
        TINYTEST_TRUE( (9 == SqlCol_getLengthMin(pObj2)) );
        TINYTEST_TRUE( (0 == SqlCol_getFlags(pObj2)) );

        obj_Release(pObj2);
        pObj2 = OBJ_NIL;

        // Test json support.
        pStr = SqlCol_ToJson(pObj1);
        TINYTEST_FALSE( (OBJ_NIL == pStr) );
        fprintf(stderr, "JSON: %s\n", AStr_getData(pStr));
        pObj2 = SqlCol_NewFromJsonString(pStr);
        TINYTEST_FALSE( (OBJ_NIL == pObj2) );
        fRc = obj_IsKindOf(pObj2, OBJ_IDENT_SQLCOL);
        TINYTEST_TRUE( (fRc) );
        obj_Release(pStr);
        pStr = OBJ_NIL;
        // Verify new object.
        pStr = SqlCol_getName(pObj2);
        TINYTEST_FALSE( (OBJ_NIL == pStr) );
        iRc = AStr_CompareA(pStr, "ex_name");
        TINYTEST_TRUE( (0 == iRc) );
        pStr = SqlCol_getDesc(pObj2);
        TINYTEST_FALSE( (OBJ_NIL == pStr) );
        iRc = AStr_CompareA(pStr, "Example Name");
        TINYTEST_TRUE( (0 == iRc) );
        pStr = SqlCol_getDefVal(pObj2);
        TINYTEST_FALSE( (OBJ_NIL == pStr) );
        iRc = AStr_CompareA(pStr, "0.00");
        TINYTEST_TRUE( (0 == iRc) );
        pStr = SqlCol_getCheckExpr(pObj2);
        TINYTEST_TRUE( (OBJ_NIL == pStr) );
        TINYTEST_TRUE( (SQLCOL_TYPE_DECIMAL == SqlCol_getType(pObj2)) );
        TINYTEST_TRUE( (0 == SqlCol_getKeySeq(pObj2)) );
        TINYTEST_TRUE( (2 == SqlCol_getDecimalPlaces(pObj2)) );
        TINYTEST_TRUE( (5 == SqlCol_getColSeq(pObj2)) );
        TINYTEST_TRUE( (9 == SqlCol_getLength(pObj2)) );
        TINYTEST_TRUE( (9 == SqlCol_getLengthMin(pObj2)) );
        TINYTEST_TRUE( (0 == SqlCol_getFlags(pObj2)) );

        obj_Release(pObj2);
        pObj2 = OBJ_NIL;

        obj_Release(pObj1);
        pObj1 = OBJ_NIL;
    }

    fprintf(stderr, "...%s completed.\n\n\n", pTestName);
    return 1;
}



int             test_SqlCol_Test01 (
    const
    char            *pTestName
)
{
    //ERESULT         eRc = ERESULT_SUCCESS;
    SQLCOL_DATA	    *pObj = OBJ_NIL;
    bool            fRc;
   
    fprintf(stderr, "Performing: %s\n", pTestName);

    pObj = SqlCol_New( );
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    if (pObj) {

        //obj_TraceSet(pObj, true);       
        fRc = obj_IsKindOf(pObj, OBJ_IDENT_SQLCOL);
        TINYTEST_TRUE( (fRc) );
        //TINYTEST_TRUE( (ERESULT_OK(eRc)) );
        
        {
            ASTR_DATA       *pStr = SqlCol_ToDebugString(pObj, 0);
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




TINYTEST_START_SUITE(test_SqlCol);
    TINYTEST_ADD_TEST(test_SqlCol_Test01,setUp,tearDown);
    TINYTEST_ADD_TEST(test_SqlCol_Copy01,setUp,tearDown);
    TINYTEST_ADD_TEST(test_SqlCol_OpenClose,setUp,tearDown);
TINYTEST_END_SUITE();

TINYTEST_MAIN_SINGLE_SUITE(test_SqlCol);





