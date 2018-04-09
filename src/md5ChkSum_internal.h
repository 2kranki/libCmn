// vi:nu:et:sts=4 ts=4 sw=4
/* 
 * File:   md5ChkSum_internal.h
 *	Generated 04/01/2018 21:11:43
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




#include    <md5ChkSum.h>


/* Add prototype support.  */
#ifndef PROTO
#if defined (USE_PROTOTYPES) ? USE_PROTOTYPES : defined (__STDC__)
#define PROTO(ARGS) ARGS
#else
#define PROTO(ARGS) ()
#endif
#endif

#include    <md5_plumb.h>


#ifndef MD5CHKSUM_INTERNAL_H
#define	MD5CHKSUM_INTERNAL_H



#ifdef	__cplusplus
extern "C" {
#endif




    //---------------------------------------------------------------
    //                  Object Data Description
    //---------------------------------------------------------------

#pragma pack(push, 1)
struct md5ChkSum_data_s	{
    /* Warning - OBJ_DATA must be first in this object!
     */
    OBJ_DATA        super;
    OBJ_IUNKNOWN    *pSuperVtbl;    // Needed for Inheritance

    // Common Data
    ERESULT         eRc;
    struct MD5Context
                    ctx;
    uint8_t         digest[16];
    ASTR_DATA       *pMD5_Str;

};
#pragma pack(pop)

    extern
    const
    struct md5ChkSum_class_data_s  md5ChkSum_ClassObj;

    extern
    const
    MD5CHKSUM_VTBL         md5ChkSum_Vtbl;



    //---------------------------------------------------------------
    //              Internal Method Forward Definitions
    //---------------------------------------------------------------

   bool            md5ChkSum_setLastError(
        MD5CHKSUM_DATA     *this,
        ERESULT         value
    );


    OBJ_IUNKNOWN *  md5ChkSum_getSuperVtbl(
        MD5CHKSUM_DATA     *this
    );


    void            md5ChkSum_Dealloc(
        OBJ_ID          objId
    );


    void *          md5ChkSum_QueryInfo(
        OBJ_ID          objId,
        uint32_t        type,
        void            *pData
    );


    ASTR_DATA *     md5ChkSum_ToJSON(
        MD5CHKSUM_DATA      *this
    );




#ifdef NDEBUG
#else
    bool			md5ChkSum_Validate(
        MD5CHKSUM_DATA       *this
    );
#endif



#ifdef	__cplusplus
}
#endif

#endif	/* MD5CHKSUM_INTERNAL_H */

