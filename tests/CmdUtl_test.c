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
#include    <cmdutl_internal.h>



//fixme: need to adjust for:
static
const
char        *pTestInput01 =
    " "
    "one=123 "
    "--two=\"xyz\" "
    "three=[\"a\", \"b\", \"c\"] "
    "4"
"\n";


#ifdef XYZZY
static
const
char        *pTestInput02 =
"{\n"
    "\"one\": {\n"
            "\t\"header\": \"SVG Viewer\",\n"
            "\t\"items\": [\n"
                            "\t\t{\"id\": \"Open\"},\n"
                            "\t\t[\"abc\", 1.234, 0.3e-1, 3.141516,],\n"
                            "\t\tnull,\n"
                            "\t\tfalse,\n"
                            "\t\ttrue\n"
                            "]\n"
            "\t}\n"
    "\"two\":null\n"
"}\n";
#endif



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

    
    szTbl_SharedReset();
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






int         test_cmdutl_OpenClose(
    const
    char        *pTestName
)
{
    CMDUTL_DATA	*pObj = OBJ_NIL;
   
    fprintf(stderr, "Performing: %s\n", pTestName);
    
    pObj = cmdutl_Alloc( );
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    pObj = cmdutl_Init(pObj, 0, NULL);
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    if (pObj) {

        // Test something.

        obj_Release(pObj);
        pObj = OBJ_NIL;
    }

    fprintf(stderr, "...%s completed.\n", pTestName);
    return 1;
}



int         test_cmdutl_CommandString01(
    const
    char        *pTestName
)
{
    ASTR_DATA       *pStr = OBJ_NIL;
    ASTRARRAY_DATA  *pArray = OBJ_NIL;
    uint32_t        cArray;
    bool            fDebug = false;
    
    
    fprintf(stderr, "Performing: %s\n", pTestName);
    
    pArray = cmdutl_CommandStringToArray(" a b --c d");
    XCTAssertFalse( (OBJ_NIL == pArray) );
    cArray = AStrArray_getSize(pArray);
    XCTAssertTrue( (5 == cArray) );

    if (pArray) {

        pStr = AStrArray_Get(pArray, 1);
        XCTAssertFalse( (OBJ_NIL == pStr) );
        XCTAssertTrue( (ERESULT_SUCCESS_EQUAL == AStr_CompareA(pStr, "")) );
        
        pStr = AStrArray_Get(pArray, 2);
        XCTAssertFalse( (OBJ_NIL == pStr) );
        XCTAssertTrue( (ERESULT_SUCCESS_EQUAL == AStr_CompareA(pStr, "a")) );
        
        pStr = AStrArray_Get(pArray, 3);
        XCTAssertFalse( (OBJ_NIL == pStr) );
        XCTAssertTrue( (ERESULT_SUCCESS_EQUAL == AStr_CompareA(pStr, "b")) );
        
        pStr = AStrArray_Get(pArray, 4);
        XCTAssertFalse( (OBJ_NIL == pStr) );
        XCTAssertTrue( (ERESULT_SUCCESS_EQUAL == AStr_CompareA(pStr, "--c")) );
        
        pStr = AStrArray_Get(pArray, 5);
        XCTAssertFalse( (OBJ_NIL == pStr) );
        XCTAssertTrue( (ERESULT_SUCCESS_EQUAL == AStr_CompareA(pStr, "d")) );
        
        obj_Release(pArray);
        pArray = OBJ_NIL;
    }
    
    pArray = cmdutl_CommandStringToArray(" --define xx=\"yy yy\" abc");
    XCTAssertFalse( (OBJ_NIL == pArray) );
    cArray = AStrArray_getSize(pArray);
    XCTAssertTrue( (5 == cArray) );

    if (pArray) {

        if (fDebug) {
            ASTR_DATA       *pDump;
            pDump = AStrArray_ToDebugString(pArray, 0);
            if (pDump) {
                fprintf(stderr, "%s\n", AStr_getData(pDump));
                obj_Release(pDump);
            }
        }
        pStr = AStrArray_Get(pArray, 1);
        XCTAssertFalse( (OBJ_NIL == pStr) );
        XCTAssertTrue( (ERESULT_SUCCESS_EQUAL == AStr_CompareA(pStr, "")) );
        
        pStr = AStrArray_Get(pArray, 2);
        XCTAssertFalse( (OBJ_NIL == pStr) );
        XCTAssertTrue( (ERESULT_SUCCESS_EQUAL == AStr_CompareA(pStr, "--define")) );
        
        pStr = AStrArray_Get(pArray, 3);
        XCTAssertFalse( (OBJ_NIL == pStr) );
        XCTAssertTrue( (ERESULT_SUCCESS_EQUAL == AStr_CompareA(pStr, "xx")) );
        
        pStr = AStrArray_Get(pArray, 4);
        XCTAssertFalse( (OBJ_NIL == pStr) );
        XCTAssertTrue( (ERESULT_SUCCESS_EQUAL == AStr_CompareA(pStr, "yy yy")) );
        
        pStr = AStrArray_Get(pArray, 5);
        XCTAssertFalse( (OBJ_NIL == pStr) );
        XCTAssertTrue( (ERESULT_SUCCESS_EQUAL == AStr_CompareA(pStr, "abc")) );
        
        obj_Release(pArray);
        pArray = OBJ_NIL;
    }
    
    fprintf(stderr, "...%s completed.\n", pTestName);
    return 1;
}



