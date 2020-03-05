// vi:nu:et:sts=4 ts=4 sw=4

//****************************************************************
//          Generic Source Token (Token) Header
//****************************************************************
/*
 * Program
 *			Generic Source Token (Token)
 * Purpose
 *          This object provides a standardized way of handling
 *          pieces of text parsed from a text string. Initially,
 *          tokens consist of individual characters. As they are
 *          combined into character strings, those strings must
 *          stored in an external table such as szTbl.
 *
 * Remarks
 *  1.      The file index should remain constant and valid for the
 *          life of this object.
 *  2.      String Tokens must be unique per string so that they can
 *          be used in lieu of an actual string.  The token is used
 *          as an index into the shared szTbl.
 *
 * History
 *  05/26/2015 Generated
 *	01/02/2020 Regenerated
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
#include        <SrcLoc.h>


#ifndef         TOKEN_H
#define         TOKEN_H


#define   TOKEN_JSON_SUPPORT 1
//#define   TOKEN_SINGLETON    1


#ifdef NDEBUG
#   define  TRC_OBJ_TOKEN(cbp,desc,pToken)     /**/
#else
#   define  TRC_OBJ_TOKEN(cbp,desc,pToken)                                          \
    do {                                                                            \
        if (obj_Trace(cbp) || obj_Trace(((OBJ_DATA *)cbp)->pVtbl->pClassObject())) {\
            ASTR_DATA       *pStr = Token_ToDataString(pToken);                     \
            trace_TraceA(trace_Shared(),                                            \
                    "Token: %s  %d - %s",                                           \
                    desc,                                                           \
                    Token_getClass(pToken),                                         \
                    AStr_getData(pStr)                                              \
            );                                                                      \
            obj_Release(pStr);                                                      \
        }                                                                           \
    } while(0)
#endif



