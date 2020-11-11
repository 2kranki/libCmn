// vi:nu:et:sts=4 ts=4 sw=4
/*
 *	Generated 02/27/2020 16:46:25
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
#include    <Opcodes_internal.h>
#ifdef  OPCODES_JSON_SUPPORT
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

#ifdef  OPCODES_JSON_SUPPORT
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






int             test_Opcodes_OpenClose (
    const
    char            *pTestName
)
{
    ERESULT         eRc = ERESULT_SUCCESS;
    OPCODES_DATA	    *pObj = OBJ_NIL;
    bool            fRc;
   
    fprintf(stderr, "Performing: %s\n", pTestName);

    pObj = Opcodes_Alloc( );
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    pObj = Opcodes_Init( pObj );
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    if (pObj) {

        //obj_TraceSet(pObj, true);       
        fRc = obj_IsKindOf(pObj, OBJ_IDENT_OPCODES);
        TINYTEST_TRUE( (fRc) );
        
        // Test something.
        TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );

        obj_Release(pObj);
        pObj = OBJ_NIL;
    }

    fprintf(stderr, "...%s completed.\n\n\n", pTestName);
    return 1;
}



int             test_Opcodes_Copy01 (
    const
    char            *pTestName
)
{
    ERESULT         eRc = ERESULT_SUCCESS;
    OPCODES_DATA	    *pObj1 = OBJ_NIL;
    OPCODES_DATA	    *pObj2 = OBJ_NIL;
    bool            fRc;
#if defined(OPCODES_JSON_SUPPORT) && defined(XYZZY)
    ASTR_DATA	    *pStr = OBJ_NIL;
#endif
   
    fprintf(stderr, "Performing: %s\n", pTestName);

    pObj1 = Opcodes_New( );
    TINYTEST_FALSE( (OBJ_NIL == pObj1) );
    if (pObj1) {

        //obj_TraceSet(pObj1, true);       
        fRc = obj_IsKindOf(pObj1, OBJ_IDENT_OPCODES);
        TINYTEST_TRUE( (fRc) );
        
        // Test assign.
        pObj2 = Opcodes_New();
        TINYTEST_FALSE( (OBJ_NIL == pObj2) );
        eRc = Opcodes_Assign(pObj1, pObj2);
        TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );

        fRc = obj_IsKindOf(pObj2, OBJ_IDENT_OPCODES);
        TINYTEST_TRUE( (fRc) );
        //eRc = Opcodes_Compare(pObj1, pObj2);
        //TINYTEST_TRUE( (0 == eRc) );
        //TODO: Add More tests here!

        obj_Release(pObj2);
        pObj2 = OBJ_NIL;

        // Test copy.
        pObj2 = Opcodes_Copy(pObj1);
        TINYTEST_FALSE( (OBJ_NIL == pObj2) );

        fRc = obj_IsKindOf(pObj2, OBJ_IDENT_OPCODES);
        TINYTEST_TRUE( (fRc) );
        //eRc = Opcodes_Compare(pObj1, pObj2);
        //TINYTEST_TRUE( (0 == eRc) );
        //TODO: Add More tests here!

        obj_Release(pObj2);
        pObj2 = OBJ_NIL;

        // Test json support.
#if defined(OPCODES_JSON_SUPPORT) && defined(XYZZY)
        pStr = Opcodes_ToJson(pObj1);
        TINYTEST_FALSE( (OBJ_NIL == pStr) );
        fprintf(stderr, "JSON: %s\n", AStr_getData(pStr));
        pObj2 = Opcodes_NewFromJsonString(pStr);
        TINYTEST_FALSE( (OBJ_NIL == pObj2) );
        fRc = obj_IsKindOf(pObj2, OBJ_IDENT_OPCODES);
        TINYTEST_TRUE( (fRc) );
        obj_Release(pStr);
        pStr = OBJ_NIL;
        //eRc = Opcodes_Compare(pObj1, pObj2);
        //TINYTEST_TRUE( (0 == eRc) );

        obj_Release(pObj2);
        pObj2 = OBJ_NIL;
#endif

        obj_Release(pObj1);
        pObj1 = OBJ_NIL;
    }

    fprintf(stderr, "...%s completed.\n\n\n", pTestName);
    return 1;
}



int             test_Opcodes_Test01 (
    const
    char            *pTestName
)
{
    ERESULT         eRc = ERESULT_SUCCESS;
    OPCODES_DATA	*pObj = OBJ_NIL;
    OPCODES_DATA    *pObj2 = OBJ_NIL;
    OPCODE_DATA     *pOpc = OBJ_NIL;
    bool            fRc;
    OBJENUM_DATA    *pEnum = OBJ_NIL;
    uint32_t        i;
    ASTR_DATA       *pStr = OBJ_NIL;
   
    fprintf(stderr, "Performing: %s\n", pTestName);

    pObj = Opcodes_New( );
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    if (pObj) {

        //obj_TraceSet(pObj, true);       
        fRc = obj_IsKindOf(pObj, OBJ_IDENT_OPCODES);
        TINYTEST_TRUE( (fRc) );

        pOpc = Opcode_NewA("lh");
        TINYTEST_FALSE( (OBJ_NIL == pOpc) );
        eRc = Opcodes_Add(pObj, pOpc);
        TINYTEST_TRUE( (ERESULT_OK(eRc)) );
        TINYTEST_TRUE( (1 == Opcodes_getSize(pObj)) );
        obj_Release(pOpc);
        pOpc = Opcode_NewA("br");
        TINYTEST_FALSE( (OBJ_NIL == pOpc) );
        eRc = Opcodes_Add(pObj, pOpc);
        TINYTEST_TRUE( (ERESULT_OK(eRc)) );
        TINYTEST_TRUE( (2 == Opcodes_getSize(pObj)) );
        obj_Release(pOpc);
        pOpc = Opcode_NewA("br");
        TINYTEST_FALSE( (OBJ_NIL == pOpc) );
        // V1 was based on the opcode name being unique
        // and was used as the index.
        // V2 does not require that.
        eRc = Opcodes_Add(pObj, pOpc);
        TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );
        TINYTEST_TRUE( (3 == Opcodes_getSize(pObj)) );
        obj_Release(pOpc);

        pEnum = Opcodes_Enum(pObj);
        TINYTEST_FALSE( (OBJ_NIL == pEnum) );
        fprintf(stderr, "Enum:\n");
        for (;;) {
            pOpc = OBJ_NIL;
            eRc = ObjEnum_Next(pEnum, 1, (OBJ_ID *)&pOpc, &i);
            if (ERESULT_OK(eRc) && pOpc) {
                fprintf(stderr, "\t%s\n", Opcode_getNameA(pOpc));
            } else {
                break;
            }
        }
        obj_Release(pEnum);
        pEnum = OBJ_NIL;

        pStr = Opcodes_ToJson(pObj);
        TINYTEST_FALSE( (OBJ_NIL == pStr) );
        fprintf(stderr, "ToJson: %s\n", AStr_getData(pStr));
        pObj2 = Opcodes_NewFromJsonString(pStr);
        TINYTEST_FALSE( (OBJ_NIL == pObj2) );
        TINYTEST_TRUE( (3 == Opcodes_getSize(pObj)) );
        //FIXME: pOpc = Opcodes_FindA(pObj2, "br");
        //FIXME: TINYTEST_FALSE( (OBJ_NIL == pOpc) );
        //FIXME: pOpc = Opcodes_FindA(pObj2, "lh");
        //FIXME: TINYTEST_FALSE( (OBJ_NIL == pOpc) );
        obj_Release(pStr);
        pStr = OBJ_NIL;
        obj_Release(pObj2);
        pObj2 = OBJ_NIL;

        obj_Release(pObj);
        pObj = OBJ_NIL;
    }

    fprintf(stderr, "...%s completed.\n\n\n", pTestName);
    return 1;
}




TINYTEST_START_SUITE(test_Opcodes);
    TINYTEST_ADD_TEST(test_Opcodes_Test01,setUp,tearDown);
    //TINYTEST_ADD_TEST(test_Opcodes_Copy01,setUp,tearDown);
    TINYTEST_ADD_TEST(test_Opcodes_OpenClose,setUp,tearDown);
TINYTEST_END_SUITE();

TINYTEST_MAIN_SINGLE_SUITE(test_Opcodes);





