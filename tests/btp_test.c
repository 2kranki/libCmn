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
#include    <btp_internal.h>



#include    <str.h>

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






int         test_btp_OpenClose(
    const
    char        *pTestName
)
{
    BTP_DATA	*pObj = OBJ_NIL;
    bool            fRc;
   
    fprintf(stderr, "Performing: %s\n", pTestName);
    
    pObj = btp_Alloc( );
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    pObj = btp_Init( pObj, (P_BTP_COMPARE)str_Compare );
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    if (pObj) {

        fRc = btp_Add( pObj, "abc");
        XCTAssertTrue( (fRc ) );
        fRc = btp_Add( pObj, "def");
        XCTAssertTrue( (fRc ) );

        obj_Release(pObj);
        pObj = OBJ_NIL;
    }

    fprintf(stderr, "...%s completed.\n", pTestName);
    return 1;
}



int         test_btp_Tree01(
    const
    char        *pTestName
)
{
	BTP_DATA        *pTree;
    bool            fRc;
    
    fprintf(stderr, "Performing: %s\n", pTestName);
    
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
    
    fprintf(stderr, "...%s completed.\n", pTestName);
    return 1;
}



int         test_btp_Tree02(
    const
    char        *pTestName
)
{
	BTP_DATA        *pTree;
    bool            fRc;
    
    fprintf(stderr, "Performing: %s\n", pTestName);
    
    pTree = create_Tree02();
    XCTAssertFalse( (NULL == pTree) );
    
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
    
    fprintf(stderr, "...%s completed.\n", pTestName);
    return 1;
}




TINYTEST_START_SUITE(test_btp);
  TINYTEST_ADD_TEST(test_btp_Tree02,setUp,tearDown);
  TINYTEST_ADD_TEST(test_btp_Tree01,setUp,tearDown);
  TINYTEST_ADD_TEST(test_btp_OpenClose,setUp,tearDown);
TINYTEST_END_SUITE();

TINYTEST_MAIN_SINGLE_SUITE(test_btp);





