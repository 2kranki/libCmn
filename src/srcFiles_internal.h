// vi:nu:et:sts=4 ts=4 sw=4
/* 
 * File:   SrcFiles_internal.h
 *  Generated 10/19/2020 16:14:31
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




#include        <SrcFiles.h>
#include        <JsonIn.h>


#ifndef SRCFILES_INTERNAL_H
#define SRCFILES_INTERNAL_H





#ifdef  __cplusplus
extern "C" {
#endif




    //---------------------------------------------------------------
    //                  Object Data Description
    //---------------------------------------------------------------

#pragma pack(push, 1)
struct SrcFiles_data_s  {
    /* Warning - OBJ_DATA must be first in this object!
     */
    OBJ_DATA        super;
    OBJ_IUNKNOWN    *pSuperVtbl;    // Needed for Inheritance

    // Common Data
    OBJARRAY_DATA   *pPaths;
    OBJARRAY_DATA   *pStack;
    SRCFILE_DATA    *pTop;
    uint8_t         fReuse;
    uint8_t         rsvd8[3];

};
#pragma pack(pop)

    extern
    struct SrcFiles_class_data_s  SrcFiles_ClassObj;

    extern
    const
    SRCFILES_VTBL         SrcFiles_Vtbl;



    //---------------------------------------------------------------
    //              Class Object Method Forward Definitions
    //---------------------------------------------------------------

#ifdef  SRCFILES_SINGLETON
    SRCFILES_DATA * SrcFiles_getSingleton (
        void
    );

    bool            SrcFiles_setSingleton (
     SRCFILES_DATA       *pValue
);
#endif



    //---------------------------------------------------------------
    //              Internal Method Forward Definitions
    //---------------------------------------------------------------

    bool            SrcFiles_setPaths(
        SRCFILES_DATA   *this,
        OBJARRAY_DATA   *pValue
    );


    OBJ_IUNKNOWN *  SrcFiles_getSuperVtbl (
        SRCFILES_DATA     *this
    );


    ERESULT         SrcFiles_Assign (
        SRCFILES_DATA    *this,
        SRCFILES_DATA    *pOther
    );


    SRCFILES_DATA * SrcFiles_Copy (
        SRCFILES_DATA     *this
    );


    void            SrcFiles_Dealloc (
        OBJ_ID          objId
    );


#ifdef  SRCFILES_JSON_SUPPORT
    /*!
     Parse the new object from an established parser.
     @param pParser an established jsonIn Parser Object
     @return    a new object if successful, otherwise, OBJ_NIL
     @warning   Returned object must be released.
     */
    SRCFILES_DATA * SrcFiles_ParseJsonObject (
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
    ERESULT         SrcFiles_ParseJsonFields (
        JSONIN_DATA     *pParser,
        SRCFILES_DATA   *pObject
    );
#endif


    void *          SrcFiles_QueryInfo (
        OBJ_ID          objId,
        uint32_t        type,
        void            *pData
    );


#ifdef  SRCFILES_JSON_SUPPORT
    /*!
     Create a string that describes this object and the objects within it in
     HJSON formt. (See hjson object for details.)
     Example:
     @code
     ASTR_DATA      *pDesc = SrcFiles_ToJson(this);
     @endcode
     @param     this    object pointer
     @return    If successful, an AStr object which must be released containing the
                JSON text, otherwise OBJ_NIL.
     @warning   Remember to release the returned AStr object.
     */
    ASTR_DATA *     SrcFiles_ToJson (
        SRCFILES_DATA    *this
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
    ERESULT         SrcFiles_ToJsonFields (
        SRCFILES_DATA   *this,
        ASTR_DATA       *pStr
    );
#endif




#ifdef NDEBUG
#else
    bool            SrcFiles_Validate (
        SRCFILES_DATA       *this
    );
#endif



#ifdef  __cplusplus
}
#endif

#endif  /* SRCFILES_INTERNAL_H */