int         test_cmdutl_ParseCommandLine01(
    const
    char        *pTestName
)
{
    CMDUTL_DATA     *pObj = OBJ_NIL;
    char            *ppArgs[] = {
        "./test",
        "-vv",
        "-f",
        "xyzzy",
        "abc",
        "def",
        NULL
    };
    const
    char            *pOptString = "df::hv";
    int             iRc;
    bool            fRc;
    char            *pArg;
    
    fprintf(stderr, "Performing: %s\n", pTestName);
    
    pObj = cmdutl_New(6, ppArgs);
    XCTAssertFalse( (OBJ_NIL == pObj) );
    
    if (pObj) {
        
        iRc = cmdutl_Parse(pObj, pOptString);
        XCTAssertTrue( ('v' == iRc) );
        XCTAssertTrue( ('v' == pObj->optopt) );
        XCTAssertTrue( (NULL == pObj->pOptArg) );
        XCTAssertTrue( (pObj->optIndex == 1) );
        XCTAssertTrue( (pObj->subopt == 1) );

        fRc = cmdutl_IsMore(pObj);
        XCTAssertTrue( (fRc) );
        
        iRc = cmdutl_Parse(pObj, pOptString);
        XCTAssertTrue( ('v' == iRc) );
        XCTAssertTrue( ('v' == pObj->optopt) );
        XCTAssertTrue( (NULL == pObj->pOptArg) );
        XCTAssertTrue( (pObj->optIndex == 2) );
        XCTAssertTrue( (pObj->subopt == 0) );
        
        iRc = cmdutl_Parse(pObj, pOptString);
        XCTAssertTrue( ('f' == iRc) );
        XCTAssertTrue( ('f' == pObj->optopt) );
        XCTAssertTrue( (pObj->pOptArg) );
        XCTAssertTrue( (0 == strcmp(pObj->pOptArg, "xyzzy")) );
        
        iRc = cmdutl_Parse(pObj, pOptString);
        XCTAssertTrue( (-1 == iRc) );
        XCTAssertTrue( (0 == pObj->optopt) );
        XCTAssertTrue( (NULL == pObj->pOptArg) );
        
        pArg = cmdutl_NextArg(pObj);
        XCTAssertTrue( (0 == pObj->optopt) );
        XCTAssertTrue( (pArg) );
        XCTAssertTrue( (0 == strcmp(pArg, "abc")) );
        
        fRc = cmdutl_IsMore(pObj);
        XCTAssertTrue( (fRc) );
        
        pArg = cmdutl_NextArg(pObj);
        XCTAssertTrue( (0 == pObj->optopt) );
        XCTAssertTrue( (pArg) );
        XCTAssertTrue( (0 == strcmp(pArg, "def")) );
        
        fRc = cmdutl_IsMore(pObj);
        XCTAssertTrue( (!fRc) );

        pArg = cmdutl_NextArg(pObj);
        XCTAssertTrue( (0 == pObj->optopt) );
        XCTAssertTrue( (NULL == pArg) );
        
        obj_Release(pObj);
        pObj = OBJ_NIL;
    }
    
    fprintf(stderr, "...%s completed.\n", pTestName);
    return 1;
}



