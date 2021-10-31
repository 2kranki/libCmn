// vi:nu:et:sts=4 ts=4 sw=4
//****************************************************************
//                      Test Object Program
//****************************************************************
/*
 * Program
 *          Test Object Program
 * Purpose
 *          This program tests a particular object given certain
 *          parameters.
 *
 * Remarks
 *  1.      This relies on the fact that we can add to the Test
 *          Object by simply coding methods that use the Test
 *          Object.
 *
 * History
 *  08/29/2021 Generated
 */


/*
 This is free and unencumbered software released into the public domain.
 
 Anyone is free to copy, modify, publish, use, compile, sell, or
 distribute this software, either in source code form or as a compiled
 binary, for any purpose, commercial or non-commercial, and by any
 means.
 
 In jurisdictions that recognize copyright laws, the author or authors
 of this software dedicate any and all copyright interest in the
 software to the public domain. We make this dedication for the benefit
 of the public at large and to the detriment of our heirs and
 successors. We intend this dedication to be an overt act of
 relinquishment in perpetuity of all present and future rights to this
 software under copyright law.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
 IN NO EVENT SHALL THE AUTHORS BE LIABLE FOR ANY CLAIM, DAMAGES OR
 OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
 ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 OTHER DEALINGS IN THE SOFTWARE.
 
 For more information, please refer to <http://unlicense.org/>
 */




/*
 TestForFail(error_sttring)         <= Tests eRc for failure
 TestForFalse(test, error_sttring)
 TestForNotNull(test, error)
 TestForNull(test, error)
 TestForSuccess(error)              <= Tests eRc for success
 TestForTrue(test, error)
 */





#include    <test_defs.h>
#include    <Test_internal.h>
#include    <trace.h>
#include    <FileIO_internal.h>
#include    <File.h>
#include    <JsonIn.h>
#include    <SrcErrors.h>
#include    <szTbl.h>






ERESULT         Test_FileIO_OpenClose (
    TEST_DATA       *this,
    const
    char            *pTestName
)
{
    ERESULT         eRc = ERESULT_SUCCESS;
    FILEIO_DATA       *pObj = OBJ_NIL;
    bool            fRc;
   
    fprintf(stderr, "Performing: %s\n", pTestName);

    pObj = FileIO_Alloc( );
    TestForNotNull(pObj, "Missing Test Alloc() object");
    pObj = FileIO_Init( pObj );
    TestForNotNull(pObj, "Missing Test Init() object");
    if (pObj) {

        //obj_TraceSet(pObj, true);       
        fRc = obj_IsKindOf(pObj, OBJ_IDENT_FILEIO);
        TestForTrue(fRc, "Failed Ident Test");
        
        // Test something.
        TestForSuccess("test failed");

        obj_Release(pObj);
        pObj = OBJ_NIL;
    }

    fprintf(stderr, "...%s completed.\n\n\n", pTestName);
    return eRc;
}



