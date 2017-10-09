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
#include    <table_internal.h>



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
    mem_Dump( );
    mem_Release( );
    
    return 1; 
}






int         test_table_OpenClose(
    const
    char        *pTestName
)
{
    TABLE_DATA	*pObj = OBJ_NIL;
   
    fprintf(stderr, "Performing: %s\n", pTestName);
    
    pObj = table_Alloc( );
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    pObj = table_Init( pObj, 2, 3, true );
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    if (pObj) {

        // Test something.

        obj_Release(pObj);
        pObj = OBJ_NIL;
    }

    fprintf(stderr, "...%s completed.\n", pTestName);
    return 1;
}



int         test_table_AddDelete(
    const
    char        *pTestName
)
{
    TABLE_DATA		*pTable = NULL;
    void            *pEntry1;
    void            *pEntry2;
    void            *pEntry3;
    bool            fRc;
   
    fprintf(stderr, "Performing: %s\n", pTestName);
    
    pTable = table_Alloc( );
    XCTAssertFalse( (NULL == pTable) );
    pTable = table_Init( pTable, 2, 3, true );
    XCTAssertFalse( (NULL == pTable) );
    if (pTable) {

        pEntry1 = table_Add(pTable);
        XCTAssertFalse( (NULL == pEntry1) );
        pEntry2 = table_Add(pTable);
        XCTAssertFalse( (NULL == pEntry2) );
        pEntry3 = table_Add(pTable);
        XCTAssertTrue( (NULL == pEntry3) );

        fRc = table_Delete(pTable,pEntry2);
        XCTAssertTrue( (fRc) );
        fRc = table_Delete(pTable,pEntry2);
        XCTAssertTrue( (!fRc) );

        pEntry2 = table_Add(pTable);
        XCTAssertFalse( (NULL == pEntry2) );
        
        pEntry3 = table_Head(pTable);
        XCTAssertFalse( (NULL == pEntry3) );
        XCTAssertTrue( (pEntry3 == pEntry1) );
        
        pEntry3 = table_Next(pTable,pEntry3);
        XCTAssertFalse( (NULL == pEntry3) );
        XCTAssertTrue( (pEntry3 == pEntry2) );
        
        fRc = table_MoveBefore(pTable,pEntry1, pEntry2);
        XCTAssertTrue( (fRc) );

        pEntry3 = table_Head(pTable);
        XCTAssertFalse( (NULL == pEntry3) );
        XCTAssertTrue( (pEntry3 == pEntry2) );
        
        obj_Release(pTable);
        pTable = NULL;
    }

    fprintf(stderr, "...%s completed.\n", pTestName);
    return 1;
}




TINYTEST_START_SUITE(test_table);
  TINYTEST_ADD_TEST(test_table_AddDelete,setUp,tearDown);
  TINYTEST_ADD_TEST(test_table_OpenClose,setUp,tearDown);
TINYTEST_END_SUITE();

TINYTEST_MAIN_SINGLE_SUITE(test_table);





