// vi:nu:et:sts=4 ts=4 sw=4
/*
 *  Generated 07/08/2021 09:13:40
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
#include    <Base64_internal.h>
#include    <JsonIn.h>
#ifdef  BASE64_JSON_SUPPORT
#   include    <SrcErrors.h>
#   include    <szTbl.h>
#endif



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

#ifdef  BASE64_JSON_SUPPORT
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






int             test_Base64_OpenClose (
    const
    char            *pTestName
)
{
    ERESULT         eRc = ERESULT_SUCCESS;
    BASE64_DATA       *pObj = OBJ_NIL;
    bool            fRc;
   
    fprintf(stderr, "Performing: %s\n", pTestName);

    pObj = Base64_Alloc( );
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    pObj = Base64_Init( pObj );
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    if (pObj) {

        //obj_TraceSet(pObj, true);       
        fRc = obj_IsKindOf(pObj, OBJ_IDENT_BASE64);
        TINYTEST_TRUE( (fRc) );
        
        // Test something.
        TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );

        obj_Release(pObj);
        pObj = OBJ_NIL;
    }

    fprintf(stderr, "...%s completed.\n\n\n", pTestName);
    return 1;
}



int             test_Base64_Copy01 (
    const
    char            *pTestName
)
{
    ERESULT         eRc = ERESULT_SUCCESS;
    BASE64_DATA       *pObj1 = OBJ_NIL;
    BASE64_DATA       *pObj2 = OBJ_NIL;
    bool            fRc;
#if defined(BASE64_JSON_SUPPORT) && defined(XYZZY)
    ASTR_DATA       *pStr = OBJ_NIL;
#endif
    //int             iRc;
   
    fprintf(stderr, "Performing: %s\n", pTestName);

    pObj1 = Base64_New( );
    TINYTEST_FALSE( (OBJ_NIL == pObj1) );
    if (pObj1) {

        //obj_TraceSet(pObj1, true);       
        fRc = obj_IsKindOf(pObj1, OBJ_IDENT_BASE64);
        TINYTEST_TRUE( (fRc) );
        
        // Test assign.
        pObj2 = Base64_New();
        TINYTEST_FALSE( (OBJ_NIL == pObj2) );
        eRc = Base64_Assign(pObj1, pObj2);
        TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );

        fRc = obj_IsKindOf(pObj2, OBJ_IDENT_BASE64);
        TINYTEST_TRUE( (fRc) );
        //iRc = Base64_Compare(pObj1, pObj2);
        //TINYTEST_TRUE( (0 == iRc) );
        //TODO: Add More tests here!

        obj_Release(pObj2);
        pObj2 = OBJ_NIL;

        // Test copy.
        pObj2 = Base64_Copy(pObj1);
        TINYTEST_FALSE( (OBJ_NIL == pObj2) );

        fRc = obj_IsKindOf(pObj2, OBJ_IDENT_BASE64);
        TINYTEST_TRUE( (fRc) );
        //iRc = Base64_Compare(pObj1, pObj2);
        //TINYTEST_TRUE( (0 == iRc) );
        //TODO: Add More tests here!

        obj_Release(pObj2);
        pObj2 = OBJ_NIL;

        // Test json support.
#if defined(BASE64_JSON_SUPPORT) && defined(XYZZY)
        pStr = Base64_ToJson(pObj1);
        TINYTEST_FALSE( (OBJ_NIL == pStr) );
        fprintf(stderr, "JSON: %s\n", AStr_getData(pStr));
        pObj2 = Base64_NewFromJsonString(pStr);
        TINYTEST_FALSE( (OBJ_NIL == pObj2) );
        fRc = obj_IsKindOf(pObj2, OBJ_IDENT_BASE64);
        TINYTEST_TRUE( (fRc) );
        obj_Release(pStr);
        pStr = OBJ_NIL;
        //iRc = Base64_Compare(pObj1, pObj2);
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



int             test_Base64_Test01 (
    const
    char            *pTestName
)
{
    //ERESULT         eRc = ERESULT_SUCCESS;
    BASE64_DATA     *pObj = OBJ_NIL;
    bool            fRc;
    const
    char            *pData = "Man";
    const
    char            *pBase64 = "TWFu";
    ASTR_DATA       *pStr = OBJ_NIL;
    U8ARRAY_DATA    *pArray = OBJ_NIL;
    int             i;
   
    fprintf(stderr, "Performing: %s\n", pTestName);

    pObj = Base64_New( );
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    if (pObj) {

        obj_TraceSet(pObj, true);
        fRc = obj_IsKindOf(pObj, OBJ_IDENT_BASE64);
        TINYTEST_TRUE( (fRc) );
        //TINYTEST_TRUE( (ERESULT_OK(eRc)) );

        fprintf(stderr, "\tInput    : (%d)\"%s\"\n", (int)strlen(pData), pData);
        fprintf(stderr, "\tShould be: (%d)\"%s\"\n", (int)strlen(pBase64), pBase64);
        pStr = Base64_EncodeData((int)strlen(pData), (void *)pData);
        TINYTEST_FALSE( (OBJ_NIL == pStr) );
        fprintf(stderr, "\tBase64   : (%d)\"%s\"\n\n", AStr_getSize(pStr), AStr_getData(pStr));
        i = AStr_CompareA(pStr, pBase64);
        TINYTEST_TRUE( (0 == i) );
        obj_Release(pStr);
        pStr = OBJ_NIL;

        fprintf(stderr, "\tInput    : (%d)\"%s\"\n", (int)strlen(pBase64), pBase64);
        fprintf(stderr, "\tShould be: (%d)\"%s\"\n", (int)strlen(pData), pData);
        pArray = Base64_DecodeData((int)strlen(pBase64), (void *)pBase64);
        TINYTEST_FALSE( (OBJ_NIL == pArray) );
        pStr = u8Array_ToString(pArray);
        TINYTEST_FALSE( (OBJ_NIL == pStr) );
        fprintf(stderr, "\tData     : (%d)\"%s\"\n", AStr_getSize(pStr), AStr_getData(pStr));
        i = AStr_CompareA(pStr, pData);
        TINYTEST_TRUE( (0 == i) );
        obj_Release(pStr);
        pStr = OBJ_NIL;
        obj_Release(pArray);
        pArray = OBJ_NIL;

        {
            ASTR_DATA       *pStr = Base64_ToDebugString(pObj, 4);
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



int             test_Base64_Test02 (
    const
    char            *pTestName
)
{
    //ERESULT         eRc = ERESULT_SUCCESS;
    BASE64_DATA     *pObj = OBJ_NIL;
    bool            fRc;
    const
    char            *pData = "pleasure.";
    const
    char            *pBase64 = "cGxlYXN1cmUu";
    ASTR_DATA       *pStr = OBJ_NIL;
    U8ARRAY_DATA    *pArray = OBJ_NIL;
    int             i;

    fprintf(stderr, "Performing: %s\n", pTestName);

    pObj = Base64_New( );
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    if (pObj) {

        obj_TraceSet(pObj, true);
        fRc = obj_IsKindOf(pObj, OBJ_IDENT_BASE64);
        TINYTEST_TRUE( (fRc) );
        //TINYTEST_TRUE( (ERESULT_OK(eRc)) );

        fprintf(stderr, "\tInput    : (%d)\"%s\"\n", (int)strlen(pData), pData);
        fprintf(stderr, "\tShould be: (%d)\"%s\"\n", (int)strlen(pBase64), pBase64);
        pStr = Base64_EncodeData((int)strlen(pData), (void *)pData);
        TINYTEST_FALSE( (OBJ_NIL == pStr) );
        fprintf(stderr, "\tBase64   : (%d)\"%s\"\n", AStr_getSize(pStr), AStr_getData(pStr));
        i = AStr_CompareA(pStr, pBase64);
        TINYTEST_TRUE( (0 == i) );
        obj_Release(pStr);
        pStr = OBJ_NIL;

        {
            ASTR_DATA       *pStr = Base64_ToDebugString(pObj, 4);
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



int             test_Base64_Test03 (
    const
    char            *pTestName
)
{
    //ERESULT         eRc = ERESULT_SUCCESS;
    BASE64_DATA     *pObj = OBJ_NIL;
    bool            fRc;
    const
    char            *pData0 = "leasure.";
    const
    char            *pBase64_0 = "bGVhc3VyZS4=";
    const
    char            *pData1 = "easure.";
    const
    char            *pBase64_1 = "ZWFzdXJlLg==";
    const
    char            *pData2 = "asure.";
    const
    char            *pBase64_2 = "YXN1cmUu";
    const
    char            *pData3 = "sure.";
    const
    char            *pBase64_3 = "c3VyZS4=";
    ASTR_DATA       *pStr = OBJ_NIL;
    U8ARRAY_DATA    *pArray = OBJ_NIL;
    int             i;

    fprintf(stderr, "Performing: %s\n", pTestName);

    pObj = Base64_New( );
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    if (pObj) {

        obj_TraceSet(pObj, true);
        fRc = obj_IsKindOf(pObj, OBJ_IDENT_BASE64);
        TINYTEST_TRUE( (fRc) );
        //TINYTEST_TRUE( (ERESULT_OK(eRc)) );

        fprintf(stderr, "\tInput    : (%d)\"%s\"\n", (int)strlen(pData0), pData0);
        fprintf(stderr, "\tShould be: (%d)\"%s\"\n", (int)strlen(pBase64_0), pBase64_0);
        pStr = Base64_EncodeData((int)strlen(pData0), (void *)pData0);
        TINYTEST_FALSE( (OBJ_NIL == pStr) );
        fprintf(stderr, "\tBase64   : (%d)\"%s\"\n", AStr_getSize(pStr), AStr_getData(pStr));
        i = AStr_CompareA(pStr, pBase64_0);
        TINYTEST_TRUE( (0 == i) );
        obj_Release(pStr);
        pStr = OBJ_NIL;

        fprintf(stderr, "\tInput    : (%d)\"%s\"\n", (int)strlen(pData1), pData1);
        fprintf(stderr, "\tShould be: (%d)\"%s\"\n", (int)strlen(pBase64_1), pBase64_1);
        pStr = Base64_EncodeData((int)strlen(pData1), (void *)pData1);
        TINYTEST_FALSE( (OBJ_NIL == pStr) );
        fprintf(stderr, "\tBase64   : (%d)\"%s\"\n", AStr_getSize(pStr), AStr_getData(pStr));
        i = AStr_CompareA(pStr, pBase64_1);
        TINYTEST_TRUE( (0 == i) );
        obj_Release(pStr);
        pStr = OBJ_NIL;

        fprintf(stderr, "\tInput    : (%d)\"%s\"\n", (int)strlen(pData2), pData2);
        fprintf(stderr, "\tShould be: (%d)\"%s\"\n", (int)strlen(pBase64_2), pBase64_2);
        pStr = Base64_EncodeData((int)strlen(pData2), (void *)pData2);
        TINYTEST_FALSE( (OBJ_NIL == pStr) );
        fprintf(stderr, "\tBase64   : (%d)\"%s\"\n", AStr_getSize(pStr), AStr_getData(pStr));
        i = AStr_CompareA(pStr, pBase64_2);
        TINYTEST_TRUE( (0 == i) );
        obj_Release(pStr);
        pStr = OBJ_NIL;

        fprintf(stderr, "\tInput    : (%d)\"%s\"\n", (int)strlen(pData3), pData3);
        fprintf(stderr, "\tShould be: (%d)\"%s\"\n", (int)strlen(pBase64_3), pBase64_3);
        pStr = Base64_EncodeData((int)strlen(pData3), (void *)pData3);
        TINYTEST_FALSE( (OBJ_NIL == pStr) );
        fprintf(stderr, "\tBase64   : (%d)\"%s\"\n", AStr_getSize(pStr), AStr_getData(pStr));
        i = AStr_CompareA(pStr, pBase64_3);
        TINYTEST_TRUE( (0 == i) );
        obj_Release(pStr);
        pStr = OBJ_NIL;

        fprintf(stderr, "\tInput    : (%d)\"%s\"\n", (int)strlen(pBase64_0), pBase64_0);
        fprintf(stderr, "\tShould be: (%d)\"%s\"\n", (int)strlen(pData0), pData0);
        pArray = Base64_DecodeData((int)strlen(pBase64_0), (void *)pBase64_0);
        TINYTEST_FALSE( (OBJ_NIL == pArray) );
        pStr = u8Array_ToString(pArray);
        TINYTEST_FALSE( (OBJ_NIL == pStr) );
        fprintf(stderr, "\tData     : (%d)\"%s\"\n", AStr_getSize(pStr), AStr_getData(pStr));
        i = AStr_CompareA(pStr, pData0);
        TINYTEST_TRUE( (0 == i) );
        obj_Release(pStr);
        pStr = OBJ_NIL;
        obj_Release(pArray);
        pArray = OBJ_NIL;

        fprintf(stderr, "\tInput    : (%d)\"%s\"\n", (int)strlen(pBase64_1), pBase64_1);
        fprintf(stderr, "\tShould be: (%d)\"%s\"\n", (int)strlen(pData1), pData1);
        pArray = Base64_DecodeData((int)strlen(pBase64_1), (void *)pBase64_1);
        TINYTEST_FALSE( (OBJ_NIL == pArray) );
        pStr = u8Array_ToString(pArray);
        TINYTEST_FALSE( (OBJ_NIL == pStr) );
        fprintf(stderr, "\tData     : (%d)\"%s\"\n", AStr_getSize(pStr), AStr_getData(pStr));
        i = AStr_CompareA(pStr, pData1);
        TINYTEST_TRUE( (0 == i) );
        obj_Release(pStr);
        pStr = OBJ_NIL;
        obj_Release(pArray);
        pArray = OBJ_NIL;

        fprintf(stderr, "\tInput    : (%d)\"%s\"\n", (int)strlen(pBase64_2), pBase64_2);
        fprintf(stderr, "\tShould be: (%d)\"%s\"\n", (int)strlen(pData2), pData2);
        pArray = Base64_DecodeData((int)strlen(pBase64_2), (void *)pBase64_2);
        TINYTEST_FALSE( (OBJ_NIL == pArray) );
        pStr = u8Array_ToString(pArray);
        TINYTEST_FALSE( (OBJ_NIL == pStr) );
        fprintf(stderr, "\tData     : (%d)\"%s\"\n", AStr_getSize(pStr), AStr_getData(pStr));
        i = AStr_CompareA(pStr, pData2);
        TINYTEST_TRUE( (0 == i) );
        obj_Release(pStr);
        pStr = OBJ_NIL;
        obj_Release(pArray);
        pArray = OBJ_NIL;

        fprintf(stderr, "\tInput    : (%d)\"%s\"\n", (int)strlen(pBase64_3), pBase64_3);
        fprintf(stderr, "\tShould be: (%d)\"%s\"\n", (int)strlen(pData3), pData3);
        pArray = Base64_DecodeData((int)strlen(pBase64_3), (void *)pBase64_3);
        TINYTEST_FALSE( (OBJ_NIL == pArray) );
        pStr = u8Array_ToString(pArray);
        TINYTEST_FALSE( (OBJ_NIL == pStr) );
        fprintf(stderr, "\tData     : (%d)\"%s\"\n", AStr_getSize(pStr), AStr_getData(pStr));
        i = AStr_CompareA(pStr, pData3);
        TINYTEST_TRUE( (0 == i) );
        obj_Release(pStr);
        pStr = OBJ_NIL;
        obj_Release(pArray);
        pArray = OBJ_NIL;

        {
            ASTR_DATA       *pStr = Base64_ToDebugString(pObj, 4);
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



int             test_Base64_Test04 (
    const
    char            *pTestName
)
{
    //ERESULT         eRc = ERESULT_SUCCESS;
    BASE64_DATA     *pObj = OBJ_NIL;
    bool            fRc;
    const
    char            *pData = "any carnal pleasure";
    const
    char            *pBase64 = "YW55IGNhcm5hbCBwbGVhc3VyZQ==";
    ASTR_DATA       *pStr = OBJ_NIL;
    U8ARRAY_DATA    *pArray = OBJ_NIL;
    int             i;

    fprintf(stderr, "Performing: %s\n", pTestName);

    pObj = Base64_New( );
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    if (pObj) {

        obj_TraceSet(pObj, true);
        fRc = obj_IsKindOf(pObj, OBJ_IDENT_BASE64);
        TINYTEST_TRUE( (fRc) );
        //TINYTEST_TRUE( (ERESULT_OK(eRc)) );

        fprintf(stderr, "\tInput    : (%d)\"%s\"\n", (int)strlen(pData), pData);
        fprintf(stderr, "\tShould be: (%d)\"%s\"\n", (int)strlen(pBase64), pBase64);
        pStr = Base64_EncodeData((int)strlen(pData), (void *)pData);
        TINYTEST_FALSE( (OBJ_NIL == pStr) );
        fprintf(stderr, "\tBase64   : (%d)\"%s\"\n", AStr_getSize(pStr), AStr_getData(pStr));
        i = AStr_CompareA(pStr, pBase64);
        TINYTEST_TRUE( (0 == i) );
        obj_Release(pStr);
        pStr = OBJ_NIL;

        fprintf(stderr, "\tInput    : (%d)\"%s\"\n", (int)strlen(pBase64), pBase64);
        fprintf(stderr, "\tShould be: (%d)\"%s\"\n", (int)strlen(pData), pData);
        pArray = Base64_DecodeData((int)strlen(pBase64), (void *)pBase64);
        TINYTEST_FALSE( (OBJ_NIL == pArray) );
        pStr = u8Array_ToString(pArray);
        TINYTEST_FALSE( (OBJ_NIL == pStr) );
        fprintf(stderr, "\tData     : (%d)\"%s\"\n", AStr_getSize(pStr), AStr_getData(pStr));
        i = AStr_CompareA(pStr, pData);
        TINYTEST_TRUE( (0 == i) );
        obj_Release(pStr);
        pStr = OBJ_NIL;
        obj_Release(pArray);
        pArray = OBJ_NIL;

        {
            ASTR_DATA       *pStr = Base64_ToDebugString(pObj, 4);
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




TINYTEST_START_SUITE(test_Base64);
    TINYTEST_ADD_TEST(test_Base64_Test04,setUp,tearDown);
    TINYTEST_ADD_TEST(test_Base64_Test03,setUp,tearDown);
    TINYTEST_ADD_TEST(test_Base64_Test02,setUp,tearDown);
    TINYTEST_ADD_TEST(test_Base64_Test01,setUp,tearDown);
    //TINYTEST_ADD_TEST(test_Base64_Copy01,setUp,tearDown);
    TINYTEST_ADD_TEST(test_Base64_OpenClose,setUp,tearDown);
TINYTEST_END_SUITE();

TINYTEST_MAIN_SINGLE_SUITE(test_Base64);





