/*
 *	Generated 01/16/2019 16:27:57
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
#include    <memrrds_internal.h>



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






int             test_memrrds_OpenClose(
    const
    char            *pTestName
)
{
    ERESULT         eRc = ERESULT_SUCCESS;
    MEMRRDS_DATA	    *pObj = OBJ_NIL;
   
    fprintf(stderr, "Performing: %s\n", pTestName);

    pObj = memrrds_Alloc( );
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    pObj = memrrds_Init( pObj );
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    if (pObj) {

        //obj_TraceSet(pObj, true);       
        
        // Test something.
        TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );

        obj_Release(pObj);
        pObj = OBJ_NIL;
    }

    fprintf(stderr, "...%s completed.\n\n", pTestName);
    return 1;
}



int             test_memrrds_Insert01(
    const
    char            *pTestName
)
{
    ERESULT         eRc = ERESULT_SUCCESS;
    MEMRRDS_DATA    *pObj = OBJ_NIL;
    //uint32_t        i;
    //uint32_t        index;
    uint8_t         data[8];
    uint8_t         *pData = data;
    
    fprintf(stderr, "Performing: %s\n", pTestName);
    
    pObj = memrrds_Alloc( );
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    pObj = memrrds_Init( pObj );
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    if (pObj) {
        
        //obj_TraceSet(pObj, true);
        eRc = memrrds_SetupSizes(pObj, 8);
        TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );
        
        str_Copy((char *)data, sizeof(data), "2222222");
        eRc = memrrds_Write(pObj, 2, pData);
        TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );

        str_Copy((char *)data, sizeof(data), "0000000");
        pData = data;
        eRc = memrrds_Read(pObj, 2, pData);
        TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );
        TINYTEST_TRUE((0 == strcmp((char *)pData, "2222222")));
        
        obj_Release(pObj);
        pObj = OBJ_NIL;
    }
    
    fprintf(stderr, "...%s completed.\n\n", pTestName);
    return 1;
}




TINYTEST_START_SUITE(test_memrrds);
    TINYTEST_ADD_TEST(test_memrrds_Insert01,setUp,tearDown);
    TINYTEST_ADD_TEST(test_memrrds_OpenClose,setUp,tearDown);
TINYTEST_END_SUITE();

TINYTEST_MAIN_SINGLE_SUITE(test_memrrds);





