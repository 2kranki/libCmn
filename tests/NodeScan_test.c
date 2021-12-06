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
#include    <NodeScan_internal.h>
#include    <NodeTree_internal.h>
#include    <JsonIn.h>
#include    <SrcErrors.h>
#include    <szTbl.h>



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



// Example from Knuth's "The Art of Computer Programming - Volume 1 (3rd Ed.)",
// page 335 which consists of a forest (two trees) that have sibling roots.
// This was taken from "NodeTree_test".
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







ERESULT         Test_NodeScan_OpenClose (
    TEST_DATA       *this,
    const
    char            *pTestName
)
{
    ERESULT         eRc = ERESULT_SUCCESS;
    NODESCAN_DATA       *pObj = OBJ_NIL;
    bool            fRc;
   
    fprintf(stderr, "Performing: %s\n", pTestName);

    pObj = NodeScan_Alloc( );
    TestForNotNull(pObj, "Missing Test Alloc() object");
    pObj = NodeScan_Init( pObj );
    TestForNotNull(pObj, "Missing Test Init() object");
    if (pObj) {

        //obj_TraceSet(pObj, true);       
        fRc = obj_IsKindOf(pObj, OBJ_IDENT_NODESCAN);
        TestForTrue(fRc, "Failed Ident Test");
#ifdef   NODESCAN_MSGS
        NodeScan_setMsg(pObj, (void *)Test_MsgInfo, (void *)Test_MsgWarn, this);
#endif
        
        // Test something.
        TestForSuccess("test failed");

        obj_Release(pObj);
        pObj = OBJ_NIL;
    }

    fprintf(stderr, "...%s completed.\n\n\n", pTestName);
    return eRc;
}



