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
#include    <NodeGraph_internal.h>



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






int         test_NodeGraph_OpenClose(
    const
    char        *pTestName
)
{
    NODEGRAPH_DATA *pObj = OBJ_NIL;
   
    fprintf(stderr, "Performing: %s\n", pTestName);
    
    pObj = NodeGraph_Alloc( );
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    pObj = NodeGraph_Init( pObj );
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    if (pObj) {

        // Test something.

        obj_Release(pObj);
        pObj = OBJ_NIL;
    }

    fprintf(stderr, "...%s completed.\n", pTestName);
    return 1;
}


/* Simple01 is taken from "Data Structures Using C", Tenenbaum et al,
 * Prentice Hall, 1990
 */
int         test_NodeGraph_Simple01(
    const
    char        *pTestName
)
{
    NODEGRAPH_DATA  *pObj = OBJ_NIL;
    NODE_DATA       *pFrom;
    NODE_DATA       *pTo;
    ERESULT         eRc;
    
    fprintf(stderr, "Performing: %s\n", pTestName);
    
    pObj = NodeGraph_Alloc( );
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    pObj = NodeGraph_Init( pObj );
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    if (pObj) {
        
        eRc = NodeGraph_NodeAddA(pObj, 0, "A", OBJ_NIL);
        TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );
        eRc = NodeGraph_NodeAddA(pObj, 0, "B", OBJ_NIL);
        TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );
        eRc = NodeGraph_NodeAddA(pObj, 0, "C", OBJ_NIL);
        TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );
        eRc = NodeGraph_NodeAddA(pObj, 0, "D", OBJ_NIL);
        TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );
        eRc = NodeGraph_NodeAddA(pObj, 0, "E", OBJ_NIL);
        TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );

        pFrom = NodeGraph_NodeFindA(pObj, 0, "B");
        TINYTEST_FALSE( (OBJ_NIL == pFrom) );
        pTo = NodeGraph_NodeFindA(pObj, 0, "C");
        TINYTEST_FALSE( (OBJ_NIL == pTo) );
        //FIXME: eRc = NodeGraph_ArcAdd(pObj, pFrom, pTo, "B->C");
        TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );

        pFrom = NodeGraph_NodeFindA(pObj, 0, "A");
        TINYTEST_FALSE( (OBJ_NIL == pFrom) );
        pTo = NodeGraph_NodeFindA(pObj, 0, "C");
        TINYTEST_FALSE( (OBJ_NIL == pTo) );
        //FIXME: eRc = NodeGraph_ArcAdd(pObj, pFrom, pTo, "A->C");
        TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );

        pFrom = NodeGraph_NodeFindA(pObj, 0, "A");
        TINYTEST_FALSE( (OBJ_NIL == pFrom) );
        pTo = NodeGraph_NodeFindA(pObj, 0, "D");
        TINYTEST_FALSE( (OBJ_NIL == pTo) );
        //FIXME: eRc = NodeGraph_ArcAdd(pObj, pFrom, pTo, "A->D");
        TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );

        pFrom = NodeGraph_NodeFindA(pObj, 0, "C");
        TINYTEST_FALSE( (OBJ_NIL == pFrom) );
        pTo = NodeGraph_NodeFindA(pObj, 0, "D");
        TINYTEST_FALSE( (OBJ_NIL == pTo) );
        //FIXME: eRc = NodeGraph_ArcAdd(pObj, pFrom, pTo, "C->D");
        TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );

        pFrom = NodeGraph_NodeFindA(pObj, 0, "C");
        TINYTEST_FALSE( (OBJ_NIL == pFrom) );
        pTo = NodeGraph_NodeFindA(pObj, 0, "E");
        TINYTEST_FALSE( (OBJ_NIL == pTo) );
        //FIXME: eRc = NodeGraph_ArcAdd(pObj, pFrom, pTo, "C->E");
        TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );

        pFrom = NodeGraph_NodeFindA(pObj, 0, "D");
        TINYTEST_FALSE( (OBJ_NIL == pFrom) );
        pTo = NodeGraph_NodeFindA(pObj, 0, "E");
        TINYTEST_FALSE( (OBJ_NIL == pTo) );
        //FIXME: eRc = NodeGraph_ArcAdd(pObj, pFrom, pTo, "D->E");
        TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );

        pFrom = NodeGraph_NodeFindA(pObj, 0, "E");
        TINYTEST_FALSE( (OBJ_NIL == pFrom) );
        pTo = NodeGraph_NodeFindA(pObj, 0, "D");
        TINYTEST_FALSE( (OBJ_NIL == pTo) );
        //FIXME: eRc = NodeGraph_ArcAdd(pObj, pFrom, pTo, "E->D");
        TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );

        obj_Release(pObj);
        pObj = OBJ_NIL;
    }
    
    fprintf(stderr, "...%s completed.\n", pTestName);
    return 1;
}




TINYTEST_START_SUITE(test_NodeGraph);
    TINYTEST_ADD_TEST(test_NodeGraph_Simple01,setUp,tearDown);
    TINYTEST_ADD_TEST(test_NodeGraph_OpenClose,setUp,tearDown);
TINYTEST_END_SUITE();

TINYTEST_MAIN_SINGLE_SUITE(test_NodeGraph);





