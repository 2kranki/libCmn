// vi:nu:et:sts=4 ts=4 sw=4

//****************************************************************
//          TBL Machine Emulator (TblE) Header
//****************************************************************
/*
 * Program
 *			TBL Machine Emulator (TblE)
 * Purpose
 *          This object provides a TBL execution machine.  TBL was
 *          defined in "Engineering a Compiler" is an version of the
 *          developed by Robert Freiburghouse. It provides a versatile
 *          virtual machine that can be tuned to finite state machines,
 *          compilers, semantic analyzers, code generators, etc.
 *          The base virtual machine has a few simple opcodes
 *          (called Actions).  The opcodes can be dynamically updated
 *          to add additional opcodes as needed for specific tasks.
 *
 *          There is a common flag that can be set true or false as
 *          needed, then tested with conditional branches such as
 *          if and if_not.
 * Remarks
 *  1.      The virtual machine has at most 256 opcodes. The first 64
 *          are defined or reserved. The remaining opcodes are assignable
 *          depending on the task needed.
 *  2.      Program memory defaults to  32k and data memeory defaults
 *          to a separate 32k.  Stack size defaults to 2k.  These are
 *          are changable at object creation time.
 *  3.      There are 128 registers accessed by 128..255. A value of 0..127
 *          is simply returned as a constant.
 *  4.      The first 256 bytes of program memory are designated Low
 *          Program Memory and are reserved for specific purposes such
 *          as interrupts. The first 1024 bytes of data memory are
 *          designated Low Data Memory and are reserved for specific
 *          purposes.
 *  5.      If an address is given in the "end" statement, then execution
 *          begins there. Otherwise, it begins at 256.
 *
 * History
 *  11/17/2017 Generated
 *	02/22/2020 Regenerated
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





#include        <Tbl_defs.h>
#include        <AStr.h>


#ifndef         TBLE_H
#define         TBLE_H


//#define   TBLE_IS_IMMUTABLE     1
#define   TBLE_JSON_SUPPORT     1
//#define   TBLE_SINGLETON        1





#ifdef	__cplusplus
extern "C" {
#endif
    

    //****************************************************************
    //* * * * * * * * * * * *  Data Definitions  * * * * * * * * * * *
    //****************************************************************


    typedef struct TblE_data_s	TBLE_DATA;            // Inherits from OBJ
    typedef struct TblE_class_data_s TBLE_CLASS_DATA;   // Inherits from OBJ

    typedef struct TblE_vtbl_s	{
        OBJ_IUNKNOWN    iVtbl;              // Inherited Vtbl.
        // Put other methods below this as pointers and add their
        // method names to the vtbl definition in TblE_object.c.
        // Properties:
        // Methods:
        //bool        (*pIsEnabled)(TBLE_DATA *);
    } TBLE_VTBL;

    typedef struct TblE_class_vtbl_s	{
        OBJ_IUNKNOWN    iVtbl;              // Inherited Vtbl.
        // Put other methods below this as pointers and add their
        // method names to the vtbl definition in TblE_object.c.
        // Properties:
        // Methods:
        //bool        (*pIsEnabled)(TBLE_DATA *);
    } TBLE_CLASS_VTBL;


    //              Opcode Routine Definition
    // Opcodes will be called 3 parameters. 0 will be passed for any
    // parameter that is not present.
    typedef
    bool        (*P_TBLE_EXEC)(TBLE_DATA *, int32_t, int32_t);


    typedef struct TblE_Opcode_Entry_s {
        uint8_t         opc;
        const
        char            *pName;
        P_TBLE_EXEC     pExec;
        uint8_t         opcode;
        //uint8_t         len;          // Opcode Length in bytes (determined by
        //                              // Argument Types
        uint8_t         arg1Type;       // optional (See TBLE_ARGTYPE)
        uint8_t         arg2Type;       // optional (See TBLE_ARGTYPE)
        uint8_t         arg3Type;       // optional (See TBLE_ARGTYPE)
    } TBLE_OPCODE_ENTRY;


    typedef enum TblE_argType_e {
        TBLE_ARGTYPE_UNKNOWN=0,     // Unknown or Not Present
        TBLE_ARGTYPE_CON1,          // Unsigned 1-byte Constant | Register Index
        // Constant (unsigned) must be < 128
        // Register Index (unsigned) must be > 127 and < 256
        TBLE_ARGTYPE_REG1,          // 1-byte Register Index
        // 0 .. 127 will cause exception
        // Register Index (unsigned) must be > 127 and < 256
        TBLE_ARGTYPE_INT2,          // Signed 2-byte Integer Constant
        TBLE_ARGTYPE_INT4,          // Signed 4-byte Integer Constant
        TBLE_ARGTYPE_PGMADR,        // Unsigned 2-byte Program Address
        TBLE_ARGTYPE_MEMADR         // Unsigned 2-byte Memory Address
    } TBLE_ARGTYPE;


    // The first 64 actions of the 256 total are reserved for base machine
    // and are always present.
    //  OPCODE                      PARM1           PARM2           PARM3
    typedef enum TblE_opcodes_e {
        // *** Default Actions ***
        TBLE_OPCODE_UNKNOWN=0,
        // Add the given constant or register to the accumulator
        TBLE_OPCODE_A,          //  conReg
        // Unconditional Branch
        TBLE_OPCODE_B,          //  program_address
        // Branch if accumulator is not zero
        TBLE_OPCODE_BNZ,        //  program_address
        // Branch if accumulator is zero
        TBLE_OPCODE_BZ,         //  program_address
        // Call a function.
        TBLE_OPCODE_CALL,       //  program_address
        // Complement acculator.
        TBLE_OPCODE_CMA,
        // Decrement the accumulator.
        TBLE_OPCODE_DEC,
        // Compare two conReg's for equality if true set accumulator to 1
        // otherwise set accumulator to 0
        TBLE_OPCODE_EQ,         //  arg_index/value arg_index/value
        TBLE_OPCODE_EXIT,
        TBLE_OPCODE_HALT,
        // Increment the accumulator.
        TBLE_OPCODE_INC,
        // Load a register into the accumulator.
        TBLE_OPCODE_LDA,        //  conReg
        // Load an unsigned 16-bit value into a register.
        TBLE_OPCODE_LDC2,       //  Register    integer
        // Load a signed 32-bit value into a register.
        TBLE_OPCODE_LDC4,       //  Reg         integer
        // Load a 8-bit value into a register.
        TBLE_OPCODE_LDM8,       //  Reg         memory_address
        // Load a 16-bit value into a register.
        TBLE_OPCODE_LDM16,      //  conReg      memory_address
        // Load a 32-bit value into a register.
        TBLE_OPCODE_LDM32,      //  conReg      memory_address
        // Compare two conReg's for inequality if true set accumulator to 1
        // otherwise set accumulator to 0
        TBLE_OPCODE_NE,         //  arg_index/value arg_index/value
        TBLE_OPCODE_NOP,
        // If accummulator is non-zero, put zero in it. Otherwise,
        // put 1 in it.
        TBLE_OPCODE_NOT,
        // Set acculator to one;
        TBLE_OPCODE_ONE,
        // Pop the top of the stack into a register.
        TBLE_OPCODE_POPR,       //  Reg
        // Push a register onto the stack.
        TBLE_OPCODE_PUSHR,      //  Reg
        // Return from a subroutine.
        TBLE_OPCODE_RET,
        // Subtract the given constant or register from the accumulator
        TBLE_OPCODE_S,          //  conReg
        // Store the accumulator in a register.
        TBLE_OPCODE_STA,        //  conReg
        // Put the accumulator to stderr.
        TBLE_OPCODE_STDERR,     //  conReg
        // Get a character fron stdin.
        TBLE_OPCODE_STDIN,      //  conReg
        // Put the accumulator to stderr.
        TBLE_OPCODE_STDOUT,     //  conReg
        // Store a register into memory as a 8-bit value.
        TBLE_OPCODE_STM8,       //  conReg      integer
        // Store a register into memory as a 16-bit value.
        TBLE_OPCODE_STM16,      //  conReg      integer
        // Store a register into memory as a 32-bit value.
        TBLE_OPCODE_STM32,      //  conReg      integer
        TBLE_OPCODE_SVC,        //  conReg      conReg
        // Set acculator to zero;
        TBLE_OPCODE_ZERO,
        // *** User Actions ***
        TBLE_OPCODE_FIRST_USER=64
    } TBLE_OPCODES;




    /****************************************************************
    * * * * * * * * * * *  Routine Definitions	* * * * * * * * * * *
    ****************************************************************/


    //---------------------------------------------------------------
    //                      *** Class Methods ***
    //---------------------------------------------------------------

