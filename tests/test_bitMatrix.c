/*
 *	Generated 08/12/2018 15:05:02
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
#include    <szTbl.h>
#include    <trace.h>
#include    <bitMatrix_internal.h>



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






int             test_bitMatrix_OpenClose(
    const
    char            *pTestName
)
{
    BITMATRIX_DATA	*pObj = OBJ_NIL;
    ERESULT         eRc;
   
    fprintf(stderr, "Performing: %s\n", pTestName);

    pObj = bitMatrix_New(2, 1);
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    if (pObj) {

        TINYTEST_TRUE( (2 == pObj->cElems) );
        TINYTEST_TRUE( (1 == pObj->xWords) );
        TINYTEST_FALSE( (NULL == pObj->pElems) );

        eRc = bitMatrix_IsEmpty(pObj);
        TINYTEST_TRUE( (ERESULT_SUCCESS_TRUE == eRc) );
        
        eRc = bitMatrix_Get(pObj, 1, 1);
        TINYTEST_TRUE( (ERESULT_SUCCESS_FALSE == eRc) );

        TINYTEST_TRUE( (0x00000000 == pObj->pElems[0]) );
        eRc = bitMatrix_Set(pObj, 1, 1, true);
        TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );
        TINYTEST_TRUE( (0x80000000 == pObj->pElems[0]) );

        eRc = bitMatrix_IsEmpty(pObj);
        TINYTEST_TRUE( (ERESULT_FAILURE_FALSE == eRc) );
        
        eRc = bitMatrix_Get(pObj, 1, 1);
        TINYTEST_TRUE( (ERESULT_SUCCESS_TRUE == eRc) );
        
        eRc = bitMatrix_Get(pObj, 2, 1);
        TINYTEST_TRUE( (ERESULT_SUCCESS_FALSE == eRc) );
        
        TINYTEST_TRUE( (0x80000000 == pObj->pElems[0]) );
        TINYTEST_TRUE( (0x00000000 == pObj->pElems[1]) );
        eRc = bitMatrix_Set(pObj, 2, 1, true);
        TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );
        TINYTEST_TRUE( (0x80000000 == pObj->pElems[0]) );
        TINYTEST_TRUE( (0x80000000 == pObj->pElems[1]) );
        
        eRc = bitMatrix_IsEmpty(pObj);
        TINYTEST_TRUE( (ERESULT_FAILURE_FALSE == eRc) );
        
        eRc = bitMatrix_Get(pObj, 2, 1);
        TINYTEST_TRUE( (ERESULT_SUCCESS_TRUE == eRc) );
        
        obj_Release(pObj);
        pObj = OBJ_NIL;
    }

    fprintf(stderr, "...%s completed.\n\n", pTestName);
    return 1;
}



int             test_bitMatrix_Reflex01(
    const
    char            *pTestName
)
{
    BITMATRIX_DATA  *pObj = OBJ_NIL;
    ERESULT         eRc;
    
    fprintf(stderr, "Performing: %s\n", pTestName);
    
    pObj = bitMatrix_New(11, 11);
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    if (pObj) {
        
        // Set up "BEGINS-DIRECTLY-WITH", fig a, pg 268,
        // in "Compiler Design Theory", Lewis, Rosenkrantz
        // and Stearns, Addison-Wesley, 1976
        eRc = bitMatrix_Set(pObj, 1, 2, true);
        TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );
        eRc = bitMatrix_Set(pObj, 1, 3, true);
        TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );
        eRc = bitMatrix_Set(pObj, 1, 10, true);
        TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );
        eRc = bitMatrix_Set(pObj, 2, 7, true);
        TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );
        eRc = bitMatrix_Set(pObj, 3, 4, true);
        TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );
        eRc = bitMatrix_Set(pObj, 3, 6, true);
        TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );
        eRc = bitMatrix_Set(pObj, 3, 8, true);
        TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );
        eRc = bitMatrix_Set(pObj, 4, 9, true);
        TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );
        eRc = bitMatrix_Set(pObj, 5, 8, true);
        TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );
        eRc = bitMatrix_Set(pObj, 5, 10, true);
        TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );

        eRc = bitMatrix_ReflectiveTransitiveClosure(pObj);
        TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );
        
        eRc = bitMatrix_Get(pObj, 1, 1);
        TINYTEST_TRUE( (ERESULT_SUCCESS_TRUE == eRc) );
        eRc = bitMatrix_Get(pObj, 1, 2);
        TINYTEST_TRUE( (ERESULT_SUCCESS_TRUE == eRc) );
        eRc = bitMatrix_Get(pObj, 1, 3);
        TINYTEST_TRUE( (ERESULT_SUCCESS_TRUE == eRc) );
        eRc = bitMatrix_Get(pObj, 1, 4);
        TINYTEST_TRUE( (ERESULT_SUCCESS_TRUE == eRc) );
        eRc = bitMatrix_Get(pObj, 1, 5);
        TINYTEST_TRUE( (ERESULT_SUCCESS_FALSE == eRc) );
        eRc = bitMatrix_Get(pObj, 1, 6);
        TINYTEST_TRUE( (ERESULT_SUCCESS_TRUE == eRc) );
        eRc = bitMatrix_Get(pObj, 1, 7);
        TINYTEST_TRUE( (ERESULT_SUCCESS_TRUE == eRc) );
        eRc = bitMatrix_Get(pObj, 1, 8);
        TINYTEST_TRUE( (ERESULT_SUCCESS_TRUE == eRc) );
        eRc = bitMatrix_Get(pObj, 1, 9);
        TINYTEST_TRUE( (ERESULT_SUCCESS_TRUE == eRc) );
        eRc = bitMatrix_Get(pObj, 1, 10);
        TINYTEST_TRUE( (ERESULT_SUCCESS_TRUE == eRc) );
        eRc = bitMatrix_Get(pObj, 1, 11);
        TINYTEST_TRUE( (ERESULT_SUCCESS_FALSE == eRc) );
        eRc = bitMatrix_Get(pObj, 2, 1);
        TINYTEST_TRUE( (ERESULT_SUCCESS_FALSE == eRc) );
        eRc = bitMatrix_Get(pObj, 2, 2);
        TINYTEST_TRUE( (ERESULT_SUCCESS_TRUE == eRc) );
        eRc = bitMatrix_Get(pObj, 2, 3);
        TINYTEST_TRUE( (ERESULT_SUCCESS_FALSE == eRc) );
        eRc = bitMatrix_Get(pObj, 2, 4);
        TINYTEST_TRUE( (ERESULT_SUCCESS_FALSE == eRc) );
        eRc = bitMatrix_Get(pObj, 2, 5);
        TINYTEST_TRUE( (ERESULT_SUCCESS_FALSE == eRc) );
        eRc = bitMatrix_Get(pObj, 2, 6);
        TINYTEST_TRUE( (ERESULT_SUCCESS_FALSE == eRc) );
        eRc = bitMatrix_Get(pObj, 2, 7);
        TINYTEST_TRUE( (ERESULT_SUCCESS_TRUE == eRc) );
        eRc = bitMatrix_Get(pObj, 2, 8);
        TINYTEST_TRUE( (ERESULT_SUCCESS_FALSE == eRc) );
        eRc = bitMatrix_Get(pObj, 2, 9);
        TINYTEST_TRUE( (ERESULT_SUCCESS_FALSE == eRc) );
        eRc = bitMatrix_Get(pObj, 2, 10);
        TINYTEST_TRUE( (ERESULT_SUCCESS_FALSE == eRc) );
        eRc = bitMatrix_Get(pObj, 2, 11);
        TINYTEST_TRUE( (ERESULT_SUCCESS_FALSE == eRc) );
        eRc = bitMatrix_Get(pObj, 3, 1);
        TINYTEST_TRUE( (ERESULT_SUCCESS_FALSE == eRc) );
        eRc = bitMatrix_Get(pObj, 3, 2);
        TINYTEST_TRUE( (ERESULT_SUCCESS_FALSE == eRc) );
        eRc = bitMatrix_Get(pObj, 3, 3);
        TINYTEST_TRUE( (ERESULT_SUCCESS_TRUE == eRc) );
        eRc = bitMatrix_Get(pObj, 3, 4);
        TINYTEST_TRUE( (ERESULT_SUCCESS_TRUE == eRc) );
        eRc = bitMatrix_Get(pObj, 3, 5);
        TINYTEST_TRUE( (ERESULT_SUCCESS_FALSE == eRc) );
        eRc = bitMatrix_Get(pObj, 3, 6);
        TINYTEST_TRUE( (ERESULT_SUCCESS_TRUE == eRc) );
        eRc = bitMatrix_Get(pObj, 3, 7);
        TINYTEST_TRUE( (ERESULT_SUCCESS_FALSE == eRc) );
        eRc = bitMatrix_Get(pObj, 3, 8);
        TINYTEST_TRUE( (ERESULT_SUCCESS_TRUE == eRc) );
        eRc = bitMatrix_Get(pObj, 3, 9);
        TINYTEST_TRUE( (ERESULT_SUCCESS_TRUE == eRc) );
        eRc = bitMatrix_Get(pObj, 3, 10);
        TINYTEST_TRUE( (ERESULT_SUCCESS_FALSE == eRc) );
        eRc = bitMatrix_Get(pObj, 3, 11);
        TINYTEST_TRUE( (ERESULT_SUCCESS_FALSE == eRc) );
        eRc = bitMatrix_Get(pObj, 4, 1);
        TINYTEST_TRUE( (ERESULT_SUCCESS_FALSE == eRc) );
        eRc = bitMatrix_Get(pObj, 4, 2);
        TINYTEST_TRUE( (ERESULT_SUCCESS_FALSE == eRc) );
        eRc = bitMatrix_Get(pObj, 4, 3);
        TINYTEST_TRUE( (ERESULT_SUCCESS_FALSE == eRc) );
        eRc = bitMatrix_Get(pObj, 4, 4);
        TINYTEST_TRUE( (ERESULT_SUCCESS_TRUE == eRc) );
        eRc = bitMatrix_Get(pObj, 4, 5);
        TINYTEST_TRUE( (ERESULT_SUCCESS_FALSE == eRc) );
        eRc = bitMatrix_Get(pObj, 4, 6);
        TINYTEST_TRUE( (ERESULT_SUCCESS_FALSE == eRc) );
        eRc = bitMatrix_Get(pObj, 4, 7);
        TINYTEST_TRUE( (ERESULT_SUCCESS_FALSE == eRc) );
        eRc = bitMatrix_Get(pObj, 4, 8);
        TINYTEST_TRUE( (ERESULT_SUCCESS_FALSE == eRc) );
        eRc = bitMatrix_Get(pObj, 4, 9);
        TINYTEST_TRUE( (ERESULT_SUCCESS_TRUE == eRc) );
        eRc = bitMatrix_Get(pObj, 4, 10);
        TINYTEST_TRUE( (ERESULT_SUCCESS_FALSE == eRc) );
        eRc = bitMatrix_Get(pObj, 4, 11);
        TINYTEST_TRUE( (ERESULT_SUCCESS_FALSE == eRc) );
        eRc = bitMatrix_Get(pObj, 5, 1);
        TINYTEST_TRUE( (ERESULT_SUCCESS_FALSE == eRc) );
        eRc = bitMatrix_Get(pObj, 5, 2);
        TINYTEST_TRUE( (ERESULT_SUCCESS_FALSE == eRc) );
        eRc = bitMatrix_Get(pObj, 5, 3);
        TINYTEST_TRUE( (ERESULT_SUCCESS_FALSE == eRc) );
        eRc = bitMatrix_Get(pObj, 5, 4);
        TINYTEST_TRUE( (ERESULT_SUCCESS_FALSE == eRc) );
        eRc = bitMatrix_Get(pObj, 5, 5);
        TINYTEST_TRUE( (ERESULT_SUCCESS_TRUE == eRc) );
        eRc = bitMatrix_Get(pObj, 5, 6);
        TINYTEST_TRUE( (ERESULT_SUCCESS_FALSE == eRc) );
        eRc = bitMatrix_Get(pObj, 5, 7);
        TINYTEST_TRUE( (ERESULT_SUCCESS_FALSE == eRc) );
        eRc = bitMatrix_Get(pObj, 5, 8);
        TINYTEST_TRUE( (ERESULT_SUCCESS_TRUE == eRc) );
        eRc = bitMatrix_Get(pObj, 5, 9);
        TINYTEST_TRUE( (ERESULT_SUCCESS_FALSE == eRc) );
        eRc = bitMatrix_Get(pObj, 5, 10);
        TINYTEST_TRUE( (ERESULT_SUCCESS_TRUE == eRc) );
        eRc = bitMatrix_Get(pObj, 5, 11);
        TINYTEST_TRUE( (ERESULT_SUCCESS_FALSE == eRc) );
        eRc = bitMatrix_Get(pObj, 6, 1);
        TINYTEST_TRUE( (ERESULT_SUCCESS_FALSE == eRc) );
        eRc = bitMatrix_Get(pObj, 6, 2);
        TINYTEST_TRUE( (ERESULT_SUCCESS_FALSE == eRc) );
        eRc = bitMatrix_Get(pObj, 6, 3);
        TINYTEST_TRUE( (ERESULT_SUCCESS_FALSE == eRc) );
        eRc = bitMatrix_Get(pObj, 6, 4);
        TINYTEST_TRUE( (ERESULT_SUCCESS_FALSE == eRc) );
        eRc = bitMatrix_Get(pObj, 6, 5);
        TINYTEST_TRUE( (ERESULT_SUCCESS_FALSE == eRc) );
        eRc = bitMatrix_Get(pObj, 6, 6);
        TINYTEST_TRUE( (ERESULT_SUCCESS_TRUE == eRc) );
        eRc = bitMatrix_Get(pObj, 6, 7);
        TINYTEST_TRUE( (ERESULT_SUCCESS_FALSE == eRc) );
        eRc = bitMatrix_Get(pObj, 6, 8);
        TINYTEST_TRUE( (ERESULT_SUCCESS_FALSE == eRc) );
        eRc = bitMatrix_Get(pObj, 6, 9);
        TINYTEST_TRUE( (ERESULT_SUCCESS_FALSE == eRc) );
        eRc = bitMatrix_Get(pObj, 6, 10);
        TINYTEST_TRUE( (ERESULT_SUCCESS_FALSE == eRc) );
        eRc = bitMatrix_Get(pObj, 6, 11);
        TINYTEST_TRUE( (ERESULT_SUCCESS_FALSE == eRc) );
        eRc = bitMatrix_Get(pObj, 7, 1);
        TINYTEST_TRUE( (ERESULT_SUCCESS_FALSE == eRc) );
        eRc = bitMatrix_Get(pObj, 7, 2);
        TINYTEST_TRUE( (ERESULT_SUCCESS_FALSE == eRc) );
        eRc = bitMatrix_Get(pObj, 7, 3);
        TINYTEST_TRUE( (ERESULT_SUCCESS_FALSE == eRc) );
        eRc = bitMatrix_Get(pObj, 7, 4);
        TINYTEST_TRUE( (ERESULT_SUCCESS_FALSE == eRc) );
        eRc = bitMatrix_Get(pObj, 7, 5);
        TINYTEST_TRUE( (ERESULT_SUCCESS_FALSE == eRc) );
        eRc = bitMatrix_Get(pObj, 7, 6);
        TINYTEST_TRUE( (ERESULT_SUCCESS_FALSE == eRc) );
        eRc = bitMatrix_Get(pObj, 7, 7);
        TINYTEST_TRUE( (ERESULT_SUCCESS_TRUE == eRc) );
        eRc = bitMatrix_Get(pObj, 7, 8);
        TINYTEST_TRUE( (ERESULT_SUCCESS_FALSE == eRc) );
        eRc = bitMatrix_Get(pObj, 7, 9);
        TINYTEST_TRUE( (ERESULT_SUCCESS_FALSE == eRc) );
        eRc = bitMatrix_Get(pObj, 7, 10);
        TINYTEST_TRUE( (ERESULT_SUCCESS_FALSE == eRc) );
        eRc = bitMatrix_Get(pObj, 7, 11);
        TINYTEST_TRUE( (ERESULT_SUCCESS_FALSE == eRc) );
        eRc = bitMatrix_Get(pObj, 8, 1);
        TINYTEST_TRUE( (ERESULT_SUCCESS_FALSE == eRc) );
        eRc = bitMatrix_Get(pObj, 8, 2);
        TINYTEST_TRUE( (ERESULT_SUCCESS_FALSE == eRc) );
        eRc = bitMatrix_Get(pObj, 8, 3);
        TINYTEST_TRUE( (ERESULT_SUCCESS_FALSE == eRc) );
        eRc = bitMatrix_Get(pObj, 8, 4);
        TINYTEST_TRUE( (ERESULT_SUCCESS_FALSE == eRc) );
        eRc = bitMatrix_Get(pObj, 8, 5);
        TINYTEST_TRUE( (ERESULT_SUCCESS_FALSE == eRc) );
        eRc = bitMatrix_Get(pObj, 8, 6);
        TINYTEST_TRUE( (ERESULT_SUCCESS_FALSE == eRc) );
        eRc = bitMatrix_Get(pObj, 8, 7);
        TINYTEST_TRUE( (ERESULT_SUCCESS_FALSE == eRc) );
        eRc = bitMatrix_Get(pObj, 8, 8);
        TINYTEST_TRUE( (ERESULT_SUCCESS_TRUE == eRc) );
        eRc = bitMatrix_Get(pObj, 8, 9);
        TINYTEST_TRUE( (ERESULT_SUCCESS_FALSE == eRc) );
        eRc = bitMatrix_Get(pObj, 8, 10);
        TINYTEST_TRUE( (ERESULT_SUCCESS_FALSE == eRc) );
        eRc = bitMatrix_Get(pObj, 8, 11);
        TINYTEST_TRUE( (ERESULT_SUCCESS_FALSE == eRc) );
        eRc = bitMatrix_Get(pObj, 9, 1);
        TINYTEST_TRUE( (ERESULT_SUCCESS_FALSE == eRc) );
        eRc = bitMatrix_Get(pObj, 9, 2);
        TINYTEST_TRUE( (ERESULT_SUCCESS_FALSE == eRc) );
        eRc = bitMatrix_Get(pObj, 9, 3);
        TINYTEST_TRUE( (ERESULT_SUCCESS_FALSE == eRc) );
        eRc = bitMatrix_Get(pObj, 9, 4);
        TINYTEST_TRUE( (ERESULT_SUCCESS_FALSE == eRc) );
        eRc = bitMatrix_Get(pObj, 9, 5);
        TINYTEST_TRUE( (ERESULT_SUCCESS_FALSE == eRc) );
        eRc = bitMatrix_Get(pObj, 9, 6);
        TINYTEST_TRUE( (ERESULT_SUCCESS_FALSE == eRc) );
        eRc = bitMatrix_Get(pObj, 9, 7);
        TINYTEST_TRUE( (ERESULT_SUCCESS_FALSE == eRc) );
        eRc = bitMatrix_Get(pObj, 9, 8);
        TINYTEST_TRUE( (ERESULT_SUCCESS_FALSE == eRc) );
        eRc = bitMatrix_Get(pObj, 9, 9);
        TINYTEST_TRUE( (ERESULT_SUCCESS_TRUE == eRc) );
        eRc = bitMatrix_Get(pObj, 9, 10);
        TINYTEST_TRUE( (ERESULT_SUCCESS_FALSE == eRc) );
        eRc = bitMatrix_Get(pObj, 9, 11);
        TINYTEST_TRUE( (ERESULT_SUCCESS_FALSE == eRc) );
        eRc = bitMatrix_Get(pObj, 10, 1);
        TINYTEST_TRUE( (ERESULT_SUCCESS_FALSE == eRc) );
        eRc = bitMatrix_Get(pObj, 10, 2);
        TINYTEST_TRUE( (ERESULT_SUCCESS_FALSE == eRc) );
        eRc = bitMatrix_Get(pObj, 10, 3);
        TINYTEST_TRUE( (ERESULT_SUCCESS_FALSE == eRc) );
        eRc = bitMatrix_Get(pObj, 10, 4);
        TINYTEST_TRUE( (ERESULT_SUCCESS_FALSE == eRc) );
        eRc = bitMatrix_Get(pObj, 10, 5);
        TINYTEST_TRUE( (ERESULT_SUCCESS_FALSE == eRc) );
        eRc = bitMatrix_Get(pObj, 10, 6);
        TINYTEST_TRUE( (ERESULT_SUCCESS_FALSE == eRc) );
        eRc = bitMatrix_Get(pObj, 10, 7);
        TINYTEST_TRUE( (ERESULT_SUCCESS_FALSE == eRc) );
        eRc = bitMatrix_Get(pObj, 10, 8);
        TINYTEST_TRUE( (ERESULT_SUCCESS_FALSE == eRc) );
        eRc = bitMatrix_Get(pObj, 10, 9);
        TINYTEST_TRUE( (ERESULT_SUCCESS_FALSE == eRc) );
        eRc = bitMatrix_Get(pObj, 10, 10);
        TINYTEST_TRUE( (ERESULT_SUCCESS_TRUE == eRc) );
        eRc = bitMatrix_Get(pObj, 10, 11);
        TINYTEST_TRUE( (ERESULT_SUCCESS_FALSE == eRc) );
        eRc = bitMatrix_Get(pObj, 11, 1);
        TINYTEST_TRUE( (ERESULT_SUCCESS_FALSE == eRc) );
        eRc = bitMatrix_Get(pObj, 11, 2);
        TINYTEST_TRUE( (ERESULT_SUCCESS_FALSE == eRc) );
        eRc = bitMatrix_Get(pObj, 11, 3);
        TINYTEST_TRUE( (ERESULT_SUCCESS_FALSE == eRc) );
        eRc = bitMatrix_Get(pObj, 11, 4);
        TINYTEST_TRUE( (ERESULT_SUCCESS_FALSE == eRc) );
        eRc = bitMatrix_Get(pObj, 11, 5);
        TINYTEST_TRUE( (ERESULT_SUCCESS_FALSE == eRc) );
        eRc = bitMatrix_Get(pObj, 11, 6);
        TINYTEST_TRUE( (ERESULT_SUCCESS_FALSE == eRc) );
        eRc = bitMatrix_Get(pObj, 11, 7);
        TINYTEST_TRUE( (ERESULT_SUCCESS_FALSE == eRc) );
        eRc = bitMatrix_Get(pObj, 11, 8);
        TINYTEST_TRUE( (ERESULT_SUCCESS_FALSE == eRc) );
        eRc = bitMatrix_Get(pObj, 11, 9);
        TINYTEST_TRUE( (ERESULT_SUCCESS_FALSE == eRc) );
        eRc = bitMatrix_Get(pObj, 11, 10);
        TINYTEST_TRUE( (ERESULT_SUCCESS_FALSE == eRc) );
        eRc = bitMatrix_Get(pObj, 11, 11);
        TINYTEST_TRUE( (ERESULT_SUCCESS_TRUE == eRc) );

        obj_Release(pObj);
        pObj = OBJ_NIL;
    }
    
    fprintf(stderr, "...%s completed.\n\n", pTestName);
    return 1;
}



int             test_bitMatrix_Inflate01(
    const
    char            *pTestName
)
{
    BITMATRIX_DATA  *pObj = OBJ_NIL;
    ERESULT         eRc;
    uint32_t        x;
    //uint32_t        y;
    
    fprintf(stderr, "Performing: %s\n", pTestName);
    
    pObj = bitMatrix_New(1, 1);
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    if (pObj) {
        
        TINYTEST_TRUE( (1 == pObj->cElems) );
        TINYTEST_TRUE( (1 == pObj->xWords) );
        TINYTEST_FALSE( (NULL == pObj->pElems) );
        
        eRc = bitMatrix_IsEmpty(pObj);
        TINYTEST_TRUE( (ERESULT_SUCCESS_TRUE == eRc) );
        
        eRc = bitMatrix_Get(pObj, 1, 1);
        TINYTEST_TRUE( (ERESULT_SUCCESS_FALSE == eRc) );

        TINYTEST_TRUE( (0x00000000 == pObj->pElems[0]) );
        //TINYTEST_TRUE( (0x00000000 == pObj->pElems[1]) );
        eRc = bitMatrix_Set(pObj, 1, 1, true);
        TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );
        TINYTEST_TRUE( (0x80000000 == pObj->pElems[0]) );
        //TINYTEST_TRUE( (0x00000000 == pObj->pElems[1]) );

        for (x=1; x<32; ++x) {
            eRc = bitMatrix_InflateX(pObj, 1);
            TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );
            TINYTEST_TRUE( (1 == pObj->cElems) );
            TINYTEST_TRUE( (1 == pObj->xWords) );
            eRc = bitMatrix_Set(pObj, 1, x+1, true);
            TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );
        }
        TINYTEST_TRUE( (0xFFFFFFFF == pObj->pElems[0]) );
        //TINYTEST_TRUE( (0x00000000 == pObj->pElems[1]) );

        eRc = bitMatrix_InflateX(pObj, 1);
        TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );
        TINYTEST_TRUE( (2 == pObj->cElems) );
        TINYTEST_TRUE( (2 == pObj->xWords) );

        eRc = bitMatrix_Set(pObj, 1, 33, true);
        TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );
        TINYTEST_TRUE( (0xFFFFFFFF == pObj->pElems[0]) );
        TINYTEST_TRUE( (0x80000000 == pObj->pElems[1]) );

        obj_Release(pObj);
        pObj = OBJ_NIL;
    }
    
    fprintf(stderr, "...%s completed.\n\n", pTestName);
    return 1;
}



int             test_bitMatrix_Inflate02(
    const
    char            *pTestName
)
{
    BITMATRIX_DATA  *pObj = OBJ_NIL;
    ERESULT         eRc;
    //uint32_t        x;
    uint32_t        y;
    
    fprintf(stderr, "Performing: %s\n", pTestName);
    
    pObj = bitMatrix_New(1, 1);
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    if (pObj) {
        
        TINYTEST_TRUE( (1 == pObj->cElems) );
        TINYTEST_TRUE( (1 == pObj->xWords) );
        TINYTEST_FALSE( (NULL == pObj->pElems) );
        
        eRc = bitMatrix_IsEmpty(pObj);
        TINYTEST_TRUE( (ERESULT_SUCCESS_TRUE == eRc) );
        
        eRc = bitMatrix_Get(pObj, 1, 1);
        TINYTEST_TRUE( (ERESULT_SUCCESS_FALSE == eRc) );
        
        TINYTEST_TRUE( (0x00000000 == pObj->pElems[0]) );
        eRc = bitMatrix_Set(pObj, 1, 1, true);
        TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );
        TINYTEST_TRUE( (0x80000000 == pObj->pElems[0]) );
        
        for (y=1; y<32; ++y) {
            eRc = bitMatrix_InflateY(pObj, 1);
            TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );
            TINYTEST_TRUE( ((y + 1) == pObj->cElems) );
            TINYTEST_TRUE( (1 == pObj->xWords) );
            eRc = bitMatrix_Set(pObj, (y + 1), 1, true);
            TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );
        }
        TINYTEST_TRUE( (0x80000000 == pObj->pElems[0]) );
        TINYTEST_TRUE( (0x80000000 == pObj->pElems[1]) );
        
        eRc = bitMatrix_InflateY(pObj, 1);
        TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );
        TINYTEST_TRUE( (33 == pObj->cElems) );
        TINYTEST_TRUE( (1 == pObj->xWords) );
        
        eRc = bitMatrix_Set(pObj, 33, 1, true);
        TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );
        TINYTEST_TRUE( (0x80000000 == pObj->pElems[0]) );
        TINYTEST_TRUE( (0x80000000 == pObj->pElems[1]) );

        obj_Release(pObj);
        pObj = OBJ_NIL;
    }
    
    fprintf(stderr, "...%s completed.\n\n", pTestName);
    return 1;
}



int             test_bitMatrix_Invert01(
    const
    char            *pTestName
)
{
    BITMATRIX_DATA  *pObj = OBJ_NIL;
    ERESULT         eRc;
    //uint32_t        x;
    //uint32_t        y;
    
    fprintf(stderr, "Performing: %s\n", pTestName);
    
    pObj = bitMatrix_New(2, 1);
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    if (pObj) {
        
        TINYTEST_TRUE( (2 == pObj->cElems) );
        TINYTEST_TRUE( (1 == pObj->xWords) );
        TINYTEST_FALSE( (NULL == pObj->pElems) );
        
        eRc = bitMatrix_IsEmpty(pObj);
        TINYTEST_TRUE( (ERESULT_SUCCESS_TRUE == eRc) );
        
        eRc = bitMatrix_Invert(pObj);
        TINYTEST_TRUE( (ERESULT_SUCCESS_FALSE == eRc) );
        
        TINYTEST_TRUE( (0xFFFFFFFF == pObj->pElems[0]) );
        TINYTEST_TRUE( (0xFFFFFFFF == pObj->pElems[1]) );
        
        obj_Release(pObj);
        pObj = OBJ_NIL;
    }
    
    fprintf(stderr, "...%s completed.\n\n", pTestName);
    return 1;
}



int             test_bitMatrix_JSON01(
    const
    char            *pTestName
)
{
    BITMATRIX_DATA  *pObj = OBJ_NIL;
    BITMATRIX_DATA  *pNew = OBJ_NIL;
    ERESULT         eRc;
    //uint32_t        x;
    //uint32_t        y;
    ASTR_DATA       *pStr = OBJ_NIL;
    const
    char            *pStrA =
    "{\"objectType\":\"bitMatrix\",\n"
        "\t\"xSize\":4,\n"
        "\t\"xWords\":1,\n"
        "\t\"ySize\":4,\n"
        "\t\"cElems\":4,\n"
        "\t\"Elems\":[\n"
            "\t\t2147483648,\n"
            "\t\t1073741824,\n"
            "\t\t536870912,\n"
            "\t\t268435456\n"
        "\t]\n"
    "}\n";
    
    fprintf(stderr, "Performing: %s\n", pTestName);
    
    pObj = bitMatrix_NewIdentity(4);
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    if (pObj) {
        
        TINYTEST_TRUE( (4 == pObj->cElems) );
        TINYTEST_TRUE( (1 == pObj->xWords) );
        TINYTEST_FALSE( (NULL == pObj->pElems) );
        
        pStr = bitMatrix_ToJSON(pObj);
        TINYTEST_FALSE( (OBJ_NIL == pStr) );
        fprintf(stderr, "\tjson=\"%s\"\n", AStr_getData(pStr));
        eRc = AStr_CompareA(pStr, pStrA);
        TINYTEST_TRUE( (ERESULT_SUCCESS_EQUAL == eRc) );
        
        pNew = bitMatrix_NewFromJSONString(pStr);
        TINYTEST_FALSE( (OBJ_NIL == pNew) );
        TINYTEST_TRUE( (4 == pNew->xSize) );
        TINYTEST_TRUE( (4 == pNew->ySize) );
        TINYTEST_TRUE( (4 == pNew->cElems) );
        TINYTEST_TRUE( (1 == pNew->xWords) );
        TINYTEST_FALSE( (NULL == pNew->pElems) );
        TINYTEST_TRUE( (2147483648 == pNew->pElems[0]) );
        TINYTEST_TRUE( (1073741824 == pNew->pElems[1]) );
        TINYTEST_TRUE( ( 536870912 == pNew->pElems[2]) );
        TINYTEST_TRUE( ( 268435456 == pNew->pElems[3]) );
        obj_Release(pNew);
        pNew = OBJ_NIL;

        obj_Release(pStr);
        pStr = OBJ_NIL;
        obj_Release(pObj);
        pObj = OBJ_NIL;
    }
    
    fprintf(stderr, "...%s completed.\n\n", pTestName);
    return 1;
}




TINYTEST_START_SUITE(test_bitMatrix);
    TINYTEST_ADD_TEST(test_bitMatrix_JSON01,setUp,tearDown);
    TINYTEST_ADD_TEST(test_bitMatrix_Invert01,setUp,tearDown);
    TINYTEST_ADD_TEST(test_bitMatrix_Inflate02,setUp,tearDown);
    TINYTEST_ADD_TEST(test_bitMatrix_Inflate01,setUp,tearDown);
    TINYTEST_ADD_TEST(test_bitMatrix_Reflex01,setUp,tearDown);
    TINYTEST_ADD_TEST(test_bitMatrix_OpenClose,setUp,tearDown);
TINYTEST_END_SUITE();

TINYTEST_MAIN_SINGLE_SUITE(test_bitMatrix);





