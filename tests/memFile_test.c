/*
 *	Generated 01/13/2019 15:55:16
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
#include    <str.h>
#include    <trace.h>
#include    <memFile_internal.h>



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






int             test_memFile_OpenClose(
    const
    char            *pTestName
)
{
    ERESULT         eRc = ERESULT_SUCCESS;
    MEMFILE_DATA	    *pObj = OBJ_NIL;
   
    fprintf(stderr, "Performing: %s\n", pTestName);

    pObj = memFile_Alloc( );
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    pObj = memFile_Init( pObj );
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



int             test_memFile_Create01(
    const
    char            *pTestName
)
{
    ERESULT         eRc = ERESULT_SUCCESS;
    MEMFILE_DATA    *pObj = OBJ_NIL;
    PATH_DATA       *pPath = OBJ_NIL;
    const
    char            *pPathA = "/tmp/testFile.temp.";
    DATETIME_DATA   *pTime = OBJ_NIL;
    ASTR_DATA       *pStr = OBJ_NIL;
    int64_t         fileSize = 0;
    //uint32_t        i;
    uint32_t        index;
    uint8_t         data[256];
    uint8_t         *pData = data;
    
    fprintf(stderr, "Performing: %s\n", pTestName);
    
    pTime = dateTime_NewCurrent();
    TINYTEST_FALSE( (OBJ_NIL == pTime) );
    pPath = path_NewA(pPathA);
    TINYTEST_FALSE( (OBJ_NIL == pPath) );
    pStr = dateTime_ToFileString(pTime);
    TINYTEST_FALSE( (OBJ_NIL == pTime) );
    path_AppendAStr(pPath, pStr);
    obj_Release(pStr);
    pStr = OBJ_NIL;
    path_AppendA(pPath, ".txt");
    fprintf(stderr, "\tPath = \"%s\"\n", path_getData(pPath));
    
    pObj = memFile_Alloc( );
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    pObj = memFile_Init( pObj );
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    if (pObj) {
        
        eRc = memFile_Create(pObj, pPath);
        TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );
        
        eRc =   memFile_Write(
                             pObj,
                             (uint32_t)(strlen(path_getData(pPath))+1),
                             path_getData(pPath)
                );
        TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );
        
        fileSize = memFile_Size(pObj);
        fprintf(
                stderr,
                "\tSize = %ld  fileio_Size=%lld\n",
                (strlen(path_getData(pPath))+1),
                fileSize
                );
        TINYTEST_TRUE( ((strlen(path_getData(pPath))+1) == fileSize) );
        
        eRc = memFile_Close(pObj, false);
        TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );
        
        fileSize = memFile_Size(pObj);
        TINYTEST_TRUE( (-1 == fileSize) );
        
        eRc = memFile_Open(pObj, pPath);
        TINYTEST_TRUE( (!ERESULT_FAILED(eRc)) );
        
        index = 0;
        eRc = memFile_Read(pObj, 256, data, &index);
        TINYTEST_TRUE( (!ERESULT_FAILED(eRc)) );
        TINYTEST_TRUE( ((strlen(path_getData(pPath))+1) == index) );
        TINYTEST_TRUE( (0 == strcmp(path_getData(pPath), (const char *)data)) );

        eRc = memFile_Close(pObj, true);
        TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );
        
        obj_Release(pObj);
        pObj = OBJ_NIL;
    }
    
    obj_Release(pPath);
    pPath = OBJ_NIL;
    
    obj_Release(pTime);
    pTime = OBJ_NIL;
    
    fprintf(stderr, "...%s completed.\n\n", pTestName);
    return 1;
}




TINYTEST_START_SUITE(test_memFile);
    TINYTEST_ADD_TEST(test_memFile_Create01,setUp,tearDown);
    TINYTEST_ADD_TEST(test_memFile_OpenClose,setUp,tearDown);
TINYTEST_END_SUITE();

TINYTEST_MAIN_SINGLE_SUITE(test_memFile);





