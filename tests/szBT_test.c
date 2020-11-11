// vi:nu:et:sts=4 ts=4 sw=4
/*
 *	Generated 02/25/2020 10:00:28
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
#include    <szBT_internal.h>
#ifdef  SZBT_JSON_SUPPORT
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

#ifdef  SZBT_JSON_SUPPORT
    SrcErrors_SharedReset( );
    szTbl_SharedReset( );
#endif
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






int             test_szBT_OpenClose (
    const
    char            *pTestName
)
{
    ERESULT         eRc = ERESULT_SUCCESS;
    SZBT_DATA	    *pObj = OBJ_NIL;
    bool            fRc;
   
    fprintf(stderr, "Performing: %s\n", pTestName);

    pObj = szBT_Alloc( );
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    pObj = szBT_Init( pObj );
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    if (pObj) {

        //obj_TraceSet(pObj, true);       
        fRc = obj_IsKindOf(pObj, OBJ_IDENT_SZBT);
        TINYTEST_TRUE( (fRc) );
        
        // Test something.
        TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );

        obj_Release(pObj);
        pObj = OBJ_NIL;
    }

    fprintf(stderr, "...%s completed.\n\n\n", pTestName);
    return 1;
}



int             test_szBT_Copy01 (
    const
    char            *pTestName
)
{
    ERESULT         eRc = ERESULT_SUCCESS;
    SZBT_DATA	    *pObj1 = OBJ_NIL;
    SZBT_DATA	    *pObj2 = OBJ_NIL;
    bool            fRc;
#if defined(SZBT_JSON_SUPPORT) && defined(XYZZY)
    ASTR_DATA	    *pStr = OBJ_NIL;
#endif
   
    fprintf(stderr, "Performing: %s\n", pTestName);

    pObj1 = szBT_New( );
    TINYTEST_FALSE( (OBJ_NIL == pObj1) );
    if (pObj1) {

        //obj_TraceSet(pObj1, true);       
        fRc = obj_IsKindOf(pObj1, OBJ_IDENT_SZBT);
        TINYTEST_TRUE( (fRc) );
        
        // Test assign.
        pObj2 = szBT_New();
        TINYTEST_FALSE( (OBJ_NIL == pObj2) );
        eRc = szBT_Assign(pObj1, pObj2);
        TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );

        fRc = obj_IsKindOf(pObj2, OBJ_IDENT_SZBT);
        TINYTEST_TRUE( (fRc) );
        //eRc = szBT_Compare(pObj1, pObj2);
        //TINYTEST_TRUE( (0 == eRc) );
        //TODO: Add More tests here!

        obj_Release(pObj2);
        pObj2 = OBJ_NIL;

        // Test copy.
        pObj2 = szBT_Copy(pObj1);
        TINYTEST_FALSE( (OBJ_NIL == pObj2) );

        fRc = obj_IsKindOf(pObj2, OBJ_IDENT_SZBT);
        TINYTEST_TRUE( (fRc) );
        //eRc = szBT_Compare(pObj1, pObj2);
        //TINYTEST_TRUE( (0 == eRc) );
        //TODO: Add More tests here!

        obj_Release(pObj2);
        pObj2 = OBJ_NIL;

        // Test json support.
#if defined(SZBT_JSON_SUPPORT) && defined(XYZZY)
        pStr = szBT_ToJson(pObj1);
        TINYTEST_FALSE( (OBJ_NIL == pStr) );
        fprintf(stderr, "JSON: %s\n", AStr_getData(pStr));
        pObj2 = szBT_NewFromJsonString(pStr);
        TINYTEST_FALSE( (OBJ_NIL == pObj2) );
        fRc = obj_IsKindOf(pObj2, OBJ_IDENT_SZBT);
        TINYTEST_TRUE( (fRc) );
        obj_Release(pStr);
        pStr = OBJ_NIL;
        //eRc = szBT_Compare(pObj1, pObj2);
        //TINYTEST_TRUE( (0 == eRc) );

        obj_Release(pObj2);
        pObj2 = OBJ_NIL;
#endif

        obj_Release(pObj1);
        pObj1 = OBJ_NIL;
    }

    fprintf(stderr, "...%s completed.\n\n\n", pTestName);
    return 1;
}



int             test_szBT_Test01 (
    const
    char            *pTestName
)
{
    ERESULT         eRc = ERESULT_SUCCESS;
    SZBT_DATA	    *pObj = OBJ_NIL;
    bool            fRc;
    uint32_t        i;
    uint32_t        cnt;
    char            *pNameA;
    char            *pWork;

    fprintf(stderr, "Performing: %s\n", pTestName);

    pObj = szBT_New( );
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    if (pObj) {

        //obj_TraceSet(pObj, true);       
        fRc = obj_IsKindOf(pObj, OBJ_IDENT_SZBT);
        TINYTEST_TRUE( (fRc) );
        
        for (i=0; i<20; ++i) {
            pNameA = strings[i];
            eRc = szBT_AddUpdateA(pObj, pNameA, pNameA);
            XCTAssertFalse( (ERESULT_FAILED(eRc)) );
            cnt = szBT_getSize(pObj);
            XCTAssertTrue( (cnt == (i+1)) );
            XCTAssertTrue( (pObj->unique == (i+2)) );
            fprintf(stderr, "\tAdded %s\n", strings[i]);
            fprintf(stderr, "\tLooking for: %s\n", strings[i]);
            pWork = szBT_FindA(pObj, strings[i]);
            XCTAssertTrue( (pWork) );
            fprintf(stderr, "\t\tFound\n");
        }

        for (i=0; i<20; ++i) {
            pNameA = strings[i];
            fprintf(stderr, "\tLooking for: %s\n", strings[i]);
            pWork = szBT_FindA(pObj, strings[i]);
            XCTAssertTrue( (pWork) );
            fprintf(stderr, "\t\tFound\n");
        }

        obj_Release(pObj);
        pObj = OBJ_NIL;
    }

    fprintf(stderr, "...%s completed.\n\n\n", pTestName);
    return 1;
}




TINYTEST_START_SUITE(test_szBT);
    TINYTEST_ADD_TEST(test_szBT_Test01,setUp,tearDown);
    //TINYTEST_ADD_TEST(test_szBT_Copy01,setUp,tearDown);
    TINYTEST_ADD_TEST(test_szBT_OpenClose,setUp,tearDown);
TINYTEST_END_SUITE();

TINYTEST_MAIN_SINGLE_SUITE(test_szBT);





