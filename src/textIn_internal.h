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
#include    <srcLoc_internal.h>
#include    <ascii.h>
#include    <sidxe.h>
#include    <u8Array.h>
#include    <W32Str.h>


#ifndef TEXTIN_INTERNAL_H
#define	TEXTIN_INTERNAL_H



#ifdef	__cplusplus
extern "C" {
#endif


    typedef enum textIn_state_e {
        TEXTIN_STATE_UNKNOWN=0,
        TEXTIN_STATE_IN_TAB,
        TEXTIN_STATE_NORMAL
    } TEXTIN_STATE;
    
    
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
#define TEXTIN_FLAG_SAVCHR  OBJ_FLAG_USER1

    // Common Data
    union {
        ASTR_DATA           *pAStr;
        FILE                *pFile;
        U8ARRAY_DATA        *pU8Array;
        W32STR_DATA         *pWStr;
    };
    uint16_t        type;               // see TEXTIN_TYPE
    uint16_t        tabSize;            /* Tab Spacing Size */
    uint8_t         state;
    uint8_t         fFile;              // true == FILE parameter was supplied and
    //                                  //          we are not responsible for closing
    //                                  //          it. Otherwise, we are.
    uint8_t         fOpen;
    uint8_t         fStripCR;
    uint8_t         fStripNL;
    uint8_t         fAtEOF;
    uint8_t         fCols80;            // true == IBM 80 Column Card Input
    //                                  //      (ie cols 1-71 data,
    //                                  //          col 72 continuation indicator,
    //                                  //          cols 73-80 sequence number)
    uint8_t         fSeq80;             // Validate sequence numbers
    PATH_DATA       *pPath;
    const
    char            *pPathA;
    uint8_t         *pBuffer;
    uint16_t        filenameIndex;
    uint16_t        rsvd16;
#if defined(__MACOSX_ENV__) || defined(__WIN32_ENV__) || defined(__WIN64_ENV__)
    SIDXE_DATA      *pSidx;
#endif
    TEXTIN_CHRLOC   curChr;
    TEXTIN_CHRLOC   savChr;

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

    bool            textIn_setPath(
        TEXTIN_DATA     *this,
        PATH_DATA       *pValue
    );
    
    
    bool            textIn_setTabSize(
        TEXTIN_DATA     *this,
        uint16_t        value
    );
    
    
    OBJ_IUNKNOWN *  textIn_getSuperVtbl(
        TEXTIN_DATA     *this
    );


    void            textIn_Dealloc(
        OBJ_ID          objId
    );


    TEXTIN_DATA *   textIn_Init(
        TEXTIN_DATA     *this
    );
    
    
    void *          textIn_QueryInfo(
        OBJ_ID          objId,
        uint32_t        type,
        void            *pData
    );


    ERESULT         textIn_SetupBase(
        TEXTIN_DATA     *this,
        PATH_DATA       *pPath,
        uint16_t        tabSize         // Tab Spacing if any (0 will default to 4)
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

