// vi:nu:et:sts=4 ts=4 sw=4
/*
 *	Generated 01/31/2020 10:23:30
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
#include    <JsonIn.h>
#include    <trace.h>
#include    <Dir_internal.h>
#ifdef  DIR_JSON_SUPPORT
#   include    <SrcErrors.h>
#   include    <szTbl.h>
#endif
#include    <enum_internal.h>
#include    <sys/stat.h>
#include    <sys/types.h>



static
char            *pDir = NULL;
static
char            *pPattern = NULL;
static
int             count = 1;



static
bool            globScanner(void *pObject, DIRENTRY_DATA *pEntry, void *pData)
{
    ERESULT         eRc;
    PATH_DATA       *pPath;
    DIRENTRY_DATA   *pLink;

    if (pPattern) {
        eRc = DirEntry_MatchA(pEntry, pPattern);
        if (ERESULT_FAILED(eRc)) {
            return true;
        }
    }
    pPath = DirEntry_getFullPath(pEntry);
    if (pPath) {
        fprintf(
                stderr,
                "\t%2d name: %s  type: %d\n",
                count++,
                Path_getData(pPath),
                DirEntry_getType(pEntry)
        );
        DirEntry_Complete(pEntry);
        pLink = DirEntry_Target(pEntry);
        if (!(pLink == pEntry)) {
            fprintf(
                    stderr,
                    "  ->  %2d name: %s  type: %d",
                    count++,
                    Path_getData(DirEntry_getFullPath(pLink)),
                    DirEntry_getType(pLink)
            );
        }
        fprintf(stderr, "\n");
    }

    return true;
}



static
bool            scanner( void *pData, DIRENTRY_DATA *pEntry)
{
    ERESULT         eRc;
    PATH_DATA       *pPath;
    DIRENTRY_DATA   *pLink;

    if (pPattern) {
        eRc = DirEntry_MatchA(pEntry, pPattern);
        if (ERESULT_FAILED(eRc)) {
            return true;
        }
    }
    pPath = DirEntry_getFullPath(pEntry);
    if (pPath) {
        fprintf(
                stderr,
                "\t%2d name: %s  type: %d",
                count++,
                Path_getData(DirEntry_getFullPath(pEntry)),
                DirEntry_getType(pEntry)
                );
        DirEntry_Complete(pEntry);
        pLink = DirEntry_Target(pEntry);
        if (!(pLink == pEntry)) {
            fprintf(
                    stderr,
                    "  ->  %2d name: %s  type: %d",
                    count++,
                    Path_getData(DirEntry_getFullPath(pLink)),
                    DirEntry_getType(pLink)
            );
        }
            fprintf(stderr, "\n");
    }

    return true;
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

    pPattern = NULL;
#ifdef  DIR_JSON_SUPPORT
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






int             test_Dir_OpenClose (
    const
    char            *pTestName
)
{
    ERESULT         eRc = ERESULT_SUCCESS;
    DIR_DATA	    *pObj = OBJ_NIL;
    bool            fRc;
   
    fprintf(stderr, "Performing: %s\n", pTestName);

    pObj = Dir_Alloc( );
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    pObj = Dir_Init( pObj );
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    if (pObj) {

        //obj_TraceSet(pObj, true);       
        fRc = obj_IsKindOf(pObj, OBJ_IDENT_DIR);
        TINYTEST_TRUE( (fRc) );
        
        // Test something.
        TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );

        obj_Release(pObj);
        pObj = OBJ_NIL;
    }

    fprintf(stderr, "...%s completed.\n\n\n\n", pTestName);
    return 1;
}



int             test_Dir_Copy01 (
    const
    char            *pTestName
)
{
    ERESULT         eRc = ERESULT_SUCCESS;
    DIR_DATA	    *pObj1 = OBJ_NIL;
    DIR_DATA	    *pObj2 = OBJ_NIL;
    bool            fRc;
#if defined(DIR_JSON_SUPPORT) && defined(XYZZY)
    ASTR_DATA	    *pStr = OBJ_NIL;
#endif
   
    fprintf(stderr, "Performing: %s\n", pTestName);

    pObj1 = Dir_New( );
    TINYTEST_FALSE( (OBJ_NIL == pObj1) );
    if (pObj1) {

        //obj_TraceSet(pObj1, true);       
        fRc = obj_IsKindOf(pObj1, OBJ_IDENT_DIR);
        TINYTEST_TRUE( (fRc) );
        
        // Test assign.
        pObj2 = Dir_New();
        TINYTEST_FALSE( (OBJ_NIL == pObj2) );
        eRc = Dir_Assign(pObj1, pObj2);
        TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );

        fRc = obj_IsKindOf(pObj2, OBJ_IDENT_DIR);
        TINYTEST_TRUE( (fRc) );
        //eRc = Dir_Compare(pObj1, pObj2);
        //TINYTEST_TRUE( (ERESULT_SUCCESS_EQUAL == eRc) );
        //TODO: Add More tests here!

        obj_Release(pObj2);
        pObj2 = OBJ_NIL;

        // Test copy.
        pObj2 = Dir_Copy(pObj1);
        TINYTEST_FALSE( (OBJ_NIL == pObj2) );

        fRc = obj_IsKindOf(pObj2, OBJ_IDENT_DIR);
        TINYTEST_TRUE( (fRc) );
        //TODO: Add More tests here!

        obj_Release(pObj2);
        pObj2 = OBJ_NIL;

        // Test json support.
#if defined(DIR_JSON_SUPPORT) && defined(XYZZY)
        pStr = Dir_ToJson(pObj1);
        TINYTEST_FALSE( (OBJ_NIL == pStr) );
        fprintf(stderr, "JSON: %s\n", AStr_getData(pStr));
        pObj2 = Dir_NewFromJsonString(pStr);
        TINYTEST_FALSE( (OBJ_NIL == pObj2) );
        fRc = obj_IsKindOf(pObj2, OBJ_IDENT_DIR);
        TINYTEST_TRUE( (fRc) );
        obj_Release(pStr);
        pStr = OBJ_NIL;
        //eRc = Dir_Compare(pObj1, pObj2);
        //TINYTEST_TRUE( (ERESULT_SUCCESS_EQUAL == eRc) );

        obj_Release(pObj2);
        pObj2 = OBJ_NIL;
#endif

        obj_Release(pObj1);
        pObj1 = OBJ_NIL;
    }

    fprintf(stderr, "...%s completed.\n\n\n\n", pTestName);
    return 1;
}



/* We used this test to work through adding recurse to ScanDir.
 So, we aimed at a directory that only had a few subdirectoreis
 and not many files to make checking easier.
 */
