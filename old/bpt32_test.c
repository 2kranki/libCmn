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
#include    <FileIO.h>
#include    <RRDS.h>
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



int             test_bpt32_Write01(
    const
    char            *pTestName
)
{
    ERESULT         eRc = ERESULT_SUCCESS;
    BPT32_DATA      *pObj = OBJ_NIL;
    //LRU_DATA        *pLRU = OBJ_NIL;
    PATH_DATA       *pPath = OBJ_NIL;
    ASTR_DATA       *pStr = OBJ_NIL;
    const
    char            *pPathA = "/tmp/testBPT32.temp.data";
    uint32_t        i = 0;
    uint32_t        key = 0;
    uint32_t        data = 0;
    uint32_t        dataRet = 0;
    uint32_t        blockSize = 64;
    static
    uint32_t        keysAdded[31] = {
        8,17,36,42,53,56,65,72,73,75,
        77,81,83,96,98,102,104,107,112,117,
        119,121,123,125,127,131,133,135,137,139,
        141
    };

    fprintf(stderr, "Performing: %s\n", pTestName);
    
    pPath = Path_NewA(pPathA);
    TINYTEST_FALSE( (OBJ_NIL == pPath) );
    fprintf(stderr, "\tPath = \"%s\"\n", Path_getData(pPath));
    eRc = Path_Delete(pPath);
    
    pObj = bpt32_New( );
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    if (pObj) {
        
        fprintf(stderr, "pObj = %p\n", pObj);
        obj_TraceSet(pObj, true);
        
        eRc =   bpt32_SetupSizes(
                                 pObj,
                                 blockSize,
                                 sizeof(uint32_t),      // Data size
                                 8,                     // # of LRU Buffers
                                 11                     // LRU Hash Size
                );
        TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );
        TINYTEST_TRUE( (pObj->blockSize == blockSize) );
        TINYTEST_TRUE( (pObj->dataSize == sizeof(uint32_t)) );
        // Blocksize == 64, Max Records for Leaf == 5
        // Blocksize == 64, Max Records for Index == 5
        // We chose 64 because it works in a hex dump of
        // the file nicely.

        eRc = bpt32_Create(pObj, pPath);
        TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );
        
        // Adding the first record sets up the bpt32
        // object.
        data = 8;                                  // 1
        eRc = bpt32_Add(pObj, data, &data);
        TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );
        TINYTEST_TRUE( (pObj->pHdr->root == 2) );
        TINYTEST_TRUE( (pObj->pHdr->dataHead == 2) );
        TINYTEST_TRUE( (pObj->pHdr->dataTail == 2) );
        TINYTEST_TRUE( (pObj->pHdr->cRecords == 2) );

        data = 17;                                 // 2
        eRc = bpt32_Add(pObj, data, &data);
        TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );
        
        data = 42;                                 // 3
        eRc = bpt32_Add(pObj, data, &data);
        TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );
        
        data = 53;                                 // 4
        eRc = bpt32_Add(pObj, data, &data);
        TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );
        
        data = 36;                                 // 5
        eRc = bpt32_Add(pObj, data, &data);
        TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );

        // This node should cause a block split which will add
        // a second leaf and an index block which will become
        // root.
        data = 56;                                 // 6
        eRc = bpt32_Add(pObj, data, &data);
        TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );
        TINYTEST_TRUE( (pObj->pHdr->cRecords == 4) );   // New Index and Leaf Blocks
        TINYTEST_TRUE( (pObj->pHdr->dataHead == 2) );
        TINYTEST_TRUE( (pObj->pHdr->dataTail == 3) );

#ifdef XYZZY
        {
            pStr = objArray_ToDebugString(pObj->pSrchStk, 4);
            fprintf(stderr, "1\t%s\n", AStr_getData(pStr));
            obj_Release(pStr);
            pStr = OBJ_NIL;
        }
