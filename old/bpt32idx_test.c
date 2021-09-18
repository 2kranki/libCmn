/*
 *	Generated 01/12/2019 14:04:35
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
#include    <bpt32idx_internal.h>



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






int             test_bpt32idx_OpenClose(
    const
    char            *pTestName
)
{
    ERESULT         eRc = ERESULT_SUCCESS;
    BPT32IDX_DATA	    *pObj = OBJ_NIL;
   
    fprintf(stderr, "Performing: %s\n", pTestName);

    pObj = bpt32idx_New( );
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    if (pObj) {

        //obj_TraceSet(pObj, true);       
        
        // Test something.
        TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );

        obj_Release(pObj);
        pObj = OBJ_NIL;
    }

    fprintf(stderr, "...%s completed.\n\n", pTestName);
    return 1;
}



int             test_bpt32idx_Insert01(
    const
    char            *pTestName
)
{
    ERESULT         eRc = ERESULT_SUCCESS;
    BPT32IDX_DATA   *pObj = OBJ_NIL;
    uint32_t        d;
    uint32_t        k;
    uint32_t        i;
    uint32_t        max;
    ASTR_DATA       *pStr;
    BPT32IDX_NODE   *pNode;
    BPT32IDX_DATA   *pNew = OBJ_NIL;

    fprintf(stderr, "Performing: %s\n", pTestName);
    
    pObj = bpt32idx_Alloc( );
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    pObj = bpt32idx_Init( pObj );
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    if (pObj) {
        
        eRc = bpt32idx_Setup(pObj, 48, 3, true);
        TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );
        TINYTEST_TRUE( (pObj->pBlock) );
        TINYTEST_TRUE( (pObj->pBlock->max == 4) );
        max = pObj->pBlock->max;
        
        pStr = bpt32idx_ToDebugString(pObj, 3);
        fprintf(stderr, "\n%s\n\n", AStr_getData(pStr));
        obj_Release(pStr);
        pStr = OBJ_NIL;
        
        for (i=0; i<pObj->pBlock->max; ++i) {
            k = i + 1;
            d = i;
            fprintf(stderr, "\tInserting: %d\n", k);
            eRc = bpt32idx_Insert(pObj, k, d, &pNew);
            TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );
            pStr = bpt32idx_ToDebugString(pObj, 3);
            fprintf(stderr, "\n%s\n\n", AStr_getData(pStr));
            obj_Release(pStr);
            pStr = OBJ_NIL;
            TINYTEST_TRUE( (OBJ_NIL == pNew) );
        }
        
        pStr = bpt32idx_ToDebugString(pObj, 3);
        fprintf(stderr, "\n%s\n\n", AStr_getData(pStr));
        obj_Release(pStr);
        pStr = OBJ_NIL;
        
#ifdef NOT_NEEDED_YET
        for (i=1; i<pObj->pBlock->max; ++i) {
            k = i + 1;
            d = i;
            fprintf(stderr, "\tInserting: %d\n", k);
            eRc = bpt32idx_Insert(pObj, k, d);
            TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );
            pStr = bpt32idx_ToDebugString(pObj, 3);
            fprintf(stderr, "\n%s\n\n", AStr_getData(pStr));
            obj_Release(pStr);
            pStr = OBJ_NIL;
        }
#endif
        
        fprintf(stderr, "\tDeleting: 3\n");
        eRc = bpt32idx_Delete(pObj, 3);
        TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );
        
        pStr = bpt32idx_ToDebugString(pObj, 3);
        fprintf(stderr, "\n%s\n\n", AStr_getData(pStr));
        obj_Release(pStr);
        pStr = OBJ_NIL;
        
        pNode = bpt32idx_FindNode(pObj, 3, &i);
        TINYTEST_TRUE( (pNode) );
        TINYTEST_TRUE( (pNode->key == 4) );
        TINYTEST_TRUE( (i == 2) );

        fprintf(stderr, "\tDeleting: %d\n", max);
        eRc = bpt32idx_Delete(pObj, max);
        TINYTEST_TRUE( (!ERESULT_FAILED(eRc)) );
        
        pStr = bpt32idx_ToDebugString(pObj, 3);
        fprintf(stderr, "\n%s\n\n", AStr_getData(pStr));
        obj_Release(pStr);
        pStr = OBJ_NIL;
        
        fprintf(stderr, "\tDeleting: 1\n");
        eRc = bpt32idx_Delete(pObj, 1);
        TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );
        
        pStr = bpt32idx_ToDebugString(pObj, 3);
        fprintf(stderr, "\n%s\n\n", AStr_getData(pStr));
        obj_Release(pStr);
        pStr = OBJ_NIL;
        
        obj_Release(pObj);
        pObj = OBJ_NIL;
    }
    
    fprintf(stderr, "...%s completed.\n\n", pTestName);
    return 1;
}



int             test_bpt32idx_Insert02(
    const
    char            *pTestName
)
{
    ERESULT         eRc = ERESULT_SUCCESS;
    BPT32IDX_DATA   *pObj = OBJ_NIL;
    uint32_t        d;
    uint32_t        k;
    uint32_t        i;
    uint32_t        max;
    ASTR_DATA       *pStr;
    BPT32IDX_NODE   *pNode;
    BPT32IDX_DATA   *pNew = OBJ_NIL;

    fprintf(stderr, "Performing: %s\n", pTestName);
    
    pObj = bpt32idx_Alloc( );
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    pObj = bpt32idx_Init( pObj );
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    if (pObj) {
        
        eRc = bpt32idx_Setup(pObj, 48, 3, true);
        TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );
        TINYTEST_TRUE( (pObj->pBlock) );
        TINYTEST_TRUE( (pObj->pBlock->max == 4) );
        max = pObj->pBlock->max;
        
        pStr = bpt32idx_ToDebugString(pObj, 3);
        fprintf(stderr, "\n%s\n\n", AStr_getData(pStr));
        obj_Release(pStr);
        pStr = OBJ_NIL;
        
        k = 3;
        d = k;
        fprintf(stderr, "\tInserting: %d\n", k);
        eRc = bpt32idx_Insert(pObj, k, d, &pNew);
        TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );
        pStr = bpt32idx_ToDebugString(pObj, 3);
        fprintf(stderr, "\n%s\n\n", AStr_getData(pStr));
        obj_Release(pStr);
        pStr = OBJ_NIL;
        TINYTEST_TRUE( (OBJ_NIL == pNew) );

        k = 1;
        d = k;
        fprintf(stderr, "\tInserting: %d\n", k);
        eRc = bpt32idx_Insert(pObj, k, d, &pNew);
        TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );
        pStr = bpt32idx_ToDebugString(pObj, 3);
        fprintf(stderr, "\n%s\n\n", AStr_getData(pStr));
        obj_Release(pStr);
        pStr = OBJ_NIL;
        TINYTEST_TRUE( (OBJ_NIL == pNew) );

        k = 4;
        d = k;
        fprintf(stderr, "\tInserting: %d\n", k);
        eRc = bpt32idx_Insert(pObj, k, d, &pNew);
        TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );
        pStr = bpt32idx_ToDebugString(pObj, 3);
        fprintf(stderr, "\n%s\n\n", AStr_getData(pStr));
        obj_Release(pStr);
        pStr = OBJ_NIL;
        TINYTEST_TRUE( (OBJ_NIL == pNew) );

        k = 2;
        d = k;
        fprintf(stderr, "\tInserting: %d\n", k);
        eRc = bpt32idx_Insert(pObj, k, d, &pNew);
        TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );
        pStr = bpt32idx_ToDebugString(pObj, 3);
        fprintf(stderr, "\n%s\n\n", AStr_getData(pStr));
        obj_Release(pStr);
        pStr = OBJ_NIL;
        TINYTEST_TRUE( (OBJ_NIL == pNew) );

        fprintf(stderr, "\tDeleting: 3\n");
        eRc = bpt32idx_Delete(pObj, 3);
        TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );
        
        pStr = bpt32idx_ToDebugString(pObj, 3);
        fprintf(stderr, "\n%s\n\n", AStr_getData(pStr));
        obj_Release(pStr);
        pStr = OBJ_NIL;
        
        pNode = bpt32idx_FindNode(pObj, 3, &i);
        TINYTEST_TRUE( (pNode) );
        TINYTEST_TRUE( (pNode->key == 4) );
        TINYTEST_TRUE( (i == 2) );
        
        fprintf(stderr, "\tDeleting: %d\n", max);
        eRc = bpt32idx_Delete(pObj, max);
        TINYTEST_TRUE( (!ERESULT_FAILED(eRc)) );
        
        pStr = bpt32idx_ToDebugString(pObj, 3);
        fprintf(stderr, "\n%s\n\n", AStr_getData(pStr));
        obj_Release(pStr);
        pStr = OBJ_NIL;
        
        fprintf(stderr, "\tDeleting: 1\n");
        eRc = bpt32idx_Delete(pObj, 1);
        TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );
        
        pStr = bpt32idx_ToDebugString(pObj, 3);
        fprintf(stderr, "\n%s\n\n", AStr_getData(pStr));
        obj_Release(pStr);
        pStr = OBJ_NIL;
        
        obj_Release(pObj);
        pObj = OBJ_NIL;
    }
    
    fprintf(stderr, "...%s completed.\n\n", pTestName);
    return 1;
}



int             test_bpt32idx_Insert03(
    const
    char            *pTestName
)
{
    ERESULT         eRc = ERESULT_SUCCESS;
    BPT32IDX_DATA   *pObj = OBJ_NIL;
    BPT32IDX_DATA   *pNew = OBJ_NIL;
    uint32_t        d;
    uint32_t        k;
    uint32_t        i;
    uint32_t        max;
    ASTR_DATA       *pStr;
    BPT32IDX_NODE   *pNode;
    
    fprintf(stderr, "Performing: %s\n", pTestName);
    
    pObj = bpt32idx_Alloc( );
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    pObj = bpt32idx_Init( pObj );
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    if (pObj) {
        
        eRc = bpt32idx_Setup(pObj, 48, 3, true);
        TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );
        TINYTEST_TRUE( (pObj->pBlock) );
        TINYTEST_TRUE( (pObj->pBlock->max == 4) );
        max = pObj->pBlock->max;
        
        pStr = bpt32idx_ToDebugString(pObj, 3);
        fprintf(stderr, "\n%s\n\n", AStr_getData(pStr));
        obj_Release(pStr);
        pStr = OBJ_NIL;
        
        k = 3;
        d = k;
        fprintf(stderr, "\tInserting: %d\n", k);
        eRc = bpt32idx_Insert(pObj, k, d, &pNew);
        TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );
        pStr = bpt32idx_ToDebugString(pObj, 3);
        fprintf(stderr, "\n%s\n\n", AStr_getData(pStr));
        obj_Release(pStr);
        pStr = OBJ_NIL;
        TINYTEST_TRUE( (OBJ_NIL == pNew) );

        k = 1;
        d = k;
        fprintf(stderr, "\tInserting: %d\n", k);
        eRc = bpt32idx_Insert(pObj, k, d, &pNew);
        TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );
        pStr = bpt32idx_ToDebugString(pObj, 3);
        fprintf(stderr, "\n%s\n\n", AStr_getData(pStr));
        obj_Release(pStr);
        pStr = OBJ_NIL;
        TINYTEST_TRUE( (OBJ_NIL == pNew) );

        k = 4;
        d = k;
        fprintf(stderr, "\tInserting: %d\n", k);
        eRc = bpt32idx_Insert(pObj, k, d, &pNew);
        TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );
        pStr = bpt32idx_ToDebugString(pObj, 3);
        fprintf(stderr, "\n%s\n\n", AStr_getData(pStr));
        obj_Release(pStr);
        pStr = OBJ_NIL;
        TINYTEST_TRUE( (OBJ_NIL == pNew) );

        k = 5;
        d = k;
        fprintf(stderr, "\tInserting: %d\n", k);
        eRc = bpt32idx_Insert(pObj, k, d, &pNew);
        TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );
        pStr = bpt32idx_ToDebugString(pObj, 3);
        fprintf(stderr, "\n%s\n\n", AStr_getData(pStr));
        obj_Release(pStr);
        pStr = OBJ_NIL;
        TINYTEST_TRUE( (OBJ_NIL == pNew) );

        // Cause a split with new record in lower half
        k = 2;
        d = k;
        fprintf(stderr, "\tInserting: %d\n", k);
        eRc = bpt32idx_Insert(pObj, k, d, &pNew);
        TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );
        pStr = bpt32idx_ToDebugString(pObj, 3);
        fprintf(stderr, "\n%s\n\n", AStr_getData(pStr));
        obj_Release(pStr);
        pStr = OBJ_NIL;
        TINYTEST_TRUE( (pNew) );
        pStr = bpt32idx_ToDebugString(pNew, 3);
        fprintf(stderr, "\n%s\n\n", AStr_getData(pStr));
        obj_Release(pStr);
        pStr = OBJ_NIL;
        obj_Release(pNew);
        pNew = OBJ_NIL;

        obj_Release(pObj);
        pObj = OBJ_NIL;
    }
    
    fprintf(stderr, "...%s completed.\n\n", pTestName);
    return 1;
}




TINYTEST_START_SUITE(test_bpt32idx);
    TINYTEST_ADD_TEST(test_bpt32idx_Insert03,setUp,tearDown);
    TINYTEST_ADD_TEST(test_bpt32idx_Insert02,setUp,tearDown);
    TINYTEST_ADD_TEST(test_bpt32idx_Insert01,setUp,tearDown);
    TINYTEST_ADD_TEST(test_bpt32idx_OpenClose,setUp,tearDown);
TINYTEST_END_SUITE();

TINYTEST_MAIN_SINGLE_SUITE(test_bpt32idx);





