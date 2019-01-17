/*
 *	Generated 01/12/2019 14:04:44
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
#include    <lru.h>
#include    <memFile.h>
#include    <trace.h>
#include    <bpt32_internal.h>



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






int             test_bpt32_OpenClose(
    const
    char            *pTestName
)
{
    ERESULT         eRc = ERESULT_SUCCESS;
    BPT32_DATA	    *pObj = OBJ_NIL;
   
    fprintf(stderr, "Performing: %s\n", pTestName);

    pObj = bpt32_Alloc( );
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    pObj = bpt32_Init( pObj );
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



int             test_bpt32_Write01(
    const
    char            *pTestName
)
{
    ERESULT         eRc = ERESULT_SUCCESS;
    BPT32_DATA      *pObj = OBJ_NIL;
    MEMFILE_DATA    *pFile = OBJ_NIL;
    uint32_t        data1 = 0;
    uint32_t        data2 = 0;
    uint32_t        index1 = 0;
    uint32_t        index2 = 0;
    uint32_t        i = 0;

    fprintf(stderr, "Performing: %s\n", pTestName);
    
    pFile = memFile_New( );
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    eRc = memFile_SetupSizes(pFile, 64);
    TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );

    pObj = bpt32_New( );
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    if (pObj) {
        
        bpt32_setReadWrite(
                           pObj,
                           (void *)memFile_Read,
                           (void *)memFile_Write,
                           pFile
        );
        
        eRc = bpt32_SetupSizes(pObj, 64, 4);
        TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );
        
        eRc = bpt32_Add(pObj, 1, &data1);
        TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );

        for (i=0; i<5; ++i) {
            eRc = ERESULT_OUT_OF_MEMORY;
        }
        
        obj_Release(pObj);
        pObj = OBJ_NIL;
    }
    
    obj_Release(pFile);
    pFile = OBJ_NIL;

    fprintf(stderr, "...%s completed.\n\n", pTestName);
    return 1;
}




TINYTEST_START_SUITE(test_bpt32);
    TINYTEST_ADD_TEST(test_bpt32_OpenClose,setUp,tearDown);
TINYTEST_END_SUITE();

TINYTEST_MAIN_SINGLE_SUITE(test_bpt32);





