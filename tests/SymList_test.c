// vi:nu:et:sts=4 ts=4 sw=4
/*
 *  Generated 07/13/2021 03:07:27
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
#include    <test_defs.h>
#include    <trace.h>
#include    <SymList_internal.h>
#include    <JsonIn.h>
#ifdef  SYMLIST_JSON_SUPPORT
#   include    <SrcErrors.h>
#   include    <szTbl.h>
#endif

static
char        *strings[] = {
    "bob",
    "bobby",
    "iryana",
    "dashsa",
    "dasha",
    "name",
    "way",
    "bigger",
    "Now",
    "is",
    "the",
    "time",
    "for",
    "all",
    "good",
    "men",
    "to",
    "come",
    "aid",
    "of",
    "their",
    "country",
    "We",
    "need",
    "another",
    "item",
    "in",
    "here",
    "Are",
    "you",
    "alright",
    "with",
    "this",
    (char *)NULL
};



ERESULT     listEntryPrintRtn(
    NODELIST_DATA   *this,
    NODE_DATA       *pNode,
    void            *pVoid
)
{
    char            *pNameA;

    pNameA = Node_getNameUTF8(pNode);
    fprintf(stderr, "\t\t%s\n", pNameA);
    mem_Free(pNameA);
    return ERESULT_SUCCESS;
}




int             setUp (
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


int             tearDown (
    const
    char            *pTestName
)
{
    // Put teardown code here. This method is called after the invocation of each
    // test method in the class.

#ifdef  SYMLIST_JSON_SUPPORT
    SrcErrors_SharedReset( );
    szTbl_SharedReset( );
#endif
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






int             test_SymList_OpenClose (
    const
    char            *pTestName
)
{
    ERESULT         eRc = ERESULT_SUCCESS;
    SYMLIST_DATA       *pObj = OBJ_NIL;
    bool            fRc;
   
    fprintf(stderr, "Performing: %s\n", pTestName);

    pObj = SymList_Alloc( );
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    pObj = SymList_Init( pObj );
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    if (pObj) {

        //obj_TraceSet(pObj, true);       
        fRc = obj_IsKindOf(pObj, OBJ_IDENT_SYMLIST);
        TINYTEST_TRUE( (fRc) );
        
        // Test something.
        TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );

        obj_Release(pObj);
        pObj = OBJ_NIL;
    }

    fprintf(stderr, "...%s completed.\n\n\n", pTestName);
    return 1;
}



int             test_SymList_Copy01 (
    const
    char            *pTestName
)
{
    ERESULT         eRc = ERESULT_SUCCESS;
    SYMLIST_DATA       *pObj1 = OBJ_NIL;
    SYMLIST_DATA       *pObj2 = OBJ_NIL;
    bool            fRc;
#if defined(SYMLIST_JSON_SUPPORT) && defined(XYZZY)
    ASTR_DATA       *pStr = OBJ_NIL;
#endif
    //int             iRc;
   
    fprintf(stderr, "Performing: %s\n", pTestName);

    pObj1 = SymList_New( );
    TINYTEST_FALSE( (OBJ_NIL == pObj1) );
    if (pObj1) {

        //obj_TraceSet(pObj1, true);       
        fRc = obj_IsKindOf(pObj1, OBJ_IDENT_SYMLIST);
        TINYTEST_TRUE( (fRc) );
        
        // Test assign.
        pObj2 = SymList_New();
        TINYTEST_FALSE( (OBJ_NIL == pObj2) );
        eRc = SymList_Assign(pObj1, pObj2);
        TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );

        fRc = obj_IsKindOf(pObj2, OBJ_IDENT_SYMLIST);
        TINYTEST_TRUE( (fRc) );
        //iRc = SymList_Compare(pObj1, pObj2);
        //TINYTEST_TRUE( (0 == iRc) );
        //TODO: Add More tests here!

        obj_Release(pObj2);
        pObj2 = OBJ_NIL;

        // Test copy.
        pObj2 = SymList_Copy(pObj1);
        TINYTEST_FALSE( (OBJ_NIL == pObj2) );

        fRc = obj_IsKindOf(pObj2, OBJ_IDENT_SYMLIST);
        TINYTEST_TRUE( (fRc) );
        //iRc = SymList_Compare(pObj1, pObj2);
        //TINYTEST_TRUE( (0 == iRc) );
        //TODO: Add More tests here!

        obj_Release(pObj2);
        pObj2 = OBJ_NIL;

        // Test json support.
#if defined(SYMLIST_JSON_SUPPORT) && defined(XYZZY)
        pStr = SymList_ToJson(pObj1);
        TINYTEST_FALSE( (OBJ_NIL == pStr) );
        fprintf(stderr, "JSON: %s\n", AStr_getData(pStr));
        pObj2 = SymList_NewFromJsonString(pStr);
        TINYTEST_FALSE( (OBJ_NIL == pObj2) );
        fRc = obj_IsKindOf(pObj2, OBJ_IDENT_SYMLIST);
        TINYTEST_TRUE( (fRc) );
        obj_Release(pStr);
        pStr = OBJ_NIL;
        //iRc = SymList_Compare(pObj1, pObj2);
        //TINYTEST_TRUE( (0 == iRc) );

        obj_Release(pObj2);
        pObj2 = OBJ_NIL;
#endif

        obj_Release(pObj1);
        pObj1 = OBJ_NIL;
    }

    fprintf(stderr, "...%s completed.\n\n\n", pTestName);
    return 1;
}



int             test_SymList_Test01 (
    const
    char            *pTestName
)
{
    //ERESULT         eRc = ERESULT_SUCCESS;
    SYMLIST_DATA       *pObj = OBJ_NIL;
    bool            fRc;
   
    fprintf(stderr, "Performing: %s\n", pTestName);

    pObj = SymList_New( );
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    if (pObj) {

        //obj_TraceSet(pObj, true);       
        fRc = obj_IsKindOf(pObj, OBJ_IDENT_SYMLIST);
        TINYTEST_TRUE( (fRc) );
        //TINYTEST_TRUE( (ERESULT_OK(eRc)) );
        
        {
            ASTR_DATA       *pStr = SymList_ToDebugString(pObj, 4);
            if (pStr) {
                fprintf(stderr, "Debug: %s\n", AStr_getData(pStr));
                obj_Release(pStr);
                pStr = OBJ_NIL;
            }
        }

        obj_Release(pObj);
        pObj = OBJ_NIL;
    }

    fprintf(stderr, "...%s completed.\n\n\n", pTestName);
    return 1;
}



int         test_SymList_AddFindDelete01(
    const
    char        *pTestName
)
{
    SYMLIST_DATA    *pList;
    SYM_DATA        *pSym;
    uint32_t        i;
    uint32_t        cnt;
    ERESULT         eRc;

    fprintf(stderr, "Performing: %s\n", pTestName);

    pList = SymList_New( );
    XCTAssertFalse( (OBJ_NIL == pList) );
    if (pList) {

        for (i=0; i<10; ++i) {
            pSym = Sym_NewA(0, strings[i]);
            eRc = SymList_Add2Head(pList, pSym);
            XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
            cnt = SymList_getSize(pList);
            XCTAssertTrue( (cnt == (i+1)) );
            pSym = SymList_FindA(pList, 0, strings[i]);
            XCTAssertTrue( (pSym) );
            obj_Release(pSym);
            pSym = OBJ_NIL;
        }

#ifdef XYZZY
        eRc = SymList_DeleteA(pList, 0, strings[5]);
        XCTAssertTrue( (ERESULT_OK(eRc)) );
        cnt = SymList_getSize(pList);
        XCTAssertTrue( (cnt == 9) );
        pSym = SymList_FindA(pList, 0, strings[11]);
        XCTAssertTrue( (OBJ_NIL == pSym) );
#endif

        obj_Release(pList);
        pList = OBJ_NIL;
        //szTbl_SharedReset();
    }

    fprintf(stderr, "...%s completed.\n\n\n\n", pTestName);
    return 1;
}



int         test_SymList_AddFindDelete02(
    const
    char        *pTestName
)
{
    SYMLIST_DATA    *pList;
    SYM_DATA        *pSym;
    SYM_DATA        *pSym2;
    int             i;
    int             iMax;
    uint32_t        cnt;
    ERESULT         eRc;

    fprintf(stderr, "Performing: %s\n", pTestName);

    pList = SymList_New( );
    XCTAssertFalse( (OBJ_NIL == pList) );
    if (pList) {

        //TODO: SymList_setOrdered(pList, true);

        iMax = 10;
        for (i=0; i<iMax; ++i) {
            char        *pNameA = NULL;
            pSym = Sym_NewA(0, strings[i]);
            pNameA = (char *)Sym_getNameA(pSym);
            fprintf(stderr, "\t\tAdding (%p) %s\n", pSym, pNameA);
            eRc = SymList_Add2Head(pList, pSym);
            XCTAssertTrue( (ERESULT_OK(eRc)) );
            cnt = SymList_getSize(pList);
            XCTAssertTrue( (cnt == (i+1)) );
            pSym2 = SymList_FindA(pList, 0, strings[i]);
            XCTAssertTrue( (pSym2) );
            obj_Release(pSym);
            pSym = OBJ_NIL;
        }
        fprintf(stderr, "\tAdded %d Syms to list.\n", iMax);


        cnt = SymList_getSize(pList);
        fprintf(stderr, "\n\tList Count = %d\n", cnt);
        XCTAssertTrue( (cnt == iMax) );
        for (i=0; i<iMax; i++) {
            char        *pNameA = NULL;
            pSym = SymList_Index(pList, i+1);
            pNameA = (char *)Sym_getNameA(pSym);
            fprintf(stderr, "\t\t%2d - %s\n", i+1, pNameA);
        }

        fprintf(stderr, "\nForEach:\n");
        SymList_ForEach(pList, (void *)listEntryPrintRtn, pList, NULL);

        pSym = SymList_Index(pList, 1);
        pSym2 = SymList_Index(pList, 1);
        i = Sym_Compare(pSym, pSym2);
        XCTAssertTrue( (i == 0) );
        pSym2 = SymList_Index(pList, 2);
        i = Sym_Compare(pSym, pSym2);
        XCTAssertTrue( (i > 0) );
        pSym = SymList_Index(pList, 6);
        pSym2 = SymList_Index(pList, 1);
        i = Sym_Compare(pSym, pSym2);
        XCTAssertTrue( (i < 0) );

        eRc = SymList_SortAscending(pList);
        XCTAssertTrue( (ERESULT_OK(eRc)) );

        cnt = SymList_getSize(pList);
        fprintf(stderr, "\n\tCount = %d\n", cnt);
        XCTAssertTrue( (cnt == iMax) );
        for (i=0; i<iMax; ++i) {
            char        *pNameA = NULL;
            pSym = SymList_Index(pList, i+1);
            pNameA = (char *)Sym_getNameA(pSym);
            fprintf(stderr, "\t\t%2d - %s\n", i+1, pNameA);
        }

        obj_Release(pList);
        pList = OBJ_NIL;
        //szTbl_SharedReset();
    }

    fprintf(stderr, "...%s completed.\n\n\n\n", pTestName);
    return 1;
}




TINYTEST_START_SUITE(test_SymList);
    TINYTEST_ADD_TEST(test_SymList_AddFindDelete02,setUp,tearDown);
    TINYTEST_ADD_TEST(test_SymList_AddFindDelete01,setUp,tearDown);
    TINYTEST_ADD_TEST(test_SymList_Test01,setUp,tearDown);
    //TINYTEST_ADD_TEST(test_SymList_Copy01,setUp,tearDown);
    TINYTEST_ADD_TEST(test_SymList_OpenClose,setUp,tearDown);
TINYTEST_END_SUITE();

TINYTEST_MAIN_SINGLE_SUITE(test_SymList);





