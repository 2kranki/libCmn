// vi:nu:et:sts=4 ts=4 sw=4
/* 
 * File:   W32StrC_internal.h
 *	Generated 01/23/2020 22:22:04
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




#include        <W32StrC.h>
#include        <JsonIn.h>
#include        <utf8.h>


#ifndef W32STRC_INTERNAL_H
#define	W32STRC_INTERNAL_H



#define     PROPERTY_STR_OWNED 1



#ifdef	__cplusplus
extern "C" {
#endif




    //---------------------------------------------------------------
    //                  Object Data Description
    //---------------------------------------------------------------

#pragma pack(push, 1)
struct W32StrC_data_s	{
    /* Warning - OBJ_DATA must be first in this object!
     */
    OBJ_DATA        super;
    OBJ_IUNKNOWN    *pSuperVtbl;    // Needed for Inheritance
    #define W32STRC_FLAG_MALLOC OBJ_FLAG_USER1

    // Common Data
    uint32_t        len;        // Number of chars excluding trailing NUL
    W32CHR_T        *pArray;

};
#pragma pack(pop)

    extern
    struct W32StrC_class_data_s  W32StrC_ClassObj;

    extern
    const
    W32STRC_VTBL         W32StrC_Vtbl;



    //---------------------------------------------------------------
    //              Class Object Method Forward Definitions
    //---------------------------------------------------------------

#ifdef  W32STRC_SINGLETON
    W32STRC_DATA *  W32StrC_getSingleton (
        void
    );

    bool            W32StrC_setSingleton (
     W32STRC_DATA       *pValue
);
#endif



    //---------------------------------------------------------------
    //              Internal Method Forward Definitions
    //---------------------------------------------------------------

    OBJ_IUNKNOWN *  W32StrC_getSuperVtbl (
        W32STRC_DATA     *this
    );


    ERESULT         W32StrC_Assign (
        W32STRC_DATA    *this,
        W32STRC_DATA    *pOther
    );


    W32STRC_DATA *  W32StrC_Copy (
        W32STRC_DATA    *this
    );


    bool            W32StrC_CopyFromA(
        W32STRC_DATA    *this,
        const
        char            *pStrA
    );


    bool            W32StrC_CopyFromW32(
        W32STRC_DATA    *this,
        uint32_t        len,
        const
        W32CHR_T        *pStrW32
    );


    void            W32StrC_Dealloc (
        OBJ_ID          objId
    );


    bool            W32StrC_FreeLine(
        W32STRC_DATA    *this
    );


#ifdef  W32STRC_JSON_SUPPORT
    /*!
     Parse the new object from an established parser.
     @param pParser an established jsonIn Parser Object
     @return    a new object if successful, otherwise, OBJ_NIL
     @warning   Returned object must be released.
     */
    W32STRC_DATA *   W32StrC_ParseJsonObject (
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
    ERESULT         W32StrC_ParseJsonFields(
        JSONIN_DATA     *pParser,
        W32STRC_DATA    *pObject
    );
#endif


    void *          W32StrC_QueryInfo (
        OBJ_ID          objId,
        uint32_t        type,
        void            *pData
    );


#ifdef  W32STRC_JSON_SUPPORT
    ASTR_DATA *     W32StrC_ToJson (
        W32STRC_DATA    *this
    );


    ERESULT         W32StrC_ToJsonFields (
        W32STRC_DATA    *this,
        ASTR_DATA       *pStr
    );
#endif




#ifdef NDEBUG
#else
    bool            W32StrC_Validate (
        W32STRC_DATA    *this
    );
#endif



#ifdef	__cplusplus
}
#endif

#endif	/* W32STRC_INTERNAL_H */

