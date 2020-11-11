// vi:nu:et:sts=4 ts=4 sw=4
/*
 *	Generated 02/22/2020 20:18:16
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
#include    <Syms_internal.h>
#ifdef  SYMS_JSON_SUPPORT
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

#ifdef  SYMS_JSON_SUPPORT
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






int             test_Syms_OpenClose (
    const
    char            *pTestName
)
{
    ERESULT         eRc = ERESULT_SUCCESS;
    SYMS_DATA	    *pObj = OBJ_NIL;
    bool            fRc;
   
    fprintf(stderr, "Performing: %s\n", pTestName);

    pObj = Syms_Alloc( );
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    pObj = Syms_Init( pObj );
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    if (pObj) {

        //obj_TraceSet(pObj, true);       
        fRc = obj_IsKindOf(pObj, OBJ_IDENT_SYMS);
        TINYTEST_TRUE( (fRc) );
        
        // Test something.
        TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );

        obj_Release(pObj);
        pObj = OBJ_NIL;
    }

    fprintf(stderr, "...%s completed.\n\n\n", pTestName);
    return 1;
}



int             test_Syms_Copy01 (
    const
    char            *pTestName
)
{
    ERESULT         eRc = ERESULT_SUCCESS;
    SYMS_DATA	    *pObj1 = OBJ_NIL;
    SYMS_DATA	    *pObj2 = OBJ_NIL;
    bool            fRc;
#if defined(SYMS_JSON_SUPPORT) && defined(XYZZY)
    ASTR_DATA	    *pStr = OBJ_NIL;
#endif
   
    fprintf(stderr, "Performing: %s\n", pTestName);

    pObj1 = Syms_New( );
    TINYTEST_FALSE( (OBJ_NIL == pObj1) );
    if (pObj1) {

        //obj_TraceSet(pObj1, true);       
        fRc = obj_IsKindOf(pObj1, OBJ_IDENT_SYMS);
        TINYTEST_TRUE( (fRc) );
        
        // Test assign.
        pObj2 = Syms_New();
        TINYTEST_FALSE( (OBJ_NIL == pObj2) );
        eRc = Syms_Assign(pObj1, pObj2);
        TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );

        fRc = obj_IsKindOf(pObj2, OBJ_IDENT_SYMS);
        TINYTEST_TRUE( (fRc) );
        //eRc = Syms_Compare(pObj1, pObj2);
        //TINYTEST_TRUE( (0 == eRc) );
        //TODO: Add More tests here!

        obj_Release(pObj2);
        pObj2 = OBJ_NIL;

        // Test copy.
        pObj2 = Syms_Copy(pObj1);
        TINYTEST_FALSE( (OBJ_NIL == pObj2) );

        fRc = obj_IsKindOf(pObj2, OBJ_IDENT_SYMS);
        TINYTEST_TRUE( (fRc) );
        //eRc = Syms_Compare(pObj1, pObj2);
        //TINYTEST_TRUE( (0 == eRc) );
        //TODO: Add More tests here!

        obj_Release(pObj2);
        pObj2 = OBJ_NIL;

        // Test json support.
#if defined(SYMS_JSON_SUPPORT) && defined(XYZZY)
        pStr = Syms_ToJson(pObj1);
        TINYTEST_FALSE( (OBJ_NIL == pStr) );
        fprintf(stderr, "JSON: %s\n", AStr_getData(pStr));
        pObj2 = Syms_NewFromJsonString(pStr);
        TINYTEST_FALSE( (OBJ_NIL == pObj2) );
        fRc = obj_IsKindOf(pObj2, OBJ_IDENT_SYMS);
        TINYTEST_TRUE( (fRc) );
        obj_Release(pStr);
        pStr = OBJ_NIL;
        //eRc = Syms_Compare(pObj1, pObj2);
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



int             test_Syms_Test01 (
    const
    char            *pTestName
)
{
    ERESULT         eRc = ERESULT_SUCCESS;
    SYMS_DATA	    *pObj = OBJ_NIL;
    bool            fRc;
    SYM_DATA        *pSym;
    SYM_DATA        *pSymFnd;
    uint32_t        i;
    uint32_t        cnt;
    ASTR_DATA       *pStr;

    fprintf(stderr, "Performing: %s\n", pTestName);

    pObj = Syms_New( );
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    if (pObj) {

        //obj_TraceSet(pObj, true);       
        fRc = obj_IsKindOf(pObj, OBJ_IDENT_SYMS);
        TINYTEST_TRUE( (fRc) );
        
        for (i=0; i<33; ++i) {
            pSym = Sym_NewA(0, strings[i]);
            TINYTEST_FALSE( (OBJ_NIL == pSym) );
            eRc = Syms_Add(pObj, pSym);
            XCTAssertFalse( (ERESULT_FAILED(eRc)) );
            cnt = Syms_getSize(pObj);
            XCTAssertTrue( (cnt == (i+1)) );
            fprintf(stderr, "\tAdded %p - %s\n", pSym, strings[i]);
            fprintf(stderr, "\tLooking for: %s\n", strings[i]);
            pSymFnd = Syms_FindA(pObj, 0, strings[i]);
            XCTAssertTrue( (pSymFnd) );
            fprintf(stderr, "\t\tFound\n");
            obj_Release(pSym);
            pSym = OBJ_NIL;
        }

        pStr = Syms_ToDebugString(pObj, 0);
        if (pStr) {
            fprintf(stderr, "DEBUG:\n%s\n", AStr_getData(pStr));
            obj_Release(pStr);
            pStr = OBJ_NIL;
        }
    
        obj_Release(pObj);
        pObj = OBJ_NIL;
    }

    fprintf(stderr, "...%s completed.\n\n\n", pTestName);
    return 1;
}




TINYTEST_START_SUITE(test_Syms);
    TINYTEST_ADD_TEST(test_Syms_Test01,setUp,tearDown);
    //TINYTEST_ADD_TEST(test_Syms_Copy01,setUp,tearDown);
    TINYTEST_ADD_TEST(test_Syms_OpenClose,setUp,tearDown);
TINYTEST_END_SUITE();

TINYTEST_MAIN_SINGLE_SUITE(test_Syms);





