// vi:nu:et:sts=4 ts=4 sw=4

//****************************************************************
//               TCP/IP Network Support (Net) Header
//****************************************************************
/*
 * Program
 *          TCP/IP Network Support (Net)
 * Purpose
 *          This object provides the primary interface to creating
 *          a TCP/IP Server/Client.  It is designed to work with
 *          several submodules:
 *              NetHTTP  - Network HTTP Support
 *              NetHTTPA - TCP/IP Network HTTP Response/Answer
 *              NetHTTPR - TCP/IP Network HTTP Request
 *              NetIO    - Network I/O using Unix Sockets
 *              NetMIME  - Network MIME Support
 *
 * Remarks
 *  1.      None
 *
 * References
 *  1.      "Advanced Programming in the UNIX Environment, 3rd Edition",
 *          W. Stevens, Addison-Wesley Professional, 2013
 *  2.      "Beej Guide to Network Programming",
 *          http://beej.us/guide/bgnet/
 *
 * History
 *  07/03/2021 Generated
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


#ifndef         NET_H
#define         NET_H


//#define   NET_IS_IMMUTABLE     1
//#define   NET_JSON_SUPPORT     1
//#define   NET_SINGLETON        1





#ifdef  __cplusplus
extern "C" {
#endif
    

    //****************************************************************
    //* * * * * * * * * * * *  Data Definitions  * * * * * * * * * * *
    //****************************************************************


    typedef struct Net_data_s  NET_DATA;            // Inherits from OBJ
    typedef struct Net_class_data_s NET_CLASS_DATA;   // Inherits from OBJ

    typedef struct Net_vtbl_s  {
        OBJ_IUNKNOWN    iVtbl;              // Inherited Vtbl.
        // Put other methods below this as pointers and add their
        // method names to the vtbl definition in Net_object.c.
        // Properties:
        // Methods:
        //bool        (*pIsEnabled)(NET_DATA *);
    } NET_VTBL;

    typedef struct Net_class_vtbl_s    {
        OBJ_IUNKNOWN    iVtbl;              // Inherited Vtbl.
        // Put other methods below this as pointers and add their
        // method names to the vtbl definition in Net_object.c.
        // Properties:
        // Methods:
        //bool        (*pIsEnabled)(NET_DATA *);
    } NET_CLASS_VTBL;




    /****************************************************************
    * * * * * * * * * * *  Routine Definitions  * * * * * * * * * * *
    ****************************************************************/


    //---------------------------------------------------------------
    //                      *** Class Methods ***
    //---------------------------------------------------------------

#ifdef  NET_SINGLETON
    NET_DATA *      Net_Shared (
        void
    );

    void            Net_SharedReset (
        void
    );
#endif


   /*!
     Allocate a new Object and partially initialize. Also, this sets an
     indicator that the object was alloc'd which is tested when the object is
     released.
     @return    pointer to Net object if successful, otherwise OBJ_NIL.
     */
    NET_DATA *      Net_Alloc (
        void
    );
    
    
    OBJ_ID          Net_Class (
        void
    );
    
    
    NET_DATA *      Net_New (
        void
    );
    
    
#ifdef  NET_JSON_SUPPORT
    NET_DATA *      Net_NewFromJsonString (
        ASTR_DATA       *pString
    );

    NET_DATA *      Net_NewFromJsonStringA (
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

    ERESULT         Net_Disable (
        NET_DATA        *this
    );


    ERESULT         Net_Enable (
        NET_DATA        *this
    );

   
    NET_DATA *      Net_Init (
        NET_DATA        *this
    );


    ERESULT         Net_IsEnabled (
        NET_DATA        *this
    );
    
 
#ifdef  NET_JSON_SUPPORT
    /*!
     Create a string that describes this object and the objects within it in
     HJSON formt. (See hjson object for details.)
     Example:
     @code
     ASTR_DATA      *pDesc = Net_ToJson(this);
     @endcode
     @param     this    object pointer
     @return    If successful, an AStr object which must be released containing the
                JSON text, otherwise OBJ_NIL.
     @warning   Remember to release the returned AStr object.
     */
    ASTR_DATA *     Net_ToJson (
        NET_DATA        *this
    );
#endif


    /*!
     Create a string that describes this object and the objects within it.
     Example:
     @code 
        ASTR_DATA      *pDesc = Net_ToDebugString(this,4);
     @endcode 
     @param     this    object pointer
     @param     indent  number of characters to indent every line of output, can be 0
     @return    If successful, an AStr object which must be released containing the
                description, otherwise OBJ_NIL.
     @warning   Remember to release the returned AStr object.
     */
    ASTR_DATA *     Net_ToDebugString (
        NET_DATA        *this,
        int             indent
    );
    
    

    
#ifdef  __cplusplus
}
#endif

#endif  /* NET_H */

