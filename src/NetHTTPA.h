// vi:nu:et:sts=4 ts=4 sw=4

//****************************************************************
//      TCP/IP Network HTTP Response/Answer (NetHTTPA) Header
//****************************************************************
/*
 * Program
 *          TCP/IP Network HTTP Response/Answer (NetHTTPA)
 * Purpose
 *          This object provides a standardized way of handling
 *          a separate NetHTTPA to run things without complications
 *          of interfering with the main NetHTTPA. A NetHTTPA may be 
 *          called a NetHTTPA on other O/S's.
 *
 * Remarks
 *  1.      None
 *
 * History
 *  07/07/2021 Generated
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
#include        <Value.h>


#ifndef         NETHTTPA_H
#define         NETHTTPA_H


//#define   NETHTTPA_IS_IMMUTABLE     1
#define   NETHTTPA_JSON_SUPPORT       1
//#define   NETHTTPA_SINGLETON        1





#ifdef  __cplusplus
extern "C" {
#endif
    

    //****************************************************************
    //* * * * * * * * * * * *  Data Definitions  * * * * * * * * * * *
    //****************************************************************


    typedef struct NetHTTPA_data_s  NETHTTPA_DATA;            // Inherits from OBJ
    typedef struct NetHTTPA_class_data_s NETHTTPA_CLASS_DATA;   // Inherits from OBJ

    typedef struct NetHTTPA_vtbl_s  {
        OBJ_IUNKNOWN    iVtbl;              // Inherited Vtbl.
        // Put other methods below this as pointers and add their
        // method names to the vtbl definition in NetHTTPA_object.c.
        // Properties:
        // Methods:
        //bool        (*pIsEnabled)(NETHTTPA_DATA *);
    } NETHTTPA_VTBL;

    typedef struct NetHTTPA_class_vtbl_s    {
        OBJ_IUNKNOWN    iVtbl;              // Inherited Vtbl.
        // Put other methods below this as pointers and add their
        // method names to the vtbl definition in NetHTTPA_object.c.
        // Properties:
        // Methods:
        //bool        (*pIsEnabled)(NETHTTPA_DATA *);
    } NETHTTPA_CLASS_VTBL;




    /****************************************************************
    * * * * * * * * * * *  Routine Definitions  * * * * * * * * * * *
    ****************************************************************/


    //---------------------------------------------------------------
    //                      *** Class Methods ***
    //---------------------------------------------------------------

#ifdef  NETHTTPA_SINGLETON
    NETHTTPA_DATA * NetHTTPA_Shared (
        void
    );

    void            NetHTTPA_SharedReset (
        void
    );
#endif


   /*!
     Allocate a new Object and partially initialize. Also, this sets an
     indicator that the object was alloc'd which is tested when the object is
     released.
     @return    pointer to NetHTTPA object if successful, otherwise OBJ_NIL.
     */
    NETHTTPA_DATA * NetHTTPA_Alloc (
        void
    );
    
    
    OBJ_ID          NetHTTPA_Class (
        void
    );
    
    
    NETHTTPA_DATA * NetHTTPA_New (
        void
    );
    
    
#ifdef  NETHTTPA_JSON_SUPPORT
    NETHTTPA_DATA * NetHTTPA_NewFromJsonString (
        ASTR_DATA       *pString
    );

    NETHTTPA_DATA * NetHTTPA_NewFromJsonStringA (
        const
        char            *pStringA
    );
#endif



    //---------------------------------------------------------------
    //                      *** Properties ***
    //---------------------------------------------------------------

    VALUE_DATA *    NetHTTPA_getBody (
        NETHTTPA_DATA   *this
    );

    bool            NetHTTPA_setBody (
        NETHTTPA_DATA   *this,
        VALUE_DATA      *pValue
    );


    /*! @property Response Code
     */
    uint16_t        NetHTTPA_getCode (
        NETHTTPA_DATA   *this
    );

    bool            NetHTTPA_setCode (
        NETHTTPA_DATA   *this,
        uint16_t        value
    );


    /*! @property HTTP Major Release
     */
    uint16_t        NetHTTPA_getMajorRelease (
        NETHTTPA_DATA   *this
    );

    bool            NetHTTPA_setMajorRelease (
        NETHTTPA_DATA   *this,
        uint16_t        value
    );


    ASTR_DATA *     NetHTTPA_getMimeType (
        NETHTTPA_DATA   *this
    );

    bool            NetHTTPA_setMimeType (
        NETHTTPA_DATA   *this,
        ASTR_DATA       *pValue
    );


    /*! @property HTTP Minor Release
     */
    uint16_t        NetHTTPA_getMinorRelease (
        NETHTTPA_DATA   *this
    );

    bool            NetHTTPA_setMinorRelease (
        NETHTTPA_DATA   *this,
        uint16_t        value
    );


    
    //---------------------------------------------------------------
    //                      *** Methods ***
    //---------------------------------------------------------------

    ERESULT         NetHTTPA_Disable (
        NETHTTPA_DATA   *this
    );


    ERESULT         NetHTTPA_Enable (
        NETHTTPA_DATA   *this
    );

   
    NETHTTPA_DATA * NetHTTPA_Init (
        NETHTTPA_DATA   *this
    );


    ERESULT         NetHTTPA_IsEnabled (
        NETHTTPA_DATA   *this
    );
    
 
    ERESULT         NetHTTPA_Parse (
        NETHTTPA_DATA   *this,
        ASTR_DATA       *pStr
    );


#ifdef  NETHTTPA_JSON_SUPPORT
    /*!
     Create a string that describes this object and the objects within it in
     HJSON formt. (See hjson object for details.)
     Example:
     @code
     ASTR_DATA      *pDesc = NetHTTPA_ToJson(this);
     @endcode
     @param     this    object pointer
     @return    If successful, an AStr object which must be released containing the
                JSON text, otherwise OBJ_NIL.
     @warning   Remember to release the returned AStr object.
     */
    ASTR_DATA *     NetHTTPA_ToJson (
        NETHTTPA_DATA   *this
    );
#endif


    /*!
     Create a string that describes this object and the objects within it.
     Example:
     @code 
        ASTR_DATA      *pDesc = NetHTTPA_ToDebugString(this,4);
     @endcode 
     @param     this    object pointer
     @param     indent  number of characters to indent every line of output, can be 0
     @return    If successful, an AStr object which must be released containing the
                description, otherwise OBJ_NIL.
     @warning   Remember to release the returned AStr object.
     */
    ASTR_DATA *     NetHTTPA_ToDebugString (
        NETHTTPA_DATA   *this,
        int             indent
    );
    
    

    
#ifdef  __cplusplus
}
#endif

#endif  /* NETHTTPA_H */

