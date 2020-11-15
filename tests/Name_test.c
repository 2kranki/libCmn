// vi:nu:et:sts=4 ts=4 sw=4
/*
 *	Generated 01/11/2020 10:01:40
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
#include    <SrcErrors.h>
#include    <szTbl.h>
#include    <trace.h>
#include    <Name_internal.h>



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






int             test_Name_OpenClose (
    const
    char            *pTestName
)
{
    ERESULT         eRc = ERESULT_SUCCESS;
    NAME_DATA	    *pObj = OBJ_NIL;
    bool            fRc;
   
    fprintf(stderr, "Performing: %s\n", pTestName);

    pObj = Name_Alloc( );
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    pObj = Name_Init( pObj );
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    if (pObj) {

        //obj_TraceSet(pObj, true);       
        fRc = obj_IsKindOf(pObj, OBJ_IDENT_NAME);
        TINYTEST_TRUE( (fRc) );
        
        // Test something.
        TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );

        obj_Release(pObj);
        pObj = OBJ_NIL;
    }

    fprintf(stderr, "...%s completed.\n\n\n", pTestName);
    return 1;
}



int             test_Name_Copy01 (
    const
    char            *pTestName
)
{
    ERESULT         eRc = ERESULT_SUCCESS;
    NAME_DATA       *pObj1 = OBJ_NIL;
    NAME_DATA       *pObj2 = OBJ_NIL;
    bool            fRc;
    ASTR_DATA       *pStr = OBJ_NIL;

    fprintf(stderr, "Performing: %s\n", pTestName);

    pObj1 = Name_NewUTF8("abc");
    TINYTEST_FALSE( (OBJ_NIL == pObj1) );
    if (pObj1) {

        //obj_TraceSet(pObj1, true);
        fRc = obj_IsKindOf(pObj1, OBJ_IDENT_NAME);
        TINYTEST_TRUE( (fRc) );

        // Test assign.
        pObj2 = Name_New();
        TINYTEST_FALSE( (OBJ_NIL == pObj2) );
        eRc = Name_Assign(pObj1, pObj2);
        TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );

        fRc = obj_IsKindOf(pObj2, OBJ_IDENT_NAME);
        TINYTEST_TRUE( (fRc) );
        eRc = Name_Compare(pObj1, pObj2);
        TINYTEST_TRUE( (0 == eRc) );

        obj_Release(pObj2);
        pObj2 = OBJ_NIL;

        // Test copy.
        pObj2 = Name_Copy(pObj1);
        TINYTEST_FALSE( (OBJ_NIL == pObj2) );

        fRc = obj_IsKindOf(pObj2, OBJ_IDENT_NAME);
        TINYTEST_TRUE( (fRc) );
        eRc = Name_Compare(pObj1, pObj2);
        TINYTEST_TRUE( (0 == eRc) );

        obj_Release(pObj2);
        pObj2 = OBJ_NIL;

        // Test json support.
        pStr = Name_ToJson(pObj1);
        TINYTEST_FALSE( (OBJ_NIL == pStr) );
        fprintf(stderr, "JSON: %s\n", AStr_getData(pStr));
        pObj2 = Name_NewFromJsonString(pStr);
        TINYTEST_FALSE( (OBJ_NIL == pObj2) );
        fRc = obj_IsKindOf(pObj2, OBJ_IDENT_NAME);
        TINYTEST_TRUE( (fRc) );
        obj_Release(pStr);
        pStr = OBJ_NIL;
        eRc = Name_Compare(pObj1, pObj2);
        TINYTEST_TRUE( (0 == eRc) );

        obj_Release(pObj2);
        pObj2 = OBJ_NIL;

        obj_Release(pObj1);
        pObj1 = OBJ_NIL;
    }

    fprintf(stderr, "...%s completed.\n\n\n", pTestName);
    return 1;
}



int             test_Name_Test01 (
    const
    char            *pTestName
)
{
    NAME_DATA   *pName1 = OBJ_NIL;
    ASTR_DATA   *pAStr1 = OBJ_NIL;
    ERESULT     eRc;
    const
    char        *pChrs = NULL;
    NAME_DATA   *pName2 = OBJ_NIL;
    ASTR_DATA   *pJSON = OBJ_NIL;
    uint16_t    type1;
    uint16_t    type2;

    fprintf(stderr, "Performing: %s\n", pTestName);

    pAStr1 = AStr_NewA("abc");
    XCTAssertFalse( (OBJ_NIL == pAStr1) );
    pName1 = Name_NewAStr(pAStr1);
    XCTAssertFalse( (OBJ_NIL == pName1) );
    obj_Release(pAStr1);
    pAStr1 = OBJ_NIL;
    if (pName1) {

        pAStr1 = Name_getStr(pName1);
        XCTAssertTrue( (0 == AStr_CompareA(pAStr1, "abc")) );
        obj_Release(pAStr1);
        pAStr1 = OBJ_NIL;

        pChrs = Name_getUTF8(pName1);
        XCTAssertTrue( (0 == str_Compare("abc", pChrs)) );
        mem_Free((void *)pChrs);
        pChrs = NULL;

        pJSON = Name_ToJson(pName1);
        XCTAssertFalse( (OBJ_NIL == pJSON) );
        fprintf(stderr, "\tJSON=\"%s\"\n", AStr_getData(pJSON));
        //eRc = AStr_CompareA(pJSON, pJSON01);
        //XCTAssertTrue( (0 == eRc) );

        pName2 = Name_NewFromJsonString(pJSON);
        eRc = Name_CompareA(pName2, "abc");
        XCTAssertTrue( (0 == eRc) );
        obj_Release(pJSON);
        pJSON = OBJ_NIL;

        type1 = pName1->type;
        type2 = pName2->type;
        fprintf(stderr, "\tType1=%d  Type2=%d\n", type1, type2);
        XCTAssertTrue( (NAME_TYPE_ASTR == type2) );

        obj_Release(pName2);
        pName2 = OBJ_NIL;

        pName2 = Name_Copy(pName1);
        XCTAssertFalse( (OBJ_NIL == pName2) );
        eRc = Name_CompareA(pName2, "abc");
        XCTAssertTrue( (0 == eRc) );

        obj_Release(pName2);
        pName2 = OBJ_NIL;

        pName2 = Name_DeepCopy(pName1);
        XCTAssertFalse( (OBJ_NIL == pName2) );
        eRc = Name_CompareA(pName2, "abc");
        XCTAssertTrue( (0 == eRc) );

        obj_Release(pName2);
        pName2 = OBJ_NIL;

        obj_Release(pName1);
        pName1 = OBJ_NIL;
    }

    fprintf(stderr, "...%s completed.\n\n\n", pTestName);
    return 1;
}



int         test_Name_UTF8(
    const
    char        *pTestName
)
{
    NAME_DATA   *pName1 = OBJ_NIL;
    ASTR_DATA   *pAStr1 = OBJ_NIL;
    ERESULT     eRc;
    const
    char        *pChrs = NULL;
    NAME_DATA   *pName2 = OBJ_NIL;
    ASTR_DATA   *pJSON = OBJ_NIL;
    uint16_t    type1;
    uint16_t    type2;

    fprintf(stderr, "Performing: %s\n", pTestName);

    pName1 = Name_NewUTF8( "abc" );
    XCTAssertFalse( (OBJ_NIL == pName1) );
    if (pName1) {

        pAStr1 = Name_getStr(pName1);
        XCTAssertTrue( (0 == AStr_CompareA(pAStr1, "abc")) );
        obj_Release(pAStr1);
        pAStr1 = OBJ_NIL;

        pChrs = Name_getUTF8(pName1);
        XCTAssertTrue( (0 == str_Compare("abc", pChrs)) );
        mem_Free((void *)pChrs);
        pChrs = NULL;

        pJSON = Name_ToJson(pName1);
        XCTAssertFalse( (OBJ_NIL == pJSON) );
        fprintf(stderr, "\tJSON=\"%s\"\n", AStr_getData(pJSON));
        //eRc = AStr_CompareA(pJSON, pJSON01);
        //XCTAssertTrue( (0 == eRc) );

        pName2 = Name_NewFromJsonString(pJSON);
        eRc = Name_CompareA(pName2, "abc");
        XCTAssertTrue( (0 == eRc) );
        obj_Release(pJSON);
        pJSON = OBJ_NIL;

        type1 = pName1->type;
        type2 = pName2->type;
        fprintf(stderr, "\tType1=%d  Type2=%d\n", type1, type2);
        XCTAssertTrue( (NAME_TYPE_UTF8 == type2) );

        obj_Release(pName2);
        pName2 = OBJ_NIL;

        pName2 = Name_Copy(pName1);
        XCTAssertFalse( (OBJ_NIL == pName2) );
        eRc = Name_CompareA(pName2, "abc");
        XCTAssertTrue( (0 == eRc) );

        obj_Release(pName2);
        pName2 = OBJ_NIL;

        pName2 = Name_DeepCopy(pName1);
        XCTAssertFalse( (OBJ_NIL == pName2) );
        eRc = Name_CompareA(pName2, "abc");
        XCTAssertTrue( (0 == eRc) );

        obj_Release(pName2);
        pName2 = OBJ_NIL;

        obj_Release(pName1);
        pName1 = OBJ_NIL;
    }

    fprintf(stderr, "...%s completed.\n\n\n", pTestName);
    return 1;
}



int         test_Name_UTF8Con(
    const
    char        *pTestName
)
{
    NAME_DATA   *pName1 = OBJ_NIL;
    ASTR_DATA   *pAStr1 = OBJ_NIL;
    const
    char        *pChrs = NULL;
    ERESULT     eRc;
    NAME_DATA   *pName2 = OBJ_NIL;
    ASTR_DATA   *pJSON = OBJ_NIL;
    uint16_t    type1;
    uint16_t    type2;

    fprintf(stderr, "Performing: %s\n", pTestName);
    pName1 = Name_NewUTF8Con( "abc" );
    XCTAssertFalse( (OBJ_NIL == pName1) );
    if (pName1) {

        pAStr1 = Name_getStr(pName1);
        XCTAssertTrue( (0 == AStr_CompareA(pAStr1, "abc")) );
        obj_Release(pAStr1);
        pAStr1 = OBJ_NIL;

        pChrs = Name_getUTF8(pName1);
        XCTAssertTrue( (0 == str_Compare("abc", pChrs)) );
        mem_Free((void *)pChrs);
        pChrs = NULL;

        pJSON = Name_ToJson(pName1);
        XCTAssertFalse( (OBJ_NIL == pJSON) );
        fprintf(stderr, "\tJSON=\"%s\"\n", AStr_getData(pJSON));
        //eRc = AStr_CompareA(pJSON, pJSON01);
        //XCTAssertTrue( (0 == eRc) );

        pName2 = Name_NewFromJsonString(pJSON);
        eRc = Name_CompareA(pName2, "abc");
        XCTAssertTrue( (0 == eRc) );
        obj_Release(pJSON);
        pJSON = OBJ_NIL;

        type1 = pName1->type;
        type2 = pName2->type;
        fprintf(stderr, "\tType1=%d  Type2=%d\n", type1, type2);
        XCTAssertTrue( (NAME_TYPE_UTF8 == type2) );

        obj_Release(pName2);
        pName2 = OBJ_NIL;

        pName2 = Name_Copy(pName1);
        XCTAssertFalse( (OBJ_NIL == pName2) );
        eRc = Name_CompareA(pName2, "abc");
        XCTAssertTrue( (0 == eRc) );

        obj_Release(pName2);
        pName2 = OBJ_NIL;

        pName2 = Name_DeepCopy(pName1);
        XCTAssertFalse( (OBJ_NIL == pName2) );
        eRc = Name_CompareA(pName2, "abc");
        XCTAssertTrue( (0 == eRc) );

        obj_Release(pName2);
        pName2 = OBJ_NIL;

        obj_Release(pName1);
        pName1 = OBJ_NIL;
    }

    fprintf(stderr, "...%s completed.\n\n\n", pTestName);
    return 1;
}



int         test_Name_Int(
    const
    char        *pTestName
)
{
    NAME_DATA   *pName1 = OBJ_NIL;
    ASTR_DATA   *pAStr1 = OBJ_NIL;
    ERESULT     eRc;
    NAME_DATA   *pName2 = OBJ_NIL;
    ASTR_DATA   *pJSON = OBJ_NIL;
    uint16_t    type1;
    uint16_t    type2;


    fprintf(stderr, "Performing: %s\n", pTestName);
    pName1 = Name_NewInt( 123456 );
    XCTAssertFalse( (OBJ_NIL == pName1) );
    if (pName1) {

        pAStr1 = Name_getStr(pName1);
        fprintf(stderr, "strA = \"%s\"\n", AStr_getData(pAStr1));
        eRc = AStr_CompareA(pAStr1, "0000000000000123456");
        XCTAssertTrue( (0 == eRc) );
        obj_Release(pAStr1);
        pAStr1 = OBJ_NIL;

        pJSON = Name_ToJson(pName1);
        XCTAssertFalse( (OBJ_NIL == pJSON) );
        fprintf(stderr, "\tJSON=\"%s\"\n", AStr_getData(pJSON));
        //eRc = AStr_CompareA(pJSON, pJSON01);
        //XCTAssertTrue( (0 == eRc) );

        pName2 = Name_NewFromJsonString(pJSON);
        eRc = Name_CompareA(pName2, "123456");
        XCTAssertTrue( (0 == eRc) );
        obj_Release(pJSON);
        pJSON = OBJ_NIL;

        type1 = pName1->type;
        type2 = pName2->type;
        fprintf(stderr, "\tType1=%d  Type2=%d\n", type1, type2);
        XCTAssertTrue( (NAME_TYPE_INTEGER == type2) );

        obj_Release(pName2);
        pName2 = OBJ_NIL;

        pName2 = Name_Copy(pName1);
        XCTAssertFalse( (OBJ_NIL == pName2) );
        eRc = Name_CompareA(pName2, "123456");
        XCTAssertTrue( (0 == eRc) );

        obj_Release(pName2);
        pName2 = OBJ_NIL;

        pName2 = Name_DeepCopy(pName1);
        XCTAssertFalse( (OBJ_NIL == pName2) );
        eRc = Name_CompareA(pName2, "123456");
        XCTAssertTrue( (0 == eRc) );

        obj_Release(pName2);
        pName2 = OBJ_NIL;

        obj_Release(pName1);
        pName1 = OBJ_NIL;
    }

    fprintf(stderr, "...%s completed.\n\n\n", pTestName);
    return 1;
}




TINYTEST_START_SUITE(test_Name);
    TINYTEST_ADD_TEST(test_Name_Int,setUp,tearDown);
    TINYTEST_ADD_TEST(test_Name_UTF8Con,setUp,tearDown);
    TINYTEST_ADD_TEST(test_Name_UTF8,setUp,tearDown);
    TINYTEST_ADD_TEST(test_Name_Test01,setUp,tearDown);
    TINYTEST_ADD_TEST(test_Name_Copy01,setUp,tearDown);
    TINYTEST_ADD_TEST(test_Name_OpenClose,setUp,tearDown);
TINYTEST_END_SUITE();

TINYTEST_MAIN_SINGLE_SUITE(test_Name);





