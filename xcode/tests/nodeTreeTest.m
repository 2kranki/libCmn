/*
 *	Generated 08/04/2015 17:02:38
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


#import <XCTest/XCTest.h>
#import <libCmn/libCmn.h>



// All code under test must be linked into the Unit Test bundle
// Test Macros:
//      XCTAssert(expression, failure_description, ...)
//      XCTFail(failure_description, ...)
//      XCTAssertEqualObjects(object_1, object_2, failure_description, ...) uses isEqualTo:
//      XCTAssertEquals(value_1, value_2, failure_description, ...)
//      XCTAssertEqualsWithAccuracy(value_1, value_2, accuracy, failure_description, ...)
//      XCTAssertNil(expression, failure_description, ...)
//      XCTAssertNotNil(expression, failure_description, ...)
//      XCTAssertTrue(expression, failure_description, ...)
//      XCTAssertFalse(expression, failure_description, ...)
//      XCTAssertThrows(expression, failure_description, ...)
//      XCTAssertThrowsSpecific(expression, exception_class, failure_description, ...)
//      XCTAssertThrowsSpecificNamed(expression, exception_class, exception_name, failure_description, ...)
//      XCTAssertNoThrow(expression, failure_description, ...)
//      XCTAssertNoThrowSpecific(expression, exception_class, failure_description, ...)
//      XCTAssertNoThrowSpecificNamed(expression, exception_class, exception_name, failure_description, ...)


#include    "nodeTree_internal.h"
#include    "nodeArray.h"
#include    "eresult.h"



static
uint32_t        count = 0;
static
NODE_DATA       *pNodes[20];




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
    NODE_DATA       *pNodeI = OBJ_NIL;
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
    pNodeI = node_NewWithUTF8Con("I", OBJ_NIL);
    if  (OBJ_NIL == pNodeI) {
        obj_Release(pTree);
        pTree = OBJ_NIL;
        return pTree;
    }
    
    fprintf(stderr, "\n\nCreate the tree:\n");
    fprintf(stderr, "Tree    Index  Sibling  Child  Parent\n");
    fprintf(stderr, "A         1       0       2       0\n");
    fprintf(stderr, "--B       2       3       5       1\n");
    fprintf(stderr, "----C     5       6       0       2\n");
    fprintf(stderr, "----D     6       0       0       2\n");
    fprintf(stderr, "--E       3       4       7       1\n");
    fprintf(stderr, "----F     7       8       9       3\n");
    fprintf(stderr, "------G   9       0       0       7\n");
    fprintf(stderr, "----H     8       0       0       3\n");
    fprintf(stderr, "--I       4       0       0       1\n");
    fprintf(stderr, "\n\n\n");

    i = nodeTree_ChildAdd(pTree, 0, pNodeA);
    if  (i == 1)
        ;
    else {
        obj_Release(pTree);
        pTree = OBJ_NIL;
        return pTree;
    }
    eRc = nodeTree_ChildrenAdd(pTree,node_getIndex(pNodeA), pNodeB, pNodeE, pNodeI, OBJ_NIL);
    if  (ERESULT_FAILED(eRc)) {
        obj_Release(pTree);
        pTree = OBJ_NIL;
        return pTree;
    }
    eRc = nodeTree_ChildrenAdd(pTree,node_getIndex(pNodeB), pNodeC, pNodeD, OBJ_NIL);
    if  (ERESULT_FAILED(eRc)) {
        obj_Release(pTree);
        pTree = OBJ_NIL;
        return pTree;
    }
    eRc = nodeTree_ChildrenAdd(pTree,node_getIndex(pNodeE), pNodeF, pNodeH, OBJ_NIL);
    if  (ERESULT_FAILED(eRc)) {
        obj_Release(pTree);
        pTree = OBJ_NIL;
        return pTree;
    }
    eRc = nodeTree_ChildrenAdd(pTree,node_getIndex(pNodeF), pNodeG, OBJ_NIL);
    if  (ERESULT_FAILED(eRc)) {
        obj_Release(pTree);
        pTree = OBJ_NIL;
        return pTree;
    }

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







@interface nodeTreeTests : XCTestCase

@end

@implementation nodeTreeTests


- (void)setUp
{
    [super setUp];
    // Put setup code here. This method is called before the invocation of each
    // test method in the class.
    
    mem_Init( );
    
}


- (void)tearDown
{
    mem_Dump( );
    mem_Release( );
    
    // Put teardown code here. This method is called after the invocation of each
    // test method in the class.
    [super tearDown];
}




- (void)testOpenClose
{
    NODETREE_DATA	*pObj = OBJ_NIL;
   
    pObj = nodeTree_Alloc( );
    XCTAssertFalse( (OBJ_NIL == pObj) );
    pObj = nodeTree_Init( pObj );
    XCTAssertFalse( (OBJ_NIL == pObj) );
    if (pObj) {
        obj_Release(pObj);
        pObj = OBJ_NIL;
    }

    szTbl_SharedReset();
    
}



- (void)testUpDownDelete01
{
    NODETREE_DATA	*pObj = OBJ_NIL;
    NODEARRAY_DATA  *pArray = OBJ_NIL;
    NODEENTRY_DATA  *pEntry = OBJ_NIL;
    uint32_t        i;
    uint32_t        iMax;
    const
    char            *pStrA;
    ERESULT         eRc;
    ASTR_DATA       *pStr = OBJ_NIL;
    
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
        XCTAssertTrue( (node_getIndex(nodeEntry_getNode(pEntry)) == 1) );
        XCTAssertTrue( (nodeEntry_getSibling(pEntry) == 0) );
        XCTAssertTrue( (nodeEntry_getChild(pEntry) == 2) );
        XCTAssertTrue( (nodeEntry_getParent(pEntry) == 0) );
        pEntry = objArray_Get(pObj->pArray, 2);
        XCTAssertFalse( (pEntry == OBJ_NIL) );
        XCTAssertTrue( (node_getIndex(nodeEntry_getNode(pEntry)) == 2) );
        XCTAssertTrue( (nodeEntry_getSibling(pEntry) == 3) );
        XCTAssertTrue( (nodeEntry_getChild(pEntry) == 5) );
        XCTAssertTrue( (nodeEntry_getParent(pEntry) == 1) );
        pEntry = objArray_Get(pObj->pArray, 3);
        XCTAssertFalse( (pEntry == OBJ_NIL) );
        XCTAssertTrue( (node_getIndex(nodeEntry_getNode(pEntry)) == 3) );
        XCTAssertTrue( (nodeEntry_getSibling(pEntry) == 4) );
        XCTAssertTrue( (nodeEntry_getChild(pEntry) == 7) );
        XCTAssertTrue( (nodeEntry_getParent(pEntry) == 1) );
        pEntry = objArray_Get(pObj->pArray, 4);
        XCTAssertFalse( (pEntry == OBJ_NIL) );
        XCTAssertTrue( (node_getIndex(nodeEntry_getNode(pEntry)) == 4) );
        XCTAssertTrue( (nodeEntry_getSibling(pEntry) == 0) );
        XCTAssertTrue( (nodeEntry_getChild(pEntry) == 0) );
        XCTAssertTrue( (nodeEntry_getParent(pEntry) == 1) );
        pEntry = objArray_Get(pObj->pArray, 5);
        XCTAssertFalse( (pEntry == OBJ_NIL) );
        XCTAssertTrue( (node_getIndex(nodeEntry_getNode(pEntry)) == 5) );
        XCTAssertTrue( (nodeEntry_getSibling(pEntry) == 6) );
        XCTAssertTrue( (nodeEntry_getChild(pEntry) == 0) );
        XCTAssertTrue( (nodeEntry_getParent(pEntry) == 2) );
        pEntry = objArray_Get(pObj->pArray, 6);
        XCTAssertFalse( (pEntry == OBJ_NIL) );
        XCTAssertTrue( (node_getIndex(nodeEntry_getNode(pEntry)) == 6) );
        XCTAssertTrue( (nodeEntry_getSibling(pEntry) == 0) );
        XCTAssertTrue( (nodeEntry_getChild(pEntry) == 0) );
        XCTAssertTrue( (nodeEntry_getParent(pEntry) == 2) );
        pEntry = objArray_Get(pObj->pArray, 7);
        XCTAssertFalse( (pEntry == OBJ_NIL) );
        XCTAssertTrue( (node_getIndex(nodeEntry_getNode(pEntry)) == 7) );
        XCTAssertTrue( (nodeEntry_getSibling(pEntry) == 8) );
        XCTAssertTrue( (nodeEntry_getChild(pEntry) == 9) );
        XCTAssertTrue( (nodeEntry_getParent(pEntry) == 3) );
        pEntry = objArray_Get(pObj->pArray, 8);
        XCTAssertFalse( (pEntry == OBJ_NIL) );
        XCTAssertTrue( (node_getIndex(nodeEntry_getNode(pEntry)) == 8) );
        XCTAssertTrue( (nodeEntry_getSibling(pEntry) == 0) );
        XCTAssertTrue( (nodeEntry_getChild(pEntry) == 0) );
        XCTAssertTrue( (nodeEntry_getParent(pEntry) == 3) );
        pEntry = objArray_Get(pObj->pArray, 9);
        XCTAssertFalse( (pEntry == OBJ_NIL) );
        XCTAssertTrue( (node_getIndex(nodeEntry_getNode(pEntry)) == 9) );
        XCTAssertTrue( (nodeEntry_getSibling(pEntry) == 0) );
        XCTAssertTrue( (nodeEntry_getChild(pEntry) == 0) );
        XCTAssertTrue( (nodeEntry_getParent(pEntry) == 7) );

        pStr = nodeTree_ToDebugString(pObj, 0);
        fprintf(stderr, "Debug = %s\n\n\n",AStr_getData(pStr));
        obj_Release(pStr);
        pStr = OBJ_NIL;
        
        pArray = nodeTree_ToLinearizationPre(pObj);
        XCTAssertFalse( (OBJ_NIL == pArray) );
        iMax = nodeArray_getSize(pArray);
        XCTAssertTrue( (19 == iMax) );
        fprintf(stderr, "\nLinearization Preorder(%d):\n",iMax);
        fprintf(stderr, "\tShould be: (A(B(CD)E(F(G)H)I))\n");
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

        visitorReset();
        eRc = nodeTree_VisitInorder(pObj, visitor, NULL);
        XCTAssertFalse( (ERESULT_FAILED(eRc)) );
        XCTAssertTrue( (9 == count) );
        fprintf(stderr, "\nInorder(%d):\n",iMax);
        fprintf(stderr, "\tCDBGFHEIA (should be)\n\t");
        for (i=0; i<count; ++i) {
            pStrA = node_getNameUTF8(pNodes[i]);
            fprintf(stderr, "%c", *pStrA);
            mem_Free((void *)pStrA);
            pStrA = NULL;
        }
        fprintf(stderr, " (actual)\n");
        eRc = name_CompareA(node_getName(pNodes[0]),"C");
        XCTAssertTrue( (ERESULT_SUCCESS_EQUAL == eRc) );
        eRc = name_CompareA(node_getName(pNodes[1]),"D");
        XCTAssertTrue( (ERESULT_SUCCESS_EQUAL == eRc) );
        eRc = name_CompareA(node_getName(pNodes[2]),"B");
        XCTAssertTrue( (ERESULT_SUCCESS_EQUAL == eRc) );
        eRc = name_CompareA(node_getName(pNodes[3]),"G");
        XCTAssertTrue( (ERESULT_SUCCESS_EQUAL == eRc) );
        eRc = name_CompareA(node_getName(pNodes[4]),"F");
        XCTAssertTrue( (ERESULT_SUCCESS_EQUAL == eRc) );
        eRc = name_CompareA(node_getName(pNodes[5]),"H");
        XCTAssertTrue( (ERESULT_SUCCESS_EQUAL == eRc) );
        eRc = name_CompareA(node_getName(pNodes[6]),"E");
        XCTAssertTrue( (ERESULT_SUCCESS_EQUAL == eRc) );
        eRc = name_CompareA(node_getName(pNodes[7]),"I");
        XCTAssertTrue( (ERESULT_SUCCESS_EQUAL == eRc) );
        eRc = name_CompareA(node_getName(pNodes[8]),"A");
        XCTAssertTrue( (ERESULT_SUCCESS_EQUAL == eRc) );

        visitorReset();
        eRc = nodeTree_VisitPostorder(pObj, visitor, NULL);
        XCTAssertFalse( (ERESULT_FAILED(eRc)) );
        XCTAssertTrue( (9 == count) );
        fprintf(stderr, "\nPostorder(%d):\n",iMax);
        fprintf(stderr, "\tDCGHFIEBA (should be)\n\t");
        for (i=0; i<count; ++i) {
            pStrA = node_getNameUTF8(pNodes[i]);
            fprintf(stderr, "%c", *pStrA);
            mem_Free((void *)pStrA);
            pStrA = NULL;
        }
        fprintf(stderr, " (actual)\n");
        eRc = name_CompareA(node_getName(pNodes[0]),"D");
        XCTAssertTrue( (ERESULT_SUCCESS_EQUAL == eRc) );
        eRc = name_CompareA(node_getName(pNodes[1]),"C");
        XCTAssertTrue( (ERESULT_SUCCESS_EQUAL == eRc) );
        eRc = name_CompareA(node_getName(pNodes[2]),"G");
        XCTAssertTrue( (ERESULT_SUCCESS_EQUAL == eRc) );
        eRc = name_CompareA(node_getName(pNodes[3]),"H");
        XCTAssertTrue( (ERESULT_SUCCESS_EQUAL == eRc) );
        eRc = name_CompareA(node_getName(pNodes[4]),"F");
        XCTAssertTrue( (ERESULT_SUCCESS_EQUAL == eRc) );
        eRc = name_CompareA(node_getName(pNodes[5]),"I");
        XCTAssertTrue( (ERESULT_SUCCESS_EQUAL == eRc) );
        eRc = name_CompareA(node_getName(pNodes[6]),"E");
        XCTAssertTrue( (ERESULT_SUCCESS_EQUAL == eRc) );
        eRc = name_CompareA(node_getName(pNodes[7]),"B");
        XCTAssertTrue( (ERESULT_SUCCESS_EQUAL == eRc) );
        eRc = name_CompareA(node_getName(pNodes[8]),"A");
        XCTAssertTrue( (ERESULT_SUCCESS_EQUAL == eRc) );
        
        visitorReset();
        eRc = nodeTree_VisitPreorder(pObj, visitor, NULL);
        XCTAssertFalse( (ERESULT_FAILED(eRc)) );
        XCTAssertTrue( (9 == count) );
        fprintf(stderr, "\nPreorder(%d):\n",iMax);
        fprintf(stderr, "\tABCDEFGHI (should be)\n\t");
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
        eRc = name_CompareA(node_getName(pNodes[3]),"D");
        XCTAssertTrue( (ERESULT_SUCCESS_EQUAL == eRc) );
        eRc = name_CompareA(node_getName(pNodes[4]),"E");
        XCTAssertTrue( (ERESULT_SUCCESS_EQUAL == eRc) );
        eRc = name_CompareA(node_getName(pNodes[5]),"F");
        XCTAssertTrue( (ERESULT_SUCCESS_EQUAL == eRc) );
        eRc = name_CompareA(node_getName(pNodes[6]),"G");
        XCTAssertTrue( (ERESULT_SUCCESS_EQUAL == eRc) );
        eRc = name_CompareA(node_getName(pNodes[7]),"H");
        XCTAssertTrue( (ERESULT_SUCCESS_EQUAL == eRc) );
        eRc = name_CompareA(node_getName(pNodes[8]),"I");
        XCTAssertTrue( (ERESULT_SUCCESS_EQUAL == eRc) );
        
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
        
        eRc = nodeTree_NodeDelete(pObj, 3);     // Delete E(3) which includes F(7),G(9),H(8)
        XCTAssertFalse( (ERESULT_FAILED(eRc)) );
        
        // Verify that the linkage fields are correct.
        pEntry = objArray_Get(pObj->pArray, 1);
        XCTAssertFalse( (pEntry == OBJ_NIL) );
        XCTAssertTrue( (node_getIndex(nodeEntry_getNode(pEntry)) == 1) );
        XCTAssertTrue( (nodeEntry_getSibling(pEntry) == 0) );
        XCTAssertTrue( (nodeEntry_getChild(pEntry) == 2) );
        XCTAssertTrue( (nodeEntry_getParent(pEntry) == 0) );
        pEntry = objArray_Get(pObj->pArray, 2);
        XCTAssertFalse( (pEntry == OBJ_NIL) );
        XCTAssertTrue( (node_getIndex(nodeEntry_getNode(pEntry)) == 2) );
        XCTAssertTrue( (nodeEntry_getSibling(pEntry) == 4) );
        XCTAssertTrue( (nodeEntry_getChild(pEntry) == 5) );
        XCTAssertTrue( (nodeEntry_getParent(pEntry) == 1) );
        pEntry = objArray_Get(pObj->pArray, 3);
        XCTAssertTrue( (pEntry == OBJ_NIL) );
        pEntry = objArray_Get(pObj->pArray, 4);
        XCTAssertFalse( (pEntry == OBJ_NIL) );
        XCTAssertTrue( (node_getIndex(nodeEntry_getNode(pEntry)) == 4) );
        XCTAssertTrue( (nodeEntry_getSibling(pEntry) == 0) );
        XCTAssertTrue( (nodeEntry_getChild(pEntry) == 0) );
        XCTAssertTrue( (nodeEntry_getParent(pEntry) == 1) );
        pEntry = objArray_Get(pObj->pArray, 5);
        XCTAssertFalse( (pEntry == OBJ_NIL) );
        XCTAssertTrue( (node_getIndex(nodeEntry_getNode(pEntry)) == 5) );
        XCTAssertTrue( (nodeEntry_getSibling(pEntry) == 6) );
        XCTAssertTrue( (nodeEntry_getChild(pEntry) == 0) );
        XCTAssertTrue( (nodeEntry_getParent(pEntry) == 2) );
        pEntry = objArray_Get(pObj->pArray, 6);
        XCTAssertFalse( (pEntry == OBJ_NIL) );
        XCTAssertTrue( (node_getIndex(nodeEntry_getNode(pEntry)) == 6) );
        XCTAssertTrue( (nodeEntry_getSibling(pEntry) == 0) );
        XCTAssertTrue( (nodeEntry_getChild(pEntry) == 0) );
        XCTAssertTrue( (nodeEntry_getParent(pEntry) == 2) );
        pEntry = objArray_Get(pObj->pArray, 7);
        XCTAssertTrue( (pEntry == OBJ_NIL) );
        pEntry = objArray_Get(pObj->pArray, 8);
        XCTAssertTrue( (pEntry == OBJ_NIL) );
        pEntry = objArray_Get(pObj->pArray, 9);
        XCTAssertTrue( (pEntry == OBJ_NIL) );
        
        XCTAssertTrue( (obj_IsFlag(pObj, OBJ_FLAG_ALLOC)) );
        obj_Release(pObj);
        pObj = OBJ_NIL;
    }
    
    szTbl_SharedReset();
    
}



- (void)testMove01
{
    NODETREE_DATA	*pObj = OBJ_NIL;
    NODEENTRY_DATA  *pEntry = OBJ_NIL;
    uint32_t        i;
    ERESULT         eRc;
    
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
        XCTAssertTrue( (node_getIndex(nodeEntry_getNode(pEntry)) == 1) );
        XCTAssertTrue( (nodeEntry_getSibling(pEntry) == 0) );
        XCTAssertTrue( (nodeEntry_getChild(pEntry) == 2) );
        XCTAssertTrue( (nodeEntry_getParent(pEntry) == 0) );
        pEntry = objArray_Get(pObj->pArray, 2);
        XCTAssertFalse( (pEntry == OBJ_NIL) );
        XCTAssertTrue( (node_getIndex(nodeEntry_getNode(pEntry)) == 2) );
        XCTAssertTrue( (nodeEntry_getSibling(pEntry) == 3) );
        XCTAssertTrue( (nodeEntry_getChild(pEntry) == 5) );
        XCTAssertTrue( (nodeEntry_getParent(pEntry) == 1) );
        pEntry = objArray_Get(pObj->pArray, 3);
        XCTAssertFalse( (pEntry == OBJ_NIL) );
        XCTAssertTrue( (node_getIndex(nodeEntry_getNode(pEntry)) == 3) );
        XCTAssertTrue( (nodeEntry_getSibling(pEntry) == 4) );
        XCTAssertTrue( (nodeEntry_getChild(pEntry) == 7) );
        XCTAssertTrue( (nodeEntry_getParent(pEntry) == 1) );
        pEntry = objArray_Get(pObj->pArray, 4);
        XCTAssertFalse( (pEntry == OBJ_NIL) );
        XCTAssertTrue( (node_getIndex(nodeEntry_getNode(pEntry)) == 4) );
        XCTAssertTrue( (nodeEntry_getSibling(pEntry) == 0) );
        XCTAssertTrue( (nodeEntry_getChild(pEntry) == 0) );
        XCTAssertTrue( (nodeEntry_getParent(pEntry) == 1) );
        pEntry = objArray_Get(pObj->pArray, 5);
        XCTAssertFalse( (pEntry == OBJ_NIL) );
        XCTAssertTrue( (node_getIndex(nodeEntry_getNode(pEntry)) == 5) );
        XCTAssertTrue( (nodeEntry_getSibling(pEntry) == 6) );
        XCTAssertTrue( (nodeEntry_getChild(pEntry) == 0) );
        XCTAssertTrue( (nodeEntry_getParent(pEntry) == 2) );
        pEntry = objArray_Get(pObj->pArray, 6);
        XCTAssertFalse( (pEntry == OBJ_NIL) );
        XCTAssertTrue( (node_getIndex(nodeEntry_getNode(pEntry)) == 6) );
        XCTAssertTrue( (nodeEntry_getSibling(pEntry) == 0) );
        XCTAssertTrue( (nodeEntry_getChild(pEntry) == 0) );
        XCTAssertTrue( (nodeEntry_getParent(pEntry) == 2) );
        pEntry = objArray_Get(pObj->pArray, 7);
        XCTAssertFalse( (pEntry == OBJ_NIL) );
        XCTAssertTrue( (node_getIndex(nodeEntry_getNode(pEntry)) == 7) );
        XCTAssertTrue( (nodeEntry_getSibling(pEntry) == 8) );
        XCTAssertTrue( (nodeEntry_getChild(pEntry) == 9) );
        XCTAssertTrue( (nodeEntry_getParent(pEntry) == 3) );
        pEntry = objArray_Get(pObj->pArray, 8);
        XCTAssertFalse( (pEntry == OBJ_NIL) );
        XCTAssertTrue( (node_getIndex(nodeEntry_getNode(pEntry)) == 8) );
        XCTAssertTrue( (nodeEntry_getSibling(pEntry) == 0) );
        XCTAssertTrue( (nodeEntry_getChild(pEntry) == 0) );
        XCTAssertTrue( (nodeEntry_getParent(pEntry) == 3) );
        pEntry = objArray_Get(pObj->pArray, 9);
        XCTAssertFalse( (pEntry == OBJ_NIL) );
        XCTAssertTrue( (node_getIndex(nodeEntry_getNode(pEntry)) == 9) );
        XCTAssertTrue( (nodeEntry_getSibling(pEntry) == 0) );
        XCTAssertTrue( (nodeEntry_getChild(pEntry) == 0) );
        XCTAssertTrue( (nodeEntry_getParent(pEntry) == 7) );
        
        eRc = nodeTree_ChildrenMove(pObj, 2, 3);    // Delete C(5), D(6) after
        //                                              // child H(8) of E(3)
        XCTAssertFalse( (ERESULT_FAILED(eRc)) );
        
        // Verify that the linkage fields are correct.
        pEntry = objArray_Get(pObj->pArray, 1);
        XCTAssertFalse( (pEntry == OBJ_NIL) );
        XCTAssertTrue( (node_getIndex(nodeEntry_getNode(pEntry)) == 1) );
        XCTAssertTrue( (nodeEntry_getSibling(pEntry) == 0) );
        XCTAssertTrue( (nodeEntry_getChild(pEntry) == 2) );
        XCTAssertTrue( (nodeEntry_getParent(pEntry) == 0) );
        pEntry = objArray_Get(pObj->pArray, 2);
        XCTAssertFalse( (pEntry == OBJ_NIL) );
        XCTAssertTrue( (node_getIndex(nodeEntry_getNode(pEntry)) == 2) );
        XCTAssertTrue( (nodeEntry_getSibling(pEntry) == 3) );
        XCTAssertTrue( (nodeEntry_getChild(pEntry) == 0) );
        XCTAssertTrue( (nodeEntry_getParent(pEntry) == 1) );
        pEntry = objArray_Get(pObj->pArray, 3);
        XCTAssertFalse( (pEntry == OBJ_NIL) );
        XCTAssertTrue( (node_getIndex(nodeEntry_getNode(pEntry)) == 3) );
        XCTAssertTrue( (nodeEntry_getSibling(pEntry) == 4) );
        XCTAssertTrue( (nodeEntry_getChild(pEntry) == 7) );
        XCTAssertTrue( (nodeEntry_getParent(pEntry) == 1) );
        pEntry = objArray_Get(pObj->pArray, 4);
        XCTAssertFalse( (pEntry == OBJ_NIL) );
        XCTAssertTrue( (node_getIndex(nodeEntry_getNode(pEntry)) == 4) );
        XCTAssertTrue( (nodeEntry_getSibling(pEntry) == 0) );
        XCTAssertTrue( (nodeEntry_getChild(pEntry) == 0) );
        XCTAssertTrue( (nodeEntry_getParent(pEntry) == 1) );
        pEntry = objArray_Get(pObj->pArray, 5);
        XCTAssertFalse( (pEntry == OBJ_NIL) );
        XCTAssertTrue( (node_getIndex(nodeEntry_getNode(pEntry)) == 5) );
        XCTAssertTrue( (nodeEntry_getSibling(pEntry) == 6) );
        XCTAssertTrue( (nodeEntry_getChild(pEntry) == 0) );
        XCTAssertTrue( (nodeEntry_getParent(pEntry) == 3) );
        pEntry = objArray_Get(pObj->pArray, 6);
        XCTAssertFalse( (pEntry == OBJ_NIL) );
        XCTAssertTrue( (node_getIndex(nodeEntry_getNode(pEntry)) == 6) );
        XCTAssertTrue( (nodeEntry_getSibling(pEntry) == 0) );
        XCTAssertTrue( (nodeEntry_getChild(pEntry) == 0) );
        XCTAssertTrue( (nodeEntry_getParent(pEntry) == 3) );
        pEntry = objArray_Get(pObj->pArray, 7);
        XCTAssertFalse( (pEntry == OBJ_NIL) );
        XCTAssertTrue( (node_getIndex(nodeEntry_getNode(pEntry)) == 7) );
        XCTAssertTrue( (nodeEntry_getSibling(pEntry) == 8) );
        XCTAssertTrue( (nodeEntry_getChild(pEntry) == 9) );
        XCTAssertTrue( (nodeEntry_getParent(pEntry) == 3) );
        pEntry = objArray_Get(pObj->pArray, 8);
        XCTAssertFalse( (pEntry == OBJ_NIL) );
        XCTAssertTrue( (node_getIndex(nodeEntry_getNode(pEntry)) == 8) );
        XCTAssertTrue( (nodeEntry_getSibling(pEntry) == 5) );
        XCTAssertTrue( (nodeEntry_getChild(pEntry) == 0) );
        XCTAssertTrue( (nodeEntry_getParent(pEntry) == 3) );
        pEntry = objArray_Get(pObj->pArray, 9);
        XCTAssertFalse( (pEntry == OBJ_NIL) );
        XCTAssertTrue( (node_getIndex(nodeEntry_getNode(pEntry)) == 9) );
        XCTAssertTrue( (nodeEntry_getSibling(pEntry) == 0) );
        XCTAssertTrue( (nodeEntry_getChild(pEntry) == 0) );
        XCTAssertTrue( (nodeEntry_getParent(pEntry) == 7) );
        
        XCTAssertTrue( (obj_IsFlag(pObj, OBJ_FLAG_ALLOC)) );
        obj_Release(pObj);
        pObj = OBJ_NIL;
    }
    
    szTbl_SharedReset();
    
}



- (void)testNode
{
    NODETREE_DATA	*pObj = OBJ_NIL;
    NODE_DATA       *pNodeA = OBJ_NIL;
    NODE_DATA       *pNodeB = OBJ_NIL;
    NODE_DATA       *pNode = OBJ_NIL;
    uint32_t        nodeA;
    uint32_t        nodeB;
    
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
    
    szTbl_SharedReset();
    
}



- (void)testNodeLinkChild
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
    
    szTbl_SharedReset();
    
}



@end



