// vi:nu:et:sts=4 ts=4 sw=4

//****************************************************************
//          Constant NUL-terminated Wide String (W32StrC) Header
//****************************************************************
/*
 * Program
 *			Constant NUL-terminated Wide String (W32StrC)
 * Purpose
 *          This object provides a constant wide NUL-terminated
 *          string which can not be changed. It is important that
 *          its data remain constant since other programs rely
 *          on that.
 *
 *          Advance(), LookAhead() and Reset() provide a mechanism
 *          for scanning the string. It does use the obj's Misc
 *          field.
 *
 * Remarks
 *	1.      OBJ_FLAG_USER1 is used by this object.
 *  2.      obj's Misc fields are not used by this object unless
 *          the scan methods (Advance, LookAhead or Reset) are
 *          used.
 *
 * History
 *  02/19/2016 Generated
 *	01/23/2020 Regenerated
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
#include        <W32Str.h>
#include        <stdio.h>


#ifndef         W32STRC_H
#define         W32STRC_H


#define     W32STRC_IS_CONSTANT     1
#define     W32STRC_JSON_SUPPORT    1
//#define   W32STRC_SINGLETON       1





#ifdef	__cplusplus
extern "C" {
#endif
    

    //****************************************************************
    //* * * * * * * * * * * *  Data Definitions  * * * * * * * * * * *
    //****************************************************************


#ifdef DEFINED_IN_CMNDEFS
    typedef struct W32StrC_data_s	W32STRC_DATA;            // Inherits from OBJ
    typedef struct W32StrC_class_data_s W32STRC_CLASS_DATA;   // Inherits from OBJ
#endif

    typedef struct W32StrC_vtbl_s	{
        OBJ_IUNKNOWN    iVtbl;              // Inherited Vtbl.
        // Put other methods below this as pointers and add their
        // method names to the vtbl definition in W32StrC_object.c.
        // Properties:
        // Methods:
        const
        W32CHR_T *  (*pGetData)(W32STRC_DATA *);
        uint32_t    (*pGetLength)(W32STRC_DATA *);
    } W32STRC_VTBL;

    typedef struct W32StrC_class_vtbl_s	{
        OBJ_IUNKNOWN    iVtbl;              // Inherited Vtbl.
        // Put other methods below this as pointers and add their
        // method names to the vtbl definition in W32StrC_object.c.
        // Properties:
        // Methods:
        //bool        (*pIsEnabled)(W32STRC_DATA *);
    } W32STRC_CLASS_VTBL;




    /****************************************************************
    * * * * * * * * * * *  Routine Definitions	* * * * * * * * * * *
    ****************************************************************/


    //---------------------------------------------------------------
    //                      *** Class Methods ***
    //---------------------------------------------------------------

#ifdef  W32STRC_SINGLETON
    W32STRC_DATA *  W32StrC_Shared (
        void
    );

    void            W32StrC_SharedReset (
        void
    );
