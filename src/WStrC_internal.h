// vi:nu:et:sts=4 ts=4 sw=4
/* 
 * File:   WStrC_internal.h
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


#include    "WStrC.h"
#include    "AStr.h"
#include    "utf8.h"


#ifdef	__cplusplus
extern "C" {
#endif


  typedef struct WStrC_vtbl_internal_s	{
        WSTRC_VTBL         iVtbl;              // Inherited Vtbl.
        // Put other methods below this as pointers and add their
        // method names to the vtbl definition in WStrC_object.c.
        // Properties:
        // Methods:
#ifdef NDEBUG
#else
        bool			(*pValidate)(WSTRC_DATA *);
#endif
    } WSTRC_VTBL_INTERNAL;



#pragma pack(push, 1)
struct WStrC_data_s	{
    /* Warning - OBJ_DATA must be first in this object!
     */
    OBJ_DATA        super;
    OBJ_IUNKNOWN    *pSuperVtbl;      // Needed for Inheritance
#define WSTRC_FLAG_MALLOC 5

    // Common Data
    uint32_t        len;		// Number of chars excluding trailing NUL
    const
    int32_t         *pArray;

};
#pragma pack(pop)

    extern
    const
    struct WStrC_class_data_s	WStrC_ClassObj;

    extern
    const
    WSTRC_VTBL_INTERNAL WStrC_Vtbl;



    // Internal Functions
    void            WStrC_Dealloc(
        OBJ_ID          objId
    );


    WSTRC_DATA *    WStrC_Init(
        WSTRC_DATA      *this
    );
    
    WSTRC_DATA *    WStrC_InitA(
        WSTRC_DATA      *this,
        const
        char            *pStr
    );
    
    WSTRC_DATA *    WStrC_InitConW(
        WSTRC_DATA      *this,
        const
        int32_t         *pStr
    );
    
    WSTRC_DATA *    WStrC_InitW(
        WSTRC_DATA      *this,
        const
        int32_t         *pStr
    );
    
    
#ifdef NDEBUG
#else
    bool			WStrC_Validate(
        WSTRC_DATA       *cbp
    );
#endif



#ifdef	__cplusplus
}
#endif

#endif	/* WSTRC_INTERNAL_H */

