// vi:nu:et:sts=4 ts=4 sw=4
/* 
 * File:   LexC_internal.h
 *  Generated 09/02/2021 08:48:25
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




#include        <LexC.h>
#include        <JsonIn.h>
#include        <Lex_internal.h>


#ifndef LEXC_INTERNAL_H
#define LEXC_INTERNAL_H





#ifdef  __cplusplus
extern "C" {
#endif




    //---------------------------------------------------------------
    //                  Object Data Description
    //---------------------------------------------------------------

#pragma pack(push, 1)
struct LexC_data_s  {
    /* Warning - OBJ_DATA must be first in this object!
     */
    LEX_DATA        super;
    OBJ_IUNKNOWN    *pSuperVtbl;    // Needed for Inheritance

    // Common Data
    ASTR_DATA       *pStr;
    uint16_t        size;           // maximum number of elements
    uint16_t        rsvd16;

};
#pragma pack(pop)

    extern
    struct LexC_class_data_s  LexC_ClassObj;

    extern
    const
    LEXC_VTBL         LexC_Vtbl;



    //---------------------------------------------------------------
    //              Class Object Method Forward Definitions
    //---------------------------------------------------------------

#ifdef  LEXC_SINGLETON
    LEXC_DATA *     LexC_getSingleton (
        void
    );

    bool            LexC_setSingleton (
     LEXC_DATA       *pValue
);
#endif



    //---------------------------------------------------------------
    //              Internal Method Forward Definitions
    //---------------------------------------------------------------

    OBJ_IUNKNOWN *  LexC_getSuperVtbl (
        LEXC_DATA       *this
    );


    ERESULT         LexC_Assign (
        LEXC_DATA       *this,
        LEXC_DATA       *pOther
    );


    LEXC_DATA *     LexC_Copy (
        LEXC_DATA       *this
    );


    void            LexC_Dealloc (
        OBJ_ID          objId
    );


    LEXC_DATA *     LexC_DeepCopy (
        LEXC_DATA       *this
    );


#ifdef  LEXC_JSON_SUPPORT
    /*!
     Parse the new object from an established parser.
     @param pParser an established jsonIn Parser Object
     @return    a new object if successful, otherwise, OBJ_NIL
     @warning   Returned object must be released.
     */
    LEXC_DATA *     LexC_ParseJsonObject (
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
    ERESULT         LexC_ParseJsonFields (
        JSONIN_DATA     *pParser,
        LEXC_DATA       *pObject
    );
#endif


    // The post-process exit is called when the default parser is about
    // to finalize a token. This exit may ignore the token or continue
    // with the finalization.  Ignoring the token causes the parser to
    // start all over again scanning the next token. This exit could
    // manipulate the internal save token save string if needed.
    // Return codes:
    //      0 == Keep token/clsNew as is
    //      1 == Reset data area and scan next char
    //      2 == Keep data as is and scan next char
    int             LexC_ParserPostExit (
        LEXC_DATA       *this,
        LEX_DATA        *pLex,              // LEX Object Ptr
        LEX_PARSE_DATA  *pData              // Current Parse Data Ptr
    );


    /*
     This exit allows the entire lexical scan to be over-ridden.
     The exit can call:
            Lex_TokenAppendStringW32(this, data.chr2);
            fRc = Lex_NextInput(this, &data, false);
     as needed to do its own scan if desired. It should return:
        0 == Accept what exit scanned
        1 == Skip to next token and continue scan.
        2 == Continue with default scanner.
     */
    int             LexC_ParserPreExit (
        LEXC_DATA       *this,
        LEX_DATA        *pLex,              // LEX Object Ptr
        LEX_PARSE_DATA  *pData              // Current Parse Data Ptr
    );


    void *          LexC_QueryInfo (
        OBJ_ID          objId,
        uint32_t        type,
        void            *pData
    );


#ifdef  LEXC_JSON_SUPPORT
    /*!
     Create a string that describes this object and the objects within it in
     HJSON formt. (See hjson object for details.)
     Example:
     @code
     ASTR_DATA      *pDesc = LexC_ToJson(this);
     @endcode
     @param     this    object pointer
     @return    If successful, an AStr object which must be released containing the
                JSON text, otherwise OBJ_NIL.
     @warning   Remember to release the returned AStr object.
     */
    ASTR_DATA *     LexC_ToJson (
        LEXC_DATA       *this
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
    ERESULT         LexC_ToJsonFields (
        LEXC_DATA     *this,
        ASTR_DATA       *pStr
    );
#endif




#ifdef NDEBUG
#else
    bool            LexC_Validate (
        LEXC_DATA       *this
    );
#endif



#ifdef  __cplusplus
}
#endif

#endif  /* LEXC_INTERNAL_H */

