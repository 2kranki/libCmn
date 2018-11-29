/*
 *	Generated 12/08/2017 10:18:28
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
#include    <blocks.h>
#include    <trace.h>
#include    <rbt_tree.h>



static
char        *strings[] = {
    "bob",
    "bobby",
    "iryana",
    "dashsa",
    "dasha",
    "name",
    "way",
    "bigger",
    "Now",
    "is",
    "the",
    "time",
    "for",
    "all",
    "good",
    "men",
    "to",
    "come",
    "aid",
    "of",
    "their",
    "country",
    "We",
    "need",
    "another",
    "item",
    "in",
    "here",
    "Are",
    "you",
    "alright",
    "with",
    "this",
    (char *)NULL,
    (char *)NULL,
    (char *)NULL
};


//      Node Record Descriptor
typedef struct  node_record_s NODE_RECORD;
#pragma pack(push, 1)
struct  node_record_s {
    // RBT_NODE must be first field in this struct.
    RBT_NODE        node;
    uint32_t        unique;
};
#pragma pack(pop)



//---------------------------------------------------------------
//                  N o d e  C o m p a r e
//---------------------------------------------------------------

int             node_Cmp(
    void            *this,
    NODE_RECORD     *pRecordA,
    NODE_RECORD     *pRecordB
)
{
    int             iRc;
    char            *pStrA = pRecordA->node.pKey;
    char            *pStrB = pRecordB->node.pKey;
    
    iRc = strcmp(pStrA, pStrB);
    
    return iRc;
}





int         setUp(
    const
    char        *pTestName
)
{
    mem_Init( );
    trace_Shared( ); 
    // Put setup code here. This method is called before the invocation of each
    // test method in the class.
    
    return 1; 
}


int         tearDown(
    const
    char        *pTestName
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






int         test_rbt_Tree_OpenClose(
    const
    char        *pTestName
)
{
    BLOCKS_DATA	*pBlocks = OBJ_NIL;
    RBT_TREE    tree = {0};
    RBT_TREE    *pTree = &tree;
    ERESULT     eRc;
   
    fprintf(stderr, "Performing: %s\n", pTestName);

    pBlocks = blocks_New( );
    TINYTEST_FALSE( (OBJ_NIL == pBlocks) );
    if (pBlocks) {

        eRc = blocks_SetupSizes(pBlocks, 0, sizeof(NODE_RECORD));
        TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );
        pTree = rbt_Init(
                    pTree,
                    (void *)node_Cmp,
                    (sizeof(NODE_RECORD) - sizeof(RBT_NODE)),
                    (void *)blocks_RecordNew,
                    (void *)blocks_RecordFree,
                    pBlocks
                );
        TINYTEST_TRUE( (&tree == pTree) );
        tree.pNodeFree = (void *)blocks_RecordFree;
        tree.pNodeAlloc = (void *)blocks_RecordNew;
        tree.pObjAllocFree = pBlocks;
        tree.dataSize = sizeof(NODE_RECORD) - sizeof(RBT_NODE);
        
        // Test something!

        obj_Release(pBlocks);
        pBlocks = OBJ_NIL;
    }

    fprintf(stderr, "...%s completed.\n\n\n\n", pTestName);
    return 1;
}



int         test_rbt_Tree_AddFind01(
    const
    char        *pTestName
)
{
    BLOCKS_DATA     *pBlocks = OBJ_NIL;
    RBT_TREE        tree = {0};
    RBT_TREE        *pTree = &tree;
    NODE_RECORD     record = {0};
    NODE_RECORD     *pRecord = &record;
    char            *pFound = NULL;
    ERESULT         eRc;
    bool            fRc;
    char            **pStrA;
    int             iRc;
    
    fprintf(stderr, "Performing: %s\n", pTestName);
    
    pBlocks = blocks_New( );
    TINYTEST_FALSE( (OBJ_NIL == pBlocks) );
    if (pBlocks) {
        
        eRc = blocks_SetupSizes(pBlocks, 0, sizeof(NODE_RECORD));
        TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );
        pTree = rbt_Init(
                         pTree,
                         (void *)strcmp,
                         (sizeof(NODE_RECORD) - sizeof(RBT_NODE)),
                         (void *)blocks_RecordNew,
                         (void *)blocks_RecordFree,
                         pBlocks
                );
        TINYTEST_TRUE( (&tree == pTree) );
        
        pStrA = strings;
        while (*pStrA) {
            NODE_RECORD     newRcd = {0};
            fprintf(stderr, "\tInserting %s\n", *pStrA);
            pRecord = blocks_RecordNew(pBlocks);
            fRc = rbt_Insert(pTree, *pStrA, *pStrA);
            TINYTEST_TRUE( (fRc) );
            fRc = rbt_VerifyTree(pTree, pTree->pRoot);
            TINYTEST_TRUE( (fRc) );
            fprintf(stderr, "\tFinding %s\n", *pStrA);
            pFound = rbt_Find(pTree, *pStrA);
            TINYTEST_FALSE( (NULL == pFound) );
            TINYTEST_TRUE( (0 == strcmp(pFound, *pStrA)) );
            fprintf(stderr, "\t\tFound\n");
            ++pStrA;
        }
        
        pStrA = strings;
        while (*pStrA) {
            NODE_RECORD     newRcd = {0};
            fprintf(stderr, "\tFinding %s\n", *pStrA);
            pFound = rbt_Find(pTree, *pStrA);
            XCTAssertTrue( (0 == strcmp(pFound, *pStrA)) );
            fprintf(stderr, "\t\tFound\n");
            ++pStrA;
        }
        
        rbt_DumpTree(pTree);
        fRc = rbt_VerifyTree(pTree, pTree->pRoot);
        TINYTEST_TRUE( (fRc) );

        obj_Release(pBlocks);
        pBlocks = OBJ_NIL;
    }
    
    fprintf(stderr, "...%s completed.\n\n\n\n", pTestName);
    return 1;
}




TINYTEST_START_SUITE(test_rbt_tree);
    TINYTEST_ADD_TEST(test_rbt_Tree_AddFind01,setUp,tearDown);
    TINYTEST_ADD_TEST(test_rbt_Tree_OpenClose,setUp,tearDown);
TINYTEST_END_SUITE();

TINYTEST_MAIN_SINGLE_SUITE(test_rbt_tree);





