// vi:nu:et:sts=4 ts=4 sw=4

//****************************************************************
//          TCP/IP Network HTTP Request (NetHTTPR) Header
//****************************************************************
/*
 * Program
 *          TCP/IP Network HTTP Request (NetHTTPR)
 * Purpose
 *          This object provides a standardized way of handling
 *          a separate NetHTTPR to run things without complications
 *          of interfering with the main NetHTTPR. A NetHTTPR may be 
 *          called a NetHTTPR on other O/S's.
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


#ifndef         NETHTTPR_H
#define         NETHTTPR_H


//#define   NETHTTPR_IS_IMMUTABLE     1
#define   NETHTTPR_JSON_SUPPORT       1
//#define   NETHTTPR_SINGLETON        1





#ifdef  __cplusplus
extern "C" {
#endif
    

    //****************************************************************
    //* * * * * * * * * * * *  Data Definitions  * * * * * * * * * * *
    //****************************************************************


    typedef struct NetHTTPR_data_s  NETHTTPR_DATA;            // Inherits from OBJ
    typedef struct NetHTTPR_class_data_s NETHTTPR_CLASS_DATA;   // Inherits from OBJ

    typedef struct NetHTTPR_vtbl_s  {
        OBJ_IUNKNOWN    iVtbl;              // Inherited Vtbl.
        // Put other methods below this as pointers and add their
        // method names to the vtbl definition in NetHTTPR_object.c.
        // Properties:
        // Methods:
        //bool        (*pIsEnabled)(NETHTTPR_DATA *);
    } NETHTTPR_VTBL;

    typedef struct NetHTTPR_class_vtbl_s    {
        OBJ_IUNKNOWN    iVtbl;              // Inherited Vtbl.
        // Put other methods below this as pointers and add their
        // method names to the vtbl definition in NetHTTPR_object.c.
        // Properties:
        // Methods:
        //bool        (*pIsEnabled)(NETHTTPR_DATA *);
    } NETHTTPR_CLASS_VTBL;


    typedef enum NetHTTPR_cmds_e    {
        NETHTTPR_CMD_UNKNOWN=0,
        NETHTTPR_CMD_CONNECT,
        NETHTTPR_CMD_DELETE,
        NETHTTPR_CMD_GET,
        NETHTTPR_CMD_HEAD,
        NETHTTPR_CMD_OPTIONS,
        NETHTTPR_CMD_POST,
        NETHTTPR_CMD_PUT,
        NETHTTPR_CMD_TRACE,
    } NETHTTPR_CMDS;




    /****************************************************************
    * * * * * * * * * * *  Routine Definitions  * * * * * * * * * * *
    ****************************************************************/


    //---------------------------------------------------------------
    //                      *** Class Methods ***
    //---------------------------------------------------------------

#ifdef  NETHTTPR_SINGLETON
    NETHTTPR_DATA * NetHTTPR_Shared (
        void
    );

    void            NetHTTPR_SharedReset (
        void
    );
#endif


   /*!
     Allocate a new Object and partially initialize. Also, this sets an
     indicator that the object was alloc'd which is tested when the object is
     released.
     @return    pointer to NetHTTPR object if successful, otherwise OBJ_NIL.
     */
    NETHTTPR_DATA * NetHTTPR_Alloc (
        void
    );
    
    
    OBJ_ID          NetHTTPR_Class (
        void
    );
    
    
    NETHTTPR_DATA * NetHTTPR_New (
        void
    );
    
    
#ifdef  NETHTTPR_JSON_SUPPORT
    NETHTTPR_DATA * NetHTTPR_NewFromJsonString (
        ASTR_DATA       *pString
    );

    NETHTTPR_DATA * NetHTTPR_NewFromJsonStringA (
        const
        char            *pStringA
    );
#endif



    //---------------------------------------------------------------
    //                      *** Properties ***
    //---------------------------------------------------------------

    ASTR_DATA *     NetHTTPR_getBody (
        NETHTTPR_DATA   *this
    );



    /*! @property HTTP Major Release
     */
    uint16_t        NetHTTPR_getMajorRelease (
        NETHTTPR_DATA   *this
    );

    bool            NetHTTPR_setMajorRelease (
        NETHTTPR_DATA   *this,
        uint16_t        value
    );


    /*! @property HTTP Minor Release
    */
    uint16_t        NetHTTPR_getMinorRelease (
        NETHTTPR_DATA   *this
    );

    bool            NetHTTPR_setMinorRelease (
        NETHTTPR_DATA   *this,
        uint16_t        value
    );



    //---------------------------------------------------------------
    //                      *** Methods ***
    //---------------------------------------------------------------

    ERESULT         NetHTTPR_Disable (
        NETHTTPR_DATA   *this
    );


    ERESULT         NetHTTPR_Enable (
        NETHTTPR_DATA   *this
    );

   
    NETHTTPR_DATA * NetHTTPR_Init (
        NETHTTPR_DATA   *this
    );


    ERESULT         NetHTTPR_IsEnabled (
        NETHTTPR_DATA   *this
    );
    
 
    ERESULT         NetHTTPR_Parse (
        NETHTTPR_DATA   *this,
        ASTR_DATA       *pStr
    );


#ifdef  NETHTTPR_JSON_SUPPORT
    /*!
     Create a string that describes this object and the objects within it in
     HJSON formt. (See hjson object for details.)
     Example:
     @code
     ASTR_DATA      *pDesc = NetHTTPR_ToJson(this);
     @endcode
     @param     this    object pointer
     @return    If successful, an AStr object which must be released containing the
                JSON text, otherwise OBJ_NIL.
     @warning   Remember to release the returned AStr object.
     */
    ASTR_DATA *     NetHTTPR_ToJson (
        NETHTTPR_DATA   *this
    );
#endif


    /*!
     Create a string that describes this object and the objects within it.
     Example:
     @code 
        ASTR_DATA      *pDesc = NetHTTPR_ToDebugString(this,4);
     @endcode 
     @param     this    object pointer
     @param     indent  number of characters to indent every line of output, can be 0
     @return    If successful, an AStr object which must be released containing the
                description, otherwise OBJ_NIL.
     @warning   Remember to release the returned AStr object.
     */
    ASTR_DATA *     NetHTTPR_ToDebugString (
        NETHTTPR_DATA     *this,
        int             indent
    );
    
    

    
#ifdef  __cplusplus
}
#endif

#endif  /* NETHTTPR_H */

