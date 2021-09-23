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
#include    <Endian_internal.h>
#include    <JsonIn.h>
#include    <SrcErrors.h>
#include    <szTbl.h>






ERESULT         Test_Endian_OpenClose (
    TEST_DATA       *this,
    const
    char            *pTestName
)
{
    ERESULT         eRc = ERESULT_SUCCESS;
    ENDIAN_DATA       *pObj = OBJ_NIL;
    bool            fRc;
   
    fprintf(stderr, "Performing: %s\n", pTestName);

    pObj = Endian_Alloc( );
    TestForNotNull(pObj, "Missing Test Alloc() object");
    pObj = Endian_Init( pObj );
    TestForNotNull(pObj, "Missing Test Init() object");
    if (pObj) {

        //obj_TraceSet(pObj, true);       
        fRc = obj_IsKindOf(pObj, OBJ_IDENT_ENDIAN);
        TestForTrue(fRc, "Failed Ident Test");
        
        // Test something.
        TestForSuccess("test failed");

        obj_Release(pObj);
        pObj = OBJ_NIL;
    }

    fprintf(stderr, "...%s completed.\n\n\n", pTestName);
    return eRc;
}



ERESULT         Test_Endian_Copy01 (
    TEST_DATA       *this,
    const
    char            *pTestName
)
{
    ERESULT         eRc = ERESULT_SUCCESS;
    ENDIAN_DATA       *pObj1 = OBJ_NIL;
    ENDIAN_DATA       *pObj2 = OBJ_NIL;
    bool            fRc;
#if defined(ENDIAN_JSON_SUPPORT) && defined(XYZZY)
    ASTR_DATA       *pStr = OBJ_NIL;
#endif
    //int             iRc;
   
    fprintf(stderr, "Performing: %s\n", pTestName);

    pObj1 = Endian_New( );
    TestForNotNull(pObj1, "Missing Test object");
    if (pObj1) {

        //obj_TraceSet(pObj1, true);       
        fRc = obj_IsKindOf(pObj1, OBJ_IDENT_ENDIAN);
        TestForTrue(fRc, "Failed Ident Test");
        
        // Test assign.
        pObj2 = Endian_New();
        TestForNotNull(pObj2, "Missing copied object");
        eRc = Endian_Assign(pObj1, pObj2);
        TestForFalse((ERESULT_FAILED(eRc)), "Assignment failed");

        fRc = obj_IsKindOf(pObj2, OBJ_IDENT_ENDIAN);
        TestForTrue(fRc, "Failed Ident Test");
        //iRc = Endian_Compare(pObj1, pObj2);
        //TestForTrue((0 == iRc), "Failed Compare");
        //TODO: Add More tests here!

        obj_Release(pObj2);
        pObj2 = OBJ_NIL;

        // Test copy.
        pObj2 = Endian_Copy(pObj1);
        TestForNotNull(pObj2, "Missing copied object");

        fRc = obj_IsKindOf(pObj2, OBJ_IDENT_ENDIAN);
        TestForTrue(fRc, "Failed Ident Test");
        //iRc = Endian_Compare(pObj1, pObj2);
        //TestForTrue((0 == iRc), "Failed Compare");
        //TODO: Add More tests here!

        obj_Release(pObj2);
        pObj2 = OBJ_NIL;

        // Test json support.
#if defined(ENDIAN_JSON_SUPPORT) && defined(XYZZY)
        pStr = Endian_ToJson(pObj1);
        TestForNotNull(pStr, "Missing JSON output");
        fprintf(stderr, "JSON: %s\n", AStr_getData(pStr));
        pObj2 = Endian_NewFromJsonString(pStr);
        TestForNotNull(pObj2, "Missing JSON created object");
        fRc = obj_IsKindOf(pObj2, OBJ_IDENT_ENDIAN);
        TestForTrue(fRc, "Failed Ident Test");
        obj_Release(pStr);
        pStr = OBJ_NIL;
        //iRc = Endian_Compare(pObj1, pObj2);
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



ERESULT         Test_Endian_Test01 (
    TEST_DATA       *this,
    const
    char            *pTestName
)
{
    ERESULT         eRc = ERESULT_SUCCESS;
    ENDIAN_DATA     *pObj = OBJ_NIL;
    bool            fRc;
    const
    uint16_t        cu16 = 0x0102;
    const
    uint32_t        cu24 = 0x00010203;
    const
    uint32_t        cu32 = 0x01020304;
    const
    uint64_t        cu64 = 0x0102030405060708;
    uint8_t         uout[9];
    int             i;
    uint16_t        u16 = 0x0102;
    uint32_t        u24 = 0x00010203;
    uint32_t        u32 = 0x01020304;
    uint64_t        u64 = 0x0102030405060708;

    fprintf(stderr, "Performing: %s\n", pTestName);

    pObj = Endian_New( );
    TestForNotNull(pObj, "Missing Test object");
    if (pObj) {

        //obj_TraceSet(pObj, true);       
        fRc = obj_IsKindOf(pObj, OBJ_IDENT_ENDIAN);
        TestForTrue(fRc, "Failed Ident Test");
        
        for (i=0; i<9; ++i) {
            uout[i] = 0;
        }
        Endian_PutU16Big(cu16, uout);
        TestForTrue((uout[0] == 0x01), "");
        TestForTrue((uout[1] == 0x02), "");
        TestForTrue((uout[2] == 0x00), "");
        u16 = Endian_GetU16Big(uout);
        TestForTrue((u16 == cu16), "");
        uout[0] = 0;
        uout[1] = 0;

        Endian_PutU24Big(cu24, uout);
        TestForTrue((uout[0] == 0x01), "");
        TestForTrue((uout[1] == 0x02), "");
        TestForTrue((uout[2] == 0x03), "");
        TestForTrue((uout[3] == 0x00), "");
        u24 = Endian_GetU24Big(uout);
        TestForTrue((u24 == cu24), "");
        uout[0] = 0;
        uout[1] = 0;
        uout[2] = 0;

        Endian_PutU32Big(cu32, uout);
        TestForTrue((uout[0] == 0x01), "");
        TestForTrue((uout[1] == 0x02), "");
        TestForTrue((uout[2] == 0x03), "");
        TestForTrue((uout[3] == 0x04), "");
        TestForTrue((uout[4] == 0x00), "");
        u32 = Endian_GetU32Big(uout);
        TestForTrue((u32 == cu32), "");
        uout[0] = 0;
        uout[1] = 0;
        uout[2] = 0;
        uout[3] = 0;
        uout[4] = 0;

        Endian_PutU64Big(cu64, uout);
        TestForTrue((uout[0] == 0x01), "");
        TestForTrue((uout[1] == 0x02), "");
        TestForTrue((uout[2] == 0x03), "");
        TestForTrue((uout[3] == 0x04), "");
        TestForTrue((uout[4] == 0x05), "");
        TestForTrue((uout[5] == 0x06), "");
        TestForTrue((uout[6] == 0x07), "");
        TestForTrue((uout[7] == 0x08), "");
        TestForTrue((uout[8] == 0x00), "");
        u64 = Endian_GetU64Big(uout);
        TestForTrue((u64 == cu64), "");

        for (i=0; i<9; ++i) {
            uout[i] = 0;
        }
        Endian_PutU16Little(cu16, uout);
        TestForTrue((uout[0] == 0x02), "");
        TestForTrue((uout[1] == 0x01), "");
        TestForTrue((uout[2] == 0x00), "");
        u16 = Endian_GetU16Little(uout);
        TestForTrue((u16 == cu16), "");
        uout[0] = 0;
        uout[1] = 0;

        Endian_PutU24Little(cu24, uout);
        TestForTrue((uout[0] == 0x03), "");
        TestForTrue((uout[1] == 0x02), "");
        TestForTrue((uout[2] == 0x01), "");
        TestForTrue((uout[3] == 0x00), "");
        u24 = Endian_GetU24Little(uout);
        TestForTrue((u16 == cu16), "");
        uout[0] = 0;
        uout[1] = 0;
        uout[2] = 0;

        Endian_PutU32Little(cu32, uout);
        TestForTrue((uout[0] == 0x04), "");
        TestForTrue((uout[1] == 0x03), "");
        TestForTrue((uout[2] == 0x02), "");
        TestForTrue((uout[3] == 0x01), "");
        TestForTrue((uout[4] == 0x00), "");
        u32 = Endian_GetU32Little(uout);
        TestForTrue((u32 == cu32), "");
        uout[0] = 0;
        uout[1] = 0;
        uout[2] = 0;
        uout[3] = 0;
        uout[4] = 0;

        Endian_PutU64Little(cu64, uout);
        TestForTrue((uout[0] == 0x08), "");
        TestForTrue((uout[1] == 0x07), "");
        TestForTrue((uout[2] == 0x06), "");
        TestForTrue((uout[3] == 0x05), "");
        TestForTrue((uout[4] == 0x04), "");
        TestForTrue((uout[5] == 0x03), "");
        TestForTrue((uout[6] == 0x02), "");
        TestForTrue((uout[7] == 0x01), "");
        TestForTrue((uout[8] == 0x00), "");
        u64 = Endian_GetU64Little(uout);
        TestForTrue((u64 == cu64), "");

        obj_Release(pObj);
        pObj = OBJ_NIL;
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
    TestExec("OpenClose", Test_Endian_OpenClose, NULL, NULL);
    //TestExec("Copy01", Test_Endian_Copy01, pTest, NULL, NULL);
    TestExec("Test01", Test_Endian_Test01, NULL, NULL);

    obj_Release(pTest);
    pTest = OBJ_NIL;

    // Return to Operating System.
    return 0;
}



