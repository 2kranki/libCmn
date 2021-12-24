// vi:nu:et:sts=4 ts=4 sw=4
/* 
 * File:   Exec_internal.h
 *  Generated 10/31/2021 18:53:12
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




#include        <Exec.h>
#include        <AStrArray.h>
#include        <Dir.h>
#include        <Item.h>
#include        <JsonIn.h>
#include        <TextIn.h>
#include        <U16Array.h>


#ifndef EXEC_INTERNAL_H
#define EXEC_INTERNAL_H





#ifdef  __cplusplus
extern "C" {
#endif




    //---------------------------------------------------------------
    //                  Object Data Description
    //---------------------------------------------------------------

#pragma pack(push, 1)
struct Exec_data_s  {
    /* Warning - OBJ_DATA must be first in this object!
     */
    OBJ_DATA        super;
    OBJ_IUNKNOWN    *pSuperVtbl;    // Needed for Inheritance

    // Common Data
    ASTR_DATA       *pStart;
    ASTR_DATA       *pStr;
    OBJARRAY_DATA   *pArray;        // An array of Items
    OBJARRAY_DATA   *pSorted;       // A sorted array of Items
    U16ARRAY_DATA   *pIndex;
    uint32_t        maxIndex;
    OBJARRAY_DATA   *pItems;

};
#pragma pack(pop)

    extern
    struct Exec_class_data_s  Exec_ClassObj;

    extern
    const
    EXEC_VTBL         Exec_Vtbl;



    //---------------------------------------------------------------
    //              Class Object Method Forward Definitions
    //---------------------------------------------------------------

#ifdef  EXEC_SINGLETON
    EXEC_DATA *     Exec_getSingleton (
        void
    );

    bool            Exec_setSingleton (
     EXEC_DATA       *pValue
);
#endif



    //---------------------------------------------------------------
    //              Internal Method Forward Definitions
    //---------------------------------------------------------------

    bool            Exec_setStart (
        EXEC_DATA       *this,
        ASTR_DATA       *pValue
    );


    OBJ_IUNKNOWN *  Exec_getSuperVtbl (
        EXEC_DATA     *this
    );


    ERESULT         Exec_Assign (
        EXEC_DATA    *this,
        EXEC_DATA    *pOther
    );


    EXEC_DATA *       Exec_Copy (
        EXEC_DATA     *this
    );


    void            Exec_Dealloc (
        OBJ_ID          objId
    );


    EXEC_DATA *     Exec_DeepCopy (
        EXEC_DATA       *this
    );


#ifdef  EXEC_JSON_SUPPORT
    /*!
     Parse the new object from an established parser.
     @param pParser an established jsonIn Parser Object
     @return    a new object if successful, otherwise, OBJ_NIL
     @warning   Returned object must be released.
     */
    EXEC_DATA *       Exec_ParseJsonObject (
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
    ERESULT         Exec_ParseJsonFields (
        JSONIN_DATA     *pParser,
        EXEC_DATA     *pObject
    );
#endif


    void *          Exec_QueryInfo (
        OBJ_ID          objId,
        uint32_t        type,
        void            *pData
    );


    /*!
     Read the input file into an array.
     @param     this    object pointer
     @return    if successful, the AStrArray with data.  Otherwise, OBJ_NIL.
     */
    OBJARRAY_DATA * Exec_ReadFile (
        EXEC_DATA       *this,
        TEXTIN_DATA     *pIn
    );


#ifdef  EXEC_JSON_SUPPORT
    /*!
     Create a string that describes this object and the objects within it in
     HJSON formt. (See hjson object for details.)
     Example:
     @code
     ASTR_DATA      *pDesc = Exec_ToJson(this);
     @endcode
     @param     this    object pointer
     @return    If successful, an AStr object which must be released containing the
                JSON text, otherwise OBJ_NIL.
     @warning   Remember to release the returned AStr object.
     */
    ASTR_DATA *     Exec_ToJson (
        EXEC_DATA      *this
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
    ERESULT         Exec_ToJsonFields (
        EXEC_DATA       *this,
        ASTR_DATA       *pStr
    );
#endif


#ifdef NDEBUG
#else
    bool            Exec_Validate (
        EXEC_DATA       *this
    );
#endif


    /*!
     Write out the enum arrays.
     @param     this    object pointer
     @return    if successful, ERESULT_SUCCESS.  Otherwise, an ERESULT_*
                error code.
     */
    ERESULT         Exec_WriteFile (
        EXEC_DATA       *this
    );



#ifdef  __cplusplus
}
#endif

#endif  /* EXEC_INTERNAL_H */

