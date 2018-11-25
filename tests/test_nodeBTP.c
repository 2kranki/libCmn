/*
 *	Generated 11/22/2018 23:21:01
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
#include    <nodeBTP_internal.h>



static
ERESULT         printNode(
    OBJ_ID          pObj,
    NODE_DATA       *pNode,
    void            *pArg3
)
{
    char            *pNameA;
    
    pNameA = node_getNameUTF8((NODE_DATA *)pNode);
    if (pNameA) {
        fprintf(stderr, "%s", pNameA);
        mem_Free(pNameA);
    }
    return ERESULT_SUCCESS;
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






int             test_nodeBTP_OpenClose(
    const
    char            *pTestName
)
{
    NODEBTP_DATA	    *pObj = OBJ_NIL;
   
    fprintf(stderr, "Performing: %s\n", pTestName);

    pObj = nodeBTP_Alloc( );
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    pObj = nodeBTP_Init( pObj );
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    if (pObj) {

        // Test something.

        obj_Release(pObj);
        pObj = OBJ_NIL;
    }

    fprintf(stderr, "...%s completed.\n\n", pTestName);
    return 1;
}



int             test_nodeBTP_Add01(
    const
    char            *pTestName
)
{
    NODEBTP_DATA    *pTree = OBJ_NIL;
    NODE_DATA       *pNode = OBJ_NIL;
    NODE_DATA       *pEntry = NULL;
    ERESULT         eRc;
    const
    char            *pStrA = "ABCDEFG";
    const
    char            *pStrP = pStrA;
    char            strA[2] = {0};
    ASTR_DATA       *pStr = OBJ_NIL;
    
    fprintf(stderr, "Performing: %s\n", pTestName);
    fprintf(stderr, "\tGenerate a right degenerate tree (ie worst case)\n\n");

    pTree = nodeBTP_Alloc( );
    TINYTEST_FALSE( (OBJ_NIL == pTree) );
    pTree = nodeBTP_Init( pTree );
    TINYTEST_FALSE( (OBJ_NIL == pTree) );
    if (pTree) {
        
        while (*pStrP) {
            strA[0] = *pStrP;
            pNode = node_NewWithUTF8AndClass(strA, 0, OBJ_NIL);
            TINYTEST_FALSE( (OBJ_NIL == pNode) );
            if (pNode) {
                eRc = nodeBTP_Add(pTree, pNode, false);
                TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );
                fprintf(stderr, "\tAdded %s\n", strA);
                obj_Release(pNode);
                pNode = OBJ_NIL;
            }
            ++pStrP;
        }
        fprintf(stderr, "\n\n");
        
        fprintf(stderr, "\tPre-Order Recurse: ABCDEFG\n\t      Recurse Got: ");
        eRc = nodeBTP_VisitNodesPreRecurse(pTree, (void *)printNode, OBJ_NIL, NULL);
        fprintf(stderr, "\n\n");
        
        fprintf(stderr, "\tIn-Order Recurse: ABCDEFG\n\t      Parent Got: ");
        eRc = nodeBTP_VisitNodesInParent(pTree, (void *)printNode, OBJ_NIL, NULL);
        fprintf(stderr, "\n\t     Recurse Got: ");
        eRc = nodeBTP_VisitNodesInRecurse(pTree, (void *)printNode, OBJ_NIL, NULL);
        fprintf(stderr, "\n\n");
        
        fprintf(stderr, "\tPost-Order Recurse: GFEDCBA\n\t       Recurse Got: ");
        eRc = nodeBTP_VisitNodesPostRecurse(pTree, (void *)printNode, OBJ_NIL, NULL);
        fprintf(stderr, "\n\n");

        pStr = nodeBTP_ToDebugString(pTree, 4);
        fprintf(stderr, "%s\n\n\n", AStr_getData(pStr));
        obj_Release(pStr);
        pStr = OBJ_NIL;
        
        obj_Release(pTree);
        pTree = OBJ_NIL;
    }
    
    fprintf(stderr, "...%s completed.\n\n\n\n", pTestName);
    return 1;
}



int             test_nodeBTP_Add02(
    const
    char            *pTestName
)
{
    NODEBTP_DATA    *pTree = OBJ_NIL;
    NODE_DATA       *pNode = OBJ_NIL;
    ERESULT         eRc;
    //              ABCDEFG
    const
    char            *pStrA = "DBFCGAE";
    const
    char            *pStrP = pStrA;
    char            strA[2] = {0};
    ASTR_DATA       *pStr = OBJ_NIL;
    
    fprintf(stderr, "Performing: %s\n", pTestName);
    fprintf(stderr, "\tGenerate a right degenerate tree\n\n");
    
    pTree = nodeBTP_Alloc( );
    TINYTEST_FALSE( (OBJ_NIL == pTree) );
    pTree = nodeBTP_Init( pTree );
    TINYTEST_FALSE( (OBJ_NIL == pTree) );
    if (pTree) {
        
        while (*pStrP) {
            strA[0] = *pStrP;
            pNode = node_NewWithUTF8AndClass(strA, 0, OBJ_NIL);
            TINYTEST_FALSE( (OBJ_NIL == pNode) );
            if (pNode) {
                eRc = nodeBTP_Add(pTree, pNode, false);
                TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );
                fprintf(stderr, "\tAdded %s\n", strA);
                obj_Release(pNode);
                pNode = OBJ_NIL;
            }
            ++pStrP;
        }
        fprintf(stderr, "\n\n");
        
        fprintf(stderr, "\tPre-Order Recurse: DBACFEG\n\t       Parent Got: ");
        //FIXME: eRc = nodeBTP_VisitNodesPreParent(pTree, (void *)printNode, OBJ_NIL, NULL);
        fprintf(stderr, "\n\t     Recurse Got: ");
        eRc = nodeBTP_VisitNodesPreRecurse(pTree, (void *)printNode, OBJ_NIL, NULL);
        fprintf(stderr, "\n\n");
        
        fprintf(stderr, "\tIn-Order Recurse: ABCDEFG\n\t      Parent Got: ");
        eRc = nodeBTP_VisitNodesInParent(pTree, (void *)printNode, OBJ_NIL, NULL);
        fprintf(stderr, "\n\t     Recurse Got: ");
        eRc = nodeBTP_VisitNodesInRecurse(pTree, (void *)printNode, OBJ_NIL, NULL);
        fprintf(stderr, "\n\n");
        
        fprintf(stderr, "\tPost-Order Recurse: ACBEGFD\n\t       Recurse Got: ");
        eRc = nodeBTP_VisitNodesPostRecurse(pTree, (void *)printNode, OBJ_NIL, NULL);
        fprintf(stderr, "\n\n");
        
        pStr = nodeBTP_ToDebugString(pTree, 4);
        fprintf(stderr, "%s\n\n\n", AStr_getData(pStr));
        obj_Release(pStr);
        pStr = OBJ_NIL;
        
        obj_Release(pTree);
        pTree = OBJ_NIL;
    }
    
    fprintf(stderr, "...%s completed.\n\n\n\n", pTestName);
    return 1;
}




TINYTEST_START_SUITE(test_nodeBTP);
    TINYTEST_ADD_TEST(test_nodeBTP_Add02,setUp,tearDown);
    TINYTEST_ADD_TEST(test_nodeBTP_Add01,setUp,tearDown);
    TINYTEST_ADD_TEST(test_nodeBTP_OpenClose,setUp,tearDown);
TINYTEST_END_SUITE();

TINYTEST_MAIN_SINGLE_SUITE(test_nodeBTP);





