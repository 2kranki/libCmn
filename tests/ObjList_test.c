// vi:nu:et:sts=4 ts=4 sw=4
/*
 *	Generated 12/15/2019 12:58:04
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
#include    <Name.h>
#include    <SrcErrors.h>
#include    <szTbl.h>
#include    <trace.h>
#include    <ObjList_internal.h>



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

    SrcErrors_SharedReset();
    szTbl_SharedReset();
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






int             test_ObjList_OpenClose(
    const
    char            *pTestName
)
{
    ERESULT         eRc = ERESULT_SUCCESS;
    OBJLIST_DATA	    *pObj = OBJ_NIL;
   
    fprintf(stderr, "Performing: %s\n", pTestName);

    pObj = ObjList_Alloc( );
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    pObj = ObjList_Init( pObj );
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    if (pObj) {

        //obj_TraceSet(pObj, true);       
        
        // Test something.
        TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );

        obj_Release(pObj);
        pObj = OBJ_NIL;
    }

    fprintf(stderr, "...%s completed.\n\n\n", pTestName);
    return 1;
}



int         test_ObjList_BasicList01(
    const
    char        *pTestName
)
{
    OBJLIST_DATA    *pObj = OBJ_NIL;
    OBJLIST_DATA    *pObj2 = OBJ_NIL;
    NAME_DATA       *pNameA = OBJ_NIL;
    NAME_DATA       *pNameB = OBJ_NIL;
    NAME_DATA       *pNameC = OBJ_NIL;
    NAME_DATA       *pNameD = OBJ_NIL;
    NAME_DATA       *pNameE = OBJ_NIL;
    ERESULT         eRc;
    ASTR_DATA       *pStr = OBJ_NIL;
    NAME_DATA       *pEntry;

    fprintf(stderr, "Performing: %s\n", pTestName);
    
    pObj = ObjList_Alloc( );
    XCTAssertFalse( (OBJ_NIL == pObj) );
    pObj = ObjList_Init( pObj );
    XCTAssertFalse( (OBJ_NIL == pObj) );
    if (pObj) {
        
        pNameA = Name_NewUTF8("A");
        XCTAssertFalse( (OBJ_NIL == pNameA) );
        pNameB = Name_NewUTF8("B");
        XCTAssertFalse( (OBJ_NIL == pNameB) );
        pNameC = Name_NewUTF8("C");
        XCTAssertFalse( (OBJ_NIL == pNameC) );
        pNameD = Name_NewUTF8("D");
        XCTAssertFalse( (OBJ_NIL == pNameD) );
        pNameE = Name_NewUTF8("E");
        XCTAssertFalse( (OBJ_NIL == pNameE) );
        
        eRc = ObjList_Add2Head(pObj, pNameA);
        XCTAssertFalse( (ERESULT_FAILED(eRc)) );
        eRc = ObjList_Add2Head(pObj, pNameB);
        XCTAssertFalse( (ERESULT_FAILED(eRc)) );
        eRc = ObjList_Add2Head(pObj, pNameC);
        XCTAssertFalse( (ERESULT_FAILED(eRc)) );
        
        // Verify that the linkage fields are correct.
        pEntry = ObjList_Head(pObj);
        XCTAssertFalse( (pEntry == OBJ_NIL) );
        XCTAssertTrue( (pEntry == pNameC) );
        pEntry = ObjList_Index(pObj, 1);
        XCTAssertFalse( (pEntry == OBJ_NIL) );
        XCTAssertTrue( (pEntry == pNameC) );
        pEntry = ObjList_Index(pObj, 2);
        XCTAssertFalse( (pEntry == OBJ_NIL) );
        XCTAssertTrue( (pEntry == pNameB) );
        pEntry = ObjList_Index(pObj, 3);
        XCTAssertFalse( (pEntry == OBJ_NIL) );
        XCTAssertTrue( (pEntry == pNameA) );
        pEntry = ObjList_Tail(pObj);
        XCTAssertFalse( (pEntry == OBJ_NIL) );
        XCTAssertTrue( (pEntry == pNameA) );
        
        pStr = ObjList_ToDebugString(pObj, 0);
        fprintf(stderr, "Debug = %s\n\n\n",AStr_getData(pStr));
        obj_Release(pStr);
        pStr = OBJ_NIL;
        
        pObj2 = ObjList_Copy(pObj);
        XCTAssertFalse( (OBJ_NIL == pObj) );
        XCTAssertTrue( (!(pObj == pObj2)) );
        XCTAssertTrue( (ObjList_getSize(pObj) == ObjList_getSize(pObj2)) );

        pStr = ObjList_ToDebugString(pObj2, 0);
        fprintf(stderr, "Debug = %s\n\n\n",AStr_getData(pStr));
        obj_Release(pStr);
        pStr = OBJ_NIL;

        // Verify that the linkage fields are correct.
        pEntry = ObjList_Head(pObj2);
        XCTAssertFalse( (pEntry == OBJ_NIL) );
        XCTAssertTrue( (pEntry == pNameC) );
        eRc = Name_CompareA(pEntry, "C");
        XCTAssertTrue( (ERESULT_SUCCESS_EQUAL == eRc) );
        pEntry = ObjList_Index(pObj2, 1);
        XCTAssertFalse( (pEntry == OBJ_NIL) );
        XCTAssertTrue( (pEntry == pNameC) );
        eRc = Name_CompareA(pEntry, "C");
        XCTAssertTrue( (ERESULT_SUCCESS_EQUAL == eRc) );
        pEntry = ObjList_Index(pObj2, 2);
        XCTAssertFalse( (pEntry == OBJ_NIL) );
        XCTAssertTrue( (pEntry == pNameB) );
        eRc = Name_CompareA(pEntry, "B");
        XCTAssertTrue( (ERESULT_SUCCESS_EQUAL == eRc) );
        pEntry = ObjList_Index(pObj2, 3);
        XCTAssertFalse( (pEntry == OBJ_NIL) );
        XCTAssertTrue( (pEntry == pNameA) );
        eRc = Name_CompareA(pEntry, "A");
        XCTAssertTrue( (ERESULT_SUCCESS_EQUAL == eRc) );
        pEntry = ObjList_Tail(pObj2);
        XCTAssertFalse( (pEntry == OBJ_NIL) );
        XCTAssertTrue( (pEntry == pNameA) );
        eRc = Name_CompareA(pEntry, "A");
        XCTAssertTrue( (ERESULT_SUCCESS_EQUAL == eRc) );

        obj_Release(pObj2);
        pObj2 = OBJ_NIL;

        pObj2 = ObjList_DeepCopy(pObj);
        XCTAssertFalse( (OBJ_NIL == pObj) );
        XCTAssertTrue( (!(pObj == pObj2)) );
        XCTAssertTrue( (ObjList_getSize(pObj) == ObjList_getSize(pObj2)) );

        pStr = ObjList_ToDebugString(pObj2, 0);
        fprintf(stderr, "Debug = %s\n\n\n",AStr_getData(pStr));
        obj_Release(pStr);
        pStr = OBJ_NIL;
        // Verify that the linkage fields are correct.
        pEntry = ObjList_Head(pObj2);
        XCTAssertFalse( (pEntry == OBJ_NIL) );
        XCTAssertTrue( !(pEntry == pNameC) );
        eRc = Name_CompareA(pEntry, "C");
        XCTAssertTrue( (ERESULT_SUCCESS_EQUAL == eRc) );
        pEntry = ObjList_Index(pObj2, 1);
        XCTAssertFalse( (pEntry == OBJ_NIL) );
        XCTAssertTrue( !(pEntry == pNameC) );
        eRc = Name_CompareA(pEntry, "C");
        XCTAssertTrue( (ERESULT_SUCCESS_EQUAL == eRc) );
        pEntry = ObjList_Index(pObj2, 2);
        XCTAssertFalse( (pEntry == OBJ_NIL) );
        XCTAssertTrue( !(pEntry == pNameB) );
        eRc = Name_CompareA(pEntry, "B");
        XCTAssertTrue( (ERESULT_SUCCESS_EQUAL == eRc) );
        pEntry = ObjList_Index(pObj2, 3);
        XCTAssertFalse( (pEntry == OBJ_NIL) );
        XCTAssertTrue( !(pEntry == pNameA) );
        eRc = Name_CompareA(pEntry, "A");
        XCTAssertTrue( (ERESULT_SUCCESS_EQUAL == eRc) );
        pEntry = ObjList_Tail(pObj2);
        XCTAssertFalse( (pEntry == OBJ_NIL) );
        XCTAssertTrue( !(pEntry == pNameA) );
        eRc = Name_CompareA(pEntry, "A");
        XCTAssertTrue( (ERESULT_SUCCESS_EQUAL == eRc) );
        
        obj_Release(pObj2);
        pObj2 = OBJ_NIL;
        
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
    
    fprintf(stderr, "...%s completed.\n\n\n", pTestName);
    return 1;
}



int         test_ObjList_Shift(
    const
    char        *pTestName
)
{
    OBJLIST_DATA    *pObj = OBJ_NIL;
    NAME_DATA       *pNameA = OBJ_NIL;
    NAME_DATA       *pNameB = OBJ_NIL;
    NAME_DATA       *pNameC = OBJ_NIL;
    NAME_DATA       *pNameD = OBJ_NIL;
    NAME_DATA       *pNameE = OBJ_NIL;
    ERESULT         eRc;
    ASTR_DATA       *pStr = OBJ_NIL;
    NAME_DATA       *pEntry;

    fprintf(stderr, "Performing: %s\n", pTestName);
    
    pObj = ObjList_Alloc( );
    XCTAssertFalse( (OBJ_NIL == pObj) );
    pObj = ObjList_Init( pObj );
    XCTAssertFalse( (OBJ_NIL == pObj) );
    if (pObj) {
        
        pNameA = Name_NewUTF8("A");
        XCTAssertFalse( (OBJ_NIL == pNameA) );
        pNameB = Name_NewUTF8("B");
        XCTAssertFalse( (OBJ_NIL == pNameB) );
        pNameC = Name_NewUTF8("C");
        XCTAssertFalse( (OBJ_NIL == pNameC) );
        pNameD = Name_NewUTF8("D");
        XCTAssertFalse( (OBJ_NIL == pNameD) );
        pNameE = Name_NewUTF8("E");
        XCTAssertFalse( (OBJ_NIL == pNameE) );
        
        eRc = ObjList_Add2Head(pObj, pNameA);
        XCTAssertFalse( (ERESULT_FAILED(eRc)) );
        eRc = ObjList_Add2Head(pObj, pNameB);
        XCTAssertFalse( (ERESULT_FAILED(eRc)) );
        eRc = ObjList_Add2Head(pObj, pNameC);
        XCTAssertFalse( (ERESULT_FAILED(eRc)) );
        eRc = ObjList_Add2Head(pObj, pNameD);
        XCTAssertFalse( (ERESULT_FAILED(eRc)) );
        eRc = ObjList_Add2Head(pObj, pNameE);
        XCTAssertFalse( (ERESULT_FAILED(eRc)) );

        // Verify that the linkage fields are correct.
        pEntry = ObjList_Head(pObj);
        XCTAssertFalse( (pEntry == OBJ_NIL) );
        XCTAssertTrue( (pEntry == pNameE) );
        pEntry = ObjList_Index(pObj, 1);
        XCTAssertFalse( (pEntry == OBJ_NIL) );
        XCTAssertTrue( (pEntry == pNameE) );
        pEntry = ObjList_Index(pObj, 2);
        XCTAssertFalse( (pEntry == OBJ_NIL) );
        XCTAssertTrue( (pEntry == pNameD) );
        pEntry = ObjList_Index(pObj, 3);
        XCTAssertFalse( (pEntry == OBJ_NIL) );
        XCTAssertTrue( (pEntry == pNameC) );
        pEntry = ObjList_Index(pObj, 4);
        XCTAssertFalse( (pEntry == OBJ_NIL) );
        XCTAssertTrue( (pEntry == pNameB) );
        pEntry = ObjList_Index(pObj, 5);
        XCTAssertFalse( (pEntry == OBJ_NIL) );
        XCTAssertTrue( (pEntry == pNameA) );
        
        pStr = ObjList_ToDebugString(pObj, 0);
        fprintf(stderr, "Debug = %s\n\n\n",AStr_getData(pStr));
        obj_Release(pStr);
        pStr = OBJ_NIL;
        
        pEntry = ObjList_ShiftHead(pObj);
        XCTAssertFalse( (pEntry == OBJ_NIL) );
        XCTAssertTrue( (pEntry == pNameA) );
        pStr = ObjList_ToDebugString(pObj, 0);
        fprintf(stderr, "After ShiftHead = %s\n\n\n",AStr_getData(pStr));
        obj_Release(pStr);
        pStr = OBJ_NIL;

        pEntry = ObjList_ShiftTail(pObj);
        XCTAssertFalse( (pEntry == OBJ_NIL) );
        XCTAssertTrue( (pEntry == pNameE) );
        pStr = ObjList_ToDebugString(pObj, 0);
        fprintf(stderr, "After ShiftTail = %s\n\n\n",AStr_getData(pStr));
        obj_Release(pStr);
        pStr = OBJ_NIL;

        pEntry = ObjList_Pop(pObj);
        XCTAssertFalse( (pEntry == OBJ_NIL) );
        XCTAssertTrue( (pEntry == pNameE) );
        XCTAssertTrue( (2 == obj_getRetainCount(pEntry)) );
        obj_Release(pEntry);
        pEntry = OBJ_NIL;

        eRc = ObjList_Push(pObj, pNameE);
        XCTAssertFalse( (ERESULT_FAILED(eRc)) );
        pEntry = ObjList_Head(pObj);
        XCTAssertFalse( (pEntry == OBJ_NIL) );
        XCTAssertTrue( (pEntry == pNameE) );
        XCTAssertTrue( (2 == obj_getRetainCount(pEntry)) );

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
    
    fprintf(stderr, "...%s completed.\n\n\n", pTestName);
    return 1;
}



int         test_ObjList_Json01(
    const
    char        *pTestName
)
{
    OBJLIST_DATA    *pObj = OBJ_NIL;
    OBJLIST_DATA    *pObj2 = OBJ_NIL;
    NAME_DATA       *pNameA = OBJ_NIL;
    NAME_DATA       *pNameB = OBJ_NIL;
    NAME_DATA       *pNameC = OBJ_NIL;
    NAME_DATA       *pNameD = OBJ_NIL;
    NAME_DATA       *pNameE = OBJ_NIL;
    ERESULT         eRc;
    ASTR_DATA       *pStr = OBJ_NIL;
    //NAME_DATA       *pEntry;

    fprintf(stderr, "Performing: %s\n", pTestName);

    pObj = ObjList_New( );
    XCTAssertFalse( (OBJ_NIL == pObj) );
    if (pObj) {

        pNameA = Name_NewUTF8("A");
        XCTAssertFalse( (OBJ_NIL == pNameA) );
        pNameB = Name_NewUTF8("B");
        XCTAssertFalse( (OBJ_NIL == pNameB) );
        pNameC = Name_NewUTF8("C");
        XCTAssertFalse( (OBJ_NIL == pNameC) );
        pNameD = Name_NewUTF8("D");
        XCTAssertFalse( (OBJ_NIL == pNameD) );
        pNameE = Name_NewUTF8("E");
        XCTAssertFalse( (OBJ_NIL == pNameE) );

        eRc = ObjList_Add2Tail(pObj, pNameA);
        XCTAssertFalse( (ERESULT_FAILED(eRc)) );
        eRc = ObjList_Add2Tail(pObj, pNameB);
        XCTAssertFalse( (ERESULT_FAILED(eRc)) );
        eRc = ObjList_Add2Tail(pObj, pNameC);
        XCTAssertFalse( (ERESULT_FAILED(eRc)) );
        eRc = ObjList_Add2Tail(pObj, pNameD);
        XCTAssertFalse( (ERESULT_FAILED(eRc)) );
        eRc = ObjList_Add2Tail(pObj, pNameE);
        XCTAssertFalse( (ERESULT_FAILED(eRc)) );

        pStr = ObjList_ToDebugString(pObj, 0);
        fprintf(stderr, "Debug1 = %s\n\n\n", AStr_getData(pStr));
        obj_Release(pStr);
        pStr = OBJ_NIL;

        pStr = ObjList_ToJson(pObj);
        TINYTEST_FALSE( (pStr == OBJ_NIL) );
        if (pStr) {
            fprintf(stderr, "Json = %s\n\n\n", AStr_getData(pStr));
        }

        pObj2 = ObjList_NewFromJsonString(pStr);
        TINYTEST_FALSE( (pObj2 == OBJ_NIL) );
        obj_Release(pStr);
        pStr = OBJ_NIL;
        XCTAssertTrue( (!(pObj == pObj2)) );
        XCTAssertTrue( (ObjList_getSize(pObj) == ObjList_getSize(pObj2)) );

        pStr = ObjList_ToDebugString(pObj2, 0);
        fprintf(stderr, "Debug2 = %s\n\n\n",AStr_getData(pStr));
        obj_Release(pStr);
        pStr = OBJ_NIL;

        obj_Release(pObj2);
        pObj2 = OBJ_NIL;

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

        obj_Release(pObj);
        pObj = OBJ_NIL;
    }

    fprintf(stderr, "...%s completed.\n\n\n", pTestName);
    return 1;
}




TINYTEST_START_SUITE(test_ObjList);
    TINYTEST_ADD_TEST(test_ObjList_Json01,setUp,tearDown);
    TINYTEST_ADD_TEST(test_ObjList_Shift,setUp,tearDown);
    TINYTEST_ADD_TEST(test_ObjList_BasicList01,setUp,tearDown);
    TINYTEST_ADD_TEST(test_ObjList_OpenClose,setUp,tearDown);
TINYTEST_END_SUITE();

TINYTEST_MAIN_SINGLE_SUITE(test_ObjList);





