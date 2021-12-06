// vi:nu:et:sts=4 ts=4 sw=4
/*
 *	Generated 01/10/2020 16:43:19
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
#include    <szTbl.h>
#include    <trace.h>
#include    <NodeTree_internal.h>



static
uint32_t        count = 0;
static
NODELINK_DATA   *pNodes[64];



// Example from Knuth's "The Art of Computer Programming - Volume 1 (3rd Ed.)", page 332
// which consists of a forest (two trees) that have sibling roots.
static
NODETREE_DATA * createTestTree01(
)
{
    NODETREE_DATA    *pTree = OBJ_NIL;
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



static
void            visitor(
    OBJ_ID          pObject,            // Object supplied below
    NODETREE_DATA   *pTree,             // Our Tree
    NODELINK_DATA   *pNode,             // Current Node
    uint16_t        indent
)
{
    pNodes[count] = pNode;
    ++count;
}


static
void            visitorPrint(
    OBJ_ID          pObject,            // Object supplied below
    NODETREE_DATA   *pTree,             // Our Tree
    NODELINK_DATA   *pNode,             // Current Node
    uint16_t        indent
)
{
    const
    char            *pStrA;
    fprintf(stderr, "%3d ", indent);
    pStrA = Node_getNameUTF8(NodeLink_getNode(pNode));
    fprintf(stderr, "%s\n", pStrA);
    mem_Free((void *)pStrA);
    pStrA = NULL;
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




int             setUp (
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


int             tearDown (
    const
    char            *pTestName
)
{
    // Put teardown code here. This method is called after the invocation of each
    // test method in the class.

    szTbl_SharedReset( );
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






int             test_NodeTree_OpenClose (
    const
    char            *pTestName
)
{
    ERESULT         eRc = ERESULT_SUCCESS;
    NODETREE_DATA	    *pObj = OBJ_NIL;
    bool            fRc;
   
    fprintf(stderr, "Performing: %s\n", pTestName);

    pObj = NodeTree_Alloc( );
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    pObj = NodeTree_Init( pObj );
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    if (pObj) {

        //obj_TraceSet(pObj, true);       
        fRc = obj_IsKindOf(pObj, OBJ_IDENT_NODETREE);
        TINYTEST_TRUE( (fRc) );
        
        // Test something.
        TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );

        obj_Release(pObj);
        pObj = OBJ_NIL;
    }

    fprintf(stderr, "...%s completed.\n\n\n", pTestName);
    return 1;
}



int             test_NodeTree_Test01 (
    const
    char            *pTestName
)
{
    ERESULT         eRc = ERESULT_SUCCESS;
    NODETREE_DATA	    *pObj = OBJ_NIL;
    bool            fRc;
   
    fprintf(stderr, "Performing: %s\n", pTestName);

    pObj = NodeTree_Alloc( );
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    pObj = NodeTree_Init( pObj );
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    if (pObj) {

        //obj_TraceSet(pObj, true);       
        fRc = obj_IsKindOf(pObj, OBJ_IDENT_NODETREE);
        TINYTEST_TRUE( (fRc) );
        
        // Test something.
        TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );

        obj_Release(pObj);
        pObj = OBJ_NIL;
    }

    fprintf(stderr, "...%s completed.\n\n\n", pTestName);
    return 1;
}



int         test_NodeTree_UpDown01(
    const
    char        *pTestName
)
{
    NODETREE_DATA   *pObj = OBJ_NIL;
    OBJARRAY_DATA   *pArray = OBJ_NIL;
    NODELINK_DATA   *pEntry = OBJ_NIL;
    uint32_t        i;
    uint32_t        iMax;
    const
    char            *pStrA;
    ERESULT         eRc = ERESULT_SUCCESS;
    //ASTR_DATA       *pStr = OBJ_NIL;

    fprintf(stderr, "Performing: %s\n", pTestName);

    pObj = createTestTree01();
    XCTAssertFalse( (pObj == OBJ_NIL) );
    if (pObj) {

#ifdef XYZZY
        pStr = NodeTree_ToDebugString(pObj, 0);
        fprintf(stderr, "Debug = %s\n\n\n",AStr_getData(pStr));
        obj_Release(pStr);
        pStr = OBJ_NIL;
#endif

        i = NodeTree_SiblingCount(pObj, 1);
        XCTAssertTrue( (i == 1) );
        i = NodeTree_ChildCount(pObj, 1);
        XCTAssertTrue( (i == 2) );
        i = NodeTree_ChildCount(pObj, 2);
        XCTAssertTrue( (i == 3) );
        i = NodeTree_ChildCount(pObj, 3);
        XCTAssertTrue( (i == 0) );
        i = NodeTree_ChildCount(pObj, 4);
        XCTAssertTrue( (i == 1) );
        i = NodeTree_ChildCount(pObj, 5);
        XCTAssertTrue( (i == 0) );
        i = NodeTree_ChildCount(pObj, 6);
        XCTAssertTrue( (i == 1) );
        i = NodeTree_ChildCount(pObj, 7);
        XCTAssertTrue( (i == 1) );
        i = NodeTree_ChildCount(pObj, 8);
        XCTAssertTrue( (i == 0) );
        i = NodeTree_ChildCount(pObj, 9);
        XCTAssertTrue( (i == 0) );
        i = NodeTree_ChildCount(pObj, 10);
        XCTAssertTrue( (i == 0) );

        // Verify that the linkage fields are correct.
        pEntry = (NODELINK_DATA *)ObjArray_Get(pObj->pArray, 1);
        XCTAssertFalse( (pEntry == OBJ_NIL) );
        XCTAssertTrue( (NodeLink_getIndex(pEntry) == 1) );
        XCTAssertTrue( (NodeLink_getChild(pEntry) == 3) );
        XCTAssertTrue( (NodeLink_getSibling(pEntry) == 2) );
        XCTAssertTrue( (NodeLink_getParent(pEntry) == 0) );
        pEntry = (NODELINK_DATA *)ObjArray_Get(pObj->pArray, 2);
        XCTAssertFalse( (pEntry == OBJ_NIL) );
        XCTAssertTrue( (NodeLink_getIndex(pEntry) == 2) );
        XCTAssertTrue( (NodeLink_getChild(pEntry) == 6) );
        XCTAssertTrue( (NodeLink_getSibling(pEntry) == 0) );
        XCTAssertTrue( (NodeLink_getParent(pEntry) == 0) );
        pEntry = (NODELINK_DATA *)ObjArray_Get(pObj->pArray, 3);
        XCTAssertFalse( (pEntry == OBJ_NIL) );
        XCTAssertTrue( (NodeLink_getIndex(pEntry) == 3) );
        XCTAssertTrue( (NodeLink_getChild(pEntry) == 0) );
        XCTAssertTrue( (NodeLink_getSibling(pEntry) == 4) );
        XCTAssertTrue( (NodeLink_getParent(pEntry) == 1) );
        pEntry = (NODELINK_DATA *)ObjArray_Get(pObj->pArray, 4);
        XCTAssertFalse( (pEntry == OBJ_NIL) );
        XCTAssertTrue( (NodeLink_getIndex(pEntry) == 4) );
        XCTAssertTrue( (NodeLink_getChild(pEntry) == 5) );
        XCTAssertTrue( (NodeLink_getSibling(pEntry) == 0) );
        XCTAssertTrue( (NodeLink_getParent(pEntry) == 1) );
        pEntry = (NODELINK_DATA *)ObjArray_Get(pObj->pArray, 5);
        XCTAssertFalse( (pEntry == OBJ_NIL) );
        XCTAssertTrue( (NodeLink_getIndex(pEntry) == 5) );
        XCTAssertTrue( (NodeLink_getChild(pEntry) == 0) );
        XCTAssertTrue( (NodeLink_getSibling(pEntry) == 0) );
        XCTAssertTrue( (NodeLink_getParent(pEntry) == 4) );
        pEntry = (NODELINK_DATA *)ObjArray_Get(pObj->pArray, 6);
        XCTAssertFalse( (pEntry == OBJ_NIL) );
        XCTAssertTrue( (NodeLink_getIndex(pEntry) == 6) );
        XCTAssertTrue( (NodeLink_getChild(pEntry) == 9) );
        XCTAssertTrue( (NodeLink_getSibling(pEntry) == 7) );
        XCTAssertTrue( (NodeLink_getParent(pEntry) == 2) );
        pEntry = (NODELINK_DATA *)ObjArray_Get(pObj->pArray, 7);
        XCTAssertFalse( (pEntry == OBJ_NIL) );
        XCTAssertTrue( (NodeLink_getIndex(pEntry) == 7) );
        XCTAssertTrue( (NodeLink_getChild(pEntry) == 10) );
        XCTAssertTrue( (NodeLink_getSibling(pEntry) == 8) );
        XCTAssertTrue( (NodeLink_getParent(pEntry) == 2) );
        pEntry = (NODELINK_DATA *)ObjArray_Get(pObj->pArray, 8);
        XCTAssertFalse( (pEntry == OBJ_NIL) );
        XCTAssertTrue( (NodeLink_getIndex(pEntry) == 8) );
        XCTAssertTrue( (NodeLink_getChild(pEntry) == 0) );
        XCTAssertTrue( (NodeLink_getSibling(pEntry) == 0) );
        XCTAssertTrue( (NodeLink_getParent(pEntry) == 2) );
        pEntry = (NODELINK_DATA *)ObjArray_Get(pObj->pArray, 9);
        XCTAssertFalse( (pEntry == OBJ_NIL) );
        XCTAssertTrue( (NodeLink_getIndex(pEntry) == 9) );
        XCTAssertTrue( (NodeLink_getChild(pEntry) == 0) );
        XCTAssertTrue( (NodeLink_getSibling(pEntry) == 0) );
        XCTAssertTrue( (NodeLink_getParent(pEntry) == 6) );
        pEntry = (NODELINK_DATA *)ObjArray_Get(pObj->pArray, 10);
        XCTAssertFalse( (pEntry == OBJ_NIL) );
        XCTAssertTrue( (NodeLink_getIndex(pEntry) == 10) );
        XCTAssertTrue( (NodeLink_getChild(pEntry) == 0) );
        XCTAssertTrue( (NodeLink_getSibling(pEntry) == 0) );
        XCTAssertTrue( (NodeLink_getParent(pEntry) == 7) );

        visitorReset();
        eRc = NodeTree_VisitPostorder(pObj, visitor, NULL);
        XCTAssertFalse( (ERESULT_FAILED(eRc)) );
        fprintf(stderr, "\nPostorder(%d):\n",count);
        XCTAssertTrue( (10 == count) );
        fprintf(stderr, "\tBKCAHEJFGD (should be)\n\t");
        for (i=0; i<count; ++i) {
            pStrA = Node_getNameUTF8(NodeLink_getNode(pNodes[i]));
            fprintf(stderr, "%c", *pStrA);
            mem_Free((void *)pStrA);
            pStrA = NULL;
        }
        fprintf(stderr, " (actual)\n");
        eRc = Name_CompareA(Node_getName(NodeLink_getNode(pNodes[0])),"B");
        XCTAssertTrue( (0 == eRc) );
        eRc = Name_CompareA(Node_getName(NodeLink_getNode(pNodes[1])),"K");
        XCTAssertTrue( (0 == eRc) );
        eRc = Name_CompareA(Node_getName(NodeLink_getNode(pNodes[2])),"C");
        XCTAssertTrue( (0 == eRc) );
        eRc = Name_CompareA(Node_getName(NodeLink_getNode(pNodes[3])),"A");
        XCTAssertTrue( (0 == eRc) );
        eRc = Name_CompareA(Node_getName(NodeLink_getNode(pNodes[4])),"H");
        XCTAssertTrue( (0 == eRc) );
        eRc = Name_CompareA(Node_getName(NodeLink_getNode(pNodes[5])),"E");
        XCTAssertTrue( (0 == eRc) );
        eRc = Name_CompareA(Node_getName(NodeLink_getNode(pNodes[6])),"J");
        XCTAssertTrue( (0 == eRc) );
        eRc = Name_CompareA(Node_getName(NodeLink_getNode(pNodes[7])),"F");
        XCTAssertTrue( (0 == eRc) );
        eRc = Name_CompareA(Node_getName(NodeLink_getNode(pNodes[8])),"G");
        XCTAssertTrue( (0 == eRc) );
        eRc = Name_CompareA(Node_getName(NodeLink_getNode(pNodes[9])),"D");
        XCTAssertTrue( (0 == eRc) );
        eRc = NodeTree_VisitPostorder(pObj, visitorPrint, NULL);
        XCTAssertFalse( (ERESULT_FAILED(eRc)) );

        visitorReset();
        eRc = NodeTree_VisitPreorder(pObj, visitor, NULL);
        XCTAssertFalse( (ERESULT_FAILED(eRc)) );
        fprintf(stderr, "\nPreorder(%d):\n",count);
        XCTAssertTrue( (10 == count) );
        fprintf(stderr, "\tABCKDEHFJG (should be)\n\t");
        for (i=0; i<count; ++i) {
            pStrA = Node_getNameUTF8(NodeLink_getNode(pNodes[i]));
            fprintf(stderr, "%c", *pStrA);
            mem_Free((void *)pStrA);
            pStrA = NULL;
        }
        fprintf(stderr, " (actual)\n\n");
        eRc = Name_CompareA(Node_getName(NodeLink_getNode(pNodes[0])),"A");
        XCTAssertTrue( (0 == eRc) );
        eRc = Name_CompareA(Node_getName(NodeLink_getNode(pNodes[1])),"B");
        XCTAssertTrue( (0 == eRc) );
        eRc = Name_CompareA(Node_getName(NodeLink_getNode(pNodes[2])),"C");
        XCTAssertTrue( (0 == eRc) );
        eRc = Name_CompareA(Node_getName(NodeLink_getNode(pNodes[3])),"K");
        XCTAssertTrue( (0 == eRc) );
        eRc = Name_CompareA(Node_getName(NodeLink_getNode(pNodes[4])),"D");
        XCTAssertTrue( (0 == eRc) );
        eRc = Name_CompareA(Node_getName(NodeLink_getNode(pNodes[5])),"E");
        XCTAssertTrue( (0 == eRc) );
        eRc = Name_CompareA(Node_getName(NodeLink_getNode(pNodes[6])),"H");
        XCTAssertTrue( (0 == eRc) );
        eRc = Name_CompareA(Node_getName(NodeLink_getNode(pNodes[7])),"F");
        XCTAssertTrue( (0 == eRc) );
        eRc = Name_CompareA(Node_getName(NodeLink_getNode(pNodes[8])),"J");
        XCTAssertTrue( (0 == eRc) );
        eRc = Name_CompareA(Node_getName(NodeLink_getNode(pNodes[9])),"G");
        XCTAssertTrue( (0 == eRc) );
        eRc = NodeTree_VisitPreorder(pObj, visitorPrint, NULL);
        XCTAssertFalse( (ERESULT_FAILED(eRc)) );

        visitorReset();
        eRc = NodeTree_VisitBreadthFirst(pObj, visitor, NULL);
        XCTAssertFalse( (ERESULT_FAILED(eRc)) );
        fprintf(stderr, "\nBreadthFirst(%d):\n",count);
        XCTAssertTrue( (10 == count) );
        fprintf(stderr, "\tADBCEFGKHJ (should be)\n\t");
        for (i=0; i<count; ++i) {
            pStrA = Node_getNameUTF8(NodeLink_getNode(pNodes[i]));
            fprintf(stderr, "%c", *pStrA);
            mem_Free((void *)pStrA);
            pStrA = NULL;
        }
        fprintf(stderr, " (actual)\n\n");
        eRc = Name_CompareA(Node_getName(NodeLink_getNode(pNodes[0])),"A");
        XCTAssertTrue( (0 == eRc) );
        eRc = Name_CompareA(Node_getName(NodeLink_getNode(pNodes[1])),"D");
        XCTAssertTrue( (0 == eRc) );
        eRc = Name_CompareA(Node_getName(NodeLink_getNode(pNodes[2])),"B");
        XCTAssertTrue( (0 == eRc) );
        eRc = Name_CompareA(Node_getName(NodeLink_getNode(pNodes[3])),"C");
        XCTAssertTrue( (0 == eRc) );
        eRc = Name_CompareA(Node_getName(NodeLink_getNode(pNodes[4])),"E");
        XCTAssertTrue( (0 == eRc) );
        eRc = Name_CompareA(Node_getName(NodeLink_getNode(pNodes[5])),"F");
        XCTAssertTrue( (0 == eRc) );
        eRc = Name_CompareA(Node_getName(NodeLink_getNode(pNodes[6])),"G");
        XCTAssertTrue( (0 == eRc) );
        eRc = Name_CompareA(Node_getName(NodeLink_getNode(pNodes[7])),"K");
        XCTAssertTrue( (0 == eRc) );
        eRc = Name_CompareA(Node_getName(NodeLink_getNode(pNodes[8])),"H");
        XCTAssertTrue( (0 == eRc) );
        eRc = Name_CompareA(Node_getName(NodeLink_getNode(pNodes[9])),"J");
        XCTAssertTrue( (0 == eRc) );
        eRc = NodeTree_VisitBreadthFirst(pObj, visitorPrint, NULL);
        XCTAssertFalse( (ERESULT_FAILED(eRc)) );

        pArray = NodeTree_ToLinearizationPost(pObj);
        XCTAssertFalse( (OBJ_NIL == pArray) );
        iMax = ObjArray_getSize(pArray);
        fprintf(stderr, "\nLinearization Postorder(%d):\n", iMax);
        XCTAssertTrue( (22 == iMax) );
        fprintf(stderr, "\tShould be: ((B(K)C)A((H)E(J)FG)D)\n");
        fprintf(stderr, "\tFound:     ");
        for (i=1; i<=iMax; ++i) {
            pStrA = Node_getNameUTF8(NodeLink_getNode(ObjArray_Get(pArray, i)));
            fprintf(stderr, "%s", pStrA);
            mem_Free((void *)pStrA);
        }
        fprintf(stderr, "\n");
        eRc = Name_CompareA(Node_getName(NodeLink_getNode(ObjArray_Get(pArray,  1))),"(");
        XCTAssertTrue( (0 == eRc) );
        eRc = Name_CompareA(Node_getName(NodeLink_getNode(ObjArray_Get(pArray,  2))),"(");
        XCTAssertTrue( (0 == eRc) );
        eRc = Name_CompareA(Node_getName(NodeLink_getNode(ObjArray_Get(pArray,  3))),"B");
        XCTAssertTrue( (0 == eRc) );
        eRc = Name_CompareA(Node_getName(NodeLink_getNode(ObjArray_Get(pArray,  4))),"(");
        XCTAssertTrue( (0 == eRc) );
        eRc = Name_CompareA(Node_getName(NodeLink_getNode(ObjArray_Get(pArray,  5))),"K");
        XCTAssertTrue( (0 == eRc) );
        eRc = Name_CompareA(Node_getName(NodeLink_getNode(ObjArray_Get(pArray,  6))),")");
        XCTAssertTrue( (0 == eRc) );
        eRc = Name_CompareA(Node_getName(NodeLink_getNode(ObjArray_Get(pArray,  7))),"C");
        XCTAssertTrue( (0 == eRc) );
        eRc = Name_CompareA(Node_getName(NodeLink_getNode(ObjArray_Get(pArray,  8))),")");
        XCTAssertTrue( (0 == eRc) );
        eRc = Name_CompareA(Node_getName(NodeLink_getNode(ObjArray_Get(pArray,  9))),"A");
        XCTAssertTrue( (0 == eRc) );
        eRc = Name_CompareA(Node_getName(NodeLink_getNode(ObjArray_Get(pArray, 10))),"(");
        XCTAssertTrue( (0 == eRc) );
        eRc = Name_CompareA(Node_getName(NodeLink_getNode(ObjArray_Get(pArray, 11))),"(");
        XCTAssertTrue( (0 == eRc) );
        eRc = Name_CompareA(Node_getName(NodeLink_getNode(ObjArray_Get(pArray, 12))),"H");
        XCTAssertTrue( (0 == eRc) );
        eRc = Name_CompareA(Node_getName(NodeLink_getNode(ObjArray_Get(pArray, 13))),")");
        XCTAssertTrue( (0 == eRc) );
        eRc = Name_CompareA(Node_getName(NodeLink_getNode(ObjArray_Get(pArray, 14))),"E");
        XCTAssertTrue( (0 == eRc) );
        eRc = Name_CompareA(Node_getName(NodeLink_getNode(ObjArray_Get(pArray, 15))),"(");
        XCTAssertTrue( (0 == eRc) );
        eRc = Name_CompareA(Node_getName(NodeLink_getNode(ObjArray_Get(pArray, 16))),"J");
        XCTAssertTrue( (0 == eRc) );
        eRc = Name_CompareA(Node_getName(NodeLink_getNode(ObjArray_Get(pArray, 17))),")");
        XCTAssertTrue( (0 == eRc) );
        eRc = Name_CompareA(Node_getName(NodeLink_getNode(ObjArray_Get(pArray, 18))),"F");
        XCTAssertTrue( (0 == eRc) );
        eRc = Name_CompareA(Node_getName(NodeLink_getNode(ObjArray_Get(pArray, 19))),"G");
        XCTAssertTrue( (0 == eRc) );
        eRc = Name_CompareA(Node_getName(NodeLink_getNode(ObjArray_Get(pArray, 20))),")");
        XCTAssertTrue( (0 == eRc) );
        eRc = Name_CompareA(Node_getName(NodeLink_getNode(ObjArray_Get(pArray, 21))),"D");
        XCTAssertTrue( (0 == eRc) );
        eRc = Name_CompareA(Node_getName(NodeLink_getNode(ObjArray_Get(pArray, 22))),")");
        XCTAssertTrue( (0 == eRc) );
        obj_Release(pArray);
        pArray = OBJ_NIL;
        fprintf(stderr, "\n\n\n");

        pArray = NodeTree_ToLinearizationPre(pObj);
        XCTAssertFalse( (OBJ_NIL == pArray) );
        iMax = ObjArray_getSize(pArray);
        fprintf(stderr, "\nLinearization Preorder(%d):\n",iMax);
        XCTAssertTrue( (22 == iMax) );
        fprintf(stderr, "\tShould be: (A(BC(K))D(E(H)F(J)G))\n");
        fprintf(stderr, "\tFound:     ");
        for (i=1; i<=iMax; ++i) {
            pStrA = Node_getNameUTF8(NodeLink_getNode(ObjArray_Get(pArray, i)));
            fprintf(stderr, "%s", pStrA);
            mem_Free((void *)pStrA);
        }
        fprintf(stderr, "\n");
        eRc = Name_CompareA(Node_getName(NodeLink_getNode(ObjArray_Get(pArray,  1))),"(");
        XCTAssertTrue( (0 == eRc) );
        eRc = Name_CompareA(Node_getName(NodeLink_getNode(ObjArray_Get(pArray,  2))),"A");
        XCTAssertTrue( (0 == eRc) );
        eRc = Name_CompareA(Node_getName(NodeLink_getNode(ObjArray_Get(pArray,  3))),"(");
        XCTAssertTrue( (0 == eRc) );
        eRc = Name_CompareA(Node_getName(NodeLink_getNode(ObjArray_Get(pArray,  4))),"B");
        XCTAssertTrue( (0 == eRc) );
        eRc = Name_CompareA(Node_getName(NodeLink_getNode(ObjArray_Get(pArray,  5))),"C");
        XCTAssertTrue( (0 == eRc) );
        eRc = Name_CompareA(Node_getName(NodeLink_getNode(ObjArray_Get(pArray,  6))),"(");
        XCTAssertTrue( (0 == eRc) );
        eRc = Name_CompareA(Node_getName(NodeLink_getNode(ObjArray_Get(pArray,  7))),"K");
        XCTAssertTrue( (0 == eRc) );
        eRc = Name_CompareA(Node_getName(NodeLink_getNode(ObjArray_Get(pArray,  8))),")");
        XCTAssertTrue( (0 == eRc) );
        eRc = Name_CompareA(Node_getName(NodeLink_getNode(ObjArray_Get(pArray,  9))),")");
        XCTAssertTrue( (0 == eRc) );
        eRc = Name_CompareA(Node_getName(NodeLink_getNode(ObjArray_Get(pArray, 10))),"D");
        XCTAssertTrue( (0 == eRc) );
        eRc = Name_CompareA(Node_getName(NodeLink_getNode(ObjArray_Get(pArray, 11))),"(");
        XCTAssertTrue( (0 == eRc) );
        eRc = Name_CompareA(Node_getName(NodeLink_getNode(ObjArray_Get(pArray, 12))),"E");
        XCTAssertTrue( (0 == eRc) );
        eRc = Name_CompareA(Node_getName(NodeLink_getNode(ObjArray_Get(pArray, 13))),"(");
        XCTAssertTrue( (0 == eRc) );
        eRc = Name_CompareA(Node_getName(NodeLink_getNode(ObjArray_Get(pArray, 14))),"H");
        XCTAssertTrue( (0 == eRc) );
        eRc = Name_CompareA(Node_getName(NodeLink_getNode(ObjArray_Get(pArray, 15))),")");
        XCTAssertTrue( (0 == eRc) );
        eRc = Name_CompareA(Node_getName(NodeLink_getNode(ObjArray_Get(pArray, 16))),"F");
        XCTAssertTrue( (0 == eRc) );
        eRc = Name_CompareA(Node_getName(NodeLink_getNode(ObjArray_Get(pArray, 17))),"(");
        XCTAssertTrue( (0 == eRc) );
        eRc = Name_CompareA(Node_getName(NodeLink_getNode(ObjArray_Get(pArray, 18))),"J");
        XCTAssertTrue( (0 == eRc) );
        eRc = Name_CompareA(Node_getName(NodeLink_getNode(ObjArray_Get(pArray, 19))),")");
        XCTAssertTrue( (0 == eRc) );
        eRc = Name_CompareA(Node_getName(NodeLink_getNode(ObjArray_Get(pArray, 20))),"G");
        XCTAssertTrue( (0 == eRc) );
        eRc = Name_CompareA(Node_getName(NodeLink_getNode(ObjArray_Get(pArray, 21))),")");
        XCTAssertTrue( (0 == eRc) );
        eRc = Name_CompareA(Node_getName(NodeLink_getNode(ObjArray_Get(pArray, 22))),")");
        XCTAssertTrue( (0 == eRc) );
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



int         test_NodeTree_Delete01(
    const
    char            *pTestName
)
{
    NODETREE_DATA   *pObj = OBJ_NIL;
    NODELINK_DATA   *pEntry = OBJ_NIL;
    uint32_t        i;
    ERESULT         eRc = ERESULT_SUCCESS;
    //ASTR_DATA       *pStr = OBJ_NIL;

    fprintf(stderr, "Performing: %s\n", pTestName);

    pObj = createTestTree01();
    XCTAssertFalse( (pObj == OBJ_NIL) );
    if (pObj) {

        eRc = NodeTree_Verify(pObj, NULL);
        XCTAssertFalse( (ERESULT_FAILED(eRc)) );

#ifdef XYZZY
        pStr = NodeTree_ToDebugString(pObj, 0);
        fprintf(stderr, "Debug = %s\n\n\n",AStr_getData(pStr));
        obj_Release(pStr);
        pStr = OBJ_NIL;
#endif

        i = NodeTree_SiblingCount(pObj, 1);
        XCTAssertTrue( (i == 1) );
        i = NodeTree_ChildCount(pObj, 1);
        XCTAssertTrue( (i == 2) );
        i = NodeTree_ChildCount(pObj, 2);
        XCTAssertTrue( (i == 3) );
        i = NodeTree_ChildCount(pObj, 3);
        XCTAssertTrue( (i == 0) );
        i = NodeTree_ChildCount(pObj, 4);
        XCTAssertTrue( (i == 1) );
        i = NodeTree_ChildCount(pObj, 5);
        XCTAssertTrue( (i == 0) );
        i = NodeTree_ChildCount(pObj, 6);
        XCTAssertTrue( (i == 1) );
        i = NodeTree_ChildCount(pObj, 7);
        XCTAssertTrue( (i == 1) );
        i = NodeTree_ChildCount(pObj, 8);
        XCTAssertTrue( (i == 0) );
        i = NodeTree_ChildCount(pObj, 9);
        XCTAssertTrue( (i == 0) );
        i = NodeTree_ChildCount(pObj, 10);
        XCTAssertTrue( (i == 0) );

        // Verify that the linkage fields are correct.
        pEntry = (NODELINK_DATA *)ObjArray_Get(pObj->pArray, 1);
        XCTAssertFalse( (pEntry == OBJ_NIL) );
        XCTAssertTrue( (NodeLink_getIndex(pEntry) == 1) );
        XCTAssertTrue( (NodeLink_getChild(pEntry) == 3) );
        XCTAssertTrue( (NodeLink_getSibling(pEntry) == 2) );
        XCTAssertTrue( (NodeLink_getParent(pEntry) == 0) );
        pEntry = (NODELINK_DATA *)ObjArray_Get(pObj->pArray, 2);
        XCTAssertFalse( (pEntry == OBJ_NIL) );
        XCTAssertTrue( (NodeLink_getIndex(pEntry) == 2) );
        XCTAssertTrue( (NodeLink_getChild(pEntry) == 6) );
        XCTAssertTrue( (NodeLink_getSibling(pEntry) == 0) );
        XCTAssertTrue( (NodeLink_getParent(pEntry) == 0) );
        pEntry = (NODELINK_DATA *)ObjArray_Get(pObj->pArray, 3);
        XCTAssertFalse( (pEntry == OBJ_NIL) );
        XCTAssertTrue( (NodeLink_getIndex(pEntry) == 3) );
        XCTAssertTrue( (NodeLink_getChild(pEntry) == 0) );
        XCTAssertTrue( (NodeLink_getSibling(pEntry) == 4) );
        XCTAssertTrue( (NodeLink_getParent(pEntry) == 1) );
        pEntry = (NODELINK_DATA *)ObjArray_Get(pObj->pArray, 4);
        XCTAssertFalse( (pEntry == OBJ_NIL) );
        XCTAssertTrue( (NodeLink_getIndex(pEntry) == 4) );
        XCTAssertTrue( (NodeLink_getChild(pEntry) == 5) );
        XCTAssertTrue( (NodeLink_getSibling(pEntry) == 0) );
        XCTAssertTrue( (NodeLink_getParent(pEntry) == 1) );
        pEntry = (NODELINK_DATA *)ObjArray_Get(pObj->pArray, 5);
        XCTAssertFalse( (pEntry == OBJ_NIL) );
        XCTAssertTrue( (NodeLink_getIndex(pEntry) == 5) );
        XCTAssertTrue( (NodeLink_getChild(pEntry) == 0) );
        XCTAssertTrue( (NodeLink_getSibling(pEntry) == 0) );
        XCTAssertTrue( (NodeLink_getParent(pEntry) == 4) );
        pEntry = (NODELINK_DATA *)ObjArray_Get(pObj->pArray, 6);
        XCTAssertFalse( (pEntry == OBJ_NIL) );
        XCTAssertTrue( (NodeLink_getIndex(pEntry) == 6) );
        XCTAssertTrue( (NodeLink_getChild(pEntry) == 9) );
        XCTAssertTrue( (NodeLink_getSibling(pEntry) == 7) );
        XCTAssertTrue( (NodeLink_getParent(pEntry) == 2) );
        pEntry = (NODELINK_DATA *)ObjArray_Get(pObj->pArray, 7);
        XCTAssertFalse( (pEntry == OBJ_NIL) );
        XCTAssertTrue( (NodeLink_getIndex(pEntry) == 7) );
        XCTAssertTrue( (NodeLink_getChild(pEntry) == 10) );
        XCTAssertTrue( (NodeLink_getSibling(pEntry) == 8) );
        XCTAssertTrue( (NodeLink_getParent(pEntry) == 2) );
        pEntry = (NODELINK_DATA *)ObjArray_Get(pObj->pArray, 8);
        XCTAssertFalse( (pEntry == OBJ_NIL) );
        XCTAssertTrue( (NodeLink_getIndex(pEntry) == 8) );
        XCTAssertTrue( (NodeLink_getChild(pEntry) == 0) );
        XCTAssertTrue( (NodeLink_getSibling(pEntry) == 0) );
        XCTAssertTrue( (NodeLink_getParent(pEntry) == 2) );
        pEntry = (NODELINK_DATA *)ObjArray_Get(pObj->pArray, 9);
        XCTAssertFalse( (pEntry == OBJ_NIL) );
        XCTAssertTrue( (NodeLink_getIndex(pEntry) == 9) );
        XCTAssertTrue( (NodeLink_getChild(pEntry) == 0) );
        XCTAssertTrue( (NodeLink_getSibling(pEntry) == 0) );
        XCTAssertTrue( (NodeLink_getParent(pEntry) == 6) );
        pEntry = (NODELINK_DATA *)ObjArray_Get(pObj->pArray, 10);
        XCTAssertFalse( (pEntry == OBJ_NIL) );
        XCTAssertTrue( (NodeLink_getIndex(pEntry) == 10) );
        XCTAssertTrue( (NodeLink_getChild(pEntry) == 0) );
        XCTAssertTrue( (NodeLink_getSibling(pEntry) == 0) );
        XCTAssertTrue( (NodeLink_getParent(pEntry) == 7) );

/*          Before Delete
 Tree    Index   Child  Sibling  Parent
                 (Left) (Right)
 A         1       3       2       0
 --B       3       0       4       1
 --C       4       5       0       1
 ----K     5       0       0       4
 D         2       6       0       0
 --E       6       9       7       2
 ----H     9       0       0       6
 --F       7      10       8       2
 ----J    10       0       0       7
 --G       8       0       0       2
 */

        eRc = NodeTree_NodeDelete(pObj, 6);    // Delete E(6) and H(9)
        //                                          // child D(2)
        XCTAssertFalse( (ERESULT_FAILED(eRc)) );

