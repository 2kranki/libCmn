// vi:nu:et:sts=4 ts=4 sw=4

//****************************************************************
//        Network I/O using Unix Sockets (NetIO) Header
//****************************************************************
/*
 * Program
 *          Network I/O using Unix Sockets (NetIO)
 * Purpose
 *          This object is designed to be run in its own thread
 *          to perform I/O on a TCP/IP Socket. If run in server
 *          mode, it issues an accept() followed by one or more
 *          recv() functions.  It also provides hooks for the
 *          HTTP object to use it for its I/O.
 *
 * Remarks
 *  1.      NetIO uses OBJ_FLAG_USER1.
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


#ifndef         NETIO_H
#define         NETIO_H


//#define   NETIO_IS_IMMUTABLE     1
//#define   NETIO_JSON_SUPPORT     1
//#define   NETIO_SINGLETON        1





#ifdef  __cplusplus
extern "C" {
#endif
    

    //****************************************************************
    //* * * * * * * * * * * *  Data Definitions  * * * * * * * * * * *
    //****************************************************************


    typedef struct NetIO_data_s  NETIO_DATA;            // Inherits from OBJ
    typedef struct NetIO_class_data_s NETIO_CLASS_DATA;   // Inherits from OBJ

    typedef struct NetIO_vtbl_s  {
        OBJ_IUNKNOWN    iVtbl;              // Inherited Vtbl.
        // Put other methods below this as pointers and add their
        // method names to the vtbl definition in NetIO_object.c.
        // Properties:
        // Methods:
        //bool        (*pIsEnabled)(NETIO_DATA *);
    } NETIO_VTBL;

    typedef struct NetIO_class_vtbl_s    {
        OBJ_IUNKNOWN    iVtbl;              // Inherited Vtbl.
        // Put other methods below this as pointers and add their
        // method names to the vtbl definition in NetIO_object.c.
        // Properties:
        // Methods:
        //bool        (*pIsEnabled)(NETIO_DATA *);
    } NETIO_CLASS_VTBL;




    /****************************************************************
    * * * * * * * * * * *  Routine Definitions  * * * * * * * * * * *
    ****************************************************************/


    //---------------------------------------------------------------
    //                      *** Class Methods ***
    //---------------------------------------------------------------

#ifdef  NETIO_SINGLETON
    NETIO_DATA *     NetIO_Shared (
        void
    );

    void            NetIO_SharedReset (
        void
    );
#endif


   /*!
     Allocate a new Object and partially initialize. Also, this sets an
     indicator that the object was alloc'd which is tested when the object is
     released.
     @return    pointer to NetIO object if successful, otherwise OBJ_NIL.
     */
    NETIO_DATA *     NetIO_Alloc (
        void
    );
    
    
    OBJ_ID          NetIO_Class (
        void
    );
    
    
    NETIO_DATA *     NetIO_New (
        void
    );
    
    
#ifdef  NETIO_JSON_SUPPORT
    NETIO_DATA *   NetIO_NewFromJsonString (
        ASTR_DATA       *pString
    );

    NETIO_DATA *   NetIO_NewFromJsonStringA (
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

    ERESULT     NetIO_Disable (
        NETIO_DATA       *this
    );


    ERESULT     NetIO_Enable (
        NETIO_DATA       *this
    );

   
    NETIO_DATA *   NetIO_Init (
        NETIO_DATA     *this
    );


    ERESULT     NetIO_IsEnabled (
        NETIO_DATA       *this
    );
    
 
    /*!
     Open a Network connection using Unix Sockets for 2-way communication.
     @param     this    object pointer
     @return    if successful, ERESULT_SUCCESS.  Otherwise, an ERESULT_*
                error code.
     */
    ERESULT         NetIO_Open (
        NETIO_DATA      *this
    );


#ifdef  NETIO_JSON_SUPPORT
    /*!
     Create a string that describes this object and the objects within it in
     HJSON formt. (See hjson object for details.)
     Example:
     @code
     ASTR_DATA      *pDesc = NetIO_ToJson(this);
     @endcode
     @param     this    object pointer
     @return    If successful, an AStr object which must be released containing the
                JSON text, otherwise OBJ_NIL.
     @warning   Remember to release the returned AStr object.
     */
    ASTR_DATA *     NetIO_ToJson (
        NETIO_DATA   *this
    );
#endif


    /*!
     Create a string that describes this object and the objects within it.
     Example:
     @code 
        ASTR_DATA      *pDesc = NetIO_ToDebugString(this,4);
     @endcode 
     @param     this    object pointer
     @param     indent  number of characters to indent every line of output, can be 0
     @return    If successful, an AStr object which must be released containing the
                description, otherwise OBJ_NIL.
     @warning   Remember to release the returned AStr object.
     */
    ASTR_DATA *     NetIO_ToDebugString (
        NETIO_DATA     *this,
        int             indent
    );
    
    

    
#ifdef  __cplusplus
}
#endif

#endif  /* NETIO_H */

