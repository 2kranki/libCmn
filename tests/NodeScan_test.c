// vi:nu:et:sts=4 ts=4 sw=4
/*
 *	Generated 12/17/2019 10:10:16
 *  Tests are consistant with NodeTree_test.c.
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
#include    <NodeLink.h>
#include    <trace.h>
#include    <NodeScan_internal.h>
#include    <NodeTree.h>


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



// Example from Knuth's "The Art of Computer Programming - Volume 1 (3rd Ed.)", page 332
// which consists of a forest (two trees) that have sibling roots.
static
NODETREE_DATA * createTestTree01(
)
{
    NODETREE_DATA	*pTree = OBJ_NIL;
    NODELINK_DATA   *pNodeA = OBJ_NIL;
    NODELINK_DATA   *pNodeB = OBJ_NIL;
    NODELINK_DATA   *pNodeC = OBJ_NIL;
    NODELINK_DATA   *pNodeD = OBJ_NIL;
    NODELINK_DATA   *pNodeE = OBJ_NIL;
    NODELINK_DATA   *pNodeF = OBJ_NIL;
    NODELINK_DATA   *pNodeG = OBJ_NIL;
    NODELINK_DATA   *pNodeH = OBJ_NIL;
    NODELINK_DATA   *pNodeJ = OBJ_NIL;
    NODELINK_DATA   *pNodeK = OBJ_NIL;
    uint32_t        i;
    ERESULT         eRc;
    
    pTree = NodeTree_Alloc( );
    if  (OBJ_NIL == pTree) {
        return pTree;
    }
    pTree = NodeTree_Init( pTree );
    if  (OBJ_NIL == pTree) {
        return pTree;
    }
    
    pNodeA = NodeLink_NewWithUTF8ConAndClass(0, "A", OBJ_NIL);
    if  (OBJ_NIL == pNodeA) {
        obj_Release(pTree);
        pTree = OBJ_NIL;
        return pTree;
    }
    pNodeB = NodeLink_NewWithUTF8ConAndClass(0, "B", OBJ_NIL);
    if  (OBJ_NIL == pNodeB) {
        obj_Release(pTree);
        pTree = OBJ_NIL;
        return pTree;
    }
    pNodeC = NodeLink_NewWithUTF8ConAndClass(0, "C", OBJ_NIL);
    if  (OBJ_NIL == pNodeC) {
        obj_Release(pTree);
        pTree = OBJ_NIL;
        return pTree;
    }
    pNodeD = NodeLink_NewWithUTF8ConAndClass(0, "D", OBJ_NIL);
    if  (OBJ_NIL == pNodeD) {
        obj_Release(pTree);
        pTree = OBJ_NIL;
        return pTree;
    }
    pNodeE = NodeLink_NewWithUTF8ConAndClass(0, "E", OBJ_NIL);
    if  (OBJ_NIL == pNodeE) {
        obj_Release(pTree);
        pTree = OBJ_NIL;
        return pTree;
    }
    pNodeF = NodeLink_NewWithUTF8ConAndClass(0, "F", OBJ_NIL);
    if  (OBJ_NIL == pNodeF) {
        obj_Release(pTree);
        pTree = OBJ_NIL;
        return pTree;
    }
    pNodeG = NodeLink_NewWithUTF8ConAndClass(0, "G", OBJ_NIL);
    if  (OBJ_NIL == pNodeG) {
        obj_Release(pTree);
        pTree = OBJ_NIL;
        return pTree;
    }
    pNodeH = NodeLink_NewWithUTF8ConAndClass(0, "H", OBJ_NIL);
    if  (OBJ_NIL == pNodeH) {
        obj_Release(pTree);
        pTree = OBJ_NIL;
        return pTree;
    }
    pNodeJ = NodeLink_NewWithUTF8ConAndClass(0, "J", OBJ_NIL);
    if  (OBJ_NIL == pNodeJ) {
        obj_Release(pTree);
        pTree = OBJ_NIL;
        return pTree;
    }
    pNodeK = NodeLink_NewWithUTF8ConAndClass(0, "K", OBJ_NIL);
    if  (OBJ_NIL == pNodeK) {
        obj_Release(pTree);
        pTree = OBJ_NIL;
        return pTree;
    }

    fprintf(stderr, "\n\nCreate the tree:\n");
    fprintf(stderr, "Tree    Index   Child  Sibling  Parent\n");
    fprintf(stderr, "                (Left) (Right)\n");
    fprintf(stderr, "A         1       3       2       0\n");
    fprintf(stderr, "--B       3       0       4       1\n");
    fprintf(stderr, "--C       4       5       0       1\n");
    fprintf(stderr, "----K     5       0       0       4\n");
    fprintf(stderr, "D         2       6       0       0\n");
    fprintf(stderr, "--E       6       9       7       2\n");
    fprintf(stderr, "----H     9       0       0       6\n");
    fprintf(stderr, "--F       7      10       8       2\n");
    fprintf(stderr, "----J    10       0       0       7\n");
    fprintf(stderr, "--G       8       0       0       2\n");
    fprintf(stderr, "\n");
    fprintf(stderr, "Preorder Traversal:  \n");
    fprintf(stderr, "Inorder Traversal:   (A(B, C(K), D(E(H), F(J), G))\n");
    fprintf(stderr, "Postorder Traversal: ((B, (K)C)A, ((H)E, (J)F, G)D),\n");
    fprintf(stderr, "\n\n\n");

    i = NodeTree_ChildAdd(pTree, 0, pNodeA);
    if  (i == 1)
        ;
    else {
        obj_Release(pTree);
        pTree = OBJ_NIL;
        return pTree;
    }
    i = NodeTree_SiblingAdd(pTree, NodeLink_getIndex(pNodeA), pNodeD);
    if  (i == 2)
        ;
    else {
        obj_Release(pTree);
        pTree = OBJ_NIL;
        return pTree;
    }

    //                                                         3      4
    eRc = NodeTree_ChildrenAdd(pTree,NodeLink_getIndex(pNodeA), pNodeB, pNodeC, OBJ_NIL);
    if  (ERESULT_FAILED(eRc)) {
        obj_Release(pTree);
        pTree = OBJ_NIL;
        return pTree;
    }
    //                                                        5
    eRc = NodeTree_ChildrenAdd(pTree,NodeLink_getIndex(pNodeC), pNodeK, OBJ_NIL);
    if  (ERESULT_FAILED(eRc)) {
        obj_Release(pTree);
        pTree = OBJ_NIL;
        return pTree;
    }
    //                                                         6      7       8
    eRc = NodeTree_ChildrenAdd(pTree,NodeLink_getIndex(pNodeD), pNodeE, pNodeF, pNodeG, OBJ_NIL);
    if  (ERESULT_FAILED(eRc)) {
        obj_Release(pTree);
        pTree = OBJ_NIL;
        return pTree;
    }
    //                                                         9
    eRc = NodeTree_ChildrenAdd(pTree,NodeLink_getIndex(pNodeE), pNodeH, OBJ_NIL);
    if  (ERESULT_FAILED(eRc)) {
        obj_Release(pTree);
        pTree = OBJ_NIL;
        return pTree;
    }
    //                                                        10
    eRc = NodeTree_ChildrenAdd(pTree,NodeLink_getIndex(pNodeF), pNodeJ, OBJ_NIL);
    if  (ERESULT_FAILED(eRc)) {
        obj_Release(pTree);
        pTree = OBJ_NIL;
        return pTree;
    }

    obj_Release(pNodeK);
    pNodeK = OBJ_NIL;
    obj_Release(pNodeJ);
    pNodeJ = OBJ_NIL;
    obj_Release(pNodeH);
    pNodeH = OBJ_NIL;
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




// Example from "Algorithms + Data Structures = Programs" by Niklaus Wirth
// Page 193 and 199
// Tree representation of: (a + b / c) * (d - e * f)
// Note - Each node must be unique.  Therefore, we must have two nodes for '*'.
static
NODETREE_DATA * createTestTree02(
)
{
    NODETREE_DATA   *pTree = OBJ_NIL;
    NODELINK_DATA   *pNodeA = OBJ_NIL;
    NODELINK_DATA   *pNodeB = OBJ_NIL;
    NODELINK_DATA   *pNodeC = OBJ_NIL;
    NODELINK_DATA   *pNodeD = OBJ_NIL;
    NODELINK_DATA   *pNodeE = OBJ_NIL;
    NODELINK_DATA   *pNodeF = OBJ_NIL;
    NODELINK_DATA   *pNodeG = OBJ_NIL;          // * (1)
    NODELINK_DATA   *pNodeH = OBJ_NIL;          // +
    NODELINK_DATA   *pNodeI = OBJ_NIL;          // /
    NODELINK_DATA   *pNodeJ = OBJ_NIL;          // -
    NODELINK_DATA   *pNodeK = OBJ_NIL;          // * (2)
    uint32_t        i;
    ERESULT         eRc;
    
    pTree = NodeTree_Alloc( );
    if  (OBJ_NIL == pTree) {
        return pTree;
    }
    pTree = NodeTree_Init( pTree );
    if  (OBJ_NIL == pTree) {
        return pTree;
    }
    
    pNodeA = NodeLink_NewWithUTF8ConAndClass(0, "a", OBJ_NIL);
    if  (OBJ_NIL == pNodeA) {
        obj_Release(pTree);
        pTree = OBJ_NIL;
        return pTree;
    }
    pNodeB = NodeLink_NewWithUTF8ConAndClass(0, "b", OBJ_NIL);
    if  (OBJ_NIL == pNodeB) {
        obj_Release(pTree);
        pTree = OBJ_NIL;
        return pTree;
    }
    pNodeC = NodeLink_NewWithUTF8ConAndClass(0, "c", OBJ_NIL);
    if  (OBJ_NIL == pNodeC) {
        obj_Release(pTree);
        pTree = OBJ_NIL;
        return pTree;
    }
    pNodeD = NodeLink_NewWithUTF8ConAndClass(0, "d", OBJ_NIL);
    if  (OBJ_NIL == pNodeD) {
        obj_Release(pTree);
        pTree = OBJ_NIL;
        return pTree;
    }
    pNodeE = NodeLink_NewWithUTF8ConAndClass(0, "e", OBJ_NIL);
    if  (OBJ_NIL == pNodeE) {
        obj_Release(pTree);
        pTree = OBJ_NIL;
        return pTree;
    }
    pNodeF = NodeLink_NewWithUTF8ConAndClass(0, "f", OBJ_NIL);
    if  (OBJ_NIL == pNodeF) {
        obj_Release(pTree);
        pTree = OBJ_NIL;
        return pTree;
    }
    pNodeG = NodeLink_NewWithUTF8ConAndClass(0, "*1", OBJ_NIL);
    if  (OBJ_NIL == pNodeG) {
        obj_Release(pTree);
        pTree = OBJ_NIL;
        return pTree;
    }
    pNodeH = NodeLink_NewWithUTF8ConAndClass(0, "+", OBJ_NIL);
    if  (OBJ_NIL == pNodeH) {
        obj_Release(pTree);
        pTree = OBJ_NIL;
        return pTree;
    }
    pNodeI = NodeLink_NewWithUTF8ConAndClass(0, "/", OBJ_NIL);
    if  (OBJ_NIL == pNodeI) {
        obj_Release(pTree);
        pTree = OBJ_NIL;
        return pTree;
    }
    
    pNodeJ = NodeLink_NewWithUTF8ConAndClass(0, "-", OBJ_NIL);
    if  (OBJ_NIL == pNodeI) {
        obj_Release(pTree);
        pTree = OBJ_NIL;
        return pTree;
    }
    
    pNodeK = NodeLink_NewWithUTF8ConAndClass(0, "*2", OBJ_NIL);
    if  (OBJ_NIL == pNodeI) {
        obj_Release(pTree);
        pTree = OBJ_NIL;
        return pTree;
    }
    
    fprintf(stderr, "\n\nCreate the tree:\n");
    fprintf(stderr, "Tree            Index  Sibling  Child  Parent\n");
    fprintf(stderr, "'*1'         G    1       0       2       0\n");
    fprintf(stderr, "--'+'        H    2       3       4       1\n");
    fprintf(stderr, "----'a'      A    4       5       0       2\n");
    fprintf(stderr, "----'/'      I    5       0       6       2\n");
    fprintf(stderr, "------'b'    B    6       7       0       5\n");
    fprintf(stderr, "------'c'    C    7       0       0       5\n");
    fprintf(stderr, "--'-'        J    3       0       8       1\n");
    fprintf(stderr, "----'d'      D    8       9       0       3\n");
    fprintf(stderr, "----'*2'     K    9       0      10       3\n");
    fprintf(stderr, "--------'e'  E   10      11       0       9\n");
    fprintf(stderr, "--------'f'  F   11       0       0       9\n");
    fprintf(stderr, "\n");
    fprintf(stderr, "Preorder Traversal:  *1 + a / b c - d *2 e f\n");
    fprintf(stderr, "Inorder Traversal:   a + b / c *1 d - e *2 f\n");
    fprintf(stderr, "Postorder Traversal: a b c / + d e f *2 - *1\n");
    fprintf(stderr, "\n\n\n");
    
    //                                 1
    i = NodeTree_ChildAdd(pTree, 0, pNodeG);
    if  (i == 1)
        ;
    else {
        obj_Release(pTree);
        pTree = OBJ_NIL;
        return pTree;
    }
    //                                                         2       3
    eRc = NodeTree_ChildrenAdd(pTree,NodeLink_getIndex(pNodeG), pNodeH, pNodeJ, OBJ_NIL);
    if  (ERESULT_FAILED(eRc)) {
        obj_Release(pTree);
        pTree = OBJ_NIL;
        return pTree;
    }
    //                                                         4       5
    eRc = NodeTree_ChildrenAdd(pTree,NodeLink_getIndex(pNodeH), pNodeA, pNodeI, OBJ_NIL);
    if  (ERESULT_FAILED(eRc)) {
        obj_Release(pTree);
        pTree = OBJ_NIL;
        return pTree;
    }
    //                                                         6       7
    eRc = NodeTree_ChildrenAdd(pTree,NodeLink_getIndex(pNodeI), pNodeB, pNodeC, OBJ_NIL);
    if  (ERESULT_FAILED(eRc)) {
        obj_Release(pTree);
        pTree = OBJ_NIL;
        return pTree;
    }
    //                                                         8       9
    eRc = NodeTree_ChildrenAdd(pTree,NodeLink_getIndex(pNodeJ), pNodeD, pNodeK, OBJ_NIL);
    if  (ERESULT_FAILED(eRc)) {
        obj_Release(pTree);
        pTree = OBJ_NIL;
        return pTree;
    }
    //                                                        10      11
    eRc = NodeTree_ChildrenAdd(pTree,NodeLink_getIndex(pNodeK), pNodeE, pNodeF, OBJ_NIL);
    if  (ERESULT_FAILED(eRc)) {
        obj_Release(pTree);
        pTree = OBJ_NIL;
        return pTree;
    }

    obj_Release(pNodeK);
    pNodeK = OBJ_NIL;
    obj_Release(pNodeJ);
    pNodeJ = OBJ_NIL;
    obj_Release(pNodeI);
    pNodeI = OBJ_NIL;
    obj_Release(pNodeH);
    pNodeH = OBJ_NIL;
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






int             test_NodeScan_OpenClose(
    const
    char            *pTestName
)
{
    ERESULT         eRc = ERESULT_SUCCESS;
    NODESCAN_DATA	    *pObj = OBJ_NIL;
   
    fprintf(stderr, "Performing: %s\n", pTestName);

    pObj = NodeScan_Alloc( );
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    pObj = NodeScan_Init( pObj );
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



int         test_NodeScan_ScanPost01(
    const
    char        *pTestName
)
{
    NODESCAN_DATA   *pObj = OBJ_NIL;
    NODETREE_DATA   *pTree = OBJ_NIL;
    NODEARRAY_DATA  *pArray = OBJ_NIL;
    //NODE_DATA       *pNode = OBJ_NIL;
    bool            fDump = true;
    uint32_t        i;
    uint32_t        iMax;
    const
    char            *pStrA;

    fprintf(stderr, "Performing: %s\n", pTestName);
    
    pTree = createTestTree02( );
    TINYTEST_FALSE( (OBJ_NIL == pTree) );

    pObj = NodeScan_NewFromTreePost(pTree);
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    if (pObj) {
        
        pArray = NodeScan_getArray(pObj);
        TINYTEST_FALSE( (OBJ_NIL == pArray) );
        if (pArray && fDump) {
            iMax = NodeArray_getSize(pArray);
            fprintf(stderr, "\nLinearization Postorder(%d):\n",iMax);
            XCTAssertTrue( (23 == iMax) );
            fprintf(stderr, "\tShould be: (((a(bc)/)+(d(ef)*2)-)*1)\n");
            fprintf(stderr, "\tFound:     ");
            for (i=1; i<=iMax; ++i) {
                pStrA = Node_getNameUTF8(NodeArray_Get(pArray, i));
                fprintf(stderr, "%s", pStrA);
                mem_Free((void *)pStrA);
            }
            fprintf(stderr, "\n");
        }
        
        obj_Release(pObj);
        pObj = OBJ_NIL;
    }
    
    obj_Release(pTree);
    pTree = OBJ_NIL;

    fprintf(stderr, "...%s completed.\n\n\n", pTestName);
    return 1;
}



int         test_NodeScan_ScanPre01(
    const
    char        *pTestName
)
{
    NODESCAN_DATA   *pObj = OBJ_NIL;
    NODETREE_DATA   *pTree = OBJ_NIL;
    NODEARRAY_DATA  *pArray = OBJ_NIL;
    //NODE_DATA       *pNode = OBJ_NIL;
    bool            fDump = true;
    uint32_t        i;
    uint32_t        iMax;
    const
    char            *pStrA;

    fprintf(stderr, "Performing: %s\n", pTestName);
    
    pTree = createTestTree02( );
    TINYTEST_FALSE( (OBJ_NIL == pTree) );

    pObj = NodeScan_NewFromTreePre(pTree);
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    if (pObj) {
        
        pArray = NodeScan_getArray(pObj);
        TINYTEST_FALSE( (OBJ_NIL == pArray) );
        if (pArray && fDump) {
            iMax = NodeArray_getSize(pArray);
            fprintf(stderr, "\nLinearization Preorder(%d):\n",iMax);
            XCTAssertTrue( (23 == iMax) );
            fprintf(stderr, "\tShould be: ( *1 ( + ( a / ( b c ) ) - ( d *2 ( e f ) ) ) )\n");
            fprintf(stderr, "\tFound:     ");
            for (i=1; i<=iMax; ++i) {
                pStrA = Node_getNameUTF8(NodeArray_Get(pArray, i));
                fprintf(stderr, "%s ", pStrA);
                mem_Free((void *)pStrA);
            }
            fprintf(stderr, "\n");
        }
        
        obj_Release(pObj);
        pObj = OBJ_NIL;
    }
    
    obj_Release(pTree);
    pTree = OBJ_NIL;

    fprintf(stderr, "...%s completed.\n\n\n", pTestName);
    return 1;
}




TINYTEST_START_SUITE(test_NodeScan);
    TINYTEST_ADD_TEST(test_NodeScan_ScanPre01,setUp,tearDown);
    TINYTEST_ADD_TEST(test_NodeScan_ScanPost01,setUp,tearDown);
    TINYTEST_ADD_TEST(test_NodeScan_OpenClose,setUp,tearDown);
TINYTEST_END_SUITE();

TINYTEST_MAIN_SINGLE_SUITE(test_NodeScan);





