// vi:nu:et:sts=4 ts=4 sw=4
/*
 *	Generated 01/31/2020 13:16:48
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
#include    <Appl_internal.h>
#include    <objTest_internal.h>
#ifdef  APPL_JSON_SUPPORT
#   include    <SrcErrors.h>
#   include    <szTbl.h>
#endif



typedef     struct args_s {
    uint16_t        fArchive;
    NUMBER_DATA     *pArgLen;
    PATH_DATA       *pInFilePath;      // ("-f" | "--file=")<string> or ("-f" | "--file") <string>
    PATH_DATA       *pOutFilePath;     // ("-o" | "--out=")<string> or ("-o" | "--out") <string>
} ARGS;




ARGS                args = {
    0,                  // fArchive
    0,                  // argLen
    OBJ_NIL,            // pInFilePath
    OBJ_NIL             // pOutFilePath
};


CMDUTL_OPTION       pPgmArgs1[] = {
    {
        "archive",
        'a',
        CMDUTL_ARG_OPTION_NONE,
        CMDUTL_TYPE_BOOL,
        offsetof(ARGS, fArchive),
        NULL,
        "Set Archive Mode"
    },
    {
        "arglength",
        'l',
        CMDUTL_ARG_OPTION_REQUIRED,
        CMDUTL_TYPE_NUMBER,
        offsetof(ARGS, pArgLen),
        NULL,
        "Set Argument Length"
    },
    {
        "input",
        'i',
        CMDUTL_ARG_OPTION_REQUIRED,
        CMDUTL_TYPE_PATH,
        offsetof(ARGS, pInFilePath),
        NULL,
        "Set Input File Path"
    },
    {
        "output",
        'o',
        CMDUTL_ARG_OPTION_REQUIRED,
        CMDUTL_TYPE_PATH,
        offsetof(ARGS, pOutFilePath),
        NULL,
        "Set Output File Path"
    },
    {NULL,0,0,0,0,NULL,NULL}                    // End of Table
};



static
const
char        *ppArgs2[] = {
    "./program_name",
    "--debug",
    "1",
    "2",
    "3",
    NULL
};
static
int         cArgs2 = 5;



/*!
 Print the program description with a trailing '\n' and leading "  ".
 @param     pObj        Object Pointer
 @param     pOutput     File to write to
 @param     pPgmPath    Program's Path
 @return    ERESULT_SUCCESS if successful, otherwise, an ERESULT_*
            error code.
 */
ERESULT         usageDesc(
    OBJ_ID          pObj,
    FILE            *pOutput,
    PATH_DATA       *pPgmPath
)
{
    fprintf(pOutput, "  This program does blah blah blah.\n");
    return ERESULT_SUCCESS;
}



/*!
 Print the program usage line with a trailing '\n' and leading "  ".
 @param     pObj        Object Pointer
 @param     pOutput     File to write to
 @param     pPgmPath    Program's Path
 @param     pNameA      Program's name
 @return    ERESULT_SUCCESS if successful, otherwise, an ERESULT_*
            error code.
 */
ERESULT         usageProgLine(
    OBJ_ID          pObj,
    FILE            *pOutput,
    PATH_DATA       *pPgmPath,
    const
    char            *pNameA
)
{
    fprintf(pOutput, "  %s [options] other_stuff\n", pNameA);

    return ERESULT_SUCCESS;
}



int         processArg(
    OBJ_ID      pObj,
    const
    char        *pArg
)
{
    fprintf(stderr, "processArg arg:\"%s\"\n", pArg);
    return 0;
}



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

    Appl_SharedReset();
#ifdef  APPL_JSON_SUPPORT
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






int             test_Appl_OpenClose (
    const
    char            *pTestName
)
{
    ERESULT         eRc = ERESULT_SUCCESS;
    APPL_DATA	    *pObj = OBJ_NIL;
    bool            fRc;
   
    fprintf(stderr, "Performing: %s\n", pTestName);

    pObj = Appl_Alloc( );
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    pObj = Appl_Init( pObj );
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    if (pObj) {

        //obj_TraceSet(pObj, true);       
        fRc = obj_IsKindOf(pObj, OBJ_IDENT_APPL);
        TINYTEST_TRUE( (fRc) );
        
        // Test something.
        TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );

        obj_Release(pObj);
        pObj = OBJ_NIL;
    }

    fprintf(stderr, "...%s completed.\n\n\n", pTestName);
    return 1;
}



