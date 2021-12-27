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
#include    <Misc_internal.h>
#include    <JsonIn.h>
#include    <SrcErrors.h>
#include    <szTbl.h>


/*
    Example Data for Binary String Search
 */
typedef enum Item_Type_e {
    ITEM_TYPE_UNKNOWN=0,
    ITEM_TYPE_COMMENT=1,
    ITEM_TYPE_GENERAL=2,
    ITEM_TYPE_HEADING=3,
    ITEM_TYPE_LINK=4,
    ITEM_TYPE_TITLE=5,
    ITEM_TYPE_WEBSITES=6,
} ITEM_TYPES;

typedef struct {
    const
    char            *pEnum;
    char            *pDesc;
    char            *pName;
    uint32_t        value;
} Item_Type_entry;

static
const
Item_Type_entry    Item_Type_entries[] = {
    {"ITEM_TYPE_COMMENT", "", "COMMENT", 1},
    {"ITEM_TYPE_GENERAL", "", "GENERAL", 2},
    {"ITEM_TYPE_HEADING", "", "HEADING", 3},
    {"ITEM_TYPE_LINK", "", "LINK", 4},
    {"ITEM_TYPE_TITLE", "", "TITLE", 5},
    {"ITEM_TYPE_UNKNOWN", "", "UNKNOWN", 0},
    {"ITEM_TYPE_WEBSITES", "", "WEBSITES", 6},
};

static
uint32_t    cItem_Type_entries = 7;





ERESULT         Test_Misc_OpenClose (
    TEST_DATA       *this,
    const
    char            *pTestName
)
{
    ERESULT         eRc = ERESULT_SUCCESS;
    MISC_DATA       *pObj = OBJ_NIL;
    bool            fRc;
   
    fprintf(stderr, "Performing: %s\n", pTestName);

    pObj = Misc_Alloc( );
    TestForNotNull(pObj, "Missing Test Alloc() object");
    pObj = Misc_Init( pObj );
    TestForNotNull(pObj, "Missing Test Init() object");
    if (pObj) {

        //obj_TraceSet(pObj, true);       
        fRc = obj_IsKindOf(pObj, OBJ_IDENT_MISC);
        TestForTrue(fRc, "Failed Ident Test");
#ifdef   MISC_MSGS
        Misc_setMsg(pObj, (void *)Test_MsgInfo, (void *)Test_MsgWarn, this);
#endif
        
        // Test something.
        TestForSuccess("test failed");

        obj_Release(pObj);
        pObj = OBJ_NIL;
    }

    fprintf(stderr, "...%s completed.\n\n\n", pTestName);
    return eRc;
}



