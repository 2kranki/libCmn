// vi:nu:et:sts=4 ts=4 sw=4

//****************************************************************
//                  8-bit Arithmetic Logic Unit (ALU8) Header
//****************************************************************
/*
 * Program
 *          8-bit Arithmetic Logic Unit (ALU8)
 * Purpose
 *          This object provides an Arithmetic Logic Unit (ALU)
 *          that can be used in simulators. It is based on the
 *          Intel 8080/8085 ALU, but does not exactly duplicate
 *          its functionality. It can be used for any 8-bit
 *          calculations including those for the Zilog Z80 which
 *          actually used a 4-bit ALU that was used 2 times in
 *          succession.
 *
 *          You could use two successive calls to this ALU to
 *          create a 16-bit ALU. You would have to handle the
 *          flags however.
 * Remarks
 *  1.      http://www.righto.com/2013/01/inside-alu-of-8085-microprocessor.html
 *          has a nice explanation of the Intel 8085 ALU.
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


#ifndef         ALU8_H
#define         ALU8_H


//#define   ALU8_IS_IMMUTABLE     1
//#define   ALU8_JSON_SUPPORT     1
//#define   ALU8_SINGLETON        1





#ifdef  __cplusplus
extern "C" {
#endif
    

    //****************************************************************
    //* * * * * * * * * * * *  Data Definitions  * * * * * * * * * * *
    //****************************************************************


    typedef struct ALU8_data_s  ALU8_DATA;            // Inherits from OBJ
    typedef struct ALU8_class_data_s ALU8_CLASS_DATA;   // Inherits from OBJ

    typedef struct ALU8_vtbl_s  {
        OBJ_IUNKNOWN    iVtbl;              // Inherited Vtbl.
        // Put other methods below this as pointers and add their
        // method names to the vtbl definition in ALU8_object.c.
        // Properties:
        // Methods:
        //bool        (*pIsEnabled)(ALU8_DATA *);
    } ALU8_VTBL;

    typedef struct ALU8_class_vtbl_s    {
        OBJ_IUNKNOWN    iVtbl;              // Inherited Vtbl.
        // Put other methods below this as pointers and add their
        // method names to the vtbl definition in ALU8_object.c.
        // Properties:
        // Methods:
        //bool        (*pIsEnabled)(ALU8_DATA *);
    } ALU8_CLASS_VTBL;


    //              Operation Codes
    // The given operation is performed using the input flags as needed
    // and the result if given back to pResult if present and/or pFlags
    // if present. No value is retained in the ALU.
    typedef enum ALU8_ops_e {
        ALU8_OP_UNKNOWN=0,
        ALU8_OP_ADD,                // pResult = op1 + op2 + carry(input)
        ALU8_OP_AND,                // pResult = op1 & op2
        ALU8_OP_COMPLEMENT,         // pResult = 2s Complement of op1
        ALU8_OP_DEC_ADJUST,         // pResult = Decimal Adjust of op1,
        //                          //          aux_carry(input), carry(input)
        ALU8_OP_NOT,                // pResult = 1s Complement of op1
        ALU8_OP_OR,                 // pResult = op1 | op2
        ALU8_OP_SHIFT_LEFT,         // pResult = op1 << 1, carry == overflow
        ALU8_OP_SHIFT_RIGHT,        // pResult = op1 >> 1, carry == underflow
        ALU8_OP_SUB,                // pResult = op1 - op2 - carry(input)
        ALU8_OP_XOR                 // pResult = op1 ^ op2
    } ALU8_OPS;


    //              ALU Flags
    // An operation always starts with all flags off. The
    // appropriate flags are set during the operation or
    // at its end.
    typedef enum ALU8_flags_e {
        ALU8_FLAG_NONE=0x00,
        ALU8_FLAG_SIGN=0x80,        // 1 = negative, 0 == positive
        ALU8_FLAG_ZERO=0x40,        // 1 == zero, 0 == non-zero amount
        ALU8_FLAG_UNUSED1=0x20,
        ALU8_FLAG_AUX_CARRY=0x10,   // Carry from bit 3 (used with BCD mostly)
        ALU8_FLAG_UNUSED2=0x08,
        ALU8_FLAG_PARITY=0x04,
        ALU8_FLAG_UNUSED3=0x02,
        ALU8_FLAG_CARRY=0x01
    } ALU8_FLAGS;




    /****************************************************************
    * * * * * * * * * * *  Routine Definitions  * * * * * * * * * * *
    ****************************************************************/


    //---------------------------------------------------------------
    //                      *** Class Methods ***
    //---------------------------------------------------------------

#ifdef  ALU8_SINGLETON
    ALU8_DATA *     ALU8_Shared (
        void
    );

    void            ALU8_SharedReset (
        void
    );
#endif


   /*!
     Allocate a new Object and partially initialize. Also, this sets an
     indicator that the object was alloc'd which is tested when the object is
     released.
     @return    pointer to ALU8 object if successful, otherwise OBJ_NIL.
     */
    ALU8_DATA *     ALU8_Alloc (
        void
    );
    
    
    OBJ_ID          ALU8_Class (
        void
    );
    
    
    ASTR_DATA *     ALU8_GenEvenParityTable (
        void
    );


    /*!
     Execute an ALU operation.
     @param     oper        operation to perform, see ALU8_OPS.
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
    ERESULT         ALU8_Exec (
        int             oper,
        uint8_t         op1,
        uint8_t         op2,
        uint8_t         flags,
        uint8_t         *pFlags,
        uint8_t         *pResult
    );


    ALU8_DATA *     ALU8_New (
        void
    );
    
    
#ifdef  ALU8_JSON_SUPPORT
    ALU8_DATA *     ALU8_NewFromJsonString (
        ASTR_DATA       *pString
    );

    ALU8_DATA *     ALU8_NewFromJsonStringA (
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

    ALU8_DATA *     ALU8_Init (
        ALU8_DATA       *this
    );


#ifdef  ALU8_JSON_SUPPORT
    /*!
     Create a string that describes this object and the objects within it in
     HJSON formt. (See hjson object for details.)
     Example:
     @code
     ASTR_DATA      *pDesc = ALU8_ToJson(this);
     @endcode
     @param     this    object pointer
     @return    If successful, an AStr object which must be released containing the
                JSON text, otherwise OBJ_NIL.
     @warning   Remember to release the returned AStr object.
     */
    ASTR_DATA *     ALU8_ToJson (
        ALU8_DATA       *this
    );
#endif


    /*!
     Create a string that describes this object and the objects within it.
     Example:
     @code 
        ASTR_DATA      *pDesc = ALU8_ToDebugString(this,4);
     @endcode 
     @param     this    object pointer
     @param     indent  number of characters to indent every line of output, can be 0
     @return    If successful, an AStr object which must be released containing the
                description, otherwise OBJ_NIL.
     @warning   Remember to release the returned AStr object.
     */
    ASTR_DATA *     ALU8_ToDebugString (
        ALU8_DATA       *this,
        int             indent
    );
    
    

    
#ifdef  __cplusplus
}
#endif

#endif  /* ALU8_H */

