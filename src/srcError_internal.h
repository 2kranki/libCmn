// vi:nu:et:sts=4 ts=4 sw=4
/* 
 * File:   srcError_internal.h
 *	Generated 12/17/2017 07:12:31
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




#include    <srcError.h>
#include    <SrcLoc_internal.h>


#ifndef SRCERROR_INTERNAL_H
#define	SRCERROR_INTERNAL_H



#ifdef	__cplusplus
extern "C" {
#endif




    //---------------------------------------------------------------
    //                  Object Data Description
    //---------------------------------------------------------------

 #pragma pack(push, 1)
struct srcError_data_s	{
    /* Warning - OBJ_DATA must be first in this object!
     */
    OBJ_DATA        super;
    OBJ_IUNKNOWN    *pSuperVtbl;      // Needed for Inheritance

    // Common Data
    uint16_t        severity;
    uint16_t        rsvd16;
    SRCLOC          loc;
    ASTR_DATA       *pErrorStr;

};
#pragma pack(pop)

    extern
    const
    struct srcError_class_data_s  srcError_ClassObj;

    extern
    const
    SRCERROR_VTBL         srcError_Vtbl;



    //---------------------------------------------------------------
    //              Internal Method Forward Definitions
    //---------------------------------------------------------------

    bool            srcError_setErrorStr(
        SRCERROR_DATA   *this,
        ASTR_DATA       *pValue
    );
    
    
    bool            srcError_setLocation(
        SRCERROR_DATA   *this,
        const
        SRCLOC          *pValue
    );
    
    
    bool            srcError_setSeverity(
        SRCERROR_DATA   *this,
        uint16_t        value
    );
    
    
    OBJ_IUNKNOWN *  srcError_getSuperVtbl(
        SRCERROR_DATA     *this
    );


    void            srcError_Dealloc(
        OBJ_ID          objId
    );


    void *          srcError_QueryInfo(
        OBJ_ID          objId,
        uint32_t        type,
        void            *pData
    );


    ASTR_DATA *     srcError_ToJSON(
        SRCERROR_DATA      *this
    );




#ifdef NDEBUG
#else
    bool			srcError_Validate(
        SRCERROR_DATA       *this
    );
#endif



#ifdef	__cplusplus
}
#endif

#endif	/* SRCERROR_INTERNAL_H */

