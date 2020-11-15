// vi:nu:et:sts=4 ts=4 sw=4
/*
 *	Generated 01/29/2020 13:19:38
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
#include    <trace.h>
#include    <Path_internal.h>
#ifdef  PATH_JSON_SUPPORT
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

#ifdef  PATH_JSON_SUPPORT
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






int             test_Path_OpenClose (
    const
    char            *pTestName
)
{
    ERESULT         eRc = ERESULT_SUCCESS;
    PATH_DATA	    *pObj = OBJ_NIL;
    bool            fRc;
   
    fprintf(stderr, "Performing: %s\n", pTestName);

    pObj = Path_Alloc( );
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    pObj = Path_Init( pObj );
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    if (pObj) {

        //obj_TraceSet(pObj, true);       
        fRc = obj_IsKindOf(pObj, OBJ_IDENT_PATH);
        TINYTEST_TRUE( (fRc) );
        
        // Test something.
        TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );

        obj_Release(pObj);
        pObj = OBJ_NIL;
    }

    fprintf(stderr, "...%s completed.\n\n\n", pTestName);
    return 1;
}



int             test_Path_Copy01 (
    const
    char            *pTestName
)
{
    ERESULT         eRc = ERESULT_SUCCESS;
    PATH_DATA	    *pObj1 = OBJ_NIL;
    PATH_DATA	    *pObj2 = OBJ_NIL;
    bool            fRc;
#if defined(PATH_JSON_SUPPORT)
    ASTR_DATA	    *pStr = OBJ_NIL;
#endif
   
    fprintf(stderr, "Performing: %s\n", pTestName);

    pObj1 = Path_NewA("/Applications");
    TINYTEST_FALSE( (OBJ_NIL == pObj1) );
    if (pObj1) {

        //obj_TraceSet(pObj1, true);       
        fRc = obj_IsKindOf(pObj1, OBJ_IDENT_PATH);
        TINYTEST_TRUE( (fRc) );
        
        // Test assign.
        pObj2 = Path_New();
        TINYTEST_FALSE( (OBJ_NIL == pObj2) );
        eRc = Path_Assign(pObj1, pObj2);
        TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );

        fRc = obj_IsKindOf(pObj2, OBJ_IDENT_PATH);
        TINYTEST_TRUE( (fRc) );
        eRc = Path_Compare(pObj1, pObj2);
        TINYTEST_TRUE( (0 == eRc) );
        //TODO: Add More tests here!

        obj_Release(pObj2);
        pObj2 = OBJ_NIL;

        // Test copy.
        pObj2 = Path_Copy(pObj1);
        TINYTEST_FALSE( (OBJ_NIL == pObj2) );

        fRc = obj_IsKindOf(pObj2, OBJ_IDENT_PATH);
        TINYTEST_TRUE( (fRc) );
        //TODO: Add More tests here!

        obj_Release(pObj2);
        pObj2 = OBJ_NIL;

        // Test json support.
#if defined(PATH_JSON_SUPPORT)
        pStr = Path_ToJson(pObj1);
        TINYTEST_FALSE( (OBJ_NIL == pStr) );
        fprintf(stderr, "JSON: %s\n", AStr_getData(pStr));
        pObj2 = Path_NewFromJsonString(pStr);
        TINYTEST_FALSE( (OBJ_NIL == pObj2) );
        fRc = obj_IsKindOf(pObj2, OBJ_IDENT_PATH);
        TINYTEST_TRUE( (fRc) );
        obj_Release(pStr);
        pStr = OBJ_NIL;
        eRc = Path_Compare(pObj1, pObj2);
        TINYTEST_TRUE( (0 == eRc) );

        obj_Release(pObj2);
        pObj2 = OBJ_NIL;
#endif

        obj_Release(pObj1);
        pObj1 = OBJ_NIL;
    }

    fprintf(stderr, "...%s completed.\n\n\n", pTestName);
    return 1;
}



int             test_Path_Test01 (
    const
    char            *pTestName
)
{
    //ERESULT         eRc = ERESULT_SUCCESS;
    PATH_DATA	    *pObj = OBJ_NIL;
    bool            fRc;
   
    fprintf(stderr, "Performing: %s\n", pTestName);

    pObj = Path_New( );
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    if (pObj) {

        //obj_TraceSet(pObj, true);       
        fRc = obj_IsKindOf(pObj, OBJ_IDENT_PATH);
        TINYTEST_TRUE( (fRc) );
        
        obj_Release(pObj);
        pObj = OBJ_NIL;
    }

    fprintf(stderr, "...%s completed.\n\n\n", pTestName);
    return 1;
}



int         test_Path_CharFindNext(
    const
    char        *pTestName
)
{
    PATH_DATA	*pObj = OBJ_NIL;
    ERESULT     eRc;
    uint32_t    index;
    
    fprintf(stderr, "Performing: %s\n", pTestName);
    pObj = Path_NewA("file://Users/bob/x/tmp.txt");
    XCTAssertFalse( (OBJ_NIL == pObj) );
    if (pObj) {
        
        index = 0;      // Start at the beginning.
        eRc = AStr_CharFindNextW32((ASTR_DATA *)pObj, &index, '/');
        XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
        XCTAssertTrue( (6 == index) );
        
        obj_Release(pObj);
        pObj = OBJ_NIL;
    }
    
    fprintf(stderr, "...%s completed.\n", pTestName);
    return 1;
}



int         test_Path_DateLastUpdated(
    const
    char        *pTestName
)
{
    PATH_DATA       *pObj = OBJ_NIL;
    ERESULT         eRc;
    uint32_t        index;
    DATETIME_DATA   *pTime = OBJ_NIL;
    ASTR_DATA       *pStr = OBJ_NIL;
    const
    char            *pStrA;
    
    fprintf(stderr, "Performing: %s\n", pTestName);
    pObj = Path_NewA("/Users/bob/Support/testFiles/test_ebcdic.txt");
    XCTAssertFalse( (OBJ_NIL == pObj) );
    if (pObj) {
        
        index = 0;      // Start at the beginning.
        eRc = Path_DateLastUpdated(pObj, &pTime);
        XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
        XCTAssertFalse( (OBJ_NIL == pTime) );
        if (pTime) {
            pStr = DateTime_ToString(pTime);
            if (pStr) {
                pStrA = AStr_getData(pStr);
                fprintf(stderr, "\tDate = \"%s\"\n", pStrA);
                //XCTAssertTrue( (0 == strcmp(" 4/ 3/2000  1:37:14.000", AStr_getData(pStr))) );
                XCTAssertTrue( ((*pStrA == ' ') || (*pStrA == '1')) );
                ++pStrA;
                XCTAssertTrue( ((*pStrA >= '0') && (*pStrA <= '9')) );
                ++pStrA;
                XCTAssertTrue( (*pStrA == '/') );
                ++pStrA;
                XCTAssertTrue( ((*pStrA == ' ') || ((*pStrA >= '1') && (*pStrA <= '3'))) );
                ++pStrA;
                XCTAssertTrue( ((*pStrA >= '0') && (*pStrA <= '9')) );
                ++pStrA;
                XCTAssertTrue( (*pStrA == '/') );
                obj_Release(pStr);
                pStr = OBJ_NIL;
            }
            obj_Release(pTime);
            pTime = OBJ_NIL;
        }

        obj_Release(pObj);
        pObj = OBJ_NIL;
    }
    
    fprintf(stderr, "...%s completed.\n", pTestName);
    return 1;
}



int         test_Path_NewFromEnv(
    const
    char        *pTestName
)
{
    PATH_DATA	*pObj = OBJ_NIL;
    ERESULT     eRc;
    
    fprintf(stderr, "Performing: %s\n", pTestName);
    pObj = Path_NewFromEnv("HOME");
    XCTAssertFalse( (OBJ_NIL == pObj) );
    if (pObj) {
        
        eRc = Path_CompareA(pObj, "/Users/bob");
        XCTAssertTrue( (0 == eRc) );
        
        obj_Release(pObj);
        pObj = OBJ_NIL;
    }
    
    fprintf(stderr, "...%s completed.\n", pTestName);
    return 1;
}



int         test_Path_SplitPath01(
    const
    char        *pTestName
)
{
    PATH_DATA	*pObj = OBJ_NIL;
    ERESULT     eRc;
    ASTR_DATA   *pDrive = OBJ_NIL;
    PATH_DATA   *pPath = OBJ_NIL;
    PATH_DATA   *pFileName = OBJ_NIL;
    ASTR_DATA   *pFileN = OBJ_NIL;
    ASTR_DATA   *pFileE = OBJ_NIL;
    
    fprintf(stderr, "Performing: %s\n", pTestName);
    pObj = Path_NewA("file://Users/bob/x/tmp.txt");
    XCTAssertFalse( (OBJ_NIL == pObj) );
    if (pObj) {
        
        eRc = Path_SplitPath(pObj, &pDrive, &pPath, &pFileName);
        XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );

        XCTAssertTrue( (pDrive) );
        XCTAssertTrue( (4 == AStr_getLength(pDrive)) );
        XCTAssertTrue( (0 == strcmp(AStr_getData(pDrive), "file")) );
        if (pDrive) {
            obj_Release(pDrive);
            pDrive = OBJ_NIL;
        }
        
        XCTAssertTrue( (pPath) );
        XCTAssertTrue( (12 == AStr_getLength((ASTR_DATA *)pPath)) );
        XCTAssertTrue( (0 == strcmp(AStr_getData((ASTR_DATA *)pPath), "/Users/bob/x")) );
        if (pPath) {
            obj_Release(pPath);
            pPath = OBJ_NIL;
        }

        XCTAssertTrue( (pFileName) );
        XCTAssertTrue( (7 == AStr_getLength((ASTR_DATA *)pFileName)) );
        XCTAssertTrue( (0 == strcmp(AStr_getData((ASTR_DATA *)pFileName), "tmp.txt")) );
        
        eRc = Path_SplitFile(pFileName, &pFileN, &pFileE);
        XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
        if (pFileName) {
            obj_Release(pFileName);
            pFileName = OBJ_NIL;
        }
        
        XCTAssertTrue( (pFileN) );
        XCTAssertTrue( (3 == AStr_getLength(pFileN)) );
        XCTAssertTrue( (0 == strcmp(AStr_getData(pFileN), "tmp")) );
        if (pFileN) {
            obj_Release(pFileN);
            pFileN = OBJ_NIL;
        }
        
        XCTAssertTrue( (pFileE) );
        XCTAssertTrue( (3 == AStr_getLength(pFileE)) );
        XCTAssertTrue( (0 == strcmp(AStr_getData(pFileE), "txt")) );
        if (pFileE) {
            obj_Release(pFileE);
            pFileE = OBJ_NIL;
        }
       
        obj_Release(pObj);
        pObj = OBJ_NIL;
    }
    
    fprintf(stderr, "...%s completed.\n", pTestName);
    return 1;
}



int         test_Path_SplitPath02(
    const
    char        *pTestName
)
{
    PATH_DATA	*pObj = OBJ_NIL;
    ERESULT     eRc;
    ASTR_DATA  *pDrive = OBJ_NIL;
    PATH_DATA   *pPath = OBJ_NIL;
    PATH_DATA   *pFileName = OBJ_NIL;
    ASTR_DATA  *pFileN = OBJ_NIL;
    ASTR_DATA  *pFileE = OBJ_NIL;
    
    fprintf(stderr, "Performing: %s\n", pTestName);
    pObj = Path_NewA("/Users/bob/x/tmp.txt");
    XCTAssertFalse( (OBJ_NIL == pObj) );
    if (pObj) {
        
        eRc = Path_SplitPath(pObj, &pDrive, &pPath, &pFileName);
        XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
        
        XCTAssertTrue( (NULL == pDrive) );
        
        XCTAssertTrue( (pPath) );
        XCTAssertTrue( (12 == AStr_getLength((ASTR_DATA *)pPath)) );
        XCTAssertTrue( (0 == strcmp(AStr_getData((ASTR_DATA *)pPath), "/Users/bob/x")) );
        if (pPath) {
            obj_Release(pPath);
            pPath = OBJ_NIL;
        }
        
        eRc = Path_SplitFile(pFileName, &pFileN, &pFileE);
        XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
        if (pFileName) {
            obj_Release(pFileName);
            pFileName = OBJ_NIL;
        }
        
        XCTAssertTrue( (pFileN) );
        XCTAssertTrue( (3 == AStr_getLength(pFileN)) );
        XCTAssertTrue( (0 == strcmp(AStr_getData(pFileN), "tmp")) );
        if (pFileN) {
            obj_Release(pFileN);
            pFileN = OBJ_NIL;
        }
        
        XCTAssertTrue( (pFileE) );
        XCTAssertTrue( (3 == AStr_getLength(pFileE)) );
        XCTAssertTrue( (0 == strcmp(AStr_getData(pFileE), "txt")) );
        if (pFileE) {
            obj_Release(pFileE);
            pFileE = OBJ_NIL;
        }
        
        obj_Release(pObj);
        pObj = OBJ_NIL;
    }
    
    fprintf(stderr, "...%s completed.\n", pTestName);
    return 1;
}



int         test_Path_SplitPath03(
    const
    char        *pTestName
)
{
    PATH_DATA	*pObj = OBJ_NIL;
    ERESULT     eRc;
    ASTR_DATA  *pDrive = OBJ_NIL;
    PATH_DATA   *pPath = OBJ_NIL;
    PATH_DATA   *pFileName = OBJ_NIL;
    ASTR_DATA  *pFileN = OBJ_NIL;
    ASTR_DATA  *pFileE = OBJ_NIL;
    
    fprintf(stderr, "Performing: %s\n", pTestName);
    pObj = Path_NewA("tmp.txt");
    XCTAssertFalse( (OBJ_NIL == pObj) );
    if (pObj) {
        
        eRc = Path_SplitPath(pObj, &pDrive, &pPath, &pFileName);
        XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
        
        XCTAssertTrue( (NULL == pDrive) );
        
        XCTAssertTrue( (NULL == pPath) );
        
        eRc = Path_SplitFile(pFileName, &pFileN, &pFileE);
        XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
        if (pFileName) {
            obj_Release(pFileName);
            pFileName = OBJ_NIL;
        }
        
        XCTAssertTrue( (pFileN) );
        XCTAssertTrue( (3 == AStr_getLength(pFileN)) );
        XCTAssertTrue( (0 == strcmp(AStr_getData(pFileN), "tmp")) );
        if (pFileN) {
            obj_Release(pFileN);
            pFileN = OBJ_NIL;
        }
        
        XCTAssertTrue( (pFileE) );
        XCTAssertTrue( (3 == AStr_getLength(pFileE)) );
        XCTAssertTrue( (0 == strcmp(AStr_getData(pFileE), "txt")) );
        if (pFileE) {
            obj_Release(pFileE);
            pFileE = OBJ_NIL;
        }
        
        obj_Release(pObj);
        pObj = OBJ_NIL;
    }
    
    fprintf(stderr, "...%s completed.\n", pTestName);
    return 1;
}



int         test_Path_SplitPath04(
    const
    char        *pTestName
)
{
    PATH_DATA	*pObj = OBJ_NIL;
    ERESULT     eRc;
    ASTR_DATA  *pDrive = OBJ_NIL;
    PATH_DATA   *pPath = OBJ_NIL;
    PATH_DATA   *pFileName = OBJ_NIL;
    ASTR_DATA  *pFileN = OBJ_NIL;
    ASTR_DATA  *pFileE = OBJ_NIL;
    
    fprintf(stderr, "Performing: %s\n", pTestName);
    pObj = Path_NewA("/tmp.txt");
    XCTAssertFalse( (OBJ_NIL == pObj) );
    if (pObj) {
        
        eRc = Path_SplitPath(pObj, &pDrive, &pPath, &pFileName);
        XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
        
        XCTAssertTrue( (NULL == pDrive) );
        
        XCTAssertTrue( (pPath) );
        XCTAssertTrue( (1 == AStr_getLength((ASTR_DATA *)pPath)) );
        XCTAssertTrue( (0 == strcmp(AStr_getData((ASTR_DATA *)pPath), "/")) );
        if (pPath) {
            obj_Release(pPath);
            pPath = OBJ_NIL;
        }
        
        eRc = Path_SplitFile(pFileName, &pFileN, &pFileE);
        XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
        if (pFileName) {
            obj_Release(pFileName);
            pFileName = OBJ_NIL;
        }
        
        XCTAssertTrue( (pFileN) );
        XCTAssertTrue( (3 == AStr_getLength(pFileN)) );
        XCTAssertTrue( (0 == strcmp(AStr_getData(pFileN), "tmp")) );
        if (pFileN) {
            obj_Release(pFileN);
            pFileN = OBJ_NIL;
        }
        
        XCTAssertTrue( (pFileE) );
        XCTAssertTrue( (3 == AStr_getLength(pFileE)) );
        XCTAssertTrue( (0 == strcmp(AStr_getData(pFileE), "txt")) );
        if (pFileE) {
            obj_Release(pFileE);
            pFileE = OBJ_NIL;
        }
        
        obj_Release(pObj);
        pObj = OBJ_NIL;
    }
    
    fprintf(stderr, "...%s completed.\n", pTestName);
    return 1;
}



int         test_Path_SplitPath05(
    const
    char        *pTestName
)
{
    PATH_DATA	*pObj = OBJ_NIL;
    ERESULT     eRc;
    ASTR_DATA  *pDrive = OBJ_NIL;
    PATH_DATA   *pFileName = OBJ_NIL;
    PATH_DATA   *pPath = OBJ_NIL;
    ASTR_DATA  *pFileN = OBJ_NIL;
    ASTR_DATA  *pFileE = OBJ_NIL;
    
    fprintf(stderr, "Performing: %s\n", pTestName);
    pObj = Path_NewA("file:tmp.txt");
    XCTAssertFalse( (OBJ_NIL == pObj) );
    if (pObj) {
        
        eRc = Path_SplitPath(pObj, &pDrive, &pPath, &pFileName);
        XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
        
        XCTAssertTrue( (pDrive) );
        XCTAssertTrue( (4 == AStr_getLength(pDrive)) );
        XCTAssertTrue( (0 == strcmp(AStr_getData(pDrive), "file")) );
        if (pDrive) {
            obj_Release(pDrive);
            pDrive = OBJ_NIL;
        }
        
        XCTAssertTrue( (NULL == pPath) );
        
        eRc = Path_SplitFile(pFileName, &pFileN, &pFileE);
        XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
        if (pFileName) {
            obj_Release(pFileName);
            pFileName = OBJ_NIL;
        }
        
        XCTAssertTrue( (pFileN) );
        XCTAssertTrue( (3 == AStr_getLength(pFileN)) );
        XCTAssertTrue( (0 == strcmp(AStr_getData(pFileN), "tmp")) );
        if (pFileN) {
            obj_Release(pFileN);
            pFileN = OBJ_NIL;
        }
        
        XCTAssertTrue( (pFileE) );
        XCTAssertTrue( (3 == AStr_getLength(pFileE)) );
        XCTAssertTrue( (0 == strcmp(AStr_getData(pFileE), "txt")) );
        if (pFileE) {
            obj_Release(pFileE);
            pFileE = OBJ_NIL;
        }
        
        obj_Release(pObj);
        pObj = OBJ_NIL;
    }
    
    fprintf(stderr, "...%s completed.\n", pTestName);
    return 1;
}



int         test_Path_SplitPath06(
    const
    char        *pTestName
)
{
    PATH_DATA	*pObj = OBJ_NIL;
    ERESULT     eRc;
    ASTR_DATA  *pDrive = OBJ_NIL;
    PATH_DATA   *pPath = OBJ_NIL;
    PATH_DATA   *pFileName = OBJ_NIL;
    ASTR_DATA  *pFileN = OBJ_NIL;
    ASTR_DATA  *pFileE = OBJ_NIL;
    
    fprintf(stderr, "Performing: %s\n", pTestName);
    pObj = Path_NewA("file:/tmp.txt");
    XCTAssertFalse( (OBJ_NIL == pObj) );
    if (pObj) {
        
        eRc = Path_SplitPath(pObj, &pDrive, &pPath, &pFileName);
        XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
        
        XCTAssertTrue( (pDrive) );
        XCTAssertTrue( (4 == AStr_getLength(pDrive)) );
        XCTAssertTrue( (0 == strcmp(AStr_getData(pDrive), "file")) );
        if (pDrive) {
            obj_Release(pDrive);
            pDrive = OBJ_NIL;
        }
        
        XCTAssertTrue( (pPath) );
        XCTAssertTrue( (1 == AStr_getLength((ASTR_DATA *)pPath)) );
        XCTAssertTrue( (0 == strcmp(AStr_getData((ASTR_DATA *)pPath), "/")) );
        if (pPath) {
            obj_Release(pPath);
            pPath = OBJ_NIL;
        }
        
        eRc = Path_SplitFile(pFileName, &pFileN, &pFileE);
        XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
        if (pFileName) {
            obj_Release(pFileName);
            pFileName = OBJ_NIL;
        }
        
        XCTAssertTrue( (pFileN) );
        XCTAssertTrue( (3 == AStr_getLength(pFileN)) );
        XCTAssertTrue( (0 == strcmp(AStr_getData(pFileN), "tmp")) );
        if (pFileN) {
            obj_Release(pFileN);
            pFileN = OBJ_NIL;
        }
        
        XCTAssertTrue( (pFileE) );
        XCTAssertTrue( (3 == AStr_getLength(pFileE)) );
        XCTAssertTrue( (0 == strcmp(AStr_getData(pFileE), "txt")) );
        if (pFileE) {
            obj_Release(pFileE);
            pFileE = OBJ_NIL;
        }
        
        obj_Release(pObj);
        pObj = OBJ_NIL;
    }
    
    fprintf(stderr, "...%s completed.\n", pTestName);
    return 1;
}



int         test_Path_SplitPath07(
    const
    char        *pTestName
)
{
    PATH_DATA	*pObj = OBJ_NIL;
    ERESULT     eRc;
    ASTR_DATA  *pDrive = OBJ_NIL;
    PATH_DATA   *pPath = OBJ_NIL;
    PATH_DATA   *pFileName = OBJ_NIL;
    ASTR_DATA  *pFileN = OBJ_NIL;
    ASTR_DATA  *pFileE = OBJ_NIL;
    
    fprintf(stderr, "Performing: %s\n", pTestName);
    pObj = Path_NewA(":/tmp.txt");
    XCTAssertFalse( (OBJ_NIL == pObj) );
    if (pObj) {
        
        eRc = Path_SplitPath(pObj, &pDrive, &pPath, &pFileName);
        XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
        
        XCTAssertTrue( (NULL == pDrive) );
        
        XCTAssertTrue( (pPath) );
        XCTAssertTrue( (1 == AStr_getLength((ASTR_DATA *)pPath)) );
        XCTAssertTrue( (0 == strcmp(AStr_getData((ASTR_DATA *)pPath), "/")) );
        if (pPath) {
            obj_Release(pPath);
            pPath = OBJ_NIL;
        }
        
        eRc = Path_SplitFile(pFileName, &pFileN, &pFileE);
        XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
        if (pFileName) {
            obj_Release(pFileName);
            pFileName = OBJ_NIL;
        }
        
        XCTAssertTrue( (pFileN) );
        XCTAssertTrue( (3 == AStr_getLength(pFileN)) );
        XCTAssertTrue( (0 == strcmp(AStr_getData(pFileN), "tmp")) );
        if (pFileN) {
            obj_Release(pFileN);
            pFileN = OBJ_NIL;
        }
        
        XCTAssertTrue( (pFileE) );
        XCTAssertTrue( (3 == AStr_getLength(pFileE)) );
        XCTAssertTrue( (0 == strcmp(AStr_getData(pFileE), "txt")) );
        if (pFileE) {
            obj_Release(pFileE);
            pFileE = OBJ_NIL;
        }
        
        obj_Release(pObj);
        pObj = OBJ_NIL;
    }
    
    fprintf(stderr, "...%s completed.\n", pTestName);
    return 1;
}



int         test_Path_SplitPath08(
    const
    char        *pTestName
)
{
    PATH_DATA	*pObj = OBJ_NIL;
    ERESULT     eRc;
    ASTR_DATA  *pDrive = OBJ_NIL;
    PATH_DATA   *pPath = OBJ_NIL;
    PATH_DATA   *pFileName = OBJ_NIL;
    ASTR_DATA  *pFileN = OBJ_NIL;
    ASTR_DATA  *pFileE = OBJ_NIL;
    
    fprintf(stderr, "Performing: %s\n", pTestName);
    pObj = Path_NewA("tmp");
    XCTAssertFalse( (OBJ_NIL == pObj) );
    if (pObj) {
        
        eRc = Path_SplitPath(pObj, &pDrive, &pPath, &pFileName);
        XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
        
        XCTAssertTrue( (NULL == pDrive) );
        
        XCTAssertTrue( (NULL == pPath) );
        
        eRc = Path_SplitFile(pFileName, &pFileN, &pFileE);
        XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
        if (pFileName) {
            obj_Release(pFileName);
            pFileName = OBJ_NIL;
        }
        
        XCTAssertTrue( (pFileN) );
        XCTAssertTrue( (3 == AStr_getLength(pFileN)) );
        XCTAssertTrue( (0 == strcmp(AStr_getData(pFileN), "tmp")) );
        if (pFileN) {
            obj_Release(pFileN);
            pFileN = OBJ_NIL;
        }
        
        XCTAssertTrue( (NULL == pFileE) );
        
        obj_Release(pObj);
        pObj = OBJ_NIL;
    }
    
    fprintf(stderr, "...%s completed.\n", pTestName);
    return 1;
}



int         test_Path_SplitPath09(
    const
    char        *pTestName
)
{
    PATH_DATA   *pObj = OBJ_NIL;
    ERESULT     eRc;
    ASTR_DATA   *pDrive = OBJ_NIL;
    PATH_DATA   *pPath = OBJ_NIL;
    PATH_DATA   *pFileName = OBJ_NIL;
    ASTR_DATA   *pFileN = OBJ_NIL;
    ASTR_DATA   *pFileE = OBJ_NIL;

    fprintf(stderr, "Performing: %s\n", pTestName);
    pObj = Path_NewA("/tmp/x/");
    XCTAssertFalse( (OBJ_NIL == pObj) );
    if (pObj) {

        eRc = Path_SplitPath(pObj, &pDrive, &pPath, &pFileName);
        XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );

        XCTAssertTrue( (NULL == pDrive) );

        XCTAssertFalse( (NULL == pPath) );
        XCTAssertTrue( (6 == AStr_getLength((ASTR_DATA *)pPath)) );
        XCTAssertTrue( (0 == strcmp(AStr_getData((ASTR_DATA *)pPath), "/tmp/x")) );
        obj_Release(pPath);
        pPath = OBJ_NIL;

        XCTAssertTrue( (NULL == pFileName) );

        XCTAssertTrue( (NULL == pFileN) );

        XCTAssertTrue( (NULL == pFileE) );

        obj_Release(pObj);
        pObj = OBJ_NIL;
    }

    fprintf(stderr, "...%s completed.\n", pTestName);
    return 1;
}



int         test_Path_SplitFile01(
    const
    char        *pTestName
)
{
    PATH_DATA   *pObj = OBJ_NIL;
    ERESULT     eRc;
    //ASTR_DATA   *pDrive = OBJ_NIL;
    //PATH_DATA   *pPath = OBJ_NIL;
    PATH_DATA   *pFileName = OBJ_NIL;
    ASTR_DATA   *pFileN = OBJ_NIL;
    ASTR_DATA   *pFileE = OBJ_NIL;
    
    fprintf(stderr, "Performing: %s\n", pTestName);
    pObj = Path_NewA("/x/y/z.txt");
    XCTAssertFalse( (OBJ_NIL == pObj) );
    if (pObj) {
        
        eRc = Path_SplitFile(pObj, &pFileN, &pFileE);
        XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
        if (pFileName) {
            obj_Release(pFileName);
            pFileName = OBJ_NIL;
        }
        
        XCTAssertTrue( (pFileN) );
        XCTAssertTrue( (6 == AStr_getLength(pFileN)) );
        XCTAssertTrue( (0 == strcmp(AStr_getData(pFileN), "/x/y/z")) );
        if (pFileN) {
            obj_Release(pFileN);
            pFileN = OBJ_NIL;
        }
        
        XCTAssertTrue( (pFileE) );
        XCTAssertTrue( (3 == AStr_getLength(pFileE)) );
        XCTAssertTrue( (0 == strcmp(AStr_getData(pFileE), "txt")) );
        if (pFileE) {
            obj_Release(pFileE);
            pFileE = OBJ_NIL;
        }

        obj_Release(pObj);
        pObj = OBJ_NIL;
    }
    
    fprintf(stderr, "...%s completed.\n", pTestName);
    return 1;
}



int         test_Path_SplitFile02(
    const
    char        *pTestName
)
{
    PATH_DATA   *pObj = OBJ_NIL;
    ERESULT     eRc;
    //ASTR_DATA   *pDrive = OBJ_NIL;
    //PATH_DATA   *pPath = OBJ_NIL;
    PATH_DATA   *pFileName = OBJ_NIL;
    ASTR_DATA   *pFileN = OBJ_NIL;
    ASTR_DATA   *pFileE = OBJ_NIL;
    
    fprintf(stderr, "Performing: %s\n", pTestName);
    pObj = Path_NewA("txt");
    XCTAssertFalse( (OBJ_NIL == pObj) );
    if (pObj) {
        
        eRc = Path_SplitFile(pObj, &pFileN, &pFileE);
        XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
        if (pFileName) {
            obj_Release(pFileName);
            pFileName = OBJ_NIL;
        }
        
        XCTAssertTrue( (pFileN) );
        XCTAssertTrue( (3 == AStr_getLength(pFileN)) );
        XCTAssertTrue( (0 == strcmp(AStr_getData(pFileN), "txt")) );
        if (pFileN) {
            obj_Release(pFileN);
            pFileN = OBJ_NIL;
        }
        
        XCTAssertTrue( (OBJ_NIL == pFileE) );
        //XCTAssertTrue( (3 == AStr_getLength(pFileE)) );
        //XCTAssertTrue( (0 == strcmp(AStr_getData(pFileE), "txt")) );
        if (pFileE) {
            obj_Release(pFileE);
            pFileE = OBJ_NIL;
        }
        
        obj_Release(pObj);
        pObj = OBJ_NIL;
    }
    
    fprintf(stderr, "...%s completed.\n", pTestName);
    return 1;
}



int         test_Path_CleanDir01(
    const
    char        *pTestName
)
{
    PATH_DATA	*pObj = OBJ_NIL;
    ERESULT     eRc;
    
    fprintf(stderr, "Performing: %s\n", pTestName);
    pObj = Path_NewA("//tmp/");
    XCTAssertFalse( (OBJ_NIL == pObj) );
    if (pObj) {
        
        eRc = Path_Clean(pObj);
        XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
        XCTAssertTrue( (4 == AStr_getLength((ASTR_DATA *)pObj)) );
        XCTAssertTrue( (0 == strcmp(AStr_getData((ASTR_DATA *)pObj), "/tmp")) );
        
        obj_Release(pObj);
        pObj = OBJ_NIL;
    }
    
    fprintf(stderr, "...%s completed.\n", pTestName);
    return 1;
}



int         test_Path_CleanDir02(
    const
    char        *pTestName
)
{
    PATH_DATA	*pObj = OBJ_NIL;
    ERESULT     eRc;
    
    fprintf(stderr, "Performing: %s\n", pTestName);
    pObj = Path_NewA("/");
    XCTAssertFalse( (OBJ_NIL == pObj) );
    if (pObj) {
        
        eRc = Path_Clean(pObj);
        XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
        XCTAssertTrue( (1 == AStr_getLength((ASTR_DATA *)pObj)) );
        XCTAssertTrue( (0 == strcmp(AStr_getData((ASTR_DATA *)pObj), "/")) );
        
        obj_Release(pObj);
        pObj = OBJ_NIL;
    }
    
    fprintf(stderr, "...%s completed.\n", pTestName);
    return 1;
}



int         test_Path_CleanDir03(
    const
    char        *pTestName
)
{
    PATH_DATA	*pObj = OBJ_NIL;
    ERESULT     eRc;
    
    fprintf(stderr, "Performing: %s\n", pTestName);
    pObj = Path_NewA("/./");
    XCTAssertFalse( (OBJ_NIL == pObj) );
    if (pObj) {
        
        eRc = Path_Clean(pObj);
        XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
        XCTAssertTrue( (1 == AStr_getLength((ASTR_DATA *)pObj)) );
        XCTAssertTrue( (0 == strcmp(AStr_getData((ASTR_DATA *)pObj), "/")) );
        
        obj_Release(pObj);
        pObj = OBJ_NIL;
    }
    
    fprintf(stderr, "...%s completed.\n", pTestName);
    return 1;
}



int         test_Path_CleanDir04(
    const
    char        *pTestName
)
{
    PATH_DATA	*pObj = OBJ_NIL;
    ERESULT     eRc;
    
    fprintf(stderr, "Performing: %s\n", pTestName);
    pObj = Path_NewA("x/./y");
    XCTAssertFalse( (OBJ_NIL == pObj) );
    if (pObj) {
        
        eRc = Path_Clean(pObj);
        XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
        XCTAssertTrue( (3 == AStr_getLength((ASTR_DATA *)pObj)) );
        XCTAssertTrue( (0 == strcmp(AStr_getData((ASTR_DATA *)pObj), "x/y")) );
        
        obj_Release(pObj);
        pObj = OBJ_NIL;
    }
    
    fprintf(stderr, "...%s completed.\n", pTestName);
    return 1;
}



int         test_Path_CleanDir05(
    const
    char        *pTestName
)
{
    PATH_DATA	*pObj = OBJ_NIL;
    ERESULT     eRc;
    
    fprintf(stderr, "Performing: %s\n", pTestName);
    pObj = Path_NewA("x//y");
    XCTAssertFalse( (OBJ_NIL == pObj) );
    if (pObj) {
        
        eRc = Path_Clean(pObj);
        XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
        XCTAssertTrue( (3 == AStr_getLength((ASTR_DATA *)pObj)) );
        XCTAssertTrue( (0 == strcmp(AStr_getData((ASTR_DATA *)pObj), "x/y")) );
        
        obj_Release(pObj);
        pObj = OBJ_NIL;
    }
    
    fprintf(stderr, "...%s completed.\n", pTestName);
    return 1;
}



int         test_Path_CleanDir06(
    const
    char        *pTestName
)
{
    PATH_DATA	*pObj = OBJ_NIL;
    ERESULT     eRc;
    const
    char        *pszStr;
    uint32_t    i;
    
    fprintf(stderr, "Performing: %s\n", pTestName);
    pObj = Path_NewA("~/y.tmp");
    XCTAssertFalse( (OBJ_NIL == pObj) );
    if (pObj) {
        
        eRc = Path_Clean(pObj);
        XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
        i = AStr_getLength((ASTR_DATA *)pObj);
        XCTAssertTrue( (16 == i) );
        pszStr = AStr_getData((ASTR_DATA *)pObj);
        XCTAssertTrue( (0 == strcmp(pszStr, "/Users/bob/y.tmp")) );
        
        obj_Release(pObj);
        pObj = OBJ_NIL;
    }
    
    fprintf(stderr, "...%s completed.\n", pTestName);
    return 1;
}



int         test_Path_ToBash(
    const
    char        *pTestName
)
{
    PATH_DATA	*pObj = OBJ_NIL;
    ERESULT     eRc;
    ASTR_DATA   *pStr;
    
    fprintf(stderr, "Performing: %s\n", pTestName);
    pObj = Path_NewA("xy z.txt");
    XCTAssertFalse( (OBJ_NIL == pObj) );
    if (pObj) {
        
        eRc = Path_ToBash(pObj,&pStr);
        XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
        XCTAssertTrue( (9 == AStr_getLength(pStr)) );
        XCTAssertTrue( (0 == AStr_CompareA(pStr, "xy\\ z.txt")) );
        obj_Release(pStr);
        pStr = NULL;
        
        obj_Release(pObj);
        pObj = OBJ_NIL;
    }
    
    fprintf(stderr, "...%s completed.\n", pTestName);
    return 1;
}



int         test_Path_ExpandEnvVars01(
    const
    char        *pTestName
)
{
    PATH_DATA   *pObj = OBJ_NIL;
    ERESULT     eRc;
    //ASTR_DATA   *pStr = OBJ_NIL;
    const
    char        *pHome = NULL;
    int         len = 0;
    
    fprintf(stderr, "Performing: %s\n", pTestName);
    pHome = getenv("HOME");
    if (pHome) {
        len = (int)strlen(pHome);
    }
    pObj = Path_NewA("${HOME}");
    XCTAssertFalse( (OBJ_NIL == pObj) );
    if (pObj) {
        
        eRc = Path_ExpandVars(pObj, NULL, OBJ_NIL);
        XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
        XCTAssertTrue( (len == AStr_getLength((ASTR_DATA *)pObj)) );
        XCTAssertTrue( (0 == AStr_CompareA((ASTR_DATA *)pObj, pHome)) );
        //obj_Release(pStr);
        //pStr = NULL;
        
        obj_Release(pObj);
        pObj = OBJ_NIL;
    }
    
    fprintf(stderr, "...%s completed.\n", pTestName);
    return 1;
}



int         test_Path_ExpandEnvVars02(
    const
    char        *pTestName
)
{
    PATH_DATA   *pObj = OBJ_NIL;
    ERESULT     eRc;
    ASTR_DATA   *pStr = OBJ_NIL;
    const
    char        *pHome = NULL;
    int         len = 0;
    
    fprintf(stderr, "Performing: %s\n", pTestName);
    pHome = getenv("HOME");
    if (pHome) {
        len = (int)strlen(pHome);
        pStr = AStr_NewA(pHome);
        eRc = AStr_AppendA(pStr, "$");
        XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
        eRc = AStr_AppendA(pStr, pHome);
        XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
    }
    pObj = Path_NewA("${HOME}$${HOME}");
    XCTAssertFalse( (OBJ_NIL == pObj) );
    if (pObj) {
        
        eRc = Path_ExpandVars(pObj, NULL, OBJ_NIL);
        XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
        XCTAssertTrue( (AStr_getLength(pStr) == AStr_getLength((ASTR_DATA *)pObj)) );
        XCTAssertTrue( (0 == AStr_Compare((ASTR_DATA *)pObj, pStr)) );
        
        obj_Release(pObj);
        pObj = OBJ_NIL;
    }
    obj_Release(pStr);
    pStr = NULL;

    fprintf(stderr, "...%s completed.\n", pTestName);
    return 1;
}



int         test_Path_Version01(
    const
    char        *pTestName
)
{
    PATH_DATA   *pObj = OBJ_NIL;
    PATH_DATA   *pPath = OBJ_NIL;
    PATH_DATA   *pPathW = OBJ_NIL;
    ERESULT     eRc;
    ASTR_DATA   *pStrF = OBJ_NIL;
    ASTR_DATA   *pStrE = OBJ_NIL;
    //ASTR_DATA   *pStrW = OBJ_NIL;
    
    fprintf(stderr, "Performing: %s\n", pTestName);
    pObj = Path_NewA("~/git/libCmn/programs/genMake/tests/test.txt");
    XCTAssertFalse( (OBJ_NIL == pObj) );
    if (pObj) {
        
        eRc = Path_Clean(pObj);
        XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
        
        eRc = Path_IsExisting(pObj);
        XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
        
        pPath = Path_ToVersioned(pObj);
        XCTAssertFalse( (OBJ_NIL == pPath) );
        fprintf(stderr, "\tversion = \"%s\"\n", Path_getData(pPath));

        eRc = Path_SplitPath(pPath, OBJ_NIL, OBJ_NIL, &pPathW);
        XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );

        eRc = Path_SplitFile(pPathW, &pStrF, &pStrE);
        XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
        XCTAssertFalse( (OBJ_NIL == pStrF) );
        XCTAssertFalse( (OBJ_NIL == pStrE) );

        eRc = AStr_CompareA(pStrF, "test.0002");
        XCTAssertTrue( (0 == eRc) );
        eRc = AStr_CompareA(pStrE, "txt");
        XCTAssertTrue( (0 == eRc) );

        obj_Release(pStrE);
        pStrE = OBJ_NIL;
        obj_Release(pStrF);
        pStrF = OBJ_NIL;
        obj_Release(pPathW);
        pPathW = OBJ_NIL;
        obj_Release(pPath);
        pPath = OBJ_NIL;
        obj_Release(pObj);
        pObj = OBJ_NIL;
    }
    
    fprintf(stderr, "...%s completed.\n", pTestName);
    return 1;
}




TINYTEST_START_SUITE(test_Path);
    TINYTEST_ADD_TEST(test_Path_Version01,setUp,tearDown);
    TINYTEST_ADD_TEST(test_Path_ExpandEnvVars02,setUp,tearDown);
    TINYTEST_ADD_TEST(test_Path_ExpandEnvVars01,setUp,tearDown);
    TINYTEST_ADD_TEST(test_Path_ToBash,setUp,tearDown);
    TINYTEST_ADD_TEST(test_Path_CleanDir06,setUp,tearDown);
    TINYTEST_ADD_TEST(test_Path_CleanDir05,setUp,tearDown);
    TINYTEST_ADD_TEST(test_Path_CleanDir04,setUp,tearDown);
    TINYTEST_ADD_TEST(test_Path_CleanDir03,setUp,tearDown);
    TINYTEST_ADD_TEST(test_Path_CleanDir02,setUp,tearDown);
    TINYTEST_ADD_TEST(test_Path_CleanDir01,setUp,tearDown);
    TINYTEST_ADD_TEST(test_Path_SplitFile02,setUp,tearDown);
    TINYTEST_ADD_TEST(test_Path_SplitFile01,setUp,tearDown);
    TINYTEST_ADD_TEST(test_Path_SplitPath09,setUp,tearDown);
    TINYTEST_ADD_TEST(test_Path_SplitPath08,setUp,tearDown);
    TINYTEST_ADD_TEST(test_Path_SplitPath07,setUp,tearDown);
    TINYTEST_ADD_TEST(test_Path_SplitPath06,setUp,tearDown);
    TINYTEST_ADD_TEST(test_Path_SplitPath05,setUp,tearDown);
    TINYTEST_ADD_TEST(test_Path_SplitPath04,setUp,tearDown);
    TINYTEST_ADD_TEST(test_Path_SplitPath03,setUp,tearDown);
    TINYTEST_ADD_TEST(test_Path_SplitPath02,setUp,tearDown);
    TINYTEST_ADD_TEST(test_Path_SplitPath01,setUp,tearDown);
    TINYTEST_ADD_TEST(test_Path_NewFromEnv,setUp,tearDown);
    TINYTEST_ADD_TEST(test_Path_DateLastUpdated,setUp,tearDown);
    TINYTEST_ADD_TEST(test_Path_CharFindNext,setUp,tearDown);
    TINYTEST_ADD_TEST(test_Path_Test01,setUp,tearDown);
    TINYTEST_ADD_TEST(test_Path_Copy01,setUp,tearDown);
    TINYTEST_ADD_TEST(test_Path_OpenClose,setUp,tearDown);
TINYTEST_END_SUITE();

TINYTEST_MAIN_SINGLE_SUITE(test_Path);





