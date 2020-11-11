// vi:nu:et:sts=4 ts=4 sw=4
/*
 *	Generated 02/18/2020 11:52:42
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
#include    <U16Matrix_internal.h>
#ifdef  U16MATRIX_JSON_SUPPORT
#   include    <SrcErrors.h>
#   include    <szTbl.h>
#endif



uint16_t        valueCheckGet(
    MATRIX_BUILD    *pBuild,
    uint32_t        i,
    uint32_t        j
)
{
    uint32_t        base;
    uint32_t        index;
    uint32_t        highest = pBuild->highest;
    uint16_t        value = 0;

    base = pBuild->pBase[i-1];
    index = base + j - 1;
    if (index >= highest)
        ;
    else {
        if (pBuild->pCheck[index] == i) {
            value = pBuild->pValue[index];
        }
    }

    return value;
}



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

#ifdef  U16MATRIX_JSON_SUPPORT
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






int             test_U16Matrix_OpenClose (
    const
    char            *pTestName
)
{
    ERESULT         eRc = ERESULT_SUCCESS;
    U16MATRIX_DATA	    *pObj = OBJ_NIL;
    bool            fRc;
   
    fprintf(stderr, "Performing: %s\n", pTestName);

    pObj = U16Matrix_Alloc( );
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    pObj = U16Matrix_Init( pObj );
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    if (pObj) {

        //obj_TraceSet(pObj, true);       
        fRc = obj_IsKindOf(pObj, OBJ_IDENT_U16MATRIX);
        TINYTEST_TRUE( (fRc) );
        
        // Test something.
        TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );

        obj_Release(pObj);
        pObj = OBJ_NIL;
    }

    fprintf(stderr, "...%s completed.\n\n\n", pTestName);
    return 1;
}



int             test_U16Matrix_Copy01 (
    const
    char            *pTestName
)
{
    ERESULT         eRc = ERESULT_SUCCESS;
    U16MATRIX_DATA	*pObj1 = OBJ_NIL;
    U16MATRIX_DATA	*pObj2 = OBJ_NIL;
    bool            fRc;
    ASTR_DATA	    *pStr = OBJ_NIL;
    uint32_t        i;
    uint32_t        iMax = 3;
    uint32_t        j;
    uint32_t        jMax = 2;

    fprintf(stderr, "Performing: %s\n", pTestName);

    //                              m      n
    pObj1 = U16Matrix_NewWithSizes(iMax, jMax);
    TINYTEST_FALSE( (OBJ_NIL == pObj1) );
    if (pObj1) {

        //obj_TraceSet(pObj1, true);       
        fRc = obj_IsKindOf(pObj1, OBJ_IDENT_U16MATRIX);
        TINYTEST_TRUE( (fRc) );
        for (i=0; i<iMax; i++) {
            for (j=0; j<jMax; j++) {
                eRc = U16Matrix_Set(pObj1, i+1, j+1, ((i * jMax) + j));
                TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );
            }
        }
        
        // Test assign.
        //                              m      n
        pObj2 = U16Matrix_NewWithSizes(iMax, jMax);
        TINYTEST_FALSE( (OBJ_NIL == pObj2) );
        eRc = U16Matrix_Assign(pObj1, pObj2);
        TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );

        fRc = obj_IsKindOf(pObj2, OBJ_IDENT_U16MATRIX);
        TINYTEST_TRUE( (fRc) );
        eRc = U16Matrix_Compare(pObj1, pObj2);
        TINYTEST_TRUE( (0 == eRc) );

        obj_Release(pObj2);
        pObj2 = OBJ_NIL;

        // Test copy.
        pObj2 = U16Matrix_Copy(pObj1);
        TINYTEST_FALSE( (OBJ_NIL == pObj2) );

        fRc = obj_IsKindOf(pObj2, OBJ_IDENT_U16MATRIX);
        TINYTEST_TRUE( (fRc) );
        eRc = U16Matrix_Compare(pObj1, pObj2);
        TINYTEST_TRUE( (0 == eRc) );

        obj_Release(pObj2);
        pObj2 = OBJ_NIL;

        // Test json support.
        pStr = U16Matrix_ToJson(pObj1);
        TINYTEST_FALSE( (OBJ_NIL == pStr) );
        fprintf(stderr, "JSON: %s\n", AStr_getData(pStr));
        pObj2 = U16Matrix_NewFromJsonString(pStr);
        TINYTEST_FALSE( (OBJ_NIL == pObj2) );
        fRc = obj_IsKindOf(pObj2, OBJ_IDENT_U16MATRIX);
        TINYTEST_TRUE( (fRc) );
        obj_Release(pStr);
        pStr = OBJ_NIL;
        eRc = U16Matrix_Compare(pObj1, pObj2);
        TINYTEST_TRUE( (0 == eRc) );

        obj_Release(pObj2);
        pObj2 = OBJ_NIL;

        obj_Release(pObj1);
        pObj1 = OBJ_NIL;
    }

    fprintf(stderr, "...%s completed.\n\n\n", pTestName);
    return 1;
}



int             test_U16Matrix_Test01 (
    const
    char            *pTestName
)
{
    //ERESULT         eRc = ERESULT_SUCCESS;
    U16MATRIX_DATA	    *pObj = OBJ_NIL;
    bool            fRc;
   
    fprintf(stderr, "Performing: %s\n", pTestName);

    pObj = U16Matrix_New( );
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    if (pObj) {

        //obj_TraceSet(pObj, true);       
        fRc = obj_IsKindOf(pObj, OBJ_IDENT_U16MATRIX);
        TINYTEST_TRUE( (fRc) );
        
        obj_Release(pObj);
        pObj = OBJ_NIL;
    }

    fprintf(stderr, "...%s completed.\n\n\n", pTestName);
    return 1;
}



int         test_U16Matrix_SetGet01(
    const
    char        *pTestName
)
{
    U16MATRIX_DATA  *pObj = OBJ_NIL;
    ERESULT         eRc;
    ASTR_DATA       *pStr;
    uint16_t        max = 4;
    uint16_t        value = 0;

    fprintf(stderr, "Performing: %s\n", pTestName);

    pObj = U16Matrix_NewWithSizes(max, max);
    XCTAssertFalse( (OBJ_NIL == pObj) );
    if (pObj) {

        value = U16Matrix_Get(pObj, 1, 1);
        XCTAssertTrue( (0 == value) );
        value = U16Matrix_Get(pObj, 1, 2);
        XCTAssertTrue( (0 == value) );
        value = U16Matrix_Get(pObj, 1, 3);
        XCTAssertTrue( (0 == value) );
        value = U16Matrix_Get(pObj, 1, 4);
        XCTAssertTrue( (0 == value) );

        value = U16Matrix_Get(pObj, 1, 1);
        XCTAssertTrue( (0 == value) );
        eRc = U16Matrix_Set(pObj, 1, 1, 1);
        XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
        value = U16Matrix_Get(pObj, 1, 1);
        XCTAssertTrue( (1 == value) );
        value = U16Matrix_Get(pObj, 1, 2);
        XCTAssertTrue( (0 == value) );
        value = U16Matrix_Get(pObj, 1, 3);
        XCTAssertTrue( (0 == value) );
        value = U16Matrix_Get(pObj, 1, 4);
        XCTAssertTrue( (0 == value) );

        eRc = U16Matrix_Set(pObj, 2, 2, 1);
        XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
        value = U16Matrix_Get(pObj, 2, 2);
        XCTAssertTrue( (1 == value) );
        value = U16Matrix_Get(pObj, 2, 1);
        XCTAssertTrue( (0 == value) );
        value = U16Matrix_Get(pObj, 2, 3);
        XCTAssertTrue( (0 == value) );
        value = U16Matrix_Get(pObj, 2, 4);
        XCTAssertTrue( (0 == value) );

        eRc = U16Matrix_Set(pObj, 3, 3, 1);
        XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
        value = U16Matrix_Get(pObj, 3, 3);
        XCTAssertTrue( (1 == value) );
        value = U16Matrix_Get(pObj, 3, 1);
        XCTAssertTrue( (0 == value) );
        value = U16Matrix_Get(pObj, 3, 2);
        XCTAssertTrue( (0 == value) );
        value = U16Matrix_Get(pObj, 3, 4);
        XCTAssertTrue( (0 == value) );

        eRc = U16Matrix_Set(pObj, 4, 4, 1);
        XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
        value = U16Matrix_Get(pObj, 4, 4);
        XCTAssertTrue( (1 == value) );
        value = U16Matrix_Get(pObj, 4, 1);
        XCTAssertTrue( (0 == value) );
        value = U16Matrix_Get(pObj, 4, 2);
        XCTAssertTrue( (0 == value) );
        value = U16Matrix_Get(pObj, 4, 3);
        XCTAssertTrue( (0 == value) );

        pStr = U16Matrix_ToDebugString(pObj, 0);
        fprintf(stderr, "%s\n\n", AStr_getData(pStr));
        obj_Release(pStr);
        pStr = OBJ_NIL;

        obj_Release(pObj);
        pObj = OBJ_NIL;
    }

    fprintf(stderr, "...%s completed.\n", pTestName);
    return 1;
}



int         test_U16Matrix_SetGet02(
    const
    char        *pTestName
)
{
    U16MATRIX_DATA    *pObj = OBJ_NIL;
    ERESULT         eRc;
    ASTR_DATA       *pStr;
    uint16_t        max = 4;
    uint16_t        value = 0;

    fprintf(stderr, "Performing: %s\n", pTestName);

    pObj = U16Matrix_NewWithSizes((2 * max), max);
    XCTAssertFalse( (OBJ_NIL == pObj) );
    if (pObj) {

        value = U16Matrix_Get(pObj, 1, 1);
        XCTAssertTrue( (0 == value) );
        eRc = U16Matrix_Set(pObj, 1, 1, 1);
        XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
        value = U16Matrix_Get(pObj, 1, 1);
        XCTAssertTrue( (1 == value) );

        eRc = U16Matrix_Set(pObj, 2, 2, 1);
        XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
        value = U16Matrix_Get(pObj, 2, 2);
        XCTAssertTrue( (1 == value) );

        eRc = U16Matrix_Set(pObj, 3, 3, 1);
        XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
        value = U16Matrix_Get(pObj, 3, 3);
        XCTAssertTrue( (1 == value) );

        eRc = U16Matrix_Set(pObj, 4, 4, 1);
        XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
        value = U16Matrix_Get(pObj, 4, 4);
        XCTAssertTrue( (1 == value) );

        eRc = U16Matrix_Set(pObj, 5, 1, 100);
        XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
        value = U16Matrix_Get(pObj, 5, 1);
        XCTAssertTrue( (100 == value) );

        pStr = U16Matrix_ToDebugString(pObj, 0);
        fprintf(stderr, "%s\n\n", AStr_getData(pStr));
        obj_Release(pStr);
        pStr = OBJ_NIL;

        obj_Release(pObj);
        pObj = OBJ_NIL;
    }

    fprintf(stderr, "...%s completed.\n", pTestName);
    return 1;
}



int         test_U16Matrix_Identity01(
    const
    char        *pTestName
)
{
    U16MATRIX_DATA    *pObj = OBJ_NIL;
    ASTR_DATA       *pStr;
    uint16_t        value = 0;

    fprintf(stderr, "Performing: %s\n", pTestName);

    pObj = U16Matrix_NewIdentity(2);
    XCTAssertFalse( (OBJ_NIL == pObj) );
    if (pObj) {

        value = U16Matrix_Get(pObj, 1, 1);
        XCTAssertTrue( (1 == value) );
        value = U16Matrix_Get(pObj, 1, 2);
        XCTAssertTrue( (0 == value) );
        value = U16Matrix_Get(pObj, 2, 1);
        XCTAssertTrue( (0 == value) );
        value = U16Matrix_Get(pObj, 2, 2);
        XCTAssertTrue( (1 == value) );

        pStr = U16Matrix_ToDebugString(pObj, 0);
        fprintf(stderr, "%s\n\n", AStr_getData(pStr));
        obj_Release(pStr);
        pStr = OBJ_NIL;

#ifdef XYZZY
        pStr = U16Matrix_CompressedTable(pObj, "test");
        fprintf(stderr, "%s\n\n\n", AStr_getData(pStr));
        obj_Release(pStr);
        pStr = OBJ_NIL;
#endif

        obj_Release(pObj);
        pObj = OBJ_NIL;
    }

    fprintf(stderr, "...%s completed.\n", pTestName);
    return 1;
}



int         test_U16Matrix_Multiply01(
    const
    char        *pTestName
)
{
    U16MATRIX_DATA    *pObj = OBJ_NIL;
    U16MATRIX_DATA    *pObj2 = OBJ_NIL;
    U16MATRIX_DATA    *pResult = OBJ_NIL;
    ERESULT         eRc;
    uint16_t        value = 0;

    /*
     1   2    0  1    4  7
            X       =
     3   4    2  3    8  15
     */

    fprintf(stderr, "Performing: %s\n", pTestName);

    pObj = U16Matrix_NewWithSizes(2, 2);
    XCTAssertFalse( (OBJ_NIL == pObj) );
    if (pObj) {

        value = U16Matrix_Get(pObj, 1, 1);
        XCTAssertTrue( (0 == value) );
        eRc = U16Matrix_Set(pObj, 1, 1, 1);
        XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
        value = U16Matrix_Get(pObj, 1, 1);
        XCTAssertTrue( (1 == value) );

        eRc = U16Matrix_Set(pObj, 1, 2, 2);
        XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
        value = U16Matrix_Get(pObj, 1, 2);
        XCTAssertTrue( (2 == value) );

        eRc = U16Matrix_Set(pObj, 2, 1, 3);
        XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
        value = U16Matrix_Get(pObj, 2, 1);
        XCTAssertTrue( (3 == value) );

        eRc = U16Matrix_Set(pObj, 2, 2, 4);
        XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
        value = U16Matrix_Get(pObj, 2, 2);
        XCTAssertTrue( (4 == value) );

        pObj2 = U16Matrix_NewWithSizes(2, 2);
        XCTAssertFalse( (OBJ_NIL == pObj2) );
        if (pObj2) {

            value = U16Matrix_Get(pObj2, 1, 1);
            XCTAssertTrue( (0 == value) );
            eRc = U16Matrix_Set(pObj2, 1, 1, 0);
            XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
            value = U16Matrix_Get(pObj2, 1, 1);
            XCTAssertTrue( (0 == value) );

            eRc = U16Matrix_Set(pObj2, 1, 2, 1);
            XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
            value = U16Matrix_Get(pObj2, 1, 2);
            XCTAssertTrue( (1 == value) );

            eRc = U16Matrix_Set(pObj2, 2, 1, 2);
            XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
            value = U16Matrix_Get(pObj2, 2, 1);
            XCTAssertTrue( (2 == value) );

            eRc = U16Matrix_Set(pObj2, 2, 2, 3);
            XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
            value = U16Matrix_Get(pObj2, 2, 2);
            XCTAssertTrue( (3 == value) );

            pResult = U16Matrix_Multiply(pObj, pObj2);
            XCTAssertFalse( (OBJ_NIL == pResult) );
            XCTAssertTrue( (2 == U16Matrix_getM(pResult)) );
            XCTAssertTrue( (2 == U16Matrix_getN(pResult)) );

            if (pResult) {

                value = U16Matrix_getN(pResult);
                fprintf(stderr, "n = %d\n", value);
                XCTAssertTrue( (2 == value) );
                value = U16Matrix_getN(pResult);
                fprintf(stderr, "m = %d\n", value);
                XCTAssertTrue( (2 == value) );

                value = U16Matrix_Get(pResult, 1, 1);
                fprintf(stderr, "(1,1) = %d need 4\n", value);
                XCTAssertTrue( (4 == value) );

                value = U16Matrix_Get(pResult, 1, 2);
                fprintf(stderr, "(1,2) = %d need 7\n", value);
                XCTAssertTrue( (7 == value) );

                value = U16Matrix_Get(pResult, 2, 1);
                fprintf(stderr, "(2,1) = %d need 8\n", value);
                XCTAssertTrue( (8 == value) );

                value = U16Matrix_Get(pResult, 2, 2);
                fprintf(stderr, "(2,2) = %d need 15\n", value);
                XCTAssertTrue( (15 == value) );

                obj_Release(pResult);
                pResult = OBJ_NIL;
            }

            obj_Release(pObj2);
            pObj2 = OBJ_NIL;
        }

        obj_Release(pObj);
        pObj = OBJ_NIL;
    }

    fprintf(stderr, "...%s completed.\n", pTestName);
    return 1;
}



