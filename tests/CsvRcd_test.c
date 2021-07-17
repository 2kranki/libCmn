// vi:nu:et:sts=4 ts=4 sw=4
/*
 *  Generated 07/16/2021 23:40:28
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
#include    <CsvRcd_internal.h>
#include    <JsonIn.h>
#ifdef  CSVRCD_JSON_SUPPORT
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

#ifdef  CSVRCD_JSON_SUPPORT
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






int             test_CsvRcd_OpenClose (
    const
    char            *pTestName
)
{
    ERESULT         eRc = ERESULT_SUCCESS;
    CSVRCD_DATA       *pObj = OBJ_NIL;
    bool            fRc;
   
    fprintf(stderr, "Performing: %s\n", pTestName);

    pObj = CsvRcd_Alloc( );
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    pObj = CsvRcd_Init( pObj );
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    if (pObj) {

        //obj_TraceSet(pObj, true);       
        fRc = obj_IsKindOf(pObj, OBJ_IDENT_CSVRCD);
        TINYTEST_TRUE( (fRc) );
        
        // Test something.
        TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );

        obj_Release(pObj);
        pObj = OBJ_NIL;
    }

    fprintf(stderr, "...%s completed.\n\n\n", pTestName);
    return 1;
}



int             test_CsvRcd_Copy01 (
    const
    char            *pTestName
)
{
    ERESULT         eRc = ERESULT_SUCCESS;
    CSVRCD_DATA       *pObj1 = OBJ_NIL;
    CSVRCD_DATA       *pObj2 = OBJ_NIL;
    bool            fRc;
#if defined(CSVRCD_JSON_SUPPORT) && defined(XYZZY)
    ASTR_DATA       *pStr = OBJ_NIL;
#endif
    //int             iRc;
   
    fprintf(stderr, "Performing: %s\n", pTestName);

    pObj1 = CsvRcd_New( );
    TINYTEST_FALSE( (OBJ_NIL == pObj1) );
    if (pObj1) {

        //obj_TraceSet(pObj1, true);       
        fRc = obj_IsKindOf(pObj1, OBJ_IDENT_CSVRCD);
        TINYTEST_TRUE( (fRc) );
        
        // Test assign.
        pObj2 = CsvRcd_New();
        TINYTEST_FALSE( (OBJ_NIL == pObj2) );
        eRc = CsvRcd_Assign(pObj1, pObj2);
        TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );

        fRc = obj_IsKindOf(pObj2, OBJ_IDENT_CSVRCD);
        TINYTEST_TRUE( (fRc) );
        //iRc = CsvRcd_Compare(pObj1, pObj2);
        //TINYTEST_TRUE( (0 == iRc) );
        //TODO: Add More tests here!

        obj_Release(pObj2);
        pObj2 = OBJ_NIL;

        // Test copy.
        pObj2 = CsvRcd_Copy(pObj1);
        TINYTEST_FALSE( (OBJ_NIL == pObj2) );

        fRc = obj_IsKindOf(pObj2, OBJ_IDENT_CSVRCD);
        TINYTEST_TRUE( (fRc) );
        //iRc = CsvRcd_Compare(pObj1, pObj2);
        //TINYTEST_TRUE( (0 == iRc) );
        //TODO: Add More tests here!

        obj_Release(pObj2);
        pObj2 = OBJ_NIL;

        // Test json support.
#if defined(CSVRCD_JSON_SUPPORT) && defined(XYZZY)
        pStr = CsvRcd_ToJson(pObj1);
        TINYTEST_FALSE( (OBJ_NIL == pStr) );
        fprintf(stderr, "JSON: %s\n", AStr_getData(pStr));
        pObj2 = CsvRcd_NewFromJsonString(pStr);
        TINYTEST_FALSE( (OBJ_NIL == pObj2) );
        fRc = obj_IsKindOf(pObj2, OBJ_IDENT_CSVRCD);
        TINYTEST_TRUE( (fRc) );
        obj_Release(pStr);
        pStr = OBJ_NIL;
        //iRc = CsvRcd_Compare(pObj1, pObj2);
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



int             test_CsvRcd_Test01 (
    const
    char            *pTestName
)
{
    //ERESULT         eRc = ERESULT_SUCCESS;
    CSVRCD_DATA     *pObj = OBJ_NIL;
    bool            fRc;
    W32STR_DATA     *pStr = OBJ_NIL;
    W32ARRAY_DATA   *pArray = OBJ_NIL;
    //uint32_t        i;
    uint32_t        iMax;
    int             iRc;
    const
    char            *pDataA = "  a,   10  ,,   \"def, ghi\"  \n";

    fprintf(stderr, "Performing: %s\n", pTestName);

    pStr = W32Str_NewA(pDataA);
    TINYTEST_FALSE( (OBJ_NIL == pStr) );
    fprintf(stderr, "\tParsing: %s\n", pDataA);

    pObj = CsvRcd_New( );
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    if (pObj) {

        obj_TraceSet(pObj, true);
        fRc = obj_IsKindOf(pObj, OBJ_IDENT_CSVRCD);
        TINYTEST_TRUE( (fRc) );
        pArray = CsvRcd_Parse(pObj, pStr);
        TINYTEST_FALSE( (OBJ_NIL == pArray) );
        obj_Release(pStr);
        pStr = OBJ_NIL;

        {
            ASTR_DATA       *pStr = W32Array_ToDebugString(pArray, 4);
            if (pStr) {
                fprintf(stderr, "Returned Array: %s\n", AStr_getData(pStr));
                obj_Release(pStr);
                pStr = OBJ_NIL;
            }
        }
        iMax = W32Array_getSize(pArray);
        TINYTEST_TRUE( (4 == iMax) );
        pStr = W32Array_Get(pArray, 1);
        TINYTEST_FALSE( (OBJ_NIL == pStr) );
        iRc = W32Str_getSize(pStr);
        TINYTEST_TRUE( (1 == iRc) );
        iRc = W32Str_CompareA(pStr, "a");
        TINYTEST_TRUE( (0 == iRc) );
        pStr = W32Array_Get(pArray, 2);
        TINYTEST_FALSE( (OBJ_NIL == pStr) );
        iRc = W32Str_getSize(pStr);
        TINYTEST_TRUE( (2 == iRc) );
        iRc = W32Str_CompareA(pStr, "10");
        TINYTEST_TRUE( (0 == iRc) );
        pStr = W32Array_Get(pArray, 3);
        TINYTEST_FALSE( (OBJ_NIL == pStr) );
        iRc = W32Str_getSize(pStr);
        TINYTEST_TRUE( (0 == iRc) );
        pStr = W32Array_Get(pArray, 4);
        TINYTEST_FALSE( (OBJ_NIL == pStr) );
        iRc = W32Str_getSize(pStr);
        TINYTEST_TRUE( (8 == iRc) );
        iRc = W32Str_CompareA(pStr, "def, ghi");
        TINYTEST_TRUE( (0 == iRc) );

        obj_Release(pArray);
        pArray = OBJ_NIL;

        obj_Release(pObj);
        pObj = OBJ_NIL;
    }

    fprintf(stderr, "...%s completed.\n\n\n", pTestName);
    return 1;
}



int             test_CsvRcd_Test02 (
    const
    char            *pTestName
)
{
    //ERESULT         eRc = ERESULT_SUCCESS;
    CSVRCD_DATA     *pObj = OBJ_NIL;
    bool            fRc;
    W32STR_DATA     *pStr = OBJ_NIL;
    W32ARRAY_DATA   *pArray = OBJ_NIL;
    //uint32_t        i;
    uint32_t        iMax;
    int             iRc;
    const
    char            *pDataA =
            "7/6/21,10:00:11,TRD,"
            "BOT +3 BUTTERFLY SPX 100 (Weeklys) 9 JUL 21 4345/4365/4385 CALL @4.15,"
            "-7.80,\"-1,245.00\",\"19,233.97\"\n";

    fprintf(stderr, "Performing: %s\n", pTestName);

    pStr = W32Str_NewA(pDataA);
    TINYTEST_FALSE( (OBJ_NIL == pStr) );
    fprintf(stderr, "\tParsing: %s\n", pDataA);

    pObj = CsvRcd_New( );
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    if (pObj) {

        obj_TraceSet(pObj, true);
        fRc = obj_IsKindOf(pObj, OBJ_IDENT_CSVRCD);
        TINYTEST_TRUE( (fRc) );
        pArray = CsvRcd_Parse(pObj, pStr);
        TINYTEST_FALSE( (OBJ_NIL == pArray) );
        obj_Release(pStr);
        pStr = OBJ_NIL;

        {
            ASTR_DATA       *pStr = W32Array_ToDebugString(pArray, 4);
            if (pStr) {
                fprintf(stderr, "Returned Array: %s\n", AStr_getData(pStr));
                obj_Release(pStr);
                pStr = OBJ_NIL;
            }
        }
        iMax = W32Array_getSize(pArray);
        TINYTEST_TRUE( (7 == iMax) );
        pStr = W32Array_Get(pArray, 1);
        TINYTEST_FALSE( (OBJ_NIL == pStr) );
        iRc = W32Str_getSize(pStr);
        TINYTEST_TRUE( (6 == iRc) );
        iRc = W32Str_CompareA(pStr, "7/6/21");
        TINYTEST_TRUE( (0 == iRc) );
        pStr = W32Array_Get(pArray, 2);
        TINYTEST_FALSE( (OBJ_NIL == pStr) );
        iRc = W32Str_getSize(pStr);
        TINYTEST_TRUE( (8 == iRc) );
        iRc = W32Str_CompareA(pStr, "10:00:11");
        TINYTEST_TRUE( (0 == iRc) );
        pStr = W32Array_Get(pArray, 3);
        TINYTEST_FALSE( (OBJ_NIL == pStr) );
        iRc = W32Str_getSize(pStr);
        TINYTEST_TRUE( (3 == iRc) );
        iRc = W32Str_CompareA(pStr, "TRD");
        TINYTEST_TRUE( (0 == iRc) );
        pStr = W32Array_Get(pArray, 4);
        TINYTEST_FALSE( (OBJ_NIL == pStr) );
        iRc = W32Str_getSize(pStr);
        TINYTEST_TRUE( (69 == iRc) );
        iRc = W32Str_CompareA(pStr, "BOT +3 BUTTERFLY SPX 100 (Weeklys) 9 JUL 21 4345/4365/4385 CALL @4.15");
        TINYTEST_TRUE( (0 == iRc) );
        pStr = W32Array_Get(pArray, 5);
        TINYTEST_FALSE( (OBJ_NIL == pStr) );
        iRc = W32Str_getSize(pStr);
        TINYTEST_TRUE( (5 == iRc) );
        iRc = W32Str_CompareA(pStr, "-7.80");
        TINYTEST_TRUE( (0 == iRc) );
        pStr = W32Array_Get(pArray, 6);
        TINYTEST_FALSE( (OBJ_NIL == pStr) );
        iRc = W32Str_getSize(pStr);
        TINYTEST_TRUE( (9 == iRc) );
        iRc = W32Str_CompareA(pStr, "-1,245.00");
        TINYTEST_TRUE( (0 == iRc) );
        pStr = W32Array_Get(pArray, 7);
        TINYTEST_FALSE( (OBJ_NIL == pStr) );
        iRc = W32Str_getSize(pStr);
        TINYTEST_TRUE( (9 == iRc) );
        iRc = W32Str_CompareA(pStr, "19,233.97");
        TINYTEST_TRUE( (0 == iRc) );

        obj_Release(pArray);
        pArray = OBJ_NIL;

        obj_Release(pObj);
        pObj = OBJ_NIL;
    }

    fprintf(stderr, "...%s completed.\n\n\n", pTestName);
    return 1;
}




TINYTEST_START_SUITE(test_CsvRcd);
    TINYTEST_ADD_TEST(test_CsvRcd_Test02,setUp,tearDown);
    TINYTEST_ADD_TEST(test_CsvRcd_Test01,setUp,tearDown);
    //TINYTEST_ADD_TEST(test_CsvRcd_Copy01,setUp,tearDown);
    TINYTEST_ADD_TEST(test_CsvRcd_OpenClose,setUp,tearDown);
TINYTEST_END_SUITE();

TINYTEST_MAIN_SINGLE_SUITE(test_CsvRcd);





