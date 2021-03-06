// vi:nu:et:sts=4 ts=4 sw=4
/* 
 * File:   MsgData_internal.h
 *	Generated 12/31/2019 10:05:08
 *
 * Notes:
 *  --	N/A
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




#include        <MsgData.h>
#include        <JsonIn.h>
#include        <Value_internal.h>


#ifndef MSGDATA_INTERNAL_H
#define	MSGDATA_INTERNAL_H



#define     PROPERTY_STR_OWNED 1



#ifdef	__cplusplus
extern "C" {
#endif




    //---------------------------------------------------------------
    //                  Object Data Description
    //---------------------------------------------------------------

#pragma pack(push, 1)
struct MsgData_data_s	{
    /* Warning - OBJ_DATA must be first in this object!
     */
    VALUE_DATA      super;
    OBJ_IUNKNOWN    *pSuperVtbl;    // Needed for Inheritance

    // Common Data
    uint32_t        origin;         // Origin Number
    uint32_t        dest;           // Destination Number (0 == general broadcast)
    uint32_t        num32;          // Number which can be used by User

};
#pragma pack(pop)

    extern
    struct MsgData_class_data_s  MsgData_ClassObj;

    extern
    const
    MSGDATA_VTBL    MsgData_Vtbl;



    //---------------------------------------------------------------
    //              Class Object Method Forward Definitions
    //---------------------------------------------------------------

#ifdef  MSGDATA_SINGLETON
    MSGDATA_DATA *  MsgData_getSingleton (
        void
    );

    bool            MsgData_setSingleton (
     MSGDATA_DATA       *pValue
);
#endif



    //---------------------------------------------------------------
    //              Internal Method Forward Definitions
    //---------------------------------------------------------------

    OBJ_IUNKNOWN *  MsgData_getSuperVtbl (
        MSGDATA_DATA     *this
    );


    void            MsgData_Dealloc (
        OBJ_ID          objId
    );


#ifdef  MSGDATA_JSON_SUPPORT
    MSGDATA_DATA *  MsgData_ParseJsonObject (
        JSONIN_DATA     *pParser
    );


    /*!
     Parse the object from an established parser.
     @param pParser     an established jsonIn Parser Object
     @param pObject     an Object to be filled in with the
                        parsed fields.
     @return    If successful, ERESULT_SUCCESS. Otherwise, an ERESULT_*
                error code.
     */
    ERESULT         MsgData_ParseJsonFields (
        JSONIN_DATA     *pParser,
        MSGDATA_DATA    *pObject
    );
#endif


    void *          MsgData_QueryInfo (
        OBJ_ID          objId,
        uint32_t        type,
        void            *pData
    );


#ifdef  MSGDATA_JSON_SUPPORT
    ASTR_DATA *     MsgData_ToJson (
        MSGDATA_DATA      *this
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
    ERESULT         MsgData_ToJsonFields (
        MSGDATA_DATA    *this,
        ASTR_DATA       *pStr
    );
#endif




#ifdef NDEBUG
#else
    bool			MsgData_Validate (
        MSGDATA_DATA       *this
    );
#endif



#ifdef	__cplusplus
}
#endif

#endif	/* MSGDATA_INTERNAL_H */

