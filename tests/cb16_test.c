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
#include    <cb16_internal.h>



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






int         test_cb16_OpenClose(
    const
    char        *pTestName
)
{
    CB16_DATA	*pObj = OBJ_NIL;
   
    fprintf(stderr, "Performing: %s\n", pTestName);
    
    pObj = cb16_Alloc(8);
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    pObj = cb16_Init( pObj );
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    if (pObj) {

        // Test something.

        obj_Release(pObj);
        pObj = OBJ_NIL;
    }

    fprintf(stderr, "...%s completed.\n", pTestName);
    return 1;
}



int         test_cb16_PutGet01(
    const
    char        *pTestName
)
{
	CB16_DATA       *cbp;
    uint32_t        i;
    uint16_t        data16;
    bool            fRc;
    
    fprintf(stderr, "Performing: %s\n", pTestName);
    
	cbp = cb16_Alloc(8);
    XCTAssertFalse( (NULL == cbp) );
	cbp = cb16_Init( cbp );
    XCTAssertFalse( (NULL == cbp) );
    if (cbp) {
        
        for (i=0; i<8; ++i) {
            fRc = cb16_Put(cbp, i, 0);
            XCTAssertTrue( (fRc) );
        }
        // Can't test this properly because TNeo simulation does not work well enough.
        //fRc = cb16_Put(cbp, i, 0);          // One too many
        //STAssertFalse( (fRc) );
        
        for (i=0; i<8; ++i) {
            fRc = cb16_Get(cbp, &data16, 0);
            XCTAssertTrue( (fRc) );
            XCTAssertTrue( (i == data16) );
        }
        //fRc = cb16_Get(cbp, &data16, 0);    // One too many
        //STAssertFalse( (fRc) );
        
        obj_Release(cbp);
        cbp = NULL;
    }
    
    fprintf(stderr, "...%s completed.\n", pTestName);
    return 1;
}




TINYTEST_START_SUITE(test_cb16);
  TINYTEST_ADD_TEST(test_cb16_PutGet01,setUp,tearDown);
  TINYTEST_ADD_TEST(test_cb16_OpenClose,setUp,tearDown);
TINYTEST_END_SUITE();

TINYTEST_MAIN_SINGLE_SUITE(test_cb16);





