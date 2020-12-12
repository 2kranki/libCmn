// vi:nu:et:sts=4 ts=4 sw=4

//****************************************************************
//           32-bit Arithmetic Logic Unit (ALU32) Header
//****************************************************************
/*
 * Program
 *          32-bit Arithmetic Logic Unit (ALU32)
 * Purpose
 *          This object provides a 32-bit Arithmetic Logic Unit
 *          for use in computer simulation.
 *
 *          The accumulator size for this ALU is 32 bits. Bit 0
 *          is the highest order bit and bit 31 is the lowest
 *          order bit. Normally the 32-bit value is considered
 *          unsigned. If it is signed, then the sign bit is bit
 *          0.
 *
 * Remarks
 *  1.      None
 *
 * History
 *  12/06/2020 Generated
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





#include        <cmn_defs.h>
#include        <AStr.h>


#ifndef         ALU32_H
#define         ALU32_H


//#define   ALU32_IS_IMMUTABLE     1
//#define   ALU32_JSON_SUPPORT     1
//#define   ALU32_SINGLETON        1





#ifdef  __cplusplus
extern "C" {
#endif
    

    //****************************************************************
    //* * * * * * * * * * * *  Data Definitions  * * * * * * * * * * *
    //****************************************************************


    typedef struct ALU32_data_s  ALU32_DATA;            // Inherits from OBJ
    typedef struct ALU32_class_data_s ALU32_CLASS_DATA;   // Inherits from OBJ

    typedef struct ALU32_vtbl_s  {
        OBJ_IUNKNOWN    iVtbl;              // Inherited Vtbl.
        // Put other methods below this as pointers and add their
        // method names to the vtbl definition in ALU32_object.c.
        // Properties:
        // Methods:
        //bool        (*pIsEnabled)(ALU32_DATA *);
    } ALU32_VTBL;

    typedef struct ALU32_class_vtbl_s    {
        OBJ_IUNKNOWN    iVtbl;              // Inherited Vtbl.
        // Put other methods below this as pointers and add their
        // method names to the vtbl definition in ALU32_object.c.
        // Properties:
        // Methods:
        //bool        (*pIsEnabled)(ALU32_DATA *);
    } ALU32_CLASS_VTBL;


    //              Operation Codes
    // The given operation is performed using the input flags as needed
    // and the result if given back to pResult if present and/or pFlags
    // if present. No value is retained in the ALU.
    typedef enum ALU32_ops_e {
        ALU32_OP_UNKNOWN=0,
        ALU32_OP_ADD,               // pResult = op1 + op2
        ALU32_OP_AND,               // pResult = op1 & op2
        ALU32_OP_COMPLEMENT,        // pResult = 2s Complement of op1
        ALU32_OP_NOT,               // pResult = 1s Complement of op1
        ALU32_OP_OR,                // pResult = op1 | op2
        ALU32_OP_SHIFT_LEFT,        // pResult = (op1[1..31] << 1) + carry(in),
        //                          // carry(out) <- op1[0] == overflow
        ALU32_OP_SHIFT_RIGHT,       // pResult = carry(in) + (op1[0..30] >> 1),
        //                          // carry(out) <- op1[31] == underflow
        ALU32_OP_SHIFTA_LEFT,       // (arith) pResult = op1[0] | (op1[1..31] << 1) + 0,
        //                          // carry(out) <- !(op1[0] == op1[1])
        ALU32_OP_SHIFTA_RIGHT,      // (arith) pResult = op1[0] | (op1[0..30] >> 1),
        //                          // carry(out) <- op1[31] == underflow
        ALU32_OP_SHIFTL_LEFT,       // pResult = (op1[1..31] << 1) + 0,
        //                          // carry(out) <- op1[0] == overflow
        ALU32_OP_SHIFTL_RIGHT,      // pResult = 0 + (op1[0..30] >> 1),
        //                          // carry(out) <- op1[31] == underflow
        ALU32_OP_SHIFTR_LEFT,       // pResult = (op1[1..31] << 1) + op1[0],
        //                          // carry(out) <- op1[0] == overflow
        ALU32_OP_SHIFTR_RIGHT,      // pResult = op1[31] + (op1[0..30] >> 1),
        //                          // carry(out) <- op1[31] == underflow
        ALU32_OP_SUB,               // pResult = op1 - op2
        ALU32_OP_XOR                // pResult = op1 ^ op2
    } ALU32_OPS;


    //              ALU Flags
    // An operation always starts with all flags off. The
    // appropriate flags are set during the operation or
    // at its end.
    typedef enum ALU32_flags_e {
        ALU32_FLAG_NONE=0x00,
        ALU32_FLAG_SIGN=0x80,
        ALU32_FLAG_ZERO=0x40,
        ALU32_FLAG_PARITY=0x20,
        ALU32_FLAG_CARRY=0x10
    } ALU32_FLAGS;





    /****************************************************************
    * * * * * * * * * * *  Routine Definitions  * * * * * * * * * * *
    ****************************************************************/


    //---------------------------------------------------------------
    //                      *** Class Methods ***
    //---------------------------------------------------------------

