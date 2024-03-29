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
#include    <Item_internal.h>
#include    <JsonIn.h>
#include    <SrcErrors.h>
#include    <szTbl.h>






ERESULT         Test_Item_OpenClose (
    TEST_DATA       *this,
    const
    char            *pTestName
)
{
    ERESULT         eRc = ERESULT_SUCCESS;
    ITEM_DATA       *pObj = OBJ_NIL;
    bool            fRc;
   
    fprintf(stderr, "Performing: %s\n", pTestName);

    pObj = Item_Alloc( );
    TestForNotNull(pObj, "Missing Test Alloc() object");
    pObj = Item_Init( pObj );
    TestForNotNull(pObj, "Missing Test Init() object");
    if (pObj) {

        //obj_TraceSet(pObj, true);       
        fRc = obj_IsKindOf(pObj, OBJ_IDENT_ITEM);
        TestForTrue(fRc, "Failed Ident Test");
        
        // Test something.
        TestForSuccess("test failed");

        obj_Release(pObj);
        pObj = OBJ_NIL;
    }

    fprintf(stderr, "...%s completed.\n\n\n", pTestName);
    return eRc;
}



ERESULT         Test_Item_Copy01 (
    TEST_DATA       *this,
    const
    char            *pTestName
)
{
    ERESULT         eRc = ERESULT_SUCCESS;
    ITEM_DATA       *pObj1 = OBJ_NIL;
    ITEM_DATA       *pObj2 = OBJ_NIL;
    bool            fRc;
    ASTR_DATA       *pStr = OBJ_NIL;
    int             iRc;
   
    fprintf(stderr, "Performing: %s\n", pTestName);

    pObj1 = Item_New( );
    TestForNotNull(pObj1, "Missing Test object");
    if (pObj1) {

        //obj_TraceSet(pObj1, true);       
        fRc = obj_IsKindOf(pObj1, OBJ_IDENT_ITEM);
        TestForTrue(fRc, "Failed Ident Test");
        
        eRc = Item_SetupA(pObj1, NULL, "xyzzy.pdf", "Xyzzy", "a", "b", NULL);
        TestForSuccess("");
        eRc = Item_AddKeyWordsA(pObj1, "x", "y", NULL);
        TestForSuccess("");
        Item_setType(pObj1, ITEM_TYPE_LINK);
        {
            ASTR_DATA       *pStr = Item_ToDebugString(pObj1, 4);
            if (pStr) {
                fprintf(stderr, "Setup1: %s\n", AStr_getData(pStr));
                obj_Release(pStr);
                pStr = OBJ_NIL;
            }
        }

        // Test assign.
        pObj2 = Item_New();
        TestForNotNull(pObj2, "Missing copied object");
        eRc = Item_Assign(pObj1, pObj2);
        TestForFalse((ERESULT_FAILED(eRc)), "Assignment failed");

        fRc = obj_IsKindOf(pObj2, OBJ_IDENT_ITEM);
        TestForTrue(fRc, "Failed Ident Test");
        TestForTrue((ITEM_TYPE_LINK == pObj2->type), "");
        {
            ASTR_DATA       *pStr = Item_ToDebugString(pObj2, 4);
            if (pStr) {
                fprintf(stderr, "Assign2: %s\n", AStr_getData(pStr));
                obj_Release(pStr);
                pStr = OBJ_NIL;
            }
        }

        obj_Release(pObj2);
        pObj2 = OBJ_NIL;

        // Test copy.
        pObj2 = Item_Copy(pObj1);
        TestForNotNull(pObj2, "Missing copied object");

        fRc = obj_IsKindOf(pObj2, OBJ_IDENT_ITEM);
        TestForTrue(fRc, "Failed Ident Test");
        TestForTrue((ITEM_TYPE_LINK == pObj2->type), "");
        {
            ASTR_DATA       *pStr = Item_ToDebugString(pObj2, 4);
            if (pStr) {
                fprintf(stderr, "Copy2: %s\n", AStr_getData(pStr));
                obj_Release(pStr);
                pStr = OBJ_NIL;
            }
        }

        obj_Release(pObj2);
        pObj2 = OBJ_NIL;

        // Test json support.
        pStr = Item_ToJson(pObj1);
        TestForNotNull(pStr, "Missing JSON output");
        fprintf(stderr, "JSON: %s\n", AStr_getData(pStr));
        pObj2 = Item_NewFromJsonString(pStr);
        TestForNotNull(pObj2, "Missing JSON created object");
        fRc = obj_IsKindOf(pObj2, OBJ_IDENT_ITEM);
        TestForTrue(fRc, "Failed Ident Test");
        TestForTrue((ITEM_TYPE_LINK == pObj2->type), "");
        obj_Release(pStr);
        pStr = OBJ_NIL;
        {
            ASTR_DATA       *pStr = Item_ToDebugString(pObj2, 4);
            if (pStr) {
                fprintf(stderr, "JSON2: %s\n", AStr_getData(pStr));
                obj_Release(pStr);
                pStr = OBJ_NIL;
            }
        }
        iRc = AStrArray_getSize(Item_getHeadings(pObj2));
        TestForTrue((2 == iRc), "");
        iRc = AStrArray_getSize(Item_getKeyWords(pObj2));
        TestForTrue((2 == iRc), "");

        obj_Release(pObj2);
        pObj2 = OBJ_NIL;

        obj_Release(pObj1);
        pObj1 = OBJ_NIL;
    }

    fprintf(stderr, "...%s completed.\n\n\n", pTestName);
    return eRc;
}