ERESULT         Test_Misc_Copy01 (
    TEST_DATA       *this,
    const
    char            *pTestName
)
{
    ERESULT         eRc = ERESULT_SUCCESS;
    MISC_DATA       *pObj1 = OBJ_NIL;
    MISC_DATA       *pObj2 = OBJ_NIL;
    bool            fRc;
#if defined(MISC_JSON_SUPPORT) && defined(XYZZY)
    ASTR_DATA       *pStr = OBJ_NIL;
#endif
    //int             iRc;
   
    fprintf(stderr, "Performing: %s\n", pTestName);

    pObj1 = Misc_New( );
    TestForNotNull(pObj1, "Missing Test object");
    if (pObj1) {

        //obj_TraceSet(pObj1, true);       
        fRc = obj_IsKindOf(pObj1, OBJ_IDENT_MISC);
        TestForTrue(fRc, "Failed Ident Test");
#ifdef   MISC_MSGS
        Misc_setMsg(pObj1, (void *)Test_MsgInfo, (void *)Test_MsgWarn, this);
#endif
        
        // Test assign.
        pObj2 = Misc_New();
        TestForNotNull(pObj2, "Missing copied object");
        eRc = Misc_Assign(pObj1, pObj2);
        TestForFalse((ERESULT_FAILED(eRc)), "Assignment failed");

        fRc = obj_IsKindOf(pObj2, OBJ_IDENT_MISC);
        TestForTrue(fRc, "Failed Ident Test");
        //iRc = Misc_Compare(pObj1, pObj2);
        //TestForTrue((0 == iRc), "Failed Compare");
        //TODO: Add More tests here!

        obj_Release(pObj2);
        pObj2 = OBJ_NIL;

        // Test copy.
        pObj2 = Misc_Copy(pObj1);
        TestForNotNull(pObj2, "Missing copied object");

        fRc = obj_IsKindOf(pObj2, OBJ_IDENT_MISC);
        TestForTrue(fRc, "Failed Ident Test");
        //iRc = Misc_Compare(pObj1, pObj2);
        //TestForTrue((0 == iRc), "Failed Compare");
        //TODO: Add More tests here!

        obj_Release(pObj2);
        pObj2 = OBJ_NIL;

        // Test json support.
#if defined(MISC_JSON_SUPPORT) && defined(XYZZY)
        pStr = Misc_ToJson(pObj1);
        TestForNotNull(pStr, "Missing JSON output");
        fprintf(stderr, "JSON: %s\n", AStr_getData(pStr));
        pObj2 = Misc_NewFromJsonString(pStr);
        TestForNotNull(pObj2, "Missing JSON created object");
        fRc = obj_IsKindOf(pObj2, OBJ_IDENT_MISC);
        TestForTrue(fRc, "Failed Ident Test");
        obj_Release(pStr);
        pStr = OBJ_NIL;
        //iRc = Misc_Compare(pObj1, pObj2);
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



ERESULT         Test_Misc_Test01 (
    TEST_DATA       *this,
    const
    char            *pTestName
)
{
    ERESULT         eRc = ERESULT_SUCCESS;
    MISC_DATA       *pObj = OBJ_NIL;
    bool            fRc;
    Item_Type_entry *pEntry = NULL;
    uint32_t        value = 0;

    fprintf(stderr, "Performing: %s\n", pTestName);

    pObj = Misc_New( );
    TestForNotNull(pObj, "Missing Test object");
    if (pObj) {

        //obj_TraceSet(pObj, true);       
        fRc = obj_IsKindOf(pObj, OBJ_IDENT_MISC);
        TestForTrue(fRc, "Failed Ident Test");
        TestForSuccess("");
#ifdef   MISC_LOG
        Misc_setLog(pObj, this);
#endif
                
        pEntry = Misc_SearchBinaryStrA(
                    "ITEM_TYPE_COMMENT",
                    (void *)Item_Type_entries,
                    cItem_Type_entries,
                    sizeof(Item_Type_entry),
                    offsetof(Item_Type_entry, pEnum)
            );
        TestForNotNull(pEntry, "");
        if (pEntry) {
            value = pEntry->value;
        }
        TestForTrue((ITEM_TYPE_COMMENT == value), "");

        pEntry = Misc_SearchBinaryStrA(
                    "ITEM_TYPE_WEBSITES",
                    (void *)Item_Type_entries,
                    cItem_Type_entries,
                    sizeof(Item_Type_entry),
                    offsetof(Item_Type_entry, pEnum)
            );
        TestForNotNull(pEntry, "");
        if (pEntry) {
            value = pEntry->value;
        }
        TestForTrue((ITEM_TYPE_WEBSITES == value), "");

        pEntry = Misc_SearchBinaryStrA(
                    "ITEM_TYPE_UNKNOWN",
                    (void *)Item_Type_entries,
                    cItem_Type_entries,
                    sizeof(Item_Type_entry),
                    offsetof(Item_Type_entry, pEnum)
            );
        TestForNotNull(pEntry, "");
        if (pEntry) {
            value = pEntry->value;
        }
        TestForTrue((ITEM_TYPE_UNKNOWN == value), "");

        pEntry = Misc_SearchBinaryStrA(
                    "ITEM_TYPE_XYZZY",
                    (void *)Item_Type_entries,
                    cItem_Type_entries,
                    sizeof(Item_Type_entry),
                    offsetof(Item_Type_entry, pEnum)
            );
        TestForNull(pEntry, "");

        obj_Release(pObj);
        pObj = OBJ_NIL;
    }

    fprintf(stderr, "...%s completed.\n\n\n", pTestName);
    return eRc;
}



ERESULT         Test_Misc_Test02 (
    TEST_DATA       *this,
    const
    char            *pTestName
)
{
    ERESULT         eRc = ERESULT_SUCCESS;
    MISC_DATA       *pObj = OBJ_NIL;
    bool            fRc;
    uint64_t        amt;
    uint64_t        amt2;

    fprintf(stderr, "Performing: %s\n", pTestName);

    pObj = Misc_New( );
    TestForNotNull(pObj, "Missing Test object");
    if (pObj) {

        //obj_TraceSet(pObj, true);
        fRc = obj_IsKindOf(pObj, OBJ_IDENT_MISC);
        TestForTrue(fRc, "Failed Ident Test");
        TestForSuccess("");
#ifdef   MISC_LOG
        Misc_setLog(pObj, this);
#endif

        fRc = Misc_IsPrime(2049);
        TestForFalse(fRc, "");
        fRc = Misc_IsPrime(2051);
        TestForFalse(fRc, "");
        fRc = Misc_IsPrime(2053);
        TestForTrue(fRc, "");
        fRc = Misc_IsPrime(2057);
        TestForFalse(fRc, "");

        fRc = Misc_IsPrime(4097);
        TestForFalse(fRc, "");
        fRc = Misc_IsPrime(4099);
        TestForTrue(fRc, "");
        fRc = Misc_IsPrime(4101);
        TestForFalse(fRc, "");
        fRc = Misc_IsPrime(4103);
        TestForFalse(fRc, "");

        fRc = Misc_IsPrime(8209);
        TestForTrue(fRc, "");

        fRc = Misc_IsPrime(16411);
        TestForTrue(fRc, "");

        amt = 2147483648;
        amt2 = amt - 1;
        fRc = false;
        while (!fRc) {
            amt2 += 2;
            fRc = Misc_IsPrime(amt2);
        }
        fprintf(stderr, "\tPrime for %lld is %lld\n", amt, amt2);
        TestForTrue((2147483659 == amt2), "");

        obj_Release(pObj);
        pObj = OBJ_NIL;
    }

    fprintf(stderr, "...%s completed.\n\n\n", pTestName);
    return eRc;
}



ERESULT         Test_Misc_Test03 (
    TEST_DATA       *this,
    const
    char            *pTestName
)
{
    ERESULT         eRc = ERESULT_SUCCESS;
    MISC_DATA       *pObj = OBJ_NIL;
    bool            fRc;

    fprintf(stderr, "Performing: %s\n", pTestName);

    pObj = Misc_New( );
    TestForNotNull(pObj, "Missing Test object");
    if (pObj) {

        //obj_TraceSet(pObj, true);
        fRc = obj_IsKindOf(pObj, OBJ_IDENT_MISC);
        TestForTrue(fRc, "Failed Ident Test");
        TestForSuccess("");
#ifdef   MISC_LOG
        Misc_setLog(pObj, this);
#endif

        fRc = Misc_PatternMatchA("*.dmg","xyzzy.dmg",NULL,NULL);
        TestForTrue(fRc, "");
        fRc = Misc_PatternMatchA("*.dmg","xyzzy.txt",NULL,NULL);
        TestForFalse(fRc, "");
        fRc = Misc_PatternMatchA("x*.txt","xyzzy.txt",NULL,NULL);
        TestForTrue(fRc, "");
        fRc = Misc_PatternMatchA("x*.t*","xyzzy.txt",NULL,NULL);
        TestForTrue(fRc, "");
        fRc = Misc_PatternMatchA("x*.??t","xyzzy.txt",NULL,NULL);
        TestForTrue(fRc, "");
        fRc = Misc_PatternMatchA("x*.*t","xyzzy.txt",NULL,NULL);
        TestForTrue(fRc, "");
        fRc = Misc_PatternMatchA("x?zz?.dmg","xyzzy.dmg",NULL,NULL);
        TestForTrue(fRc, "");
        fRc = Misc_PatternMatchA("x?zy?.dmg","xyzzy.dmg",NULL,NULL);
        TestForFalse(fRc, "");
        fRc = Misc_PatternMatchA("x?zz?.*","xyzzy.dmg",NULL,NULL);
        TestForTrue(fRc, "");
        fRc = Misc_PatternMatchA("*y.??t","xyzzy.txt",NULL,NULL);
        TestForTrue(fRc, "");
        fRc = Misc_PatternMatchA("/usr/bin/grep", "/usr/bin/grep",NULL,NULL);
        TestForTrue(fRc, "");
        fRc = Misc_PatternMatchA("/usr/bin/*", "/usr/bin/grep",NULL,NULL);
        TestForTrue(fRc, "");
        fRc = Misc_PatternMatchA("/usr/*/grep", "/usr/bin/grep",NULL,NULL);
        TestForTrue(fRc, "");
        fRc = Misc_PatternMatchA("/*/bin/grep", "/usr/bin/grep",NULL,NULL);
        TestForTrue(fRc, "");

        obj_Release(pObj);
        pObj = OBJ_NIL;
    }

    fprintf(stderr, "...%s completed.\n\n\n", pTestName);
    return eRc;
}



ERESULT         Test_Misc_Test04 (
    TEST_DATA       *this,
    const
    char            *pTestName
)
{
    ERESULT         eRc = ERESULT_SUCCESS;
    MISC_DATA       *pObj = OBJ_NIL;
    bool            fRc;

    fprintf(stderr, "Performing: %s\n", pTestName);

    pObj = Misc_New( );
    TestForNotNull(pObj, "Missing Test object");
    if (pObj) {

        //obj_TraceSet(pObj, true);
        fRc = obj_IsKindOf(pObj, OBJ_IDENT_MISC);
        TestForTrue(fRc, "Failed Ident Test");
        TestForSuccess("");
#ifdef   MISC_LOG
        Misc_setLog(pObj, this);
#endif

        fRc = Misc_IsEvenParity8(0x01);
        TestForFalse(fRc, "");
        fRc = Misc_IsEvenParity8(0x02);
        TestForFalse(fRc, "");
        fRc = Misc_IsEvenParity8(0x04);
        TestForFalse(fRc, "");
        fRc = Misc_IsEvenParity8(0x08);
        TestForFalse(fRc, "");
        fRc = Misc_IsEvenParity8(0x10);
        TestForFalse(fRc, "");
        fRc = Misc_IsEvenParity8(0x20);
        TestForFalse(fRc, "");
        fRc = Misc_IsEvenParity8(0x40);
        TestForFalse(fRc, "");
        fRc = Misc_IsEvenParity8(0x80);
        TestForFalse(fRc, "");

        fRc = Misc_IsEvenParity8(0x00);
        TestForTrue(fRc, "");
        fRc = Misc_IsEvenParity8(0x11);
        TestForTrue(fRc, "");
        fRc = Misc_IsEvenParity8(0x22);
        TestForTrue(fRc, "");
        fRc = Misc_IsEvenParity8(0x44);
        TestForTrue(fRc, "");
        fRc = Misc_IsEvenParity8(0x88);
        TestForTrue(fRc, "");


        obj_Release(pObj);
        pObj = OBJ_NIL;
    }

    fprintf(stderr, "...%s completed.\n\n\n", pTestName);
    return eRc;
}



ERESULT         Test_Misc_Test05 (
    TEST_DATA       *this,
    const
    char            *pTestName
)
{
    ERESULT         eRc = ERESULT_SUCCESS;
    MISC_DATA       *pObj = OBJ_NIL;
    bool            fRc;

    fprintf(stderr, "Performing: %s\n", pTestName);

    pObj = Misc_New( );
    TestForNotNull(pObj, "Missing Test object");
    if (pObj) {

        //obj_TraceSet(pObj, true);
        fRc = obj_IsKindOf(pObj, OBJ_IDENT_MISC);
        TestForTrue(fRc, "Failed Ident Test");
        TestForSuccess("");
#ifdef   MISC_LOG
        Misc_setLog(pObj, this);
#endif

        fRc = Misc_AbbrevA("EXACT", "EXACT");
        TestForTrue(fRc, "");
        fRc = Misc_AbbrevA("EXACT", "exact");
        TestForTrue(fRc, "");
        fRc = Misc_AbbrevA("EXACT", "e");
        TestForFalse(fRc, "");
        fRc = Misc_AbbrevA("Exact", "e");
        TestForTrue(fRc, "");
        fRc = Misc_AbbrevA("eXact", "x");
        TestForTrue(fRc, "");
        fRc = Misc_AbbrevA("eXact", "ext");
        TestForTrue(fRc, "");
        fRc = Misc_AbbrevA("eXact", "xray");
        TestForFalse(fRc, "");

        obj_Release(pObj);
        pObj = OBJ_NIL;
    }

    fprintf(stderr, "...%s completed.\n\n\n", pTestName);
    return eRc;
}



ERESULT         Test_Misc_Test06 (
    TEST_DATA       *this,
    const
    char            *pTestName
)
{
    ERESULT         eRc = ERESULT_SUCCESS;
    MISC_DATA       *pObj = OBJ_NIL;
    bool            fRc;
    uint32_t        u32;
    uint64_t        u64;

    fprintf(stderr, "Performing: %s\n", pTestName);

    pObj = Misc_New( );
    TestForNotNull(pObj, "Missing Test object");
    if (pObj) {

        //obj_TraceSet(pObj, true);
        fRc = obj_IsKindOf(pObj, OBJ_IDENT_MISC);
        TestForTrue(fRc, "Failed Ident Test");
        TestForSuccess("");
#ifdef   MISC_LOG
        Misc_setLog(pObj, this);
#endif

        u32 = Misc_BitReversal32(0x00000001);
        TestForTrue((u32 == 0x80000000), "");
        u32 = Misc_BitReversal32(0x80000000);
        TestForTrue((u32 == 0x00000001), "");
        u32 = Misc_BitReversal32(0x80000001);
        TestForTrue((u32 == 0x80000001), "");

        u64 = Misc_BitReversal64(0x0000000000000001);
        TestForTrue((u64 == 0x8000000000000000), "");
        u64 = Misc_BitReversal64(0x8000000000000000);
        TestForTrue((u64 == 0x0000000000000001), "");

        obj_Release(pObj);
        pObj = OBJ_NIL;
    }

    fprintf(stderr, "...%s completed.\n\n\n", pTestName);
    return eRc;
}



ERESULT         Test_Misc_Test07 (
    TEST_DATA       *this,
    const
    char            *pTestName
)
{
    ERESULT         eRc = ERESULT_SUCCESS;
    MISC_DATA       *pObj = OBJ_NIL;
    bool            fRc;

    fprintf(stderr, "Performing: %s\n", pTestName);

    pObj = Misc_New( );
    TestForNotNull(pObj, "Missing Test object");
    if (pObj) {

        //obj_TraceSet(pObj, true);
        fRc = obj_IsKindOf(pObj, OBJ_IDENT_MISC);
        TestForTrue(fRc, "Failed Ident Test");
        TestForSuccess("");
#ifdef   MISC_LOG
        Misc_setLog(pObj, this);
#endif

        {
            ASTR_DATA       *pStr = Misc_ToDebugString(pObj, 4);
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



ERESULT         Test_Misc_Test08 (
    TEST_DATA       *this,
    const
    char            *pTestName
)
{
    ERESULT         eRc = ERESULT_SUCCESS;
    MISC_DATA       *pObj = OBJ_NIL;
    bool            fRc;

    fprintf(stderr, "Performing: %s\n", pTestName);

    pObj = Misc_New( );
    TestForNotNull(pObj, "Missing Test object");
    if (pObj) {

        //obj_TraceSet(pObj, true);
        fRc = obj_IsKindOf(pObj, OBJ_IDENT_MISC);
        TestForTrue(fRc, "Failed Ident Test");
        TestForSuccess("");
#ifdef   MISC_LOG
        Misc_setLog(pObj, this);
#endif

        {
            ASTR_DATA       *pStr = Misc_ToDebugString(pObj, 4);
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
    TestExec("OpenClose", Test_Misc_OpenClose, NULL, NULL);
    //TestExec("Copy01", Test_Misc_Copy01, NULL, NULL);
    TestExec("Test01", Test_Misc_Test01, NULL, NULL);
    TestExec("Test02", Test_Misc_Test02, NULL, NULL);
    TestExec("Test03", Test_Misc_Test03, NULL, NULL);
    TestExec("Test04", Test_Misc_Test04, NULL, NULL);
    TestExec("Test05", Test_Misc_Test05, NULL, NULL);
    TestExec("Test06", Test_Misc_Test06, NULL, NULL);
    TestExec("Test07", Test_Misc_Test07, NULL, NULL);
    TestExec("Test08", Test_Misc_Test08, NULL, NULL);

    obj_Release(pTest);
    pTest = OBJ_NIL;

    // Return to Operating System.
    return 0;
}



