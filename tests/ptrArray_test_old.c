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
#include    <ptrArray_internal.h>



static
char	*stringTable[] = {
    "now",
    "before",
    "after",
    "tomorrow",
    "today",
    "someday",
};
static
int             num = 6;




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




int    	compareStrings(
    const
    char        *pStr1,
    const
    char        *pStr2
)
{
    int         cmp = strcmp(pStr1, pStr2);
    return cmp;
}






int         test_ptrArray_OpenClose(
    const
    char            *pTestName
)
{
    PTRARRAY_DATA   *pObj = OBJ_NIL;
    ERESULT         eRc;
    uint32_t        i;
    uint32_t        index;
    const
    char            *pStr;
   
    fprintf(stderr, "Performing: %s\n", pTestName);
    pObj = ptrArray_Alloc( );
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    pObj = ptrArray_Init(pObj);
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    if (pObj) {

        for (i=0; i<num; ++i) {
            eRc = ptrArray_AppendData(pObj, stringTable[i], &index);
            XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
            XCTAssertTrue( (index == (i + 1)) );
        }
        
        for (i=0; i<ptrArray_getSize(pObj); ++i) {
            pStr = ptrArray_GetData(pObj, i+1);
            XCTAssertFalse( (NULL == pStr) );
            XCTAssertTrue( (0 == strcmp(pStr, stringTable[i])) );
        }
        
        eRc = ptrArray_Sort(pObj, (PTR_COMPARE)&compareStrings);
        
        fprintf(stderr, "\n\nSorted Array:\n");
        for (i=0; i<ptrArray_getSize(pObj); ++i) {
            pStr = ptrArray_GetData(pObj, i+1);
            fprintf(stderr, "%d - %s\n", i+1, pStr);
        }
        fprintf(stderr, "End of Sorted Array\n\n");
        
        pStr = (const char *)ptrArray_Delete(pObj, 2);
        fprintf(stderr, "Deleted: '%s'\nArray After Delete:\n", pStr);
        for (i=0; i<ptrArray_getSize(pObj); ++i) {
            pStr = ptrArray_GetData(pObj, i+1);
            fprintf(stderr, "%d - %s\n", i+1, pStr);
        }
        fprintf(stderr, "End of Array After Delete\n\n");
        
        obj_Release(pObj);
        pObj = OBJ_NIL;
    }

    fprintf(stderr, "...%s completed.\n", pTestName);
    return 1;
}




TINYTEST_START_SUITE(test_ptrArray);
  TINYTEST_ADD_TEST(test_ptrArray_OpenClose,setUp,tearDown);
TINYTEST_END_SUITE();

TINYTEST_MAIN_SINGLE_SUITE(test_ptrArray);





