/*
 *	Generated 12/09/2017 07:54:00
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
#include    <JsonIn.h>
#include    <szTbl.h>
#include    <trace.h>
#include    <genObj_internal.h>
#include    <crc.h>



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

    
    szTbl_SharedReset( );
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






int         test_genObj_OpenClose(
    const
    char        *pTestName
)
{
    GENOBJ_DATA	*pObj = OBJ_NIL;
   
    fprintf(stderr, "Performing: %s\n", pTestName);

    pObj = genObj_Alloc( );
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    pObj = genObj_Init( pObj );
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    if (pObj) {

        // Test something.

        obj_Release(pObj);
        pObj = OBJ_NIL;
    }

    fprintf(stderr, "...%s completed.\n\n", pTestName);
    return 1;
}



int         test_genObj_License(
    const
    char            *pTestName
)
{
    GENOBJ_DATA     *pObj = OBJ_NIL;
    ASTR_DATA       *pStr = OBJ_NIL;
    ERESULT         eRc;
    int             iRc;
    int             offset = 0;
    const
    char            *pOutputA =
    "/*\n"
    " This is free and unencumbered software released into the public domain.\n"
    " \n"
    " Anyone is free to copy, modify, publish, use, compile, sell, or\n"
    " distribute this software, either in source code form or as a compiled\n"
    " binary, for any purpose, commercial or non-commercial, and by any\n"
    " means.\n"
    " \n"
    " In jurisdictions that recognize copyright laws, the author or authors\n"
    " of this software dedicate any and all copyright interest in the\n"
    " software to the public domain. We make this dedication for the benefit\n"
    " of the public at large and to the detriment of our heirs and\n"
    " successors. We intend this dedication to be an overt act of\n"
    " relinquishment in perpetuity of all present and future rights to this\n"
    " software under copyright law.\n"
    " \n"
    " THE SOFTWARE IS PROVIDED \"AS IS\", WITHOUT WARRANTY OF ANY KIND,\n"
    " EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF\n"
    " MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.\n"
    " IN NO EVENT SHALL THE AUTHORS BE LIABLE FOR ANY CLAIM, DAMAGES OR\n"
    " OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,\n"
    " ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR\n"
    " OTHER DEALINGS IN THE SOFTWARE.\n"
    " \n"
    " For more information, please refer to <http://unlicense.org/>\n"
    " \n"
    " */\n"
    "\n\n\n"
    ;

    fprintf(stderr, "Performing: %s\n", pTestName);
    
    pObj = genObj_New( );
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    if (pObj) {
        
        eRc = genObj_GenLicense(pObj, &pStr);
        TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );
        fprintf(stderr, "%s", AStr_getData(pStr));
        iRc = str_CompareSpcl(pOutputA, AStr_getData(pStr), &offset);
        fprintf(stderr, "\tiRc=%d  offset=%04X\n", iRc, offset);
        TINYTEST_TRUE( (0 == iRc) );
        obj_Release(pStr);
        pStr = OBJ_NIL;

        obj_Release(pObj);
        pObj = OBJ_NIL;
    }
    
    fprintf(stderr, "...%s completed.\n\n\n", pTestName);
    return 1;
}



