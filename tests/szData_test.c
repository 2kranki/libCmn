/*
 *	Generated 02/07/2018 09:15:58
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
#include    <SrcErrors.h>
#include    <szTbl.h>
#include    <trace.h>
#include    <szData_internal.h>



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






int             test_szData_OpenClose(
    const
    char            *pTestName
)
{
    SZDATA_DATA	    *pObj = OBJ_NIL;
   
    fprintf(stderr, "Performing: %s\n", pTestName);

    pObj = szData_Alloc( );
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    pObj = szData_Init( pObj );
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    if (pObj) {

        // Test something.

        obj_Release(pObj);
        pObj = OBJ_NIL;
    }

    fprintf(stderr, "...%s completed.\n\n", pTestName);
    return 1;
}



int             test_szData_Create01(
    const
    char                *pTestName
)
{
    ERESULT             eRc;
    SZDATA_DATA         *pObj = OBJ_NIL;
    ASTR_DATA           *pStr = OBJ_NIL;
    static
    char                *pJSON =
        "{"
            "\"objectType\":\"szData\", "
            "\"class\":9, "
            "\"name\":{ \"objectType\":\"utf8\", \"len\":5, "
                        "\"crc\":3168274023, \"data\":\"xyzzy\" }\n, "
            "\"data\":{ \"objectType\":\"AStr\", \"len\":4, "
            "\"crc\":2638675519, \"data\":\"1234\"}\n "
        "}\n";
    
    fprintf(stderr, "Performing: %s\n", pTestName);
    
    pObj = szData_NewA("xyzzy");
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    if (pObj) {
        
        pStr = AStr_NewA("1234");
        TINYTEST_FALSE( (OBJ_NIL == pStr) );
        szData_setData(pObj, pStr);
        obj_Release(pStr);
        pStr = OBJ_NIL;
        szData_setClass(pObj, 9);

        eRc = szData_CompareA(pObj, "xyzzy");
        TINYTEST_TRUE( (eRc == ERESULT_SUCCESS_EQUAL) );

        pStr = szData_ToJSON(pObj);
        TINYTEST_FALSE( (OBJ_NIL == pStr) );
        fprintf(stderr, "\tToJSON: %s\n", AStr_getData(pStr));
        TINYTEST_TRUE( (0 == strcmp(pJSON, AStr_getData(pStr))) );
        obj_Release(pStr);
        pStr = OBJ_NIL;

        obj_Release(pObj);
        pObj = OBJ_NIL;
    }
    
    pObj = szData_NewFromJSONStringA(pJSON);
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    if (pObj) {
        eRc = szData_CompareA(pObj, "xyzzy");
        TINYTEST_TRUE( (eRc == ERESULT_SUCCESS_EQUAL) );
        TINYTEST_TRUE( (9 == szData_getClass(pObj)) );
        pStr = szData_getData(pObj);
        TINYTEST_FALSE( (OBJ_NIL == pStr) );
        eRc = AStr_CompareA(pStr, "1234");
        TINYTEST_TRUE( (eRc == ERESULT_SUCCESS_EQUAL) );

        obj_Release(pObj);
        pObj = OBJ_NIL;
    }
    
    fprintf(stderr, "...%s completed.\n\n", pTestName);
    return 1;
}




TINYTEST_START_SUITE(test_szData);
    TINYTEST_ADD_TEST(test_szData_Create01,setUp,tearDown);
    TINYTEST_ADD_TEST(test_szData_OpenClose,setUp,tearDown);
TINYTEST_END_SUITE();

TINYTEST_MAIN_SINGLE_SUITE(test_szData);





