// vi:nu:et:sts=4 ts=4 sw=4

//****************************************************************
//                  An Item to be generated (GenItem) Header
//****************************************************************
/*
 * Program
 *          An Item to be generated (GenItem)
 * Purpose
 *          This object provides a standardized way of handling
 *          a separate GenItem to run things without complications
 *          of interfering with the main GenItem. A GenItem may be 
 *          called a GenItem on other O/S's.
 *
 * Remarks
 *  1.      None
 *
 * History
 *  11/21/2021 Generated
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





#include        <genObject_defs.h>
#include        <AStr.h>


#ifndef         GENITEM_H
#define         GENITEM_H


//#define   GENITEM_IS_IMMUTABLE     1
//#define   GENITEM_JSON_SUPPORT     1
//#define   GENITEM_SINGLETON        1





#ifdef  __cplusplus
extern "C" {
#endif
    

    //****************************************************************
    //* * * * * * * * * * * *  Data Definitions  * * * * * * * * * * *
    //****************************************************************


    typedef struct GenItem_data_s  GENITEM_DATA;          // Inherits from GENITEM
    typedef struct GenItem_class_data_s GENITEM_CLASS_DATA;  // Inherits from OBJ

    typedef struct GenItem_vtbl_s  {
        OBJ_IUNKNOWN    iVtbl;              // Inherited Vtbl.
        //GenItem_VTBL    iVtbl;              // Inherited Vtbl.
        // Put other methods below this as pointers and add their
        // method names to the vtbl definition in GenItem_object.c.
        // Properties:
        // Methods:
        //bool        (*pIsEnabled)(GENITEM_DATA *);
    } GENITEM_VTBL;

    typedef struct GenItem_class_vtbl_s    {
        OBJ_IUNKNOWN    iVtbl;              // Inherited Vtbl.
        // Put other methods below this as pointers and add their
        // method names to the vtbl definition in GenItem_object.c.
        // Properties:
        // Methods:
        //bool        (*pIsEnabled)(GENITEM_DATA *);
    } GENITEM_CLASS_VTBL;


    /* The following enum was generated from:
     * "genitem_types.txt"
     * If you want to change this enum, you
     * should alter the above file and
     * regenerate using genEnum!
     */

    typedef enum GenItem_type_e {
        GENITEM_TYPE_OBJECT=0,
        GENITEM_TYPE_ENUM=1,
        GENITEM_TYPE_PROPERTY=2,
    } GENITEM_TYPES;




    /****************************************************************
    * * * * * * * * * * *  Routine Definitions  * * * * * * * * * * *
    ****************************************************************/


    //---------------------------------------------------------------
    //                      *** Class Methods ***
    //---------------------------------------------------------------

#ifdef  GENITEM_SINGLETON
    GENITEM_DATA *  GenItem_Shared (
        void
    );

    void            GenItem_SharedReset (
        void
    );
#endif


   /*!
     Allocate a new Object and partially initialize. Also, this sets an
     indicator that the object was alloc'd which is tested when the object is
     released.
     @return    pointer to GenItem object if successful, otherwise OBJ_NIL.
     */
    GENITEM_DATA *  GenItem_Alloc (
        void
    );
    
    
    OBJ_ID          GenItem_Class (
        void
    );
    
    
    GENITEM_DATA *  GenItem_New (
        void
    );
    
    
#ifdef  GENITEM_JSON_SUPPORT
    GENITEM_DATA *  GenItem_NewFromJsonString (
        ASTR_DATA       *pString
    );

    GENITEM_DATA *  GenItem_NewFromJsonStringA (
        const
        char            *pStringA
    );
#endif



    //---------------------------------------------------------------
    //                      *** Properties ***
    //---------------------------------------------------------------

    PATH_DATA *     GenItem_getModel (
        GENITEM_DATA    *this
    );

    bool            GenItem_setModel (
        GENITEM_DATA    *this,
        PATH_DATA       *pValue
    );


    
    //---------------------------------------------------------------
    //                      *** Methods ***
    //---------------------------------------------------------------

    ERESULT         GenItem_Disable (
        GENITEM_DATA    *this
    );


    ERESULT         GenItem_Enable (
        GENITEM_DATA    *this
    );

   
    GENITEM_DATA *  GenItem_Init (
        GENITEM_DATA    *this
    );


    ERESULT         GenItem_IsEnabled (
        GENITEM_DATA    *this
    );
    
 
#ifdef  GENITEM_JSON_SUPPORT
    /*!
     Create a string that describes this object and the objects within it in
     HJSON formt. (See hjson object for details.)
     Example:
     @code
     ASTR_DATA      *pDesc = GenItem_ToJson(this);
     @endcode
     @param     this    object pointer
     @return    If successful, an AStr object which must be released containing the
                JSON text, otherwise OBJ_NIL.
     @warning   Remember to release the returned AStr object.
     */
    ASTR_DATA *     GenItem_ToJson (
        GENITEM_DATA    *this
    );
#endif


    /*!
     Create a string that describes this object and the objects within it.
     Example:
     @code 
        ASTR_DATA      *pDesc = GenItem_ToDebugString(this,4);
     @endcode 
     @param     this    object pointer
     @param     indent  number of characters to indent every line of output, can be 0
     @return    If successful, an AStr object which must be released containing the
                description, otherwise OBJ_NIL.
     @warning   Remember to release the returned AStr object.
     */
    ASTR_DATA *     GenItem_ToDebugString (
        GENITEM_DATA    *this,
        int             indent
    );
    
    

    
#ifdef  __cplusplus
}
#endif

#endif  /* GENITEM_H */

