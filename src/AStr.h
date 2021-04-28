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
 *	1.      The Object User flags and Misc data are not used in
 *          this object.
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


#define   ASTR_JSON_SUPPORT 1
//#define   ASTR_SINGLETON    1



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
    
    
    OBJ_ID         AStr_Class(
        void
    );
    
    
    ASTR_DATA *    AStr_New(
        void
    );

    
    ASTR_DATA *    AStr_NewA(
        const
        char			*pszIn			/* Input String Pointer */
    );
    
    
    ASTR_DATA *    AStr_NewFromMidA(
        const
        char            *pszIn,         /* [in] Variable String Pointer */
        uint32_t        offset,
        uint32_t        len
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
    
    
    ASTR_DATA *     AStr_NewFromHexData(
        void            *pData,
        int32_t         cData,
        uint16_t        indent
    );


    ASTR_DATA *    AStr_NewFromInt64(
        int64_t         value
    );
    
    
#ifdef  ASTR_JSON_SUPPORT
    ASTR_DATA *    AStr_NewFromJsonString(
        ASTR_DATA       *pString
    );
    
    ASTR_DATA *    AStr_NewFromJsonStringA(
        const
        char            *pString
    );
#endif


    ASTR_DATA *    AStr_NewFromPrint(
        const
        char            *pFormat,
        ...
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


    ASTR_DATA *    AStr_NewFromW32Str(
        W32STR_DATA     *pStr
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
    
    
    ASTR_DATA *    AStr_NewW32(
        const
        W32CHR_T		*pszIn			/* Input String Pointer */
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
     @return:   return the number of Unicode characters in
                the string, not the actual size of the string in
                memory.  -1 indicates an error occurred.
     */
    uint32_t        AStr_getLength(
        ASTR_DATA      *this
    );
    
    
    /*!
     @return:   return the number of Unicode characters in
                the string, not the actual size of the string in
                memory.  -1 indicates an error occurred.
     */
    uint32_t        AStr_getSize(
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
    
    
    ERESULT         AStr_AppendMidA(
        ASTR_DATA        *this,
        const
        char            *pStr,
        uint32_t        offset,
        uint32_t        len
    );
    
    
    ERESULT         AStr_AppendW32Str(
        ASTR_DATA		*this,
        W32STR_DATA     *pStr
    );
    
    
    ERESULT         AStr_AppendUtf8File(
        ASTR_DATA		*this,
        PATH_DATA       *pPath
    );
    
    
    ERESULT         AStr_AppendW32(
        ASTR_DATA		*this,
        uint32_t        len,
        const
        W32CHR_T        *pStr
    );
    
    
    ERESULT         AStr_AppendCharA(
        ASTR_DATA		*this,
        const
        char            chr
    );
    
    
    ERESULT         AStr_AppendCharW32(
        ASTR_DATA		*this,
        const
        W32CHR_T        chr
    );
    
    
    ERESULT         AStr_AppendCharRepeatA(
        ASTR_DATA		*this,
        uint32_t        len,
        const
        char            chr
    );
    
    
    ERESULT         AStr_AppendCharRepeatW32(
        ASTR_DATA		*this,
        uint32_t        len,
        const
        W32CHR_T        chr
    );
    
    
    ERESULT         AStr_AppendHex8(
        ASTR_DATA       *this,
        const
        uint8_t         num
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
    
    
    /*!
     Append a hexadecimal dump of the provided area.
     @param this    Object Pointer
     @param pData   pointer to Data to be dumped
     @param cData   data length
     @param indent  number of spaces to indent each line of the dump with
     */
    ERESULT        AStr_AppendHexData(
        ASTR_DATA       *this,
        void            *pData,
        int32_t         cData,
        uint16_t        indent
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
    
    
    /*!
     Find the next occurrence of the given character starting the search at the
     given index into the string.  The search is performed in an increasing index
     until the end of the string is reached.
     @param     this    object pointer
     @param     pIndex  required pointer to string index (set to 0 to start at
                        the beginning of the string)
     @param     chr     character to look for
     @return    If character was found, ERESULT_SUCCESS and the string index gives
                the index of the character within the string (relative to 1). Otherwise,
                an ERESULT_* error code is returned.
     */
    ERESULT         AStr_CharFindNextW32(
        ASTR_DATA		*this,
        uint32_t        *pIndex,                // [in-out]
        const
        W32CHR_T        chr
    );
    
    
    /*!
     Find the previous occurrence of the given character starting the search at the
     given index into the string.  The search is performed in an decreasing index
     until the beginning of the string is reached.
     @param     this    object pointer
     @param     pIndex  required pointer to string index (set to 0 to start at
                        the end of the string)
     @param     chr     character to look for
     @return    If character was found, ERESULT_SUCCESS and the string index gives
                the index of the character within the string (relative to 1). Otherwise,
                an ERESULT_* error code is returned.
     */
    ERESULT         AStr_CharFindPrevW32(
        ASTR_DATA		*this,
        uint32_t        *pIndex,                // [in-out]
        const
        W32CHR_T        chr
    );
    
    
    W32CHR_T        AStr_CharGetW32(
        ASTR_DATA		*this,
        uint32_t        offset
    );
    
    W32CHR_T        AStr_CharGetFirstW32(
        ASTR_DATA        *this
    );
    
    W32CHR_T        AStr_CharGetLastW32(
        ASTR_DATA        *this
    );
    

    ERESULT         AStr_CharInsertW32(
        ASTR_DATA       *this,
        uint32_t        offset,
        W32CHR_T        chr
    );
    
    
    ERESULT         AStr_CharInsertW32Repeat(
        ASTR_DATA       *this,
        uint32_t        offset,
        uint32_t        len,
        W32CHR_T        chr
    );
    
    
    ERESULT         AStr_CharPutW32(
        ASTR_DATA		*this,
        uint32_t        offset,
        W32CHR_T        chr
    );
    
    
    ERESULT         AStr_CharReplaceAllW32(
        ASTR_DATA		*this,
        const
        W32CHR_T        chrSrch,
        const
        W32CHR_T        chrRepl
    );
    
    
    /*!
     Compare 'this' to 'pOther'.
     @param     this    object pointer
     @param     pOther  Other String Object Pointer
     @return    0  if this == other
                <0 if this < other
                >0 if this > other
     */
    int             AStr_Compare(
        ASTR_DATA		*this,
        ASTR_DATA       *pOther
    );
    
    
    /*!
     Compare 'this' to 'pOther'.
     @param     this    object pointer
     @param     pOther  UTF-8 Ascii String Pointer
     @return    0  if this == other
                <0 if this < other
                >0 if this > other
     */
    int             AStr_CompareA(
        ASTR_DATA		*this,
        const
        char            *pOther
    );
    
    
    /*!
     Compare the given string against 'this' from the left hand side of the string
     (ie compare the leading part of the string)
     @param     this    object pointer
     @return    0  if this == other
                <0 if this < other
                >0 if this > other
     */
    int             AStr_CompareLeftA(
        ASTR_DATA        *this,
        const
        char            *pOther
    );
    
    
    /*!
     Compare the given string against 'this' from the right hand side of the string
     (ie compare the trailing part of the string)
     @param     this    object pointer
     @return    0  if this == other
                <0 if this < other
                >0 if this > other
     */
    int             AStr_CompareRightA(
        ASTR_DATA		*this,
        const
        char            *pOther
    );
    
    
    int             AStr_CompareW32(
        ASTR_DATA		*this,
        const
        W32CHR_T        *pOther
    );
    
    
    ASTR_DATA *     AStr_Copy(
        ASTR_DATA       *this
    );
    
    
    char *          AStr_CStringA(
        ASTR_DATA		*this,
        uint32_t        *pLen       // Optional returned string length
                                    // less terminating NUL
    );
    
    
    ASTR_DATA *     AStr_DeepCopy(
        ASTR_DATA       *this
    );
    
    
    /*!
     Substitute hash values or environment variables into the current string
     using a BASH-like syntax with the hash value having the highest priority.
     Variable names should have the syntax of:
            '$' '{' [a-zA-Z_][a-zA-Z0-9_]* '}'.
     Substitutions are rescanned after insertion.
     @param     this        object pointer
     @param     pFindA      optional method to find the variable by name
     @param     pFindObj    Object for FindA
     @return    ERESULT_SUCCESS if successful.  Otherwise, an ERESULT_* error code
                is returned.
     */
    ERESULT         AStr_ExpandVars(
        ASTR_DATA       *this,
        const
        char *          (*pFindA)(OBJ_ID, const char *pNameA),
        OBJ_ID          pFindObj
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
    ERESULT         AStr_FindNextA(
        ASTR_DATA       *this,
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
    ERESULT         AStr_FindNextW32(
        ASTR_DATA       *this,
        const
        W32CHR_T        *pStrW32,
        uint32_t        *pIndex
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

    
    ERESULT         AStr_InsertW32(
        ASTR_DATA		*this,
        uint32_t        offset,
        const
        W32CHR_T        *pStr
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
    
    
    /*!
     Match this string against a pattern using misc_PatternMatchA.
     @param     this    object pointer
     @param     pPattern pointer to a pattern string as containing optional
                         match characters, '?' and '*'.
     @return    If successful, ERESULT_SUCCESS is returned, otherwise an ERESULT_*
                 error is returned.
     */
    ERESULT         AStr_MatchA(
        ASTR_DATA       *this,
        const
        char            *pPattern
    );
    
    
    /*!
     Create a new string that consists of the len characters from the offset
     into the current string.
     @param     this    object pointer
     @param     offset  offset into the current string for the first char
                        (Relative to 1)
     @param     len     number of characters to select
     @param     ppOther returned string object pointer
     @return    If successful, an AStr object which must be released is placed in
                *ppOther and ERESULT_SUCCESS is returned, otherwise an ERESULT_*
                error is returned.
     @warning  Remember to release the returned AStr object if present.
     */
    ERESULT         AStr_Mid(
        ASTR_DATA		*this,
        uint32_t        offset,
        uint32_t        len,
        ASTR_DATA       **ppOther            // [out]
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
     @warning  Remember to release the returned AStr object if present.
     */
    ERESULT         AStr_Right(
        ASTR_DATA		*this,
        uint32_t        len,
        ASTR_DATA       **ppOther           // [out]
    );
    
    
    ERESULT         AStr_SpanW32(
        ASTR_DATA		*this,
        uint32_t        *pIndex,            // [in-out]
        const
        W32CHR_T        *pSetStr            // NUL-terminated set of unicode chars
    );
    
    
    /*!
     Create an array of strings from this string which are delimited by the
     given character. If the character is not found in this string, then
     the string is returned. A trailing deliminating character is ignored.
     @param     this    object pointer
     @param     chr     deliminating character
     @return    If the character is not found in this string or some other error
                condition occurs, then OBJ_NIL is returned. If successful, an
                array of AStr objects which must be released is returned. The
                deliminating character is not included.
     @warning  Remember to release the returned AStr object.
     */
    ASTRARRAY_DATA * AStr_SplitOnCharW32(
        ASTR_DATA       *this,
        const
        W32CHR_T        chr
    );
    
    
    /*!
     Convert this string to a constant string object.
     @param     this    object pointer
     @return    If successful, an AStrC object which must be released,
                otherwise OBJ_NIL.
     @warning   Remember to release the returned AStrC object.
     */
    ASTRC_DATA *    AStr_ToAStrC(
        ASTR_DATA       *this
    );
    
    
    /*!
     Convert this string to an ascii character constant format using escape
     sequences for non-printable characters.
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
     Create a new string from the current one that the first character only
     is translated to lower case.
     @return    If successful, an new AStr object which must be released,
                otherwise OBJ_NIL.
     */
    ASTR_DATA *     AStr_ToLowerName(
        ASTR_DATA      *this
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
     Convert the contents of this string to an integer if possible.
     @return    If successful, an AStr object which must be released,
                otherwise OBJ_NIL.
     @warning  Remember to release the returned AStr object.
     */
    ASTR_DATA *     AStr_ToJson(
        ASTR_DATA       *this
    );
    
    
    /*!
     Create a new string from the current one that is translated to
     SQL single quote constant.
     @return    If successful, an new AStr object which must be released,
                otherwise OBJ_NIL.
     */
    ASTR_DATA *     AStr_ToSQL(
        ASTR_DATA      *this
    );


    /*!
     Copy the string to stderr.
     @return    If successful, ERESULT_SUCCESS, otherwise ERESULT_* error.
     */
    ERESULT         AStr_ToStderr(
        ASTR_DATA       *this
    );
    
    
    /*!
     Create a new string from the current one.
     @return    If successful, an new AStr object which must be released,
                otherwise OBJ_NIL.
     */
    ASTR_DATA *     AStr_ToString(
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
    
    
    /*!
     Create a new string from the current one that the first character only
     is translated to upper case.
     @return    If successful, an new AStr object which must be released,
                otherwise OBJ_NIL.
     */
    ASTR_DATA *     AStr_ToUpperName(
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
    W32STR_DATA *   AStr_ToW32Str(
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