#ifdef  ALU32_SINGLETON
    ALU32_DATA *     ALU32_Shared (
        void
    );

    void            ALU32_SharedReset (
        void
    );
#endif


   /*!
     Allocate a new Object and partially initialize. Also, this sets an
     indicator that the object was alloc'd which is tested when the object is
     released.
     @return    pointer to ALU32 object if successful, otherwise OBJ_NIL.
     */
    ALU32_DATA *     ALU32_Alloc (
        void
    );
    
    
    OBJ_ID          ALU32_Class (
        void
    );
    
    
    int             ALU32_even_parity (
        uint32_t        x
    );


    /*!
     Execute an ALU operation.
     @param     oper        operation to perform, see E8085ALU_OPS.
     @param     flags       The flags to be used for input especially
                            the carry flag and the aux carray flag.
     @param     op1         operand 1
     @param     op2         operand 2
     @param     pResult     If non-null, store result at this location.
     @param     pFlags      if non-null, store the new flags at this
                            location.
     @return    if successful, ERESULT_SUCCESS.  Otherwise, an ERESULT_*
                error code.
     */
    ERESULT         ALU32_Exec (
        int             oper,
        uint32_t        op1,
        uint32_t        op2,
        uint8_t         flags,
        uint8_t         *pFlags,
        uint32_t        *pResult
    );


    ALU32_DATA *     ALU32_New (
        void
    );
    
    
#ifdef  ALU32_JSON_SUPPORT
    ALU32_DATA *   ALU32_NewFromJsonString (
        ASTR_DATA       *pString
    );

    ALU32_DATA *   ALU32_NewFromJsonStringA (
        const
        char            *pStringA
    );
#endif



    //---------------------------------------------------------------
    //                      *** Properties ***
    //---------------------------------------------------------------



    
    //---------------------------------------------------------------
    //                      *** Methods ***
    //---------------------------------------------------------------

    ERESULT     ALU32_Disable (
        ALU32_DATA       *this
    );


    ERESULT     ALU32_Enable (
        ALU32_DATA       *this
    );

   
    ALU32_DATA *   ALU32_Init (
        ALU32_DATA     *this
    );


    ERESULT     ALU32_IsEnabled (
        ALU32_DATA       *this
    );
    
 
#ifdef  ALU32_JSON_SUPPORT
    /*!
     Create a string that describes this object and the objects within it in
     HJSON formt. (See hjson object for details.)
     Example:
     @code
     ASTR_DATA      *pDesc = ALU32_ToJson(this);
     @endcode
     @param     this    object pointer
     @return    If successful, an AStr object which must be released containing the
                JSON text, otherwise OBJ_NIL.
     @warning   Remember to release the returned AStr object.
     */
    ASTR_DATA *     ALU32_ToJson (
        ALU32_DATA   *this
    );
#endif


    /*!
     Create a string that describes this object and the objects within it.
     Example:
     @code 
        ASTR_DATA      *pDesc = ALU32_ToDebugString(this,4);
     @endcode 
     @param     this    object pointer
     @param     indent  number of characters to indent every line of output, can be 0
     @return    If successful, an AStr object which must be released containing the
                description, otherwise OBJ_NIL.
     @warning   Remember to release the returned AStr object.
     */
    ASTR_DATA *     ALU32_ToDebugString (
        ALU32_DATA     *this,
        int             indent
    );
    
    

    
#ifdef  __cplusplus
}
#endif

#endif  /* ALU32_H */

