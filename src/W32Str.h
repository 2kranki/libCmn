// vi:nu:et:sts=4 ts=4 sw=4

//****************************************************************
//          Wide (32 bit) NUL-terminated String (W32Str) Header
//****************************************************************
/*
 * Program
 *			Wide (UTF-32) NUL-terminated String (W32Str)
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
#include        <AStrC.h>

#ifndef         W32STR_H
#define         W32STR_H


#ifdef	__cplusplus
extern "C" {
#endif
    

    //****************************************************************
    //* * * * * * * * * * * *  Data Definitions  * * * * * * * * * * *
    //****************************************************************


    // W32STR_DATA and W32STR_VTBL are defined in "cmn_defs.h"



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
    W32STR_DATA *   W32Str_Alloc(
        void
    );
    
    
    // Return offset of chr in string (relative to 1)
    // Returns 0 if not found.
    uint32_t        W32Str_ChrInStr(
        W32CHR_T        chr,
        const
        W32CHR_T        *pStr
    );
    
    
    OBJ_ID          W32Str_Class(
        void
    );
    
    
    /*!
     @result
     ERESULT_SUCCESS_EQUAL if str1 == str2,
     ERESULT_SUCCESS_LESS_THAN if str1 < str2
     or ERESULT_SUCCESS_GREATER_THAN if str1 > str2.
     */
    ERESULT         W32Str_Cmp(
        const
        W32CHR_T        *pStr1,
        const
        W32CHR_T        *pStr2
    );
    
    
    uint32_t        W32Str_StrLen(
        const
        W32CHR_T        *pData
    );
    
    
    W32STR_DATA *   W32Str_New(
        void
    );
    
    
    W32STR_DATA *   W32Str_NewA(
        const
        char            *pStr
    );
    
    
    W32STR_DATA *   W32Str_NewW32(
        uint32_t        len,
        const
        W32CHR_T        *pStr
    );
    
    
    W32STR_DATA *   W32Str_NewFromEnv(
        const
        char            *pStr
    );
    
    
    W32STR_DATA *   W32Str_NewFromJSONString(
        ASTR_DATA       *pString
    );
    
    W32STR_DATA *   W32Str_NewFromJSONStringA(
        const
        char            *pString
    );
    

    W32STR_DATA *   W32Str_NewFromTimeNow(
        void
    );
    

    W32STR_DATA *   W32Str_NewFromUtf8File(
        PATH_DATA       *pPath
    );
    
    

    
    //---------------------------------------------------------------
    //                      *** Properties ***
    //---------------------------------------------------------------

    uint32_t        W32Str_getCrcIEEE(
        W32STR_DATA     *this
    );
    
    
    const
    W32CHR_T *      W32Str_getData(
        W32STR_DATA     *this
    );
    
    
    uint32_t        W32Str_getLength(
        W32STR_DATA     *this
    );

    
    
    
    //---------------------------------------------------------------
    //                      *** Methods ***
    //---------------------------------------------------------------

    ERESULT         W32Str_Append(
        W32STR_DATA     *this,
        W32STR_DATA     *pOther
    );
    
    
    ERESULT         W32Str_AppendA(
        W32STR_DATA		*this,
        const
        char            *pStr               // UTF-8 String
    );
    
    
    ERESULT         W32Str_AppendPrintA(
        W32STR_DATA		*this,
        const
        char            *pFormat,
        ...
    );
    
    
    ERESULT         W32Str_AppendUtf8File(
        W32STR_DATA		*this,
        PATH_DATA       *pPath
    );
    
    
    ERESULT         W32Str_AppendStrA(
        W32STR_DATA		*this,
        ASTR_DATA       *pStr
    );
    
    
    ERESULT         W32Str_AppendW32(
        W32STR_DATA		*this,
        uint32_t        len,                // Data Length or 0 to use NUL-terminator
        const
        W32CHR_T        *pStr
    );
    
    
    // Append len number of chr's to string.
    ERESULT         W32Str_AppendCharW32(
        W32STR_DATA		*this,
        uint32_t        len,
        const
        W32CHR_T        chr
    );
    
    
    ERESULT         W32Str_Assign(
        W32STR_DATA		*this,
        W32STR_DATA     *pOther
    );
    
    
    // Search the string for the provided char. If *pIndex
    // is set to 0, then the search begins at the begin-
    // ning of the string.
    ERESULT         W32Str_CharFindNextW32(
        W32STR_DATA		*this,
        uint32_t        *pIndex,            // [in-out]
        const
        W32CHR_T        chr
    );
    

    // Search the string backwards for the provided char. If
    // *pIndex is set to 0, then the search begins at the
    // end of the string.
    ERESULT         W32Str_CharFindPrevW32(
        W32STR_DATA		*this,
        uint32_t        *pIndex,            // [in-out]
        W32CHR_T        chr
    );
    
    
    /*! Get a character from the string at the specified offset 
        if it is within the string.
     @param     offset   0 < offset <= WStr_getLength()
     @result
        valid character if returned character is greater than or 
        equal to zero, otherwise -1
     */
    W32CHR_T        W32Str_CharGetW32(
        W32STR_DATA		*this,
        uint32_t        offset              // Relative to 1
    );
    

    /*! Simple scan and replace of single characters
     */
    ERESULT         W32Str_CharReplaceAllW32(
        W32STR_DATA		*this,
        const
        W32CHR_T        chrSrch,
        const
        W32CHR_T        chrRepl
    );
    
    
    ERESULT         W32Str_CharPutW32(
        W32STR_DATA		*this,
        uint32_t        offset,             // Relative to 1
        const
        W32CHR_T        chr
    );
    
    
    /*!
     @result
        ERESULT_SUCCESS_EQUAL if this == other,
        ERESULT_SUCCESS_LESS_THAN if this < other
        or ERESULT_SUCCESS_GREATER_THAN if this > other.
     */
    ERESULT         W32Str_Compare(
        W32STR_DATA		*this,
        W32STR_DATA     *pOther
    );
    
    
    /*!
     @param     pString
        Pointer to nul-terminated UTF-8 char string
     @result
        ERESULT_SUCCESS_EQUAL if this == string,
        ERESULT_SUCCESS_LESS_THAN if this < string
        or ERESULT_SUCCESS_GREATER_THAN if this > string.
     */
    ERESULT         W32Str_CompareA(
        W32STR_DATA		*this,
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
    ERESULT         W32Str_CompareW32(
        W32STR_DATA		*this,
        const
        W32CHR_T        *pString
    );
    
    
    W32STR_DATA *   W32Str_Copy(
        W32STR_DATA		*this
    );
    
    
    /*!
     @result
        If successful, a NUL-terminated UTF-8 string that
        needs to be freed with mem_Free(). Otherwise, NULL.
     */
    char *          W32Str_CStringA(
        W32STR_DATA		*this,
        uint32_t        *pLen       // Optional returned string length
                                    // less terminating NUL
    );
    
    
    /*! Escape double parentheses, backslashes, and certain
     whitespace so that the line can be used in a C program
     string constant.
     @result
        If successful, ERESULT_SUCCESS. Otherwise, ERESULT_FAULURE.
     */
    ERESULT         W32Str_EscapeForC(
        W32STR_DATA		*this
    );
    
    
    /*! Scan the string until one of the characters in the given
        nul-terminated string are found. Start searching at the
        given index and bump it as the search continues.
     @param     this    object pointer
     @param     pStrA   pointer to a wide char nul-terminated string.
     @param     pIndex  Index into the string to start at and where the
                        scan stopped.
     @return    If one of the chars is found, ERESULT_SUCCESS.
                ERESULT_OUT_OF_RANGE if none of the chars are found.
     */
    ERESULT         W32Str_FindNextA(
        W32STR_DATA     *this,
        const
        char            *pStrA,             // UTF-8 String
        uint32_t        *pIndex
    );


    /*! Scan the string until one of the characters in the given
        nul-terminated string are found. Start searching at the
        given index and bump it as the search continues.
     @param     this    object pointer
     @param     pStrW32 pointer to a wide char nul-terminated string.
     @param     pIndex  Index into the string to start at and where the
                        scan stopped.
     @return    If one of the chars is found, ERESULT_SUCCESS.
                ERESULT_OUT_OF_RANGE if none of the chars are found.
     */
    ERESULT         W32Str_FindNextW32(
        W32STR_DATA     *this,
        const
        W32CHR_T        *pStrW32,
        uint32_t        *pIndex
    );


    uint32_t        W32Str_Hash(
        W32STR_DATA     *this
    );
    
    /*! Scan the string until one of the characters in the given
        nul-terminated string are found. Start searching at the
        given index and bump it as the search continues.
     @param     this    object pointer
     @param     pSetStr pointer to a nul-terminated set of wide chars.
     @param     pIndex  Index into the string to start at and where the
                        scan stopped.
     @return    If one of the chars is found, ERESULT_SUCCESS.
                ERESULT_OUT_OF_RANGE if none of the chars are found.
     */
    ERESULT         W32Str_IndexUntil(
        W32STR_DATA		*this,
        const
        W32CHR_T        *pSetStr,
        uint32_t        *pIndex             // [in-out]
    );
    
    
    W32STR_DATA *   W32Str_Init(
        W32STR_DATA     *this
    );

    
    ERESULT         W32Str_InsertA(
        W32STR_DATA		*this,
        uint32_t        offset,
        const
        char            *pStr
    );

    
    // Tests the string data for any characters
    // larger than 0x7E.
    // If found, returns FAILURE.
    // Otherwise, returns SUCCESS.
    ERESULT         W32Str_IsOnlyASCII(
        W32STR_DATA		*this
    );
    
    
    ERESULT         W32Str_Left(
        W32STR_DATA		*this,
        uint32_t        len,
        W32STR_DATA     **ppOther           // [out]
    );
    
    
    ERESULT         W32Str_Lower(
        W32STR_DATA		*this
    );
    
    
    ERESULT         W32Str_Mid(
        W32STR_DATA		*this,
        uint32_t        offset,
        uint32_t        len,
        W32STR_DATA     **ppOther           // [out]
    );
    
    
    ERESULT         W32Str_Remove(
        W32STR_DATA		*this,
        uint32_t        offset,
        uint32_t        len
    );
    
    
    ERESULT         W32Str_Right(
        W32STR_DATA		*this,
        uint32_t        len,
        W32STR_DATA     **ppOther           // [out]
    );
    
    
    // Scans this string until it finds a character that
    // is not in the Nul-terminated Set String.
    // Returns:
    //      0 if the end of string is found.
    //      n where n is the offset into the string
    ERESULT         W32Str_SpanW32(
        W32STR_DATA		*this,
        uint32_t        *pIndex,            // [in-out]
        const
        W32CHR_T        *pSetStr
    );
    
    
    /*!
     Convert this string to an ascii character constant format using escape
     sequences for non-printable character.
     @param     this    object pointer
     @return    If successful, an AStr object which must be released,
                otherwise OBJ_NIL.
     @warning   Remember to release the returned AStr object.
     */
    ASTR_DATA *     W32Str_ToChrCon(
        W32STR_DATA     *this
    );
    
    
    /*!
     Create a string that describes this object and the
     objects within it.
     Example:
     @code
     ASTR_DATA      *pDesc = WStr_ToDebugString(pObj,4);
     @endcode
     @param     this    object pointer
     @param     indent  number of characters to indent every line of output, can be 0
     @return    If successful, an AStr object which must be released,
                 otherwise OBJ_NIL.
     @warning   Remember to release the returned AStr object.
     */
    ASTR_DATA *     W32Str_ToDebugString(
        W32STR_DATA     *this,
        int             indent
    );
    
    
    // ToInt32() tries to convert the string to a signed 32-bit
    // number with format [+ | -][0..9]*
    // 0 is returned if the number is mal-formed.
    int32_t         W32Str_ToInt32(
        W32STR_DATA		*this
    );
    
    
    /*!
     Create a JSON string that describes this object.
     @return    If successful, an AStr object which must be released,
                otherwise OBJ_NIL.
     @warning   Remember to release the returned AStr object.
     */
    ASTR_DATA *     W32Str_ToJSON(
        W32STR_DATA     *this
    );
    
    
    ERESULT         W32Str_ToUtf8File(
        W32STR_DATA		*this,
        PATH_DATA       *pPath
    );
    
    
    // Trim() removes white-space from both ends of the string.
    // White-space is considered any character that is numeri-
    // cally less than or equal to a space ( ' ' ).
    ERESULT         W32Str_Trim(
        W32STR_DATA		*this
    );
    
    
    ERESULT         W32Str_Truncate(
        W32STR_DATA		*this,
        uint32_t        len
    );
    
    
    ERESULT         W32Str_Upper(
        W32STR_DATA		*this
    );
    
    
    
#ifdef	__cplusplus
}
#endif

#endif	/* W32STR_H */

