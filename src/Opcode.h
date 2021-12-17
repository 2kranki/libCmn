// vi:nu:et:sts=4 ts=4 sw=4

//****************************************************************
//          Universal Opcode Table Entry (Opcode) Header
//****************************************************************
/*
 * Program
 *			Universal Opcode Table Entry (Opcode)
 * Purpose
 *			This object provides a Universal Opcode Table Entry
 *          can be used in machine emulators, assemblers,
 *          disassemblers, etc.
 *
 *          Generally, you would generate the specific table from
 *          this one for the appropriate application.
 * Remarks
 *	1.      None
 *
 * History
 *	02/27/2020 Generated
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
#include        <Node.h>


#ifndef         OPCODE_H
#define         OPCODE_H


//#define   OPCODE_IS_IMMUTABLE     1
#define   OPCODE_JSON_SUPPORT     1
//#define   OPCODE_SINGLETON        1





#ifdef	__cplusplus
extern "C" {
#endif
    

    //****************************************************************
    //* * * * * * * * * * * *  Data Definitions  * * * * * * * * * * *
    //****************************************************************


    typedef struct Opcode_data_s	OPCODE_DATA;            // Inherits from OBJ
    typedef struct Opcode_class_data_s OPCODE_CLASS_DATA;   // Inherits from OBJ

    typedef struct Opcode_vtbl_s	{
        OBJ_IUNKNOWN    iVtbl;              // Inherited Vtbl.
        // Put other methods below this as pointers and add their
        // method names to the vtbl definition in Opcode_object.c.
        // Properties:
        // Methods:
        //bool        (*pIsEnabled)(OPCODE_DATA *);
    } OPCODE_VTBL;

    typedef struct Opcode_class_vtbl_s	{
        OBJ_IUNKNOWN    iVtbl;              // Inherited Vtbl.
        // Put other methods below this as pointers and add their
        // method names to the vtbl definition in Opcode_object.c.
        // Properties:
        // Methods:
        //bool        (*pIsEnabled)(OPCODE_DATA *);
    } OPCODE_CLASS_VTBL;


    // Opcode Table Entry
    // Note:    No pointers are allowed in this structure. Also, this
    //          structure size must be a multiple of 4.
    typedef struct    Opcode_Entry_s {
#define OPCODE_ENTRY_NAME_MAX 12             // Name Length w/o trailing NUL
        const
        char            NameA[OPCODE_ENTRY_NAME_MAX+1];
#define OPCODE_ENTRY_DIS_MAX 16              // Disassembly String Length w/ trailing NUL
        const
        char            DisA[OPCODE_ENTRY_DIS_MAX];
        uint8_t         iLen;               // Full Instruction Length including operands
        uint8_t         cCode;              // Operation Code Length
#define OPCODE_ENTRY_CCODE_MAX 4            // number of bytes in opcode and mask
        uint8_t         iCode[OPCODE_ENTRY_CCODE_MAX]; // Operation Code
        uint8_t         iMask[OPCODE_ENTRY_CCODE_MAX]; // Operation Code Mask
        /*
         To detect an operation code, you must retrieve the number of bytes
         from memory given by cCode, and it with the mask and then compare
         it with the actual operation code.
         */
        int16_t         iType;              //
        uint8_t         iClass;
        uint8_t         cCondCodes;         // Number of Condition Codes
#define OPCODE_ENTRY_CCONDCODE_MAX 8        // Maximum number of condition codes
#define OPCODE_ENTRY_SZCONDCODE_MAX 11      // Condition Code Length w/ trailing NUL
        const
        char            szCondCodes[OPCODE_ENTRY_CCONDCODE_MAX][OPCODE_ENTRY_SZCONDCODE_MAX];
        uint16_t        iCondCodes;
        uint16_t        iFeatures;
#define OPCODE_ENTRY_IFEATURES_MAX 16       // Number of Features allowed (1 per bit)
        uint32_t        iInterrupts;
