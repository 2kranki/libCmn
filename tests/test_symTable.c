/*
 *	Generated 03/27/2017 21:41:31
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
#include    <symTable_internal.h>
#include    <trace.h>
#include    <szTbl.h>



static
char    *stringTable[] = {
    "now",
    "xray",
    "before",
    "after",
    "tomorrow",
    "today",
    "someday",
    NULL
};
static
int             cStringTable = 7;




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
    trace_SharedReset( ); 
    mem_Dump( );
    mem_Release( );
    
    return 1; 
}







int         test_symTable_OpenClose(
    const
    char        *test_name
)
{
    SYMTABLE_DATA	*pObj = OBJ_NIL;
   
    pObj = symTable_Alloc( );
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    pObj = symTable_Init(pObj, SYMTABLE_HASH_SIZE_XXXXXSMALL);
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    if (pObj) {

        // Test something.

        obj_Release(pObj);
        pObj = OBJ_NIL;
    }

    return 1;
}



int         test_symTable_General01(
    const
    char        *test_name
)
{
    SYMTABLE_DATA   *pObj = OBJ_NIL;
    OBJENUM_DATA    *pEnum = OBJ_NIL;
    ERESULT         eRc;
    uint32_t        i;
    uint32_t        size;
    ASTR_DATA       *pStr  = OBJ_NIL;
    ASTR_DATA       *pStrs[cStringTable];
    //ASTRC_DATA      *pStrC = OBJ_NIL;

    pObj = symTable_Alloc( );
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    pObj = symTable_Init(pObj, SYMTABLE_HASH_SIZE_XXXXXSMALL);
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    if (pObj) {
        
        for (i=0; i<cStringTable; ++i) {
            if (stringTable[i]) {
                pStr = AStr_NewA(stringTable[i]);
                TINYTEST_FALSE( (OBJ_NIL == pStr) );
                pStrs[i] = pStr;
                eRc = symTable_Add(pObj, pStr);
                TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );
                obj_Release(pStr);
                pStr = OBJ_NIL;
            }
        }
        size = symTable_getSize(pObj);
        TINYTEST_TRUE( (size == cStringTable) );
        
        for (i=0; i<cStringTable; ++i) {
            pStr = symTable_Find(pObj, pStrs[i]);
            TINYTEST_FALSE( (OBJ_NIL == pStr) );
            TINYTEST_TRUE( (pStr == pStrs[i]) );
        }
        
        pEnum = symTable_Enum(pObj);
        TINYTEST_FALSE( (OBJ_NIL == pEnum) );
        TINYTEST_TRUE( (cStringTable == objEnum_getSize(pEnum)) );
        
        fprintf(stderr, "\tEnumerate data:\n");
        for (i=0; ; ++i) {
            eRc = objEnum_Next(pEnum, 1, (OBJ_ID *)&pStr, &size);
            if (ERESULT_FAILED(eRc)) {
                break;
            }
            fprintf(stderr, "\t\t%2d - %s\n", i, AStr_getData(pStr));
        }
        
        obj_Release(pEnum);
        pEnum = OBJ_NIL;
        
        for (i=0; i<cStringTable; ++i) {
            obj_Release(pStrs[i]);
        }
        obj_Release(pObj);
        pObj = OBJ_NIL;
    }
    
    return 1;
}




TINYTEST_START_SUITE(test_symTable);
    TINYTEST_ADD_TEST(test_symTable_General01,setUp,tearDown);
    TINYTEST_ADD_TEST(test_symTable_OpenClose,setUp,tearDown);
TINYTEST_END_SUITE();

TINYTEST_MAIN_SINGLE_SUITE(test_symTable);