int         test_cmdutl_ParseCommandLine02(
    const
    char        *pTestName
)
{
    CMDUTL_DATA     *pObj = OBJ_NIL;
    CMDUTL_OPTION   longDefns[5] = {
        {"debug",   'd', CMDUTL_ARG_OPTION_NONE},
        {"file",    'f', CMDUTL_ARG_OPTION_REQUIRED},
        {"help",    'h', CMDUTL_ARG_OPTION_NONE},
        {"verbose", 'v', CMDUTL_ARG_OPTION_NONE},
        {0, 0, 0}
    };
    char            *ppArgs[] = {
        "./test",
        "--verbose",
        "--file",
        "xyzzy",
        "abc",
        "-f",
        "xyzzy2",
        "def",
        NULL
    };
    int             iRc;
    bool            fRc;
    char            *pArg;
    int             longIndex;

    fprintf(stderr, "Performing: %s\n", pTestName);
    
    pObj = cmdutl_New(8, ppArgs);
    XCTAssertFalse( (OBJ_NIL == pObj) );
    
    if (pObj) {
        
        iRc = cmdutl_ParseLong(pObj, longDefns, &longIndex);
        XCTAssertTrue( ('v' == iRc) );
        XCTAssertTrue( ('v' == pObj->optopt) );
        XCTAssertTrue( (NULL == pObj->pOptArg) );
        XCTAssertTrue( (pObj->optIndex == 2) );
        XCTAssertTrue( (3 == longIndex) );

        fRc = cmdutl_IsMore(pObj);
        XCTAssertTrue( (fRc) );
        
        iRc = cmdutl_ParseLong(pObj, longDefns, &longIndex);
        XCTAssertTrue( ('f' == iRc) );
        XCTAssertTrue( ('f' == pObj->optopt) );
        XCTAssertTrue( (pObj->pOptArg) );
        XCTAssertTrue( (0 == strcmp(pObj->pOptArg, "xyzzy")) );
        XCTAssertTrue( (1 == longIndex) );

        iRc = cmdutl_ParseLong(pObj, longDefns, &longIndex);
        XCTAssertTrue( (-1 == iRc) );
        XCTAssertTrue( (0 == pObj->optopt) );
        XCTAssertTrue( (NULL == pObj->pOptArg) );
        
        pArg = cmdutl_NextArg(pObj);
        XCTAssertTrue( (0 == pObj->optopt) );
        XCTAssertTrue( (pArg) );
        XCTAssertTrue( (0 == strcmp(pArg, "abc")) );
        
        fRc = cmdutl_IsMore(pObj);
        XCTAssertTrue( (fRc) );
        
        iRc = cmdutl_ParseLong(pObj, longDefns, &longIndex);
        XCTAssertTrue( ('f' == iRc) );
        //XCTAssertTrue( ('f' == pObj->optopt) );
        XCTAssertTrue( (pObj->pOptArg) );
        XCTAssertTrue( (0 == strcmp(pObj->pOptArg, "xyzzy2")) );
        XCTAssertTrue( (1 == longIndex) );

        pArg = cmdutl_NextArg(pObj);
        XCTAssertTrue( (0 == pObj->optopt) );
        XCTAssertTrue( (pArg) );
        XCTAssertTrue( (0 == strcmp(pArg, "def")) );
        
        fRc = cmdutl_IsMore(pObj);
        XCTAssertTrue( (!fRc) );
        
        pArg = cmdutl_NextArg(pObj);
        XCTAssertTrue( (0 == pObj->optopt) );
        XCTAssertTrue( (NULL == pArg) );
        
        obj_Release(pObj);
        pObj = OBJ_NIL;
    }
    
    fprintf(stderr, "...%s completed.\n", pTestName);
    return 1;
}



