// vi:nu:et:sts=4 ts=4 sw=4
/* 
 * File:   macro_internal.h
 *	Generated 08/08/2015 08:06:48
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



#include    <macro.h>
#include    <node_internal.h>


#ifndef MACRO_INTERNAL_H
#define	MACRO_INTERNAL_H




#ifdef	__cplusplus
extern "C" {
#endif


#pragma pack(push, 1)
struct macro_data_s	{
    /* Warning - OBJ_DATA must be first in this object!
     */
    NODE_DATA       super;
    OBJ_IUNKNOWN    *pSuperVtbl;

    // Common Data
    NAME_DATA       *pName;
    W32STR_DATA     *pBody;         // ???? or Use Token Stream
    NODEARRAY_DATA  *pKeywordParameters;
    NODEARRAY_DATA  *pPositionalParameters;

};
#pragma pack(pop)

    extern
    const
    MACRO_VTBL      macro_Vtbl;



    // Internal Functions
    void            macro_Dealloc(
        OBJ_ID          objId
    );

    void *          macro_QueryInfo(
        OBJ_ID          objId,
        uint32_t        type,
        void            *pData
    );
    
#ifdef NDEBUG
#else
    bool			macro_Validate(
        MACRO_DATA       *cbp
    );
#endif



#ifdef	__cplusplus
}
#endif

#endif	/* MACRO_INTERNAL_H */