#endif


   /*!
     Allocate a new Object and partially initialize. Also, this sets an
     indicator that the object was alloc'd which is tested when the object is
     released.
     @return    pointer to W32StrC object if successful, otherwise OBJ_NIL.
     */
    W32STRC_DATA *  W32StrC_Alloc (
        void
    );
    
    
    OBJ_ID          W32StrC_Class (
        void
    );
    
    
    W32STRC_DATA *  W32StrC_New (
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

    W32STRC_DATA *  W32StrC_NewFromW32Str(
        W32STR_DATA     *pStr
    );

    W32STRC_DATA *  W32StrC_NewFromW32 (
        uint32_t        len,
        const
        W32CHR_T        *pStrW32
    );

    W32STRC_DATA *  W32StrC_NewW32(
        const
        W32CHR_T        *pStr
    );


#ifdef  W32STRC_JSON_SUPPORT
    W32STRC_DATA *   W32StrC_NewFromJsonString(
        ASTR_DATA       *pString
    );

    W32STRC_DATA *   W32StrC_NewFromJsonStringA(
        const
        char            *pStringA
    );
#endif



    //---------------------------------------------------------------
    //                      *** Properties ***
    //---------------------------------------------------------------

    uint32_t        W32StrC_getCrcIEEE(
        W32STRC_DATA    *this
    );


    const
    W32CHR_T *      W32StrC_getData(
        W32STRC_DATA   *this
    );


    uint32_t        W32StrC_getLength(
        W32STRC_DATA   *this
    );


    uint32_t        W32StrC_getSize(
        W32STRC_DATA     *this
    );


    
    //---------------------------------------------------------------
    //                      *** Methods ***
    //---------------------------------------------------------------

    /*!
     Advance the index into the string by the offset amount.
     @warning   This method uses obj's misc field.
     */
    void            W32StrC_Advance(
        W32STRC_DATA    *this,
        int32_t         offset
    );


    /*!
     Assign the contents of this object to the other object (ie
     this -> other).  Any objects in other will be released before
     a copy of the object is performed.
     Example:
     @code
        ERESULT eRc = W32StrC_Assign(this,pOther);
     @endcode
     @param     this    object pointer
     @param     pOther  a pointer to another W32STRC object
     @return    If successful, ERESULT_SUCCESS otherwise an
                ERESULT_* error
     */
    ERESULT         W32StrC_Assign (
        W32STRC_DATA    *this,
        W32STRC_DATA    *pOther
    );


    /*!
     @return    0  if this == other
                <0 if this < other
                >0 if this > other
     */
    int             W32StrC_Compare(
        W32STRC_DATA    *this,
        W32STRC_DATA    *pOther
    );


    /*!
     @param     pString
     Pointer to nul-terminated UTF-8 char string
     @return    0  if this == other
                <0 if this < other
                >0 if this > other
     */
    int             W32StrC_CompareA(
        W32STRC_DATA    *this,
        const
        char            *pString
    );


    /*!
     @param     pString
     Pointer to nul-terminated wide char string
     @return    0  if this == other
                <0 if this < other
                >0 if this > other
     */
    int             W32StrC_CompareW32(
        W32STRC_DATA    *this,
        const
        W32CHR_T        *pString
    );


    W32STRC_DATA *  W32StrC_Copy(
        W32STRC_DATA    *this
    );


    /*!
     @result        If successful, a NUL-terminated UTF-8 string that
                    needs to be freed with mem_Free(). Otherwise, NULL.
     */
    char *          W32StrC_CStringA(
        W32STRC_DATA    *this
    );


    W32CHR_T        W32StrC_GetCharW32(
        W32STRC_DATA    *this,
        uint32_t        offset              // Relative to 1
    );


    uint32_t        W32StrC_Hash(
        W32STRC_DATA    *this
    );


    W32STRC_DATA *  W32StrC_Init (
        W32STRC_DATA    *this
    );


    /*!
     Create a new string from the left  portion of the current string
     with len number of characters.
     @return    If successful, an WStrC object which must be released,
                 otherwise OBJ_NIL.
     */
    W32STRC_DATA *  W32StrC_Left(
        W32STRC_DATA    *this,
        uint32_t        len
    );


    /*!
     Return the character pointed at by the obj's Misc plus offset.
     @return    If successful, the indexed character, otherwise 0.
     @warning   This method uses obj's misc field.
     */
    W32CHR_T        W32StrC_LookAhead(
        W32STRC_DATA    *this,
        uint32_t        offset              // Relative to 1
    );


    /*!
     Match the given character against the current obj's Misc
     index into the string.  If they match, advance the scan.
     @return    If they match, return true otherwise false.
     @warning   This method uses obj's misc field.
     */
    bool            W32StrC_MatchChr(
        W32STRC_DATA    *this,
        W32CHR_T        chr
    );


    /*!
     Match the given UTF-8 String against the current obj's Misc
     index into the string.  If they match, it advances the scan.
     @return    If they match, return true otherwise false.
     @warning   This method uses obj's misc field.
     */
    bool            W32StrC_MatchStrA(
        W32STRC_DATA    *this,
        const
        char            *pStrA
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
     Reset the scan index.
     @warning   This method uses obj's misc field.
     */
    void            W32StrC_Reset(
        W32STRC_DATA    *this
    );


    W32STRC_DATA *  W32StrC_Right(
        W32STRC_DATA    *this,
        uint32_t        len
    );


#ifdef  W32STRC_JSON_SUPPORT
    /*!
     Create a string that describes this object and the objects within it in
     HJSON formt. (See hjson object for details.)
     Example:
     @code
     ASTR_DATA      *pDesc = W32StrC_ToJson(this);
     @endcode
     @param     this    object pointer
     @return    If successful, an AStr object which must be released containing the
                JSON text, otherwise OBJ_NIL and LastError set to an appropriate
                ERESULT_* error code.
     @warning   Remember to release the returned AStr object.
     */
    ASTR_DATA *     W32StrC_ToJson(
        W32STRC_DATA   *this
    );
#endif


    /*!
     Create a string that describes this object and the objects within it.
     Example:
     @code 
        ASTR_DATA      *pDesc = W32StrC_ToDebugString(this,4);
     @endcode 
     @param     this    object pointer
     @param     indent  number of characters to indent every line of output, can be 0
     @return    If successful, an AStr object which must be released containing the
                description, otherwise OBJ_NIL.
     @warning   Remember to release the returned AStr object.
     */
    ASTR_DATA *    W32StrC_ToDebugString (
        W32STRC_DATA    *this,
        int             indent
    );
    
    

    
#ifdef	__cplusplus
}
#endif

#endif	/* W32STRC_H */

