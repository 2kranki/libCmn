// vi:nu:et:sts=4 ts=4 sw=4
/* 
 * File:   name_internal.h
 *	Generated 02/07/2016 15:50:27
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



#include    <name.h>
#include    <AStr.h>
#include    <WStr.h>


#ifndef NAME_INTERNAL_H
#define	NAME_INTERNAL_H 1


#ifdef	__cplusplus
extern "C" {
#endif


//#pragma pack(push, 1)
struct name_data_s	{
    /* Warning - OBJ_DATA must be first in this object!
     */
    OBJ_DATA        super;
    OBJ_IUNKNOWN    *pSuperVtbl;
#define NAME_FLAG_HASH  OBJ_FLAG_USER1  /* Hash is initialized. */

    // Common Data
    ERESULT         eRc;
    uint16_t        type;               /* Type in union below*/
    uint16_t        rsvd;
    union {
        char            chrs[8];            // UTF-8 Character w/NUL
        int64_t			integer;			// Integer
        const
        char            *pChrs;             // UTF-8 Character String
        OBJ_ID			pObj;               // any object
    };
    uint32_t            hash;

};
//#pragma pack(pop)

    extern
    const
    NAME_VTBL       name_Vtbl;



    // Internal Functions
    bool            name_setLastError(
        NAME_DATA       *this,
        ERESULT         value
    );
    
    
    void            name_Dealloc(
        OBJ_ID          objId
    );

    
    NAME_DATA *     name_Init(
        NAME_DATA       *this
    );

    
    NAME_DATA *   name_InitPtr(
        NAME_DATA       *this,
        const
        void            *pValue
    );
    
    
    void *          name_QueryInfo(
        OBJ_ID          objId,
        uint32_t        type,
        void            *pData
    );
    
    
    void            name_ReleaseDataIfObj(
        NAME_DATA       *this
    );
    
#ifdef NDEBUG
#else
    bool			name_Validate(
        NAME_DATA       *cbp
    );
#endif



#ifdef	__cplusplus
}
#endif

#endif	/* NAME_INTERNAL_H */