#ifdef XYZZY
        pStr = NodeTree_ToDebugString(pObj, 0);
        fprintf(stderr, "After Delete = %s\n\n\n",AStr_getData(pStr));
        obj_Release(pStr);
        pStr = OBJ_NIL;
#endif

        /*          After Delete
         Tree    Index   Child  Sibling  Parent
                         (Left) (Right)
         A         1       3       2       0
         --B       3       0       4       1
         --C       4       5       0       1
         ----K     5       0       0       4
         D         2       7       0       0
         --F       7      10       8       2
         ----J    10       0       0       7
         --G       8       0       0       2
         */

        // Verify that the linkage fields are correct.
        pEntry = (NODELINK_DATA *)ObjArray_Get(pObj->pArray, 1);
        XCTAssertFalse( (pEntry == OBJ_NIL) );
        XCTAssertTrue( (NodeLink_getIndex(pEntry) == 1) );
        XCTAssertTrue( (NodeLink_getChild(pEntry) == 3) );
        XCTAssertTrue( (NodeLink_getSibling(pEntry) == 2) );
        XCTAssertTrue( (NodeLink_getParent(pEntry) == 0) );
        pEntry = (NODELINK_DATA *)ObjArray_Get(pObj->pArray, 2);
        XCTAssertFalse( (pEntry == OBJ_NIL) );
        XCTAssertTrue( (NodeLink_getIndex(pEntry) == 2) );
        XCTAssertTrue( (NodeLink_getChild(pEntry) == 7) );
        XCTAssertTrue( (NodeLink_getSibling(pEntry) == 0) );
        XCTAssertTrue( (NodeLink_getParent(pEntry) == 0) );
        pEntry = (NODELINK_DATA *)ObjArray_Get(pObj->pArray, 3);
        XCTAssertFalse( (pEntry == OBJ_NIL) );
        XCTAssertTrue( (NodeLink_getIndex(pEntry) == 3) );
        XCTAssertTrue( (NodeLink_getChild(pEntry) == 0) );
        XCTAssertTrue( (NodeLink_getSibling(pEntry) == 4) );
        XCTAssertTrue( (NodeLink_getParent(pEntry) == 1) );
        pEntry = (NODELINK_DATA *)ObjArray_Get(pObj->pArray, 4);
        XCTAssertFalse( (pEntry == OBJ_NIL) );
        XCTAssertTrue( (NodeLink_getIndex(pEntry) == 4) );
        XCTAssertTrue( (NodeLink_getChild(pEntry) == 5) );
        XCTAssertTrue( (NodeLink_getSibling(pEntry) == 0) );
        XCTAssertTrue( (NodeLink_getParent(pEntry) == 1) );
        pEntry = (NODELINK_DATA *)ObjArray_Get(pObj->pArray, 5);
        XCTAssertFalse( (pEntry == OBJ_NIL) );
        XCTAssertTrue( (NodeLink_getIndex(pEntry) == 5) );
        XCTAssertTrue( (NodeLink_getChild(pEntry) == 0) );
        XCTAssertTrue( (NodeLink_getSibling(pEntry) == 0) );
        XCTAssertTrue( (NodeLink_getParent(pEntry) == 4) );
        pEntry = (NODELINK_DATA *)ObjArray_Get(pObj->pArray, 6);
        XCTAssertTrue( (pEntry == OBJ_NIL) );
        pEntry = (NODELINK_DATA *)ObjArray_Get(pObj->pArray, 7);
        XCTAssertFalse( (pEntry == OBJ_NIL) );
        XCTAssertTrue( (NodeLink_getIndex(pEntry) == 7) );
        XCTAssertTrue( (NodeLink_getChild(pEntry) == 10) );
        XCTAssertTrue( (NodeLink_getSibling(pEntry) == 8) );
        XCTAssertTrue( (NodeLink_getParent(pEntry) == 2) );
        pEntry = (NODELINK_DATA *)ObjArray_Get(pObj->pArray, 8);
        XCTAssertFalse( (pEntry == OBJ_NIL) );
        XCTAssertTrue( (NodeLink_getIndex(pEntry) == 8) );
        XCTAssertTrue( (NodeLink_getChild(pEntry) == 0) );
        XCTAssertTrue( (NodeLink_getSibling(pEntry) == 0) );
        XCTAssertTrue( (NodeLink_getParent(pEntry) == 2) );
        pEntry = (NODELINK_DATA *)ObjArray_Get(pObj->pArray, 9);
        XCTAssertTrue( (pEntry == OBJ_NIL) );
        pEntry = (NODELINK_DATA *)ObjArray_Get(pObj->pArray, 10);
        XCTAssertFalse( (pEntry == OBJ_NIL) );
        XCTAssertTrue( (NodeLink_getIndex(pEntry) == 10) );
        XCTAssertTrue( (NodeLink_getChild(pEntry) == 0) );
        XCTAssertTrue( (NodeLink_getSibling(pEntry) == 0) );
        XCTAssertTrue( (NodeLink_getParent(pEntry) == 7) );

        XCTAssertTrue( (obj_IsFlag(pObj, OBJ_FLAG_ALLOC)) );
        obj_Release(pObj);
        pObj = OBJ_NIL;
    }

    fprintf(stderr, "...%s completed.\n\n\n", pTestName);
    return 1;
}



