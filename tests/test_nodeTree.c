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
#include    <name.h>
#include    <node.h>
#include    <nodeArray.h>
#include    <szTbl.h>
#include    <trace.h>
#include    <nodeTree_internal.h>



static
uint32_t        count = 0;
static
NODE_DATA       *pNodes[64];



// Example from Knuth's "The Art of Computer Programming - Volume 1", page 332???
// which consists of a forest (two trees) that have sibling roots.
static
NODETREE_DATA * createTestTree01(
)
{
    NODETREE_DATA	*pTree = OBJ_NIL;
    NODE_DATA       *pNodeA = OBJ_NIL;
    NODE_DATA       *pNodeB = OBJ_NIL;
    NODE_DATA       *pNodeC = OBJ_NIL;
    NODE_DATA       *pNodeD = OBJ_NIL;
    NODE_DATA       *pNodeE = OBJ_NIL;
    NODE_DATA       *pNodeF = OBJ_NIL;
    NODE_DATA       *pNodeG = OBJ_NIL;
    NODE_DATA       *pNodeH = OBJ_NIL;
    NODE_DATA       *pNodeJ = OBJ_NIL;
    NODE_DATA       *pNodeK = OBJ_NIL;
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
    
    pNodeA = node_NewWithUTF8Con("A", OBJ_NIL);
    if  (OBJ_NIL == pNodeA) {
        obj_Release(pTree);
        pTree = OBJ_NIL;
        return pTree;
    }
    pNodeB = node_NewWithUTF8Con("B", OBJ_NIL);
    if  (OBJ_NIL == pNodeB) {
        obj_Release(pTree);
        pTree = OBJ_NIL;
        return pTree;
    }
    pNodeC = node_NewWithUTF8Con("C", OBJ_NIL);
    if  (OBJ_NIL == pNodeC) {
        obj_Release(pTree);
        pTree = OBJ_NIL;
        return pTree;
    }
    pNodeD = node_NewWithUTF8Con("D", OBJ_NIL);
    if  (OBJ_NIL == pNodeD) {
        obj_Release(pTree);
        pTree = OBJ_NIL;
        return pTree;
    }
    pNodeE = node_NewWithUTF8Con("E", OBJ_NIL);
    if  (OBJ_NIL == pNodeE) {
        obj_Release(pTree);
        pTree = OBJ_NIL;
        return pTree;
    }
    pNodeF = node_NewWithUTF8Con("F", OBJ_NIL);
    if  (OBJ_NIL == pNodeF) {
        obj_Release(pTree);
        pTree = OBJ_NIL;
        return pTree;
    }
    pNodeG = node_NewWithUTF8Con("G", OBJ_NIL);
    if  (OBJ_NIL == pNodeG) {
        obj_Release(pTree);
        pTree = OBJ_NIL;
        return pTree;
    }
    pNodeH = node_NewWithUTF8Con("H", OBJ_NIL);
    if  (OBJ_NIL == pNodeH) {
        obj_Release(pTree);
        pTree = OBJ_NIL;
        return pTree;
    }
    pNodeJ = node_NewWithUTF8Con("J", OBJ_NIL);
    if  (OBJ_NIL == pNodeJ) {
        obj_Release(pTree);
        pTree = OBJ_NIL;
        return pTree;
    }
    pNodeK = node_NewWithUTF8Con("K", OBJ_NIL);
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

    i = nodeTree_ChildAdd(pTree, 0, pNodeA);
    if  (i == 1)
        ;
    else {
        obj_Release(pTree);
        pTree = OBJ_NIL;
        return pTree;
    }
    i = nodeTree_SiblingAdd(pTree, node_getIndex(pNodeA), pNodeD);
    if  (i == 2)
        ;
    else {
        obj_Release(pTree);
        pTree = OBJ_NIL;
        return pTree;
    }

    //                                                         3      4
    eRc = nodeTree_ChildrenAdd(pTree,node_getIndex(pNodeA), pNodeB, pNodeC, OBJ_NIL);
    if  (ERESULT_FAILED(eRc)) {
        obj_Release(pTree);
        pTree = OBJ_NIL;
        return pTree;
    }
    //                                                        5
    eRc = nodeTree_ChildrenAdd(pTree,node_getIndex(pNodeC), pNodeK, OBJ_NIL);
    if  (ERESULT_FAILED(eRc)) {
        obj_Release(pTree);
        pTree = OBJ_NIL;
        return pTree;
    }
    //                                                         6      7       8
    eRc = nodeTree_ChildrenAdd(pTree,node_getIndex(pNodeD), pNodeE, pNodeF, pNodeG, OBJ_NIL);
    if  (ERESULT_FAILED(eRc)) {
        obj_Release(pTree);
        pTree = OBJ_NIL;
        return pTree;
    }
    //                                                         9
    eRc = nodeTree_ChildrenAdd(pTree,node_getIndex(pNodeE), pNodeH, OBJ_NIL);
    if  (ERESULT_FAILED(eRc)) {
        obj_Release(pTree);
        pTree = OBJ_NIL;
        return pTree;
    }
    //                                                        10
    eRc = nodeTree_ChildrenAdd(pTree,node_getIndex(pNodeF), pNodeJ, OBJ_NIL);
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
    NODETREE_DATA    *pTree = OBJ_NIL;
    NODE_DATA       *pNodeA = OBJ_NIL;
    NODE_DATA       *pNodeB = OBJ_NIL;
    NODE_DATA       *pNodeC = OBJ_NIL;
    NODE_DATA       *pNodeD = OBJ_NIL;
    NODE_DATA       *pNodeE = OBJ_NIL;
    NODE_DATA       *pNodeF = OBJ_NIL;
    NODE_DATA       *pNodeG = OBJ_NIL;          // * (1)
    NODE_DATA       *pNodeH = OBJ_NIL;          // +
    NODE_DATA       *pNodeI = OBJ_NIL;          // /
    NODE_DATA       *pNodeJ = OBJ_NIL;          // -
    NODE_DATA       *pNodeK = OBJ_NIL;          // * (2)
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
    
    pNodeA = node_NewWithUTF8Con("a", OBJ_NIL);
    if  (OBJ_NIL == pNodeA) {
        obj_Release(pTree);
        pTree = OBJ_NIL;
        return pTree;
    }
    pNodeB = node_NewWithUTF8Con("b", OBJ_NIL);
    if  (OBJ_NIL == pNodeB) {
        obj_Release(pTree);
        pTree = OBJ_NIL;
        return pTree;
    }
    pNodeC = node_NewWithUTF8Con("c", OBJ_NIL);
    if  (OBJ_NIL == pNodeC) {
        obj_Release(pTree);
        pTree = OBJ_NIL;
        return pTree;
    }
    pNodeD = node_NewWithUTF8Con("d", OBJ_NIL);
    if  (OBJ_NIL == pNodeD) {
        obj_Release(pTree);
        pTree = OBJ_NIL;
        return pTree;
    }
    pNodeE = node_NewWithUTF8Con("e", OBJ_NIL);
    if  (OBJ_NIL == pNodeE) {
        obj_Release(pTree);
        pTree = OBJ_NIL;
        return pTree;
    }
    pNodeF = node_NewWithUTF8Con("f", OBJ_NIL);
    if  (OBJ_NIL == pNodeF) {
        obj_Release(pTree);
        pTree = OBJ_NIL;
        return pTree;
    }
    pNodeG = node_NewWithUTF8Con("*1", OBJ_NIL);
    if  (OBJ_NIL == pNodeG) {
        obj_Release(pTree);
        pTree = OBJ_NIL;
        return pTree;
    }
    pNodeH = node_NewWithUTF8Con("+", OBJ_NIL);
    if  (OBJ_NIL == pNodeH) {
        obj_Release(pTree);
        pTree = OBJ_NIL;
        return pTree;
    }
    pNodeI = node_NewWithUTF8Con("/", OBJ_NIL);
    if  (OBJ_NIL == pNodeI) {
        obj_Release(pTree);
        pTree = OBJ_NIL;
        return pTree;
    }
    
    pNodeJ = node_NewWithUTF8Con("-", OBJ_NIL);
    if  (OBJ_NIL == pNodeI) {
        obj_Release(pTree);
        pTree = OBJ_NIL;
        return pTree;
    }
    
    pNodeK = node_NewWithUTF8Con("*2", OBJ_NIL);
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
    i = nodeTree_ChildAdd(pTree, 0, pNodeG);
    if  (i == 1)
        ;
    else {
        obj_Release(pTree);
        pTree = OBJ_NIL;
        return pTree;
    }
    //                                                         2       3
    eRc = nodeTree_ChildrenAdd(pTree,node_getIndex(pNodeG), pNodeH, pNodeJ, OBJ_NIL);
    if  (ERESULT_FAILED(eRc)) {
        obj_Release(pTree);
        pTree = OBJ_NIL;
        return pTree;
    }
    //                                                         4       5
    eRc = nodeTree_ChildrenAdd(pTree,node_getIndex(pNodeH), pNodeA, pNodeI, OBJ_NIL);
    if  (ERESULT_FAILED(eRc)) {
        obj_Release(pTree);
        pTree = OBJ_NIL;
        return pTree;
    }
    //                                                         6       7
    eRc = nodeTree_ChildrenAdd(pTree,node_getIndex(pNodeI), pNodeB, pNodeC, OBJ_NIL);
    if  (ERESULT_FAILED(eRc)) {
        obj_Release(pTree);
        pTree = OBJ_NIL;
        return pTree;
    }
    //                                                         8       9
    eRc = nodeTree_ChildrenAdd(pTree,node_getIndex(pNodeJ), pNodeD, pNodeK, OBJ_NIL);
    if  (ERESULT_FAILED(eRc)) {
        obj_Release(pTree);
        pTree = OBJ_NIL;
        return pTree;
    }
    //                                                        10      11
    eRc = nodeTree_ChildrenAdd(pTree,node_getIndex(pNodeK), pNodeE, pNodeF, OBJ_NIL);
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



static
void            visitor(
    OBJ_ID          pObject,            // Object supplied below
    NODETREE_DATA   *pTree,             // Our Tree
    NODE_DATA       *pNode,             // Current Node
    uint16_t        indent
)
{
    pNodes[count] = pNode;
    ++count;
}


static
void            visitorReset(
)
{
    for (int i=0; i<20; ++i) {
        pNodes[i] = OBJ_NIL;
    }
    count = 0;
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

    szTbl_SharedReset();
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






int         test_nodeTree_OpenClose(
    const
    char        *pTestName
)
{
    NODETREE_DATA *pObj = OBJ_NIL;
   
    fprintf(stderr, "Performing: %s\n", pTestName);
    
    pObj = nodeTree_Alloc( );
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    pObj = nodeTree_Init( pObj );
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    if (pObj) {

        // Test something.

        obj_Release(pObj);
        pObj = OBJ_NIL;
    }

    fprintf(stderr, "...%s completed.\n\n", pTestName);
    return 1;
}



int         test_nodeTree_UpDown01(
    const
    char        *pTestName
)
{
    NODETREE_DATA	*pObj = OBJ_NIL;
    NODEARRAY_DATA  *pArray = OBJ_NIL;
    NODE_DATA       *pEntry = OBJ_NIL;
    uint32_t        i;
    uint32_t        iMax;
    const
    char            *pStrA;
    ERESULT         eRc = ERESULT_SUCCESS;
    ASTR_DATA       *pStr = OBJ_NIL;
    
    fprintf(stderr, "Performing: %s\n", pTestName);
    
    pObj = createTestTree01();
    XCTAssertFalse( (pObj == OBJ_NIL) );
    if (pObj) {

#ifdef XYZZY
        pStr = nodeTree_ToDebugString(pObj, 0);
        fprintf(stderr, "Debug = %s\n\n\n",AStr_getData(pStr));
        obj_Release(pStr);
        pStr = OBJ_NIL;
#endif
        
        i = nodeTree_SiblingCount(pObj, 1);
        XCTAssertTrue( (i == 1) );
        i = nodeTree_ChildCount(pObj, 1);
        XCTAssertTrue( (i == 2) );
        i = nodeTree_ChildCount(pObj, 2);
        XCTAssertTrue( (i == 3) );
        i = nodeTree_ChildCount(pObj, 3);
        XCTAssertTrue( (i == 0) );
        i = nodeTree_ChildCount(pObj, 4);
        XCTAssertTrue( (i == 1) );
        i = nodeTree_ChildCount(pObj, 5);
        XCTAssertTrue( (i == 0) );
        i = nodeTree_ChildCount(pObj, 6);
        XCTAssertTrue( (i == 1) );
        i = nodeTree_ChildCount(pObj, 7);
        XCTAssertTrue( (i == 1) );
        i = nodeTree_ChildCount(pObj, 8);
        XCTAssertTrue( (i == 0) );
        i = nodeTree_ChildCount(pObj, 9);
        XCTAssertTrue( (i == 0) );
        i = nodeTree_ChildCount(pObj, 10);
        XCTAssertTrue( (i == 0) );

        // Verify that the linkage fields are correct.
        pEntry = objArray_Get(pObj->pArray, 1);
        XCTAssertFalse( (pEntry == OBJ_NIL) );
        XCTAssertTrue( (node_getIndex(pEntry) == 1) );
        XCTAssertTrue( (node_getChild(pEntry) == 3) );
        XCTAssertTrue( (node_getSibling(pEntry) == 2) );
        XCTAssertTrue( (node_getParent(pEntry) == 0) );
        pEntry = objArray_Get(pObj->pArray, 2);
        XCTAssertFalse( (pEntry == OBJ_NIL) );
        XCTAssertTrue( (node_getIndex(pEntry) == 2) );
        XCTAssertTrue( (node_getChild(pEntry) == 6) );
        XCTAssertTrue( (node_getSibling(pEntry) == 0) );
        XCTAssertTrue( (node_getParent(pEntry) == 0) );
        pEntry = objArray_Get(pObj->pArray, 3);
        XCTAssertFalse( (pEntry == OBJ_NIL) );
        XCTAssertTrue( (node_getIndex(pEntry) == 3) );
        XCTAssertTrue( (node_getChild(pEntry) == 0) );
        XCTAssertTrue( (node_getSibling(pEntry) == 4) );
        XCTAssertTrue( (node_getParent(pEntry) == 1) );
        pEntry = objArray_Get(pObj->pArray, 4);
        XCTAssertFalse( (pEntry == OBJ_NIL) );
        XCTAssertTrue( (node_getIndex(pEntry) == 4) );
        XCTAssertTrue( (node_getChild(pEntry) == 5) );
        XCTAssertTrue( (node_getSibling(pEntry) == 0) );
        XCTAssertTrue( (node_getParent(pEntry) == 1) );
        pEntry = objArray_Get(pObj->pArray, 5);
        XCTAssertFalse( (pEntry == OBJ_NIL) );
        XCTAssertTrue( (node_getIndex(pEntry) == 5) );
        XCTAssertTrue( (node_getChild(pEntry) == 0) );
        XCTAssertTrue( (node_getSibling(pEntry) == 0) );
        XCTAssertTrue( (node_getParent(pEntry) == 4) );
        pEntry = objArray_Get(pObj->pArray, 6);
        XCTAssertFalse( (pEntry == OBJ_NIL) );
        XCTAssertTrue( (node_getIndex(pEntry) == 6) );
        XCTAssertTrue( (node_getChild(pEntry) == 9) );
        XCTAssertTrue( (node_getSibling(pEntry) == 7) );
        XCTAssertTrue( (node_getParent(pEntry) == 2) );
        pEntry = objArray_Get(pObj->pArray, 7);
        XCTAssertFalse( (pEntry == OBJ_NIL) );
        XCTAssertTrue( (node_getIndex(pEntry) == 7) );
        XCTAssertTrue( (node_getChild(pEntry) == 10) );
        XCTAssertTrue( (node_getSibling(pEntry) == 8) );
        XCTAssertTrue( (node_getParent(pEntry) == 2) );
        pEntry = objArray_Get(pObj->pArray, 8);
        XCTAssertFalse( (pEntry == OBJ_NIL) );
        XCTAssertTrue( (node_getIndex(pEntry) == 8) );
        XCTAssertTrue( (node_getChild(pEntry) == 0) );
        XCTAssertTrue( (node_getSibling(pEntry) == 0) );
        XCTAssertTrue( (node_getParent(pEntry) == 2) );
        pEntry = objArray_Get(pObj->pArray, 9);
        XCTAssertFalse( (pEntry == OBJ_NIL) );
        XCTAssertTrue( (node_getIndex(pEntry) == 9) );
        XCTAssertTrue( (node_getChild(pEntry) == 0) );
        XCTAssertTrue( (node_getSibling(pEntry) == 0) );
        XCTAssertTrue( (node_getParent(pEntry) == 6) );
        pEntry = objArray_Get(pObj->pArray, 10);
        XCTAssertFalse( (pEntry == OBJ_NIL) );
        XCTAssertTrue( (node_getIndex(pEntry) == 10) );
        XCTAssertTrue( (node_getChild(pEntry) == 0) );
        XCTAssertTrue( (node_getSibling(pEntry) == 0) );
        XCTAssertTrue( (node_getParent(pEntry) == 7) );

#ifdef XYZZY
        visitorReset();
        eRc = nodeTree_VisitInorder(pObj, visitor, NULL);
        XCTAssertFalse( (ERESULT_FAILED(eRc)) );
        fprintf(stderr, "\nInorder(%d):\n", count);
        XCTAssertTrue( (10 == count) );
        fprintf(stderr, "\tABCKDEHFJG (should be)\n\t");
        for (i=0; i<count; ++i) {
            pStrA = node_getNameUTF8(pNodes[i]);
            fprintf(stderr, "%c", *pStrA);
            mem_Free((void *)pStrA);
            pStrA = NULL;
        }
        fprintf(stderr, " (actual)\n");
        eRc = name_CompareA(node_getName(pNodes[0]),"A");
        XCTAssertTrue( (ERESULT_SUCCESS_EQUAL == eRc) );
        eRc = name_CompareA(node_getName(pNodes[1]),"B");
        XCTAssertTrue( (ERESULT_SUCCESS_EQUAL == eRc) );
        eRc = name_CompareA(node_getName(pNodes[2]),"C");
        XCTAssertTrue( (ERESULT_SUCCESS_EQUAL == eRc) );
        eRc = name_CompareA(node_getName(pNodes[3]),"K");
        XCTAssertTrue( (ERESULT_SUCCESS_EQUAL == eRc) );
        eRc = name_CompareA(node_getName(pNodes[4]),"D");
        XCTAssertTrue( (ERESULT_SUCCESS_EQUAL == eRc) );
        eRc = name_CompareA(node_getName(pNodes[5]),"E");
        XCTAssertTrue( (ERESULT_SUCCESS_EQUAL == eRc) );
        eRc = name_CompareA(node_getName(pNodes[6]),"H");
        XCTAssertTrue( (ERESULT_SUCCESS_EQUAL == eRc) );
        eRc = name_CompareA(node_getName(pNodes[7]),"F");
        XCTAssertTrue( (ERESULT_SUCCESS_EQUAL == eRc) );
        eRc = name_CompareA(node_getName(pNodes[8]),"J");
        XCTAssertTrue( (ERESULT_SUCCESS_EQUAL == eRc) );
        eRc = name_CompareA(node_getName(pNodes[9]),"G");
        XCTAssertTrue( (ERESULT_SUCCESS_EQUAL == eRc) );
#endif

        visitorReset();
        eRc = nodeTree_VisitPostorder(pObj, visitor, NULL);
        XCTAssertFalse( (ERESULT_FAILED(eRc)) );
        fprintf(stderr, "\nPostorder(%d):\n",count);
        XCTAssertTrue( (10 == count) );
        fprintf(stderr, "\tBKCAHEJFGD (should be)\n\t");
        for (i=0; i<count; ++i) {
            pStrA = node_getNameUTF8(pNodes[i]);
            fprintf(stderr, "%c", *pStrA);
            mem_Free((void *)pStrA);
            pStrA = NULL;
        }
        fprintf(stderr, " (actual)\n");
        eRc = name_CompareA(node_getName(pNodes[0]),"B");
        XCTAssertTrue( (ERESULT_SUCCESS_EQUAL == eRc) );
        eRc = name_CompareA(node_getName(pNodes[1]),"K");
        XCTAssertTrue( (ERESULT_SUCCESS_EQUAL == eRc) );
        eRc = name_CompareA(node_getName(pNodes[2]),"C");
        XCTAssertTrue( (ERESULT_SUCCESS_EQUAL == eRc) );
        eRc = name_CompareA(node_getName(pNodes[3]),"A");
        XCTAssertTrue( (ERESULT_SUCCESS_EQUAL == eRc) );
        eRc = name_CompareA(node_getName(pNodes[4]),"H");
        XCTAssertTrue( (ERESULT_SUCCESS_EQUAL == eRc) );
        eRc = name_CompareA(node_getName(pNodes[5]),"E");
        XCTAssertTrue( (ERESULT_SUCCESS_EQUAL == eRc) );
        eRc = name_CompareA(node_getName(pNodes[6]),"J");
        XCTAssertTrue( (ERESULT_SUCCESS_EQUAL == eRc) );
        eRc = name_CompareA(node_getName(pNodes[7]),"F");
        XCTAssertTrue( (ERESULT_SUCCESS_EQUAL == eRc) );
        eRc = name_CompareA(node_getName(pNodes[8]),"G");
        XCTAssertTrue( (ERESULT_SUCCESS_EQUAL == eRc) );
        eRc = name_CompareA(node_getName(pNodes[9]),"D");
        XCTAssertTrue( (ERESULT_SUCCESS_EQUAL == eRc) );

        visitorReset();
        eRc = nodeTree_VisitPreorder(pObj, visitor, NULL);
        XCTAssertFalse( (ERESULT_FAILED(eRc)) );
        fprintf(stderr, "\nPreorder(%d):\n",count);
        XCTAssertTrue( (10 == count) );
        fprintf(stderr, "\tABCKDEHFJG (should be)\n\t");
        for (i=0; i<count; ++i) {
            pStrA = node_getNameUTF8(pNodes[i]);
            fprintf(stderr, "%c", *pStrA);
            mem_Free((void *)pStrA);
            pStrA = NULL;
        }
        fprintf(stderr, " (actual)\n\n");
        eRc = name_CompareA(node_getName(pNodes[0]),"A");
        XCTAssertTrue( (ERESULT_SUCCESS_EQUAL == eRc) );
        eRc = name_CompareA(node_getName(pNodes[1]),"B");
        XCTAssertTrue( (ERESULT_SUCCESS_EQUAL == eRc) );
        eRc = name_CompareA(node_getName(pNodes[2]),"C");
        XCTAssertTrue( (ERESULT_SUCCESS_EQUAL == eRc) );
        eRc = name_CompareA(node_getName(pNodes[3]),"K");
        XCTAssertTrue( (ERESULT_SUCCESS_EQUAL == eRc) );
        eRc = name_CompareA(node_getName(pNodes[4]),"D");
        XCTAssertTrue( (ERESULT_SUCCESS_EQUAL == eRc) );
        eRc = name_CompareA(node_getName(pNodes[5]),"E");
        XCTAssertTrue( (ERESULT_SUCCESS_EQUAL == eRc) );
        eRc = name_CompareA(node_getName(pNodes[6]),"H");
        XCTAssertTrue( (ERESULT_SUCCESS_EQUAL == eRc) );
        eRc = name_CompareA(node_getName(pNodes[7]),"F");
        XCTAssertTrue( (ERESULT_SUCCESS_EQUAL == eRc) );
        eRc = name_CompareA(node_getName(pNodes[8]),"J");
        XCTAssertTrue( (ERESULT_SUCCESS_EQUAL == eRc) );
        eRc = name_CompareA(node_getName(pNodes[9]),"G");
        XCTAssertTrue( (ERESULT_SUCCESS_EQUAL == eRc) );

        visitorReset();
        eRc = nodeTree_VisitBreadthFirst(pObj, visitor, NULL);
        XCTAssertFalse( (ERESULT_FAILED(eRc)) );
        fprintf(stderr, "\nBreadthFirst(%d):\n",count);
        XCTAssertTrue( (10 == count) );
        fprintf(stderr, "\tADBCEFGKHJ (should be)\n\t");
        for (i=0; i<count; ++i) {
            pStrA = node_getNameUTF8(pNodes[i]);
            fprintf(stderr, "%c", *pStrA);
            mem_Free((void *)pStrA);
            pStrA = NULL;
        }
        fprintf(stderr, " (actual)\n\n");
        eRc = name_CompareA(node_getName(pNodes[0]),"A");
        XCTAssertTrue( (ERESULT_SUCCESS_EQUAL == eRc) );
        eRc = name_CompareA(node_getName(pNodes[1]),"D");
        XCTAssertTrue( (ERESULT_SUCCESS_EQUAL == eRc) );
        eRc = name_CompareA(node_getName(pNodes[2]),"B");
        XCTAssertTrue( (ERESULT_SUCCESS_EQUAL == eRc) );
        eRc = name_CompareA(node_getName(pNodes[3]),"C");
        XCTAssertTrue( (ERESULT_SUCCESS_EQUAL == eRc) );
        eRc = name_CompareA(node_getName(pNodes[4]),"E");
        XCTAssertTrue( (ERESULT_SUCCESS_EQUAL == eRc) );
        eRc = name_CompareA(node_getName(pNodes[5]),"F");
        XCTAssertTrue( (ERESULT_SUCCESS_EQUAL == eRc) );
        eRc = name_CompareA(node_getName(pNodes[6]),"G");
        XCTAssertTrue( (ERESULT_SUCCESS_EQUAL == eRc) );
        eRc = name_CompareA(node_getName(pNodes[7]),"K");
        XCTAssertTrue( (ERESULT_SUCCESS_EQUAL == eRc) );
        eRc = name_CompareA(node_getName(pNodes[8]),"H");
        XCTAssertTrue( (ERESULT_SUCCESS_EQUAL == eRc) );
        eRc = name_CompareA(node_getName(pNodes[9]),"J");
        XCTAssertTrue( (ERESULT_SUCCESS_EQUAL == eRc) );

        pArray = nodeTree_ToLinearizationPost(pObj);
        XCTAssertFalse( (OBJ_NIL == pArray) );
        iMax = nodeArray_getSize(pArray);
        fprintf(stderr, "\nLinearization Postorder(%d):\n", iMax);
        XCTAssertTrue( (22 == iMax) );
        fprintf(stderr, "\tShould be: ((B(K)C)A((H)E(J)FG)D)\n");
        fprintf(stderr, "\tFound:     ");
        for (i=1; i<=iMax; ++i) {
            pStrA = node_getNameUTF8(nodeArray_Get(pArray, i));
            fprintf(stderr, "%s", pStrA);
            mem_Free((void *)pStrA);
        }
        fprintf(stderr, "\n");
        eRc = name_CompareA(node_getName(nodeArray_Get(pArray,  1)),"(");
        XCTAssertTrue( (ERESULT_SUCCESS_EQUAL == eRc) );
        eRc = name_CompareA(node_getName(nodeArray_Get(pArray,  2)),"(");
        XCTAssertTrue( (ERESULT_SUCCESS_EQUAL == eRc) );
        eRc = name_CompareA(node_getName(nodeArray_Get(pArray,  3)),"B");
        XCTAssertTrue( (ERESULT_SUCCESS_EQUAL == eRc) );
        eRc = name_CompareA(node_getName(nodeArray_Get(pArray,  4)),"(");
        XCTAssertTrue( (ERESULT_SUCCESS_EQUAL == eRc) );
        eRc = name_CompareA(node_getName(nodeArray_Get(pArray,  5)),"K");
        XCTAssertTrue( (ERESULT_SUCCESS_EQUAL == eRc) );
        eRc = name_CompareA(node_getName(nodeArray_Get(pArray,  6)),")");
        XCTAssertTrue( (ERESULT_SUCCESS_EQUAL == eRc) );
        eRc = name_CompareA(node_getName(nodeArray_Get(pArray,  7)),"C");
        XCTAssertTrue( (ERESULT_SUCCESS_EQUAL == eRc) );
        eRc = name_CompareA(node_getName(nodeArray_Get(pArray,  8)),")");
        XCTAssertTrue( (ERESULT_SUCCESS_EQUAL == eRc) );
        eRc = name_CompareA(node_getName(nodeArray_Get(pArray,  9)),"A");
        XCTAssertTrue( (ERESULT_SUCCESS_EQUAL == eRc) );
        eRc = name_CompareA(node_getName(nodeArray_Get(pArray, 10)),"(");
        XCTAssertTrue( (ERESULT_SUCCESS_EQUAL == eRc) );
        eRc = name_CompareA(node_getName(nodeArray_Get(pArray, 11)),"(");
        XCTAssertTrue( (ERESULT_SUCCESS_EQUAL == eRc) );
        eRc = name_CompareA(node_getName(nodeArray_Get(pArray, 12)),"H");
        XCTAssertTrue( (ERESULT_SUCCESS_EQUAL == eRc) );
        eRc = name_CompareA(node_getName(nodeArray_Get(pArray, 13)),")");
        XCTAssertTrue( (ERESULT_SUCCESS_EQUAL == eRc) );
        eRc = name_CompareA(node_getName(nodeArray_Get(pArray, 14)),"E");
        XCTAssertTrue( (ERESULT_SUCCESS_EQUAL == eRc) );
        eRc = name_CompareA(node_getName(nodeArray_Get(pArray, 15)),"(");
        XCTAssertTrue( (ERESULT_SUCCESS_EQUAL == eRc) );
        eRc = name_CompareA(node_getName(nodeArray_Get(pArray, 16)),"J");
        XCTAssertTrue( (ERESULT_SUCCESS_EQUAL == eRc) );
        eRc = name_CompareA(node_getName(nodeArray_Get(pArray, 17)),")");
        XCTAssertTrue( (ERESULT_SUCCESS_EQUAL == eRc) );
        eRc = name_CompareA(node_getName(nodeArray_Get(pArray, 18)),"F");
        XCTAssertTrue( (ERESULT_SUCCESS_EQUAL == eRc) );
        eRc = name_CompareA(node_getName(nodeArray_Get(pArray, 19)),"G");
        XCTAssertTrue( (ERESULT_SUCCESS_EQUAL == eRc) );
        eRc = name_CompareA(node_getName(nodeArray_Get(pArray, 20)),")");
        XCTAssertTrue( (ERESULT_SUCCESS_EQUAL == eRc) );
        eRc = name_CompareA(node_getName(nodeArray_Get(pArray, 21)),"D");
        XCTAssertTrue( (ERESULT_SUCCESS_EQUAL == eRc) );
        eRc = name_CompareA(node_getName(nodeArray_Get(pArray, 22)),")");
        XCTAssertTrue( (ERESULT_SUCCESS_EQUAL == eRc) );
        obj_Release(pArray);
        pArray = OBJ_NIL;
        fprintf(stderr, "\n\n\n");
        
        pArray = nodeTree_ToLinearizationPre(pObj);
        XCTAssertFalse( (OBJ_NIL == pArray) );
        iMax = nodeArray_getSize(pArray);
        fprintf(stderr, "\nLinearization Preorder(%d):\n",iMax);
        XCTAssertTrue( (22 == iMax) );
        fprintf(stderr, "\tShould be: (A(BC(K))D(E(H)F(J)G))\n");
        fprintf(stderr, "\tFound:     ");
        for (i=1; i<=iMax; ++i) {
            pStrA = node_getNameUTF8(nodeArray_Get(pArray, i));
            fprintf(stderr, "%s", pStrA);
            mem_Free((void *)pStrA);
        }
        fprintf(stderr, "\n");
        eRc = name_CompareA(node_getName(nodeArray_Get(pArray,  1)),"(");
        XCTAssertTrue( (ERESULT_SUCCESS_EQUAL == eRc) );
        eRc = name_CompareA(node_getName(nodeArray_Get(pArray,  2)),"A");
        XCTAssertTrue( (ERESULT_SUCCESS_EQUAL == eRc) );
        eRc = name_CompareA(node_getName(nodeArray_Get(pArray,  3)),"(");
        XCTAssertTrue( (ERESULT_SUCCESS_EQUAL == eRc) );
        eRc = name_CompareA(node_getName(nodeArray_Get(pArray,  4)),"B");
        XCTAssertTrue( (ERESULT_SUCCESS_EQUAL == eRc) );
        eRc = name_CompareA(node_getName(nodeArray_Get(pArray,  5)),"C");
        XCTAssertTrue( (ERESULT_SUCCESS_EQUAL == eRc) );
        eRc = name_CompareA(node_getName(nodeArray_Get(pArray,  6)),"(");
        XCTAssertTrue( (ERESULT_SUCCESS_EQUAL == eRc) );
        eRc = name_CompareA(node_getName(nodeArray_Get(pArray,  7)),"K");
        XCTAssertTrue( (ERESULT_SUCCESS_EQUAL == eRc) );
        eRc = name_CompareA(node_getName(nodeArray_Get(pArray,  8)),")");
        XCTAssertTrue( (ERESULT_SUCCESS_EQUAL == eRc) );
        eRc = name_CompareA(node_getName(nodeArray_Get(pArray,  9)),")");
        XCTAssertTrue( (ERESULT_SUCCESS_EQUAL == eRc) );
        eRc = name_CompareA(node_getName(nodeArray_Get(pArray, 10)),"D");
        XCTAssertTrue( (ERESULT_SUCCESS_EQUAL == eRc) );
        eRc = name_CompareA(node_getName(nodeArray_Get(pArray, 11)),"(");
        XCTAssertTrue( (ERESULT_SUCCESS_EQUAL == eRc) );
        eRc = name_CompareA(node_getName(nodeArray_Get(pArray, 12)),"E");
        XCTAssertTrue( (ERESULT_SUCCESS_EQUAL == eRc) );
        eRc = name_CompareA(node_getName(nodeArray_Get(pArray, 13)),"(");
        XCTAssertTrue( (ERESULT_SUCCESS_EQUAL == eRc) );
        eRc = name_CompareA(node_getName(nodeArray_Get(pArray, 14)),"H");
        XCTAssertTrue( (ERESULT_SUCCESS_EQUAL == eRc) );
        eRc = name_CompareA(node_getName(nodeArray_Get(pArray, 15)),")");
        XCTAssertTrue( (ERESULT_SUCCESS_EQUAL == eRc) );
        eRc = name_CompareA(node_getName(nodeArray_Get(pArray, 16)),"F");
        XCTAssertTrue( (ERESULT_SUCCESS_EQUAL == eRc) );
        eRc = name_CompareA(node_getName(nodeArray_Get(pArray, 17)),"(");
        XCTAssertTrue( (ERESULT_SUCCESS_EQUAL == eRc) );
        eRc = name_CompareA(node_getName(nodeArray_Get(pArray, 18)),"J");
        XCTAssertTrue( (ERESULT_SUCCESS_EQUAL == eRc) );
        eRc = name_CompareA(node_getName(nodeArray_Get(pArray, 19)),")");
        XCTAssertTrue( (ERESULT_SUCCESS_EQUAL == eRc) );
        eRc = name_CompareA(node_getName(nodeArray_Get(pArray, 20)),"G");
        XCTAssertTrue( (ERESULT_SUCCESS_EQUAL == eRc) );
        eRc = name_CompareA(node_getName(nodeArray_Get(pArray, 21)),")");
        XCTAssertTrue( (ERESULT_SUCCESS_EQUAL == eRc) );
        eRc = name_CompareA(node_getName(nodeArray_Get(pArray, 22)),")");
        XCTAssertTrue( (ERESULT_SUCCESS_EQUAL == eRc) );
        obj_Release(pArray);
        pArray = OBJ_NIL;
        fprintf(stderr, "\n\n\n");
        
#ifdef XYZZY
        eRc = nodeTree_NodeDelete(pObj, 3);     // Delete E(3) which includes F(7),G(9),H(8)
        XCTAssertFalse( (ERESULT_FAILED(eRc)) );
        
        // Verify that the linkage fields are correct.
        pEntry = objArray_Get(pObj->pArray, 1);
        XCTAssertFalse( (pEntry == OBJ_NIL) );
        XCTAssertTrue( (node_getIndex(pEntry) == 1) );
        XCTAssertTrue( (node_getSibling(pEntry) == 0) );
        XCTAssertTrue( (node_getChild(pEntry) == 2) );
        XCTAssertTrue( (node_getParent(pEntry) == 0) );
        pEntry = objArray_Get(pObj->pArray, 2);
        XCTAssertFalse( (pEntry == OBJ_NIL) );
        XCTAssertTrue( (node_getIndex(pEntry) == 2) );
        XCTAssertTrue( (node_getSibling(pEntry) == 4) );
        XCTAssertTrue( (node_getChild(pEntry) == 5) );
        XCTAssertTrue( (node_getParent(pEntry) == 1) );
        pEntry = objArray_Get(pObj->pArray, 3);
        XCTAssertTrue( (pEntry == OBJ_NIL) );
        pEntry = objArray_Get(pObj->pArray, 4);
        XCTAssertFalse( (pEntry == OBJ_NIL) );
        XCTAssertTrue( (node_getIndex(pEntry) == 4) );
        XCTAssertTrue( (node_getSibling(pEntry) == 0) );
        XCTAssertTrue( (node_getChild(pEntry) == 0) );
        XCTAssertTrue( (node_getParent(pEntry) == 1) );
        pEntry = objArray_Get(pObj->pArray, 5);
        XCTAssertFalse( (pEntry == OBJ_NIL) );
        XCTAssertTrue( (node_getIndex(pEntry) == 5) );
        XCTAssertTrue( (node_getSibling(pEntry) == 6) );
        XCTAssertTrue( (node_getChild(pEntry) == 0) );
        XCTAssertTrue( (node_getParent(pEntry) == 2) );
        pEntry = objArray_Get(pObj->pArray, 6);
        XCTAssertFalse( (pEntry == OBJ_NIL) );
        XCTAssertTrue( (node_getIndex(pEntry) == 6) );
        XCTAssertTrue( (node_getSibling(pEntry) == 0) );
        XCTAssertTrue( (node_getChild(pEntry) == 0) );
        XCTAssertTrue( (node_getParent(pEntry) == 2) );
        pEntry = objArray_Get(pObj->pArray, 7);
        XCTAssertTrue( (pEntry == OBJ_NIL) );
        pEntry = objArray_Get(pObj->pArray, 8);
        XCTAssertTrue( (pEntry == OBJ_NIL) );
        pEntry = objArray_Get(pObj->pArray, 9);
        XCTAssertTrue( (pEntry == OBJ_NIL) );
#endif
        
        XCTAssertTrue( (obj_IsFlag(pObj, OBJ_FLAG_ALLOC)) );
        obj_Release(pObj);
        pObj = OBJ_NIL;
    }
    
    fprintf(stderr, "...%s completed.\n\n", pTestName);
    return 1;
}



int         test_nodeTree_Delete01(
    const
    char            *pTestName
)
{
    NODETREE_DATA   *pObj = OBJ_NIL;
    NODE_DATA       *pEntry = OBJ_NIL;
    uint32_t        i;
    ERESULT         eRc = ERESULT_SUCCESS;
    
    fprintf(stderr, "Performing: %s\n", pTestName);
    
    pObj = createTestTree01();
    XCTAssertFalse( (pObj == OBJ_NIL) );
    if (pObj) {
        
        i = nodeTree_ChildCount(pObj, 1);
        XCTAssertFalse( (ERESULT_FAILED(eRc)) );
        XCTAssertTrue( (i == 3) );
        i = nodeTree_ChildCount(pObj, 2);
        XCTAssertFalse( (ERESULT_FAILED(eRc)) );
        XCTAssertTrue( (i == 2) );
        i = nodeTree_ChildCount(pObj, 7);
        XCTAssertFalse( (ERESULT_FAILED(eRc)) );
        XCTAssertTrue( (i == 1) );
        i = nodeTree_ChildCount(pObj, 9);
        XCTAssertFalse( (ERESULT_FAILED(eRc)) );
        XCTAssertTrue( (i == 0) );
        
        // Verify that the linkage fields are correct.
        pEntry = objArray_Get(pObj->pArray, 1);
        XCTAssertFalse( (pEntry == OBJ_NIL) );
        XCTAssertTrue( (node_getIndex(pEntry) == 1) );
        XCTAssertTrue( (node_getSibling(pEntry) == 0) );
        XCTAssertTrue( (node_getChild(pEntry) == 2) );
        XCTAssertTrue( (node_getParent(pEntry) == 0) );
        pEntry = objArray_Get(pObj->pArray, 2);
        XCTAssertFalse( (pEntry == OBJ_NIL) );
        XCTAssertTrue( (node_getIndex(pEntry) == 2) );
        XCTAssertTrue( (node_getSibling(pEntry) == 3) );
        XCTAssertTrue( (node_getChild(pEntry) == 5) );
        XCTAssertTrue( (node_getParent(pEntry) == 1) );
        pEntry = objArray_Get(pObj->pArray, 3);
        XCTAssertFalse( (pEntry == OBJ_NIL) );
        XCTAssertTrue( (node_getIndex(pEntry) == 3) );
        XCTAssertTrue( (node_getSibling(pEntry) == 4) );
        XCTAssertTrue( (node_getChild(pEntry) == 7) );
        XCTAssertTrue( (node_getParent(pEntry) == 1) );
        pEntry = objArray_Get(pObj->pArray, 4);
        XCTAssertFalse( (pEntry == OBJ_NIL) );
        XCTAssertTrue( (node_getIndex(pEntry) == 4) );
        XCTAssertTrue( (node_getSibling(pEntry) == 0) );
        XCTAssertTrue( (node_getChild(pEntry) == 0) );
        XCTAssertTrue( (node_getParent(pEntry) == 1) );
        pEntry = objArray_Get(pObj->pArray, 5);
        XCTAssertFalse( (pEntry == OBJ_NIL) );
        XCTAssertTrue( (node_getIndex(pEntry) == 5) );
        XCTAssertTrue( (node_getSibling(pEntry) == 6) );
        XCTAssertTrue( (node_getChild(pEntry) == 0) );
        XCTAssertTrue( (node_getParent(pEntry) == 2) );
        pEntry = objArray_Get(pObj->pArray, 6);
        XCTAssertFalse( (pEntry == OBJ_NIL) );
        XCTAssertTrue( (node_getIndex(pEntry) == 6) );
        XCTAssertTrue( (node_getSibling(pEntry) == 0) );
        XCTAssertTrue( (node_getChild(pEntry) == 0) );
        XCTAssertTrue( (node_getParent(pEntry) == 2) );
        pEntry = objArray_Get(pObj->pArray, 7);
        XCTAssertFalse( (pEntry == OBJ_NIL) );
        XCTAssertTrue( (node_getIndex(pEntry) == 7) );
        XCTAssertTrue( (node_getSibling(pEntry) == 8) );
        XCTAssertTrue( (node_getChild(pEntry) == 9) );
        XCTAssertTrue( (node_getParent(pEntry) == 3) );
        pEntry = objArray_Get(pObj->pArray, 8);
        XCTAssertFalse( (pEntry == OBJ_NIL) );
        XCTAssertTrue( (node_getIndex(pEntry) == 8) );
        XCTAssertTrue( (node_getSibling(pEntry) == 0) );
        XCTAssertTrue( (node_getChild(pEntry) == 0) );
        XCTAssertTrue( (node_getParent(pEntry) == 3) );
        pEntry = objArray_Get(pObj->pArray, 9);
        XCTAssertFalse( (pEntry == OBJ_NIL) );
        XCTAssertTrue( (node_getIndex(pEntry) == 9) );
        XCTAssertTrue( (node_getSibling(pEntry) == 0) );
        XCTAssertTrue( (node_getChild(pEntry) == 0) );
        XCTAssertTrue( (node_getParent(pEntry) == 7) );
        
        eRc = nodeTree_ChildrenMove(pObj, 2, 3);    // Delete C(5), D(6) after
        //                                              // child H(8) of E(3)
        XCTAssertFalse( (ERESULT_FAILED(eRc)) );
        
        // Verify that the linkage fields are correct.
        pEntry = objArray_Get(pObj->pArray, 1);
        XCTAssertFalse( (pEntry == OBJ_NIL) );
        XCTAssertTrue( (node_getIndex(pEntry) == 1) );
        XCTAssertTrue( (node_getSibling(pEntry) == 0) );
        XCTAssertTrue( (node_getChild(pEntry) == 2) );
        XCTAssertTrue( (node_getParent(pEntry) == 0) );
        pEntry = objArray_Get(pObj->pArray, 2);
        XCTAssertFalse( (pEntry == OBJ_NIL) );
        XCTAssertTrue( (node_getIndex(pEntry) == 2) );
        XCTAssertTrue( (node_getSibling(pEntry) == 3) );
        XCTAssertTrue( (node_getChild(pEntry) == 0) );
        XCTAssertTrue( (node_getParent(pEntry) == 1) );
        pEntry = objArray_Get(pObj->pArray, 3);
        XCTAssertFalse( (pEntry == OBJ_NIL) );
        XCTAssertTrue( (node_getIndex(pEntry) == 3) );
        XCTAssertTrue( (node_getSibling(pEntry) == 4) );
        XCTAssertTrue( (node_getChild(pEntry) == 7) );
        XCTAssertTrue( (node_getParent(pEntry) == 1) );
        pEntry = objArray_Get(pObj->pArray, 4);
        XCTAssertFalse( (pEntry == OBJ_NIL) );
        XCTAssertTrue( (node_getIndex(pEntry) == 4) );
        XCTAssertTrue( (node_getSibling(pEntry) == 0) );
        XCTAssertTrue( (node_getChild(pEntry) == 0) );
        XCTAssertTrue( (node_getParent(pEntry) == 1) );
        pEntry = objArray_Get(pObj->pArray, 5);
        XCTAssertFalse( (pEntry == OBJ_NIL) );
        XCTAssertTrue( (node_getIndex(pEntry) == 5) );
        XCTAssertTrue( (node_getSibling(pEntry) == 6) );
        XCTAssertTrue( (node_getChild(pEntry) == 0) );
        XCTAssertTrue( (node_getParent(pEntry) == 3) );
        pEntry = objArray_Get(pObj->pArray, 6);
        XCTAssertFalse( (pEntry == OBJ_NIL) );
        XCTAssertTrue( (node_getIndex(pEntry) == 6) );
        XCTAssertTrue( (node_getSibling(pEntry) == 0) );
        XCTAssertTrue( (node_getChild(pEntry) == 0) );
        XCTAssertTrue( (node_getParent(pEntry) == 3) );
        pEntry = objArray_Get(pObj->pArray, 7);
        XCTAssertFalse( (pEntry == OBJ_NIL) );
        XCTAssertTrue( (node_getIndex(pEntry) == 7) );
        XCTAssertTrue( (node_getSibling(pEntry) == 8) );
        XCTAssertTrue( (node_getChild(pEntry) == 9) );
        XCTAssertTrue( (node_getParent(pEntry) == 3) );
        pEntry = objArray_Get(pObj->pArray, 8);
        XCTAssertFalse( (pEntry == OBJ_NIL) );
        XCTAssertTrue( (node_getIndex(pEntry) == 8) );
        XCTAssertTrue( (node_getSibling(pEntry) == 5) );
        XCTAssertTrue( (node_getChild(pEntry) == 0) );
        XCTAssertTrue( (node_getParent(pEntry) == 3) );
        pEntry = objArray_Get(pObj->pArray, 9);
        XCTAssertFalse( (pEntry == OBJ_NIL) );
        XCTAssertTrue( (node_getIndex(pEntry) == 9) );
        XCTAssertTrue( (node_getSibling(pEntry) == 0) );
        XCTAssertTrue( (node_getChild(pEntry) == 0) );
        XCTAssertTrue( (node_getParent(pEntry) == 7) );
        
        XCTAssertTrue( (obj_IsFlag(pObj, OBJ_FLAG_ALLOC)) );
        obj_Release(pObj);
        pObj = OBJ_NIL;
    }
    
    fprintf(stderr, "...%s completed.\n\n", pTestName);
    return 1;
}



int         test_nodeTree_Move01(
    const
    char        *pTestName
)
{
    NODETREE_DATA	*pObj = OBJ_NIL;
    NODE_DATA       *pEntry = OBJ_NIL;
    uint32_t        i;
    ERESULT         eRc = ERESULT_SUCCESS;
    
    fprintf(stderr, "Performing: %s\n", pTestName);
    
    pObj = createTestTree01();
    XCTAssertFalse( (pObj == OBJ_NIL) );
    if (pObj) {
        
        i = nodeTree_ChildCount(pObj, 1);
        XCTAssertFalse( (ERESULT_FAILED(eRc)) );
        XCTAssertTrue( (i == 3) );
        i = nodeTree_ChildCount(pObj, 2);
        XCTAssertFalse( (ERESULT_FAILED(eRc)) );
        XCTAssertTrue( (i == 2) );
        i = nodeTree_ChildCount(pObj, 7);
        XCTAssertFalse( (ERESULT_FAILED(eRc)) );
        XCTAssertTrue( (i == 1) );
        i = nodeTree_ChildCount(pObj, 9);
        XCTAssertFalse( (ERESULT_FAILED(eRc)) );
        XCTAssertTrue( (i == 0) );
        
        // Verify that the linkage fields are correct.
        pEntry = objArray_Get(pObj->pArray, 1);
        XCTAssertFalse( (pEntry == OBJ_NIL) );
        XCTAssertTrue( (node_getIndex(pEntry) == 1) );
        XCTAssertTrue( (node_getSibling(pEntry) == 0) );
        XCTAssertTrue( (node_getChild(pEntry) == 2) );
        XCTAssertTrue( (node_getParent(pEntry) == 0) );
        pEntry = objArray_Get(pObj->pArray, 2);
        XCTAssertFalse( (pEntry == OBJ_NIL) );
        XCTAssertTrue( (node_getIndex(pEntry) == 2) );
        XCTAssertTrue( (node_getSibling(pEntry) == 3) );
        XCTAssertTrue( (node_getChild(pEntry) == 5) );
        XCTAssertTrue( (node_getParent(pEntry) == 1) );
        pEntry = objArray_Get(pObj->pArray, 3);
        XCTAssertFalse( (pEntry == OBJ_NIL) );
        XCTAssertTrue( (node_getIndex(pEntry) == 3) );
        XCTAssertTrue( (node_getSibling(pEntry) == 4) );
        XCTAssertTrue( (node_getChild(pEntry) == 7) );
        XCTAssertTrue( (node_getParent(pEntry) == 1) );
        pEntry = objArray_Get(pObj->pArray, 4);
        XCTAssertFalse( (pEntry == OBJ_NIL) );
        XCTAssertTrue( (node_getIndex(pEntry) == 4) );
        XCTAssertTrue( (node_getSibling(pEntry) == 0) );
        XCTAssertTrue( (node_getChild(pEntry) == 0) );
        XCTAssertTrue( (node_getParent(pEntry) == 1) );
        pEntry = objArray_Get(pObj->pArray, 5);
        XCTAssertFalse( (pEntry == OBJ_NIL) );
        XCTAssertTrue( (node_getIndex(pEntry) == 5) );
        XCTAssertTrue( (node_getSibling(pEntry) == 6) );
        XCTAssertTrue( (node_getChild(pEntry) == 0) );
        XCTAssertTrue( (node_getParent(pEntry) == 2) );
        pEntry = objArray_Get(pObj->pArray, 6);
        XCTAssertFalse( (pEntry == OBJ_NIL) );
        XCTAssertTrue( (node_getIndex(pEntry) == 6) );
        XCTAssertTrue( (node_getSibling(pEntry) == 0) );
        XCTAssertTrue( (node_getChild(pEntry) == 0) );
        XCTAssertTrue( (node_getParent(pEntry) == 2) );
        pEntry = objArray_Get(pObj->pArray, 7);
        XCTAssertFalse( (pEntry == OBJ_NIL) );
        XCTAssertTrue( (node_getIndex(pEntry) == 7) );
        XCTAssertTrue( (node_getSibling(pEntry) == 8) );
        XCTAssertTrue( (node_getChild(pEntry) == 9) );
        XCTAssertTrue( (node_getParent(pEntry) == 3) );
        pEntry = objArray_Get(pObj->pArray, 8);
        XCTAssertFalse( (pEntry == OBJ_NIL) );
        XCTAssertTrue( (node_getIndex(pEntry) == 8) );
        XCTAssertTrue( (node_getSibling(pEntry) == 0) );
        XCTAssertTrue( (node_getChild(pEntry) == 0) );
        XCTAssertTrue( (node_getParent(pEntry) == 3) );
        pEntry = objArray_Get(pObj->pArray, 9);
        XCTAssertFalse( (pEntry == OBJ_NIL) );
        XCTAssertTrue( (node_getIndex(pEntry) == 9) );
        XCTAssertTrue( (node_getSibling(pEntry) == 0) );
        XCTAssertTrue( (node_getChild(pEntry) == 0) );
        XCTAssertTrue( (node_getParent(pEntry) == 7) );
        
        eRc = nodeTree_ChildrenMove(pObj, 2, 3);    // Delete C(5), D(6) after
        //                                              // child H(8) of E(3)
        XCTAssertFalse( (ERESULT_FAILED(eRc)) );
        
        // Verify that the linkage fields are correct.
        pEntry = objArray_Get(pObj->pArray, 1);
        XCTAssertFalse( (pEntry == OBJ_NIL) );
        XCTAssertTrue( (node_getIndex(pEntry) == 1) );
        XCTAssertTrue( (node_getSibling(pEntry) == 0) );
        XCTAssertTrue( (node_getChild(pEntry) == 2) );
        XCTAssertTrue( (node_getParent(pEntry) == 0) );
        pEntry = objArray_Get(pObj->pArray, 2);
        XCTAssertFalse( (pEntry == OBJ_NIL) );
        XCTAssertTrue( (node_getIndex(pEntry) == 2) );
        XCTAssertTrue( (node_getSibling(pEntry) == 3) );
        XCTAssertTrue( (node_getChild(pEntry) == 0) );
        XCTAssertTrue( (node_getParent(pEntry) == 1) );
        pEntry = objArray_Get(pObj->pArray, 3);
        XCTAssertFalse( (pEntry == OBJ_NIL) );
        XCTAssertTrue( (node_getIndex(pEntry) == 3) );
        XCTAssertTrue( (node_getSibling(pEntry) == 4) );
        XCTAssertTrue( (node_getChild(pEntry) == 7) );
        XCTAssertTrue( (node_getParent(pEntry) == 1) );
        pEntry = objArray_Get(pObj->pArray, 4);
        XCTAssertFalse( (pEntry == OBJ_NIL) );
        XCTAssertTrue( (node_getIndex(pEntry) == 4) );
        XCTAssertTrue( (node_getSibling(pEntry) == 0) );
        XCTAssertTrue( (node_getChild(pEntry) == 0) );
        XCTAssertTrue( (node_getParent(pEntry) == 1) );
        pEntry = objArray_Get(pObj->pArray, 5);
        XCTAssertFalse( (pEntry == OBJ_NIL) );
        XCTAssertTrue( (node_getIndex(pEntry) == 5) );
        XCTAssertTrue( (node_getSibling(pEntry) == 6) );
        XCTAssertTrue( (node_getChild(pEntry) == 0) );
        XCTAssertTrue( (node_getParent(pEntry) == 3) );
        pEntry = objArray_Get(pObj->pArray, 6);
        XCTAssertFalse( (pEntry == OBJ_NIL) );
        XCTAssertTrue( (node_getIndex(pEntry) == 6) );
        XCTAssertTrue( (node_getSibling(pEntry) == 0) );
        XCTAssertTrue( (node_getChild(pEntry) == 0) );
        XCTAssertTrue( (node_getParent(pEntry) == 3) );
        pEntry = objArray_Get(pObj->pArray, 7);
        XCTAssertFalse( (pEntry == OBJ_NIL) );
        XCTAssertTrue( (node_getIndex(pEntry) == 7) );
        XCTAssertTrue( (node_getSibling(pEntry) == 8) );
        XCTAssertTrue( (node_getChild(pEntry) == 9) );
        XCTAssertTrue( (node_getParent(pEntry) == 3) );
        pEntry = objArray_Get(pObj->pArray, 8);
        XCTAssertFalse( (pEntry == OBJ_NIL) );
        XCTAssertTrue( (node_getIndex(pEntry) == 8) );
        XCTAssertTrue( (node_getSibling(pEntry) == 5) );
        XCTAssertTrue( (node_getChild(pEntry) == 0) );
        XCTAssertTrue( (node_getParent(pEntry) == 3) );
        pEntry = objArray_Get(pObj->pArray, 9);
        XCTAssertFalse( (pEntry == OBJ_NIL) );
        XCTAssertTrue( (node_getIndex(pEntry) == 9) );
        XCTAssertTrue( (node_getSibling(pEntry) == 0) );
        XCTAssertTrue( (node_getChild(pEntry) == 0) );
        XCTAssertTrue( (node_getParent(pEntry) == 7) );
        
        XCTAssertTrue( (obj_IsFlag(pObj, OBJ_FLAG_ALLOC)) );
        obj_Release(pObj);
        pObj = OBJ_NIL;
    }
      
    fprintf(stderr, "...%s completed.\n\n", pTestName);
    return 1;
}



int         test_nodeTree_Node01(
    const
    char        *pTestName
)
{
    NODETREE_DATA	*pObj = OBJ_NIL;
    NODE_DATA       *pNodeA = OBJ_NIL;
    NODE_DATA       *pNodeB = OBJ_NIL;
    NODE_DATA       *pNode = OBJ_NIL;
    uint32_t        nodeA;
    uint32_t        nodeB;
    
    fprintf(stderr, "Performing: %s\n", pTestName);
    
    pObj = nodeTree_Alloc( );
    XCTAssertFalse( (OBJ_NIL == pObj) );
    pObj = nodeTree_Init( pObj );
    XCTAssertFalse( (OBJ_NIL == pObj) );
    if (pObj) {

        pNodeA = node_NewWithUTF8Con("A", OBJ_NIL);
        XCTAssertFalse( (OBJ_NIL == pNodeA) );
        pNodeB = node_NewWithUTF8Con("B", OBJ_NIL);
        XCTAssertFalse( (OBJ_NIL == pNodeB) );

        nodeA = nodeTree_ChildAdd(pObj, 0, pNodeA);
        XCTAssertTrue( (nodeA == 1) );
        XCTAssertTrue( (node_getIndex(pNodeA) == 1) );
        nodeB = nodeTree_ChildAdd(pObj,node_getIndex(pNodeA), pNodeB);
        XCTAssertTrue( (nodeB == 2) );
        
        pNode = nodeTree_Node(pObj, nodeA);
        XCTAssertTrue( (pNodeA == pNode) );
        pNode = nodeTree_Node(pObj, nodeB);
        XCTAssertTrue( (pNodeB == pNode) );
        
        obj_Release(pNodeB);
        pNodeB = OBJ_NIL;
        XCTAssertTrue( (obj_IsFlag(pNodeA, OBJ_FLAG_ALLOC)) );
        obj_Release(pNodeA);
        pNodeA = OBJ_NIL;
        obj_Release(pObj);
        pObj = OBJ_NIL;
    }
    
    fprintf(stderr, "...%s completed.\n\n", pTestName);
    return 1;
}



int         test_nodeTree_NodeLinkChild(
    const
    char        *pTestName
)
{
    NODETREE_DATA	*pObj = OBJ_NIL;
    NODE_DATA       *pNodeA = OBJ_NIL;
    NODE_DATA       *pNode = OBJ_NIL;
    uint32_t        nodeA;
    uint32_t        nodeB;
    uint32_t        nodeC;
    uint32_t        nodeD;
    uint32_t        node;
    ERESULT         eRc;
    
    fprintf(stderr, "Performing: %s\n", pTestName);
    
    pObj = nodeTree_Alloc( );
    XCTAssertFalse( (OBJ_NIL == pObj) );
    pObj = nodeTree_Init( pObj );
    XCTAssertFalse( (OBJ_NIL == pObj) );
    if (pObj) {
        
        pNodeA = node_NewWithUTF8Con("A", OBJ_NIL);
        XCTAssertFalse( (OBJ_NIL == pNodeA) );

        // Set up root.
        nodeA = nodeTree_ChildAdd(pObj, 0, pNodeA);
        XCTAssertTrue( (nodeA == 1) );
        XCTAssertTrue( (node_getIndex(pNodeA) == 1) );
        pNode = nodeTree_Node(pObj, nodeA);
        XCTAssertTrue( (pNodeA == pNode) );

        nodeB = nodeTree_NodeNewUTF8(pObj, "B", 10, OBJ_NIL);
        XCTAssertTrue( (nodeB == 2) );
        nodeC = nodeTree_NodeNewUTF8(pObj, "C", 20, OBJ_NIL);
        XCTAssertTrue( (nodeC == 3) );
        nodeD = nodeTree_NodeNewUTF8(pObj, "D", 30, OBJ_NIL);
        XCTAssertTrue( (nodeD == 4) );
        
        eRc = nodeTree_NodeLinkChild(pObj, nodeA, nodeB);
        XCTAssertFalse( (ERESULT_FAILED(eRc)) );
        node = nodeTree_NodeParent(pObj,nodeB);
        XCTAssertTrue( (node == 1) );
        eRc = nodeTree_NodeLinkChild(pObj, nodeB, nodeC);
        XCTAssertFalse( (ERESULT_FAILED(eRc)) );
        node = nodeTree_NodeParent(pObj,nodeC);
        XCTAssertTrue( (node == nodeB) );
        eRc = nodeTree_NodeLinkChild(pObj, nodeB, nodeD);
        XCTAssertFalse( (ERESULT_FAILED(eRc)) );
        node = nodeTree_NodeParent(pObj,nodeD);
        XCTAssertTrue( (node == nodeB) );
        
        XCTAssertTrue( (obj_IsFlag(pNodeA, OBJ_FLAG_ALLOC)) );
        obj_Release(pNodeA);
        pNodeA = OBJ_NIL;
        obj_Release(pObj);
        pObj = OBJ_NIL;
    }
    
    fprintf(stderr, "...%s completed.\n\n", pTestName);
    return 1;
}



int         test_nodeTree_UpDown02(
    const
    char            *pTestName
)
{
    NODETREE_DATA   *pObj = OBJ_NIL;
    NODEARRAY_DATA  *pArray = OBJ_NIL;
    NODE_DATA       *pEntry = OBJ_NIL;
    uint32_t        i;
    uint32_t        iMax;
    const
    char            *pStrA;
    ERESULT         eRc = ERESULT_SUCCESS;
    //ASTR_DATA       *pStr = OBJ_NIL;
    
    fprintf(stderr, "Performing: %s\n", pTestName);
    
    pObj = createTestTree02();
    XCTAssertFalse( (pObj == OBJ_NIL) );
    if (pObj) {

#ifdef XYZZY
        pStr = nodeTree_ToDebugString(pObj, 0);
        fprintf(stderr, "Debug = %s\n\n\n",AStr_getData(pStr));
        obj_Release(pStr);
        pStr = OBJ_NIL;
#endif
        
        i = nodeTree_ChildCount(pObj, 1);
        XCTAssertTrue( (i == 2) );
        i = nodeTree_ChildCount(pObj, 2);
        XCTAssertTrue( (i == 2) );
        i = nodeTree_ChildCount(pObj, 3);
        XCTAssertTrue( (i == 2) );
        i = nodeTree_ChildCount(pObj, 4);
        XCTAssertTrue( (i == 0) );
        i = nodeTree_ChildCount(pObj, 5);
        XCTAssertTrue( (i == 2) );
        i = nodeTree_ChildCount(pObj, 6);
        XCTAssertTrue( (i == 0) );
        i = nodeTree_ChildCount(pObj, 7);
        XCTAssertTrue( (i == 0) );
        i = nodeTree_ChildCount(pObj, 8);
        XCTAssertTrue( (i == 0) );
        i = nodeTree_ChildCount(pObj, 9);
        XCTAssertTrue( (i == 2) );
        i = nodeTree_ChildCount(pObj, 10);
        XCTAssertTrue( (i == 0) );
        i = nodeTree_ChildCount(pObj, 11);
        XCTAssertTrue( (i == 0) );

        // Verify that the linkage fields are correct.
        pEntry = objArray_Get(pObj->pArray, 1);
        XCTAssertFalse( (pEntry == OBJ_NIL) );
        XCTAssertTrue( (node_getIndex(pEntry) == 1) );
        XCTAssertTrue( (node_getSibling(pEntry) == 0) );
        XCTAssertTrue( (node_getChild(pEntry) == 2) );
        XCTAssertTrue( (node_getParent(pEntry) == 0) );
        pEntry = objArray_Get(pObj->pArray, 2);
        XCTAssertFalse( (pEntry == OBJ_NIL) );
        XCTAssertTrue( (node_getIndex(pEntry) == 2) );
        XCTAssertTrue( (node_getSibling(pEntry) == 3) );
        XCTAssertTrue( (node_getChild(pEntry) == 4) );
        XCTAssertTrue( (node_getParent(pEntry) == 1) );
        pEntry = objArray_Get(pObj->pArray, 3);
        XCTAssertFalse( (pEntry == OBJ_NIL) );
        XCTAssertTrue( (node_getIndex(pEntry) == 3) );
        XCTAssertTrue( (node_getSibling(pEntry) == 0) );
        XCTAssertTrue( (node_getChild(pEntry) == 8) );
        XCTAssertTrue( (node_getParent(pEntry) == 1) );
        pEntry = objArray_Get(pObj->pArray, 4);
        XCTAssertFalse( (pEntry == OBJ_NIL) );
        XCTAssertTrue( (node_getIndex(pEntry) == 4) );
        XCTAssertTrue( (node_getSibling(pEntry) == 5) );
        XCTAssertTrue( (node_getChild(pEntry) == 0) );
        XCTAssertTrue( (node_getParent(pEntry) == 2) );
        pEntry = objArray_Get(pObj->pArray, 5);
        XCTAssertFalse( (pEntry == OBJ_NIL) );
        XCTAssertTrue( (node_getIndex(pEntry) == 5) );
        XCTAssertTrue( (node_getSibling(pEntry) == 0) );
        XCTAssertTrue( (node_getChild(pEntry) == 6) );
        XCTAssertTrue( (node_getParent(pEntry) == 2) );
        pEntry = objArray_Get(pObj->pArray, 6);
        XCTAssertFalse( (pEntry == OBJ_NIL) );
        XCTAssertTrue( (node_getIndex(pEntry) == 6) );
        XCTAssertTrue( (node_getSibling(pEntry) == 7) );
        XCTAssertTrue( (node_getChild(pEntry) == 0) );
        XCTAssertTrue( (node_getParent(pEntry) == 5) );
        pEntry = objArray_Get(pObj->pArray, 7);
        XCTAssertFalse( (pEntry == OBJ_NIL) );
        XCTAssertTrue( (node_getIndex(pEntry) == 7) );
        XCTAssertTrue( (node_getSibling(pEntry) == 0) );
        XCTAssertTrue( (node_getChild(pEntry) == 0) );
        XCTAssertTrue( (node_getParent(pEntry) == 5) );
        pEntry = objArray_Get(pObj->pArray, 8);
        XCTAssertFalse( (pEntry == OBJ_NIL) );
        XCTAssertTrue( (node_getIndex(pEntry) == 8) );
        XCTAssertTrue( (node_getSibling(pEntry) == 9) );
        XCTAssertTrue( (node_getChild(pEntry) == 0) );
        XCTAssertTrue( (node_getParent(pEntry) == 3) );
        pEntry = objArray_Get(pObj->pArray, 9);
        XCTAssertFalse( (pEntry == OBJ_NIL) );
        XCTAssertTrue( (node_getIndex(pEntry) == 9) );
        XCTAssertTrue( (node_getSibling(pEntry) == 0) );
        XCTAssertTrue( (node_getChild(pEntry) == 10) );
        XCTAssertTrue( (node_getParent(pEntry) == 3) );
        pEntry = objArray_Get(pObj->pArray, 10);
        XCTAssertFalse( (pEntry == OBJ_NIL) );
        XCTAssertTrue( (node_getIndex(pEntry) == 10) );
        XCTAssertTrue( (node_getSibling(pEntry) == 11) );
        XCTAssertTrue( (node_getChild(pEntry) == 0) );
        XCTAssertTrue( (node_getParent(pEntry) == 9) );
        pEntry = objArray_Get(pObj->pArray, 11);
        XCTAssertFalse( (pEntry == OBJ_NIL) );
        XCTAssertTrue( (node_getIndex(pEntry) == 11) );
        XCTAssertTrue( (node_getSibling(pEntry) == 0) );
        XCTAssertTrue( (node_getChild(pEntry) == 0) );
        XCTAssertTrue( (node_getParent(pEntry) == 9) );

#ifdef XYZZY
        visitorReset();
        eRc = nodeTree_VisitInorder(pObj, visitor, NULL);
        XCTAssertFalse( (ERESULT_FAILED(eRc)) );
        fprintf(stderr, "\nInorder(%d):\n",count);
        //XCTAssertTrue( (11 == count) );
        fprintf(stderr, "\ta + b / c *1 d - e *2 f (should be)\n\t");
        for (i=0; i<count; ++i) {
            pStrA = node_getNameUTF8(pNodes[i]);
            fprintf(stderr, "%s ", pStrA);
            mem_Free((void *)pStrA);
            pStrA = NULL;
        }
        fprintf(stderr, " (actual)\n");
        eRc = name_CompareA(node_getName(pNodes[0]),"a");
        XCTAssertTrue( (ERESULT_SUCCESS_EQUAL == eRc) );
        eRc = name_CompareA(node_getName(pNodes[1]),"+");
        XCTAssertTrue( (ERESULT_SUCCESS_EQUAL == eRc) );
        eRc = name_CompareA(node_getName(pNodes[2]),"b");
        XCTAssertTrue( (ERESULT_SUCCESS_EQUAL == eRc) );
        eRc = name_CompareA(node_getName(pNodes[3]),"/");
        XCTAssertTrue( (ERESULT_SUCCESS_EQUAL == eRc) );
        eRc = name_CompareA(node_getName(pNodes[4]),"c");
        XCTAssertTrue( (ERESULT_SUCCESS_EQUAL == eRc) );
        eRc = name_CompareA(node_getName(pNodes[5]),"*1");
        XCTAssertTrue( (ERESULT_SUCCESS_EQUAL == eRc) );
        eRc = name_CompareA(node_getName(pNodes[6]),"d");
        XCTAssertTrue( (ERESULT_SUCCESS_EQUAL == eRc) );
        eRc = name_CompareA(node_getName(pNodes[7]),"-");
        XCTAssertTrue( (ERESULT_SUCCESS_EQUAL == eRc) );
        eRc = name_CompareA(node_getName(pNodes[8]),"e");
        XCTAssertTrue( (ERESULT_SUCCESS_EQUAL == eRc) );
        eRc = name_CompareA(node_getName(pNodes[8]),"*2");
        XCTAssertTrue( (ERESULT_SUCCESS_EQUAL == eRc) );
        eRc = name_CompareA(node_getName(pNodes[8]),"f");
        XCTAssertTrue( (ERESULT_SUCCESS_EQUAL == eRc) );
#endif

        visitorReset();
        eRc = nodeTree_VisitPostorder(pObj, visitor, NULL);
        XCTAssertFalse( (ERESULT_FAILED(eRc)) );
        fprintf(stderr, "\nPostorder(%d):\n", count);
        XCTAssertTrue( (11 == count) );
        fprintf(stderr, "\ta b c / + d e f *2 - *1 (should be)\n\t");
        for (i=0; i<count; ++i) {
            pStrA = node_getNameUTF8(pNodes[i]);
            fprintf(stderr, "%s ", pStrA);
            mem_Free((void *)pStrA);
            pStrA = NULL;
        }
        fprintf(stderr, " (actual)\n");
        eRc = name_CompareA(node_getName(pNodes[0]),"a");
        XCTAssertTrue( (ERESULT_SUCCESS_EQUAL == eRc) );
        eRc = name_CompareA(node_getName(pNodes[1]),"b");
        XCTAssertTrue( (ERESULT_SUCCESS_EQUAL == eRc) );
        eRc = name_CompareA(node_getName(pNodes[2]),"c");
        XCTAssertTrue( (ERESULT_SUCCESS_EQUAL == eRc) );
        eRc = name_CompareA(node_getName(pNodes[3]),"/");
        XCTAssertTrue( (ERESULT_SUCCESS_EQUAL == eRc) );
        eRc = name_CompareA(node_getName(pNodes[4]),"+");
        XCTAssertTrue( (ERESULT_SUCCESS_EQUAL == eRc) );
        eRc = name_CompareA(node_getName(pNodes[5]),"d");
        XCTAssertTrue( (ERESULT_SUCCESS_EQUAL == eRc) );
        eRc = name_CompareA(node_getName(pNodes[6]),"e");
        XCTAssertTrue( (ERESULT_SUCCESS_EQUAL == eRc) );
        eRc = name_CompareA(node_getName(pNodes[7]),"f");
        XCTAssertTrue( (ERESULT_SUCCESS_EQUAL == eRc) );
        eRc = name_CompareA(node_getName(pNodes[8]),"*2");
        XCTAssertTrue( (ERESULT_SUCCESS_EQUAL == eRc) );
        eRc = name_CompareA(node_getName(pNodes[9]),"-");
        XCTAssertTrue( (ERESULT_SUCCESS_EQUAL == eRc) );
        eRc = name_CompareA(node_getName(pNodes[10]),"*1");
        XCTAssertTrue( (ERESULT_SUCCESS_EQUAL == eRc) );

        visitorReset();
        eRc = nodeTree_VisitPreorder(pObj, visitor, NULL);
        XCTAssertFalse( (ERESULT_FAILED(eRc)) );
        fprintf(stderr, "\nPreorder(%d):\n", count);
        XCTAssertTrue( (11 == count) );
        fprintf(stderr, "\t*1 + a / b c - d *2 e f (should be)\n\t");
        for (i=0; i<count; ++i) {
            pStrA = node_getNameUTF8(pNodes[i]);
            fprintf(stderr, "%s ", pStrA);
            mem_Free((void *)pStrA);
            pStrA = NULL;
        }
        fprintf(stderr, " (actual)\n\n");
        eRc = name_CompareA(node_getName(pNodes[0]),"*1");
        XCTAssertTrue( (ERESULT_SUCCESS_EQUAL == eRc) );
        eRc = name_CompareA(node_getName(pNodes[1]),"+");
        XCTAssertTrue( (ERESULT_SUCCESS_EQUAL == eRc) );
        eRc = name_CompareA(node_getName(pNodes[2]),"a");
        XCTAssertTrue( (ERESULT_SUCCESS_EQUAL == eRc) );
        eRc = name_CompareA(node_getName(pNodes[3]),"/");
        XCTAssertTrue( (ERESULT_SUCCESS_EQUAL == eRc) );
        eRc = name_CompareA(node_getName(pNodes[4]),"b");
        XCTAssertTrue( (ERESULT_SUCCESS_EQUAL == eRc) );
        eRc = name_CompareA(node_getName(pNodes[5]),"c");
        XCTAssertTrue( (ERESULT_SUCCESS_EQUAL == eRc) );
        eRc = name_CompareA(node_getName(pNodes[6]),"-");
        XCTAssertTrue( (ERESULT_SUCCESS_EQUAL == eRc) );
        eRc = name_CompareA(node_getName(pNodes[7]),"d");
        XCTAssertTrue( (ERESULT_SUCCESS_EQUAL == eRc) );
        eRc = name_CompareA(node_getName(pNodes[8]),"*2");
        XCTAssertTrue( (ERESULT_SUCCESS_EQUAL == eRc) );
        eRc = name_CompareA(node_getName(pNodes[9]),"e");
        XCTAssertTrue( (ERESULT_SUCCESS_EQUAL == eRc) );
        eRc = name_CompareA(node_getName(pNodes[10]),"f");
        XCTAssertTrue( (ERESULT_SUCCESS_EQUAL == eRc) );

#ifdef  XYZZY
        visitorReset();
        eRc = nodeTree_VisitBreadthFirst(pObj, visitor, NULL);
        XCTAssertFalse( (ERESULT_FAILED(eRc)) );
        XCTAssertTrue( (9 == count) );
        eRc = name_CompareA(node_getName(pNodes[0]),"A");
        XCTAssertTrue( (ERESULT_SUCCESS_EQUAL == eRc) );
        eRc = name_CompareA(node_getName(pNodes[1]),"B");
        XCTAssertTrue( (ERESULT_SUCCESS_EQUAL == eRc) );
        eRc = name_CompareA(node_getName(pNodes[2]),"E");
        XCTAssertTrue( (ERESULT_SUCCESS_EQUAL == eRc) );
        eRc = name_CompareA(node_getName(pNodes[3]),"I");
        XCTAssertTrue( (ERESULT_SUCCESS_EQUAL == eRc) );
        eRc = name_CompareA(node_getName(pNodes[4]),"C");
        XCTAssertTrue( (ERESULT_SUCCESS_EQUAL == eRc) );
        eRc = name_CompareA(node_getName(pNodes[5]),"D");
        XCTAssertTrue( (ERESULT_SUCCESS_EQUAL == eRc) );
        eRc = name_CompareA(node_getName(pNodes[6]),"F");
        XCTAssertTrue( (ERESULT_SUCCESS_EQUAL == eRc) );
        eRc = name_CompareA(node_getName(pNodes[7]),"H");
        XCTAssertTrue( (ERESULT_SUCCESS_EQUAL == eRc) );
        eRc = name_CompareA(node_getName(pNodes[8]),"G");
        XCTAssertTrue( (ERESULT_SUCCESS_EQUAL == eRc) );
#endif

#ifdef XYZZY
        pArray = nodeTree_ToLinearizationPost(pObj);
        XCTAssertFalse( (OBJ_NIL == pArray) );
        iMax = nodeArray_getSize(pArray);
        fprintf(stderr, "\nLinearization Postorder(%d):\n",iMax);
        XCTAssertTrue( (29 == iMax) );
        fprintf(stderr, "\tShould be: (DCGHFIEBA)\n");
        fprintf(stderr, "\tFound:     ");
        for (i=1; i<=iMax; ++i) {
            pStrA = node_getNameUTF8(nodeArray_Get(pArray, i));
            fprintf(stderr, "%s", pStrA);
            mem_Free((void *)pStrA);
        }
        fprintf(stderr, "\n");
        eRc = name_CompareA(node_getName(nodeArray_Get(pArray,  1)),"(");
        XCTAssertTrue( (ERESULT_SUCCESS_EQUAL == eRc) );
        eRc = name_CompareA(node_getName(nodeArray_Get(pArray,  2)),"A");
        XCTAssertTrue( (ERESULT_SUCCESS_EQUAL == eRc) );
        eRc = name_CompareA(node_getName(nodeArray_Get(pArray,  3)),"(");
        XCTAssertTrue( (ERESULT_SUCCESS_EQUAL == eRc) );
        eRc = name_CompareA(node_getName(nodeArray_Get(pArray,  4)),"B");
        XCTAssertTrue( (ERESULT_SUCCESS_EQUAL == eRc) );
        eRc = name_CompareA(node_getName(nodeArray_Get(pArray,  5)),"(");
        XCTAssertTrue( (ERESULT_SUCCESS_EQUAL == eRc) );
        eRc = name_CompareA(node_getName(nodeArray_Get(pArray,  6)),"C");
        XCTAssertTrue( (ERESULT_SUCCESS_EQUAL == eRc) );
        eRc = name_CompareA(node_getName(nodeArray_Get(pArray,  7)),"D");
        XCTAssertTrue( (ERESULT_SUCCESS_EQUAL == eRc) );
        eRc = name_CompareA(node_getName(nodeArray_Get(pArray,  8)),")");
        XCTAssertTrue( (ERESULT_SUCCESS_EQUAL == eRc) );
        eRc = name_CompareA(node_getName(nodeArray_Get(pArray,  9)),"E");
        XCTAssertTrue( (ERESULT_SUCCESS_EQUAL == eRc) );
        eRc = name_CompareA(node_getName(nodeArray_Get(pArray, 10)),"(");
        XCTAssertTrue( (ERESULT_SUCCESS_EQUAL == eRc) );
        eRc = name_CompareA(node_getName(nodeArray_Get(pArray, 11)),"F");
        XCTAssertTrue( (ERESULT_SUCCESS_EQUAL == eRc) );
        eRc = name_CompareA(node_getName(nodeArray_Get(pArray, 12)),"(");
        XCTAssertTrue( (ERESULT_SUCCESS_EQUAL == eRc) );
        eRc = name_CompareA(node_getName(nodeArray_Get(pArray, 13)),"G");
        XCTAssertTrue( (ERESULT_SUCCESS_EQUAL == eRc) );
        eRc = name_CompareA(node_getName(nodeArray_Get(pArray, 14)),")");
        XCTAssertTrue( (ERESULT_SUCCESS_EQUAL == eRc) );
        eRc = name_CompareA(node_getName(nodeArray_Get(pArray, 15)),"H");
        XCTAssertTrue( (ERESULT_SUCCESS_EQUAL == eRc) );
        eRc = name_CompareA(node_getName(nodeArray_Get(pArray, 16)),")");
        XCTAssertTrue( (ERESULT_SUCCESS_EQUAL == eRc) );
        eRc = name_CompareA(node_getName(nodeArray_Get(pArray, 17)),"I");
        XCTAssertTrue( (ERESULT_SUCCESS_EQUAL == eRc) );
        eRc = name_CompareA(node_getName(nodeArray_Get(pArray, 18)),")");
        XCTAssertTrue( (ERESULT_SUCCESS_EQUAL == eRc) );
        eRc = name_CompareA(node_getName(nodeArray_Get(pArray, 19)),")");
        XCTAssertTrue( (ERESULT_SUCCESS_EQUAL == eRc) );
        obj_Release(pArray);
        pArray = OBJ_NIL;
        fprintf(stderr, "\n\n\n");
#endif
        
        pArray = nodeTree_ToLinearizationPre(pObj);
        XCTAssertFalse( (OBJ_NIL == pArray) );
        iMax = nodeArray_getSize(pArray);
        fprintf(stderr, "\nLinearization Preorder(%d):\n",iMax);
        XCTAssertTrue( (23 == iMax) );
        fprintf(stderr, "\tShould be: ( *1 ( + ( a / ( b c ) ) - ( d *2 ( e f ) ) ) )\n");
        fprintf(stderr, "\tFound:     ");
        for (i=1; i<=iMax; ++i) {
            pStrA = node_getNameUTF8(nodeArray_Get(pArray, i));
            fprintf(stderr, "%s ", pStrA);
            mem_Free((void *)pStrA);
        }
        fprintf(stderr, "\n");
        eRc = name_CompareA(node_getName(nodeArray_Get(pArray,  1)),"(");
        XCTAssertTrue( (ERESULT_SUCCESS_EQUAL == eRc) );
        eRc = name_CompareA(node_getName(nodeArray_Get(pArray,  2)),"*1");
        XCTAssertTrue( (ERESULT_SUCCESS_EQUAL == eRc) );
        eRc = name_CompareA(node_getName(nodeArray_Get(pArray,  3)),"(");
        XCTAssertTrue( (ERESULT_SUCCESS_EQUAL == eRc) );
        eRc = name_CompareA(node_getName(nodeArray_Get(pArray,  4)),"+");
        XCTAssertTrue( (ERESULT_SUCCESS_EQUAL == eRc) );
        eRc = name_CompareA(node_getName(nodeArray_Get(pArray,  5)),"(");
        XCTAssertTrue( (ERESULT_SUCCESS_EQUAL == eRc) );
        eRc = name_CompareA(node_getName(nodeArray_Get(pArray,  6)),"a");
        XCTAssertTrue( (ERESULT_SUCCESS_EQUAL == eRc) );
        eRc = name_CompareA(node_getName(nodeArray_Get(pArray,  7)),"/");
        XCTAssertTrue( (ERESULT_SUCCESS_EQUAL == eRc) );
        eRc = name_CompareA(node_getName(nodeArray_Get(pArray,  8)),"(");
        XCTAssertTrue( (ERESULT_SUCCESS_EQUAL == eRc) );
        eRc = name_CompareA(node_getName(nodeArray_Get(pArray,  9)),"b");
        XCTAssertTrue( (ERESULT_SUCCESS_EQUAL == eRc) );
        eRc = name_CompareA(node_getName(nodeArray_Get(pArray, 10)),"c");
        XCTAssertTrue( (ERESULT_SUCCESS_EQUAL == eRc) );
        eRc = name_CompareA(node_getName(nodeArray_Get(pArray, 11)),")");
        XCTAssertTrue( (ERESULT_SUCCESS_EQUAL == eRc) );
        eRc = name_CompareA(node_getName(nodeArray_Get(pArray, 12)),")");
        XCTAssertTrue( (ERESULT_SUCCESS_EQUAL == eRc) );
        eRc = name_CompareA(node_getName(nodeArray_Get(pArray, 13)),"-");
        XCTAssertTrue( (ERESULT_SUCCESS_EQUAL == eRc) );
        eRc = name_CompareA(node_getName(nodeArray_Get(pArray, 14)),"(");
        XCTAssertTrue( (ERESULT_SUCCESS_EQUAL == eRc) );
        eRc = name_CompareA(node_getName(nodeArray_Get(pArray, 15)),"d");
        XCTAssertTrue( (ERESULT_SUCCESS_EQUAL == eRc) );
        eRc = name_CompareA(node_getName(nodeArray_Get(pArray, 16)),"*2");
        XCTAssertTrue( (ERESULT_SUCCESS_EQUAL == eRc) );
        eRc = name_CompareA(node_getName(nodeArray_Get(pArray, 17)),"(");
        XCTAssertTrue( (ERESULT_SUCCESS_EQUAL == eRc) );
        eRc = name_CompareA(node_getName(nodeArray_Get(pArray, 18)),"e");
        XCTAssertTrue( (ERESULT_SUCCESS_EQUAL == eRc) );
        eRc = name_CompareA(node_getName(nodeArray_Get(pArray, 19)),"f");
        XCTAssertTrue( (ERESULT_SUCCESS_EQUAL == eRc) );
        eRc = name_CompareA(node_getName(nodeArray_Get(pArray, 20)),")");
        XCTAssertTrue( (ERESULT_SUCCESS_EQUAL == eRc) );
        eRc = name_CompareA(node_getName(nodeArray_Get(pArray, 21)),")");
        XCTAssertTrue( (ERESULT_SUCCESS_EQUAL == eRc) );
        eRc = name_CompareA(node_getName(nodeArray_Get(pArray, 22)),")");
        XCTAssertTrue( (ERESULT_SUCCESS_EQUAL == eRc) );
        eRc = name_CompareA(node_getName(nodeArray_Get(pArray, 23)),")");
        XCTAssertTrue( (ERESULT_SUCCESS_EQUAL == eRc) );
        obj_Release(pArray);
        pArray = OBJ_NIL;
        fprintf(stderr, "\n\n\n");
        
        XCTAssertTrue( (obj_IsFlag(pObj, OBJ_FLAG_ALLOC)) );
        obj_Release(pObj);
        pObj = OBJ_NIL;
    }
    
    fprintf(stderr, "...%s completed.\n\n", pTestName);
    return 1;
}




TINYTEST_START_SUITE(test_nodeTree);
    TINYTEST_ADD_TEST(test_nodeTree_UpDown02,setUp,tearDown);
    //TINYTEST_ADD_TEST(test_nodeTree_NodeLinkChild,setUp,tearDown);
    //TINYTEST_ADD_TEST(test_nodeTree_Node01,setUp,tearDown);
    //TINYTEST_ADD_TEST(test_nodeTree_Move01,setUp,tearDown);
    //TINYTEST_ADD_TEST(test_nodeTree_Delete01,setUp,tearDown);
    TINYTEST_ADD_TEST(test_nodeTree_UpDown01,setUp,tearDown);
    TINYTEST_ADD_TEST(test_nodeTree_OpenClose,setUp,tearDown);
TINYTEST_END_SUITE();

TINYTEST_MAIN_SINGLE_SUITE(test_nodeTree);





