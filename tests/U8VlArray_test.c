// vi:nu:et:sts=4 ts=4 sw=4
/*
 *	Generated 03/20/2020 11:56:58
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
#include    <JsonIn.h>
#include    <trace.h>
#include    <U8VlArray_internal.h>
#ifdef  U8VLARRAY_JSON_SUPPORT
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

#ifdef  U8VLARRAY_JSON_SUPPORT
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






int             test_U8VlArray_OpenClose (
    const
    char            *pTestName
)
{
    ERESULT         eRc = ERESULT_SUCCESS;
    U8VLARRAY_DATA	    *pObj = OBJ_NIL;
    bool            fRc;
   
    fprintf(stderr, "Performing: %s\n", pTestName);

    pObj = U8VlArray_Alloc( );
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    pObj = U8VlArray_Init( pObj );
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    if (pObj) {

        //obj_TraceSet(pObj, true);       
        fRc = obj_IsKindOf(pObj, OBJ_IDENT_U8VLARRAY);
        TINYTEST_TRUE( (fRc) );
        
        // Test something.
        TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );

        obj_Release(pObj);
        pObj = OBJ_NIL;
    }

    fprintf(stderr, "...%s completed.\n\n\n", pTestName);
    return 1;
}



int             test_U8VlArray_Copy01 (
    const
    char            *pTestName
)
{
    ERESULT         eRc = ERESULT_SUCCESS;
    U8VLARRAY_DATA	    *pObj1 = OBJ_NIL;
    U8VLARRAY_DATA	    *pObj2 = OBJ_NIL;
    bool            fRc;
#if defined(U8VLARRAY_JSON_SUPPORT)
    ASTR_DATA	    *pStr = OBJ_NIL;
#endif
    uint8_t         wrk[17];

    fprintf(stderr, "Performing: %s\n", pTestName);

    pObj1 = U8VlArray_New( );
    TINYTEST_FALSE( (OBJ_NIL == pObj1) );
    if (pObj1) {

        //obj_TraceSet(pObj1, true);       
        fRc = obj_IsKindOf(pObj1, OBJ_IDENT_U8VLARRAY);
        TINYTEST_TRUE( (fRc) );
        eRc = U8VlArray_SetupSize(pObj1, 16);
        TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );
        // 100B0231 03313204 31323300 00000000
        pObj1->pData[0]  = 0x10;
        pObj1->pData[1]  = 0x0B;
        pObj1->pData[2]  = 0x02;
        pObj1->pData[3]  = 0x31;
        pObj1->pData[4]  = 0x03;
        pObj1->pData[5]  = 0x31;
        pObj1->pData[6]  = 0x32;
        pObj1->pData[7]  = 0x04;
        pObj1->pData[8]  = 0x31;
        pObj1->pData[9]  = 0x32;
        pObj1->pData[10] = 0x33;

        // Test assign.
        pObj2 = U8VlArray_New();
        TINYTEST_FALSE( (OBJ_NIL == pObj2) );
        eRc = U8VlArray_Assign(pObj1, pObj2);
        TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );

        fRc = obj_IsKindOf(pObj2, OBJ_IDENT_U8VLARRAY);
        TINYTEST_TRUE( (fRc) );
        eRc = U8VlArray_Compare(pObj1, pObj2);
        TINYTEST_TRUE( (0 == eRc) );

        obj_Release(pObj2);
        pObj2 = OBJ_NIL;

        // Test copy.
        pObj2 = U8VlArray_Copy(pObj1);
        TINYTEST_FALSE( (OBJ_NIL == pObj2) );

        fRc = obj_IsKindOf(pObj2, OBJ_IDENT_U8VLARRAY);
        TINYTEST_TRUE( (fRc) );
        eRc = U8VlArray_Compare(pObj1, pObj2);
        TINYTEST_TRUE( (0 == eRc) );

        obj_Release(pObj2);
        pObj2 = OBJ_NIL;

        // Test json support.
#if defined(U8VLARRAY_JSON_SUPPORT)
        pStr = U8VlArray_ToJson(pObj1);
        TINYTEST_FALSE( (OBJ_NIL == pStr) );
        fprintf(stderr, "JSON: %s\n", AStr_getData(pStr));
        pObj2 = U8VlArray_NewFromJsonString(pStr);
        TINYTEST_FALSE( (OBJ_NIL == pObj2) );
        fRc = obj_IsKindOf(pObj2, OBJ_IDENT_U8VLARRAY);
        TINYTEST_TRUE( (fRc) );
        obj_Release(pStr);
        pStr = OBJ_NIL;
        eRc = U8VlArray_Compare(pObj1, pObj2);
        TINYTEST_TRUE( (0 == eRc) );

        obj_Release(pObj2);
        pObj2 = OBJ_NIL;
#endif

        obj_Release(pObj1);
        pObj1 = OBJ_NIL;
    }

    fprintf(stderr, "...%s completed.\n\n\n", pTestName);
    return 1;
}



int             test_U8VlArray_Test01 (
    const
    char            *pTestName
)
{
    ERESULT         eRc = ERESULT_SUCCESS;
    U8VLARRAY_DATA	*pObj = OBJ_NIL;
    bool            fRc;
    uint8_t         wrk[17];
    uint8_t         *pWrk;
   
    fprintf(stderr, "Performing: %s\n", pTestName);

    pObj = U8VlArray_New( );
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    if (pObj) {

        fRc = obj_IsKindOf(pObj, OBJ_IDENT_U8VLARRAY);
        TINYTEST_TRUE( (fRc) );
        eRc = U8VlArray_SetupSize(pObj, 16);
        TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );
        TINYTEST_TRUE( (pObj->pData[0] == 16) );
        TINYTEST_TRUE( (pObj->pData[1] == 2) );
        {
            ASTR_DATA       *pWrk = U8VlArray_ToDebugString(pObj, 0);
            if (pWrk) {
                fprintf(stderr, "%s\n\n", AStr_getData(pWrk));
                obj_Release(pWrk);
            }
        }

        wrk[0] = 2;
        wrk[1] = '1';
        eRc = U8VlArray_AppendData(pObj, wrk);
        TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );
        TINYTEST_TRUE( (pObj->pData[0] == 16) );
        TINYTEST_TRUE( (pObj->pData[1] == 4) );
        {
            ASTR_DATA       *pWrk = U8VlArray_ToDebugString(pObj, 0);
            if (pWrk) {
                fprintf(stderr, "%s\n\n", AStr_getData(pWrk));
                obj_Release(pWrk);
            }
        }

        wrk[0] = 3;
        wrk[1] = '1';
        wrk[2] = '2';
        eRc = U8VlArray_AppendData(pObj, wrk);
        TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );
        TINYTEST_TRUE( (pObj->pData[0] == 16) );
        TINYTEST_TRUE( (pObj->pData[1] == 7) );
        {
            ASTR_DATA       *pWrk = U8VlArray_ToDebugString(pObj, 0);
            if (pWrk) {
                fprintf(stderr, "%s\n\n", AStr_getData(pWrk));
                obj_Release(pWrk);
            }
        }

        wrk[0] = 4;
        wrk[1] = '1';
        wrk[2] = '2';
        wrk[3] = '3';
        eRc = U8VlArray_AppendData(pObj, wrk);
        TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );
        TINYTEST_TRUE( (pObj->pData[0] == 16) );
        TINYTEST_TRUE( (pObj->pData[1] == 11) );
        {
            ASTR_DATA       *pWrk = U8VlArray_ToDebugString(pObj, 0);
            if (pWrk) {
                fprintf(stderr, "%s\n\n", AStr_getData(pWrk));
                obj_Release(pWrk);
            }
        }

        pWrk = U8VlArray_Get(pObj, 1);
        TINYTEST_FALSE( (NULL == pWrk) );
        TINYTEST_TRUE( (pWrk[0] == 2) );
        TINYTEST_TRUE( (pWrk[1] == '1') );

        pWrk = U8VlArray_Get(pObj, 2);
        TINYTEST_FALSE( (NULL == pWrk) );
        TINYTEST_TRUE( (pWrk[0] == 3) );
        TINYTEST_TRUE( (pWrk[1] == '1') );
        TINYTEST_TRUE( (pWrk[2] == '2') );

        pWrk = U8VlArray_Get(pObj, 3);
        TINYTEST_FALSE( (NULL == pWrk) );
        TINYTEST_TRUE( (pWrk[0] == 4) );
        TINYTEST_TRUE( (pWrk[1] == '1') );
        TINYTEST_TRUE( (pWrk[2] == '2') );
        TINYTEST_TRUE( (pWrk[3] == '3') );

        pWrk = U8VlArray_Get(pObj, 4);
        TINYTEST_TRUE( (NULL == pWrk) );

        {
            ASTR_DATA       *pWrk = U8VlArray_ToDebugString(pObj, 0);
            if (pWrk) {
                fprintf(stderr, "%s\n\n", AStr_getData(pWrk));
                obj_Release(pWrk);
            }
        }

        wrk[0] = 2;
        wrk[1] = '2';
        eRc = U8VlArray_InsertData(pObj, 0, wrk);
        TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );
        TINYTEST_TRUE( (pObj->pData[0] == 16) );
        TINYTEST_TRUE( (pObj->pData[1] == 13) );
        TINYTEST_TRUE( (pObj->pData[3] == '2') );
        TINYTEST_TRUE( (pObj->pData[7] == '1') );

        {
            ASTR_DATA       *pWrk = U8VlArray_ToDebugString(pObj, 0);
            if (pWrk) {
                fprintf(stderr, "%s\n\n", AStr_getData(pWrk));
                obj_Release(pWrk);
            }
        }

        wrk[0] = 2;
        wrk[1] = '3';
        eRc = U8VlArray_InsertData(pObj, 2, wrk);
        TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );
        TINYTEST_TRUE( (pObj->pData[0] == 16) );
        TINYTEST_TRUE( (pObj->pData[1] == 15) );
        TINYTEST_TRUE( (pObj->pData[7] == '3') );

        {
            ASTR_DATA       *pWrk = U8VlArray_ToDebugString(pObj, 0);
            if (pWrk) {
                fprintf(stderr, "%s\n\n", AStr_getData(pWrk));
                obj_Release(pWrk);
            }
        }

        obj_Release(pObj);
        pObj = OBJ_NIL;
    }

    fprintf(stderr, "...%s completed.\n\n\n", pTestName);
    return 1;
}




TINYTEST_START_SUITE(test_U8VlArray);
    TINYTEST_ADD_TEST(test_U8VlArray_Test01,setUp,tearDown);
    //TINYTEST_ADD_TEST(test_U8VlArray_Copy01,setUp,tearDown);
    TINYTEST_ADD_TEST(test_U8VlArray_OpenClose,setUp,tearDown);
TINYTEST_END_SUITE();

TINYTEST_MAIN_SINGLE_SUITE(test_U8VlArray);