ERESULT         Test_NodeScan_Copy01 (
    TEST_DATA       *this,
    const
    char            *pTestName
)
{
    ERESULT         eRc = ERESULT_SUCCESS;
    NODESCAN_DATA       *pObj1 = OBJ_NIL;
    NODESCAN_DATA       *pObj2 = OBJ_NIL;
    bool            fRc;
#if defined(NODESCAN_JSON_SUPPORT) && defined(XYZZY)
    ASTR_DATA       *pStr = OBJ_NIL;
#endif
    //int             iRc;
   
    fprintf(stderr, "Performing: %s\n", pTestName);

    pObj1 = NodeScan_New( );
    TestForNotNull(pObj1, "Missing Test object");
    if (pObj1) {

        //obj_TraceSet(pObj1, true);       
        fRc = obj_IsKindOf(pObj1, OBJ_IDENT_NODESCAN);
        TestForTrue(fRc, "Failed Ident Test");
#ifdef   NODESCAN_MSGS
        NodeScan_setMsg(pObj1, (void *)Test_MsgInfo, (void *)Test_MsgWarn, this);
#endif
        
        // Test assign.
        pObj2 = NodeScan_New();
        TestForNotNull(pObj2, "Missing copied object");
        eRc = NodeScan_Assign(pObj1, pObj2);
        TestForFalse((ERESULT_FAILED(eRc)), "Assignment failed");

        fRc = obj_IsKindOf(pObj2, OBJ_IDENT_NODESCAN);
        TestForTrue(fRc, "Failed Ident Test");
        //iRc = NodeScan_Compare(pObj1, pObj2);
        //TestForTrue((0 == iRc), "Failed Compare");
        //TODO: Add More tests here!

        obj_Release(pObj2);
        pObj2 = OBJ_NIL;

        // Test copy.
        pObj2 = NodeScan_Copy(pObj1);
        TestForNotNull(pObj2, "Missing copied object");

        fRc = obj_IsKindOf(pObj2, OBJ_IDENT_NODESCAN);
        TestForTrue(fRc, "Failed Ident Test");
        //iRc = NodeScan_Compare(pObj1, pObj2);
        //TestForTrue((0 == iRc), "Failed Compare");
        //TODO: Add More tests here!

        obj_Release(pObj2);
        pObj2 = OBJ_NIL;

        // Test json support.
#if defined(NODESCAN_JSON_SUPPORT) && defined(XYZZY)
        pStr = NodeScan_ToJson(pObj1);
        TestForNotNull(pStr, "Missing JSON output");
        fprintf(stderr, "JSON: %s\n", AStr_getData(pStr));
        pObj2 = NodeScan_NewFromJsonString(pStr);
        TestForNotNull(pObj2, "Missing JSON created object");
        fRc = obj_IsKindOf(pObj2, OBJ_IDENT_NODESCAN);
        TestForTrue(fRc, "Failed Ident Test");
        obj_Release(pStr);
        pStr = OBJ_NIL;
        //iRc = NodeScan_Compare(pObj1, pObj2);
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



ERESULT         Test_NodeScan_Test01 (
    TEST_DATA       *this,
    const
    char            *pTestName
)
{
    ERESULT         eRc = ERESULT_SUCCESS;
    NODESCAN_DATA   *pObj = OBJ_NIL;
    NODETREE_DATA   *pTree = OBJ_NIL;
    NODEARRAY_DATA  *pArray = OBJ_NIL;
    bool            fRc;
    uint32_t        i;
    uint32_t        iMax;
    const
    char            *pLinearPostA = "((B(K)C)A((H)E(J)FG)D)";
    const
    char            *pChrA;
    const
    char            *pStrA;

    fprintf(stderr, "Performing: %s\n", pTestName);

    pTree = createTestTree02(this);
    TestForNotNull(pTree, "");

    pObj = NodeScan_NewFromTreePost(pTree);
    TestForNotNull(pObj, "Missing Test object");
    if (pObj) {

        //obj_TraceSet(pObj, true);       
        fRc = obj_IsKindOf(pObj, OBJ_IDENT_NODESCAN);
        TestForTrue(fRc, "Failed Ident Test");
        TestForSuccess("");
#ifdef   NODESCAN_LOG
        NodeScan_setLog(pObj, this);
#endif

        pArray = NodeScan_getArray(pObj);
        TestForNotNull(pArray, "");
        iMax = NodeArray_getSize(pArray);
        fprintf(stderr, "\nLinearization Postorder(%d):\n", iMax);
        TestForTrue((iMax == 22), "");
        fprintf(stderr, "\tShould be: %s\n", pLinearPostA);
        fprintf(stderr, "\tFound:     ");
        pChrA = pLinearPostA;
        for (i=1; i<=iMax; ++i) {
            pStrA = Node_getNameUTF8(NodeArray_Get(pArray, i));
            fprintf(stderr, "%s", pStrA);
            TestForTrue((*pChrA == *pStrA), "");
            mem_Free((void *)pStrA);
            pChrA++;
        }
        fprintf(stderr, "\n\n\n");

        {
            ASTR_DATA       *pStr = NodeScan_ToDebugString(pObj, 4);
            if (pStr) {
                fprintf(stderr, "Debug: %s\n", AStr_getData(pStr));
                obj_Release(pStr);
                pStr = OBJ_NIL;
            }
        }

        obj_Release(pObj);
        pObj = OBJ_NIL;
    }

    obj_Release(pTree);
    pTree = OBJ_NIL;

    fprintf(stderr, "...%s completed.\n\n\n", pTestName);
    return eRc;
}



ERESULT         Test_NodeScan_Test02 (
    TEST_DATA       *this,
    const
    char            *pTestName
)
{
    ERESULT         eRc = ERESULT_SUCCESS;
    NODESCAN_DATA   *pObj = OBJ_NIL;
    NODETREE_DATA   *pTree = OBJ_NIL;
    NODEARRAY_DATA  *pArray = OBJ_NIL;
    bool            fRc;
    uint32_t        i;
    uint32_t        iMax;
    const
    char            *pLinearPreA = "(A(BC(K))D(E(H)F(J)G))";
    const
    char            *pChrA;
    const
    char            *pStrA;

    fprintf(stderr, "Performing: %s\n", pTestName);

    pTree = createTestTree02(this);
    TestForNotNull(pTree, "");

    pObj = NodeScan_NewFromTreePre(pTree);
    TestForNotNull(pObj, "Missing Test object");
    if (pObj) {

        //obj_TraceSet(pObj, true);
        fRc = obj_IsKindOf(pObj, OBJ_IDENT_NODESCAN);
        TestForTrue(fRc, "Failed Ident Test");
        TestForSuccess("");
#ifdef   NODESCAN_LOG
        NodeScan_setLog(pObj, this);
#endif

        pArray = NodeScan_getArray(pObj);
        TestForNotNull(pArray, "");
        iMax = NodeArray_getSize(pArray);
        fprintf(stderr, "\nLinearization Preorder(%d):\n", iMax);
        TestForTrue((iMax == 22), "");
        fprintf(stderr, "\tShould be: %s\n", pLinearPreA);
        fprintf(stderr, "\tFound:     ");
        pChrA = pLinearPreA;
        for (i=1; i<=iMax; ++i) {
            pStrA = Node_getNameUTF8(NodeArray_Get(pArray, i));
            fprintf(stderr, "%s", pStrA);
            TestForTrue((*pChrA == *pStrA), "");
            mem_Free((void *)pStrA);
            pChrA++;
        }
        fprintf(stderr, "\n\n\n");

        {
            ASTR_DATA       *pStr = NodeScan_ToDebugString(pObj, 4);
            if (pStr) {
                fprintf(stderr, "Debug: %s\n", AStr_getData(pStr));
                obj_Release(pStr);
                pStr = OBJ_NIL;
            }
        }

        obj_Release(pObj);
        pObj = OBJ_NIL;
    }

    obj_Release(pTree);
    pTree = OBJ_NIL;

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
    TestExec("OpenClose", Test_NodeScan_OpenClose, NULL, NULL);
    //TestExec("Copy01", Test_NodeScan_Copy01, NULL, NULL);
    TestExec("Test01", Test_NodeScan_Test01, NULL, NULL);
    TestExec("Test02", Test_NodeScan_Test02, NULL, NULL);

    obj_Release(pTest);
    pTest = OBJ_NIL;

    // Return to Operating System.
    return 0;
}



