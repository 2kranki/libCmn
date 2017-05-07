// vi:nu:et:sts=4 ts=4 sw=4

//****************************************************************
//          Wide NUL-terminated String (WStr) Header
//****************************************************************
/*
 * Program
 *			Wide NUL-terminated String (WStr)
 * Purpose
 *			This object provides a NUL-terminated Wide string
 *          and its manipulation.
 *
 * Remarks
 *	1.      All offsets/indices are relative to one. Zero is normally
 *          used to denote beginning or end of the data depending on
 *          the operation.
 *
 * History
 *	06/08/2015 Generated
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
#include        <str.h>


#ifndef         WSTR_H
#define         WSTR_H


#ifdef	__cplusplus
extern "C" {
#endif
    

    //****************************************************************
    //* * * * * * * * * * * *  Data Definitions  * * * * * * * * * * *
    //****************************************************************


    // WSTR_DATA and WSTR_VTBL are defined in "cmn.h"



    /****************************************************************
    * * * * * * * * * * *  Routine Definitions	* * * * * * * * * * *
    ****************************************************************/


    //---------------------------------------------------------------
    //                      *** Class Methods ***
    //---------------------------------------------------------------

    /* Alloc() allocates an area large enough for the bstr including
     * the stack.  If 0 is passed for the stack size, then an ap-
     * propriate default is chosen. The stack size is passed to Init()
     * via obj_misc1.
     */
    WSTR_DATA *     WStr_Alloc(
    );
    
    
    // Return offset of chr in string (relative to 1)
    // Returns 0 if not found.
    uint32_t        WStr_ChrInStr(
        int32_t         chr,
        const
        int32_t         *pStr
    );
    
    
    /*!
     @result
     ERESULT_SUCCESS_EQUAL if str1 == str2,
     ERESULT_SUCCESS_LESS_THAN if str1 < str2
     or ERESULT_SUCCESS_GREATER_THAN if str1 > str2.
     */
    ERESULT         WStr_Cmp(
        const
        int32_t         *pStr1,
        const
        int32_t         *pStr2
    );
    
    
    bool            WStr_IsWhiteSpaceW(
        int32_t         chr
    );
    
    
    uint32_t        WStr_StrLen(
        const
        int32_t         *pData
    );
    
    
    WSTR_DATA *     WStr_New(
    );
    
    
    WSTR_DATA *     WStr_NewA(
        const
        char            *pStr
    );
    
    
    WSTR_DATA *     WStr_NewW(
        uint32_t        len,
        const
        int32_t         *pStr
    );
    
    
    WSTR_DATA *     WStr_NewFromEnv(
        const
        char            *pStr
    );
    
    
    WSTR_DATA *     WStr_NewFromTimeNow(
    );
    

    WSTR_DATA *     WStr_NewFromUtf8File(
        PATH_DATA       *pPath
    );
    
    
    // Returns a ptr to an array of white space
    // characters terminated with a NUL.
    const
    int32_t *       WStr_WhiteSpaceW(
    );
    
    

    
    //---------------------------------------------------------------
    //                      *** Properties ***
    //---------------------------------------------------------------

    const
    int32_t *       WStr_getData(
        WSTR_DATA     *this
    );
    
    
    uint32_t        WStr_getLength(
        WSTR_DATA     *this
    );

    
    
    
    //---------------------------------------------------------------
    //                      *** Methods ***
    //---------------------------------------------------------------

    ERESULT         WStr_Append(
        WSTR_DATA		*this,
        WSTR_DATA       *pOther
    );
    
    
    ERESULT         WStr_AppendA(
        WSTR_DATA		*this,
        const
        char            *pStr               // UTF-8 String
    );
    
    
    ERESULT         WStr_AppendPrint(
        WSTR_DATA		*this,
        const
        char            *pFormat,
        ...
    );
    
    
    ERESULT         WStr_AppendUtf8File(
        WSTR_DATA		*this,
        PATH_DATA       *pPath
    );
    
    
    ERESULT         WStr_AppendStrA(
        WSTR_DATA		*this,
        ASTR_DATA       *pStr
    );
    
    
    ERESULT         WStr_AppendW(
        WSTR_DATA		*this,
        uint32_t        len,                // Data Length or 0 to use NUL-terminator
        const
        int32_t         *pStr
    );
    
    
    // Append len number of chr's to string.
    ERESULT         WStr_AppendCharW(
        WSTR_DATA		*this,
        uint32_t        len,
        const
        int32_t         chr
    );
    
    
    ERESULT         WStr_Assign(
        WSTR_DATA		*this,
        WSTR_DATA       *pOther
    );
    
    
    // Search the string for the provided char. If *pIndex
    // is set to 0, then the search begins at the begin-
    // ning of the string.
    ERESULT         WStr_CharFindNextW(
        WSTR_DATA		*this,
        uint32_t        *pIndex,            // [in-out]
        const
        int32_t         chr
    );
    

    // Search the string backwards for the provided char. If
    // *pIndex is set to 0, then the search begins at the
    // end of the string.
    ERESULT         WStr_CharFindPrevW(
        WSTR_DATA		*this,
        uint32_t        *pIndex,            // [in-out]
        int32_t         chr
    );
    
    
    /*! Get a character from the string at the specified offset 
        if it is within the string.
     @param     offset   0 < offset <= WStr_getLength()
     @result
        valid character if returned character is greater than or 
        equal to zero, otherwise -1
     */
    int32_t         WStr_CharGetW(
        WSTR_DATA		*this,
        uint32_t        offset              // Relative to 1
    );
    

    /*! Simple scan and replace of single characters
     */
    ERESULT         WStr_CharReplaceAllW(
        WSTR_DATA		*this,
        const
        int32_t         chrSrch,
        const
        int32_t         chrRepl
    );
    
    
    ERESULT         WStr_CharPutW(
        WSTR_DATA		*this,
        uint32_t        offset,             // Relative to 1
        const
        int32_t         chr
    );
    
    
    /*!
     @result
        ERESULT_SUCCESS_EQUAL if this == other,
        ERESULT_SUCCESS_LESS_THAN if this < other
        or ERESULT_SUCCESS_GREATER_THAN if this > other.
     */
    ERESULT         WStr_Compare(
        WSTR_DATA		*this,
        WSTR_DATA       *pOther
    );
    
    
    /*!
     @param     pString
        Pointer to nul-terminated UTF-8 char string
     @result
        ERESULT_SUCCESS_EQUAL if this == string,
        ERESULT_SUCCESS_LESS_THAN if this < string
        or ERESULT_SUCCESS_GREATER_THAN if this > string.
     */
    ERESULT         WStr_CompareA(
        WSTR_DATA		*this,
        const
        char            *pString
    );
    

    /*!
     @param     pString
        Pointer to nul-terminated wide char string
     @result
        ERESULT_SUCCESS_EQUAL if this == string,
        ERESULT_SUCCESS_LESS_THAN if this < string
        or ERESULT_SUCCESS_GREATER_THAN if this > string.
     */
    ERESULT         WStr_CompareW(
        WSTR_DATA		*this,
        const
        int32_t         *pString
    );
    
    
    WSTR_DATA *     WStr_Copy(
        WSTR_DATA		*this
    );
    
    
    /*!
     @result
        If successful, a NUL-terminated UTF-8 string that
        needs to be freed with mem_Free(). Otherwise, NULL.
     */
    char *          WStr_CStringA(
        WSTR_DATA		*this,
        uint32_t        *pLen       // Optional returned string length
                                    // less terminating NUL
    );
    
    
    /*! Escape double parentheses, backslashes, and certain
     whitespace so that the line can be used in a C program
     string constant.
     @result
        If successful, ERESULT_SUCCESS. Otherwise, ERESULT_FAULURE.
     */
    ERESULT         WStr_EscapeForC(
        WSTR_DATA		*this
    );
    
    
    uint32_t        WStr_Hash(
        WSTR_DATA     *this
    );
    
    
    ERESULT         WStr_IndexUntil(
        WSTR_DATA		*this,
        const
        int32_t         *pSetStr,
        uint32_t        *pIndex             // [in-out]
    );
    
    
    WSTR_DATA *     WStr_Init(
        WSTR_DATA       *this
    );

    
    ERESULT         WStr_InsertA(
        WSTR_DATA		*this,
        uint32_t        offset,
        const
        char            *pStr
    );

    
    // Tests the string data for any characters
    // larger than 0x7E.
    // If found, returns FAILURE.
    // Otherwise, returns SUCCESS.
    ERESULT         WStr_IsOnlyASCII(
        WSTR_DATA		*this
    );
    
    
    ERESULT         WStr_Left(
        WSTR_DATA		*this,
        uint32_t        len,
        WSTR_DATA       **ppOther           // [out]
    );
    
    
    ERESULT         WStr_Lower(
        WSTR_DATA		*this
    );
    
    
    ERESULT         WStr_Mid(
        WSTR_DATA		*this,
        uint32_t        offset,
        uint32_t        len,
        WSTR_DATA       **ppOther           // [out]
    );
    
    
    ERESULT         WStr_Remove(
        WSTR_DATA		*this,
        uint32_t        offset,
        uint32_t        len
    );
    
    
    ERESULT         WStr_Right(
        WSTR_DATA		*this,
        uint32_t        len,
        WSTR_DATA       **ppOther           // [out]
    );
    
    
    // Calculates the index into the string for all the
    // characters found in the Set String. Returns 0
    // if the end of string is found.
    ERESULT         WStr_SpanW(
        WSTR_DATA		*this,
        uint32_t        *pIndex,            // [in-out]
        const
        int32_t         *pSetStr
    );
    
    
    /*!
     Create a string that describes this object and the
     objects within it.
     Example:
     @code:
     ASTR_DATA      *pDesc = WStr_ToDebugString(pObj,4);
     @endcode:
     @param:    this    object pointer
     @param:    indent  number of characters to indent every line of output, can be 0
     @return:   If successful, an AStr object which must be released,
     otherwise OBJ_NIL.
     @warning: Remember to release the returned AStr object.
     */
    ASTR_DATA *     WStr_ToDebugString(
        WSTR_DATA       *this,
        int             indent
    );
    
    
    // ToInt32() tries to convert the string to a signed 32-bit
    // number with format [+ | -][0..9]*
    // 0 is returned if the number is mal-formed.
    int32_t         WStr_ToInt32(
        WSTR_DATA		*this
    );
    
    
    ERESULT         WStr_ToUtf8File(
        WSTR_DATA		*this,
        PATH_DATA       *pPath
    );
    
    
    // Trim() removes white-space from both ends of the string.
    // White-space is considered any character that is numeri-
    // cally less than or equal to a space ( ' ' ).
    ERESULT         WStr_Trim(
        WSTR_DATA		*this
    );
    
    
    ERESULT         WStr_Truncate(
        WSTR_DATA		*this,
        uint32_t        len
    );
    
    
    ERESULT         WStr_Upper(
        WSTR_DATA		*this
    );
    
    
    
#ifdef	__cplusplus
}
#endif

#endif	/* BSTR_H */

