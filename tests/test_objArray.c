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
#include    <objArray_internal.h>



static
char	*stringTable[] = {
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
int             num = 7;



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
    mem_Dump( );
    mem_Release( );
    
    return 1; 
}






int         test_objArray_OpenClose(
    const
    char        *pTestName
)
{
    OBJARRAY_DATA	*pObj = OBJ_NIL;
    ERESULT         eRc;
    uint32_t        i;
    uint32_t        size;
    ASTR_DATA       *pStr;
   
    fprintf(stderr, "Performing: %s\n", pTestName);
    
    pObj = objArray_Alloc( );
    XCTAssertFalse( (OBJ_NIL == pObj) );
    pObj = objArray_Init( pObj );
    XCTAssertFalse( (OBJ_NIL == pObj) );
    if (pObj) {
        
        for (i=0; i<num; ++i) {
            pStr = AStr_NewA(stringTable[i]);
            XCTAssertFalse( (OBJ_NIL == pStr) );
            if (pStr) {
                eRc = objArray_AppendObj(pObj, pStr, NULL);
                XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
                obj_Release(pStr);
                pStr = OBJ_NIL;
                size = objArray_getSize(pObj);
            }
        }
        fprintf(stderr, "\tcount = %d\n", objArray_getSize(pObj));
        XCTAssertTrue( (num == objArray_getSize(pObj)) );

        for (i=0; i<num; ++i) {
            pStr = objArray_Get(pObj, i+1);
            fprintf(stderr, "%d - %s\n", i, AStr_getData(pStr));
            XCTAssertFalse( (OBJ_NIL == pStr) );
            XCTAssertTrue( (0 == strcmp((char *)AStr_getData(pStr), stringTable[i])) );
        }
        
        eRc = objArray_SortAscending(pObj, (OBJ_COMPARE)&AStr_Compare);
        fprintf(stderr, "\n\tSorted Array:\n");
        for (i=0; i<num; ++i) {
            pStr = objArray_Get(pObj, i+1);
            fprintf( stderr, "%d - %s\n", i, AStr_getData(pStr) );
        }
        
        obj_Release(pObj);
        pObj = OBJ_NIL;
    }

    fprintf(stderr, "...%s completed.\n", pTestName);
    return 1;
}



int         test_objArray_GetPut01(
    const
    char        *pTestName
)
{
    OBJARRAY_DATA    *pObj = OBJ_NIL;
    ERESULT         eRc;
    uint32_t        i;
    uint32_t        size;
    ASTR_DATA       *pStr;
    
    fprintf(stderr, "Performing: %s\n", pTestName);
    
    pObj = objArray_Alloc( );
    XCTAssertFalse( (OBJ_NIL == pObj) );
    pObj = objArray_Init( pObj );
    XCTAssertFalse( (OBJ_NIL == pObj) );
    if (pObj) {
        
        for (i=0; i<num; ++i) {
            pStr = AStr_NewA(stringTable[i]);
            XCTAssertFalse( (OBJ_NIL == pStr) );
            if (pStr) {
                eRc = objArray_Put(pObj, (i+1), pStr);
                XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
                obj_Release(pStr);
                pStr = OBJ_NIL;
                size = objArray_getSize(pObj);
                XCTAssertTrue( (size == (i + 1)) );
            }
        }
        fprintf(stderr, "\tcount = %d\n", objArray_getSize(pObj));
        XCTAssertTrue( (num == objArray_getSize(pObj)) );
        
        for (i=0; i<num; ++i) {
            pStr = objArray_Get(pObj, i+1);
            fprintf(stderr, "%d - %s\n", i, AStr_getData(pStr));
            XCTAssertFalse( (OBJ_NIL == pStr) );
            XCTAssertTrue( (0 == strcmp((char *)AStr_getData(pStr), stringTable[i])) );
        }
        
        eRc = objArray_SortAscending(pObj, (OBJ_COMPARE)&AStr_Compare);
        fprintf(stderr, "\n\tSorted Array:\n");
        for (i=0; i<num; ++i) {
            pStr = objArray_Get(pObj, i+1);
            fprintf( stderr, "%d - %s\n", i, AStr_getData(pStr) );
        }
        
        obj_Release(pObj);
        pObj = OBJ_NIL;
    }
    
    fprintf(stderr, "...%s completed.\n", pTestName);
    return 1;
}




TINYTEST_START_SUITE(test_objArray);
    TINYTEST_ADD_TEST(test_objArray_GetPut01,setUp,tearDown);
    TINYTEST_ADD_TEST(test_objArray_OpenClose,setUp,tearDown);
TINYTEST_END_SUITE();

TINYTEST_MAIN_SINGLE_SUITE(test_objArray);





