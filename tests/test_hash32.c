/*
 *	Generated 06/30/2017 09:01:13
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
#include    <hash32_internal.h>



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






int         test_hash32_OpenClose(
    const
    char        *pTestName
)
{
    HASH32_DATA	*pObj = OBJ_NIL;
   
    fprintf(stderr, "Performing: %s\n", pTestName);
    pObj = hash32_Alloc( );
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    pObj = hash32_Init( pObj, 17 );
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    if (pObj) {

        // Test something.

        obj_Release(pObj);
        pObj = OBJ_NIL;
    }

    fprintf(stderr, "...%s completed.\n", pTestName);
    return 1;
}



int         test_hash32_AddFindDelete_1(
    const
    char        *pTestName
)
{
    HASH32_DATA     *pObj = OBJ_NIL;
    uint32_t        i;
    uint32_t        cnt;
    bool            fRc;
    void            *pVoid;
    
    fprintf(stderr, "Performing: %s\n", pTestName);
    pObj = hash32_Alloc( );
    XCTAssertFalse( (OBJ_NIL == pObj) );
    pObj = hash32_Init( pObj, 3 );
    XCTAssertFalse( (OBJ_NIL == pObj) );
    if (pObj) {
        
        for (i=0; i<10; ++i) {
            fRc = hash32_Add(pObj, i+1, (void *)(size_t)(i+1));
            XCTAssertTrue( (fRc) );
            cnt = hash32_getCount(pObj);
            XCTAssertTrue( (cnt == (i+1)) );
        }
        
        for (i=0; i<10; ++i) {
            pVoid = hash32_Find(pObj, i+1);
            XCTAssertTrue( ((uint32_t)pVoid == i+1) );
        }
        
        pVoid = hash32_Find(pObj, 3);
        XCTAssertTrue( ((uint32_t)pVoid == 3) );
        pVoid = hash32_Find(pObj, 9);
        XCTAssertTrue( ((uint32_t)pVoid == 9) );
        pVoid = hash32_Find(pObj, 6);
        XCTAssertTrue( ((uint32_t)pVoid == 6) );
        
        fRc = hash32_Delete(pObj, 5);
        XCTAssertTrue( (fRc) );
        cnt = hash32_getCount(pObj);
        XCTAssertTrue( (cnt == 9) );
        
        fRc = hash32_Delete(pObj, 10);
        XCTAssertTrue( (fRc) );
        cnt = hash32_getCount(pObj);
        XCTAssertTrue( (cnt == 8) );
        
        obj_Release(pObj);
        pObj = OBJ_NIL;
    }
    
    fprintf(stderr, "...%s completed.\n", pTestName);
    return 1; 
}




TINYTEST_START_SUITE(test_hash32);
  TINYTEST_ADD_TEST(test_hash32_AddFindDelete_1,setUp,tearDown);
  TINYTEST_ADD_TEST(test_hash32_OpenClose,setUp,tearDown);
TINYTEST_END_SUITE();

TINYTEST_MAIN_SINGLE_SUITE(test_hash32);