ERESULT         Test_Item_Test01 (
    TEST_DATA       *this,
    const
    char            *pTestName
)
{
    ERESULT         eRc = ERESULT_SUCCESS;
    ITEM_DATA       *pObj = OBJ_NIL;
    bool            fRc;
   
    fprintf(stderr, "Performing: %s\n", pTestName);

    pObj = Item_New( );
    TestForNotNull(pObj, "Missing Test object");
    if (pObj) {

        //obj_TraceSet(pObj, true);       
        fRc = obj_IsKindOf(pObj, OBJ_IDENT_ITEM);
        TestForTrue(fRc, "Failed Ident Test");
        
        {
            ASTR_DATA       *pStr = Item_ToDebugString(pObj, 4);
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



ERESULT         Test_Item_Test02 (
    TEST_DATA       *this,
    const
    char            *pTestName
)
{
    ERESULT         eRc = ERESULT_SUCCESS;
    ITEM_DATA       *pObj = OBJ_NIL;
    bool            fRc;
    int             iRc;
    ASTR_DATA       *pStr = OBJ_NIL;

    fprintf(stderr, "Performing: %s\n", pTestName);

    pObj = Item_New( );
    TestForNotNull(pObj, "Missing Test object");
    if (pObj) {

        //obj_TraceSet(pObj, true);
        fRc = obj_IsKindOf(pObj, OBJ_IDENT_ITEM);
        TestForTrue(fRc, "Failed Ident Test");

        eRc = Item_SetupA(pObj, NULL, "xyzzy.pdf", "Xyzzy", NULL);
        TestForSuccess("");

        pStr = AStr_New();
        TestForNotNull(pStr, "");
        eRc = Item_Generate(pObj, pStr);
        TestForSuccess("");
        fprintf(stderr, "\tlink: %s\n", AStr_getData(pStr));
        iRc = AStr_CompareA(pStr,   "<li><a href=\"./xyzzy.pdf\" "
                                    "target=\"_blank\">Xyzzy</a></li>");
        TestForTrue((0 == iRc), "");
        obj_Release(pStr);
        pStr = OBJ_NIL;

        {
            ASTR_DATA       *pStr = Item_ToDebugString(pObj, 4);
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



ERESULT         Test_Item_Test03 (
    TEST_DATA       *this,
    const
    char            *pTestName
)
{
    ERESULT         eRc = ERESULT_SUCCESS;
    ITEM_DATA       *pObj = OBJ_NIL;
    bool            fRc;

    fprintf(stderr, "Performing: %s\n", pTestName);

    pObj = Item_New( );
    TestForNotNull(pObj, "Missing Test object");
    if (pObj) {

        //obj_TraceSet(pObj, true);
        fRc = obj_IsKindOf(pObj, OBJ_IDENT_ITEM);
        TestForTrue(fRc, "Failed Ident Test");

        {
            ASTR_DATA       *pStr = Item_ToDebugString(pObj, 4);
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



ERESULT         Test_Item_Test04 (
    TEST_DATA       *this,
    const
    char            *pTestName
)
{
    ERESULT         eRc = ERESULT_SUCCESS;
    ITEM_DATA       *pObj = OBJ_NIL;
    bool            fRc;

    fprintf(stderr, "Performing: %s\n", pTestName);

    pObj = Item_New( );
    TestForNotNull(pObj, "Missing Test object");
    if (pObj) {

        //obj_TraceSet(pObj, true);
        fRc = obj_IsKindOf(pObj, OBJ_IDENT_ITEM);
        TestForTrue(fRc, "Failed Ident Test");

        eRc = Item_SetupA(pObj, NULL, "xyzzy.pdf", "Xyzzy", "a", "b", NULL);
        TestForSuccess("");
        eRc = Item_AddKeyWordsA(pObj, "x", "y", NULL);
        TestForSuccess("");

        {
            ASTR_DATA       *pStr = Item_ToDebugString(pObj, 4);
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
    TestExec("OpenClose", Test_Item_OpenClose, NULL, NULL);
    TestExec("Copy01", Test_Item_Copy01, NULL, NULL);
    TestExec("Test01", Test_Item_Test01, NULL, NULL);
    TestExec("Test02", Test_Item_Test02, NULL, NULL);
    TestExec("Test03", Test_Item_Test03, NULL, NULL);
    TestExec("Test04", Test_Item_Test04, NULL, NULL);

    obj_Release(pTest);
    pTest = OBJ_NIL;

    // Return to Operating System.
    return 0;
}



