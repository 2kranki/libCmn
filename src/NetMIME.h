// vi:nu:et:sts=4 ts=4 sw=4

//****************************************************************
//                  Network MIME Support (NetMIME) Header
//****************************************************************
/*
 * Program
 *          Network MIME Support (NetMIME)
 * Purpose
 *          This object provides a standardized way of handling
 *          a separate NetMIME to run things without complications
 *          of interfering with the main NetMIME. A NetMIME may be 
 *          called a NetMIME on other O/S's.
 *
 * Remarks
 *  1.      None
 *
 * History
 *  07/02/2021 Generated
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


#ifndef         NETMIME_H
#define         NETMIME_H


//#define   NETMIME_IS_IMMUTABLE     1
//#define   NETMIME_JSON_SUPPORT     1
//#define   NETMIME_SINGLETON        1





#ifdef  __cplusplus
extern "C" {
#endif
    

    //****************************************************************
    //* * * * * * * * * * * *  Data Definitions  * * * * * * * * * * *
    //****************************************************************


    typedef struct NetMIME_data_s  NETMIME_DATA;            // Inherits from OBJ
    typedef struct NetMIME_class_data_s NETMIME_CLASS_DATA;   // Inherits from OBJ

    typedef struct NetMIME_vtbl_s  {
        OBJ_IUNKNOWN    iVtbl;              // Inherited Vtbl.
        // Put other methods below this as pointers and add their
        // method names to the vtbl definition in NetMIME_object.c.
        // Properties:
        // Methods:
        //bool        (*pIsEnabled)(NETMIME_DATA *);
    } NETMIME_VTBL;

    typedef struct NetMIME_class_vtbl_s    {
        OBJ_IUNKNOWN    iVtbl;              // Inherited Vtbl.
        // Put other methods below this as pointers and add their
        // method names to the vtbl definition in NetMIME_object.c.
        // Properties:
        // Methods:
        //bool        (*pIsEnabled)(NETMIME_DATA *);
    } NETMIME_CLASS_VTBL;




    /****************************************************************
    * * * * * * * * * * *  Routine Definitions  * * * * * * * * * * *
    ****************************************************************/


    //---------------------------------------------------------------
    //                      *** Class Methods ***
    //---------------------------------------------------------------

#ifdef  NETMIME_SINGLETON
    NETMIME_DATA *     NetMIME_Shared (
        void
    );

    void            NetMIME_SharedReset (
        void
    );
#endif


   /*!
     Allocate a new Object and partially initialize. Also, this sets an
     indicator that the object was alloc'd which is tested when the object is
     released.
     @return    pointer to NetMIME object if successful, otherwise OBJ_NIL.
     */
    NETMIME_DATA *     NetMIME_Alloc (
        void
    );
    
    
    OBJ_ID          NetMIME_Class (
        void
    );
    
    
    NETMIME_DATA *     NetMIME_New (
        void
    );
    
    
#ifdef  NETMIME_JSON_SUPPORT
    NETMIME_DATA *   NetMIME_NewFromJsonString (
        ASTR_DATA       *pString
    );

    NETMIME_DATA *   NetMIME_NewFromJsonStringA (
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

    ERESULT     NetMIME_Disable (
        NETMIME_DATA       *this
    );


    ERESULT     NetMIME_Enable (
        NETMIME_DATA       *this
    );

   
    NETMIME_DATA *   NetMIME_Init (
        NETMIME_DATA     *this
    );


    ERESULT     NetMIME_IsEnabled (
        NETMIME_DATA       *this
    );
    
 
#ifdef  NETMIME_JSON_SUPPORT
    /*!
     Create a string that describes this object and the objects within it in
     HJSON formt. (See hjson object for details.)
     Example:
     @code
     ASTR_DATA      *pDesc = NetMIME_ToJson(this);
     @endcode
     @param     this    object pointer
     @return    If successful, an AStr object which must be released containing the
                JSON text, otherwise OBJ_NIL.
     @warning   Remember to release the returned AStr object.
     */
    ASTR_DATA *     NetMIME_ToJson (
        NETMIME_DATA   *this
    );
#endif


    /*!
     Create a string that describes this object and the objects within it.
     Example:
     @code 
        ASTR_DATA      *pDesc = NetMIME_ToDebugString(this,4);
     @endcode 
     @param     this    object pointer
     @param     indent  number of characters to indent every line of output, can be 0
     @return    If successful, an AStr object which must be released containing the
                description, otherwise OBJ_NIL.
     @warning   Remember to release the returned AStr object.
     */
    ASTR_DATA *     NetMIME_ToDebugString (
        NETMIME_DATA     *this,
        int             indent
    );
    
    

    
#ifdef  __cplusplus
}
#endif

#endif  /* NETMIME_H */

