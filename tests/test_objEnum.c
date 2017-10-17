/*
 *	Generated 10/15/2017 09:38:35
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
#include    <objEnum_internal.h>



static
char    *pStringTable[] = {
    "now",
    "before",
    "after",
    "tomorrow",
    "today",
    "someday"
};
static
int             cStringTable = 6;



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






int         test_objEnum_OpenClose(
    const
    char        *pTestName
)
{
    OBJENUM_DATA	*pObj = OBJ_NIL;
    ASTR_DATA       *pStr = OBJ_NIL;
    ERESULT         eRc;
    uint32_t        i;
    uint32_t        j = 0;

    fprintf(stderr, "Performing: %s\n", pTestName);

    pObj = objEnum_Alloc( );
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    pObj = objEnum_Init( pObj );
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    if (pObj) {

        fprintf(stderr, "\tAppending data:\n");
        for(i=0; i<cStringTable; ++i) {
            pStr = AStr_NewA(pStringTable[i]);
            if (pStr) {
                eRc = objEnum_Append(pObj, pStr);
                TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );
                fprintf(stderr, "\t%2d - %s\n",
                        objArray_getSize(pObj->pArray),
                        AStr_getData(pStr)
                );
                obj_Release(pStr);
                pStr = OBJ_NIL;
            }
        }
        
        fprintf(stderr, "\tEnumerate data:\n");
        for (;;) {
            eRc = objEnum_Next(pObj, 1, (OBJ_ID *)&pStr, &i);
            if (ERESULT_FAILED(eRc)) {
                break;
            }
            fprintf(stderr, "\t%2d - %s\n", pObj->current, AStr_getData(pStr));
        }


        obj_Release(pObj);
        pObj = OBJ_NIL;
    }

    fprintf(stderr, "...%s completed.\n", pTestName);
    return 1;
}




TINYTEST_START_SUITE(test_objEnum);
    TINYTEST_ADD_TEST(test_objEnum_OpenClose,setUp,tearDown);
TINYTEST_END_SUITE();

TINYTEST_MAIN_SINGLE_SUITE(test_objEnum);