int             test_Dir_Test01 (
    const
    char            *pTestName
)
{
    ERESULT         eRc = ERESULT_SUCCESS;
    DIR_DATA	    *pObj = OBJ_NIL;

    fprintf(stderr, "Performing: %s\n", pTestName);

    pObj = Dir_New( );
    pDir = strdup(TEST_FILES_DIR);
    count = 1;
    XCTAssertFalse( (OBJ_NIL == pObj) );
    if (pObj) {
        PATH_DATA   *pPath;

        count = 1;
        pPath = Path_NewA(pDir);
        eRc = Dir_ScanDir(pObj, pPath, true, (void *)&scanner, NULL, NULL);
        obj_Release(pPath);
        pPath = OBJ_NIL;

        obj_Release(pObj);
        pObj = OBJ_NIL;
    }
    free(pDir);
    pDir = NULL;


    fprintf(stderr, "...%s completed.\n\n\n\n", pTestName);
    return 1;
}



int         test_Dir_Scan01(
    const
    char        *pTestName
)
{
    DIR_DATA    *pObj = OBJ_NIL;
    ERESULT     eRc;
    PATH_DATA   *pPath;

    fprintf(stderr, "Performing: %s\n", pTestName);

    //pPattern = "*.wav";
    pDir = strdup(TEST_FILES_DIR);
    pObj = Dir_New( );
    count = 1;
    XCTAssertFalse( (OBJ_NIL == pObj) );
    if (pObj) {

        count = 1;
        pPath = Path_NewA(pDir);
        eRc = Dir_ScanDir(pObj, pPath, false, (void *)&scanner, NULL, NULL);
        obj_Release(pPath);
        pPath = OBJ_NIL;

        obj_Release(pObj);
        pObj = OBJ_NIL;
    }
    free(pDir);
    pDir = NULL;

    fprintf(stderr, "...%s completed.\n\n\n\n", pTestName);
    return 1;
}



