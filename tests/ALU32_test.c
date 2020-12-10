// vi:nu:et:sts=4 ts=4 sw=4
/*
 *  Generated 12/06/2020 10:50:57
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
#include    <ALU32_internal.h>
#include    <JsonIn.h>
#ifdef  ALU32_JSON_SUPPORT
#   include    <SrcErrors.h>
#   include    <szTbl.h>
#endif



void            displayFlags (
    uint8_t         flags
)
{
    if (flags & ALU32_FLAG_CARRY)
        fprintf(stderr, "\t\tCarry\n");
    if (flags & ALU32_FLAG_PARITY)
        fprintf(stderr, "\t\tParity\n");
    if (flags & ALU32_FLAG_SIGN)
        fprintf(stderr, "\t\tSign\n");
    if (flags & ALU32_FLAG_ZERO)
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

#ifdef  ALU32_JSON_SUPPORT
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






int             test_ALU32_OpenClose (
    const
    char            *pTestName
)
{
    ERESULT         eRc = ERESULT_SUCCESS;
    ALU32_DATA       *pObj = OBJ_NIL;
    bool            fRc;
   
    fprintf(stderr, "Performing: %s\n", pTestName);

    pObj = ALU32_Alloc( );
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    pObj = ALU32_Init( pObj );
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    if (pObj) {

        //obj_TraceSet(pObj, true);       
        fRc = obj_IsKindOf(pObj, OBJ_IDENT_ALU32);
        TINYTEST_TRUE( (fRc) );
        
        // Test something.
        TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );

        obj_Release(pObj);
        pObj = OBJ_NIL;
    }

    fprintf(stderr, "...%s completed.\n\n\n", pTestName);
    return 1;
}



int             test_ALU32_Copy01 (
    const
    char            *pTestName
)
{
    ERESULT         eRc = ERESULT_SUCCESS;
    ALU32_DATA       *pObj1 = OBJ_NIL;
    ALU32_DATA       *pObj2 = OBJ_NIL;
    bool            fRc;
#if defined(ALU32_JSON_SUPPORT) && defined(XYZZY)
    ASTR_DATA       *pStr = OBJ_NIL;
#endif
   
    fprintf(stderr, "Performing: %s\n", pTestName);

    pObj1 = ALU32_New( );
    TINYTEST_FALSE( (OBJ_NIL == pObj1) );
    if (pObj1) {

        //obj_TraceSet(pObj1, true);       
        fRc = obj_IsKindOf(pObj1, OBJ_IDENT_ALU32);
        TINYTEST_TRUE( (fRc) );
        
        // Test assign.
        pObj2 = ALU32_New();
        TINYTEST_FALSE( (OBJ_NIL == pObj2) );
        eRc = ALU32_Assign(pObj1, pObj2);
        TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );

        fRc = obj_IsKindOf(pObj2, OBJ_IDENT_ALU32);
        TINYTEST_TRUE( (fRc) );
        //eRc = ALU32_Compare(pObj1, pObj2);
        //TINYTEST_TRUE( (ERESULT_SUCCESS_EQUAL == eRc) );
        //TODO: Add More tests here!

        obj_Release(pObj2);
        pObj2 = OBJ_NIL;

        // Test copy.
        pObj2 = ALU32_Copy(pObj1);
        TINYTEST_FALSE( (OBJ_NIL == pObj2) );

        fRc = obj_IsKindOf(pObj2, OBJ_IDENT_ALU32);
        TINYTEST_TRUE( (fRc) );
        //eRc = ALU32_Compare(pObj1, pObj2);
        //TINYTEST_TRUE( (ERESULT_SUCCESS_EQUAL == eRc) );
        //TODO: Add More tests here!

        obj_Release(pObj2);
        pObj2 = OBJ_NIL;

        // Test json support.
#if defined(ALU32_JSON_SUPPORT) && defined(XYZZY)
        pStr = ALU32_ToJson(pObj1);
        TINYTEST_FALSE( (OBJ_NIL == pStr) );
        fprintf(stderr, "JSON: %s\n", AStr_getData(pStr));
        pObj2 = ALU32_NewFromJsonString(pStr);
        TINYTEST_FALSE( (OBJ_NIL == pObj2) );
        fRc = obj_IsKindOf(pObj2, OBJ_IDENT_ALU32);
        TINYTEST_TRUE( (fRc) );
        obj_Release(pStr);
        pStr = OBJ_NIL;
        //eRc = ALU32_Compare(pObj1, pObj2);
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



int             test_ALU32_Test01 (
    const
    char            *pTestName
)
{
    //ERESULT         eRc = ERESULT_SUCCESS;
    ALU32_DATA       *pObj = OBJ_NIL;
    bool            fRc;
   
    fprintf(stderr, "Performing: %s\n", pTestName);

    pObj = ALU32_New( );
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    if (pObj) {

        //obj_TraceSet(pObj, true);       
        fRc = obj_IsKindOf(pObj, OBJ_IDENT_ALU32);
        TINYTEST_TRUE( (fRc) );
        //TINYTEST_TRUE( (ERESULT_OK(eRc)) );
        
        {
            ASTR_DATA       *pStr = ALU32_ToDebugString(pObj, 0);
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



int             test_ALU32_Parity01 (
    const
    char            *pTestName
)
{
    //ERESULT         eRc = ERESULT_SUCCESS;
    int             parity;

    fprintf(stderr, "Performing: %s\n", pTestName);

    parity = ALU32_even_parity(0);
    fprintf(stderr, "Parity(0): %d\n", parity);
    TINYTEST_TRUE( (1 == parity) );

    parity = ALU32_even_parity(1);
    fprintf(stderr, "Parity(1): %d\n", parity);
    TINYTEST_TRUE( (0 == parity) );

    parity = ALU32_even_parity(0x80000000);
    fprintf(stderr, "Parity(0x80000000): %d\n", parity);
    TINYTEST_TRUE( (0 == parity) );

    parity = ALU32_even_parity(0x80000001);
    fprintf(stderr, "Parity(0x80000001): %d\n", parity);
    TINYTEST_TRUE( (1 == parity) );

    parity = ALU32_even_parity(0x80808080);
    fprintf(stderr, "Parity(0x80808080): %d\n", parity);
    TINYTEST_TRUE( (1 == parity) );

    parity = ALU32_even_parity(0xFFFFFFFF);
    fprintf(stderr, "Parity(0xFFFFFFFF): %d\n", parity);
    TINYTEST_TRUE( (1 == parity) );

    fprintf(stderr, "...%s completed.\n\n\n", pTestName);
    return 1;
}



int             test_ALU32_Add01 (
    const
    char            *pTestName
)
{
    ERESULT         eRc = ERESULT_SUCCESS;
    ALU32_DATA   *pObj = OBJ_NIL;
    bool            fRc;
    uint32_t        result;
    uint8_t         flags;

    fprintf(stderr, "Performing: %s\n", pTestName);

    pObj = ALU32_New( );
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    if (pObj) {

        //obj_TraceSet(pObj, true);
        fRc = obj_IsKindOf(pObj, OBJ_IDENT_ALU32);
        TINYTEST_TRUE( (fRc) );
        //TINYTEST_TRUE( (ERESULT_OK(eRc)) );

        eRc =   ALU32_Exec(
                            ALU32_OP_ADD,
                            1,
                            4,
                            ALU32_FLAG_NONE,
                            &flags,
                            &result
                );
        TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );
        fprintf(stderr, "\tAdd 1+4 w/o carry: result=%02X flags=%02X\n", result, flags);
        displayFlags(flags);
        TINYTEST_TRUE( (5 == result) );
        TINYTEST_TRUE( (ALU32_FLAG_PARITY == flags) );

        eRc =   ALU32_Exec(
                            ALU32_OP_ADD,
                            2,
                            14,
                            ALU32_FLAG_CARRY,
                            &flags,
                            &result
                );
        TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );
        fprintf(stderr, "\tAdd 2+14 w/carry: result=%02X flags=%02X\n", result, flags);
        displayFlags(flags);
        TINYTEST_TRUE( (17 == result) );
        TINYTEST_TRUE( (ALU32_FLAG_PARITY == flags) );

        eRc =   ALU32_Exec(
                            ALU32_OP_ADD,
                            1,
                            0x7FFFFFFF,
                            ALU32_FLAG_CARRY,
                            &flags,
                            &result
                );
        TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );
        fprintf(stderr, "\tAdd 1+0x7FFFFFFF w/carry: result=%02X flags=%02X\n", result, flags);
        displayFlags(flags);
        TINYTEST_TRUE( (0x80000001 == result) );
        TINYTEST_TRUE( ((ALU32_FLAG_PARITY | ALU32_FLAG_SIGN) == flags) );

        eRc =   ALU32_Exec(
                            ALU32_OP_ADD,
                            1,
                            0xFFFFFFFE,
                            ALU32_FLAG_CARRY,
                            &flags,
                            &result
                );
        TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );
        fprintf(stderr, "\tAdd 1+0xFFFFFFFE w/carry: result=%02X flags=%02X\n", result, flags);
        displayFlags(flags);
        TINYTEST_TRUE( (0 == result) );
        TINYTEST_TRUE( ((ALU32_FLAG_PARITY | ALU32_FLAG_CARRY | ALU32_FLAG_ZERO) == flags) );

        obj_Release(pObj);
        pObj = OBJ_NIL;
    }

    fprintf(stderr, "...%s completed.\n\n\n", pTestName);
    return 1;
}



int             test_ALU32_And01 (
    const
    char            *pTestName
)
{
    ERESULT         eRc = ERESULT_SUCCESS;
    ALU32_DATA   *pObj = OBJ_NIL;
    bool            fRc;
    uint32_t        result;
    uint8_t         flags;

    fprintf(stderr, "Performing: %s\n", pTestName);

    pObj = ALU32_New( );
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    if (pObj) {

        //obj_TraceSet(pObj, true);
        fRc = obj_IsKindOf(pObj, OBJ_IDENT_ALU32);
        TINYTEST_TRUE( (fRc) );
        //TINYTEST_TRUE( (ERESULT_OK(eRc)) );

        eRc =   ALU32_Exec(
                            ALU32_OP_AND,
                            0x03,
                            1,
                            ALU32_FLAG_NONE,
                            &flags,
                            &result
                );
        TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );
        fprintf(stderr, "\tAdd 3&1 w/o carry: result=%02X flags=%02X\n", result, flags);
        displayFlags(flags);
        TINYTEST_TRUE( (0x01 == result) );
        TINYTEST_TRUE( (ALU32_FLAG_NONE == flags) );

        eRc =   ALU32_Exec(
                            ALU32_OP_AND,
                            0x03,
                            1,
                            ALU32_FLAG_CARRY,
                            &flags,
                            &result
                );
        TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );
        fprintf(stderr, "\tAdd 3&1 w/carry: result=%02X flags=%02X\n", result, flags);
        displayFlags(flags);
        TINYTEST_TRUE( (0x01 == result) );
        TINYTEST_TRUE( (ALU32_FLAG_NONE == flags) );

        obj_Release(pObj);
        pObj = OBJ_NIL;
    }

    fprintf(stderr, "...%s completed.\n\n\n", pTestName);
    return 1;
}



int             test_ALU32_Complement01 (
    const
    char            *pTestName
)
{
    ERESULT         eRc = ERESULT_SUCCESS;
    ALU32_DATA   *pObj = OBJ_NIL;
    bool            fRc;
    uint32_t        result;
    uint8_t         flags;

    fprintf(stderr, "Performing: %s\n", pTestName);

    pObj = ALU32_New( );
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    if (pObj) {

        //obj_TraceSet(pObj, true);
        fRc = obj_IsKindOf(pObj, OBJ_IDENT_ALU32);
        TINYTEST_TRUE( (fRc) );
        //TINYTEST_TRUE( (ERESULT_OK(eRc)) );

        eRc =   ALU32_Exec(
                            ALU32_OP_COMPLEMENT,
                            0x88,
                            0x80,
                            ALU32_FLAG_NONE,
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
        TINYTEST_TRUE( (0xFFFFFF78 == result) );
        TINYTEST_TRUE( (ALU32_FLAG_NONE == flags) );

        eRc =   ALU32_Exec(
                            ALU32_OP_COMPLEMENT,
                            0x88,
                            0x80,
                            ALU32_FLAG_CARRY,
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
        TINYTEST_TRUE( (0xFFFFFF78 == result) );
        TINYTEST_TRUE( (ALU32_FLAG_NONE == flags) );

        obj_Release(pObj);
        pObj = OBJ_NIL;
    }

    fprintf(stderr, "...%s completed.\n\n\n", pTestName);
    return 1;
}



int             test_ALU32_Not01 (
    const
    char            *pTestName
)
{
    ERESULT         eRc = ERESULT_SUCCESS;
    ALU32_DATA   *pObj = OBJ_NIL;
    bool            fRc;
    uint32_t        result;
    uint8_t         flags;

    fprintf(stderr, "Performing: %s\n", pTestName);

    pObj = ALU32_New( );
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    if (pObj) {

        //obj_TraceSet(pObj, true);
        fRc = obj_IsKindOf(pObj, OBJ_IDENT_ALU32);
        TINYTEST_TRUE( (fRc) );
        //TINYTEST_TRUE( (ERESULT_OK(eRc)) );

        eRc =   ALU32_Exec(
                            ALU32_OP_NOT,
                            0x88,
                            0x80,
                            ALU32_FLAG_NONE,
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
        TINYTEST_TRUE( (0xFFFFFF77 == result) );
        TINYTEST_TRUE( (ALU32_FLAG_NONE == flags) );

        eRc =   ALU32_Exec(
                            ALU32_OP_NOT,
                            0x88,
                            0x80,
                            ALU32_FLAG_CARRY,
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
        TINYTEST_TRUE( (0xFFFFFF77 == result) );
        TINYTEST_TRUE( (ALU32_FLAG_NONE == flags) );

        obj_Release(pObj);
        pObj = OBJ_NIL;
    }

    fprintf(stderr, "...%s completed.\n\n\n", pTestName);
    return 1;
}



int             test_ALU32_Or01 (
    const
    char            *pTestName
)
{
    ERESULT         eRc = ERESULT_SUCCESS;
    ALU32_DATA   *pObj = OBJ_NIL;
    bool            fRc;
    uint32_t        result;
    uint8_t         flags;

    fprintf(stderr, "Performing: %s\n", pTestName);

    pObj = ALU32_New( );
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    if (pObj) {

        //obj_TraceSet(pObj, true);
        fRc = obj_IsKindOf(pObj, OBJ_IDENT_ALU32);
        TINYTEST_TRUE( (fRc) );
        //TINYTEST_TRUE( (ERESULT_OK(eRc)) );

        eRc =   ALU32_Exec(
                            ALU32_OP_OR,
                            0x03,
                            0x80,
                            ALU32_FLAG_NONE,
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
        TINYTEST_TRUE( (ALU32_FLAG_NONE == flags) );

        eRc =   ALU32_Exec(
                            ALU32_OP_OR,
                            0x03,
                            0x80,
                            ALU32_FLAG_CARRY,
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
        TINYTEST_TRUE( (ALU32_FLAG_NONE == flags) );

        obj_Release(pObj);
        pObj = OBJ_NIL;
    }

    fprintf(stderr, "...%s completed.\n\n\n", pTestName);
    return 1;
}



int             test_ALU32_ShiftLeft01 (
    const
    char            *pTestName
)
{
    ERESULT         eRc = ERESULT_SUCCESS;
    ALU32_DATA   *pObj = OBJ_NIL;
    bool            fRc;
    uint32_t        result;
    uint8_t         flags;

    fprintf(stderr, "Performing: %s\n", pTestName);

    pObj = ALU32_New( );
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    if (pObj) {

        //obj_TraceSet(pObj, true);
        fRc = obj_IsKindOf(pObj, OBJ_IDENT_ALU32);
        TINYTEST_TRUE( (fRc) );
        //TINYTEST_TRUE( (ERESULT_OK(eRc)) );

        eRc =   ALU32_Exec(
                            ALU32_OP_SHIFT_LEFT,
                            0x80000003,
                            0x80,
                            ALU32_FLAG_NONE,
                            &flags,
                            &result
                );
        TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );
        fprintf(
                stderr,
                "\t(0x80000003 << 1) w/o carry: result=%02X flags=%02X\n",
                result,
                flags
        );
        displayFlags(flags);
        TINYTEST_TRUE( (0x06 == result) );
        TINYTEST_TRUE( (ALU32_FLAG_CARRY == flags) );

        eRc =   ALU32_Exec(
                            ALU32_OP_SHIFT_LEFT,
                            0x80000003,
                            0x80,
                            ALU32_FLAG_CARRY,
                            &flags,
                            &result
                );
        TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );
        fprintf(
                stderr,
                "\t(0x80000003 << 1) w/carry: result=%02X flags=%02X\n",
                result,
                flags
        );
        displayFlags(flags);
        TINYTEST_TRUE( (0x07 == result) );
        TINYTEST_TRUE( (ALU32_FLAG_CARRY == flags) );

        obj_Release(pObj);
        pObj = OBJ_NIL;
    }

    fprintf(stderr, "...%s completed.\n\n\n", pTestName);
    return 1;
}



int             test_ALU32_ShiftRight01 (
    const
    char            *pTestName
)
{
    ERESULT         eRc = ERESULT_SUCCESS;
    ALU32_DATA   *pObj = OBJ_NIL;
    bool            fRc;
    uint32_t        result;
    uint8_t         flags;

    fprintf(stderr, "Performing: %s\n", pTestName);

    pObj = ALU32_New( );
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    if (pObj) {

        //obj_TraceSet(pObj, true);
        fRc = obj_IsKindOf(pObj, OBJ_IDENT_ALU32);
        TINYTEST_TRUE( (fRc) );
        //TINYTEST_TRUE( (ERESULT_OK(eRc)) );

        eRc =   ALU32_Exec(
                            ALU32_OP_SHIFT_RIGHT,
                            0x83,
                            0x80,
                            ALU32_FLAG_NONE,
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
        TINYTEST_TRUE( (ALU32_FLAG_CARRY == flags) );

        eRc =   ALU32_Exec(
                            ALU32_OP_SHIFT_RIGHT,
                            0x83,
                            0x80,
                            ALU32_FLAG_CARRY,
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
        TINYTEST_TRUE( (ALU32_FLAG_CARRY == flags) );

        obj_Release(pObj);
        pObj = OBJ_NIL;
    }

    fprintf(stderr, "...%s completed.\n\n\n", pTestName);
    return 1;
}



int             test_ALU32_Sub01 (
    const
    char            *pTestName
)
{
    ERESULT         eRc = ERESULT_SUCCESS;
    ALU32_DATA   *pObj = OBJ_NIL;
    bool            fRc;
    uint32_t        result;
    uint8_t         flags;

    fprintf(stderr, "Performing: %s\n", pTestName);

    pObj = ALU32_New( );
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    if (pObj) {

        //obj_TraceSet(pObj, true);
        fRc = obj_IsKindOf(pObj, OBJ_IDENT_ALU32);
        TINYTEST_TRUE( (fRc) );
        //TINYTEST_TRUE( (ERESULT_OK(eRc)) );

        eRc =   ALU32_Exec(
                            ALU32_OP_SUB,
                            4,
                            1,
                            ALU32_FLAG_NONE,
                            &flags,
                            &result
                );
        TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );
        fprintf(stderr, "\tSub 4-1 w/o carry: result=%02X flags=%02X\n", result, flags);
        displayFlags(flags);
        TINYTEST_TRUE( (3 == result) );
        TINYTEST_TRUE( ((ALU32_FLAG_PARITY) == flags) );

        eRc =   ALU32_Exec(
                            ALU32_OP_SUB,
                            2,
                            3,
                            ALU32_FLAG_CARRY,
                            &flags,
                            &result
                );
        TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );
        fprintf(stderr, "\tSub 2-3 w/carry: result=%02X flags=%02X\n", result, flags);
        displayFlags(flags);
        TINYTEST_TRUE( (0xFFFFFFFE == result) );
        TINYTEST_TRUE( ((ALU32_FLAG_SIGN | ALU32_FLAG_CARRY) == flags) );

        eRc =   ALU32_Exec(
                            ALU32_OP_SUB,
                            0x80000000,
                            1,
                            ALU32_FLAG_CARRY,
                            &flags,
                            &result
                );
        TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );
        fprintf(stderr, "\tSub 0x80000000-1 w/carry: result=%02X flags=%02X\n", result, flags);
        displayFlags(flags);
        TINYTEST_TRUE( (0x7FFFFFFE == result) );
        TINYTEST_TRUE( (ALU32_FLAG_PARITY == flags) );

        eRc =   ALU32_Exec(
                            ALU32_OP_ADD,
                            1,
                            0xFFFFFFFE,
                            ALU32_FLAG_CARRY,
                            &flags,
                            &result
                );
        TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );
        fprintf(stderr, "\tSub 1-0xFFFFFFFE w/carry: result=%02X flags=%02X\n", result, flags);
        displayFlags(flags);
        TINYTEST_TRUE( (0 == result) );
        TINYTEST_TRUE( ((ALU32_FLAG_PARITY | \
                         ALU32_FLAG_CARRY | ALU32_FLAG_ZERO) == flags) );

        obj_Release(pObj);
        pObj = OBJ_NIL;
    }

    fprintf(stderr, "...%s completed.\n\n\n", pTestName);
    return 1;
}



int             test_ALU32_Xor01 (
    const
    char            *pTestName
)
{
    ERESULT         eRc = ERESULT_SUCCESS;
    ALU32_DATA   *pObj = OBJ_NIL;
    bool            fRc;
    uint32_t        result;
    uint8_t         flags;

    fprintf(stderr, "Performing: %s\n", pTestName);

    pObj = ALU32_New( );
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    if (pObj) {

        //obj_TraceSet(pObj, true);
        fRc = obj_IsKindOf(pObj, OBJ_IDENT_ALU32);
        TINYTEST_TRUE( (fRc) );
        //TINYTEST_TRUE( (ERESULT_OK(eRc)) );

        eRc =   ALU32_Exec(
                            ALU32_OP_XOR,
                            0x03,
                            0x81,
                            ALU32_FLAG_NONE,
                            &flags,
                            &result
                );
        TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );
        fprintf(
                stderr,
                "\tXOR 0x80 | 0x03 w/o carry: result=%02X flags=%02X\n",
                result,
                flags
        );
        displayFlags(flags);
        TINYTEST_TRUE( (0x82 == result) );
        TINYTEST_TRUE( ((ALU32_FLAG_PARITY) == flags) );

        eRc =   ALU32_Exec(
                            ALU32_OP_XOR,
                            0x03,
                            0x81,
                            ALU32_FLAG_CARRY,
                            &flags,
                            &result
                );
        TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );
        fprintf(
                stderr,
                "\tXOR 0x80 | 0x03 w/o carry: result=%02X flags=%02X\n",
                result,
                flags
        );
        displayFlags(flags);
        TINYTEST_TRUE( (0x82 == result) );
        TINYTEST_TRUE( ((ALU32_FLAG_PARITY) == flags) );

        obj_Release(pObj);
        pObj = OBJ_NIL;
    }

    fprintf(stderr, "...%s completed.\n\n\n", pTestName);
    return 1;
}




TINYTEST_START_SUITE(test_ALU32);
    TINYTEST_ADD_TEST(test_ALU32_Xor01,setUp,tearDown);
    TINYTEST_ADD_TEST(test_ALU32_Sub01,setUp,tearDown);
    TINYTEST_ADD_TEST(test_ALU32_ShiftRight01,setUp,tearDown);
    TINYTEST_ADD_TEST(test_ALU32_ShiftLeft01,setUp,tearDown);
    TINYTEST_ADD_TEST(test_ALU32_Or01,setUp,tearDown);
    TINYTEST_ADD_TEST(test_ALU32_Not01,setUp,tearDown);
    TINYTEST_ADD_TEST(test_ALU32_Complement01,setUp,tearDown);
    TINYTEST_ADD_TEST(test_ALU32_And01,setUp,tearDown);
    TINYTEST_ADD_TEST(test_ALU32_Add01,setUp,tearDown);
    TINYTEST_ADD_TEST(test_ALU32_Parity01,setUp,tearDown);
    TINYTEST_ADD_TEST(test_ALU32_Test01,setUp,tearDown);
    //TINYTEST_ADD_TEST(test_ALU32_Copy01,setUp,tearDown);
    TINYTEST_ADD_TEST(test_ALU32_OpenClose,setUp,tearDown);
TINYTEST_END_SUITE();

TINYTEST_MAIN_SINGLE_SUITE(test_ALU32);