int         test_U16Matrix_Multiply02(
    const
    char        *pTestName
)
{
    U16MATRIX_DATA    *pObj = OBJ_NIL;
    U16MATRIX_DATA    *pObj2 = OBJ_NIL;
    U16MATRIX_DATA    *pResult = OBJ_NIL;
    ERESULT         eRc;
    uint16_t        value = 0;

    /*
     0 0 1 1     12     15
     1 0 0 0  X   4  =  12
     1 1 0 1      9     22
     1 1 0 0      6     16
     */

    fprintf(stderr, "Performing: %s\n", pTestName);

    pObj = U16Matrix_NewWithSizes(4, 4);
    XCTAssertFalse( (OBJ_NIL == pObj) );
    if (pObj) {

        value = U16Matrix_Get(pObj, 1, 3);
        XCTAssertTrue( (0 == value) );
        eRc = U16Matrix_Set(pObj, 1, 3, 1);
        XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
        value = U16Matrix_Get(pObj, 1, 3);
        XCTAssertTrue( (1 == value) );

        eRc = U16Matrix_Set(pObj, 1, 4, 1);
        XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
        value = U16Matrix_Get(pObj, 1, 4);
        XCTAssertTrue( (1 == value) );

        eRc = U16Matrix_Set(pObj, 2, 1, 1);
        XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
        value = U16Matrix_Get(pObj, 2, 1);
        XCTAssertTrue( (1 == value) );

        eRc = U16Matrix_Set(pObj, 3, 1, 1);
        XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
        value = U16Matrix_Get(pObj, 3, 1);
        XCTAssertTrue( (1 == value) );

        eRc = U16Matrix_Set(pObj, 3, 2, 1);
        XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
        value = U16Matrix_Get(pObj, 3, 2);
        XCTAssertTrue( (1 == value) );

        eRc = U16Matrix_Set(pObj, 3, 4, 1);
        XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
        value = U16Matrix_Get(pObj, 3, 4);
        XCTAssertTrue( (1 == value) );

        eRc = U16Matrix_Set(pObj, 4, 1, 1);
        XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
        value = U16Matrix_Get(pObj, 4, 1);
        XCTAssertTrue( (1 == value) );

        eRc = U16Matrix_Set(pObj, 4, 2, 1);
        XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
        value = U16Matrix_Get(pObj, 4, 2);
        XCTAssertTrue( (1 == value) );

        pObj2 = U16Matrix_NewWithSizes(4, 1);
        XCTAssertFalse( (OBJ_NIL == pObj2) );
        if (pObj2) {

            value = U16Matrix_Get(pObj2, 1, 1);
            XCTAssertTrue( (0 == value) );
            eRc = U16Matrix_Set(pObj2, 1, 1, 12);
            XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
            value = U16Matrix_Get(pObj2, 1, 1);
            XCTAssertTrue( (12 == value) );

            eRc = U16Matrix_Set(pObj2, 2, 1, 4);
            XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
            value = U16Matrix_Get(pObj2, 2, 1);
            XCTAssertTrue( (4 == value) );

            eRc = U16Matrix_Set(pObj2, 3, 1, 9);
            XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
            value = U16Matrix_Get(pObj2, 3, 1);
            XCTAssertTrue( (9 == value) );

            eRc = U16Matrix_Set(pObj2, 4, 1, 6);
            XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
            value = U16Matrix_Get(pObj2, 4, 1);
            XCTAssertTrue( (6 == value) );

            pResult = U16Matrix_Multiply(pObj, pObj2);
            XCTAssertFalse( (OBJ_NIL == pResult) );

            if (pResult) {

                value = U16Matrix_getM(pResult);
                fprintf(stderr, "m = %d need 4\n", value);
                XCTAssertTrue( (4 == value) );
                value = U16Matrix_getN(pResult);
                fprintf(stderr, "n = %d need 1\n", value);
                XCTAssertTrue( (1 == value) );

                value = U16Matrix_Get(pResult, 1, 1);
                fprintf(stderr, "(1,1) = %d need 15\n", value);
                XCTAssertTrue( (15 == value) );
                value = U16Matrix_Get(pResult, 2, 1);
                fprintf(stderr, "(2,1) = %d need 12\n", value);
                XCTAssertTrue( (12 == value) );
                value = U16Matrix_Get(pResult, 3, 1);
                fprintf(stderr, "(3,1) = %d need 22\n", value);
                XCTAssertTrue( (22 == value) );
                value = U16Matrix_Get(pResult, 4, 1);
                fprintf(stderr, "(4,1) = %d need 16\n", value);
                XCTAssertTrue( (16 == value) );

                obj_Release(pResult);
                pResult = OBJ_NIL;
            }

            obj_Release(pObj2);
            pObj2 = OBJ_NIL;
        }

        obj_Release(pObj);
        pObj = OBJ_NIL;
    }

    fprintf(stderr, "...%s completed.\n", pTestName);
    return 1;
}



