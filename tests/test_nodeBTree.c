/*
 *	Generated 11/12/2018 09:44:16
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
#include    <nodeBTree_internal.h>


static
ERESULT         printNode(
    OBJ_ID          pObj,
    NODE_DATA       *pNode,
    void            *pArg3
)
{
    char            *pNameA;
    
    pNameA = node_getNameUTF8(pNode);
    if (pNameA) {
        fprintf(stderr, "%s", pNameA);
        mem_Free(pNameA);
    }
    return ERESULT_SUCCESS;
}




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






int             test_nodeBTree_OpenClose(
    const
    char            *pTestName
)
{
    NODEBTREE_DATA	*pObj = OBJ_NIL;
   
    fprintf(stderr, "Performing: %s\n", pTestName);

    pObj = nodeBTree_Alloc( );
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    pObj = nodeBTree_Init( pObj );
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    if (pObj) {

        // Test something.

        obj_Release(pObj);
        pObj = OBJ_NIL;
    }

    fprintf(stderr, "...%s completed.\n\n\n\n", pTestName);
    return 1;
}



int             test_nodeBTree_Add01(
    const
    char            *pTestName
)
{
    NODEBTREE_DATA  *pTree = OBJ_NIL;
    NODELNKP_DATA   *pNode = OBJ_NIL;
    NODEBTREE_NODE  *pEntry = NULL;
    ERESULT         eRc;
    const
    char            *pStrA = "ABCDE";
    const
    char            *pStrP = pStrA;
    char            strA[2] = {0};
    ASTR_DATA       *pStr = OBJ_NIL;
    
    fprintf(stderr, "Performing: %s\n", pTestName);
    fprintf(stderr, "\tGenerate a right degenerate tree\n\n");

    pTree = nodeBTree_Alloc( );
    TINYTEST_FALSE( (OBJ_NIL == pTree) );
    pTree = nodeBTree_Init( pTree );
    TINYTEST_FALSE( (OBJ_NIL == pTree) );
    if (pTree) {
        
        while (*pStrP) {
            strA[0] = *pStrP;
            pNode = nodeLnkP_NewWithUTF8AndClass(strA, 0, OBJ_NIL);
            TINYTEST_FALSE( (OBJ_NIL == pNode) );
            if (pNode) {
                eRc = nodeBTree_Add(pTree, pNode, false);
                TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );
                fprintf(stderr, "\tAdded %s\n", strA);
                obj_Release(pNode);
                pNode = OBJ_NIL;
            }
            ++pStrP;
        }
        fprintf(stderr, "\n\n");
        
        fprintf(stderr, "\tPre-Order Recurse: AEDCB\n\t              Got: ");
        eRc = nodeBTree_VisitNodesPreRecurse(pTree, printNode, OBJ_NIL, NULL);
        fprintf(stderr, "\n\n");
        
        fprintf(stderr, "\tIn-Order Recurse: AEDCB\n\t             Got: ");
        eRc = nodeBTree_VisitNodesInRecurse(pTree, printNode, OBJ_NIL, NULL);
        fprintf(stderr, "\n\n");
        
        fprintf(stderr, "\tPost-Order Recurse: EDCBA\n\t               Got: ");
        eRc = nodeBTree_VisitNodesPostRecurse(pTree, printNode, OBJ_NIL, NULL);
        fprintf(stderr, "\n\n");

        pStr = nodeBTree_ToDebugString(pTree, 4);
        fprintf(stderr, "%s\n\n\n", AStr_getData(pStr));
        obj_Release(pStr);
        pStr = OBJ_NIL;
        
        obj_Release(pTree);
        pTree = OBJ_NIL;
    }
    
    fprintf(stderr, "...%s completed.\n\n\n\n", pTestName);
    return 1;
}



int             test_nodeBTree_Add02(
    const
    char            *pTestName
)
{
    NODEBTREE_DATA  *pTree = OBJ_NIL;
    NODELNKP_DATA   *pNode = OBJ_NIL;
    NODEBTREE_NODE  *pEntry = NULL;
    ERESULT         eRc;
    //              ABCDEFG
    const
    char            *pStrA = "DBFCGAE";
    const
    char            *pStrP = pStrA;
    char            strA[2] = {0};
    ASTR_DATA       *pStr = OBJ_NIL;
    
    fprintf(stderr, "Performing: %s\n", pTestName);
    fprintf(stderr, "\tGenerate a right degenerate tree\n\n");
    
    pTree = nodeBTree_Alloc( );
    TINYTEST_FALSE( (OBJ_NIL == pTree) );
    pTree = nodeBTree_Init( pTree );
    TINYTEST_FALSE( (OBJ_NIL == pTree) );
    if (pTree) {
        
        while (*pStrP) {
            strA[0] = *pStrP;
            pNode = nodeLnkP_NewWithUTF8AndClass(strA, 0, OBJ_NIL);
            TINYTEST_FALSE( (OBJ_NIL == pNode) );
            if (pNode) {
                eRc = nodeBTree_Add(pTree, pNode, false);
                TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );
                fprintf(stderr, "\tAdded %s\n", strA);
                obj_Release(pNode);
                pNode = OBJ_NIL;
            }
            ++pStrP;
        }
        fprintf(stderr, "\n\n");
        
        fprintf(stderr, "\tPre-Order Recurse: DACBEGF\n\t              Got: ");
        eRc = nodeBTree_VisitNodesPreRecurse(pTree, printNode, OBJ_NIL, NULL);
        fprintf(stderr, "\n\n");
        
        fprintf(stderr, "\tIn-Order Recurse: ACBDEGF\n\t             Got: ");
        eRc = nodeBTree_VisitNodesInRecurse(pTree, printNode, OBJ_NIL, NULL);
        fprintf(stderr, "\n\n");
        
        fprintf(stderr, "\tPost-Order Recurse: ACBEGFD\n\t               Got: ");
        eRc = nodeBTree_VisitNodesPostRecurse(pTree, printNode, OBJ_NIL, NULL);
        fprintf(stderr, "\n\n");
        
        pStr = nodeBTree_ToDebugString(pTree, 4);
        fprintf(stderr, "%s\n\n\n", AStr_getData(pStr));
        obj_Release(pStr);
        pStr = OBJ_NIL;
        
        obj_Release(pTree);
        pTree = OBJ_NIL;
    }
    
    fprintf(stderr, "...%s completed.\n\n\n\n", pTestName);
    return 1;
}



int             test_nodeBTree_Traverse01(
    const
    char            *pTestName
)
{
    NODEBTREE_DATA  *pTree = OBJ_NIL;
    NODE_DATA       *pNode = OBJ_NIL;
    NODEBTREE_NODE  *pEntry = NULL;
    ERESULT         eRc;
    
    fprintf(stderr, "Performing: %s\n", pTestName);
    
    pTree = nodeBTree_Alloc( );
    TINYTEST_FALSE( (OBJ_NIL == pTree) );
    pTree = nodeBTree_Init( pTree );
    TINYTEST_FALSE( (OBJ_NIL == pTree) );
    if (pTree) {
        
#ifdef xyzzy
        pNode = node_NewWithUTF8ConAndClass("A", 0, OBJ_NIL);
        TINYTEST_FALSE( (OBJ_NIL == pNode) );
        pEntry = blocks_RecordNew((BLOCKS_DATA *)pTree);
        TINYTEST_FALSE( (NULL == pEntry) );
        pEntry->pNode = pNode;
        //FIXME: pTree->pRoot = pEntry;
        
        pNode = node_NewWithUTF8ConAndClass("B", 0, OBJ_NIL);
        TINYTEST_FALSE( (OBJ_NIL == pNode) );
        pEntry = blocks_RecordNew((BLOCKS_DATA *)pTree);
        TINYTEST_FALSE( (NULL == pEntry) );
        pEntry->pNode = pNode;
        //FIXME: pTree->pRoot->pLeft = pEntry;
        
        pNode = node_NewWithUTF8ConAndClass("D", 0, OBJ_NIL);
        TINYTEST_FALSE( (OBJ_NIL == pNode) );
        pEntry = blocks_RecordNew((BLOCKS_DATA *)pTree);
        TINYTEST_FALSE( (NULL == pEntry) );
        pEntry->pNode = pNode;
        //FIXME: pTree->pRoot->pLeft->pLeft = pEntry;
        
        pNode = node_NewWithUTF8ConAndClass("G", 0, OBJ_NIL);
        TINYTEST_FALSE( (OBJ_NIL == pNode) );
        pEntry = blocks_RecordNew((BLOCKS_DATA *)pTree);
        TINYTEST_FALSE( (NULL == pEntry) );
        pEntry->pNode = pNode;
        //FIXME: pTree->pRoot->pLeft->pLeft->pRight = pEntry;
        
        pNode = node_NewWithUTF8ConAndClass("C", 0, OBJ_NIL);
        TINYTEST_FALSE( (OBJ_NIL == pNode) );
        pEntry = blocks_RecordNew((BLOCKS_DATA *)pTree);
        TINYTEST_FALSE( (NULL == pEntry) );
        pEntry->pNode = pNode;
        //FIXME: pTree->pRoot->pRight = pEntry;
        
        pNode = node_NewWithUTF8ConAndClass("F", 0, OBJ_NIL);
        TINYTEST_FALSE( (OBJ_NIL == pNode) );
        pEntry = blocks_RecordNew((BLOCKS_DATA *)pTree);
        TINYTEST_FALSE( (NULL == pEntry) );
        pEntry->pNode = pNode;
        //FIXME: pTree->pRoot->pRight->pRight = pEntry;
        
        pNode = node_NewWithUTF8ConAndClass("E", 0, OBJ_NIL);
        TINYTEST_FALSE( (OBJ_NIL == pNode) );
        pEntry = blocks_RecordNew((BLOCKS_DATA *)pTree);
        TINYTEST_FALSE( (NULL == pEntry) );
        pEntry->pNode = pNode;
        //FIXME: pTree->pRoot->pRight->pLeft = pEntry;
        
        pNode = node_NewWithUTF8ConAndClass("H", 0, OBJ_NIL);
        TINYTEST_FALSE( (OBJ_NIL == pNode) );
        pEntry = blocks_RecordNew((BLOCKS_DATA *)pTree);
        TINYTEST_FALSE( (NULL == pEntry) );
        pEntry->pNode = pNode;
        //FIXME: pTree->pRoot->pRight->pLeft->pLeft = pEntry;
        
        pNode = node_NewWithUTF8ConAndClass("I", 0, OBJ_NIL);
        TINYTEST_FALSE( (OBJ_NIL == pNode) );
        pEntry = blocks_RecordNew((BLOCKS_DATA *)pTree);
        TINYTEST_FALSE( (NULL == pEntry) );
        pEntry->pNode = pNode;
        //FIXME: pTree->pRoot->pRight->pLeft->pRight = pEntry;
#endif
        
        fprintf(stderr, "Preorder:   ABDGCEHIF\n");
        fprintf(stderr, "Actual:     ");
        eRc = nodeBTree_PreOrderTraversal(pTree, (void *)printNode, NULL, NULL);
        TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );
        fprintf(stderr, "\n\n\n");

        fprintf(stderr, "Inorder:    DGBAHEICF\n");
        fprintf(stderr, "Actual:     ");
        eRc = nodeBTree_InOrderTraversal(pTree, (void *)printNode, NULL, NULL);
        TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );
        fprintf(stderr, "\n\n\n");

        fprintf(stderr, "Postorder:  GDBHIEFCA\n");
        fprintf(stderr, "\n\n\n");

        obj_Release(pTree);
        pTree = OBJ_NIL;
    }
    
    fprintf(stderr, "...%s completed.\n\n\n\n", pTestName);
    return 1;
}




TINYTEST_START_SUITE(test_nodeBTree);
    //TINYTEST_ADD_TEST(test_nodeBTree_Traverse01,setUp,tearDown);
    TINYTEST_ADD_TEST(test_nodeBTree_Add02,setUp,tearDown);
    TINYTEST_ADD_TEST(test_nodeBTree_Add01,setUp,tearDown);
    TINYTEST_ADD_TEST(test_nodeBTree_OpenClose,setUp,tearDown);
TINYTEST_END_SUITE();

TINYTEST_MAIN_SINGLE_SUITE(test_nodeBTree);





