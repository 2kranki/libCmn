/*
 *	Generated 06/05/2017 21:57:10
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
#include    <path_internal.h>



int         setUp(
    const
    char        *pTestName
)
{
    mem_Init( );
    trace_Shared( ); 
    // Put setup code here. This method is called before the invocation of each
    // test method in the class.
    
    return 1; 
}


int         tearDown(
    const
    char        *pTestName
)
{
    // Put teardown code here. This method is called after the invocation of each
    // test method in the class.

    
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






int         test_path_OpenClose(
    const
    char        *pTestName
)
{
    PATH_DATA	*pObj = OBJ_NIL;
   
    fprintf(stderr, "Performing: %s\n", pTestName);
    pObj = path_Alloc( );
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    pObj = path_Init( pObj );
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    if (pObj) {

        // Test something.

        obj_Release(pObj);
        pObj = OBJ_NIL;
    }

    fprintf(stderr, "...%s completed.\n", pTestName);
    return 1;
}



int         test_path_CharFindNext(
    const
    char        *pTestName
)
{
    PATH_DATA	*pObj = OBJ_NIL;
    ERESULT     eRc;
    uint32_t    index;
    
    fprintf(stderr, "Performing: %s\n", pTestName);
    pObj = path_NewA("file://Users/bob/x/tmp.txt");
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



int         test_path_DateLastUpdated(
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
    pObj = path_NewA("/Users/bob/Support/testFiles/test_ebcdic.txt");
    XCTAssertFalse( (OBJ_NIL == pObj) );
    if (pObj) {
        
        index = 0;      // Start at the beginning.
        eRc = path_DateLastUpdated(pObj, &pTime);
        XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
        XCTAssertFalse( (OBJ_NIL == pTime) );
        if (pTime) {
            pStr = dateTime_ToString(pTime);
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



int         test_path_NewFromEnv(
    const
    char        *pTestName
)
{
    PATH_DATA	*pObj = OBJ_NIL;
    ERESULT     eRc;
    
    fprintf(stderr, "Performing: %s\n", pTestName);
    pObj = path_NewFromEnv("HOME");
    XCTAssertFalse( (OBJ_NIL == pObj) );
    if (pObj) {
        
        eRc = path_CompareA(pObj, "/Users/bob");
        XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
        
        obj_Release(pObj);
        pObj = OBJ_NIL;
    }
    
    fprintf(stderr, "...%s completed.\n", pTestName);
    return 1;
}



int         test_path_SplitPath01(
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
    pObj = path_NewA("file://Users/bob/x/tmp.txt");
    XCTAssertFalse( (OBJ_NIL == pObj) );
    if (pObj) {
        
        eRc = path_SplitPath(pObj, &pDrive, &pPath, &pFileName);
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
        
        eRc = path_SplitFile(pFileName, &pFileN, &pFileE);
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



int         test_path_SplitPath02(
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
    pObj = path_NewA("/Users/bob/x/tmp.txt");
    XCTAssertFalse( (OBJ_NIL == pObj) );
    if (pObj) {
        
        eRc = path_SplitPath(pObj, &pDrive, &pPath, &pFileName);
        XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
        
        XCTAssertTrue( (NULL == pDrive) );
        
        XCTAssertTrue( (pPath) );
        XCTAssertTrue( (12 == AStr_getLength((ASTR_DATA *)pPath)) );
        XCTAssertTrue( (0 == strcmp(AStr_getData((ASTR_DATA *)pPath), "/Users/bob/x")) );
        if (pPath) {
            obj_Release(pPath);
            pPath = OBJ_NIL;
        }
        
        eRc = path_SplitFile(pFileName, &pFileN, &pFileE);
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



int         test_path_SplitPath03(
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
    pObj = path_NewA("tmp.txt");
    XCTAssertFalse( (OBJ_NIL == pObj) );
    if (pObj) {
        
        eRc = path_SplitPath(pObj, &pDrive, &pPath, &pFileName);
        XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
        
        XCTAssertTrue( (NULL == pDrive) );
        
        XCTAssertTrue( (NULL == pPath) );
        
        eRc = path_SplitFile(pFileName, &pFileN, &pFileE);
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



int         test_path_SplitPath04(
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
    pObj = path_NewA("/tmp.txt");
    XCTAssertFalse( (OBJ_NIL == pObj) );
    if (pObj) {
        
        eRc = path_SplitPath(pObj, &pDrive, &pPath, &pFileName);
        XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
        
        XCTAssertTrue( (NULL == pDrive) );
        
        XCTAssertTrue( (pPath) );
        XCTAssertTrue( (1 == AStr_getLength((ASTR_DATA *)pPath)) );
        XCTAssertTrue( (0 == strcmp(AStr_getData((ASTR_DATA *)pPath), "/")) );
        if (pPath) {
            obj_Release(pPath);
            pPath = OBJ_NIL;
        }
        
        eRc = path_SplitFile(pFileName, &pFileN, &pFileE);
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



int         test_path_SplitPath05(
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
    pObj = path_NewA("file:tmp.txt");
    XCTAssertFalse( (OBJ_NIL == pObj) );
    if (pObj) {
        
        eRc = path_SplitPath(pObj, &pDrive, &pPath, &pFileName);
        XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
        
        XCTAssertTrue( (pDrive) );
        XCTAssertTrue( (4 == AStr_getLength(pDrive)) );
        XCTAssertTrue( (0 == strcmp(AStr_getData(pDrive), "file")) );
        if (pDrive) {
            obj_Release(pDrive);
            pDrive = OBJ_NIL;
        }
        
        XCTAssertTrue( (NULL == pPath) );
        
        eRc = path_SplitFile(pFileName, &pFileN, &pFileE);
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



int         test_path_SplitPath06(
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
    pObj = path_NewA("file:/tmp.txt");
    XCTAssertFalse( (OBJ_NIL == pObj) );
    if (pObj) {
        
        eRc = path_SplitPath(pObj, &pDrive, &pPath, &pFileName);
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
        
        eRc = path_SplitFile(pFileName, &pFileN, &pFileE);
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



int         test_path_SplitPath07(
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
    pObj = path_NewA(":/tmp.txt");
    XCTAssertFalse( (OBJ_NIL == pObj) );
    if (pObj) {
        
        eRc = path_SplitPath(pObj, &pDrive, &pPath, &pFileName);
        XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
        
        XCTAssertTrue( (NULL == pDrive) );
        
        XCTAssertTrue( (pPath) );
        XCTAssertTrue( (1 == AStr_getLength((ASTR_DATA *)pPath)) );
        XCTAssertTrue( (0 == strcmp(AStr_getData((ASTR_DATA *)pPath), "/")) );
        if (pPath) {
            obj_Release(pPath);
            pPath = OBJ_NIL;
        }
        
        eRc = path_SplitFile(pFileName, &pFileN, &pFileE);
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



int         test_path_SplitPath08(
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
    pObj = path_NewA("tmp");
    XCTAssertFalse( (OBJ_NIL == pObj) );
    if (pObj) {
        
        eRc = path_SplitPath(pObj, &pDrive, &pPath, &pFileName);
        XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
        
        XCTAssertTrue( (NULL == pDrive) );
        
        XCTAssertTrue( (NULL == pPath) );
        
        eRc = path_SplitFile(pFileName, &pFileN, &pFileE);
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



int         test_path_CleanDir01(
    const
    char        *pTestName
)
{
    PATH_DATA	*pObj = OBJ_NIL;
    ERESULT     eRc;
    
    fprintf(stderr, "Performing: %s\n", pTestName);
    pObj = path_NewA("//tmp/");
    XCTAssertFalse( (OBJ_NIL == pObj) );
    if (pObj) {
        
        eRc = path_Clean(pObj);
        XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
        XCTAssertTrue( (4 == AStr_getLength((ASTR_DATA *)pObj)) );
        XCTAssertTrue( (0 == strcmp(AStr_getData((ASTR_DATA *)pObj), "/tmp")) );
        
        obj_Release(pObj);
        pObj = OBJ_NIL;
    }
    
    fprintf(stderr, "...%s completed.\n", pTestName);
    return 1;
}



int         test_path_CleanDir02(
    const
    char        *pTestName
)
{
    PATH_DATA	*pObj = OBJ_NIL;
    ERESULT     eRc;
    
    fprintf(stderr, "Performing: %s\n", pTestName);
    pObj = path_NewA("/");
    XCTAssertFalse( (OBJ_NIL == pObj) );
    if (pObj) {
        
        eRc = path_Clean(pObj);
        XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
        XCTAssertTrue( (1 == AStr_getLength((ASTR_DATA *)pObj)) );
        XCTAssertTrue( (0 == strcmp(AStr_getData((ASTR_DATA *)pObj), "/")) );
        
        obj_Release(pObj);
        pObj = OBJ_NIL;
    }
    
    fprintf(stderr, "...%s completed.\n", pTestName);
    return 1;
}



int         test_path_CleanDir03(
    const
    char        *pTestName
)
{
    PATH_DATA	*pObj = OBJ_NIL;
    ERESULT     eRc;
    
    fprintf(stderr, "Performing: %s\n", pTestName);
    pObj = path_NewA("/./");
    XCTAssertFalse( (OBJ_NIL == pObj) );
    if (pObj) {
        
        eRc = path_Clean(pObj);
        XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
        XCTAssertTrue( (1 == AStr_getLength((ASTR_DATA *)pObj)) );
        XCTAssertTrue( (0 == strcmp(AStr_getData((ASTR_DATA *)pObj), "/")) );
        
        obj_Release(pObj);
        pObj = OBJ_NIL;
    }
    
    fprintf(stderr, "...%s completed.\n", pTestName);
    return 1;
}



int         test_path_CleanDir04(
    const
    char        *pTestName
)
{
    PATH_DATA	*pObj = OBJ_NIL;
    ERESULT     eRc;
    
    fprintf(stderr, "Performing: %s\n", pTestName);
    pObj = path_NewA("x/./y");
    XCTAssertFalse( (OBJ_NIL == pObj) );
    if (pObj) {
        
        eRc = path_Clean(pObj);
        XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
        XCTAssertTrue( (3 == AStr_getLength((ASTR_DATA *)pObj)) );
        XCTAssertTrue( (0 == strcmp(AStr_getData((ASTR_DATA *)pObj), "x/y")) );
        
        obj_Release(pObj);
        pObj = OBJ_NIL;
    }
    
    fprintf(stderr, "...%s completed.\n", pTestName);
    return 1;
}



int         test_path_CleanDir05(
    const
    char        *pTestName
)
{
    PATH_DATA	*pObj = OBJ_NIL;
    ERESULT     eRc;
    
    fprintf(stderr, "Performing: %s\n", pTestName);
    pObj = path_NewA("x//y");
    XCTAssertFalse( (OBJ_NIL == pObj) );
    if (pObj) {
        
        eRc = path_Clean(pObj);
        XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
        XCTAssertTrue( (3 == AStr_getLength((ASTR_DATA *)pObj)) );
        XCTAssertTrue( (0 == strcmp(AStr_getData((ASTR_DATA *)pObj), "x/y")) );
        
        obj_Release(pObj);
        pObj = OBJ_NIL;
    }
    
    fprintf(stderr, "...%s completed.\n", pTestName);
    return 1;
}



int         test_path_CleanDir06(
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
    pObj = path_NewA("~/y.tmp");
    XCTAssertFalse( (OBJ_NIL == pObj) );
    if (pObj) {
        
        eRc = path_Clean(pObj);
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



int         test_path_ToBash(
    const
    char        *pTestName
)
{
    PATH_DATA	*pObj = OBJ_NIL;
    ERESULT     eRc;
    ASTR_DATA   *pStr;
    
    fprintf(stderr, "Performing: %s\n", pTestName);
    pObj = path_NewA("xy z.txt");
    XCTAssertFalse( (OBJ_NIL == pObj) );
    if (pObj) {
        
        eRc = path_ToBash(pObj,&pStr);
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




TINYTEST_START_SUITE(test_path);
  TINYTEST_ADD_TEST(test_path_ToBash,setUp,tearDown);
  TINYTEST_ADD_TEST(test_path_CleanDir06,setUp,tearDown);
  TINYTEST_ADD_TEST(test_path_CleanDir05,setUp,tearDown);
  TINYTEST_ADD_TEST(test_path_CleanDir04,setUp,tearDown);
  TINYTEST_ADD_TEST(test_path_CleanDir03,setUp,tearDown);
  TINYTEST_ADD_TEST(test_path_CleanDir02,setUp,tearDown);
  TINYTEST_ADD_TEST(test_path_CleanDir01,setUp,tearDown);
  TINYTEST_ADD_TEST(test_path_SplitPath08,setUp,tearDown);
  TINYTEST_ADD_TEST(test_path_SplitPath07,setUp,tearDown);
  TINYTEST_ADD_TEST(test_path_SplitPath06,setUp,tearDown);
  TINYTEST_ADD_TEST(test_path_SplitPath05,setUp,tearDown);
  TINYTEST_ADD_TEST(test_path_SplitPath04,setUp,tearDown);
  TINYTEST_ADD_TEST(test_path_SplitPath03,setUp,tearDown);
  TINYTEST_ADD_TEST(test_path_SplitPath02,setUp,tearDown);
  TINYTEST_ADD_TEST(test_path_SplitPath01,setUp,tearDown);
  TINYTEST_ADD_TEST(test_path_NewFromEnv,setUp,tearDown);
  TINYTEST_ADD_TEST(test_path_DateLastUpdated,setUp,tearDown);
  TINYTEST_ADD_TEST(test_path_CharFindNext,setUp,tearDown);
  TINYTEST_ADD_TEST(test_path_OpenClose,setUp,tearDown);
TINYTEST_END_SUITE();

TINYTEST_MAIN_SINGLE_SUITE(test_path);





