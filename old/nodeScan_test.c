/*
 *	Generated 06/05/2017 21:57:10
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
#include    <nodeLink.h>
#include    <nodeScan_internal.h>
#include    <nodeTree.h>


typedef enum our_node_classes_e {
    BEGIN_NODE_CLASSES_AT=NODE_CLASS_USER,
    NODE_CLASS_ADD,
    NODE_CLASS_DIVIDE,
    NODE_CLASS_EXPR,
    NODE_CLASS_MULTIPLY,
    NODE_CLASS_PHRASE,
    NODE_CLASS_SUBTRACT,
    NODE_CLASS_TERM,
    NODE_CLASS_VALUE,
    NODE_CLASS_VARIABLE,
} OUR_NODE_CLASSES;



static
NODETREE_DATA * createTestTree01(
)
{
    NODETREE_DATA   *pTree = OBJ_NIL;
    NODELINK_DATA   *pNodeA = OBJ_NIL;
    NODELINK_DATA   *pNodeB = OBJ_NIL;
    NODELINK_DATA   *pNodeC = OBJ_NIL;
    NODELINK_DATA   *pNodeD = OBJ_NIL;
    NODELINK_DATA   *pNodeE = OBJ_NIL;
    NODELINK_DATA   *pNodeF = OBJ_NIL;
    NODELINK_DATA   *pNodeG = OBJ_NIL;
    uint32_t        i;
    ERESULT         eRc;
    
    pTree = nodeTree_Alloc( );
    if  (OBJ_NIL == pTree) {
        return pTree;
    }
    pTree = nodeTree_Init( pTree );
    if  (OBJ_NIL == pTree) {
        return pTree;
    }
    
    pNodeA = nodeLink_NewWithUTF8ConAndClass(NODE_CLASS_ADD, "+", OBJ_NIL);
    if  (OBJ_NIL == pNodeA) {
        obj_Release(pTree);
        pTree = OBJ_NIL;
        return pTree;
    }
    
    pNodeB = nodeLink_NewWithUTF8ConAndClass(NODE_CLASS_MULTIPLY, "*", OBJ_NIL);
    if  (OBJ_NIL == pNodeB) {
        obj_Release(pTree);
        pTree = OBJ_NIL;
        return pTree;
    }

    pNodeC = nodeLink_NewWithUTF8ConAndClass(NODE_CLASS_VARIABLE, "a", OBJ_NIL);
    if  (OBJ_NIL == pNodeC) {
        obj_Release(pTree);
        pTree = OBJ_NIL;
        return pTree;
    }

    pNodeD = nodeLink_NewWithUTF8ConAndClass(NODE_CLASS_VARIABLE, "b", OBJ_NIL);
    if  (OBJ_NIL == pNodeD) {
        obj_Release(pTree);
        pTree = OBJ_NIL;
        return pTree;
    }

    pNodeE = nodeLink_NewWithUTF8ConAndClass(NODE_CLASS_MULTIPLY, "*", OBJ_NIL);
    if  (OBJ_NIL == pNodeE) {
        obj_Release(pTree);
        pTree = OBJ_NIL;
        return pTree;
    }

    pNodeF = nodeLink_NewWithUTF8ConAndClass(NODE_CLASS_VARIABLE, "c", OBJ_NIL);
    if  (OBJ_NIL == pNodeF) {
        obj_Release(pTree);
        pTree = OBJ_NIL;
        return pTree;
    }

    pNodeG = nodeLink_NewWithUTF8ConAndClass(NODE_CLASS_VARIABLE, "d", OBJ_NIL);
    if  (OBJ_NIL == pNodeG) {
        obj_Release(pTree);
        pTree = OBJ_NIL;
        return pTree;
    }

    fprintf(stderr, "\n\nCreate the tree:\n");
    fprintf(stderr, "Tree    Index  Sibling  Child  Parent\n");
    fprintf(stderr, "+         1       0       2       0\n");
    fprintf(stderr, "--*       2       3       4       1\n");
    fprintf(stderr, "----a     4       5       0       2\n");
    fprintf(stderr, "----b     5       0       0       2\n");
    fprintf(stderr, "--*       3       4       6       1\n");
    fprintf(stderr, "----c     6       8       0       3\n");
    fprintf(stderr, "----d     7       0       0       3\n");
    fprintf(stderr, "\n\n\n");
    
    i = nodeTree_ChildAdd(pTree, 0, pNodeA);
    if  (i == 1)
        ;
    else {
        obj_Release(pTree);
        pTree = OBJ_NIL;
        return pTree;
    }
    eRc = nodeTree_ChildrenAdd(pTree, nodeLink_getIndex(pNodeA), pNodeB, pNodeE, OBJ_NIL);
    if  (ERESULT_FAILED(eRc)) {
        obj_Release(pTree);
        pTree = OBJ_NIL;
        return pTree;
    }
    eRc = nodeTree_ChildrenAdd(pTree, nodeLink_getIndex(pNodeB), pNodeC, pNodeD, OBJ_NIL);
    if  (ERESULT_FAILED(eRc)) {
        obj_Release(pTree);
        pTree = OBJ_NIL;
        return pTree;
    }
    eRc = nodeTree_ChildrenAdd(pTree,nodeLink_getIndex(pNodeE), pNodeF, pNodeG, OBJ_NIL);
    if  (ERESULT_FAILED(eRc)) {
        obj_Release(pTree);
        pTree = OBJ_NIL;
        return pTree;
    }
    
    obj_Release(pNodeG);
    pNodeG = OBJ_NIL;
    obj_Release(pNodeF);
    pNodeF = OBJ_NIL;
    obj_Release(pNodeE);
    pNodeE = OBJ_NIL;
    obj_Release(pNodeD);
    pNodeD = OBJ_NIL;
    obj_Release(pNodeC);
    pNodeC = OBJ_NIL;
    obj_Release(pNodeB);
    pNodeB = OBJ_NIL;
    obj_Release(pNodeA);
    pNodeA = OBJ_NIL;
    
    return pTree;
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






int         test_nodeScan_OpenClose(
    const
    char        *pTestName
)
{
    NODESCAN_DATA *pObj = OBJ_NIL;
   
    fprintf(stderr, "Performing: %s\n", pTestName);
    
    pObj = nodeScan_Alloc( );
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    pObj = nodeScan_Init( pObj );
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    if (pObj) {

        // Test something.

        obj_Release(pObj);
        pObj = OBJ_NIL;
    }

    fprintf(stderr, "...%s completed.\n", pTestName);
    return 1;
}



int         test_nodeScan_Scanf01(
    const
    char        *pTestName
)
{
    NODESCAN_DATA   *pObj = OBJ_NIL;
    NODETREE_DATA   *pTree = OBJ_NIL;
    NODEARRAY_DATA  *pArray = OBJ_NIL;
    NODEENUM_DATA   *pEnum = OBJ_NIL;
    NODE_DATA       *pNode = OBJ_NIL;
    char            *pWrkStr = NULL;
    uint32_t        count = 0;
    
    fprintf(stderr, "Performing: %s\n", pTestName);
    
    pTree = createTestTree01( );
    TINYTEST_FALSE( (OBJ_NIL == pTree) );
    pArray = nodeTree_ToLinearizationPre(pTree);
    TINYTEST_FALSE( (OBJ_NIL == pArray) );

    fprintf(stderr, "\n");
    pEnum = nodeArray_Enum(pArray);
    TINYTEST_FALSE( (OBJ_NIL == pEnum) );
    while (ERESULT_SUCCESS == NodeEnum_Next(pEnum, 1, (void *)&pNode, &count)) {
        if (pNode && (count == 1)) {
            pWrkStr = name_ToUTF8(node_getName(pNode));
            fprintf(stderr, "\t%s\n", pWrkStr);
            mem_Free(pWrkStr);
            pWrkStr = NULL;
        }
    }
    obj_Release(pEnum);
    pEnum = OBJ_NIL;
    fprintf(stderr, "\n");

    pObj = nodeScan_NewFromArray(pArray);
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    if (pObj) {
        
        // Test something.
        
        obj_Release(pObj);
        pObj = OBJ_NIL;
    }
    
    obj_Release(pArray);
    pArray = OBJ_NIL;
    obj_Release(pTree);
    pTree = OBJ_NIL;

    fprintf(stderr, "...%s completed.\n", pTestName);
    return 1;
}




TINYTEST_START_SUITE(test_nodeScan);
    TINYTEST_ADD_TEST(test_nodeScan_Scanf01,setUp,tearDown);
    TINYTEST_ADD_TEST(test_nodeScan_OpenClose,setUp,tearDown);
TINYTEST_END_SUITE();

TINYTEST_MAIN_SINGLE_SUITE(test_nodeScan);





