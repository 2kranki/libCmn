/*
 *	Generated 01/12/2019 14:04:44
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
#include    <lru.h>
#include    <memFile.h>
#include    <memrrds.h>
#include    <trace.h>
#include    <bpt32_internal.h>



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






int             test_bpt32_OpenClose(
    const
    char            *pTestName
)
{
    ERESULT         eRc = ERESULT_SUCCESS;
    BPT32_DATA	    *pObj = OBJ_NIL;
   
    fprintf(stderr, "Performing: %s\n", pTestName);

    pObj = bpt32_Alloc( );
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    pObj = bpt32_Init( pObj );
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



int             test_bpt32_Block01(
    const
    char            *pTestName
)
{
    ERESULT         eRc = ERESULT_SUCCESS;
    BPT32_DATA      *pObj = OBJ_NIL;
    uint8_t         blk1[64];
    BPT32_BLOCK     *pBlock1 = (BPT32_BLOCK *)blk1;
    uint8_t         blk2[64];
    BPT32_BLOCK     *pBlock2 = (BPT32_BLOCK *)blk2;
    uint32_t        d = 0;
    uint32_t        i = 0;
    uint32_t        index = 0;
    BPT32_NODE      *pNode = NULL;
    uint16_t        dataSize = 7;

    fprintf(stderr, "Performing: %s\n", pTestName);
    
    pObj = bpt32_Alloc( );
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    pObj = bpt32_Init( pObj );
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    if (pObj) {
        
        eRc =   bpt32_BlockInit(
                            pBlock1,
                            OBJ_IDENT_BPT32LF,  // block type
                            sizeof(blk1),       // block size
                            dataSize,           // data size
                            22                  // block index
                );
        TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );
        TINYTEST_TRUE( (OBJ_IDENT_BPT32LF == pBlock1->blockType) );
        TINYTEST_TRUE( (8 == pBlock1->actualSize) );
        TINYTEST_TRUE( (22 == pBlock1->index) );
        TINYTEST_TRUE( (3 == pBlock1->max) );

        eRc =   bpt32_BlockInit(
                                pBlock2,
                                OBJ_IDENT_BPT32IDX, // block type
                                sizeof(blk2),       // block size
                                8,                  // data size
                                23                  // block index
                );
        TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );
        TINYTEST_TRUE( (OBJ_IDENT_BPT32IDX == pBlock2->blockType) );
        TINYTEST_TRUE( (4 == pBlock2->actualSize) );
        TINYTEST_TRUE( (23 == pBlock2->index) );
        TINYTEST_TRUE( (5 == pBlock2->max) );

        for (i=0; i<pBlock1->max; ++i) {
            d = i + 10;
            eRc = bpt32_NodeInsert(pObj, pBlock1, d, &d);
            TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );
            TINYTEST_TRUE( ((i + 1) == pBlock1->used) );
        }

        for (i=0; i<pBlock1->max; ++i) {
            d = i + 10;
            pNode = bpt32_NodeFind(pBlock1, d, &index);
            TINYTEST_FALSE( (NULL == pNode) );
            TINYTEST_TRUE( (d == pNode->key) );
        }
        
        obj_Release(pObj);
        pObj = OBJ_NIL;
    }
    
    fprintf(stderr, "...%s completed.\n\n", pTestName);
    return 1;
}



int             test_bpt32_Block02(
    const
    char            *pTestName
)
{
    ERESULT         eRc = ERESULT_SUCCESS;
    BPT32_DATA      *pObj = OBJ_NIL;
    uint8_t         blk1[64];
    BPT32_BLOCK     *pBlock1 = (BPT32_BLOCK *)blk1;
    uint8_t         blk2[64];
    BPT32_BLOCK     *pBlock2 = (BPT32_BLOCK *)blk2;
    uint32_t        d = 0;
    uint32_t        i = 0;
    uint32_t        index = 0;
    BPT32_NODE      *pNode = NULL;
    
    fprintf(stderr, "Performing: %s\n", pTestName);
    
    pObj = bpt32_Alloc( );
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    pObj = bpt32_Init( pObj );
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    if (pObj) {
        
        eRc =   bpt32_BlockInit(
                                pBlock1,
                                OBJ_IDENT_BPT32LF,  // block type
                                sizeof(blk1),       // block size
                                7,                  // data size
                                22                  // block index
                );
        TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );
        TINYTEST_TRUE( (OBJ_IDENT_BPT32LF == pBlock1->blockType) );
        TINYTEST_TRUE( (8 == pBlock1->actualSize) );
        TINYTEST_TRUE( (22 == pBlock1->index) );
        TINYTEST_TRUE( (3 == pBlock1->max) );
        
        eRc =   bpt32_BlockInit(
                                pBlock2,
                                OBJ_IDENT_BPT32IDX, // block type
                                sizeof(blk2),       // block size
                                8,                  // data size
                                23                  // block index
                                );
        TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );
        TINYTEST_TRUE( (OBJ_IDENT_BPT32IDX == pBlock2->blockType) );
        TINYTEST_TRUE( (4 == pBlock2->actualSize) );
        TINYTEST_TRUE( (23 == pBlock2->index) );
        TINYTEST_TRUE( (5 == pBlock2->max) );
        
        // Force insertions before ending key.
        for (i=pBlock1->max; i; --i) {
            d = ((i - 1) << 1) + 10;
            fprintf(stderr, "\tAdding %d to block1\n", d);
            eRc = bpt32_NodeInsert(pObj, pBlock1, d, &d);
            TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );
            //TINYTEST_TRUE( ((pBlock1->max - i - 1) == pBlock1->used) );
        }
        
        for (i=0; i<pBlock1->max; ++i) {
            d = (i << 1) + 10;
            fprintf(stderr, "\tFinding %d in block1\n", d);
            pNode = bpt32_NodeFind(pBlock1, d, &index);
            TINYTEST_FALSE( (NULL == pNode) );
            TINYTEST_TRUE( (d == pNode->key) );
            pNode = bpt32_Index2Node(pBlock1, i);
            TINYTEST_FALSE( (NULL == pNode) );
            TINYTEST_TRUE( (d == pNode->key) );
        }
        
        d = (pBlock1->max << 1) + 10;
        index = 0;
        fprintf(stderr, "\tFinding %d in block1\n", d);
        pNode = bpt32_NodeFind(pBlock1, d, &index);
        fprintf(stderr, "\t\tFound: index=%d %d\n", index, pNode->key);
        TINYTEST_FALSE( (NULL == pNode) );
        TINYTEST_TRUE( ((((pBlock1->max - 1) << 1) + 10) == pNode->key) );

        d = (0 << 1) + 10 + 1;
        index = 0;
        fprintf(stderr, "\tFinding %d in block1\n", d);
        pNode = bpt32_NodeFind(pBlock1, d, &index);
        fprintf(stderr, "\t\tFound: index=%d %d\n", index, pNode->key);
        TINYTEST_FALSE( (NULL == pNode) );
        TINYTEST_TRUE( ((((2 - 1) << 1) + 10) == pNode->key) );

        obj_Release(pObj);
        pObj = OBJ_NIL;
    }
    
    fprintf(stderr, "...%s completed.\n\n", pTestName);
    return 1;
}



int             test_bpt32_Block03(
    const
    char            *pTestName
)
{
    ERESULT         eRc = ERESULT_SUCCESS;
    BPT32_DATA      *pObj = OBJ_NIL;
    uint8_t         blk1[256];
    BPT32_BLOCK     *pBlock1 = (BPT32_BLOCK *)blk1;
    uint8_t         blk2[64];
    BPT32_BLOCK     *pBlock2 = (BPT32_BLOCK *)blk2;
    uint32_t        d = 0;
    uint32_t        i = 0;
    uint32_t        index = 0;
    BPT32_NODE      *pNode = NULL;
    
    fprintf(stderr, "Performing: %s\n", pTestName);
    
    pObj = bpt32_Alloc( );
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    pObj = bpt32_Init( pObj );
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    if (pObj) {
        
        eRc =   bpt32_BlockInit(
                                pBlock1,
                                OBJ_IDENT_BPT32LF,  // block type
                                sizeof(blk1),       // block size
                                7,                  // data size
                                22                  // block index
                                );
        TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );
        TINYTEST_TRUE( (OBJ_IDENT_BPT32LF == pBlock1->blockType) );
        TINYTEST_TRUE( (8 == pBlock1->actualSize) );
        TINYTEST_TRUE( (22 == pBlock1->index) );
        TINYTEST_TRUE( (19 == pBlock1->max) );
        
        eRc =   bpt32_BlockInit(
                                pBlock2,
                                OBJ_IDENT_BPT32IDX, // block type
                                sizeof(blk2),       // block size
                                8,                  // data size
                                23                  // block index
                                );
        TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );
        TINYTEST_TRUE( (OBJ_IDENT_BPT32IDX == pBlock2->blockType) );
        TINYTEST_TRUE( (4 == pBlock2->actualSize) );
        TINYTEST_TRUE( (23 == pBlock2->index) );
        TINYTEST_TRUE( (5 == pBlock2->max) );
        
        // Force insertions before ending key.
        for (i=pBlock1->max; i; --i) {
            d = ((i - 1) << 1) + 10;
            fprintf(stderr, "\tAdding %d to block1\n", d);
            eRc = bpt32_NodeInsert(pObj, pBlock1, d, &d);
            TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );
            //TINYTEST_TRUE( ((pBlock1->max - i - 1) == pBlock1->used) );
        }
        
        for (i=0; i<pBlock1->max; ++i) {
            d = (i << 1) + 10;
            fprintf(stderr, "\tFinding %d in block1\n", d);
            pNode = bpt32_NodeFind(pBlock1, d, &index);
            TINYTEST_FALSE( (NULL == pNode) );
            TINYTEST_TRUE( (d == pNode->key) );
            pNode = bpt32_Index2Node(pBlock1, i);
            TINYTEST_FALSE( (NULL == pNode) );
            TINYTEST_TRUE( (d == pNode->key) );
        }
        
        d = (pBlock1->max << 1) + 10;
        index = 0;
        fprintf(stderr, "\tFinding %d in block1\n", d);
        pNode = bpt32_NodeFind(pBlock1, d, &index);
        fprintf(stderr, "\t\tFound: index=%d %d\n", index, pNode->key);
        TINYTEST_FALSE( (NULL == pNode) );
        TINYTEST_TRUE( ((((pBlock1->max - 1) << 1) + 10) == pNode->key) );
        
        d = (0 << 1) + 10 + 1;
        index = 0;
        fprintf(stderr, "\tFinding %d in block1\n", d);
        pNode = bpt32_NodeFind(pBlock1, d, &index);
        fprintf(stderr, "\t\tFound: index=%d %d\n", index, pNode->key);
        TINYTEST_FALSE( (NULL == pNode) );
        TINYTEST_TRUE( ((((2 - 1) << 1) + 10) == pNode->key) );
        
        obj_Release(pObj);
        pObj = OBJ_NIL;
    }
    
    fprintf(stderr, "...%s completed.\n\n", pTestName);
    return 1;
}



int             test_bpt32_Write01(
    const
    char            *pTestName
)
{
    ERESULT         eRc = ERESULT_SUCCESS;
    BPT32_DATA      *pObj = OBJ_NIL;
    //LRU_DATA        *pLRU = OBJ_NIL;
    PATH_DATA       *pPath = OBJ_NIL;
    //ASTR_DATA       *pStr = OBJ_NIL;
    const
    char            *pPathA = "/tmp/testBPT32.temp.txt";
    uint32_t        data1 = 0x5A5A5A5A;             // Set an eye-catcher
    uint32_t        data2 = 0;
    //uint32_t        index1 = 0;
    //uint32_t        index2 = 0;
    //uint32_t        i = 0;
    uint32_t        blockSize = 64;

    fprintf(stderr, "Performing: %s\n", pTestName);
    
    pPath = path_NewA(pPathA);
    TINYTEST_FALSE( (OBJ_NIL == pPath) );
    fprintf(stderr, "\tPath = \"%s\"\n", path_getData(pPath));
    eRc = path_Delete(pPath);
    
    pObj = bpt32_New( );
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    if (pObj) {
        
        fprintf(stderr, "pObj = %p\n", pObj);
        
        eRc =   bpt32_SetupSizes(
                                 pObj,
                                 blockSize,
                                 sizeof(uint32_t),      // Data size
                                 8,                     // # of LRU Buffers
                                 11                     // LRU Hash Size
                );
        TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );
        TINYTEST_TRUE( (pObj->pBlock->index == 2) );
        TINYTEST_TRUE( (pObj->pBlock->blockType == OBJ_IDENT_BPT32LF) );
        TINYTEST_TRUE( (pObj->pBlock->dataSize == sizeof(uint32_t)) );
        TINYTEST_TRUE( (pObj->pBlock->actualSize == sizeof(uint32_t)) );
        TINYTEST_TRUE( (pObj->pBlock->max == 3) );
        TINYTEST_TRUE( (pObj->pBlock->used == 0) );

        eRc = bpt32_Create(pObj, pPath);
        TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );
        
        // Adding the first record sets up the bpt32
        // object.
        data1 = 8;
        eRc = bpt32_Add(pObj, data1, &data1);
        TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );
        TINYTEST_TRUE( (pObj->pHdr->root == 2) );
        TINYTEST_TRUE( (pObj->pHdr->dataHead == 2) );
        TINYTEST_TRUE( (pObj->pHdr->dataTail == 2) );
        TINYTEST_TRUE( (pObj->pHdr->cRecords == 2) );
        TINYTEST_TRUE( (pObj->pBlock->used == 0) );

        data2 = 0;
        pObj->srchCur = 0;
        eRc = bpt32_BlockSearch(pObj, pObj->pHdr->root, data1, &data2);
        TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );
        TINYTEST_TRUE( (data2 == data1) );
        TINYTEST_TRUE( (pObj->blockIndex == 1) );
        TINYTEST_TRUE( (pObj->pBlockNode) );
        TINYTEST_TRUE( (pObj->pBlockNode->key == data2) );
        TINYTEST_TRUE( (pObj->srchCur == 1) );
        TINYTEST_TRUE( (pObj->pSrchStk[0] == 2) );

        data1 = 17;
        eRc = bpt32_Add(pObj, data1, &data1);
        TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );
        
        data1 = 42;
        eRc = bpt32_Add(pObj, data1, &data1);
        TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );
        
        data1 = 53;
        eRc = bpt32_Add(pObj, data1, &data1);
        TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );
        
        data1 = 36;
        eRc = bpt32_Add(pObj, data1, &data1);
        TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );
        
#ifdef XYZZY
        data1 = 56;
        eRc = bpt32_Add(pObj, data1, &data1);
        TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );
        
        data1 = 81;
        eRc = bpt32_Add(pObj, data1, &data1);
        TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );
        
        data1 = 72;
        eRc = bpt32_Add(pObj, data1, &data1);
        TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );

        data1 = 65;
        eRc = bpt32_Add(pObj, data1, &data1);
        TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );
#endif
        
        eRc = bpt32_Close(pObj, false);
        TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );

        obj_Release(pObj);
        pObj = OBJ_NIL;
    }
    
    obj_Release(pPath);
    pPath = OBJ_NIL;
    
    fprintf(stderr, "...%s completed.\n\n", pTestName);
    return 1;
}




TINYTEST_START_SUITE(test_bpt32);
    //TINYTEST_ADD_TEST(test_bpt32_Write01,setUp,tearDown);
    TINYTEST_ADD_TEST(test_bpt32_Block03,setUp,tearDown);
    TINYTEST_ADD_TEST(test_bpt32_Block02,setUp,tearDown);
    TINYTEST_ADD_TEST(test_bpt32_Block01,setUp,tearDown);
    TINYTEST_ADD_TEST(test_bpt32_OpenClose,setUp,tearDown);
TINYTEST_END_SUITE();

TINYTEST_MAIN_SINGLE_SUITE(test_bpt32);





