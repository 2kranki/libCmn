// vi:nu:et:sts=4 ts=4 sw=4
/*
 *  Generated 04/14/2021 10:28:06
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
#include    <SqlRow_internal.h>
#include    <JsonIn.h>
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






int             test_SqlRow_OpenClose (
    const
    char            *pTestName
)
{
    ERESULT         eRc = ERESULT_SUCCESS;
    SQLROW_DATA       *pObj = OBJ_NIL;
    bool            fRc;
   
    fprintf(stderr, "Performing: %s\n", pTestName);

    pObj = SqlRow_Alloc( );
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    pObj = SqlRow_Init( pObj );
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    if (pObj) {

        //obj_TraceSet(pObj, true);       
        fRc = obj_IsKindOf(pObj, OBJ_IDENT_SQLROW);
        TINYTEST_TRUE( (fRc) );
        
        // Test something.
        TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );

        obj_Release(pObj);
        pObj = OBJ_NIL;
    }

    fprintf(stderr, "...%s completed.\n\n\n", pTestName);
    return 1;
}



int             test_SqlRow_Copy01 (
    const
    char            *pTestName
)
{
    ERESULT         eRc = ERESULT_SUCCESS;
    SQLROW_DATA     *pObj1 = OBJ_NIL;
    SQLROW_DATA     *pObj2 = OBJ_NIL;
    bool            fRc;
    ASTR_DATA       *pStr = OBJ_NIL;
    SQLCOL_STRUCT   ex1 = {
        "dec1",
        "Decimal 1",
        "table",            // Table Name
        "database",         // Database Name
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
    SQLCOL_DATA     *pCol1 = OBJ_NIL;
    int             iRc;

    fprintf(stderr, "Performing: %s\n", pTestName);

    pCol1 = SqlCol_NewFromStruct(&ex1);
    TINYTEST_FALSE( (OBJ_NIL == pCol1) );
    if (pCol1) {
        // Verify new object.
        pStr = SqlCol_getName(pCol1);
        TINYTEST_FALSE( (OBJ_NIL == pStr) );
        iRc = AStr_CompareA(pStr, "dec1");
        TINYTEST_TRUE( (0 == iRc) );
        pStr = SqlCol_getDatabaseName(pCol1);
        TINYTEST_FALSE( (OBJ_NIL == pStr) );
        iRc = AStr_CompareA(pStr, "database");
        TINYTEST_TRUE( (0 == iRc) );
        pStr = SqlCol_getDesc(pCol1);
        TINYTEST_FALSE( (OBJ_NIL == pStr) );
        iRc = AStr_CompareA(pStr, "Decimal 1");
        TINYTEST_TRUE( (0 == iRc) );
        pStr = SqlCol_getDefVal(pCol1);
        TINYTEST_FALSE( (OBJ_NIL == pStr) );
        iRc = AStr_CompareA(pStr, "0.00");
        TINYTEST_TRUE( (0 == iRc) );
        pStr = SqlCol_getCheckExpr(pCol1);
        TINYTEST_TRUE( (OBJ_NIL == pStr) );
        pStr = SqlCol_getTableName(pCol1);
        TINYTEST_FALSE( (OBJ_NIL == pStr) );
        iRc = AStr_CompareA(pStr, "table");
        TINYTEST_TRUE( (0 == iRc) );
        TINYTEST_TRUE( (SQLCOL_TYPE_DECIMAL == SqlCol_getType(pCol1)) );
        TINYTEST_TRUE( (0 == SqlCol_getKeySeq(pCol1)) );
        TINYTEST_TRUE( (2 == SqlCol_getDecimalPlaces(pCol1)) );
        TINYTEST_TRUE( (5 == SqlCol_getColSeq(pCol1)) );
        TINYTEST_TRUE( (9 == SqlCol_getLength(pCol1)) );
        TINYTEST_TRUE( (9 == SqlCol_getLengthMin(pCol1)) );
        TINYTEST_TRUE( (0 == SqlCol_getFlags(pCol1)) );

        pStr = SqlCol_FullName(pCol1);
        TINYTEST_FALSE( (OBJ_NIL == pStr) );
        iRc = AStr_CompareA(pStr, "database.table.dec1");
        TINYTEST_TRUE( (0 == iRc) );
        obj_Release(pStr);
        pStr = OBJ_NIL;
    }

    pObj1 = SqlRow_New( );
    TINYTEST_FALSE( (OBJ_NIL == pObj1) );
    if (pObj1) {

        //obj_TraceSet(pObj1, true);       
        fRc = obj_IsKindOf(pObj1, OBJ_IDENT_SQLROW);
        TINYTEST_TRUE( (fRc) );
        
        // Test assign.
        pObj2 = SqlRow_New();
        TINYTEST_FALSE( (OBJ_NIL == pObj2) );
        eRc = SqlRow_Assign(pObj1, pObj2);
        TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );

        fRc = obj_IsKindOf(pObj2, OBJ_IDENT_SQLROW);
        TINYTEST_TRUE( (fRc) );
        {
            ASTR_DATA       *pStr = SqlRow_ToDebugString(pObj2, 4);
            fprintf(stderr, "1 ASSIGN: %s\n", AStr_getData(pStr));
            obj_Release(pStr);
        }

        obj_Release(pObj2);
        pObj2 = OBJ_NIL;

        // Test copy.
        pObj2 = SqlRow_Copy(pObj1);
        TINYTEST_FALSE( (OBJ_NIL == pObj2) );

        fRc = obj_IsKindOf(pObj2, OBJ_IDENT_SQLROW);
        TINYTEST_TRUE( (fRc) );
        //eRc = SqlRow_Compare(pObj1, pObj2);
        //TINYTEST_TRUE( (ERESULT_SUCCESS_EQUAL == eRc) );
        //TODO: Add More tests here!
        {
            ASTR_DATA       *pStr = SqlRow_ToDebugString(pObj2, 4);
            fprintf(stderr, "2 COPY: %s\n", AStr_getData(pStr));
            obj_Release(pStr);
        }

        obj_Release(pObj2);
        pObj2 = OBJ_NIL;

        // Test json support.
        pStr = SqlRow_ToJson(pObj1);
        TINYTEST_FALSE( (OBJ_NIL == pStr) );
        fprintf(stderr, "JSON: %s\n", AStr_getData(pStr));
        pObj2 = SqlRow_NewFromJsonString(pStr);
        TINYTEST_FALSE( (OBJ_NIL == pObj2) );
        fRc = obj_IsKindOf(pObj2, OBJ_IDENT_SQLROW);
        TINYTEST_TRUE( (fRc) );
        obj_Release(pStr);
        pStr = OBJ_NIL;
        //eRc = SqlRow_Compare(pObj1, pObj2);
        //TINYTEST_TRUE( (ERESULT_SUCCESS_EQUAL == eRc) );
        {
            ASTR_DATA       *pStr = SqlRow_ToDebugString(pObj2, 4);
            fprintf(stderr, "3 JSON: %s\n", AStr_getData(pStr));
            obj_Release(pStr);
        }

        obj_Release(pObj2);
        pObj2 = OBJ_NIL;

        obj_Release(pObj1);
        pObj1 = OBJ_NIL;
    }

    obj_Release(pCol1);
    pCol1 = OBJ_NIL;

    fprintf(stderr, "...%s completed.\n\n\n", pTestName);
    return 1;
}



int             test_SqlRow_Test01 (
    const
    char            *pTestName
)
{
    //ERESULT         eRc = ERESULT_SUCCESS;
    SQLROW_DATA       *pObj = OBJ_NIL;
    bool            fRc;
   
    fprintf(stderr, "Performing: %s\n", pTestName);

    pObj = SqlRow_New( );
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    if (pObj) {

        //obj_TraceSet(pObj, true);       
        fRc = obj_IsKindOf(pObj, OBJ_IDENT_SQLROW);
        TINYTEST_TRUE( (fRc) );
        //TINYTEST_TRUE( (ERESULT_OK(eRc)) );
        
        {
            ASTR_DATA       *pStr = SqlRow_ToDebugString(pObj, 0);
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




TINYTEST_START_SUITE(test_SqlRow);
    TINYTEST_ADD_TEST(test_SqlRow_Test01,setUp,tearDown);
    TINYTEST_ADD_TEST(test_SqlRow_Copy01,setUp,tearDown);
    TINYTEST_ADD_TEST(test_SqlRow_OpenClose,setUp,tearDown);
TINYTEST_END_SUITE();

TINYTEST_MAIN_SINGLE_SUITE(test_SqlRow);





