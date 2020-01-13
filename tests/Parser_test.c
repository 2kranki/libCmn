// vi:nu:et:sts=4 ts=4 sw=4
/*
 *	Generated 12/15/2019 15:07:38
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
#include    <Parser_internal.h>



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

    szTbl_SharedReset( );
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






int             test_Parser_OpenClose(
    const
    char            *pTestName
)
{
    ERESULT         eRc = ERESULT_SUCCESS;
    PARSER_DATA	    *pObj = OBJ_NIL;
   
    fprintf(stderr, "Performing: %s\n", pTestName);

    pObj = Parser_Alloc( );
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    pObj = Parser_Init( pObj );
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



int         test_Parser_Properties01(
    const
    char        *pTestName
)
{
    PARSER_DATA    *pObj = OBJ_NIL;
    NODE_DATA       *pNode;
    NODE_DATA       *pNode2;
    ERESULT         eRc;
   
    pObj = Parser_Alloc( );
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    pObj = Parser_Init(pObj);
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    if (pObj) {

        XCTAssertTrue( (0 == Parser_PropertyCount(pObj)) );
        pNode = Node_NewWithUTF8AndClass(0, "abc", OBJ_NIL);
        XCTAssertFalse( (OBJ_NIL == pObj) );
        eRc = Parser_PropertyAdd(pObj, pNode);
        XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
        XCTAssertTrue( (1 == Parser_PropertyCount(pObj)) );
        pNode2 = Parser_Property(pObj, "abc");
        XCTAssertTrue( (pNode == pNode2) );
        obj_Release(pNode);
        pNode = OBJ_NIL;
        
        obj_Release(pObj);
        pObj = OBJ_NIL;
    }
   
    return 1;
}




TINYTEST_START_SUITE(test_Parser);
    TINYTEST_ADD_TEST(test_Parser_Properties01,setUp,tearDown);
    TINYTEST_ADD_TEST(test_Parser_OpenClose,setUp,tearDown);
TINYTEST_END_SUITE();

TINYTEST_MAIN_SINGLE_SUITE(test_Parser);





