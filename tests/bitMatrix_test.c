// vi:nu:et:sts=4 ts=4 sw=4
/*
 *	Generated 12/18/2019 08:00:28
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
#include    <BitMatrix_internal.h>
#include    <srcErrors.h>
#include    <szTbl.h>



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

    
    srcErrors_SharedReset( );
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






int             test_BitMatrix_OpenClose(
    const
    char            *pTestName
)
{
    ERESULT         eRc = ERESULT_SUCCESS;
    BITMATRIX_DATA	    *pObj = OBJ_NIL;
   
    fprintf(stderr, "Performing: %s\n", pTestName);

    pObj = BitMatrix_Alloc( );
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    pObj = BitMatrix_Init( pObj );
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    if (pObj) {

        //obj_TraceSet(pObj, true);       
        
        // Test something.
        TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );

        obj_Release(pObj);
        pObj = OBJ_NIL;
    }

    fprintf(stderr, "...%s completed.\n\n\n", pTestName);
    return 1;
}



int             test_BitMatrix_Test01(
    const
    char            *pTestName
)
{
    BITMATRIX_DATA    *pObj = OBJ_NIL;
    ERESULT         eRc;
   
    fprintf(stderr, "Performing: %s\n", pTestName);

    pObj = BitMatrix_NewWithSizes(2, 1);
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    if (pObj) {

        TINYTEST_TRUE( (2 == pObj->cElems) );
        TINYTEST_TRUE( (1 == pObj->xWords) );
        TINYTEST_FALSE( (NULL == pObj->pElems) );

        eRc = BitMatrix_IsEmpty(pObj);
        TINYTEST_TRUE( (ERESULT_SUCCESS_TRUE == eRc) );
        
        eRc = BitMatrix_Get(pObj, 1, 1);
        TINYTEST_TRUE( (ERESULT_SUCCESS_FALSE == eRc) );

        fprintf(stderr, "elems[0] = 0x%08X\n", pObj->pElems[0]);
        TINYTEST_TRUE( (0x00000000 == pObj->pElems[0]) );
        eRc = BitMatrix_Set(pObj, 1, 1, true);
        TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );
        fprintf(stderr, "elems[0] = 0x%08X\n", pObj->pElems[0]);
        TINYTEST_TRUE( (0x00000001 == pObj->pElems[0]) );

        eRc = BitMatrix_IsEmpty(pObj);
        TINYTEST_TRUE( (ERESULT_FAILURE_FALSE == eRc) );
        
        eRc = BitMatrix_Get(pObj, 1, 1);
        TINYTEST_TRUE( (ERESULT_SUCCESS_TRUE == eRc) );
        
        eRc = BitMatrix_Get(pObj, 2, 1);
        TINYTEST_TRUE( (ERESULT_SUCCESS_FALSE == eRc) );
        
        fprintf(stderr, "elems[0] = 0x%08X\n", pObj->pElems[0]);
        TINYTEST_TRUE( (0x00000001 == pObj->pElems[0]) );
        fprintf(stderr, "elems[1] = 0x%08X\n", pObj->pElems[1]);
        TINYTEST_TRUE( (0x00000000 == pObj->pElems[1]) );
        eRc = BitMatrix_Set(pObj, 2, 1, true);
        TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );
        fprintf(stderr, "elems[0] = 0x%08X\n", pObj->pElems[0]);
        TINYTEST_TRUE( (0x00000001 == pObj->pElems[0]) );
        fprintf(stderr, "elems[1] = 0x%08X\n", pObj->pElems[1]);
        TINYTEST_TRUE( (0x00000001 == pObj->pElems[1]) );
        
        eRc = BitMatrix_IsEmpty(pObj);
        TINYTEST_TRUE( (ERESULT_FAILURE_FALSE == eRc) );
        
        eRc = BitMatrix_Get(pObj, 2, 1);
        TINYTEST_TRUE( (ERESULT_SUCCESS_TRUE == eRc) );
        
        obj_Release(pObj);
        pObj = OBJ_NIL;
    }

    fprintf(stderr, "...%s completed.\n\n", pTestName);
    return 1;
}



int             test_BitMatrix_Reflex01(
    const
    char            *pTestName
)
{
    BITMATRIX_DATA  *pObj = OBJ_NIL;
    ERESULT         eRc;
    
    fprintf(stderr, "Performing: %s\n", pTestName);
    
    pObj = BitMatrix_NewWithSizes(11, 11);
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    if (pObj) {
        
        // Set up "BEGINS-DIRECTLY-WITH", fig a, pg 268,
        // in "Compiler Design Theory", Lewis, Rosenkrantz
        // and Stearns, Addison-Wesley, 1976
        eRc = BitMatrix_Set(pObj, 1, 2, true);
        TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );
        eRc = BitMatrix_Set(pObj, 1, 3, true);
        TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );
        eRc = BitMatrix_Set(pObj, 1, 10, true);
        TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );
        eRc = BitMatrix_Set(pObj, 2, 7, true);
        TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );
        eRc = BitMatrix_Set(pObj, 3, 4, true);
        TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );
        eRc = BitMatrix_Set(pObj, 3, 6, true);
        TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );
        eRc = BitMatrix_Set(pObj, 3, 8, true);
        TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );
        eRc = BitMatrix_Set(pObj, 4, 9, true);
        TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );
        eRc = BitMatrix_Set(pObj, 5, 8, true);
        TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );
        eRc = BitMatrix_Set(pObj, 5, 10, true);
        TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );

        eRc = BitMatrix_ReflectiveTransitiveClosure(pObj);
        TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );
        
        eRc = BitMatrix_Get(pObj, 1, 1);
        TINYTEST_TRUE( (ERESULT_SUCCESS_TRUE == eRc) );
        eRc = BitMatrix_Get(pObj, 1, 2);
        TINYTEST_TRUE( (ERESULT_SUCCESS_TRUE == eRc) );
        eRc = BitMatrix_Get(pObj, 1, 3);
        TINYTEST_TRUE( (ERESULT_SUCCESS_TRUE == eRc) );
        eRc = BitMatrix_Get(pObj, 1, 4);
        TINYTEST_TRUE( (ERESULT_SUCCESS_TRUE == eRc) );
        eRc = BitMatrix_Get(pObj, 1, 5);
        TINYTEST_TRUE( (ERESULT_SUCCESS_FALSE == eRc) );
        eRc = BitMatrix_Get(pObj, 1, 6);
        TINYTEST_TRUE( (ERESULT_SUCCESS_TRUE == eRc) );
        eRc = BitMatrix_Get(pObj, 1, 7);
        TINYTEST_TRUE( (ERESULT_SUCCESS_TRUE == eRc) );
        eRc = BitMatrix_Get(pObj, 1, 8);
        TINYTEST_TRUE( (ERESULT_SUCCESS_TRUE == eRc) );
        eRc = BitMatrix_Get(pObj, 1, 9);
        TINYTEST_TRUE( (ERESULT_SUCCESS_TRUE == eRc) );
        eRc = BitMatrix_Get(pObj, 1, 10);
        TINYTEST_TRUE( (ERESULT_SUCCESS_TRUE == eRc) );
        eRc = BitMatrix_Get(pObj, 1, 11);
        TINYTEST_TRUE( (ERESULT_SUCCESS_FALSE == eRc) );
        eRc = BitMatrix_Get(pObj, 2, 1);
        TINYTEST_TRUE( (ERESULT_SUCCESS_FALSE == eRc) );
        eRc = BitMatrix_Get(pObj, 2, 2);
        TINYTEST_TRUE( (ERESULT_SUCCESS_TRUE == eRc) );
        eRc = BitMatrix_Get(pObj, 2, 3);
        TINYTEST_TRUE( (ERESULT_SUCCESS_FALSE == eRc) );
        eRc = BitMatrix_Get(pObj, 2, 4);
        TINYTEST_TRUE( (ERESULT_SUCCESS_FALSE == eRc) );
        eRc = BitMatrix_Get(pObj, 2, 5);
        TINYTEST_TRUE( (ERESULT_SUCCESS_FALSE == eRc) );
        eRc = BitMatrix_Get(pObj, 2, 6);
        TINYTEST_TRUE( (ERESULT_SUCCESS_FALSE == eRc) );
        eRc = BitMatrix_Get(pObj, 2, 7);
        TINYTEST_TRUE( (ERESULT_SUCCESS_TRUE == eRc) );
        eRc = BitMatrix_Get(pObj, 2, 8);
        TINYTEST_TRUE( (ERESULT_SUCCESS_FALSE == eRc) );
        eRc = BitMatrix_Get(pObj, 2, 9);
        TINYTEST_TRUE( (ERESULT_SUCCESS_FALSE == eRc) );
        eRc = BitMatrix_Get(pObj, 2, 10);
        TINYTEST_TRUE( (ERESULT_SUCCESS_FALSE == eRc) );
        eRc = BitMatrix_Get(pObj, 2, 11);
        TINYTEST_TRUE( (ERESULT_SUCCESS_FALSE == eRc) );
        eRc = BitMatrix_Get(pObj, 3, 1);
        TINYTEST_TRUE( (ERESULT_SUCCESS_FALSE == eRc) );
        eRc = BitMatrix_Get(pObj, 3, 2);
        TINYTEST_TRUE( (ERESULT_SUCCESS_FALSE == eRc) );
        eRc = BitMatrix_Get(pObj, 3, 3);
        TINYTEST_TRUE( (ERESULT_SUCCESS_TRUE == eRc) );
        eRc = BitMatrix_Get(pObj, 3, 4);
        TINYTEST_TRUE( (ERESULT_SUCCESS_TRUE == eRc) );
        eRc = BitMatrix_Get(pObj, 3, 5);
        TINYTEST_TRUE( (ERESULT_SUCCESS_FALSE == eRc) );
        eRc = BitMatrix_Get(pObj, 3, 6);
        TINYTEST_TRUE( (ERESULT_SUCCESS_TRUE == eRc) );
        eRc = BitMatrix_Get(pObj, 3, 7);
        TINYTEST_TRUE( (ERESULT_SUCCESS_FALSE == eRc) );
        eRc = BitMatrix_Get(pObj, 3, 8);
        TINYTEST_TRUE( (ERESULT_SUCCESS_TRUE == eRc) );
        eRc = BitMatrix_Get(pObj, 3, 9);
        TINYTEST_TRUE( (ERESULT_SUCCESS_TRUE == eRc) );
        eRc = BitMatrix_Get(pObj, 3, 10);
        TINYTEST_TRUE( (ERESULT_SUCCESS_FALSE == eRc) );
        eRc = BitMatrix_Get(pObj, 3, 11);
        TINYTEST_TRUE( (ERESULT_SUCCESS_FALSE == eRc) );
        eRc = BitMatrix_Get(pObj, 4, 1);
        TINYTEST_TRUE( (ERESULT_SUCCESS_FALSE == eRc) );
        eRc = BitMatrix_Get(pObj, 4, 2);
        TINYTEST_TRUE( (ERESULT_SUCCESS_FALSE == eRc) );
        eRc = BitMatrix_Get(pObj, 4, 3);
        TINYTEST_TRUE( (ERESULT_SUCCESS_FALSE == eRc) );
        eRc = BitMatrix_Get(pObj, 4, 4);
        TINYTEST_TRUE( (ERESULT_SUCCESS_TRUE == eRc) );
        eRc = BitMatrix_Get(pObj, 4, 5);
        TINYTEST_TRUE( (ERESULT_SUCCESS_FALSE == eRc) );
        eRc = BitMatrix_Get(pObj, 4, 6);
        TINYTEST_TRUE( (ERESULT_SUCCESS_FALSE == eRc) );
        eRc = BitMatrix_Get(pObj, 4, 7);
        TINYTEST_TRUE( (ERESULT_SUCCESS_FALSE == eRc) );
        eRc = BitMatrix_Get(pObj, 4, 8);
        TINYTEST_TRUE( (ERESULT_SUCCESS_FALSE == eRc) );
        eRc = BitMatrix_Get(pObj, 4, 9);
        TINYTEST_TRUE( (ERESULT_SUCCESS_TRUE == eRc) );
        eRc = BitMatrix_Get(pObj, 4, 10);
        TINYTEST_TRUE( (ERESULT_SUCCESS_FALSE == eRc) );
        eRc = BitMatrix_Get(pObj, 4, 11);
        TINYTEST_TRUE( (ERESULT_SUCCESS_FALSE == eRc) );
        eRc = BitMatrix_Get(pObj, 5, 1);
        TINYTEST_TRUE( (ERESULT_SUCCESS_FALSE == eRc) );
        eRc = BitMatrix_Get(pObj, 5, 2);
        TINYTEST_TRUE( (ERESULT_SUCCESS_FALSE == eRc) );
        eRc = BitMatrix_Get(pObj, 5, 3);
        TINYTEST_TRUE( (ERESULT_SUCCESS_FALSE == eRc) );
        eRc = BitMatrix_Get(pObj, 5, 4);
        TINYTEST_TRUE( (ERESULT_SUCCESS_FALSE == eRc) );
        eRc = BitMatrix_Get(pObj, 5, 5);
        TINYTEST_TRUE( (ERESULT_SUCCESS_TRUE == eRc) );
        eRc = BitMatrix_Get(pObj, 5, 6);
        TINYTEST_TRUE( (ERESULT_SUCCESS_FALSE == eRc) );
        eRc = BitMatrix_Get(pObj, 5, 7);
        TINYTEST_TRUE( (ERESULT_SUCCESS_FALSE == eRc) );
        eRc = BitMatrix_Get(pObj, 5, 8);
        TINYTEST_TRUE( (ERESULT_SUCCESS_TRUE == eRc) );
        eRc = BitMatrix_Get(pObj, 5, 9);
        TINYTEST_TRUE( (ERESULT_SUCCESS_FALSE == eRc) );
        eRc = BitMatrix_Get(pObj, 5, 10);
        TINYTEST_TRUE( (ERESULT_SUCCESS_TRUE == eRc) );
        eRc = BitMatrix_Get(pObj, 5, 11);
        TINYTEST_TRUE( (ERESULT_SUCCESS_FALSE == eRc) );
        eRc = BitMatrix_Get(pObj, 6, 1);
        TINYTEST_TRUE( (ERESULT_SUCCESS_FALSE == eRc) );
        eRc = BitMatrix_Get(pObj, 6, 2);
        TINYTEST_TRUE( (ERESULT_SUCCESS_FALSE == eRc) );
        eRc = BitMatrix_Get(pObj, 6, 3);
        TINYTEST_TRUE( (ERESULT_SUCCESS_FALSE == eRc) );
        eRc = BitMatrix_Get(pObj, 6, 4);
        TINYTEST_TRUE( (ERESULT_SUCCESS_FALSE == eRc) );
        eRc = BitMatrix_Get(pObj, 6, 5);
        TINYTEST_TRUE( (ERESULT_SUCCESS_FALSE == eRc) );
        eRc = BitMatrix_Get(pObj, 6, 6);
        TINYTEST_TRUE( (ERESULT_SUCCESS_TRUE == eRc) );
        eRc = BitMatrix_Get(pObj, 6, 7);
        TINYTEST_TRUE( (ERESULT_SUCCESS_FALSE == eRc) );
        eRc = BitMatrix_Get(pObj, 6, 8);
        TINYTEST_TRUE( (ERESULT_SUCCESS_FALSE == eRc) );
        eRc = BitMatrix_Get(pObj, 6, 9);
        TINYTEST_TRUE( (ERESULT_SUCCESS_FALSE == eRc) );
        eRc = BitMatrix_Get(pObj, 6, 10);
        TINYTEST_TRUE( (ERESULT_SUCCESS_FALSE == eRc) );
        eRc = BitMatrix_Get(pObj, 6, 11);
        TINYTEST_TRUE( (ERESULT_SUCCESS_FALSE == eRc) );
        eRc = BitMatrix_Get(pObj, 7, 1);
        TINYTEST_TRUE( (ERESULT_SUCCESS_FALSE == eRc) );
        eRc = BitMatrix_Get(pObj, 7, 2);
        TINYTEST_TRUE( (ERESULT_SUCCESS_FALSE == eRc) );
        eRc = BitMatrix_Get(pObj, 7, 3);
        TINYTEST_TRUE( (ERESULT_SUCCESS_FALSE == eRc) );
        eRc = BitMatrix_Get(pObj, 7, 4);
        TINYTEST_TRUE( (ERESULT_SUCCESS_FALSE == eRc) );
        eRc = BitMatrix_Get(pObj, 7, 5);
        TINYTEST_TRUE( (ERESULT_SUCCESS_FALSE == eRc) );
        eRc = BitMatrix_Get(pObj, 7, 6);
        TINYTEST_TRUE( (ERESULT_SUCCESS_FALSE == eRc) );
        eRc = BitMatrix_Get(pObj, 7, 7);
        TINYTEST_TRUE( (ERESULT_SUCCESS_TRUE == eRc) );
        eRc = BitMatrix_Get(pObj, 7, 8);
        TINYTEST_TRUE( (ERESULT_SUCCESS_FALSE == eRc) );
        eRc = BitMatrix_Get(pObj, 7, 9);
        TINYTEST_TRUE( (ERESULT_SUCCESS_FALSE == eRc) );
        eRc = BitMatrix_Get(pObj, 7, 10);
        TINYTEST_TRUE( (ERESULT_SUCCESS_FALSE == eRc) );
        eRc = BitMatrix_Get(pObj, 7, 11);
        TINYTEST_TRUE( (ERESULT_SUCCESS_FALSE == eRc) );
        eRc = BitMatrix_Get(pObj, 8, 1);
        TINYTEST_TRUE( (ERESULT_SUCCESS_FALSE == eRc) );
        eRc = BitMatrix_Get(pObj, 8, 2);
        TINYTEST_TRUE( (ERESULT_SUCCESS_FALSE == eRc) );
        eRc = BitMatrix_Get(pObj, 8, 3);
        TINYTEST_TRUE( (ERESULT_SUCCESS_FALSE == eRc) );
        eRc = BitMatrix_Get(pObj, 8, 4);
        TINYTEST_TRUE( (ERESULT_SUCCESS_FALSE == eRc) );
        eRc = BitMatrix_Get(pObj, 8, 5);
        TINYTEST_TRUE( (ERESULT_SUCCESS_FALSE == eRc) );
        eRc = BitMatrix_Get(pObj, 8, 6);
        TINYTEST_TRUE( (ERESULT_SUCCESS_FALSE == eRc) );
        eRc = BitMatrix_Get(pObj, 8, 7);
        TINYTEST_TRUE( (ERESULT_SUCCESS_FALSE == eRc) );
        eRc = BitMatrix_Get(pObj, 8, 8);
        TINYTEST_TRUE( (ERESULT_SUCCESS_TRUE == eRc) );
        eRc = BitMatrix_Get(pObj, 8, 9);
        TINYTEST_TRUE( (ERESULT_SUCCESS_FALSE == eRc) );
        eRc = BitMatrix_Get(pObj, 8, 10);
        TINYTEST_TRUE( (ERESULT_SUCCESS_FALSE == eRc) );
        eRc = BitMatrix_Get(pObj, 8, 11);
        TINYTEST_TRUE( (ERESULT_SUCCESS_FALSE == eRc) );
        eRc = BitMatrix_Get(pObj, 9, 1);
        TINYTEST_TRUE( (ERESULT_SUCCESS_FALSE == eRc) );
        eRc = BitMatrix_Get(pObj, 9, 2);
        TINYTEST_TRUE( (ERESULT_SUCCESS_FALSE == eRc) );
        eRc = BitMatrix_Get(pObj, 9, 3);
        TINYTEST_TRUE( (ERESULT_SUCCESS_FALSE == eRc) );
        eRc = BitMatrix_Get(pObj, 9, 4);
        TINYTEST_TRUE( (ERESULT_SUCCESS_FALSE == eRc) );
        eRc = BitMatrix_Get(pObj, 9, 5);
        TINYTEST_TRUE( (ERESULT_SUCCESS_FALSE == eRc) );
        eRc = BitMatrix_Get(pObj, 9, 6);
        TINYTEST_TRUE( (ERESULT_SUCCESS_FALSE == eRc) );
        eRc = BitMatrix_Get(pObj, 9, 7);
        TINYTEST_TRUE( (ERESULT_SUCCESS_FALSE == eRc) );
        eRc = BitMatrix_Get(pObj, 9, 8);
        TINYTEST_TRUE( (ERESULT_SUCCESS_FALSE == eRc) );
        eRc = BitMatrix_Get(pObj, 9, 9);
        TINYTEST_TRUE( (ERESULT_SUCCESS_TRUE == eRc) );
        eRc = BitMatrix_Get(pObj, 9, 10);
        TINYTEST_TRUE( (ERESULT_SUCCESS_FALSE == eRc) );
        eRc = BitMatrix_Get(pObj, 9, 11);
        TINYTEST_TRUE( (ERESULT_SUCCESS_FALSE == eRc) );
        eRc = BitMatrix_Get(pObj, 10, 1);
        TINYTEST_TRUE( (ERESULT_SUCCESS_FALSE == eRc) );
        eRc = BitMatrix_Get(pObj, 10, 2);
        TINYTEST_TRUE( (ERESULT_SUCCESS_FALSE == eRc) );
        eRc = BitMatrix_Get(pObj, 10, 3);
        TINYTEST_TRUE( (ERESULT_SUCCESS_FALSE == eRc) );
        eRc = BitMatrix_Get(pObj, 10, 4);
        TINYTEST_TRUE( (ERESULT_SUCCESS_FALSE == eRc) );
        eRc = BitMatrix_Get(pObj, 10, 5);
        TINYTEST_TRUE( (ERESULT_SUCCESS_FALSE == eRc) );
        eRc = BitMatrix_Get(pObj, 10, 6);
        TINYTEST_TRUE( (ERESULT_SUCCESS_FALSE == eRc) );
        eRc = BitMatrix_Get(pObj, 10, 7);
        TINYTEST_TRUE( (ERESULT_SUCCESS_FALSE == eRc) );
        eRc = BitMatrix_Get(pObj, 10, 8);
        TINYTEST_TRUE( (ERESULT_SUCCESS_FALSE == eRc) );
        eRc = BitMatrix_Get(pObj, 10, 9);
        TINYTEST_TRUE( (ERESULT_SUCCESS_FALSE == eRc) );
        eRc = BitMatrix_Get(pObj, 10, 10);
        TINYTEST_TRUE( (ERESULT_SUCCESS_TRUE == eRc) );
        eRc = BitMatrix_Get(pObj, 10, 11);
        TINYTEST_TRUE( (ERESULT_SUCCESS_FALSE == eRc) );
        eRc = BitMatrix_Get(pObj, 11, 1);
        TINYTEST_TRUE( (ERESULT_SUCCESS_FALSE == eRc) );
        eRc = BitMatrix_Get(pObj, 11, 2);
        TINYTEST_TRUE( (ERESULT_SUCCESS_FALSE == eRc) );
        eRc = BitMatrix_Get(pObj, 11, 3);
        TINYTEST_TRUE( (ERESULT_SUCCESS_FALSE == eRc) );
        eRc = BitMatrix_Get(pObj, 11, 4);
        TINYTEST_TRUE( (ERESULT_SUCCESS_FALSE == eRc) );
        eRc = BitMatrix_Get(pObj, 11, 5);
        TINYTEST_TRUE( (ERESULT_SUCCESS_FALSE == eRc) );
        eRc = BitMatrix_Get(pObj, 11, 6);
        TINYTEST_TRUE( (ERESULT_SUCCESS_FALSE == eRc) );
        eRc = BitMatrix_Get(pObj, 11, 7);
        TINYTEST_TRUE( (ERESULT_SUCCESS_FALSE == eRc) );
        eRc = BitMatrix_Get(pObj, 11, 8);
        TINYTEST_TRUE( (ERESULT_SUCCESS_FALSE == eRc) );
        eRc = BitMatrix_Get(pObj, 11, 9);
        TINYTEST_TRUE( (ERESULT_SUCCESS_FALSE == eRc) );
        eRc = BitMatrix_Get(pObj, 11, 10);
        TINYTEST_TRUE( (ERESULT_SUCCESS_FALSE == eRc) );
        eRc = BitMatrix_Get(pObj, 11, 11);
        TINYTEST_TRUE( (ERESULT_SUCCESS_TRUE == eRc) );

        obj_Release(pObj);
        pObj = OBJ_NIL;
    }
    
    fprintf(stderr, "...%s completed.\n\n", pTestName);
    return 1;
}



int             test_BitMatrix_Inflate01(
    const
    char            *pTestName
)
{
    BITMATRIX_DATA  *pObj = OBJ_NIL;
    ERESULT         eRc;
    uint32_t        x;
    //uint32_t        y;
    
    fprintf(stderr, "Performing: %s\n", pTestName);
    
    pObj = BitMatrix_NewWithSizes(1, 1);
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    if (pObj) {
        
        TINYTEST_TRUE( (1 == pObj->cElems) );
        TINYTEST_TRUE( (1 == pObj->xWords) );
        TINYTEST_FALSE( (NULL == pObj->pElems) );
        
        eRc = BitMatrix_IsEmpty(pObj);
        TINYTEST_TRUE( (ERESULT_SUCCESS_TRUE == eRc) );
        
        eRc = BitMatrix_Get(pObj, 1, 1);
        TINYTEST_TRUE( (ERESULT_SUCCESS_FALSE == eRc) );

        TINYTEST_TRUE( (0x00000000 == pObj->pElems[0]) );
        //TINYTEST_TRUE( (0x00000000 == pObj->pElems[1]) );
        eRc = BitMatrix_Set(pObj, 1, 1, true);
        TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );
        fprintf(stderr, "elems[0] = 0x%08X\n", pObj->pElems[0]);
        TINYTEST_TRUE( (0x00000001 == pObj->pElems[0]) );
        //TINYTEST_TRUE( (0x00000000 == pObj->pElems[1]) );

        for (x=1; x<32; ++x) {
            eRc = BitMatrix_InflateX(pObj, 1);
            TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );
            TINYTEST_TRUE( (1 == pObj->cElems) );
            TINYTEST_TRUE( (1 == pObj->xWords) );
            eRc = BitMatrix_Set(pObj, 1, x+1, true);
            TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );
        }
        fprintf(stderr, "elems[0] = 0x%08X\n", pObj->pElems[0]);
        TINYTEST_TRUE( (0xFFFFFFFF == pObj->pElems[0]) );
        //TINYTEST_TRUE( (0x00000000 == pObj->pElems[1]) );

        eRc = BitMatrix_InflateX(pObj, 1);
        TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );
        TINYTEST_TRUE( (2 == pObj->cElems) );
        TINYTEST_TRUE( (2 == pObj->xWords) );

        eRc = BitMatrix_Set(pObj, 1, 33, true);
        TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );
        fprintf(stderr, "elems[0] = 0x%08X\n", pObj->pElems[0]);
        TINYTEST_TRUE( (0xFFFFFFFF == pObj->pElems[0]) );
        fprintf(stderr, "elems[1] = 0x%08X\n", pObj->pElems[1]);
        TINYTEST_TRUE( (0x00000001 == pObj->pElems[1]) );

        obj_Release(pObj);
        pObj = OBJ_NIL;
    }
    
    fprintf(stderr, "...%s completed.\n\n", pTestName);
    return 1;
}



int             test_BitMatrix_Inflate02(
    const
    char            *pTestName
)
{
    BITMATRIX_DATA  *pObj = OBJ_NIL;
    ERESULT         eRc;
    //uint32_t        x;
    uint32_t        y;
    
    fprintf(stderr, "Performing: %s\n", pTestName);
    
    pObj = BitMatrix_NewWithSizes(1, 1);
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    if (pObj) {
        
        TINYTEST_TRUE( (1 == pObj->cElems) );
        TINYTEST_TRUE( (1 == pObj->xWords) );
        TINYTEST_FALSE( (NULL == pObj->pElems) );
        
        eRc = BitMatrix_IsEmpty(pObj);
        TINYTEST_TRUE( (ERESULT_SUCCESS_TRUE == eRc) );
        
        eRc = BitMatrix_Get(pObj, 1, 1);
        TINYTEST_TRUE( (ERESULT_SUCCESS_FALSE == eRc) );
        
        TINYTEST_TRUE( (0x00000000 == pObj->pElems[0]) );
        eRc = BitMatrix_Set(pObj, 1, 1, true);
        TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );
        TINYTEST_TRUE( (0x00000001 == pObj->pElems[0]) );
        
        for (y=1; y<32; ++y) {
            eRc = BitMatrix_InflateY(pObj, 1);
            TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );
            TINYTEST_TRUE( ((y + 1) == pObj->cElems) );
            TINYTEST_TRUE( (1 == pObj->xWords) );
            eRc = BitMatrix_Set(pObj, (y + 1), 1, true);
            TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );
        }
        TINYTEST_TRUE( (0x00000001 == pObj->pElems[0]) );
        TINYTEST_TRUE( (0x00000001 == pObj->pElems[1]) );
        
        eRc = BitMatrix_InflateY(pObj, 1);
        TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );
        TINYTEST_TRUE( (33 == pObj->cElems) );
        TINYTEST_TRUE( (1 == pObj->xWords) );
        
        eRc = BitMatrix_Set(pObj, 33, 1, true);
        TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );
        TINYTEST_TRUE( (0x00000001 == pObj->pElems[0]) );
        TINYTEST_TRUE( (0x00000001 == pObj->pElems[1]) );

        obj_Release(pObj);
        pObj = OBJ_NIL;
    }
    
    fprintf(stderr, "...%s completed.\n\n", pTestName);
    return 1;
}



int             test_BitMatrix_Invert01(
    const
    char            *pTestName
)
{
    BITMATRIX_DATA  *pObj = OBJ_NIL;
    ERESULT         eRc;
    //uint32_t        x;
    //uint32_t        y;
    
    fprintf(stderr, "Performing: %s\n", pTestName);
    
    pObj = BitMatrix_NewWithSizes(2, 1);
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    if (pObj) {
        
        TINYTEST_TRUE( (2 == pObj->cElems) );
        TINYTEST_TRUE( (1 == pObj->xWords) );
        TINYTEST_FALSE( (NULL == pObj->pElems) );
        
        eRc = BitMatrix_IsEmpty(pObj);
        TINYTEST_TRUE( (ERESULT_SUCCESS_TRUE == eRc) );
        
        eRc = BitMatrix_Invert(pObj);
        TINYTEST_TRUE( (ERESULT_SUCCESS_FALSE == eRc) );
        
        TINYTEST_TRUE( (0xFFFFFFFF == pObj->pElems[0]) );
        TINYTEST_TRUE( (0xFFFFFFFF == pObj->pElems[1]) );
        
        obj_Release(pObj);
        pObj = OBJ_NIL;
    }
    
    fprintf(stderr, "...%s completed.\n\n", pTestName);
    return 1;
}



int             test_BitMatrix_Json01(
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
    "{\"objectType\":\"BitMatrix\",\n"
        "\t\"xSize\":4,\n"
        "\t\"xWords\":1,\n"
        "\t\"ySize\":4,\n"
        "\t\"cElems\":4,\n"
        "\t\"Elems\":[\n"
            "\t\t1,\n"
            "\t\t2,\n"
            "\t\t4,\n"
            "\t\t8\n"
        "\t]\n"
    "}\n";
    
    fprintf(stderr, "Performing: %s\n", pTestName);
    
    pObj = BitMatrix_NewIdentity(4);
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    if (pObj) {
        
        TINYTEST_TRUE( (4 == pObj->cElems) );
        TINYTEST_TRUE( (1 == pObj->xWords) );
        TINYTEST_FALSE( (NULL == pObj->pElems) );
        
        pStr = BitMatrix_ToJson(pObj);
        TINYTEST_FALSE( (OBJ_NIL == pStr) );
        fprintf(stderr, "\tjson=\"%s\"\n", AStr_getData(pStr));
        eRc = AStr_CompareA(pStr, pStrA);
        TINYTEST_TRUE( (ERESULT_SUCCESS_EQUAL == eRc) );
        
        pNew = BitMatrix_NewFromJsonString(pStr);
        TINYTEST_FALSE( (OBJ_NIL == pNew) );
        TINYTEST_TRUE( (4 == pNew->xSize) );
        TINYTEST_TRUE( (4 == pNew->ySize) );
        TINYTEST_TRUE( (4 == pNew->cElems) );
        TINYTEST_TRUE( (1 == pNew->xWords) );
        TINYTEST_FALSE( (NULL == pNew->pElems) );
        TINYTEST_TRUE( (1 == pNew->pElems[0]) );
        TINYTEST_TRUE( (2 == pNew->pElems[1]) );
        TINYTEST_TRUE( (4 == pNew->pElems[2]) );
        TINYTEST_TRUE( (8 == pNew->pElems[3]) );
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




TINYTEST_START_SUITE(test_BitMatrix);
    TINYTEST_ADD_TEST(test_BitMatrix_Json01,setUp,tearDown);
    TINYTEST_ADD_TEST(test_BitMatrix_Invert01,setUp,tearDown);
    TINYTEST_ADD_TEST(test_BitMatrix_Inflate02,setUp,tearDown);
    TINYTEST_ADD_TEST(test_BitMatrix_Inflate01,setUp,tearDown);
    TINYTEST_ADD_TEST(test_BitMatrix_Reflex01,setUp,tearDown);
    TINYTEST_ADD_TEST(test_BitMatrix_Test01,setUp,tearDown);
    TINYTEST_ADD_TEST(test_BitMatrix_OpenClose,setUp,tearDown);
TINYTEST_END_SUITE();

TINYTEST_MAIN_SINGLE_SUITE(test_BitMatrix);





