// vi:nu:et:sts=4 ts=4 sw=4

//****************************************************************
//        Constant NUL-terminated Wide String (W32StrC) Header
//****************************************************************
/*
 * Program
 *			Constant NUL-terminated Wide String (W32StrC)
 * Purpose
 *			This object provides a constant wide NUL-terminated
 *          string which can not be changed. It is important that
 *          its data remain constant since other programs rely
 *          on that.
 *
 * Remarks
 *	1.      Using this object allows for testable code, because a
 *          function, TaskBody() must be supplied which is repeatedly
 *          called on the internal WStrC. A testing unit simply calls
 *          the TaskBody() function as many times as needed to test.
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
#include        <str.h>


#ifndef         W32STRC_H
#define         W32STRC_H



#ifdef	__cplusplus
extern "C" {
#endif
    

    //****************************************************************
    //* * * * * * * * * * * *  Data Definitions  * * * * * * * * * * *
    //****************************************************************


    // W32STRC_DATA and W32STRC_VTBL are defined in "cmn_defs.h"



    /****************************************************************
    * * * * * * * * * * *  Routine Definitions	* * * * * * * * * * *
    ****************************************************************/


    //---------------------------------------------------------------
    //                      *** Class Methods ***
    //---------------------------------------------------------------

    W32STRC_DATA *  W32StrC_Alloc(
        void
    );
    
    
    W32STRC_DATA *  W32StrC_New(
        void
    );
    
    W32STRC_DATA *  W32StrC_NewA(
        const
        char            *pStr
    );
    
    W32STRC_DATA *  W32StrC_NewConW32(
        const
        W32CHR_T        *pStr
    );
    
    W32STRC_DATA *  W32StrC_NewFromStrW32(
        WSTR_DATA       *pStr
    );
    
    W32STRC_DATA *  W32StrC_NewW32(
        const
        W32CHR_T        *pStr
    );
    
    
    

    //---------------------------------------------------------------
    //                      *** Properties ***
    //---------------------------------------------------------------

    const
    W32CHR_T *      W32StrC_getData(
        W32STRC_DATA   *this
    );
    
    
    uint32_t        W32StrC_getLength(
        W32STRC_DATA   *this
    );
    
    

    
    //---------------------------------------------------------------
    //                      *** Methods ***
    //---------------------------------------------------------------

    /*!
     @result
     ERESULT_SUCCESS_EQUAL if this == other,
     ERESULT_SUCCESS_LESS_THAN if this < other
     or ERESULT_SUCCESS_GREATER_THAN if this > other.
     */
    ERESULT         W32StrC_Compare(
        W32STRC_DATA	*this,
        W32STRC_DATA    *pOther
    );
    
    
    /*!
     @param     pString
     Pointer to nul-terminated UTF-8 char string
     @result
     ERESULT_SUCCESS_EQUAL if this == string,
     ERESULT_SUCCESS_LESS_THAN if this < string
     or ERESULT_SUCCESS_GREATER_THAN if this > string.
     */
    ERESULT         W32StrC_CompareA(
        W32STRC_DATA	*this,
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
    ERESULT         W32StrC_CompareW32(
        W32STRC_DATA	*this,
        const
        W32CHR_T        *pString
    );
    
    
    W32STRC_DATA *  W32StrC_Copy(
        W32STRC_DATA    *this
    );
    
    
    /*!
     @result
     If successful, a NUL-terminated UTF-8 string that
     needs to be freed with mem_Free(). Otherwise, NULL.
     */
    char *          W32StrC_CStringA(
        W32STRC_DATA	*this
    );
    
    
    uint32_t        W32StrC_Hash(
        W32STRC_DATA    *this
    );
    
    
    W32STRC_DATA *  W32StrC_InitA(
        W32STRC_DATA    *this,
        const
        char            *pStr
    );
    
    W32STRC_DATA *  W32StrC_InitConW32(
        W32STRC_DATA    *this,
        const
        W32CHR_T        *pStr
    );
    
    W32STRC_DATA *  W32StrC_InitW32(
        W32STRC_DATA    *this,
        const
        W32CHR_T        *pStr
    );
    
    
    /*!
     Create a new string from a portion of the current string starting
     at index with len number of characters.
     @return    If successful, an WStrC object which must be released,
                 otherwise OBJ_NIL.
     */
    W32STRC_DATA *  W32StrC_Mid(
        W32STRC_DATA    *this,
        uint32_t        offset,         /* Relative to 1 */
        uint32_t        len
    );
    
    
    /*!
     Create a string that describes this object and the
     objects within it.
     @return    If successful, an AStr object which must be released,
                otherwise OBJ_NIL.
     */
    ASTR_DATA *     W32StrC_ToDebugString(
        W32STRC_DATA    *this,
        int             indent
    );
    
    

    
#ifdef	__cplusplus
}
#endif

#endif	/* W32STRC_H */

