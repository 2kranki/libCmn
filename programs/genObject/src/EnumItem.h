// vi:nu:et:sts=4 ts=4 sw=4

//****************************************************************
//                  Enumeration Item (EnumItem) Header
//****************************************************************
/*
 * Program
 *          Enumeration Item (EnumItem)
 * Purpose
 *          This object provides a standardized way of handling
 *          a separate EnumItem to run things without complications
 *          of interfering with the main EnumItem. A EnumItem may be 
 *          called a EnumItem on other O/S's.
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


#ifndef         ENUMITEM_H
#define         ENUMITEM_H


//#define   ENUMITEM_IS_IMMUTABLE     1
#define   ENUMITEM_JSON_SUPPORT       1
//#define   ENUMITEM_SINGLETON        1
//#define       ENUMITEM_MSGS   1





#ifdef  __cplusplus
extern "C" {
#endif
    

    //****************************************************************
    //* * * * * * * * * * * *  Data Definitions  * * * * * * * * * * *
    //****************************************************************


    typedef struct EnumItem_data_s  ENUMITEM_DATA;          // Inherits from ENUMITEM
    typedef struct EnumItem_class_data_s ENUMITEM_CLASS_DATA;  // Inherits from OBJ

    typedef struct EnumItem_vtbl_s  {
        OBJ_IUNKNOWN    iVtbl;              // Inherited Vtbl.
        //EnumItem_VTBL    iVtbl;              // Inherited Vtbl.
        // Put other methods below this as pointers and add their
        // method names to the vtbl definition in EnumItem_object.c.
        // Properties:
        // Methods:
        //bool        (*pIsEnabled)(ENUMITEM_DATA *);
    } ENUMITEM_VTBL;

    typedef struct EnumItem_class_vtbl_s    {
        OBJ_IUNKNOWN    iVtbl;              // Inherited Vtbl.
        // Put other methods below this as pointers and add their
        // method names to the vtbl definition in EnumItem_object.c.
        // Properties:
        // Methods:
        //bool        (*pIsEnabled)(ENUMITEM_DATA *);
    } ENUMITEM_CLASS_VTBL;




    /****************************************************************
    * * * * * * * * * * *  Routine Definitions  * * * * * * * * * * *
    ****************************************************************/


    //---------------------------------------------------------------
    //                      *** Class Methods ***
    //---------------------------------------------------------------

#ifdef  ENUMITEM_SINGLETON
    ENUMITEM_DATA *     EnumItem_Shared (
        void
    );

    void            EnumItem_SharedReset (
        void
    );
#endif


   /*!
     Allocate a new Object and partially initialize. Also, this sets an
     indicator that the object was alloc'd which is tested when the object is
     released.
     @return    pointer to EnumItem object if successful, otherwise OBJ_NIL.
     */
    ENUMITEM_DATA *     EnumItem_Alloc (
        void
    );
    
    
    OBJ_ID          EnumItem_Class (
        void
    );
    
    
    ENUMITEM_DATA *     EnumItem_New (
        void
    );
    
    
#ifdef  ENUMITEM_JSON_SUPPORT
    ENUMITEM_DATA *   EnumItem_NewFromJsonString (
        ASTR_DATA       *pString
    );

    ENUMITEM_DATA *   EnumItem_NewFromJsonStringA (
        const
        char            *pStringA
    );
#endif



    //---------------------------------------------------------------
    //                      *** Properties ***
    //---------------------------------------------------------------

#ifdef ENUMITEM_MSGS
    /*! @property   Messages
        Allows information and warning messages to be issued.
     */
    bool            EnumItem_setMsgs (
        ENUMITEM_DATA    *this,
        void            (*pMsgInfo)(OBJ_ID, const char *, ...),
        void            (*pMsgWarn)(OBJ_ID, uint16_t, const char *, ...),
        OBJ_ID          pObj
    );
#endif


    
    //---------------------------------------------------------------
    //                      *** Methods ***
    //---------------------------------------------------------------

    ERESULT     EnumItem_Disable (
        ENUMITEM_DATA       *this
    );


    ERESULT     EnumItem_Enable (
        ENUMITEM_DATA       *this
    );

   
    ENUMITEM_DATA *   EnumItem_Init (
        ENUMITEM_DATA     *this
    );


    ERESULT     EnumItem_IsEnabled (
        ENUMITEM_DATA       *this
    );
    
 
#ifdef  ENUMITEM_JSON_SUPPORT
    /*!
     Create a string that describes this object and the objects within it in
     HJSON formt. (See hjson object for details.)
     Example:
     @code
     ASTR_DATA      *pDesc = EnumItem_ToJson(this);
     @endcode
     @param     this    object pointer
     @return    If successful, an AStr object which must be released containing the
                JSON text, otherwise OBJ_NIL.
     @warning   Remember to release the returned AStr object.
     */
    ASTR_DATA *     EnumItem_ToJson (
        ENUMITEM_DATA   *this
    );
#endif


    /*!
     Create a string that describes this object and the objects within it.
     Example:
     @code 
        ASTR_DATA      *pDesc = EnumItem_ToDebugString(this,4);
     @endcode 
     @param     this    object pointer
     @param     indent  number of characters to indent every line of output, can be 0
     @return    If successful, an AStr object which must be released containing the
                description, otherwise OBJ_NIL.
     @warning   Remember to release the returned AStr object.
     */
    ASTR_DATA *     EnumItem_ToDebugString (
        ENUMITEM_DATA     *this,
        int             indent
    );
    
    

    
#ifdef  __cplusplus
}
#endif

#endif  /* ENUMITEM_H */

