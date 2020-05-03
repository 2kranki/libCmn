// vi:nu:et:sts=4 ts=4 sw=4
/*
 *	Generated 04/26/2020 17:31:56
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
#include    <NodeProp_internal.h>
#ifdef  NODEPROP_JSON_SUPPORT
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

#ifdef  NODEPROP_JSON_SUPPORT
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






int             test_NodeProp_OpenClose (
    const
    char            *pTestName
)
{
    ERESULT         eRc = ERESULT_SUCCESS;
    NODEPROP_DATA	*pObj = OBJ_NIL;
    bool            fRc;
   
    fprintf(stderr, "Performing: %s\n", pTestName);

    pObj = NodeProp_Alloc( );
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    pObj = NodeProp_Init( pObj );
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    if (pObj) {

        //obj_TraceSet(pObj, true);       
        fRc = obj_IsKindOf(pObj, OBJ_IDENT_NODEPROP);
        TINYTEST_TRUE( (fRc) );

        // Test something.
        TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );

        obj_Release(pObj);
        pObj = OBJ_NIL;
    }

    fprintf(stderr, "...%s completed.\n\n\n", pTestName);
    return 1;
}



int             test_NodeProp_Copy01 (
    const
    char            *pTestName
)
{
    ERESULT         eRc = ERESULT_SUCCESS;
    NODEPROP_DATA	*pObj1 = OBJ_NIL;
    NODEPROP_DATA	*pObj2 = OBJ_NIL;
    bool            fRc;
#if defined(NODEPROP_JSON_SUPPORT)
    ASTR_DATA	    *pStr = OBJ_NIL;
#endif
   
    fprintf(stderr, "Performing: %s\n", pTestName);

    pObj1 = NodeProp_New( );
    TINYTEST_FALSE( (OBJ_NIL == pObj1) );
    if (pObj1) {

        //obj_TraceSet(pObj1, true);       
        fRc = obj_IsKindOf(pObj1, OBJ_IDENT_NODEPROP);
        TINYTEST_TRUE( (fRc) );
        pObj1->pName = AStr_NewA("name");
        pObj1->pExternal = AStr_NewA("xyzzy");
        pObj1->pInternal = AStr_NewA("pName");
        pObj1->pShort = AStr_NewA("Name Description");
        pObj1->pTypeDef = AStr_NewA("OBJ_ID");
        pObj1->vis = NODEPROP_VIS_PUBLIC;
        pObj1->fObj = 'T';

        // Test assign.
        pObj2 = NodeProp_New();
        TINYTEST_FALSE( (OBJ_NIL == pObj2) );
        eRc = NodeProp_Assign(pObj1, pObj2);
        TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );

        fRc = obj_IsKindOf(pObj2, OBJ_IDENT_NODEPROP);
        TINYTEST_TRUE( (fRc) );
        //eRc = NodeProp_Compare(pObj1, pObj2);
        //TINYTEST_TRUE( (ERESULT_SUCCESS_EQUAL == eRc) );
        //TODO: Add More tests here!

        obj_Release(pObj2);
        pObj2 = OBJ_NIL;

        // Test copy.
        pObj2 = NodeProp_Copy(pObj1);
        TINYTEST_FALSE( (OBJ_NIL == pObj2) );

        fRc = obj_IsKindOf(pObj2, OBJ_IDENT_NODEPROP);
        TINYTEST_TRUE( (fRc) );
        //eRc = NodeProp_Compare(pObj1, pObj2);
        //TINYTEST_TRUE( (ERESULT_SUCCESS_EQUAL == eRc) );
        //TODO: Add More tests here!

        obj_Release(pObj2);
        pObj2 = OBJ_NIL;

        // Test json support.
#if defined(NODEPROP_JSON_SUPPORT)
        pStr = NodeProp_ToJson(pObj1);
        TINYTEST_FALSE( (OBJ_NIL == pStr) );
        fprintf(stderr, "JSON: %s\n", AStr_getData(pStr));
        pObj2 = NodeProp_NewFromJsonString(pStr);
        TINYTEST_FALSE( (OBJ_NIL == pObj2) );
        fRc = obj_IsKindOf(pObj2, OBJ_IDENT_NODEPROP);
        TINYTEST_TRUE( (fRc) );
        obj_Release(pStr);
        pStr = OBJ_NIL;
        //eRc = NodeProp_Compare(pObj1, pObj2);
        //TINYTEST_TRUE( (ERESULT_SUCCESS_EQUAL == eRc) );

        obj_Release(pObj2);
        pObj2 = OBJ_NIL;
#endif

        obj_Release(pObj1);
        pObj1 = OBJ_NIL;
    }

    fprintf(stderr, "...%s completed.\n\n\n", pTestName);
    return 1;
}



int             test_NodeProp_Test01 (
    const
    char            *pTestName
)
{
    //ERESULT         eRc = ERESULT_SUCCESS;
    NODEPROP_DATA   *pObj = OBJ_NIL;
    bool            fRc;
    ASTR_DATA       *pStr = OBJ_NIL;
   
    fprintf(stderr, "Performing: %s\n", pTestName);

    pObj = NodeProp_New( );
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    if (pObj) {

        pObj->pName = AStr_NewA("Name");
        pObj->pInternal = AStr_NewA("pName");
        pObj->pShort = AStr_NewA("Name Description");
        pObj->pTypeDef = AStr_NewA("ASTR_DATA");
        pObj->vis = NODEPROP_VIS_PUBLIC;
        pObj->fObj = 'T';

        //obj_TraceSet(pObj, true);
        fRc = obj_IsKindOf(pObj, OBJ_IDENT_NODEPROP);
        TINYTEST_TRUE( (fRc) );
        //TINYTEST_TRUE( (ERESULT_OK(eRc)) );
        
        {
            ASTR_DATA       *pStr = NodeProp_ToDebugString(pObj, 0);
            if (pStr) {
                fprintf(stderr, "Debug: %s\n", AStr_getData(pStr));
                obj_Release(pStr);
                pStr = OBJ_NIL;
            }
        }

        fprintf(stderr, "         1         2         3\n");
        fprintf(stderr, "123456789012345678901234567890\n");
        pStr = NodeProp_GenHdrDefn(pObj, "Class", "CLASS_DATA");
        TINYTEST_FALSE( (OBJ_NIL == pStr) );
        fprintf(stderr, "Header:\n%s\n", AStr_getData(pStr));
        obj_Release(pStr);
        pStr = OBJ_NIL;

        fprintf(stderr, "         1         2         3\n");
        fprintf(stderr, "123456789012345678901234567890\n");
        pStr = NodeProp_GenCode(pObj, "Class", "CLASS_DATA");
        TINYTEST_FALSE( (OBJ_NIL == pStr) );
        fprintf(stderr, "Header:\n%s\n", AStr_getData(pStr));
        obj_Release(pStr);
        pStr = OBJ_NIL;

        fprintf(stderr, "         1         2         3\n");
        fprintf(stderr, "123456789012345678901234567890\n");
        pObj->vis = NODEPROP_VIS_READ_ONLY;
        pStr = NodeProp_GenIntVar(pObj, "Class", "CLASS_DATA");
        TINYTEST_FALSE( (OBJ_NIL == pStr) );
        fprintf(stderr, "Header:\n%s\n", AStr_getData(pStr));
        obj_Release(pStr);
        pStr = OBJ_NIL;

        obj_Release(pObj);
        pObj = OBJ_NIL;
    }

    fprintf(stderr, "...%s completed.\n\n\n", pTestName);
    return 1;
}



int             test_NodeProp_Test02 (
    const
    char            *pTestName
)
{
    //ERESULT         eRc = ERESULT_SUCCESS;
    NODEPROP_DATA   *pObj = OBJ_NIL;
    bool            fRc;
    ASTR_DATA       *pStr = OBJ_NIL;

    fprintf(stderr, "Performing: %s\n", pTestName);

    pObj = NodeProp_New( );
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    if (pObj) {

        pObj->pName = AStr_NewA("name");
        pObj->pExternal = AStr_NewA("xyzzy");
        pObj->pInternal = AStr_NewA("pName");
        pObj->pShort = AStr_NewA("Name Description");
        pObj->pTypeDef = AStr_NewA("OBJ_ID");
        pObj->vis = NODEPROP_VIS_PUBLIC;
        pObj->fObj = 'T';

        //obj_TraceSet(pObj, true);
        fRc = obj_IsKindOf(pObj, OBJ_IDENT_NODEPROP);
        TINYTEST_TRUE( (fRc) );
        //TINYTEST_TRUE( (ERESULT_OK(eRc)) );

        {
            ASTR_DATA       *pStr = NodeProp_ToDebugString(pObj, 0);
            if (pStr) {
                fprintf(stderr, "Debug: %s\n", AStr_getData(pStr));
                obj_Release(pStr);
                pStr = OBJ_NIL;
            }
        }

        fprintf(stderr, "         1         2         3\n");
        fprintf(stderr, "123456789012345678901234567890\n");
        pStr = NodeProp_GenHdrDefn(pObj, "Class", "CLASS_DATA");
        TINYTEST_FALSE( (OBJ_NIL == pStr) );
        fprintf(stderr, "Header:\n%s\n", AStr_getData(pStr));
        obj_Release(pStr);
        pStr = OBJ_NIL;

        fprintf(stderr, "         1         2         3\n");
        fprintf(stderr, "123456789012345678901234567890\n");
        pStr = NodeProp_GenCode(pObj, "Class", "CLASS_DATA");
        TINYTEST_FALSE( (OBJ_NIL == pStr) );
        fprintf(stderr, "Header:\n%s\n", AStr_getData(pStr));
        obj_Release(pStr);
        pStr = OBJ_NIL;

        fprintf(stderr, "         1         2         3\n");
        fprintf(stderr, "123456789012345678901234567890\n");
        pObj->vis = NODEPROP_VIS_READ_ONLY;
        pStr = NodeProp_GenIntVar(pObj, "Class", "CLASS_DATA");
        TINYTEST_FALSE( (OBJ_NIL == pStr) );
        fprintf(stderr, "Header:\n%s\n", AStr_getData(pStr));
        obj_Release(pStr);
        pStr = OBJ_NIL;

        obj_Release(pObj);
        pObj = OBJ_NIL;
    }

    fprintf(stderr, "...%s completed.\n\n\n", pTestName);
    return 1;
}



int             test_NodeProp_Test03 (
    const
    char            *pTestName
)
{
    //ERESULT         eRc = ERESULT_SUCCESS;
    NODEPROP_DATA   *pObj = OBJ_NIL;
    bool            fRc;
    ASTR_DATA       *pStr = OBJ_NIL;

    fprintf(stderr, "Performing: %s\n", pTestName);

    pObj = NodeProp_New( );
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    if (pObj) {

        pObj->pName = AStr_NewA("name");
        pObj->pShort = AStr_NewA("Name Description");
        pObj->pTypeDef = AStr_NewA("int32_t");
        pObj->vis = NODEPROP_VIS_PUBLIC;

        //obj_TraceSet(pObj, true);
        fRc = obj_IsKindOf(pObj, OBJ_IDENT_NODEPROP);
        TINYTEST_TRUE( (fRc) );
        //TINYTEST_TRUE( (ERESULT_OK(eRc)) );

        {
            ASTR_DATA       *pStr = NodeProp_ToDebugString(pObj, 0);
            if (pStr) {
                fprintf(stderr, "Debug: %s\n", AStr_getData(pStr));
                obj_Release(pStr);
                pStr = OBJ_NIL;
            }
        }

        fprintf(stderr, "         1         2         3\n");
        fprintf(stderr, "123456789012345678901234567890\n");
        pStr = NodeProp_GenHdrDefn(pObj, "Class", "CLASS_DATA");
        TINYTEST_FALSE( (OBJ_NIL == pStr) );
        fprintf(stderr, "Header:\n%s\n", AStr_getData(pStr));
        obj_Release(pStr);
        pStr = OBJ_NIL;

        fprintf(stderr, "         1         2         3\n");
        fprintf(stderr, "123456789012345678901234567890\n");
        pObj->vis = NODEPROP_VIS_READ_ONLY;
        pStr = NodeProp_GenHdrDefn(pObj, "Class", "CLASS_DATA");
        TINYTEST_FALSE( (OBJ_NIL == pStr) );
        fprintf(stderr, "Header:\n%s\n", AStr_getData(pStr));
        obj_Release(pStr);
        pStr = OBJ_NIL;

        fprintf(stderr, "         1         2         3\n");
        fprintf(stderr, "123456789012345678901234567890\n");
        pStr = NodeProp_GenCode(pObj, "Class", "CLASS_DATA");
        TINYTEST_FALSE( (OBJ_NIL == pStr) );
        fprintf(stderr, "Header:\n%s\n", AStr_getData(pStr));
        obj_Release(pStr);
        pStr = OBJ_NIL;

        fprintf(stderr, "         1         2         3\n");
        fprintf(stderr, "123456789012345678901234567890\n");
        pObj->vis = NODEPROP_VIS_READ_ONLY;
        pStr = NodeProp_GenIntVar(pObj, "Class", "CLASS_DATA");
        TINYTEST_FALSE( (OBJ_NIL == pStr) );
        fprintf(stderr, "Header:\n%s\n", AStr_getData(pStr));
        obj_Release(pStr);
        pStr = OBJ_NIL;

        obj_Release(pObj);
        pObj = OBJ_NIL;
    }

    fprintf(stderr, "...%s completed.\n\n\n", pTestName);
    return 1;
}




TINYTEST_START_SUITE(test_NodeProp);
    TINYTEST_ADD_TEST(test_NodeProp_Test03,setUp,tearDown);
    TINYTEST_ADD_TEST(test_NodeProp_Test02,setUp,tearDown);
    TINYTEST_ADD_TEST(test_NodeProp_Test01,setUp,tearDown);
    TINYTEST_ADD_TEST(test_NodeProp_Copy01,setUp,tearDown);
    TINYTEST_ADD_TEST(test_NodeProp_OpenClose,setUp,tearDown);
TINYTEST_END_SUITE();

TINYTEST_MAIN_SINGLE_SUITE(test_NodeProp);





