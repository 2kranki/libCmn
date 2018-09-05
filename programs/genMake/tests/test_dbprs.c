/*
 *	Generated 09/04/2018 13:50:27
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
#include    <szTbl.h>
#include    <trace.h>
#include    <dbprs_internal.h>


bool        fJson;
bool        fObject;
bool        fRoutine;
bool        fTest;



ASTR_DATA *     doJson(
    OBJ_ID          pObj,
    const
    char            *pName,
    const
    char            *pSrcDir,
    const
    char            *pObjDir,
    const
    char            *pObjVar
)
{
    fprintf(stderr, "\tJson for %s\n", pName);
    fJson = true;
    return OBJ_NIL;
}


ASTR_DATA *     doObject(
    OBJ_ID          pObj,
    const
    char            *pName,
    const
    char            *pSrcDir,
    const
    char            *pObjDir,
    const
    char            *pObjVar
)
{
    fprintf(stderr, "\tObject for %s\n", pName);
    fObject = true;
    return OBJ_NIL;
}


ASTR_DATA *     doRoutine(
    OBJ_ID          pObj,
    const
    char            *pName,
    const
    char            *pSrcDir,
    const
    char            *pObjDir,
    const
    char            *pObjVar
)
{
    fprintf(stderr, "\tRoutine for %s\n", pName);
    fRoutine = true;
    return OBJ_NIL;
}


ASTR_DATA *     doTest(
    OBJ_ID          pObj,
    const
    char            *pName,
    const
    char            *pSrcDir,
    const
    char            *pObjDir,
    const
    char            *pObjVar
)
{
    fprintf(stderr, "\tTest for %s\n", pName);
    fTest = true;
    return OBJ_NIL;
}




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






int             test_dbprs_OpenClose(
    const
    char            *pTestName
)
{
    DBPRS_DATA	    *pObj = OBJ_NIL;
   
    fprintf(stderr, "Performing: %s\n", pTestName);

    pObj = dbprs_Alloc( );
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    pObj = dbprs_Init( pObj );
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    if (pObj) {

        // Test something.

        obj_Release(pObj);
        pObj = OBJ_NIL;
    }

    fprintf(stderr, "...%s completed.\n\n", pTestName);
    return 1;
}



int             test_dbprs_Object01(
    const
    char            *pTestName
)
{
    DBPRS_DATA      *pObj = OBJ_NIL;
    GENBASE_DATA    *pGen = OBJ_NIL;
    ERESULT         eRc;
    ASTR_DATA       *pStr = OBJ_NIL;
    NODE_DATA       *pNode = OBJ_NIL;
    const
    char                *pGoodJsonObject1 = "{\n"
        "\"AStr\":{"
            "\"deps\":[\"cmn\",\"array\"],"
            "\"json\":true,"
            "\"test\":true"
        "}\n"
    "}\n";

    fprintf(stderr, "Performing: %s\n", pTestName);
    
    pGen = genBase_New();
    TINYTEST_FALSE( (OBJ_NIL == pGen) );
    genBase_setGenerators(pGen, OBJ_NIL, doJson, doObject, doRoutine, doTest);
    
    pObj = dbprs_Alloc( );
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    pObj = dbprs_Init( pObj );
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    if (pObj) {
        
        fJson = false;
        fObject = false;
        fRoutine = false;
        fTest = false;
        dbprs_setGen(pObj, pGen);
        
        obj_TraceSet(pObj, true);
        eRc = dbprs_ParseInputStr(pObj, pGoodJsonObject1);
        TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );

        pNode = dbprs_getNodes(pObj);
        TINYTEST_FALSE( (OBJ_NIL == pNode) );
        TINYTEST_TRUE( (obj_IsKindOf(pNode, OBJ_IDENT_NODE)) );
        pNode = nodeHash_FindA((NODEHASH_DATA *)node_getData(pNode), "AStr");
        TINYTEST_FALSE( (OBJ_NIL == pObj) );
        TINYTEST_TRUE( (obj_IsKindOf(pNode, OBJ_IDENT_NODE)) );
        eRc = dbprs_ParseObject(pObj, pNode);
        TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );
        TINYTEST_TRUE( (fJson) );
        TINYTEST_TRUE( (fObject) );
        TINYTEST_TRUE( (!fRoutine) );
        TINYTEST_TRUE( (fTest) );

        obj_Release(pObj);
        pObj = OBJ_NIL;
    }
    obj_Release(pGen);
    pGen = OBJ_NIL;

    fprintf(stderr, "...%s completed.\n\n", pTestName);
    return 1;
}




TINYTEST_START_SUITE(test_dbprs);
    TINYTEST_ADD_TEST(test_dbprs_Object01,setUp,tearDown);
    TINYTEST_ADD_TEST(test_dbprs_OpenClose,setUp,tearDown);
TINYTEST_END_SUITE();

TINYTEST_MAIN_SINGLE_SUITE(test_dbprs);





