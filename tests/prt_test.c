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
#include    <fbsi_internal.h>
#include    <fbso_internal.h>



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






int         test_fbs_OpenClose(
    const
    char        *pTestName
)
{
    FBSI_DATA	*pObjI = OBJ_NIL;
    FBSO_DATA	*pObjO = OBJ_NIL;
    const
    char        *pFilePathStr = "/Users/bob/Support/x/test.txt";
    PATH_DATA   *pFilePath = OBJ_NIL;
   
    fprintf(stderr, "Performing: %s\n", pTestName);
    
    pFilePath = Path_NewA(pFilePathStr);
    XCTAssertFalse( (OBJ_NIL == pFilePath) );
    
    pObjO = fbso_Alloc();
    XCTAssertFalse( (OBJ_NIL == pObjO) );
    pObjO = fbso_Init( pObjO, pFilePath );
    XCTAssertFalse( (OBJ_NIL == pObjO) );
    if (pObjO) {
        obj_Release(pObjO);
        pObjO = OBJ_NIL;
    }
    
    pObjI = fbsi_Alloc();
    XCTAssertFalse( (OBJ_NIL == pObjI) );
    pObjI = fbsi_InitPath( pObjI, pFilePath );
    XCTAssertFalse( (OBJ_NIL == pObjI) );
    if (pObjI) {
        obj_Release(pObjI);
        pObjI = OBJ_NIL;
    }
    
    obj_Release(pFilePath);

    fprintf(stderr, "...%s completed.\n", pTestName);
    return 1;
}




TINYTEST_START_SUITE(test_fbs);
  TINYTEST_ADD_TEST(test_fbs_OpenClose,setUp,tearDown);
TINYTEST_END_SUITE();

TINYTEST_MAIN_SINGLE_SUITE(test_fbs);





