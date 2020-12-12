// vi:nu:et:sts=4 ts=4 sw=4
/*
 *  Generated 12/06/2020 10:50:20
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
#include    <ALU8_internal.h>
#include    <JsonIn.h>
#ifdef  ALU8_JSON_SUPPORT
#   include    <SrcErrors.h>
#   include    <szTbl.h>
#endif



void            displayFlags (
    uint8_t         flags
)
{
    if (flags & ALU8_FLAG_AUX_CARRY)
        fprintf(stderr, "\t\tAux Carry\n");
    if (flags & ALU8_FLAG_CARRY)
        fprintf(stderr, "\t\tCarry\n");
    if (flags & ALU8_FLAG_PARITY)
        fprintf(stderr, "\t\tParity\n");
    if (flags & ALU8_FLAG_SIGN)
        fprintf(stderr, "\t\tSign\n");
    if (flags & ALU8_FLAG_ZERO)
        fprintf(stderr, "\t\tZero\n");

}



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

#ifdef  ALU8_JSON_SUPPORT
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






int             test_ALU8_OpenClose (
    const
    char            *pTestName
)
{
    ERESULT         eRc = ERESULT_SUCCESS;
    ALU8_DATA       *pObj = OBJ_NIL;
    bool            fRc;
   
    fprintf(stderr, "Performing: %s\n", pTestName);

    pObj = ALU8_Alloc( );
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    pObj = ALU8_Init( pObj );
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    if (pObj) {

        //obj_TraceSet(pObj, true);       
        fRc = obj_IsKindOf(pObj, OBJ_IDENT_ALU8);
        TINYTEST_TRUE( (fRc) );
        
        // Test something.
        TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );

        obj_Release(pObj);
        pObj = OBJ_NIL;
    }

    fprintf(stderr, "...%s completed.\n\n\n", pTestName);
    return 1;
}



int             test_ALU8_Copy01 (
    const
    char            *pTestName
)
{
    ERESULT         eRc = ERESULT_SUCCESS;
    ALU8_DATA       *pObj1 = OBJ_NIL;
    ALU8_DATA       *pObj2 = OBJ_NIL;
    bool            fRc;
#if defined(ALU8_JSON_SUPPORT) && defined(XYZZY)
    ASTR_DATA       *pStr = OBJ_NIL;
#endif
   
    fprintf(stderr, "Performing: %s\n", pTestName);

    pObj1 = ALU8_New( );
    TINYTEST_FALSE( (OBJ_NIL == pObj1) );
    if (pObj1) {

        //obj_TraceSet(pObj1, true);       
        fRc = obj_IsKindOf(pObj1, OBJ_IDENT_ALU8);
        TINYTEST_TRUE( (fRc) );
        
        // Test assign.
        pObj2 = ALU8_New();
        TINYTEST_FALSE( (OBJ_NIL == pObj2) );
        eRc = ALU8_Assign(pObj1, pObj2);
        TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );

        fRc = obj_IsKindOf(pObj2, OBJ_IDENT_ALU8);
        TINYTEST_TRUE( (fRc) );
        //eRc = ALU8_Compare(pObj1, pObj2);
        //TINYTEST_TRUE( (ERESULT_SUCCESS_EQUAL == eRc) );
        //TODO: Add More tests here!

        obj_Release(pObj2);
        pObj2 = OBJ_NIL;

        // Test copy.
        pObj2 = ALU8_Copy(pObj1);
        TINYTEST_FALSE( (OBJ_NIL == pObj2) );

        fRc = obj_IsKindOf(pObj2, OBJ_IDENT_ALU8);
        TINYTEST_TRUE( (fRc) );
        //eRc = ALU8_Compare(pObj1, pObj2);
        //TINYTEST_TRUE( (ERESULT_SUCCESS_EQUAL == eRc) );
        //TODO: Add More tests here!

        obj_Release(pObj2);
        pObj2 = OBJ_NIL;

        // Test json support.
#if defined(ALU8_JSON_SUPPORT) && defined(XYZZY)
        pStr = ALU8_ToJson(pObj1);
        TINYTEST_FALSE( (OBJ_NIL == pStr) );
        fprintf(stderr, "JSON: %s\n", AStr_getData(pStr));
        pObj2 = ALU8_NewFromJsonString(pStr);
        TINYTEST_FALSE( (OBJ_NIL == pObj2) );
        fRc = obj_IsKindOf(pObj2, OBJ_IDENT_ALU8);
        TINYTEST_TRUE( (fRc) );
        obj_Release(pStr);
        pStr = OBJ_NIL;
        //eRc = ALU8_Compare(pObj1, pObj2);
        //TINYTEST_TRUE( (ERESULT_SUCCESS_EQUAL == eRc) );

        obj_Release(pObj2);
        pObj2 = OBJ_NIL;
#endif

        obj_Release(pObj1);
        pObj1 = OBJ_NIL;
    }

    fprintf(stderr, "...%s completed.\n\n\n", pTestName);
    return 1;
}



int             test_ALU8_Test01 (
    const
    char            *pTestName
)
{
    //ERESULT         eRc = ERESULT_SUCCESS;
    ALU8_DATA       *pObj = OBJ_NIL;
    bool            fRc;
   
    fprintf(stderr, "Performing: %s\n", pTestName);

    pObj = ALU8_New( );
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    if (pObj) {

        //obj_TraceSet(pObj, true);       
        fRc = obj_IsKindOf(pObj, OBJ_IDENT_ALU8);
        TINYTEST_TRUE( (fRc) );
        //TINYTEST_TRUE( (ERESULT_OK(eRc)) );
        
        {
            ASTR_DATA       *pStr = ALU8_ToDebugString(pObj, 0);
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
    return 1;
}



int             test_ALU8_GenParity01 (
    const
    char            *pTestName
)
{
    //ERESULT         eRc = ERESULT_SUCCESS;
    //ALU8_DATA   *pObj = OBJ_NIL;
    //bool            fRc;
    ASTR_DATA       *pStr = OBJ_NIL;

    fprintf(stderr, "Performing: %s\n", pTestName);

    pStr = ALU8_GenEvenParityTable( );
    TINYTEST_FALSE( (OBJ_NIL == pStr) );
    if (pStr) {
        fprintf(stderr, "Table: %s\n", AStr_getData(pStr));
        obj_Release(pStr);
        pStr = OBJ_NIL;
    }

    fprintf(stderr, "...%s completed.\n\n\n", pTestName);
    return 1;
}



int             test_ALU8_Add01 (
    const
    char            *pTestName
)
{
    ERESULT         eRc = ERESULT_SUCCESS;
    ALU8_DATA   *pObj = OBJ_NIL;
    bool            fRc;
    uint8_t         result;
    uint8_t         flags;

    fprintf(stderr, "Performing: %s\n", pTestName);

    pObj = ALU8_New( );
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    if (pObj) {

        //obj_TraceSet(pObj, true);
        fRc = obj_IsKindOf(pObj, OBJ_IDENT_ALU8);
        TINYTEST_TRUE( (fRc) );
        //TINYTEST_TRUE( (ERESULT_OK(eRc)) );

        eRc =   ALU8_Exec(
                            ALU8_OP_ADD,
                            1,
                            4,
                            ALU8_FLAG_NONE,
                            &flags,
                            &result
                );
        TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );
        fprintf(stderr, "\tAdd 1+4 w/o carry: result=%02X flags=%02X\n", result, flags);
        displayFlags(flags);
        TINYTEST_TRUE( (5 == result) );
        TINYTEST_TRUE( (ALU8_FLAG_PARITY == flags) );

        eRc =   ALU8_Exec(
                            ALU8_OP_ADD,
                            2,
                            14,
                            ALU8_FLAG_CARRY,
                            &flags,
                            &result
                );
        TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );
        fprintf(stderr, "\tAdd 2+14 w/carry: result=%02X flags=%02X\n", result, flags);
        displayFlags(flags);
        TINYTEST_TRUE( (17 == result) );
        TINYTEST_TRUE( ((ALU8_FLAG_AUX_CARRY | ALU8_FLAG_PARITY) == flags) );

        eRc =   ALU8_Exec(
                            ALU8_OP_ADD,
                            1,
                            127,
                            ALU8_FLAG_CARRY,
                            &flags,
                            &result
                );
        TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );
        fprintf(stderr, "\tAdd 1+127 w/carry: result=%02X flags=%02X\n", result, flags);
        displayFlags(flags);
        TINYTEST_TRUE( (129 == result) );
        TINYTEST_TRUE( ((ALU8_FLAG_AUX_CARRY | ALU8_FLAG_PARITY \
                         | ALU8_FLAG_SIGN) == flags) );

        eRc =   ALU8_Exec(
                            ALU8_OP_ADD,
                            1,
                            254,
                            ALU8_FLAG_CARRY,
                            &flags,
                            &result
                );
        TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );
        fprintf(stderr, "\tAdd 1+254 w/carry: result=%02X flags=%02X\n", result, flags);
        displayFlags(flags);
        TINYTEST_TRUE( (0 == result) );
        TINYTEST_TRUE( ((ALU8_FLAG_AUX_CARRY | ALU8_FLAG_PARITY | \
                         ALU8_FLAG_CARRY | ALU8_FLAG_ZERO) == flags) );

        obj_Release(pObj);
        pObj = OBJ_NIL;
    }

    fprintf(stderr, "...%s completed.\n\n\n", pTestName);
    return 1;
}



int             test_ALU8_And01 (
    const
    char            *pTestName
)
{
    ERESULT         eRc = ERESULT_SUCCESS;
    ALU8_DATA   *pObj = OBJ_NIL;
    bool            fRc;
    uint8_t         result;
    uint8_t         flags;

    fprintf(stderr, "Performing: %s\n", pTestName);

    pObj = ALU8_New( );
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    if (pObj) {

        //obj_TraceSet(pObj, true);
        fRc = obj_IsKindOf(pObj, OBJ_IDENT_ALU8);
        TINYTEST_TRUE( (fRc) );
        //TINYTEST_TRUE( (ERESULT_OK(eRc)) );

        eRc =   ALU8_Exec(
                            ALU8_OP_AND,
                            0x03,
                            1,
                            ALU8_FLAG_NONE,
                            &flags,
                            &result
                );
        TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );
        fprintf(stderr, "\tAdd 3&1 w/o carry: result=%02X flags=%02X\n", result, flags);
        displayFlags(flags);
        TINYTEST_TRUE( (0x01 == result) );
        TINYTEST_TRUE( (ALU8_FLAG_NONE == flags) );

        eRc =   ALU8_Exec(
                            ALU8_OP_AND,
                            0x03,
                            1,
                            ALU8_FLAG_CARRY,
                            &flags,
                            &result
                );
        TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );
        fprintf(stderr, "\tAdd 3&1 w/carry: result=%02X flags=%02X\n", result, flags);
        displayFlags(flags);
        TINYTEST_TRUE( (0x01 == result) );
        TINYTEST_TRUE( (ALU8_FLAG_NONE == flags) );

        obj_Release(pObj);
        pObj = OBJ_NIL;
    }

    fprintf(stderr, "...%s completed.\n\n\n", pTestName);
    return 1;
}



int             test_ALU8_Complement01 (
    const
    char            *pTestName
)
{
    ERESULT         eRc = ERESULT_SUCCESS;
    ALU8_DATA   *pObj = OBJ_NIL;
    bool            fRc;
    uint8_t         result;
    uint8_t         flags;

    fprintf(stderr, "Performing: %s\n", pTestName);

    pObj = ALU8_New( );
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    if (pObj) {

        //obj_TraceSet(pObj, true);
        fRc = obj_IsKindOf(pObj, OBJ_IDENT_ALU8);
        TINYTEST_TRUE( (fRc) );
        //TINYTEST_TRUE( (ERESULT_OK(eRc)) );

        eRc =   ALU8_Exec(
                            ALU8_OP_COMPLEMENT,
                            0x88,
                            0x80,
                            ALU8_FLAG_NONE,
                            &flags,
                            &result
                );
        TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );
        fprintf(
                stderr,
                "\tNot 0x88 w/o carry: result=%02X flags=%02X\n",
                result,
                flags
        );
        displayFlags(flags);
        TINYTEST_TRUE( (0x78 == result) );
        TINYTEST_TRUE( (ALU8_FLAG_NONE == flags) );

        eRc =   ALU8_Exec(
                            ALU8_OP_COMPLEMENT,
                            0x88,
                            0x80,
                            ALU8_FLAG_CARRY,
                            &flags,
                            &result
                );
        TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );
        fprintf(
                stderr,
                "\tNot 0x88 w/o carry: result=%02X flags=%02X\n",
                result,
                flags
        );
        displayFlags(flags);
        TINYTEST_TRUE( (0x78 == result) );
        TINYTEST_TRUE( (ALU8_FLAG_NONE == flags) );

        obj_Release(pObj);
        pObj = OBJ_NIL;
    }

    fprintf(stderr, "...%s completed.\n\n\n", pTestName);
    return 1;
}



int             test_ALU8_DecAdjust01 (
    const
    char            *pTestName
)
{
    ERESULT         eRc = ERESULT_SUCCESS;
    ALU8_DATA   *pObj = OBJ_NIL;
    bool            fRc;
    uint8_t         result;
    uint8_t         flags;

    fprintf(stderr, "Performing: %s\n", pTestName);

    pObj = ALU8_New( );
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    if (pObj) {

        //obj_TraceSet(pObj, true);
        fRc = obj_IsKindOf(pObj, OBJ_IDENT_ALU8);
        TINYTEST_TRUE( (fRc) );
        //TINYTEST_TRUE( (ERESULT_OK(eRc)) );

        eRc =   ALU8_Exec(
                            ALU8_OP_DEC_ADJUST,
                            0x9B,
                            4,
                            ALU8_FLAG_NONE,
                            &flags,
                            &result
                );
        TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );
        fprintf(
                stderr,
                "\tDecAdjust 0x9B w/o carry: result=%02X flags=%02X\n\n",
                result,
                flags
        );
        displayFlags(flags);
        TINYTEST_TRUE( (0x01 == result) );
        TINYTEST_TRUE( ((ALU8_FLAG_CARRY | ALU8_FLAG_AUX_CARRY) == flags) );

        eRc =   ALU8_Exec(
                            ALU8_OP_ADD,
                            0x29,
                            0x49,
                            flags,
                            &flags,
                            &result
                );
        TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );
        fprintf(
                stderr,
                "\tAdd 0x29+0x49 w/carry: result=%02X flags=%02X\n",
                result,
                flags
        );
        displayFlags(flags);
        TINYTEST_TRUE( (0x73 == result) );
        TINYTEST_TRUE( ((ALU8_FLAG_AUX_CARRY) == flags) );

        eRc =   ALU8_Exec(
                            ALU8_OP_DEC_ADJUST,
                            result,
                            127,
                            flags,
                            &flags,
                            &result
                );
        TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );
        fprintf(stderr, "\tDecAdjust 0x73 w/aux_carry: result=%02X flags=%02X\n", result, flags);
        displayFlags(flags);
        TINYTEST_TRUE( (0x79 == result) );
        TINYTEST_TRUE( (ALU8_FLAG_NONE == flags) );

        obj_Release(pObj);
        pObj = OBJ_NIL;
    }

    fprintf(stderr, "...%s completed.\n\n\n", pTestName);
    return 1;
}



int             test_ALU8_Not01 (
    const
    char            *pTestName
)
{
    ERESULT         eRc = ERESULT_SUCCESS;
    ALU8_DATA   *pObj = OBJ_NIL;
    bool            fRc;
    uint8_t         result;
    uint8_t         flags;

    fprintf(stderr, "Performing: %s\n", pTestName);

    pObj = ALU8_New( );
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    if (pObj) {

        //obj_TraceSet(pObj, true);
        fRc = obj_IsKindOf(pObj, OBJ_IDENT_ALU8);
        TINYTEST_TRUE( (fRc) );
        //TINYTEST_TRUE( (ERESULT_OK(eRc)) );

        eRc =   ALU8_Exec(
                            ALU8_OP_NOT,
                            0x88,
                            0x80,
                            ALU8_FLAG_NONE,
                            &flags,
                            &result
                );
        TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );
        fprintf(
                stderr,
                "\tNot 0x88 w/o carry: result=%02X flags=%02X\n",
                result,
                flags
        );
        displayFlags(flags);
        TINYTEST_TRUE( (0x77 == result) );
        TINYTEST_TRUE( (ALU8_FLAG_NONE == flags) );

        eRc =   ALU8_Exec(
                            ALU8_OP_NOT,
                            0x88,
                            0x80,
                            ALU8_FLAG_CARRY,
                            &flags,
                            &result
                );
        TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );
        fprintf(
                stderr,
                "\tNot 0x88 w/o carry: result=%02X flags=%02X\n",
                result,
                flags
        );
        displayFlags(flags);
        TINYTEST_TRUE( (0x77 == result) );
        TINYTEST_TRUE( (ALU8_FLAG_NONE == flags) );

        obj_Release(pObj);
        pObj = OBJ_NIL;
    }

    fprintf(stderr, "...%s completed.\n\n\n", pTestName);
    return 1;
}



int             test_ALU8_Or01 (
    const
    char            *pTestName
)
{
    ERESULT         eRc = ERESULT_SUCCESS;
    ALU8_DATA   *pObj = OBJ_NIL;
    bool            fRc;
    uint8_t         result;
    uint8_t         flags;

    fprintf(stderr, "Performing: %s\n", pTestName);

    pObj = ALU8_New( );
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    if (pObj) {

        //obj_TraceSet(pObj, true);
        fRc = obj_IsKindOf(pObj, OBJ_IDENT_ALU8);
        TINYTEST_TRUE( (fRc) );
        //TINYTEST_TRUE( (ERESULT_OK(eRc)) );

        eRc =   ALU8_Exec(
                            ALU8_OP_OR,
                            0x03,
                            0x80,
                            ALU8_FLAG_NONE,
                            &flags,
                            &result
                );
        TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );
        fprintf(
                stderr,
                "\tAdd 0x80 | 0x03 w/o carry: result=%02X flags=%02X\n",
                result,
                flags
        );
        displayFlags(flags);
        TINYTEST_TRUE( (0x83 == result) );
        TINYTEST_TRUE( (ALU8_FLAG_SIGN == flags) );

        eRc =   ALU8_Exec(
                            ALU8_OP_OR,
                            0x03,
                            0x80,
                            ALU8_FLAG_CARRY,
                            &flags,
                            &result
                );
        TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );
        fprintf(
                stderr,
                "\tAdd 0x80 | 0x03 w/o carry: result=%02X flags=%02X\n",
                result,
                flags
        );
        displayFlags(flags);
        TINYTEST_TRUE( (0x83 == result) );
        TINYTEST_TRUE( (ALU8_FLAG_SIGN == flags) );

        obj_Release(pObj);
        pObj = OBJ_NIL;
    }

    fprintf(stderr, "...%s completed.\n\n\n", pTestName);
    return 1;
}



int             test_ALU8_ShiftLeft01 (
    const
    char            *pTestName
)
{
    ERESULT         eRc = ERESULT_SUCCESS;
    ALU8_DATA   *pObj = OBJ_NIL;
    bool            fRc;
    uint8_t         result;
    uint8_t         flags;

    fprintf(stderr, "Performing: %s\n", pTestName);

    pObj = ALU8_New( );
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    if (pObj) {

        //obj_TraceSet(pObj, true);
        fRc = obj_IsKindOf(pObj, OBJ_IDENT_ALU8);
        TINYTEST_TRUE( (fRc) );
        //TINYTEST_TRUE( (ERESULT_OK(eRc)) );

        eRc =   ALU8_Exec(
                            ALU8_OP_SHIFT_LEFT,
                            0x83,
                            0x80,
                            ALU8_FLAG_NONE,
                            &flags,
                            &result
                );
        TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );
        fprintf(
                stderr,
                "\t(0x83 << 1) w/o carry: result=%02X flags=%02X\n",
                result,
                flags
        );
        displayFlags(flags);
        TINYTEST_TRUE( (0x06 == result) );
        TINYTEST_TRUE( ((ALU8_FLAG_CARRY | ALU8_FLAG_PARITY) == flags) );

        eRc =   ALU8_Exec(
                            ALU8_OP_SHIFT_LEFT,
                            0x83,
                            0x80,
                            ALU8_FLAG_CARRY,
                            &flags,
                            &result
                );
        TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );
        fprintf(
                stderr,
                "\t(0x83 << 1) w/carry: result=%02X flags=%02X\n",
                result,
                flags
        );
        displayFlags(flags);
        TINYTEST_TRUE( (0x07 == result) );
        TINYTEST_TRUE( (ALU8_FLAG_CARRY == flags) );

        obj_Release(pObj);
        pObj = OBJ_NIL;
    }

    fprintf(stderr, "...%s completed.\n\n\n", pTestName);
    return 1;
}



int             test_ALU8_ShiftRight01 (
    const
    char            *pTestName
)
{
    ERESULT         eRc = ERESULT_SUCCESS;
    ALU8_DATA   *pObj = OBJ_NIL;
    bool            fRc;
    uint8_t         result;
    uint8_t         flags;

    fprintf(stderr, "Performing: %s\n", pTestName);

    pObj = ALU8_New( );
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    if (pObj) {

        //obj_TraceSet(pObj, true);
        fRc = obj_IsKindOf(pObj, OBJ_IDENT_ALU8);
        TINYTEST_TRUE( (fRc) );
        //TINYTEST_TRUE( (ERESULT_OK(eRc)) );

        eRc =   ALU8_Exec(
                            ALU8_OP_SHIFT_RIGHT,
                            0x83,
                            0x80,
                            ALU8_FLAG_NONE,
                            &flags,
                            &result
                );
        TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );
        fprintf(
                stderr,
                "\t(0x83 >> 1) w/o carry: result=%02X flags=%02X\n",
                result,
                flags
        );
        displayFlags(flags);
        TINYTEST_TRUE( (0x41 == result) );
        TINYTEST_TRUE( ((ALU8_FLAG_CARRY | ALU8_FLAG_PARITY) == flags) );

        eRc =   ALU8_Exec(
                            ALU8_OP_SHIFT_RIGHT,
                            0x83,
                            0x80,
                            ALU8_FLAG_CARRY,
                            &flags,
                            &result
                );
        TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );
        fprintf(
                stderr,
                "\t(0x83 >> 1) w/carry: result=%02X flags=%02X\n",
                result,
                flags
        );
        displayFlags(flags);
        TINYTEST_TRUE( (0xC1 == result) );
        TINYTEST_TRUE( ((ALU8_FLAG_CARRY | ALU8_FLAG_SIGN) == flags) );

        obj_Release(pObj);
        pObj = OBJ_NIL;
    }

    fprintf(stderr, "...%s completed.\n\n\n", pTestName);
    return 1;
}



int             test_ALU8_Sub01 (
    const
    char            *pTestName
)
{
    ERESULT         eRc = ERESULT_SUCCESS;
    ALU8_DATA   *pObj = OBJ_NIL;
    bool            fRc;
    uint8_t         result;
    uint8_t         flags;

    fprintf(stderr, "Performing: %s\n", pTestName);

    pObj = ALU8_New( );
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    if (pObj) {

        //obj_TraceSet(pObj, true);
        fRc = obj_IsKindOf(pObj, OBJ_IDENT_ALU8);
        TINYTEST_TRUE( (fRc) );
        //TINYTEST_TRUE( (ERESULT_OK(eRc)) );

        eRc =   ALU8_Exec(
                            ALU8_OP_SUB,
                            4,
                            1,
                            ALU8_FLAG_NONE,
                            &flags,
                            &result
                );
        TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );
        fprintf(stderr, "\tSub 4-1 w/o carry: result=%02X flags=%02X\n", result, flags);
        displayFlags(flags);
        TINYTEST_TRUE( (3 == result) );
        TINYTEST_TRUE( (ALU8_FLAG_PARITY == flags) );

        eRc =   ALU8_Exec(
                            ALU8_OP_SUB,
                            2,
                            3,
                            ALU8_FLAG_CARRY,
                            &flags,
                            &result
                );
        TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );
        fprintf(stderr, "\tSub 2-3 w/carry: result=%02X flags=%02X\n", result, flags);
        displayFlags(flags);
        TINYTEST_TRUE( (0xFE == result) );
        TINYTEST_TRUE( ((ALU8_FLAG_SIGN | ALU8_FLAG_CARRY) == flags) );

        eRc =   ALU8_Exec(
                            ALU8_OP_SUB,
                            128,
                            1,
                            ALU8_FLAG_CARRY,
                            &flags,
                            &result
                );
        TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );
        fprintf(stderr, "\tSub 128-1 w/carry: result=%02X flags=%02X\n", result, flags);
        displayFlags(flags);
        TINYTEST_TRUE( (126 == result) );
        TINYTEST_TRUE( (ALU8_FLAG_PARITY == flags) );

        eRc =   ALU8_Exec(
                            ALU8_OP_ADD,
                            1,
                            254,
                            ALU8_FLAG_CARRY,
                            &flags,
                            &result
                );
        TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );
        fprintf(stderr, "\tSub 1-254 w/carry: result=%02X flags=%02X\n", result, flags);
        displayFlags(flags);
        TINYTEST_TRUE( (0 == result) );
        TINYTEST_TRUE( ((ALU8_FLAG_AUX_CARRY | ALU8_FLAG_PARITY | \
                         ALU8_FLAG_CARRY | ALU8_FLAG_ZERO) == flags) );

        obj_Release(pObj);
        pObj = OBJ_NIL;
    }

    fprintf(stderr, "...%s completed.\n\n\n", pTestName);
    return 1;
}



int             test_ALU8_Xor01 (
    const
    char            *pTestName
)
{
    ERESULT         eRc = ERESULT_SUCCESS;
    ALU8_DATA   *pObj = OBJ_NIL;
    bool            fRc;
    uint8_t         result;
    uint8_t         flags;

    fprintf(stderr, "Performing: %s\n", pTestName);

    pObj = ALU8_New( );
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    if (pObj) {

        //obj_TraceSet(pObj, true);
        fRc = obj_IsKindOf(pObj, OBJ_IDENT_ALU8);
        TINYTEST_TRUE( (fRc) );
        //TINYTEST_TRUE( (ERESULT_OK(eRc)) );

        eRc =   ALU8_Exec(
                            ALU8_OP_XOR,
                            0x03,
                            0x81,
                            ALU8_FLAG_NONE,
                            &flags,
                            &result
                );
        TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );
        fprintf(
                stderr,
                "\tAdd 0x80 | 0x03 w/o carry: result=%02X flags=%02X\n",
                result,
                flags
        );
        displayFlags(flags);
        TINYTEST_TRUE( (0x82 == result) );
        TINYTEST_TRUE( ((ALU8_FLAG_PARITY | ALU8_FLAG_SIGN) == flags) );

        eRc =   ALU8_Exec(
                            ALU8_OP_XOR,
                            0x03,
                            0x81,
                            ALU8_FLAG_CARRY,
                            &flags,
                            &result
                );
        TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );
        fprintf(
                stderr,
                "\tAdd 0x80 | 0x03 w/o carry: result=%02X flags=%02X\n",
                result,
                flags
        );
        displayFlags(flags);
        TINYTEST_TRUE( (0x82 == result) );
        TINYTEST_TRUE( ((ALU8_FLAG_PARITY | ALU8_FLAG_SIGN) == flags) );

        obj_Release(pObj);
        pObj = OBJ_NIL;
    }

    fprintf(stderr, "...%s completed.\n\n\n", pTestName);
    return 1;
}




TINYTEST_START_SUITE(test_ALU8);
    TINYTEST_ADD_TEST(test_ALU8_Xor01,setUp,tearDown);
    TINYTEST_ADD_TEST(test_ALU8_Sub01,setUp,tearDown);
    TINYTEST_ADD_TEST(test_ALU8_ShiftRight01,setUp,tearDown);
    TINYTEST_ADD_TEST(test_ALU8_ShiftLeft01,setUp,tearDown);
    TINYTEST_ADD_TEST(test_ALU8_Or01,setUp,tearDown);
    TINYTEST_ADD_TEST(test_ALU8_Not01,setUp,tearDown);
    TINYTEST_ADD_TEST(test_ALU8_DecAdjust01,setUp,tearDown);
    TINYTEST_ADD_TEST(test_ALU8_Complement01,setUp,tearDown);
    TINYTEST_ADD_TEST(test_ALU8_And01,setUp,tearDown);
    TINYTEST_ADD_TEST(test_ALU8_Add01,setUp,tearDown);
    TINYTEST_ADD_TEST(test_ALU8_GenParity01,setUp,tearDown);
    TINYTEST_ADD_TEST(test_ALU8_Test01,setUp,tearDown);
    //TINYTEST_ADD_TEST(test_ALU8_Copy01,setUp,tearDown);
    TINYTEST_ADD_TEST(test_ALU8_OpenClose,setUp,tearDown);
TINYTEST_END_SUITE();

TINYTEST_MAIN_SINGLE_SUITE(test_ALU8);





