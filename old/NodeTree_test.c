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



// Example from Knuth's "The Art of Computer Programming - Volume 1 (3rd Ed.)", page 332
// which consists of a forest (two trees) that have sibling roots.
static
NODETREE_DATA * createTestTree01(
)
{
    NODETREE_DATA   *pTree = OBJ_NIL;
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

    pTree = NodeTree_Alloc( );
    if  (OBJ_NIL == pTree) {
        return pTree;
    }
    pTree = NodeTree_Init( pTree );
    if  (OBJ_NIL == pTree) {
        return pTree;
    }

    pNodeA = Node_NewWithUTF8ConAndClass(0, "A", OBJ_NIL);
    if  (OBJ_NIL == pNodeA) {
        obj_Release(pTree);
        pTree = OBJ_NIL;
        return pTree;
    }
    pNodeB = Node_NewWithUTF8ConAndClass(0, "B", OBJ_NIL);
    if  (OBJ_NIL == pNodeB) {
        obj_Release(pTree);
        pTree = OBJ_NIL;
        return pTree;
    }
    pNodeC = Node_NewWithUTF8ConAndClass(0, "C", OBJ_NIL);
    if  (OBJ_NIL == pNodeC) {
        obj_Release(pTree);
        pTree = OBJ_NIL;
        return pTree;
    }
    pNodeD = Node_NewWithUTF8ConAndClass(0, "D", OBJ_NIL);
    if  (OBJ_NIL == pNodeD) {
        obj_Release(pTree);
        pTree = OBJ_NIL;
        return pTree;
    }
    pNodeE = Node_NewWithUTF8ConAndClass(0, "E", OBJ_NIL);
    if  (OBJ_NIL == pNodeE) {
        obj_Release(pTree);
        pTree = OBJ_NIL;
        return pTree;
    }
    pNodeF = Node_NewWithUTF8ConAndClass(0, "F", OBJ_NIL);
    if  (OBJ_NIL == pNodeF) {
        obj_Release(pTree);
        pTree = OBJ_NIL;
        return pTree;
    }
    pNodeG = Node_NewWithUTF8ConAndClass(0, "G", OBJ_NIL);
    if  (OBJ_NIL == pNodeG) {
        obj_Release(pTree);
        pTree = OBJ_NIL;
        return pTree;
    }
    pNodeH = Node_NewWithUTF8ConAndClass(0, "H", OBJ_NIL);
    if  (OBJ_NIL == pNodeH) {
        obj_Release(pTree);
        pTree = OBJ_NIL;
        return pTree;
    }
    pNodeJ = Node_NewWithUTF8ConAndClass(0, "J", OBJ_NIL);
    if  (OBJ_NIL == pNodeJ) {
        obj_Release(pTree);
        pTree = OBJ_NIL;
        return pTree;
    }
    pNodeK = Node_NewWithUTF8ConAndClass(0, "K", OBJ_NIL);
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

    pTree = NodeTree_Alloc( );
    if  (OBJ_NIL == pTree) {
        return pTree;
    }
    pTree = NodeTree_Init( pTree );
    if  (OBJ_NIL == pTree) {
        return pTree;
    }

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







ERESULT         Test_NodeTree_OpenClose (
    TEST_DATA       *this,
    const
    char            *pTestName
)
{
    ERESULT         eRc = ERESULT_SUCCESS;
    NODETREE_DATA       *pObj = OBJ_NIL;
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
    NODETREE_DATA       *pObj = OBJ_NIL;
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

    obj_Release(pTest);
    pTest = OBJ_NIL;

    // Return to Operating System.
    return 0;
}



