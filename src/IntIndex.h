// vi:nu:et:sts=4 ts=4 sw=4

//****************************************************************
//                  Integer Index (IntIndex) Header
//****************************************************************
/*
 * Program
 *          Integer Index (IntIndex)
 * Purpose
 *          This object provides an integer index with an associated
 *          data pointer. The index is maintained in order (either
 *          signed or unsigned(default)).
 *
 * Remarks
 *  1.      None
 *
 * History
 *  01/03/2021 Generated
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


#ifndef         INTINDEX_H
#define         INTINDEX_H


//#define   INTINDEX_IS_IMMUTABLE     1
//#define   INTINDEX_JSON_SUPPORT     1
//#define   INTINDEX_SINGLETON        1





#ifdef  __cplusplus
extern "C" {
#endif
    

    //****************************************************************
    //* * * * * * * * * * * *  Data Definitions  * * * * * * * * * * *
    //****************************************************************


    typedef struct IntIndex_data_s  INTINDEX_DATA;            // Inherits from OBJ
    typedef struct IntIndex_class_data_s INTINDEX_CLASS_DATA;   // Inherits from OBJ

    typedef struct IntIndex_vtbl_s  {
        OBJ_IUNKNOWN    iVtbl;              // Inherited Vtbl.
        // Put other methods below this as pointers and add their
        // method names to the vtbl definition in IntIndex_object.c.
        // Properties:
        // Methods:
        //bool        (*pIsEnabled)(INTINDEX_DATA *);
    } INTINDEX_VTBL;

    typedef struct IntIndex_class_vtbl_s    {
        OBJ_IUNKNOWN    iVtbl;              // Inherited Vtbl.
        // Put other methods below this as pointers and add their
        // method names to the vtbl definition in IntIndex_object.c.
        // Properties:
        // Methods:
        //bool        (*pIsEnabled)(INTINDEX_DATA *);
    } INTINDEX_CLASS_VTBL;




    /****************************************************************
    * * * * * * * * * * *  Routine Definitions  * * * * * * * * * * *
    ****************************************************************/


    //---------------------------------------------------------------
    //                      *** Class Methods ***
    //---------------------------------------------------------------

#ifdef  INTINDEX_SINGLETON
    INTINDEX_DATA * IntIndex_Shared (
        void
    );

    void            IntIndex_SharedReset (
        void
    );
#endif


   /*!
     Allocate a new Object and partially initialize. Also, this sets an
     indicator that the object was alloc'd which is tested when the object is
     released.
     @return    pointer to IntIndex object if successful, otherwise OBJ_NIL.
     */
    INTINDEX_DATA * IntIndex_Alloc (
        void
    );
    
    
    OBJ_ID          IntIndex_Class (
        void
    );
    
    
    INTINDEX_DATA * IntIndex_New (
        void
    );
    
    
#ifdef  INTINDEX_JSON_SUPPORT
    INTINDEX_DATA *   IntIndex_NewFromJsonString (
        ASTR_DATA       *pString
    );

    INTINDEX_DATA *   IntIndex_NewFromJsonStringA (
        const
        char            *pStringA
    );
#endif



    //---------------------------------------------------------------
    //                      *** Properties ***
    //---------------------------------------------------------------

    bool            IntIndex_getSigned (
        INTINDEX_DATA   *this
    );

    bool            IntIndex_setSigned (
        INTINDEX_DATA   *this,
        bool            fValue
    );



    
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
    ERESULT         IntIndex_Add (
        INTINDEX_DATA   *this,
        int             index,
        void            *ptr,
        bool            fUpdate
    );


    /*!
     Search the index by index number and return the associated void
     pointer if found.
     @param     this    object pointer
     @param     index   index number to search by
     @return    if successful, the void pointer associated with the
                index; otherwise, NULL;
     */
    void *         IntIndex_Find (
        INTINDEX_DATA   *this,
        int             index
    );

   
    INTINDEX_DATA * IntIndex_Init (
        INTINDEX_DATA   *this
    );


    ERESULT         IntIndex_IsEnabled (
        INTINDEX_DATA   *this
    );
    
 
#ifdef  INTINDEX_JSON_SUPPORT
    /*!
     Create a string that describes this object and the objects within it in
     HJSON formt. (See hjson object for details.)
     Example:
     @code
     ASTR_DATA      *pDesc = IntIndex_ToJson(this);
     @endcode
     @param     this    object pointer
     @return    If successful, an AStr object which must be released containing the
                JSON text, otherwise OBJ_NIL.
     @warning   Remember to release the returned AStr object.
     */
    ASTR_DATA *     IntIndex_ToJson (
        INTINDEX_DATA   *this
    );
#endif


    /*!
     Create a string that describes this object and the objects within it.
     Example:
     @code 
        ASTR_DATA      *pDesc = IntIndex_ToDebugString(this,4);
     @endcode 
     @param     this    object pointer
     @param     indent  number of characters to indent every line of output, can be 0
     @return    If successful, an AStr object which must be released containing the
                description, otherwise OBJ_NIL.
     @warning   Remember to release the returned AStr object.
     */
    ASTR_DATA *     IntIndex_ToDebugString (
        INTINDEX_DATA     *this,
        int             indent
    );
    
    

    
#ifdef  __cplusplus
}
#endif

#endif  /* INTINDEX_H */