#ifdef	__cplusplus
extern "C" {
#endif
    

    //****************************************************************
    //* * * * * * * * * * * *  Data Definitions  * * * * * * * * * * *
    //****************************************************************


    typedef struct Token_data_s	TOKEN_DATA;            // Inherits from OBJ
    typedef struct Token_class_data_s TOKEN_CLASS_DATA;   // Inherits from OBJ

    typedef struct Token_vtbl_s	{
        OBJ_IUNKNOWN    iVtbl;              // Inherited Vtbl.
        // Put other methods below this as pointers and add their
        // method names to the vtbl definition in Token_object.c.
        // Properties:
        // Methods:
        //bool        (*pIsEnabled)(TOKEN_DATA *);
    } TOKEN_VTBL;

    typedef struct Token_class_vtbl_s	{
        OBJ_IUNKNOWN    iVtbl;              // Inherited Vtbl.
        // Put other methods below this as pointers and add their
        // method names to the vtbl definition in Token_object.c.
        // Properties:
        // Methods:
        //bool        (*pIsEnabled)(TOKEN_DATA *);
    } TOKEN_CLASS_VTBL;


    typedef enum Token_type_e {
        TOKEN_TYPE_UNKNOWN=0,
        TOKEN_TYPE_CHAR,            // A single Unicode character in UTF-8
        TOKEN_TYPE_DOUBLE,          // double
        TOKEN_TYPE_INTEGER,         // int64_t
        TOKEN_TYPE_STRTOKEN,        // String Token for szTbl
        TOKEN_TYPE_W32CHAR,         // A single Unicode character
        TOKEN_TYPE_USER=32          // First User Type allowed
    } TOKEN_TYPE;


    typedef enum Token_misc_e {
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

#ifdef  TOKEN_SINGLETON
    TOKEN_DATA *    Token_Shared (
        void
    );

    void            Token_SharedReset (
        void
    );
#endif


   /*!
     Allocate a new Object and partially initialize. Also, this sets an
     indicator that the object was alloc'd which is tested when the object is
     released.
     @return    pointer to Token object if successful, otherwise OBJ_NIL.
     */
    TOKEN_DATA *    Token_Alloc (
        void
    );
    
    
    OBJ_ID          Token_Class (
        void
    );
    
    
    TOKEN_DATA *    Token_New (
        void
    );
    
    
    TOKEN_DATA *    Token_NewCharW32(
        SRCLOC          *pLoc,
        int32_t         cls,
        W32CHR_T        chr
    );


    TOKEN_DATA *    Token_NewInteger(
        SRCLOC          *pLoc,
        int32_t         cls,
        int64_t         integer
    );


    TOKEN_DATA *    Token_NewFromJsonString(
        ASTR_DATA       *pString
     );

     TOKEN_DATA *   Token_NewFromJsonStringA(
        const
        char            *pString
     );


    TOKEN_DATA *   Token_NewFromW32STR(
        SRCLOC          *pLoc,
        int32_t         cls,
        W32STR_DATA     *pString
     );


    TOKEN_DATA *    Token_NewStrA(
        SRCLOC          *pLoc,
        int32_t         cls,
        const
        char            *pStrA
     );


    TOKEN_DATA *    Token_NewStrW32(
        SRCLOC          *pLoc,
        int32_t         cls,
        const
        W32CHR_T        *pStrW32
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
    TOKEN_DATA *    Token_NewStrToken(
        SRCLOC          *pLoc,
        int32_t         cls,
        uint32_t        token
    );



    //---------------------------------------------------------------
    //                      *** Properties ***
    //---------------------------------------------------------------

    /* A Character Token is only one character.
     */
    W32CHR_T        Token_getChrW32(
        TOKEN_DATA      *this
    );

    bool            Token_setChrW32(
        TOKEN_DATA      *this,
        W32CHR_T        value
    );


    /* Class is used to categorize the token. For instance, if
     * the token type is text, then the class might be an
     * identifier, keyword, etc.
     */
    int32_t         Token_getClass(
        TOKEN_DATA      *this
    );

    bool            Token_setClass(
        TOKEN_DATA      *this,
        int32_t         value
    );


    uint16_t        Token_getColNo(
        TOKEN_DATA      *this
    );

    bool            Token_setColNo(
        TOKEN_DATA      *this,
        uint16_t        value
    );


    uint32_t        Token_getFileIndex(
        TOKEN_DATA      *this
    );

    bool            Token_setFileIndex(
        TOKEN_DATA      *this,
        uint32_t        value
    );


    int64_t         Token_getInteger(
        TOKEN_DATA      *this
    );

    bool            Token_setInteger(
        TOKEN_DATA      *this,
        int64_t         value
    );


    uint16_t        Token_getLen(
        TOKEN_DATA      *this
    );

    bool            Token_setLen(
        TOKEN_DATA      *this,
        uint16_t        value
    );


    uint32_t        Token_getLineNo(
        TOKEN_DATA      *this
    );

    bool            Token_setLineNo(
        TOKEN_DATA      *this,
        uint32_t        value
    );


    SRCLOC *        Token_getLoc(
        TOKEN_DATA      *this
    );


    int16_t         Token_getMisc(
        TOKEN_DATA      *this
    );

    bool            Token_setMisc(
        TOKEN_DATA      *this,
        int16_t         value
    );


    int64_t         Token_getOffset(
        TOKEN_DATA      *this
    );

    bool            Token_setOffset(
        TOKEN_DATA      *this,
        int64_t         value
    );


    uint32_t        Token_getStrToken(
        TOKEN_DATA      *this
    );

    bool            Token_setStrToken(
        TOKEN_DATA      *this,
        uint32_t        value
    );


    /*!
     Add the string to the shared string table and set up the token
     as a string token reference.
     @return    If successful, true; otherwise false.
     */
    bool            Token_setStrW32(
        TOKEN_DATA      *this,
        const
        W32CHR_T        *pStrW32
    );


    /*!
     Get the token's data as a constant character string.
     @return    If successful, a nul-terminated string which must be
                freed with mem_Free(), otherwise NULL.
     */
    char *          Token_getTextA(
        TOKEN_DATA      *this
    );


    /*!
     Get the token's data as an AStr object.
     @return    If successful, an AStr object which must be released,
                otherwise OBJ_NIL.
     @warning   Remember to release the returned AStr object.
     */
    ASTR_DATA *     Token_getTextAStr(
        TOKEN_DATA      *this
    );


    /* Type is the internal type of the token itself
     * such as Text, Char, StmIdx, etc. Class is used
     * categorize the token stream.
     */
    uint16_t        Token_getType(
        TOKEN_DATA      *this
    );

    bool            Token_setType(
        TOKEN_DATA      *this,
        uint16_t        value
    );


    /*!
     Add the string to the shared string table and set up the token
     as a string token reference.
     @return    If successful, true; otherwise false.
     */
    bool            Token_setW32STR(
        TOKEN_DATA      *this,
        W32STR_DATA     *pStr
    );



    //---------------------------------------------------------------
    //                      *** Methods ***
    //---------------------------------------------------------------

    //---------------------------------------------------------------
    //                       A s s i g n
    //---------------------------------------------------------------

    /*!
     Assign the contents of this object to the other object (ie
     this -> other).  Any objects in other will be released before
     a copy of the object is performed.
     Example:
     @code
        ERESULT eRc = Token_Assign(this,pOther);
     @endcode
     @param     this    object pointer
     @param     pOther  a pointer to another TOKEN object
     @return    If successful, ERESULT_SUCCESS otherwise an
                ERESULT_* error
     */
    ERESULT         Token_Assign (
        TOKEN_DATA      *this,
        TOKEN_DATA      *pOther
    );


    /*!
     Compare the two provided objects.
     @return    ERESULT_SUCCESS_EQUAL if this == other
                ERESULT_SUCCESS_LESS_THAN if this < other
                ERESULT_SUCCESS_GREATER_THAN if this > other
     */
    ERESULT         Token_Compare (
        TOKEN_DATA     *this,
        TOKEN_DATA     *pOther
    );


    /*!
     Copy the current object creating a new object.
     Example:
     @code
        Token      *pCopy = Token_Copy(this);
     @endcode
     @param     this    object pointer
     @return    If successful, a TOKEN object which must be
                released, otherwise OBJ_NIL.
     @warning   Remember to release the returned object.
     */
    TOKEN_DATA *    Token_Copy (
        TOKEN_DATA      *this
    );

   
    TOKEN_DATA *    Token_Init (
        TOKEN_DATA      *this
    );


    ERESULT         Token_IsEnabled (
        TOKEN_DATA      *this
    );
    
 
    /*!
     Create a string of the token data in string format. This returns
     just the data, not any other fields such a filename, line or col.
     @return    If successful, an AStr object which must be released,
                otherwise OBJ_NIL.
     @warning   Remember to release the returned AStr object.
     */
    ASTR_DATA *     Token_ToDataString(
        TOKEN_DATA      *this
    );


    /*!
     Create a string that describes this object and the objects within it in
     HJSON formt. (See hjson object for details.)
     Example:
     @code
     ASTR_DATA      *pDesc = Token_ToJson(this);
     @endcode
     @param     this    object pointer
     @return    If successful, an AStr object which must be released containing the
                JSON text, otherwise OBJ_NIL and LastError set to an appropriate
                ERESULT_* error code.
     @warning   Remember to release the returned AStr object.
     */
    ASTR_DATA *     Token_ToJson(
        TOKEN_DATA   *this
    );


    SRCLOC_DATA *   Token_ToSrcLoc(
        TOKEN_DATA      *this
    );


    /*!
     Create a string that describes this object and the objects within it.
     Example:
     @code 
        ASTR_DATA      *pDesc = Token_ToDebugString(this,4);
     @endcode 
     @param     this    object pointer
     @param     indent  number of characters to indent every line of output, can be 0
     @return    If successful, an AStr object which must be released containing the
                description, otherwise OBJ_NIL.
     @warning   Remember to release the returned AStr object.
     */
    ASTR_DATA *    Token_ToDebugString (
        TOKEN_DATA     *this,
        int             indent
    );
    
    

    
#ifdef	__cplusplus
}
#endif

#endif	/* TOKEN_H */

