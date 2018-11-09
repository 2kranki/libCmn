// vi:nu:et:sts=4 ts=4 sw=4

//****************************************************************
//                  Text Token (token) Header
//****************************************************************
/*
 * Program
 *			Text Token (token)
 * Purpose
 *			This object provides a standardized way of handling
 *          pieces of text parsed from a text string. Initially,
 *          tokens consist of individual characters. As they are
 *          combined into character strings, those strings must
 *          stored in an external table such as szTbl.
 *
 * Remarks
 *	1.      The file index should remain constant and valid for the
 *          life of this object.
 *  2.      String Tokens must be unique per string so that they can 
 *          be used in lieu of an actual string.  The token is used
 *          as an index into the shared szTbl.
 *
 * History
 *	05/26/2015 Generated
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
#include        <srcLoc.h>
#include        <W32Str.h>
#include        <W32StrC.h>


#ifndef         TOKEN_H
#define         TOKEN_H



#ifdef	__cplusplus
extern "C" {
#endif
    

    //****************************************************************
    //* * * * * * * * * * * *  Data Definitions  * * * * * * * * * * *
    //****************************************************************


    typedef struct token_data_s     TOKEN_DATA;

    typedef struct token_vtbl_s	{
        OBJ_IUNKNOWN    iVtbl;              // Inherited Vtbl.
        // Put other methods below this as pointers and add their
        // method names to the vtbl definition in table_object.c.
    } TOKEN_VTBL;
    
    
    typedef struct tokenList_data_s	TOKENLIST_DATA;

    
    typedef enum token_type_e {
        TOKEN_TYPE_UNKNOWN=0,
        TOKEN_TYPE_CHAR,            // A single Unicode character in UTF-8
        TOKEN_TYPE_FLOAT,           // double
        TOKEN_TYPE_INTEGER,         // int64_t
        TOKEN_TYPE_STR_UTF8,        // UTF-8 String Token
        TOKEN_TYPE_STRCON_UTF8,     // UTF-8 String Constant Token
        TOKEN_TYPE_STRTOKEN,        // String Token for szTbl
        TOKEN_TYPE_W32CHAR,         // A single Unicode character
        TOKEN_TYPE_USER=32          // First User Type allowed
    } TOKEN_TYPE;
    
    
    typedef enum token_misc_e {
        TOKEN_MISC_UNKNOWN=0,
        // Type of Integer Constant for TOKEN_TYPE_INTEGER
        TOKEN_MISC_SI,              // signed int
        TOKEN_MISC_UI,              // unsigned int
        TOKEN_MISC_SL,              // signed long
        TOKEN_MISC_UL,              // unsigned long
        TOKEN_MISC_SLL,             // signed long long
        TOKEN_MISC_ULL,             // unsigned long long
    } TOKEN_MISC;
    
    



    /****************************************************************
    * * * * * * * * * * *  Routine Definitions	* * * * * * * * * * *
    ****************************************************************/


    //---------------------------------------------------------------
    //                      *** Class Methods ***
    //---------------------------------------------------------------

    TOKEN_DATA *    token_Alloc(
        void
    );
    
    
    OBJ_ID          token_Class(
        void
    );
    
    
    TOKEN_DATA *     token_NewCharW32(
        SRCLOC          *pLoc,
        int32_t         cls,
        W32CHR_T        chr
    );
    
    
    TOKEN_DATA *    token_NewInteger(
        SRCLOC          *pLoc,
        int32_t         cls,
        int64_t         integer
    );

    
    TOKEN_DATA *     token_NewFromJSONString(
        ASTR_DATA       *pString
    );
    
    TOKEN_DATA *     token_NewFromJSONStringA(
        const
        char            *pString
    );
    
   
    TOKEN_DATA *     token_NewFromW32STR(
        SRCLOC          *pLoc,
        int32_t         cls,
        W32STR_DATA     *pString
    );
    
    
    TOKEN_DATA *     token_NewStrA(
        SRCLOC          *pLoc,
        int32_t         cls,
        const
        char            *pStr
    );
    
    
    TOKEN_DATA *     token_NewStrW32(
        SRCLOC          *pLoc,
        int32_t         cls,
        const
        W32CHR_T        *pStr
    );
    
    
    /*!
     Create a new token object with the given parameter of a String Token Number.
     Normally, String Token Numbers are indexes into an szTbl object that will 
     return the string.
     @param     pLoc        pointer to a source location
     @param     cls         Token class (see PPLEX.H for examples)
     @param     token       Token String Number (probably returned by szTbl)
     @return    If successful, a TOKEN_DATA pointer otherwise OBJ_NIL
     */
    TOKEN_DATA *     token_NewStrToken(
        SRCLOC          *pLoc,
        int32_t         cls,
        uint32_t        token
    );
    
    
    

    //---------------------------------------------------------------
    //                      *** Properties ***
    //---------------------------------------------------------------

    /* A Character Token is only one character.
     */
    W32CHR_T        token_getChrW32(
        TOKEN_DATA      *this
    );
    
    bool            token_setChrW32(
        TOKEN_DATA      *this,
        W32CHR_T        value
    );
    
    
    /* Class is used to categorize the token. For instance, if
     * the token type is text, then the class might be an 
     * identifier, keyword, etc.
     */
    int32_t         token_getClass(
        TOKEN_DATA      *this
    );
    
    bool            token_setClass(
        TOKEN_DATA      *this,
        int32_t         value
    );
    
    
    uint16_t        token_getColNo(
        TOKEN_DATA      *this
    );
    
    bool            token_setColNo(
        TOKEN_DATA      *this,
        uint16_t        value
    );
    
    
    uint16_t        token_getFileIndex(
        TOKEN_DATA      *this
    );

    bool            token_setFileIndex(
        TOKEN_DATA      *this,
        uint16_t        value
    );
    
    
    int64_t         token_getInteger(
        TOKEN_DATA      *this
    );
    
    bool            token_setInteger(
        TOKEN_DATA      *this,
        int64_t         value
    );
    
    
    uint16_t        token_getLen(
        TOKEN_DATA      *this
    );
    
    bool            token_setLen(
        TOKEN_DATA      *this,
        uint16_t        value
    );
    
    
    uint32_t        token_getLineNo(
        TOKEN_DATA      *this
    );

    bool            token_setLineNo(
        TOKEN_DATA      *this,
        uint32_t        value
    );


    SRCLOC *        token_getLoc(
        TOKEN_DATA      *this
    );
    
    
    int16_t         token_getMisc(
        TOKEN_DATA      *this
    );
    
    bool            token_setMisc(
        TOKEN_DATA      *this,
        int16_t         value
    );
    
    
    int64_t         token_getOffset(
        TOKEN_DATA      *this
    );
    
    bool            token_setOffset(
        TOKEN_DATA      *this,
        int64_t         value
    );
    

    uint32_t        token_getStrToken(
        TOKEN_DATA      *this
    );
    
    bool            token_setStrToken(
        TOKEN_DATA      *this,
        uint32_t        value
    );
    
    
    /*!
     Add the string to the shared string table and set up the token
     as a string token reference.
     @return    If successful, true; otherwise false.
     */
    bool            token_setStrW32(
        TOKEN_DATA      *this,
        const
        W32CHR_T        *pStr
    );
    
    
    /*!
     Get the token's data as a constant character string.
     @return    If successful, an AStr object which must be released,
                otherwise NULL.
     */
    const
    char *          token_getTextA(
        TOKEN_DATA      *this
    );
    
    
    /*!
     Get the token's data as an AStr object.
     @return    If successful, an AStr object which must be released,
                otherwise OBJ_NIL.
     @warning   Remember to release the returned AStr object.
     */
    ASTR_DATA *     token_getTextAStr(
        TOKEN_DATA      *this
    );

    
    /* Type is the internal type of the token itself
     * such as Text, Char, StmIdx, etc. Class is used
     * categorize the token stream.
     */
    uint16_t        token_getType(
        TOKEN_DATA      *this
    );
    
    bool            token_setType(
        TOKEN_DATA      *this,
        uint16_t        value
    );
    
    
    /*!
     Add the string to the shared string table and set up the token
     as a string token reference.
     @return    If successful, true; otherwise false.
     */
    bool            token_setW32STR(
        TOKEN_DATA      *this,
        W32STR_DATA     *pStr
        );
    
    

    //---------------------------------------------------------------
    //                      *** Methods ***
    //---------------------------------------------------------------

    /*!
     Assign this to pOther (ie Other = this;)
     @return        ERESULT_SUCCESS
     */
    ERESULT         token_Assign(
        TOKEN_DATA       *this,
        TOKEN_DATA       *pOther
    );
    
    
    /*!
     Compare this token with the other specified. Only
     the type and the actual value are compared.
     @return
        ERESULT_SUCCESS_UNEQUAL     (this < pOther)
        ERESULT_SUCCESS_EQUAL       (this == pOther)
        ERESULT_SUCCESS_UNEQUAL     (this > pOther)
     */
    ERESULT         token_Compare(
        TOKEN_DATA       *this,
        TOKEN_DATA       *pOther
    );
    
    
    /*!
     Creates a duplicate copy of itself otherwise returns OBJ_NIL.
     */
    TOKEN_DATA *     token_Copy(
        TOKEN_DATA       *this
    );

    
    TOKEN_DATA *     token_Init(
        TOKEN_DATA       *this
    );

    TOKEN_DATA *     token_InitCharW32(
        TOKEN_DATA      *this,
        SRCLOC          *pLoc,
        int32_t         cls,
        W32CHR_T        chr
    );
    
    TOKEN_DATA *    token_InitInteger(
        TOKEN_DATA      *this,
        SRCLOC          *pLoc,
        int32_t         cls,
        int64_t         integer
    );

