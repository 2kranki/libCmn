// vi:nu:et:sts=4 ts=4 sw=4 tw=90

//****************************************************************
//       Constant NUL-terminated UTF-8 String (AStrC) Header
//****************************************************************
/*
 * Program
 *			Constant NUL-terminated UTF-8 String (AStrC)
 * Purpose
 *			This object provides a constant (ie immutable) NUL-
 *          terminated UTF-8 String.  This is the immutable
 *          version of AStr.
 *
 * Remarks
 *	1.      None
 *
 * History
 *	02/19/2016 Generated
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
#include        <path.h>
#include        <str.h>


#ifndef         ASTRC_H
#define         ASTRC_H



#ifdef	__cplusplus
extern "C" {
#endif
    

    //****************************************************************
    //* * * * * * * * * * * *  Data Definitions  * * * * * * * * * * *
    //****************************************************************


    // ASTRC_DATA and ASTRC_VTBL are defined in "str.h"

    

    /****************************************************************
    * * * * * * * * * * *  Routine Definitions	* * * * * * * * * * *
    ****************************************************************/


    //---------------------------------------------------------------
    //                      *** Class Methods ***
    //---------------------------------------------------------------

    ASTRC_DATA *    AStrC_Alloc(
        void
    );
    
    
    ASTRC_DATA *    AStrC_New(
        void
    );
    
    
    /*!
     Create a new AStrC object from the provided character string
     copying it for the new object.
     @return:   If successful, an AStrC object which must be released,
                otherwise OBJ_NIL.
     */
    ASTRC_DATA *    AStrC_NewA(
        const
        char            *pStr
    );
    
    
    ASTRC_DATA *    AStrC_NewW32(
        const
        W32CHR_T        *pStr
    );
    
    
    ASTRC_DATA *   AStrC_NewFromAStr(
        ASTR_DATA       *pStr
    );
    
    
    /*!
     Create a new AStrC object from the provided character constant.
     However, use the character constant as is.  Upon release of the
     new object, the new AStrC object will not from the provided
     character constant and will will just release the object.
     @return:   If successful, an AStrC object which must be released,
                otherwise OBJ_NIL.
     */
    ASTRC_DATA *   AStrC_NewFromConstant(
        const
        char            *pStrA
    );
    
    


    //---------------------------------------------------------------
    //                      *** Properties ***
    //---------------------------------------------------------------

    const
    char *          AStrC_getData(
        ASTRC_DATA      *this
    );
    
    
    /*!
     @return:   return the number of Ascii or Unicode characters in
                the string, not the actual size of the string in
                memory.  -1 indicates that an error occurred.
     */
    uint32_t        AStrC_getLength(
        ASTRC_DATA      *this
    );
    
    

    
    //---------------------------------------------------------------
    //                      *** Methods ***
    //---------------------------------------------------------------

    /*!
     Create a new string that is the current string concatenated with
     the contents of the provided AStrC object.
     @return:   If successful, an AStrC object which must be released,
                 otherwise OBJ_NIL and an Error Code is set.
     */
    ASTRC_DATA *    AStrC_Append(
        ASTRC_DATA      *this,
        ASTRC_DATA      *pOther
    );
    
    
    /*!
     Create a new string that is the current string concatenated with
     the contents of the provided UTF-8 string.
     @return:   If successful, an AStrC object which must be released,
                 otherwise OBJ_NIL and an Error Code is set.
     */
    ASTRC_DATA *    AStrC_AppendA(
        ASTRC_DATA      *this,
        const
        char            *pStr
    );
    
    
    /*!
     Create a new string that is the current string concatenated with
     the contents of the provided string.
     @return:   If successful, an AStrC object which must be released,
                 otherwise OBJ_NIL and an Error Code is set.
     */
    ASTRC_DATA *    AStrC_AppendAStr(
        ASTRC_DATA      *this,
        ASTR_DATA       *pStr
    );


    /*!
     Create a new string that is the current string concatenated with
     the contents of the UTF8 File.
     @return:   If successful, an AStrC object which must be released,
                 otherwise OBJ_NIL and an Error Code is set.
     */
    ASTRC_DATA *    AStrC_AppendUtf8File(
        ASTRC_DATA      *this,
        PATH_DATA       *pPath
    );
    
    
    /*!
     Compare 'this' to 'pOther'.
     @param     this    object pointer
     @param     pOther  Other String Object Pointer
     @return    If str == const, ERESULT_SUCCESS_EQUAL. Otherwise,
                ERESULT_SUCCESS_LESS_THAN, ERESULT_SUCCESS_GREATER_THAN or an
                ERESULT_* error code.
     */
    ERESULT         AStrC_Compare(
        ASTRC_DATA      *this,
        ASTRC_DATA      *pOther
    );
    
    ERESULT         AStrC_CompareA(
        ASTRC_DATA		*this,
        const
        char            *pData
    );
    
    ERESULT         AStrC_CompareW32(
        ASTRC_DATA		*this,
        const
        W32CHR_T        *pData
    );
    
    
    ASTRC_DATA *    AStrC_Copy(
        ASTRC_DATA      *this
    );
    
    
    ASTRC_DATA *    AStrC_DeepCopy(
        ASTRC_DATA      *this
    );
    
    
    uint32_t        AStrC_Hash(
        ASTRC_DATA      *this
    );
    
    
    ASTRC_DATA *   AStrC_InitA(
        ASTRC_DATA     *this,
        const
        char           *pStr
    );
    
    ASTRC_DATA *   AStrC_InitW32(
        ASTRC_DATA     *this,
        const
        W32CHR_T       *pStr
    );
    
    
    ASTRC_DATA *    AStrC_Mid(
        ASTRC_DATA      *this,
        uint32_t        offset,
        uint32_t        len
    );
    
    
    /*!
     Create an AStr object from this string.
     @return:   If successful, an AStr object which must be released,
                otherwise OBJ_NIL.
     */
    ASTR_DATA *     AStrC_ToAStr(
        ASTRC_DATA      *this
    );
    
    
    /*!
     Create an AStr object from this string.
     @return:   If successful, an AStr object which must be released,
                otherwise OBJ_NIL.
     */
    ASTRC_DATA *    AStrC_ToString(
        ASTRC_DATA      *this
    );
    
    
    /*!
     Create a string that describes this object and the
     objects within it.
     @return:   If successful, an AStr object which must be released,
                otherwise OBJ_NIL.
     */
    ASTR_DATA *    AStrC_ToDebugString(
        ASTRC_DATA      *this,
        int             indent
    );
    
    
    /*!
     Create an W32Str object from this string.
     @return:   If successful, an W32Str object which must be released,
                otherwise OBJ_NIL.
     */
    W32STR_DATA *   AStrC_ToW32Str(
        ASTRC_DATA      *this
    );
    
    
    /*!
     Remove white-space from the beginning and ending of the current string.
     @return:   If successful, an new AStr object which must be released,
                otherwise OBJ_NIL.
     */
    ASTRC_DATA *    AStrC_Trim(
        ASTRC_DATA		*this
    );
    
    

    
#ifdef	__cplusplus
}
#endif

#endif	/* ASTRC_H */

