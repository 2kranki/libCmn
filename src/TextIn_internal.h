// vi:nu:et:sts=4 ts=4 sw=4
/* 
 * File:   TextIn_internal.h
 *	Generated 01/21/2020 22:03:13
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




#include        <TextIn.h>
#include        <JsonIn.h>
#include        <SrcLoc_internal.h>
#include        <ascii.h>
#include        <LineIndex.h>
#include        <W32Str.h>


#ifndef TEXTIN_INTERNAL_H
#define	TEXTIN_INTERNAL_H



#define     PROPERTY_STR_OWNED 1



#ifdef	__cplusplus
extern "C" {
#endif



typedef enum TextIn_state_e {
    TEXTIN_STATE_UNKNOWN=0,
    TEXTIN_STATE_IN_TAB,
    TEXTIN_STATE_NORMAL
} TEXTIN_STATE;


typedef enum TextIn_type_e {
    TEXTIN_TYPE_UNKNOWN=0,
    TEXTIN_TYPE_ASTR,
    TEXTIN_TYPE_FILE,
    TEXTIN_TYPE_STRA,
    TEXTIN_TYPE_WSTR
} TEXTIN_TYPE;




    //---------------------------------------------------------------
    //                  Object Data Description
    //---------------------------------------------------------------

#pragma pack(push, 1)
struct TextIn_data_s	{
    /* Warning - OBJ_DATA must be first in this object!
     */
    OBJ_DATA        super;
    OBJ_IUNKNOWN    *pSuperVtbl;    // Needed for Inheritance
#define TEXTIN_FLAG_SAVCHR  OBJ_FLAG_USER1

    // Common Data
    union {
        ASTR_DATA           *pAStr;
        FILE                *pFile;
        char                *pStrA;
        W32STR_DATA         *pWStr;
    };
    uint16_t        type;               // see TEXTIN_TYPE
    uint16_t        tabSize;            // Tab Spacing Size
    uint8_t         state;
    uint8_t         fFile;              // true == FILE parameter was supplied and
    //                                  //          we are not responsible for closing
    //                                  //          it. Otherwise, we are.
    uint8_t         fOpen;
    uint8_t         fStripCR;
    uint8_t         fStripNL;
    uint8_t         fAtEOF;
    uint8_t         fCols80;            // true == IBM 80 Column Card Input
    //                                  //          (ie
    //                                  //              cols 1-71 data,
    //                                  //              col  72 continuation indicator,
    //                                  //              cols 73-80 optional sequence
    //                                  //                          number
    uint8_t         fSeq80;             // Validate sequence numbers
    //                                  // (Only valid if fCols80 == true)
    PATH_DATA       *pPath;
    const
    char            *pPathA;
    uint8_t         *pBuffer;
    uint16_t        fileIndex;
    uint16_t        upperLimit;         // If set upper length limit for line.
#if defined(__MACOSX_ENV__) || defined(__MACOS64_ENV__)
    LINEINDEX_DATA  *pLineIndex;
#endif
#if defined(__WIN32_ENV__) || defined(__WIN64_ENV__)
    LINEINDEX_DATA  *pLineIndex;
#endif
    int64_t         offset;
    TOKEN_FIELDS    curTok;
    TOKEN_FIELDS    savTok;
    ERESULT         (*pLineExit)(
                                 OBJ_ID,
                                 int             len,
                                 char            *pBuffer,
                                 SRCLOC          *pLoc
                    );
    OBJ_ID          oLineExit;

};
#pragma pack(pop)

    extern
    struct TextIn_class_data_s  TextIn_ClassObj;

    extern
    const
    TEXTIN_VTBL         TextIn_Vtbl;



    //---------------------------------------------------------------
    //              Class Object Method Forward Definitions
    //---------------------------------------------------------------

#ifdef  TEXTIN_SINGLETON
    TEXTIN_DATA *   TextIn_getSingleton (
        void
    );

    bool            TextIn_setSingleton (
     TEXTIN_DATA       *pValue
);
#endif



    //---------------------------------------------------------------
    //              Internal Method Forward Definitions
    //---------------------------------------------------------------

    bool            TextIn_setPath(
        TEXTIN_DATA     *this,
        PATH_DATA       *pValue
    );


    OBJ_IUNKNOWN *  TextIn_getSuperVtbl (
        TEXTIN_DATA     *this
    );


    bool            TextIn_setTabSize(
        TEXTIN_DATA     *this,
        uint16_t        value
    );


    ERESULT         TextIn_Assign (
        TEXTIN_DATA    *this,
        TEXTIN_DATA    *pOther
    );


    TEXTIN_DATA *       TextIn_Copy (
        TEXTIN_DATA     *this
    );


    void            TextIn_Dealloc (
        OBJ_ID          objId
    );


#ifdef  TEXTIN_JSON_SUPPORT
    /*!
     Parse the new object from an established parser.
     @param pParser an established jsonIn Parser Object
     @return    a new object if successful, otherwise, OBJ_NIL
     @warning   Returned object must be released.
     */
    TEXTIN_DATA *       TextIn_ParseJsonObject (
        JSONIN_DATA     *pParser
    );


    /*!
     Parse the object from an established parser.
     @param pParser     an established jsonIn Parser Object
     @param pObject     an Object to be filled in with the
                        parsed fields.
     @return    If successful, ERESULT_SUCCESS. Otherwise, an ERESULT_*
                error code.
     */
    ERESULT         TextIn_ParseJsonFields(
        JSONIN_DATA     *pParser,
        TEXTIN_DATA     *pObject
    );
#endif


    void *          TextIn_QueryInfo (
        OBJ_ID          objId,
        uint32_t        type,
        void            *pData
    );


    ERESULT         textIn_SetupBase(
        TEXTIN_DATA     *this,
        PATH_DATA       *pPath,
        uint16_t        fileIndex,      // File Path Index for a separate path table
        uint16_t        tabSize         // Tab Spacing if any (0 will default to 4)
    );


#ifdef  TEXTIN_JSON_SUPPORT
    ASTR_DATA *     TextIn_ToJson (
        TEXTIN_DATA      *this
    );
#endif




#ifdef NDEBUG
#else
    bool			TextIn_Validate (
        TEXTIN_DATA       *this
    );
#endif



#ifdef	__cplusplus
}
#endif

#endif	/* TEXTIN_INTERNAL_H */