int         test_cmdutl_ParseCommandLine03(
    const
    char        *pTestName
)
{
    ERESULT         eRc;
    CMDUTL_DATA     *pObj = OBJ_NIL;
    CMDUTL_OPTION   longDefns1[4] = {
        {"debug",   'd', CMDUTL_ARG_OPTION_NONE},
        {"file",    'f', CMDUTL_ARG_OPTION_REQUIRED},
        {"verbose", 'v', CMDUTL_ARG_OPTION_NONE},
        {0, 0, 0}
    };
    CMDUTL_OPTION   longDefns2[4] = {
        {NULL,      'D', CMDUTL_ARG_OPTION_NONE},
        {"help",    'h', CMDUTL_ARG_OPTION_NONE},
        {NULL,      'V', CMDUTL_ARG_OPTION_NONE},
        {0, 0, 0}
    };
    char            *ppArgs[] = {
        "./test",
        "--verbose",
        "--file",
        "xyzzy",
        "abc",
        "-f",
        "xyzzy2",
        "def",
        NULL
    };
    int             iRc;
    bool            fRc;
    char            *pArg;
    int             longIndex;
    
    fprintf(stderr, "Performing: %s\n", pTestName);
    
    pObj = cmdutl_New(8, ppArgs);
    XCTAssertFalse( (OBJ_NIL == pObj) );
    
    if (pObj) {
        
        eRc = cmdutl_SetupOptions(pObj, longDefns1, longDefns2);
        XCTAssertFalse( (ERESULT_FAILED(eRc)) );

        iRc = cmdutl_ParseLong(pObj, cmdutl_getOptionDefinitions(pObj), &longIndex);
        XCTAssertTrue( ('v' == iRc) );
        XCTAssertTrue( ('v' == pObj->optopt) );
        XCTAssertTrue( (NULL == pObj->pOptArg) );
        XCTAssertTrue( (pObj->optIndex == 2) );
        XCTAssertTrue( (2 == longIndex) );
        
        fRc = cmdutl_IsMore(pObj);
        XCTAssertTrue( (fRc) );
        
        iRc = cmdutl_ParseLong(pObj, cmdutl_getOptionDefinitions(pObj), &longIndex);
        XCTAssertTrue( ('f' == iRc) );
        XCTAssertTrue( ('f' == pObj->optopt) );
        XCTAssertTrue( (pObj->pOptArg) );
        XCTAssertTrue( (0 == strcmp(pObj->pOptArg, "xyzzy")) );
        XCTAssertTrue( (1 == longIndex) );
        
        iRc = cmdutl_ParseLong(pObj, cmdutl_getOptionDefinitions(pObj), &longIndex);
        XCTAssertTrue( (-1 == iRc) );
        XCTAssertTrue( (0 == pObj->optopt) );
        XCTAssertTrue( (NULL == pObj->pOptArg) );
        
        pArg = cmdutl_NextArg(pObj);
        XCTAssertTrue( (0 == pObj->optopt) );
        XCTAssertTrue( (pArg) );
        XCTAssertTrue( (0 == strcmp(pArg, "abc")) );
        
        fRc = cmdutl_IsMore(pObj);
        XCTAssertTrue( (fRc) );
        
        iRc = cmdutl_ParseLong(pObj, cmdutl_getOptionDefinitions(pObj), &longIndex);
        XCTAssertTrue( ('f' == iRc) );
        //XCTAssertTrue( ('f' == pObj->optopt) );
        XCTAssertTrue( (pObj->pOptArg) );
        XCTAssertTrue( (0 == strcmp(pObj->pOptArg, "xyzzy2")) );
        XCTAssertTrue( (1 == longIndex) );
        
        pArg = cmdutl_NextArg(pObj);
        XCTAssertTrue( (0 == pObj->optopt) );
        XCTAssertTrue( (pArg) );
        XCTAssertTrue( (0 == strcmp(pArg, "def")) );
        
        fRc = cmdutl_IsMore(pObj);
        XCTAssertTrue( (!fRc) );
        
        pArg = cmdutl_NextArg(pObj);
        XCTAssertTrue( (0 == pObj->optopt) );
        XCTAssertTrue( (NULL == pArg) );
        
        obj_Release(pObj);
        pObj = OBJ_NIL;
    }
    
    fprintf(stderr, "...%s completed.\n", pTestName);
    return 1;
}



