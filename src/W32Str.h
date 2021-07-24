// vi:nu:et:sts=4 ts=4 sw=4

//****************************************************************
//                  Mutable Wide (W32CHR_T) NUL-terminated String (W32Str) Header
//****************************************************************
/*
 * Program
 *          Mutable Wide (W32CHR_T) NUL-terminated String (W32Str)
 * Purpose
 *          This object provides a NUL-terminated Wide string
 *          and its manipulation.  While this takes more room,
 *          it is very efficient from an access point of view
 *          for parsing applications.
 *
 * Remarks
 *  1.      All offsets/indices are relative to one. Zero is normally
 *          used to denote beginning or end of the data depending on
 *          the operation.
 *  2.      obj's Misc fields are not used by this object.
 *
 * History
 *  06/08/2015 Generated
 *  07/15/2021 Regenerated and rebuilt
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
#include        <AStr.h>
#include        <AStrC.h>


#ifndef         W32STR_H
#define         W32STR_H


//#define   W32STR_IS_IMMUTABLE     1
#define   W32STR_JSON_SUPPORT       1
//#define   W32STR_SINGLETON        1



typedef struct W32Array_data_s  W32ARRAY_DATA;            // Inherits from OBJ


#ifdef  __cplusplus
extern "C" {
#endif
    

    //****************************************************************
    //* * * * * * * * * * * *  Data Definitions  * * * * * * * * * * *
    //****************************************************************

    // W32STR_DATA and W32STR_VTBL are defined in "cmn_defs.h"
    //typedef struct W32Str_data_s  W32STR_DATA;            // Inherits from OBJ
    typedef struct W32Str_class_data_s W32STR_CLASS_DATA;   // Inherits from OBJ

    /*** See above!
    typedef struct W32Str_vtbl_s  {
        OBJ_IUNKNOWN    iVtbl;              // Inherited Vtbl.
        // Put other methods below this as pointers and add their
        // method names to the vtbl definition in W32Str_object.c.
        // Properties:
        // Methods:
        //bool        (*pIsEnabled)(W32STR_DATA *);
    } W32STR_VTBL;
    ***/

    typedef struct W32Str_class_vtbl_s    {
        OBJ_IUNKNOWN    iVtbl;              // Inherited Vtbl.
        // Put other methods below this as pointers and add their
        // method names to the vtbl definition in W32Str_object.c.
        // Properties:
        // Methods:
        //bool        (*pIsEnabled)(W32STR_DATA *);
    } W32STR_CLASS_VTBL;




    /****************************************************************
    * * * * * * * * * * *  Routine Definitions  * * * * * * * * * * *
    ****************************************************************/


    //---------------------------------------------------------------
    //                      *** Class Methods ***
    //---------------------------------------------------------------

#ifdef  W32STR_SINGLETON
    W32STR_DATA *   W32Str_Shared (
        void
    );

    void            W32Str_SharedReset (
        void
    );
