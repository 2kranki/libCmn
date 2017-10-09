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
#include    <name.h>
#include    <szTbl.h>
#include    <objList_internal.h>



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

    
    szTbl_SharedReset();
    trace_SharedReset( ); 
    mem_Dump( );
    mem_Release( );
    
    return 1; 
}






int         test_objList_OpenClose(
    const
    char        *pTestName
)
{
    OBJLIST_DATA *pObj = OBJ_NIL;
   
    fprintf(stderr, "Performing: %s\n", pTestName);
    
    pObj = objList_Alloc( );
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    pObj = objList_Init( pObj );
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    if (pObj) {

        // Test something.

        obj_Release(pObj);
        pObj = OBJ_NIL;
    }

    fprintf(stderr, "...%s completed.\n", pTestName);
    return 1;
}



int         test_objList_BasicList01(
    const
    char        *pTestName
)
{
    OBJLIST_DATA	*pObj = OBJ_NIL;
    NAME_DATA       *pNameA = OBJ_NIL;
    NAME_DATA       *pNameB = OBJ_NIL;
    NAME_DATA       *pNameC = OBJ_NIL;
    NAME_DATA       *pNameD = OBJ_NIL;
    NAME_DATA       *pNameE = OBJ_NIL;
    ERESULT         eRc;
    ASTR_DATA       *pStr = OBJ_NIL;
    NAME_DATA       *pEntry;
    
    fprintf(stderr, "Performing: %s\n", pTestName);
    
    pObj = objList_Alloc( );
    XCTAssertFalse( (OBJ_NIL == pObj) );
    pObj = objList_Init( pObj );
    XCTAssertFalse( (OBJ_NIL == pObj) );
    if (pObj) {
        
        pNameA = name_NewUTF8("A");
        XCTAssertFalse( (OBJ_NIL == pNameA) );
        pNameB = name_NewUTF8("B");
        XCTAssertFalse( (OBJ_NIL == pNameB) );
        pNameC = name_NewUTF8("C");
        XCTAssertFalse( (OBJ_NIL == pNameC) );
        pNameD = name_NewUTF8("D");
        XCTAssertFalse( (OBJ_NIL == pNameD) );
        pNameE = name_NewUTF8("E");
        XCTAssertFalse( (OBJ_NIL == pNameE) );
        
        eRc = objList_Add2Head(pObj, pNameA);
        XCTAssertFalse( (ERESULT_FAILED(eRc)) );
        eRc = objList_Add2Head(pObj, pNameB);
        XCTAssertFalse( (ERESULT_FAILED(eRc)) );
        eRc = objList_Add2Head(pObj, pNameC);
        XCTAssertFalse( (ERESULT_FAILED(eRc)) );
        
        // Verify that the linkage fields are correct.
        pEntry = objList_Head(pObj);
        XCTAssertFalse( (pEntry == OBJ_NIL) );
        XCTAssertTrue( (pEntry == pNameC) );
        pEntry = objList_Index(pObj, 1);
        XCTAssertFalse( (pEntry == OBJ_NIL) );
        XCTAssertTrue( (pEntry == pNameC) );
        pEntry = objList_Index(pObj, 2);
        XCTAssertFalse( (pEntry == OBJ_NIL) );
        XCTAssertTrue( (pEntry == pNameB) );
        pEntry = objList_Index(pObj, 3);
        XCTAssertFalse( (pEntry == OBJ_NIL) );
        XCTAssertTrue( (pEntry == pNameA) );
        pEntry = objList_Tail(pObj);
        XCTAssertFalse( (pEntry == OBJ_NIL) );
        XCTAssertTrue( (pEntry == pNameA) );
        
        pStr = objList_ToDebugString(pObj, 0);
        fprintf(stderr, "Debug = %s\n\n\n",AStr_getData(pStr));
        obj_Release(pStr);
        pStr = OBJ_NIL;
        
        obj_Release(pNameE);
        pNameE = OBJ_NIL;
        obj_Release(pNameD);
        pNameD = OBJ_NIL;
        obj_Release(pNameC);
        pNameC = OBJ_NIL;
        obj_Release(pNameB);
        pNameB = OBJ_NIL;
        obj_Release(pNameA);
        pNameA = OBJ_NIL;
        
        XCTAssertTrue( (obj_IsFlag(pObj, OBJ_FLAG_ALLOC)) );
        obj_Release(pObj);
        pObj = OBJ_NIL;
    }
    
    fprintf(stderr, "...%s completed.\n", pTestName);
    return 1;
}




TINYTEST_START_SUITE(test_objList);
  TINYTEST_ADD_TEST(test_objList_BasicList01,setUp,tearDown);
  TINYTEST_ADD_TEST(test_objList_OpenClose,setUp,tearDown);
TINYTEST_END_SUITE();

TINYTEST_MAIN_SINGLE_SUITE(test_objList);