int         test_cmdutl_ParseCommandLine04(
    const
    char        *pTestName
)
{
    ERESULT         eRc;
    CMDUTL_DATA     *pObj = OBJ_NIL;
    typedef struct options_s {
        uint16_t        fDebug;
        uint16_t        fVerbose;
        PATH_DATA       *pFilePath;
    } OPTIONS;
    OPTIONS         options = {0};
    CMDUTL_OPTION   longDefns1[4] = {
        {"debug",   'd', CMDUTL_ARG_OPTION_NONE, CMDUTL_TYPE_BOOL,
            offsetof(OPTIONS, fDebug), NULL, NULL},
        {"file",    'f', CMDUTL_ARG_OPTION_REQUIRED, CMDUTL_TYPE_PATH,
            offsetof(OPTIONS, pFilePath), NULL, NULL},
        {"verbose", 'v', CMDUTL_ARG_OPTION_NONE, CMDUTL_TYPE_INCR,
            offsetof(OPTIONS, fVerbose), NULL, NULL},
        {0}
    };
    CMDUTL_OPTION   longDefns2[4] = {
        {NULL,      'D', CMDUTL_ARG_OPTION_NONE},
        {"help",    'h', CMDUTL_ARG_OPTION_NONE},
        {NULL,      'V', CMDUTL_ARG_OPTION_NONE},
        {0, 0, 0}
    };
    char            *ppArgs[] = {
        "./test",
        "-vv",
        "--file",
        "xyzzy",
        "abc",
        "-f",
        "xyzzy2",
        "def",
        NULL
    };
    //int             iRc;
    bool            fRc;
    char            *pArg;
    //int             longIndex;
    
    fprintf(stderr, "Performing: %s\n", pTestName);
    
    pObj = cmdutl_New(8, ppArgs);
    XCTAssertFalse( (OBJ_NIL == pObj) );
    
    if (pObj) {
        
        eRc = cmdutl_SetupOptions(pObj, longDefns1, longDefns2);
        XCTAssertFalse( (ERESULT_FAILED(eRc)) );
        pObj->pObj = &options;

        eRc = cmdutl_ProcessOptions(pObj);
        XCTAssertFalse( (ERESULT_FAILED(eRc)) );
        XCTAssertTrue( (0 == options.fDebug) );
        XCTAssertTrue( (2 == options.fVerbose) );
        XCTAssertFalse( (OBJ_NIL == options.pFilePath) );
        XCTAssertTrue( (obj_IsKindOf(options.pFilePath, OBJ_IDENT_PATH)) );
        XCTAssertTrue( (0 == strcmp(path_getData(options.pFilePath), "xyzzy")) );
        obj_Release(options.pFilePath);
        options.pFilePath = OBJ_NIL;

        fRc = cmdutl_IsMore(pObj);
        XCTAssertTrue( (fRc) );
        
        pArg = cmdutl_NextArg(pObj);
        XCTAssertTrue( (0 == pObj->optopt) );
        XCTAssertTrue( (pArg) );
        XCTAssertTrue( (0 == strcmp(pArg, "abc")) );
        
        fRc = cmdutl_IsMore(pObj);
        XCTAssertTrue( (fRc) );
        
        eRc = cmdutl_ProcessOptions(pObj);
        XCTAssertFalse( (ERESULT_FAILED(eRc)) );
        XCTAssertTrue( (0 == options.fDebug) );
        XCTAssertTrue( (2 == options.fVerbose) );
        XCTAssertFalse( (OBJ_NIL == options.pFilePath) );
        XCTAssertTrue( (obj_IsKindOf(options.pFilePath, OBJ_IDENT_PATH)) );
        XCTAssertTrue( (0 == strcmp(path_getData(options.pFilePath), "xyzzy2")) );
        obj_Release(options.pFilePath);
        options.pFilePath = OBJ_NIL;
        

        pArg = cmdutl_NextArg(pObj);
        XCTAssertTrue( (0 == pObj->optopt) );
        XCTAssertTrue( (pArg) );
        XCTAssertTrue( (0 == strcmp(pArg, "def")) );
        
        fRc = cmdutl_IsMore(pObj);
        XCTAssertTrue( (!fRc) );
        
        pArg = cmdutl_NextArg(pObj);
        XCTAssertTrue( (0 == pObj->optopt) );
        XCTAssertTrue( (NULL == pArg) );
        
        pObj->pObj = NULL;
        obj_Release(pObj);
        pObj = OBJ_NIL;
    }
    
    fprintf(stderr, "...%s completed.\n", pTestName);
    return 1;
}



