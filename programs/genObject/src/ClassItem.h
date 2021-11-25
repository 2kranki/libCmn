// vi:nu:et:sts=4 ts=4 sw=4

//****************************************************************
//                  Class Item (ClassItem) Header
//****************************************************************
/*
 * Program
 *          Class Item (ClassItem)
 * Purpose
 *          This object provides a standardized way of handling
 *          a separate ClassItem to run things without complications
 *          of interfering with the main ClassItem. A ClassItem may be 
 *          called a ClassItem on other O/S's.
 *
 * Remarks
 *  1.      None
 *
 * History
 *  11/23/2021 Generated
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


#ifndef         CLASSITEM_H
#define         CLASSITEM_H


//#define   CLASSITEM_IS_IMMUTABLE     1
#define   CLASSITEM_JSON_SUPPORT       1
//#define   CLASSITEM_SINGLETON        1
//#define       CLASSITEM_MSGS   1





#ifdef  __cplusplus
extern "C" {
#endif
    

    //****************************************************************
    //* * * * * * * * * * * *  Data Definitions  * * * * * * * * * * *
    //****************************************************************


    typedef struct ClassItem_data_s  CLASSITEM_DATA;          // Inherits from CLASSITEM
    typedef struct ClassItem_class_data_s CLASSITEM_CLASS_DATA;  // Inherits from OBJ

    typedef struct ClassItem_vtbl_s  {
        OBJ_IUNKNOWN    iVtbl;              // Inherited Vtbl.
        //ClassItem_VTBL    iVtbl;              // Inherited Vtbl.
        // Put other methods below this as pointers and add their
        // method names to the vtbl definition in ClassItem_object.c.
        // Properties:
        // Methods:
        //bool        (*pIsEnabled)(CLASSITEM_DATA *);
    } CLASSITEM_VTBL;

    typedef struct ClassItem_class_vtbl_s    {
        OBJ_IUNKNOWN    iVtbl;              // Inherited Vtbl.
        // Put other methods below this as pointers and add their
        // method names to the vtbl definition in ClassItem_object.c.
        // Properties:
        // Methods:
        //bool        (*pIsEnabled)(CLASSITEM_DATA *);
    } CLASSITEM_CLASS_VTBL;




    /****************************************************************
    * * * * * * * * * * *  Routine Definitions  * * * * * * * * * * *
    ****************************************************************/


    //---------------------------------------------------------------
    //                      *** Class Methods ***
    //---------------------------------------------------------------

#ifdef  CLASSITEM_SINGLETON
    CLASSITEM_DATA *     ClassItem_Shared (
        void
    );

    void            ClassItem_SharedReset (
        void
    );
#endif


   /*!
     Allocate a new Object and partially initialize. Also, this sets an
     indicator that the object was alloc'd which is tested when the object is
     released.
     @return    pointer to ClassItem object if successful, otherwise OBJ_NIL.
     */
    CLASSITEM_DATA *     ClassItem_Alloc (
        void
    );
    
    
    OBJ_ID          ClassItem_Class (
        void
    );
    
    
    CLASSITEM_DATA *     ClassItem_New (
        void
    );
    
    
#ifdef  CLASSITEM_JSON_SUPPORT
    CLASSITEM_DATA *   ClassItem_NewFromJsonString (
        ASTR_DATA       *pString
    );

    CLASSITEM_DATA *   ClassItem_NewFromJsonStringA (
        const
        char            *pStringA
    );
#endif



    //---------------------------------------------------------------
    //                      *** Properties ***
    //---------------------------------------------------------------

#ifdef CLASSITEM_MSGS
    /*! @property   Messages
        Allows information and warning messages to be issued.
     */
    bool            ClassItem_setMsgs (
        CLASSITEM_DATA    *this,
        void            (*pMsgInfo)(OBJ_ID, const char *, ...),
        void            (*pMsgWarn)(OBJ_ID, uint16_t, const char *, ...),
        OBJ_ID          pObj
    );
#endif


    
    //---------------------------------------------------------------
    //                      *** Methods ***
    //---------------------------------------------------------------

    ERESULT     ClassItem_Disable (
        CLASSITEM_DATA       *this
    );


    ERESULT     ClassItem_Enable (
        CLASSITEM_DATA       *this
    );

   
    CLASSITEM_DATA *   ClassItem_Init (
        CLASSITEM_DATA     *this
    );


    ERESULT     ClassItem_IsEnabled (
        CLASSITEM_DATA       *this
    );
    
 
#ifdef  CLASSITEM_JSON_SUPPORT
    /*!
     Create a string that describes this object and the objects within it in
     HJSON formt. (See hjson object for details.)
     Example:
     @code
     ASTR_DATA      *pDesc = ClassItem_ToJson(this);
     @endcode
     @param     this    object pointer
     @return    If successful, an AStr object which must be released containing the
                JSON text, otherwise OBJ_NIL.
     @warning   Remember to release the returned AStr object.
     */
    ASTR_DATA *     ClassItem_ToJson (
        CLASSITEM_DATA   *this
    );
#endif


    /*!
     Create a string that describes this object and the objects within it.
     Example:
     @code 
        ASTR_DATA      *pDesc = ClassItem_ToDebugString(this,4);
     @endcode 
     @param     this    object pointer
     @param     indent  number of characters to indent every line of output, can be 0
     @return    If successful, an AStr object which must be released containing the
                description, otherwise OBJ_NIL.
     @warning   Remember to release the returned AStr object.
     */
    ASTR_DATA *     ClassItem_ToDebugString (
        CLASSITEM_DATA     *this,
        int             indent
    );
    
    

    
#ifdef  __cplusplus
}
#endif

#endif  /* CLASSITEM_H */

