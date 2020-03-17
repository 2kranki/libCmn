// vi:nu:et:sts=4 ts=4 sw=4
/* 
 * File:   Scanner_internal.h
 *	Generated 03/04/2020 21:17:29
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




#include        <Scanner.h>
#include        <JsonIn.h>
#include        <W32StrC_internal.h>


#ifndef SCANNER_INTERNAL_H
#define	SCANNER_INTERNAL_H





#ifdef	__cplusplus
extern "C" {
#endif




    //---------------------------------------------------------------
    //                  Object Data Description
    //---------------------------------------------------------------

#pragma pack(push, 1)
struct Scanner_data_s	{
    /* Warning - OBJ_DATA must be first in this object!
     */
    W32STRC_DATA    super;
    OBJ_IUNKNOWN    *pSuperVtbl;    // Needed for Inheritance

    // Common Data
    W32CHR_T        sep;            // Special Seperator/Terminator Character
    // Find an Identifier for its value. If not found, return 0.
    int32_t         (*pFindValueA)(OBJ_ID, const char *);
    OBJ_ID          pObjFind;


};
#pragma pack(pop)

    extern
    struct Scanner_class_data_s  Scanner_ClassObj;

    extern
    const
    SCANNER_VTBL         Scanner_Vtbl;



    //---------------------------------------------------------------
    //              Class Object Method Forward Definitions
    //---------------------------------------------------------------

#ifdef  SCANNER_SINGLETON
    SCANNER_DATA *  Scanner_getSingleton (
        void
    );

    bool            Scanner_setSingleton (
     SCANNER_DATA       *pValue
);
#endif



    //---------------------------------------------------------------
    //              Internal Method Forward Definitions
    //---------------------------------------------------------------

    OBJ_IUNKNOWN *  Scanner_getSuperVtbl (
        SCANNER_DATA     *this
    );


    ERESULT         Scanner_Assign (
        SCANNER_DATA    *this,
        SCANNER_DATA    *pOther
    );


    SCANNER_DATA *  Scanner_Copy (
        SCANNER_DATA     *this
    );


    void            Scanner_Dealloc (
        OBJ_ID          objId
    );


    //      >>> Parsing Methods <<<
    int32_t         Scanner_Add(
        SCANNER_DATA    *this
    );

    int32_t         Scanner_And(
        SCANNER_DATA    *this
    );

    int32_t         Scanner_Cond(
        SCANNER_DATA    *this
    );

    int32_t         Scanner_Eq(
        SCANNER_DATA    *this
    );

    int32_t         Scanner_Expr(
         SCANNER_DATA    *this
   );

    int32_t         Scanner_LogicalAnd(
        SCANNER_DATA    *this
    );

    int32_t         Scanner_LogicalOr(
        SCANNER_DATA    *this
    );

    int32_t         Scanner_Mult(
        SCANNER_DATA    *this
    );

    int32_t         Scanner_Number(
        SCANNER_DATA    *this
    );

    int32_t         Scanner_Or(
        SCANNER_DATA    *this
    );

    int32_t         Scanner_Primary(
        SCANNER_DATA    *this
    );

    int32_t         Scanner_Rel(
        SCANNER_DATA    *this
    );

    int32_t         Scanner_Shift(
        SCANNER_DATA    *this
    );

    int32_t         Scanner_Xor(
        SCANNER_DATA    *this
    );


#ifdef  SCANNER_JSON_SUPPORT
    /*!
     Parse the new object from an established parser.
     @param pParser an established jsonIn Parser Object
     @return    a new object if successful, otherwise, OBJ_NIL
     @warning   Returned object must be released.
     */
    SCANNER_DATA *       Scanner_ParseJsonObject (
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
    ERESULT         Scanner_ParseJsonFields (
        JSONIN_DATA     *pParser,
        SCANNER_DATA     *pObject
    );
#endif


    void *          Scanner_QueryInfo (
        OBJ_ID          objId,
        uint32_t        type,
        void            *pData
    );


#ifdef  SCANNER_JSON_SUPPORT
    /*!
     Create a string that describes this object and the objects within it in
     HJSON formt. (See hjson object for details.)
     Example:
     @code
     ASTR_DATA      *pDesc = Scanner_ToJson(this);
     @endcode
     @param     this    object pointer
     @return    If successful, an AStr object which must be released containing the
                JSON text, otherwise OBJ_NIL and LastError set to an appropriate
                ERESULT_* error code.
     @warning   Remember to release the returned AStr object.
     */
    ASTR_DATA *     Scanner_ToJson (
        SCANNER_DATA      *this
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
    ERESULT         Scanner_ToJsonFields (
        SCANNER_DATA     *this,
        ASTR_DATA       *pStr
    );
#endif




#ifdef NDEBUG
#else
    bool			Scanner_Validate (
        SCANNER_DATA       *this
    );
#endif



#ifdef	__cplusplus
}
#endif

#endif	/* SCANNER_INTERNAL_H */

