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
#include    <Parser_internal.h>
#include    <JsonIn.h>
#include    <Lex_internal.h>
#include    <SrcErrors.h>
#include    <szTbl.h>






ERESULT         Test_Parser_OpenClose (
    TEST_DATA       *this,
    const
    char            *pTestName
)
{
    ERESULT         eRc = ERESULT_SUCCESS;
    PARSER_DATA       *pObj = OBJ_NIL;
    bool            fRc;
   
    fprintf(stderr, "Performing: %s\n", pTestName);

    pObj = Parser_Alloc( );
    TestForNotNull(pObj, "Missing Test Alloc() object");
    pObj = Parser_Init( pObj );
    TestForNotNull(pObj, "Missing Test Init() object");
    if (pObj) {

        //obj_TraceSet(pObj, true);       
        fRc = obj_IsKindOf(pObj, OBJ_IDENT_PARSER);
        TestForTrue(fRc, "Failed Ident Test");
#ifdef   PARSER_MSGS
        Parser_setMsg(pObj, (void *)Test_MsgInfo, (void *)Test_MsgWarn, this);
#endif
        
        // Test something.
        TestForSuccess("test failed");

        obj_Release(pObj);
        pObj = OBJ_NIL;
    }

    fprintf(stderr, "...%s completed.\n\n\n", pTestName);
    return eRc;
}



