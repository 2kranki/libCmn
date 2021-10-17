/*
 *	Generated 01/12/2019 14:04:41
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
#include    <BPT32Leaf_internal.h>



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






int             test_BPT32Leaf_OpenClose(
    const
    char            *pTestName
)
{
    ERESULT         eRc = ERESULT_SUCCESS;
    BPT32LEAF_DATA        *pObj = OBJ_NIL;
    
    fprintf(stderr, "Performing: %s\n", pTestName);
    
    pObj = BPT32Leaf_Alloc( );
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    pObj = BPT32Leaf_Init( pObj );
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



int             test_BPT32Leaf_Insert01(
    const
    char            *pTestName
)
{
    ERESULT         eRc = ERESULT_SUCCESS;
    BPT32LEAF_DATA    *pObj = OBJ_NIL;
    uint32_t        d;
    uint32_t        k;
    uint32_t        i;
    uint32_t        max;
    ASTR_DATA       *pStr;
    BPT32LEAF_NODE    *pNode;

    fprintf(stderr, "Performing: %s\n", pTestName);
    
    pObj = BPT32Leaf_Alloc( );
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    pObj = BPT32Leaf_Init( pObj );
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    if (pObj) {
        
        eRc = BPT32Leaf_Setup(pObj, 52, 3, 0, true);
        TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );
        TINYTEST_TRUE( (pObj->pBlock) );
        TINYTEST_TRUE( (pObj->pBlock->dataSize == 3) );
        TINYTEST_TRUE( (pObj->pBlock->actualSize == 4) );
        TINYTEST_TRUE( (pObj->pBlock->max == 4) );
        max = pObj->pBlock->max;
        
        pStr = BPT32Leaf_ToDebugString(pObj, 3);
        fprintf(stderr, "\n%s\n\n", AStr_getData(pStr));
        obj_Release(pStr);
        pStr = OBJ_NIL;
        
        for (i=0; i<max; ++i) {
            k = i + 1;
            d = k;
            fprintf(stderr, "\tInserting: %d\n", k);
            eRc = BPT32Leaf_Insert(pObj, k, &d);
            TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );
            pStr = BPT32Leaf_ToDebugString(pObj, 3);
            fprintf(stderr, "\n%s\n\n", AStr_getData(pStr));
            obj_Release(pStr);
            pStr = OBJ_NIL;
        }
        
        pStr = BPT32Leaf_ToDebugString(pObj, 3);
        fprintf(stderr, "\n%s\n\n", AStr_getData(pStr));
        obj_Release(pStr);
        pStr = OBJ_NIL;
        
        fprintf(stderr, "\tDeleting: 3\n");
        eRc = BPT32Leaf_Delete(pObj, 3);
        TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );

        pStr = BPT32Leaf_ToDebugString(pObj, 3);
        fprintf(stderr, "\n%s\n\n", AStr_getData(pStr));
        obj_Release(pStr);
        pStr = OBJ_NIL;
        
        pNode = BPT32Leaf_FindNode(pObj, 3, &i);
        TINYTEST_TRUE( (pNode) );
        TINYTEST_TRUE( (pNode->key == 4) );
        TINYTEST_TRUE( (i == 2) );
        
        fprintf(stderr, "\tDeleting: 10\n");
        eRc = BPT32Leaf_Delete(pObj, 10);
        TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );
        
        pStr = BPT32Leaf_ToDebugString(pObj, 3);
        fprintf(stderr, "\n%s\n\n", AStr_getData(pStr));
        obj_Release(pStr);
        pStr = OBJ_NIL;
        
        fprintf(stderr, "\tDeleting: 1\n");
        eRc = BPT32Leaf_Delete(pObj, 1);
        TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );
        
        pStr = BPT32Leaf_ToDebugString(pObj, 3);
        fprintf(stderr, "\n%s\n\n", AStr_getData(pStr));
        obj_Release(pStr);
        pStr = OBJ_NIL;
        
        obj_Release(pObj);
        pObj = OBJ_NIL;
    }
    
    fprintf(stderr, "...%s completed.\n\n", pTestName);
    return 1;
}



int             test_BPT32Leaf_Insert02(
    const
    char            *pTestName
)
{
    ERESULT         eRc = ERESULT_SUCCESS;
    BPT32LEAF_DATA    *pObj = OBJ_NIL;
    uint32_t        d;
    uint32_t        k;
    uint32_t        i;
    uint32_t        max;
    ASTR_DATA       *pStr;
    BPT32LEAF_NODE    *pNode;
    
    fprintf(stderr, "Performing: %s\n", pTestName);
    
    pObj = BPT32Leaf_Alloc( );
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    pObj = BPT32Leaf_Init( pObj );
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    if (pObj) {
        
        eRc = BPT32Leaf_Setup(pObj, 52, 3, 0, true);
        TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );
        TINYTEST_TRUE( (pObj->pBlock) );
        TINYTEST_TRUE( (pObj->pBlock->dataSize == 3) );
        TINYTEST_TRUE( (pObj->pBlock->actualSize == 4) );
        TINYTEST_TRUE( (pObj->pBlock->max == 4) );
        max = pObj->pBlock->max;
        
        pStr = BPT32Leaf_ToDebugString(pObj, 3);
        fprintf(stderr, "\n%s\n\n", AStr_getData(pStr));
        obj_Release(pStr);
        pStr = OBJ_NIL;
        
        k = 3;
        d = k;
        fprintf(stderr, "\tInserting: %d\n", k);
        eRc = BPT32Leaf_Insert(pObj, k, &d);
        TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );
        pStr = BPT32Leaf_ToDebugString(pObj, 3);
        fprintf(stderr, "\n%s\n\n", AStr_getData(pStr));
        obj_Release(pStr);
        pStr = OBJ_NIL;

        k = 1;
        d = k;
        fprintf(stderr, "\tInserting: %d\n", k);
        eRc = BPT32Leaf_Insert(pObj, k, &d);
        TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );
        pStr = BPT32Leaf_ToDebugString(pObj, 3);
        fprintf(stderr, "\n%s\n\n", AStr_getData(pStr));
        obj_Release(pStr);
        pStr = OBJ_NIL;
        
        k = 4;
        d = k;
        fprintf(stderr, "\tInserting: %d\n", k);
        eRc = BPT32Leaf_Insert(pObj, k, &d);
        TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );
        pStr = BPT32Leaf_ToDebugString(pObj, 3);
        fprintf(stderr, "\n%s\n\n", AStr_getData(pStr));
        obj_Release(pStr);
        pStr = OBJ_NIL;
        
        k = 2;
        d = k;
        fprintf(stderr, "\tInserting: %d\n", k);
        eRc = BPT32Leaf_Insert(pObj, k, &d);
        TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );
        pStr = BPT32Leaf_ToDebugString(pObj, 3);
        fprintf(stderr, "\n%s\n\n", AStr_getData(pStr));
        obj_Release(pStr);
        pStr = OBJ_NIL;
        
        pStr = BPT32Leaf_ToDebugString(pObj, 3);
        fprintf(stderr, "\n%s\n\n", AStr_getData(pStr));
        obj_Release(pStr);
        pStr = OBJ_NIL;
        
        fprintf(stderr, "\tDeleting: 3\n");
        eRc = BPT32Leaf_Delete(pObj, 3);
        TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );
        
        pStr = BPT32Leaf_ToDebugString(pObj, 3);
        fprintf(stderr, "\n%s\n\n", AStr_getData(pStr));
        obj_Release(pStr);
        pStr = OBJ_NIL;
        
        pNode = BPT32Leaf_FindNode(pObj, 3, &i);
        TINYTEST_TRUE( (pNode) );
        TINYTEST_TRUE( (pNode->key == 4) );
        TINYTEST_TRUE( (i == 2) );
        
        fprintf(stderr, "\tDeleting: 10\n");
        eRc = BPT32Leaf_Delete(pObj, 10);
        TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );
        
        pStr = BPT32Leaf_ToDebugString(pObj, 3);
        fprintf(stderr, "\n%s\n\n", AStr_getData(pStr));
        obj_Release(pStr);
        pStr = OBJ_NIL;
        
        fprintf(stderr, "\tDeleting: 1\n");
        eRc = BPT32Leaf_Delete(pObj, 1);
        TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );
        
        pStr = BPT32Leaf_ToDebugString(pObj, 3);
        fprintf(stderr, "\n%s\n\n", AStr_getData(pStr));
        obj_Release(pStr);
        pStr = OBJ_NIL;
        
        obj_Release(pObj);
        pObj = OBJ_NIL;
    }
    
    fprintf(stderr, "...%s completed.\n\n", pTestName);
    return 1;
}



int             test_BPT32Leaf_Insert03(
    const
    char            *pTestName
)
{
    ERESULT         eRc = ERESULT_SUCCESS;
    BPT32LEAF_DATA    *pObj = OBJ_NIL;
    uint32_t        d;
    uint32_t        k;
    //uint32_t        i;
    uint32_t        max;
    ASTR_DATA       *pStr;
    BPT32LEAF_NODE    *pNode;
    BPT32LEAF_DATA    *pNew = OBJ_NIL;

    fprintf(stderr, "Performing: %s\n", pTestName);
    
    pObj = BPT32Leaf_Alloc( );
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    pObj = BPT32Leaf_Init( pObj );
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    if (pObj) {
        
        obj_TraceSet(pObj, true);
        
        eRc = BPT32Leaf_Setup(pObj, 52, 3, 0, true);
        TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );
        TINYTEST_TRUE( (pObj->pBlock) );
        TINYTEST_TRUE( (pObj->pBlock->dataSize == 3) );
        TINYTEST_TRUE( (pObj->pBlock->actualSize == 4) );
        TINYTEST_TRUE( (pObj->pBlock->max == 4) );
        max = pObj->pBlock->max;
        
        pStr = BPT32Leaf_ToDebugString(pObj, 3);
        fprintf(stderr, "\n%s\n\n", AStr_getData(pStr));
        obj_Release(pStr);
        pStr = OBJ_NIL;
        
        k = 3;
        d = k;
        fprintf(stderr, "\tInserting: %d\n", k);
        eRc = BPT32Leaf_Insert(pObj, k, &d);
        TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );
        pStr = BPT32Leaf_ToDebugString(pObj, 3);
        fprintf(stderr, "\n%s\n\n", AStr_getData(pStr));
        obj_Release(pStr);
        pStr = OBJ_NIL;
        TINYTEST_TRUE( (OBJ_NIL == pNew) );

        k = 1;
        d = k;
        fprintf(stderr, "\tInserting: %d\n", k);
        eRc = BPT32Leaf_Insert(pObj, k, &d);
        TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );
        pStr = BPT32Leaf_ToDebugString(pObj, 3);
        fprintf(stderr, "\n%s\n\n", AStr_getData(pStr));
        obj_Release(pStr);
        pStr = OBJ_NIL;
        TINYTEST_TRUE( (OBJ_NIL == pNew) );

        k = 4;
        d = k;
        fprintf(stderr, "\tInserting: %d\n", k);
        eRc = BPT32Leaf_Insert(pObj, k, &d);
        TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );
        pStr = BPT32Leaf_ToDebugString(pObj, 3);
        fprintf(stderr, "\n%s\n\n", AStr_getData(pStr));
        obj_Release(pStr);
        pStr = OBJ_NIL;
        TINYTEST_TRUE( (OBJ_NIL == pNew) );

        k = 5;
        d = k;
        fprintf(stderr, "\tInserting: %d\n", k);
        eRc = BPT32Leaf_Insert(pObj, k, &d);
        TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );
        pStr = BPT32Leaf_ToDebugString(pObj, 3);
        fprintf(stderr, "\n%s\n\n", AStr_getData(pStr));
        obj_Release(pStr);
        pStr = OBJ_NIL;
        TINYTEST_TRUE( (OBJ_NIL == pNew) );

        // We have to simulate the manager to have split()
        // work properly since it relies on it heavily.
#ifdef SIMULATED_MGR
        k = 2;
        d = k;
        fprintf(stderr, "\tInserting: %d\n", k);
        eRc = BPT32Leaf_Insert(pObj, k, &d);
        TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );
        TINYTEST_TRUE( (pObj->pBlock->used == 3) );
        pStr = BPT32Leaf_ToDebugString(pObj, 3);
        fprintf(stderr, "\n%s\n\n", AStr_getData(pStr));
        obj_Release(pStr);
        pStr = OBJ_NIL;
        pNode = BPT32Leaf_Index2Node(pObj, 0);
        TINYTEST_TRUE( (pNode->key == 1) );
        pNode = BPT32Leaf_Index2Node(pObj, 1);
        TINYTEST_TRUE( (pNode->key == 2) );
        pNode = BPT32Leaf_Index2Node(pObj, 2);
        TINYTEST_TRUE( (pNode->key == 3) );
        TINYTEST_TRUE( (pNew) );
        TINYTEST_TRUE( (pNew->pBlock->used == 2) );
        pStr = BPT32Leaf_ToDebugString(pNew, 3);
        fprintf(stderr, "\n%s\n\n", AStr_getData(pStr));
        obj_Release(pStr);
        pStr = OBJ_NIL;
        pNode = BPT32Leaf_Index2Node(pNew, 0);
        TINYTEST_TRUE( (pNode->key == 4) );
        pNode = BPT32Leaf_Index2Node(pNew, 1);
        TINYTEST_TRUE( (pNode->key == 5) );
        obj_Release(pNew);
        pNew = OBJ_NIL;
#endif

        obj_Release(pObj);
        pObj = OBJ_NIL;
    }
    
    fprintf(stderr, "...%s completed.\n\n", pTestName);
    return 1;
}




TINYTEST_START_SUITE(test_BPT32Leaf);
    TINYTEST_ADD_TEST(test_BPT32Leaf_Insert03,setUp,tearDown);
    TINYTEST_ADD_TEST(test_BPT32Leaf_Insert02,setUp,tearDown);
    TINYTEST_ADD_TEST(test_BPT32Leaf_Insert01,setUp,tearDown);
    TINYTEST_ADD_TEST(test_BPT32Leaf_OpenClose,setUp,tearDown);
TINYTEST_END_SUITE();

TINYTEST_MAIN_SINGLE_SUITE(test_BPT32Leaf);





