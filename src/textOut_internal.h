// vi:nu:et:sts=4 ts=4 sw=4
/* 
 * File:   textOut_internal.h
 *	Generated 12/08/2017 10:18:28
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




#include    <textOut.h>
#include    <fbso.h>


#ifndef TEXTOUT_INTERNAL_H
#define	TEXTOUT_INTERNAL_H



#ifdef	__cplusplus
extern "C" {
#endif


    typedef enum textOut_type_e {
        TEXTOUT_TYPE_UNKNOWN=0,
        TEXTOUT_TYPE_ASTR,
        TEXTOUT_TYPE_FBSO,
        TEXTOUT_TYPE_FILE,
        TEXTOUT_TYPE_FILE_CLOSE,
        TEXTOUT_TYPE_U8ARRAY
    } TEXTOUT_TYPE;
    
    
    


    //---------------------------------------------------------------
    //                  Object Data Description
    //---------------------------------------------------------------

 #pragma pack(push, 1)
struct textOut_data_s	{
    /* Warning - OBJ_DATA must be first in this object!
     */
    OBJ_DATA        super;
    OBJ_IUNKNOWN    *pSuperVtbl;    // Needed for Inheritance

    // Common Data
    uint16_t        offset;         //
    uint16_t        tabSize;        //
    char            offsetChr;
    uint8_t         fTabify;
    uint8_t         type;
    uint8_t         rsvd8[1];
    union {
        ASTR_DATA           *pStr;
        FILE                *pFile;
        U8ARRAY_DATA        *pU8Array;
    };
    
};
#pragma pack(pop)

    extern
    const
    struct textOut_class_data_s  textOut_ClassObj;

    extern
    const
    TEXTOUT_VTBL         textOut_Vtbl;



    //---------------------------------------------------------------
    //              Internal Method Forward Definitions
    //---------------------------------------------------------------

    OBJ_IUNKNOWN *  textOut_getSuperVtbl(
        TEXTOUT_DATA     *this
    );


    void            textOut_Dealloc(
        OBJ_ID          objId
    );


    void *          textOut_QueryInfo(
        OBJ_ID          objId,
        uint32_t        type,
        void            *pData
    );


    ASTR_DATA *     textOut_ToJSON(
        TEXTOUT_DATA      *this
    );




#ifdef NDEBUG
#else
    bool			textOut_Validate(
        TEXTOUT_DATA       *this
    );
#endif



#ifdef	__cplusplus
}
#endif

#endif	/* TEXTOUT_INTERNAL_H */

