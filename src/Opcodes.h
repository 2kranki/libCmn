// vi:nu:et:sts=4 ts=4 sw=4

//****************************************************************
//          Universal Opcode Table (Opcodes) Header
//****************************************************************
/*
 * Program
 *			Universal Opcode Table (Opcodes)
 * Purpose
 *			It is the goal of this opcode table to provide all the
 *          information needed for assemblers, disassemblers, and
 *          emulators. Each of these applications need the opcodes
 *          indexed differently.
 *
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
#include        <ObjArray.h>
#include        <ObjEnum.h>
#include        <Opcode.h>


#ifndef         OPCODES_H
#define         OPCODES_H


//#define   OPCODES_IS_IMMUTABLE     1
#define   OPCODES_JSON_SUPPORT     1
//#define   OPCODES_SINGLETON        1





#ifdef	__cplusplus
extern "C" {
#endif
    

    //****************************************************************
    //* * * * * * * * * * * *  Data Definitions  * * * * * * * * * * *
    //****************************************************************


    typedef struct Opcodes_data_s	OPCODES_DATA;            // Inherits from OBJ
    typedef struct Opcodes_class_data_s OPCODES_CLASS_DATA;   // Inherits from OBJ

    typedef struct Opcodes_vtbl_s	{
        OBJ_IUNKNOWN    iVtbl;              // Inherited Vtbl.
        // Put other methods below this as pointers and add their
        // method names to the vtbl definition in Opcodes_object.c.
        // Properties:
        // Methods:
        OPCODE_DATA *   (*pFindA) (
            OPCODES_DATA    *this,
            const
            char            *pNameA
        );
    } OPCODES_VTBL;

    typedef struct Opcodes_class_vtbl_s	{
        OBJ_IUNKNOWN    iVtbl;              // Inherited Vtbl.
        // Put other methods below this as pointers and add their
        // method names to the vtbl definition in Opcodes_object.c.
        // Properties:
        // Methods:
        //bool        (*pIsEnabled)(OPCODES_DATA *);
    } OPCODES_CLASS_VTBL;




    /****************************************************************
    * * * * * * * * * * *  Routine Definitions	* * * * * * * * * * *
    ****************************************************************/


    //---------------------------------------------------------------
    //                      *** Class Methods ***
    //---------------------------------------------------------------

#ifdef  OPCODES_SINGLETON
    OPCODES_DATA *  Opcodes_Shared (
        void
    );

    void            Opcodes_SharedReset (
        void
    );
#endif


   /*!
     Allocate a new Object and partially initialize. Also, this sets an
     indicator that the object was alloc'd which is tested when the object is
     released.
     @return    pointer to Opcodes object if successful, otherwise OBJ_NIL.
     */
    OPCODES_DATA *  Opcodes_Alloc (
        void
    );
    
    
    OBJ_ID          Opcodes_Class (
        void
    );
    
    
    OPCODES_DATA *  Opcodes_New (
        void
    );
    
    
#ifdef  OPCODES_JSON_SUPPORT
    OPCODES_DATA *  Opcodes_NewFromJsonString (
        ASTR_DATA       *pString
    );

    OPCODES_DATA *  Opcodes_NewFromJsonStringA (
        const
        char            *pStringA
    );
#endif



    //---------------------------------------------------------------
    //                      *** Properties ***
    //---------------------------------------------------------------

    OBJARRAY_DATA * Opcodes_getArray (
        OPCODES_DATA    *this
    );


    uint32_t        Opcodes_getSize (
        OPCODES_DATA    *this
    );


    
    //---------------------------------------------------------------
    //                      *** Methods ***
    //---------------------------------------------------------------

    /*!
     Add the given node to the Tree. Duplicates are not allowed.
     @param     this        Object Pointer
     @param     pOpc        Opcode Entry Object Pointer
     @return    If successful, ERESULT_SUCCESS; otherwise, an ERESULT_*
                error code is returned.
     */
    ERESULT         Opcodes_Add (
        OPCODES_DATA    *this,
        OPCODE_DATA     *pOpc
    );


    ERESULT         Opcodes_DeleteA (
        OPCODES_DATA    *this,
        const
        char            *pNameA
    );


    /*!
     Create an enumerator for the entries.
     @return    If successful, an ENUM object is returned.  Otherwise,
     OBJ_NIL.
     @warning   Remember to release the returned ENUM object.
     */
    OBJENUM_DATA *  Opcodes_Enum (
        OPCODES_DATA    *this
    );


    /*!
     Search the entries for a particular symbol entry using the
     characteristics of the given node and its compare function.
     @return    If successful, an SYM object is returned.  Otherwise,
                OBJ_NIL.
     */
    OPCODE_DATA *   Opcodes_FindA (
        OPCODES_DATA    *this,
        const
        char            *pNameA
    );


    /*!
     Get the indexth Opcode from the array of opcodes.
     @return    If successful, an Opcode object is returned.  Otherwise,
                OBJ_NIL.
     */
    OPCODE_DATA *   Opcodes_Get (
        OPCODES_DATA    *this,
        uint32_t        index
    );


    OPCODES_DATA *   Opcodes_Init (
        OPCODES_DATA     *this
    );


#ifdef  OPCODES_JSON_SUPPORT
    /*!
     Create a string that describes this object and the objects within it in
     HJSON formt. (See hjson object for details.)
     Example:
     @code
     ASTR_DATA      *pDesc = Opcodes_ToJson(this);
     @endcode
     @param     this    object pointer
     @return    If successful, an AStr object which must be released containing the
                JSON text, otherwise OBJ_NIL and LastError set to an appropriate
                ERESULT_* error code.
     @warning   Remember to release the returned AStr object.
     */
    ASTR_DATA *     Opcodes_ToJson (
        OPCODES_DATA   *this
    );
#endif


    /*!
     Create a string that describes this object and the objects within it.
     Example:
     @code 
        ASTR_DATA      *pDesc = Opcodes_ToDebugString(this,4);
     @endcode 
     @param     this    object pointer
     @param     indent  number of characters to indent every line of output, can be 0
     @return    If successful, an AStr object which must be released containing the
                description, otherwise OBJ_NIL.
     @warning   Remember to release the returned AStr object.
     */
    ASTR_DATA *    Opcodes_ToDebugString (
        OPCODES_DATA    *this,
        int             indent
    );
    
    
    /*!
     Verify the binary tree used by this object.
     @param     this    object pointer
     @return    if successful, ERESULT_SUCCESS.  Otherwise, an ERESULT_*
                error code.
     */
    ERESULT        Opcodes_VerifyTree (
        OPCODES_DATA    *this
    );



    
#ifdef	__cplusplus
}
#endif

#endif	/* OPCODES_H */

