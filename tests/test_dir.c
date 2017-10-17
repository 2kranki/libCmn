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
#include    <dir_internal.h>
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
bool            scanner( void *pData, DIRENTRY_DATA *pEntry)
{
    ERESULT         eRc;
    PATH_DATA       *pPath;
    char            *pStr;
    struct stat     statbuf;
    
    if (pPattern) {
        eRc = dirEntry_MatchA(pEntry, pPattern);
        if (ERESULT_FAILED(eRc)) {
            return true;
        }
    }
    pPath = path_Copy(dirEntry_getDir(pEntry));
    path_AppendFileName(pPath, dirEntry_getName(pEntry));
    pStr = AStr_CStringA((ASTR_DATA *)pPath,NULL);
    
    fprintf(    stderr,
                "\t%2d name: %s  type: %d\n",
                count++,
                pStr,
                dirEntry_getType(pEntry)
    );
    
    if (-1 == stat(pStr,&statbuf))
        fprintf(stderr, "\tCould not stat: %s\n", pStr);
    else {
        //fprintf(stderr, "\tname: (%d)%s\n", statbuf->d_namlen, pDirent->d_name);
    }
    
    mem_Free(pStr);
    pStr = NULL;
    obj_Release(pPath);
    pPath = OBJ_NIL;

    return true;
}




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

    pPattern = NULL;
    trace_SharedReset( ); 
    mem_Dump( );
    mem_Release( );
    
    return 1; 
}






int         test_dir_OpenClose(
    const
    char        *pTestName
)
{
    DIR_DATA	*pObj = OBJ_NIL;
   
    fprintf(stderr, "Performing: %s\n", pTestName);
    
    pObj = dir_Alloc( );
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    pObj = dir_Init( pObj );
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    if (pObj) {

        // Test something.

        obj_Release(pObj);
        pObj = OBJ_NIL;
    }

    fprintf(stderr, "...%s completed.\n", pTestName);
    return 1;
}



int         test_dir_Scan01(
    const
    char        *pTestName
)
{
    DIR_DATA	*pObj = OBJ_NIL;
    ERESULT     eRc;
    PATH_DATA   *pPath;
    
    fprintf(stderr, "Performing: %s\n", pTestName);
    
    //pPattern = "*.wav";
    pDir = getenv("HOME");
    pObj = dir_Alloc( );
    XCTAssertFalse( (OBJ_NIL == pObj) );
    pObj = dir_Init( pObj );
    XCTAssertFalse( (OBJ_NIL == pObj) );
    if (pObj) {
        
        count = 1;
        pPath = path_NewA(pDir);
        eRc = dir_ScanDir(pObj, pPath, &scanner, NULL);
        obj_Release(pPath);
        pPath = OBJ_NIL;
        
        obj_Release(pObj);
        pObj = OBJ_NIL;
    }
    
    fprintf(stderr, "...%s completed.\n", pTestName);
    return 1;
}



int         test_dir_Scan02(
    const
    char        *pTestName
)
{
    DIR_DATA    *pObj = OBJ_NIL;
    ERESULT     eRc;
    PATH_DATA   *pPath;
    
    fprintf(stderr, "Performing: %s\n", pTestName);
    
    pPattern = "*.wav";
    pDir = getenv("HOME");
    pObj = dir_Alloc( );
    XCTAssertFalse( (OBJ_NIL == pObj) );
    pObj = dir_Init( pObj );
    XCTAssertFalse( (OBJ_NIL == pObj) );
    if (pObj) {
        
        count = 1;
        pPath = path_NewA(pDir);
        eRc = dir_ScanDir(pObj, pPath, &scanner, NULL);
        obj_Release(pPath);
        pPath = OBJ_NIL;
        
        obj_Release(pObj);
        pObj = OBJ_NIL;
    }
    
    fprintf(stderr, "...%s completed.\n", pTestName);
    return 1;
}



int         test_dir_Scan03(
    const
    char        *pTestName
)
{
    DIR_DATA    *pObj = OBJ_NIL;
    ERESULT     eRc;
    PATH_DATA   *pPath;
    
    fprintf(stderr, "Performing: %s\n", pTestName);
    
    pPattern = NULL;
    pDir = ".";
    pObj = dir_Alloc( );
    XCTAssertFalse( (OBJ_NIL == pObj) );
    pObj = dir_Init( pObj );
    XCTAssertFalse( (OBJ_NIL == pObj) );
    if (pObj) {
        
        count = 1;
        pPath = path_NewA(pDir);
        eRc = dir_ScanDir(pObj, pPath, &scanner, NULL);
        obj_Release(pPath);
        pPath = OBJ_NIL;
        
        obj_Release(pObj);
        pObj = OBJ_NIL;
    }
    
    fprintf(stderr, "...%s completed.\n", pTestName);
    return 1;
}



int         test_dir_Enum01(
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
    char            *pStrA = NULL;

    fprintf(stderr, "Performing: %s\n", pTestName);
    
    pDir = getenv("HOME");
    fprintf(stderr, "\tDir: %s\n", pDir);
    pObj = dir_Alloc( );
    XCTAssertFalse( (OBJ_NIL == pObj) );
    pObj = dir_Init( pObj );
    XCTAssertFalse( (OBJ_NIL == pObj) );
    if (pObj) {
        
        pPath = path_NewA(pDir);
        if (pPath) {
            pEnum = dir_EnumDir(pObj, pPath);
            if (pEnum) {
                i = 1;
                for (;;) {
                    eRc = objEnum_Next(pEnum, 1, (void **)&pEntry, &count);
                    if (ERESULT_FAILED(eRc)) {
                        break;
                    }
                    dirEntry_GetAllData(pEntry);
                    fprintf(
                            stderr,
                            "%2d name: %-25s  type: %2d  gen: %d\n",
                            i,
                            AStr_getData(dirEntry_getName(pEntry)),
                            dirEntry_getType(pEntry),
                            dirEntry_getGenerationNumber(pEntry)
                    );
                    mem_Free(pStrA);
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
    
    fprintf(stderr, "...%s completed.\n", pTestName);
    return 1;
}




TINYTEST_START_SUITE(test_dir);
    TINYTEST_ADD_TEST(test_dir_Enum01,setUp,tearDown);
    TINYTEST_ADD_TEST(test_dir_Scan03,setUp,tearDown);
    TINYTEST_ADD_TEST(test_dir_Scan02,setUp,tearDown);
    TINYTEST_ADD_TEST(test_dir_Scan01,setUp,tearDown);
    TINYTEST_ADD_TEST(test_dir_OpenClose,setUp,tearDown);
TINYTEST_END_SUITE();

TINYTEST_MAIN_SINGLE_SUITE(test_dir);





