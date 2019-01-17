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
#include    <dateTime.h>
#include    <file.h>
#include    <trace.h>
#include    <fileio_internal.h>



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






int         test_fileio_OpenClose(
    const
    char            *pTestName
)
{
    FILEIO_DATA	*pObj = OBJ_NIL;
   
    fprintf(stderr, "Performing: %s\n", pTestName);
    
    pObj = fileio_Alloc( );
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    pObj = fileio_Init(pObj);
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    if (pObj) {

        // Test something.

        obj_Release(pObj);
        pObj = OBJ_NIL;
    }

    fprintf(stderr, "...%s completed.\n", pTestName);
    return 1;
}



int         test_fileio_Read01(
    const
    char            *pTestName
)
{
    ERESULT         eRc;
    FILEIO_DATA     *pObj = OBJ_NIL;
    PATH_DATA       *pPath = OBJ_NIL;
    const
    char            *pPathA = "~/git/libCmn/tests/files/test_objects.json.txt";
    int64_t         fileSize = 0;
    uint8_t         buffer[256];
    uint8_t         *pBuffer = NULL;
    uint32_t        amtRead = 0;
    off_t           fileOffset;
    
    fprintf(stderr, "Performing: %s\n", pTestName);
    
    pPath = path_NewA(pPathA);
    TINYTEST_FALSE( (OBJ_NIL == pPath) );
    path_Clean(pPath);
    fprintf(stderr, "\tpath=%s\n", path_getData(pPath));
    TINYTEST_FALSE( (ERESULT_FAILED(path_IsFile(pPath))) );


    pObj = fileio_New( );
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    if (pObj) {
        
        eRc = fileio_Open(pObj, pPath);
        TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );
        
        fileSize = fileio_Size(pObj);
        TINYTEST_FALSE( (-1 == fileSize) );

        if (fileSize) {
            pBuffer = mem_Malloc(fileSize);
            TINYTEST_FALSE( (NULL == pBuffer) );
            eRc = fileio_Read(pObj, (uint32_t)fileSize, pBuffer, &amtRead);
            TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );
            TINYTEST_TRUE( (amtRead == fileSize) );
            mem_Free(pBuffer);
            pBuffer = NULL;
        }
        
        fileOffset = fileio_SeekBegin(pObj, 0);
        TINYTEST_TRUE( (0 == fileOffset) );
        
        eRc = fileio_Gets(pObj, 256, buffer);
        TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );
        fprintf(stderr, "\tline = \"%s\"\n", buffer);
        TINYTEST_TRUE( (0 == strcmp((const char *)buffer, "{")) );

        eRc = fileio_Gets(pObj, 256, buffer);
        TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );
        fprintf(stderr, "\tline = \"%s\"\n", buffer);
        TINYTEST_TRUE( (0 == strcmp((const char *)buffer, "    \"name\":")) );

        eRc = fileio_Gets(pObj, 256, buffer);
        TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );
        fprintf(stderr, "\tline = \"%s\"\n", buffer);
        TINYTEST_TRUE( (0 == strcmp((const char *)buffer, "        \"libXYZZY\",")) );
        
        eRc = fileio_Gets(pObj, 256, buffer);
        TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );
        fprintf(stderr, "\tline = \"%s\"\n", buffer);
        TINYTEST_TRUE( (0 == strcmp((const char *)buffer, "    \"lib_deps\": ")) );
        
        eRc = fileio_Close(pObj, false);
        TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );
        
        obj_Release(pObj);
        pObj = OBJ_NIL;
    }
    
    obj_Release(pPath);
    pPath = OBJ_NIL;
    
    fprintf(stderr, "...%s completed.\n", pTestName);
    return 1;
}



int         test_fileio_Create01(
    const
    char            *pTestName
)
{
    ERESULT         eRc;
    FILEIO_DATA     *pObj = OBJ_NIL;
    PATH_DATA       *pPath = OBJ_NIL;
    const
    char            *pPathA = "/tmp/testFile.temp.";
    int64_t         fileSize = 0;
    //uint8_t         *pBuffer = NULL;
    DATETIME_DATA   *pTime = OBJ_NIL;
    ASTR_DATA       *pStr = OBJ_NIL;
    
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

    pObj = fileio_Alloc( );
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    pObj = fileio_Init(pObj);
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    if (pObj) {
        
        eRc = fileio_Open(pObj, pPath);
        TINYTEST_TRUE( (ERESULT_FAILED(eRc)) );
        
        eRc = fileio_Create(pObj, pPath);
        TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );
        
        eRc =   fileio_Write(
                           pObj,
                           (uint32_t)(strlen(path_getData(pPath))+1),
                           path_getData(pPath)
                );
        TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );

        fileSize = fileio_Size(pObj);
        fprintf(
                stderr,
                "\tSize = %ld  fileio_Size=%lld\n",
                (strlen(path_getData(pPath))+1),
                fileSize
        );
        TINYTEST_TRUE( ((strlen(path_getData(pPath))+1) == fileSize) );
        
        eRc = fileio_Close(pObj, true);
        TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );
        
        fileSize = file_SizeA(path_getData(pPath));
        TINYTEST_TRUE( (-1 == fileSize) );
        
        obj_Release(pObj);
        pObj = OBJ_NIL;
    }
    
    obj_Release(pPath);
    pPath = OBJ_NIL;
    
    obj_Release(pTime);
    pTime = OBJ_NIL;
    
    fprintf(stderr, "...%s completed.\n", pTestName);
    return 1;
}




TINYTEST_START_SUITE(test_fileio);
    TINYTEST_ADD_TEST(test_fileio_Create01,setUp,tearDown);
    TINYTEST_ADD_TEST(test_fileio_Read01,setUp,tearDown);
    TINYTEST_ADD_TEST(test_fileio_OpenClose,setUp,tearDown);
TINYTEST_END_SUITE();

TINYTEST_MAIN_SINGLE_SUITE(test_fileio);