#ifdef XYZZY
    TOKEN_DATA *     token_InitObj(
        TOKEN_DATA      *this,
        SRCLOC          *pLoc,
        int32_t         cls,
        OBJ_DATA        *pObj
    );
    
    TOKEN_DATA *     token_InitStringA(
        TOKEN_DATA      *this,
        SRCLOC          *pLoc,
        int32_t         cls,
        ASTR_DATA       *pString
    );
    
    TOKEN_DATA *     token_InitW32Str(
        TOKEN_DATA      *this,
        SRCLOC          *pLoc,
        int32_t         cls,
        W32STR_DATA     *pString
    );
    
    TOKEN_DATA *     token_InitStrA(
        TOKEN_DATA      *this,
        SRCLOC          *pLoc,
        int32_t         cls,
        const
        char            *pStr
    );
    
    TOKEN_DATA *     token_InitStrW32(
        TOKEN_DATA      *this,
        SRCLOC          *pLoc,
        int32_t         cls,
        const
        W32CHR_T        *pStr
    );
    
    /*!
     Initialize the object with the given parameter of a String Token Number.
     Normally, String Token Numbers are indexes into an szTbl object that
     will return the string.
     @param     this    TOKEN_DATA object pointer (released if an error occurs)
     @param     fileIndex   index to a file path held in an array (relative to 1) (optional)
     @param     offset      file offset of first character
     @param     lineNo  Line Number for the start of the token
     @param     colNo   Column Number for the start of the token
     @param     cls     Token class (see PPLEX.H for examples)
     @param     token   Token String Number (probably returned by szTbl)
     @return    If successful, a TOKEN_DATA pointer otherwise OBJ_NIL
     */
    TOKEN_DATA *    token_InitStrToken(
        TOKEN_DATA      *this,
        SRCLOC          *pLoc,
        int32_t         cls,
        const
        uint32_t        token
    );
