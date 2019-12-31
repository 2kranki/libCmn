// vi:nu:et:sts=4 ts=4 sw=4
/* 
 * File:   SrcError_internal.h
 *	Generated 12/28/2019 09:57:21
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




#include        <SrcError.h>
#include        <JsonIn.h>
#include        <SrcLoc_internal.h>


#ifndef SRCERROR_INTERNAL_H
#define	SRCERROR_INTERNAL_H



#define     PROPERTY_ERRORSTR_OWNED 1



#ifdef	__cplusplus
extern "C" {
#endif




    //---------------------------------------------------------------
    //                  Object Data Description
    //---------------------------------------------------------------

#pragma pack(push, 1)
struct SrcError_data_s	{
    /* Warning - OBJ_DATA must be first in this object!
     */
    OBJ_DATA        super;
    OBJ_IUNKNOWN    *pSuperVtbl;    // Needed for Inheritance

    // Common Data
    uint16_t        severity;
    uint16_t        rsvd16;
    SRCLOC          loc;
    ASTR_DATA       *pErrorStr;

};
#pragma pack(pop)

    extern
    struct SrcError_class_data_s  SrcError_ClassObj;

    extern
    const
    SRCERROR_VTBL         SrcError_Vtbl;



    //---------------------------------------------------------------
    //              Class Object Method Forward Definitions
    //---------------------------------------------------------------

#ifdef  SRCERROR_SINGLETON
    SRCERROR_DATA * SrcError_getSingleton (
        void
    );

    bool            SrcError_setSingleton (
     SRCERROR_DATA       *pValue
);
#endif



    //---------------------------------------------------------------
    //              Internal Method Forward Definitions
    //---------------------------------------------------------------

    bool            SrcError_setErrorStr (
        SRCERROR_DATA   *this,
        ASTR_DATA       *pValue
    );


    bool            SrcError_setLocation (
        SRCERROR_DATA   *this,
        const
        SRCLOC          *pValue
    );


    bool            SrcError_setSeverity (
        SRCERROR_DATA   *this,
        uint16_t        value
    );


    OBJ_IUNKNOWN *  SrcError_getSuperVtbl (
        SRCERROR_DATA   *this
    );


    void            SrcError_Dealloc (
        OBJ_ID          objId
    );


#ifdef  SRCERROR_JSON_SUPPORT
    SRCERROR_DATA *       SrcError_ParseJsonObject (
        JSONIN_DATA     *pParser
    );
#endif


    void *          SrcError_QueryInfo (
        OBJ_ID          objId,
        uint32_t        type,
        void            *pData
    );


#ifdef  SRCREF_JSON_SUPPORT
    ASTR_DATA *     SrcError_ToJson (
        SRCERROR_DATA      *this
    );
#endif




#ifdef NDEBUG
#else
    bool			SrcError_Validate (
        SRCERROR_DATA       *this
    );
#endif



#ifdef	__cplusplus
}
#endif

#endif	/* SRCERROR_INTERNAL_H */

