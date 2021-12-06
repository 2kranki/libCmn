// vi:nu:et:sts=4 ts=4 sw=4
//****************************************************************
//                      Test Object Program
//****************************************************************
/*
 * Program
 *          Test Object Program
 * Purpose
 *          This program tests a particular object given certain
 *          parameters.
 *
 * Remarks
 *  1.      This relies on the fact that we can add to the Test
 *          Object by simply coding methods that use the Test
 *          Object.
 *
 * History
 *  08/29/2021 Generated
 */


/*
 This is free and unencumbered software released into the public domain.
 
 Anyone is free to copy, modify, publish, use, compile, sell, or
 distribute this software, either in source code form or as a compiled
 binary, for any purpose, commercial or non-commercial, and by any
 means.
 
 In jurisdictions that recognize copyright laws, the author or authors
 of this software dedicate any and all copyright interest in the
 software to the public domain. We make this dedication for the benefit
 of the public at large and to the detriment of our heirs and
 successors. We intend this dedication to be an overt act of
 relinquishment in perpetuity of all present and future rights to this
 software under copyright law.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
 IN NO EVENT SHALL THE AUTHORS BE LIABLE FOR ANY CLAIM, DAMAGES OR
 OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
 ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 OTHER DEALINGS IN THE SOFTWARE.
 
 For more information, please refer to <http://unlicense.org/>
 */




/*
 TestForFail(error_sttring)         <= Tests eRc for failure
 TestForFalse(test, error_sttring)
 TestForNotNull(test, error)
 TestForNull(test, error)
 TestForSuccess(error)              <= Tests eRc for success
 TestForTrue(test, error)
 */





#include    <test_defs.h>
#include    <Test_internal.h>
#include    <trace.h>
#include    <NodeTree_internal.h>
#include    <JsonIn.h>
#include    <SrcErrors.h>
#include    <szTbl.h>



static
uint32_t        count = 0;
static
NODE_DATA       *pNodes[64];



