// vi:nu:et:sts=4 ts=4 sw=4
/*
 *	Generated 12/16/2019 13:08:24
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
#include    <NodeEnum_internal.h>


static
char            *pStringTable[] = {
    "now",
    "before",
    "after",
    "tomorrow",
    "today",
    "someday"
};
static
int             cStringTable = 6;





int             setUp(
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


int             tearDown(
    const
    char            *pTestName
)
{
    // Put teardown code here. This method is called after the invocation of each
    // test method in the class.

    
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






int             test_NodeEnum_OpenClose(
    const
    char            *pTestName
)
{
    ERESULT         eRc = ERESULT_SUCCESS;
    NODEENUM_DATA	*pObj = OBJ_NIL;
    bool            fRc;
   
    fprintf(stderr, "Performing: %s\n", pTestName);

    pObj = NodeEnum_Alloc( );
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    pObj = NodeEnum_Init( pObj );
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    if (pObj) {

        fRc = obj_IsKindOf(pObj, OBJ_IDENT_OBJENUM);
        TINYTEST_TRUE( (fRc) );

        // Test something.
        TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );

        obj_Release(pObj);
        pObj = OBJ_NIL;
    }

    fprintf(stderr, "...%s completed.\n\n", pTestName);
    return 1;
}



int         test_NodeEnum_Test01(
    const
    char        *pTestName
)
{
    NODEENUM_DATA   *pObj = OBJ_NIL;
    NODE_DATA       *pNode = OBJ_NIL;
    ERESULT         eRc;
    uint32_t        i;
    
    fprintf(stderr, "Performing: %s\n", pTestName);
    
    pObj = NodeEnum_Alloc( );
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    pObj = NodeEnum_Init( pObj );
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    if (pObj) {
        
        fprintf(stderr, "\tAppending data:\n");
        for(i=0; i<cStringTable; ++i) {
            pNode = Node_NewWithUTF8AndClass(0, pStringTable[i], OBJ_NIL);
            if (pNode) {
                eRc = NodeEnum_AppendObj(pObj, pNode);
                TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );
                fprintf(stderr, "\t%2d - %s\n", i, pStringTable[i]);
                obj_Release(pNode);
                pNode = OBJ_NIL;
            }
        }
        
        fprintf(stderr, "\tEnumerate data:\n");
        i = 0;
        for (;;) {
            char        *pStrA;
            eRc = NodeEnum_Next(pObj, 1, (OBJ_ID *)&pNode, &i);
            if (ERESULT_FAILED(eRc)) {
                break;
            }
            if (pNode) {
                pStrA = Node_getNameUTF8(pNode);
                fprintf(stderr, "\t%2d - %s\n", i, pStrA);
                mem_Free(pStrA);
                pStrA = NULL;
            }
            ++i;
        }
        
        
        obj_Release(pObj);
        pObj = OBJ_NIL;
    }
    
    fprintf(stderr, "...%s completed.\n", pTestName);
    return 1;
}




TINYTEST_START_SUITE(test_NodeEnum);
    TINYTEST_ADD_TEST(test_NodeEnum_Test01,setUp,tearDown);
    TINYTEST_ADD_TEST(test_NodeEnum_OpenClose,setUp,tearDown);
TINYTEST_END_SUITE();

TINYTEST_MAIN_SINGLE_SUITE(test_NodeEnum);





