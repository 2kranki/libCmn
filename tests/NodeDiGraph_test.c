// vi:nu:et:sts=4 ts=4 sw=4
/*
 *	Generated 12/14/2019 14:40:22
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
#include    <NodeDiGraph_internal.h>



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






int             test_NodeDiGraph_OpenClose(
    const
    char            *pTestName
)
{
    ERESULT         eRc = ERESULT_SUCCESS;
    NODEDIGRAPH_DATA	    *pObj = OBJ_NIL;
   
    fprintf(stderr, "Performing: %s\n", pTestName);

    pObj = NodeDiGraph_Alloc( );
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    pObj = NodeDiGraph_Init( pObj );
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    if (pObj) {

        //obj_TraceSet(pObj, true);       
        
        // Test something.
        TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );

        obj_Release(pObj);
        pObj = OBJ_NIL;
    }

    fprintf(stderr, "...%s completed.\n\n", pTestName);
    return 1;
}



/* Simple01 is taken from "Data Structures Using C", Tenenbaum et al,
 * Prentice Hall, 1990
 */
int         test_NodeDiGraph_Simple01(
    const
    char        *pTestName
)
{
    NODEDIGRAPH_DATA *pObj = OBJ_NIL;
    NODE_DATA       *pFrom;
    NODE_DATA       *pTo;
    NODEARC_DATA    *pArc;
    ERESULT         eRc;
    
    fprintf(stderr, "Performing: %s\n", pTestName);
    
    pObj = NodeDiGraph_Alloc( );
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    pObj = NodeDiGraph_Init( pObj );
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    if (pObj) {
        
        eRc = NodeDiGraph_NodeAddA(pObj, 0, "A", OBJ_NIL);
        TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );
        eRc = NodeDiGraph_NodeAddA(pObj, 0, "B", OBJ_NIL);
        TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );
        eRc = NodeDiGraph_NodeAddA(pObj, 0, "C", OBJ_NIL);
        TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );
        eRc = NodeDiGraph_NodeAddA(pObj, 0, "D", OBJ_NIL);
        TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );
        eRc = NodeDiGraph_NodeAddA(pObj, 0, "E", OBJ_NIL);
        TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );

        pFrom = NodeDiGraph_NodeFindA(pObj, 0, "B");
        TINYTEST_FALSE( (OBJ_NIL == pFrom) );
        pTo = NodeDiGraph_NodeFindA(pObj, 0, "C");
        TINYTEST_FALSE( (OBJ_NIL == pTo) );
        pArc = NodeDiGraph_ArcAddNodes(pObj, pFrom, pTo, 0);
        TINYTEST_FALSE( (OBJ_NIL == pArc) );

        pFrom = NodeDiGraph_NodeFindA(pObj, 0, "A");
        TINYTEST_FALSE( (OBJ_NIL == pFrom) );
        pTo = NodeDiGraph_NodeFindA(pObj, 0, "C");
        TINYTEST_FALSE( (OBJ_NIL == pTo) );
        pArc = NodeDiGraph_ArcAddNodes(pObj, pFrom, pTo, 0);
        TINYTEST_FALSE( (OBJ_NIL == pArc) );

        pFrom = NodeDiGraph_NodeFindA(pObj, 0, "A");
        TINYTEST_FALSE( (OBJ_NIL == pFrom) );
        pTo = NodeDiGraph_NodeFindA(pObj, 0, "D");
        TINYTEST_FALSE( (OBJ_NIL == pTo) );
        pArc = NodeDiGraph_ArcAddNodes(pObj, pFrom, pTo, 0);
        TINYTEST_FALSE( (OBJ_NIL == pArc) );

        pFrom = NodeDiGraph_NodeFindA(pObj, 0, "C");
        TINYTEST_FALSE( (OBJ_NIL == pFrom) );
        pTo = NodeDiGraph_NodeFindA(pObj, 0, "D");
        TINYTEST_FALSE( (OBJ_NIL == pTo) );
        pArc = NodeDiGraph_ArcAddNodes(pObj, pFrom, pTo, 0);
        TINYTEST_FALSE( (OBJ_NIL == pArc) );

        pFrom = NodeDiGraph_NodeFindA(pObj, 0, "C");
        TINYTEST_FALSE( (OBJ_NIL == pFrom) );
        pTo = NodeDiGraph_NodeFindA(pObj, 0, "E");
        TINYTEST_FALSE( (OBJ_NIL == pTo) );
        pArc = NodeDiGraph_ArcAddNodes(pObj, pFrom, pTo, 0);
        TINYTEST_FALSE( (OBJ_NIL == pArc) );

        pFrom = NodeDiGraph_NodeFindA(pObj, 0, "D");
        TINYTEST_FALSE( (OBJ_NIL == pFrom) );
        pTo = NodeDiGraph_NodeFindA(pObj, 0, "E");
        TINYTEST_FALSE( (OBJ_NIL == pTo) );
        pArc = NodeDiGraph_ArcAddNodes(pObj, pFrom, pTo, 0);
        TINYTEST_FALSE( (OBJ_NIL == pArc) );

        pFrom = NodeDiGraph_NodeFindA(pObj, 0, "E");
        TINYTEST_FALSE( (OBJ_NIL == pFrom) );
        pTo = NodeDiGraph_NodeFindA(pObj, 0, "D");
        TINYTEST_FALSE( (OBJ_NIL == pTo) );
        pArc = NodeDiGraph_ArcAddNodes(pObj, pFrom, pTo, 0);
        TINYTEST_FALSE( (OBJ_NIL == pArc) );

        obj_Release(pObj);
        pObj = OBJ_NIL;
    }
    
    fprintf(stderr, "...%s completed.\n", pTestName);
    return 1;
}




TINYTEST_START_SUITE(test_NodeDiGraph);
    TINYTEST_ADD_TEST(test_NodeDiGraph_Simple01,setUp,tearDown);
    TINYTEST_ADD_TEST(test_NodeDiGraph_OpenClose,setUp,tearDown);
TINYTEST_END_SUITE();

TINYTEST_MAIN_SINGLE_SUITE(test_NodeDiGraph);





