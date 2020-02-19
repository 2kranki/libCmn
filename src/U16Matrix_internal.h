// vi:nu:et:sts=4 ts=4 sw=4
/* 
 * File:   U16Matrix_internal.h
 *	Generated 02/18/2020 11:52:42
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




#include        <U16Matrix.h>
#include        <array_internal.h>
#include        <JsonIn.h>


#ifndef U16MATRIX_INTERNAL_H
#define	U16MATRIX_INTERNAL_H



#define     PROPERTY_STR_OWNED 1



#ifdef	__cplusplus
extern "C" {
#endif


typedef struct matrix_build_s {
    uint32_t        m;              // Height (Number of Rows, i)
    uint32_t        n;              // Width (Number of Columns, j)
    uint32_t        baseMax;        // Highest index allowed (m * n)
    uint32_t        maxBase;        // Current Highest Index Used
    uint32_t        highest;        // Highest pCheck entry used
    int32_t         *pBase;            // Row Base Index (j) into VALUE/CHECK
    uint32_t        *pCheck;        // Column Check for Row indexed from pBase
    uint16_t        *pValue;        // Row and Column value given Check
} MATRIX_BUILD;





    //---------------------------------------------------------------
    //                  Object Data Description
    //---------------------------------------------------------------

#pragma pack(push, 1)
struct U16Matrix_data_s	{
    /* Warning - OBJ_DATA must be first in this object!
     */
    ARRAY_DATA      super;
    OBJ_IUNKNOWN    *pSuperVtbl;    // Needed for Inheritance

    // Common Data
    uint32_t        m;              // Height (Number of Rows, j)
    uint32_t        n;              // Width (Number of Columns, i)
    uint32_t        cElems;         // Size of Elems (ie m * n)

};
#pragma pack(pop)

    extern
    struct U16Matrix_class_data_s  U16Matrix_ClassObj;

    extern
    const
    U16MATRIX_VTBL         U16Matrix_Vtbl;



    //---------------------------------------------------------------
    //              Class Object Method Forward Definitions
    //---------------------------------------------------------------

#ifdef  U16MATRIX_SINGLETON
    U16MATRIX_DATA * U16Matrix_getSingleton (
        void
    );

    bool            U16Matrix_setSingleton (
     U16MATRIX_DATA       *pValue
);
#endif



    //---------------------------------------------------------------
    //              Internal Method Forward Definitions
    //---------------------------------------------------------------

    OBJ_IUNKNOWN *  U16Matrix_getSuperVtbl (
        U16MATRIX_DATA     *this
    );


    bool            U16Matrix_AddRowToValueCheck (
        U16MATRIX_DATA  *this,
        MATRIX_BUILD    *pBuild,
        uint32_t        row
    );


    ERESULT         U16Matrix_Assign (
        U16MATRIX_DATA    *this,
        U16MATRIX_DATA    *pOther
    );


    MATRIX_BUILD *  U16Matrix_BuildValueCheck (
        U16MATRIX_DATA  *this
    );


    U16MATRIX_DATA * U16Matrix_Copy (
        U16MATRIX_DATA     *this
    );


    void            U16Matrix_Dealloc (
        OBJ_ID          objId
    );


    ERESULT         U16Matrix_FreeValueCheck (
        U16MATRIX_DATA  *this,
        MATRIX_BUILD    *pBuild
    );


    uint32_t        U16Matrix_Index (
        U16MATRIX_DATA  *this,
        uint32_t        i,
        uint32_t        j
    );


    bool            U16Matrix_IsIndexValid (
        U16MATRIX_DATA  *this,
        uint32_t        i,
        uint32_t        j
    );


#ifdef  U16MATRIX_JSON_SUPPORT
    /*!
     Parse the new object from an established parser.
     @param pParser an established jsonIn Parser Object
     @return    a new object if successful, otherwise, OBJ_NIL
     @warning   Returned object must be released.
     */
    U16MATRIX_DATA * U16Matrix_ParseJsonObject (
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
    ERESULT         U16Matrix_ParseJsonFields (
        JSONIN_DATA     *pParser,
        U16MATRIX_DATA     *pObject
    );
#endif


    void *          U16Matrix_QueryInfo (
        OBJ_ID          objId,
        uint32_t        type,
        void            *pData
    );


    ERESULT         U16Matrix_Setup (
        U16MATRIX_DATA  *this,
        uint32_t        m,
        uint32_t        n
    );


#ifdef  U16MATRIX_JSON_SUPPORT
    /*!
     Create a string that describes this object and the objects within it in
     HJSON formt. (See hjson object for details.)
     Example:
     @code
     ASTR_DATA      *pDesc = U16Matrix_ToJson(this);
     @endcode
     @param     this    object pointer
     @return    If successful, an AStr object which must be released containing the
                JSON text, otherwise OBJ_NIL and LastError set to an appropriate
                ERESULT_* error code.
     @warning   Remember to release the returned AStr object.
     */
    ASTR_DATA *     U16Matrix_ToJson (
        U16MATRIX_DATA      *this
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
    ERESULT         U16Matrix_ToJsonFields (
        U16MATRIX_DATA     *this,
        ASTR_DATA       *pStr
    );
#endif




#ifdef NDEBUG
#else
    bool			U16Matrix_Validate (
        U16MATRIX_DATA       *this
    );
#endif



#ifdef	__cplusplus
}
#endif

#endif	/* U16MATRIX_INTERNAL_H */

