// vi:nu:et:sts=4 ts=4 sw=4

//****************************************************************
//              NUL-terminated String (AStr) Header
//****************************************************************
/*
 * Program
 *			NUL-terminated String (AStr)
 * Purpose
 *			This object provides a NUL-terminated String and its
 *          manipulation with support for unicode characters.
 *
 * Remarks
 *	1.      Some -A (ascii) methods have been removed since
 *          the characters within this object could be unicode.
 *
 * History
 *	09/19/2015 Generated
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






#include        <cmn_defs.h>


#ifndef         ASTR_H
#define         ASTR_H


#ifdef	__cplusplus
extern "C" {
#endif
    

    //****************************************************************
    //* * * * * * * * * * * *  Data Definitions  * * * * * * * * * * *
    //****************************************************************


    // ASTR_DATA and ASTR_VTBL are defined in "cmn_defs.h"



    /****************************************************************
    * * * * * * * * * * *  Routine Definitions	* * * * * * * * * * *
    ****************************************************************/


    //---------------------------------------------------------------
    //                      *** Class Methods ***
    //---------------------------------------------------------------

    ASTR_DATA *    AStr_Alloc(
        void
    );
    
    
    ASTR_DATA *    AStr_New(
        void
    );

    
    ASTR_DATA *    AStr_NewA(
        const
        char			*pszIn			/* Input String Pointer */
    );
    
    
    ASTR_DATA *    AStr_NewFromCharA(
        uint32_t        len,
        const
        char            chr
    );
    
    
    ASTR_DATA *    AStr_NewFromEnv(
        const
        char            *pStr
    );
    
    
    ASTR_DATA *    AStr_NewFromInt64(
        int64_t         value
    );
    
    
    ERESULT         AStr_NewFromJSONString(
        ASTR_DATA       *pString,
        ASTR_DATA       **ppData
    );
    
    ERESULT         AStr_NewFromJSONStringA(
        const
        char            *pString,
        ASTR_DATA       **ppData
    );
    

    ASTR_DATA *    AStr_NewFromStrW(
        WSTR_DATA       *pStr
    );
    
    
    ASTR_DATA *    AStr_NewFromTimeNow(
        void
    );
 
    
    ASTR_DATA *    AStr_NewFromUInt64(
        uint64_t        value
    );
    
    
    ASTR_DATA *    AStr_NewFromUtf8File(
        PATH_DATA       *pPath
    );
    
    
    /*!
     Create a new string from a string escaping double parens and backslash
     characters so that the new string may be used directly in a string
     constant within a program.
     @param     this    object pointer
     @return    If successful, an AStr object which must be released,
                 otherwise OBJ_NIL.
     @warning  Remember to release the returned AStr object.
     */
    ASTR_DATA *    AStr_NewParenthesizedFromAStr(
        ASTR_DATA       *this
    );
    
    
    ASTR_DATA *    AStr_NewW(
        const
        int32_t			*pszIn			/* Input String Pointer */
    );
    
    
    

    //---------------------------------------------------------------
    //                      *** Properties ***
    //---------------------------------------------------------------

    uint32_t        AStr_getCrcIEEE(
        ASTR_DATA       *this
    );
    
    
    const
    char *          AStr_getData(
        ASTR_DATA      *this
    );
    
    
    /*!
     @return:   return the number of Ascii or Unicode characters in
                the string, not the actual size of the string in
                memory.
     */
    uint32_t        AStr_getLength(
        ASTR_DATA      *this
    );
    
    

    
    //---------------------------------------------------------------
    //                      *** Methods ***
    //---------------------------------------------------------------

    ERESULT         AStr_Append(
        ASTR_DATA		*this,
        ASTR_DATA       *pOther
    );
    
    
    ERESULT         AStr_AppendA(
        ASTR_DATA		*this,
        const
        char            *pStr
    );
    
    
    ERESULT         AStr_AppendStrW(
        ASTR_DATA		*this,
        WSTR_DATA       *pStr
    );
    
    
    ERESULT         AStr_AppendUtf8File(
        ASTR_DATA		*this,
        PATH_DATA       *pPath
    );
    
    
    ERESULT         AStr_AppendW(
        ASTR_DATA		*this,
        uint32_t        len,
        const
        int32_t         *pStr
    );
    
    
    ERESULT         AStr_AppendCharA(
        ASTR_DATA		*this,
        const
        char            chr
    );
    
    
    ERESULT         AStr_AppendCharW(
        ASTR_DATA		*this,
        const
        int32_t         chr
    );
    
    
    ERESULT         AStr_AppendCharRepeatA(
        ASTR_DATA		*this,
        uint32_t        len,
        const
        char            chr
    );
    
    
    ERESULT         AStr_AppendCharRepeatW(
        ASTR_DATA		*this,
        uint32_t        len,
        const
        int32_t         chr
    );
    
    
    ERESULT         AStr_AppendHex16(
        ASTR_DATA		*this,
        const
        uint16_t        num
    );
    
    
    ERESULT         AStr_AppendHex32(
        ASTR_DATA		*this,
        const
        uint32_t        num
    );
    
    
    ERESULT         AStr_AppendPrint(
        ASTR_DATA		*this,
        const
        char            *pFormat,
        ...
    );
    
    
    ERESULT         AStr_Assign(
        ASTR_DATA		*this,
        ASTR_DATA       *pOther
    );
    
    
    ERESULT         AStr_CharFindNextW(
        ASTR_DATA		*this,
        uint32_t        *pIndex,                // [in-out]
        const
        int32_t         chr
    );
    
    
    ERESULT         AStr_CharFindPrevW(
        ASTR_DATA		*this,
        uint32_t        *pIndex,                // [in-out]
        const
        int32_t         chr
    );
    
    
    int32_t         AStr_CharGetW(
        ASTR_DATA		*this,
        uint32_t        offset
    );
    
    
    ERESULT         AStr_CharInsertW(
        ASTR_DATA       *this,
        uint32_t        offset,
        int32_t         chr
    );
    
    
    ERESULT         AStr_CharPutW(
        ASTR_DATA		*this,
        uint32_t        offset,
        int32_t         chr
    );
    
    
    ERESULT         AStr_CharReplaceAllW(
        ASTR_DATA		*this,
        const
        int32_t         chrSrch,
        const
        int32_t         chrRepl
    );
    
    
    ERESULT         AStr_Compare(
        ASTR_DATA		*this,
        ASTR_DATA       *pOther
    );
    
    
    ERESULT         AStr_CompareA(
        ASTR_DATA		*this,
        const
        char            *pOther
    );
    
    
    /*!
     Compare the given string against 'this' from the right hand side of the string
     (ie compare the trailing part of the string)
     @param     this    object pointer
     @return    If str == const, ERESULT_SUCCESS_EQUAL. Otherwise, ERESULT_SUCCESS_LESS_THAN,
                ERESULT_SUCCESS_GREATER_THAN or an ERESULT_* error code.
                otherwise, an ERESULT_* Error Code.
     */
    ERESULT         AStr_CompareRightA(
        ASTR_DATA		*this,
        const
        char            *pOther
    );
    
    
    ERESULT         AStr_CompareW(
        ASTR_DATA		*this,
        const
        int32_t         *pOther
    );
    
    
    ASTR_DATA *     AStr_Copy(
        ASTR_DATA       *this
    );
    
    
    char *          AStr_CStringA(
        ASTR_DATA		*this,
        uint32_t        *pLen       // Optional returned string length
                                    // less terminating NUL
    );
    
    
    uint32_t        AStr_Hash(
        ASTR_DATA       *this
    );
    
    
    ASTR_DATA *     AStr_Init(
        ASTR_DATA       *this
    );


    ERESULT         AStr_InsertA(
        ASTR_DATA		*this,
        uint32_t        offset,
        const
        char            *pStr
        );

    
    ERESULT         AStr_InsertW(
        ASTR_DATA		*this,
        uint32_t        offset,
        const
        int32_t         *pStr
    );

    
    /*!
     Checks the string to see if it only contains ASCII characters 
     (ie no wide characters).
     @param     this    object pointer
     @return    If string contains only ASCII, ERESULT_SUCCESS,
                otherwise, an ERESULT_* Error Code.
     */
    ERESULT         AStr_IsOnlyASCII(
        ASTR_DATA		*this
    );
    
    
    ERESULT         AStr_Left(
        ASTR_DATA		*this,
        uint32_t        len,
        ASTR_DATA       **ppOther           // [out]
    );
    
    
    ERESULT         AStr_Mid(
        ASTR_DATA		*this,
        uint32_t        offset,
        uint32_t        len,
        ASTR_DATA      **ppOther            // [out]
    );
    
    
    ERESULT         AStr_Remove(
        ASTR_DATA		*this,
        uint32_t        offset,
        uint32_t        len
    );
    
    
    /*!
     Create a new string that consists of the right-most characters of the current
     string.
     @param     this    object pointer
     @param     len     number of characters on the right of the current string
     @param     ppOther returned string object pointer
     @return    If successful, an AStr object which must be released is placed in
                *ppOther and ERESULT_SUCCESS is returned, otherwise an ERESULT_*
                error is returned.
     @warning  Remember to release the returned AStr object.
     */
    ERESULT         AStr_Right(
        ASTR_DATA		*this,
        uint32_t        len,
        ASTR_DATA      **ppOther           // [out]
    );
    
    
    ERESULT         AStr_SpanW(
        ASTR_DATA		*this,
        uint32_t        *pIndex,            // [in-out]
        const
        int32_t         *pSetStr            // NUL-terminated set of unicode chars
    );
    
    
    /*!
     Convert this string to an ascii character constant format using escape
     sequences for non-printable character.
     @param     this    object pointer
     @return    If successful, an AStr object which must be released,
                otherwise OBJ_NIL.
     @warning   Remember to release the returned AStr object.
     */
    ASTR_DATA *     AStr_ToChrCon(
        ASTR_DATA       *this
    );
    
    
    ASTR_DATA *     AStr_ToLower(
        ASTR_DATA       *this
    );
    
    
    /*!
     Create a string that describes this object and the
     objects within it.
     Example:
     @code
     ASTR_DATA      *pDesc = AStr_ToDebugString(pObj,4);
     @endcode
     @param     this    object pointer
     @param     indent  number of characters to indent every line of output, can be 0
     @return    If successful, an AStr object which must be released,
                otherwise OBJ_NIL.
     @warning  Remember to release the returned AStr object.
     */
    ASTR_DATA *     AStr_ToDebugString(
        ASTR_DATA      *this,
        int             indent
    );
    
    
    int64_t         AStr_ToInt64(
        ASTR_DATA		*this
    );
    
    
    /*!
     Create a JSON string that describes this object.
     @return    If successful, an AStr object which must be released,
                otherwise OBJ_NIL.
     @warning  Remember to release the returned AStr object.
     */
    ASTR_DATA *     AStr_ToJSON(
        ASTR_DATA       *this
    );
    
    
    /*!
     Create a new string from the current one that is translated to
     upper case.
     @return    If successful, an new AStr object which must be released,
                otherwise OBJ_NIL.
     */
    ASTR_DATA *     AStr_ToUpper(
        ASTR_DATA      *this
    );
    
    
    uint64_t        AStr_ToUint64(
        ASTR_DATA		*this
    );
    
    
    ERESULT         AStr_ToUtf8File(
        ASTR_DATA		*this,
        PATH_DATA       *pPath
    );
    
    
    // The string returned from this must be obj_Release'd.
    WSTR_DATA *     AStr_ToWStr(
        ASTR_DATA       *this
    );
    
    
    /*!
     Remove white-space from the beginning and ending of the string.
     @return:   If successful, an new AStr object which must be released,
     otherwise OBJ_NIL.
     */
    ERESULT         AStr_Trim(
        ASTR_DATA		*this
    );
    
    
    ERESULT         AStr_Truncate(
        ASTR_DATA		*this,
        uint32_t        len
    );
    
    

    
#ifdef	__cplusplus
}
#endif

#endif	/* ASTR_H */