int         test_genObj_Method01(
    const
    char            *pTestName
)
{
    GENOBJ_DATA     *pObj = OBJ_NIL;
    ASTR_DATA       *pStr = OBJ_NIL;
    ERESULT         eRc;
    int             iRc;
    int             offset = 0;
    const
    char            *pOutputA =
    "    //---------------------------------------------------------------\n"
    "    //\t\t\t                 a b c\n"
    "    //---------------------------------------------------------------\n"
    "\n"
    "    int\t\t\txyzzy_abc(\n"
    "    \tXYZZY_DATA\t*this\n"
    "    )\n"
    "    {\n"
    "    \tint\t\t\tiRet = 0;\n"
    "\n"
    "    \t// Do initialization.\n"
    "    #ifdef NDEBUG\n"
    "    #else\n"
    "    \tif (!xyzzy_Validate(this)) {\n"
    "    \t\tDEBUG_BREAK();\n"
    "    \t\treturn ERESULT_INVALID_OBJECT;\n"
    "    \t}\n"
    "    #endif\n"
    "\n"
    "\n"
    "    \t// Return to caller.\n"
    "    \treturn iRet;\n"
    "    }\n"
    "\n\n\n"
    ;
    const
    char            *pOutputB =
    "    //---------------------------------------------------------------\n"
    "    //\t\t\t                a b c 2\n"
    "    //---------------------------------------------------------------\n"
    "\n"
    "    static\n"
    "    int\t\t\txyzzy_abc2(\n"
    "    \tXYZZY_DATA\t*this,\n"
    "    \tconst\n"
    "    \tASTR_DATA\t\t*pStr\n"
    "    )\n"
    "    {\n"
    "    \tint\t\t\tiRet = 0;\n"
    "    \tconst\n"
    "    \tASTR_DATA\t\t*pStrWrk;\n"
    "\n"
    "    \t// Do initialization.\n"
    "    #ifdef NDEBUG\n"
    "    #else\n"
    "    \tif (!xyzzy_Validate(this)) {\n"
    "    \t\tDEBUG_BREAK();\n"
    "    \t\treturn ERESULT_INVALID_OBJECT;\n"
    "    \t}\n"
    "    #endif\n"
    "\n"
    "\n"
    "    \t// Return to caller.\n"
    "    \treturn iRet;\n"
    "    }\n"
    "\n\n\n"
    ;
    // Alignment is automatically \t\t for ParmDefs.
    const
    char        *pParmDefsB[] = {
        "const\n",
        "ASTR_DATA\t\t*pStr\n",
        NULL
    };
    // Alignment is automatically \t\t for DataDefs.
    const
    char        *pDataDefsB[] = {
        "const\n",
        "ASTR_DATA\t\t*pStrWrk;\n",
        NULL
    };
    const
    char            *pOutputC =
    "    //---------------------------------------------------------------\n"
    "    //\t\t\t                a b c 3\n"
    "    //---------------------------------------------------------------\n"
    "\n"
    "    static\n"
    "    int\t\t\txyzzy_abc3(\n"
    "    \tXYZZY_DATA\t*this\n"
    "    )\n"
    "    {\n"
    "    \tint\t\t\tiRet = 0;\n"
    "    \tconst\n"
    "    \tchar\t\t*pStrA;\n"
    "\n"
    "    \t// Do initialization.\n"
    "    #ifdef NDEBUG\n"
    "    #else\n"
    "    \tif (!xyzzy_Validate(this)) {\n"
    "    \t\tDEBUG_BREAK();\n"
    "    \t\treturn ERESULT_INVALID_OBJECT;\n"
    "    \t}\n"
    "    #endif\n"
    "\n"
    "    \t// Do Something.\n"
    "    \tc = a + b;\n"
    "\n"
    "    \t// Return to caller.\n"
    "    \treturn iRet;\n"
    "    }\n"
    "\n\n\n"
    ;
    // Alignment is automatically \t\t for DataDefs.
    const
    char        *pDataDefsC[] = {
        "const\n",
        "char\t\t*pStrA;\n",
        NULL
    };
    // Alignment is automatically \t\t for DataDefs.
    const
    char        *pBodyC[] = {
        "// Do Something.\n",
        "c = a + b;\n",
        NULL
    };

    fprintf(stderr, "Performing: %s\n", pTestName);
    
    pObj = genObj_New( );
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    if (pObj) {
        
        eRc = genObj_DictAddA(pObj, "ClassName", "xyzzy");
        TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );

        // Note - if we don't supply a str, GenMethod() will create one.
        eRc = genObj_GenMethod(pObj, &pStr, 4, "abc", "int", NULL, NULL, NULL, false);
        TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );
        TINYTEST_FALSE( (OBJ_NIL == pStr) );
        fprintf(stderr, "%s", AStr_getData(pStr));
        iRc = str_CompareSpcl(pOutputA, AStr_getData(pStr), &offset);
        fprintf(stderr, "\tiRc=%d  offset=%04X\n", iRc, offset);
        TINYTEST_TRUE( (0 == iRc) );
        obj_Release(pStr);
        pStr = OBJ_NIL;
        
        eRc = genObj_GenMethod(
                               pObj,
                               &pStr,
                               4,
                               "abc2",
                               "int",
                               pParmDefsB,
                               pDataDefsB,
                               NULL,
                               true
              );
        TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );
        fprintf(stderr, "%s", AStr_getData(pStr));
        iRc = str_CompareSpcl(pOutputB, AStr_getData(pStr), &offset);
        fprintf(stderr, "\tiRc=%d  offset=%04X\n", iRc, offset);
        TINYTEST_TRUE( (0 == iRc) );
        obj_Release(pStr);
        pStr = OBJ_NIL;
        
        eRc = genObj_GenMethod(
                               pObj,
                               &pStr,
                               4,
                               "abc3",
                               "int",
                               NULL,
                               pDataDefsC,
                               pBodyC,
                               true
            );
        TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );
        fprintf(stderr, "%s", AStr_getData(pStr));
        iRc = str_CompareSpcl(pOutputC, AStr_getData(pStr), &offset);
        fprintf(stderr, "\tiRc=%d  offset=%04X\n", iRc, offset);
        TINYTEST_TRUE( (0 == iRc) );
        obj_Release(pStr);
        pStr = OBJ_NIL;
        
        obj_Release(pObj);
        pObj = OBJ_NIL;
    }
    
    fprintf(stderr, "...%s completed.\n\n", pTestName);
    return 1;
}



