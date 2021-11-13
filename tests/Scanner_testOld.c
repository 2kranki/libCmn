// vi:nu:et:sts=4 ts=4 sw=4
/*
 *	Generated 03/04/2020 21:17:29
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
#include    <AStrArray.h>
#include    <JsonIn.h>
#include    <trace.h>
#include    <Scanner_internal.h>
#ifdef  SCANNER_JSON_SUPPORT
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

#ifdef  SCANNER_JSON_SUPPORT
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






int             test_Scanner_OpenClose (
    const
    char            *pTestName
)
{
    ERESULT         eRc = ERESULT_SUCCESS;
    SCANNER_DATA	    *pObj = OBJ_NIL;
    bool            fRc;
   
    fprintf(stderr, "Performing: %s\n", pTestName);

    pObj = Scanner_Alloc( );
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    pObj = Scanner_Init( pObj );
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    if (pObj) {

        //obj_TraceSet(pObj, true);       
        fRc = obj_IsKindOf(pObj, OBJ_IDENT_SCANNER);
        TINYTEST_TRUE( (fRc) );
        
        // Test something.
        TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );

        obj_Release(pObj);
        pObj = OBJ_NIL;
    }

    fprintf(stderr, "...%s completed.\n\n\n", pTestName);
    return 1;
}



int             test_Scanner_Copy01 (
    const
    char            *pTestName
)
{
    ERESULT         eRc = ERESULT_SUCCESS;
    SCANNER_DATA	    *pObj1 = OBJ_NIL;
    SCANNER_DATA	    *pObj2 = OBJ_NIL;
    bool            fRc;
#if defined(SCANNER_JSON_SUPPORT)
    ASTR_DATA	    *pStr = OBJ_NIL;
#endif
   
    fprintf(stderr, "Performing: %s\n", pTestName);

    pObj1 = Scanner_NewA("abcdef");
    TINYTEST_FALSE( (OBJ_NIL == pObj1) );
    if (pObj1) {

        //obj_TraceSet(pObj1, true);       
        fRc = obj_IsKindOf(pObj1, OBJ_IDENT_SCANNER);
        TINYTEST_TRUE( (fRc) );
        
        // Test assign.
        pObj2 = Scanner_New();
        TINYTEST_FALSE( (OBJ_NIL == pObj2) );
        eRc = Scanner_Assign(pObj1, pObj2);
        TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );

        fRc = obj_IsKindOf(pObj2, OBJ_IDENT_SCANNER);
        TINYTEST_TRUE( (fRc) );
        eRc = Scanner_Compare(pObj1, pObj2);
        TINYTEST_TRUE( (0 == eRc) );

        obj_Release(pObj2);
        pObj2 = OBJ_NIL;

        // Test copy.
        pObj2 = Scanner_Copy(pObj1);
        TINYTEST_FALSE( (OBJ_NIL == pObj2) );

        fRc = obj_IsKindOf(pObj2, OBJ_IDENT_SCANNER);
        TINYTEST_TRUE( (fRc) );
        eRc = Scanner_Compare(pObj1, pObj2);
        TINYTEST_TRUE( (0 == eRc) );

        obj_Release(pObj2);
        pObj2 = OBJ_NIL;

        // Test json support.
#if defined(SCANNER_JSON_SUPPORT)
        pStr = Scanner_ToJson(pObj1);
        TINYTEST_FALSE( (OBJ_NIL == pStr) );
        fprintf(stderr, "JSON: %s\n", AStr_getData(pStr));
        pObj2 = Scanner_NewFromJsonString(pStr);
        TINYTEST_FALSE( (OBJ_NIL == pObj2) );
        fRc = obj_IsKindOf(pObj2, OBJ_IDENT_SCANNER);
        TINYTEST_TRUE( (fRc) );
        obj_Release(pStr);
        pStr = OBJ_NIL;
        eRc = Scanner_Compare(pObj1, pObj2);
        TINYTEST_TRUE( (0 == eRc) );

        obj_Release(pObj2);
        pObj2 = OBJ_NIL;
#endif

        obj_Release(pObj1);
        pObj1 = OBJ_NIL;
    }

    fprintf(stderr, "...%s completed.\n\n\n", pTestName);
    return 1;
}



int             test_Scanner_Test01 (
    const
    char            *pTestName
)
{
    //ERESULT         eRc = ERESULT_SUCCESS;
    SCANNER_DATA	    *pObj = OBJ_NIL;
    bool            fRc;
   
    fprintf(stderr, "Performing: %s\n", pTestName);

    pObj = Scanner_New( );
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    if (pObj) {

        //obj_TraceSet(pObj, true);       
        fRc = obj_IsKindOf(pObj, OBJ_IDENT_SCANNER);
        TINYTEST_TRUE( (fRc) );
        
        obj_Release(pObj);
        pObj = OBJ_NIL;
    }

    fprintf(stderr, "...%s completed.\n\n\n", pTestName);
    return 1;
}



int             test_Scanner_ScanInteger01(
    const
    char            *pTestName
)
{
    SCANNER_DATA    *pObj = OBJ_NIL;
    char            *pTestString;
    int32_t         value = 0;
    bool            fRc;

    fprintf(stderr, "Performing: %s\n", pTestName);

    pTestString = " 100";
    pObj = Scanner_NewA(pTestString);
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    if (pObj) {

        value = 0;
        fRc = Scanner_ScanInteger32(pObj, &value);
        TINYTEST_TRUE( (fRc) );
        TINYTEST_TRUE( (4 == obj_getMisc(pObj)) );
        TINYTEST_TRUE( (100 == value) );

        obj_Release(pObj);
        pObj = OBJ_NIL;
    }

    pTestString = " 100 ";
    pObj = Scanner_NewA(pTestString);
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    if (pObj) {

        value = 0;
        fRc = Scanner_ScanInteger32(pObj, &value);
        TINYTEST_TRUE( (fRc) );
        TINYTEST_TRUE( (4 == obj_getMisc(pObj)) );
        TINYTEST_TRUE( (100 == value) );

        obj_Release(pObj);
        pObj = OBJ_NIL;
    }

    pTestString = " 100,";
    pObj = Scanner_NewA(pTestString);
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    if (pObj) {

        value = 0;
        fRc = Scanner_ScanInteger32(pObj, &value);
        TINYTEST_TRUE( (fRc) );
        TINYTEST_TRUE( (4 == obj_getMisc(pObj)) );
        TINYTEST_TRUE( (100 == value) );

        obj_Release(pObj);
        pObj = OBJ_NIL;
    }

    pTestString = " -10,";
    pObj = Scanner_NewA(pTestString);
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    if (pObj) {

        value = 0;
        fRc = Scanner_ScanInteger32(pObj, &value);
        TINYTEST_TRUE( (fRc) );
        TINYTEST_TRUE( (4 == obj_getMisc(pObj)) );
        TINYTEST_TRUE( (-10 == value) );

        obj_Release(pObj);
        pObj = OBJ_NIL;
    }

    pTestString = " +10,";
    pObj = Scanner_NewA(pTestString);
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    if (pObj) {

        value = 0;
        fRc = Scanner_ScanInteger32(pObj, &value);
        TINYTEST_TRUE( (fRc) );
        TINYTEST_TRUE( (4 == obj_getMisc(pObj)) );
        TINYTEST_TRUE( (10 == value) );

        obj_Release(pObj);
        pObj = OBJ_NIL;
    }

    pTestString = " x,";
    pObj = Scanner_NewA(pTestString);
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    if (pObj) {

        value = 0;
        fRc = Scanner_ScanInteger32(pObj, &value);
        TINYTEST_TRUE( (!fRc) );
        TINYTEST_TRUE( (1 == obj_getMisc(pObj)) );
        TINYTEST_TRUE( (0 == value) );

        obj_Release(pObj);
        pObj = OBJ_NIL;
    }

    pTestString = " 1x,";
    pObj = Scanner_NewA(pTestString);
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    if (pObj) {

        value = 0;
        fRc = Scanner_ScanInteger32(pObj, &value);
        TINYTEST_TRUE( (fRc) );
        TINYTEST_TRUE( (2 == obj_getMisc(pObj)) );
        TINYTEST_TRUE( (1 == value) );

        obj_Release(pObj);
        pObj = OBJ_NIL;
    }

    pTestString = " 0x10F";
    pObj = Scanner_NewA(pTestString);
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    if (pObj) {

        value = 0;
        fRc = Scanner_ScanInteger32(pObj, &value);
        TINYTEST_TRUE( (fRc) );
        fprintf(stderr, "\t%s == %d scan: %d\n", pTestString, value, obj_getMisc(pObj));
        TINYTEST_TRUE( (6 == obj_getMisc(pObj)) );
        TINYTEST_TRUE( (271 == value) );

        obj_Release(pObj);
        pObj = OBJ_NIL;
    }

    pTestString = " 0x10F ";
    pObj = Scanner_NewA(pTestString);
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    if (pObj) {

        value = 0;
        fRc = Scanner_ScanInteger32(pObj, &value);
        TINYTEST_TRUE( (fRc) );
        fprintf(stderr, "\t%s == %d scan: %d\n", pTestString, value, obj_getMisc(pObj));
        TINYTEST_TRUE( (6 == obj_getMisc(pObj)) );
        TINYTEST_TRUE( (271 == value) );

        obj_Release(pObj);
        pObj = OBJ_NIL;
    }

    pTestString = " 0x10F,";
    pObj = Scanner_NewA(pTestString);
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    if (pObj) {

        value = 0;
        fRc = Scanner_ScanInteger32(pObj, &value);
        TINYTEST_TRUE( (fRc) );
        fprintf(stderr, "\t%s == %d scan: %d\n", pTestString, value, obj_getMisc(pObj));
        TINYTEST_TRUE( (6 == obj_getMisc(pObj)) );
        TINYTEST_TRUE( (271 == value) );

        obj_Release(pObj);
        pObj = OBJ_NIL;
    }

    pTestString = " 0100";
    pObj = Scanner_NewA(pTestString);
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    if (pObj) {

        value = 0;
        fRc = Scanner_ScanInteger32(pObj, &value);
        TINYTEST_TRUE( (fRc) );
        fprintf(stderr, "\t%s == %d scan: %d\n", pTestString, value, obj_getMisc(pObj));
        TINYTEST_TRUE( (5 == obj_getMisc(pObj)) );
        TINYTEST_TRUE( (64 == value) );

        obj_Release(pObj);
        pObj = OBJ_NIL;
    }

    pTestString = " 0277 ";
    pObj = Scanner_NewA(pTestString);
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    if (pObj) {

        value = 0;
        fRc = Scanner_ScanInteger32(pObj, &value);
        TINYTEST_TRUE( (fRc) );
        fprintf(stderr, "\t%s == %d scan: %d\n", pTestString, value, obj_getMisc(pObj));
        TINYTEST_TRUE( (5 == obj_getMisc(pObj)) );
        TINYTEST_TRUE( (191 == value) );

        obj_Release(pObj);
        pObj = OBJ_NIL;
    }

    pTestString = " 0123 ";
    pObj = Scanner_NewA(pTestString);
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    if (pObj) {

        value = 0;
        fRc = Scanner_ScanInteger32(pObj, &value);
        TINYTEST_TRUE( (fRc) );
        fprintf(stderr, "\t%s == %d scan: %d\n", pTestString, value, obj_getMisc(pObj));
        TINYTEST_TRUE( (5 == obj_getMisc(pObj)) );
        TINYTEST_TRUE( (83 == value) );

        obj_Release(pObj);
        pObj = OBJ_NIL;
    }

    pTestString = " 0";
    pObj = Scanner_NewA(pTestString);
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    if (pObj) {

        value = 0;
        fRc = Scanner_ScanInteger32(pObj, &value);
        TINYTEST_TRUE( (fRc) );
        TINYTEST_TRUE( (2 == obj_getMisc(pObj)) );
        TINYTEST_TRUE( (0 == value) );

        obj_Release(pObj);
        pObj = OBJ_NIL;
    }

    fprintf(stderr, "...%s completed.\n\n", pTestName);
    return 1;
}



int             test_Scanner_ScanAstr01(
    const
    char            *pTestName
)
{
    SCANNER_DATA    *pObj = OBJ_NIL;
    char            *pTestString;
    ASTR_DATA       *pStr = OBJ_NIL;

    fprintf(stderr, "Performing: %s\n", pTestName);

    pTestString = " abc";
    pObj = Scanner_NewA(pTestString);
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    if (pObj) {

        pStr = OBJ_NIL;
        pStr = Scanner_ScanStringToAStr(pObj);
        TINYTEST_FALSE( (OBJ_NIL == pStr) );
        fprintf(stderr, "\t%s == \"%s\" scan: %d\n",
                pTestString,
                AStr_getData(pStr),
                obj_getMisc(pObj)
        );
        TINYTEST_TRUE( (4 == obj_getMisc(pObj)) );
        TINYTEST_TRUE( (0 == strcmp("abc", AStr_getData(pStr))) );
        obj_Release(pStr);
        pStr = OBJ_NIL;

        obj_Release(pObj);
        pObj = OBJ_NIL;
    }

       pTestString = " abc ";
       pObj = Scanner_NewA(pTestString);
       TINYTEST_FALSE( (OBJ_NIL == pObj) );
       if (pObj) {

           pStr = OBJ_NIL;
           pStr = Scanner_ScanStringToAStr(pObj);
           TINYTEST_FALSE( (OBJ_NIL == pStr) );
           fprintf(stderr, "\t%s == \"%s\" scan: %d\n",
                   pTestString,
                   AStr_getData(pStr),
                   obj_getMisc(pObj)
           );
           TINYTEST_TRUE( (5 == obj_getMisc(pObj)) );
           TINYTEST_TRUE( (0 == strcmp("abc", AStr_getData(pStr))) );
           obj_Release(pStr);
           pStr = OBJ_NIL;

           obj_Release(pObj);
           pObj = OBJ_NIL;
       }

       pTestString = " abc,";
       pObj = Scanner_NewA(pTestString);
       TINYTEST_FALSE( (OBJ_NIL == pObj) );
       if (pObj) {

           pStr = OBJ_NIL;
           pStr = Scanner_ScanStringToAStr(pObj);
           TINYTEST_FALSE( (OBJ_NIL == pStr) );
           fprintf(stderr, "\t%s == \"%s\" scan: %d\n",
                   pTestString,
                   AStr_getData(pStr),
                   obj_getMisc(pObj)
           );
           TINYTEST_TRUE( (5 == obj_getMisc(pObj)) );
           TINYTEST_TRUE( (0 == strcmp("abc", AStr_getData(pStr))) );
           obj_Release(pStr);
           pStr = OBJ_NIL;

           obj_Release(pObj);
           pObj = OBJ_NIL;
       }

        pTestString = " abc= ";
        pObj = Scanner_NewA(pTestString);
        TINYTEST_FALSE( (OBJ_NIL == pObj) );
        if (pObj) {

            pObj->sep = '=';
            pStr = Scanner_ScanStringToAStr(pObj);
            TINYTEST_FALSE( (OBJ_NIL == pStr) );
            fprintf(stderr, "\t%s == \"%s\" scan: %d\n",
                    pTestString,
                    AStr_getData(pStr),
                    obj_getMisc(pObj)
            );
            TINYTEST_TRUE( (6 == obj_getMisc(pObj)) );
            TINYTEST_TRUE( (0 == strcmp("abc=", AStr_getData(pStr))) );
            obj_Release(pStr);
            pStr = OBJ_NIL;

            obj_Release(pObj);
            pObj = OBJ_NIL;
        }

        //             1234567
        pTestString = " 'abc' ";
        pObj = Scanner_NewA(pTestString);
        TINYTEST_FALSE( (OBJ_NIL == pObj) );
        if (pObj) {

            pStr = OBJ_NIL;
            pStr = Scanner_ScanStringToAStr(pObj);
            TINYTEST_FALSE( (OBJ_NIL == pStr) );
            fprintf(stderr, "\t%s == \"%s\" scan: %d\n",
                    pTestString,
                    AStr_getData(pStr),
                    obj_getMisc(pObj)
            );
            TINYTEST_TRUE( (7 == obj_getMisc(pObj)) );
            TINYTEST_TRUE( (0 == strcmp("abc", AStr_getData(pStr))) );
            obj_Release(pStr);
            pStr = OBJ_NIL;

            obj_Release(pObj);
            pObj = OBJ_NIL;
        }

        pTestString = " \"abc\" ";
        pObj = Scanner_NewA(pTestString);
        TINYTEST_FALSE( (OBJ_NIL == pObj) );
        if (pObj) {

            pStr = OBJ_NIL;
            pStr = Scanner_ScanStringToAStr(pObj);
            TINYTEST_FALSE( (OBJ_NIL == pStr) );
            fprintf(stderr, "\t%s == \"%s\" scan: %d\n",
                    pTestString,
                    AStr_getData(pStr),
                    obj_getMisc(pObj)
            );
            TINYTEST_TRUE( (7 == obj_getMisc(pObj)) );
            TINYTEST_TRUE( (0 == strcmp("abc", AStr_getData(pStr))) );
            obj_Release(pStr);
            pStr = OBJ_NIL;

            obj_Release(pObj);
            pObj = OBJ_NIL;
        }

        pTestString = " \"abc\\n\\r\" ";
        pObj = Scanner_NewA(pTestString);
        TINYTEST_FALSE( (OBJ_NIL == pObj) );
        if (pObj) {

            pStr = OBJ_NIL;
            pStr = Scanner_ScanStringToAStr(pObj);
            TINYTEST_FALSE( (OBJ_NIL == pStr) );
            fprintf(stderr, "\t%s == \"%s\" scan: %d\n",
                    pTestString,
                    AStr_getData(pStr),
                    obj_getMisc(pObj)
            );
            TINYTEST_TRUE( (11 == obj_getMisc(pObj)) );
            TINYTEST_TRUE( (0 == strcmp("abc\n\r", AStr_getData(pStr))) );
            obj_Release(pStr);
            pStr = OBJ_NIL;

            obj_Release(pObj);
            pObj = OBJ_NIL;
        }

        pTestString = " \"abc\\x0A\" ";
        pObj = Scanner_NewA(pTestString);
        TINYTEST_FALSE( (OBJ_NIL == pObj) );
        if (pObj) {

            pStr = OBJ_NIL;
            pStr = Scanner_ScanStringToAStr(pObj);
            TINYTEST_FALSE( (OBJ_NIL == pStr) );
            fprintf(stderr, "\t%s == \"%s\" scan: %d\n",
                    pTestString,
                    AStr_getData(pStr),
                    obj_getMisc(pObj)
            );
            TINYTEST_TRUE( (11 == obj_getMisc(pObj)) );
            TINYTEST_TRUE( (0 == strcmp("abc\n", AStr_getData(pStr))) );
            obj_Release(pStr);
            pStr = OBJ_NIL;

            obj_Release(pObj);
            pObj = OBJ_NIL;
        }

    fprintf(stderr, "...%s completed.\n\n", pTestName);
    return 1;
}



int             test_Scanner_ScanAstrArray01(
    const
    char            *pTestName
)
{
    ERESULT         eRc;
    SCANNER_DATA    *pObj = OBJ_NIL;
    ASTRARRAY_DATA  *pArray = OBJ_NIL;
    char            *pTestString;
    bool            fDebug = true;

    fprintf(stderr, "Performing: %s\n", pTestName);

    pTestString = " a ";
    pObj = Scanner_NewA(pTestString);
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    if (pObj) {

        pArray = OBJ_NIL;
        pArray = Scanner_ScanStringToAstrArray(pObj);
        TINYTEST_FALSE( (OBJ_NIL == pArray) );
        fprintf(stderr, "\tscan: %d\n", obj_getMisc(pObj));
        TINYTEST_TRUE( (4 == obj_getMisc(pObj)) );
        TINYTEST_FALSE( (OBJ_NIL == pArray) );
        TINYTEST_TRUE( (2 == AStrArray_getSize(pArray)) );
        eRc = AStr_CompareA(AStrArray_Get(pArray, 2), "a");
        TINYTEST_TRUE( (0 == eRc) );
        obj_Release(pArray);
        pArray = OBJ_NIL;

        obj_Release(pObj);
        pObj = OBJ_NIL;
    }

    pTestString = " a,b";
    pObj = Scanner_NewA(pTestString);
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    if (pObj) {

        pArray = OBJ_NIL;
        pArray = Scanner_ScanStringToAstrArray(pObj);
        TINYTEST_FALSE( (OBJ_NIL == pArray) );
        fprintf(stderr, "\tscan: %d\n", obj_getMisc(pObj));
        TINYTEST_TRUE( (5 == obj_getMisc(pObj)) );
        TINYTEST_FALSE( (OBJ_NIL == pArray) );
        TINYTEST_TRUE( (3 == AStrArray_getSize(pArray)) );
        eRc = AStr_CompareA(AStrArray_Get(pArray, 2), "a");
        TINYTEST_TRUE( (0 == eRc) );
        eRc = AStr_CompareA(AStrArray_Get(pArray, 3), "b");
        TINYTEST_TRUE( (0 == eRc) );
        obj_Release(pArray);
        pArray = OBJ_NIL;

        obj_Release(pObj);
        pObj = OBJ_NIL;
    }

    pTestString = " a b";
    pObj = Scanner_NewA(pTestString);
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    if (pObj) {

        pArray = OBJ_NIL;
        pArray = Scanner_ScanStringToAstrArray(pObj);
        TINYTEST_FALSE( (OBJ_NIL == pArray) );
        fprintf(stderr, "\tscan: %d\n", obj_getMisc(pObj));
        TINYTEST_TRUE( (5 == obj_getMisc(pObj)) );
        TINYTEST_FALSE( (OBJ_NIL == pArray) );
        TINYTEST_TRUE( (3 == AStrArray_getSize(pArray)) );
        eRc = AStr_CompareA(AStrArray_Get(pArray, 2), "a");
        TINYTEST_TRUE( (0 == eRc) );
        eRc = AStr_CompareA(AStrArray_Get(pArray, 3), "b");
        TINYTEST_TRUE( (0 == eRc) );
        obj_Release(pArray);
        pArray = OBJ_NIL;

        obj_Release(pObj);
        pObj = OBJ_NIL;
    }

    //             0 000000 00111
    //             1 234567 89012
    pTestString = "\"yy yy\" abc";
    pObj = Scanner_NewA(pTestString);
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    if (pObj) {

        pArray = OBJ_NIL;
        pArray = Scanner_ScanStringToAstrArray(pObj);
        TINYTEST_FALSE( (OBJ_NIL == pArray) );
        fprintf(stderr, "\tscan: %d\n", obj_getMisc(pObj));
        if (fDebug) {
            ASTR_DATA       *pDump;
            pDump = AStrArray_ToDebugString(pArray, 0);
            if (pDump) {
                fprintf(stderr, "%s\n", AStr_getData(pDump));
                obj_Release(pDump);
            }
        }
        TINYTEST_TRUE( (12 == obj_getMisc(pObj)) );
        TINYTEST_FALSE( (OBJ_NIL == pArray) );
        TINYTEST_TRUE( (3 == AStrArray_getSize(pArray)) );
        eRc = AStr_CompareA(AStrArray_Get(pArray, 1), "");
        TINYTEST_TRUE( (0 == eRc) );
        eRc = AStr_CompareA(AStrArray_Get(pArray, 2), "yy yy");
        TINYTEST_TRUE( (0 == eRc) );
        eRc = AStr_CompareA(AStrArray_Get(pArray, 3), "abc");
        TINYTEST_TRUE( (0 == eRc) );
        obj_Release(pArray);
        pArray = OBJ_NIL;

        obj_Release(pObj);
        pObj = OBJ_NIL;
    }

    //             00000000011111 111112 22222
    //             12345678901234 567890 12345
    pTestString = " --define xx=\"yy yy\" abc";
    pObj = Scanner_NewA(pTestString);
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    if (pObj) {

        pObj->sep = '=';
        pArray = OBJ_NIL;
        pArray = Scanner_ScanStringToAstrArray(pObj);
        TINYTEST_FALSE( (OBJ_NIL == pArray) );
        fprintf(stderr, "\tscan: %d\n", obj_getMisc(pObj));
        if (fDebug) {
            ASTR_DATA       *pDump;
            pDump = AStrArray_ToDebugString(pArray, 0);
            if (pDump) {
                fprintf(stderr, "%s\n", AStr_getData(pDump));
                obj_Release(pDump);
            }
        }
        TINYTEST_TRUE( (25 == obj_getMisc(pObj)) );
        TINYTEST_FALSE( (OBJ_NIL == pArray) );
        TINYTEST_TRUE( (5 == AStrArray_getSize(pArray)) );
        eRc = AStr_CompareA(AStrArray_Get(pArray, 1), "");
        TINYTEST_TRUE( (0 == eRc) );
        eRc = AStr_CompareA(AStrArray_Get(pArray, 2), "--define");
        TINYTEST_TRUE( (0 == eRc) );
        eRc = AStr_CompareA(AStrArray_Get(pArray, 3), "xx=");
        TINYTEST_TRUE( (0 == eRc) );
        eRc = AStr_CompareA(AStrArray_Get(pArray, 4), "yy yy");
        TINYTEST_TRUE( (0 == eRc) );
        eRc = AStr_CompareA(AStrArray_Get(pArray, 5), "abc");
        TINYTEST_TRUE( (0 == eRc) );
        obj_Release(pArray);
        pArray = OBJ_NIL;

        obj_Release(pObj);
        pObj = OBJ_NIL;
    }

    fprintf(stderr, "...%s completed.\n\n", pTestName);
    return 1;
}



int             test_Scanner_ScanIdentifier01(
    const
    char            *pTestName
)
{
    SCANNER_DATA    *pObj = OBJ_NIL;
    char            *pTestString;
    ASTR_DATA       *pStr = OBJ_NIL;

    fprintf(stderr, "Performing: %s\n", pTestName);

    pTestString = " abc";
    pObj = Scanner_NewA(pTestString);
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    if (pObj) {

        pStr = OBJ_NIL;
        pStr = Scanner_ScanIdentifierToAStr(pObj);
        TINYTEST_FALSE( (OBJ_NIL == pStr) );
        fprintf(stderr, "\t%s == \"%s\" scan: %d\n",
                pTestString,
                AStr_getData(pStr),
                obj_getMisc(pObj)
        );
        TINYTEST_TRUE( (4 == obj_getMisc(pObj)) );
        TINYTEST_TRUE( (0 == strcmp("abc", AStr_getData(pStr))) );
        obj_Release(pStr);
        pStr = OBJ_NIL;

        obj_Release(pObj);
        pObj = OBJ_NIL;
    }

       pTestString = " abc+def";
       pObj = Scanner_NewA(pTestString);
       TINYTEST_FALSE( (OBJ_NIL == pObj) );
       if (pObj) {

           pStr = OBJ_NIL;
           pStr = Scanner_ScanIdentifierToAStr(pObj);
           TINYTEST_FALSE( (OBJ_NIL == pStr) );
           fprintf(stderr, "\t%s == \"%s\" scan: %d\n",
                   pTestString,
                   AStr_getData(pStr),
                   obj_getMisc(pObj)
           );
           TINYTEST_TRUE( (4 == obj_getMisc(pObj)) );
           TINYTEST_TRUE( (0 == strcmp("abc", AStr_getData(pStr))) );
           obj_Release(pStr);
           pStr = OBJ_NIL;

           obj_Release(pObj);
           pObj = OBJ_NIL;
       }

       pTestString = " abc,";
       pObj = Scanner_NewA(pTestString);
       TINYTEST_FALSE( (OBJ_NIL == pObj) );
       if (pObj) {

           pStr = OBJ_NIL;
           pStr = Scanner_ScanIdentifierToAStr(pObj);
           TINYTEST_FALSE( (OBJ_NIL == pStr) );
           fprintf(stderr, "\t%s == \"%s\" scan: %d\n",
                   pTestString,
                   AStr_getData(pStr),
                   obj_getMisc(pObj)
           );
           TINYTEST_TRUE( (4 == obj_getMisc(pObj)) );
           TINYTEST_TRUE( (0 == strcmp("abc", AStr_getData(pStr))) );
           obj_Release(pStr);
           pStr = OBJ_NIL;

           obj_Release(pObj);
           pObj = OBJ_NIL;
       }

        pTestString = " abc= ";
        pObj = Scanner_NewA(pTestString);
        TINYTEST_FALSE( (OBJ_NIL == pObj) );
        if (pObj) {

            pStr = Scanner_ScanIdentifierToAStr(pObj);
            TINYTEST_FALSE( (OBJ_NIL == pStr) );
            fprintf(stderr, "\t%s == \"%s\" scan: %d\n",
                    pTestString,
                    AStr_getData(pStr),
                    obj_getMisc(pObj)
            );
            TINYTEST_TRUE( (4 == obj_getMisc(pObj)) );
            TINYTEST_TRUE( (0 == strcmp("abc", AStr_getData(pStr))) );
            obj_Release(pStr);
            pStr = OBJ_NIL;

            obj_Release(pObj);
            pObj = OBJ_NIL;
        }

        //             1234567
        pTestString = " 'abc' ";
        pObj = Scanner_NewA(pTestString);
        TINYTEST_FALSE( (OBJ_NIL == pObj) );
        if (pObj) {

            pStr = OBJ_NIL;
            pStr = Scanner_ScanIdentifierToAStr(pObj);
            TINYTEST_TRUE( (OBJ_NIL == pStr) );
            fprintf(stderr, "\tscan: %d\n", Scanner_getIndex(pObj));
            TINYTEST_TRUE( (1 == Scanner_getIndex(pObj)) );
            obj_Release(pStr);
            pStr = OBJ_NIL;

            obj_Release(pObj);
            pObj = OBJ_NIL;
        }

        pTestString = " \"abc\" ";
        pObj = Scanner_NewA(pTestString);
        TINYTEST_FALSE( (OBJ_NIL == pObj) );
        if (pObj) {

            pStr = OBJ_NIL;
            pStr = Scanner_ScanIdentifierToAStr(pObj);
            TINYTEST_TRUE( (OBJ_NIL == pStr) );
            fprintf(stderr, "\tscan: %d\n", Scanner_getIndex(pObj));
            TINYTEST_TRUE( (1 == Scanner_getIndex(pObj)) );
            obj_Release(pStr);
            pStr = OBJ_NIL;

            obj_Release(pObj);
            pObj = OBJ_NIL;
        }

    fprintf(stderr, "...%s completed.\n\n", pTestName);
    return 1;
}



int             test_Scanner_Calc01(
    const
    char            *pTestName
)
{
    ERESULT         eRc = ERESULT_SUCCESS;
    SCANNER_DATA    *pObj = OBJ_NIL;
    char            *pTestString;
    int32_t         iRc;

    fprintf(stderr, "Performing: %s\n", pTestName);

    pTestString = "1+1";
    pObj = Scanner_NewA(pTestString);
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    if (pObj) {

        iRc = 0;
        eRc = Scanner_Calc(pObj, &iRc);
        TINYTEST_TRUE(ERESULT_OK(eRc));
        fprintf(stderr, "\t%s == %d scan: %d\n",
                pTestString,
                iRc,
                obj_getMisc(pObj)
        );
        TINYTEST_TRUE( (2 == iRc) );

        obj_Release(pObj);
        pObj = OBJ_NIL;
    }

    pTestString = "2*5+1";
    pObj = Scanner_NewA(pTestString);
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    if (pObj) {

        iRc = 0;
        eRc = Scanner_Calc(pObj, &iRc);
        TINYTEST_TRUE(ERESULT_OK(eRc));
        fprintf(stderr, "\t%s == %d scan: %d\n",
                pTestString,
                iRc,
                obj_getMisc(pObj)
        );
        TINYTEST_TRUE( (11 == iRc) );

        obj_Release(pObj);
        pObj = OBJ_NIL;
    }

    pTestString = "1+2*5";
    pObj = Scanner_NewA(pTestString);
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    if (pObj) {

        iRc = 0;
        eRc = Scanner_Calc(pObj, &iRc);
        TINYTEST_TRUE(ERESULT_OK(eRc));
        fprintf(stderr, "\t%s == %d scan: %d\n",
                pTestString,
                iRc,
                obj_getMisc(pObj)
        );
        TINYTEST_TRUE( (11 == iRc) );

        obj_Release(pObj);
        pObj = OBJ_NIL;
    }

    fprintf(stderr, "...%s completed.\n\n", pTestName);
    return 1;
}




TINYTEST_START_SUITE(test_Scanner);
    TINYTEST_ADD_TEST(test_Scanner_Calc01,setUp,tearDown);
    TINYTEST_ADD_TEST(test_Scanner_ScanIdentifier01,setUp,tearDown);
    TINYTEST_ADD_TEST(test_Scanner_ScanAstrArray01,setUp,tearDown);
    TINYTEST_ADD_TEST(test_Scanner_ScanAstr01,setUp,tearDown);
    TINYTEST_ADD_TEST(test_Scanner_ScanInteger01,setUp,tearDown);
    TINYTEST_ADD_TEST(test_Scanner_Test01,setUp,tearDown);
    TINYTEST_ADD_TEST(test_Scanner_Copy01,setUp,tearDown);
    TINYTEST_ADD_TEST(test_Scanner_OpenClose,setUp,tearDown);
TINYTEST_END_SUITE();

TINYTEST_MAIN_SINGLE_SUITE(test_Scanner);





