
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
//      STAssert(expression, failure_description, ...)
//      STFail(failure_description, ...)
//      STAssertEqualObjects(object_1, object_2, failure_description, ...) uses isEqualTo:
//      STAssertEquals(value_1, value_2, failure_description, ...)
//      STAssertEqualsWithAccuracy(value_1, value_2, accuracy, failure_description, ...)
//      STAssertNil(expression, failure_description, ...)
//      STAssertNotNil(expression, failure_description, ...)
//      STAssertTrue(expression, failure_description, ...)
//      STAssertFalse(expression, failure_description, ...)
//      STAssertThrows(expression, failure_description, ...)
//      STAssertThrowsSpecific(expression, exception_class, failure_description, ...)
//      STAssertThrowsSpecificNamed(expression, exception_class, exception_name, failure_description, ...)
//      STAssertNoThrow(expression, failure_description, ...)
//      STAssertNoThrowSpecific(expression, exception_class, failure_description, ...)
//      STAssertNoThrowSpecificNamed(expression, exception_class, exception_name, failure_description, ...)


#include    "cmn_defs.h"
#include    "btp.h"
#include    "btp_internal.h"
#include    "str.h"

/*  Tree01
 
                        A
                       / \
                      B   C
                     /   / \
                    D   E   F
                    \   / \
                     G H  I
 
 Preorder:  ABDGCEHIF
 Inorder:   DGBAHEICF
 Postorder: GDBHIEFCA
 */

char        *tree01_preorder  = "ABDGCEHIF";
char        *tree01_inorder   = "DGBAHEICF";
char        *tree01_postorder = "GDBHIEFCA";


BTP_DATA *      create_Tree01()
{
	BTP_DATA        *pTree;
	BTP_NODE        *pNode;
    
    pTree = btp_Alloc();
    pTree = btp_Init( pTree, (P_BTP_COMPARE)str_Compare );
    if (pTree) {
        pNode = btp_MakeNode(pTree, "A");
        pTree->pTree = pNode;
        ++pTree->num;
        pNode = btp_SetLeftNode(pTree, pNode, "B");
        ++pTree->num;
        pNode = btp_SetLeftNode(pTree, pNode, "D");
        ++pTree->num;
        pNode = btp_SetRightNode(pTree, pNode, "G");
        ++pTree->num;
        pNode = pTree->pTree;
        pNode = btp_SetRightNode(pTree, pNode, "C");
        ++pTree->num;
        pNode = btp_SetRightNode(pTree, pNode, "F");
        ++pTree->num;
        pNode = pNode->pParent;
        pNode = btp_SetLeftNode(pTree, pNode, "E");
        ++pTree->num;
        pNode = btp_SetLeftNode(pTree, pNode, "H");
        ++pTree->num;
        pNode = pNode->pParent;
        pNode = btp_SetRightNode(pTree, pNode, "I");
        ++pTree->num;
    }
    
    return pTree;
}




/*  Tree02
 
                                        A
                                       /
                                      B
                                    /  \
                                   /    \
                                  /      D
                                 C      / \
                                / \    G   H
                               /   F      / \
                              E     \    K   L
                               \     J
                                I
 
 
 Preorder:  ABCEIFJDGHKL
 Inorder:   EICFJBGDKHLA
 Postorder: IEJFCGKLHDBA
 */

char        *tree02_preorder  = "ABCEIFJDGHKL";
char        *tree02_inorder   = "EICFJBGDKHLA";
char        *tree02_postorder = "IEJFCGKLHDBA";


