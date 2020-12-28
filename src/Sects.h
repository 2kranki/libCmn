// vi:nu:et:sts=4 ts=4 sw=4

//****************************************************************
//                  Section Table (Sects) Header
//****************************************************************
/*
 * Program
 *          Section Table (Sects)
 * Purpose
 *          This object provides a standardized way of handling
 *          a separate Sects to run things without complications
 *          of interfering with the main Sects. A Sects may be 
 *          called a Sects on other O/S's.
 *
 * Remarks
 *  1.      None
 *
 * History
 *  12/27/2020 Generated
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
#include        <ObjEnum.h>
#include        <Sect.h>


#ifndef         SECTS_H
#define         SECTS_H


//#define   SECTS_IS_IMMUTABLE     1
#define   SECTS_JSON_SUPPORT       1
//#define   SECTS_SINGLETON        1





#ifdef  __cplusplus
extern "C" {
#endif
    

    //****************************************************************
    //* * * * * * * * * * * *  Data Definitions  * * * * * * * * * * *
    //****************************************************************


    typedef struct Sects_data_s  SECTS_DATA;            // Inherits from OBJ
    typedef struct Sects_class_data_s SECTS_CLASS_DATA;   // Inherits from OBJ

    typedef struct Sects_vtbl_s  {
        OBJ_IUNKNOWN    iVtbl;              // Inherited Vtbl.
        // Put other methods below this as pointers and add their
        // method names to the vtbl definition in Sects_object.c.
        // Properties:
        // Methods:
        //bool        (*pIsEnabled)(SECTS_DATA *);
    } SECTS_VTBL;

    typedef struct Sects_class_vtbl_s    {
        OBJ_IUNKNOWN    iVtbl;              // Inherited Vtbl.
        // Put other methods below this as pointers and add their
        // method names to the vtbl definition in Sects_object.c.
        // Properties:
        // Methods:
        //bool        (*pIsEnabled)(SECTS_DATA *);
    } SECTS_CLASS_VTBL;




    /****************************************************************
    * * * * * * * * * * *  Routine Definitions  * * * * * * * * * * *
    ****************************************************************/


    //---------------------------------------------------------------
    //                      *** Class Methods ***
    //---------------------------------------------------------------

#ifdef  SECTS_SINGLETON
    SECTS_DATA *     Sects_Shared (
        void
    );

    void            Sects_SharedReset (
        void
    );
#endif


   /*!
     Allocate a new Object and partially initialize. Also, this sets an
     indicator that the object was alloc'd which is tested when the object is
     released.
     @return    pointer to Sects object if successful, otherwise OBJ_NIL.
     */
    SECTS_DATA *     Sects_Alloc (
        void
    );
    
    
    OBJ_ID          Sects_Class (
        void
    );
    
    
    SECTS_DATA *     Sects_New (
        void
    );
    
    
#ifdef  SECTS_JSON_SUPPORT
    SECTS_DATA *   Sects_NewFromJsonString (
        ASTR_DATA       *pString
    );

    SECTS_DATA *   Sects_NewFromJsonStringA (
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

    /*!
     Add the given Symbol object to the Tree.
     @param     this        Object Pointer
     @param     pSym        Symbol Entry Object Pointer
     @return    If successful, ERESULT_SUCCESS; otherwise, an ERESULT_*
                error code is returned.
     */
    ERESULT         Sects_Add (
        SECTS_DATA      *this,
        SECT_DATA       *pSym
    );

    ERESULT         Sects_AddA (
        SECTS_DATA      *this,
        char            ident,
        char            type,
        uint32_t        addr,
        uint32_t        offset,
        uint32_t        len,
        const
        char            *pNameA
    );


    ERESULT         Sects_DeleteA (
        SECTS_DATA      *this,
        const
        char            *pNameA
    );


    /*!
     Create an enumerator for the entries.
     @return    If successful, an ENUM object is returned.  Otherwise,
     OBJ_NIL.
     @warning   Remember to release the returned ENUM object.
     */
    OBJENUM_DATA *  Sects_Enum (
        SECTS_DATA       *this
    );


    /*!
     Search the entries for a particular entry using the
     the given name and the table entry's compare function.
     @return    If successful, an SECT object is returned.
                Otherwise, OBJ_NIL.
     */
    SECT_DATA *    Sects_FindA (
        SECTS_DATA      *this,
        const
        char            *pNameA
    );


    SECTS_DATA *   Sects_Init (
        SECTS_DATA     *this
    );


    ERESULT     Sects_IsEnabled (
        SECTS_DATA       *this
    );
    
 
#ifdef  SECTS_JSON_SUPPORT
    /*!
     Create a string that describes this object and the objects within it in
     HJSON formt. (See hjson object for details.)
     Example:
     @code
     ASTR_DATA      *pDesc = Sects_ToJson(this);
     @endcode
     @param     this    object pointer
     @return    If successful, an AStr object which must be released containing the
                JSON text, otherwise OBJ_NIL.
     @warning   Remember to release the returned AStr object.
     */
    ASTR_DATA *     Sects_ToJson (
        SECTS_DATA   *this
    );
#endif


    /*!
     Create a string that describes this object and the objects within it.
     Example:
     @code 
        ASTR_DATA      *pDesc = Sects_ToDebugString(this,4);
     @endcode 
     @param     this    object pointer
     @param     indent  number of characters to indent every line of output, can be 0
     @return    If successful, an AStr object which must be released containing the
                description, otherwise OBJ_NIL.
     @warning   Remember to release the returned AStr object.
     */
    ASTR_DATA *     Sects_ToDebugString (
        SECTS_DATA     *this,
        int             indent
    );
    
    

    
#ifdef  __cplusplus
}
#endif

#endif  /* SECTS_H */

