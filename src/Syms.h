// vi:nu:et:sts=4 ts=4 sw=4

//****************************************************************
//          SYMS Console Transmit Task (Syms) Header
//****************************************************************
/*
 * Program
 *			Separate Syms (Syms)
 * Purpose
 *			This object provides a standardized way of handling
 *          a separate Syms to run things without complications
 *          of interfering with the main Syms. A Syms may be 
 *          called a Syms on other O/S's.
 *
 * Remarks
 *	1.      None
 *
 * History
 *	02/22/2020 Generated
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
#include        <NodeEnum.h>
#include        <Sym.h>


#ifndef         SYMS_H
#define         SYMS_H


//#define   SYMS_IS_IMMUTABLE     1
#define   SYMS_JSON_SUPPORT     1
//#define   SYMS_SINGLETON        1





#ifdef	__cplusplus
extern "C" {
#endif
    

    //****************************************************************
    //* * * * * * * * * * * *  Data Definitions  * * * * * * * * * * *
    //****************************************************************


    typedef struct Syms_data_s	SYMS_DATA;            // Inherits from OBJ
    typedef struct Syms_class_data_s SYMS_CLASS_DATA;   // Inherits from OBJ

    typedef struct Syms_vtbl_s	{
        OBJ_IUNKNOWN    iVtbl;              // Inherited Vtbl.
        // Put other methods below this as pointers and add their
        // method names to the vtbl definition in Syms_object.c.
        // Properties:
        // Methods:
        //bool        (*pIsEnabled)(SYMS_DATA *);
    } SYMS_VTBL;

    typedef struct Syms_class_vtbl_s	{
        OBJ_IUNKNOWN    iVtbl;              // Inherited Vtbl.
        // Put other methods below this as pointers and add their
        // method names to the vtbl definition in Syms_object.c.
        // Properties:
        // Methods:
        //bool        (*pIsEnabled)(SYMS_DATA *);
    } SYMS_CLASS_VTBL;




    /****************************************************************
    * * * * * * * * * * *  Routine Definitions	* * * * * * * * * * *
    ****************************************************************/


    //---------------------------------------------------------------
    //                      *** Class Methods ***
    //---------------------------------------------------------------

#ifdef  SYMS_SINGLETON
    SYMS_DATA *     Syms_Shared (
        void
    );

    void            Syms_SharedReset (
        void
    );
#endif


   /*!
     Allocate a new Object and partially initialize. Also, this sets an
     indicator that the object was alloc'd which is tested when the object is
     released.
     @return    pointer to Syms object if successful, otherwise OBJ_NIL.
     */
    SYMS_DATA *     Syms_Alloc (
        void
    );
    
    
    OBJ_ID          Syms_Class (
        void
    );
    
    
    SYMS_DATA *     Syms_New (
        void
    );
    
    
#ifdef  SYMS_JSON_SUPPORT
    SYMS_DATA *   Syms_NewFromJsonString (
        ASTR_DATA       *pString
    );

    SYMS_DATA *   Syms_NewFromJsonStringA (
        const
        char            *pStringA
    );
#endif



    //---------------------------------------------------------------
    //                      *** Properties ***
    //---------------------------------------------------------------

    uint32_t        Syms_getSize (
        SYMS_DATA       *this
    );


    
    //---------------------------------------------------------------
    //                      *** Methods ***
    //---------------------------------------------------------------

    /*!
     Add the given node to the Hash. If duplicates are not allowed, then
     the node's name must not exist in the Hash.  Otherwise, the node will
     be added to the head of the Hash list effectively blocking access to
     other nodes with the same name.  The A versions creates a node from
     the data given before trying to add it to the Hash.
     @param     this        Object Pointer
     @param     pSym        Symbol Entry Object Pointer
     @param     fReplace    true == replace current entry if it exists,
                            otherwise, return ERESULT_DATA_ALREADY_EXISTS
                            error.
     @return    If successful, ERESULT_SUCCESS; otherwise, an ERESULT_*
     error code is returned.
     */
    ERESULT         Syms_Add (
        SYMS_DATA       *this,
        SYM_DATA        *pSym,
        bool            fReplace
    );


    ERESULT         Syms_DeleteA (
        SYMS_DATA       *this,
        int32_t         cls,
        const
        char            *pNameA
    );


    /*!
     Create an enumerator for the entries.
     @return    If successful, an ENUM object is returned.  Otherwise,
     OBJ_NIL.
     @warning   Remember to release the returned ENUM object.
     */
    NODEENUM_DATA *  Syms_Enum (
        SYMS_DATA        *this
    );


    /*!
     Search the entries for a particular symbol entry using the
     characteristics of the given node and its compare function.
     @return    If successful, an SYM object is returned.  Otherwise,
                OBJ_NIL.
     */
    SYM_DATA *      Syms_FindA (
        SYMS_DATA       *this,
        int32_t         cls,
        const
        char            *pNameA
    );


    SYMS_DATA *     Syms_Init (
        SYMS_DATA       *this
    );


#ifdef  SYMS_JSON_SUPPORT
    /*!
     Create a string that describes this object and the objects within it in
     HJSON formt. (See hjson object for details.)
     Example:
     @code
     ASTR_DATA      *pDesc = Syms_ToJson(this);
     @endcode
     @param     this    object pointer
     @return    If successful, an AStr object which must be released containing the
                JSON text, otherwise OBJ_NIL and LastError set to an appropriate
                ERESULT_* error code.
     @warning   Remember to release the returned AStr object.
     */
    ASTR_DATA *     Syms_ToJson (
        SYMS_DATA   *this
    );
#endif


    /*!
     Create a string that describes this object and the objects within it.
     Example:
     @code 
        ASTR_DATA      *pDesc = Syms_ToDebugString(this,4);
     @endcode 
     @param     this    object pointer
     @param     indent  number of characters to indent every line of output, can be 0
     @return    If successful, an AStr object which must be released containing the
                description, otherwise OBJ_NIL.
     @warning   Remember to release the returned AStr object.
     */
    ASTR_DATA *    Syms_ToDebugString (
        SYMS_DATA     *this,
        int             indent
    );
    
    

    
#ifdef	__cplusplus
}
#endif

#endif	/* SYMS_H */