int         test_NodeTree_Move01(
    const
    char        *pTestName
)
{
    NODETREE_DATA    *pObj = OBJ_NIL;
    NODELINK_DATA   *pEntry = OBJ_NIL;
    uint32_t        i;
    ERESULT         eRc = ERESULT_SUCCESS;

    fprintf(stderr, "Performing: %s\n", pTestName);

    pObj = createTestTree01();
    XCTAssertFalse( (pObj == OBJ_NIL) );
    if (pObj) {

#ifdef XYZZY
        pStr = NodeTree_ToDebugString(pObj, 0);
        fprintf(stderr, "Debug = %s\n\n\n",AStr_getData(pStr));
        obj_Release(pStr);
        pStr = OBJ_NIL;
#endif

        i = NodeTree_SiblingCount(pObj, 1);
        XCTAssertTrue( (i == 1) );
        i = NodeTree_ChildCount(pObj, 1);
        XCTAssertTrue( (i == 2) );
        i = NodeTree_ChildCount(pObj, 2);
        XCTAssertTrue( (i == 3) );
        i = NodeTree_ChildCount(pObj, 3);
        XCTAssertTrue( (i == 0) );
        i = NodeTree_ChildCount(pObj, 4);
        XCTAssertTrue( (i == 1) );
        i = NodeTree_ChildCount(pObj, 5);
        XCTAssertTrue( (i == 0) );
        i = NodeTree_ChildCount(pObj, 6);
        XCTAssertTrue( (i == 1) );
        i = NodeTree_ChildCount(pObj, 7);
        XCTAssertTrue( (i == 1) );
        i = NodeTree_ChildCount(pObj, 8);
        XCTAssertTrue( (i == 0) );
        i = NodeTree_ChildCount(pObj, 9);
        XCTAssertTrue( (i == 0) );
        i = NodeTree_ChildCount(pObj, 10);
        XCTAssertTrue( (i == 0) );

        // Verify that the linkage fields are correct.
        pEntry = (NODELINK_DATA *)ObjArray_Get(pObj->pArray, 1);
        XCTAssertFalse( (pEntry == OBJ_NIL) );
        XCTAssertTrue( (NodeLink_getIndex(pEntry) == 1) );
        XCTAssertTrue( (NodeLink_getChild(pEntry) == 3) );
        XCTAssertTrue( (NodeLink_getSibling(pEntry) == 2) );
        XCTAssertTrue( (NodeLink_getParent(pEntry) == 0) );
        pEntry = (NODELINK_DATA *)ObjArray_Get(pObj->pArray, 2);
        XCTAssertFalse( (pEntry == OBJ_NIL) );
        XCTAssertTrue( (NodeLink_getIndex(pEntry) == 2) );
        XCTAssertTrue( (NodeLink_getChild(pEntry) == 6) );
        XCTAssertTrue( (NodeLink_getSibling(pEntry) == 0) );
        XCTAssertTrue( (NodeLink_getParent(pEntry) == 0) );
        pEntry = (NODELINK_DATA *)ObjArray_Get(pObj->pArray, 3);
        XCTAssertFalse( (pEntry == OBJ_NIL) );
        XCTAssertTrue( (NodeLink_getIndex(pEntry) == 3) );
        XCTAssertTrue( (NodeLink_getChild(pEntry) == 0) );
        XCTAssertTrue( (NodeLink_getSibling(pEntry) == 4) );
        XCTAssertTrue( (NodeLink_getParent(pEntry) == 1) );
        pEntry = (NODELINK_DATA *)ObjArray_Get(pObj->pArray, 4);
        XCTAssertFalse( (pEntry == OBJ_NIL) );
        XCTAssertTrue( (NodeLink_getIndex(pEntry) == 4) );
        XCTAssertTrue( (NodeLink_getChild(pEntry) == 5) );
        XCTAssertTrue( (NodeLink_getSibling(pEntry) == 0) );
        XCTAssertTrue( (NodeLink_getParent(pEntry) == 1) );
        pEntry = (NODELINK_DATA *)ObjArray_Get(pObj->pArray, 5);
        XCTAssertFalse( (pEntry == OBJ_NIL) );
        XCTAssertTrue( (NodeLink_getIndex(pEntry) == 5) );
        XCTAssertTrue( (NodeLink_getChild(pEntry) == 0) );
        XCTAssertTrue( (NodeLink_getSibling(pEntry) == 0) );
        XCTAssertTrue( (NodeLink_getParent(pEntry) == 4) );
        pEntry = (NODELINK_DATA *)ObjArray_Get(pObj->pArray, 6);
        XCTAssertFalse( (pEntry == OBJ_NIL) );
        XCTAssertTrue( (NodeLink_getIndex(pEntry) == 6) );
        XCTAssertTrue( (NodeLink_getChild(pEntry) == 9) );
        XCTAssertTrue( (NodeLink_getSibling(pEntry) == 7) );
        XCTAssertTrue( (NodeLink_getParent(pEntry) == 2) );
        pEntry = (NODELINK_DATA *)ObjArray_Get(pObj->pArray, 7);
        XCTAssertFalse( (pEntry == OBJ_NIL) );
        XCTAssertTrue( (NodeLink_getIndex(pEntry) == 7) );
        XCTAssertTrue( (NodeLink_getChild(pEntry) == 10) );
        XCTAssertTrue( (NodeLink_getSibling(pEntry) == 8) );
        XCTAssertTrue( (NodeLink_getParent(pEntry) == 2) );
        pEntry = (NODELINK_DATA *)ObjArray_Get(pObj->pArray, 8);
        XCTAssertFalse( (pEntry == OBJ_NIL) );
        XCTAssertTrue( (NodeLink_getIndex(pEntry) == 8) );
        XCTAssertTrue( (NodeLink_getChild(pEntry) == 0) );
        XCTAssertTrue( (NodeLink_getSibling(pEntry) == 0) );
        XCTAssertTrue( (NodeLink_getParent(pEntry) == 2) );
        pEntry = (NODELINK_DATA *)ObjArray_Get(pObj->pArray, 9);
        XCTAssertFalse( (pEntry == OBJ_NIL) );
        XCTAssertTrue( (NodeLink_getIndex(pEntry) == 9) );
        XCTAssertTrue( (NodeLink_getChild(pEntry) == 0) );
        XCTAssertTrue( (NodeLink_getSibling(pEntry) == 0) );
        XCTAssertTrue( (NodeLink_getParent(pEntry) == 6) );
        pEntry = (NODELINK_DATA *)ObjArray_Get(pObj->pArray, 10);
        XCTAssertFalse( (pEntry == OBJ_NIL) );
        XCTAssertTrue( (NodeLink_getIndex(pEntry) == 10) );
        XCTAssertTrue( (NodeLink_getChild(pEntry) == 0) );
        XCTAssertTrue( (NodeLink_getSibling(pEntry) == 0) );
        XCTAssertTrue( (NodeLink_getParent(pEntry) == 7) );

        /*          Before Move
         Tree    Index   Child  Sibling  Parent
         (Left) (Right)
         A         1       3       2       0
         --B       3       0       4       1
         --C       4       5       0       1
         ----K     5       0       0       4
         D         2       6       0       0
         --E       6       9       7       2
         ----H     9       0       0       6
         --F       7      10       8       2
         ----J    10       0       0       7
         --G       8       0       0       2
         */

        eRc = NodeTree_ChildrenMove(pObj, 7, 3);    // Move J(10) under B(3)
        XCTAssertFalse( (ERESULT_FAILED(eRc)) );

        /*          After Move
         Tree    Index   Child  Sibling  Parent
                         (Left) (Right)
         A         1       3       2       0
         --B       3      10       4       1
         --C       4       5       0       1
         ----K     5       0       0       4
         D         2       6       0       0
         --E       6       9       7       2
         ----H     9       0       0       6
         --F       7       0       8       2
         ----J    10       0       0       3
         --G       8       0       0       2
         */

        // Verify that the linkage fields are correct.
        pEntry = (NODELINK_DATA *)ObjArray_Get(pObj->pArray, 1);
        XCTAssertFalse( (pEntry == OBJ_NIL) );
        XCTAssertTrue( (NodeLink_getIndex(pEntry) == 1) );
        XCTAssertTrue( (NodeLink_getChild(pEntry) == 3) );
        XCTAssertTrue( (NodeLink_getSibling(pEntry) == 2) );
        XCTAssertTrue( (NodeLink_getParent(pEntry) == 0) );
        pEntry = (NODELINK_DATA *)ObjArray_Get(pObj->pArray, 2);
        XCTAssertFalse( (pEntry == OBJ_NIL) );
        XCTAssertTrue( (NodeLink_getIndex(pEntry) == 2) );
        XCTAssertTrue( (NodeLink_getChild(pEntry) == 6) );
        XCTAssertTrue( (NodeLink_getSibling(pEntry) == 0) );
        XCTAssertTrue( (NodeLink_getParent(pEntry) == 0) );
        pEntry = (NODELINK_DATA *)ObjArray_Get(pObj->pArray, 3);
        XCTAssertFalse( (pEntry == OBJ_NIL) );
        XCTAssertTrue( (NodeLink_getIndex(pEntry) == 3) );
        XCTAssertTrue( (NodeLink_getChild(pEntry) == 10) );
        XCTAssertTrue( (NodeLink_getSibling(pEntry) == 4) );
        XCTAssertTrue( (NodeLink_getParent(pEntry) == 1) );
        pEntry = (NODELINK_DATA *)ObjArray_Get(pObj->pArray, 4);
        XCTAssertFalse( (pEntry == OBJ_NIL) );
        XCTAssertTrue( (NodeLink_getIndex(pEntry) == 4) );
        XCTAssertTrue( (NodeLink_getChild(pEntry) == 5) );
        XCTAssertTrue( (NodeLink_getSibling(pEntry) == 0) );
        XCTAssertTrue( (NodeLink_getParent(pEntry) == 1) );
        pEntry = (NODELINK_DATA *)ObjArray_Get(pObj->pArray, 5);
        XCTAssertFalse( (pEntry == OBJ_NIL) );
        XCTAssertTrue( (NodeLink_getIndex(pEntry) == 5) );
        XCTAssertTrue( (NodeLink_getChild(pEntry) == 0) );
        XCTAssertTrue( (NodeLink_getSibling(pEntry) == 0) );
        XCTAssertTrue( (NodeLink_getParent(pEntry) == 4) );
        pEntry = (NODELINK_DATA *)ObjArray_Get(pObj->pArray, 6);
        XCTAssertFalse( (pEntry == OBJ_NIL) );
        XCTAssertTrue( (NodeLink_getIndex(pEntry) == 6) );
        XCTAssertTrue( (NodeLink_getChild(pEntry) == 9) );
        XCTAssertTrue( (NodeLink_getSibling(pEntry) == 7) );
        XCTAssertTrue( (NodeLink_getParent(pEntry) == 2) );
        pEntry = (NODELINK_DATA *)ObjArray_Get(pObj->pArray, 7);
        XCTAssertFalse( (pEntry == OBJ_NIL) );
        XCTAssertTrue( (NodeLink_getIndex(pEntry) == 7) );
        XCTAssertTrue( (NodeLink_getChild(pEntry) == 0) );
        XCTAssertTrue( (NodeLink_getSibling(pEntry) == 8) );
        XCTAssertTrue( (NodeLink_getParent(pEntry) == 2) );
        pEntry = (NODELINK_DATA *)ObjArray_Get(pObj->pArray, 8);
        XCTAssertFalse( (pEntry == OBJ_NIL) );
        XCTAssertTrue( (NodeLink_getIndex(pEntry) == 8) );
        XCTAssertTrue( (NodeLink_getChild(pEntry) == 0) );
        XCTAssertTrue( (NodeLink_getSibling(pEntry) == 0) );
        XCTAssertTrue( (NodeLink_getParent(pEntry) == 2) );
        pEntry = (NODELINK_DATA *)ObjArray_Get(pObj->pArray, 9);
        XCTAssertFalse( (pEntry == OBJ_NIL) );
        XCTAssertTrue( (NodeLink_getIndex(pEntry) == 9) );
        XCTAssertTrue( (NodeLink_getChild(pEntry) == 0) );
        XCTAssertTrue( (NodeLink_getSibling(pEntry) == 0) );
        XCTAssertTrue( (NodeLink_getParent(pEntry) == 6) );
        pEntry = (NODELINK_DATA *)ObjArray_Get(pObj->pArray, 10);
        XCTAssertFalse( (pEntry == OBJ_NIL) );
        XCTAssertTrue( (NodeLink_getIndex(pEntry) == 10) );
        XCTAssertTrue( (NodeLink_getChild(pEntry) == 0) );
        XCTAssertTrue( (NodeLink_getSibling(pEntry) == 0) );
        XCTAssertTrue( (NodeLink_getParent(pEntry) == 3) );

        XCTAssertTrue( (obj_IsFlag(pObj, OBJ_FLAG_ALLOC)) );
        obj_Release(pObj);
        pObj = OBJ_NIL;
    }

    fprintf(stderr, "...%s completed.\n\n", pTestName);
    return 1;
}