#endif
    

    ERESULT     token_SetupCharW32(
        TOKEN_DATA      *this,
        SRCLOC          *pLoc,
        int32_t         cls,
        const
        W32CHR_T        chr
    );
    
    
    /*!
     Set the general parameters of the token at once releasing any prior
     data retained.
     Example:
     @code
     ERESULT      eRc = token_SetFnLCC(this,"zyzzy",256,16,CLASS_TERMINAL);
     @endcode
     @param     this    TOKEN_DATA object pointer
     @return    If successful, ERESULT_SUCCESS otherwise an ERESULT_* error code
     */
    ERESULT         token_SetupFnLCC(
        TOKEN_DATA      *this,
        SRCLOC          *pLoc,
        int32_t         cls
    );
    
    
    ERESULT     token_SetupStrW32(
        TOKEN_DATA      *this,
        SRCLOC          *pLoc,
        int32_t         cls,
        const
        W32CHR_T        *pStr
    );
    
    
    /*!
     Create a string of the token data in string format. This returns
     just the data, not any other fields such a filename, line or col.
     @return    If successful, an AStr object which must be released,
                otherwise OBJ_NIL.
     @warning   Remember to release the returned AStr object.
     */
    ASTR_DATA *     token_ToDataString(
        TOKEN_DATA      *this
    );
    
    
    /*!
     Create a JSON string that describes this object.
     @return    If successful, an AStr object which must be released,
                otherwise OBJ_NIL.
     @warning   Remember to release the returned AStr object.
     */
    ASTR_DATA *     token_ToJSON(
        TOKEN_DATA      *this
    );
    
    
    /*!
     Create a string that describes this object and the objects within it.
     Example:
     @code
     ASTR_DATA      *pDesc = token_ToDebugString(this,4);
     @endcode
     @param     this    TOKEN_DATA object pointer
     @param     indent  number of characters to indent every line of output, can be 0
     @return    If successful, an AStr object which must be released containing the
                 description, otherwise OBJ_NIL.
     @warning   Remember to release the returned AStr object.
     */
    ASTR_DATA *     token_ToDebugString(
        TOKEN_DATA      *this,
        int             indent
    );

    
    

#ifdef	__cplusplus
}
#endif

#endif	/* TOKEN_H */

