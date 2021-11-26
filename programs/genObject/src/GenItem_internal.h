// vi:nu:et:sts=4 ts=4 sw=4
/* 
 * File:   GenItem_internal.h
 *  Generated 11/21/2021 11:15:18
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




#include        <GenItem.h>
#include        <JsonIn.h>


#ifndef GENITEM_INTERNAL_H
#define GENITEM_INTERNAL_H





#ifdef  __cplusplus
extern "C" {
#endif




    //---------------------------------------------------------------
    //                  Object Data Description
    //---------------------------------------------------------------

#pragma pack(push, 1)
struct GenItem_data_s  {
    /* Warning - OBJ_DATA must be first in this object!
     */
    OBJ_DATA        super;
    OBJ_IUNKNOWN    *pSuperVtbl;    // Needed for Inheritance

    // Common Data
    DICT_DATA       *pDict;
    PATH_DATA       *pModel;
    PATH_DATA       *pOutput;
    uint16_t        size;           // maximum number of elements
    uint16_t        rsvd16;
    ASTR_DATA       *pFile;

    // Look up an item in the dictionary. If it is not found,
    // look it up in the Environment Variables. Return the first
    // one found or NULL.
    const char *    (*pDictLookupA)(OBJ_ID, const char *);
    OBJ_ID          pDictObj;

    ERESULT         (*pGen)(OBJ_ID, const char *);
    OBJ_ID          pGenObj;

    OBJ_ID          pLog;
    
};
#pragma pack(pop)

    extern
    struct GenItem_class_data_s  GenItem_ClassObj;

    extern
    const
    GENITEM_VTBL         GenItem_Vtbl;



    //---------------------------------------------------------------
    //              Class Object Method Forward Definitions
    //---------------------------------------------------------------

#ifdef  GENITEM_SINGLETON
    GENITEM_DATA *  GenItem_getSingleton (
        void
    );

    bool            GenItem_setSingleton (
     GENITEM_DATA       *pValue
);
#endif



    //---------------------------------------------------------------
    //              Internal Method Forward Definitions
    //---------------------------------------------------------------

    OBJ_IUNKNOWN *  GenItem_getSuperVtbl (
        GENITEM_DATA    *this
    );


    ERESULT         GenItem_Assign (
        GENITEM_DATA    *this,
        GENITEM_DATA    *pOther
    );


    GENITEM_DATA *  GenItem_Copy (
        GENITEM_DATA    *this
    );


    void            GenItem_Dealloc (
        OBJ_ID          objId
    );


    GENITEM_DATA *  GenItem_DeepCopy (
        GENITEM_DATA    *this
    );


#ifdef  GENITEM_JSON_SUPPORT
    /*!
     Parse the new object from an established parser.
     @param pParser an established jsonIn Parser Object
     @return    a new object if successful, otherwise, OBJ_NIL
     @warning   Returned object must be released.
     */
    GENITEM_DATA *  GenItem_ParseJsonObject (
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
    ERESULT         GenItem_ParseJsonFields (
        JSONIN_DATA     *pParser,
        GENITEM_DATA    *pObject
    );
#endif


    /*!
     The text in the input is part of the argument to an %ifdef or %ifndef.
     Evaluate the text as a boolean expression.  Return true or false.
     @param     this    object pointer
     @return    exprssion evaluates to a true (1+) or false (0).
     */
    int             GenItem_PreProcBoolEval (
        GENITEM_DATA    *this,
        char            *z,
        int             lineno
    );


    void *          GenItem_QueryInfo (
        OBJ_ID          objId,
        uint32_t        type,
        void            *pData
    );


#ifdef  GENITEM_JSON_SUPPORT
    /*!
     Create a string that describes this object and the objects within it in
     HJSON formt. (See hjson object for details.)
     Example:
     @code
     ASTR_DATA      *pDesc = GenItem_ToJson(this);
     @endcode
     @param     this    object pointer
     @return    If successful, an AStr object which must be released containing the
                JSON text, otherwise OBJ_NIL.
     @warning   Remember to release the returned AStr object.
     */
    ASTR_DATA *     GenItem_ToJson (
        GENITEM_DATA    *this
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
    ERESULT         GenItem_ToJsonFields (
        GENITEM_DATA    *this,
        ASTR_DATA       *pStr
    );
#endif




#ifdef NDEBUG
#else
    bool            GenItem_Validate (
        GENITEM_DATA       *this
    );
#endif



#ifdef  __cplusplus
}
#endif

#endif  /* GENITEM_INTERNAL_H */

