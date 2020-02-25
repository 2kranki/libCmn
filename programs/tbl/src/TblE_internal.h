// vi:nu:et:sts=4 ts=4 sw=4
/* 
 * File:   TblE_internal.h
 *	Generated 02/22/2020 22:19:59
 *
 * Notes:
 *
 *      The original machine was a byte addressable program memory, a
 *      512 32-bit word data memory and a 1000 32-bit word stack. Initial
 *      input was simply an array of integers (0..255) and the program
 *      counter starting at 0. The idea for this was to be able to fit
 *      the machine in very small computers.
 *
 *      I have decided to go with a byte addressable program and data
 *      memory, a growable stack, 128 32-bit registers.  The memory
 *      will be read/write.  I also am including an I/O system similar
 *      in concept to what William Waite included in his macro systems,
 *      simcmp and stage2.
 *
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




#include        <TblE.h>
#include        <JsonIn.h>


#ifndef TBLE_INTERNAL_H
#define	TBLE_INTERNAL_H



#define     PROPERTY_STR_OWNED 1



#ifdef	__cplusplus
extern "C" {
#endif




    //---------------------------------------------------------------
    //                  Object Data Description
    //---------------------------------------------------------------

#pragma pack(push, 1)
struct TblE_data_s	{
    /* Warning - OBJ_DATA must be first in this object!
     */
    OBJ_DATA        super;
    OBJ_IUNKNOWN    *pSuperVtbl;    // Needed for Inheritance

    // Common Data
    uint16_t        pc;
    uint16_t        rsvd16_1;
    uint16_t        cProgram;
    uint16_t        programMax;
    uint8_t         *pProgram;

    uint16_t        cMemory;
    uint16_t        memoryMax;
    uint8_t         *pMemory;

    int32_t         regs[128];

    uint32_t        cStack;
    uint32_t        *pStack;
    uint32_t        stackPointer;
    uint32_t        stackPointerMax;

    uint8_t         fTest;              // Used to test for true/false and re/set
    //                                  // by certain actions
    uint8_t         fSingleStep;        // If true, execute one opcode and stop
    uint8_t         rsvd8_1;
    uint8_t         rsvd8_2;
    int32_t         accumulator;
    TBLE_OPCODE_ENTRY
                    opcodes[256];
    uint32_t        actionPointer;

    // Interrupts
    OBJ_ID          pInterruptObj;
    bool            (*pInvalidMemAddr)(OBJ_ID, uint16_t pgmAddr, int32_t addr);
    bool            (*pInvalidPgmAddr)(OBJ_ID, uint16_t pgmAddr, int32_t addr);
    bool            (*pInvalidRegAddr)(OBJ_ID, uint16_t pgmAddr, int32_t reg);

};
#pragma pack(pop)

    extern
    struct TblE_class_data_s  TblE_ClassObj;

    extern
    const
    TBLE_VTBL         TblE_Vtbl;



    //---------------------------------------------------------------
    //              Class Object Method Forward Definitions
    //---------------------------------------------------------------

#ifdef  TBLE_SINGLETON
    TBLE_DATA *     TblE_getSingleton (
        void
    );

    bool            TblE_setSingleton (
     TBLE_DATA       *pValue
);
#endif



    //---------------------------------------------------------------
    //              Internal Method Forward Definitions
    //---------------------------------------------------------------

    OBJ_IUNKNOWN *  TblE_getSuperVtbl (
        TBLE_DATA     *this
    );


    ERESULT         TblE_Assign (
        TBLE_DATA    *this,
        TBLE_DATA    *pOther
    );


    TBLE_DATA *       TblE_Copy (
        TBLE_DATA     *this
    );


    void            TblE_Dealloc (
        OBJ_ID          objId
    );


    /*!
     Free the areas gotten for the machine.
     @param     this    object pointer
     @return    if successful, ERESULT_SUCCESS.  Otherwise, an ERESULT_*
                error code.
     */
    ERESULT         TblE_Free (
        TBLE_DATA        *this
    );


    int32_t         TblE_MemSet (
        TBLE_DATA       *this,
        uint32_t        index,
        uint32_t        len,
        uint8_t         value
    );


    int32_t         TblE_OperandGet (
        TBLE_DATA       *this,
        uint8_t         type,
        uint32_t        addr,
        uint16_t        *pLen       // Returned Operand Length
    );


#ifdef  TBLE_JSON_SUPPORT
    /*!
     Parse the new object from an established parser.
     @param pParser an established jsonIn Parser Object
     @return    a new object if successful, otherwise, OBJ_NIL
     @warning   Returned object must be released.
     */
    TBLE_DATA *       TblE_ParseJsonObject (
        JSONIN_DATA     *pParser
    );


    /*!
     Parse the object from an established parser. This helps facilitate
     parsing the fields from an inheriting object.
     @param pParser     an established jsonIn Parser Object
     @param pObject     an Object to be filled in with the
                        parsed fields.
     @return    If successful, ERESULT_SUCCESS. Otherwise, an ERESULT_*
                error code.
     */
    ERESULT         TblE_ParseJsonFields (
        JSONIN_DATA     *pParser,
        TBLE_DATA       *pObject
    );
#endif


    void *          TblE_QueryInfo (
        OBJ_ID          objId,
        uint32_t        type,
        void            *pData
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
        TBLE_DATA      *this
    );


    /*!
     Append the json representation of the object's fields to the given
     string. This helps facilitate parsing the fields from an inheriting 
     object.
     @param this        Object Pointer
     @param pStr        String Pointer to be appended to.
     @return    If successful, ERESULT_SUCCESS. Otherwise, an ERESULT_*
                error code.
     */
    ERESULT         TblE_ToJsonFields (
        TBLE_DATA     *this,
        ASTR_DATA       *pStr
    );
#endif




#ifdef NDEBUG
#else
    bool			TblE_Validate (
        TBLE_DATA       *this
    );
#endif



#ifdef	__cplusplus
}
#endif

#endif	/* TBLE_INTERNAL_H */

