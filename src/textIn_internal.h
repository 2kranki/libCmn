// vi:nu:et:sts=4 ts=4 sw=4
/* 
 * File:   textIn_internal.h
 *	Generated 11/23/2017 23:46:18
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




#include    <textIn.h>
#include    <ascii.h>
#include    <u8Array.h>
#include    <WStr.h>


#ifndef TEXTIN_INTERNAL_H
#define	TEXTIN_INTERNAL_H



#ifdef	__cplusplus
extern "C" {
#endif


    typedef enum textIn_type_e {
        TEXTIN_TYPE_UNKNOWN=0,
        TEXTIN_TYPE_ASTR,
        TEXTIN_TYPE_FILE,
        TEXTIN_TYPE_U8ARRAY,
        TEXTIN_TYPE_WSTR
    } TEXTIN_TYPE;
    
    


    //---------------------------------------------------------------
    //                  Object Data Description
    //---------------------------------------------------------------

 #pragma pack(push, 1)
struct textIn_data_s	{
    /* Warning - OBJ_DATA must be first in this object!
     */
    OBJ_DATA        super;
    OBJ_IUNKNOWN    *pSuperVtbl;      // Needed for Inheritance

    // Common Data
    ERESULT         eRc;
    union {
        ASTR_DATA           *pAStr;
        FILE                *pFile;
        U8ARRAY_DATA        *pU8Array;
        WSTR_DATA           *pWStr;
    };
    uint16_t        type;               // OBJ_CLASS_FBSI or OBJ_CLASS_SBUF
    uint16_t        flags;              /* Flags */
#define FLG_EOF         0x8000                  /* End-of-File has been reached. */
#define FLG_INS         0x4000                  /* Lines are being inserted. */
#define FLG_NNL         0x2000                  /* Remove all '\n's. */
#define FLG_OPN         0x1000                  /* File is open and useable. */
#define FLG_TAB         0x0800                  /* Expand Horizontal Tabs. */
#define FLG_FILE        0x0400                  /* FILE file was provided */
    uint32_t        lineNo;             /* Current Line Number */
    uint16_t        colNo;              /* Current Column Number */
    uint16_t        tabSize;            /* Tab Spacing Size */
    size_t          fileOffset;
    uint8_t         fStripCR;
    uint8_t         rsvd8_1[3];
    PATH_DATA       *pPath;
    const
    char            *pPathA;
    uint8_t         *pBuffer;

};
#pragma pack(pop)

    extern
    const
    struct textIn_class_data_s  textIn_ClassObj;

    extern
    const
    TEXTIN_VTBL         textIn_Vtbl;



    //---------------------------------------------------------------
    //              Internal Method Forward Definitions
    //---------------------------------------------------------------

   bool            textIn_setLastError(
        TEXTIN_DATA     *this,
        ERESULT         value
    );


    OBJ_IUNKNOWN *  textIn_getSuperVtbl(
        TEXTIN_DATA     *this
    );


    void            textIn_Dealloc(
        OBJ_ID          objId
    );


    TEXTIN_DATA *   textIn_Init(
        TEXTIN_DATA     *this,
        PATH_DATA       *pPath,
        uint16_t        tabSize         // Tab Spacing if any (0 will default to 4)
    );
    
    
    void *          textIn_QueryInfo(
        OBJ_ID          objId,
        uint32_t        type,
        void            *pData
    );


    ASTR_DATA *     textIn_ToJSON(
        TEXTIN_DATA      *this
    );




#ifdef NDEBUG
#else
    bool			textIn_Validate(
        TEXTIN_DATA       *this
    );
#endif



#ifdef	__cplusplus
}
#endif

#endif	/* TEXTIN_INTERNAL_H */

