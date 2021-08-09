// vi:nu:et:sts=4 ts=4 sw=4
/* 
 * File:   SrcFile_internal.h
 *  Generated 06/06/2020 10:44:03
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




#include        <SrcFile.h>
#include        <array.h>
#include        <JsonIn.h>
#include        <TextIn_internal.h>
#include        <Token_internal.h>


#ifndef SRCFILE_INTERNAL_H
#define SRCFILE_INTERNAL_H





#ifdef  __cplusplus
extern "C" {
#endif




    //---------------------------------------------------------------
    //                  Object Data Description
    //---------------------------------------------------------------

#pragma pack(push, 1)
struct SrcFile_data_s  {
    /* Warning - OBJ_DATA must be first in this object!
     */
    TEXTIN_DATA     super;
    OBJ_IUNKNOWN    *pSuperVtbl;    // Needed for Inheritance

    // Common Data
    TOKEN_DATA      curchr;             /*  Current Character */
    uint8_t         fInit;
    uint8_t         rsvd8[3];
    uint16_t        sizeInputs;
    uint16_t        curInputs;
    TOKEN_DATA      *pInputs;
    TOKEN_FIELDS    chkData;

};
#pragma pack(pop)

    extern
    struct SrcFile_class_data_s  SrcFile_ClassObj;

    extern
    const
    SRCFILE_VTBL     SrcFile_Vtbl;



    //---------------------------------------------------------------
    //              Class Object Method Forward Definitions
    //---------------------------------------------------------------

#ifdef  SRCFILE_SINGLETON
    SRCFILE_DATA *  SrcFile_getSingleton (
        void
    );

    bool            SrcFile_setSingleton (
     SRCFILE_DATA       *pValue
);
#endif



    //---------------------------------------------------------------
    //              Internal Method Forward Definitions
    //---------------------------------------------------------------

    OBJ_IUNKNOWN *  SrcFile_getSuperVtbl (
        SRCFILE_DATA     *this
    );


    ERESULT         SrcFile_Assign (
        SRCFILE_DATA    *this,
        SRCFILE_DATA    *pOther
    );


    SRCFILE_DATA *  SrcFile_Copy (
        SRCFILE_DATA     *this
    );


    void            SrcFile_Dealloc (
        OBJ_ID          objId
    );


    ERESULT         SrcFile_InputNextChar (
        SRCFILE_DATA    *this
    );


#ifdef  SRCFILE_JSON_SUPPORT
    /*!
     Parse the new object from an established parser.
     @param pParser an established jsonIn Parser Object
     @return    a new object if successful, otherwise, OBJ_NIL
     @warning   Returned object must be released.
     */
    SRCFILE_DATA *       SrcFile_ParseJsonObject (
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
    ERESULT         SrcFile_ParseJsonFields (
        JSONIN_DATA     *pParser,
        SRCFILE_DATA     *pObject
    );
#endif


    /*!
     Preload the lookahead tokens.
     @param     this    object pointer
     @return    If successful, ERESULT_SUCCESS. Otherwise, an ERESULT_*
                error code.
     */
    ERESULT         SrcFile_Preload (
        SRCFILE_DATA    *this
    );


    void *          SrcFile_QueryInfo (
        OBJ_ID          objId,
        uint32_t        type,
        void            *pData
    );


#ifdef  SRCFILE_JSON_SUPPORT
    /*!
     Create a string that describes this object and the objects within it in
     HJSON formt. (See hjson object for details.)
     Example:
     @code
     ASTR_DATA      *pDesc = SrcFile_ToJson(this);
     @endcode
     @param     this    object pointer
     @return    If successful, an AStr object which must be released containing the
                JSON text, otherwise OBJ_NIL.
     @warning   Remember to release the returned AStr object.
     */
    ASTR_DATA *     SrcFile_ToJson (
        SRCFILE_DATA      *this
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
    ERESULT         SrcFile_ToJsonFields (
        SRCFILE_DATA     *this,
        ASTR_DATA       *pStr
    );
#endif




#ifdef NDEBUG
#else
    bool            SrcFile_Validate (
        SRCFILE_DATA       *this
    );
#endif



#ifdef  __cplusplus
}
#endif

#endif  /* SRCFILE_INTERNAL_H */