// Example from "Data Structures Using C", Taenenbaum et al, 1990,
// page 295(b).
static
NODETREE_DATA * createTestTree01(
    TEST_DATA       *this
)
{
    NODETREE_DATA   *pTree  = OBJ_NIL;
    NODE_DATA       *pNodeA = OBJ_NIL;
    NODE_DATA       *pNodeB = OBJ_NIL;
    NODE_DATA       *pNodeC = OBJ_NIL;
    NODE_DATA       *pNodeD = OBJ_NIL;
    NODE_DATA       *pNodeE = OBJ_NIL;
    NODE_DATA       *pNodeF = OBJ_NIL;
    NODE_DATA       *pNodeG = OBJ_NIL;
    NODE_DATA       *pNodeH = OBJ_NIL;
    NODE_DATA       *pNodeI = OBJ_NIL;
    NODE_DATA       *pNodeJ = OBJ_NIL;
    NODE_DATA       *pNodeK = OBJ_NIL;
    NODE_DATA       *pNodeL = OBJ_NIL;
    NODE_DATA       *pNodeM = OBJ_NIL;
    NODE_DATA       *pNodeN = OBJ_NIL;
    NODE_DATA       *pNodeO = OBJ_NIL;
    NODE_DATA       *pNodeP = OBJ_NIL;
    NODE_DATA       *pNodeQ = OBJ_NIL;
    NODE_DATA       *pNodeR = OBJ_NIL;
    uint32_t        i;
    ERESULT         eRc;
    //NODETREE_RECORD *pRcd   = NULL;

    pTree = NodeTree_New( );
    TestForNotNull(pTree, "");
    NodeTree_setUnique(pTree, true);

    pNodeA = Node_NewWithUTF8ConAndClass(0, "A", OBJ_NIL);
    TestForNotNull(pNodeA, "");
    pNodeB = Node_NewWithUTF8ConAndClass(0, "B", OBJ_NIL);
    TestForNotNull(pNodeB, "");
    pNodeC = Node_NewWithUTF8ConAndClass(0, "C", OBJ_NIL);
    TestForNotNull(pNodeC, "");
    pNodeD = Node_NewWithUTF8ConAndClass(0, "D", OBJ_NIL);
    TestForNotNull(pNodeD, "");
    pNodeE = Node_NewWithUTF8ConAndClass(0, "E", OBJ_NIL);
    TestForNotNull(pNodeE, "");
    pNodeF = Node_NewWithUTF8ConAndClass(0, "F", OBJ_NIL);
    TestForNotNull(pNodeF, "");
    pNodeG = Node_NewWithUTF8ConAndClass(0, "G", OBJ_NIL);
    TestForNotNull(pNodeG, "");
    pNodeH = Node_NewWithUTF8ConAndClass(0, "H", OBJ_NIL);
    TestForNotNull(pNodeH, "");
    pNodeI = Node_NewWithUTF8ConAndClass(0, "I", OBJ_NIL);
    TestForNotNull(pNodeI, "");
    pNodeJ = Node_NewWithUTF8ConAndClass(0, "J", OBJ_NIL);
    TestForNotNull(pNodeJ, "");
    pNodeK = Node_NewWithUTF8ConAndClass(0, "K", OBJ_NIL);
    TestForNotNull(pNodeK, "");
    pNodeL = Node_NewWithUTF8ConAndClass(0, "L", OBJ_NIL);
    TestForNotNull(pNodeL, "");
    pNodeM = Node_NewWithUTF8ConAndClass(0, "M", OBJ_NIL);
    TestForNotNull(pNodeM, "");
    pNodeN = Node_NewWithUTF8ConAndClass(0, "N", OBJ_NIL);
    TestForNotNull(pNodeN, "");
    pNodeO = Node_NewWithUTF8ConAndClass(0, "O", OBJ_NIL);
    TestForNotNull(pNodeO, "");
    pNodeP = Node_NewWithUTF8ConAndClass(0, "P", OBJ_NIL);
    TestForNotNull(pNodeP, "");
    pNodeQ = Node_NewWithUTF8ConAndClass(0, "Q", OBJ_NIL);
    TestForNotNull(pNodeQ, "");
    pNodeR = Node_NewWithUTF8ConAndClass(0, "R", OBJ_NIL);
    TestForNotNull(pNodeR, "");

    fprintf(stderr, "\n\nCreate the forest:\n");
    fprintf(stderr, "    A--------------G-------------L \n");
    fprintf(stderr, "    |              |             | \n");
    fprintf(stderr, "    |              |             | \n");
    fprintf(stderr, "    B---C          H             M---N---O\n");
    fprintf(stderr, "        |          |             |  \n");
    fprintf(stderr, "        D---E---F  I---J---K     P---Q  \n");
    fprintf(stderr, "                                 |  \n");
    fprintf(stderr, "                                 R  \n");
    fprintf(stderr, "\n");
    fprintf(stderr, " | == Child Link\n");
    fprintf(stderr, " - == Sibling Link\n");
    fprintf(stderr, "\n");
    fprintf(stderr, "Tree    Index   Child  Sibling  Parent  Level\n");
    fprintf(stderr, "                (Left) (Right)\n");
    fprintf(stderr, "A         1       4       2       0       0\n");
    fprintf(stderr, "B         4       0       7       1       1\n");
    fprintf(stderr, "C         7      10       0       1       1\n");
    fprintf(stderr, "D        10       0      11       7       0\n");
    fprintf(stderr, "E        11       0      12       7       1\n");
    fprintf(stderr, "F        12       0       0       7       2\n");
    fprintf(stderr, "G         2       5       3       0       2\n");
    fprintf(stderr, "H         5      13       0       2       2\n");
    fprintf(stderr, "I        13       0      14       5       1\n");
    fprintf(stderr, "J        14       0      15       5       1\n");
    fprintf(stderr, "K        15       0       0       5       1\n");
    fprintf(stderr, "L         3       6       0       0       1\n");
    fprintf(stderr, "M         6      16       8       3       1\n");
    fprintf(stderr, "N         8       0       9       3       1\n");
    fprintf(stderr, "O         9       0       0       3       1\n");
    fprintf(stderr, "P        16      17      18       6       1\n");
    fprintf(stderr, "Q        18       0       0      16       1\n");
    fprintf(stderr, "R        17       0       0       6       1\n");
    fprintf(stderr, "\n");
    fprintf(stderr, "Preorder Traversal:  ABCDEFGHIJKLMPRQNO\n");
    fprintf(stderr, "Postorder Traversal: BDEFCAIJKHGRPQMNOL\n");
    fprintf(stderr, "Breadth First Traversal: AGLBCHMNODEFIJKPQR\n");
    fprintf(stderr, "\n\n\n");

    //                                 1
    i = NodeTree_ChildAdd(pTree, 0, pNodeA);
    TestForTrue((1 == i), "");
    //                                                          2       3
    eRc = NodeTree_SiblingsAdd(pTree, Node_getUnique(pNodeA), pNodeG, pNodeL, OBJ_NIL);
    TestForSuccess("");
    TestForTrue((2 == Node_getUnique(pNodeG)), "");
    TestForTrue((3 == Node_getUnique(pNodeL)), "");
    //                                                      4
    i = NodeTree_ChildAdd(pTree, Node_getUnique(pNodeA), pNodeB);
    TestForTrue((4 == i), "");
    //                                                      5
    i = NodeTree_ChildAdd(pTree, Node_getUnique(pNodeG), pNodeH);
    TestForTrue((5 == i), "");
    //                                                      6
    i = NodeTree_ChildAdd(pTree, Node_getUnique(pNodeL), pNodeM);
    TestForTrue((6 == i), "");
    //                                                      7
    i = NodeTree_SiblingAdd(pTree,Node_getUnique(pNodeB), pNodeC);
    TestForTrue((7 == i), "");
    //                                                         8       9
    eRc = NodeTree_SiblingsAdd(pTree,Node_getUnique(pNodeM), pNodeN, pNodeO, OBJ_NIL);
    TestForSuccess("");
    TestForTrue((8 == Node_getUnique(pNodeN)), "");
    TestForTrue((9 == Node_getUnique(pNodeO)), "");
    //                                                    10
    i = NodeTree_ChildAdd(pTree,Node_getUnique(pNodeC), pNodeD);
    TestForTrue((10 == i), "");
    //                                                         11      12
    eRc = NodeTree_SiblingsAdd(pTree,Node_getUnique(pNodeD), pNodeE, pNodeF, OBJ_NIL);
    TestForSuccess("");
    TestForTrue((11 == Node_getUnique(pNodeE)), "");
    TestForTrue((12 == Node_getUnique(pNodeF)), "");
    //                                                    13
    i = NodeTree_ChildAdd(pTree,Node_getUnique(pNodeH), pNodeI);
    TestForTrue((13 == i), "");
    //                                                         14      15
    eRc = NodeTree_SiblingsAdd(pTree,Node_getUnique(pNodeI), pNodeJ, pNodeK, OBJ_NIL);
    TestForSuccess("");
    TestForTrue((14 == Node_getUnique(pNodeJ)), "");
    TestForTrue((15 == Node_getUnique(pNodeK)), "");
    //                                                     16
    i = NodeTree_ChildAdd(pTree, Node_getUnique(pNodeM), pNodeP);
    TestForTrue((16 == i), "");
    //                                                     17
    i = NodeTree_ChildAdd(pTree, Node_getUnique(pNodeP), pNodeR);
    TestForTrue((17 == i), "");
    //                                                      18
    i = NodeTree_SiblingAdd(pTree,Node_getUnique(pNodeP), pNodeQ);
    TestForTrue((18 == i), "");

    {
        ASTR_DATA       *pStr = NodeTree_ToDebugString(pTree, 4);
        if (pStr) {
            fprintf(stderr, "Debug: %s\n", AStr_getData(pStr));
            obj_Release(pStr);
            pStr = OBJ_NIL;
        }
    }

    obj_Release(pNodeR);
    pNodeR = OBJ_NIL;
    obj_Release(pNodeQ);
    pNodeQ = OBJ_NIL;
    obj_Release(pNodeP);
    pNodeP = OBJ_NIL;
    obj_Release(pNodeO);
    pNodeO = OBJ_NIL;
    obj_Release(pNodeN);
    pNodeN = OBJ_NIL;
    obj_Release(pNodeM);
    pNodeM = OBJ_NIL;
    obj_Release(pNodeL);
    pNodeL = OBJ_NIL;
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




// Example from Knuth's "The Art of Computer Programming - Volume 1 (3rd Ed.)",
// page 335 which consists of a forest (two trees) that have sibling roots.
static
NODETREE_DATA * createTestTree02(
    TEST_DATA       *this
)
{
    NODETREE_DATA   *pTree  = OBJ_NIL;
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
    NODETREE_RECORD *pRcd   = NULL;

    pTree = NodeTree_New( );
    TestForNotNull(pTree, "");
    NodeTree_setUnique(pTree, true);

    pNodeA = Node_NewWithUTF8ConAndClass(0, "A", OBJ_NIL);
    TestForNotNull(pNodeA, "");
    pNodeB = Node_NewWithUTF8ConAndClass(0, "B", OBJ_NIL);
    TestForNotNull(pNodeB, "");
    pNodeC = Node_NewWithUTF8ConAndClass(0, "C", OBJ_NIL);
    TestForNotNull(pNodeC, "");
    pNodeD = Node_NewWithUTF8ConAndClass(0, "D", OBJ_NIL);
    TestForNotNull(pNodeD, "");
    pNodeE = Node_NewWithUTF8ConAndClass(0, "E", OBJ_NIL);
    TestForNotNull(pNodeE, "");
    pNodeF = Node_NewWithUTF8ConAndClass(0, "F", OBJ_NIL);
    TestForNotNull(pNodeF, "");
    pNodeG = Node_NewWithUTF8ConAndClass(0, "G", OBJ_NIL);
    TestForNotNull(pNodeG, "");
    pNodeH = Node_NewWithUTF8ConAndClass(0, "H", OBJ_NIL);
    TestForNotNull(pNodeH, "");
    pNodeJ = Node_NewWithUTF8ConAndClass(0, "J", OBJ_NIL);
    TestForNotNull(pNodeJ, "");
    pNodeK = Node_NewWithUTF8ConAndClass(0, "K", OBJ_NIL);
    TestForNotNull(pNodeK, "");

    fprintf(stderr, "\n\nCreate the forest:\n");
    fprintf(stderr, "     A----------------D \n");
    fprintf(stderr, "     |                | \n");
    fprintf(stderr, "     |                | \n");
    fprintf(stderr, "     B-----C          E------F-----G \n");
    fprintf(stderr, "           |          |      | \n");
    fprintf(stderr, "           |          |      | \n");
    fprintf(stderr, "           K          H      J \n");
    fprintf(stderr, "\n");
    fprintf(stderr, " | == Child Link\n");
    fprintf(stderr, " - == Sibling Link\n");
    fprintf(stderr, "\n");
    fprintf(stderr, "Tree    Index   Child  Sibling  Parent  Level\n");
    fprintf(stderr, "                (Left) (Right)\n");
    fprintf(stderr, "A         1       3       2       0       0\n");
    fprintf(stderr, "--B       3       0       4       1       1\n");
    fprintf(stderr, "--C       4       5       0       1       1\n");
    fprintf(stderr, "----K     5       0       0       4       2\n");
    fprintf(stderr, "D         2       6       0       0       0\n");
    fprintf(stderr, "--E       6       9       7       2       1\n");
    fprintf(stderr, "----H     9       0       0       6       2\n");
    fprintf(stderr, "--F       7      10       8       2       1\n");
    fprintf(stderr, "----J    10       0       0       7       2\n");
    fprintf(stderr, "--G       8       0       0       2       1\n");
    fprintf(stderr, "\n");
    fprintf(stderr, "Preorder Traversal:  (A(B,C(K),D(E(H),F(J),G))\n");
    fprintf(stderr, "Postorder Traversal: ((B, (K)C)A, ((H)E, (J)F,G)D),\n");
    fprintf(stderr, "Breadth First Traversal: ((A,D)(B,C,E,F,G)(K,H,J))\n");
    fprintf(stderr, "\n\n\n");

    i = NodeTree_ChildAdd(pTree, 0, pNodeA);
    TestForTrue((1 == i), "");
    i = NodeTree_SiblingAdd(pTree, Node_getUnique(pNodeA), pNodeD);
    TestForTrue((2 == i), "");

    //                                                         3      4
    eRc = NodeTree_ChildrenAdd(pTree,Node_getUnique(pNodeA), pNodeB, pNodeC, OBJ_NIL);
    TestForSuccess("");
    //                                                        5
    eRc = NodeTree_ChildrenAdd(pTree,Node_getUnique(pNodeC), pNodeK, OBJ_NIL);
    TestForSuccess("");
    //                                                         6      7       8
    eRc = NodeTree_ChildrenAdd(pTree,Node_getUnique(pNodeD), pNodeE, pNodeF, pNodeG, OBJ_NIL);
    TestForSuccess("");
    //                                                         9
    eRc = NodeTree_ChildrenAdd(pTree,Node_getUnique(pNodeE), pNodeH, OBJ_NIL);
    TestForSuccess("");
    //                                                        10
    eRc = NodeTree_ChildrenAdd(pTree,Node_getUnique(pNodeF), pNodeJ, OBJ_NIL);
    TestForSuccess("");

    // Check the forest structure.
    i = pTree->root;
    TestForTrue((1 == i), "");
    pRcd = Blocks_RecordGetUnique((BLOCKS_DATA *)pTree, i);
    TestForTrue((pRcd->unique == i), "");
    TestForTrue((pRcd->childIndex == 3), "");
    TestForTrue((pRcd->siblingIndex == 2), "");
    TestForTrue((pRcd->parentIndex == 0), "");
    i = 2;
    pRcd = Blocks_RecordGetUnique((BLOCKS_DATA *)pTree, i);
    TestForTrue((pRcd->unique == i), "");
    TestForTrue((pRcd->childIndex == 6), "");
    TestForTrue((pRcd->siblingIndex == 0), "");
    TestForTrue((pRcd->parentIndex == 0), "");
    i = 3;
    pRcd = Blocks_RecordGetUnique((BLOCKS_DATA *)pTree, i);
    TestForTrue((pRcd->unique == i), "");
    TestForTrue((pRcd->childIndex == 0), "");
    TestForTrue((pRcd->siblingIndex == 4), "");
    TestForTrue((pRcd->parentIndex == 1), "");
    i = 4;
    pRcd = Blocks_RecordGetUnique((BLOCKS_DATA *)pTree, i);
    TestForTrue((pRcd->unique == i), "");
    TestForTrue((pRcd->childIndex == 5), "");
    TestForTrue((pRcd->siblingIndex == 0), "");
    TestForTrue((pRcd->parentIndex == 1), "");
    i = 5;
    pRcd = Blocks_RecordGetUnique((BLOCKS_DATA *)pTree, i);
    TestForTrue((pRcd->unique == i), "");
    TestForTrue((pRcd->childIndex == 0), "");
    TestForTrue((pRcd->siblingIndex == 0), "");
    TestForTrue((pRcd->parentIndex == 4), "");
    i = 6;
    pRcd = Blocks_RecordGetUnique((BLOCKS_DATA *)pTree, i);
    TestForTrue((pRcd->unique == i), "");
    TestForTrue((pRcd->childIndex == 9), "");
    TestForTrue((pRcd->siblingIndex == 7), "");
    TestForTrue((pRcd->parentIndex == 2), "");
    i = 7;
    pRcd = Blocks_RecordGetUnique((BLOCKS_DATA *)pTree, i);
    TestForTrue((pRcd->unique == i), "");
    TestForTrue((pRcd->childIndex == 10), "");
    TestForTrue((pRcd->siblingIndex == 8), "");
    TestForTrue((pRcd->parentIndex == 2), "");
    i = 8;
    pRcd = Blocks_RecordGetUnique((BLOCKS_DATA *)pTree, i);
    TestForTrue((pRcd->unique == i), "");
    TestForTrue((pRcd->childIndex == 0), "");
    TestForTrue((pRcd->siblingIndex == 0), "");
    TestForTrue((pRcd->parentIndex == 2), "");
    i = 9;
    pRcd = Blocks_RecordGetUnique((BLOCKS_DATA *)pTree, i);
    TestForTrue((pRcd->unique == i), "");
    TestForTrue((pRcd->childIndex == 0), "");
    TestForTrue((pRcd->siblingIndex == 0), "");
    TestForTrue((pRcd->parentIndex == 6), "");
    i = 10;
    pRcd = Blocks_RecordGetUnique((BLOCKS_DATA *)pTree, i);
    TestForTrue((pRcd->unique == i), "");
    TestForTrue((pRcd->childIndex == 0), "");
    TestForTrue((pRcd->siblingIndex == 0), "");
    TestForTrue((pRcd->parentIndex == 7), "");

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
NODETREE_DATA * createTestTree03(
    TEST_DATA       *this
)
{
    NODETREE_DATA   *pTree = OBJ_NIL;
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
    //NODETREE_RECORD *pRcd = NULL;

    pTree = NodeTree_Alloc( );
    if  (OBJ_NIL == pTree) {
        return pTree;
    }
    pTree = NodeTree_Init( pTree );
    if  (OBJ_NIL == pTree) {
        return pTree;
    }
    NodeTree_setUnique(pTree, true);

    pNodeA = Node_NewWithUTF8ConAndClass(0, "a", OBJ_NIL);
    if  (OBJ_NIL == pNodeA) {
        obj_Release(pTree);
        pTree = OBJ_NIL;
        return pTree;
    }
    pNodeB = Node_NewWithUTF8ConAndClass(0, "b", OBJ_NIL);
    if  (OBJ_NIL == pNodeB) {
        obj_Release(pTree);
        pTree = OBJ_NIL;
        return pTree;
    }
    pNodeC = Node_NewWithUTF8ConAndClass(0, "c", OBJ_NIL);
    if  (OBJ_NIL == pNodeC) {
        obj_Release(pTree);
        pTree = OBJ_NIL;
        return pTree;
    }
    pNodeD = Node_NewWithUTF8ConAndClass(0, "d", OBJ_NIL);
    if  (OBJ_NIL == pNodeD) {
        obj_Release(pTree);
        pTree = OBJ_NIL;
        return pTree;
    }
    pNodeE = Node_NewWithUTF8ConAndClass(0, "e", OBJ_NIL);
    if  (OBJ_NIL == pNodeE) {
        obj_Release(pTree);
        pTree = OBJ_NIL;
        return pTree;
    }
    pNodeF = Node_NewWithUTF8ConAndClass(0, "f", OBJ_NIL);
    if  (OBJ_NIL == pNodeF) {
        obj_Release(pTree);
        pTree = OBJ_NIL;
        return pTree;
    }
    pNodeG = Node_NewWithUTF8ConAndClass(0, "*1", OBJ_NIL);
    if  (OBJ_NIL == pNodeG) {
        obj_Release(pTree);
        pTree = OBJ_NIL;
        return pTree;
    }
    pNodeH = Node_NewWithUTF8ConAndClass(0, "+", OBJ_NIL);
    if  (OBJ_NIL == pNodeH) {
        obj_Release(pTree);
        pTree = OBJ_NIL;
        return pTree;
    }
    pNodeI = Node_NewWithUTF8ConAndClass(0, "/", OBJ_NIL);
    if  (OBJ_NIL == pNodeI) {
        obj_Release(pTree);
        pTree = OBJ_NIL;
        return pTree;
    }

    pNodeJ = Node_NewWithUTF8ConAndClass(0, "-", OBJ_NIL);
    if  (OBJ_NIL == pNodeI) {
        obj_Release(pTree);
        pTree = OBJ_NIL;
        return pTree;
    }

    pNodeK = Node_NewWithUTF8ConAndClass(0, "*2", OBJ_NIL);
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
    fprintf(stderr, "------'e'    E   10      11       0       9\n");
    fprintf(stderr, "------'f'    F   11       0       0       9\n");
    fprintf(stderr, "\n");
    fprintf(stderr, "Preorder Traversal:  *1 + a / b c - d *2 e f\n");
    fprintf(stderr, "Inorder Traversal:   a + b / c *1 d - e *2 f\n");
    fprintf(stderr, "Postorder Traversal: a b c / + d e f *2 - *1\n");
    fprintf(stderr, "Breadth First Traversal: ((*1), (+,-), (a,/,d,*2), (b,c,e,f)\n");
    fprintf(stderr, "\n\n\n");

    //                                 1
    i = NodeTree_ChildAdd(pTree, 0, pNodeG);
    TestForTrue((1 == i), "");
    //                                                         2       3
    eRc = NodeTree_ChildrenAdd(pTree,Node_getUnique(pNodeG), pNodeH, pNodeJ, OBJ_NIL);
    TestForSuccess("");
    //                                                         4       5
    eRc = NodeTree_ChildrenAdd(pTree,Node_getUnique(pNodeH), pNodeA, pNodeI, OBJ_NIL);
    TestForSuccess("");
    //                                                         6       7
    eRc = NodeTree_ChildrenAdd(pTree,Node_getUnique(pNodeI), pNodeB, pNodeC, OBJ_NIL);
    TestForSuccess("");
    //                                                         8       9
    eRc = NodeTree_ChildrenAdd(pTree,Node_getUnique(pNodeJ), pNodeD, pNodeK, OBJ_NIL);
    TestForSuccess("");
    //                                                        10      11
    eRc = NodeTree_ChildrenAdd(pTree,Node_getUnique(pNodeK), pNodeE, pNodeF, OBJ_NIL);
    TestForSuccess("");

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
    uint16_t        indent,
    void            *pOther
)
{
    pNodes[count] = pNode;
    count++;
}


static
void            visitorPrint(
    OBJ_ID          pObject,            // Object supplied below
    NODETREE_DATA   *pTree,             // Our Tree
    NODE_DATA       *pNode,             // Current Node
    uint16_t        indent,
    void            *pOther
)
{
    const
    char            *pStrA;
    fprintf(stderr, "%3d ", indent);
    pStrA = Node_getNameUTF8(pNode);
    fprintf(stderr, "%s\n", pStrA);
    mem_Free((void *)pStrA);
    pStrA = NULL;
    pNodes[count] = pNode;
    count++;
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







ERESULT         Test_NodeTree_OpenClose (
    TEST_DATA       *this,
    const
    char            *pTestName
)
{
    ERESULT         eRc = ERESULT_SUCCESS;
    NODETREE_DATA   *pObj = OBJ_NIL;
    bool            fRc;
   
    fprintf(stderr, "Performing: %s\n", pTestName);

    pObj = NodeTree_Alloc( );
    TestForNotNull(pObj, "Missing Test Alloc() object");
    pObj = NodeTree_Init( pObj );
    TestForNotNull(pObj, "Missing Test Init() object");
    if (pObj) {

        //obj_TraceSet(pObj, true);       
        fRc = obj_IsKindOf(pObj, OBJ_IDENT_NODETREE);
        TestForTrue(fRc, "Failed Ident Test");
#ifdef   NODETREE_MSGS
        NodeTree_setMsg(pObj, (void *)Test_MsgInfo, (void *)Test_MsgWarn, this);
#endif
        
        // Test something.
        TestForSuccess("test failed");

        obj_Release(pObj);
        pObj = OBJ_NIL;
    }

    fprintf(stderr, "...%s completed.\n\n\n", pTestName);
    return eRc;
}



ERESULT         Test_NodeTree_Copy01 (
    TEST_DATA       *this,
    const
    char            *pTestName
)
{
    ERESULT         eRc = ERESULT_SUCCESS;
    NODETREE_DATA       *pObj1 = OBJ_NIL;
    NODETREE_DATA       *pObj2 = OBJ_NIL;
    bool            fRc;
#if defined(NODETREE_JSON_SUPPORT) && defined(XYZZY)
    ASTR_DATA       *pStr = OBJ_NIL;
#endif
    //int             iRc;
   
    fprintf(stderr, "Performing: %s\n", pTestName);

    pObj1 = NodeTree_New( );
    TestForNotNull(pObj1, "Missing Test object");
    if (pObj1) {

        //obj_TraceSet(pObj1, true);       
        fRc = obj_IsKindOf(pObj1, OBJ_IDENT_NODETREE);
        TestForTrue(fRc, "Failed Ident Test");
#ifdef   NODETREE_MSGS
        NodeTree_setMsg(pObj1, (void *)Test_MsgInfo, (void *)Test_MsgWarn, this);
#endif
        
        // Test assign.
        pObj2 = NodeTree_New();
        TestForNotNull(pObj2, "Missing copied object");
        eRc = NodeTree_Assign(pObj1, pObj2);
        TestForFalse((ERESULT_FAILED(eRc)), "Assignment failed");

        fRc = obj_IsKindOf(pObj2, OBJ_IDENT_NODETREE);
        TestForTrue(fRc, "Failed Ident Test");
        //iRc = NodeTree_Compare(pObj1, pObj2);
        //TestForTrue((0 == iRc), "Failed Compare");
        //TODO: Add More tests here!

        obj_Release(pObj2);
        pObj2 = OBJ_NIL;

        // Test copy.
        pObj2 = NodeTree_Copy(pObj1);
        TestForNotNull(pObj2, "Missing copied object");

        fRc = obj_IsKindOf(pObj2, OBJ_IDENT_NODETREE);
        TestForTrue(fRc, "Failed Ident Test");
        //iRc = NodeTree_Compare(pObj1, pObj2);
        //TestForTrue((0 == iRc), "Failed Compare");
        //TODO: Add More tests here!

        obj_Release(pObj2);
        pObj2 = OBJ_NIL;

        // Test json support.
#if defined(NODETREE_JSON_SUPPORT) && defined(XYZZY)
        pStr = NodeTree_ToJson(pObj1);
        TestForNotNull(pStr, "Missing JSON output");
        fprintf(stderr, "JSON: %s\n", AStr_getData(pStr));
        pObj2 = NodeTree_NewFromJsonString(pStr);
        TestForNotNull(pObj2, "Missing JSON created object");
        fRc = obj_IsKindOf(pObj2, OBJ_IDENT_NODETREE);
        TestForTrue(fRc, "Failed Ident Test");
        obj_Release(pStr);
        pStr = OBJ_NIL;
        //iRc = NodeTree_Compare(pObj1, pObj2);
        //TestForTrue((0 == iRc), "Failed Compare");

        obj_Release(pObj2);
        pObj2 = OBJ_NIL;
#endif

        obj_Release(pObj1);
        pObj1 = OBJ_NIL;
    }

    fprintf(stderr, "...%s completed.\n\n\n", pTestName);
    return eRc;
}



ERESULT         Test_NodeTree_Test01 (
    TEST_DATA       *this,
    const
    char            *pTestName
)
{
    ERESULT         eRc = ERESULT_SUCCESS;
    NODETREE_DATA   *pObj = OBJ_NIL;
    bool            fRc;
   
    fprintf(stderr, "Performing: %s\n", pTestName);

    pObj = NodeTree_New( );
    TestForNotNull(pObj, "Missing Test object");
    if (pObj) {

        //obj_TraceSet(pObj, true);       
        fRc = obj_IsKindOf(pObj, OBJ_IDENT_NODETREE);
        TestForTrue(fRc, "Failed Ident Test");
        TestForSuccess("");
#ifdef   NODETREE_LOG
        NodeTree_setLog(pObj, this);
#endif
        NodeTree_setUnique(pObj, true);
                
        {
            ASTR_DATA       *pStr = NodeTree_ToDebugString(pObj, 4);
            if (pStr) {
                fprintf(stderr, "Debug: %s\n", AStr_getData(pStr));
                obj_Release(pStr);
                pStr = OBJ_NIL;
            }
        }

        obj_Release(pObj);
        pObj = OBJ_NIL;
    }

    fprintf(stderr, "...%s completed.\n\n\n", pTestName);
    return eRc;
}



ERESULT         Test_NodeTree_Test02 (
    TEST_DATA       *this,
    const
    char            *pTestName
)
{
    ERESULT         eRc = ERESULT_SUCCESS;
    NODETREE_DATA   *pObj = OBJ_NIL;
    bool            fRc;
    uint32_t        i;
    //uint32_t        iMax;
    //NODETREE_RECORD *pRcd;
    const
    char            *pBreadthA = "AGLBCHMNODEFIJKPQR";
    const
    char            *pPreA = "ABCDEFGHIJKLMPRQNO";
    const
    char            *pPostA = "BDEFCAIJKHGRPQMNOL";
    const
    char            *pChrA;

    fprintf(stderr, "Performing: %s\n", pTestName);

    pObj = createTestTree01(this);
    TestForNotNull(pObj, "Missing Test object");
    if (pObj) {

        //obj_TraceSet(pObj, true);
        fRc = obj_IsKindOf(pObj, OBJ_IDENT_NODETREE);
        TestForTrue(fRc, "Failed Ident Test");
        TestForSuccess("");
#ifdef   NODETREE_LOG
        NodeTree_setLog(pObj, this);
#endif

        fprintf(stderr, "PostOrder Traversal: BDEFCAIJKHGRPQMNOL\n");
        eRc = NodeTree_VisitPostOrder(pObj, (void *)visitorPrint, NULL, NULL);
        TestForSuccess("");
        fprintf(stderr, "\nPostOrder Traversal: complete\n\n");
        TestForTrue((count == 18), "");
        pChrA = pPostA;
        for (i=0; i<count; i++) {
            const
            char    *pNameA = Node_getNameUTF8(pNodes[i]);
            TestForTrue((*pChrA == *pNameA), "");
            mem_Free((void *)pNameA);
            pChrA++;
        }
        visitorReset();

        fprintf(stderr, "Preorder Traversal:  ABCDEFGHIJKLMPRQNO\n");
        eRc = NodeTree_VisitPreOrder(pObj, (void *)visitorPrint, NULL, NULL);
        TestForSuccess("");
        fprintf(stderr, "\nPreOrder Traversal: complete\n\n");
        TestForTrue((count == 18), "");
        pChrA = pPreA;
        for (i=0; i<count; i++) {
            const
            char    *pNameA = Node_getNameUTF8(pNodes[i]);
            TestForTrue((*pChrA == *pNameA), "");
            mem_Free((void *)pNameA);
            pChrA++;
        }
        visitorReset();

        fprintf(stderr, "Breadth First Traversal: AGLBCHMNODEFIJKPQR\n");
        eRc = NodeTree_VisitBreadthFirst(pObj, (void *)visitorPrint, NULL, NULL);
        TestForSuccess("");
        fprintf(stderr, "\nBreadth First Traversal: complete\n\n");
        TestForTrue((count == 18), "");
        pChrA = pBreadthA;
        for (i=0; i<count; i++) {
            const
            char    *pNameA = Node_getNameUTF8(pNodes[i]);
            TestForTrue((*pChrA == *pNameA), "");
            mem_Free((void *)pNameA);
            pChrA++;
        }
        visitorReset();

        {
            ASTR_DATA       *pStr = NodeTree_ToDebugString(pObj, 4);
            if (pStr) {
                fprintf(stderr, "Debug: %s\n", AStr_getData(pStr));
                obj_Release(pStr);
                pStr = OBJ_NIL;
            }
        }

        obj_Release(pObj);
        pObj = OBJ_NIL;
    }

    fprintf(stderr, "...%s completed.\n\n\n", pTestName);
    return eRc;
}



ERESULT         Test_NodeTree_Test03 (
    TEST_DATA       *this,
    const
    char            *pTestName
)
{
    ERESULT         eRc = ERESULT_SUCCESS;
    NODETREE_DATA   *pObj = OBJ_NIL;
    bool            fRc;
    uint32_t        i;
    uint32_t        iMax;
    const
    char            *pBreadthA = "ADBCEFGKHJ";
    const
    char            *pPreA = "ABCKDEHFJG";
    const
    char            *pPostA = "BKCAHEJFGD";
    const
    char            *pLinearPostA = "((B(K)C)A((H)E(J)FG)D)";
    const
    char            *pLinearPreA = "(A(BC(K))D(E(H)F(J)G))";
    const
    char            *pChrA;
    const
    char            *pStrA;
    NODEARRAY_DATA  *pArray = OBJ_NIL;

    fprintf(stderr, "Performing: %s\n", pTestName);

    pObj = createTestTree02(this);
    TestForNotNull(pObj, "Missing Test object");
    if (pObj) {

        //obj_TraceSet(pObj, true);
        fRc = obj_IsKindOf(pObj, OBJ_IDENT_NODETREE);
        TestForTrue(fRc, "Failed Ident Test");
        TestForSuccess("");
#ifdef   NODETREE_LOG
        NodeTree_setLog(pObj, this);
#endif

        i = NodeTree_SiblingCount(pObj, 1);
        TestForTrue((i == 1), "");
        i = NodeTree_ChildCount(pObj, 1);
        TestForTrue((i == 2), "");
        i = NodeTree_ChildCount(pObj, 2);
        TestForTrue((i == 3), "");
        i = NodeTree_ChildCount(pObj, 3);
        TestForTrue((i == 0), "");
        i = NodeTree_ChildCount(pObj, 4);
        TestForTrue((i == 1), "");
        i = NodeTree_ChildCount(pObj, 5);
        TestForTrue((i == 0), "");
        i = NodeTree_ChildCount(pObj, 6);
        TestForTrue((i == 1), "");
        i = NodeTree_ChildCount(pObj, 7);
        TestForTrue((i == 1), "");
        i = NodeTree_ChildCount(pObj, 8);
        TestForTrue((i == 0), "");
        i = NodeTree_ChildCount(pObj, 9);
        TestForTrue((i == 0), "");
        i = NodeTree_ChildCount(pObj, 10);
        TestForTrue((i == 0), "");

        fprintf(stderr, "Postorder Traversal: ((B, (K)C)A, ((H)E, (J)F, G)D)\n");
        eRc = NodeTree_VisitPostOrder(pObj, (void *)visitorPrint, NULL, NULL);
        TestForSuccess("");
        fprintf(stderr, "\nPostOrder Traversal: complete\n\n");
        TestForTrue((count == 10), "");
        pChrA = pPostA;
        for (i=0; i<count; i++) {
            const
            char    *pNameA = Node_getNameUTF8(pNodes[i]);
            TestForTrue((*pChrA == *pNameA), "");
            mem_Free((void *)pNameA);
            pChrA++;
        }
        visitorReset();

        fprintf(stderr, "Preorder Traversal:  (A(B,C(K),D(E(H),F(J),G))\n");
        eRc = NodeTree_VisitPreOrder(pObj, (void *)visitorPrint, NULL, NULL);
        TestForSuccess("");
        fprintf(stderr, "\nPreOrder Traversal: complete\n\n");
        TestForTrue((count == 10), "");
        pChrA = pPreA;
        for (i=0; i<count; i++) {
            const
            char    *pNameA = Node_getNameUTF8(pNodes[i]);
            TestForTrue((*pChrA == *pNameA), "");
            mem_Free((void *)pNameA);
            pChrA++;
        }
        visitorReset();

        fprintf(stderr, "Breadth First Traversal: ((A,D)(B,C,E,F,G)(K,H,J))\n");
        eRc = NodeTree_VisitBreadthFirst(pObj, (void *)visitorPrint, NULL, NULL);
        TestForSuccess("");
        fprintf(stderr, "\nBreadth First Traversal: complete\n\n");
        TestForTrue((count == 10), "");
        pChrA = pBreadthA;
        for (i=0; i<count; i++) {
            const
            char    *pNameA = Node_getNameUTF8(pNodes[i]);
            TestForTrue((*pChrA == *pNameA), "");
            mem_Free((void *)pNameA);
            pChrA++;
        }
        visitorReset();

        pArray = NodeTree_ToLinearizationPost(pObj);
        TestForNotNull(pArray, "");
        iMax = NodeArray_getSize(pArray);
        fprintf(stderr, "\nLinearization Postorder(%d):\n", iMax);
        TestForTrue((iMax == 22), "");
        fprintf(stderr, "\tShould be: ((B(K)C)A((H)E(J)FG)D)\n");
        fprintf(stderr, "\tFound:     ");
        pChrA = pLinearPostA;
        for (i=1; i<=iMax; ++i) {
            pStrA = Node_getNameUTF8(NodeArray_Get(pArray, i));
            fprintf(stderr, "%s", pStrA);
            TestForTrue((*pChrA == *pStrA), "");
            mem_Free((void *)pStrA);
            pChrA++;
        }
        fprintf(stderr, "\n");
        obj_Release(pArray);
        pArray = OBJ_NIL;
        fprintf(stderr, "\n\n\n");

        pArray = NodeTree_ToLinearizationPre(pObj);
        TestForNotNull(pArray, "");
        iMax = NodeArray_getSize(pArray);
        fprintf(stderr, "\nLinearization Preorder(%d):\n",iMax);
        TestForTrue((iMax == 22), "");
        fprintf(stderr, "\tShould be: (A(BC(K))D(E(H)F(J)G))\n");
        fprintf(stderr, "\tFound:     ");
        pChrA = pLinearPreA;
        for (i=1; i<=iMax; ++i) {
            pStrA = Node_getNameUTF8(NodeArray_Get(pArray, i));
            fprintf(stderr, "%s", pStrA);
            TestForTrue((*pChrA == *pStrA), "");
            mem_Free((void *)pStrA);
            pChrA++;
        }
        fprintf(stderr, "\n");
        obj_Release(pArray);
        pArray = OBJ_NIL;
        fprintf(stderr, "\n\n\n");

        {
            ASTR_DATA       *pStr = NodeTree_ToDebugString(pObj, 4);
            if (pStr) {
                fprintf(stderr, "Debug: %s\n", AStr_getData(pStr));
                obj_Release(pStr);
                pStr = OBJ_NIL;
            }
        }

        obj_Release(pObj);
        pObj = OBJ_NIL;
    }

    fprintf(stderr, "...%s completed.\n\n\n", pTestName);
    return eRc;
}



ERESULT         Test_NodeTree_Test04 (
    TEST_DATA       *this,
    const
    char            *pTestName
)
{
    ERESULT         eRc = ERESULT_SUCCESS;
    NODETREE_DATA   *pObj = OBJ_NIL;
    bool            fRc;

    fprintf(stderr, "Performing: %s\n", pTestName);

    pObj = NodeTree_New( );
    TestForNotNull(pObj, "Missing Test object");
    if (pObj) {

        //obj_TraceSet(pObj, true);
        fRc = obj_IsKindOf(pObj, OBJ_IDENT_NODETREE);
        TestForTrue(fRc, "Failed Ident Test");
        TestForSuccess("");
#ifdef   NODETREE_LOG
        NodeTree_setLog(pObj, this);
#endif

        {
            ASTR_DATA       *pStr = NodeTree_ToDebugString(pObj, 4);
            if (pStr) {
                fprintf(stderr, "Debug: %s\n", AStr_getData(pStr));
                obj_Release(pStr);
                pStr = OBJ_NIL;
            }
        }

        obj_Release(pObj);
        pObj = OBJ_NIL;
    }

    fprintf(stderr, "...%s completed.\n\n\n", pTestName);
    return eRc;
}



ERESULT         Test_NodeTree_Test05 (
    TEST_DATA       *this,
    const
    char            *pTestName
)
{
    ERESULT         eRc = ERESULT_SUCCESS;
    NODETREE_DATA   *pObj = OBJ_NIL;
    bool            fRc;
    uint32_t        i;
    NODETREE_RECORD *pRcd   = NULL;

    fprintf(stderr, "Performing: %s\n", pTestName);
    fprintf(stderr, "\tTesting Node Deletion...\n");

    pObj = createTestTree02(this);
    TestForNotNull(pObj, "Missing Test object");
    if (pObj) {

        //obj_TraceSet(pObj, true);
        fRc = obj_IsKindOf(pObj, OBJ_IDENT_NODETREE);
        TestForTrue(fRc, "Failed Ident Test");
        TestForSuccess("");
#ifdef   NODETREE_LOG
        NodeTree_setLog(pObj, this);
#endif

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
        //                                     // child D(2)
        TestForSuccess("");
        i = NodeTree_getSize(pObj);
        TestForTrue((i == 10), "");

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
        // Check the forest structure.
        i = pObj->root;
        TestForTrue((1 == i), "");
        pRcd = Blocks_RecordGetUnique((BLOCKS_DATA *)pObj, i);
        TestForTrue((pRcd->unique == i), "");
        TestForTrue((pRcd->childIndex == 3), "");
        TestForTrue((pRcd->siblingIndex == 2), "");
        TestForTrue((pRcd->parentIndex == 0), "");
        i = 2;
        pRcd = Blocks_RecordGetUnique((BLOCKS_DATA *)pObj, i);
        TestForTrue((pRcd->unique == i), "");
        TestForTrue((pRcd->childIndex == 7), "");
        TestForTrue((pRcd->siblingIndex == 0), "");
        TestForTrue((pRcd->parentIndex == 0), "");
        i = 3;
        pRcd = Blocks_RecordGetUnique((BLOCKS_DATA *)pObj, i);
        TestForTrue((pRcd->unique == i), "");
        TestForTrue((pRcd->childIndex == 0), "");
        TestForTrue((pRcd->siblingIndex == 4), "");
        TestForTrue((pRcd->parentIndex == 1), "");
        i = 4;
        pRcd = Blocks_RecordGetUnique((BLOCKS_DATA *)pObj, i);
        TestForTrue((pRcd->unique == i), "");
        TestForTrue((pRcd->childIndex == 5), "");
        TestForTrue((pRcd->siblingIndex == 0), "");
        TestForTrue((pRcd->parentIndex == 1), "");
        i = 5;
        pRcd = Blocks_RecordGetUnique((BLOCKS_DATA *)pObj, i);
        TestForTrue((pRcd->unique == i), "");
        TestForTrue((pRcd->childIndex == 0), "");
        TestForTrue((pRcd->siblingIndex == 0), "");
        TestForTrue((pRcd->parentIndex == 4), "");
        i = 6;
        pRcd = Blocks_RecordGetUnique((BLOCKS_DATA *)pObj, i);
        TestForTrue((pRcd->unique == i), "");
        TestForTrue((pRcd->pNode == OBJ_NIL), "");
        i = 7;
        pRcd = Blocks_RecordGetUnique((BLOCKS_DATA *)pObj, i);
        TestForTrue((pRcd->unique == i), "");
        TestForTrue((pRcd->childIndex == 10), "");
        TestForTrue((pRcd->siblingIndex == 8), "");
        TestForTrue((pRcd->parentIndex == 2), "");
        i = 8;
        pRcd = Blocks_RecordGetUnique((BLOCKS_DATA *)pObj, i);
        TestForTrue((pRcd->unique == i), "");
        TestForTrue((pRcd->childIndex == 0), "");
        TestForTrue((pRcd->siblingIndex == 0), "");
        TestForTrue((pRcd->parentIndex == 2), "");
        i = 9;
        pRcd = Blocks_RecordGetUnique((BLOCKS_DATA *)pObj, i);
        TestForTrue((pRcd->unique == i), "");
        TestForTrue((pRcd->pNode == OBJ_NIL), "");
        i = 10;
        pRcd = Blocks_RecordGetUnique((BLOCKS_DATA *)pObj, i);
        TestForTrue((pRcd->unique == i), "");
        TestForTrue((pRcd->childIndex == 0), "");
        TestForTrue((pRcd->siblingIndex == 0), "");
        TestForTrue((pRcd->parentIndex == 7), "");

        {
            ASTR_DATA       *pStr = NodeTree_ToDebugString(pObj, 4);
            if (pStr) {
                fprintf(stderr, "Debug: %s\n", AStr_getData(pStr));
                obj_Release(pStr);
                pStr = OBJ_NIL;
            }
        }

        obj_Release(pObj);
        pObj = OBJ_NIL;
    }

    fprintf(stderr, "...%s completed.\n\n\n", pTestName);
    return eRc;
}



ERESULT         Test_NodeTree_Test06 (
    TEST_DATA       *this,
    const
    char            *pTestName
)
{
    ERESULT         eRc = ERESULT_SUCCESS;
    NODETREE_DATA   *pObj = OBJ_NIL;
    bool            fRc;
    uint32_t        i;
    NODETREE_RECORD *pRcd   = NULL;

    fprintf(stderr, "Performing: %s\n", pTestName);
    fprintf(stderr, "\tTesting ChildrenMove()...\n");

    pObj = createTestTree02(this);
    TestForNotNull(pObj, "Missing Test object");
    if (pObj) {

        //obj_TraceSet(pObj, true);
        fRc = obj_IsKindOf(pObj, OBJ_IDENT_NODETREE);
        TestForTrue(fRc, "Failed Ident Test");
        TestForSuccess("");
#ifdef   NODETREE_LOG
        NodeTree_setLog(pObj, this);
#endif

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
        TestForSuccess("");

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
        // Check the forest structure.
        i = pObj->root;
        TestForTrue((1 == i), "");
        pRcd = Blocks_RecordGetUnique((BLOCKS_DATA *)pObj, i);
        TestForTrue((pRcd->unique == i), "");
        TestForTrue((pRcd->childIndex == 3), "");
        TestForTrue((pRcd->siblingIndex == 2), "");
        TestForTrue((pRcd->parentIndex == 0), "");
        i = 2;
        pRcd = Blocks_RecordGetUnique((BLOCKS_DATA *)pObj, i);
        TestForTrue((pRcd->unique == i), "");
        TestForTrue((pRcd->childIndex == 6), "");
        TestForTrue((pRcd->siblingIndex == 0), "");
        TestForTrue((pRcd->parentIndex == 0), "");
        i = 3;
        pRcd = Blocks_RecordGetUnique((BLOCKS_DATA *)pObj, i);
        TestForTrue((pRcd->unique == i), "");
        TestForTrue((pRcd->childIndex == 10), "");
        TestForTrue((pRcd->siblingIndex == 4), "");
        TestForTrue((pRcd->parentIndex == 1), "");
        i = 4;
        pRcd = Blocks_RecordGetUnique((BLOCKS_DATA *)pObj, i);
        TestForTrue((pRcd->unique == i), "");
        TestForTrue((pRcd->childIndex == 5), "");
        TestForTrue((pRcd->siblingIndex == 0), "");
        TestForTrue((pRcd->parentIndex == 1), "");
        i = 5;
        pRcd = Blocks_RecordGetUnique((BLOCKS_DATA *)pObj, i);
        TestForTrue((pRcd->unique == i), "");
        TestForTrue((pRcd->childIndex == 0), "");
        TestForTrue((pRcd->siblingIndex == 0), "");
        TestForTrue((pRcd->parentIndex == 4), "");
        i = 6;
        pRcd = Blocks_RecordGetUnique((BLOCKS_DATA *)pObj, i);
        TestForTrue((pRcd->unique == i), "");
        TestForTrue((pRcd->childIndex == 9), "");
        TestForTrue((pRcd->siblingIndex == 7), "");
        TestForTrue((pRcd->parentIndex == 2), "");
        i = 7;
        pRcd = Blocks_RecordGetUnique((BLOCKS_DATA *)pObj, i);
        TestForTrue((pRcd->unique == i), "");
        TestForTrue((pRcd->childIndex == 0), "");
        TestForTrue((pRcd->siblingIndex == 8), "");
        TestForTrue((pRcd->parentIndex == 2), "");
        i = 8;
        pRcd = Blocks_RecordGetUnique((BLOCKS_DATA *)pObj, i);
        TestForTrue((pRcd->unique == i), "");
        TestForTrue((pRcd->childIndex == 0), "");
        TestForTrue((pRcd->siblingIndex == 0), "");
        TestForTrue((pRcd->parentIndex == 2), "");
        i = 9;
        pRcd = Blocks_RecordGetUnique((BLOCKS_DATA *)pObj, i);
        TestForTrue((pRcd->unique == i), "");
        TestForTrue((pRcd->childIndex == 0), "");
        TestForTrue((pRcd->siblingIndex == 0), "");
        TestForTrue((pRcd->parentIndex == 6), "");
        i = 10;
        pRcd = Blocks_RecordGetUnique((BLOCKS_DATA *)pObj, i);
        TestForTrue((pRcd->unique == i), "");
        TestForTrue((pRcd->childIndex == 0), "");
        TestForTrue((pRcd->siblingIndex == 0), "");
        TestForTrue((pRcd->parentIndex == 3), "");


        {
            ASTR_DATA       *pStr = NodeTree_ToDebugString(pObj, 4);
            if (pStr) {
                fprintf(stderr, "Debug: %s\n", AStr_getData(pStr));
                obj_Release(pStr);
                pStr = OBJ_NIL;
            }
        }

        obj_Release(pObj);
        pObj = OBJ_NIL;
    }

    fprintf(stderr, "...%s completed.\n\n\n", pTestName);
    return eRc;
}



ERESULT         Test_NodeTree_Test07 (
    TEST_DATA       *this,
    const
    char            *pTestName
)
{
    ERESULT         eRc = ERESULT_SUCCESS;
    NODETREE_DATA   *pObj = OBJ_NIL;
    bool            fRc;

    fprintf(stderr, "Performing: %s\n", pTestName);

    pObj = createTestTree01(this);
    TestForNotNull(pObj, "Missing Test object");
    if (pObj) {

        //obj_TraceSet(pObj, true);
        fRc = obj_IsKindOf(pObj, OBJ_IDENT_NODETREE);
        TestForTrue(fRc, "Failed Ident Test");
        TestForSuccess("");
#ifdef   NODETREE_LOG
        NodeTree_setLog(pObj, this);
#endif

        {
            ASTR_DATA       *pStr = NodeTree_ToDebugString(pObj, 4);
            if (pStr) {
                fprintf(stderr, "Debug: %s\n", AStr_getData(pStr));
                obj_Release(pStr);
                pStr = OBJ_NIL;
            }
        }

        obj_Release(pObj);
        pObj = OBJ_NIL;
    }

    fprintf(stderr, "...%s completed.\n\n\n", pTestName);
    return eRc;
}



ERESULT         Test_NodeTree_Test08 (
    TEST_DATA       *this,
    const
    char            *pTestName
)
{
    ERESULT         eRc = ERESULT_SUCCESS;
    NODETREE_DATA   *pObj = OBJ_NIL;
    bool            fRc;

    fprintf(stderr, "Performing: %s\n", pTestName);

    pObj = createTestTree01(this);
    TestForNotNull(pObj, "Missing Test object");
    if (pObj) {

        //obj_TraceSet(pObj, true);
        fRc = obj_IsKindOf(pObj, OBJ_IDENT_NODETREE);
        TestForTrue(fRc, "Failed Ident Test");
        TestForSuccess("");
#ifdef   NODETREE_LOG
        NodeTree_setLog(pObj, this);
#endif

        {
            ASTR_DATA       *pStr = NodeTree_ToDebugString(pObj, 4);
            if (pStr) {
                fprintf(stderr, "Debug: %s\n", AStr_getData(pStr));
                obj_Release(pStr);
                pStr = OBJ_NIL;
            }
        }

        obj_Release(pObj);
        pObj = OBJ_NIL;
    }

    fprintf(stderr, "...%s completed.\n\n\n", pTestName);
    return eRc;
}



ERESULT         Test_NodeTree_Test09 (
    TEST_DATA       *this,
    const
    char            *pTestName
)
{
    ERESULT         eRc = ERESULT_SUCCESS;
    NODETREE_DATA   *pObj = OBJ_NIL;
    bool            fRc;

    fprintf(stderr, "Performing: %s\n", pTestName);

    pObj = createTestTree01(this);
    TestForNotNull(pObj, "Missing Test object");
    if (pObj) {

        //obj_TraceSet(pObj, true);
        fRc = obj_IsKindOf(pObj, OBJ_IDENT_NODETREE);
        TestForTrue(fRc, "Failed Ident Test");
        TestForSuccess("");
#ifdef   NODETREE_LOG
        NodeTree_setLog(pObj, this);
#endif

        {
            ASTR_DATA       *pStr = NodeTree_ToDebugString(pObj, 4);
            if (pStr) {
                fprintf(stderr, "Debug: %s\n", AStr_getData(pStr));
                obj_Release(pStr);
                pStr = OBJ_NIL;
            }
        }

        obj_Release(pObj);
        pObj = OBJ_NIL;
    }

    fprintf(stderr, "...%s completed.\n\n\n", pTestName);
    return eRc;
}




int     main (
    int         cArgs,
    const
    char        *ppArgs[],
    const
    char        *ppEnv[]
)
{
    ERESULT     eRc;
    TEST_DATA   test = {0};
    TEST_DATA   *pTest = OBJ_NIL;
    int         i;
    const
    char        *pTestNameA = NULL;

    pTest = Test_Init(&test);
    if (OBJ_NIL == pTest) {
        fprintf(
                stderr,
                "\x1b[1m\x1b[31mFATAL\x1b[0m: Could not create Test object!\n\n\n"
        );
        exit(201);
    }

    // Scan args.
    for (i=0; i<cArgs; i++) {
        if (0 == strcmp("--no_int3", ppArgs[i])) {
            Test_setAllowInt3(pTest, false);
        }
    }

    // Execute tests.
    TestExec("OpenClose", Test_NodeTree_OpenClose, NULL, NULL);
    //TestExec("Copy01", Test_NodeTree_Copy01, NULL, NULL);
    TestExec("Test01", Test_NodeTree_Test01, NULL, NULL);
    TestExec("Test02", Test_NodeTree_Test02, NULL, NULL);
    TestExec("Test03", Test_NodeTree_Test03, NULL, NULL);
    TestExec("Test04", Test_NodeTree_Test04, NULL, NULL);
    TestExec("Test05", Test_NodeTree_Test05, NULL, NULL);
    TestExec("Test06", Test_NodeTree_Test06, NULL, NULL);
    TestExec("Test07", Test_NodeTree_Test07, NULL, NULL);
    TestExec("Test08", Test_NodeTree_Test08, NULL, NULL);
    TestExec("Test09", Test_NodeTree_Test09, NULL, NULL);

    obj_Release(pTest);
    pTest = OBJ_NIL;

    // Return to Operating System.
    return 0;
}



