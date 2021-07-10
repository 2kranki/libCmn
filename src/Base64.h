// vi:nu:et:sts=4 ts=4 sw=4

//****************************************************************
//                  Base64 Encoding/Decoding (Base64) Header
//****************************************************************
/*
 * Program
 *          Base64 Encoding/Decoding (Base64)
 * Purpose
 *          This object provides support to encode bytes of data
 *          into a Base64 string and to decode the same.  This is
 *          primarily used in MIME data transfer.
 *
 * Remarks
 *  1.      None
 *
 * History
 *  07/08/2021 Generated
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
#include        <u8Array.h>
#include        <AStr.h>


#ifndef         BASE64_H
#define         BASE64_H


//#define   BASE64_IS_IMMUTABLE     1
//#define   BASE64_JSON_SUPPORT     1
//#define   BASE64_SINGLETON        1





#ifdef  __cplusplus
extern "C" {
#endif
    

    //****************************************************************
    //* * * * * * * * * * * *  Data Definitions  * * * * * * * * * * *
    //****************************************************************


    typedef struct Base64_data_s  BASE64_DATA;            // Inherits from OBJ
    typedef struct Base64_class_data_s BASE64_CLASS_DATA;   // Inherits from OBJ

    typedef struct Base64_vtbl_s  {
        OBJ_IUNKNOWN    iVtbl;              // Inherited Vtbl.
        // Put other methods below this as pointers and add their
        // method names to the vtbl definition in Base64_object.c.
        // Properties:
        // Methods:
        //bool        (*pIsEnabled)(BASE64_DATA *);
    } BASE64_VTBL;

    typedef struct Base64_class_vtbl_s    {
        OBJ_IUNKNOWN    iVtbl;              // Inherited Vtbl.
        // Put other methods below this as pointers and add their
        // method names to the vtbl definition in Base64_object.c.
        // Properties:
        // Methods:
        //bool        (*pIsEnabled)(BASE64_DATA *);
    } BASE64_CLASS_VTBL;




    /****************************************************************
    * * * * * * * * * * *  Routine Definitions  * * * * * * * * * * *
    ****************************************************************/


    //---------------------------------------------------------------
    //                      *** Class Methods ***
    //---------------------------------------------------------------

#ifdef  BASE64_SINGLETON
    BASE64_DATA *   Base64_Shared (
        void
    );

    void            Base64_SharedReset (
        void
    );
#endif


   /*!
     Allocate a new Object and partially initialize. Also, this sets an
     indicator that the object was alloc'd which is tested when the object is
     released.
     @return    pointer to Base64 object if successful, otherwise OBJ_NIL.
     */
    BASE64_DATA *   Base64_Alloc (
        void
    );
    
    
    OBJ_ID          Base64_Class (
        void
    );
    
    
    BASE64_DATA *   Base64_New (
        void
    );
    
    
#ifdef  BASE64_JSON_SUPPORT
    BASE64_DATA *   Base64_NewFromJsonString (
        ASTR_DATA       *pString
    );

    BASE64_DATA *   Base64_NewFromJsonStringA (
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

    ERESULT         Base64_Disable (
        BASE64_DATA     *this
    );


    ERESULT         Base64_Enable (
        BASE64_DATA     *this
    );

   
    BASE64_DATA *   Base64_Init (
        BASE64_DATA     *this
    );


    ERESULT         Base64_IsEnabled (
        BASE64_DATA     *this
    );
    
 
#ifdef  BASE64_JSON_SUPPORT
    /*!
     Create a string that describes this object and the objects within it in
     HJSON formt. (See hjson object for details.)
     Example:
     @code
     ASTR_DATA      *pDesc = Base64_ToJson(this);
     @endcode
     @param     this    object pointer
     @return    If successful, an AStr object which must be released containing the
                JSON text, otherwise OBJ_NIL.
     @warning   Remember to release the returned AStr object.
     */
    ASTR_DATA *     Base64_ToJson (
        BASE64_DATA     *this
    );
#endif


    /*!
     Create a string that describes this object and the objects within it.
     Example:
     @code 
        ASTR_DATA      *pDesc = Base64_ToDebugString(this,4);
     @endcode 
     @param     this    object pointer
     @param     indent  number of characters to indent every line of output, can be 0
     @return    If successful, an AStr object which must be released containing the
                description, otherwise OBJ_NIL.
     @warning   Remember to release the returned AStr object.
     */
    ASTR_DATA *     Base64_ToDebugString (
        BASE64_DATA     *this,
        int             indent
    );
    
    

    
#ifdef  __cplusplus
}
#endif

#endif  /* BASE64_H */

