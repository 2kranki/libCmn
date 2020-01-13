// vi:nu:et:sts=4 ts=4 sw=4
/* 
 * File:   W32StrC_internal.h
 *	Generated 02/19/2016 09:34:06
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




#ifndef WSTRC_INTERNAL_H
#define	WSTRC_INTERNAL_H


#include    <W32StrC.h>
#include    <AStr.h>
#include    <utf8.h>


#ifdef	__cplusplus
extern "C" {
#endif


  typedef struct W32StrC_vtbl_internal_s	{
        W32STRC_VTBL       iVtbl;              // Inherited Vtbl.
        // Put other methods below this as pointers and add their
        // method names to the vtbl definition in WStrC_object.c.
        // Properties:
        // Methods:
#ifdef NDEBUG
#else
        bool			(*pValidate)(W32STRC_DATA *);
#endif
    } W32STRC_VTBL_INTERNAL;



#pragma pack(push, 1)
struct W32StrC_data_s	{
    /* Warning - OBJ_DATA must be first in this object!
     */
    OBJ_DATA        super;
    OBJ_IUNKNOWN    *pSuperVtbl;      // Needed for Inheritance
#define W32STRC_FLAG_MALLOC OBJ_FLAG_USER1

    // Common Data
    uint32_t        len;		// Number of chars excluding trailing NUL
    const
    W32CHR_T        *pArray;

};
#pragma pack(pop)

    extern
    const
    struct W32StrC_class_data_s	W32StrC_ClassObj;

    extern
    const
    W32STRC_VTBL_INTERNAL W32StrC_Vtbl;



    // Internal Functions
    void            W32StrC_Dealloc(
        OBJ_ID          objId
    );


    W32STRC_DATA *  W32StrC_Init(
        W32STRC_DATA    *this
    );
    
    W32STRC_DATA *  W32StrC_InitA(
        W32STRC_DATA    *this,
        const
        char            *pStr
    );
    
    W32STRC_DATA *  W32StrC_InitConW(
        W32STRC_DATA    *this,
        const
        W32CHR_T        *pStr
    );
    
    W32STRC_DATA *  W32StrC_InitW(
        W32STRC_DATA    *this,
        const
        W32CHR_T        *pStr
    );
    
    
    void *          W32StrC_QueryInfo(
        OBJ_ID          objId,
        uint32_t        type,
        void            *pData
    );
    
    
    ERESULT         W32StrC_SetupA(
        W32STRC_DATA    *this,
        const
        char            *pStr
    );
    
    
#ifdef NDEBUG
#else
    bool			W32StrC_Validate(
        W32STRC_DATA    *this
    );
#endif



#ifdef	__cplusplus
}
#endif

#endif	/* WSTRC_INTERNAL_H */

