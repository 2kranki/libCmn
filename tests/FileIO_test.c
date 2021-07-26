// vi:nu:et:sts=4 ts=4 sw=4
/*
 *  Generated 07/10/2021 11:26:44
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
#include    <test_defs.h>
#include    <DateTime.h>
#include    <File.h>
#include    <trace.h>
#include    <FileIO_internal.h>
#include    <JsonIn.h>
#ifdef  FILEIO_JSON_SUPPORT
#   include    <SrcErrors.h>
#   include    <szTbl.h>
#endif



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

#ifdef  FILEIO_JSON_SUPPORT
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






int             test_FileIO_OpenClose (
    const
    char            *pTestName
)
{
    ERESULT         eRc = ERESULT_SUCCESS;
    FILEIO_DATA       *pObj = OBJ_NIL;
    bool            fRc;
   
    fprintf(stderr, "Performing: %s\n", pTestName);

    pObj = FileIO_Alloc( );
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    pObj = FileIO_Init( pObj );
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    if (pObj) {

        //obj_TraceSet(pObj, true);       
        fRc = obj_IsKindOf(pObj, OBJ_IDENT_FILEIO);
        TINYTEST_TRUE( (fRc) );
        
        // Test something.
        TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );

        obj_Release(pObj);
        pObj = OBJ_NIL;
    }

    fprintf(stderr, "...%s completed.\n\n\n", pTestName);
    return 1;
}



int             test_FileIO_Copy01 (
    const
    char            *pTestName
)
{
    ERESULT         eRc = ERESULT_SUCCESS;
    FILEIO_DATA       *pObj1 = OBJ_NIL;
    FILEIO_DATA       *pObj2 = OBJ_NIL;
    bool            fRc;
#if defined(FILEIO_JSON_SUPPORT) && defined(XYZZY)
    ASTR_DATA       *pStr = OBJ_NIL;
#endif
    //int             iRc;
   
    fprintf(stderr, "Performing: %s\n", pTestName);

    pObj1 = FileIO_New( );
    TINYTEST_FALSE( (OBJ_NIL == pObj1) );
    if (pObj1) {

        //obj_TraceSet(pObj1, true);       
        fRc = obj_IsKindOf(pObj1, OBJ_IDENT_FILEIO);
        TINYTEST_TRUE( (fRc) );
        
        // Test assign.
        pObj2 = FileIO_New();
        TINYTEST_FALSE( (OBJ_NIL == pObj2) );
        eRc = FileIO_Assign(pObj1, pObj2);
        TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );

        fRc = obj_IsKindOf(pObj2, OBJ_IDENT_FILEIO);
        TINYTEST_TRUE( (fRc) );
        //iRc = FileIO_Compare(pObj1, pObj2);
        //TINYTEST_TRUE( (0 == iRc) );
        //TODO: Add More tests here!

        obj_Release(pObj2);
        pObj2 = OBJ_NIL;

        // Test copy.
        pObj2 = FileIO_Copy(pObj1);
        TINYTEST_FALSE( (OBJ_NIL == pObj2) );

        fRc = obj_IsKindOf(pObj2, OBJ_IDENT_FILEIO);
        TINYTEST_TRUE( (fRc) );
        //iRc = FileIO_Compare(pObj1, pObj2);
        //TINYTEST_TRUE( (0 == iRc) );
        //TODO: Add More tests here!

        obj_Release(pObj2);
        pObj2 = OBJ_NIL;

        // Test json support.
#if defined(FILEIO_JSON_SUPPORT) && defined(XYZZY)
        pStr = FileIO_ToJson(pObj1);
        TINYTEST_FALSE( (OBJ_NIL == pStr) );
        fprintf(stderr, "JSON: %s\n", AStr_getData(pStr));
        pObj2 = FileIO_NewFromJsonString(pStr);
        TINYTEST_FALSE( (OBJ_NIL == pObj2) );
        fRc = obj_IsKindOf(pObj2, OBJ_IDENT_FILEIO);
        TINYTEST_TRUE( (fRc) );
        obj_Release(pStr);
        pStr = OBJ_NIL;
        //iRc = FileIO_Compare(pObj1, pObj2);
        //TINYTEST_TRUE( (0 == iRc) );

        obj_Release(pObj2);
        pObj2 = OBJ_NIL;
#endif

        obj_Release(pObj1);
        pObj1 = OBJ_NIL;
    }

    fprintf(stderr, "...%s completed.\n\n\n", pTestName);
    return 1;
}



int             test_FileIO_Test01 (
    const
    char            *pTestName
)
{
    //ERESULT         eRc = ERESULT_SUCCESS;
    FILEIO_DATA       *pObj = OBJ_NIL;
    bool            fRc;
   
    fprintf(stderr, "Performing: %s\n", pTestName);

    pObj = FileIO_New( );
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    if (pObj) {

        //obj_TraceSet(pObj, true);       
        fRc = obj_IsKindOf(pObj, OBJ_IDENT_FILEIO);
        TINYTEST_TRUE( (fRc) );
        //TINYTEST_TRUE( (ERESULT_OK(eRc)) );
        
        {
            ASTR_DATA       *pStr = FileIO_ToDebugString(pObj, 4);
            if (pStr) {
                fprintf(stderr, "Debug: %s\n", AStr_getData(pStr));
                obj_Release(pStr);
                pStr = OBJ_NIL;
            }
        }

        obj_Release(pObj);
        pObj = OBJ_NIL;
    }

    fprintf(stderr, "...%s completed.\n\n\n", pTestName);
    return 1;
}



int         test_FileIO_Read01(
    const
    char            *pTestName
)
{
    ERESULT         eRc;
    FILEIO_DATA     *pObj = OBJ_NIL;
    PATH_DATA       *pPath = OBJ_NIL;
    const
    char            *pPathA = TEST_FILES_DIR "/test_expand_01.txt";
    int64_t         fileSize = 0;
    uint8_t         buffer[256];
    uint8_t         *pBuffer = NULL;
    uint32_t        amtRead = 0;
    off_t           fileOffset;

    fprintf(stderr, "Performing: %s\n", pTestName);

    pPath = Path_NewA(pPathA);
    TINYTEST_FALSE( (OBJ_NIL == pPath) );
    Path_Clean(pPath);
    fprintf(stderr, "\tpath=%s\n", Path_getData(pPath));
    TINYTEST_FALSE( (ERESULT_FAILED(Path_IsFile(pPath))) );


    pObj = FileIO_New( );
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    if (pObj) {

        eRc = FileIO_Open(pObj, pPath, false);
        TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );

        fileSize = FileIO_Size(pObj);
        TINYTEST_FALSE( (-1 == fileSize) );

        if (fileSize) {
            pBuffer = mem_Malloc(fileSize);
            TINYTEST_FALSE( (NULL == pBuffer) );
            eRc = FileIO_Read(pObj, (uint32_t)fileSize, pBuffer, &amtRead);
            TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );
            TINYTEST_TRUE( (amtRead == fileSize) );
            mem_Free(pBuffer);
            pBuffer = NULL;
        }

        fileOffset = FileIO_SeekBegin(pObj, 0);
        TINYTEST_TRUE( (0 == fileOffset) );

        eRc = FileIO_Gets(pObj, 256, buffer);
        TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );
        fprintf(stderr, "\tline = \"%s\"\n", buffer);
        TINYTEST_TRUE( (0 == strcmp((const char *)buffer, "LNAME:${LNAME} UNAME:${UNAME}")) );

        eRc = FileIO_Gets(pObj, 256, buffer);
        TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );
        fprintf(stderr, "\tline = \"%s\"\n", buffer);
        TINYTEST_TRUE( (0 == strcmp((const char *)buffer, "${UNAME} ${LNAME} ${UNAME}")) );

        eRc = FileIO_Gets(pObj, 256, buffer);
        TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );
        fprintf(stderr, "\tline = \"%s\"\n", buffer);
        TINYTEST_TRUE( (0 == strcmp((const char *)buffer, "${XX} ${UNAME} ${XX}")) );

        eRc = FileIO_Gets(pObj, 256, buffer);
        TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );
        fprintf(stderr, "\tline = \"%s\"\n", buffer);
        TINYTEST_TRUE( (0 == strcmp((const char *)buffer, "")) );

        eRc = FileIO_Close(pObj, false);
        TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );

        obj_Release(pObj);
        pObj = OBJ_NIL;
    }

    obj_Release(pPath);
    pPath = OBJ_NIL;

    fprintf(stderr, "...%s completed.\n", pTestName);
    return 1;
}



int         test_FileIO_Read02(
    const
    char            *pTestName
)
{
    ERESULT         eRc;
    FILEIO_DATA     *pObj = OBJ_NIL;
    PATH_DATA       *pPath = OBJ_NIL;
    IO_INTERFACE    *pIO = OBJ_NIL;
    const
    char            *pPathA = TEST_FILES_DIR "/test_expand_01.txt";
    off_t           fileSize = 0;
    uint8_t         buffer[256];
    uint8_t         *pBuffer = NULL;
    off_t           amtRead = 0;
    off_t           fileOffset;

    fprintf(stderr, "Performing: %s\n", pTestName);

    pPath = Path_NewA(pPathA);
    TINYTEST_FALSE( (OBJ_NIL == pPath) );
    Path_Clean(pPath);
    fprintf(stderr, "\tpath=%s\n", Path_getData(pPath));
    TINYTEST_FALSE( (ERESULT_FAILED(Path_IsFile(pPath))) );


    pObj = FileIO_New( );
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    if (pObj) {

        eRc = FileIO_Open(pObj, pPath, false);
        TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );

        fileSize = FileIO_Size(pObj);
        TINYTEST_FALSE( (-1 == fileSize) );

        pIO = FileIO_getIO(pObj);
        TINYTEST_FALSE( (OBJ_NIL == pIO) );

        if (fileSize) {
            pBuffer = mem_Malloc(fileSize);
            TINYTEST_FALSE( (NULL == pBuffer) );
            amtRead = pIO->pVtbl->pRead(pIO, pBuffer, (int32_t)fileSize);
            TINYTEST_TRUE( (amtRead == fileSize) );
            mem_Free(pBuffer);
            pBuffer = NULL;
        }

        fileOffset = pIO->pVtbl->pSeek(pIO, 0, IO_SEEK_SET);
        TINYTEST_TRUE( (0 == fileOffset) );

        eRc = FileIO_Gets(pObj, 256, buffer);
        TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );
        fprintf(stderr, "\tline = \"%s\"\n", buffer);
        TINYTEST_TRUE( (0 == strcmp((const char *)buffer, "LNAME:${LNAME} UNAME:${UNAME}")) );

        eRc = FileIO_Gets(pObj, 256, buffer);
        TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );
        fprintf(stderr, "\tline = \"%s\"\n", buffer);
        TINYTEST_TRUE( (0 == strcmp((const char *)buffer, "${UNAME} ${LNAME} ${UNAME}")) );

        eRc = FileIO_Gets(pObj, 256, buffer);
        TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );
        fprintf(stderr, "\tline = \"%s\"\n", buffer);
        TINYTEST_TRUE( (0 == strcmp((const char *)buffer, "${XX} ${UNAME} ${XX}")) );

        eRc = FileIO_Gets(pObj, 256, buffer);
        TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );
        fprintf(stderr, "\tline = \"%s\"\n", buffer);
        TINYTEST_TRUE( (0 == strcmp((const char *)buffer, "")) );

        eRc = pIO->pVtbl->pClose(pIO);
        TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );

        obj_Release(pIO);
        pIO = OBJ_NIL;
        obj_Release(pObj);
        pObj = OBJ_NIL;
    }

    obj_Release(pPath);
    pPath = OBJ_NIL;

    fprintf(stderr, "...%s completed.\n", pTestName);
    return 1;
}



int         test_FileIO_Create01(
    const
    char            *pTestName
)
{
    ERESULT         eRc;
    FILEIO_DATA     *pObj = OBJ_NIL;
    PATH_DATA       *pPath = OBJ_NIL;
    const
    char            *pPathA = "/tmp/testFile.tmp";
    int64_t         fileSize = 0;
    //uint8_t         *pBuffer = NULL;
    DATETIME_DATA   *pTime = OBJ_NIL;
    ASTR_DATA       *pStr = OBJ_NIL;

    fprintf(stderr, "Performing: %s\n", pTestName);

    pTime = DateTime_NewCurrent();
    TINYTEST_FALSE( (OBJ_NIL == pTime) );

    pPath = Path_NewA(pPathA);
    TINYTEST_FALSE( (OBJ_NIL == pPath) );
    pStr = DateTime_ToFileString(pTime);
    TINYTEST_FALSE( (OBJ_NIL == pTime) );
    Path_AppendAStr(pPath, pStr);
    obj_Release(pStr);
    pStr = OBJ_NIL;
    Path_AppendA(pPath, ".txt");
    fprintf(stderr, "\tPath = \"%s\"\n", Path_getData(pPath));

    pObj = FileIO_Alloc( );
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    pObj = FileIO_Init(pObj);
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    if (pObj) {

        eRc = FileIO_Open(pObj, pPath, false);
        TINYTEST_TRUE( (ERESULT_FAILED(eRc)) );

        eRc = FileIO_Create(pObj, pPath, false);
        TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );

        eRc =   FileIO_Write(
                           pObj,
                           (uint32_t)(strlen(Path_getData(pPath))+1),
                           Path_getData(pPath)
                );
        TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );

        fileSize = FileIO_Size(pObj);
        fprintf(
                stderr,
                "\tSize = %ld  FileIO_Size=%lld\n",
                (strlen(Path_getData(pPath))+1),
                fileSize
        );
        TINYTEST_TRUE( ((strlen(Path_getData(pPath))+1) == fileSize) );

        eRc = FileIO_Close(pObj, true);
        TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );

        fileSize = File_SizeA(Path_getData(pPath));
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



int             test_FileIO_Create02(
    const
    char            *pTestName
)
{
    ERESULT         eRc = ERESULT_SUCCESS;
    FILEIO_DATA     *pObj = OBJ_NIL;
    PATH_DATA       *pPath = OBJ_NIL;
    const
    char            *pPathA = "/tmp/testFile.tmp";
    DATETIME_DATA   *pTime = OBJ_NIL;
    ASTR_DATA       *pStr = OBJ_NIL;
    int64_t         fileSize = 0;
    //uint32_t        i;
    uint32_t        index;
    uint8_t         data[256];
    //uint8_t         *pData = data;

    fprintf(stderr, "Performing: %s\n", pTestName);

    pTime = DateTime_NewCurrent();
    TINYTEST_FALSE( (OBJ_NIL == pTime) );
    pPath = Path_NewA(pPathA);
    TINYTEST_FALSE( (OBJ_NIL == pPath) );
    pStr = DateTime_ToFileString(pTime);
    TINYTEST_FALSE( (OBJ_NIL == pTime) );
    Path_AppendAStr(pPath, pStr);
    obj_Release(pStr);
    pStr = OBJ_NIL;
    Path_AppendA(pPath, ".txt");
    fprintf(stderr, "\tPath = \"%s\"\n", Path_getData(pPath));

    pObj = FileIO_New( );
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    if (pObj) {

        eRc = FileIO_Create(pObj, pPath, true);
        TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );

        eRc =   FileIO_Write(
                             pObj,
                             (uint32_t)(strlen(Path_getData(pPath))+1),
                             Path_getData(pPath)
                );
        TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );

        fileSize = FileIO_Size(pObj);
        fprintf(
                stderr,
                "\tSize = %ld  fileio_Size=%lld\n",
                (strlen(Path_getData(pPath))+1),
                fileSize
                );
        TINYTEST_TRUE( ((strlen(Path_getData(pPath))+1) == fileSize) );

        eRc = FileIO_Close(pObj, false);
        TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );

        fileSize = FileIO_Size(pObj);
        TINYTEST_TRUE( (-1 == fileSize) );

        eRc = FileIO_Open(pObj, pPath, true);
        TINYTEST_TRUE( (!ERESULT_FAILED(eRc)) );

        index = 0;
        eRc = FileIO_Read(pObj, 256, data, &index);
        TINYTEST_TRUE( (!ERESULT_FAILED(eRc)) );
        TINYTEST_TRUE( ((strlen(Path_getData(pPath))+1) == index) );
        TINYTEST_TRUE( (0 == strcmp(Path_getData(pPath), (const char *)data)) );

        eRc = FileIO_Close(pObj, true);
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




TINYTEST_START_SUITE(test_FileIO);
    TINYTEST_ADD_TEST(test_FileIO_Create02,setUp,tearDown);
    TINYTEST_ADD_TEST(test_FileIO_Create01,setUp,tearDown);
    TINYTEST_ADD_TEST(test_FileIO_Read02,setUp,tearDown);
    TINYTEST_ADD_TEST(test_FileIO_Read01,setUp,tearDown);
    TINYTEST_ADD_TEST(test_FileIO_Test01,setUp,tearDown);
    //TINYTEST_ADD_TEST(test_FileIO_Copy01,setUp,tearDown);
    TINYTEST_ADD_TEST(test_FileIO_OpenClose,setUp,tearDown);
TINYTEST_END_SUITE();

TINYTEST_MAIN_SINGLE_SUITE(test_FileIO);





