// vi:nu:et:sts=4 ts=4 sw=4
/* 
 * File:   Index_internal.h
 *  Generated 12/22/2021 13:33:31
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




#include        <Index.h>
#include        <JsonIn.h>


#ifndef INDEX_INTERNAL_H
#define INDEX_INTERNAL_H





#ifdef  __cplusplus
extern "C" {
#endif




    //---------------------------------------------------------------
    //                  Object Data Description
    //---------------------------------------------------------------

#pragma pack(push, 1)
struct Index_data_s  {
    /* Warning - OBJ_DATA must be first in this object!
     */
    OBJ_DATA        super;
    OBJ_IUNKNOWN    *pSuperVtbl;    // Needed for Inheritance

    // Common Data
    ASTR_DATA       *pDrv;
    PATHARRAY_DATA  *pExcludes;
    PATHARRAY_DATA  *pTop;
    PATH_DATA       *pDir;
    PATH_DATA       *pPath;
    NODETREE_DATA   *pTree;
    OBJARRAY_DATA   *pItems;

#ifdef   INDEX_LOG
    // Informational and Warning Log Messages
    OBJ_ID          *pLog;
#endif
};
#pragma pack(pop)

    extern
    struct Index_class_data_s  Index_ClassObj;

    extern
    const
    INDEX_VTBL         Index_Vtbl;



    //---------------------------------------------------------------
    //              Class Object Method Forward Definitions
    //---------------------------------------------------------------

#ifdef  INDEX_SINGLETON
    INDEX_DATA *     Index_getSingleton (
        void
    );

    bool            Index_setSingleton (
     INDEX_DATA       *pValue
);
#endif



    //---------------------------------------------------------------
    //              Internal Method Forward Definitions
    //---------------------------------------------------------------

    INDEX_DATA *  Index_getSuper (
        INDEX_DATA     *this
    );


    OBJ_IUNKNOWN *  Index_getSuperVtbl (
        INDEX_DATA     *this
    );


    ERESULT         Index_Assign (
        INDEX_DATA    *this,
        INDEX_DATA    *pOther
    );


    INDEX_DATA *    Index_Copy (
        INDEX_DATA     *this
    );


    void            Index_Dealloc (
        OBJ_ID          objId
    );


    INDEX_DATA *     Index_DeepCopy (
        INDEX_DATA       *this
    );


    /*!
     Gather up the items that will make up the main and site link indices.
     @param     this    object pointer
     @param     pPath   Path object pointer to subdirectory with items in it.
     @return    if successful, ERESULT_SUCCESS.  Otherwise, an ERESULT_*
                error code.
     */
    ERESULT         Index_GatherItems (
        INDEX_DATA      *this,
        PATH_DATA       *pPath
    );


#ifdef  INDEX_JSON_SUPPORT
    /*!
     Parse the new object from an established parser.
     @param pParser an established jsonIn Parser Object
     @return    a new object if successful, otherwise, OBJ_NIL
     @warning   Returned object must be released.
     */
    INDEX_DATA *       Index_ParseJsonObject (
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
    ERESULT         Index_ParseJsonFields (
        JSONIN_DATA     *pParser,
        INDEX_DATA     *pObject
    );
#endif


    void *          Index_QueryInfo (
        OBJ_ID          objId,
        uint32_t        type,
        void            *pData
    );


#ifdef  INDEX_JSON_SUPPORT
    /*!
     Create a string that describes this object and the objects within it in
     HJSON formt. (See hjson object for details.)
     Example:
     @code
     ASTR_DATA      *pDesc = Index_ToJson(this);
     @endcode
     @param     this    object pointer
     @return    If successful, an AStr object which must be released containing the
                JSON text, otherwise OBJ_NIL.
     @warning   Remember to release the returned AStr object.
     */
    ASTR_DATA *     Index_ToJson (
        INDEX_DATA      *this
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
    ERESULT         Index_ToJsonFields (
        INDEX_DATA     *this,
        ASTR_DATA       *pStr
    );
#endif




#ifdef NDEBUG
#else
    bool            Index_Validate (
        INDEX_DATA       *this
    );
#endif



#ifdef  __cplusplus
}
#endif

#endif  /* INDEX_INTERNAL_H */

