// vi:nu:et:sts=4 ts=4 sw=4
/* 
 * File:   NetIO_internal.h
 *  Generated 07/02/2021 14:27:06
 *
 * Notes:
 *  --  N/A
 *
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




#include        <NetIO.h>
#include        <JsonIn.h>
#include        <sys/socket.h>
#include        <sys/types.h>
#include        <arpa/inet.h>
#include        <netinet/in.h>
#include        <netdb.h>
#include        <fcntl.h>
#include        <signal.h>



#ifndef NETIO_INTERNAL_H
#define NETIO_INTERNAL_H





#ifdef  __cplusplus
extern "C" {
#endif




    //---------------------------------------------------------------
    //                  Object Data Description
    //---------------------------------------------------------------

#pragma pack(push, 1)
struct NetIO_data_s  {
    /* Warning - OBJ_DATA must be first in this object!
     */
    OBJ_DATA        super;
    OBJ_IUNKNOWN    *pSuperVtbl;    // Needed for Inheritance
#define NETIO_FLAG_OPEN OBJ_FLAG_USER1

    // Common Data
    uint16_t        size;           // maximum number of elements
    uint16_t        rsvd16;
    ASTR_DATA       *pStr;
    int             socket;
    struct addrinfo addr_info;

};
#pragma pack(pop)

    extern
    struct NetIO_class_data_s  NetIO_ClassObj;

    extern
    const
    NETIO_VTBL         NetIO_Vtbl;



    //---------------------------------------------------------------
    //              Class Object Method Forward Definitions
    //---------------------------------------------------------------

#ifdef  NETIO_SINGLETON
    NETIO_DATA *     NetIO_getSingleton (
        void
    );

    bool            NetIO_setSingleton (
     NETIO_DATA       *pValue
);
#endif



    //---------------------------------------------------------------
    //              Internal Method Forward Definitions
    //---------------------------------------------------------------

    OBJ_IUNKNOWN *  NetIO_getSuperVtbl (
        NETIO_DATA     *this
    );


    ERESULT         NetIO_Assign (
        NETIO_DATA    *this,
        NETIO_DATA    *pOther
    );


    NETIO_DATA *       NetIO_Copy (
        NETIO_DATA     *this
    );


    void            NetIO_Dealloc (
        OBJ_ID          objId
    );


#ifdef  NETIO_JSON_SUPPORT
    /*!
     Parse the new object from an established parser.
     @param pParser an established jsonIn Parser Object
     @return    a new object if successful, otherwise, OBJ_NIL
     @warning   Returned object must be released.
     */
    NETIO_DATA *       NetIO_ParseJsonObject (
        JSONIN_DATA     *pParser
    );


    /*!
     Parse the object from an established parser. This helps facilitate
     parsing the fields from an inheriting object.
     @param pParser     an established jsonIn Parser Object
     @param pObject     an Object to be filled in with the
                        parsed fields.
     @return    If successful, ERESULT_SUCCESS. Otherwise, an ERESULT_*
                error code.
     */
    ERESULT         NetIO_ParseJsonFields (
        JSONIN_DATA     *pParser,
        NETIO_DATA     *pObject
    );
#endif


    void *          NetIO_QueryInfo (
        OBJ_ID          objId,
        uint32_t        type,
        void            *pData
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
        NETIO_DATA      *this
    );


    /*!
     Append the json representation of the object's fields to the given
     string. This helps facilitate parsing the fields from an inheriting 
     object.
     @param this        Object Pointer
     @param pStr        String Pointer to be appended to.
     @return    If successful, ERESULT_SUCCESS. Otherwise, an ERESULT_*
                error code.
     */
    ERESULT         NetIO_ToJsonFields (
        NETIO_DATA     *this,
        ASTR_DATA       *pStr
    );
#endif




#ifdef NDEBUG
#else
    bool            NetIO_Validate (
        NETIO_DATA       *this
    );
#endif



#ifdef  __cplusplus
}
#endif

#endif  /* NETIO_INTERNAL_H */