int         test_genObj_Getter01(
    const
    char            *pTestName
)
{
    GENOBJ_DATA     *pObj = OBJ_NIL;
    ASTR_DATA       *pStr = OBJ_NIL;
    ERESULT         eRc;
    
    fprintf(stderr, "Performing: %s\n\n", pTestName);
    
    pObj = genObj_New( );
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    if (pObj) {
        
        eRc = genObj_DictAddA(pObj, "ClassName", "xyzzy");
        TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );
        
        fprintf(stderr, "4, \"int\", \"abc\", NULL\n");
        eRc = genObj_GenGetSet(pObj, &pStr, 4, "int", "abc", NULL, false);
        TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );
        fprintf(stderr, "%s", AStr_getData(pStr));
        obj_Release(pStr);
        pStr = OBJ_NIL;
        
        fprintf(stderr, "4, \"ERESULT\", \"eRc\", NULL\n");
        eRc = genObj_GenGetSet(pObj, &pStr, 4, "ERESULT", "eRc", NULL, false);
        TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );
        fprintf(stderr, "%s", AStr_getData(pStr));
        obj_Release(pStr);
        pStr = OBJ_NIL;
        
        fprintf(stderr, "4, \"OBJ_ID\", \"pStr\", NULL\n");
        eRc = genObj_GenGetSet(pObj, &pStr, 4, "OBJ_ID", "pStr", NULL, false);
        TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );
        fprintf(stderr, "%s", AStr_getData(pStr));
        obj_Release(pStr);
        pStr = OBJ_NIL;
        
        fprintf(stderr, "4, \"ASTR_DATA *\", \"pStr\", NULL\n");
        eRc = genObj_GenGetSet(pObj, &pStr, 4, "ASTR_DATA *", "pStr", NULL, false);
        TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );
        fprintf(stderr, "%s", AStr_getData(pStr));
        obj_Release(pStr);
        pStr = OBJ_NIL;
        
        obj_Release(pObj);
        pObj = OBJ_NIL;
    }
    
    fprintf(stderr, "...%s completed.\n\n", pTestName);
    return 1;
}



