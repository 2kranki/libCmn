// vi:nu:et:sts=4 ts=4 sw=4
/*
 *	Generated 08/19/2019 01:17:17
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
#include    <nodeHash.h>
#include    <NodeObj.h>
#include    <NodeRtn.h>
#include    <NodeTest.h>
#include    <srcErrors.h>
#include    <szTbl.h>
#include    <trace.h>
#include    <SrcParse_internal.h>



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
    srcErrors_SharedReset( );
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



ERESULT_DATA *  InputStrToJSON(
    const
    char            *pStrA,
    NODE_DATA       **ppNodes
)
{
    ERESULT_DATA    *pErr = OBJ_NIL;
    HJSON_DATA      *pObj = OBJ_NIL;
    NODEHASH_DATA   *pHash;
    NODE_DATA       *pFileNode = OBJ_NIL;

    // Do initialization.
#ifdef NDEBUG
#else
    if (NULL == pStrA) {
        DEBUG_BREAK();
        pErr = eResult_NewStrA(ERESULT_INVALID_PARAMETER, "Error: Missing String!");
        return pErr;
    }
#endif

    pObj = hjson_NewA(pStrA, 4);
    if (pObj) {
        pFileNode = hjson_ParseFileValue(pObj);
        obj_Release(pObj);
        pObj = OBJ_NIL;
    }
    srcErrors_ExitOnFatal(OBJ_NIL);

    if (OBJ_NIL == pFileNode) {
        fprintf(stderr, "ERROR - No JSON Nodes to process\n\n\n");
        exit(12);
    }
    if (pFileNode) {
        pHash = node_getData(pFileNode);
        if (OBJ_NIL == pHash) {
            fprintf(stderr, "ERROR - No JSON Array or Hash to process\n\n\n");
            exit(12);
        }
        if (obj_IsKindOf(pHash, OBJ_IDENT_NODEARRAY)
            || obj_IsKindOf(pHash, OBJ_IDENT_NODEHASH))
            ;
        else {
            fprintf(stderr, "ERROR - Missing JSON Hash to process\n\n\n");
            exit(12);
        }
    }

    // Return to caller.
    if (ppNodes) {
        *ppNodes = pFileNode;
    }
    return pErr;
}






int             test_SrcParse_OpenClose(
    const
    char            *pTestName
)
{
    ERESULT         eRc = ERESULT_SUCCESS;
    SRCPARSE_DATA	*pObj = OBJ_NIL;
   
    fprintf(stderr, "Performing: %s\n", pTestName);

    pObj = SrcParse_Alloc( );
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    pObj = SrcParse_Init( pObj );
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



int             test_SrcParse_Object01(
    const
    char            *pTestName
)
{
    SRCPARSE_DATA   *pPrs = OBJ_NIL;
    ERESULT_DATA    *pErr;
    NODE_DATA       *pNodes = OBJ_NIL;
    NODEHASH_DATA   *pHash = OBJ_NIL;
    OBJARRAY_DATA   *pArray = OBJ_NIL;
    const
    char            *pGoodJsonObject1 =
    "["
        "{name:\"AStr\",  deps:[\"array.h\"]},\n"
        "{name:\"AStrC\", deps:[\"array.h\"]}\n"
    "]\n";
    bool            fDumpNodes = false;
    uint32_t        i;
    uint32_t        iMax;
    NODEOBJ_DATA    *pObj;
    NODERTN_DATA    *pRtn;
    NODETEST_DATA   *pTest;

    fprintf(stderr, "Performing: %s\n", pTestName);
    
    pPrs = SrcParse_New( );
    TINYTEST_FALSE( (OBJ_NIL == pPrs) );
    if (pPrs) {
        
        //obj_TraceSet(pObj, true);
        pErr = InputStrToJSON(pGoodJsonObject1, &pNodes);
        TINYTEST_TRUE( (OBJ_NIL == pErr) );
        TINYTEST_FALSE( (OBJ_NIL == pNodes) );
        TINYTEST_TRUE( (obj_IsKindOf(pNodes, OBJ_IDENT_NODE)) );
        pHash = node_getData(pNodes);
        TINYTEST_FALSE( (OBJ_NIL == pHash) );
        TINYTEST_TRUE( (obj_IsKindOf(pHash, OBJ_IDENT_NODEARRAY)
                        || obj_IsKindOf(pHash, OBJ_IDENT_NODEHASH)) );

        if (fDumpNodes) {
            ASTR_DATA       *pWrk = OBJ_NIL;
            pWrk = node_ToDebugString(pNodes, 0);
            fprintf(stderr, "\n====> JSON Input:\n%s\n\n\n", AStr_getData(pWrk));
            obj_Release(pWrk);
            pWrk = OBJ_NIL;
        }

        pErr = SrcParse_ParseObjects(pPrs, pNodes);
        TINYTEST_TRUE((OBJ_NIL == pErr));

        pArray = SrcParse_getObjs(pPrs);
        TINYTEST_FALSE( (OBJ_NIL == pArray) );

        // Validate the results.
        iMax = objArray_getSize(pArray);
        fprintf(stderr, "# of Objects: %d\n", iMax);
        TINYTEST_TRUE( (2 == iMax) );
        for (i=0; i<iMax; i++) {
            pObj = objArray_Get(pArray, i+1);
            TINYTEST_FALSE( (OBJ_NIL == pObj) );
            pRtn = NodeObj_getJson(pObj);
            TINYTEST_TRUE( (OBJ_NIL == pRtn) );
            pTest = NodeObj_getTest(pObj);
            TINYTEST_FALSE( (OBJ_NIL == pTest) );
        }

        obj_Release(pNodes);
        pNodes = OBJ_NIL;

        obj_Release(pPrs);
        pPrs = OBJ_NIL;
    }

    fprintf(stderr, "...%s completed.\n\n\n\n", pTestName);
    return 1;
}



int             test_SrcParse_Object02(
    const
    char            *pTestName
)
{
    SRCPARSE_DATA   *pPrs = OBJ_NIL;
    ERESULT_DATA    *pErr;
    NODE_DATA       *pNodes = OBJ_NIL;
    NODEHASH_DATA   *pHash = OBJ_NIL;
    OBJARRAY_DATA   *pArray = OBJ_NIL;
    const
    char            *pGoodJsonObject1 =
    "["
        "{name:\"AStr\",  deps:[\"array.h\"], json:true},\n"
        "{name:\"AStrC\", deps:[\"array.h\"], json:{name:\"AStrC_jsonPlus.c\"}}\n"
    "]\n";
    bool            fDumpNodes = false;
    uint32_t        i;
    uint32_t        iMax;
    NODEOBJ_DATA    *pObj;
    NODERTN_DATA    *pRtn;
    NODETEST_DATA   *pTest;

    fprintf(stderr, "Performing: %s\n", pTestName);
    
    pPrs = SrcParse_New( );
    TINYTEST_FALSE( (OBJ_NIL == pPrs) );
    if (pPrs) {
        
        //obj_TraceSet(pObj, true);
        pErr = InputStrToJSON(pGoodJsonObject1, &pNodes);
        TINYTEST_TRUE( (OBJ_NIL == pErr) );
        TINYTEST_FALSE( (OBJ_NIL == pNodes) );
        TINYTEST_TRUE( (obj_IsKindOf(pNodes, OBJ_IDENT_NODE)) );
        pHash = node_getData(pNodes);
        TINYTEST_FALSE( (OBJ_NIL == pHash) );
        TINYTEST_TRUE( (obj_IsKindOf(pHash, OBJ_IDENT_NODEARRAY)
                        || obj_IsKindOf(pHash, OBJ_IDENT_NODEHASH)) );

        if (fDumpNodes) {
            ASTR_DATA       *pWrk = OBJ_NIL;
            pWrk = node_ToDebugString(pNodes, 0);
            fprintf(stderr, "\n====> JSON Input:\n%s\n\n\n", AStr_getData(pWrk));
            obj_Release(pWrk);
            pWrk = OBJ_NIL;
        }

        pErr = SrcParse_ParseObjects(pPrs, pNodes);
        TINYTEST_TRUE((OBJ_NIL == pErr));

        pArray = SrcParse_getObjs(pPrs);
        TINYTEST_FALSE( (OBJ_NIL == pArray) );

        // Display the Output.
        if (pArray && fDumpNodes) {
            fprintf(stderr, "\n\n===> Object Array:\n\n");
            ASTR_DATA   *pStr = objArray_ToDebugString(pArray, 0);
            fprintf(stderr, "%s\n", AStr_getData(pStr));
            obj_Release(pStr);
            pStr = OBJ_NIL;
        }

        // Validate the results.
        iMax = objArray_getSize(pArray);
        fprintf(stderr, "# of Objects: %d\n", iMax);
        TINYTEST_TRUE( (2 == iMax) );
        for (i=0; i<iMax; i++) {
            pObj = objArray_Get(pArray, i+1);
            TINYTEST_FALSE( (OBJ_NIL == pObj) );
            pRtn = NodeObj_getJson(pObj);
            TINYTEST_FALSE( (OBJ_NIL == pRtn) );
            pTest = NodeObj_getTest(pObj);
            TINYTEST_FALSE( (OBJ_NIL == pTest) );
        }

        obj_Release(pNodes);
        pNodes = OBJ_NIL;

        obj_Release(pPrs);
        pPrs = OBJ_NIL;
    }

    fprintf(stderr, "...%s completed.\n\n\n\n", pTestName);
    return 1;
}



int             test_SrcParse_Object03(
    const
    char            *pTestName
)
{
    SRCPARSE_DATA   *pPrs = OBJ_NIL;
    ERESULT_DATA    *pErr;
    NODE_DATA       *pNodes = OBJ_NIL;
    NODEHASH_DATA   *pHash = OBJ_NIL;
    OBJARRAY_DATA   *pArray = OBJ_NIL;
    const
    char            *pGoodJsonObject1 =
    "["
        "{name:\"AStr\"},\n"
        "{name:\"AStrC\"}\n"
    "]\n";
    bool            fDumpNodes = false;
    uint32_t        i;
    uint32_t        iMax;
    NODEOBJ_DATA    *pObj;
    NODERTN_DATA    *pRtn;
    NODETEST_DATA   *pTest;

    fprintf(stderr, "Performing: %s\n", pTestName);
    
    pPrs = SrcParse_New( );
    TINYTEST_FALSE( (OBJ_NIL == pPrs) );
    if (pPrs) {
        
        //obj_TraceSet(pObj, true);
        pErr = InputStrToJSON(pGoodJsonObject1, &pNodes);
        TINYTEST_TRUE( (OBJ_NIL == pErr) );
        TINYTEST_FALSE( (OBJ_NIL == pNodes) );
        TINYTEST_TRUE( (obj_IsKindOf(pNodes, OBJ_IDENT_NODE)) );
        pHash = node_getData(pNodes);
        TINYTEST_FALSE( (OBJ_NIL == pHash) );
        TINYTEST_TRUE( (obj_IsKindOf(pHash, OBJ_IDENT_NODEARRAY)
                        || obj_IsKindOf(pHash, OBJ_IDENT_NODEHASH)) );

        if (fDumpNodes) {
            ASTR_DATA       *pWrk = OBJ_NIL;
            pWrk = node_ToDebugString(pNodes, 0);
            fprintf(stderr, "\n====> JSON Input:\n%s\n\n\n", AStr_getData(pWrk));
            obj_Release(pWrk);
            pWrk = OBJ_NIL;
        }

        pErr = SrcParse_ParseObjects(pPrs, pNodes);
        TINYTEST_TRUE((OBJ_NIL == pErr));

        pArray = SrcParse_getObjs(pPrs);
        TINYTEST_FALSE( (OBJ_NIL == pArray) );

        // Validate the results.
        iMax = objArray_getSize(pArray);
        fprintf(stderr, "# of Objects: %d\n", iMax);
        TINYTEST_TRUE( (2 == iMax) );
        for (i=0; i<iMax; i++) {
            pObj = objArray_Get(pArray, i+1);
            TINYTEST_FALSE( (OBJ_NIL == pObj) );
            pRtn = NodeObj_getJson(pObj);
            TINYTEST_TRUE( (OBJ_NIL == pRtn) );
            pTest = NodeObj_getTest(pObj);
            TINYTEST_FALSE( (OBJ_NIL == pTest) );
        }

        obj_Release(pNodes);
        pNodes = OBJ_NIL;

        obj_Release(pPrs);
        pPrs = OBJ_NIL;
    }

    fprintf(stderr, "...%s completed.\n\n\n\n", pTestName);
    return 1;
}



int             test_SrcParse_Routine01(
    const
    char            *pTestName
)
{
    SRCPARSE_DATA   *pPrs = OBJ_NIL;
    ERESULT_DATA    *pErr;
    NODE_DATA       *pNodes = OBJ_NIL;
    NODEHASH_DATA   *pHash = OBJ_NIL;
    OBJARRAY_DATA   *pArray = OBJ_NIL;
    const
    char            *pGoodJsonObject1 =
    "["
        "{name:\"AStr\",  deps:[\"array.h\"]},\n"
        "{name:\"AStrC\", deps:[\"array.h\"]}\n"
    "]\n";
    bool            fDumpNodes = false;
    uint32_t        i;
    uint32_t        iMax;
    NODERTN_DATA    *pRtn;
    NODETEST_DATA   *pTest;

    fprintf(stderr, "Performing: %s\n", pTestName);
    
    pPrs = SrcParse_New( );
    TINYTEST_FALSE( (OBJ_NIL == pPrs) );
    if (pPrs) {
        
        //obj_TraceSet(pObj, true);
        pErr = InputStrToJSON(pGoodJsonObject1, &pNodes);
        TINYTEST_TRUE( (OBJ_NIL == pErr) );
        TINYTEST_FALSE( (OBJ_NIL == pNodes) );
        TINYTEST_TRUE( (obj_IsKindOf(pNodes, OBJ_IDENT_NODE)) );
        pHash = node_getData(pNodes);
        TINYTEST_FALSE( (OBJ_NIL == pHash) );
        TINYTEST_TRUE( (obj_IsKindOf(pHash, OBJ_IDENT_NODEARRAY)
                        || obj_IsKindOf(pHash, OBJ_IDENT_NODEHASH)) );

        if (fDumpNodes) {
            ASTR_DATA       *pWrk = OBJ_NIL;
            pWrk = node_ToDebugString(pNodes, 0);
            fprintf(stderr, "\n====> JSON Input:\n%s\n\n\n", AStr_getData(pWrk));
            obj_Release(pWrk);
            pWrk = OBJ_NIL;
        }

        pErr = SrcParse_ParseRoutines(pPrs, pNodes);
        TINYTEST_TRUE((OBJ_NIL == pErr));

        pArray = SrcParse_getRtns(pPrs);
        TINYTEST_FALSE( (OBJ_NIL == pArray) );

        // Validate the results.
        iMax = objArray_getSize(pArray);
        fprintf(stderr, "# of Objects: %d\n", iMax);
        TINYTEST_TRUE( (2 == iMax) );
        for (i=0; i<iMax; i++) {
            pRtn = objArray_Get(pArray, i+1);
            TINYTEST_FALSE( (OBJ_NIL == pRtn) );
            pTest = NodeRtn_getTest(pRtn);
            TINYTEST_FALSE( (OBJ_NIL == pTest) );
        }

        obj_Release(pNodes);
        pNodes = OBJ_NIL;

        obj_Release(pPrs);
        pPrs = OBJ_NIL;
    }

    fprintf(stderr, "...%s completed.\n\n\n\n", pTestName);
    return 1;
}



int             test_SrcParse_Routine02(
    const
    char            *pTestName
)
{
    SRCPARSE_DATA   *pPrs = OBJ_NIL;
    ERESULT_DATA    *pErr;
    NODE_DATA       *pNodes = OBJ_NIL;
    NODEHASH_DATA   *pHash = OBJ_NIL;
    OBJARRAY_DATA   *pArray = OBJ_NIL;
    const
    char            *pGoodJsonObject1 =
    "["
        "{name:\"AStr\"},\n"
        "{name:\"AStrC\"}\n"
    "]\n";
    bool            fDumpNodes = false;
    uint32_t        i;
    uint32_t        iMax;
    NODERTN_DATA    *pRtn;
    NODETEST_DATA   *pTest;

    fprintf(stderr, "Performing: %s\n", pTestName);
    
    pPrs = SrcParse_New( );
    TINYTEST_FALSE( (OBJ_NIL == pPrs) );
    if (pPrs) {
        
        //obj_TraceSet(pObj, true);
        pErr = InputStrToJSON(pGoodJsonObject1, &pNodes);
        TINYTEST_TRUE( (OBJ_NIL == pErr) );
        TINYTEST_FALSE( (OBJ_NIL == pNodes) );
        TINYTEST_TRUE( (obj_IsKindOf(pNodes, OBJ_IDENT_NODE)) );
        pHash = node_getData(pNodes);
        TINYTEST_FALSE( (OBJ_NIL == pHash) );
        TINYTEST_TRUE( (obj_IsKindOf(pHash, OBJ_IDENT_NODEARRAY)
                        || obj_IsKindOf(pHash, OBJ_IDENT_NODEHASH)) );

        if (fDumpNodes) {
            ASTR_DATA       *pWrk = OBJ_NIL;
            pWrk = node_ToDebugString(pNodes, 0);
            fprintf(stderr, "\n====> JSON Input:\n%s\n\n\n", AStr_getData(pWrk));
            obj_Release(pWrk);
            pWrk = OBJ_NIL;
        }

        pErr = SrcParse_ParseRoutines(pPrs, pNodes);
        TINYTEST_TRUE((OBJ_NIL == pErr));

        pArray = SrcParse_getRtns(pPrs);
        TINYTEST_FALSE( (OBJ_NIL == pArray) );

        // Validate the results.
        iMax = objArray_getSize(pArray);
        fprintf(stderr, "# of Objects: %d\n", iMax);
        TINYTEST_TRUE( (2 == iMax) );
        for (i=0; i<iMax; i++) {
            pRtn = objArray_Get(pArray, i+1);
            TINYTEST_FALSE( (OBJ_NIL == pRtn) );
            pTest = NodeRtn_getTest(pRtn);
            TINYTEST_FALSE( (OBJ_NIL == pTest) );
        }

        obj_Release(pNodes);
        pNodes = OBJ_NIL;

        obj_Release(pPrs);
        pPrs = OBJ_NIL;
    }

    fprintf(stderr, "...%s completed.\n\n\n\n", pTestName);
    return 1;
}



int             test_SrcParse_Test01(
    const
    char            *pTestName
)
{
    SRCPARSE_DATA   *pPrs = OBJ_NIL;
    ERESULT_DATA    *pErr;
    NODE_DATA       *pNodes = OBJ_NIL;
    NODEHASH_DATA   *pHash = OBJ_NIL;
    OBJARRAY_DATA   *pArray = OBJ_NIL;
    const
    char            *pGoodJsonObject1 =
    "["
        "{name:\"AStr\"},\n"
        "{name:\"AStrC\"}\n"
    "]\n";
    bool            fDumpNodes = false;
    uint32_t        i;
    uint32_t        iMax;
    NODETEST_DATA   *pTest;

    fprintf(stderr, "Performing: %s\n", pTestName);
    
    pPrs = SrcParse_New( );
    TINYTEST_FALSE( (OBJ_NIL == pPrs) );
    if (pPrs) {
        
        //obj_TraceSet(pObj, true);
        pErr = InputStrToJSON(pGoodJsonObject1, &pNodes);
        TINYTEST_TRUE( (OBJ_NIL == pErr) );
        TINYTEST_FALSE( (OBJ_NIL == pNodes) );
        TINYTEST_TRUE( (obj_IsKindOf(pNodes, OBJ_IDENT_NODE)) );
        pHash = node_getData(pNodes);
        TINYTEST_FALSE( (OBJ_NIL == pHash) );
        TINYTEST_TRUE( (obj_IsKindOf(pHash, OBJ_IDENT_NODEARRAY)
                        || obj_IsKindOf(pHash, OBJ_IDENT_NODEHASH)) );

        if (fDumpNodes) {
            ASTR_DATA       *pWrk = OBJ_NIL;
            pWrk = node_ToDebugString(pNodes, 0);
            fprintf(stderr, "\n====> JSON Input:\n%s\n\n\n", AStr_getData(pWrk));
            obj_Release(pWrk);
            pWrk = OBJ_NIL;
        }

        pErr = SrcParse_ParseTests(pPrs, pNodes);
        TINYTEST_TRUE((OBJ_NIL == pErr));

        pArray = SrcParse_getTests(pPrs);
        TINYTEST_FALSE( (OBJ_NIL == pArray) );

        // Validate the results.
        iMax = objArray_getSize(pArray);
        fprintf(stderr, "# of Objects: %d\n", iMax);
        TINYTEST_TRUE( (2 == iMax) );
        for (i=0; i<iMax; i++) {
            pTest = objArray_Get(pArray, i+1);
            TINYTEST_FALSE( (OBJ_NIL == pTest) );
        }

        obj_Release(pNodes);
        pNodes = OBJ_NIL;

        obj_Release(pPrs);
        pPrs = OBJ_NIL;
    }

    fprintf(stderr, "...%s completed.\n\n\n\n", pTestName);
    return 1;
}



int             test_SrcParse_Nodes01(
    const
    char            *pTestName
)
{
    SRCPARSE_DATA   *pPrs = OBJ_NIL;
    ERESULT_DATA    *pErr;
    NODE_DATA       *pNodes = OBJ_NIL;
    NODEHASH_DATA   *pHash = OBJ_NIL;
    OBJARRAY_DATA   *pArray = OBJ_NIL;
    NODELIB_DATA    *pLib;
    NODEPGM_DATA    *pPgm;
    const
    char            *pGoodJson1 =
    "{\n"
        "\"program\":{\n"
            "\"name\":\"genMake\",\n"
            "\"deps\":[\"Cmd\"]\n"
        "}\n,"
        "\"objects\": [\n"
            "{name:\"AStr\", \"srcDeps\":[\"libCmn.h\"], \"json\":true},\n"
            "{name:\"appl\", \"srcDeps\":[\"libCmn.h\"]},\n"
        "],\n"
        "\"routines\": [\n"
                "{name:\"dllist.c\"}\n"
        "],\n"
    "}\n";
    bool            fDumpNodes = false;
    uint32_t        iMax;
    NODEOBJ_DATA    *pObj;
    NODERTN_DATA    *pRtn;
    ASTRC_DATA      *pStrC;

    fprintf(stderr, "Performing: %s\n", pTestName);
    
    pPrs = SrcParse_New( );
    TINYTEST_FALSE( (OBJ_NIL == pPrs) );
    if (pPrs) {
        
        //obj_TraceSet(pObj, true);
        pErr = SrcParse_ParseJsonStr(pPrs, pGoodJson1);
        if (pErr) {
            eResult_Fprint(pErr, stderr);
        }
        TINYTEST_TRUE( (OBJ_NIL == pErr) );
        TINYTEST_FALSE( (OBJ_NIL == pPrs->pNodes) );
        TINYTEST_TRUE( (obj_IsKindOf(pPrs->pNodes, OBJ_IDENT_NODE)) );
        pHash = node_getData(pPrs->pNodes);
        TINYTEST_FALSE( (OBJ_NIL == pHash) );
        TINYTEST_TRUE( (obj_IsKindOf(pHash, OBJ_IDENT_NODEARRAY)
                        || obj_IsKindOf(pHash, OBJ_IDENT_NODEHASH)) );

        if (fDumpNodes) {
            ASTR_DATA       *pWrk = OBJ_NIL;
            pWrk = node_ToDebugString(pPrs->pNodes, 0);
            fprintf(stderr, "\n====> JSON Input:\n%s\n\n\n", AStr_getData(pWrk));
            obj_Release(pWrk);
            pWrk = OBJ_NIL;
        }

        pErr = SrcParse_ParseNodes(pPrs);
        if (pErr) {
            eResult_Fprint(pErr, stderr);
        }
        TINYTEST_TRUE((OBJ_NIL == pErr));

        // Validate Library vs Program.
        pLib = SrcParse_getLib(pPrs);
        TINYTEST_TRUE( (OBJ_NIL == pLib) );
        pPgm = SrcParse_getPgm(pPrs);
        TINYTEST_FALSE( (OBJ_NIL == pPgm) );
        if (fDumpNodes) {
            ASTR_DATA       *pWrk = OBJ_NIL;
            pWrk = NodePgm_ToDebugString(pPgm, 0);
            fprintf(stderr, "\n====> PGM Node:\n%s\n\n", AStr_getData(pWrk));
            obj_Release(pWrk);
            pWrk = OBJ_NIL;
        }
        pStrC = NodePgm_getMain(pPgm);
        TINYTEST_FALSE( (OBJ_NIL == pStrC) );
        TINYTEST_TRUE((ERESULT_SUCCESS_EQUAL == AStrC_CompareA(pStrC,"mainProgram.c")));

        // Validate Objects.
        pArray = SrcParse_getObjs(pPrs);
        TINYTEST_FALSE( (OBJ_NIL == pArray) );
        iMax = objArray_getSize(pArray);
        fprintf(stderr, "\tNumber of Objects: %d\n", iMax);
        TINYTEST_TRUE( (2 == iMax) );
        pObj = objArray_Get(pArray, 1);
        TINYTEST_FALSE( (OBJ_NIL == pObj) );
        if (fDumpNodes) {
            ASTR_DATA       *pWrk = OBJ_NIL;
            pWrk = NodeObj_ToDebugString(pObj, 0);
            fprintf(stderr, "\n====> OBJ 1 Node:\n%s\n\n", AStr_getData(pWrk));
            obj_Release(pWrk);
            pWrk = OBJ_NIL;
        }
        pStrC = NodeObj_getName(pObj);
        TINYTEST_FALSE( (OBJ_NIL == pStrC) );
        TINYTEST_TRUE((ERESULT_SUCCESS_EQUAL == AStrC_CompareA(pStrC,"AStr")));
        pObj = objArray_Get(pArray, 2);
        TINYTEST_FALSE( (OBJ_NIL == pObj) );
        if (fDumpNodes) {
            ASTR_DATA       *pWrk = OBJ_NIL;
            pWrk = NodeObj_ToDebugString(pObj, 0);
            fprintf(stderr, "\n====> OBJ 2 Node:\n%s\n\n", AStr_getData(pWrk));
            obj_Release(pWrk);
            pWrk = OBJ_NIL;
        }
        pStrC = NodeObj_getName(pObj);
        TINYTEST_FALSE( (OBJ_NIL == pStrC) );
        TINYTEST_TRUE((ERESULT_SUCCESS_EQUAL == AStrC_CompareA(pStrC,"appl")));

        // Validate Routines.
        pArray = SrcParse_getRtns(pPrs);
        TINYTEST_FALSE( (OBJ_NIL == pArray) );
        iMax = objArray_getSize(pArray);
        fprintf(stderr, "\tNumber of Routines: %d\n", iMax);
        TINYTEST_TRUE( (1 == iMax) );
        pRtn = objArray_Get(pArray, 1);
        TINYTEST_FALSE( (OBJ_NIL == pRtn) );
        if (fDumpNodes) {
            ASTR_DATA       *pWrk = OBJ_NIL;
            pWrk = NodeRtn_ToDebugString(pRtn, 0);
            fprintf(stderr, "\n====> RTN 1 Node:\n%s\n\n", AStr_getData(pWrk));
            obj_Release(pWrk);
            pWrk = OBJ_NIL;
        }
        pStrC = NodeRtn_getName(pRtn);
        TINYTEST_FALSE( (OBJ_NIL == pStrC) );
        TINYTEST_TRUE((ERESULT_SUCCESS_EQUAL == AStrC_CompareA(pStrC,"dllist.c")));

        obj_Release(pNodes);
        pNodes = OBJ_NIL;

        obj_Release(pPrs);
        pPrs = OBJ_NIL;
    }

    fprintf(stderr, "...%s completed.\n\n\n\n", pTestName);
    return 1;
}



int             test_SrcParse_Nodes02(
    const
    char            *pTestName
)
{
    SRCPARSE_DATA   *pPrs = OBJ_NIL;
    ERESULT_DATA    *pErr;
    NODE_DATA       *pNodes = OBJ_NIL;
    NODEHASH_DATA   *pHash = OBJ_NIL;
    OBJARRAY_DATA   *pArray = OBJ_NIL;
    NODELIB_DATA    *pLib;
    NODEPGM_DATA    *pPgm;
    const
    char            *pGoodJson1 =
    "{\n"
        "\"library\":{\n"
            "\"name\":\"Cmn\",\n"
        "}\n,"
        "\"objects\": [\n"
            "{name:\"AStr\", \"srcDeps\":[\"libCmn.h\"], \"json\":true},\n"
            "{name:\"appl\", \"srcDeps\":[\"libCmn.h\"]},\n"
        "],\n"
        "\"routines\": [\n"
                "{name:\"dllist.c\"}\n"
        "],\n"
    "}\n";
    bool            fDumpNodes = false;
    uint32_t        iMax;
    NODEOBJ_DATA    *pObj;
    NODERTN_DATA    *pRtn;
    ASTRC_DATA      *pStrC;

    fprintf(stderr, "Performing: %s\n", pTestName);
    
    pPrs = SrcParse_New( );
    TINYTEST_FALSE( (OBJ_NIL == pPrs) );
    if (pPrs) {
        
        //obj_TraceSet(pObj, true);
        pErr = SrcParse_ParseJsonStr(pPrs, pGoodJson1);
        if (pErr) {
            eResult_Fprint(pErr, stderr);
        }
        TINYTEST_TRUE( (OBJ_NIL == pErr) );
        TINYTEST_FALSE( (OBJ_NIL == pPrs->pNodes) );
        TINYTEST_TRUE( (obj_IsKindOf(pPrs->pNodes, OBJ_IDENT_NODE)) );
        pHash = node_getData(pPrs->pNodes);
        TINYTEST_FALSE( (OBJ_NIL == pHash) );
        TINYTEST_TRUE( (obj_IsKindOf(pHash, OBJ_IDENT_NODEARRAY)
                        || obj_IsKindOf(pHash, OBJ_IDENT_NODEHASH)) );

        if (fDumpNodes) {
            ASTR_DATA       *pWrk = OBJ_NIL;
            pWrk = node_ToDebugString(pPrs->pNodes, 0);
            fprintf(stderr, "\n====> JSON Input:\n%s\n\n\n", AStr_getData(pWrk));
            obj_Release(pWrk);
            pWrk = OBJ_NIL;
        }

        pErr = SrcParse_ParseNodes(pPrs);
        if (pErr) {
            eResult_Fprint(pErr, stderr);
        }
        TINYTEST_TRUE((OBJ_NIL == pErr));

        // Validate Library vs Program.
        pPgm = SrcParse_getPgm(pPrs);
        TINYTEST_TRUE( (OBJ_NIL == pPgm) );
        pLib = SrcParse_getLib(pPrs);
        TINYTEST_FALSE( (OBJ_NIL == pLib) );
        if (fDumpNodes) {
            ASTR_DATA       *pWrk = OBJ_NIL;
            pWrk = NodeLib_ToDebugString(pLib, 0);
            fprintf(stderr, "\n====> PGM Node:\n%s\n\n", AStr_getData(pWrk));
            obj_Release(pWrk);
            pWrk = OBJ_NIL;
        }
        pStrC = NodeLib_getName(pLib);
        TINYTEST_FALSE( (OBJ_NIL == pStrC) );
        TINYTEST_TRUE((ERESULT_SUCCESS_EQUAL == AStrC_CompareA(pStrC,"Cmn")));

        // Validate Objects.
        pArray = SrcParse_getObjs(pPrs);
        TINYTEST_FALSE( (OBJ_NIL == pArray) );
        iMax = objArray_getSize(pArray);
        fprintf(stderr, "\tNumber of Objects: %d\n", iMax);
        TINYTEST_TRUE( (2 == iMax) );
        pObj = objArray_Get(pArray, 1);
        TINYTEST_FALSE( (OBJ_NIL == pObj) );
        if (fDumpNodes) {
            ASTR_DATA       *pWrk = OBJ_NIL;
            pWrk = NodeObj_ToDebugString(pObj, 0);
            fprintf(stderr, "\n====> OBJ 1 Node:\n%s\n\n", AStr_getData(pWrk));
            obj_Release(pWrk);
            pWrk = OBJ_NIL;
        }
        pStrC = NodeObj_getName(pObj);
        TINYTEST_FALSE( (OBJ_NIL == pStrC) );
        TINYTEST_TRUE((ERESULT_SUCCESS_EQUAL == AStrC_CompareA(pStrC,"AStr")));
        pObj = objArray_Get(pArray, 2);
        TINYTEST_FALSE( (OBJ_NIL == pObj) );
        if (fDumpNodes) {
            ASTR_DATA       *pWrk = OBJ_NIL;
            pWrk = NodeObj_ToDebugString(pObj, 0);
            fprintf(stderr, "\n====> OBJ 2 Node:\n%s\n\n", AStr_getData(pWrk));
            obj_Release(pWrk);
            pWrk = OBJ_NIL;
        }
        pStrC = NodeObj_getName(pObj);
        TINYTEST_FALSE( (OBJ_NIL == pStrC) );
        TINYTEST_TRUE((ERESULT_SUCCESS_EQUAL == AStrC_CompareA(pStrC,"appl")));

        // Validate Routines.
        pArray = SrcParse_getRtns(pPrs);
        TINYTEST_FALSE( (OBJ_NIL == pArray) );
        iMax = objArray_getSize(pArray);
        fprintf(stderr, "\tNumber of Routines: %d\n", iMax);
        TINYTEST_TRUE( (1 == iMax) );
        pRtn = objArray_Get(pArray, 1);
        TINYTEST_FALSE( (OBJ_NIL == pRtn) );
        if (fDumpNodes) {
            ASTR_DATA       *pWrk = OBJ_NIL;
            pWrk = NodeRtn_ToDebugString(pRtn, 0);
            fprintf(stderr, "\n====> RTN 1 Node:\n%s\n\n", AStr_getData(pWrk));
            obj_Release(pWrk);
            pWrk = OBJ_NIL;
        }
        pStrC = NodeRtn_getName(pRtn);
        TINYTEST_FALSE( (OBJ_NIL == pStrC) );
        TINYTEST_TRUE((ERESULT_SUCCESS_EQUAL == AStrC_CompareA(pStrC,"dllist.c")));

        obj_Release(pNodes);
        pNodes = OBJ_NIL;

        obj_Release(pPrs);
        pPrs = OBJ_NIL;
    }

    fprintf(stderr, "...%s completed.\n\n\n\n", pTestName);
    return 1;
}




TINYTEST_START_SUITE(test_srcParse);
    TINYTEST_ADD_TEST(test_SrcParse_Nodes02,setUp,tearDown);
    TINYTEST_ADD_TEST(test_SrcParse_Nodes01,setUp,tearDown);
    TINYTEST_ADD_TEST(test_SrcParse_Test01,setUp,tearDown);
    TINYTEST_ADD_TEST(test_SrcParse_Routine02,setUp,tearDown);
    TINYTEST_ADD_TEST(test_SrcParse_Routine01,setUp,tearDown);
    TINYTEST_ADD_TEST(test_SrcParse_Object03,setUp,tearDown);
    TINYTEST_ADD_TEST(test_SrcParse_Object02,setUp,tearDown);
    TINYTEST_ADD_TEST(test_SrcParse_Object01,setUp,tearDown);
    TINYTEST_ADD_TEST(test_SrcParse_OpenClose,setUp,tearDown);
TINYTEST_END_SUITE();

TINYTEST_MAIN_SINGLE_SUITE(test_srcParse);