#define OPCODE_ENTRY_IINTERRUPTS_MAX 32     // Number of Interrupts allowed (1 per bit)
        uint32_t        unique;             // A unique number used as an index by other
        //                                  // programs
        uint16_t        flag1;              // To be used as needed
        uint16_t        flag2;              // To be used as needed
    }   OPCODE_ENTRY;



    /****************************************************************
    * * * * * * * * * * *  Routine Definitions	* * * * * * * * * * *
    ****************************************************************/


    //---------------------------------------------------------------
    //                      *** Class Methods ***
    //---------------------------------------------------------------

#ifdef  OPCODE_SINGLETON
    OPCODE_DATA *   Opcode_Shared (
        void
    );

    void            Opcode_SharedReset (
        void
    );
#endif


   /*!
     Allocate a new Object and partially initialize. Also, this sets an
     indicator that the object was alloc'd which is tested when the object is
     released.
     @return    pointer to Opcode object if successful, otherwise OBJ_NIL.
     */
    OPCODE_DATA *   Opcode_Alloc (
        void
    );
    
    
    OBJ_ID          Opcode_Class (
        void
    );
    
    
    OPCODE_DATA *   Opcode_New (
        void
    );
    
    
    OPCODE_DATA *   Opcode_NewA (
        const
        char            *pNameA
    );


    OPCODE_DATA *   Opcode_NewEntry (
        OPCODE_ENTRY    *pEntry
    );


#ifdef  OPCODE_JSON_SUPPORT
    OPCODE_DATA *   Opcode_NewFromJsonString (
        ASTR_DATA       *pString
    );

    OPCODE_DATA *   Opcode_NewFromJsonStringA (
        const
        char            *pStringA
    );
