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
#include    <BPT32_internal.h>
#include    <BPT32_Request.h>
#include    <JsonIn.h>
#include    <SrcErrors.h>
#include    <szTbl.h>






ERESULT         Test_BPT32_OpenClose (
    TEST_DATA       *this,
    const
    char            *pTestName
)
{
    ERESULT         eRc = ERESULT_SUCCESS;
    BPT32_DATA      *pObj = OBJ_NIL;
    bool            fRc;
   
    fprintf(stderr, "Performing: %s\n", pTestName);

    pObj = BPT32_Alloc( );
    TestForNotNull(pObj, "Missing Test Alloc() object");
    pObj = BPT32_Init( pObj );
    TestForNotNull(pObj, "Missing Test Init() object");
    if (pObj) {

        //obj_TraceSet(pObj, true);       
        fRc = obj_IsKindOf(pObj, OBJ_IDENT_BPT32);
        TestForTrue(fRc, "Failed Ident Test");
        
        // Test something.
        TestForSuccess("test failed");

        obj_Release(pObj);
        pObj = OBJ_NIL;
    }

    fprintf(stderr, "...%s completed.\n\n\n", pTestName);
    return eRc;
}



ERESULT         Test_BPT32_Copy01 (
    TEST_DATA       *this,
    const
    char            *pTestName
)
{
    ERESULT         eRc = ERESULT_SUCCESS;
    BPT32_DATA      *pObj1 = OBJ_NIL;
    BPT32_DATA      *pObj2 = OBJ_NIL;
    bool            fRc;
#if defined(BPT32_JSON_SUPPORT) && defined(XYZZY)
    ASTR_DATA       *pStr = OBJ_NIL;
#endif
    //int             iRc;
   
    fprintf(stderr, "Performing: %s\n", pTestName);

    pObj1 = BPT32_New( );
    TestForNotNull(pObj1, "Missing Test object");
    if (pObj1) {

        //obj_TraceSet(pObj1, true);       
        fRc = obj_IsKindOf(pObj1, OBJ_IDENT_BPT32);
        TestForTrue(fRc, "Failed Ident Test");
        
        // Test assign.
        pObj2 = BPT32_New();
        TestForNotNull(pObj2, "Missing copied object");
        eRc = BPT32_Assign(pObj1, pObj2);
        TestForFalse((ERESULT_FAILED(eRc)), "Assignment failed");

        fRc = obj_IsKindOf(pObj2, OBJ_IDENT_BPT32);
        TestForTrue(fRc, "Failed Ident Test");
        //iRc = BPT32_Compare(pObj1, pObj2);
        //TestForTrue((0 == iRc), "Failed Compare");
        //TODO: Add More tests here!

        obj_Release(pObj2);
        pObj2 = OBJ_NIL;

        // Test copy.
        pObj2 = BPT32_Copy(pObj1);
        TestForNotNull(pObj2, "Missing copied object");

        fRc = obj_IsKindOf(pObj2, OBJ_IDENT_BPT32);
        TestForTrue(fRc, "Failed Ident Test");
        //iRc = BPT32_Compare(pObj1, pObj2);
        //TestForTrue((0 == iRc), "Failed Compare");
        //TODO: Add More tests here!

        obj_Release(pObj2);
        pObj2 = OBJ_NIL;

        // Test json support.
#if defined(BPT32_JSON_SUPPORT) && defined(XYZZY)
        pStr = BPT32_ToJson(pObj1);
        TestForNotNull(pStr, "Missing JSON output");
        fprintf(stderr, "JSON: %s\n", AStr_getData(pStr));
        pObj2 = BPT32_NewFromJsonString(pStr);
        TestForNotNull(pObj2, "Missing JSON created object");
        fRc = obj_IsKindOf(pObj2, OBJ_IDENT_BPT32);
        TestForTrue(fRc, "Failed Ident Test");
        obj_Release(pStr);
        pStr = OBJ_NIL;
        //iRc = BPT32_Compare(pObj1, pObj2);
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



ERESULT         Test_BPT32_Test01 (
    TEST_DATA       *this,
    const
    char            *pTestName
)
{
    ERESULT         eRc = ERESULT_SUCCESS;
    BPT32_DATA      *pObj = OBJ_NIL;
    PATH_DATA       *pPath = OBJ_NIL;
    bool            fRc;
    uint32_t        i;
    uint32_t        iMax;
    uint32_t        data;
    const
    uint32_t        blockSize = 64;
    //              // Blocksize == 64, Max Records for Leaf == 5
    //              // Blocksize == 64, Max Records for Index == 5
    //              // We chose 64 because it works in a hex dump of
    //              // the file nicely.
    const
    uint32_t        cKeysAdded = 31;
    static
    const
    uint32_t        keysAdded[cKeysAdded] = {
        8,17,36,42,53,56,65,72,73,75,
        77,81,83,96,98,102,104,107,112,117,
        119,121,123,125,127,131,133,135,137,139,
        141
    };

    fprintf(stderr, "Performing: %s\n", pTestName);

    pPath = Path_NewA("/tmp/test.db");
    TestForNotNull(pPath, "Missing Path object");

    pObj = BPT32_New( );
    TestForNotNull(pObj, "Missing Test object");
    if (pObj) {

        //obj_TraceSet(pObj, true);       
        fRc = obj_IsKindOf(pObj, OBJ_IDENT_BPT32);
        TestForTrue(fRc, "Failed Ident Test");

        eRc = BPT32_SetupSizes(pObj, blockSize, sizeof(uint32_t), 4, 11);
        TestForSuccess("Failed Setup");
        BPT32_setMem(pObj, true);

        eRc = BPT32_Create(pObj, pPath);
        TestForSuccess("Failed Create");

        iMax = cKeysAdded;
        for (i=0; i<iMax; i++) {
            data = i + 1;
            eRc = BPT32_Add(pObj, keysAdded[i], &data);
            TestForSuccess("Failed Setup");
        }

        eRc = BPT32_Close(pObj, pPath);
        TestForSuccess("Failed Create");

        {
            ASTR_DATA       *pStr = BPT32_ToDebugString(pObj, 4);
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



ERESULT         Test_BPT32_Write01 (
    TEST_DATA       *this,
    const
    char            *pTestName
)
{
    ERESULT         eRc = ERESULT_SUCCESS;
    BPT32_DATA      *pObj = OBJ_NIL;
    PATH_DATA       *pPath = OBJ_NIL;
    bool            fRc;
    uint32_t        i;
    uint32_t        iMax;
    uint32_t        data;
    const
    uint32_t        blockSize = 64;
    //              // Blocksize == 64, Max Records for Leaf == 5
    //              // Blocksize == 64, Max Records for Index == 5
    //              // We chose 64 because it works in a hex dump of
    //              // the file nicely.
    const
    uint32_t        cKeysAdded = 31;
    static
	const
    uint32_t        keysAdded[cKeysAdded] = {
        8,17,36,42,53,56,65,72,73,75,
        77,81,83,96,98,102,104,107,112,117,
        119,121,123,125,127,131,133,135,137,139,
        141
    };


    fprintf(stderr, "Performing: %s\n", pTestName);

    pPath = Path_NewA("/tmp/test.db");
    TestForNotNull(pPath, "Missing Path object");

    pObj = BPT32_New( );
    TestForNotNull(pObj, "Missing Test object");
    if (pObj) {

        obj_TraceSet(pObj, true);
        fRc = obj_IsKindOf(pObj, OBJ_IDENT_BPT32);
        TestForTrue(fRc, "Failed Ident Test");

        eRc = BPT32_SetupSizes(pObj, blockSize, sizeof(uint32_t), 8, 11);
        TestForSuccess("Failed Setup");
        BPT32_setMem(pObj, true);

        eRc = BPT32_Create(pObj, pPath);
        TestForSuccess("Failed Create");

        iMax = cKeysAdded;
        for (i=0; i<iMax; i++) {
            data = keysAdded[i];
            eRc = BPT32_Add(pObj, data, &data);
            TestForSuccess("Failed Setup");
        }

        eRc = BPT32_Close(pObj, pPath);
        TestForSuccess("Failed Create");

        {
            ASTR_DATA       *pStr = BPT32_ToDebugString(pObj, 4);
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
    TestExec("OpenClose", Test_BPT32_OpenClose, NULL, NULL);
    //TestExec("Copy01", Test_BPT32_Copy01, pTest, NULL, NULL);
    TestExec("Test01", Test_BPT32_Test01, NULL, NULL);
    TestExec("Write01", Test_BPT32_Write01, NULL, NULL);

    obj_Release(pTest);
    pTest = OBJ_NIL;

    // Return to Operating System.
    return 0;
}



