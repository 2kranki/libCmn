/*
 *	Generated 08/21/2017 13:03:04
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
#include    <pplex.h>
#include    <trace.h>
#include    <parser_internal.h>
#include    <szTbl.h>



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

    
    szTbl_SharedReset( );
    trace_SharedReset( ); 
    mem_Dump( );
    mem_Release( );
    
    return 1; 
}






int         test_parser_OpenClose(
    const
    char        *pTestName
)
{
    PARSER_DATA	*pObj = OBJ_NIL;
   
    pObj = parser_Alloc( );
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    pObj = parser_Init(pObj, 4);
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    if (pObj) {

        fprintf(stderr, "PPLEX_OP_ADD=%d\n",PPLEX_OP_ADD);
        fprintf(stderr, "PPLEX_SPCL_COLON=%d\n",PPLEX_SPCL_COLON);
        fprintf(stderr, "PPLEX_KWD_GOAL=%d\n",PPLEX_KWD_GOAL);
        fprintf(stderr, "PPLEX_IDENTIFIER=%d\n",PPLEX_IDENTIFIER);
        fprintf(stderr, "PPLEX_KWD_INTERNAL=%d\n",PPLEX_KWD_INTERNAL);
        fprintf(stderr, "PPLEX_SEP_LPAREN=%d\n",PPLEX_SEP_LPAREN);
        fprintf(stderr, "PPLEX_OP_MUL=%d\n",PPLEX_OP_MUL);
        fprintf(stderr, "PPLEX_OP_QUESTION=%d\n",PPLEX_OP_QUESTION);
        fprintf(stderr, "PPLEX_SEP_RPAREN=%d\n",PPLEX_SEP_RPAREN);
        fprintf(stderr, "PPLEX_SEP_SEMICOLON=%d\n",PPLEX_SEP_SEMICOLON);
        fprintf(stderr, "PPLEX_KWD_TERM=%d\n",PPLEX_KWD_TERM);
        fprintf(stderr, "PPLEX_SPCL_WHITESPACE=%d\n",PPLEX_SPCL_WHITESPACE);

        obj_Release(pObj);
        pObj = OBJ_NIL;
    }
   
    return 1;
}



int         test_parser_Properties01(
    const
    char        *pTestName
)
{
    PARSER_DATA	*pObj = OBJ_NIL;
    NODE_DATA       *pNode;
    NODE_DATA       *pNode2;
    ERESULT         eRc;
   
    pObj = parser_Alloc( );
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    pObj = parser_Init(pObj, 4);
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    if (pObj) {

        XCTAssertTrue( (0 == parser_PropertyCount(pObj)) );
        pNode = node_NewWithUTF8AndClass(0, "abc", OBJ_NIL);
        XCTAssertFalse( (OBJ_NIL == pObj) );
        eRc = parser_PropertyAdd(pObj, pNode);
        XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
        XCTAssertTrue( (1 == parser_PropertyCount(pObj)) );
        pNode2 = parser_Property(pObj, "abc");
        XCTAssertTrue( (pNode == pNode2) );
        obj_Release(pNode);
        pNode = OBJ_NIL;
        
        obj_Release(pObj);
        pObj = OBJ_NIL;
    }
   
    return 1;
}




TINYTEST_START_SUITE(test_parser);
	TINYTEST_ADD_TEST(test_parser_Properties01,setUp,tearDown);
  TINYTEST_ADD_TEST(test_parser_OpenClose,setUp,tearDown);
TINYTEST_END_SUITE();

TINYTEST_MAIN_SINGLE_SUITE(test_parser);





