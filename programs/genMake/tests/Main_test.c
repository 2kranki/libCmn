// vi:nu:et:sts=4 ts=4 sw=4
/*
 *	Generated 07/17/2017 14:59:49
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
#include    <cmn_defs.h>
#include    <SrcErrors.h>
#include    <trace.h>
#include    <Main_internal.h>



#include    <data_test.c>



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

    
    szTbl_SharedReset( );
    SrcErrors_SharedReset( );
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






int         test_Main_OpenClose(
    const
    char        *pTestName
)
{
    MAIN_DATA	*pObj = OBJ_NIL;
   
    fprintf(stderr, "Performing: %s\n", pTestName);
    
    pObj = Main_New( );
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    if (pObj) {

        // Test something.

        obj_Release(pObj);
        pObj = OBJ_NIL;
    }

    fprintf(stderr, "...%s completed.\n\n", pTestName);
    return 1;
}



int         test_Main_Generation01(
    const
    char        *pTestName
)
{
    ERESULT         eRc;
    MAIN_DATA       *pObj = OBJ_NIL;
    ASTR_DATA       *pStr = OBJ_NIL;
    //ASTR_DATA       *pWrk = OBJ_NIL;
    int             iRc;
    int             offset = 0;
    bool            fDump = true;
    NODELIB_DATA    *pLib = OBJ_NIL;
    PATH_DATA       *pPath = OBJ_NIL;
    ASTR_DATA       *pInput = OBJ_NIL;
    ASTR_DATA       *pCheck = OBJ_NIL;
    //NODELIB_DATA    *pPgm = OBJ_NIL;
    uint32_t        i;
    const
    char            *pChr;
    
    fprintf(stderr, "Performing: %s\n", pTestName);

    pPath = Path_NewA(TEST_FILES_DIR "/libJson01.txt");
    TINYTEST_FALSE( (OBJ_NIL == pPath) );
    pInput = AStr_NewFromUtf8File(pPath);
    TINYTEST_FALSE( (OBJ_NIL == pInput) );
    obj_Release(pPath);
    pPath = OBJ_NIL;
    pPath = Path_NewA(TEST_FILES_DIR "/libJson01.macos64.output.txt");
    TINYTEST_FALSE( (OBJ_NIL == pPath) );
    pCheck = AStr_NewFromUtf8File(pPath);
    TINYTEST_FALSE( (OBJ_NIL == pCheck) );
    obj_Release(pPath);
    pPath = OBJ_NIL;

    pObj = Main_New();
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    if (pObj) {
        
        pObj->pOutput = TextOut_NewAStr();
        TINYTEST_FALSE( (OBJ_NIL == pObj->pOutput) );

        //appl_setDebug((APPL_DATA *)pObj, true);
        if (fDump) {
            fprintf(stderr, "INPUT_BEGIN:\n%sINPUT_END:\n\n\n", AStr_getData(pInput));
        }
        eRc = Main_ParseInputStrA(pObj, AStr_getData(pInput));
        TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );
        TINYTEST_FALSE( (OBJ_NIL == pObj->pParser) );

        pLib = SrcParse_getLib(pObj->pParser);
        TINYTEST_FALSE( (OBJ_NIL == pLib) );

        pObj->osType = OSTYPE_MACOS64;
        eRc = Main_SetupOsArch(pObj);
        TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );
        eRc = Main_GenMakefile(pObj);
        TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );
        
        if (fDump) {
            pStr = Main_getStr(pObj);
            TINYTEST_FALSE( (OBJ_NIL == pStr) );
            fprintf(stderr, "GEN_BEGIN:\n%sGEN_END:\n\n\n", AStr_getData(pStr));
        }
        
        // Skip first 3 lines of output.
        pChr = AStr_getData(Main_getStr(pObj));
        for (i=0; i<3; i++) {
            while (*pChr && (*pChr != '\n')) {
                pChr++;
            }
            pChr++;
        }
        
        iRc = str_CompareSpcl(pChr, AStr_getData(pCheck), &offset);
        fprintf(stderr, "\tiRc=%d  offset=%04X\n", iRc, offset);
        TINYTEST_TRUE( (0 == iRc) );
        
        obj_Release(pObj);
        pObj = OBJ_NIL;
    }
    
    obj_Release(pCheck);
    pCheck = OBJ_NIL;
    obj_Release(pInput);
    pInput = OBJ_NIL;

    fprintf(stderr, "...%s completed.\n\n\n", pTestName);
    return 1;
}



int         test_Main_Generation02(
    const
    char        *pTestName
)
{
    ERESULT         eRc;
    MAIN_DATA       *pObj = OBJ_NIL;
    ASTR_DATA       *pStr = OBJ_NIL;
    //ASTR_DATA       *pWrk = OBJ_NIL;
    int             iRc;
    int             offset = 0;
    bool            fDump = true;
    NODELIB_DATA    *pLib = OBJ_NIL;
    //NODELIB_DATA    *pPgm = OBJ_NIL;
    uint32_t        i;
    const
    char            *pChr;
    PATH_DATA       *pPath = OBJ_NIL;
    ASTR_DATA       *pInput = OBJ_NIL;
    ASTR_DATA       *pCheck = OBJ_NIL;

    fprintf(stderr, "Performing: %s\n", pTestName);
    
    pPath = Path_NewA(TEST_FILES_DIR "/libJson02.txt");
    TINYTEST_FALSE( (OBJ_NIL == pPath) );
    pInput = AStr_NewFromUtf8File(pPath);
    TINYTEST_FALSE( (OBJ_NIL == pInput) );
    obj_Release(pPath);
    pPath = OBJ_NIL;
    pPath = Path_NewA(TEST_FILES_DIR "/libJson02.macos64.output.txt");
    TINYTEST_FALSE( (OBJ_NIL == pPath) );
    pCheck = AStr_NewFromUtf8File(pPath);
    TINYTEST_FALSE( (OBJ_NIL == pCheck) );
    obj_Release(pPath);
    pPath = OBJ_NIL;

    pObj = Main_New();
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    if (pObj) {
        
        pObj->pOutput = TextOut_NewAStr();
        TINYTEST_FALSE( (OBJ_NIL == pObj->pOutput) );

        //appl_setDebug((APPL_DATA *)pObj, true);
        eRc = Main_ParseInputStrA(pObj, AStr_getData(pInput));
        TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );
        TINYTEST_FALSE( (OBJ_NIL == pObj->pParser) );

        pLib = SrcParse_getLib(pObj->pParser);
        TINYTEST_FALSE( (OBJ_NIL == pLib) );

        pObj->osType = OSTYPE_MACOS64;
        eRc = Main_SetupOsArch(pObj);
        TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );
        eRc = Main_GenMakefile(pObj);
        TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );
        
        if (fDump) {
            pStr = Main_getStr(pObj);
            TINYTEST_FALSE( (OBJ_NIL == pStr) );
            fprintf(stderr, "GEN_BEGIN:\n%sGEN_END:\n\n\n", AStr_getData(pStr));
        }
        
        // Skip first 3 lines of output.
        pChr = AStr_getData(Main_getStr(pObj));
        for (i=0; i<3; i++) {
            while (*pChr && (*pChr != '\n')) {
                pChr++;
            }
            pChr++;
        }
        
        iRc = str_CompareSpcl(pChr, AStr_getData(pCheck), &offset);
        fprintf(stderr, "\tiRc=%d  offset=%04X\n", iRc, offset);
        TINYTEST_TRUE( (0 == iRc) );
        
        obj_Release(pObj);
        pObj = OBJ_NIL;
    }
    
    obj_Release(pCheck);
    pCheck = OBJ_NIL;
    obj_Release(pInput);
    pInput = OBJ_NIL;

    fprintf(stderr, "...%s completed.\n\n\n", pTestName);
    return 1;
}



int         test_Main_Generation03(
    const
    char        *pTestName
)
{
    ERESULT         eRc;
    MAIN_DATA       *pObj = OBJ_NIL;
    ASTR_DATA       *pStr = OBJ_NIL;
    //ASTR_DATA       *pWrk = OBJ_NIL;
    int             iRc;
    int             offset = 0;
    bool            fDumpNodes = false;
    bool            fDump = true;
    //NODELIB_DATA    *pLib = OBJ_NIL;
    NODEPGM_DATA    *pPgm = OBJ_NIL;
    uint32_t        i;
    const
    char            *pChr;
    PATH_DATA       *pPath = OBJ_NIL;
    ASTR_DATA       *pInput = OBJ_NIL;
    ASTR_DATA       *pCheck = OBJ_NIL;

    fprintf(stderr, "Performing: %s\n", pTestName);
    
    pPath = Path_NewA(TEST_FILES_DIR "/pgmJson01.txt");
    TINYTEST_FALSE( (OBJ_NIL == pPath) );
    pInput = AStr_NewFromUtf8File(pPath);
    TINYTEST_FALSE( (OBJ_NIL == pInput) );
    obj_Release(pPath);
    pPath = OBJ_NIL;
    pPath = Path_NewA(TEST_FILES_DIR "/pgmJson01.macos64.output.txt");
    TINYTEST_FALSE( (OBJ_NIL == pPath) );
    pCheck = AStr_NewFromUtf8File(pPath);
    TINYTEST_FALSE( (OBJ_NIL == pCheck) );
    obj_Release(pPath);
    pPath = OBJ_NIL;

    pObj = Main_New();
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    if (pObj) {
        
        pObj->pOutput = TextOut_NewAStr();
        TINYTEST_FALSE( (OBJ_NIL == pObj->pOutput) );

        //appl_setDebug((APPL_DATA *)pObj, true);
        eRc = Main_ParseInputStrA(pObj, AStr_getData(pInput));
        TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );
        TINYTEST_FALSE( (OBJ_NIL == pObj->pParser) );

        pPgm = SrcParse_getPgm(pObj->pParser);
        TINYTEST_FALSE( (OBJ_NIL == pPgm) );

        if (fDump) {
            ASTR_DATA       *pWrk = OBJ_NIL;
            pWrk = SrcParse_ToString(pObj->pParser);
            if (pWrk) {
                fprintf(stderr, "\n%s\n\n\n", AStr_getData(pWrk));
                obj_Release(pWrk);
                pWrk = OBJ_NIL;
            }
        }

        pObj->osType = OSTYPE_MACOS64;
        eRc = Main_SetupOsArch(pObj);
        TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );
        eRc = Main_GenMakefile(pObj);
        TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );
        
        if (fDump) {
            ASTR_DATA       *pWrk = OBJ_NIL;
            pWrk = ExpandNodes_ToString(pObj->pExpand);
            if (pWrk) {
                fprintf(stderr, "\n%s\n\n\n", AStr_getData(pWrk));
                obj_Release(pWrk);
                pWrk = OBJ_NIL;
            }
        }
        
        if (fDump) {
            pStr = Main_getStr(pObj);
            TINYTEST_FALSE( (OBJ_NIL == pStr) );
            fprintf(stderr, "GEN_BEGIN:\n%sGEN_END:\n\n\n", AStr_getData(pStr));
        }
        
        // Skip first 3 lines of output.
        pChr = AStr_getData(Main_getStr(pObj));
        for (i=0; i<3; i++) {
            while (*pChr && (*pChr != '\n')) {
                pChr++;
            }
            pChr++;
        }
        
        iRc = str_CompareSpcl(pChr, AStr_getData(pCheck), &offset);
        fprintf(stderr, "\tiRc=%d  offset=%04X\n", iRc, offset);
        TINYTEST_TRUE( (0 == iRc) );
        
        obj_Release(pObj);
        pObj = OBJ_NIL;
    }
    
    obj_Release(pCheck);
    pCheck = OBJ_NIL;
    obj_Release(pInput);
    pInput = OBJ_NIL;

    fprintf(stderr, "...%s completed.\n\n\n", pTestName);
    return 1;
}



int         test_Main_CheckInputFilePath01(
    const
    char        *pTestName
)
{
    ERESULT         eRc;
    MAIN_DATA       *pObj = OBJ_NIL;
    ASTR_DATA       *pStr = OBJ_NIL;
    PATH_DATA       *pPath = OBJ_NIL;
    PATH_DATA       *pPathCheck = OBJ_NIL;
    static
    const
    char            *pGoodPathA = TEST_FILES_DIR "/libJson01.txt";
    int             iRc;
    int             offset = 0;
    
    
    fprintf(stderr, "Performing: %s\n", pTestName);
    
    pObj = Main_New();
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    if (pObj) {
        
        pStr = AStr_NewA(pGoodPathA);
        TINYTEST_FALSE( (OBJ_NIL == pStr) );

        pObj->osType = OSTYPE_MACOS64;
        eRc = Main_SetupOsArch(pObj);
        TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );

        pPath = Main_CheckInputPath(pObj, pStr);
        TINYTEST_FALSE( (OBJ_NIL == pPath) );

#ifdef XYZZY
        pPathCheck = Path_NewA(pOutputA);
        TINYTEST_FALSE( (OBJ_NIL == pPathCheck) );
        eRc = Path_Clean(pPathCheck);
        TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );

        iRc = str_CompareSpcl(Path_getData(pPath), Path_getData(pPathCheck), &offset);
        fprintf(stderr, "\tiRc=%d  offset=%04X\n", iRc, offset);
        TINYTEST_TRUE( (0 == iRc) );
#endif
        
        obj_Release(pPathCheck);
        pPathCheck = OBJ_NIL;
        obj_Release(pPath);
        pPath = OBJ_NIL;
        obj_Release(pStr);
        pStr = OBJ_NIL;
        obj_Release(pObj);
        pObj = OBJ_NIL;
    }
    
    fprintf(stderr, "...%s completed.\n\n\n", pTestName);
    return 1;
}



int         test_Main_CreateOutputFilePath01(
    const
    char        *pTestName
)
{
    ERESULT         eRc;
    MAIN_DATA       *pObj = OBJ_NIL;
    ASTR_DATA       *pStr = OBJ_NIL;
    PATH_DATA       *pPath = OBJ_NIL;
    PATH_DATA       *pPathCheck = OBJ_NIL;
    static
    const
    char            *pGoodPathA = "~/git/libCmn/objects.json.txt";
    const
    char            *pOutputA = "~/git/libCmn/Makefile.macos64.txt";
    int             iRc;
    int             offset = 0;
    
    
    fprintf(stderr, "Performing: %s\n", pTestName);
    
    pObj = Main_New();
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    if (pObj) {
        
        pStr = AStr_NewA(pGoodPathA);
        TINYTEST_FALSE( (OBJ_NIL == pStr) );

        pObj->osType = OSTYPE_MACOS64;
        eRc = Main_SetupOsArch(pObj);
        TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );

        pPath = Main_CreateOutputPath(pObj, pStr, pObj->pOsName);
        TINYTEST_FALSE( (OBJ_NIL == pPath) );

        pPathCheck = Path_NewA(pOutputA);
        TINYTEST_FALSE( (OBJ_NIL == pPathCheck) );
        eRc = Path_Clean(pPathCheck);
        TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );

        iRc = str_CompareSpcl(Path_getData(pPath), Path_getData(pPathCheck), &offset);
        fprintf(stderr, "\tiRc=%d  offset=%04X\n", iRc, offset);
        TINYTEST_TRUE( (0 == iRc) );
        
        obj_Release(pPathCheck);
        pPathCheck = OBJ_NIL;
        obj_Release(pPath);
        pPath = OBJ_NIL;
        obj_Release(pStr);
        pStr = OBJ_NIL;
        obj_Release(pObj);
        pObj = OBJ_NIL;
    }
    
    fprintf(stderr, "...%s completed.\n\n\n", pTestName);
    return 1;
}



int         test_Main_Generation04(
    const
    char        *pTestName
)
{
    ERESULT         eRc;
    MAIN_DATA       *pObj = OBJ_NIL;
    ASTR_DATA       *pStr = OBJ_NIL;
    ASTR_DATA       *pCheck = OBJ_NIL;
    PATH_DATA       *pPath = OBJ_NIL;
    PATH_DATA       *pInputPath = OBJ_NIL;
    PATH_DATA       *pOutputPath = OBJ_NIL;
    //ASTR_DATA       *pWrk = OBJ_NIL;
    int             iRc;
    int             offset = 0;
    bool            fDump = false;
    uint32_t        i;
    const
    char            *pChr;
    static
    const
    char            *pInputPathA = TEST_FILES_DIR "/libJson01.txt";
    
    fprintf(stderr, "Performing: %s\n", pTestName);
    
    pPath = Path_NewA(TEST_FILES_DIR "/libJson01.macos64.output.txt");
    TINYTEST_FALSE( (OBJ_NIL == pPath) );
    pCheck = AStr_NewFromUtf8File(pPath);
    TINYTEST_FALSE( (OBJ_NIL == pCheck) );
    obj_Release(pPath);
    pPath = OBJ_NIL;

    pObj = Main_New();
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    if (pObj) {
        
        pInputPath = Path_NewA(pInputPathA);
        TINYTEST_FALSE( (OBJ_NIL == pInputPath) );

        eRc = Path_Clean(pInputPath);
        pObj->osType = OSTYPE_MACOS64;
        eRc = Main_SetupOsArch(pObj);
        TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );
        eRc = Main_ProcessArg(pObj, Path_getAStr(pInputPath));
        TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );
        
        pOutputPath =   Main_CreateOutputPath(
                                            pObj,
                                            Path_getAStr(pInputPath),
                                            pObj->pOsName
                        );
        TINYTEST_FALSE( (OBJ_NIL == pOutputPath) );
        
        pStr = AStr_NewFromUtf8File(pOutputPath);
        TINYTEST_FALSE( (OBJ_NIL == pStr) );
        if (fDump) {
            fprintf(stderr, "GEN_BEGIN:\n%sGEN_END:\n\n\n", AStr_getData(pStr));
        }
        
        // Skip first 3 lines of output.
        pChr = AStr_getData(pStr);
        for (i=0; i<3; i++) {
            while (*pChr && (*pChr != '\n')) {
                pChr++;
            }
            pChr++;
        }
        
        iRc = str_CompareSpcl(pChr, AStr_getData(pCheck), &offset);
        fprintf(stderr, "\tiRc=%d  offset=%04X\n", iRc, offset);
        TINYTEST_TRUE( (0 == iRc) );
        
        eRc = Path_Delete(pOutputPath);
        TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );

        obj_Release(pOutputPath);
        pOutputPath = OBJ_NIL;
        obj_Release(pStr);
        pStr = OBJ_NIL;
        obj_Release(pInputPath);
        pInputPath = OBJ_NIL;
        obj_Release(pObj);
        pObj = OBJ_NIL;
    }
    
    obj_Release(pCheck);
    pCheck = OBJ_NIL;

    fprintf(stderr, "...%s completed.\n\n\n", pTestName);
    return 1;
}



int         test_Main_Generation05(
    const
    char        *pTestName
)
{
    ERESULT         eRc;
    MAIN_DATA       *pObj = OBJ_NIL;
    ASTR_DATA       *pStr = OBJ_NIL;
    PATH_DATA       *pInputPath = OBJ_NIL;
    PATH_DATA       *pOutputPath = OBJ_NIL;
    int             iRc;
    int             offset = 0;
    bool            fDump = false;
    uint32_t        i;
    const
    char            *pChr;
    static
    const
    char            *pInputPathA = TEST_FILES_DIR "/libJson02.txt";
    ASTR_DATA       *pCheck = OBJ_NIL;
    PATH_DATA       *pPath = OBJ_NIL;

    fprintf(stderr, "Performing: %s\n", pTestName);
    
    pPath = Path_NewA(TEST_FILES_DIR "/libJson02.macos64.output.txt");
    TINYTEST_FALSE( (OBJ_NIL == pPath) );
    pCheck = AStr_NewFromUtf8File(pPath);
    TINYTEST_FALSE( (OBJ_NIL == pCheck) );
    obj_Release(pPath);
    pPath = OBJ_NIL;
    pObj = Main_New();
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    if (pObj) {
        
        pInputPath = Path_NewA(pInputPathA);
        TINYTEST_FALSE( (OBJ_NIL == pInputPath) );

        eRc = Path_Clean(pInputPath);
        pObj->osType = OSTYPE_MACOS64;
        eRc = Main_SetupOsArch(pObj);
        TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );
        eRc = Main_ProcessArg(pObj, Path_getAStr(pInputPath));
        TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );
        
        pOutputPath =   Main_CreateOutputPath(
                                            pObj,
                                            Path_getAStr(pInputPath),
                                            pObj->pOsName
                        );
        TINYTEST_FALSE( (OBJ_NIL == pOutputPath) );
        
        pStr = AStr_NewFromUtf8File(pOutputPath);
        TINYTEST_FALSE( (OBJ_NIL == pStr) );
        if (fDump) {
            fprintf(stderr, "GEN_BEGIN:\n%sGEN_END:\n\n\n", AStr_getData(pStr));
        }
        
        // Skip first 3 lines of output.
        pChr = AStr_getData(pStr);
        for (i=0; i<3; i++) {
            while (*pChr && (*pChr != '\n')) {
                pChr++;
            }
            pChr++;
        }
        
        iRc = str_CompareSpcl(pChr, AStr_getData(pCheck), &offset);
        fprintf(stderr, "\tiRc=%d  offset=%04X\n", iRc, offset);
        TINYTEST_TRUE( (0 == iRc) );
        
        eRc = Path_Delete(pOutputPath);
        TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );

        obj_Release(pOutputPath);
        pOutputPath = OBJ_NIL;
        obj_Release(pStr);
        pStr = OBJ_NIL;
        obj_Release(pInputPath);
        pInputPath = OBJ_NIL;
        obj_Release(pObj);
        pObj = OBJ_NIL;
    }
    
    obj_Release(pCheck);
    pCheck = OBJ_NIL;

    fprintf(stderr, "...%s completed.\n\n\n", pTestName);
    return 1;
}




TINYTEST_START_SUITE(test_Main);
    TINYTEST_ADD_TEST(test_Main_Generation05,setUp,tearDown);
    TINYTEST_ADD_TEST(test_Main_Generation04,setUp,tearDown);
    TINYTEST_ADD_TEST(test_Main_Generation03,setUp,tearDown);
    TINYTEST_ADD_TEST(test_Main_CreateOutputFilePath01,setUp,tearDown);
    TINYTEST_ADD_TEST(test_Main_CheckInputFilePath01,setUp,tearDown);
    TINYTEST_ADD_TEST(test_Main_Generation02,setUp,tearDown);
    TINYTEST_ADD_TEST(test_Main_Generation01,setUp,tearDown);
    TINYTEST_ADD_TEST(test_Main_OpenClose,setUp,tearDown);
TINYTEST_END_SUITE();

TINYTEST_MAIN_SINGLE_SUITE(test_Main);





