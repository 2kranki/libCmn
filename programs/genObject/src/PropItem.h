// vi:nu:et:sts=4 ts=4 sw=4

//****************************************************************
//                  Property Item (PropItem) Header
//****************************************************************
/*
 * Program
 *          Property Item (PropItem)
 * Purpose
 *          This object provides a standardized way of handling
 *          a separate PropItem to run things without complications
 *          of interfering with the main PropItem. A PropItem may be 
 *          called a PropItem on other O/S's.
 *
 * Remarks
 *  1.      None
 *
 * History
 *  11/22/2021 Generated
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


#ifndef         PROPITEM_H
#define         PROPITEM_H


//#define   PROPITEM_IS_IMMUTABLE     1
#define   PROPITEM_JSON_SUPPORT       1
//#define   PROPITEM_SINGLETON        1
//#define       PROPITEM_MSGS   1





#ifdef  __cplusplus
extern "C" {
#endif
    

    //****************************************************************
    //* * * * * * * * * * * *  Data Definitions  * * * * * * * * * * *
    //****************************************************************


    typedef struct PropItem_data_s  PROPITEM_DATA;          // Inherits from PROPITEM
    typedef struct PropItem_class_data_s PROPITEM_CLASS_DATA;  // Inherits from OBJ

    typedef struct PropItem_vtbl_s  {
        OBJ_IUNKNOWN    iVtbl;              // Inherited Vtbl.
        //PropItem_VTBL    iVtbl;              // Inherited Vtbl.
        // Put other methods below this as pointers and add their
        // method names to the vtbl definition in PropItem_object.c.
        // Properties:
        // Methods:
        //bool        (*pIsEnabled)(PROPITEM_DATA *);
    } PROPITEM_VTBL;

    typedef struct PropItem_class_vtbl_s    {
        OBJ_IUNKNOWN    iVtbl;              // Inherited Vtbl.
        // Put other methods below this as pointers and add their
        // method names to the vtbl definition in PropItem_object.c.
        // Properties:
        // Methods:
        //bool        (*pIsEnabled)(PROPITEM_DATA *);
    } PROPITEM_CLASS_VTBL;


    /* The following enum was generated from:
     * "propitem_vis.txt"
     * If you want to change this enum, you
     * should alter the above file and
     * regenerate using genEnum!
     */

    typedef enum PropItem_vis_e {
        PROPITEM_VIS_NONE=0,
        PROPITEM_VIS_PUBLIC=1,
        PROPITEM_VIS_READ_ONLY=2,
    } PROPITEM_VISS;


    /* The following enum was generated from:
     * "propitem_types.txt"
     * If you want to change this enum, you
     * should alter the above file and
     * regenerate using genEnum!
     */

    typedef enum PropItem_type_e {
        PROPITEM_TYPE_ASTR=0,
        PROPITEM_TYPE_FLAG8=1,
        PROPITEM_TYPE_FLAG16=2,
        PROPITEM_TYPE_FLAG32=3,
        PROPITEM_TYPE_INT8=4,
        PROPITEM_TYPE_INT16=5,
        PROPITEM_TYPE_INT32=6,
        PROPITEM_TYPE_INT64=7,
        PROPITEM_TYPE_OBJECT=8,
        PROPITEM_TYPE_UINT8=9,
        PROPITEM_TYPE_UINT16=10,
        PROPITEM_TYPE_UINT32=11,
        PROPITEM_TYPE_UINT64=12,
    } PROPITEM_TYPES;



    /****************************************************************
    * * * * * * * * * * *  Routine Definitions  * * * * * * * * * * *
    ****************************************************************/


    //---------------------------------------------------------------
    //                      *** Class Methods ***
    //---------------------------------------------------------------

#ifdef  PROPITEM_SINGLETON
    PROPITEM_DATA * PropItem_Shared (
        void
    );

    void            PropItem_SharedReset (
        void
    );
#endif


   /*!
     Allocate a new Object and partially initialize. Also, this sets an
     indicator that the object was alloc'd which is tested when the object is
     released.
     @return    pointer to PropItem object if successful, otherwise OBJ_NIL.
     */
    PROPITEM_DATA * PropItem_Alloc (
        void
    );
    
    
    OBJ_ID          PropItem_Class (
        void
    );
    
    
    PROPITEM_DATA * PropItem_New (
        void
    );
    
    
#ifdef  PROPITEM_JSON_SUPPORT
    PROPITEM_DATA * PropItem_NewFromJsonString (
        ASTR_DATA       *pString
    );

    PROPITEM_DATA * PropItem_NewFromJsonStringA (
        const
        char            *pStringA
    );
#endif



    //---------------------------------------------------------------
    //                      *** Properties ***
    //---------------------------------------------------------------

#ifdef PROPITEM_MSGS
    /*! @property   Messages
        Allows information and warning messages to be issued.
     */
    bool            PropItem_setMsgs (
        PROPITEM_DATA    *this,
        void            (*pMsgInfo)(OBJ_ID, const char *, ...),
        void            (*pMsgWarn)(OBJ_ID, uint16_t, const char *, ...),
        OBJ_ID          pObj
    );