int         test_genObj_Substitute01(
    const
    char            *pTestName
)
{
    GENOBJ_DATA     *pObj = OBJ_NIL;
    ASTR_DATA       *pStr = OBJ_NIL;
    char            *pStrA;
    ASTR_DATA       *pResult = OBJ_NIL;
    ERESULT         eRc;

    fprintf(stderr, "Performing: %s\n\n", pTestName);
    
    pObj = genObj_New( );
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    if (pObj) {
        
        eRc = genObj_DictAddA(pObj, "ClassName", "xyzzy");
        TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );
        
        pStrA = "";
        pStr = AStr_NewA(pStrA);
        fprintf(stderr, "\tinput = \"%s\"\n", pStrA);
        pResult = genObj_Substitute(pObj, pStr);
        TINYTEST_FALSE( (OBJ_NIL == pResult) );
        TINYTEST_TRUE( (0 == AStr_getLength(pResult)) );
        if (pResult) {
            fprintf(
                    stderr,
                    "\toutput = (%d)\"%s\"\n\n",
                    AStr_getLength(pResult),
                    AStr_getData(pResult)
            );
            obj_Release(pResult);
            pResult = OBJ_NIL;
        }
        else {
            fprintf(stderr, "\toutput = NULL\n\n");
        }
        obj_Release(pStr);
        pStr = OBJ_NIL;
        
        pStrA = "";
        //pStr = AStr_NewA(pStrA);
        fprintf(stderr, "\tinput = OBJ_NIL\n");
        pResult = genObj_Substitute(pObj, pStr);
        TINYTEST_TRUE( (OBJ_NIL == pResult) );
        if (pResult) {
            fprintf(
                    stderr,
                    "\toutput = (%d)\"%s\"\n\n",
                    AStr_getLength(pResult),
                    AStr_getData(pResult)
            );
            obj_Release(pResult);
            pResult = OBJ_NIL;
        }
        else {
            fprintf(stderr, "\toutput = OBJ_NIL\n\n");
        }
        obj_Release(pStr);
        pStr = OBJ_NIL;
        
        pStrA = "Now is the time for all good men to come to the aid of their country!";
        pStr = AStr_NewA(pStrA);
        fprintf(stderr, "\tinput = \"%s\"\n", pStrA);
        pResult = genObj_Substitute(pObj, pStr);
        TINYTEST_FALSE( (OBJ_NIL == pResult) );
        TINYTEST_TRUE( (0 == AStr_CompareA(pResult, pStrA)) );
        TINYTEST_TRUE( (69 == AStr_getLength(pResult)) );
        if (pResult) {
            fprintf(
                    stderr,
                    "\toutput = (%d)\"%s\"\n\n",
                    AStr_getLength(pResult),
                    AStr_getData(pResult)
            );
            obj_Release(pResult);
            pResult = OBJ_NIL;
        }
        else {
            fprintf(stderr, "\toutput = OBJ_NIL\n\n");
        }
        obj_Release(pStr);
        pStr = OBJ_NIL;
        
        pStrA = "Our class name is $ClassName!";
        pStr = AStr_NewA(pStrA);
        fprintf(stderr, "\tinput = \"%s\"\n", pStrA);
        pResult = genObj_Substitute(pObj, pStr);
        TINYTEST_FALSE( (OBJ_NIL == pResult) );
        TINYTEST_TRUE( (0 == AStr_CompareA(pResult, "Our class name is xyzzy!")) );
        TINYTEST_TRUE( (24 == AStr_getLength(pResult)) );
        if (pResult) {
            fprintf(
                    stderr,
                    "\toutput = (%d)\"%s\"\n\n",
                    AStr_getLength(pResult),
                    AStr_getData(pResult)
                    );
            obj_Release(pResult);
            pResult = OBJ_NIL;
        }
        else {
            fprintf(stderr, "\toutput = OBJ_NIL\n\n");
        }
        obj_Release(pStr);
        pStr = OBJ_NIL;
        
        pStrA = "Our class name is ${ClassName}!";
        pStr = AStr_NewA(pStrA);
        fprintf(stderr, "\tinput = \"%s\"\n", pStrA);
        pResult = genObj_Substitute(pObj, pStr);
        TINYTEST_FALSE( (OBJ_NIL == pResult) );
        TINYTEST_TRUE( (0 == AStr_CompareA(pResult, "Our class name is xyzzy!")) );
        TINYTEST_TRUE( (24 == AStr_getLength(pResult)) );
        if (pResult) {
            fprintf(
                    stderr,
                    "\toutput = (%d)\"%s\"\n\n",
                    AStr_getLength(pResult),
                    AStr_getData(pResult)
                    );
            obj_Release(pResult);
            pResult = OBJ_NIL;
        }
        else {
            fprintf(stderr, "\toutput = OBJ_NIL\n\n");
        }
        obj_Release(pStr);
        pStr = OBJ_NIL;
        
        pStrA = "${ClassName}";
        pStr = AStr_NewA(pStrA);
        fprintf(stderr, "\tinput = \"%s\"\n", pStrA);
        pResult = genObj_Substitute(pObj, pStr);
        TINYTEST_FALSE( (OBJ_NIL == pResult) );
        TINYTEST_TRUE( (0 == AStr_CompareA(pResult, "xyzzy")) );
        TINYTEST_TRUE( (5 == AStr_getLength(pResult)) );
        if (pResult) {
            fprintf(
                    stderr,
                    "\toutput = (%d)\"%s\"\n\n",
                    AStr_getLength(pResult),
                    AStr_getData(pResult)
                    );
            obj_Release(pResult);
            pResult = OBJ_NIL;
        }
        else {
            fprintf(stderr, "\toutput = OBJ_NIL\n\n");
        }
        obj_Release(pStr);
        pStr = OBJ_NIL;
        
        pStrA = "${ClassName";
        pStr = AStr_NewA(pStrA);
        fprintf(stderr, "\tinput = \"%s\"\n", pStrA);
        pResult = genObj_Substitute(pObj, pStr);
        TINYTEST_TRUE( (OBJ_NIL == pResult) );
        //TINYTEST_TRUE( (0 == AStr_CompareA(pResult, "xyzzy")) );
        //TINYTEST_TRUE( (5 == AStr_getLength(pResult)) );
        if (pResult) {
            fprintf(
                    stderr,
                    "\toutput = (%d)\"%s\"\n\n",
                    AStr_getLength(pResult),
                    AStr_getData(pResult)
                    );
            obj_Release(pResult);
            pResult = OBJ_NIL;
        }
        else {
            fprintf(stderr, "\toutput = OBJ_NIL\n\n");
        }
        obj_Release(pStr);
        pStr = OBJ_NIL;
        
        obj_Release(pObj);
        pObj = OBJ_NIL;
    }
    
    fprintf(stderr, "...%s completed.\n\n", pTestName);
    return 1;
}



