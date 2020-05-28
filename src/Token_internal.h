// vi:nu:et:sts=4 ts=4 sw=4
/* 
 * File:   Token_internal.h
 *	Generated 01/02/2020 15:58:08
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




#include        <Token.h>
#include        <JsonIn.h>
#include        <SrcLoc_internal.h>


#ifndef TOKEN_INTERNAL_H
#define	TOKEN_INTERNAL_H



#define     PROPERTY_STR_OWNED 1



#ifdef	__cplusplus
extern "C" {
#endif




    //---------------------------------------------------------------
    //                  Object Data Description
    //---------------------------------------------------------------

#pragma pack(push, 1)
struct Token_data_s	{
    /* Warning - OBJ_DATA must be first in this object!
     */
    OBJ_DATA        super;
    OBJ_IUNKNOWN    *pSuperVtbl;    // Needed for Inheritance

    // Common Data
    TOKEN_FIELDS    data;

};
#pragma pack(pop)

    extern
    struct Token_class_data_s  Token_ClassObj;

    extern
    const
    TOKEN_VTBL         Token_Vtbl;



    //---------------------------------------------------------------
    //              Class Object Method Forward Definitions
    //---------------------------------------------------------------

#ifdef  TOKEN_SINGLETON
    TOKEN_DATA *     Token_getSingleton (
        void
    );

    bool            Token_setSingleton (
     TOKEN_DATA       *pValue
);
#endif



    //---------------------------------------------------------------
    //              Internal Method Forward Definitions
    //---------------------------------------------------------------

    OBJ_IUNKNOWN *  Token_getSuperVtbl (
        TOKEN_DATA     *this
    );


    bool            Token_setType(
        TOKEN_DATA      *this,
        uint16_t        value
    );


    void            Token_Dealloc (
        OBJ_ID          objId
    );


#ifdef  TOKEN_JSON_SUPPORT
    /*!
     Parse the new object from an established parser.
     @param pParser an established jsonIn Parser Object
     @return    a new object if successful, otherwise, OBJ_NIL
     @warning   Returned object must be released.
     */
    TOKEN_DATA *       Token_ParseJsonObject (
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
    ERESULT         Token_ParseJsonFields (
        JSONIN_DATA     *pParser,
        TOKEN_DATA     *pObject
    );
#endif




    void *          Token_QueryInfo (
        OBJ_ID          objId,
        uint32_t        type,
        void            *pData
    );


    ERESULT         Token_SetupCharW32(
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
     ERESULT      eRc = Token_SetFnLCC(this,"zyzzy",256,16,CLASS_TERMINAL);
     @endcode
     @param     this    object pointer
     @return    If successful, ERESULT_SUCCESS otherwise an ERESULT_* error code
     */
    ERESULT     Token_SetupFnLCC(
        TOKEN_DATA      *this,
        SRCLOC          *pLoc,
        int32_t         cls
    );


    ERESULT     Token_SetupStrW32(
        TOKEN_DATA      *this,
        SRCLOC          *pLoc,
        int32_t         cls,
        const
        W32CHR_T        *pStr
    );


    uint16_t     Token_StringToType (
        TOKEN_DATA      *this,
        const
        char            *pType
    );


#ifdef  TOKEN_JSON_SUPPORT
    /*!
     Create a string that describes this object and the objects within it in
     HJSON formt. (See hjson object for details.)
     Example:
     @code
     ASTR_DATA      *pDesc = Token_ToJson(this);
     @endcode
     @param     this    object pointer
     @return    If successful, an AStr object which must be released containing the
                JSON text, otherwise OBJ_NIL.
     @warning   Remember to release the returned AStr object.
     */
    ASTR_DATA *     Token_ToJson (
        TOKEN_DATA      *this
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
    ERESULT         Token_ToJsonFields (
        TOKEN_DATA     *this,
        ASTR_DATA       *pStr
    );
#endif


    const
    char *     Token_TypeToString (
        TOKEN_DATA      *this,
        uint16_t        type
    );


#ifdef NDEBUG
#else
    bool			Token_Validate (
        TOKEN_DATA       *this
    );
#endif



#ifdef	__cplusplus
}
#endif

#endif	/* TOKEN_INTERNAL_H */

