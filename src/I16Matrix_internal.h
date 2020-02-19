// vi:nu:et:sts=4 ts=4 sw=4
/* 
 * File:   I16Matrix_internal.h
 *	Generated 02/19/2020 09:50:41
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




#include        <I16Matrix.h>
#include        <JsonIn.h>


#ifndef I16MATRIX_INTERNAL_H
#define	I16MATRIX_INTERNAL_H



#define     PROPERTY_STR_OWNED 1



#ifdef	__cplusplus
extern "C" {
#endif




    //---------------------------------------------------------------
    //                  Object Data Description
    //---------------------------------------------------------------

#pragma pack(push, 1)
struct I16Matrix_data_s	{
    /* Warning - OBJ_DATA must be first in this object!
     */
    OBJ_DATA        super;
    OBJ_IUNKNOWN    *pSuperVtbl;    // Needed for Inheritance

    // Common Data
    uint16_t        size;		    // maximum number of elements
    uint16_t        rsvd16;
    ASTR_DATA       *pStr;

};
#pragma pack(pop)

    extern
    struct I16Matrix_class_data_s  I16Matrix_ClassObj;

    extern
    const
    I16MATRIX_VTBL         I16Matrix_Vtbl;



    //---------------------------------------------------------------
    //              Class Object Method Forward Definitions
    //---------------------------------------------------------------

#ifdef  I16MATRIX_SINGLETON
    I16MATRIX_DATA *     I16Matrix_getSingleton (
        void
    );

    bool            I16Matrix_setSingleton (
     I16MATRIX_DATA       *pValue
);
#endif



    //---------------------------------------------------------------
    //              Internal Method Forward Definitions
    //---------------------------------------------------------------

    OBJ_IUNKNOWN *  I16Matrix_getSuperVtbl (
        I16MATRIX_DATA     *this
    );


    ERESULT         I16Matrix_Assign (
        I16MATRIX_DATA    *this,
        I16MATRIX_DATA    *pOther
    );


    I16MATRIX_DATA *       I16Matrix_Copy (
        I16MATRIX_DATA     *this
    );


    void            I16Matrix_Dealloc (
        OBJ_ID          objId
    );


#ifdef  I16MATRIX_JSON_SUPPORT
    /*!
     Parse the new object from an established parser.
     @param pParser an established jsonIn Parser Object
     @return    a new object if successful, otherwise, OBJ_NIL
     @warning   Returned object must be released.
     */
    I16MATRIX_DATA *       I16Matrix_ParseJsonObject (
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
    ERESULT         I16Matrix_ParseJsonFields (
        JSONIN_DATA     *pParser,
        I16MATRIX_DATA     *pObject
    );
#endif


    void *          I16Matrix_QueryInfo (
        OBJ_ID          objId,
        uint32_t        type,
        void            *pData
    );


#ifdef  I16MATRIX_JSON_SUPPORT
    /*!
     Create a string that describes this object and the objects within it in
     HJSON formt. (See hjson object for details.)
     Example:
     @code
     ASTR_DATA      *pDesc = I16Matrix_ToJson(this);
     @endcode
     @param     this    object pointer
     @return    If successful, an AStr object which must be released containing the
                JSON text, otherwise OBJ_NIL and LastError set to an appropriate
                ERESULT_* error code.
     @warning   Remember to release the returned AStr object.
     */
    ASTR_DATA *     I16Matrix_ToJson (
        I16MATRIX_DATA      *this
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
    ERESULT         I16Matrix_ToJsonFields (
        I16MATRIX_DATA     *this,
        ASTR_DATA       *pStr
    );
#endif




#ifdef NDEBUG
#else
    bool			I16Matrix_Validate (
        I16MATRIX_DATA       *this
    );
#endif



#ifdef	__cplusplus
}
#endif

#endif	/* I16MATRIX_INTERNAL_H */

