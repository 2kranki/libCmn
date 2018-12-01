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
#include    <nodeGraph_internal.h>



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






int         test_nodeGraph_OpenClose(
    const
    char        *pTestName
)
{
    NODEGRAPH_DATA *pObj = OBJ_NIL;
   
    fprintf(stderr, "Performing: %s\n", pTestName);
    
    pObj = nodeGraph_Alloc( );
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    pObj = nodeGraph_Init( pObj );
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    if (pObj) {

        // Test something.

        obj_Release(pObj);
        pObj = OBJ_NIL;
    }

    fprintf(stderr, "...%s completed.\n", pTestName);
    return 1;
}



int         test_nodeGraph_Simple01(
    const
    char        *pTestName
)
{
    NODEGRAPH_DATA *pObj = OBJ_NIL;
    ERESULT     eRc;
    
    fprintf(stderr, "Performing: %s\n", pTestName);
    
    pObj = nodeGraph_Alloc( );
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    pObj = nodeGraph_Init( pObj );
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    if (pObj) {
        
        eRc = nodeGraph_NodeAddA(pObj, 0, "1", OBJ_NIL);
        TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );
        eRc = nodeGraph_NodeAddA(pObj, 0, "2", OBJ_NIL);
        TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );
        eRc = nodeGraph_NodeAddA(pObj, 0, "3", OBJ_NIL);
        TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );
        eRc = nodeGraph_NodeAddA(pObj, 0, "4", OBJ_NIL);
        TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );

        obj_Release(pObj);
        pObj = OBJ_NIL;
    }
    
    fprintf(stderr, "...%s completed.\n", pTestName);
    return 1;
}




TINYTEST_START_SUITE(test_nodeGraph);
    TINYTEST_ADD_TEST(test_nodeGraph_Simple01,setUp,tearDown);
    TINYTEST_ADD_TEST(test_nodeGraph_OpenClose,setUp,tearDown);
TINYTEST_END_SUITE();

TINYTEST_MAIN_SINGLE_SUITE(test_nodeGraph);





