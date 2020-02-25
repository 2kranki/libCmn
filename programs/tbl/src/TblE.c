// vi:nu:et:sts=4 ts=4 sw=4
/*
 * File:   TblE.c
 *	Generated 02/22/2020 22:19:59
 *
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




//*****************************************************************
//* * * * * * * * * * * *  Data Definitions   * * * * * * * * * * *
//*****************************************************************

/* Header File Inclusion */
#include        <TblE_internal.h>
#include        <pplex.h>
#include        <SrcErrors.h>
#include        <trace.h>






#ifdef	__cplusplus
extern "C" {
#endif
    

    


 
    /****************************************************************
    * * * * * * * * * * *  Internal Subroutines   * * * * * * * * * *
    ****************************************************************/

    //---------------------------------------------------------------
    //                       Opcode Routines
    //---------------------------------------------------------------

    bool            TblE_opc_a (
        TBLE_DATA       *this,
        int32_t         opr1,
        int32_t         opr2
    )
    {

        this->accumulator += opr1;
        return true;
    }



    bool            TblE_opc_b (
        TBLE_DATA       *this,
        int32_t         opr1,
        int32_t         opr2
    )
    {
        this->pc = (uint16_t)opr1;
        return false;
    }



    bool            TblE_opc_bnz (
        TBLE_DATA       *this,
        int32_t         opr1,
        int32_t         opr2
    )
    {
        if (this->accumulator) {
            this->pc = (uint16_t)opr1;
            return false;
        }
        return true;
    }



    bool            TblE_opc_bz (
        TBLE_DATA       *this,
        int32_t         opr1,
        int32_t         opr2
    )
    {
        if (0 == this->accumulator) {
            this->pc = (uint16_t)opr1;
            return false;
        }
        return true;
    }



    bool            TblE_opc_call (
        TBLE_DATA       *this,
        int32_t         opr1,
        int32_t         opr2
    )
    {

        // Push PC.
        if (this->stackPointer >= this->cStack) {
            SrcErrors_AddFatalA(OBJ_NIL, NULL, "Stack Overflow");
        }
        this->pStack[this->stackPointer++] = this->pc + 3;

        // Goto Function
        this->pc = opr1;

        return false;
    }



    bool            TblE_opc_cma (
        TBLE_DATA       *this,
        int32_t         opr1,
        int32_t         opr2
    )
    {
        this->accumulator = -this->accumulator;
        return true;
    }



    bool            TblE_opc_dec (
        TBLE_DATA       *this,
        int32_t         opr1,
        int32_t         opr2
    )
    {
        this->accumulator--;
        return true;
    }



    bool            TblE_opc_eq (
        TBLE_DATA       *this,
        int32_t         opr1,
        int32_t         opr2
    )
    {
        if (opr1 == opr2)
            this->accumulator = 1;
        else
            this->accumulator = 0;
        return true;
    }



    bool            TblE_opc_exit (
        TBLE_DATA       *this,
        int32_t         opr1,
        int32_t         opr2
    )
    {

        return false;
    }



    bool            TblE_opc_halt (
        TBLE_DATA       *this,
        int32_t         opr1,
        int32_t         opr2
    )
    {

        return false;
    }



    bool            TblE_opc_inc (
        TBLE_DATA       *this,
        int32_t         opr1,
        int32_t         opr2
    )
    {
        this->accumulator++;
        return true;
    }



    // Load accumulator from register.
    bool            TblE_opc_lda (
        TBLE_DATA       *this,
        int32_t         opr1,           // Source - Register Index | Byte Constant
        int32_t         opr2
    )
    {
        this->accumulator = TblE_RegGet(this, opr1);
        return true;
    }



    // Load Register from inline constant.
    bool            TblE_opc_ldc2 (
        TBLE_DATA       *this,
        int32_t         opr1,           // Destination - Register Index
        int32_t         opr2            // Source - Register Index | Byte Constant
    )
    {
        if ((opr1 >= 128) && (opr1 <= 255))
            ;
        else {
            if (this->pInvalidRegAddr) {
                bool            fRc;
                fRc = this->pInvalidRegAddr(this->pInterruptObj, this->pc, opr1);
                return fRc;
            }
        }
        TblE_RegPut(this, opr1, opr2);
        return true;
    }



    // Load Register from inline constant.
    bool            TblE_opc_ldc4 (
        TBLE_DATA       *this,
        int32_t         opr1,           // Destination - Register Index
        int32_t         opr2            // Source - Register Index | Byte Constant
    )
    {
        if ((opr1 >= 128) && (opr1 <= 255))
            ;
        else {
            if (this->pInvalidRegAddr) {
                bool            fRc;
                fRc = this->pInvalidRegAddr(this->pInterruptObj, this->pc, opr1);
                return fRc;
            }
        }
        TblE_RegPut(this, opr1, opr2);
        return true;
    }



    // Load Register from Memory.
    bool            TblE_opc_ldm8 (
        TBLE_DATA       *this,
        int32_t         opr1,           // Destination - Register Index
        int32_t         opr2            // Source - Register Index | Byte Constant
    )
    {
        int32_t         num;

        if ((opr1 >= 128) && (opr1 <= 255))
            ;
        else {
            if (this->pInvalidRegAddr) {
                bool            fRc;
                fRc = this->pInvalidRegAddr(this->pInterruptObj, this->pc, opr1);
                return fRc;
            }
        }

        num = TblE_MemGet8(this, opr2);
        TblE_RegPut(this, opr1, num);

        return true;
    }



    // Load Register from Memory.
    bool            TblE_opc_ldm16 (
        TBLE_DATA       *this,
        int32_t         opr1,           // Destination - Register Index
        int32_t         opr2            // Source - Register Index | Byte Constant
    )
    {
        int32_t         num;

        if ((opr1 >= 128) && (opr1 <= 255))
            ;
        else {
            if (this->pInvalidRegAddr) {
                bool            fRc;
                fRc = this->pInvalidRegAddr(this->pInterruptObj, this->pc, opr1);
                return fRc;
            }
        }

        num = TblE_MemGet16(this, opr2);
        TblE_RegPut(this, opr1, num);

        return true;
    }



    // Load Register from Memory.
    bool            TblE_opc_ldm32 (
        TBLE_DATA       *this,
        int32_t         opr1,           // Destination - Register Index
        int32_t         opr2            // Source - Register Index | Byte Constant
    )
    {
        int32_t         num;

        if ((opr1 >= 128) && (opr1 <= 255))
            ;
        else {
            if (this->pInvalidRegAddr) {
                bool            fRc;
                fRc = this->pInvalidRegAddr(this->pInterruptObj, this->pc, opr1);
                return fRc;
            }
        }

        num = TblE_MemGet32(this, opr2);
        TblE_RegPut(this, opr1, num);

        return true;
    }



    bool            TblE_opc_ne (
        TBLE_DATA       *this,
        int32_t         opr1,       // Register Index | Byte Constant
        int32_t         opr2        // Register Index | Byte Constant
    )
    {
        int32_t         arg1;
        int32_t         arg2;

        arg1 = TblE_RegGet(this, opr1);
        arg2 = TblE_RegGet(this, opr2);
        if (arg1 == arg2)
            this->accumulator = 0;
        else
            this->accumulator = 1;
        return true;
    }



    bool            TblE_opc_nop (
        TBLE_DATA       *this,
        int32_t         opr1,
        int32_t         opr2
    )
    {
        return true;
    }



    bool            TblE_opc_not (
        TBLE_DATA       *this,
        int32_t         opr1,
        int32_t         opr2
    )
    {

        if (this->accumulator) {
            this->accumulator = 0;
        }
        else {
            this->accumulator = 1;
        }
        return true;
    }



    bool            TblE_opc_one (
        TBLE_DATA       *this,
        int32_t         opr1,
        int32_t         opr2
    )
    {
        this->accumulator = 1;
        return true;
    }



    bool            TblE_opc_popr (
        TBLE_DATA       *this,
        int32_t         opr1,
        int32_t         opr2
    )
    {
        int32_t         val;

        if (opr1 < 128) {
            return true;
        }
        if (this->stackPointer == 0) {
            fprintf(stderr, "\nFATAL - Stack Underflow!\n");
            exit(99);
        }
        val = this->pStack[this->stackPointer--];
        TblE_RegPut(this, opr1, val);

        return true;
    }



    bool            TblE_opc_pushr (
        TBLE_DATA       *this,
        int32_t         opr1,
        int32_t         opr2
    )
    {
        int32_t         val;

        if (opr1 < 128) {
            return true;
        }
        if (this->stackPointer == this->cStack) {
            fprintf(stderr, "\nFATAL - Stack Overflow!\n");
            exit(99);
        }
        val = TblE_RegGet(this, opr1);
        this->pStack[this->stackPointer++] = val;

        return true;
    }



    bool            TblE_opc_ret (
        TBLE_DATA       *this,
        int32_t         opr1,
        int32_t         opr2
    )
    {
        if (this->stackPointer == 0) {
            fprintf(stderr, "\nFATAL - Stack Underflow!\n");
            exit(99);
        }
        this->pc = this->pStack[this->stackPointer--];
        return false;
    }



    bool            TblE_opc_s (
        TBLE_DATA       *this,
        int32_t         opr1,           // Register Index | Byte Constant
        int32_t         opr2
    )
    {
        int32_t         arg1;

        arg1 = TblE_RegGet(this, opr1);
        this->accumulator -= arg1;
        return true;
    }



    bool            TblE_opc_sta (
        TBLE_DATA       *this,
        int32_t         opr1,           // Register Index
        int32_t         opr2
    )
    {

        if ((opr1 > 127) && (opr1 < 255)) {
            TblE_RegPut(this, opr1, this->accumulator);
        } else {
            bool            fRc;
            if (this->pInvalidRegAddr) {
                fRc = this->pInvalidRegAddr(this->pInterruptObj, this->pc, opr1);
            }
        }
        return true;
    }



    bool            TblE_opc_stderr (
        TBLE_DATA       *this,
        int32_t         opr1,
        int32_t         opr2
    )
    {
        fputc(this->accumulator, stdout);
        return true;

    }



    bool            TblE_opc_stdin (
        TBLE_DATA       *this,
        int32_t         opr1,
        int32_t         opr2
    )
    {
        this->accumulator = fgetwc(stdin);
        return true;
    }



    bool            TblE_opc_stdout (
        TBLE_DATA       *this,
        int32_t         opr1,
        int32_t         opr2
    )
    {
        fputc(this->accumulator, stdout);
        return true;
    }



    bool            TblE_opc_stm8 (
        TBLE_DATA       *this,
        int32_t         opr1,           // Register Index
        int32_t         opr2            // Memory Address
    )
    {
        int32_t         num;

        num = TblE_RegGet(this, opr1);
        TblE_MemPut8(this, opr2, num);
        return true;
    }



    bool            TblE_opc_stm16 (
        TBLE_DATA       *this,
        int32_t         opr1,           // Register Index
        int32_t         opr2            // Memory Address
    )
    {
        int32_t         num;

        num = TblE_RegGet(this, opr1);
        TblE_MemPut16(this, opr2, num);
        return true;
    }



    bool            TblE_opc_stm32 (
        TBLE_DATA       *this,
        int32_t         opr1,           // Register Index
        int32_t         opr2            // Memory Address
    )
    {
        int32_t         num;

        num = TblE_RegGet(this, opr1);
        TblE_MemPut32(this, opr2, num);
        return true;
    }



    bool            TblE_opc_svc (
        TBLE_DATA       *this,
        int32_t         opr1,
        int32_t         opr2
    )
    {

        switch (opr1) {
            default:
                break;
        }

        return true;
    }



    bool            TblE_opc_zero (
        TBLE_DATA       *this,
        int32_t         opr1,
        int32_t         opr2
    )
    {
        this->accumulator = 0;
        return true;
    }



    //---------------------------------------------------------------
    //                      Opcode Table
    //---------------------------------------------------------------

    // WARNING - These entries must match the TBLE_OPCODES enumeration in
    //              TblE.h.
    TBLE_OPCODE_ENTRY
                    opcodes[65] = {
        // opc+1, Mneumonic, Function, Length, Parameter 1 Type, Parameter 2 Type
        {TBLE_OPCODE_A, "a", TblE_opc_a, TBLE_ARGTYPE_CON1, 0},
        {TBLE_OPCODE_B, "b", TblE_opc_b, TBLE_ARGTYPE_PGMADR, 0},
        {TBLE_OPCODE_BNZ, "bnz", TblE_opc_bnz, TBLE_ARGTYPE_PGMADR, 0},
        {TBLE_OPCODE_BZ, "bz", TblE_opc_bz, TBLE_ARGTYPE_PGMADR, 0},
        {TBLE_OPCODE_CALL, "call", TblE_opc_call, TBLE_ARGTYPE_PGMADR, 0},
        {TBLE_OPCODE_CMA, "cma", TblE_opc_cma, 0, 0, 0},
        {TBLE_OPCODE_DEC, "dec", TblE_opc_dec, 0, 0, 0},
        {TBLE_OPCODE_EQ, "eq", TblE_opc_eq, TBLE_ARGTYPE_CON1, TBLE_ARGTYPE_CON1},
        {TBLE_OPCODE_EXIT, "exit", TblE_opc_exit, 0, 0},
        {TBLE_OPCODE_HALT, "halt", TblE_opc_halt, 0, 0},
        {TBLE_OPCODE_INC, "inc", TblE_opc_inc, 0, 0, 0},
        {TBLE_OPCODE_LDA, "lda", TblE_opc_lda, TBLE_ARGTYPE_CON1, 0},
        {TBLE_OPCODE_LDC2, "ldc2", TblE_opc_ldc2, TBLE_ARGTYPE_REG1, TBLE_ARGTYPE_INT2},
        {TBLE_OPCODE_LDC4, "ldc4", TblE_opc_ldc4, TBLE_ARGTYPE_REG1, TBLE_ARGTYPE_INT4},
        {TBLE_OPCODE_LDM8, "ldm8", TblE_opc_ldm8, TBLE_ARGTYPE_REG1, TBLE_ARGTYPE_MEMADR},
        {TBLE_OPCODE_LDM16, "ldm16", TblE_opc_ldm16, TBLE_ARGTYPE_REG1, TBLE_ARGTYPE_MEMADR},
        {TBLE_OPCODE_LDM32, "ldm32", TblE_opc_ldm32, TBLE_ARGTYPE_REG1, TBLE_ARGTYPE_MEMADR},
        {TBLE_OPCODE_NE, "ne", TblE_opc_ne, TBLE_ARGTYPE_CON1, TBLE_ARGTYPE_CON1},
        {TBLE_OPCODE_NOP, "nop", TblE_opc_nop, 0, 0, 0},
        {TBLE_OPCODE_NOT, "not", TblE_opc_not, 0, 0},
        {TBLE_OPCODE_ONE, "one", TblE_opc_one, 0, 0, 0},
        {TBLE_OPCODE_POPR, "popr", TblE_opc_popr, 0, 0, 0},
        {TBLE_OPCODE_PUSHR, "pushr", TblE_opc_pushr, 0, 0, 0},
        {TBLE_OPCODE_RET, "ret", TblE_opc_ret, 0, 0},
        {TBLE_OPCODE_S, "s", TblE_opc_s, TBLE_ARGTYPE_CON1, 0},
        {TBLE_OPCODE_STA, "sta", TblE_opc_sta, TBLE_ARGTYPE_REG1, 0},
        {TBLE_OPCODE_STDERR, "stderr", TblE_opc_stderr, 0, 0},
        {TBLE_OPCODE_STDIN, "stdin", TblE_opc_stdin, 0, 0},
        {TBLE_OPCODE_STDOUT, "stdout", TblE_opc_stdout, 0, 0},
        {TBLE_OPCODE_STM8, "stm8", TblE_opc_stm8, TBLE_ARGTYPE_CON1, TBLE_ARGTYPE_MEMADR},
        {TBLE_OPCODE_STM16, "stm16", TblE_opc_stm16, TBLE_ARGTYPE_CON1, TBLE_ARGTYPE_MEMADR},
        {TBLE_OPCODE_STM32, "stm32", TblE_opc_stm32, TBLE_ARGTYPE_CON1, TBLE_ARGTYPE_MEMADR},
        {TBLE_OPCODE_SVC, "svc", TblE_opc_sta, TBLE_ARGTYPE_CON1, TBLE_ARGTYPE_CON1},
        {TBLE_OPCODE_ZERO, "zero", TblE_opc_zero, 0, 0},
        {0, NULL, NULL}
    };





    /****************************************************************
    * * * * * * * * * * *  External Subroutines   * * * * * * * * * *
    ****************************************************************/


    //===============================================================
    //                      *** Class Methods ***
    //===============================================================

    TBLE_DATA *     TblE_Alloc (
        void
    )
    {
        TBLE_DATA       *this;
        uint32_t        cbSize = sizeof(TBLE_DATA);
        
        // Do initialization.
        
         this = obj_Alloc( cbSize );
        
        // Return to caller.
        return this;
    }



    TBLE_DATA *     TblE_New (
        void
    )
    {
        TBLE_DATA       *this;
        
        this = TblE_Alloc( );
        if (this) {
            this = TblE_Init(this);
        } 
        return this;
    }



    TBLE_DATA *     TblE_NewWithSizes (
        uint32_t        pgmSizeK,   // Program Size in K (1024 bytes) (0 == 62k)
        uint32_t        memSizeK,   // Memory Size in K (1024 bytes) (0 == 62k)
        uint32_t        stkSizeK    // Stack Size in K (1024 bytes) (0 == 2k)
    )
    {
        TBLE_DATA       *this;
        ERESULT         eRc;

        this = TblE_New( );
        if (this) {
            eRc = TblE_Setup(this, pgmSizeK, memSizeK, stkSizeK);
            if (ERESULT_FAILED(eRc)) {
                obj_Release(this);
                return OBJ_NIL;
            }
        }
        return this;
    }





    //===============================================================
    //                      P r o p e r t i e s
    //===============================================================

    //---------------------------------------------------------------
    //                  A c c u m u l a t o r
    //---------------------------------------------------------------

    int32_t         TblE_getAccum (
        TBLE_DATA     *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!TblE_Validate(this)) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        return this->accumulator;
    }


    bool            TblE_setAccum (
        TBLE_DATA       *this,
        int32_t         value
    )
    {
#ifdef NDEBUG
#else
        if (!TblE_Validate(this)) {
            DEBUG_BREAK();
            return false;
        }
#endif

        this->accumulator = value;

        return true;
    }



    //---------------------------------------------------------------
    //                      O p c o d e s
    //---------------------------------------------------------------

    TBLE_OPCODE_ENTRY * TblE_getOpcodes(
        TBLE_DATA     *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !TblE_Validate(this) ) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        return this->opcodes;
    }



    //---------------------------------------------------------------
    //                  P r o g r a m  C o u n t e r
    //---------------------------------------------------------------
    
    uint16_t        TblE_getPC (
        TBLE_DATA     *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!TblE_Validate(this)) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        return this->pc;
    }


    bool            TblE_setPC (
        TBLE_DATA       *this,
        uint16_t        value
    )
    {
#ifdef NDEBUG
#else
        if (!TblE_Validate(this)) {
            DEBUG_BREAK();
            return false;
        }
#endif

        this->pc = value;

        return true;
    }



    //---------------------------------------------------------------
    //                              S i z e
    //---------------------------------------------------------------
    
    uint32_t        TblE_getSize (
        TBLE_DATA       *this
    )
    {
#ifdef NDEBUG
#else
        if (!TblE_Validate(this)) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        return 0;
    }



    //---------------------------------------------------------------
    //                          S u p e r
    //---------------------------------------------------------------
    
    OBJ_IUNKNOWN *  TblE_getSuperVtbl (
        TBLE_DATA     *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!TblE_Validate(this)) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        
        return this->pSuperVtbl;
    }
    
  

    

    //===============================================================
    //                          M e t h o d s
    //===============================================================


    //---------------------------------------------------------------
    //                       A d d  O p c o d e
    //---------------------------------------------------------------

    /*!
     Enable operation of this object.
     @param     this    object pointer
     @return    if successful, ERESULT_SUCCESS.  Otherwise, an ERESULT_*
                error code.
     */
    ERESULT         TblE_AddOpcode (
        TBLE_DATA       *this,
        TBLE_OPCODE_ENTRY
                        *pEntry
    )
    {
        //ERESULT         eRc;

        // Do initialization.
#ifdef NDEBUG
#else
        if (!TblE_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if ((pEntry->opc >= 64) && (pEntry->opc <= 255))
            ;
        else {
            return ERESULT_INVALID_DATA;
        }
#endif

        obj_Enable(this);

        // Put code here...

        // Return to caller.
        return ERESULT_SUCCESS;
    }



    //---------------------------------------------------------------
    //                       A s s i g n
    //---------------------------------------------------------------
    
    /*!
     Assign the contents of this object to the other object (ie
     this -> other).  Any objects in other will be released before 
     a copy of the object is performed.
     Example:
     @code 
        ERESULT eRc = TblE_Assign(this,pOther);
     @endcode 
     @param     this    object pointer
     @param     pOther  a pointer to another TBLE object
     @return    If successful, ERESULT_SUCCESS otherwise an 
                ERESULT_* error 
     */
    ERESULT         TblE_Assign (
        TBLE_DATA		*this,
        TBLE_DATA     *pOther
    )
    {
        ERESULT     eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if (!TblE_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if (!TblE_Validate(pOther)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif

        // Assign any Super(s).
        if (this->pSuperVtbl && (this->pSuperVtbl->pWhoAmI() != OBJ_IDENT_OBJ)) {
            if (this->pSuperVtbl->pAssign) {
                eRc = this->pSuperVtbl->pAssign(this, pOther);
                if (ERESULT_FAILED(eRc)) {
                    return eRc;
                }
            }
        }

        // Release objects and areas in other object.
#ifdef  XYZZY
        if (pOther->pArray) {
            obj_Release(pOther->pArray);
            pOther->pArray = OBJ_NIL;
        }
#endif

        // Create a copy of objects and areas in this object placing
        // them in other.
#ifdef  XYZZY
        if (this->pArray) {
            if (obj_getVtbl(this->pArray)->pCopy) {
                pOther->pArray = obj_getVtbl(this->pArray)->pCopy(this->pArray);
            }
            else {
                obj_Retain(this->pArray);
                pOther->pArray = this->pArray;
            }
        }
#endif

        // Copy other data from this object to other.
        
        //goto eom;

        // Return to caller.
        eRc = ERESULT_SUCCESS;
    eom:
        //FIXME: Implement the assignment.        
        eRc = ERESULT_NOT_IMPLEMENTED;
        return eRc;
    }
    
    
    
    //---------------------------------------------------------------
    //                      C o m p a r e
    //---------------------------------------------------------------
    
    /*!
     Compare the two provided objects.
     @return    ERESULT_SUCCESS_EQUAL if this == other
                ERESULT_SUCCESS_LESS_THAN if this < other
                ERESULT_SUCCESS_GREATER_THAN if this > other
     */
    ERESULT         TblE_Compare (
        TBLE_DATA     *this,
        TBLE_DATA     *pOther
    )
    {
        int             i = 0;
        ERESULT         eRc = ERESULT_SUCCESS_EQUAL;
#ifdef  xyzzy        
        const
        char            *pStr1;
        const
        char            *pStr2;
#endif
        
#ifdef NDEBUG
#else
        if (!TblE_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if (!TblE_Validate(pOther)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_PARAMETER;
        }
#endif

#ifdef  xyzzy        
        if (this->token == pOther->token) {
            this->eRc = eRc;
            return eRc;
        }
        
        pStr1 = szTbl_TokenToString(OBJ_NIL, this->token);
        pStr2 = szTbl_TokenToString(OBJ_NIL, pOther->token);
        i = strcmp(pStr1, pStr2);
#endif

        
        if (i < 0) {
            eRc = ERESULT_SUCCESS_LESS_THAN;
        }
        if (i > 0) {
            eRc = ERESULT_SUCCESS_GREATER_THAN;
        }
        
        return eRc;
    }
    
   
 
    //---------------------------------------------------------------
    //                          C o p y
    //---------------------------------------------------------------
    
    /*!
     Copy the current object creating a new object.
     Example:
     @code 
        TblE      *pCopy = TblE_Copy(this);
     @endcode 
     @param     this    object pointer
     @return    If successful, a TBLE object which must be 
                released, otherwise OBJ_NIL.
     @warning   Remember to release the returned object.
     */
    TBLE_DATA *     TblE_Copy (
        TBLE_DATA       *this
    )
    {
        TBLE_DATA       *pOther = OBJ_NIL;
        ERESULT         eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if (!TblE_Validate(this)) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
#ifdef TBLE_IS_IMMUTABLE
        obj_Retain(this);
        pOther = this;
#else
        pOther = TblE_New( );
        if (pOther) {
            eRc = TblE_Assign(this, pOther);
            if (ERESULT_HAS_FAILED(eRc)) {
                obj_Release(pOther);
                pOther = OBJ_NIL;
            }
        }
#endif
        
        // Return to caller.
        return pOther;
    }
    
    
    
    //---------------------------------------------------------------
    //                        D e a l l o c
    //---------------------------------------------------------------

    void            TblE_Dealloc (
        OBJ_ID          objId
    )
    {
        TBLE_DATA   *this = objId;
        //ERESULT         eRc;

        // Do initialization.
        if (NULL == this) {
            return;
        }        
#ifdef NDEBUG
#else
        if (!TblE_Validate(this)) {
            DEBUG_BREAK();
            return;
        }
#endif

#ifdef XYZZY
        if (obj_IsEnabled(this)) {
            ((TBLE_VTBL *)obj_getVtbl(this))->devVtbl.pStop((OBJ_DATA *)this,NULL);
        }
#endif

        TblE_Release(this);

        obj_setVtbl(this, this->pSuperVtbl);
        // pSuperVtbl is saved immediately after the super
        // object which we inherit from is initialized.
        this->pSuperVtbl->pDealloc(this);
        this = OBJ_NIL;

        // Return to caller.
    }



    //---------------------------------------------------------------
    //                         D e e p  C o p y
    //---------------------------------------------------------------
    
    /*!
     Copy the current object creating a new object.
     Example:
     @code 
        TblE      *pDeepCopy = TblE_Copy(this);
     @endcode 
     @param     this    object pointer
     @return    If successful, a TBLE object which must be 
                released, otherwise OBJ_NIL.
     @warning   Remember to release the returned object.
     */
    TBLE_DATA *     TblE_DeepyCopy (
        TBLE_DATA       *this
    )
    {
        TBLE_DATA       *pOther = OBJ_NIL;
        ERESULT         eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if (!TblE_Validate(this)) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
        pOther = TblE_New( );
        if (pOther) {
            eRc = TblE_Assign(this, pOther);
            if (ERESULT_HAS_FAILED(eRc)) {
                obj_Release(pOther);
                pOther = OBJ_NIL;
            }
        }
        
        // Return to caller.
        return pOther;
    }
    
    
    
    //---------------------------------------------------------------
    //                      D i s a b l e
    //---------------------------------------------------------------

    /*!
     Disable operation of this object.
     @param     this    object pointer
     @return    if successful, ERESULT_SUCCESS.  Otherwise, an ERESULT_*
                error code.
     */
    ERESULT         TblE_Disable (
        TBLE_DATA		*this
    )
    {
        //ERESULT         eRc;

        // Do initialization.
#ifdef NDEBUG
#else
        if (!TblE_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif

        // Put code here...

        obj_Disable(this);
        
        // Return to caller.
        return ERESULT_SUCCESS;
    }



    //---------------------------------------------------------------
    //                          E n a b l e
    //---------------------------------------------------------------

    /*!
     Enable operation of this object.
     @param     this    object pointer
     @return    if successful, ERESULT_SUCCESS.  Otherwise, an ERESULT_*
                error code.
     */
    ERESULT         TblE_Enable (
        TBLE_DATA		*this
    )
    {
        //ERESULT         eRc;

        // Do initialization.
#ifdef NDEBUG
#else
        if (!TblE_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif
        
        obj_Enable(this);

        // Put code here...
        
        // Return to caller.
        return ERESULT_SUCCESS;
    }



    //---------------------------------------------------------------
    //                          E x e c
    //---------------------------------------------------------------

    /*!
     Execute the current opcode.
     @param     this    object pointer
     @return    if successful, ERESULT_SUCCESS.  Otherwise, an ERESULT_*
                error code.
     */
    ERESULT         TblE_Exec (
        TBLE_DATA       *this
    )
    {
        //ERESULT         eRc;
        uint8_t         opcode;
        TBLE_OPCODE_ENTRY
                        *pOpcode;
        int32_t         oprnd1 = 0;
        int32_t         oprnd2 = 0;
        int32_t         oprnd3 = 0;
        uint16_t        oprndLen;
        uint16_t        pc;
        bool            fRc;

        // Do initialization.
#ifdef NDEBUG
#else
        if (!TblE_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif

        pc = this->pc;
        opcode = this->pProgram[this->pc];
        pOpcode = &this->opcodes[opcode];
        if (pOpcode->pExec == NULL) {
            return ERESULT_DATA_MISSING;
        }
        pc++;

        if (pOpcode->arg1Type) {
            oprnd1 = TblE_OperandGet(this, pOpcode->arg1Type, pc, &oprndLen);
            if (oprndLen)
                pc += oprndLen;
        }

        if (pOpcode->arg2Type) {
            oprnd2 = TblE_OperandGet(this, pOpcode->arg2Type, pc, &oprndLen);
            if (oprndLen)
                pc += oprndLen;
        }

        if (pOpcode->arg3Type) {
            oprnd3 = TblE_OperandGet(this, pOpcode->arg3Type, pc, &oprndLen);
            if (oprndLen)
                pc += oprndLen;
        }

        fRc = pOpcode->pExec(this, oprnd1, oprnd2);
        if (fRc)
            this->pc = pc;

        // Return to caller.
        return ERESULT_SUCCESS;
    }



    //---------------------------------------------------------------
    //                          I n i t
    //---------------------------------------------------------------

    TBLE_DATA *   TblE_Init (
        TBLE_DATA       *this
    )
    {
        uint32_t        cbSize = sizeof(TBLE_DATA);
        //ERESULT         eRc;
        uint32_t        i;
        TBLE_OPCODE_ENTRY
                        *pOpcode = opcodes;
        if (OBJ_NIL == this) {
            return OBJ_NIL;
        }
        
        /* cbSize can be zero if Alloc() was not called and we are
         * are passed the address of a zero'd area.
         */
        //cbSize = obj_getSize(this);       // cbSize must be set in Alloc().
        if (cbSize == 0) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }

        //this = (OBJ_ID)other_Init((OTHER_DATA *)this);        // Needed for Inheritance
        this = (OBJ_ID)obj_Init(this, cbSize, OBJ_IDENT_TBLE);
        if (OBJ_NIL == this) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
        obj_setSize(this, cbSize);
        this->pSuperVtbl = obj_getVtbl(this);
        obj_setVtbl(this, (OBJ_IUNKNOWN *)&TblE_Vtbl);

        while (pOpcode->opc) {
            this->opcodes[pOpcode->opc] = *pOpcode;
            pOpcode++;
        }

#ifdef NDEBUG
#else
        if (!TblE_Validate(this)) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
#if defined(__APPLE__) && defined(XYZZY)
//#if defined(__APPLE__)
        fprintf(
                stderr, 
                "TblE::sizeof(TBLE_DATA) = %lu\n", 
                sizeof(TBLE_DATA)
        );
#endif
        BREAK_NOT_BOUNDARY4(sizeof(TBLE_DATA));
#endif

        return this;
    }

     

    //---------------------------------------------------------------
    //                       I s E n a b l e d
    //---------------------------------------------------------------
    
    ERESULT         TblE_IsEnabled (
        TBLE_DATA		*this
    )
    {
        //ERESULT         eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if (!TblE_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif
        
        if (obj_IsEnabled(this)) {
            return ERESULT_SUCCESS_TRUE;
        }
        
        // Return to caller.
        return ERESULT_SUCCESS_FALSE;
    }
    
    
    
    //---------------------------------------------------------------
    //                  L o a d  P r o g r a m
    //---------------------------------------------------------------

    ERESULT         TblE_LoadProgramFromFile(
        TBLE_DATA       *this,
        PATH_DATA       *pInput
    )
    {
        ASTR_DATA       *pProgram = OBJ_NIL;
        uint32_t        i;
        PPLEX_DATA      *pLex = OBJ_NIL;

        // Do initialization.
#ifdef NDEBUG
#else
        if( !TblE_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif

        pProgram = AStr_NewFromUtf8File(pInput);
        if (OBJ_NIL == pProgram) {
            return ERESULT_DATA_NOT_FOUND;
        }

        // Fill program memory with unknown opcode;
        for (i=0; i<this->cProgram; ++i) {
            this->pProgram[i] = TBLE_OPCODE_UNKNOWN;
        }

        // Return to caller.
        return ERESULT_SUCCESS;
    }


    ERESULT         TblE_LoadProgramFromString(
        TBLE_DATA       *this,
        ASTR_DATA       *pInput
    )
    {
        ASTR_DATA       *pProgram = OBJ_NIL;
        uint32_t        i;
        PPLEX_DATA      *pLex = OBJ_NIL;

        // Do initialization.
#ifdef NDEBUG
#else
        if( !TblE_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif

        // Fill program memory with unknown opcode;
        for (i=0; i<this->cProgram; ++i) {
            this->pProgram[i] = TBLE_OPCODE_UNKNOWN;
        }

        // Return to caller.
        return ERESULT_SUCCESS;
    }



    //---------------------------------------------------------------
    //                       M e m o r y
    //---------------------------------------------------------------

    int32_t         TblE_MemGet8 (
        TBLE_DATA       *this,
        uint32_t        index
    )
    {
        int32_t         iRc = 0;

        if (index < this->cMemory) {
            iRc = this->pMemory[index];
        }
        else {
            DEBUG_BREAK();
            SrcErrors_AddFatalA(OBJ_NIL, NULL, "Invalid Variable Index");
        }
        return iRc;
    }


    void            TblE_MemPut8 (
        TBLE_DATA       *this,
        uint32_t        index,
        int32_t         value
    )
    {
        if (index >= this->cMemory) {
            DEBUG_BREAK();
            SrcErrors_AddFatalA(OBJ_NIL, NULL, "Invalid Variable Index");
        }
        this->pMemory[index++] = value & 0xFF;
    }



    //Todo: should we be sign-extending?????
    int32_t         TblE_MemGet16 (
        TBLE_DATA       *this,
        uint32_t        index
    )
    {
        int32_t         iRc = 0;

        if (index < (this->cMemory - 2)) {
            iRc = this->pMemory[index] | (this->pMemory[index+1] << 8);
        }
        else {
            DEBUG_BREAK();
            SrcErrors_AddFatalA(OBJ_NIL, NULL, "Invalid Variable Index");
        }
        return iRc;
    }


    void            TblE_MemPut16 (
        TBLE_DATA       *this,
        uint32_t        index,
        int32_t         value
    )
    {
        if (index >= (this->cMemory - 2)) {
            DEBUG_BREAK();
            SrcErrors_AddFatalA(OBJ_NIL, NULL, "Invalid Variable Index");
        }
        this->pMemory[index++] = value & 0xFF;
        this->pMemory[index++] = (value >> 8) & 0xFF;
    }



    int32_t         TblE_MemGet32 (
        TBLE_DATA       *this,
        uint32_t        index
    )
    {
        int32_t         iRc = 0;

        if (index < (this->cMemory - 4)) {
            iRc = this->pMemory[index]
                | (this->pMemory[index+1] << 8)
                | (this->pMemory[index+2] << 16)
                | (this->pMemory[index+3] << 24);
        }
        else {
            DEBUG_BREAK();
            SrcErrors_AddFatalA(OBJ_NIL, NULL, "Invalid Variable Index");
        }
        return iRc;
    }


    void            TblE_MemPut32 (
        TBLE_DATA       *this,
        uint32_t        index,
        int32_t         value
    )
    {
        if (index >= (this->cMemory - 4)) {
            DEBUG_BREAK();
            SrcErrors_AddFatalA(OBJ_NIL, NULL, "Invalid Variable Index");
        }
        this->pMemory[index++] = value & 0xFF;
        this->pMemory[index++] = (value >> 8) & 0xFF;
        this->pMemory[index++] = (value >> 16) & 0xFF;
        this->pMemory[index++] = (value >> 24) & 0xFF;
    }



    int32_t         TblE_MemSet (
        TBLE_DATA       *this,
        uint32_t        index,
        uint32_t        len,
        uint8_t         value
    )
    {
        uint32_t        i;
        //int32_t         iRc = 0;

        if ((index + len) >= this->cMemory) {
            DEBUG_BREAK();
            SrcErrors_AddFatalA(OBJ_NIL, NULL, "Address Range");
        }
        if ((index + len) < index) {
            DEBUG_BREAK();
            SrcErrors_AddFatalA(OBJ_NIL, NULL, "Address Overflow");
        }
        for (i=0; i<len; ++i) {
            this->pMemory[i+len] = value;
        }

        return 0;
    }



    //---------------------------------------------------------------
    //                       O p e r a n d
    //---------------------------------------------------------------

    int32_t         TblE_OperandGet (
        TBLE_DATA       *this,
        uint8_t         type,
        uint32_t        addr,
        uint16_t        *pLen       // Returned Operand Length
    )
    {
        int32_t         iRc = 0;
        uint16_t        len = 0;

        if (pLen)
            *pLen = 0;

        if (addr < this->cProgram) {
            type = this->pProgram[addr];
            switch (type) {
                case TBLE_ARGTYPE_CON1:
                    iRc = this->pProgram[addr];
                    len = 1;
                    break;

                case TBLE_ARGTYPE_INT2:
                    if (addr < (this->cProgram - 2)) {
                        iRc = (int16_t)(this->pProgram[addr]
                                        | (this->pProgram[addr+1] << 8));
                    }
                    len = 2;
                    break;

                case TBLE_ARGTYPE_INT4:
                    if (addr < (this->cProgram - 2)) {
                        iRc = (int32_t)(this->pProgram[addr]
                                        | (this->pProgram[addr+1] << 8)
                                        | (this->pProgram[addr+2] << 16)
                                        | (this->pProgram[addr+3] << 24));
                    }
                    len = 4;
                    break;

                case TBLE_ARGTYPE_PGMADR:
                    if (addr < (this->cProgram - 2)) {
                        iRc = (uint16_t)(this->pProgram[addr]
                                         | (this->pProgram[addr+1] << 8));
                    }
                    len = 2;
                    break;

                case TBLE_ARGTYPE_MEMADR:
                    if (addr < (this->cProgram - 2)) {
                        iRc = (int16_t)(this->pProgram[addr]
                                        | (this->pProgram[addr+1] << 8));
                    }
                    len = 2;
                    break;

                default:
                    break;
            }
        }

        if (pLen)
            *pLen = len;
        return iRc;
    }


    //---------------------------------------------------------------
    //                     Q u e r y  I n f o
    //---------------------------------------------------------------
    
    /*!
     Return information about this object. This method can translate
     methods to strings and vice versa, return the address of the
     object information structure.
     Example:
     @code
        // Return a method pointer for a string or NULL if not found. 
        void        *pMethod = TblE_QueryInfo(this, OBJ_QUERYINFO_TYPE_METHOD, "xyz");
     @endcode 
     @param     objId   object pointer
     @param     type    one of OBJ_QUERYINFO_TYPE members (see obj.h)
     @param     pData   for OBJ_QUERYINFO_TYPE_INFO, this field is not used,
                        for OBJ_QUERYINFO_TYPE_METHOD, this field points to a 
                        character string which represents the method name without
                        the object name, "TblE", prefix,
                        for OBJ_QUERYINFO_TYPE_PTR, this field contains the
                        address of the method to be found.
     @return    If unsuccessful, NULL. Otherwise, for:
                OBJ_QUERYINFO_TYPE_INFO: info pointer,
                OBJ_QUERYINFO_TYPE_METHOD: method pointer,
                OBJ_QUERYINFO_TYPE_PTR: constant UTF-8 method name pointer
     */
    void *          TblE_QueryInfo (
        OBJ_ID          objId,
        uint32_t        type,
        void            *pData
    )
    {
        TBLE_DATA     *this = objId;
        const
        char            *pStr = pData;
        
        if (OBJ_NIL == this) {
            return NULL;
        }
#ifdef NDEBUG
#else
        if (!TblE_Validate(this)) {
            DEBUG_BREAK();
            return NULL;
        }
#endif
        
        switch (type) {
                
        case OBJ_QUERYINFO_TYPE_OBJECT_SIZE:
            return (void *)sizeof(TBLE_DATA);
            break;
            
            case OBJ_QUERYINFO_TYPE_CLASS_OBJECT:
                return (void *)TblE_Class();
                break;
                
#ifdef XYZZY  
        // Query for an address to specific data within the object.  
        // This should be used very sparingly since it breaks the 
        // object's encapsulation.                 
        case OBJ_QUERYINFO_TYPE_DATA_PTR:
            switch (*pStr) {
 
                case 'S':
                    if (str_Compare("SuperVtbl", (char *)pStr) == 0) {
                        return &this->pSuperVtbl;
                    }
                    break;
                    
                default:
                    break;
            }
            break;
#endif
             case OBJ_QUERYINFO_TYPE_INFO:
                return (void *)obj_getInfo(this);
                break;
                
            case OBJ_QUERYINFO_TYPE_METHOD:
                switch (*pStr) {
                        
                    case 'D':
                        if (str_Compare("Disable", (char *)pStr) == 0) {
                            return TblE_Disable;
                        }
                        break;

                    case 'E':
                        if (str_Compare("Enable", (char *)pStr) == 0) {
                            return TblE_Enable;
                        }
                        break;

#ifdef  TBLE_JSON_SUPPORT
                    case 'P':
                        if (str_Compare("ParseJsonFields", (char *)pStr) == 0) {
                            return TblE_ParseJsonFields;
                        }
                        if (str_Compare("ParseJsonObject", (char *)pStr) == 0) {
                            return TblE_ParseJsonObject;
                        }
                        break;
#endif

                    case 'T':
                        if (str_Compare("ToDebugString", (char *)pStr) == 0) {
                            return TblE_ToDebugString;
                        }
#ifdef  TBLE_JSON_SUPPORT
                        if (str_Compare("ToJson", (char *)pStr) == 0) {
                            return TblE_ToJson;
                        }
#endif
                        break;
                        
                    default:
                        break;
                }
                break;
                
            case OBJ_QUERYINFO_TYPE_PTR:
                if (pData == TblE_ToDebugString)
                    return "ToDebugString";
#ifdef  TBLE_JSON_SUPPORT
                if (pData == TblE_ToJson)
                    return "ToJson";
#endif
                break;
                
            default:
                break;
        }
        
        return this->pSuperVtbl->pQueryInfo(objId, type, pData);
    }
    
    
    
    //---------------------------------------------------------------
    //                       R e g i s t e r
    //---------------------------------------------------------------

    int32_t         TblE_RegGet (
        TBLE_DATA       *this,
        uint16_t        index
    )
    {
        if (index < 128) {
            return index;
        }
        index -= 128;
        if ((index >= 0) && (index <= 127)) {
            index = this->regs[index];
        }
        else {
            SrcErrors_AddFatalA(OBJ_NIL, NULL, "Invalid Argument Index");
        }
        return index;
    }


    void            TblE_RegPut (
        TBLE_DATA       *this,
        uint16_t        index,
        int32_t         value
    )
    {
        if (index < 128) {
            DEBUG_BREAK();
            SrcErrors_AddFatalA(OBJ_NIL, NULL, "Invalid Argument Index");
        }
        index -= 128;
        if ((index >= 0) && (index <= 127)) {
            this->regs[index] = value;
        }
        else {
            DEBUG_BREAK();
            SrcErrors_AddFatalA(OBJ_NIL, NULL, "Invalid Argument Index");
        }
    }



    //---------------------------------------------------------------
    //                          F r e e
    //---------------------------------------------------------------

    /*!
     Free the areas gotten for the machine.
     @param     this    object pointer
     @return    if successful, ERESULT_SUCCESS.  Otherwise, an ERESULT_*
                error code.
     */
    ERESULT         TblE_Free (
        TBLE_DATA        *this
    )
    {
        //ERESULT         eRc;

        // Do initialization.
#ifdef NDEBUG
#else
        if (!TblE_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif

        if (this->pProgram) {
            mem_Free(this->pProgram);
            this->pProgram = NULL;
            this->pProgram = 0;
        }

        if (this->pMemory) {
            mem_Free(this->pMemory);
            this->pMemory = NULL;
            this->cMemory = 0;
        }

        if (this->pStack) {
            mem_Free(this->pStack);
            this->pStack = NULL;
            this->cStack = 0;
        }

        // Return to caller.
        return ERESULT_SUCCESS;
    }



    //---------------------------------------------------------------
    //                          R e s t a r t
    //---------------------------------------------------------------

    ERESULT         tble_Restart(
        TBLE_DATA        *this
    )
    {
        ERESULT         eRc;

        // Do initialization.
#ifdef NDEBUG
#else
        if( !TblE_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif

        this->pc = 256;
        eRc = TblE_Run(this);

        // Return to caller.
        return eRc;
    }


    //---------------------------------------------------------------
    //                          R u n
    //---------------------------------------------------------------

    ERESULT         TblE_Run(
        TBLE_DATA       *this
    )
    {

        // Do initialization.
#ifdef NDEBUG
#else
        if( !TblE_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif

        // Return to caller.
        return ERESULT_SUCCESS;
    }



    //---------------------------------------------------------------
    //                      S e t u p
    //---------------------------------------------------------------

    /*!
     Set up the initial machine.
     @param     this        object pointer
     @param     pgmSizeK    Program Size in K (1024 bytes) (0 == 32k)
     @param     memSizeK    Memory Size in K (1024 bytes) (0 == 32k)
     @param     stkSizeK    Stack Size in K (1024 bytes) (0 == 2k)
     @return    if successful, ERESULT_SUCCESS.  Otherwise, an ERESULT_*
                error code.
     */
    ERESULT         TblE_Setup (
        TBLE_DATA        *this,
        uint32_t        pgmSizeK,
        uint32_t        memSizeK,
        uint32_t        stkSizeK
    )
    {
        //ERESULT         eRc;

        // Do initialization.
#ifdef NDEBUG
#else
        if (!TblE_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif
        if (pgmSizeK == 0)
            pgmSizeK = 32;
        if (memSizeK == 0)
            memSizeK = 32;
        if (stkSizeK == 0)
            stkSizeK = 2;

        this->cProgram = (pgmSizeK * 1024);
        this->pProgram = mem_Calloc(1, this->cProgram);
        if (NULL == this->pProgram) {
            DEBUG_BREAK();
            return ERESULT_OUT_OF_MEMORY;
        }

        this->cMemory = (memSizeK * 1024);
        this->pMemory = mem_Calloc(1, this->cMemory);
        if (NULL == this->pMemory) {
            DEBUG_BREAK();
            return ERESULT_OUT_OF_MEMORY;
        }

        this->cStack = stkSizeK * 1024;
        this->pStack = mem_Calloc(this->cStack, sizeof(uint32_t));
        if (NULL == this->pStack) {
            DEBUG_BREAK();
            return ERESULT_OUT_OF_MEMORY;
        }

        this->pc = 256;

        // Return to caller.
        return ERESULT_SUCCESS;
    }



    //---------------------------------------------------------------
    //                       T o  S t r i n g
    //---------------------------------------------------------------
    
    /*!
     Create a string that describes this object and the objects within it.
     Example:
     @code 
        ASTR_DATA      *pDesc = TblE_ToDebugString(this,4);
     @endcode 
     @param     this    object pointer
     @param     indent  number of characters to indent every line of output, can be 0
     @return    If successful, an AStr object which must be released containing the
                description, otherwise OBJ_NIL.
     @warning  Remember to release the returned AStr object.
     */
    ASTR_DATA *     TblE_ToDebugString (
        TBLE_DATA      *this,
        int             indent
    )
    {
        ERESULT         eRc;
        ASTR_DATA       *pStr;
        //ASTR_DATA       *pWrkStr;
        const
        OBJ_INFO        *pInfo;
        //uint32_t        i;
        //uint32_t        j;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if (!TblE_Validate(this)) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
              
        pInfo = obj_getInfo(this);
        pStr = AStr_New();
        if (OBJ_NIL == pStr) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
        
        if (indent) {
            AStr_AppendCharRepeatA(pStr, indent, ' ');
        }
        eRc = AStr_AppendPrint(
                    pStr,
                    "{%p(%s) size=%d retain=%d\n",
                    this,
                    pInfo->pClassName,
                    TblE_getSize(this),
                    obj_getRetainCount(this)
            );

#ifdef  XYZZY        
        if (this->pData) {
            if (((OBJ_DATA *)(this->pData))->pVtbl->pToDebugString) {
                pWrkStr =   ((OBJ_DATA *)(this->pData))->pVtbl->pToDebugString(
                                                    this->pData,
                                                    indent+3
                            );
                AStr_Append(pStr, pWrkStr);
                obj_Release(pWrkStr);
            }
        }
#endif
        
        if (indent) {
            AStr_AppendCharRepeatA(pStr, indent, ' ');
        }
        eRc =   AStr_AppendPrint(
                    pStr,
                    " %p(%s)}\n", 
                    this, 
                    pInfo->pClassName
                );
        
        return pStr;
    }
    
    
    
    //---------------------------------------------------------------
    //                      V a l i d a t e
    //---------------------------------------------------------------

#ifdef NDEBUG
#else
    bool            TblE_Validate (
        TBLE_DATA      *this
    )
    {
 
        // WARNING: We have established that we have a valid pointer
        //          in 'this' yet.
       if (this) {
            if (obj_IsKindOf(this, OBJ_IDENT_TBLE))
                ;
            else {
                // 'this' is not our kind of data. We really don't
                // know what that it is at this point. 
                return false;
            }
        }
        else {
            // 'this' is NULL.
            return false;
        }
        // Now, we have validated that we have a valid pointer in
        // 'this'.


        if (!(obj_getSize(this) >= sizeof(TBLE_DATA))) {
            return false;
        }

        // Return to caller.
        return true;
    }
#endif


    
    //---------------------------------------------------------------
    //                          Z e r o
    //---------------------------------------------------------------

    ERESULT         TblE_Zero(
        TBLE_DATA       *this
    )
    {
        uint32_t        i;
        uint32_t        max;
        uint8_t         *pMem;

        // Do initialization.
#ifdef NDEBUG
#else
        if( !TblE_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif

        // Fill program memory with unknown opcode;
        max = this->cProgram;
        pMem = this->pProgram;
        for (i=0; i<max; ++i) {
            *pMem++ = TBLE_OPCODE_UNKNOWN;
        }

        // Fill data memory with 0's;
        max = this->cMemory;
        pMem = this->pMemory;
        for (i=0; i<max; ++i) {
            *pMem++ = 0;
        }

        // Zero all registers.
        for (i=0; i<128; i++) {
            this->regs[i] = 0;
        }

        this->pc = 0x100;

        // Return to caller.
        return ERESULT_SUCCESS;
    }




    
#ifdef	__cplusplus
}
#endif