#endif


   /*!
     Allocate a new Object and partially initialize. Also, this sets an
     indicator that the object was alloc'd which is tested when the object is
     released.
     @return    pointer to W32Str object if successful, otherwise OBJ_NIL.
     */
    W32STR_DATA *   W32Str_Alloc (
        void
    );
    
    
    OBJ_ID          W32Str_Class (
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
         0 if str1 == str2
         -1 if str1 < str2
         1 if str1 > str2
         -2 if error
     */
    int             W32Str_Cmp(
        const
        W32CHR_T        *pStr1,
        const
        W32CHR_T        *pStr2
    );

    int             W32Str_CmpA(
        const
        W32CHR_T        *pStr,
        const
        char            *pStrA
    );

    int             W32Str_CmpAN(
        const
        W32CHR_T        *pStr,
        const
        char            *pStrA,
        uint32_t        n
    );

    int             W32Str_CmpN(
        const
        W32CHR_T        *pStr1,
        const
        W32CHR_T        *pStr2,
        uint32_t        n
    );


    uint32_t        W32Str_StrLen(
        const
        W32CHR_T        *pData
    );


    W32STR_DATA *   W32Str_New (
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


    W32STR_DATA *   W32Str_NewFromTimeNow(
        void
    );


#ifdef  W32STR_JSON_SUPPORT
    W32STR_DATA *   W32Str_NewFromJsonString (
        ASTR_DATA       *pString
    );

    W32STR_DATA *   W32Str_NewFromJsonStringA (
        const
        char            *pStringA
    );
#endif


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


    uint32_t        W32Str_getSize (
        W32STR_DATA       *this
    );



    //---------------------------------------------------------------
    //                      *** Methods ***
    //---------------------------------------------------------------

    ERESULT         W32Str_Append(
        W32STR_DATA     *this,
        W32STR_DATA     *pOther
    );


    ERESULT         W32Str_AppendA(
        W32STR_DATA     *this,
        const
        char            *pStr               // UTF-8 String
    );


    ERESULT         W32Str_AppendPrintA(
        W32STR_DATA     *this,
        const
        char            *pFormat,
        ...
    );


    ERESULT         W32Str_AppendStrA(
        W32STR_DATA     *this,
        ASTR_DATA       *pStr
    );


    ERESULT         W32Str_AppendUtf8File(
        W32STR_DATA     *this,
        PATH_DATA       *pPath
    );


    ERESULT         W32Str_AppendW32(
        W32STR_DATA     *this,
        uint32_t        len,                // Data Length or 0 to use NUL-terminator
        const
        W32CHR_T        *pStr
    );


    // Append len number of chr's to string.
    ERESULT         W32Str_AppendCharW32(
        W32STR_DATA     *this,
        uint32_t        len,
        const
        W32CHR_T        chr
    );

    /*!
     Assign the contents of this object to the other object (ie
     this -> other).  Any objects in other will be released before
     a copy of the object is performed.
     Example:
     @code
        ERESULT eRc = W32Str_Assign(this,pOther);
     @endcode
     @param     this    object pointer
     @param     pOther  a pointer to another W32STR object
     @return    If successful, ERESULT_SUCCESS otherwise an
                ERESULT_* error
     */
    ERESULT         W32Str_Assign (
        W32STR_DATA     *this,
        W32STR_DATA     *pOther
    );


    // Search the string for the provided char. If *pIndex
    // is set to 0, then the search begins at the begin-
    // ning of the string.
    ERESULT         W32Str_CharFindNextW32(
        W32STR_DATA     *this,
        uint32_t        *pIndex,            // [in-out]
        const
        W32CHR_T        chr
    );


    /*! Scan the string until one of the characters in the given
        NUL-terminated array/string are found. Start searching at the
        given index and bump it as the search continues.
     @param     this    object pointer
     @param     pIndex  Index into the string to start at and where the
                        scan stopped. 0 will be assumed to be 1.
     @param     pChrs   pointer to a wide char NUL-terminated string.
     @return    If one of the chars is found, ERESULT_SUCCESS.
                ERESULT_OUT_OF_RANGE if none of the chars are found.
     */
    ERESULT         W32Str_CharsFindNextW32(
        W32STR_DATA     *this,
        uint32_t        *pIndex,
        const
        W32CHR_T        *pChrs          // NUL-Terminated array of wide chars
    );


    // Search the string backwards for the provided char. If
    // *pIndex is set to 0, then the search begins at the
    // end of the string.
    ERESULT         W32Str_CharFindPrevW32(
        W32STR_DATA     *this,
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
        W32STR_DATA     *this,
        uint32_t        offset              // Relative to 1
    );


    /*! Simple scan and replace of single characters
     */
    ERESULT         W32Str_CharReplaceAllW32(
        W32STR_DATA     *this,
        const
        W32CHR_T        chrSrch,
        const
        W32CHR_T        chrRepl
    );


    ERESULT         W32Str_CharPutW32(
        W32STR_DATA     *this,
        uint32_t        offset,             // Relative to 1
        const
        W32CHR_T        chr
    );


    /*!
     Compare the two provided objects.
     @return    0  if this == other
                <0 if this < other
                >0 if this > other
     */
    int             W32Str_Compare (
        W32STR_DATA     *this,
        W32STR_DATA     *pOther
    );


    /*!
     @param     this        object pointer
     @param     pString     Pointer to nul-terminated UTF-8 char string
     @return    0  if this == other
                <0 if this < other
                >0 if this > other
     */
    int             W32Str_CompareA(
        W32STR_DATA     *this,
        const
        char            *pString
    );


    /*!
     Compare the given UTF-8 String with this string ignoring case.
     @param     this        object pointer
     @param     pString     Pointer to nul-terminated UTF-8 char string
     @return    0  if this == other
                <0 if this < other
                >0 if this > other
     */
    int             W32Str_CompareA_IC(
        W32STR_DATA     *this,
        const
        char            *pString
    );


    int             W32Str_CompareA_N(
        W32STR_DATA     *this,
        const
        char            *pString,
        uint32_t        n
    );


    /*!
     Compare the current string
     @param     pString     Pointer to nul-terminated wide char string
     @param     fIgnoreCase if true, all comparisons exclude case
     @param     fIgnoreWS   if true, white-space is skipped as part of comparison
     @return    0  if this == other
                <0 if this < other
                >0 if this > other
     */
    int             W32Str_CompareW32(
        W32STR_DATA     *this,
        const
        W32CHR_T        *pString,
        bool            fIgnoreCase,
        bool            fIgnoreWS
    );


    /*!
     Copy the current object creating a new object.
     Example:
     @code
        W32Str      *pCopy = W32Str_Copy(this);
     @endcode
     @param     this    object pointer
     @return    If successful, a W32STR object which must be
                released, otherwise OBJ_NIL.
     @warning   Remember to release the returned object.
     */
    W32STR_DATA *   W32Str_Copy (
        W32STR_DATA     *this
    );


    /*!
     @result
        If successful, a NUL-terminated UTF-8 string that
        needs to be freed with mem_Free(). Otherwise, NULL.
     */
    char *          W32Str_CStringA(
        W32STR_DATA     *this,
        uint32_t        *pLen       // Optional returned string length
                                    // less terminating NUL
    );


    /*!
     Copy the current object creating a new object.
     Example:
     @code
        W32Str      *pDeepCopy = W32Str_Copy(this);
     @endcode
     @param     this    object pointer
     @return    If successful, a W32STR object which must be
                released, otherwise OBJ_NIL.
     @warning   Remember to release the returned object.
     */
    W32STR_DATA *   W32Str_DeepCopy (
        W32STR_DATA     *this
    );


    /*! Escape double parentheses, backslashes, and certain
     whitespace so that the line can be used in a C program
     string constant.
     @result
        If successful, ERESULT_SUCCESS. Otherwise, ERESULT_FAULURE.
     */
    ERESULT         W32Str_EscapeForC(
        W32STR_DATA     *this
    );


    /*! Scan the string for an occurrence of the given UTF-8 string.
        Start searching at the given index and bump it as the search
        continues.
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


    /*! Scan the string for the next occurrence of the given wide
        nul-terminated string is found.
     @param     this    object pointer
     @param     pStrW32 pointer to a wide char nul-terminated string.
     @param     pIndex  Index into the string to start at and where the
                        scan stopped.
     @return    If the string is found, ERESULT_SUCCESS and the index
                is adjusted to the beginning of where the string is.
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
        W32STR_DATA     *this,
        const
        W32CHR_T        *pSetStr,
        uint32_t        *pIndex             // [in-out]
    );


    W32STR_DATA *   W32Str_Init (
        W32STR_DATA     *this
    );


    ERESULT         W32Str_InsertA(
        W32STR_DATA     *this,
        uint32_t        offset,
        const
        char            *pStr
    );


    // Tests the string data for any characters
    // larger than 0x7E.
    // If found, returns FAILURE.
    // Otherwise, returns SUCCESS.
    ERESULT         W32Str_IsOnlyASCII(
        W32STR_DATA     *this
    );


    W32STR_DATA *   W32Str_Left(
        W32STR_DATA     *this,
        uint32_t        len
    );


    ERESULT         W32Str_Lower(
        W32STR_DATA     *this
    );


    W32STR_DATA *   W32Str_Mid(
        W32STR_DATA     *this,
        uint32_t        offset,
        uint32_t        len
    );


    ERESULT         W32Str_Remove(
        W32STR_DATA     *this,
        uint32_t        offset,
        uint32_t        len
    );


    /*!
     Remove all trailing '\r' or '\n'.
     sequences for non-printable character.
     @param     this    object pointer
     @return    If successful, ERESULT_SUCCESS. Otherwise, an ERESULT_* error.
     */
    ERESULT         W32Str_RemoveNL(
        W32STR_DATA     *this
    );


    W32STR_DATA *   W32Str_Right(
        W32STR_DATA     *this,
        uint32_t        len
    );


    // Scans this string until it finds a character that
    // is not in the Nul-terminated Set String.
    // Returns:
    //      0 if the end of string is found.
    //      n where n is the offset into the string
    ERESULT         W32Str_SpanW32(
        W32STR_DATA     *this,
        uint32_t        *pIndex,            // [in-out]
        const
        W32CHR_T        *pSetStr
    );


    W32ARRAY_DATA * W32Str_SplitOnCharW32(
        W32STR_DATA     *this,
        const
        W32CHR_T        chr
    );


    W32ARRAY_DATA * W32Str_SplitOnCharsW32(
        W32STR_DATA     *this,
        const
        W32CHR_T        *pChrs              // NUL-Terminated Array
    );


    /*!
     Convert this string to an ascii character constant format using escape
     sequences for non-printable character.
     @param     this    object pointer
     @return    If successful, an AStr object which must be released,
                otherwise OBJ_NIL.
     @warning   Remember to release the returned AStr object.
     */
    ASTR_DATA *     W32Str_ToAStr(
        W32STR_DATA     *this
    );


    // ToInt32() tries to convert the string to a signed 32-bit
    // number with format [+ | -][0..9]*
    // 0 is returned if the number is mal-formed.
    int32_t         W32Str_ToInt32(
        W32STR_DATA     *this
    );


#ifdef  W32STR_JSON_SUPPORT
    /*!
     Create a string that describes this object and the objects within it in
     HJSON formt. (See hjson object for details.)
     Example:
     @code
     ASTR_DATA      *pDesc = W32Str_ToJson(this);
     @endcode
     @param     this    object pointer
     @return    If successful, an AStr object which must be released containing the
                JSON text, otherwise OBJ_NIL.
     @warning   Remember to release the returned AStr object.
     */
    ASTR_DATA *     W32Str_ToJson (
        W32STR_DATA     *this
    );
#endif


    /*!
     Create a string that describes this object and the objects within it.
     Example:
     @code 
        ASTR_DATA      *pDesc = W32Str_ToDebugString(this,4);
     @endcode 
     @param     this    object pointer
     @param     indent  number of characters to indent every line of output, can be 0
     @return    If successful, an AStr object which must be released containing the
                description, otherwise OBJ_NIL.
     @warning   Remember to release the returned AStr object.
     */
    ASTR_DATA *     W32Str_ToDebugString (
        W32STR_DATA     *this,
        int             indent
    );
    
    
    ERESULT         W32Str_ToFile(
        W32STR_DATA     *this,
        FILE            *pOut
    );


    ERESULT         W32Str_ToUtf8File(
        W32STR_DATA     *this,
        PATH_DATA       *pPath
    );


    // Trim() removes white-space from both ends of the string.
    // White-space is considered any character that is numeri-
    // cally less than or equal to a space ( ' ' ).
    ERESULT         W32Str_Trim(
        W32STR_DATA     *this
    );


    ERESULT         W32Str_Truncate(
        W32STR_DATA     *this,
        uint32_t        len
    );


    ERESULT         W32Str_Upper(
        W32STR_DATA     *this
    );



    
#ifdef  __cplusplus
}
#endif

#endif  /* W32STR_H */

