// vi:nu:et:sts=4 ts=4 sw=4
/*
 *	Generated 01/25/2020 21:31:26
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
#include    <JsonOut_internal.h>
#ifdef  JSONOUT_JSON_SUPPORT
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

#ifdef  JSONOUT_JSON_SUPPORT
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






int             test_JsonOut_OpenClose (
    const
    char            *pTestName
)
{
    ERESULT         eRc = ERESULT_SUCCESS;
    JSONOUT_DATA	    *pObj = OBJ_NIL;
    bool            fRc;
   
    fprintf(stderr, "Performing: %s\n", pTestName);

    pObj = JsonOut_Alloc( );
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    pObj = JsonOut_Init( pObj );
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    if (pObj) {

        //obj_TraceSet(pObj, true);       
        fRc = obj_IsKindOf(pObj, OBJ_IDENT_JSONOUT);
        TINYTEST_TRUE( (fRc) );
        
        // Test something.
        TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );

        obj_Release(pObj);
        pObj = OBJ_NIL;
    }

    fprintf(stderr, "...%s completed.\n\n\n", pTestName);
    return 1;
}



int             test_JsonOut_Copy01 (
    const
    char            *pTestName
)
{
    ERESULT         eRc = ERESULT_SUCCESS;
    JSONOUT_DATA	    *pObj1 = OBJ_NIL;
    JSONOUT_DATA	    *pObj2 = OBJ_NIL;
    bool            fRc;
#if defined(JSONOUT_JSON_SUPPORT) && defined(XYZZY)
    ASTR_DATA	    *pStr = OBJ_NIL;
#endif
   
    fprintf(stderr, "Performing: %s\n", pTestName);

    pObj1 = JsonOut_New( );
    TINYTEST_FALSE( (OBJ_NIL == pObj1) );
    if (pObj1) {

        //obj_TraceSet(pObj1, true);       
        fRc = obj_IsKindOf(pObj1, OBJ_IDENT_JSONOUT);
        TINYTEST_TRUE( (fRc) );
        
        // Test assign.
        pObj2 = JsonOut_New();
        TINYTEST_FALSE( (OBJ_NIL == pObj2) );
        eRc = JsonOut_Assign(pObj1, pObj2);
        TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );

        fRc = obj_IsKindOf(pObj2, OBJ_IDENT_JSONOUT);
        TINYTEST_TRUE( (fRc) );
        //eRc = JsonOut_Compare(pObj1, pObj2);
        //TINYTEST_TRUE( (0 == eRc) );
        //TODO: Add More tests here!

        obj_Release(pObj2);
        pObj2 = OBJ_NIL;

        // Test copy.
        pObj2 = JsonOut_Copy(pObj1);
        TINYTEST_FALSE( (OBJ_NIL == pObj2) );

        fRc = obj_IsKindOf(pObj2, OBJ_IDENT_JSONOUT);
        TINYTEST_TRUE( (fRc) );
        //TODO: Add More tests here!

        obj_Release(pObj2);
        pObj2 = OBJ_NIL;

        // Test json support.
#if defined(JSONOUT_JSON_SUPPORT) && defined(XYZZY)
        pStr = JsonOut_ToJson(pObj1);
        TINYTEST_FALSE( (OBJ_NIL == pStr) );
        fprintf(stderr, "JSON: %s\n", AStr_getData(pStr));
        pObj2 = JsonOut_NewFromJsonString(pStr);
        TINYTEST_FALSE( (OBJ_NIL == pObj2) );
        fRc = obj_IsKindOf(pObj2, OBJ_IDENT_JSONOUT);
        TINYTEST_TRUE( (fRc) );
        obj_Release(pStr);
        pStr = OBJ_NIL;
        //eRc = JsonOut_Compare(pObj1, pObj2);
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



int             test_JsonOut_Test01 (
    const
    char            *pTestName
)
{
    //ERESULT         eRc = ERESULT_SUCCESS;
    JSONOUT_DATA	    *pObj = OBJ_NIL;
    bool            fRc;
   
    fprintf(stderr, "Performing: %s\n", pTestName);

    pObj = JsonOut_New( );
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    if (pObj) {

        //obj_TraceSet(pObj, true);       
        fRc = obj_IsKindOf(pObj, OBJ_IDENT_JSONOUT);
        TINYTEST_TRUE( (fRc) );
        
        obj_Release(pObj);
        pObj = OBJ_NIL;
    }

    fprintf(stderr, "...%s completed.\n\n\n", pTestName);
    return 1;
}



int             test_JsonOut_Array01 (
    const
    char            *pTestName
)
{
    //ERESULT         eRc = ERESULT_SUCCESS;
    JSONOUT_DATA    *pObj = OBJ_NIL;
    bool            fRc;
    ASTR_DATA       *pStr = OBJ_NIL;
    uint8_t         x[12] = {'a','b','c','d','e','f','g','h',0};
    const
    char            *x8 =   "\t\"x\":[\n\t\t97, 98, 99, 100, 101,"
                            " 102, 103, 104, \n\t\t0\n\t],\n";

    fprintf(stderr, "Performing: %s\n", pTestName);

    pStr = AStr_New();
    TINYTEST_FALSE( (OBJ_NIL == pStr) );

    JsonOut_Append_u8_array("x", 9, x, pStr);
    fprintf(stderr, "u8_array:\n%s\n", AStr_getData(pStr));
    TINYTEST_TRUE( (0 == AStr_CompareA(pStr,x8)) );
    obj_Release(pStr);
    pStr = OBJ_NIL;

    pObj = JsonOut_New( );
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    if (pObj) {

        //obj_TraceSet(pObj, true);
        fRc = obj_IsKindOf(pObj, OBJ_IDENT_JSONOUT);
        TINYTEST_TRUE( (fRc) );

        obj_Release(pObj);
        pObj = OBJ_NIL;
    }

    fprintf(stderr, "...%s completed.\n\n\n", pTestName);
    return 1;
}



int             test_JsonOut_Array02 (
    const
    char            *pTestName
)
{
    //ERESULT         eRc = ERESULT_SUCCESS;
    JSONOUT_DATA    *pObj = OBJ_NIL;
    bool            fRc;
    ASTR_DATA       *pStr = OBJ_NIL;
    int16_t         x[9] = {0,1,2,3,4,5,6,7,8};
    const
    char            *x_out =   "\t\"x\":{\n"
                                    "\t\ttype:I16Array,\n"
                                    "\t\tsize:9,\n"
                                    "\t\tdata:[\n"
                                        "\t\t\t0,1,2,3,4,5,6,7,\n"
                                        "\t\t\t8\n"
                                    "\t\t]\n"
                                "\t},\n";

    fprintf(stderr, "Performing: %s\n", pTestName);

    pStr = AStr_New();
    TINYTEST_FALSE( (OBJ_NIL == pStr) );

    JsonOut_Append_i16_array("x", 9, x, pStr);
    fprintf(stderr, "i16_array:\n%s\n", AStr_getData(pStr));
    TINYTEST_TRUE( (0 == AStr_CompareA(pStr,x_out)) );
    obj_Release(pStr);
    pStr = OBJ_NIL;

    pObj = JsonOut_New( );
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    if (pObj) {

        //obj_TraceSet(pObj, true);
        fRc = obj_IsKindOf(pObj, OBJ_IDENT_JSONOUT);
        TINYTEST_TRUE( (fRc) );

        obj_Release(pObj);
        pObj = OBJ_NIL;
    }

    fprintf(stderr, "...%s completed.\n\n\n", pTestName);
    return 1;
}




TINYTEST_START_SUITE(test_JsonOut);
    TINYTEST_ADD_TEST(test_JsonOut_Array02,setUp,tearDown);
    TINYTEST_ADD_TEST(test_JsonOut_Array01,setUp,tearDown);
    TINYTEST_ADD_TEST(test_JsonOut_Test01,setUp,tearDown);
    //TINYTEST_ADD_TEST(test_JsonOut_Copy01,setUp,tearDown);
    TINYTEST_ADD_TEST(test_JsonOut_OpenClose,setUp,tearDown);
TINYTEST_END_SUITE();

TINYTEST_MAIN_SINGLE_SUITE(test_JsonOut);