int         test_cmdutl_ParseCommandLine05(
    const
    char        *pTestName
)
{
    ERESULT         eRc;
    CMDUTL_DATA     *pObj = OBJ_NIL;
    typedef struct options_s {
        uint16_t        fDebug;
        uint16_t        fVerbose;
        ASTR_DATA       *pDefine;
        PATH_DATA       *pFilePath;
    } OPTIONS;
    OPTIONS         options = {0};
    CMDUTL_OPTION   longDefns1[5] = {
        {"debug",   0, CMDUTL_ARG_OPTION_NONE, CMDUTL_TYPE_BOOL,
            offsetof(OPTIONS, fDebug), NULL, NULL},
        {"define",    'f', CMDUTL_ARG_OPTION_REQUIRED, CMDUTL_TYPE_STRING,
            offsetof(OPTIONS, pDefine), NULL, NULL},
        {"file",    'f', CMDUTL_ARG_OPTION_REQUIRED, CMDUTL_TYPE_PATH,
            offsetof(OPTIONS, pFilePath), NULL, NULL},
        {"verbose", 'v', CMDUTL_ARG_OPTION_NONE, CMDUTL_TYPE_INCR,
            offsetof(OPTIONS, fVerbose), NULL, NULL},
        {0}
    };
    CMDUTL_OPTION   longDefns2[4] = {
        {NULL,      'D', CMDUTL_ARG_OPTION_NONE},
        {"help",    'h', CMDUTL_ARG_OPTION_NONE},
        {NULL,      'V', CMDUTL_ARG_OPTION_NONE},
        {0, 0, 0}
    };
    char            *ppArgs[] = {
        "./test",
        "--debug",
        "-vv",
        "--file",
        "xyzzy",
        "--define",
        "xxx=\"yy yy\"",
        "abc",
        "-f",
        "xyzzy2",
        "def",
        NULL
    };
    //int             iRc;
    bool            fRc;
    char            *pArg;
    //int             longIndex;
    
    fprintf(stderr, "Performing: %s\n", pTestName);
    
    pObj = cmdutl_New(8, ppArgs);
    XCTAssertFalse( (OBJ_NIL == pObj) );
    
    if (pObj) {
        
        eRc = cmdutl_SetupOptions(pObj, longDefns1, longDefns2);
        XCTAssertFalse( (ERESULT_FAILED(eRc)) );
        pObj->pObj = &options;
        
        eRc = cmdutl_ProcessOptions(pObj);
        XCTAssertFalse( (ERESULT_FAILED(eRc)) );
        XCTAssertTrue( (1 == options.fDebug) );
        XCTAssertTrue( (2 == options.fVerbose) );
        XCTAssertFalse( (OBJ_NIL == options.pFilePath) );
        XCTAssertTrue( (obj_IsKindOf(options.pFilePath, OBJ_IDENT_PATH)) );
        XCTAssertTrue( (0 == strcmp(path_getData(options.pFilePath), "xyzzy")) );
        obj_Release(options.pFilePath);
        options.pFilePath = OBJ_NIL;
        
        fRc = cmdutl_IsMore(pObj);
        XCTAssertTrue( (fRc) );
        
        pArg = cmdutl_NextArg(pObj);
        XCTAssertTrue( (0 == pObj->optopt) );
        XCTAssertTrue( (pArg) );
        XCTAssertTrue( (0 == strcmp(pArg, "abc")) );
        
        fRc = cmdutl_IsMore(pObj);
        XCTAssertTrue( (fRc) );
        
        eRc = cmdutl_ProcessOptions(pObj);
        XCTAssertFalse( (ERESULT_FAILED(eRc)) );
        XCTAssertTrue( (1 == options.fDebug) );
        XCTAssertTrue( (2 == options.fVerbose) );
        XCTAssertFalse( (OBJ_NIL == options.pDefine) );
        XCTAssertTrue( (obj_IsKindOf(options.pDefine, OBJ_IDENT_ASTR)) );
        XCTAssertTrue( (0 == strcmp(AStr_getData(options.pDefine), "xxx=\"yy yy\"")) );
        obj_Release(options.pDefine);
        options.pDefine = OBJ_NIL;
        XCTAssertFalse( (OBJ_NIL == options.pFilePath) );
        XCTAssertTrue( (obj_IsKindOf(options.pFilePath, OBJ_IDENT_PATH)) );
        XCTAssertTrue( (0 == strcmp(path_getData(options.pFilePath), "xyzzy2")) );
        obj_Release(options.pFilePath);
        options.pFilePath = OBJ_NIL;
        
        
        pArg = cmdutl_NextArg(pObj);
        XCTAssertTrue( (0 == pObj->optopt) );
        XCTAssertTrue( (pArg) );
        XCTAssertTrue( (0 == strcmp(pArg, "def")) );
        
        fRc = cmdutl_IsMore(pObj);
        XCTAssertTrue( (!fRc) );
        
        pArg = cmdutl_NextArg(pObj);
        XCTAssertTrue( (0 == pObj->optopt) );
        XCTAssertTrue( (NULL == pArg) );
        
        pObj->pObj = NULL;
        obj_Release(pObj);
        pObj = OBJ_NIL;
    }
    
    fprintf(stderr, "...%s completed.\n", pTestName);
    return 1;
}