ERESULT         Test_FileIO_Copy01 (
    TEST_DATA       *this,
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
    TestForNotNull(pObj1, "Missing Test object");
    if (pObj1) {

        //obj_TraceSet(pObj1, true);       
        fRc = obj_IsKindOf(pObj1, OBJ_IDENT_FILEIO);
        TestForTrue(fRc, "Failed Ident Test");
        
        // Test assign.
        pObj2 = FileIO_New();
        TestForNotNull(pObj2, "Missing copied object");
        eRc = FileIO_Assign(pObj1, pObj2);
        TestForFalse((ERESULT_FAILED(eRc)), "Assignment failed");

        fRc = obj_IsKindOf(pObj2, OBJ_IDENT_FILEIO);
        TestForTrue(fRc, "Failed Ident Test");
        //iRc = FileIO_Compare(pObj1, pObj2);
        //TestForTrue((0 == iRc), "Failed Compare");
        //TODO: Add More tests here!

        obj_Release(pObj2);
        pObj2 = OBJ_NIL;

        // Test copy.
        pObj2 = FileIO_Copy(pObj1);
        TestForNotNull(pObj2, "Missing copied object");

        fRc = obj_IsKindOf(pObj2, OBJ_IDENT_FILEIO);
        TestForTrue(fRc, "Failed Ident Test");
        //iRc = FileIO_Compare(pObj1, pObj2);
        //TestForTrue((0 == iRc), "Failed Compare");
        //TODO: Add More tests here!

        obj_Release(pObj2);
        pObj2 = OBJ_NIL;

        // Test json support.
#if defined(FILEIO_JSON_SUPPORT) && defined(XYZZY)
        pStr = FileIO_ToJson(pObj1);
        TestForNotNull(pStr, "Missing JSON output");
        fprintf(stderr, "JSON: %s\n", AStr_getData(pStr));
        pObj2 = FileIO_NewFromJsonString(pStr);
        TestForNotNull(pObj2, "Missing JSON created object");
        fRc = obj_IsKindOf(pObj2, OBJ_IDENT_FILEIO);
        TestForTrue(fRc, "Failed Ident Test");
        obj_Release(pStr);
        pStr = OBJ_NIL;
        //iRc = FileIO_Compare(pObj1, pObj2);
        //TestForTrue((0 == iRc), "Failed Compare");

        obj_Release(pObj2);
        pObj2 = OBJ_NIL;
#endif

        obj_Release(pObj1);
        pObj1 = OBJ_NIL;
    }

    fprintf(stderr, "...%s completed.\n\n\n", pTestName);
    return eRc;
}



