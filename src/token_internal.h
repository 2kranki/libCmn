// vi:nu:et:sts=4 ts=4 sw=4
/* 
 * File:   token_internal.h
 *	Generated 05/26/2015 13:40:16
 *
 * Created on September 26, 2014, 3:39 PM
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




#ifndef TOKEN_INTERNAL_H
#define	TOKEN_INTERNAL_H



#include    "token.h"
#include    "srcLoc_internal.h"



#ifdef	__cplusplus
extern "C" {
#endif

    // The TOKEN data contains all the information for a token. It is a fixed
    // length which facilitates it being used in arrays of data. If you want
    // to store variable length data such as character strings, then you MUST
    // use a mechanism such as the global/shared string table.  All data within
    // this struct must be only primitive types that can be written to or read
    // from disk files.
    
#pragma pack(push, 1)
    typedef struct token_s    {
        SRCLOC          src;
        uint16_t        len;                // Character/Token Length (Optional)
        uint16_t        misc;
        uint16_t        offset;             // offset into token string (Optional)
        uint16_t        type;               // Type in union below
        int32_t         cls;                // Character/Token Class (Optional)
        uint32_t        rsvd32;
        union {
            double          floatingPoint;
            int64_t         integer;            // Integer
            uint32_t        strToken;           // String Index Token
            W32CHR_T        w32chr[2];          // Unicode Character followed by NUL
        };
        // Do NOT declare any variables here, put them above the union.
    } TOKEN;
#pragma pack(pop)
    
#pragma pack(push, 1)
struct token_data_s	{
    /* Warning - OBJ_DATA must be first in this object!
     */
    OBJ_DATA        super;
    OBJ_IUNKNOWN    *pSuperVtbl;      // Needed for Inheritance

    // Common Data
    ERESULT         eRc;
    TOKEN           data;

};
#pragma pack(pop)

    extern
    const
    TOKEN_VTBL      token_Vtbl;



    // Internal Functions
    void            token_Dealloc(
        OBJ_ID          objId
    );


    TOKEN_DATA *     token_InitFnLCC(
        TOKEN_DATA      *this,
        uint16_t        fileIndex,
        int64_t         offset,
        uint32_t        lineNo,
        uint16_t        colNo,
        int32_t         cls
    );
    
    
    void *          token_QueryInfo(
        OBJ_ID          objId,
        uint32_t        type,
        void            *pData
    );
    
    
#ifdef NDEBUG
#else
    bool			token_Validate(
        TOKEN_DATA       *cbp
    );
#endif



#ifdef	__cplusplus
}
#endif

#endif	/* TOKEN_INTERNAL_H */