int         test_U16Matrix_ValueCheck01(
    const
    char        *pTestName
)
{
    U16MATRIX_DATA    *pObj = OBJ_NIL;
    ERESULT         eRc;
    uint16_t        value = 0;
    MATRIX_BUILD    *pBuild;
    uint32_t        i = 0;
    uint32_t        iMax = 0;

    /*
     0 0 1 1
     1 0 0 0
     1 1 0 1
     1 1 0 0
     */

    fprintf(stderr, "Performing: %s\n", pTestName);

    pObj = U16Matrix_NewWithSizes(4, 4);
    XCTAssertFalse( (OBJ_NIL == pObj) );
    if (pObj) {

        value = U16Matrix_Get(pObj, 1, 1);
        XCTAssertTrue( (0 == value) );
        value = U16Matrix_Get(pObj, 1, 2);
        XCTAssertTrue( (0 == value) );

        value = U16Matrix_Get(pObj, 1, 3);
        XCTAssertTrue( (0 == value) );
        eRc = U16Matrix_Set(pObj, 1, 3, 1);
        XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
        value = U16Matrix_Get(pObj, 1, 3);
        XCTAssertTrue( (1 == value) );

        eRc = U16Matrix_Set(pObj, 1, 4, 1);
        XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
        value = U16Matrix_Get(pObj, 1, 4);
        XCTAssertTrue( (1 == value) );

        eRc = U16Matrix_Set(pObj, 2, 1, 1);
        XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
        value = U16Matrix_Get(pObj, 2, 1);
        XCTAssertTrue( (1 == value) );

        eRc = U16Matrix_Set(pObj, 3, 1, 1);
        XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
        value = U16Matrix_Get(pObj, 3, 1);
        XCTAssertTrue( (1 == value) );

        eRc = U16Matrix_Set(pObj, 3, 2, 1);
        XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
        value = U16Matrix_Get(pObj, 3, 2);
        XCTAssertTrue( (1 == value) );

        eRc = U16Matrix_Set(pObj, 3, 4, 1);
        XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
        value = U16Matrix_Get(pObj, 3, 4);
        XCTAssertTrue( (1 == value) );

        eRc = U16Matrix_Set(pObj, 4, 1, 1);
        XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
        value = U16Matrix_Get(pObj, 4, 1);
        XCTAssertTrue( (1 == value) );

        eRc = U16Matrix_Set(pObj, 4, 2, 1);
        XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
        value = U16Matrix_Get(pObj, 4, 2);
        XCTAssertTrue( (1 == value) );

        value = U16Matrix_Get(pObj, 1, 1);
        XCTAssertTrue( (0 == value) );
        value = U16Matrix_Get(pObj, 1, 2);
        XCTAssertTrue( (0 == value) );
        value = U16Matrix_Get(pObj, 1, 3);
        XCTAssertTrue( (1 == value) );
        value = U16Matrix_Get(pObj, 1, 4);
        XCTAssertTrue( (1 == value) );
        value = U16Matrix_Get(pObj, 2, 1);
        XCTAssertTrue( (1 == value) );
        value = U16Matrix_Get(pObj, 2, 2);
        XCTAssertTrue( (0 == value) );
        value = U16Matrix_Get(pObj, 2, 3);
        XCTAssertTrue( (0 == value) );
        value = U16Matrix_Get(pObj, 2, 4);
        XCTAssertTrue( (0 == value) );
        value = U16Matrix_Get(pObj, 3, 1);
        XCTAssertTrue( (1 == value) );
        value = U16Matrix_Get(pObj, 3, 2);
        XCTAssertTrue( (1 == value) );
        value = U16Matrix_Get(pObj, 3, 3);
        XCTAssertTrue( (0 == value) );
        value = U16Matrix_Get(pObj, 3, 4);
        XCTAssertTrue( (1 == value) );
        value = U16Matrix_Get(pObj, 4, 1);
        XCTAssertTrue( (1 == value) );
        value = U16Matrix_Get(pObj, 4, 2);
        XCTAssertTrue( (1 == value) );
        value = U16Matrix_Get(pObj, 4, 3);
        XCTAssertTrue( (0 == value) );
        value = U16Matrix_Get(pObj, 4, 4);
        XCTAssertTrue( (0 == value) );

        pBuild = U16Matrix_BuildValueCheck(pObj);
        XCTAssertFalse( (NULL == pBuild) );

        if (pBuild) {

            if (pBuild->m > pBuild->highest) {
                iMax = pBuild->m;
            }
            else {
                iMax = pBuild->highest;
            }
            fprintf(stderr, "\n\n     Base Check Value\n");
            for (i=0; i<iMax; ++i) {
                fprintf(stderr, "%3d  ", i);
                if (i+1 <= pBuild->m) {
                    fprintf(stderr, "%3d  ", pBuild->pBase[i]);
                }
                else {
                    fprintf(stderr, "     ");
                }
                if (i < pBuild->highest) {
                    fprintf(stderr, "%3d  %3d\n", pBuild->pCheck[i], pBuild->pValue[i]);
                }
                else {
                    fprintf(stderr, "\n");
                }
            }
            fprintf(stderr, "\n\n\n");

            value = valueCheckGet(pBuild, 1, 1);
            fprintf(stderr, "(1,1) = %d need 0\n", value);
            XCTAssertTrue( (0 == value) );
            value = valueCheckGet(pBuild, 1, 2);
            fprintf(stderr, "(1,2) = %d need 0\n", value);
            XCTAssertTrue( (0 == value) );
            value = valueCheckGet(pBuild, 1, 3);
            fprintf(stderr, "(1,3) = %d need 1\n", value);
            XCTAssertTrue( (1 == value) );
            value = valueCheckGet(pBuild, 1, 4);
            fprintf(stderr, "(1,4) = %d need 1\n", value);
            XCTAssertTrue( (1 == value) );

            value = valueCheckGet(pBuild, 2, 1);
            fprintf(stderr, "(2,1) = %d need 1\n", value);
            XCTAssertTrue( (1 == value) );
            value = valueCheckGet(pBuild, 2, 2);
            fprintf(stderr, "(2,2) = %d need 0\n", value);
            XCTAssertTrue( (0 == value) );
            value = valueCheckGet(pBuild, 2, 3);
            fprintf(stderr, "(2,3) = %d need 0\n", value);
            XCTAssertTrue( (0 == value) );
            value = valueCheckGet(pBuild, 2, 4);
            fprintf(stderr, "(2,4) = %d need 0\n", value);
            XCTAssertTrue( (0 == value) );

            value = valueCheckGet(pBuild, 3, 1);
            fprintf(stderr, "(3,1) = %d need 1\n", value);
            XCTAssertTrue( (1 == value) );
            value = valueCheckGet(pBuild, 3, 2);
            fprintf(stderr, "(3,2) = %d need 1\n", value);
            XCTAssertTrue( (1 == value) );
            value = valueCheckGet(pBuild, 3, 3);
            fprintf(stderr, "(3,3) = %d need 0\n", value);
            XCTAssertTrue( (0 == value) );
            value = valueCheckGet(pBuild, 3, 4);
            fprintf(stderr, "(3,4) = %d need 1\n", value);
            XCTAssertTrue( (1 == value) );

            value = valueCheckGet(pBuild, 4, 1);
            fprintf(stderr, "(4,1) = %d need 1\n", value);
            XCTAssertTrue( (1 == value) );
            value = valueCheckGet(pBuild, 4, 2);
            fprintf(stderr, "(4,2) = %d need 1\n", value);
            XCTAssertTrue( (1 == value) );
            value = valueCheckGet(pBuild, 4, 3);
            fprintf(stderr, "(4,3) = %d need 0\n", value);
            XCTAssertTrue( (0 == value) );
            value = valueCheckGet(pBuild, 4, 4);
            fprintf(stderr, "(4,4) = %d need 0\n", value);
            XCTAssertTrue( (0 == value) );

            U16Matrix_FreeValueCheck(pObj, pBuild);
            pBuild = OBJ_NIL;
        }

        obj_Release(pObj);
        pObj = OBJ_NIL;
    }

    fprintf(stderr, "...%s completed.\n", pTestName);
    return 1;
}




TINYTEST_START_SUITE(test_U16Matrix);
    TINYTEST_ADD_TEST(test_U16Matrix_ValueCheck01,setUp,tearDown);
    TINYTEST_ADD_TEST(test_U16Matrix_Multiply02,setUp,tearDown);
    TINYTEST_ADD_TEST(test_U16Matrix_Multiply01,setUp,tearDown);
    TINYTEST_ADD_TEST(test_U16Matrix_Identity01,setUp,tearDown);
    TINYTEST_ADD_TEST(test_U16Matrix_SetGet02,setUp,tearDown);
    TINYTEST_ADD_TEST(test_U16Matrix_SetGet01,setUp,tearDown);
    TINYTEST_ADD_TEST(test_U16Matrix_Test01,setUp,tearDown);
    TINYTEST_ADD_TEST(test_U16Matrix_Copy01,setUp,tearDown);
    TINYTEST_ADD_TEST(test_U16Matrix_OpenClose,setUp,tearDown);
TINYTEST_END_SUITE();

TINYTEST_MAIN_SINGLE_SUITE(test_U16Matrix);