int         test_cmdutl_ParseCommandLine06(
    const
    char        *pTestName
)
{
    ERESULT         eRc;
    CMDUTL_DATA     *pObj = OBJ_NIL;
    typedef struct options_s {
        uint16_t        fDebug;
        uint16_t        fVerbose;
        ASTR_DATA       *pDefine;
        PATH_DATA       *pFilePath;
    } OPTIONS;
    OPTIONS         options = {0};
    CMDUTL_OPTION   longDefns1[5] = {
        {"debug",   0, CMDUTL_ARG_OPTION_NONE, CMDUTL_TYPE_BOOL,
            offsetof(OPTIONS, fDebug), NULL, NULL},
        {"define",    'f', CMDUTL_ARG_OPTION_REQUIRED, CMDUTL_TYPE_STRING,
            offsetof(OPTIONS, pDefine), NULL, NULL},
        {"file",    'f', CMDUTL_ARG_OPTION_REQUIRED, CMDUTL_TYPE_PATH,
            offsetof(OPTIONS, pFilePath), NULL, NULL},
        {"verbose", 'v', CMDUTL_ARG_OPTION_NONE, CMDUTL_TYPE_INCR,
            offsetof(OPTIONS, fVerbose), NULL, NULL},
        {0}
    };
    CMDUTL_OPTION   longDefns2[4] = {
        {NULL,      'D', CMDUTL_ARG_OPTION_NONE},
        {"help",    'h', CMDUTL_ARG_OPTION_NONE},
        {NULL,      'V', CMDUTL_ARG_OPTION_NONE},
        {0, 0, 0}
    };
    char            *ppArgs[] = {
        "./test",
        "--debug",
        "-vv",
        "--file",
        "xyzzy",
        "--define",
        "xxx=\"yy yy\"",
        "abc",
        "-f",
        "xyzzy2",
        "def",
        NULL
    };
    //int             iRc;
    bool            fRc;
    char            *pArg;
    //int             longIndex;
    
    fprintf(stderr, "Performing: %s\n", pTestName);
    
    pObj = cmdutl_New(8, ppArgs);
    XCTAssertFalse( (OBJ_NIL == pObj) );
    
    if (pObj) {
        
        eRc = cmdutl_SetupOptions(pObj, longDefns1, longDefns2);
        XCTAssertFalse( (ERESULT_FAILED(eRc)) );
        pObj->pObj = &options;
        
        eRc = cmdutl_ProcessOptions(pObj);
        XCTAssertFalse( (ERESULT_FAILED(eRc)) );
        XCTAssertTrue( (1 == options.fDebug) );
        XCTAssertTrue( (2 == options.fVerbose) );
        XCTAssertFalse( (OBJ_NIL == options.pFilePath) );
        XCTAssertTrue( (obj_IsKindOf(options.pFilePath, OBJ_IDENT_PATH)) );
        XCTAssertTrue( (0 == strcmp(path_getData(options.pFilePath), "xyzzy")) );
        obj_Release(options.pFilePath);
        options.pFilePath = OBJ_NIL;
        
        fRc = cmdutl_IsMore(pObj);
        XCTAssertTrue( (fRc) );
        
        pArg = cmdutl_NextArg(pObj);
        XCTAssertTrue( (0 == pObj->optopt) );
        XCTAssertTrue( (pArg) );
        XCTAssertTrue( (0 == strcmp(pArg, "abc")) );
        
        fRc = cmdutl_IsMore(pObj);
        XCTAssertTrue( (fRc) );
        
        eRc = cmdutl_ProcessOptions(pObj);
        XCTAssertFalse( (ERESULT_FAILED(eRc)) );
        XCTAssertTrue( (1 == options.fDebug) );
        XCTAssertTrue( (2 == options.fVerbose) );
        XCTAssertFalse( (OBJ_NIL == options.pDefine) );
        XCTAssertTrue( (obj_IsKindOf(options.pDefine, OBJ_IDENT_ASTR)) );
        XCTAssertTrue( (0 == strcmp(AStr_getData(options.pDefine), "xxx=\"yy yy\"")) );
        obj_Release(options.pDefine);
        options.pDefine = OBJ_NIL;
        XCTAssertFalse( (OBJ_NIL == options.pFilePath) );
        XCTAssertTrue( (obj_IsKindOf(options.pFilePath, OBJ_IDENT_PATH)) );
        XCTAssertTrue( (0 == strcmp(path_getData(options.pFilePath), "xyzzy2")) );
        obj_Release(options.pFilePath);
        options.pFilePath = OBJ_NIL;
        
        
        pArg = cmdutl_NextArg(pObj);
        XCTAssertTrue( (0 == pObj->optopt) );
        XCTAssertTrue( (pArg) );
        XCTAssertTrue( (0 == strcmp(pArg, "def")) );
        
        fRc = cmdutl_IsMore(pObj);
        XCTAssertTrue( (!fRc) );
        
        pArg = cmdutl_NextArg(pObj);
        XCTAssertTrue( (0 == pObj->optopt) );
        XCTAssertTrue( (NULL == pArg) );
        
        pObj->pObj = NULL;
        obj_Release(pObj);
        pObj = OBJ_NIL;
    }
    
    fprintf(stderr, "...%s completed.\n", pTestName);
    return 1;
}



