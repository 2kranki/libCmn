// vi:nu:et:sts=4 ts=4 sw=4

//****************************************************************
//                  uint32_t Integer Index (U32Index) Header
//****************************************************************
/*
 * Program
 *          uint32_t Integer Index (U32Index)
 * Purpose
 *          This object provides a standardized way of handling
 *          a separate U32Index to run things without complications
 *          of interfering with the main U32Index. A U32Index may be 
 *          called a U32Index on other O/S's.
 *
 * Remarks
 *  1.      None
 *
 * History
 *  01/04/2021 Generated
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


#ifndef         U32INDEX_H
#define         U32INDEX_H


//#define   U32INDEX_IS_IMMUTABLE     1
//#define   U32INDEX_JSON_SUPPORT     1
//#define   U32INDEX_SINGLETON        1





#ifdef  __cplusplus
extern "C" {
#endif
    

    //****************************************************************
    //* * * * * * * * * * * *  Data Definitions  * * * * * * * * * * *
    //****************************************************************


    typedef struct U32Index_data_s  U32INDEX_DATA;            // Inherits from OBJ
    typedef struct U32Index_class_data_s U32INDEX_CLASS_DATA;   // Inherits from OBJ

    typedef struct U32Index_vtbl_s  {
        OBJ_IUNKNOWN    iVtbl;              // Inherited Vtbl.
        // Put other methods below this as pointers and add their
        // method names to the vtbl definition in U32Index_object.c.
        // Properties:
        // Methods:
        //bool        (*pIsEnabled)(U32INDEX_DATA *);
    } U32INDEX_VTBL;

    typedef struct U32Index_class_vtbl_s    {
        OBJ_IUNKNOWN    iVtbl;              // Inherited Vtbl.
        // Put other methods below this as pointers and add their
        // method names to the vtbl definition in U32Index_object.c.
        // Properties:
        // Methods:
        //bool        (*pIsEnabled)(U32INDEX_DATA *);
    } U32INDEX_CLASS_VTBL;




    /****************************************************************
    * * * * * * * * * * *  Routine Definitions  * * * * * * * * * * *
    ****************************************************************/


    //---------------------------------------------------------------
    //                      *** Class Methods ***
    //---------------------------------------------------------------

#ifdef  U32INDEX_SINGLETON
    U32INDEX_DATA *     U32Index_Shared (
        void
    );

    void            U32Index_SharedReset (
        void
    );
#endif


   /*!
     Allocate a new Object and partially initialize. Also, this sets an
     indicator that the object was alloc'd which is tested when the object is
     released.
     @return    pointer to U32Index object if successful, otherwise OBJ_NIL.
     */
    U32INDEX_DATA *     U32Index_Alloc (
        void
    );
    
    
    OBJ_ID          U32Index_Class (
        void
    );
    
    
    U32INDEX_DATA *     U32Index_New (
        void
    );
    
    
#ifdef  U32INDEX_JSON_SUPPORT
    U32INDEX_DATA *   U32Index_NewFromJsonString (
        ASTR_DATA       *pString
    );

    U32INDEX_DATA *   U32Index_NewFromJsonStringA (
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
     Add the given item to the index if it does
     @param     this    object pointer
     @param     index   index number to search by
     @param     fUpdate true == replace ptr if index is found
     @return    if successful, the void pointer associated with the
                index; otherwise, NULL;
     */
    ERESULT         U32Index_Add (
        U32INDEX_DATA   *this,
        int             index,
        void            *ptr,
        bool            fUpdate
    );


    /*!
     Delete the index number entry from the index if present.
     @param     this    object pointer
     @param     index   index number to search by
     @return    if successful, the void pointer associated with the
                index; otherwise, NULL;
     */
    ERESULT         U32Index_Delete (
        U32INDEX_DATA   *this,
        int             index
    );


    /*!
     Search the index by index number and return the associated void
     pointer if found.
     @param     this    object pointer
     @param     index   index number to search by
     @return    if successful, the void pointer associated with the
                index; otherwise, NULL;
     */
    void *         U32Index_Find (
        U32INDEX_DATA   *this,
        int             index
    );


    U32INDEX_DATA *   U32Index_Init (
        U32INDEX_DATA     *this
    );


    ERESULT     U32Index_IsEnabled (
        U32INDEX_DATA       *this
    );
    
 
#ifdef  U32INDEX_JSON_SUPPORT
    /*!
     Create a string that describes this object and the objects within it in
     HJSON formt. (See hjson object for details.)
     Example:
     @code
     ASTR_DATA      *pDesc = U32Index_ToJson(this);
     @endcode
     @param     this    object pointer
     @return    If successful, an AStr object which must be released containing the
                JSON text, otherwise OBJ_NIL.
     @warning   Remember to release the returned AStr object.
     */
    ASTR_DATA *     U32Index_ToJson (
        U32INDEX_DATA   *this
    );
#endif


    /*!
     Create a string that describes this object and the objects within it.
     Example:
     @code 
        ASTR_DATA      *pDesc = U32Index_ToDebugString(this,4);
     @endcode 
     @param     this    object pointer
     @param     indent  number of characters to indent every line of output, can be 0
     @return    If successful, an AStr object which must be released containing the
                description, otherwise OBJ_NIL.
     @warning   Remember to release the returned AStr object.
     */
    ASTR_DATA *     U32Index_ToDebugString (
        U32INDEX_DATA     *this,
        int             indent
    );
    
    

    
#ifdef  __cplusplus
}
#endif

#endif  /* U32INDEX_H */