int             test_Appl_Copy01 (
    const
    char            *pTestName
)
{
    ERESULT         eRc = ERESULT_SUCCESS;
    APPL_DATA	    *pObj1 = OBJ_NIL;
    APPL_DATA	    *pObj2 = OBJ_NIL;
    bool            fRc;
#if defined(APPL_JSON_SUPPORT) && defined(XYZZY)
    ASTR_DATA	    *pStr = OBJ_NIL;
#endif
   
    fprintf(stderr, "Performing: %s\n", pTestName);

    pObj1 = Appl_New( );
    TINYTEST_FALSE( (OBJ_NIL == pObj1) );
    if (pObj1) {

        //obj_TraceSet(pObj1, true);       
        fRc = obj_IsKindOf(pObj1, OBJ_IDENT_APPL);
        TINYTEST_TRUE( (fRc) );
        
        // Test assign.
        pObj2 = Appl_New();
        TINYTEST_FALSE( (OBJ_NIL == pObj2) );
        eRc = Appl_Assign(pObj1, pObj2);
        TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );

        fRc = obj_IsKindOf(pObj2, OBJ_IDENT_APPL);
        TINYTEST_TRUE( (fRc) );
        //eRc = Appl_Compare(pObj1, pObj2);
        //TINYTEST_TRUE( (ERESULT_SUCCESS_EQUAL == eRc) );
        //TODO: Add More tests here!

        obj_Release(pObj2);
        pObj2 = OBJ_NIL;

        // Test copy.
        pObj2 = Appl_Copy(pObj1);
        TINYTEST_FALSE( (OBJ_NIL == pObj2) );

        fRc = obj_IsKindOf(pObj2, OBJ_IDENT_APPL);
        TINYTEST_TRUE( (fRc) );
        //TODO: Add More tests here!

        obj_Release(pObj2);
        pObj2 = OBJ_NIL;

        // Test json support.
#if defined(APPL_JSON_SUPPORT) && defined(XYZZY)
        pStr = Appl_ToJson(pObj1);
        TINYTEST_FALSE( (OBJ_NIL == pStr) );
        fprintf(stderr, "JSON: %s\n", AStr_getData(pStr));
        pObj2 = Appl_NewFromJsonString(pStr);
        TINYTEST_FALSE( (OBJ_NIL == pObj2) );
        fRc = obj_IsKindOf(pObj2, OBJ_IDENT_APPL);
        TINYTEST_TRUE( (fRc) );
        obj_Release(pStr);
        pStr = OBJ_NIL;
        //eRc = Appl_Compare(pObj1, pObj2);
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



int             test_Appl_Test01 (
    const
    char            *pTestName
)
{
    //ERESULT         eRc = ERESULT_SUCCESS;
    APPL_DATA	    *pObj = OBJ_NIL;
    bool            fRc;
   
    fprintf(stderr, "Performing: %s\n", pTestName);

    pObj = Appl_New( );
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    if (pObj) {

        //obj_TraceSet(pObj, true);       
        fRc = obj_IsKindOf(pObj, OBJ_IDENT_APPL);
        TINYTEST_TRUE( (fRc) );
        
        obj_Release(pObj);
        pObj = OBJ_NIL;
    }

    fprintf(stderr, "...%s completed.\n\n\n", pTestName);
    return 1;
}



int             test_Appl_Args01(
    const
    char            *pTestName
)
{
    OBJTEST_DATA    *pObj = OBJ_NIL;
    ERESULT         eRc;
    bool            fRc;
    NUMBER_DATA     *pNum = OBJ_NIL;
    PATH_DATA       *pPath = OBJ_NIL;
    char            *pChrStr = NULL;
    char            *ppArgs1[] = {
        "./program_name",
        "--debug",
        "-v",
        "1st_Arg",
        "2nd_Arg",
        NULL
    };
    int             cArgs1 = 5;



    fprintf(stderr, "Performing: %s\n", pTestName);
    pObj = objTest_New( );
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    if (pObj) {

        eRc = Appl_SetupFromArgV((APPL_DATA *)pObj, cArgs1, ppArgs1, NULL, pPgmArgs1);
        TINYTEST_TRUE( (!ERESULT_FAILED(eRc)) );

        fRc = Appl_IsMore((APPL_DATA *)pObj);
        TINYTEST_TRUE( (fRc) );

        eRc = Appl_ProcessOptions((APPL_DATA *)pObj);
        TINYTEST_TRUE( (!ERESULT_FAILED(eRc)) );
        TINYTEST_TRUE( (true == Appl_getDebug((APPL_DATA *)pObj)) );
        TINYTEST_TRUE( (1 == Appl_getVerbose((APPL_DATA *)pObj)) );
        TINYTEST_TRUE( (0 == objTest_getArchive(pObj)) );
        TINYTEST_TRUE( (OBJ_NIL == objTest_getArgLength(pObj)) );
        TINYTEST_TRUE( (OBJ_NIL == objTest_getInPath(pObj)) );
        TINYTEST_TRUE( (OBJ_NIL == objTest_getOutPath(pObj)) );

        fRc = Appl_IsMore((APPL_DATA *)pObj);
        TINYTEST_TRUE( (fRc) );

        pChrStr = Appl_NextArg((APPL_DATA *)pObj);
        TINYTEST_FALSE( (NULL == pChrStr) );
        TINYTEST_TRUE( (0 == strcmp("1st_Arg", pChrStr)) );

        fRc = Appl_IsMore((APPL_DATA *)pObj);
        TINYTEST_TRUE( (fRc) );

        pChrStr = Appl_NextArg((APPL_DATA *)pObj);
        TINYTEST_FALSE( (NULL == pChrStr) );
        TINYTEST_TRUE( (0 == strcmp("2nd_Arg", pChrStr)) );

        fRc = Appl_IsMore((APPL_DATA *)pObj);
        TINYTEST_TRUE( (!fRc) );

        obj_Release(pObj);
        pObj = OBJ_NIL;
    }

    fprintf(stderr, "...%s completed.\n\n\n", pTestName);
    return 1;
}



int         test_Appl_Parse01(
    const
    char        *pTestName
)
{
    ERESULT         eRc;
    ASTRCARRAY_DATA *pArgV = OBJ_NIL;
    char            *ppArgs1[] = {
        "./program_name",
        "--debug",
        "-v",
        "1st_Arg",
        "2nd_Arg",
        NULL
    };
    int             cArgs1 = 5;
    const
    char            *pCmd = "./program_name --debug -v 1st_Arg 2nd_Arg";
    uint32_t        i;


    fprintf(stderr, "Performing: %s\n", pTestName);

    eRc = Appl_ParseProgramLine(pCmd, &pArgV);
    TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );
    TINYTEST_FALSE( (OBJ_NIL == pArgV) );

    fprintf(stderr, "\tNum Args = %d\n", AStrCArray_getSize(pArgV));
    {
        ASTR_DATA           *pStr = AStrCArray_ToDebugString(pArgV, 4);
        fprintf(stderr, "%s\n", AStr_getData(pStr));
        obj_Release(pStr);
        pStr = OBJ_NIL;
    }

    i = AStrCArray_getSize(pArgV);
    TINYTEST_TRUE( (cArgs1 == i) );
    for (i=0; i<cArgs1; i++) {
        eRc = AStrC_CompareA(AStrCArray_Get(pArgV, i+1), ppArgs1[i]);
        TINYTEST_TRUE( (0 == eRc) );
    }

    obj_Release(pArgV);
    pArgV = OBJ_NIL;

    fprintf(stderr, "...%s completed.\n\n\n", pTestName);
    return 1;
}