int         test_Dir_Scan02(
    const
    char        *pTestName
)
{
    DIR_DATA    *pObj = OBJ_NIL;
    ERESULT     eRc;
    PATH_DATA   *pPath;

    fprintf(stderr, "Performing: %s\n", pTestName);

    pPattern = "*.txt";
    pDir = strdup(TEST_FILES_DIR);
    count = 1;
    pObj = Dir_Alloc( );
    XCTAssertFalse( (OBJ_NIL == pObj) );
    pObj = Dir_Init( pObj );
    XCTAssertFalse( (OBJ_NIL == pObj) );
    if (pObj) {

        count = 1;
        pPath = Path_NewA(pDir);
        eRc = Dir_ScanDir(pObj, pPath, false, (void *)&scanner, NULL, NULL);
        obj_Release(pPath);
        pPath = OBJ_NIL;

        obj_Release(pObj);
        pObj = OBJ_NIL;
    }
    free(pDir);
    pDir = NULL;

    fprintf(stderr, "...%s completed.\n\n\n\n", pTestName);
    return 1;
}



int         test_Dir_Scan03(
    const
    char        *pTestName
)
{
    DIR_DATA    *pObj = OBJ_NIL;
    ERESULT     eRc;
    PATH_DATA   *pPath;

    fprintf(stderr, "Performing: %s\n", pTestName);

    pPattern = NULL;
    pDir = strdup(TEST_FILES_DIR);
    count = 1;
    pObj = Dir_Alloc( );
    XCTAssertFalse( (OBJ_NIL == pObj) );
    pObj = Dir_Init( pObj );
    XCTAssertFalse( (OBJ_NIL == pObj) );
    if (pObj) {

        count = 1;
        pPath = Path_NewA(pDir);
        eRc = Dir_ScanDir(pObj, pPath, false, (void *)&scanner, NULL, NULL);
        obj_Release(pPath);
        pPath = OBJ_NIL;

        obj_Release(pObj);
        pObj = OBJ_NIL;
    }
    free(pDir);
    pDir = NULL;

    fprintf(stderr, "...%s completed.\n\n\n\n", pTestName);
    return 1;
}



int         test_Dir_Enum01(
    const
    char        *pTestName
)
{
    DIR_DATA        *pObj = OBJ_NIL;
    ERESULT         eRc;
    PATH_DATA       *pPath;
    OBJENUM_DATA    *pEnum = OBJ_NIL;
    DIRENTRY_DATA   *pEntry;
    uint32_t        count;
    uint32_t        i;
    PATH_DATA       *pWrkPath = OBJ_NIL;

    fprintf(stderr, "Performing: %s\n", pTestName);

    pDir = strdup(TEST_FILES_DIR);
    fprintf(stderr, "\tDir: %s\n", pDir);
    XCTAssertFalse( (NULL == pDir) );
    pObj = Dir_Alloc( );
    XCTAssertFalse( (OBJ_NIL == pObj) );
    pObj = Dir_Init( pObj );
    XCTAssertFalse( (OBJ_NIL == pObj) );
    if (pObj) {

        pPath = Path_NewA(pDir);
        if (pPath) {
            pEnum = Dir_EnumDir(pObj, pPath, false);
            if (pEnum) {
                i = 1;
                for (;;) {
                    eRc = ObjEnum_Next(pEnum, 1, (void **)&pEntry, &count);
                    if (ERESULT_FAILED(eRc)) {
                        break;
                    }
                    BREAK_NULL(pEntry);
                    DirEntry_Complete(pEntry);
                    fprintf(
                            stderr,
                            "%2d name: %-25s  type: %2d  gen: %d\n",
                            i,
                            Path_getData(DirEntry_getFullPath(pEntry)),
                            DirEntry_getType(pEntry),
                            DirEntry_getGenerationNumber(pEntry)
                    );
                    obj_Release(pWrkPath);
                    ++i;
                }
                obj_Release(pEnum);
                pEnum = OBJ_NIL;
            }
            obj_Release(pPath);
            pPath = OBJ_NIL;
        }

        obj_Release(pObj);
        pObj = OBJ_NIL;
    }
    free(pDir);
    pDir = NULL;

    fprintf(stderr, "...%s completed.\n\n\n\n", pTestName);
    return 1;
}



