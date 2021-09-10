// vi:nu:et:sts=4 ts=4 sw=4
/* 
 * File:   LexTri_internal.h
 *  Generated 09/02/2021 20:32:47
 *
 * Notes:
 *  --  N/A
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




#include        <LexTri.h>
#include        <JsonIn.h>
#include        <Lex_internal.h>


#ifndef LEXTRI_INTERNAL_H
#define LEXTRI_INTERNAL_H





#ifdef  __cplusplus
extern "C" {
#endif




    //---------------------------------------------------------------
    //                  Object Data Description
    //---------------------------------------------------------------

#pragma pack(push, 1)
struct LexTri_data_s  {
    /* Warning - OBJ_DATA must be first in this object!
     */
    LEX_DATA        super;
    OBJ_IUNKNOWN    *pSuperVtbl;    // Needed for Inheritance

    // Common Data
    ASTR_DATA       *pStr;
    uint16_t        size;           // maximum number of elements
    uint16_t        rsvd16;

    // The post-process exit is called when the default parser is about
    // to finalize a token. This exit may ignore the token or continue
    // with the finalization.  Ignoring the token causes the parser to
    // start all over again scanning the next token. This exit could
    // manipulate the internal save token save string if needed.
    // Return codes:
    //      0 == Keep token/clsNew as is
    //      1 == Reset data area and scan next char
    //      2 == Keep data as is and scan next char
    int             (*pParserPostExit)(
                                   OBJ_ID,          // pParserExitObj
                                   LEX_DATA *,      // LEX Object Ptr
                                   LEX_PARSE_DATA * // Current Parse Data Ptr
                    );
    OBJ_ID          pParserPostExitObj;


    // The pre-process exit is called before the first token is analyzed
    // allowing default parsing to be overridden.
    int             (*pParserPreExit)(
                                   OBJ_ID,          // pParserExitObj
                                   LEX_DATA *,      // LEX Object Ptr
                                   LEX_PARSE_DATA * // Current Parse Data Ptr
                    );
    OBJ_ID          pParserPreExitObj;

};
#pragma pack(pop)

    extern
    struct LexTri_class_data_s  LexTri_ClassObj;

    extern
    const
    LEXTRI_VTBL         LexTri_Vtbl;



    //---------------------------------------------------------------
    //              Class Object Method Forward Definitions
    //---------------------------------------------------------------

#ifdef  LEXTRI_SINGLETON
    LEXTRI_DATA *    LexTri_getSingleton (
        void
    );

    bool            LexTri_setSingleton (
     LEXTRI_DATA        *pValue
);
#endif



    //---------------------------------------------------------------
    //              Internal Method Forward Definitions
    //---------------------------------------------------------------

    bool            Lex_setParserPostExit(
        LEX_DATA        *this,
        ERESULT         (*pParser)(OBJ_ID, LEX_DATA *, LEX_PARSE_DATA *),
        OBJ_ID          pParseObj
    );


    bool            Lex_setParserPreExit(
        LEX_DATA        *this,
        ERESULT         (*pParser)(OBJ_ID, LEX_DATA *, LEX_PARSE_DATA *),
        OBJ_ID          pParseObj
    );


    OBJ_IUNKNOWN *  LexTri_getSuperVtbl (
        LEXTRI_DATA     *this
    );


    ERESULT         LexTri_Assign (
        LEXTRI_DATA     *this,
        LEXTRI_DATA     *pOther
    );


    LEXTRI_DATA *   LexTri_Copy (
        LEXTRI_DATA     *this
    );


    void            LexTri_Dealloc (
        OBJ_ID          objId
    );


    LEXTRI_DATA *     LexTri_DeepCopy (
        LEXTRI_DATA       *this
    );


#ifdef  LEXTRI_JSON_SUPPORT
    /*!
     Parse the new object from an established parser.
     @param pParser an established jsonIn Parser Object
     @return    a new object if successful, otherwise, OBJ_NIL
     @warning   Returned object must be released.
     */
    LEXTRI_DATA *   LexTri_ParseJsonObject (
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
    ERESULT         LexTri_ParseJsonFields (
        JSONIN_DATA     *pParser,
        LEXTRI_DATA     *pObject
    );
#endif


    void *          LexTri_QueryInfo (
        OBJ_ID          objId,
        uint32_t        type,
        void            *pData
    );


#ifdef  LEXTRI_JSON_SUPPORT
    /*!
     Create a string that describes this object and the objects within it in
     HJSON formt. (See hjson object for details.)
     Example:
     @code
     ASTR_DATA      *pDesc = LexTri_ToJson(this);
     @endcode
     @param     this    object pointer
     @return    If successful, an AStr object which must be released containing the
                JSON text, otherwise OBJ_NIL.
     @warning   Remember to release the returned AStr object.
     */
    ASTR_DATA *     LexTri_ToJson (
        LEXTRI_DATA      *this
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
    ERESULT         LexTri_ToJsonFields (
        LEXTRI_DATA     *this,
        ASTR_DATA       *pStr
    );
#endif




#ifdef NDEBUG
#else
    bool            LexTri_Validate (
        LEXTRI_DATA       *this
    );
#endif



#ifdef  __cplusplus
}
#endif

#endif  /* LEXTRI_INTERNAL_H */

