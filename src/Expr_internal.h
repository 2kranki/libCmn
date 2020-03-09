// vi:nu:et:sts=4 ts=4 sw=4
/* 
 * File:   Expr_internal.h
 *	Generated 03/03/2020 17:03:28
 *
 * Notes:
 *  --	N/A
 *
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




#include        <Expr.h>
#include        <JsonIn.h>
//#include        <lex.h>
#include        <Parser_internal.h>
//#include        <pplex.h>
#include        <SrcErrors.h>
#include        <Token.h>


#ifndef EXPR_INTERNAL_H
#define	EXPR_INTERNAL_H





#ifdef	__cplusplus
extern "C" {
#endif




    //---------------------------------------------------------------
    //                  Object Data Description
    //---------------------------------------------------------------

#pragma pack(push, 1)
struct Expr_data_s	{
    /* Warning - OBJ_DATA must be first in this object!
     */
    PARSER_DATA     super;
    OBJ_IUNKNOWN    *pSuperVtbl;    // Needed for Inheritance

    // Common Data
    LEX_DATA        *pLex;

    // Find an Identifier. If not found, return 0.
    int32_t         (*pFindValueA)(OBJ_ID, const char *);
    OBJ_ID          pObjFind;

    // Input a Character.
    void            (*pInputAdvance)(OBJ_ID, int32_t);
    int32_t         (*pInputLookAhead)(OBJ_ID, uint32_t);
    OBJ_ID          pObjInput;

    // Parse helpers.
    bool            (*pInputMatchA)(OBJ_ID, W32CHR_T);
    bool            (*pInputMatchStrA)(OBJ_ID, const char *);
    ASTR_DATA *     (*pInputScanIdentifier)(OBJ_ID, const char *);
    bool            (*pInputScanInteger32)(OBJ_ID, int32_t *);
    OBJ_ID          pObjParse;

};
#pragma pack(pop)

    extern
    struct Expr_class_data_s  Expr_ClassObj;

    extern
    const
    EXPR_VTBL         Expr_Vtbl;



    //---------------------------------------------------------------
    //              Class Object Method Forward Definitions
    //---------------------------------------------------------------

#ifdef  EXPR_SINGLETON
    EXPR_DATA *     Expr_getSingleton (
        void
    );

    bool            Expr_setSingleton (
     EXPR_DATA       *pValue
);
#endif



    //---------------------------------------------------------------
    //              Internal Method Forward Definitions
    //---------------------------------------------------------------

    OBJ_IUNKNOWN *  Expr_getSuperVtbl (
        EXPR_DATA     *this
    );


    ERESULT         Expr_Assign (
        EXPR_DATA    *this,
        EXPR_DATA    *pOther
    );


    EXPR_DATA *       Expr_Copy (
        EXPR_DATA     *this
    );


    void            Expr_Dealloc (
        OBJ_ID          objId
    );


    //      >>> Parsing Methods <<<
    int32_t         Expr_Add(
        EXPR_DATA       *this
    );

    int32_t         Expr_And(
        EXPR_DATA       *this
    );

    int32_t         Expr_Cond(
        EXPR_DATA       *this
    );

    int32_t         Expr_Eq(
        EXPR_DATA       *this
    );

    int32_t         Expr_Expr(
        EXPR_DATA       *this
    );

    int32_t         Expr_LogicalAnd(
        EXPR_DATA       *this
    );

    int32_t         Expr_LogicalOr(
        EXPR_DATA       *this
    );

    int32_t         Expr_Mult(
        EXPR_DATA       *this
    );

    int32_t         Expr_Number(
        EXPR_DATA       *this
    );

    int32_t         Expr_Or(
        EXPR_DATA       *this
    );

    int32_t         Expr_Primary(
        EXPR_DATA       *this
    );

    int32_t         Expr_Rel(
        EXPR_DATA       *this
    );

    int32_t         Expr_Shift(
        EXPR_DATA       *this
    );

    int32_t         Expr_Xor(
        EXPR_DATA       *this
    );


#ifdef  EXPR_JSON_SUPPORT
    /*!
     Parse the new object from an established parser.
     @param pParser an established jsonIn Parser Object
     @return    a new object if successful, otherwise, OBJ_NIL
     @warning   Returned object must be released.
     */
    EXPR_DATA *       Expr_ParseJsonObject (
        JSONIN_DATA     *pParser
    );


    /*!
     Parse the object from an established parser. This helps facilitate
     parsing the fields from an inheriting object.
     @param pParser     an established jsonIn Parser Object
     @param pObject     an Object to be filled in with the
                        parsed fields.
     @return    If successful, ERESULT_SUCCESS. Otherwise, an ERESULT_*
                error code.
     */
    ERESULT         Expr_ParseJsonFields (
        JSONIN_DATA     *pParser,
        EXPR_DATA     *pObject
    );
#endif


    void *          Expr_QueryInfo (
        OBJ_ID          objId,
        uint32_t        type,
        void            *pData
    );


#ifdef  EXPR_JSON_SUPPORT
    /*!
     Create a string that describes this object and the objects within it in
     HJSON formt. (See hjson object for details.)
     Example:
     @code
     ASTR_DATA      *pDesc = Expr_ToJson(this);
     @endcode
     @param     this    object pointer
     @return    If successful, an AStr object which must be released containing the
                JSON text, otherwise OBJ_NIL and LastError set to an appropriate
                ERESULT_* error code.
     @warning   Remember to release the returned AStr object.
     */
    ASTR_DATA *     Expr_ToJson (
        EXPR_DATA      *this
    );


    /*!
     Append the json representation of the object's fields to the given
     string. This helps facilitate parsing the fields from an inheriting 
     object.
     @param this        Object Pointer
     @param pStr        String Pointer to be appended to.
     @return    If successful, ERESULT_SUCCESS. Otherwise, an ERESULT_*
                error code.
     */
    ERESULT         Expr_ToJsonFields (
        EXPR_DATA     *this,
        ASTR_DATA       *pStr
    );
#endif




#ifdef NDEBUG
#else
    bool			Expr_Validate (
        EXPR_DATA       *this
    );
#endif



#ifdef	__cplusplus
}
#endif

#endif	/* EXPR_INTERNAL_H */

