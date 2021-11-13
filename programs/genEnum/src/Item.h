// vi:nu:et:sts=4 ts=4 sw=4

//****************************************************************
//                  Enumeration Item (Item) Header
//****************************************************************
/*
 * Program
 *          Enumeration Item (Item)
 * Purpose
 *          This object provides a standardized way of handling
 *          a separate Item to run things without complications
 *          of interfering with the main Item. A Item may be 
 *          called a Item on other O/S's.
 *
 * Remarks
 *  1.      None
 *
 * History
 *  11/12/2021 Generated
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





#include        <Main_defs.h>
#include        <AStr.h>


#ifndef         ITEM_H
#define         ITEM_H


//#define   ITEM_IS_IMMUTABLE     1
//#define   ITEM_JSON_SUPPORT     1
//#define   ITEM_SINGLETON        1





#ifdef  __cplusplus
extern "C" {
#endif
    

    //****************************************************************
    //* * * * * * * * * * * *  Data Definitions  * * * * * * * * * * *
    //****************************************************************


    typedef struct Item_data_s  ITEM_DATA;          // Inherits from ITEM
    typedef struct Item_class_data_s ITEM_CLASS_DATA;  // Inherits from OBJ

    typedef struct Item_vtbl_s  {
        OBJ_IUNKNOWN    iVtbl;              // Inherited Vtbl.
        //Item_VTBL    iVtbl;              // Inherited Vtbl.
        // Put other methods below this as pointers and add their
        // method names to the vtbl definition in Item_object.c.
        // Properties:
        // Methods:
        //bool        (*pIsEnabled)(ITEM_DATA *);
    } ITEM_VTBL;

    typedef struct Item_class_vtbl_s    {
        OBJ_IUNKNOWN    iVtbl;              // Inherited Vtbl.
        // Put other methods below this as pointers and add their
        // method names to the vtbl definition in Item_object.c.
        // Properties:
        // Methods:
        //bool        (*pIsEnabled)(ITEM_DATA *);
    } ITEM_CLASS_VTBL;




    /****************************************************************
    * * * * * * * * * * *  Routine Definitions  * * * * * * * * * * *
    ****************************************************************/


    //---------------------------------------------------------------
    //                      *** Class Methods ***
    //---------------------------------------------------------------

#ifdef  ITEM_SINGLETON
    ITEM_DATA *     Item_Shared (
        void
    );

    void            Item_SharedReset (
        void
    );
#endif


   /*!
     Allocate a new Object and partially initialize. Also, this sets an
     indicator that the object was alloc'd which is tested when the object is
     released.
     @return    pointer to Item object if successful, otherwise OBJ_NIL.
     */
    ITEM_DATA *     Item_Alloc (
        void
    );
    
    
    OBJ_ID          Item_Class (
        void
    );
    
    
    ITEM_DATA *     Item_New (
        void
    );
    
    
#ifdef  ITEM_JSON_SUPPORT
    ITEM_DATA *   Item_NewFromJsonString (
        ASTR_DATA       *pString
    );

    ITEM_DATA *   Item_NewFromJsonStringA (
        const
        char            *pStringA
    );
#endif



    //---------------------------------------------------------------
    //                      *** Properties ***
    //---------------------------------------------------------------

    ASTR_DATA *     Item_getDesc (
        ITEM_DATA       *this
    );

    bool            Item_setDesc (
        ITEM_DATA       *this,
        ASTR_DATA       *pValue
    );


    ASTR_DATA *     Item_getName (
        ITEM_DATA       *this
    );

    bool            Item_setName (
        ITEM_DATA       *this,
        ASTR_DATA       *pValue
    );




    
    //---------------------------------------------------------------
    //                      *** Methods ***
    //---------------------------------------------------------------

    ITEM_DATA *     Item_Init (
        ITEM_DATA       *this
    );


    /*!
     Determine if a value has been set.
     @param     this    object pointer
     @return    If successful, a value has been set; otherwise, an ERESULT_* error.
     */
    ERESULT         Item_IsValue (
        ITEM_DATA       *this
    );
    
 
#ifdef  ITEM_JSON_SUPPORT
    /*!
     Create a string that describes this object and the objects within it in
     HJSON formt. (See hjson object for details.)
     Example:
     @code
     ASTR_DATA      *pDesc = Item_ToJson(this);
     @endcode
     @param     this    object pointer
     @return    If successful, an AStr object which must be released containing the
                JSON text, otherwise OBJ_NIL.
     @warning   Remember to release the returned AStr object.
     */
    ASTR_DATA *     Item_ToJson (
        ITEM_DATA       *this
    );
#endif


    /*!
     Create a string that describes this object and the objects within it.
     Example:
     @code 
        ASTR_DATA      *pDesc = Item_ToDebugString(this,4);
     @endcode 
     @param     this    object pointer
     @param     indent  number of characters to indent every line of output, can be 0
     @return    If successful, an AStr object which must be released containing the
                description, otherwise OBJ_NIL.
     @warning   Remember to release the returned AStr object.
     */
    ASTR_DATA *     Item_ToDebugString (
        ITEM_DATA       *this,
        int             indent
    );
    
    

    
#ifdef  __cplusplus
}
#endif

#endif  /* ITEM_H */