int         test_genObj_Heading01(
    const
    char            *pTestName
)
{
    GENOBJ_DATA     *pObj = OBJ_NIL;
    ASTR_DATA       *pStr = OBJ_NIL;
    ERESULT         eRc;
    int             iRc;
    int             offset = 0;
    const
    char            *pOutputA =
    "// vi:nu:et:sts=4 ts=4 sw=4\n"
    "/*\n"
    " * Program:\n"
    " *\t\txyzzy (XYZZY)\n"
    " * Purpose:\n"
    " *\t\tThis object does something cool!\n"
    " * Remarks:\n"
    " *\t1.\tNone\n"
    " * History:\n"
    " *\tMM/DD/YYYY\tGenerated.\n"
    " *\n"
    " *\n"
    " *\n"
    " *\n"
    " *\n"
    " *\n"
    " *\n"
    " */\n"
    "\n\n\n"
    "\n\n\n"
    ;
    
    
    fprintf(stderr, "Performing: %s\n\n", pTestName);
    
    pObj = genObj_New( );
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    if (pObj) {
        
        eRc = genObj_DictAddA(pObj, "ClassName", "xyzzy");
        TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );
        eRc = genObj_DictUpdateA(pObj, GENOBJ_DATETIME, "MM/DD/YY HH:MM:SS");
        TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );
        eRc = genObj_DictUpdateA(pObj, "M", "MM");
        TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );
        eRc = genObj_DictUpdateA(pObj, "D", "DD");
        TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );
        eRc = genObj_DictUpdateA(pObj, "Y", "YYYY");
        TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );
        eRc = genObj_DictUpdateA(pObj, "H", "HH");
        TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );
        eRc = genObj_DictUpdateA(pObj, "N", "MM");
        TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );
        eRc = genObj_DictUpdateA(pObj, "S", "SS");
        TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );

        eRc = genObj_GenHeading(pObj, &pStr);
        TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );
        fprintf(stderr, "\t\"%s\"", AStr_getData(pStr));
        iRc = str_CompareSpcl(pOutputA, AStr_getData(pStr), &offset);
        fprintf(stderr, "\tiRc=%d  offset=%04X\n", iRc, offset);
        TINYTEST_TRUE( (0 == iRc) );
        obj_Release(pStr);
        pStr = OBJ_NIL;

        obj_Release(pObj);
        pObj = OBJ_NIL;
    }
    
    fprintf(stderr, "...%s completed.\n\n", pTestName);
    return 1;
}



