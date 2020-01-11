// vi:nu:et:sts=4 ts=4 sw=4
/*
 *	Generated 01/10/2020 16:43:13
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
//#include    <szTbl.h>
#include    <trace.h>
#include    <NodeBT_internal.h>



static
ERESULT         printNode(
    OBJ_ID          pObj,
    NODE_DATA       *pNode,
    void            *pArg3
)
{
    char            *pNameA;

    pNameA = node_getNameUTF8(pNode);
    if (pNameA) {
        fprintf(stderr, "%s", pNameA);
        mem_Free(pNameA);
    }
    return ERESULT_SUCCESS;
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

    //szTbl_SharedReset( );
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






int             test_NodeBT_OpenClose (
    const
    char            *pTestName
)
{
    ERESULT         eRc = ERESULT_SUCCESS;
    NODEBT_DATA	    *pObj = OBJ_NIL;
    bool            fRc;
   
    fprintf(stderr, "Performing: %s\n", pTestName);

    pObj = NodeBT_Alloc( );
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    pObj = NodeBT_Init( pObj );
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    if (pObj) {

        //obj_TraceSet(pObj, true);       
        fRc = obj_IsKindOf(pObj, OBJ_IDENT_NODEBT);
        TINYTEST_TRUE( (fRc) );
        
        // Test something.
        TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );

        obj_Release(pObj);
        pObj = OBJ_NIL;
    }

    fprintf(stderr, "...%s completed.\n\n\n", pTestName);
    return 1;
}



int             test_NodeBT_Test01 (
    const
    char            *pTestName
)
{
    ERESULT         eRc = ERESULT_SUCCESS;
    NODEBT_DATA	    *pTree = OBJ_NIL;
    bool            fRc;
    const
    char            *pStrA = "A";
    const
    char            *pStrP = pStrA;
    char            strA[2] = {0};
    NODE_DATA       *pNode = OBJ_NIL;
    NODE_DATA       *pFound = OBJ_NIL;

    fprintf(stderr, "Performing: %s\n", pTestName);

    pTree = NodeBT_New( );
    TINYTEST_FALSE( (OBJ_NIL == pTree) );
    if (pTree) {

        //obj_TraceSet(pObj, true);       
        fRc = obj_IsKindOf(pTree, OBJ_IDENT_NODEBT);
        TINYTEST_TRUE( (fRc) );

        strA[0] = 'A';
        pNode = node_NewWithUTF8AndClass(0, strA, OBJ_NIL);
        TINYTEST_FALSE( (OBJ_NIL == pNode) );
        if (pNode) {

            eRc = NodeBT_Add(pTree, pNode, false);
            TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );
            fprintf(stderr, "\tAdded %p - %s\n", pNode, strA);

            eRc = NodeBT_VerifyTree(pTree);
            TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );
            fprintf(stderr, "\tLooking for: %s\n", strA);

            pFound = NodeBT_Find(pTree, pNode);
            TINYTEST_FALSE( (OBJ_NIL == pFound) );
            fprintf(stderr, "\t\tFound\n");
            
            obj_Release(pNode);
            pNode = OBJ_NIL;
        }

        obj_Release(pTree);
        pTree = OBJ_NIL;
    }

    fprintf(stderr, "...%s completed.\n\n\n", pTestName);
    return 1;
}



int             test_NodeBT_Add01(
    const
    char            *pTestName
)
{
    NODEBT_DATA     *pTree = OBJ_NIL;
    NODE_DATA       *pNode = OBJ_NIL;
    NODE_DATA       *pFound = OBJ_NIL;
    NODE_DATA       *pEntry = NULL;
    ERESULT         eRc;
    bool            fRc;
    const
    char            *pStrA = "ABCDEFG";
    const
    char            *pStrP = pStrA;
    char            strA[2] = {0};
    ASTR_DATA       *pStr = OBJ_NIL;

    fprintf(stderr, "Performing: %s\n", pTestName);
    fprintf(stderr, "\tGenerate a right degenerate tree (ie worst case)\n\n");

    pTree = NodeBT_Alloc( );
    TINYTEST_FALSE( (OBJ_NIL == pTree) );
    pTree = NodeBT_Init( pTree );
    TINYTEST_FALSE( (OBJ_NIL == pTree) );
    if (pTree) {

        pStrP = pStrA;
        while (*pStrP) {
            strA[0] = *pStrP;
            pNode = node_NewWithUTF8AndClass(0, strA, OBJ_NIL);
            TINYTEST_FALSE( (OBJ_NIL == pNode) );
            if (pNode) {
                eRc = NodeBT_Add(pTree, pNode, false);
                TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );
                fprintf(stderr, "\tAdded %p - %s\n", pNode, strA);
                eRc = NodeBT_VerifyTree(pTree);
                TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );
                fprintf(stderr, "\tLooking for: %s\n", strA);
                pFound = NodeBT_Find(pTree, pNode);
                TINYTEST_FALSE( (OBJ_NIL == pFound) );
                fprintf(stderr, "\t\tFound\n");
                obj_Release(pNode);
                pNode = OBJ_NIL;
            }
            ++pStrP;
        }
        fprintf(stderr, "\n\n");

        pStrP = pStrA;
        while (*pStrP) {
            strA[0] = *pStrP;
            pNode = node_NewWithUTF8AndClass(0, strA, OBJ_NIL);
            TINYTEST_FALSE( (OBJ_NIL == pNode) );
            if (pNode) {
                fprintf(stderr, "\tLooking for: %s\n", strA);
                pFound = NodeBT_Find(pTree, pNode);
                TINYTEST_FALSE( (OBJ_NIL == pFound) );
                fprintf(stderr, "\t\tFound\n");
                obj_Release(pNode);
                pNode = OBJ_NIL;
            }
            ++pStrP;
        }
        fprintf(stderr, "\n\n");

        fprintf(stderr, "\tPre-Order Recurse: BADCFEG\n\t      Recurse Got: ");
        eRc = NodeBT_VisitNodesPreRecurse(pTree, (void *)printNode, OBJ_NIL, NULL);
        fprintf(stderr, "\n\n");

        fprintf(stderr, "\tIn-Order Recurse: ABCDEFG\n\t     Recurse Got: ");
        eRc = NodeBT_VisitNodesInRecurse(pTree, (void *)printNode, OBJ_NIL, NULL);
        fprintf(stderr, "\n\n");

        fprintf(stderr, "\tPost-Order Recurse: ACEGFDB\n\t       Recurse Got: ");
        eRc = NodeBT_VisitNodesPostRecurse(pTree, (void *)printNode, OBJ_NIL, NULL);
        fprintf(stderr, "\n\n");

        pStr = NodeBT_ToDebugString(pTree, 4);
        fprintf(stderr, "%s\n\n\n", AStr_getData(pStr));
        obj_Release(pStr);
        pStr = OBJ_NIL;

        obj_Release(pTree);
        pTree = OBJ_NIL;
    }

    fprintf(stderr, "...%s completed.\n\n\n\n", pTestName);
    return 1;
}



int             test_NodeBT_Add02(
    const
    char            *pTestName
)
{
    NODEBT_DATA     *pTree = OBJ_NIL;
    NODE_DATA       *pNode = OBJ_NIL;
    NODE_DATA       *pFound = OBJ_NIL;
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

    pTree = NodeBT_Alloc( );
    TINYTEST_FALSE( (OBJ_NIL == pTree) );
    pTree = NodeBT_Init( pTree );
    TINYTEST_FALSE( (OBJ_NIL == pTree) );
    if (pTree) {

        pStrP = pStrA;
        while (*pStrP) {
            strA[0] = *pStrP;
            pNode = node_NewWithUTF8AndClass(0, strA, OBJ_NIL);
            TINYTEST_FALSE( (OBJ_NIL == pNode) );
            if (pNode) {
                eRc = NodeBT_Add(pTree, pNode, false);
                TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );
                fprintf(stderr, "\tAdded %p - %s\n", pNode, strA);
                fprintf(stderr, "\tLooking for: %s\n", strA);
                pFound = NodeBT_Find(pTree, pNode);
                TINYTEST_FALSE( (OBJ_NIL == pFound) );
                fprintf(stderr, "\t\tFound\n");
                obj_Release(pNode);
                pNode = OBJ_NIL;
            }
            ++pStrP;
        }
        fprintf(stderr, "\n\n");

        pStrP = pStrA;
        while (*pStrP) {
            strA[0] = *pStrP;
            pNode = node_NewWithUTF8AndClass(0, strA, OBJ_NIL);
            TINYTEST_FALSE( (OBJ_NIL == pNode) );
            if (pNode) {
                fprintf(stderr, "\tLooking for: %s\n", strA);
                pFound = NodeBT_Find(pTree, pNode);
                TINYTEST_FALSE( (OBJ_NIL == pFound) );
                fprintf(stderr, "\t\tFound\n");
                obj_Release(pNode);
                pNode = OBJ_NIL;
            }
            ++pStrP;
        }
        fprintf(stderr, "\n\n");


        fprintf(stderr, "\tPre-Order Recurse: DBACFEG\n\t      Recurse Got: ");
        eRc = NodeBT_VisitNodesPreRecurse(pTree, (void *)printNode, OBJ_NIL, NULL);
        fprintf(stderr, "\n\n");

        fprintf(stderr, "\tIn-Order Recurse: ABCDEFG\n\t     Recurse Got: ");
        eRc = NodeBT_VisitNodesInRecurse(pTree, (void *)printNode, OBJ_NIL, NULL);
        fprintf(stderr, "\n\n");

        fprintf(stderr, "\tPost-Order Recurse: ACBEGFD\n\t       Recurse Got: ");
        eRc = NodeBT_VisitNodesPostRecurse(pTree, (void *)printNode, OBJ_NIL, NULL);
        fprintf(stderr, "\n\n");

        pStr = NodeBT_ToDebugString(pTree, 4);
        fprintf(stderr, "%s\n\n\n", AStr_getData(pStr));
        obj_Release(pStr);
        pStr = OBJ_NIL;

        obj_Release(pTree);
        pTree = OBJ_NIL;
    }

    fprintf(stderr, "...%s completed.\n\n\n\n", pTestName);
    return 1;
}




TINYTEST_START_SUITE(test_NodeBT);
    TINYTEST_ADD_TEST(test_NodeBT_Add02,setUp,tearDown);
    TINYTEST_ADD_TEST(test_NodeBT_Add01,setUp,tearDown);
    TINYTEST_ADD_TEST(test_NodeBT_Test01,setUp,tearDown);
    TINYTEST_ADD_TEST(test_NodeBT_OpenClose,setUp,tearDown);
TINYTEST_END_SUITE();

TINYTEST_MAIN_SINGLE_SUITE(test_NodeBT);





