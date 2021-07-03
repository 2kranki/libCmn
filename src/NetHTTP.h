// vi:nu:et:sts=4 ts=4 sw=4

//****************************************************************
//                Network HTTP Support (NetHTTP) Header
//****************************************************************
/*
 * Program
 *          Network HTTP Support (NetHTTP)
 * Purpose
 *          This object provides a standardized way of handling
 *          a separate NetHTTP to run things without complications
 *          of interfering with the main NetHTTP. A NetHTTP may be 
 *          called a NetHTTP on other O/S's.
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


#ifndef         NETHTTP_H
#define         NETHTTP_H


//#define   NETHTTP_IS_IMMUTABLE     1
//#define   NETHTTP_JSON_SUPPORT     1
//#define   NETHTTP_SINGLETON        1





#ifdef  __cplusplus
extern "C" {
#endif
    

    //****************************************************************
    //* * * * * * * * * * * *  Data Definitions  * * * * * * * * * * *
    //****************************************************************


    typedef struct NetHTTP_data_s  NETHTTP_DATA;            // Inherits from OBJ
    typedef struct NetHTTP_class_data_s NETHTTP_CLASS_DATA;   // Inherits from OBJ

    typedef struct NetHTTP_vtbl_s  {
        OBJ_IUNKNOWN    iVtbl;              // Inherited Vtbl.
        // Put other methods below this as pointers and add their
        // method names to the vtbl definition in NetHTTP_object.c.
        // Properties:
        // Methods:
        //bool        (*pIsEnabled)(NETHTTP_DATA *);
    } NETHTTP_VTBL;

    typedef struct NetHTTP_class_vtbl_s    {
        OBJ_IUNKNOWN    iVtbl;              // Inherited Vtbl.
        // Put other methods below this as pointers and add their
        // method names to the vtbl definition in NetHTTP_object.c.
        // Properties:
        // Methods:
        //bool        (*pIsEnabled)(NETHTTP_DATA *);
    } NETHTTP_CLASS_VTBL;




    /****************************************************************
    * * * * * * * * * * *  Routine Definitions  * * * * * * * * * * *
    ****************************************************************/


    //---------------------------------------------------------------
    //                      *** Class Methods ***
    //---------------------------------------------------------------

#ifdef  NETHTTP_SINGLETON
    NETHTTP_DATA *     NetHTTP_Shared (
        void
    );

    void            NetHTTP_SharedReset (
        void
    );
#endif


   /*!
     Allocate a new Object and partially initialize. Also, this sets an
     indicator that the object was alloc'd which is tested when the object is
     released.
     @return    pointer to NetHTTP object if successful, otherwise OBJ_NIL.
     */
    NETHTTP_DATA *     NetHTTP_Alloc (
        void
    );
    
    
    OBJ_ID          NetHTTP_Class (
        void
    );
    
    
    NETHTTP_DATA *     NetHTTP_New (
        void
    );
    
    
#ifdef  NETHTTP_JSON_SUPPORT
    NETHTTP_DATA *   NetHTTP_NewFromJsonString (
        ASTR_DATA       *pString
    );

    NETHTTP_DATA *   NetHTTP_NewFromJsonStringA (
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

    ERESULT     NetHTTP_Disable (
        NETHTTP_DATA       *this
    );


    ERESULT     NetHTTP_Enable (
        NETHTTP_DATA       *this
    );

   
    NETHTTP_DATA *   NetHTTP_Init (
        NETHTTP_DATA     *this
    );


    ERESULT     NetHTTP_IsEnabled (
        NETHTTP_DATA       *this
    );
    
 
#ifdef  NETHTTP_JSON_SUPPORT
    /*!
     Create a string that describes this object and the objects within it in
     HJSON formt. (See hjson object for details.)
     Example:
     @code
     ASTR_DATA      *pDesc = NetHTTP_ToJson(this);
     @endcode
     @param     this    object pointer
     @return    If successful, an AStr object which must be released containing the
                JSON text, otherwise OBJ_NIL.
     @warning   Remember to release the returned AStr object.
     */
    ASTR_DATA *     NetHTTP_ToJson (
        NETHTTP_DATA   *this
    );
#endif


    /*!
     Create a string that describes this object and the objects within it.
     Example:
     @code 
        ASTR_DATA      *pDesc = NetHTTP_ToDebugString(this,4);
     @endcode 
     @param     this    object pointer
     @param     indent  number of characters to indent every line of output, can be 0
     @return    If successful, an AStr object which must be released containing the
                description, otherwise OBJ_NIL.
     @warning   Remember to release the returned AStr object.
     */
    ASTR_DATA *     NetHTTP_ToDebugString (
        NETHTTP_DATA     *this,
        int             indent
    );
    
    

    
#ifdef  __cplusplus
}
#endif

#endif  /* NETHTTP_H */