ERESULT         Test_FileIO_Test01 (
    TEST_DATA       *this,
    const
    char            *pTestName
)
{
    ERESULT         eRc = ERESULT_SUCCESS;
    FILEIO_DATA     *pObj = OBJ_NIL;
    bool            fRc;
   
    fprintf(stderr, "Performing: %s\n", pTestName);

    pObj = FileIO_New( );
    TestForNotNull(pObj, "Missing Test object");
    if (pObj) {

        //obj_TraceSet(pObj, true);       
        fRc = obj_IsKindOf(pObj, OBJ_IDENT_FILEIO);
        TestForTrue(fRc, "Failed Ident Test");
        
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
    return eRc;
}



ERESULT         Test_FileIO_Read01 (
    TEST_DATA       *this,
    const
    char            *pTestName
)
{
    ERESULT         eRc = ERESULT_SUCCESS;
    FILEIO_DATA     *pObj = OBJ_NIL;
    bool            fRc;
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
    TestForNotNull(pPath, "Missing Path object");
    Path_Clean(pPath);
    fprintf(stderr, "\tpath=%s\n", Path_getData(pPath));
    eRc = Path_IsFile(pPath);
    TestForSuccess("");

    pObj = FileIO_New( );
    TestForNotNull(pObj, "Missing Test object");
    if (pObj) {

        //obj_TraceSet(pObj, true);
        fRc = obj_IsKindOf(pObj, OBJ_IDENT_FILEIO);
        TestForTrue(fRc, "Failed Ident Test");

        eRc = FileIO_Open(pObj, pPath, false);
        TestForSuccess("");

        fileSize = FileIO_Size(pObj);
        TestForFalse((-1 == fileSize), "");

        if (fileSize) {
            pBuffer = mem_Malloc(fileSize);
            TestForNotNull(pBuffer, "");
            eRc = FileIO_Read(pObj, (uint32_t)fileSize, pBuffer, &amtRead);
            TestForSuccess("");
            TestForTrue((amtRead == fileSize), "");
            mem_Free(pBuffer);
            pBuffer = NULL;
        }

        fileOffset = FileIO_SeekBegin(pObj, 0);
        TestForTrue((0 == fileOffset), "");

        eRc = FileIO_Gets(pObj, 256, buffer);
        TestForSuccess("");
        fprintf(stderr, "\tline = \"%s\"\n", buffer);
        TestForTrue((0 == strcmp((const char *)buffer, "LNAME:${LNAME} UNAME:${UNAME}")), "");

        eRc = FileIO_Gets(pObj, 256, buffer);
        TestForSuccess("");
        fprintf(stderr, "\tline = \"%s\"\n", buffer);
        TestForTrue((0 == strcmp((const char *)buffer, "${UNAME} ${LNAME} ${UNAME}")), "");

        eRc = FileIO_Gets(pObj, 256, buffer);
        TestForSuccess("");
        fprintf(stderr, "\tline = \"%s\"\n", buffer);
        TestForTrue((0 == strcmp((const char *)buffer, "${XX} ${UNAME} ${XX}")), "");

        eRc = FileIO_Gets(pObj, 256, buffer);
        TestForSuccess("");
        fprintf(stderr, "\tline = \"%s\"\n", buffer);
        TestForTrue((0 == strcmp((const char *)buffer, "")), "");

        eRc = FileIO_Close(pObj, false);
        TestForSuccess("");

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

    obj_Release(pPath);
    pPath = OBJ_NIL;

    fprintf(stderr, "...%s completed.\n\n\n", pTestName);
    return eRc;
}



ERESULT         Test_FileIO_Read02 (
    TEST_DATA       *this,
    const
    char            *pTestName
)
{
    ERESULT         eRc = ERESULT_SUCCESS;
    FILEIO_DATA     *pObj = OBJ_NIL;
    bool            fRc;
    PATH_DATA       *pPath = OBJ_NIL;
    //IO_INTERFACE    *pIO = OBJ_NIL;
    const
    char            *pPathA = TEST_FILES_DIR "/test_expand_01.txt";
    off_t           fileSize = 0;
    uint8_t         buffer[256];
    uint8_t         *pBuffer = NULL;
    uint32_t        amtRead = 0;
    off_t           fileOffset;

    fprintf(stderr, "Performing: %s\n", pTestName);

    pPath = Path_NewA(pPathA);
    TestForNotNull(pPath, "Missing Path object");
    Path_Clean(pPath);
    fprintf(stderr, "\tpath=%s\n", Path_getData(pPath));
    eRc = Path_IsFile(pPath);
    TestForSuccess("");

    pObj = FileIO_New( );
    TestForNotNull(pObj, "Missing Test object");
    if (pObj) {

        //obj_TraceSet(pObj, true);
        fRc = obj_IsKindOf(pObj, OBJ_IDENT_FILEIO);
        TestForTrue(fRc, "Failed Ident Test");

        eRc = FileIO_Open(pObj, pPath, false);
        TestForSuccess("");

        fileSize = FileIO_Size(pObj);
        TestForFalse((-1 == fileSize), "");

        if (fileSize) {
            pBuffer = mem_Malloc(fileSize);
            TestForNotNull(pBuffer, "");
            eRc = FileIO_Read(pObj, (uint32_t)fileSize, pBuffer, &amtRead);
            TestForSuccess("");
            TestForTrue((amtRead == fileSize), "");
            mem_Free(pBuffer);
            pBuffer = NULL;
        }

        fileOffset = FileIO_SeekBegin(pObj, 0);
        TestForTrue((0 == fileOffset), "");

        eRc = FileIO_Gets(pObj, 256, buffer);
        TestForSuccess("");
        fprintf(stderr, "\tline = \"%s\"\n", buffer);
        TestForTrue((0 == strcmp((const char *)buffer, "LNAME:${LNAME} UNAME:${UNAME}")), "");

        eRc = FileIO_Gets(pObj, 256, buffer);
        TestForSuccess("");
        fprintf(stderr, "\tline = \"%s\"\n", buffer);
        TestForTrue((0 == strcmp((const char *)buffer, "${UNAME} ${LNAME} ${UNAME}")), "");

        eRc = FileIO_Gets(pObj, 256, buffer);
        TestForSuccess("");
        fprintf(stderr, "\tline = \"%s\"\n", buffer);
        TestForTrue((0 == strcmp((const char *)buffer, "${XX} ${UNAME} ${XX}")), "");

        eRc = FileIO_Gets(pObj, 256, buffer);
        TestForSuccess("");
        fprintf(stderr, "\tline = \"%s\"\n", buffer);
        TestForTrue((0 == strcmp((const char *)buffer, "")), "");

        eRc = FileIO_Close(pObj, false);
        TestForSuccess("");

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

    obj_Release(pPath);
    pPath = OBJ_NIL;

    fprintf(stderr, "...%s completed.\n\n\n", pTestName);
    return eRc;
}



ERESULT         Test_FileIO_Create01 (
    TEST_DATA       *this,
    const
    char            *pTestName
)
{
    ERESULT         eRc = ERESULT_SUCCESS;
    FILEIO_DATA     *pObj = OBJ_NIL;
    bool            fRc;
    PATH_DATA       *pPath = OBJ_NIL;
    const
    char            *pPathA = "/tmp/testFile.tmp";
    int64_t         fileSize = 0;
    //uint8_t         *pBuffer = NULL;
    DATETIME_DATA   *pTime = OBJ_NIL;
    ASTR_DATA       *pStr = OBJ_NIL;

    fprintf(stderr, "Performing: %s\n", pTestName);

    pTime = DateTime_NewCurrent();
    TestForNotNull(pTime, "Missing Test object");

    pPath = Path_NewA(pPathA);
    TestForNotNull(pPath, "Missing Path object");
    pStr = DateTime_ToFileString(pTime);
    TestForNotNull(pTime, "Missing Str object");
    Path_AppendAStr(pPath, pStr);
    obj_Release(pStr);
    pStr = OBJ_NIL;
    Path_AppendA(pPath, ".txt");
    Path_Clean(pPath);
    fprintf(stderr, "\tpath=%s\n", Path_getData(pPath));
    eRc = Path_IsFile(pPath);
    TestForFail("");

    pObj = FileIO_New( );
    TestForNotNull(pObj, "Missing Test object");
    if (pObj) {

        //obj_TraceSet(pObj, true);
        fRc = obj_IsKindOf(pObj, OBJ_IDENT_FILEIO);
        TestForTrue(fRc, "Failed Ident Test");

        eRc = FileIO_Open(pObj, pPath, false);
        TestForFail("");

        eRc = FileIO_Create(pObj, pPath, false);
        TestForSuccess("");

        eRc =   FileIO_Write(
                           pObj,
                           (uint32_t)(strlen(Path_getData(pPath))+1),
                           Path_getData(pPath)
                );
        TestForSuccess("");

        fileSize = FileIO_Size(pObj);
        fprintf(
                stderr,
                "\tSize = %ld  FileIO_Size=%lld\n",
                (strlen(Path_getData(pPath))+1),
                fileSize
        );
        TestForTrue(((strlen(Path_getData(pPath))+1) == fileSize), "");

        eRc = FileIO_Close(pObj, true);
        TestForSuccess("");

        fileSize = File_SizeA(Path_getData(pPath));
        TestForTrue((-1 == fileSize), "");

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

    obj_Release(pPath);
    pPath = OBJ_NIL;

    obj_Release(pTime);
    pTime = OBJ_NIL;

    fprintf(stderr, "...%s completed.\n\n\n", pTestName);
    return eRc;
}



ERESULT         Test_FileIO_Create02 (
    TEST_DATA       *this,
    const
    char            *pTestName
)
{
    ERESULT         eRc = ERESULT_SUCCESS;
    FILEIO_DATA     *pObj = OBJ_NIL;
    bool            fRc;
    PATH_DATA       *pPath = OBJ_NIL;
    const
    char            *pPathA = "/tmp/testFile.tmp";
    int64_t         fileSize = 0;
    //uint8_t         *pBuffer = NULL;
    DATETIME_DATA   *pTime = OBJ_NIL;
    ASTR_DATA       *pStr = OBJ_NIL;
    uint32_t        index;
    uint8_t         data[256];

    fprintf(stderr, "Performing: %s\n", pTestName);

    pTime = DateTime_NewCurrent();
    TestForNotNull(pTime, "Missing Test object");

    pPath = Path_NewA(pPathA);
    TestForNotNull(pPath, "Missing Path object");
    pStr = DateTime_ToFileString(pTime);
    TestForNotNull(pTime, "Missing Str object");
    Path_AppendAStr(pPath, pStr);
    obj_Release(pStr);
    pStr = OBJ_NIL;
    Path_AppendA(pPath, ".txt");
    Path_Clean(pPath);
    fprintf(stderr, "\tpath=(%p)%s\n", pPath, Path_getData(pPath));
    eRc = Path_IsFile(pPath);
    TestForFail("");

    pObj = FileIO_New( );
    TestForNotNull(pObj, "Missing Test object");
    if (pObj) {

        //obj_TraceSet(pObj, true);
        fRc = obj_IsKindOf(pObj, OBJ_IDENT_FILEIO);
        TestForTrue(fRc, "Failed Ident Test");

        eRc = FileIO_Create(pObj, pPath, true);
        TestForSuccess("");

        eRc =   FileIO_Write(
                             pObj,
                             (uint32_t)(strlen(Path_getData(pPath))+1),
                             Path_getData(pPath)
                );
        TestForSuccess("");

        fileSize = FileIO_Size(pObj);
        fprintf(
                stderr,
                "\tSize = %ld  fileio_Size=%lld\n",
                (strlen(Path_getData(pPath))+1),
                fileSize
                );
        TestForTrue(((strlen(Path_getData(pPath))+1) == fileSize), "");

        eRc = FileIO_Close(pObj, false);
        TestForSuccess("");

        fileSize = FileIO_Size(pObj);
        TestForTrue((-1 == fileSize), "");

        eRc = FileIO_Open(pObj, pPath, true);
        TestForSuccess("");

        index = 0;
        eRc = FileIO_Read(pObj, 256, data, &index);
        TestForSuccess("");
        TestForTrue(((strlen(Path_getData(pPath))+1) == index), "");
        TestForTrue((0 == strcmp(Path_getData(pPath), (const char *)data)), "");

        eRc = FileIO_Close(pObj, true);
        TestForSuccess("");

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

    obj_Release(pPath);
    pPath = OBJ_NIL;

    obj_Release(pTime);
    pTime = OBJ_NIL;

    {
        FILEIO_CLASS_VTBL   *pVtbl = (void *)obj_getVtbl(FileIO_Class());
        pVtbl->pMemFileReset();
    }

    fprintf(stderr, "...%s completed.\n\n\n", pTestName);
    return eRc;
}




int     main (
    int         cArgs,
    const
    char        *ppArgs[],
    const
    char        *ppEnv[]
)
{
    ERESULT     eRc;
    TEST_DATA   test = {0};
    TEST_DATA   *pTest = OBJ_NIL;
    int         i;
    const
    char        *pTestNameA = NULL;

    pTest = Test_Init(&test);
    if (OBJ_NIL == pTest) {
        fprintf(
                stderr,
                "\x1b[1m\x1b[31mFATAL\x1b[0m: Could not create Test object!\n\n\n"
        );
        exit(201);
    }

    // Scan args.
    for (i=0; i<cArgs; i++) {
        if (0 == strcmp("--no_int3", ppArgs[i])) {
            Test_setAllowInt3(pTest, false);
        }
    }

    // Execute tests.
    TestExec("OpenClose", Test_FileIO_OpenClose, NULL, NULL);
    //TestExec("Copy01", Test_FileIO_Copy01, pTest, NULL, NULL);
    TestExec("Test01", Test_FileIO_Test01, NULL, NULL);
    TestExec("Read01", Test_FileIO_Read01, NULL, NULL);
    TestExec("Read02", Test_FileIO_Read02, NULL, NULL);
    TestExec("Create01", Test_FileIO_Create01, NULL, NULL);
    TestExec("Create02", Test_FileIO_Create02, NULL, NULL);

    obj_Release(pTest);
    pTest = OBJ_NIL;

    // Return to Operating System.
    return 0;
}