int         test_genObj_FileInternal01(
    const
    char            *pTestName
)
{
    GENOBJ_DATA     *pObj = OBJ_NIL;
    ASTR_DATA       *pStr = OBJ_NIL;
    ERESULT         eRc;
    int             iRc;
    int             offset = 0;
    const
    char            *pOutputA =
    "// vi:nu:et:sts=4 ts=4 sw=4\n"
    "/*\n"
    " * Program:\n"
    " *\t\txyzzy (XYZZY)\n"
    " * Purpose:\n"
    " *\t\tThis object does something cool!\n"
    " * Remarks:\n"
    " *\t1.\tNone\n"
    " * History:\n"
    " *\tMM/DD/YYYY\tGenerated.\n"
    " *\n"
    " *\n"
    " *\n"
    " *\n"
    " *\n"
    " *\n"
    " *\n"
    " */\n"
    "\n\n\n"
    "\n\n\n"
    "/*\n"
    " This is free and unencumbered software released into the public domain.\n"
    " \n"
    " Anyone is free to copy, modify, publish, use, compile, sell, or\n"
    " distribute this software, either in source code form or as a compiled\n"
    " binary, for any purpose, commercial or non-commercial, and by any\n"
    " means.\n"
    " \n"
    " In jurisdictions that recognize copyright laws, the author or authors\n"
    " of this software dedicate any and all copyright interest in the\n"
    " software to the public domain. We make this dedication for the benefit\n"
    " of the public at large and to the detriment of our heirs and\n"
    " successors. We intend this dedication to be an overt act of\n"
    " relinquishment in perpetuity of all present and future rights to this\n"
    " software under copyright law.\n"
    " \n"
    " THE SOFTWARE IS PROVIDED \"AS IS\", WITHOUT WARRANTY OF ANY KIND,\n"
    " EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF\n"
    " MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.\n"
    " IN NO EVENT SHALL THE AUTHORS BE LIABLE FOR ANY CLAIM, DAMAGES OR\n"
    " OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,\n"
    " ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR\n"
    " OTHER DEALINGS IN THE SOFTWARE.\n"
    " \n"
    " For more information, please refer to <http://unlicense.org/>\n"
    " \n"
    " */\n"
    "\n\n\n"
    "/* Header File Inclusion */\n"
    "#include <xyzzy.h>\n"
    "#include <ascii.h>\n"
    "#include <utf8.h>\n"
    "\n"
    "\n"
    "\n"
    "#ifdef    __cplusplus\n"
    "extern \"C\" {\n"
    "#endif\n"
    "\n"
    "\n"
    "\n"
    "//===============================================================\n"
    "//         Object Data Description\n"
    "//===============================================================\n"
    "\n"
    "\n"
    "#pragma pack(push, 1)\n"
    "struct xyzzy_data_s\t{\n"
    "/* Warning - OBJ_DATA must be first in this object!\n"
    " */\n"
    "\tOBJ_DATA\t\tsuper;\n"
    "\tOBJ_IUNKNOWN\t*pSuperVtbl;\t// Needed for Inheritance\n"
    "\n"
    "\t// Common Data\n"
    "\tuint16_t\t\tsize;\t\t// maximum number of elements\n"
    "\tuint16_t\t\trsvd16A;\n"
    "\tASTR_DATA\t\t*pStr;\n"
    "\n"
    "\tvolatile\n"
    "\tint32_t\t\t\tnumRead;\n"
    "\t// WARNING - 'elems' must be last element of this structure!\n"
    "\tuint32_t\t\telems[0];\n"
    "\n"
    "};\n"
    "#pragma pack(pop)\n"
    "\n"
    "\textern\n"
    "\tstruct xyzzy_class_data_s  xyzzy_ClassObj;\n"
    "\n"
    "\textern\n"
    "\tconst\n"
    "\tXYZZY_VTBL\t\txyzzy_Vtbl;\n"
    "\n"
    "\n"
    "\n"
    "\n"
    "//===============================================================\n"
    "// Class Object Method Forward Definitions\n"
    "//===============================================================\n"
    "\n"
    "\n"
    "\n"
    "\n"
    "\n"
    "//===============================================================\n"
    "//   Internal Method Forward Definitions\n"
    "//===============================================================\n"
    "\n"
    "\n"
    "\tbool\t\txyzzy_setPriority(\n"
    "\t\tXYZZY\t\t*this,\n"
    "\t\tuint16_t\t\tvalue\n"
    "\t);\n"
    "\n"
    "\n"
    "\tOBJ_IUNKNOWN *\txyzzy_getSuperVtbl(\n"
    "\t\tXYZZY_DATA\t\t*this\n"
    "\t);\n"
    "\n"
    "\n"
    "\tvoid\t\txyzzy_Dealloc(\n"
    "\t\tOBJ_ID\t\tobjId\n"
    "\t);\n"
    "\n"
    "\n"
    "\tvoid *\t\txyzzy_QueryInfo(\n"
    "\t\tOBJ_ID\t\tobjId,\n"
    "\t\tuint32_t\t\ttype,\n"
    "\t\tvoid\t\t*pData\n"
    "\t);\n"
    "\n"
    "\n"
    "#ifdef NDEBUG\n"
    "#else\n"
    "\tbool\t\txyzzy_Validate(\n"
    "\t\tXYZZY_DATA\t\t*this\n"
    "\t);\n"
    "#endif\n"
    "\n"
    "\n"
    "\n"
    "#ifdef\t__cplusplus\n"
    "}\n"
    "#endif\n"
    "\n"
    "\n"
    "#endif\t/* XYZZY_INTERNAL_H */\n"
    "\n"
    "\n"
    "\n"
    "\n"
    "\n"
    ;
    
    
    fprintf(stderr, "Performing: %s\n\n", pTestName);
    
    pObj = genObj_New( );
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    if (pObj) {
        
        eRc = genObj_DictAddA(pObj, "ClassName", "xyzzy");
        TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );
        eRc = genObj_DictUpdateA(pObj, GENOBJ_DATETIME, "MM/DD/YY HH:MM:SS");
        TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );
        eRc = genObj_DictUpdateA(pObj, "M", "MM");
        TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );
        eRc = genObj_DictUpdateA(pObj, "D", "DD");
        TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );
        eRc = genObj_DictUpdateA(pObj, "Y", "YYYY");
        TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );
        eRc = genObj_DictUpdateA(pObj, "H", "HH");
        TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );
        eRc = genObj_DictUpdateA(pObj, "N", "MM");
        TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );
        eRc = genObj_DictUpdateA(pObj, "S", "SS");
        TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );

        pStr = genObj_GenFileInternalHeader(pObj, NULL);
        fprintf(stderr, "\t\"%s\"", AStr_getData(pStr));
        iRc = str_CompareSpcl(pOutputA, AStr_getData(pStr), &offset);
        fprintf(stderr, "\tiRc=%d  offset=%04X\n", iRc, offset);
        TINYTEST_TRUE( (0 == iRc) );
        obj_Release(pStr);
        pStr = OBJ_NIL;

        obj_Release(pObj);
        pObj = OBJ_NIL;
    }
    
    fprintf(stderr, "...%s completed.\n\n", pTestName);
    return 1;
}




TINYTEST_START_SUITE(test_genObj);
    TINYTEST_ADD_TEST(test_genObj_FileInternal01,setUp,tearDown);
    TINYTEST_ADD_TEST(test_genObj_Heading01,setUp,tearDown);
    TINYTEST_ADD_TEST(test_genObj_Substitute01,setUp,tearDown);
    TINYTEST_ADD_TEST(test_genObj_Getter01,setUp,tearDown);
    TINYTEST_ADD_TEST(test_genObj_Method01,setUp,tearDown);
    TINYTEST_ADD_TEST(test_genObj_License,setUp,tearDown);
    TINYTEST_ADD_TEST(test_genObj_OpenClose,setUp,tearDown);
TINYTEST_END_SUITE();

TINYTEST_MAIN_SINGLE_SUITE(test_genObj);





