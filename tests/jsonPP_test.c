/*
 *	Generated 08/27/2019 21:35:44
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
#include    <hjson.h>
#include    <SrcErrors.h>
#include    <szTbl.h>
#include    <trace.h>
#include    <jsonPP_internal.h>



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






int             test_jsonPP_OpenClose(
    const
    char            *pTestName
)
{
    ERESULT         eRc = ERESULT_SUCCESS;
    JSONPP_DATA	    *pObj = OBJ_NIL;
   
    fprintf(stderr, "Performing: %s\n", pTestName);

    pObj = jsonPP_Alloc( );
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    pObj = jsonPP_Init( pObj );
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    if (pObj) {

        //obj_TraceSet(pObj, true);       
        
        // Test something.
        TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );

        obj_Release(pObj);
        pObj = OBJ_NIL;
    }

    fprintf(stderr, "...%s completed.\n\n", pTestName);
    return 1;
}



int         test_jsonPP_JSON01(
    const
    char        *pTestName
)
{
    ERESULT         eRc;
    HJSON_DATA      *pIn = OBJ_NIL;
    JSONPP_DATA     *pObj = OBJ_NIL;
    ASTR_DATA       *pStr = OBJ_NIL;
    ASTR_DATA       *pWrk = OBJ_NIL;
    NODE_DATA       *pNode = OBJ_NIL;
    int             iRc;
    int             offset = 0;
    static
    const
    char            *pGoodJsonA =
    "{ "
    "\"library\":{ "
    "\"name\":\"Cmn\", "
    "\"libDeps\":null, "
    "\"headers\":null, "
    "} ,"
    "\"objects\": { "
    "\"AStr\":{\"srcDeps\":[\"libCmn.h\"], \"json\":true, \"test\":true}, "
    "\"appl\":{\"srcDeps\":[\"libCmn.h\"], \"test\":true}, "
    "}, "
    "\"routines\": [ "
    "\"dllist.c\", "
    "], "
    "} ";
    const
    char            *pOutputA =
    "{\n"
    "  \"library\" : {\n"
    "    \"headers\" : null,\n"
    "    \"libDeps\" : null,\n"
    "    \"name\" : \"Cmn\"\n"
    "  },\n"
    "  \"objects\" : {\n"
    "    \"AStr\" : {\n"
    "      \"json\" : true,\n"
    "      \"srcDeps\" : [\n"
    "        \"libCmn.h\"\n"
    "      ],\n"
    "      \"test\" : true\n"
    "    },\n"
    "    \"appl\" : {\n"
    "      \"srcDeps\" : [\n"
    "        \"libCmn.h\"\n"
    "      ],\n"
    "      \"test\" : true\n"
    "    }\n"
    "  },\n"
    "  \"routines\" : [\n"
    "    \"dllist.c\"\n"
    "  ]\n"
    "}\n";
    ;
    
    
    fprintf(stderr, "Performing: %s\n", pTestName);
    
    pIn = hjson_NewA(pGoodJsonA, 2);
    TINYTEST_FALSE( (OBJ_NIL == pIn) );
    pNode = hjson_ParseFileHash(pIn);
    TINYTEST_FALSE( (OBJ_NIL == pNode) );
    
    pObj = jsonPP_New();
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    if (pObj) {
        
        obj_TraceSet(pObj, true);
        jsonPP_setIndent(pObj, 2);
        eRc = jsonPP_PrettyPrint(pObj, pNode, 0, OBJ_NIL);
        TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );
        
        pStr = jsonPP_getStr(pObj);
        fprintf(stderr, "JSON_BEGIN:\n%sJSON_END:\n\n\n", AStr_getData(pStr));
        pWrk = AStr_ToDebugString(pStr, 4);
        fprintf(stderr, "%s\n\n\n", AStr_getData(pWrk));
        obj_Release(pWrk);
        pWrk = OBJ_NIL;
        iRc = str_CompareSpcl(pOutputA, AStr_getData(pStr), &offset);
        fprintf(stderr, "\tiRc=%d  offset=%04X\n", iRc, offset);
        TINYTEST_TRUE( (0 == iRc) );
        
        obj_Release(pObj);
        pObj = OBJ_NIL;
    }
    obj_Release(pNode);
    pNode = OBJ_NIL;
    obj_Release(pIn);
    pIn = OBJ_NIL;

    fprintf(stderr, "...%s completed.\n\n\n", pTestName);
    return 1;
}




TINYTEST_START_SUITE(test_jsonPP);
    TINYTEST_ADD_TEST(test_jsonPP_JSON01,setUp,tearDown);
    TINYTEST_ADD_TEST(test_jsonPP_OpenClose,setUp,tearDown);
TINYTEST_END_SUITE();

TINYTEST_MAIN_SINGLE_SUITE(test_jsonPP);





