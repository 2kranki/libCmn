/*
 *	Generated 08/31/2016 21:21:55
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


#include    "nodeATree_internal.h"

char        *pPreorder[11] = {
    "A",
    "B",
    "D",
    "E",
    "C",
    "F",
    "H",
    "I",
    "G",
    "J",
    NULL
};

char        **ppVisit = NULL;




    void            nodeVisitor(
        OBJ_ID          pObj,               // Object supplied below
        NODE_DATA       *pNode,             // Current Node
        uint16_t        indent              // Indent level * 4
    )
    {
        const
        char            *pStrA;
        pStrA = node_getNameUTF8(pNode);
        fprintf(stderr, "%s - %s\n", *ppVisit, pStrA);
        if (0 == strcmp(*ppVisit, pStrA)) {
        }
        else {
            fprintf(
                    stderr,
                    "ERROR - nodeVisitor comparison invalid(\"%s\",\"%s\"\n",
                    *ppVisit,
                    pStrA
            );
        }
        mem_Free((void *)pStrA);
        ++ppVisit;
    }





@interface nodeATreeTests : XCTestCase

@end

@implementation nodeATreeTests


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
    NODEATREE_DATA  *pObj = OBJ_NIL;
    uint32_t        index;
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
    NODEARRAY_DATA  *pArray = OBJ_NIL;
    uint32_t        i;
    uint32_t        iMax;
    const
    char            *pStrA;
    ERESULT         eRc;
   
    pObj = nodeATree_Alloc(0);
    XCTAssertFalse( (OBJ_NIL == pObj) );
    pObj = nodeATree_Init( pObj, 2 );
    XCTAssertFalse( (OBJ_NIL == pObj) );
    if (pObj) {
        pNodeA = node_NewWithUTF8Con("A", OBJ_NIL);
        XCTAssertFalse( (OBJ_NIL == pNodeA) );
        pNodeB = node_NewWithUTF8Con("B", OBJ_NIL);
        XCTAssertFalse( (OBJ_NIL == pNodeB) );
        pNodeC = node_NewWithUTF8Con("C", OBJ_NIL);
        XCTAssertFalse( (OBJ_NIL == pNodeA) );
        pNodeD = node_NewWithUTF8Con("D", OBJ_NIL);
        XCTAssertFalse( (OBJ_NIL == pNodeD) );
        pNodeE = node_NewWithUTF8Con("E", OBJ_NIL);
        XCTAssertFalse( (OBJ_NIL == pNodeE) );
        pNodeF = node_NewWithUTF8Con("F", OBJ_NIL);
        XCTAssertFalse( (OBJ_NIL == pNodeF) );
        pNodeG = node_NewWithUTF8Con("G", OBJ_NIL);
        XCTAssertFalse( (OBJ_NIL == pNodeG) );
        pNodeH = node_NewWithUTF8Con("H", OBJ_NIL);
        XCTAssertFalse( (OBJ_NIL == pNodeH) );
        pNodeI = node_NewWithUTF8Con("I", OBJ_NIL);
        XCTAssertFalse( (OBJ_NIL == pNodeI) );
        pNodeJ = node_NewWithUTF8Con("J", OBJ_NIL);
        XCTAssertFalse( (OBJ_NIL == pNodeJ) );
        
        fprintf(stderr, "\n\nCreate the tree(B=2):\n");
        fprintf(stderr, "(Only 2 children at each level per node!)\n");
        fprintf(stderr, "(first_child_index = (B * parent_index) - (B - 2))\n");
        fprintf(stderr, "A            1\n");
        fprintf(stderr, "--B          2\n");
        fprintf(stderr, "----D        4\n");
        fprintf(stderr, "----E        5\n");
        fprintf(stderr, "--C          3\n");
        fprintf(stderr, "----F        6\n");
        fprintf(stderr, "------H     12\n");
        fprintf(stderr, "------I     13\n");
        fprintf(stderr, "----G        7\n");
        fprintf(stderr, "------J     14\n");
        index = nodeATree_ChildAdd(pObj, 0, 0, pNodeA);
        XCTAssertTrue( (index == 1) );
        XCTAssertTrue( (nodeATree_getLastError(pObj) == ERESULT_SUCCESS) );
        
        index = nodeATree_ChildAdd(pObj, 1, 0, pNodeB);
        XCTAssertTrue( (index == 2) );
        XCTAssertTrue( (nodeATree_getLastError(pObj) == ERESULT_SUCCESS) );
        index = nodeATree_ChildAdd(pObj, 1, 1, pNodeC);
        XCTAssertTrue( (index == 3) );
        XCTAssertTrue( (nodeATree_getLastError(pObj) == ERESULT_SUCCESS) );
        
        index = nodeATree_ChildAdd(pObj, 2, 0, pNodeD);
        XCTAssertTrue( (index == 4) );
        XCTAssertTrue( (nodeATree_getLastError(pObj) == ERESULT_SUCCESS) );
        index = nodeATree_ChildAdd(pObj, 2, 1, pNodeE);
        XCTAssertTrue( (index == 5) );
        XCTAssertTrue( (nodeATree_getLastError(pObj) == ERESULT_SUCCESS) );
        
        index = nodeATree_ChildAdd(pObj, 3, 0, pNodeF);
        XCTAssertTrue( (index == 6) );
        XCTAssertTrue( (nodeATree_getLastError(pObj) == ERESULT_SUCCESS) );
        index = nodeATree_ChildAdd(pObj, 3, 1, pNodeG);
        XCTAssertTrue( (index == 7) );
        XCTAssertTrue( (nodeATree_getLastError(pObj) == ERESULT_SUCCESS) );
        
        index = nodeATree_ChildAdd(pObj, 6, 0, pNodeH);
        XCTAssertTrue( (index == 12) );
        XCTAssertTrue( (nodeATree_getLastError(pObj) == ERESULT_SUCCESS) );
        index = nodeATree_ChildAdd(pObj, 6, 1, pNodeI);
        XCTAssertTrue( (index == 13) );
        XCTAssertTrue( (nodeATree_getLastError(pObj) == ERESULT_SUCCESS) );
        
        index = nodeATree_ChildAdd(pObj, 7, 0, pNodeJ);
        XCTAssertTrue( (index == 14) );
        XCTAssertTrue( (nodeATree_getLastError(pObj) == ERESULT_SUCCESS) );
        
        pArray = nodeATree_ToLinearizationPre(pObj);
        XCTAssertFalse( (OBJ_NIL == pArray) );
        iMax = nodeArray_getSize(pArray);
        fprintf(stderr, "iMax = %d\n", iMax);
        XCTAssertTrue( (32 == iMax) );
        fprintf(stderr, "\nLinearization Preorder(%d):\n   ",iMax);
        fprintf(stderr, "\tShould be: (A(B(D()E())C(F(H()I())G(J()))))\n");
        for (i=1; i<=iMax; ++i) {
            pStrA = node_getNameUTF8(nodeArray_Get(pArray, i));
            fprintf(stderr, "%s", pStrA);
            mem_Free((void *)pStrA);
        }
        pStrA = NULL;
        fprintf(stderr, "\n\n");
        obj_Release(pArray);
        pArray = OBJ_NIL;
        
        fprintf(stderr, "\nVisit Preorder:\n   ");
        ppVisit = pPreorder;
        eRc = nodeATree_VisitPreorder(pObj, nodeVisitor, NULL);
        fprintf(stderr, "\n\n");
        XCTAssertTrue( (eRc == ERESULT_SUCCESS) );
        
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
        obj_Release(pObj);
        pObj = OBJ_NIL;
    }

}



@end



