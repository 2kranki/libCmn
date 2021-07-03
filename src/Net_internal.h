// vi:nu:et:sts=4 ts=4 sw=4
/* 
 * File:   Net_internal.h
 *  Generated 07/03/2021 07:04:16
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




#include        <Net.h>
#include        <JsonIn.h>
#include        <sys/socket.h>
#include        <sys/types.h>
#include        <arpa/inet.h>
#include        <netinet/in.h>
#include        <netdb.h>
#include        <fcntl.h>
#include        <signal.h>


#ifndef NET_INTERNAL_H
#define NET_INTERNAL_H





#ifdef  __cplusplus
extern "C" {
#endif




    //---------------------------------------------------------------
    //                  Object Data Description
    //---------------------------------------------------------------

#pragma pack(push, 1)
struct Net_data_s  {
    /* Warning - OBJ_DATA must be first in this object!
     */
    OBJ_DATA        super;
    OBJ_IUNKNOWN    *pSuperVtbl;    // Needed for Inheritance
#define NET_FLAG_OPEN OBJ_FLAG_USER1

    // Common Data
    uint16_t        size;           // maximum number of elements
    uint16_t        rsvd16;
    ASTR_DATA       *pStr;
    int             socket;         // socket descriptor

};
#pragma pack(pop)

    extern
    struct Net_class_data_s  Net_ClassObj;

    extern
    const
    NET_VTBL         Net_Vtbl;



    //---------------------------------------------------------------
    //              Class Object Method Forward Definitions
    //---------------------------------------------------------------

#ifdef  NET_SINGLETON
    NET_DATA *     Net_getSingleton (
        void
    );

    bool            Net_setSingleton (
     NET_DATA       *pValue
);
#endif



    //---------------------------------------------------------------
    //              Internal Method Forward Definitions
    //---------------------------------------------------------------

    OBJ_IUNKNOWN *  Net_getSuperVtbl (
        NET_DATA     *this
    );


    ERESULT         Net_Assign (
        NET_DATA    *this,
        NET_DATA    *pOther
    );


    NET_DATA *       Net_Copy (
        NET_DATA     *this
    );


    void            Net_Dealloc (
        OBJ_ID          objId
    );


#ifdef  NET_JSON_SUPPORT
    /*!
     Parse the new object from an established parser.
     @param pParser an established jsonIn Parser Object
     @return    a new object if successful, otherwise, OBJ_NIL
     @warning   Returned object must be released.
     */
    NET_DATA *       Net_ParseJsonObject (
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
    ERESULT         Net_ParseJsonFields (
        JSONIN_DATA     *pParser,
        NET_DATA     *pObject
    );
#endif


    void *          Net_QueryInfo (
        OBJ_ID          objId,
        uint32_t        type,
        void            *pData
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
        NET_DATA      *this
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
    ERESULT         Net_ToJsonFields (
        NET_DATA     *this,
        ASTR_DATA       *pStr
    );
#endif




#ifdef NDEBUG
#else
    bool            Net_Validate (
        NET_DATA       *this
    );
#endif



#ifdef  __cplusplus
}
#endif

#endif  /* NET_INTERNAL_H */

