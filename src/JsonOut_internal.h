// vi:nu:et:sts=4 ts=4 sw=4
/* 
 * File:   JsonOut_internal.h
 *	Generated 01/25/2020 21:31:26
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




#include        <JsonOut.h>
#include        <JsonIn.h>


#ifndef JSONOUT_INTERNAL_H
#define	JSONOUT_INTERNAL_H



#define     PROPERTY_STR_OWNED 1



#ifdef	__cplusplus
extern "C" {
#endif




    //---------------------------------------------------------------
    //                  Object Data Description
    //---------------------------------------------------------------

#pragma pack(push, 1)
struct JsonOut_data_s	{
    /* Warning - OBJ_DATA must be first in this object!
     */
    OBJ_DATA        super;
    OBJ_IUNKNOWN    *pSuperVtbl;    // Needed for Inheritance

    // Common Data
    uint16_t        size;		    // maximum number of elements
    uint16_t        rsvd16;
    ASTR_DATA       *pStr;

};
#pragma pack(pop)

    extern
    struct JsonOut_class_data_s  JsonOut_ClassObj;

    extern
    const
    JSONOUT_VTBL         JsonOut_Vtbl;



    //---------------------------------------------------------------
    //              Class Object Method Forward Definitions
    //---------------------------------------------------------------

#ifdef  JSONOUT_SINGLETON
    JSONOUT_DATA *     JsonOut_getSingleton (
        void
    );

    bool            JsonOut_setSingleton (
     JSONOUT_DATA       *pValue
);
#endif



    //---------------------------------------------------------------
    //              Internal Method Forward Definitions
    //---------------------------------------------------------------

    OBJ_IUNKNOWN *  JsonOut_getSuperVtbl (
        JSONOUT_DATA     *this
    );


    ERESULT         JsonOut_Assign (
        JSONOUT_DATA    *this,
        JSONOUT_DATA    *pOther
    );


    JSONOUT_DATA *       JsonOut_Copy (
        JSONOUT_DATA     *this
    );


    void            JsonOut_Dealloc (
        OBJ_ID          objId
    );


#ifdef  JSONOUT_JSON_SUPPORT
    /*!
     Parse the new object from an established parser.
     @param pParser an established jsonIn Parser Object
     @return    a new object if successful, otherwise, OBJ_NIL
     @warning   Returned object must be released.
     */
    JSONOUT_DATA *       JsonOut_ParseJsonObject (
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
    ERESULT         JsonOut_ParseJsonFields(
        JSONIN_DATA     *pParser,
        JSONOUT_DATA     *pObject
    );
#endif


    void *          JsonOut_QueryInfo (
        OBJ_ID          objId,
        uint32_t        type,
        void            *pData
    );


#ifdef  JSONOUT_JSON_SUPPORT
    ASTR_DATA *     JsonOut_ToJson (
        JSONOUT_DATA      *this
    );
#endif




#ifdef NDEBUG
#else
    bool			JsonOut_Validate (
        JSONOUT_DATA       *this
    );
#endif



#ifdef	__cplusplus
}
#endif

#endif	/* JSONOUT_INTERNAL_H */

