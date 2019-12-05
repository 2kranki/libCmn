// vi:nu:et:sts=4 ts=4 sw=4
/*
 *	Generated 11/10/2019 17:43:09
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
#include    <srcErrors.h>
#include    <szTbl.h>
#include    <trace.h>
#include    <ExpandNodes_internal.h>
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






int             test_ExpandNodes_OpenClose(
    const
    char            *pTestName
)
{
    ERESULT             eRc = ERESULT_SUCCESS;
    //ERESULT_DATA        *pErr;
    EXPANDNODES_DATA    *pObj = OBJ_NIL;
   
    fprintf(stderr, "Performing: %s\n", pTestName);

    pObj = ExpandNodes_Alloc( );
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    pObj = ExpandNodes_Init( pObj );
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



int             test_ExpandNodes_Program01(
    const
    char            *pTestName
)
{
    SRCPARSE_DATA   *pPrs = OBJ_NIL;
    EXPANDNODES_DATA *pExpand = OBJ_NIL;
    ERESULT_DATA    *pErr;
    NODE_DATA       *pNodes = OBJ_NIL;
    NODEHASH_DATA   *pHash = OBJ_NIL;
    NODEARRAY_DATA  *pArray = OBJ_NIL;
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
                "{name:\"dllist\", suffix:\"c\", \"test\":true},\n"
                "{name:\"cmnMac64\", suffix:\"c\", os:[\"macos64\"]},\n"
                "{name:\"obj\", suffix:\"c\"},\n"
                "{name:\"str\", \"suffix\":\"c\", test:true}\n"
        "],\n"
    "}\n";
    bool            fDumpNodes = true;
    uint32_t        iMax;
    NODELIB_DATA    *pLib;
    NODEPGM_DATA    *pPgm;
    NODEOBJ_DATA    *pObj;
    NODERTN_DATA    *pRtn;
    NODERTNA_DATA   *pRtnA;
    NODETSTA_DATA   *pTstA;
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
        
        pExpand = ExpandNodes_New();
        TINYTEST_FALSE( (OBJ_NIL == pExpand) );
        if (pExpand) {
            
            pArray = SrcParse_getObjs(pPrs);
            if (fDumpNodes) {
                ASTR_DATA       *pWrk = OBJ_NIL;
                pWrk = nodeArray_ToDebugString(pArray, 0);
                fprintf(stderr, "\n====> OBJ Array:\n%s\n\n\n", AStr_getData(pWrk));
                obj_Release(pWrk);
                pWrk = OBJ_NIL;
            }
            pErr = ExpandNodes_ExpandObjs(pExpand, pArray);
            TINYTEST_TRUE( (OBJ_NIL == pErr) );
            ExpandNodes_Sort(pExpand);
            pArray = ExpandNodes_getRtns(pExpand);
            TINYTEST_FALSE( (OBJ_NIL == pArray) );
            iMax = nodeArray_getSize(pArray);
            fprintf(stderr, "\tObjs: Number of RtnAs: %d\n", iMax);
            TINYTEST_TRUE( (5 == iMax) );
            if (fDumpNodes) {
                ASTR_DATA       *pWrk = OBJ_NIL;
                pWrk = nodeArray_ToDebugString(pArray, 0);
                fprintf(stderr, "\n====> RTNA Array:\n%s\n\n\n", AStr_getData(pWrk));
                obj_Release(pWrk);
                pWrk = OBJ_NIL;
            }
            pArray = ExpandNodes_getTests(pExpand);
            TINYTEST_FALSE( (OBJ_NIL == pArray) );
            iMax = nodeArray_getSize(pArray);
            fprintf(stderr, "\tObjs: Number of TstAs: %d\n", iMax);
            TINYTEST_TRUE( (2 == iMax) );
            if (fDumpNodes) {
                ASTR_DATA       *pWrk = OBJ_NIL;
                pWrk = nodeArray_ToDebugString(pArray, 0);
                fprintf(stderr, "\n====> TSTA Array:\n%s\n\n\n", AStr_getData(pWrk));
                obj_Release(pWrk);
                pWrk = OBJ_NIL;
            }

            ExpandNodes_Clean(pExpand);
            pArray = SrcParse_getRtns(pPrs);
            if (fDumpNodes) {
                ASTR_DATA       *pWrk = OBJ_NIL;
                pWrk = nodeArray_ToDebugString(pArray, 0);
                fprintf(stderr, "\n====> RTN Array:\n%s\n\n\n", AStr_getData(pWrk));
                obj_Release(pWrk);
                pWrk = OBJ_NIL;
            }
            pErr = ExpandNodes_ExpandRtns(pExpand, pArray);
            TINYTEST_TRUE( (OBJ_NIL == pErr) );
            ExpandNodes_Sort(pExpand);
            pArray = ExpandNodes_getRtns(pExpand);
            TINYTEST_FALSE( (OBJ_NIL == pArray) );
            iMax = nodeArray_getSize(pArray);
            fprintf(stderr, "\tRtns: Number of RtnAs: %d\n", iMax);
            TINYTEST_TRUE( (4 == iMax) );
            if (fDumpNodes) {
                ASTR_DATA       *pWrk = OBJ_NIL;
                pWrk = nodeArray_ToDebugString(pArray, 0);
                fprintf(stderr, "\n====> RTNA Array:\n%s\n\n\n", AStr_getData(pWrk));
                obj_Release(pWrk);
                pWrk = OBJ_NIL;
            }
            pArray = ExpandNodes_getTests(pExpand);
            TINYTEST_FALSE( (OBJ_NIL == pArray) );
            iMax = nodeArray_getSize(pArray);
            fprintf(stderr, "\tRtns: Number of TstAs: %d\n", iMax);
            TINYTEST_TRUE( (2 == iMax) );
            if (fDumpNodes) {
                ASTR_DATA       *pWrk = OBJ_NIL;
                pWrk = nodeArray_ToDebugString(pArray, 0);
                fprintf(stderr, "\n====> TSTA Array:\n%s\n\n\n", AStr_getData(pWrk));
                obj_Release(pWrk);
                pWrk = OBJ_NIL;
            }

            obj_Release(pExpand);
            pExpand = OBJ_NIL;
        }

        obj_Release(pNodes);
        pNodes = OBJ_NIL;

        obj_Release(pPrs);
        pPrs = OBJ_NIL;
    }

    fprintf(stderr, "...%s completed.\n\n\n\n", pTestName);
    return 1;
}



int             test_ExpandNodes_Program02(
    const
    char            *pTestName
)
{
    SRCPARSE_DATA   *pPrs = OBJ_NIL;
    EXPANDNODES_DATA *pExpand = OBJ_NIL;
    ERESULT_DATA    *pErr;
    NODE_DATA       *pNodes = OBJ_NIL;
    NODEHASH_DATA   *pHash = OBJ_NIL;
    NODEARRAY_DATA  *pArray = OBJ_NIL;
    const
    char            *pGoodJson1 =
    "{\n"
        "\"program\":{\n"
            "\"name\":\"genMake\",\n"
            "\"deps\":[\"Cmd\"]\n"
        "}\n,"
        "\"routines\": [\n"
                "{name:\"dllist\", suffix:\"c\", \"test\":true},\n"
                "{name:\"cmnMac64\", suffix:\"c\", os:[\"macos64\"]},\n"
                "{name:\"obj\", suffix:\"c\", arch:[\"x86\"]},\n"
                "{name:\"str\", \"suffix\":\"c\", test:true}\n"
        "],\n"
    "}\n";
    bool            fDumpNodes = true;
    uint32_t        iMax;
    NODELIB_DATA    *pLib;
    NODEPGM_DATA    *pPgm;
    NODEOBJ_DATA    *pObj;
    NODERTN_DATA    *pRtn;
    NODERTNA_DATA   *pRtnA;
    NODETSTA_DATA   *pTstA;
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
        
        pExpand = ExpandNodes_New();
        TINYTEST_FALSE( (OBJ_NIL == pExpand) );
        if (pExpand) {
            
            pArray = SrcParse_getRtns(pPrs);
            if (fDumpNodes) {
                ASTR_DATA       *pWrk = OBJ_NIL;
                pWrk = nodeArray_ToDebugString(pArray, 0);
                fprintf(stderr, "\n====> RTN Array:\n%s\n\n\n", AStr_getData(pWrk));
                obj_Release(pWrk);
                pWrk = OBJ_NIL;
            }
            pErr = ExpandNodes_ExpandRtns(pExpand, pArray);
            TINYTEST_TRUE( (OBJ_NIL == pErr) );
            ExpandNodes_Sort(pExpand);
            pArray = ExpandNodes_getRtns(pExpand);
            TINYTEST_FALSE( (OBJ_NIL == pArray) );
            iMax = nodeArray_getSize(pArray);
            fprintf(stderr, "\tRtns: Number of RtnAs: %d\n", iMax);
            TINYTEST_TRUE( (4 == iMax) );
            if (fDumpNodes) {
                ASTR_DATA       *pWrk = OBJ_NIL;
                pWrk = nodeArray_ToDebugString(pArray, 0);
                fprintf(stderr, "\n====> RTNA Array:\n%s\n\n\n", AStr_getData(pWrk));
                obj_Release(pWrk);
                pWrk = OBJ_NIL;
            }
            pArray = ExpandNodes_getTests(pExpand);
            TINYTEST_FALSE( (OBJ_NIL == pArray) );
            iMax = nodeArray_getSize(pArray);
            fprintf(stderr, "\tRtns: Number of TstAs: %d\n", iMax);
            TINYTEST_TRUE( (2 == iMax) );
            if (fDumpNodes) {
                ASTR_DATA       *pWrk = OBJ_NIL;
                pWrk = nodeArray_ToDebugString(pArray, 0);
                fprintf(stderr, "\n====> TSTA Array:\n%s\n\n\n", AStr_getData(pWrk));
                obj_Release(pWrk);
                pWrk = OBJ_NIL;
            }

            obj_Release(pExpand);
            pExpand = OBJ_NIL;
        }

        obj_Release(pNodes);
        pNodes = OBJ_NIL;

        obj_Release(pPrs);
        pPrs = OBJ_NIL;
    }

    fprintf(stderr, "...%s completed.\n\n\n\n", pTestName);
    return 1;
}




TINYTEST_START_SUITE(test_ExpandNodes);
    TINYTEST_ADD_TEST(test_ExpandNodes_Program02,setUp,tearDown);
    TINYTEST_ADD_TEST(test_ExpandNodes_Program01,setUp,tearDown);
    TINYTEST_ADD_TEST(test_ExpandNodes_OpenClose,setUp,tearDown);
TINYTEST_END_SUITE();

TINYTEST_MAIN_SINGLE_SUITE(test_ExpandNodes);