#endif
        
        data = 81;                                 // 7
        eRc = bpt32_Add(pObj, data, &data);
        TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );
        
        data = 72;                                 // 8
        eRc = bpt32_Add(pObj, data, &data);
        TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );

        data = 65;                                 // 9
        eRc = bpt32_Add(pObj, data, &data);
        TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );
        
        data = 83;                                 // 10
        eRc = bpt32_Add(pObj, data, &data);
        TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );
        
        data = 96;                                 // 11
        eRc = bpt32_Add(pObj, data, &data);
        TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );
        
        data = 98;                                 // 12
        eRc = bpt32_Add(pObj, data, &data);
        TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );
        
        data = 102;                                // 13
        eRc = bpt32_Add(pObj, data, &data);
        TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );
        
        data = 104;                                // 14
        eRc = bpt32_Add(pObj, data, &data);
        TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );
        
        data = 107;                                // 15
        eRc = bpt32_Add(pObj, data, &data);
        TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );
        
        data = 112;                                // 16
        eRc = bpt32_Add(pObj, data, &data);
        TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );
        
        data = 119;                                // 17
        eRc = bpt32_Add(pObj, data, &data);
        TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );
        
        data = 125;                                // 18
        eRc = bpt32_Add(pObj, data, &data);
        TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );
        
        data = 127;                                // 19
        eRc = bpt32_Add(pObj, data, &data);
        TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );
        
        data = 131;                                // 20
        eRc = bpt32_Add(pObj, data, &data);
        TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );
        
        data = 133;                                // 21
        eRc = bpt32_Add(pObj, data, &data);
        TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );
        
        data = 135;                                // 22
        eRc = bpt32_Add(pObj, data, &data);
        TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );
        
        data = 137;                                // 23
        eRc = bpt32_Add(pObj, data, &data);
        TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );
        
        data = 139;                                // 24
        eRc = bpt32_Add(pObj, data, &data);
        TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );
        
        data = 141;                                // 25
        eRc = bpt32_Add(pObj, data, &data);
        TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );
        
        data = 77;                                 // 26
        eRc = bpt32_Add(pObj, data, &data);
        TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );
        
        data = 73;                                 // 27
        eRc = bpt32_Add(pObj, data, &data);
        TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );
        
        data = 75;                                 // 28
        eRc = bpt32_Add(pObj, data, &data);
        TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );
        
        data = 121;                                // 29
        eRc = bpt32_Add(pObj, data, &data);
        TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );
        
        data = 117;                                // 30
        eRc = bpt32_Add(pObj, data, &data);
        TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );
        
        data = 123;                                // 31
        eRc = bpt32_Add(pObj, data, &data);
        TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );
        
        data = 81;
        dataRet = 0;
        eRc = bpt32_Find(pObj, data, &dataRet);
        TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );
        TINYTEST_TRUE( (data == dataRet) );

        data = 119;
        dataRet = 0;
        eRc = bpt32_Find(pObj, data, &dataRet);
        TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );
        TINYTEST_TRUE( (data == dataRet) );
        
        data = 83;
        dataRet = 0;
        eRc = bpt32_Find(pObj, data, &dataRet);
        TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );
        TINYTEST_TRUE( (data == dataRet) );
        
        data = 42;
        dataRet = 0;
        eRc = bpt32_Find(pObj, data, &dataRet);
        TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );
        TINYTEST_TRUE( (data == dataRet) );
        
        data = 65;
        dataRet = 0;
        eRc = bpt32_Find(pObj, data, &dataRet);
        TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );
        TINYTEST_TRUE( (data == dataRet) );
        
        data = 36;
        dataRet = 0;
        eRc = bpt32_Find(pObj, data, &dataRet);
        TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );
        TINYTEST_TRUE( (data == dataRet) );
        
        {
            pStr = bpt32_ToDebugString(pObj, 4);
            fprintf(stderr, "\n\n%s\n\n\n", AStr_getData(pStr));
            obj_Release(pStr);
            pStr = OBJ_NIL;
        }
        
        i = 0;
        eRc = bpt32_First(pObj, &key, NULL);
        TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );
        TINYTEST_TRUE( (key == keysAdded[i]) );

        for (i=1; i<31; ++i) {
            eRc = bpt32_Next(pObj, &key, NULL);
            TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );
            TINYTEST_TRUE( (key == keysAdded[i]) );
        }
        
        eRc = bpt32_Next(pObj, &key, NULL);
        TINYTEST_TRUE( (ERESULT_FAILED(eRc)) );
        TINYTEST_TRUE( (eRc == ERESULT_EOF_ERROR) );

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
    TINYTEST_ADD_TEST(test_bpt32_Write01,setUp,tearDown);
    TINYTEST_ADD_TEST(test_bpt32_OpenClose,setUp,tearDown);
TINYTEST_END_SUITE();

TINYTEST_MAIN_SINGLE_SUITE(test_bpt32);





