// vi:nu:et:sts=4 ts=4 sw=4
/*
 *	Generated 02/02/2020 09:55:43
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
#include    <ObjHash_internal.h>
#ifdef  OBJHASH_JSON_SUPPORT
#   include    <SrcErrors.h>
#   include    <szTbl.h>
#endif


static
char    *stringTable[] = {
    "iryna",
    "rain",
#ifdef XYZZY
    "clouds",
    "sun",
    "now",
    "xray",
    "before",
    "after",
    "bob",
    "tomorrow",
    "today",
    "someday",
#endif
    NULL
};
static
int             cStringTable = (sizeof(stringTable) / sizeof(char *)) - 1;




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

#ifdef  OBJHASH_JSON_SUPPORT
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






int             test_ObjHash_OpenClose (
    const
    char            *pTestName
)
{
    ERESULT         eRc = ERESULT_SUCCESS;
    OBJHASH_DATA	    *pObj = OBJ_NIL;
    bool            fRc;
   
    fprintf(stderr, "Performing: %s\n", pTestName);

    pObj = ObjHash_Alloc( );
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    pObj = ObjHash_Init( pObj );
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    if (pObj) {

        //obj_TraceSet(pObj, true);       
        fRc = obj_IsKindOf(pObj, OBJ_IDENT_OBJHASH);
        TINYTEST_TRUE( (fRc) );
        
        // Test something.
        TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );

        obj_Release(pObj);
        pObj = OBJ_NIL;
    }

    fprintf(stderr, "...%s completed.\n\n\n", pTestName);
    return 1;
}



int             test_ObjHash_Copy01 (
    const
    char            *pTestName
)
{
    ERESULT         eRc = ERESULT_SUCCESS;
    OBJHASH_DATA	*pObj1 = OBJ_NIL;
    OBJHASH_DATA	*pObj2 = OBJ_NIL;
    bool            fRc;
    ASTR_DATA	    *pStr = OBJ_NIL;
    uint32_t        i;
    uint32_t        size;
    uint32_t        index;

    fprintf(stderr, "Performing: %s\n", pTestName);

    pObj1 = ObjHash_NewWithSize(OBJHASH_TABLE_SIZE_XXXXXSMALL);
    TINYTEST_FALSE( (OBJ_NIL == pObj1) );
    if (pObj1) {

        for (i=0; i<cStringTable; ++i) {
            if (stringTable[i]) {
                pStr = AStr_NewA(stringTable[i]);
                TINYTEST_FALSE( (OBJ_NIL == pStr) );
                index = 0;
                eRc = ObjHash_Add(pObj1, pStr, &index);
                TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );
                fprintf(stderr, "i=%d  index=%d  %s\n", i, index, stringTable[i]);
                TINYTEST_TRUE( (index == (i + 1)) );
                obj_Release(pStr);
                pStr = OBJ_NIL;
            }
        }
        size = ObjHash_getSize(pObj1);
        TINYTEST_TRUE( (size == cStringTable) );

        //obj_TraceSet(pObj1, true);
        fRc = obj_IsKindOf(pObj1, OBJ_IDENT_OBJHASH);
        TINYTEST_TRUE( (fRc) );
        
        // Test assign.
        pObj2 = ObjHash_New();
        TINYTEST_FALSE( (OBJ_NIL == pObj2) );
        eRc = ObjHash_Assign(pObj1, pObj2);
        TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );

        fRc = obj_IsKindOf(pObj2, OBJ_IDENT_OBJHASH);
        TINYTEST_TRUE( (fRc) );
        size = ObjHash_getSize(pObj2);
        TINYTEST_TRUE( (size == cStringTable) );

        obj_Release(pObj2);
        pObj2 = OBJ_NIL;

        // Test copy.
        pObj2 = ObjHash_Copy(pObj1);
        TINYTEST_FALSE( (OBJ_NIL == pObj2) );

        fRc = obj_IsKindOf(pObj2, OBJ_IDENT_OBJHASH);
        TINYTEST_TRUE( (fRc) );
        //TODO: Add More tests here!

        obj_Release(pObj2);
        pObj2 = OBJ_NIL;

        // Test json support.
#if defined(OBJHASH_JSON_SUPPORT)
        pStr = ObjHash_ToJson(pObj1);
        TINYTEST_FALSE( (OBJ_NIL == pStr) );
        fprintf(stderr, "JSON: %s\n", AStr_getData(pStr));
        pObj2 = ObjHash_NewFromJsonString(pStr);
        TINYTEST_FALSE( (OBJ_NIL == pObj2) );
        fRc = obj_IsKindOf(pObj2, OBJ_IDENT_OBJHASH);
        TINYTEST_TRUE( (fRc) );
        obj_Release(pStr);
        pStr = OBJ_NIL;
        size = ObjHash_getSize(pObj2);
        fprintf(stderr, "Obj2 Size: %d\n", size);
        TINYTEST_TRUE( (size == cStringTable) );

        obj_Release(pObj2);
        pObj2 = OBJ_NIL;
#endif

        obj_Release(pObj1);
        pObj1 = OBJ_NIL;
    }

    fprintf(stderr, "...%s completed.\n\n\n", pTestName);
    return 1;
}



int             test_ObjHash_Test01 (
    const
    char            *pTestName
)
{
    //ERESULT         eRc = ERESULT_SUCCESS;
    OBJHASH_DATA	    *pObj = OBJ_NIL;
    bool            fRc;
   
    fprintf(stderr, "Performing: %s\n", pTestName);

    pObj = ObjHash_New( );
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    if (pObj) {

        //obj_TraceSet(pObj, true);       
        fRc = obj_IsKindOf(pObj, OBJ_IDENT_OBJHASH);
        TINYTEST_TRUE( (fRc) );
        
        obj_Release(pObj);
        pObj = OBJ_NIL;
    }

    fprintf(stderr, "...%s completed.\n\n\n", pTestName);
    return 1;
}



int         test_ObjHash_Test02(
    const
    char        *pTestName
)
{
    OBJHASH_DATA    *pObj = OBJ_NIL;
    OBJENUM_DATA    *pEnum = OBJ_NIL;
    ERESULT         eRc;
    uint32_t        i;
    uint32_t        size;
    ASTR_DATA       *pStr  = OBJ_NIL;
    //ASTRC_DATA      *pStrC = OBJ_NIL;
    uint32_t        index;

    fprintf(stderr, "Performing: %s\n", pTestName);

    pObj = ObjHash_NewWithSize(OBJHASH_TABLE_SIZE_XSMALL);
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    if (pObj) {

        for (i=0; i<cStringTable; ++i) {
            if (stringTable[i]) {
                pStr = AStr_NewA(stringTable[i]);
                TINYTEST_FALSE( (OBJ_NIL == pStr) );
                index = 0;
                eRc = ObjHash_Add(pObj, pStr, &index);
                TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );
                fprintf(stderr, "i=%d  index=%d  %s\n", i, index, stringTable[i]);
                TINYTEST_TRUE( (index == (i + 1)) );
                obj_Release(pStr);
                pStr = OBJ_NIL;
            }
        }
        size = ObjHash_getSize(pObj);
        TINYTEST_TRUE( (size == cStringTable) );

        pStr = ObjHash_FindIndex(pObj, 1);
        TINYTEST_FALSE( (OBJ_NIL == pStr) );
        TINYTEST_TRUE( (0 == strcmp(AStr_getData(pStr), stringTable[0])) );
        pStr = ObjHash_FindIndex(pObj, cStringTable);
        TINYTEST_FALSE( (OBJ_NIL == pStr) );
        TINYTEST_TRUE( (0 == strcmp(AStr_getData(pStr), stringTable[cStringTable-1])) );
        pStr = OBJ_NIL;

        pEnum = ObjHash_Enum(pObj);
        TINYTEST_FALSE( (OBJ_NIL == pEnum) );
        TINYTEST_TRUE( (cStringTable == ObjEnum_getSize(pEnum)) );

        fprintf(stderr, "\tEnumerate data:\n");
        for (i=0; ; ++i) {
            eRc = ObjEnum_Next(pEnum, 1, (OBJ_ID *)&pStr, &size);
            if (ERESULT_FAILED(eRc)) {
                break;
            }
            fprintf(stderr, "\t\t%2d - %s\n", i, AStr_getData(pStr));
        }

        obj_Release(pEnum);
        pEnum = OBJ_NIL;

        obj_Release(pObj);
        pObj = OBJ_NIL;
    }

    fprintf(stderr, "...%s completed.\n\n", pTestName);
    return 1;
}




TINYTEST_START_SUITE(test_ObjHash);
    TINYTEST_ADD_TEST(test_ObjHash_Test02,setUp,tearDown);
    TINYTEST_ADD_TEST(test_ObjHash_Test01,setUp,tearDown);
    TINYTEST_ADD_TEST(test_ObjHash_Copy01,setUp,tearDown);
    TINYTEST_ADD_TEST(test_ObjHash_OpenClose,setUp,tearDown);
TINYTEST_END_SUITE();

TINYTEST_MAIN_SINGLE_SUITE(test_ObjHash);





