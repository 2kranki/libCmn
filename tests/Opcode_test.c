// vi:nu:et:sts=4 ts=4 sw=4
/*
 *	Generated 02/27/2020 14:36:27
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
#include    <trace.h>
#include    <Opcode_internal.h>
#ifdef  OPCODE_JSON_SUPPORT
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

#ifdef  OPCODE_JSON_SUPPORT
    SrcErrors_SharedReset( );
    szTbl_SharedReset( );
#endif
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






int             test_Opcode_OpenClose (
    const
    char            *pTestName
)
{
    ERESULT         eRc = ERESULT_SUCCESS;
    OPCODE_DATA	    *pObj = OBJ_NIL;
    bool            fRc;
   
    fprintf(stderr, "Performing: %s\n", pTestName);

    pObj = Opcode_Alloc( );
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    pObj = Opcode_Init( pObj );
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    if (pObj) {

        //obj_TraceSet(pObj, true);       
        fRc = obj_IsKindOf(pObj, OBJ_IDENT_OPCODE);
        TINYTEST_TRUE( (fRc) );
        
        // Test something.
        TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );

        obj_Release(pObj);
        pObj = OBJ_NIL;
    }

    fprintf(stderr, "...%s completed.\n\n\n", pTestName);
    return 1;
}



int             test_Opcode_Copy01 (
    const
    char            *pTestName
)
{
    ERESULT         eRc = ERESULT_SUCCESS;
    OPCODE_DATA	    *pObj1 = OBJ_NIL;
    OPCODE_DATA	    *pObj2 = OBJ_NIL;
    bool            fRc;
    ASTR_DATA	    *pStr = OBJ_NIL;

    fprintf(stderr, "Performing: %s\n", pTestName);

    pObj1 = Opcode_New( );
    TINYTEST_FALSE( (OBJ_NIL == pObj1) );
    if (pObj1) {

        //obj_TraceSet(pObj1, true);       
        fRc = obj_IsKindOf(pObj1, OBJ_IDENT_OPCODE);
        TINYTEST_TRUE( (fRc) );
        str_Copy((char *)pObj1->entry.NameA, OPCODE_ENTRY_NAME_MAX, "ch");
        pObj1->entry.cCode = 1;
        pObj1->entry.iCode[0] = 73;
        pObj1->entry.iMask[0] = 255;
        pObj1->entry.iType = 6;
        pObj1->entry.iLen = 4;
        pObj1->entry.iFeatures = 0x0080;
        pObj1->entry.cCondCodes = 4;
        str_Copy((char *)pObj1->entry.szCondCodes[0], OPCODE_ENTRY_SZCONDCODE_MAX, "eq");
        str_Copy((char *)pObj1->entry.szCondCodes[1], OPCODE_ENTRY_SZCONDCODE_MAX, "lt");
        str_Copy((char *)pObj1->entry.szCondCodes[2], OPCODE_ENTRY_SZCONDCODE_MAX, "gt");
        str_Copy((char *)pObj1->entry.szCondCodes[3], OPCODE_ENTRY_SZCONDCODE_MAX, "-");
        pObj1->entry.iInterrupts = 0x0030;

        // Test assign.
        pObj2 = Opcode_New();
        TINYTEST_FALSE( (OBJ_NIL == pObj2) );
        eRc = Opcode_Assign(pObj1, pObj2);
        TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );

        fRc = obj_IsKindOf(pObj2, OBJ_IDENT_OPCODE);
        TINYTEST_TRUE( (fRc) );
        TINYTEST_TRUE( (0 == strcmp(pObj2->entry.NameA, "ch")) );
        TINYTEST_TRUE( (1 == pObj2->entry.cCode) );
        TINYTEST_TRUE( (73 == pObj2->entry.iCode[0]) );
        TINYTEST_TRUE( (255 == pObj2->entry.iMask[0]) );
        TINYTEST_TRUE( (6 == pObj2->entry.iType) );
        TINYTEST_TRUE( (4 == pObj2->entry.iLen) );
        TINYTEST_TRUE( (0x0080 == pObj2->entry.iFeatures) );
        TINYTEST_TRUE( (0 == strcmp(pObj2->entry.szCondCodes[0], "eq")) );
        TINYTEST_TRUE( (0 == strcmp(pObj2->entry.szCondCodes[1], "lt")) );
        TINYTEST_TRUE( (0 == strcmp(pObj2->entry.szCondCodes[2], "gt")) );
        TINYTEST_TRUE( (0 == strcmp(pObj2->entry.szCondCodes[3], "-")) );
        TINYTEST_TRUE( (0x0030 == pObj2->entry.iInterrupts) );

        obj_Release(pObj2);
        pObj2 = OBJ_NIL;

        // Test copy.
        pObj2 = Opcode_Copy(pObj1);
        TINYTEST_FALSE( (OBJ_NIL == pObj2) );

        fRc = obj_IsKindOf(pObj2, OBJ_IDENT_OPCODE);
        TINYTEST_TRUE( (fRc) );
        TINYTEST_TRUE( (0 == strcmp(pObj2->entry.NameA, "ch")) );
        TINYTEST_TRUE( (1 == pObj2->entry.cCode) );
        TINYTEST_TRUE( (73 == pObj2->entry.iCode[0]) );
        TINYTEST_TRUE( (255 == pObj2->entry.iMask[0]) );
        TINYTEST_TRUE( (6 == pObj2->entry.iType) );
        TINYTEST_TRUE( (4 == pObj2->entry.iLen) );
        TINYTEST_TRUE( (0x0080 == pObj2->entry.iFeatures) );
        TINYTEST_TRUE( (0 == strcmp(pObj2->entry.szCondCodes[0], "eq")) );
        TINYTEST_TRUE( (0 == strcmp(pObj2->entry.szCondCodes[1], "lt")) );
        TINYTEST_TRUE( (0 == strcmp(pObj2->entry.szCondCodes[2], "gt")) );
        TINYTEST_TRUE( (0 == strcmp(pObj2->entry.szCondCodes[3], "-")) );
        TINYTEST_TRUE( (0x0030 == pObj2->entry.iInterrupts) );

        obj_Release(pObj2);
        pObj2 = OBJ_NIL;

        // Test json support.
        pStr = Opcode_ToJson(pObj1);
        TINYTEST_FALSE( (OBJ_NIL == pStr) );
        fprintf(stderr, "JSON: %s\n", AStr_getData(pStr));
        pObj2 = Opcode_NewFromJsonString(pStr);
        TINYTEST_FALSE( (OBJ_NIL == pObj2) );
        fRc = obj_IsKindOf(pObj2, OBJ_IDENT_OPCODE);
        TINYTEST_TRUE( (fRc) );
        obj_Release(pStr);
        pStr = OBJ_NIL;
        TINYTEST_TRUE( (0 == strcmp(pObj2->entry.NameA, "ch")) );
        TINYTEST_TRUE( (1 == pObj2->entry.cCode) );
        TINYTEST_TRUE( (73 == pObj2->entry.iCode[0]) );
        TINYTEST_TRUE( (255 == pObj2->entry.iMask[0]) );
        TINYTEST_TRUE( (6 == pObj2->entry.iType) );
        TINYTEST_TRUE( (4 == pObj2->entry.iLen) );
        TINYTEST_TRUE( (0x0080 == pObj2->entry.iFeatures) );
        TINYTEST_TRUE( (0 == strcmp(pObj2->entry.szCondCodes[0], "eq")) );
        TINYTEST_TRUE( (0 == strcmp(pObj2->entry.szCondCodes[1], "lt")) );
        TINYTEST_TRUE( (0 == strcmp(pObj2->entry.szCondCodes[2], "gt")) );
        TINYTEST_TRUE( (0 == strcmp(pObj2->entry.szCondCodes[3], "-")) );
        TINYTEST_TRUE( (0x0030 == pObj2->entry.iInterrupts) );

        obj_Release(pObj2);
        pObj2 = OBJ_NIL;

        obj_Release(pObj1);
        pObj1 = OBJ_NIL;
    }

    fprintf(stderr, "...%s completed.\n\n\n", pTestName);
    return 1;
}



int             test_Opcode_Test01 (
    const
    char            *pTestName
)
{
    //ERESULT         eRc = ERESULT_SUCCESS;
    OPCODE_DATA	    *pObj = OBJ_NIL;
    bool            fRc;
   
    fprintf(stderr, "Performing: %s\n", pTestName);

    pObj = Opcode_New( );
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    if (pObj) {

        //obj_TraceSet(pObj, true);       
        fRc = obj_IsKindOf(pObj, OBJ_IDENT_OPCODE);
        TINYTEST_TRUE( (fRc) );
        
        obj_Release(pObj);
        pObj = OBJ_NIL;
    }

    fprintf(stderr, "...%s completed.\n\n\n", pTestName);
    return 1;
}



int             test_Opcode_JsonIn01 (
    const
    char            *pTestName
)
{
    //ERESULT         eRc = ERESULT_SUCCESS;
    OPCODE_DATA     *pObj = OBJ_NIL;
    bool            fRc;
    static
    char            *pJsonText = "{\n"
                                    "\tobjectType:\"Opcode\","
                                    "\tName:\"ch\",\n"
                                    "\tDis:\"ch %r,%m\",\n"
                                    "\tcCode:1,\n"
                                    "\tiCode:[73],\n"
                                    "\tiMask:[255],\n"
                                    "\tiType:6,\n"
                                    "\tiLen:4,\n"
                                    "\tiFeatures:128,\n"
                                    "\tcCondCodes:4,\n"
                                    "\tszCondCodes:[\"eq\",\"lt\",\"gt\",\"-\"],\n"
                                    "\tiCondCodes:0,\n"
                                    "\tiInterrupts:48,\n"
                                "}\n";
    ASTR_DATA       *pWrk;

    fprintf(stderr, "Performing: %s\n", pTestName);

    pObj = Opcode_NewFromJsonStringA(pJsonText);
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    if (pObj) {

        //obj_TraceSet(pObj, true);
        fRc = obj_IsKindOf(pObj, OBJ_IDENT_OPCODE);
        TINYTEST_TRUE( (fRc) );
        TINYTEST_TRUE( (0 == strcmp(pObj->entry.NameA, "ch")) );
        TINYTEST_TRUE( (1 == pObj->entry.cCode) );
        TINYTEST_TRUE( (73 == pObj->entry.iCode[0]) );
        TINYTEST_TRUE( (255 == pObj->entry.iMask[0]) );
        TINYTEST_TRUE( (6 == pObj->entry.iType) );
        TINYTEST_TRUE( (4 == pObj->entry.iLen) );
        TINYTEST_TRUE( (0x0080 == pObj->entry.iFeatures) );
        TINYTEST_TRUE( (0 == strcmp(pObj->entry.szCondCodes[0], "eq")) );
        TINYTEST_TRUE( (0 == strcmp(pObj->entry.szCondCodes[1], "lt")) );
        TINYTEST_TRUE( (0 == strcmp(pObj->entry.szCondCodes[2], "gt")) );
        TINYTEST_TRUE( (0 == strcmp(pObj->entry.szCondCodes[3], "-")) );
        TINYTEST_TRUE( (0x0030 == pObj->entry.iInterrupts) );

        pWrk = Opcode_ToJson(pObj);
        if (pWrk) {
            fprintf(stderr, "\tToJson:\n%s\n\n\n", AStr_getData(pWrk));
            obj_Release(pWrk);
        }

        pWrk = Opcode_ToInitString(pObj);
        if (pWrk) {
            fprintf(stderr, "\tToInit:\n%s\n\n\n", AStr_getData(pWrk));
            obj_Release(pWrk);
        }

        obj_Release(pObj);
        pObj = OBJ_NIL;
    }

    fprintf(stderr, "...%s completed.\n\n\n", pTestName);
    return 1;
}




TINYTEST_START_SUITE(test_Opcode);
    TINYTEST_ADD_TEST(test_Opcode_JsonIn01,setUp,tearDown);
    TINYTEST_ADD_TEST(test_Opcode_Test01,setUp,tearDown);
    TINYTEST_ADD_TEST(test_Opcode_Copy01,setUp,tearDown);
    TINYTEST_ADD_TEST(test_Opcode_OpenClose,setUp,tearDown);
TINYTEST_END_SUITE();

TINYTEST_MAIN_SINGLE_SUITE(test_Opcode);