#endif


    
    //---------------------------------------------------------------
    //                      *** Methods ***
    //---------------------------------------------------------------

    /*!
     Assign the contents of this object to the other object (ie
     this -> other).  Any objects in other will be released before
     a copy of the object is performed.
     Example:
     @code
        ERESULT eRc = PropItem_Assign(this,pOther);
     @endcode
     @param     this    object pointer
     @param     pOther  a pointer to another PROPITEM object
     @return    If successful, ERESULT_SUCCESS otherwise an
                ERESULT_* error
     */
    ERESULT         PropItem_Assign (
        PROPITEM_DATA   *this,
        PROPITEM_DATA   *pOther
    );


    /*!
     Compare the two provided objects.
     @return    0  if this == other
                <0 if this < other
                >0 if this > other
     */
    int             PropItem_Compare (
        PROPITEM_DATA   *this,
        PROPITEM_DATA   *pOther
    );


    /*!
     Copy the current object creating a new object.
     Example:
     @code
        PropItem      *pCopy = PropItem_Copy(this);
     @endcode
     @param     this    object pointer
     @return    If successful, a PROPITEM object which must be
                released, otherwise OBJ_NIL.
     @warning   Remember to release the returned object.
     */
    PROPITEM_DATA * PropItem_Copy (
        PROPITEM_DATA   *this
    );

   
    /*!
     Generate a string that contains the Property Definition for the
     code file.
     @param     this    object pointer
     @param     pClass  Class Name
     @param     pClassUC Uppercase Class Name
     @return    If successful, an AStr object which must be released containing the
                description, otherwise OBJ_NIL.
     @warning  Remember to release the returned AStr object.
     */
    ASTR_DATA *     PropItem_GenCode (
        PROPITEM_DATA   *this,
        const
        char            *pClass,
        const
        char            *pClassUC
    );


    /*!
     Generate a string that contains the Property Definition for the
     header file.
     @param     this    object pointer
     @param     pClass  Class Name
     @param     pClassUC Uppercase Class Name
     @return    If successful, an AStr object which must be released containing the
                description, otherwise OBJ_NIL.
     @warning  Remember to release the returned AStr object.
     */
    ASTR_DATA *     PropItem_GenHdrDefn (
        PROPITEM_DATA   *this,
        const
        char            *pClass,
        const
        char            *pClassUC
    );


    /*!
     Generate a string that contains the Property Definition for the
     internal header file.
     @param     this    object pointer
     @param     pClass  Class Name
     @param     pClassUC Uppercase Class Name
     @return    If successful, an AStr object which must be released containing the
                description, otherwise OBJ_NIL.
     @warning  Remember to release the returned AStr object.
     */
    ASTR_DATA *     PropItem_GenIntDefn (
        PROPITEM_DATA   *this,
        const
        char            *pClass,
        const
        char            *pClassUC
    );


    /*!
     Generate a string that contains the Property Definition for the
     internal header file variable definition.
     @param     this    object pointer
     @param     pClass  Class Name
     @param     pClassUC Uppercase Class Name
     @return    If successful, an AStr object which must be released containing the
                description, otherwise OBJ_NIL.
     @warning  Remember to release the returned AStr object.
     */
    ASTR_DATA *     PropItem_GenIntVar (
        PROPITEM_DATA   *this,
        const
        char            *pClass,
        const
        char            *pClassUC
    );


    PROPITEM_DATA * PropItem_Init (
        PROPITEM_DATA   *this
    );


    ERESULT         PropItem_IsEnabled (
        PROPITEM_DATA   *this
    );
    
 
#ifdef  PROPITEM_JSON_SUPPORT
    /*!
     Create a string that describes this object and the objects within it in
     HJSON formt. (See hjson object for details.)
     Example:
     @code
     ASTR_DATA      *pDesc = PropItem_ToJson(this);
     @endcode
     @param     this    object pointer
     @return    If successful, an AStr object which must be released containing the
                JSON text, otherwise OBJ_NIL.
     @warning   Remember to release the returned AStr object.
     */
    ASTR_DATA *     PropItem_ToJson (
        PROPITEM_DATA   *this
    );
#endif


    /*!
     Create a string that describes this object and the objects within it.
     Example:
     @code 
        ASTR_DATA      *pDesc = PropItem_ToDebugString(this,4);
     @endcode 
     @param     this    object pointer
     @param     indent  number of characters to indent every line of output, can be 0
     @return    If successful, an AStr object which must be released containing the
                description, otherwise OBJ_NIL.
     @warning   Remember to release the returned AStr object.
     */
    ASTR_DATA *     PropItem_ToDebugString (
        PROPITEM_DATA   *this,
        int             indent
    );
    
    

    
#ifdef  __cplusplus
}
#endif

#endif  /* PROPITEM_H */