BTP_DATA *      create_Tree02()
{
	BTP_DATA        *pTree;
	BTP_NODE        *pNode;
    
    pTree = btp_Alloc();
    pTree = btp_Init( pTree, (P_BTP_COMPARE)str_Compare );
    if (pTree) {
        pNode = btp_MakeNode(pTree, "A");
        pTree->pTree = pNode;
        ++pTree->num;
        pNode = btp_SetLeftNode(pTree, pNode, "B");
        ++pTree->num;
        pNode = btp_SetLeftNode(pTree, pNode, "C");
        ++pTree->num;
        pNode = btp_SetLeftNode(pTree, pNode, "E");
        ++pTree->num;
        pNode = btp_SetRightNode(pTree, pNode, "I");
        ++pTree->num;
        pNode = pNode->pParent;
        pNode = pNode->pParent;
        pNode = btp_SetRightNode(pTree, pNode, "F");
        ++pTree->num;
        pNode = btp_SetRightNode(pTree, pNode, "J");
        ++pTree->num;
        pNode = pTree->pTree;
        pNode = pNode->pLeft;
        pNode = btp_SetRightNode(pTree, pNode, "D");
        ++pTree->num;
        pNode = btp_SetLeftNode(pTree, pNode, "G");
        ++pTree->num;
        pNode = pNode->pParent;
        pNode = btp_SetRightNode(pTree, pNode, "H");
        ++pTree->num;
        btp_SetLeftNode(pTree, pNode, "K");
        ++pTree->num;
        btp_SetRightNode(pTree, pNode, "L");
        ++pTree->num;
    }
    
    return pTree;
}






char        *pCheck =  NULL;

bool        visitData(BTP_DATA *cbp,const void *pData)
{
    fprintf(stderr, "visitData: %c\n", (*(char *)pData) );
    if ( (*(char *)pData) == *pCheck ) {
        ++pCheck;
        return true;
    }
    return false;
}


bool        visitNode(BTP_DATA *cbp,BTP_NODE *pNode)
{
    fprintf(stderr, "visitData: %c\n", (*(char *)pNode->pData) );
    if ( (*(char *)pNode->pData) == *pCheck ) {
        ++pCheck;
        return true;
    }
    return false;
}








@interface btpTests : XCTestCase

@end

@implementation btpTests


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



- (void)testOpenClose_1
{
	BTP_DATA        *pTree;
    bool            fRc;

    pTree = btp_Alloc();
    pTree = btp_Init( pTree, (P_BTP_COMPARE)str_Compare );
    XCTAssertFalse( (NULL == pTree) );

    if (pTree) {
        fRc = btp_Add( pTree, "abc");
        XCTAssertTrue( (fRc ) );
        fRc = btp_Add( pTree, "def");
        XCTAssertTrue( (fRc ) );

        obj_Release(pTree);
        pTree = NULL;
    }

}



- (void)testTree01
{
	BTP_DATA        *pTree;
    bool            fRc;
    
    pTree = create_Tree01();
    XCTAssertFalse( (NULL == pTree) );
    
    if (pTree) {
        pCheck = tree01_inorder;
        fprintf(stderr, "testTree01(inorder): %s\n", pCheck );
        fRc = btp_VisitInorder(pTree, visitData);
        XCTAssertTrue( (fRc ) );
        pCheck = tree01_postorder;
        fprintf(stderr, "testTree01(postorder): %s\n", pCheck );
        fRc = btp_VisitNodePostorderRecursive(pTree, pTree->pTree, visitNode);
        XCTAssertTrue( (fRc ) );
        pCheck = tree01_preorder;
        fprintf(stderr, "testTree01(preorder): %s\n", pCheck );
        fRc = btp_VisitNodePreorderRecursive(pTree, pTree->pTree, visitNode);
        XCTAssertTrue( (fRc ) );
        
        obj_Release(pTree);
        pTree = NULL;
    }
    
}



- (void)testTree02
{
	BTP_DATA        *pTree;
    bool            fRc;
    
    pTree = create_Tree02();
    XCTAssertFalse( (NULL == pTree), @"Could not open()" );
    
    if (pTree) {
        pCheck = tree02_inorder;
        fprintf(stderr, "testTree01(inorder): %s\n", pCheck );
        fRc = btp_VisitInorder(pTree, visitData);
        XCTAssertTrue( (fRc ) );
        pCheck = tree02_postorder;
        fprintf(stderr, "testTree01(postorder): %s\n", pCheck );
        fRc = btp_VisitNodePostorderRecursive(pTree, pTree->pTree, visitNode);
        XCTAssertTrue( (fRc ) );
        pCheck = tree02_preorder;
        fprintf(stderr, "testTree01(preorder): %s\n", pCheck );
        fRc = btp_VisitNodePreorderRecursive(pTree, pTree->pTree, visitNode);
        XCTAssertTrue( (fRc ) );
        
        obj_Release(pTree);
        pTree = NULL;
    }
    
}



@end