int         test_Appl_Parse02(
    const
    char        *pTestName
)
{
    ERESULT         eRc;
    ASTRCARRAY_DATA *pArgV = OBJ_NIL;
    char            *ppArgs1[] = {
        "./program_name",
        "--debug='true'",
        "-v",
        "1st_Arg",
        "\"2nd_Arg\"",
        NULL
    };
    int             cArgs1 = 5;
    const
    char            *pCmd = "./program_name --debug='true' -v 1st_Arg \"2nd_Arg\"";
    uint32_t        i;


    fprintf(stderr, "Performing: %s\n", pTestName);

    eRc = Appl_ParseProgramLine(pCmd, &pArgV);
    TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );
    TINYTEST_FALSE( (OBJ_NIL == pArgV) );

    fprintf(stderr, "\tNum Args = %d\n", AStrCArray_getSize(pArgV));
    {
        ASTR_DATA           *pStr = AStrCArray_ToDebugString(pArgV, 4);
        fprintf(stderr, "%s\n", AStr_getData(pStr));
        obj_Release(pStr);
        pStr = OBJ_NIL;
    }

    i = AStrCArray_getSize(pArgV);
    TINYTEST_TRUE( (cArgs1 == i) );
    for (i=0; i<cArgs1; i++) {
        eRc = AStrC_CompareA(AStrCArray_Get(pArgV, i+1), ppArgs1[i]);
        TINYTEST_TRUE( (0 == eRc) );
    }

    obj_Release(pArgV);
    pArgV = OBJ_NIL;

    fprintf(stderr, "...%s completed.\n\n\n", pTestName);
    return 1;
}



int         test_Appl_Usage01(
    const
    char        *pTestName
)
{
    APPL_DATA   *pObj = OBJ_NIL;
    //ERESULT     eRc;
    bool        fRc;
    //APPL_CLO    *pClo;
    //ASTR_DATA   *pStr = OBJ_NIL;

    fprintf(stderr, "Performing: %s\n", pTestName);
    pObj = Appl_Alloc( );
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    pObj = Appl_Init(pObj);
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    if (pObj) {

        fRc = Appl_setArgDefs(pObj, pPgmArgs1);
        TINYTEST_TRUE( (fRc) );
        Appl_UsageNoMsg(pObj);

        obj_Release(pObj);
        pObj = OBJ_NIL;
    }

    fprintf(stderr, "...%s completed.\n\n\n", pTestName);
    return 1;
}




TINYTEST_START_SUITE(test_Appl);
    TINYTEST_ADD_TEST(test_Appl_Usage01,setUp,tearDown);
    TINYTEST_ADD_TEST(test_Appl_Parse02,setUp,tearDown);
    TINYTEST_ADD_TEST(test_Appl_Parse01,setUp,tearDown);
    TINYTEST_ADD_TEST(test_Appl_Args01,setUp,tearDown);
    TINYTEST_ADD_TEST(test_Appl_Test01,setUp,tearDown);
    //TINYTEST_ADD_TEST(test_Appl_Copy01,setUp,tearDown);
    TINYTEST_ADD_TEST(test_Appl_OpenClose,setUp,tearDown);
TINYTEST_END_SUITE();

TINYTEST_MAIN_SINGLE_SUITE(test_Appl);





