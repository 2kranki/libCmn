// vi:nu:et:sts=4 ts=4 sw=4
/* 
 * File:   LexJ_internal.h
 *  Generated 12/09/2020 23:26:59
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




#include        <LexJ.h>
#include        <JsonIn.h>
#include        <Lex_internal.h>
#include        <SrcFile.h>


#ifndef LEXJ_INTERNAL_H
#define LEXJ_INTERNAL_H





#ifdef  __cplusplus
extern "C" {
#endif




    //---------------------------------------------------------------
    //                  Object Data Description
    //---------------------------------------------------------------

#pragma pack(push, 1)
struct LexJ_data_s  {
    /* Warning - OBJ_DATA must be first in this object!
     */
    LEX_DATA        super;
    OBJ_IUNKNOWN    *pSuperVtbl;    // Needed for Inheritance

    // Common Data
    SRCFILE_DATA    *pInput;
    bool            (*pParser)(OBJ_ID, TOKEN_DATA *);

};
#pragma pack(pop)

    extern
    struct LexJ_class_data_s  LexJ_ClassObj;

    extern
    const
    LEXJ_VTBL         LexJ_Vtbl;



    //---------------------------------------------------------------
    //              Class Object Method Forward Definitions
    //---------------------------------------------------------------

#ifdef  LEXJ_SINGLETON
    LEXJ_DATA *     LexJ_getSingleton (
        void
    );

    bool            LexJ_setSingleton (
     LEXJ_DATA       *pValue
);
#endif



    //---------------------------------------------------------------
    //              Internal Method Forward Definitions
    //---------------------------------------------------------------

    OBJ_IUNKNOWN *  LexJ_getSuperVtbl (
        LEXJ_DATA     *this
    );


    ERESULT         LexJ_Assign (
        LEXJ_DATA    *this,
        LEXJ_DATA    *pOther
    );


    const
    char *          LexJ_Class2Str(
        int32_t         cls
    );


    LEXJ_DATA *     LexJ_Copy (
        LEXJ_DATA     *this
    );


    void            LexJ_Dealloc (
        OBJ_ID          objId
    );


#ifdef  LEXJ_JSON_SUPPORT
    /*!
     Parse the new object from an established parser.
     @param pParser an established jsonIn Parser Object
     @return    a new object if successful, otherwise, OBJ_NIL
     @warning   Returned object must be released.
     */
    LEXJ_DATA *       LexJ_ParseJsonObject (
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
    ERESULT         LexJ_ParseJsonFields (
        JSONIN_DATA     *pParser,
        LEXJ_DATA       *pObject
    );
#endif


    bool            LexJ_ParseTokenJson(
        LEXJ_DATA       *this,
        TOKEN_DATA      *pTokenOut          // Optional Output Token
    );


    void *          LexJ_QueryInfo (
        OBJ_ID          objId,
        uint32_t        type,
        void            *pData
    );


#ifdef  LEXJ_JSON_SUPPORT
    /*!
     Create a string that describes this object and the objects within it in
     HJSON formt. (See hjson object for details.)
     Example:
     @code
     ASTR_DATA      *pDesc = LexJ_ToJson(this);
     @endcode
     @param     this    object pointer
     @return    If successful, an AStr object which must be released containing the
                JSON text, otherwise OBJ_NIL.
     @warning   Remember to release the returned AStr object.
     */
    ASTR_DATA *     LexJ_ToJson (
        LEXJ_DATA      *this
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
    ERESULT         LexJ_ToJsonFields (
        LEXJ_DATA     *this,
        ASTR_DATA       *pStr
    );
#endif




#ifdef NDEBUG
#else
    bool            LexJ_Validate (
        LEXJ_DATA       *this
    );
#endif



#ifdef  __cplusplus
}
#endif

#endif  /* LEXJ_INTERNAL_H */