ERESULT         Test_Parser_Copy01 (
    TEST_DATA       *this,
    const
    char            *pTestName
)
{
    ERESULT         eRc = ERESULT_SUCCESS;
    PARSER_DATA       *pObj1 = OBJ_NIL;
    PARSER_DATA       *pObj2 = OBJ_NIL;
    bool            fRc;
#if defined(PARSER_JSON_SUPPORT) && defined(XYZZY)
    ASTR_DATA       *pStr = OBJ_NIL;
#endif
    //int             iRc;
   
    fprintf(stderr, "Performing: %s\n", pTestName);

    pObj1 = Parser_New( );
    TestForNotNull(pObj1, "Missing Test object");
    if (pObj1) {

        //obj_TraceSet(pObj1, true);       
        fRc = obj_IsKindOf(pObj1, OBJ_IDENT_PARSER);
        TestForTrue(fRc, "Failed Ident Test");
#ifdef   PARSER_MSGS
        Parser_setMsg(pObj1, (void *)Test_MsgInfo, (void *)Test_MsgWarn, this);
#endif
        
        // Test assign.
        pObj2 = Parser_New();
        TestForNotNull(pObj2, "Missing copied object");
        eRc = Parser_Assign(pObj1, pObj2);
        TestForFalse((ERESULT_FAILED(eRc)), "Assignment failed");

        fRc = obj_IsKindOf(pObj2, OBJ_IDENT_PARSER);
        TestForTrue(fRc, "Failed Ident Test");
        //iRc = Parser_Compare(pObj1, pObj2);
        //TestForTrue((0 == iRc), "Failed Compare");
        //TODO: Add More tests here!

        obj_Release(pObj2);
        pObj2 = OBJ_NIL;

        // Test copy.
        pObj2 = Parser_Copy(pObj1);
        TestForNotNull(pObj2, "Missing copied object");

        fRc = obj_IsKindOf(pObj2, OBJ_IDENT_PARSER);
        TestForTrue(fRc, "Failed Ident Test");
        //iRc = Parser_Compare(pObj1, pObj2);
        //TestForTrue((0 == iRc), "Failed Compare");
        //TODO: Add More tests here!

        obj_Release(pObj2);
        pObj2 = OBJ_NIL;

        // Test json support.
#if defined(PARSER_JSON_SUPPORT) && defined(XYZZY)
        pStr = Parser_ToJson(pObj1);
        TestForNotNull(pStr, "Missing JSON output");
        fprintf(stderr, "JSON: %s\n", AStr_getData(pStr));
        pObj2 = Parser_NewFromJsonString(pStr);
        TestForNotNull(pObj2, "Missing JSON created object");
        fRc = obj_IsKindOf(pObj2, OBJ_IDENT_PARSER);
        TestForTrue(fRc, "Failed Ident Test");
        obj_Release(pStr);
        pStr = OBJ_NIL;
        //iRc = Parser_Compare(pObj1, pObj2);
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



ERESULT         Test_Parser_Test01 (
    TEST_DATA       *this,
    const
    char            *pTestName
)
{
    ERESULT         eRc = ERESULT_SUCCESS;
    PARSER_DATA     *pObj = OBJ_NIL;
    bool            fRc;
   
    fprintf(stderr, "Performing: %s\n", pTestName);

    pObj = Parser_New( );
    TestForNotNull(pObj, "Missing Test object");
    if (pObj) {

        //obj_TraceSet(pObj, true);       
        fRc = obj_IsKindOf(pObj, OBJ_IDENT_PARSER);
        TestForTrue(fRc, "Failed Ident Test");
        TestForSuccess("");
#ifdef   PARSER_LOG
        Parser_setLog(pObj, this);
#endif
                
        {
            ASTR_DATA       *pStr = Parser_ToDebugString(pObj, 4);
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



ERESULT         Test_Parser_Test02 (
    TEST_DATA       *this,
    const
    char            *pTestName
)
{
    ERESULT         eRc = ERESULT_SUCCESS;
    PARSER_DATA     *pObj = OBJ_NIL;
    bool            fRc;

    fprintf(stderr, "Performing: %s\n", pTestName);

    pObj = Parser_New( );
    TestForNotNull(pObj, "Missing Test object");
    if (pObj) {

        //obj_TraceSet(pObj, true);
        fRc = obj_IsKindOf(pObj, OBJ_IDENT_PARSER);
        TestForTrue(fRc, "Failed Ident Test");
        TestForSuccess("");
#ifdef   PARSER_LOG
        Parser_setLog(pObj, this);
#endif

        {
            ASTR_DATA       *pStr = Parser_ToDebugString(pObj, 4);
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



ERESULT         Test_Parser_Test03 (
    TEST_DATA       *this,
    const
    char            *pTestName
)
{
    ERESULT         eRc = ERESULT_SUCCESS;
    PARSER_DATA     *pObj = OBJ_NIL;
    bool            fRc;

    fprintf(stderr, "Performing: %s\n", pTestName);

    pObj = Parser_New( );
    TestForNotNull(pObj, "Missing Test object");
    if (pObj) {

        //obj_TraceSet(pObj, true);
        fRc = obj_IsKindOf(pObj, OBJ_IDENT_PARSER);
        TestForTrue(fRc, "Failed Ident Test");
        TestForSuccess("");
#ifdef   PARSER_LOG
        Parser_setLog(pObj, this);
#endif

        {
            ASTR_DATA       *pStr = Parser_ToDebugString(pObj, 4);
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



ERESULT         Test_Parser_Test04 (
    TEST_DATA       *this,
    const
    char            *pTestName
)
{
    ERESULT         eRc = ERESULT_SUCCESS;
    PARSER_DATA     *pObj = OBJ_NIL;
    bool            fRc;
    NODE_DATA       *pNode1;
    NODE_DATA       *pNode2;

    fprintf(stderr, "Performing: %s\n", pTestName);

    pObj = Parser_New( );
    TestForNotNull(pObj, "Missing Test object");
    if (pObj) {

        //obj_TraceSet(pObj, true);
        fRc = obj_IsKindOf(pObj, OBJ_IDENT_PARSER);
        TestForTrue(fRc, "Failed Ident Test");
        TestForSuccess("");
#ifdef   PARSER_LOG
        Parser_setLog(pObj, this);
#endif

        TestForTrue((0 == Parser_PropertyCount(pObj)), "");
        pNode1 = Node_NewWithUTF8AndClass(0, "abc", OBJ_NIL);
        TestForNotNull(pNode1, "");
        eRc = Parser_PropertyAdd(pObj, pNode1);
        TestForSuccess("");
        TestForTrue((1 == Parser_PropertyCount(pObj)), "");
        pNode2 = Parser_Property(pObj, "abc");
        TestForTrue((pNode1 == pNode2), "");
        obj_Release(pNode1);
        pNode1 = OBJ_NIL;

        {
            ASTR_DATA       *pStr = Parser_ToDebugString(pObj, 4);
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



#ifdef XYZZY
/*          =>>> Keeping this just in case <<<=
 I am not certain if the parser should have the lexical scanner
 built into it. So, I have changed it slightly. If I changee my mind,
 I will add this tst and make certain that this test is implemented.
 */

/* This illustrates how to set up an external lexer and properly
    plug it into the Parser object.
 */
int         test_Parser_Lexer01(
    const
    char        *pTestName
)
{
    PARSER_DATA     *pObj = OBJ_NIL;
    //ERESULT         eRc;
    bool            fRc;
    LEX_DATA        *pLex = OBJ_NIL;
    PATH_DATA       *pPath = Path_NewA("abc");  // Used for error messages only
    TOKEN_DATA      *pToken = OBJ_NIL;
    SRCFILE_DATA    *pSrc = OBJ_NIL;
    ASTR_DATA       *pBuf = OBJ_NIL;

    fprintf(stderr, "Performing: %s\n", pTestName);

    pObj = Parser_New( );
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    if (pObj) {

        pBuf = AStr_NewA("a = b + c;");
        XCTAssertFalse( (OBJ_NIL == pBuf) );
        pSrc = SrcFile_NewFromAStr(pPath, pBuf, 1, 4);
        XCTAssertFalse( (OBJ_NIL == pSrc) );

        pLex = (LEX_DATA *)Lex_New();
        XCTAssertFalse( (OBJ_NIL == pLex) );

        fRc =   Lex_setSourceInput(
                                      pLex,
                                      (void *)SrcFile_InputAdvance,
                                      (void *)SrcFile_InputLookAhead,
                                      pSrc
                                      );
        XCTAssertTrue( (fRc) );

        Parser_setSourceFunction(
                                 pObj,
                                (void *)Lex_TokenAdvance,
                                (void *)Lex_TokenLookAhead,
                                pLex
        );
        Parser_setLex(pObj, pLex);
        obj_Release(pLex);
        pLex = OBJ_NIL;

        // Now we can get some data.
        pToken = Parser_InputLookAhead(pObj, 1);
        TINYTEST_FALSE( (OBJ_NIL == pToken) );
        {
            ASTR_DATA       *pStr = Token_ToDebugString(pToken, 0);
            if (pStr) {
                fprintf(stderr, "Token 1 (a): %s\n", AStr_getData(pStr));
                obj_Release(pStr);
                pStr = OBJ_NIL;
            }
        }
        TINYTEST_TRUE( (TOKEN_TYPE_CHAR == Token_getType(pToken)) );
        TINYTEST_TRUE( (LEX_IDENTIFIER == Token_getClass(pToken)) );
        Parser_InputAdvance(pObj, 1);

        pToken = Parser_InputLookAhead(pObj, 1);
        TINYTEST_FALSE( (OBJ_NIL == pToken) );
        {
            ASTR_DATA       *pStr = Token_ToDebugString(pToken, 0);
            if (pStr) {
                fprintf(stderr, "Token 2 (=): %s\n", AStr_getData(pStr));
                obj_Release(pStr);
                pStr = OBJ_NIL;
            }
        }
        TINYTEST_TRUE( (TOKEN_TYPE_CHAR == Token_getType(pToken)) );
        TINYTEST_TRUE( (LEX_OP_ASSIGN == Token_getClass(pToken)) );
        Parser_InputAdvance(pObj, 1);

        pToken = Parser_InputLookAhead(pObj, 1);
        TINYTEST_FALSE( (OBJ_NIL == pToken) );
        {
            ASTR_DATA       *pStr = Token_ToDebugString(pToken, 0);
            if (pStr) {
                fprintf(stderr, "Token 3 (b): %s\n", AStr_getData(pStr));
                obj_Release(pStr);
                pStr = OBJ_NIL;
            }
        }
        TINYTEST_TRUE( (TOKEN_TYPE_CHAR == Token_getType(pToken)) );
        TINYTEST_TRUE( (LEX_IDENTIFIER == Token_getClass(pToken)) );
        Parser_InputAdvance(pObj, 1);

        obj_Release(pObj);
        pObj = OBJ_NIL;
    }

    obj_Release(pSrc);
    pSrc = OBJ_NIL;

    obj_Release(pBuf);
    pBuf = OBJ_NIL;

    obj_Release(pPath);
    pPath = OBJ_NIL;

    fprintf(stderr, "...%s completed.\n\n", pTestName);
    return 1;
}


#endif




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
    TestExec("OpenClose", Test_Parser_OpenClose, NULL, NULL);
    //TestExec("Copy01", Test_Parser_Copy01, NULL, NULL);
    TestExec("Test01", Test_Parser_Test01, NULL, NULL);
    TestExec("Test02", Test_Parser_Test02, NULL, NULL);
    TestExec("Test03", Test_Parser_Test03, NULL, NULL);
    TestExec("Test04", Test_Parser_Test04, NULL, NULL);

    obj_Release(pTest);
    pTest = OBJ_NIL;

    // Return to Operating System.
    return 0;
}