int         test_Dir_Enum02(
    const
    char        *pTestName
)
{
    DIR_DATA        *pObj = OBJ_NIL;
    ERESULT         eRc;
    PATH_DATA       *pPath;
    OBJENUM_DATA    *pEnum = OBJ_NIL;
    DIRENTRY_DATA   *pEntry;
    uint32_t        count;
    uint32_t        i;
    PATH_DATA       *pWrkPath = OBJ_NIL;
    const
    char            *pPathA = TEST_FILES_DIR;

    fprintf(stderr, "Performing: %s\n", pTestName);

    pDir = NULL;
    pDir = strdup(pPathA);
    fprintf(stderr, "\tDir: %s\n", pDir);
    XCTAssertFalse( (NULL == pDir) );
    pObj = Dir_Alloc( );
    XCTAssertFalse( (OBJ_NIL == pObj) );
    pObj = Dir_Init( pObj );
    XCTAssertFalse( (OBJ_NIL == pObj) );
    if (pObj) {

        pPath = Path_NewA(pDir);
        if (pPath) {
            pEnum = Dir_EnumDir(pObj, pPath, true);
            if (pEnum) {
                i = 1;
                for (;;) {
                    eRc = ObjEnum_Next(pEnum, 1, (void **)&pEntry, &count);
                    if (ERESULT_FAILED(eRc)) {
                        break;
                    }
                    BREAK_NULL(pEntry);
                    DirEntry_Complete(pEntry);
                    fprintf(
                            stderr,
                            "%2d name: %-25s  type: %2d  gen: %d\n",
                            i,
                            Path_getData(DirEntry_getFullPath(pEntry)),
                            DirEntry_getType(pEntry),
                            DirEntry_getGenerationNumber(pEntry)
                    );
                    obj_Release(pWrkPath);
                    ++i;
                }
                obj_Release(pEnum);
                pEnum = OBJ_NIL;
            }
            obj_Release(pPath);
            pPath = OBJ_NIL;
        }

        obj_Release(pObj);
        pObj = OBJ_NIL;
    }
    free(pDir);
    pDir = NULL;

    fprintf(stderr, "...%s completed.\n\n\n\n", pTestName);
    return 1;
}



int         test_Dir_Glob01(
    const
    char        *pTestName
)
{
    DIR_DATA    *pObj = OBJ_NIL;
    ERESULT     eRc;
    PATH_DATA   *pPath;

    fprintf(stderr, "Performing: %s\n", pTestName);

    pPattern = NULL;
    pDir = TEST_FILES_DIR "/";
    count = 1;
    pObj = Dir_New( );
    XCTAssertFalse( (OBJ_NIL == pObj) );
    if (pObj) {

        obj_TraceSet(pObj, true);
        count = 1;
        pPath = Path_NewA(pDir);
        eRc = Dir_GlobMatch(pObj, pPath, "*.txt", false, (void *)&globScanner, NULL, NULL);
        obj_Release(pPath);
        pPath = OBJ_NIL;
        // Count will be 1 more than what was found.
        fprintf(stderr, "%s Count: %d\n", pDir, count);
        XCTAssertTrue( (22 == count) );


        obj_Release(pObj);
        pObj = OBJ_NIL;
    }

    fprintf(stderr, "...%s completed.\n\n\n\n", pTestName);
    return 1;
}