#ifdef  TBLE_SINGLETON
    TBLE_DATA *     TblE_Shared (
        void
    );

    void            TblE_SharedReset (
        void
    );
#endif


   /*!
     Allocate a new Object and partially initialize. Also, this sets an
     indicator that the object was alloc'd which is tested when the object is
     released.
     @return    pointer to TblE object if successful, otherwise OBJ_NIL.
     */
    TBLE_DATA *     TblE_Alloc (
        void
    );
    
    
    OBJ_ID          TblE_Class (
        void
    );
    
    
    TBLE_DATA *     TblE_New (
        void
    );
    
    
    TBLE_DATA *     TblE_NewWithSizes (
        uint32_t        pgmSizeK,   // Program Size in K (1024 bytes) (0 == 32k)
        uint32_t        memSizeK,   // Memory Size in K (1024 bytes) (0 == 32k)
        uint32_t        stkSizeK    // Stack Size in K (1024 bytes) (0 == 2k)
    );


#ifdef  TBLE_JSON_SUPPORT
    TBLE_DATA *   TblE_NewFromJsonString (
        ASTR_DATA       *pString
    );

    TBLE_DATA *   TblE_NewFromJsonStringA (
        const
        char            *pStringA
    );
#endif



    //---------------------------------------------------------------
    //                      *** Properties ***
    //---------------------------------------------------------------

    /*! Property: Accumulator
     */
    int32_t         TblE_getAccum (
        TBLE_DATA     *this
    );

    bool            TblE_setAccum (
        TBLE_DATA       *this,
        int32_t         value
    );

    
    /*! Property: Program Counter
     */
    uint16_t        TblE_getPC (
        TBLE_DATA     *this
    );

    bool            TblE_setPC (
        TBLE_DATA       *this,
        uint16_t        value
    );




    //---------------------------------------------------------------
    //                      *** Methods ***
    //---------------------------------------------------------------

    /*! Add an opcode.
     @param     this    object pointer
     @param     pEntry  opcode table entry pointer
     @return    ERESULT_SUCCESS or an ERESULT_* error code
     */
    ERESULT         TblE_AddOpcode(
        TBLE_DATA       *this,
        TBLE_OPCODE_ENTRY
                        *pEntry
    );


    ERESULT         TblE_Disable (
        TBLE_DATA		*this
    );


    ERESULT         TblE_Enable (
        TBLE_DATA		*this
    );

   
    ERESULT         TblE_Exec (
        TBLE_DATA       *this
    );


    TBLE_DATA *     TblE_Init (
        TBLE_DATA       *this
    );


    /*!
     Get a machine memory value at the given address.
     @param     this    object pointer
     @param     addr    memory address
     @return    If addr is valid, return the value at the address.
                Otherwise, return zero.
     */
    int32_t         TblE_MemGet8 (
        TBLE_DATA       *this,
        uint32_t        addr
    );
    
 
    /*!
     Put the given value at machine memory address given if possible.
     @param     this    object pointer
     @param     addr    memory address
     @param     value   value to store
     */
    void            TblE_MemPut8 (
        TBLE_DATA       *this,
        uint32_t        addr,
        int32_t         value
    );


    /*!
     Get a machine memory value at the given address.
     @param     this    object pointer
     @param     addr    Register Index Number
     @return    If addr is valid, return the value at the address.
                Otherwise, return zero.
     */
    int32_t         TblE_MemGet16 (
        TBLE_DATA       *this,
        uint32_t        addr
    );


    /*!
     Put the given value at machine memory address given if possible.
     @param     this    object pointer
     @param     addr    memory address
     @param     value   value to store
     */
    void            TblE_MemPut16 (
        TBLE_DATA       *this,
        uint32_t        addr,
        int32_t         value
    );


    /*!
     Get a machine memory value at the given address.
     @param     this    object pointer
     @param     addr    Register Index Number
     @return    If addr is valid, return the value at the address.
                Otherwise, return zero.
     */
    int32_t         TblE_MemGet32 (
        TBLE_DATA       *this,
        uint32_t        addr
    );


    /*!
     Put the given value at machine memory address given if possible.
     @param     this    object pointer
     @param     addr    memory address
     @param     value   value to store
     */
    void            TblE_MemPut32 (
        TBLE_DATA       *this,
        uint32_t        addr,
        int32_t         value
    );


    /*!
     Get a machine register value.
     @param     this        object pointer
     @param     index       Register Index Number
     @return         If index < 128, simply return the index.
                    Otherwise, return the register value associated with the index.
     */
    int32_t         TblE_RegGet (
        TBLE_DATA       *this,
        uint16_t        index
    );


    void            TblE_RegPut (
        TBLE_DATA       *this,
        uint16_t        index,
        int32_t         value
    );


    /*!
     Get a machine register value.
     @param     this        object pointer
     @param     index       Register Index Number
     @return         If index < 128, simply return the index.
                    Otherwise, return the register value associated with the index.
     */
    ERESULT         TblE_Restart(
        TBLE_DATA       *this
    );


    /*!
     Run the machine until an 'exit' instruction is executed.
     @param     this        object pointer
     @param     index       Register Index Number
     @return         If index < 128, simply return the index.
                    Otherwise, return the register value associated with the index.
     */
    ERESULT         TblE_Run(
        TBLE_DATA       *this
    );


    /*!
     Set up the initial machine.
     @param     this        object pointer
     @param     pgmSizeK    Program Size in K (1024 bytes) (0 == 62k)
     @param     memSizeK    Memory Size in K (1024 bytes) (0 == 62k)
     @param     stkSizeK    Stack Size in K (1024 bytes) (0 == 2k)
     @return    if successful, ERESULT_SUCCESS.  Otherwise, an ERESULT_*
                error code.
     */
    ERESULT         TblE_Setup (
        TBLE_DATA        *this,
        uint32_t        pgmSizeK,   // Program Size in K (1024 bytes) (0 == 32k)
        uint32_t        memSizeK,   // Memory Size in K (1024 bytes) (0 == 32k)
        uint32_t        stkSizeK    // Stack Size in K (1024 bytes) (0 == 2k)
    );


#ifdef  TBLE_JSON_SUPPORT
    /*!
     Create a string that describes this object and the objects within it in
     HJSON formt. (See hjson object for details.)
     Example:
     @code
     ASTR_DATA      *pDesc = TblE_ToJson(this);
     @endcode
     @param     this    object pointer
     @return    If successful, an AStr object which must be released containing the
                JSON text, otherwise OBJ_NIL and LastError set to an appropriate
                ERESULT_* error code.
     @warning   Remember to release the returned AStr object.
     */
    ASTR_DATA *     TblE_ToJson (
        TBLE_DATA   *this
    );
#endif


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
     @warning   Remember to release the returned AStr object.
     */
    ASTR_DATA *    TblE_ToDebugString (
        TBLE_DATA     *this,
        int             indent
    );
    
    

    
#ifdef	__cplusplus
}
#endif

#endif	/* TBLE_H */

