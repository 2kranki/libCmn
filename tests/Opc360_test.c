// vi:nu:et:sts=4 ts=4 sw=4
/*
 *	Generated 02/29/2020 23:01:22
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
#include    <Opc360_internal.h>
#ifdef  OPC360_JSON_SUPPORT
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

#ifdef  OPC360_JSON_SUPPORT
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






int             test_Opc360_OpenClose (
    const
    char            *pTestName
)
{
    ERESULT         eRc = ERESULT_SUCCESS;
    OPC360_DATA	    *pObj = OBJ_NIL;
    bool            fRc;
   
    fprintf(stderr, "Performing: %s\n", pTestName);

    pObj = Opc360_Alloc( );
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    pObj = Opc360_Init( pObj );
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    if (pObj) {

        //obj_TraceSet(pObj, true);       
        fRc = obj_IsKindOf(pObj, OBJ_IDENT_OPC360);
        TINYTEST_TRUE( (fRc) );
        
        // Test something.
        TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );

        obj_Release(pObj);
        pObj = OBJ_NIL;
    }

    fprintf(stderr, "...%s completed.\n\n\n", pTestName);
    return 1;
}



int             test_Opc360_Copy01 (
    const
    char            *pTestName
)
{
    ERESULT         eRc = ERESULT_SUCCESS;
    OPC360_DATA	    *pObj1 = OBJ_NIL;
    OPC360_DATA	    *pObj2 = OBJ_NIL;
    bool            fRc;
#if defined(OPC360_JSON_SUPPORT)
    ASTR_DATA	    *pStr = OBJ_NIL;
#endif
   
    fprintf(stderr, "Performing: %s\n", pTestName);

    pObj1 = Opc360_New( );
    TINYTEST_FALSE( (OBJ_NIL == pObj1) );
    if (pObj1) {

        //obj_TraceSet(pObj1, true);       
        fRc = obj_IsKindOf(pObj1, OBJ_IDENT_OPC360);
        TINYTEST_TRUE( (fRc) );
        str_Copy((char *)Opc360_getOpcode(pObj1)->entry.Name, 9, "ch");
        Opc360_getEntry(pObj1)->cCode = 1;
        Opc360_getEntry(pObj1)->iCode[0] = 73;
        Opc360_getEntry(pObj1)->iMask[0] = 255;
        Opc360_getEntry(pObj1)->iType = 6;
        Opc360_getEntry(pObj1)->iLen = 4;
        Opc360_getEntry(pObj1)->iFeatures = 0x0080;
        Opc360_getEntry(pObj1)->cCondCodes = 4;
        str_Copy((char *)Opc360_getEntry(pObj1)->szCondCodes[0], 9, "eq");
        str_Copy((char *)Opc360_getEntry(pObj1)->szCondCodes[1], 9, "lt");
        str_Copy((char *)Opc360_getEntry(pObj1)->szCondCodes[2], 9, "gt");
        str_Copy((char *)Opc360_getEntry(pObj1)->szCondCodes[3], 9, "-");
        Opc360_getEntry(pObj1)->iInterrupts = 0x0030;

        // Test assign.
        pObj2 = Opc360_New();
        TINYTEST_FALSE( (OBJ_NIL == pObj2) );
        eRc = Opc360_Assign(pObj1, pObj2);
        TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );

        fRc = obj_IsKindOf(pObj2, OBJ_IDENT_OPC360);
        TINYTEST_TRUE( (fRc) );
        TINYTEST_TRUE( (0 == strcmp(Opc360_getEntry(pObj2)->Name, "ch")) );
        TINYTEST_TRUE( (1 == Opc360_getEntry(pObj2)->cCode) );
        TINYTEST_TRUE( (73 == Opc360_getEntry(pObj2)->iCode[0]) );
        TINYTEST_TRUE( (255 == Opc360_getEntry(pObj2)->iMask[0]) );
        TINYTEST_TRUE( (6 == Opc360_getEntry(pObj2)->iType) );
        TINYTEST_TRUE( (4 == Opc360_getEntry(pObj2)->iLen) );
        TINYTEST_TRUE( (0x0080 == Opc360_getEntry(pObj2)->iFeatures) );
        TINYTEST_TRUE( (0 == strcmp(Opc360_getEntry(pObj2)->szCondCodes[0], "eq")) );
        TINYTEST_TRUE( (0 == strcmp(Opc360_getEntry(pObj2)->szCondCodes[1], "lt")) );
        TINYTEST_TRUE( (0 == strcmp(Opc360_getEntry(pObj2)->szCondCodes[2], "gt")) );
        TINYTEST_TRUE( (0 == strcmp(Opc360_getEntry(pObj2)->szCondCodes[3], "-")) );
        TINYTEST_TRUE( (0x0030 == Opc360_getEntry(pObj2)->iInterrupts) );

        obj_Release(pObj2);
        pObj2 = OBJ_NIL;

        // Test copy.
        pObj2 = Opc360_Copy(pObj1);
        TINYTEST_FALSE( (OBJ_NIL == pObj2) );

        fRc = obj_IsKindOf(pObj2, OBJ_IDENT_OPC360);
        TINYTEST_TRUE( (fRc) );
        TINYTEST_TRUE( (0 == strcmp(Opc360_getEntry(pObj2)->Name, "ch")) );
        TINYTEST_TRUE( (1 == Opc360_getEntry(pObj2)->cCode) );
        TINYTEST_TRUE( (73 == Opc360_getEntry(pObj2)->iCode[0]) );
        TINYTEST_TRUE( (255 == Opc360_getEntry(pObj2)->iMask[0]) );
        TINYTEST_TRUE( (6 == Opc360_getEntry(pObj2)->iType) );
        TINYTEST_TRUE( (4 == Opc360_getEntry(pObj2)->iLen) );
        TINYTEST_TRUE( (0x0080 == Opc360_getEntry(pObj2)->iFeatures) );
        TINYTEST_TRUE( (0 == strcmp(Opc360_getEntry(pObj2)->szCondCodes[0], "eq")) );
        TINYTEST_TRUE( (0 == strcmp(Opc360_getEntry(pObj2)->szCondCodes[1], "lt")) );
        TINYTEST_TRUE( (0 == strcmp(Opc360_getEntry(pObj2)->szCondCodes[2], "gt")) );
        TINYTEST_TRUE( (0 == strcmp(Opc360_getEntry(pObj2)->szCondCodes[3], "-")) );
        TINYTEST_TRUE( (0x0030 == Opc360_getEntry(pObj2)->iInterrupts) );

        obj_Release(pObj2);
        pObj2 = OBJ_NIL;

        // Test json support.
#if defined(OPC360_JSON_SUPPORT)
        pStr = Opc360_ToJson(pObj1);
        TINYTEST_FALSE( (OBJ_NIL == pStr) );
        fprintf(stderr, "JSON: %s\n", AStr_getData(pStr));
        pObj2 = Opc360_NewFromJsonString(pStr);
        TINYTEST_FALSE( (OBJ_NIL == pObj2) );
        fRc = obj_IsKindOf(pObj2, OBJ_IDENT_OPC360);
        TINYTEST_TRUE( (fRc) );
        obj_Release(pStr);
        pStr = OBJ_NIL;
        TINYTEST_TRUE( (0 == strcmp(Opc360_getEntry(pObj2)->Name, "ch")) );
        TINYTEST_TRUE( (1 == Opc360_getEntry(pObj2)->cCode) );
        TINYTEST_TRUE( (73 == Opc360_getEntry(pObj2)->iCode[0]) );
        TINYTEST_TRUE( (255 == Opc360_getEntry(pObj2)->iMask[0]) );
        TINYTEST_TRUE( (6 == Opc360_getEntry(pObj2)->iType) );
        TINYTEST_TRUE( (4 == Opc360_getEntry(pObj2)->iLen) );
        TINYTEST_TRUE( (0x0080 == Opc360_getEntry(pObj2)->iFeatures) );
        TINYTEST_TRUE( (0 == strcmp(Opc360_getEntry(pObj2)->szCondCodes[0], "eq")) );
        TINYTEST_TRUE( (0 == strcmp(Opc360_getEntry(pObj2)->szCondCodes[1], "lt")) );
        TINYTEST_TRUE( (0 == strcmp(Opc360_getEntry(pObj2)->szCondCodes[2], "gt")) );
        TINYTEST_TRUE( (0 == strcmp(Opc360_getEntry(pObj2)->szCondCodes[3], "-")) );
        TINYTEST_TRUE( (0x0030 == Opc360_getEntry(pObj2)->iInterrupts) );

        obj_Release(pObj2);
        pObj2 = OBJ_NIL;
#endif

        obj_Release(pObj1);
        pObj1 = OBJ_NIL;
    }

    fprintf(stderr, "...%s completed.\n\n\n", pTestName);
    return 1;
}



int             test_Opc360_Test01 (
    const
    char            *pTestName
)
{
    //ERESULT         eRc = ERESULT_SUCCESS;
    OPC360_DATA	    *pObj = OBJ_NIL;
    bool            fRc;
   
    fprintf(stderr, "Performing: %s\n", pTestName);

    pObj = Opc360_New( );
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    if (pObj) {

        //obj_TraceSet(pObj, true);       
        fRc = obj_IsKindOf(pObj, OBJ_IDENT_OPC360);
        TINYTEST_TRUE( (fRc) );
        
        obj_Release(pObj);
        pObj = OBJ_NIL;
    }

    fprintf(stderr, "...%s completed.\n\n\n", pTestName);
    return 1;
}



int             test_Opc360_JsonIn01 (
    const
    char            *pTestName
)
{
    //ERESULT         eRc = ERESULT_SUCCESS;
    OPC360_DATA     *pObj = OBJ_NIL;
    bool            fRc;
    static
    char            *pJsonText = "{\n"
                                    "\tobjectType:\"Opc360\","
                                    "\tName:\"ch\",\n"
                                    "\tcCode:1,\n"
                                    "\tiCode:[73],\n"
                                    "\tiMask:[255],\n"
                                    "\tiType:\"OPCODE_TYPE_RX\",\n"
                                    "\tiLen:4,\n"
                                    "\tiFeatures:[\"OPCODE_FEATURE_CC\"],\n"
                                    "\tcCondCodes:4,\n"
                                    "\tszCondCodes:[\"eq\",\"lt\",\"gt\",\"-\"],\n"
                                    "\tiInterrupts:[\"OPCODE_INTERRUPT_ADDR\","
                                        "\t\t\"OPCODE_INTERRUPT_SPEC\"],\n"
                                "}\n";
    ASTR_DATA       *pWrk;

    fprintf(stderr, "Performing: %s\n", pTestName);

    pObj = Opc360_NewFromJsonStringA(pJsonText);
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    if (pObj) {

        //obj_TraceSet(pObj, true);
        fRc = obj_IsKindOf(pObj, OBJ_IDENT_OPCODE);
        TINYTEST_TRUE( (fRc) );
        TINYTEST_TRUE( (0 == strcmp(Opc360_getEntry(pObj)->Name, "ch")) );
        TINYTEST_TRUE( (1 == Opc360_getEntry(pObj)->cCode) );
        TINYTEST_TRUE( (73 == Opc360_getEntry(pObj)->iCode[0]) );
        TINYTEST_TRUE( (255 == Opc360_getEntry(pObj)->iMask[0]) );
        TINYTEST_TRUE( (6 == Opc360_getEntry(pObj)->iType) );
        TINYTEST_TRUE( (4 == Opc360_getEntry(pObj)->iLen) );
        TINYTEST_TRUE( (0x0080 == Opc360_getEntry(pObj)->iFeatures) );
        TINYTEST_TRUE( (0 == strcmp(Opc360_getEntry(pObj)->szCondCodes[0], "eq")) );
        TINYTEST_TRUE( (0 == strcmp(Opc360_getEntry(pObj)->szCondCodes[1], "lt")) );
        TINYTEST_TRUE( (0 == strcmp(Opc360_getEntry(pObj)->szCondCodes[2], "gt")) );
        TINYTEST_TRUE( (0 == strcmp(Opc360_getEntry(pObj)->szCondCodes[3], "-")) );
        TINYTEST_TRUE( (0x0030 == Opc360_getEntry(pObj)->iInterrupts) );

        pWrk = Opc360_ToJson(pObj);
        if (pWrk) {
            fprintf(stderr, "\tToJson:\n%s\n\n\n", AStr_getData(pWrk));
            obj_Release(pWrk);
        }

        obj_Release(pObj);
        pObj = OBJ_NIL;
    }

    fprintf(stderr, "...%s completed.\n\n\n", pTestName);
    return 1;
}




TINYTEST_START_SUITE(test_Opc360);
    TINYTEST_ADD_TEST(test_Opc360_JsonIn01,setUp,tearDown);
    TINYTEST_ADD_TEST(test_Opc360_Test01,setUp,tearDown);
    TINYTEST_ADD_TEST(test_Opc360_Copy01,setUp,tearDown);
    TINYTEST_ADD_TEST(test_Opc360_OpenClose,setUp,tearDown);
TINYTEST_END_SUITE();

TINYTEST_MAIN_SINGLE_SUITE(test_Opc360);