#endif



    //---------------------------------------------------------------
    //                      *** Properties ***
    //---------------------------------------------------------------

    /*! Property: Opcode Class
        To be used as needed.
     */
    uint8_t         Opcode_getClass (
        OPCODE_DATA     *this
    );

    bool            Opcode_setClass (
        OPCODE_DATA     *this,
        uint8_t         value
    );


    /*! Property: Opcode Disassembly String
     */
    const
    char *          Opcode_getDisA (
        OPCODE_DATA     *this
    );


    /*! Property: Raw Opcode Entry
     */
    OPCODE_ENTRY *  Opcode_getEntry (
        OPCODE_DATA     *this
    );


    /*! Property: Execute Method
     Set up a method and optional object to be called via the
     Exec() method below.
     */
    bool            Opcode_setExec (
        OPCODE_DATA     *this,
        ERESULT         (*pExec)(OBJ_ID, OBJ_ID),
        OBJ_ID          pObjExec
    );


    /*! Property: Flag Set 1
        To be used as needed.
     */
    uint16_t         Opcode_getFlag1 (
        OPCODE_DATA     *this
    );

    bool            Opcode_setFlag1 (
        OPCODE_DATA     *this,
        uint16_t        value
    );


    /*! Property: Flag Set 2
        To be used as needed.
     */
    uint16_t         Opcode_getFlag2 (
        OPCODE_DATA     *this
    );

    bool            Opcode_setFlag2 (
        OPCODE_DATA     *this,
        uint16_t        value
    );


    /*! Property: Opcode Length including all parameters
     */
    uint8_t         Opcode_getLen (
        OPCODE_DATA     *this
    );

    bool            Opcode_setLen (
        OPCODE_DATA     *this,
        uint8_t         value
    );


    /*! Property: Opcode Name
     */
    const
    char *          Opcode_getNameA (
        OPCODE_DATA     *this
    );


    /*! Property: Node
     */
    NODE_DATA *     Opcode_getNode (
        OPCODE_DATA     *this
    );


    /*! Property: Parse Method
     Set up a method and optional object to be called via the
     Parse() method below.
     */
    bool            Opcode_setPrs (
        OPCODE_DATA     *this,
        ERESULT         (*pPrs)(OBJ_ID, OBJ_ID),
        OBJ_ID          pObjPrs
    );


    int16_t         Opcode_getType (
        OPCODE_DATA     *this
    );


    bool            Opcode_setTypeConv (
        OPCODE_DATA     *this,
        const
        char *          (*pTypeDesc) (uint16_t),
        uint16_t        (*pTypeValue) (const char *)
    );



    //---------------------------------------------------------------
    //                      *** Methods ***
    //---------------------------------------------------------------

    /*!
     Assign the contents of this object to the other object (ie
     this -> other).  Any objects in other will be released before
     a copy of the object is performed.
     Example:
     @code
        ERESULT eRc = Opcode_Assign(this,pOther);
     @endcode
     @param     this    object pointer
     @param     pOther  a pointer to another OPCODE object
     @return    If successful, ERESULT_SUCCESS otherwise an
                ERESULT_* error
     */
    ERESULT         Opcode_Assign (
        OPCODE_DATA     *this,
        OPCODE_DATA     *pOther
    );


    /*!
     Compare the two provided objects based on their
     names.
     @return    0  if this == other
                <0 if this < other
                >0 if this > other
     */
    int             Opcode_Compare (
        OPCODE_DATA     *this,
        OPCODE_DATA     *pOther
    );


    int             Opcode_CompareA (
        OPCODE_DATA     *this,
        const
        char            *pNameA
    );


    /*!
     Compare the provided binary opcode with
     this entry.
     @return    true if this == opcode; otherwise, false
     */
    bool             Opcode_CompareOpcode (
        OPCODE_DATA     *this,
        const
        uint8_t         *pOpcode
    );


    /*!
     Copy the current object creating a new object.
     Example:
     @code
        Opcode      *pCopy = Opcode_Copy(this);
     @endcode
     @param     this    object pointer
     @return    If successful, a OPCODE object which must be
                released, otherwise OBJ_NIL.
     @warning   Remember to release the returned object.
     */
    OPCODE_DATA *   Opcode_Copy (
        OPCODE_DATA     *this
    );

   
    /*!
     Execute the method attached to this opcode. See Execute Property.
     @param     this        object pointer
     @param     pOperand    Operand object pointer (optional)
     @return    if successful, ERESULT_SUCCESS.  Otherwise, an ERESULT_*
                error code.
     */
    ERESULT         Opcode_Exec (
        OPCODE_DATA     *this,
        OBJ_ID          pOperand
    );


    uint32_t        Opcode_Hash(
        OPCODE_DATA     *this
    );


    OPCODE_DATA *   Opcode_Init (
        OPCODE_DATA     *this
    );


    /*!
     Execute the parse method attached to this opcode. See Parse Property.
     @param     this        object pointer
     @param     pOperand    Operand object pointer (optional)
     @return    if successful, ERESULT_SUCCESS.  Otherwise, an ERESULT_*
                error code.
     */
    ERESULT         Opcode_Parse (
        OPCODE_DATA     *this,
        OBJ_ID          pOperand
    );


    /*!
     Create a string that when compiled will initialize for this opcode.
     @param     this    object pointer
     @return    If successful, an AStr object which must be released containing the
                initialization, otherwise OBJ_NIL.
     @warning  Remember to release the returned AStr object.
     */
    ASTR_DATA *     Opcode_ToInitString (
        OPCODE_DATA      *this
    );


#ifdef  OPCODE_JSON_SUPPORT
    /*!
     Create a string that describes this object and the objects within it in
     HJSON formt. (See hjson object for details.)
     Example:
     @code
     ASTR_DATA      *pDesc = Opcode_ToJson(this);
     @endcode
     @param     this    object pointer
     @return    If successful, an AStr object which must be released containing the
                JSON text, otherwise OBJ_NIL and LastError set to an appropriate
                ERESULT_* error code.
     @warning   Remember to release the returned AStr object.
     */
    ASTR_DATA *     Opcode_ToJson (
        OPCODE_DATA   *this
    );
#endif


    /*!
     Create a string that describes this object and the objects within it.
     Example:
     @code 
        ASTR_DATA      *pDesc = Opcode_ToDebugString(this,4);
     @endcode 
     @param     this    object pointer
     @param     indent  number of characters to indent every line of output, can be 0
     @return    If successful, an AStr object which must be released containing the
                description, otherwise OBJ_NIL.
     @warning   Remember to release the returned AStr object.
     */
    ASTR_DATA *    Opcode_ToDebugString (
        OPCODE_DATA     *this,
        int             indent
    );
    
    

    
#ifdef	__cplusplus
}
#endif

#endif	/* OPCODE_H */