int         test_Dir_Glob02(
    const
    char        *pTestName
)
{
    DIR_DATA    *pObj = OBJ_NIL;
    ERESULT     eRc;
    PATH_DATA   *pPath;

    fprintf(stderr, "Performing: %s\n", pTestName);

    pPattern = NULL;
    pDir = TEST_FILES_DIR;
    count = 1;
    pObj = Dir_New( );
    XCTAssertFalse( (OBJ_NIL == pObj) );
    if (pObj) {

        obj_TraceSet(pObj, true);
        count = 1;
        pPath = Path_NewA(pDir);
        eRc = Dir_GlobMatch(pObj, pPath, "*.txt", true, (void *)&globScanner, NULL, NULL);
        obj_Release(pPath);
        pPath = OBJ_NIL;
        // Count will be 1 more than what was found.
        fprintf(stderr, "%s Count: %d\n", pDir, count);
        XCTAssertTrue( (25 == count) );


        obj_Release(pObj);
        pObj = OBJ_NIL;
    }

    fprintf(stderr, "...%s completed.\n\n\n\n", pTestName);
    return 1;
}



int         test_Dir_Search01(
    const
    char        *pTestName
)
{
    DIR_DATA    *pObj = OBJ_NIL;
    ERESULT     eRc;
    PATH_DATA   *pPath;
    DIRENTRY_DATA *pEntry = OBJ_NIL;

    fprintf(stderr, "Performing: %s\n", pTestName);

    pPattern = NULL;
    pDir = TEST_FILES_DIR;
    count = 1;
    pObj = Dir_New( );
    XCTAssertFalse( (OBJ_NIL == pObj) );
    if (pObj) {

        obj_TraceSet(pObj, true);

        pEntry = Dir_SearchList(pObj, ".:/usr:/usr/bin", "write");
        XCTAssertFalse( (OBJ_NIL == pEntry) );
        pPath = DirEntry_getFullPath(pEntry);
        XCTAssertFalse( (OBJ_NIL == pPath) );
        XCTAssertTrue( (0 == strcmp("/usr/bin/write", Path_getData(pPath))) );
        obj_Release(pEntry);
        pEntry = OBJ_NIL;

        obj_Release(pObj);
        pObj = OBJ_NIL;
    }

    fprintf(stderr, "...%s completed.\n\n\n\n", pTestName);
    return 1;
}




TINYTEST_START_SUITE(test_Dir);
    TINYTEST_ADD_TEST(test_Dir_Search01,setUp,tearDown);
    TINYTEST_ADD_TEST(test_Dir_Glob02,setUp,tearDown);
    TINYTEST_ADD_TEST(test_Dir_Glob01,setUp,tearDown);
    TINYTEST_ADD_TEST(test_Dir_Enum02,setUp,tearDown);
    TINYTEST_ADD_TEST(test_Dir_Enum01,setUp,tearDown);
    TINYTEST_ADD_TEST(test_Dir_Scan03,setUp,tearDown);
    TINYTEST_ADD_TEST(test_Dir_Scan02,setUp,tearDown);
    TINYTEST_ADD_TEST(test_Dir_Scan01,setUp,tearDown);
    TINYTEST_ADD_TEST(test_Dir_Test01,setUp,tearDown);
    //TINYTEST_ADD_TEST(test_Dir_Copy01,setUp,tearDown);
    TINYTEST_ADD_TEST(test_Dir_OpenClose,setUp,tearDown);
TINYTEST_END_SUITE();

TINYTEST_MAIN_SINGLE_SUITE(test_Dir);