int         test_NodeTree_Node01(
    const
    char        *pTestName
)
{
    NODETREE_DATA    *pObj = OBJ_NIL;
    NODELINK_DATA   *pNodeA = OBJ_NIL;
    NODELINK_DATA   *pNodeB = OBJ_NIL;
    NODELINK_DATA   *pNode = OBJ_NIL;
    uint32_t        nodeA;
    uint32_t        nodeB;
    ASTR_DATA       *pStr = OBJ_NIL;

    fprintf(stderr, "Performing: %s\n", pTestName);

    pObj = NodeTree_Alloc( );
    XCTAssertFalse( (OBJ_NIL == pObj) );
    pObj = NodeTree_Init( pObj );
    XCTAssertFalse( (OBJ_NIL == pObj) );
    if (pObj) {

        pNodeA = NodeLink_NewWithUTF8ConAndClass(0, "A", OBJ_NIL);
        XCTAssertFalse( (OBJ_NIL == pNodeA) );
        pNodeB = NodeLink_NewWithUTF8ConAndClass(0, "B", OBJ_NIL);
        XCTAssertFalse( (OBJ_NIL == pNodeB) );

        nodeA = NodeTree_ChildAdd(pObj, 0, pNodeA);
        XCTAssertTrue( (nodeA == 1) );
        XCTAssertTrue( (NodeLink_getIndex(pNodeA) == 1) );
        nodeB = NodeTree_ChildAdd(pObj,NodeLink_getIndex(pNodeA), pNodeB);
        XCTAssertTrue( (nodeB == 2) );

        pNode = NodeTree_Node(pObj, nodeA);
        XCTAssertTrue( (pNodeA == pNode) );
        pNode = NodeTree_Node(pObj, nodeB);
        XCTAssertTrue( (pNodeB == pNode) );

        pStr = NodeTree_ToDebugString(pObj, 0);
        if (pStr) {
            fprintf(stderr, "%s\n", AStr_getData(pStr));
            obj_Release(pStr);
            pStr = OBJ_NIL;
        }

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



int         test_NodeTree_NodeLinkChild(
    const
    char        *pTestName
)
{
    NODETREE_DATA    *pObj = OBJ_NIL;
    NODELINK_DATA   *pNodeA = OBJ_NIL;
    NODELINK_DATA   *pNode = OBJ_NIL;
    uint32_t        nodeA;
    uint32_t        nodeB;
    uint32_t        nodeC;
    uint32_t        nodeD;
    uint32_t        node;
    ERESULT         eRc;

    fprintf(stderr, "Performing: %s\n", pTestName);

    pObj = NodeTree_Alloc( );
    XCTAssertFalse( (OBJ_NIL == pObj) );
    pObj = NodeTree_Init( pObj );
    XCTAssertFalse( (OBJ_NIL == pObj) );
    if (pObj) {

        pNodeA = NodeLink_NewWithUTF8ConAndClass(0, "A", OBJ_NIL);
        XCTAssertFalse( (OBJ_NIL == pNodeA) );

        // Set up root.
        nodeA = NodeTree_ChildAdd(pObj, 0, pNodeA);
        XCTAssertTrue( (nodeA == 1) );
        XCTAssertTrue( (NodeLink_getIndex(pNodeA) == 1) );
        pNode = NodeTree_Node(pObj, nodeA);
        XCTAssertTrue( (pNodeA == pNode) );

        nodeB = NodeTree_NodeNewUTF8(pObj, 10, "B", OBJ_NIL, 0, 0);
        XCTAssertTrue( (nodeB == 2) );
        nodeC = NodeTree_NodeNewUTF8(pObj, 20, "C", OBJ_NIL, 0, 0);
        XCTAssertTrue( (nodeC == 3) );
        nodeD = NodeTree_NodeNewUTF8(pObj, 30, "D", OBJ_NIL, 0, 0);
        XCTAssertTrue( (nodeD == 4) );

        eRc = NodeTree_NodeLinkChild(pObj, nodeA, nodeB);
        XCTAssertFalse( (ERESULT_FAILED(eRc)) );
        node = NodeTree_NodeParent(pObj,nodeB);
        XCTAssertTrue( (node == 1) );
        eRc = NodeTree_NodeLinkChild(pObj, nodeB, nodeC);
        XCTAssertFalse( (ERESULT_FAILED(eRc)) );
        node = NodeTree_NodeParent(pObj,nodeC);
        XCTAssertTrue( (node == nodeB) );
        eRc = NodeTree_NodeLinkChild(pObj, nodeB, nodeD);
        XCTAssertFalse( (ERESULT_FAILED(eRc)) );
        node = NodeTree_NodeParent(pObj,nodeD);
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



int         test_NodeTree_UpDown02(
    const
    char            *pTestName
)
{
    NODETREE_DATA   *pObj = OBJ_NIL;
    OBJARRAY_DATA   *pArray = OBJ_NIL;
    NODELINK_DATA   *pEntry = OBJ_NIL;
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
        pStr = NodeTree_ToDebugString(pObj, 0);
        fprintf(stderr, "Debug = %s\n\n\n",AStr_getData(pStr));
        obj_Release(pStr);
        pStr = OBJ_NIL;
#endif

        i = NodeTree_ChildCount(pObj, 1);
        XCTAssertTrue( (i == 2) );
        i = NodeTree_ChildCount(pObj, 2);
        XCTAssertTrue( (i == 2) );
        i = NodeTree_ChildCount(pObj, 3);
        XCTAssertTrue( (i == 2) );
        i = NodeTree_ChildCount(pObj, 4);
        XCTAssertTrue( (i == 0) );
        i = NodeTree_ChildCount(pObj, 5);
        XCTAssertTrue( (i == 2) );
        i = NodeTree_ChildCount(pObj, 6);
        XCTAssertTrue( (i == 0) );
        i = NodeTree_ChildCount(pObj, 7);
        XCTAssertTrue( (i == 0) );
        i = NodeTree_ChildCount(pObj, 8);
        XCTAssertTrue( (i == 0) );
        i = NodeTree_ChildCount(pObj, 9);
        XCTAssertTrue( (i == 2) );
        i = NodeTree_ChildCount(pObj, 10);
        XCTAssertTrue( (i == 0) );
        i = NodeTree_ChildCount(pObj, 11);
        XCTAssertTrue( (i == 0) );

        // Verify that the linkage fields are correct.
        pEntry = (NODELINK_DATA *)ObjArray_Get(pObj->pArray, 1);
        XCTAssertFalse( (pEntry == OBJ_NIL) );
        XCTAssertTrue( (NodeLink_getIndex(pEntry) == 1) );
        XCTAssertTrue( (NodeLink_getSibling(pEntry) == 0) );
        XCTAssertTrue( (NodeLink_getChild(pEntry) == 2) );
        XCTAssertTrue( (NodeLink_getParent(pEntry) == 0) );
        pEntry = (NODELINK_DATA *)ObjArray_Get(pObj->pArray, 2);
        XCTAssertFalse( (pEntry == OBJ_NIL) );
        XCTAssertTrue( (NodeLink_getIndex(pEntry) == 2) );
        XCTAssertTrue( (NodeLink_getSibling(pEntry) == 3) );
        XCTAssertTrue( (NodeLink_getChild(pEntry) == 4) );
        XCTAssertTrue( (NodeLink_getParent(pEntry) == 1) );
        pEntry = (NODELINK_DATA *)ObjArray_Get(pObj->pArray, 3);
        XCTAssertFalse( (pEntry == OBJ_NIL) );
        XCTAssertTrue( (NodeLink_getIndex(pEntry) == 3) );
        XCTAssertTrue( (NodeLink_getSibling(pEntry) == 0) );
        XCTAssertTrue( (NodeLink_getChild(pEntry) == 8) );
        XCTAssertTrue( (NodeLink_getParent(pEntry) == 1) );
        pEntry = (NODELINK_DATA *)ObjArray_Get(pObj->pArray, 4);
        XCTAssertFalse( (pEntry == OBJ_NIL) );
        XCTAssertTrue( (NodeLink_getIndex(pEntry) == 4) );
        XCTAssertTrue( (NodeLink_getSibling(pEntry) == 5) );
        XCTAssertTrue( (NodeLink_getChild(pEntry) == 0) );
        XCTAssertTrue( (NodeLink_getParent(pEntry) == 2) );
        pEntry = (NODELINK_DATA *)ObjArray_Get(pObj->pArray, 5);
        XCTAssertFalse( (pEntry == OBJ_NIL) );
        XCTAssertTrue( (NodeLink_getIndex(pEntry) == 5) );
        XCTAssertTrue( (NodeLink_getSibling(pEntry) == 0) );
        XCTAssertTrue( (NodeLink_getChild(pEntry) == 6) );
        XCTAssertTrue( (NodeLink_getParent(pEntry) == 2) );
        pEntry = (NODELINK_DATA *)ObjArray_Get(pObj->pArray, 6);
        XCTAssertFalse( (pEntry == OBJ_NIL) );
        XCTAssertTrue( (NodeLink_getIndex(pEntry) == 6) );
        XCTAssertTrue( (NodeLink_getSibling(pEntry) == 7) );
        XCTAssertTrue( (NodeLink_getChild(pEntry) == 0) );
        XCTAssertTrue( (NodeLink_getParent(pEntry) == 5) );
        pEntry = (NODELINK_DATA *)ObjArray_Get(pObj->pArray, 7);
        XCTAssertFalse( (pEntry == OBJ_NIL) );
        XCTAssertTrue( (NodeLink_getIndex(pEntry) == 7) );
        XCTAssertTrue( (NodeLink_getSibling(pEntry) == 0) );
        XCTAssertTrue( (NodeLink_getChild(pEntry) == 0) );
        XCTAssertTrue( (NodeLink_getParent(pEntry) == 5) );
        pEntry = (NODELINK_DATA *)ObjArray_Get(pObj->pArray, 8);
        XCTAssertFalse( (pEntry == OBJ_NIL) );
        XCTAssertTrue( (NodeLink_getIndex(pEntry) == 8) );
        XCTAssertTrue( (NodeLink_getSibling(pEntry) == 9) );
        XCTAssertTrue( (NodeLink_getChild(pEntry) == 0) );
        XCTAssertTrue( (NodeLink_getParent(pEntry) == 3) );
        pEntry = (NODELINK_DATA *)ObjArray_Get(pObj->pArray, 9);
        XCTAssertFalse( (pEntry == OBJ_NIL) );
        XCTAssertTrue( (NodeLink_getIndex(pEntry) == 9) );
        XCTAssertTrue( (NodeLink_getSibling(pEntry) == 0) );
        XCTAssertTrue( (NodeLink_getChild(pEntry) == 10) );
        XCTAssertTrue( (NodeLink_getParent(pEntry) == 3) );
        pEntry = (NODELINK_DATA *)ObjArray_Get(pObj->pArray, 10);
        XCTAssertFalse( (pEntry == OBJ_NIL) );
        XCTAssertTrue( (NodeLink_getIndex(pEntry) == 10) );
        XCTAssertTrue( (NodeLink_getSibling(pEntry) == 11) );
        XCTAssertTrue( (NodeLink_getChild(pEntry) == 0) );
        XCTAssertTrue( (NodeLink_getParent(pEntry) == 9) );
        pEntry = (NODELINK_DATA *)ObjArray_Get(pObj->pArray, 11);
        XCTAssertFalse( (pEntry == OBJ_NIL) );
        XCTAssertTrue( (NodeLink_getIndex(pEntry) == 11) );
        XCTAssertTrue( (NodeLink_getSibling(pEntry) == 0) );
        XCTAssertTrue( (NodeLink_getChild(pEntry) == 0) );
        XCTAssertTrue( (NodeLink_getParent(pEntry) == 9) );

#ifdef XYZZY
        visitorReset();
        eRc = NodeTree_VisitInorder(pObj, visitor, NULL);
        XCTAssertFalse( (ERESULT_FAILED(eRc)) );
        fprintf(stderr, "\nInorder(%d):\n",count);
        //XCTAssertTrue( (11 == count) );
        fprintf(stderr, "\ta + b / c *1 d - e *2 f (should be)\n\t");
        for (i=0; i<count; ++i) {
            pStrA = Node_getNameUTF8(NodeLink_getNode(pNodes[i]));
            fprintf(stderr, "%s ", pStrA);
            mem_Free((void *)pStrA);
            pStrA = NULL;
        }
        fprintf(stderr, " (actual)\n");
        eRc = Name_CompareA(Node_getName(NodeLink_getNode(pNodes[0])),"a");
        XCTAssertTrue( (0 == eRc) );
        eRc = Name_CompareA(Node_getName(NodeLink_getNode(pNodes[1])),"+");
        XCTAssertTrue( (0 == eRc) );
        eRc = Name_CompareA(Node_getName(NodeLink_getNode(pNodes[2])),"b");
        XCTAssertTrue( (0 == eRc) );
        eRc = Name_CompareA(Node_getName(NodeLink_getNode(pNodes[3])),"/");
        XCTAssertTrue( (0 == eRc) );
        eRc = Name_CompareA(Node_getName(NodeLink_getNode(pNodes[4])),"c");
        XCTAssertTrue( (0 == eRc) );
        eRc = Name_CompareA(Node_getName(NodeLink_getNode(pNodes[5])),"*1");
        XCTAssertTrue( (0 == eRc) );
        eRc = Name_CompareA(Node_getName(NodeLink_getNode(pNodes[6])),"d");
        XCTAssertTrue( (0 == eRc) );
        eRc = Name_CompareA(Node_getName(NodeLink_getNode(pNodes[7])),"-");
        XCTAssertTrue( (0 == eRc) );
        eRc = Name_CompareA(Node_getName(NodeLink_getNode(pNodes[8])),"e");
        XCTAssertTrue( (0 == eRc) );
        eRc = Name_CompareA(Node_getName(NodeLink_getNode(pNodes[8])),"*2");
        XCTAssertTrue( (0 == eRc) );
        eRc = Name_CompareA(Node_getName(NodeLink_getNode(pNodes[8])),"f");
        XCTAssertTrue( (0 == eRc) );
#endif

        visitorReset();
        eRc = NodeTree_VisitPostorder(pObj, visitor, NULL);
        XCTAssertFalse( (ERESULT_FAILED(eRc)) );
        fprintf(stderr, "\nPostorder(%d):\n", count);
        XCTAssertTrue( (11 == count) );
        fprintf(stderr, "\ta b c / + d e f *2 - *1 (should be)\n\t");
        for (i=0; i<count; ++i) {
            pStrA = Node_getNameUTF8(NodeLink_getNode(pNodes[i]));
            fprintf(stderr, "%s ", pStrA);
            mem_Free((void *)pStrA);
            pStrA = NULL;
        }
        fprintf(stderr, " (actual)\n");
        eRc = Name_CompareA(Node_getName(NodeLink_getNode(pNodes[0])),"a");
        XCTAssertTrue( (0 == eRc) );
        eRc = Name_CompareA(Node_getName(NodeLink_getNode(pNodes[1])),"b");
        XCTAssertTrue( (0 == eRc) );
        eRc = Name_CompareA(Node_getName(NodeLink_getNode(pNodes[2])),"c");
        XCTAssertTrue( (0 == eRc) );
        eRc = Name_CompareA(Node_getName(NodeLink_getNode(pNodes[3])),"/");
        XCTAssertTrue( (0 == eRc) );
        eRc = Name_CompareA(Node_getName(NodeLink_getNode(pNodes[4])),"+");
        XCTAssertTrue( (0 == eRc) );
        eRc = Name_CompareA(Node_getName(NodeLink_getNode(pNodes[5])),"d");
        XCTAssertTrue( (0 == eRc) );
        eRc = Name_CompareA(Node_getName(NodeLink_getNode(pNodes[6])),"e");
        XCTAssertTrue( (0 == eRc) );
        eRc = Name_CompareA(Node_getName(NodeLink_getNode(pNodes[7])),"f");
        XCTAssertTrue( (0 == eRc) );
        eRc = Name_CompareA(Node_getName(NodeLink_getNode(pNodes[8])),"*2");
        XCTAssertTrue( (0 == eRc) );
        eRc = Name_CompareA(Node_getName(NodeLink_getNode(pNodes[9])),"-");
        XCTAssertTrue( (0 == eRc) );
        eRc = Name_CompareA(Node_getName(NodeLink_getNode(pNodes[10])),"*1");
        XCTAssertTrue( (0 == eRc) );

        visitorReset();
        eRc = NodeTree_VisitPreorder(pObj, visitor, NULL);
        XCTAssertFalse( (ERESULT_FAILED(eRc)) );
        fprintf(stderr, "\nPreorder(%d):\n", count);
        XCTAssertTrue( (11 == count) );
        fprintf(stderr, "\t*1 + a / b c - d *2 e f (should be)\n\t");
        for (i=0; i<count; ++i) {
            pStrA = Node_getNameUTF8(NodeLink_getNode(pNodes[i]));
            fprintf(stderr, "%s ", pStrA);
            mem_Free((void *)pStrA);
            pStrA = NULL;
        }
        fprintf(stderr, " (actual)\n\n");
        eRc = Name_CompareA(Node_getName(NodeLink_getNode(pNodes[0])),"*1");
        XCTAssertTrue( (0 == eRc) );
        eRc = Name_CompareA(Node_getName(NodeLink_getNode(pNodes[1])),"+");
        XCTAssertTrue( (0 == eRc) );
        eRc = Name_CompareA(Node_getName(NodeLink_getNode(pNodes[2])),"a");
        XCTAssertTrue( (0 == eRc) );
        eRc = Name_CompareA(Node_getName(NodeLink_getNode(pNodes[3])),"/");
        XCTAssertTrue( (0 == eRc) );
        eRc = Name_CompareA(Node_getName(NodeLink_getNode(pNodes[4])),"b");
        XCTAssertTrue( (0 == eRc) );
        eRc = Name_CompareA(Node_getName(NodeLink_getNode(pNodes[5])),"c");
        XCTAssertTrue( (0 == eRc) );
        eRc = Name_CompareA(Node_getName(NodeLink_getNode(pNodes[6])),"-");
        XCTAssertTrue( (0 == eRc) );
        eRc = Name_CompareA(Node_getName(NodeLink_getNode(pNodes[7])),"d");
        XCTAssertTrue( (0 == eRc) );
        eRc = Name_CompareA(Node_getName(NodeLink_getNode(pNodes[8])),"*2");
        XCTAssertTrue( (0 == eRc) );
        eRc = Name_CompareA(Node_getName(NodeLink_getNode(pNodes[9])),"e");
        XCTAssertTrue( (0 == eRc) );
        eRc = Name_CompareA(Node_getName(NodeLink_getNode(pNodes[10])),"f");
        XCTAssertTrue( (0 == eRc) );

#ifdef  XYZZY
        visitorReset();
        eRc = NodeTree_VisitBreadthFirst(pObj, visitor, NULL);
        XCTAssertFalse( (ERESULT_FAILED(eRc)) );
        XCTAssertTrue( (9 == count) );
        eRc = Name_CompareA(Node_getName(NodeLink_getNode(pNodes[0])),"A");
        XCTAssertTrue( (0 == eRc) );
        eRc = Name_CompareA(Node_getName(NodeLink_getNode(pNodes[1])),"B");
        XCTAssertTrue( (0 == eRc) );
        eRc = Name_CompareA(Node_getName(NodeLink_getNode(pNodes[2])),"E");
        XCTAssertTrue( (0 == eRc) );
        eRc = Name_CompareA(Node_getName(NodeLink_getNode(pNodes[3])),"I");
        XCTAssertTrue( (0 == eRc) );
        eRc = Name_CompareA(Node_getName(NodeLink_getNode(pNodes[4])),"C");
        XCTAssertTrue( (0 == eRc) );
        eRc = Name_CompareA(Node_getName(NodeLink_getNode(pNodes[5])),"D");
        XCTAssertTrue( (0 == eRc) );
        eRc = Name_CompareA(Node_getName(NodeLink_getNode(pNodes[6])),"F");
        XCTAssertTrue( (0 == eRc) );
        eRc = Name_CompareA(Node_getName(NodeLink_getNode(pNodes[7])),"H");
        XCTAssertTrue( (0 == eRc) );
        eRc = Name_CompareA(Node_getName(NodeLink_getNode(pNodes[8])),"G");
        XCTAssertTrue( (0 == eRc) );
#endif

#ifdef XYZZY
        pArray = NodeTree_ToLinearizationPost(pObj);
        XCTAssertFalse( (OBJ_NIL == pArray) );
        iMax = NodeArray_getSize(pArray);
        fprintf(stderr, "\nLinearization Postorder(%d):\n",iMax);
        XCTAssertTrue( (29 == iMax) );
        fprintf(stderr, "\tShould be: (DCGHFIEBA)\n");
        fprintf(stderr, "\tFound:     ");
        for (i=1; i<=iMax; ++i) {
            pStrA = Node_getNameUTF8(NodeLink_getNode(NodeArray_Get(pArray, i)));
            fprintf(stderr, "%s", pStrA);
            mem_Free((void *)pStrA);
        }
        fprintf(stderr, "\n");
        eRc = Name_CompareA(Node_getName(NodeLink_getNode(NodeArray_Get(pArray,  1))),"(");
        XCTAssertTrue( (0 == eRc) );
        eRc = Name_CompareA(Node_getName(NodeLink_getNode(NodeArray_Get(pArray,  2))),"A");
        XCTAssertTrue( (0 == eRc) );
        eRc = Name_CompareA(Node_getName(NodeLink_getNode(NodeArray_Get(pArray,  3))),"(");
        XCTAssertTrue( (0 == eRc) );
        eRc = Name_CompareA(Node_getName(NodeArray_Get(pArray,  4)),"B");
        XCTAssertTrue( (0 == eRc) );
        eRc = Name_CompareA(Node_getName(NodeArray_Get(pArray,  5)),"(");
        XCTAssertTrue( (0 == eRc) );
        eRc = Name_CompareA(Node_getName(NodeArray_Get(pArray,  6)),"C");
        XCTAssertTrue( (0 == eRc) );
        eRc = Name_CompareA(Node_getName(NodeArray_Get(pArray,  7)),"D");
        XCTAssertTrue( (0 == eRc) );
        eRc = Name_CompareA(Node_getName(NodeArray_Get(pArray,  8)),")");
        XCTAssertTrue( (0 == eRc) );
        eRc = Name_CompareA(Node_getName(NodeArray_Get(pArray,  9)),"E");
        XCTAssertTrue( (0 == eRc) );
        eRc = Name_CompareA(Node_getName(NodeArray_Get(pArray, 10)),"(");
        XCTAssertTrue( (0 == eRc) );
        eRc = Name_CompareA(Node_getName(NodeArray_Get(pArray, 11)),"F");
        XCTAssertTrue( (0 == eRc) );
        eRc = Name_CompareA(Node_getName(NodeArray_Get(pArray, 12)),"(");
        XCTAssertTrue( (0 == eRc) );
        eRc = Name_CompareA(Node_getName(NodeArray_Get(pArray, 13)),"G");
        XCTAssertTrue( (0 == eRc) );
        eRc = Name_CompareA(Node_getName(NodeArray_Get(pArray, 14)),")");
        XCTAssertTrue( (0 == eRc) );
        eRc = Name_CompareA(Node_getName(NodeArray_Get(pArray, 15)),"H");
        XCTAssertTrue( (0 == eRc) );
        eRc = Name_CompareA(Node_getName(NodeArray_Get(pArray, 16)),")");
        XCTAssertTrue( (0 == eRc) );
        eRc = Name_CompareA(Node_getName(NodeArray_Get(pArray, 17)),"I");
        XCTAssertTrue( (0 == eRc) );
        eRc = Name_CompareA(Node_getName(NodeArray_Get(pArray, 18)),")");
        XCTAssertTrue( (0 == eRc) );
        eRc = Name_CompareA(Node_getName(NodeArray_Get(pArray, 19)),")");
        XCTAssertTrue( (0 == eRc) );
        obj_Release(pArray);
        pArray = OBJ_NIL;
        fprintf(stderr, "\n\n\n");
#endif

        pArray = NodeTree_ToLinearizationPre(pObj);
        XCTAssertFalse( (OBJ_NIL == pArray) );
        iMax = ObjArray_getSize(pArray);
        fprintf(stderr, "\nLinearization Preorder(%d):\n",iMax);
        XCTAssertTrue( (23 == iMax) );
        fprintf(stderr, "\tShould be: ( *1 ( + ( a / ( b c ) ) - ( d *2 ( e f ) ) ) )\n");
        fprintf(stderr, "\tFound:     ");
        for (i=1; i<=iMax; ++i) {
            pStrA = NodeLink_getNameUTF8(ObjArray_Get(pArray, i));
            fprintf(stderr, "%s ", pStrA);
            mem_Free((void *)pStrA);
        }
        fprintf(stderr, "\n");
        eRc = Name_CompareA(NodeLink_getName(ObjArray_Get(pArray,  1)),"(");
        XCTAssertTrue( (0 == eRc) );
        eRc = Name_CompareA(NodeLink_getName(ObjArray_Get(pArray,  2)),"*1");
        XCTAssertTrue( (0 == eRc) );
        eRc = Name_CompareA(NodeLink_getName(ObjArray_Get(pArray,  3)),"(");
        XCTAssertTrue( (0 == eRc) );
        eRc = Name_CompareA(NodeLink_getName(ObjArray_Get(pArray,  4)),"+");
        XCTAssertTrue( (0 == eRc) );
        eRc = Name_CompareA(NodeLink_getName(ObjArray_Get(pArray,  5)),"(");
        XCTAssertTrue( (0 == eRc) );
        eRc = Name_CompareA(NodeLink_getName(ObjArray_Get(pArray,  6)),"a");
        XCTAssertTrue( (0 == eRc) );
        eRc = Name_CompareA(NodeLink_getName(ObjArray_Get(pArray,  7)),"/");
        XCTAssertTrue( (0 == eRc) );
        eRc = Name_CompareA(NodeLink_getName(ObjArray_Get(pArray,  8)),"(");
        XCTAssertTrue( (0 == eRc) );
        eRc = Name_CompareA(NodeLink_getName(ObjArray_Get(pArray,  9)),"b");
        XCTAssertTrue( (0 == eRc) );
        eRc = Name_CompareA(NodeLink_getName(ObjArray_Get(pArray, 10)),"c");
        XCTAssertTrue( (0 == eRc) );
        eRc = Name_CompareA(NodeLink_getName(ObjArray_Get(pArray, 11)),")");
        XCTAssertTrue( (0 == eRc) );
        eRc = Name_CompareA(NodeLink_getName(ObjArray_Get(pArray, 12)),")");
        XCTAssertTrue( (0 == eRc) );
        eRc = Name_CompareA(NodeLink_getName(ObjArray_Get(pArray, 13)),"-");
        XCTAssertTrue( (0 == eRc) );
        eRc = Name_CompareA(NodeLink_getName(ObjArray_Get(pArray, 14)),"(");
        XCTAssertTrue( (0 == eRc) );
        eRc = Name_CompareA(NodeLink_getName(ObjArray_Get(pArray, 15)),"d");
        XCTAssertTrue( (0 == eRc) );
        eRc = Name_CompareA(NodeLink_getName(ObjArray_Get(pArray, 16)),"*2");
        XCTAssertTrue( (0 == eRc) );
        eRc = Name_CompareA(NodeLink_getName(ObjArray_Get(pArray, 17)),"(");
        XCTAssertTrue( (0 == eRc) );
        eRc = Name_CompareA(NodeLink_getName(ObjArray_Get(pArray, 18)),"e");
        XCTAssertTrue( (0 == eRc) );
        eRc = Name_CompareA(NodeLink_getName(ObjArray_Get(pArray, 19)),"f");
        XCTAssertTrue( (0 == eRc) );
        eRc = Name_CompareA(NodeLink_getName(ObjArray_Get(pArray, 20)),")");
        XCTAssertTrue( (0 == eRc) );
        eRc = Name_CompareA(NodeLink_getName(ObjArray_Get(pArray, 21)),")");
        XCTAssertTrue( (0 == eRc) );
        eRc = Name_CompareA(NodeLink_getName(ObjArray_Get(pArray, 22)),")");
        XCTAssertTrue( (0 == eRc) );
        eRc = Name_CompareA(NodeLink_getName(ObjArray_Get(pArray, 23)),")");
        XCTAssertTrue( (0 == eRc) );
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




TINYTEST_START_SUITE(test_NodeTree);
    TINYTEST_ADD_TEST(test_NodeTree_UpDown02,setUp,tearDown);
    TINYTEST_ADD_TEST(test_NodeTree_NodeLinkChild,setUp,tearDown);
    TINYTEST_ADD_TEST(test_NodeTree_Node01,setUp,tearDown);
    TINYTEST_ADD_TEST(test_NodeTree_Move01,setUp,tearDown);
    TINYTEST_ADD_TEST(test_NodeTree_Delete01,setUp,tearDown);
    TINYTEST_ADD_TEST(test_NodeTree_UpDown01,setUp,tearDown);
    TINYTEST_ADD_TEST(test_NodeTree_Test01,setUp,tearDown);
    TINYTEST_ADD_TEST(test_NodeTree_OpenClose,setUp,tearDown);
TINYTEST_END_SUITE();

TINYTEST_MAIN_SINGLE_SUITE(test_NodeTree);





