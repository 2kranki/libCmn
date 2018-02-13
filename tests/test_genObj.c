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
    uint32_t        crc = 0;
    
    fprintf(stderr, "Performing: %s\n", pTestName);
    
    pObj = genObj_New( );
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    if (pObj) {
        
        eRc = genObj_GenLicense(pObj, &pStr);
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



int         test_genObj_Method01(
    const
    char            *pTestName
)
{
    GENOBJ_DATA     *pObj = OBJ_NIL;
    ASTR_DATA       *pStr = OBJ_NIL;
    ERESULT         eRc;
    
    fprintf(stderr, "Performing: %s\n", pTestName);
    
    pObj = genObj_New( );
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    if (pObj) {
        
        eRc = genObj_VarAddA(pObj, "ClassName", "xyzzy");
        TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );

        // Note - if we don't supply a str, GenMethod() will create one.
        eRc = genObj_GenMethod(pObj, &pStr, 4, "abc", "int", NULL, NULL, false);
        TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );
        TINYTEST_FALSE( (OBJ_NIL == pStr) );
        fprintf(stderr, "%s", AStr_getData(pStr));
        obj_Release(pStr);
        pStr = OBJ_NIL;
        
        eRc = genObj_GenMethod(
                               pObj,
                               &pStr,
                               4,
                               "abc2",
                               "int",
                               "        const\n        char        *pStr\n",
                               NULL,
                               true
              );
        TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );
        fprintf(stderr, "%s", AStr_getData(pStr));
        obj_Release(pStr);
        pStr = OBJ_NIL;
        
        eRc = genObj_GenMethod(
                               pObj,
                               &pStr,
                               4,
                               "abcNew3",
                               "int",
                               "        const\n        char        *pStr\n",
                               "        c = a + b;\n",
                               true
            );
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
        
        eRc = genObj_VarAddA(pObj, "ClassName", "xyzzy");
        TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );
        
        fprintf(stderr, "4, \"int\", \"abc\", NULL\n");
        eRc = genObj_GenGetSet(pObj, &pStr, 4, "int", "abc", NULL);
        TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );
        fprintf(stderr, "%s", AStr_getData(pStr));
        obj_Release(pStr);
        pStr = OBJ_NIL;
        
        fprintf(stderr, "4, \"ERESULT\", \"eRc\", NULL\n");
        eRc = genObj_GenGetSet(pObj, &pStr, 4, "ERESULT", "eRc", NULL);
        TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );
        fprintf(stderr, "%s", AStr_getData(pStr));
        obj_Release(pStr);
        pStr = OBJ_NIL;
        
        fprintf(stderr, "4, \"OBJ_ID\", \"pStr\", NULL\n");
        eRc = genObj_GenGetSet(pObj, &pStr, 4, "OBJ_ID", "pStr", NULL);
        TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );
        fprintf(stderr, "%s", AStr_getData(pStr));
        obj_Release(pStr);
        pStr = OBJ_NIL;
        
        fprintf(stderr, "4, \"ASTR_DATA *\", \"pStr\", NULL\n");
        eRc = genObj_GenGetSet(pObj, &pStr, 4, "ASTR_DATA *", "pStr", NULL);
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
        
        eRc = genObj_VarAddA(pObj, "ClassName", "xyzzy");
        TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );
        
        pStrA = "";
        pStr = AStr_NewA(pStrA);
        fprintf(stderr, "\tinput = \"%s\"\n", pStrA);
        pResult = genObj_Substitute(pObj, pStr);
        TINYTEST_FALSE( (ERESULT_FAILED(pObj->eRc)) );
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
        TINYTEST_TRUE( (ERESULT_FAILED(pObj->eRc)) );
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
        TINYTEST_FALSE( (ERESULT_FAILED(pObj->eRc)) );
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
        TINYTEST_FALSE( (ERESULT_FAILED(pObj->eRc)) );
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
        TINYTEST_FALSE( (ERESULT_FAILED(pObj->eRc)) );
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
        TINYTEST_FALSE( (ERESULT_FAILED(pObj->eRc)) );
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
        TINYTEST_TRUE( (ERESULT_FAILED(pObj->eRc)) );
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




TINYTEST_START_SUITE(test_genObj);
    TINYTEST_ADD_TEST(test_genObj_Substitute01,setUp,tearDown);
    TINYTEST_ADD_TEST(test_genObj_Getter01,setUp,tearDown);
    TINYTEST_ADD_TEST(test_genObj_Method01,setUp,tearDown);
    TINYTEST_ADD_TEST(test_genObj_License,setUp,tearDown);
    TINYTEST_ADD_TEST(test_genObj_OpenClose,setUp,tearDown);
TINYTEST_END_SUITE();

TINYTEST_MAIN_SINGLE_SUITE(test_genObj);