int         test_cmdutl_Input01(
    const
    char        *pTestName
)
{
    CMDUTL_DATA     *pObj = OBJ_NIL;
    PATH_DATA       *pPath = OBJ_NIL;
    ASTR_DATA       *pStr = OBJ_NIL;
    NODEHASH_DATA   *pHash = OBJ_NIL;
    NODE_DATA       *pFileNode = OBJ_NIL;
    NODE_DATA       *pNode = OBJ_NIL;
    NODEARRAY_DATA  *pArray = OBJ_NIL;
    const
    char            *pStrA = NULL;
    
    
    fprintf(stderr, "Performing: %s\n", pTestName);
    
    pStr = AStr_NewA(pTestInput01);
    XCTAssertFalse( (OBJ_NIL == pStr) );
    pPath = path_NewA("abc");
    XCTAssertFalse( (OBJ_NIL == pPath) );
    
    //pObj = cmdutl_NewAStr(pStr, pPath, 4);
    XCTAssertFalse( (OBJ_NIL == pObj) );
    obj_Release(pStr);
    obj_Release(pPath);
    obj_setFlags(pObj, (obj_getFlags(pObj) | OBJ_FLAG_TRACE));
    if (pObj) {
        
        //pFileNode = cmdutl_ParseFile(pObj);
        XCTAssertFalse( (OBJ_NIL == pFileNode) );
        if (pFileNode) {
            pStrA = node_getNameUTF8(pFileNode);
            XCTAssertTrue( (0 == strcmp("hash", pStrA)) );
            mem_Free((void *)pStrA);
            pHash = node_getData(pFileNode);
            XCTAssertFalse( (OBJ_NIL == pHash) );
            XCTAssertTrue( (4 == NodeHash_getSize(pHash)) );
            
            pNode = NodeHash_FindA(pHash, 0, "one");
            XCTAssertFalse( (OBJ_NIL == pNode) );
            pNode = node_getData(pNode);
            pStrA = node_getNameUTF8(pNode);
            XCTAssertTrue( (0 == strcmp("number", pStrA)) );
            mem_Free((void *)pStrA);
            pStr = node_getData(pNode);
            XCTAssertTrue( (0 == strcmp("123", AStr_getData(pStr))) );
            
            pNode = NodeHash_FindA(pHash, 0, "two");
            XCTAssertFalse( (OBJ_NIL == pNode) );
            pNode = node_getData(pNode);
            pStrA = node_getNameUTF8(pNode);
            XCTAssertTrue( (0 == strcmp("string", pStrA)) );
            mem_Free((void *)pStrA);
            pStr = node_getData(pNode);
            XCTAssertTrue( (0 == strcmp("xyz", AStr_getData(pStr))) );
            
            pNode = NodeHash_FindA(pHash, 0, "three");
            XCTAssertFalse( (OBJ_NIL == pNode) );
            pNode = node_getData(pNode);
            pStrA = node_getNameUTF8(pNode);
            XCTAssertTrue( (0 == strcmp("array", pStrA)) );
            mem_Free((void *)pStrA);
            pArray = node_getData(pNode);
            XCTAssertTrue( (3 == NodeArray_getSize(pArray)) );
            pNode = NodeArray_Get(pArray, 1);
            XCTAssertFalse( (OBJ_NIL == pNode) );
            pStr = node_getData(pNode);
            XCTAssertTrue( (0 == strcmp("a", AStr_getData(pStr))) );
            pNode = NodeArray_Get(pArray, 2);
            XCTAssertFalse( (OBJ_NIL == pNode) );
            pStr = node_getData(pNode);
            XCTAssertTrue( (0 == strcmp("b", AStr_getData(pStr))) );
            pNode = NodeArray_Get(pArray, 3);
            XCTAssertFalse( (OBJ_NIL == pNode) );
            pStr = node_getData(pNode);
            XCTAssertTrue( (0 == strcmp("c", AStr_getData(pStr))) );
            
            pNode = NodeHash_FindA(pHash, 0, "four");
            XCTAssertFalse( (OBJ_NIL == pNode) );
            pNode = node_getData(pNode);
            pStrA = node_getNameUTF8(pNode);
            XCTAssertTrue( (0 == strcmp("null", pStrA)) );
            mem_Free((void *)pStrA);
            
        }
        
        obj_Release(pFileNode);
        pFileNode = OBJ_NIL;
        
        obj_Release(pObj);
        pObj = OBJ_NIL;
    }
    
    fprintf(stderr, "...%s completed.\n", pTestName);
    return 1;
}




TINYTEST_START_SUITE(test_cmdutl);
    //TINYTEST_ADD_TEST(test_cmdutl_Input01,setUp,tearDown);
    TINYTEST_ADD_TEST(test_cmdutl_ParseCommandLine06,setUp,tearDown);
    TINYTEST_ADD_TEST(test_cmdutl_ParseCommandLine05,setUp,tearDown);
    TINYTEST_ADD_TEST(test_cmdutl_ParseCommandLine04,setUp,tearDown);
    TINYTEST_ADD_TEST(test_cmdutl_ParseCommandLine03,setUp,tearDown);
    TINYTEST_ADD_TEST(test_cmdutl_ParseCommandLine02,setUp,tearDown);
    TINYTEST_ADD_TEST(test_cmdutl_ParseCommandLine01,setUp,tearDown);
    TINYTEST_ADD_TEST(test_cmdutl_CommandString01,setUp,tearDown);
    TINYTEST_ADD_TEST(test_cmdutl_OpenClose,setUp,tearDown);
TINYTEST_END_SUITE();

TINYTEST_MAIN_SINGLE_SUITE(test_cmdutl);





