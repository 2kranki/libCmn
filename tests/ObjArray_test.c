// vi:nu:et:sts=4 ts=4 sw=4
/*
 *	Generated 12/29/2019 20:07:08
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
#include    <JsonIn.h>
#include    <trace.h>
#include    <ObjArray_internal.h>
#include    <AStrC.h>
#include    <SrcErrors.h>
#include    <szTbl.h>



static
char    *stringTable[] = {
    "now",
    "xray",
    "before",
    "after",
    "tomorrow",
    "today",
    "someday",
    NULL
};
static
int            cStringTable = 7;




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

    SrcErrors_SharedReset( );
    szTbl_SharedReset( );
    JsonIn_RegisterReset();
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






int             test_ObjArray_OpenClose(
    const
    char            *pTestName
)
{
    ERESULT         eRc = ERESULT_SUCCESS;
    OBJARRAY_DATA	*pObj = OBJ_NIL;
    bool            fRc;
   
    fprintf(stderr, "Performing: %s\n", pTestName);

    pObj = ObjArray_Alloc( );
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    pObj = ObjArray_Init( pObj );
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    if (pObj) {

        //obj_TraceSet(pObj, true);       
        fRc = obj_IsKindOf(pObj, OBJ_IDENT_OBJARRAY);
        TINYTEST_TRUE( (fRc) );
        
        // Test something.
        TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );

        obj_Release(pObj);
        pObj = OBJ_NIL;
    }

    fprintf(stderr, "...%s completed.\n\n\n", pTestName);
    return 1;
}



int         test_ObjArray_Test01(
    const
    char        *pTestName
)
{
    OBJARRAY_DATA   *pObj = OBJ_NIL;
    OBJARRAY_DATA   *pObj2 = OBJ_NIL;
    ERESULT         eRc;
    uint32_t        i;
    uint32_t        iMax;
    uint32_t        size;
    ASTR_DATA       *pStr  = OBJ_NIL;
    ASTRC_DATA      *pStrC = OBJ_NIL;
    PATH_DATA       *pPath = OBJ_NIL;
   
    fprintf(stderr, "Performing: %s\n", pTestName);
    pPath = Path_NewFromCurrentDirectory();
    fprintf(stderr, "\tCurrent Directory = %s\n", Path_getData(pPath));
    obj_Release(pPath);
    pPath = OBJ_NIL;
    
    pObj = ObjArray_Alloc( );
    XCTAssertFalse( (OBJ_NIL == pObj) );
    pObj = ObjArray_Init( pObj );
    XCTAssertFalse( (OBJ_NIL == pObj) );
    if (pObj) {
        
        for (i=0; i<cStringTable; ++i) {
            pStrC = AStrC_NewA(stringTable[i]);
            XCTAssertFalse( (OBJ_NIL == pStrC) );
            if (pStrC) {
                eRc = ObjArray_AppendObj(pObj, pStrC, NULL);
                XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
                obj_Release(pStrC);
                pStrC = OBJ_NIL;
                size = ObjArray_getSize(pObj);
            }
        }
        fprintf(stderr, "\tcount = %d\n", ObjArray_getSize(pObj));
        XCTAssertTrue( (cStringTable == ObjArray_getSize(pObj)) );

        for (i=0; i<cStringTable; ++i) {
            pStrC = ObjArray_Get(pObj, i+1);
            fprintf(stderr, "%d - %s\n", i, AStrC_getData(pStrC));
            XCTAssertFalse( (OBJ_NIL == pStrC) );
            XCTAssertTrue( (0 == strcmp((char *)AStrC_getData(pStrC), stringTable[i])) );
        }
        
        eRc = ObjArray_SortAscending(pObj, (OBJ_COMPARE)&AStrC_Compare);
        fprintf(stderr, "\n\tSorted Array:\n");
        for (i=0; i<cStringTable; ++i) {
            pStrC = ObjArray_Get(pObj, i+1);
            fprintf( stderr, "%d - %s\n", i, AStrC_getData(pStrC) );
        }
        
        pStr = ObjArray_ToDebugString(pObj, 0);
        fprintf(stderr, "\n\n\nDebug = %s\n\n\n",AStr_getData(pStr));
        obj_Release(pStr);
        pStr = OBJ_NIL;
        
        fprintf(stderr, "\n\nNow creating a copy of the array!\n");
        pObj2 = ObjArray_Copy(pObj);
        XCTAssertFalse( (OBJ_NIL == pObj) );
        XCTAssertTrue( (!(pObj == pObj2)) );
        XCTAssertTrue( (ObjArray_getSize(pObj) == ObjArray_getSize(pObj2)) );
        iMax = ObjArray_getSize(pObj);
        for (i=0; i<iMax; i++) {
            ASTRC_DATA      *pStr1 = ObjArray_Get(pObj, i+1);
            ASTRC_DATA      *pStr2 = ObjArray_Get(pObj2, i+1);
            XCTAssertFalse( (OBJ_NIL == pStr1) );
            XCTAssertFalse( (OBJ_NIL == pStr2) );
            XCTAssertTrue( (0 == AStrC_Compare(pStr1, pStr2)) );
        }
        
        pStr = ObjArray_ToDebugString(pObj2, 0);
        fprintf(stderr, "Debug = %s\n\n\n", AStr_getData(pStr));
        obj_Release(pStr);
        pStr = OBJ_NIL;

        obj_Release(pObj2);
        pObj2 = OBJ_NIL;
        
        fprintf(stderr, "Now creating a deep copy of the array!\n");
        pObj2 = ObjArray_DeepCopy(pObj);
        XCTAssertFalse( (OBJ_NIL == pObj) );
        XCTAssertTrue( (!(pObj == pObj2)) );
        fprintf(stderr, "Size_Original = %d\n", ObjArray_getSize(pObj));
        fprintf(stderr, "Size_Other = %d\n", ObjArray_getSize(pObj2));
        XCTAssertTrue( (ObjArray_getSize(pObj) == ObjArray_getSize(pObj2)) );
        
        pStr = ObjArray_ToDebugString(pObj2, 0);
        fprintf(stderr, "Debug = %s\n\n\n", AStr_getData(pStr));
        obj_Release(pStr);
        pStr = OBJ_NIL;
        fprintf(stderr, "Check that each of the entries in the new list are different"
                        " addresses from first set of objects displayed.\n\n\n");
        
        obj_Release(pObj2);
        pObj2 = OBJ_NIL;

        pStr = ObjArray_ToJson(pObj);
        if (pStr) {
            fprintf(stderr, "json=%s\n", AStr_getData(pStr));
            obj_Release(pStr);
            pStr = OBJ_NIL;
        }

        obj_Release(pObj);
        pObj = OBJ_NIL;
    }

    fprintf(stderr, "...%s completed.\n", pTestName);
    return 1;
}



int         test_ObjArray_Test02(
    const
    char        *pTestName
)
{
    OBJARRAY_DATA   *pObj = OBJ_NIL;
    OBJARRAY_DATA   *pObj2 = OBJ_NIL;
    ERESULT         eRc;
    uint32_t        i;
    uint32_t        iMax;
    uint32_t        size;
    ASTR_DATA       *pStr;
    
    fprintf(stderr, "Performing: %s\n", pTestName);
    
    pObj = ObjArray_Alloc( );
    XCTAssertFalse( (OBJ_NIL == pObj) );
    pObj = ObjArray_Init( pObj );
    XCTAssertFalse( (OBJ_NIL == pObj) );
    if (pObj) {
        
        for (i=0; i<cStringTable; ++i) {
            pStr = AStr_NewA(stringTable[i]);
            XCTAssertFalse( (OBJ_NIL == pStr) );
            if (pStr) {
                eRc = ObjArray_Put(pObj, (i+1), pStr);
                XCTAssertTrue( (ERESULT_SUCCESSFUL(eRc)) );
                obj_Release(pStr);
                pStr = OBJ_NIL;
                size = ObjArray_getSize(pObj);
                XCTAssertTrue( (size == (i + 1)) );
            }
        }
        fprintf(stderr, "\tcount = %d\n", ObjArray_getSize(pObj));
        XCTAssertTrue( (cStringTable == ObjArray_getSize(pObj)) );
        
        for (i=0; i<cStringTable; ++i) {
            pStr = ObjArray_Get(pObj, i+1);
            fprintf(stderr, "%d - %s\n", i, AStr_getData(pStr));
            XCTAssertFalse( (OBJ_NIL == pStr) );
            XCTAssertTrue( (0 == strcmp((char *)AStr_getData(pStr), stringTable[i])) );
        }
        
        eRc = ObjArray_SortAscending(pObj, (OBJ_COMPARE)&AStr_Compare);
        fprintf(stderr, "\n\tSorted Array:\n");
        for (i=0; i<cStringTable; ++i) {
            pStr = ObjArray_Get(pObj, i+1);
            fprintf( stderr, "%d - %s\n", i, AStr_getData(pStr) );
        }
        
        fprintf(stderr, "\n\n\nCurrent array:\n");
        pStr = ObjArray_ToDebugString(pObj, 0);
        fprintf(stderr, "Debug = %s\n\n\n", AStr_getData(pStr));
        obj_Release(pStr);
        pStr = OBJ_NIL;
        
        eRc = ObjArray_Xchg(pObj, 1, 7);
        fprintf(stderr, "\n\n\n\tAfter Xchg Array:\n");
        for (i=0; i<cStringTable; ++i) {
            pStr = ObjArray_Get(pObj, i+1);
            fprintf( stderr, "%d - %s\n", i, AStr_getData(pStr) );
        }
        
        eRc = ObjArray_Xchg(pObj, 1, 7);
        fprintf(stderr, "\n\n\nCurrent array:\n");
        pStr = ObjArray_ToDebugString(pObj, 0);
        fprintf(stderr, "Debug = %s\n\n\n", AStr_getData(pStr));
        obj_Release(pStr);
        pStr = OBJ_NIL;
        
        fprintf(stderr, "Now creating a copy of the array!\n");
        pObj2 = ObjArray_Copy(pObj);
        XCTAssertFalse( (OBJ_NIL == pObj) );
        XCTAssertTrue( (!(pObj == pObj2)) );
        XCTAssertTrue( (ObjArray_getSize(pObj) == ObjArray_getSize(pObj2)) );
        iMax = ObjArray_getSize(pObj);
        for (i=0; i<iMax; i++) {
            ASTR_DATA       *pStr1 = ObjArray_Get(pObj, i+1);
            ASTR_DATA       *pStr2 = ObjArray_Get(pObj2, i+1);
            XCTAssertFalse( (OBJ_NIL == pStr1) );
            XCTAssertFalse( (OBJ_NIL == pStr2) );
            XCTAssertTrue( (0 == AStr_Compare(pStr1, pStr2)) );
        }

        pStr = ObjArray_ToDebugString(pObj2, 0);
        fprintf(stderr, "Debug = %s\n\n\n", AStr_getData(pStr));
        obj_Release(pStr);
        pStr = OBJ_NIL;
        fprintf(stderr, "Check that each of the entries in the new list are the same"
                " addresses from first set of objects displayed.\n\n\n");
        
        obj_Release(pObj2);
        pObj2 = OBJ_NIL;
        
        fprintf(stderr, "Now creating a deep copy of the array!\n");
        pObj2 = ObjArray_DeepCopy(pObj);
        XCTAssertFalse( (OBJ_NIL == pObj) );
        XCTAssertTrue( (!(pObj == pObj2)) );
        XCTAssertTrue( (ObjArray_getSize(pObj) == ObjArray_getSize(pObj2)) );
        
        pStr = ObjArray_ToDebugString(pObj2, 0);
        fprintf(stderr, "Debug = %s\n\n\n", AStr_getData(pStr));
        obj_Release(pStr);
        pStr = OBJ_NIL;
        fprintf(stderr, "Check that each of the entries in the new list are different"
                " addresses from first set of objects displayed.\n\n\n");
        
        obj_Release(pObj2);
        pObj2 = OBJ_NIL;
        
        pStr = ObjArray_ToJson(pObj);
        if (pStr) {
            fprintf(stderr, "Json:\n%s\n", AStr_getData(pStr));
            pObj2 = ObjArray_NewFromJsonString(pStr);
            obj_Release(pStr);
            //pStr = OBJ_NIL;
            TINYTEST_FALSE( (OBJ_NIL == pObj2) );
            if (pObj2) {
                pStr = ObjArray_ToDebugString(pObj2, 0);
                fprintf(stderr, "Json Object:\n%s\n", AStr_getData(pStr));
                obj_Release(pStr);
                pStr = OBJ_NIL;
                obj_Release(pObj2);
                pObj2 = OBJ_NIL;
            }
        }

        obj_Release(pObj);
        pObj = OBJ_NIL;
    }
    
    fprintf(stderr, "...%s completed.\n", pTestName);
    return 1;
}



int         test_ObjArray_Json01(
    const
    char        *pTestName
)
{
    OBJARRAY_DATA   *pObj = OBJ_NIL;
    OBJARRAY_DATA   *pObj2 = OBJ_NIL;
    ERESULT         eRc;
    uint32_t        i;
    uint32_t        iMax;
    uint32_t        size;
    ASTR_DATA       *pStr  = OBJ_NIL;
    PATH_DATA       *pPath = OBJ_NIL;

    fprintf(stderr, "Performing: %s\n", pTestName);
    pPath = Path_NewFromCurrentDirectory();
    fprintf(stderr, "\tCurrent Directory = %s\n", Path_getData(pPath));
    obj_Release(pPath);
    pPath = OBJ_NIL;

    pObj = ObjArray_New( );
    XCTAssertFalse( (OBJ_NIL == pObj) );
    if (pObj) {

        for (i=0; i<cStringTable; ++i) {
            pStr = AStr_NewA(stringTable[i]);
            XCTAssertFalse( (OBJ_NIL == pStr) );
            if (pStr) {
                eRc = ObjArray_AppendObj(pObj, pStr, NULL);
                XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
                obj_Release(pStr);
                pStr = OBJ_NIL;
                size = ObjArray_getSize(pObj);
            }
        }
        fprintf(stderr, "\tcount = %d\n", ObjArray_getSize(pObj));
        XCTAssertTrue( (cStringTable == ObjArray_getSize(pObj)) );

        for (i=0; i<cStringTable; ++i) {
            pStr = ObjArray_Get(pObj, i+1);
            fprintf(stderr, "%d - %s\n", i, AStr_getData(pStr));
            XCTAssertFalse( (OBJ_NIL == pStr) );
            XCTAssertTrue( (0 == strcmp((char *)AStr_getData(pStr), stringTable[i])) );
        }

        eRc = ObjArray_SortAscending(pObj, (OBJ_COMPARE)&AStr_Compare);
        fprintf(stderr, "\n\tSorted Array:\n");
        for (i=0; i<cStringTable; ++i) {
            pStr = ObjArray_Get(pObj, i+1);
            fprintf( stderr, "%d - %s\n", i, AStr_getData(pStr) );
        }

        pStr = ObjArray_ToDebugString(pObj, 0);
        fprintf(stderr, "\n\n\nDebug1 = %s\n\n\n",AStr_getData(pStr));
        obj_Release(pStr);
        pStr = OBJ_NIL;

        fprintf(stderr, "\n\nNow creating a json copy of the array!\n");
        pStr = ObjArray_ToJson(pObj);
        TINYTEST_FALSE( (OBJ_NIL == pStr) );
        if (pStr) {
            fprintf(stderr, "Json = %s\n\n\n",AStr_getData(pStr));
            pObj2 = ObjArray_NewFromJsonString(pStr);
            TINYTEST_FALSE( (OBJ_NIL == pObj2) );
            obj_Release(pStr);
            pStr = OBJ_NIL;
        }
        pStr = ObjArray_ToDebugString(pObj2, 0);
        fprintf(stderr, "Debug2 = %s\n\n\n", AStr_getData(pStr));
        obj_Release(pStr);
        pStr = OBJ_NIL;

        fprintf(stderr, "Size1 = %d\n", ObjArray_getSize(pObj));
        fprintf(stderr, "Size2 = %d\n", ObjArray_getSize(pObj2));
        TINYTEST_TRUE( (ObjArray_getSize(pObj) == ObjArray_getSize(pObj2)) );

        iMax = ObjArray_getSize(pObj);
        for (i=0; i<iMax; i++) {
            ASTR_DATA       *pStr1 = ObjArray_Get(pObj, i+1);
            ASTR_DATA       *pStr2 = ObjArray_Get(pObj2, i+1);
            TINYTEST_TRUE( (AStr_Compare(pStr1, pStr2) == 0) );
        }

        obj_Release(pObj2);
        pObj2 = OBJ_NIL;

        obj_Release(pObj);
        pObj = OBJ_NIL;
    }

    fprintf(stderr, "...%s completed.\n", pTestName);
    return 1;
}





TINYTEST_START_SUITE(test_ObjArray);
    TINYTEST_ADD_TEST(test_ObjArray_Json01,setUp,tearDown);
    TINYTEST_ADD_TEST(test_ObjArray_Test02,setUp,tearDown);
    TINYTEST_ADD_TEST(test_ObjArray_Test01,setUp,tearDown);
    TINYTEST_ADD_TEST(test_ObjArray_OpenClose,setUp,tearDown);
TINYTEST_END_SUITE();

TINYTEST_MAIN_SINGLE_SUITE(test_ObjArray);





