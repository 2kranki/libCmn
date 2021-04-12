// vi:nu:et:sts=4 ts=4 sw=4
/*
 *  Generated 07/26/2020 08:55:08
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
#include    <trace.h>
#include    <SQLite_internal.h>
#ifdef  SQLITE_JSON_SUPPORT
#   include    <SrcErrors.h>
#   include    <szTbl.h>
#endif



// int (*pCallback)(void*,int,char**,char**)
static
int             SQLite_dump_callback (
    void            *pData,
    int             numCols,
    char            **pColText,
    char            **pColName
)
{
    //SQLITE_DATA     *this = pData;
    uint32_t        i;

    for (i=0; i<numCols; ++i) {
        fprintf(stderr, "\t%15s: %s\n", pColName[i], pColText[i]);
    }

    return SQLITE_OK;
}


// int (*pCallback)(void*,int,char**,char**)
static
int             SQLite_table_callback (
    void            *pData,
    int             numCols,
    char            **pColText,
    char            **pColName
)
{
    //SQLITE_DATA     *this = pData;
    int             i;
    bool            fDisplay = false;
    const
    char            *pName = NULL;
    const
    char            *pTblName = NULL;
    bool            fSqliteName = false;

    // The sqlite_master.tbl_name column holds the name of a table or view that the
    // object is associated with. For a table or view, the tbl_name column is a copy
    // of the name column. For an index, the tbl_name is the name of the table that
    // is indexed. For a trigger, the tbl_name column stores the name of the table or
    // view that causes the trigger to fire.

    for (i=0; i<numCols; ++i) {
        if (((strcmp(pColName[i], "type") == 0) && (strcmp(pColText[i], "table") == 0))) {
            fDisplay = true;
        }
        if ((strcmp(pColName[i], "name") == 0) && (strncmp(pColText[i], "sqlite_", 7) == 0))
            fSqliteName = true;
        if (strcmp(pColName[i], "name") == 0) {
            pName = pColText[i];
        }
        if (strcmp(pColName[i], "tbl_name") == 0) {
            pTblName = pColText[i];
        }
    }
    if (fDisplay) {
        if (pName && !fSqliteName)
            fprintf(stderr, "\tName: %s\n", pName);
        if (pTblName && !fSqliteName)
            fprintf(stderr, "\tTbl_Name: %s\n", pTblName);
    }

    return SQLITE_OK;
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

#ifdef  SQLITE_JSON_SUPPORT
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
                "Leaked memory areas were found!\n\n\n\n\n"
        );
        exitCode = 4;
        return 0;
    }
    mem_Release( );
    
    return 1; 
}






int             test_SQLite_OpenClose (
    const
    char            *pTestName
)
{
    ERESULT         eRc = ERESULT_SUCCESS;
    SQLITE_DATA       *pObj = OBJ_NIL;
    bool            fRc;
   
    fprintf(stderr, "Performing: %s\n", pTestName);

    pObj = SQLite_Alloc( );
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    pObj = SQLite_Init( pObj );
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    if (pObj) {

        //obj_TraceSet(pObj, true);       
        fRc = obj_IsKindOf(pObj, OBJ_IDENT_SQLITE);
        TINYTEST_TRUE( (fRc) );
        
        // Test something.
        TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );

        obj_Release(pObj);
        pObj = OBJ_NIL;
    }

    fprintf(stderr, "...%s completed.\n\n\n", pTestName);
    return 1;
}



int             test_SQLite_Copy01 (
    const
    char            *pTestName
)
{
    ERESULT         eRc = ERESULT_SUCCESS;
    SQLITE_DATA       *pObj1 = OBJ_NIL;
    SQLITE_DATA       *pObj2 = OBJ_NIL;
    bool            fRc;
#if defined(SQLITE_JSON_SUPPORT) && defined(XYZZY)
    ASTR_DATA       *pStr = OBJ_NIL;
#endif
   
    fprintf(stderr, "Performing: %s\n", pTestName);

    pObj1 = SQLite_New( );
    TINYTEST_FALSE( (OBJ_NIL == pObj1) );
    if (pObj1) {

        //obj_TraceSet(pObj1, true);       
        fRc = obj_IsKindOf(pObj1, OBJ_IDENT_SQLITE);
        TINYTEST_TRUE( (fRc) );
        
        // Test assign.
        pObj2 = SQLite_New();
        TINYTEST_FALSE( (OBJ_NIL == pObj2) );
        eRc = SQLite_Assign(pObj1, pObj2);
        TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );

        fRc = obj_IsKindOf(pObj2, OBJ_IDENT_SQLITE);
        TINYTEST_TRUE( (fRc) );
        //eRc = SQLite_Compare(pObj1, pObj2);
        //TINYTEST_TRUE( (0 == eRc) );
        //TODO: Add More tests here!

        obj_Release(pObj2);
        pObj2 = OBJ_NIL;

        // Test copy.
        pObj2 = SQLite_Copy(pObj1);
        TINYTEST_FALSE( (OBJ_NIL == pObj2) );

        fRc = obj_IsKindOf(pObj2, OBJ_IDENT_SQLITE);
        TINYTEST_TRUE( (fRc) );
        //eRc = SQLite_Compare(pObj1, pObj2);
        //TINYTEST_TRUE( (0 == eRc) );
        //TODO: Add More tests here!

        obj_Release(pObj2);
        pObj2 = OBJ_NIL;

        // Test json support.
#if defined(SQLITE_JSON_SUPPORT) && defined(XYZZY)
        pStr = SQLite_ToJson(pObj1);
        TINYTEST_FALSE( (OBJ_NIL == pStr) );
        fprintf(stderr, "JSON: %s\n", AStr_getData(pStr));
        pObj2 = SQLite_NewFromJsonString(pStr);
        TINYTEST_FALSE( (OBJ_NIL == pObj2) );
        fRc = obj_IsKindOf(pObj2, OBJ_IDENT_SQLITE);
        TINYTEST_TRUE( (fRc) );
        obj_Release(pStr);
        pStr = OBJ_NIL;
        //eRc = SQLite_Compare(pObj1, pObj2);
        //TINYTEST_TRUE( (0 == eRc) );

        obj_Release(pObj2);
        pObj2 = OBJ_NIL;
#endif

        obj_Release(pObj1);
        pObj1 = OBJ_NIL;
    }

    fprintf(stderr, "...%s completed.\n\n\n", pTestName);
    return 1;
}



int             test_SQLite_Test01 (
    const
    char            *pTestName
)
{
    ERESULT         eRc = ERESULT_SUCCESS;
    SQLITE_DATA     *pObj = OBJ_NIL;
    bool            fRc;
    const
    char            *pDatabasePath = TEST_FILES_DIR "/chinook.db";
    PATH_DATA       *pPath = OBJ_NIL;
    const
    char            *pSqlA = NULL;

    fprintf(stderr, "Performing: %s\n", pTestName);

    pPath = Path_NewA(pDatabasePath);
    TINYTEST_FALSE( (OBJ_NIL == pPath) );
    eRc = Path_Clean(pPath);
    TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );

    pObj = SQLite_NewPath(pPath);
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    if (pObj) {

        //obj_TraceSet(pObj, true);
        fRc = obj_IsKindOf(pObj, OBJ_IDENT_SQLITE);
        TINYTEST_TRUE( (fRc) );
        //TINYTEST_TRUE( (ERESULT_OK(eRc)) );
        
        pSqlA = "SELECT * FROM sqlite_master;";
        fprintf(stderr, "==> SQL: %s\n", pSqlA);
        eRc = SQLite_Exec(pObj, SQLite_dump_callback, NULL, pSqlA);
        TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );

        pSqlA = "SELECT * FROM sqlite_master;";
        fprintf(stderr, "==> TABLE SQL: %s\n", pSqlA);
        eRc = SQLite_Exec(pObj, SQLite_table_callback, NULL, pSqlA);
        TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );

        {
            ASTR_DATA       *pStr = SQLite_ToDebugString(pObj, 0);
            if (pStr) {
                fprintf(stderr, "Debug: %s\n", AStr_getData(pStr));
                obj_Release(pStr);
                pStr = OBJ_NIL;
            }
        }

        obj_Release(pObj);
        pObj = OBJ_NIL;
    }

    obj_Release(pPath);
    pPath = OBJ_NIL;

    fprintf(stderr, "...%s completed.\n\n\n", pTestName);
    return 1;
}



int             test_SQLite_Table01 (
    const
    char            *pTestName
)
{
    ERESULT         eRc = ERESULT_SUCCESS;
    SQLITE_DATA     *pObj = OBJ_NIL;
    bool            fRc;
    const
    char            *pDatabasePath = TEST_FILES_DIR "/chinook.db";
    PATH_DATA       *pPath = OBJ_NIL;
    ASTRCARRAY_DATA *pArray = OBJ_NIL;
    int             i;
    ASTRC_DATA      *pStr = OBJ_NIL;

    fprintf(stderr, "Performing: %s\n", pTestName);

    pPath = Path_NewA(pDatabasePath);
    TINYTEST_FALSE( (OBJ_NIL == pPath) );
    eRc = Path_Clean(pPath);
    TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );

    pObj = SQLite_NewPath(pPath);
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    if (pObj) {

        //obj_TraceSet(pObj, true);
        fRc = obj_IsKindOf(pObj, OBJ_IDENT_SQLITE);
        TINYTEST_TRUE( (fRc) );
        //TINYTEST_TRUE( (ERESULT_OK(eRc)) );

        pArray = SQLite_TableNames(pObj);
        TINYTEST_FALSE( (OBJ_NIL == pArray) );
        fprintf(stderr, "Array Size: %d\n", AStrCArray_getSize(pArray));
        TINYTEST_TRUE( (11 == AStrCArray_getSize(pArray)) );
        for (i=0; i<11; ++i) {
            pStr = AStrCArray_Get(pArray, i);
            if (pStr) {
                fprintf(stderr, "\t%s\n", AStrC_getData(pStr));
            }
        }
        obj_Release(pArray);
        pArray = OBJ_NIL;

        {
            ASTR_DATA       *pStr = SQLite_ToDebugString(pObj, 0);
            if (pStr) {
                fprintf(stderr, "Debug: %s\n", AStr_getData(pStr));
                obj_Release(pStr);
                pStr = OBJ_NIL;
            }
        }

        obj_Release(pObj);
        pObj = OBJ_NIL;
    }

    obj_Release(pPath);
    pPath = OBJ_NIL;

    fprintf(stderr, "...%s completed.\n\n\n", pTestName);
    return 1;
}




TINYTEST_START_SUITE(test_SQLite);
    TINYTEST_ADD_TEST(test_SQLite_Table01,setUp,tearDown);
    TINYTEST_ADD_TEST(test_SQLite_Test01,setUp,tearDown);
    //TINYTEST_ADD_TEST(test_SQLite_Copy01,setUp,tearDown);
    TINYTEST_ADD_TEST(test_SQLite_OpenClose,setUp,tearDown);
TINYTEST_END_SUITE();

TINYTEST_MAIN_SINGLE_SUITE(test_SQLite);





