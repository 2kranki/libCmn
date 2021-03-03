// vi:nu:et:sts=4 ts=4 sw=4
/* 
 * File:   NodeLink_internal.h
 *  Generated 02/03/2021 18:58:16
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




#include        <NodeLink.h>
#include        <JsonIn.h>
#include        <Node_internal.h>


#ifndef NODELINK_INTERNAL_H
#define NODELINK_INTERNAL_H





#ifdef  __cplusplus
extern "C" {
#endif




    //---------------------------------------------------------------
    //                  Object Data Description
    //---------------------------------------------------------------

#pragma pack(push, 1)
struct NodeLink_data_s  {
    /* Warning - OBJ_DATA must be first in this object!
     */
    NODE_DATA       super;
    OBJ_IUNKNOWN    *pSuperVtbl;    // Needed for Inheritance
#define NODELINK_LEFT_LINK   OBJ_FLAG_USER5
#define NODELINK_RIGHT_LINK  OBJ_FLAG_USER6
#define NODELINK_RIGHT_CHILD OBJ_FLAG_USER7

    // Common Data
    uint32_t        index;
    uint32_t        leftIndex;
    uint32_t        middleIndex;
    uint32_t        parentIndex;
    uint32_t        rightIndex;

};
#pragma pack(pop)

    extern
    struct NodeLink_class_data_s  NodeLink_ClassObj;

    extern
    const
    NODELINK_VTBL         NodeLink_Vtbl;



    //---------------------------------------------------------------
    //              Class Object Method Forward Definitions
    //---------------------------------------------------------------

#ifdef  NODELINK_SINGLETON
    NODELINK_DATA * NodeLink_getSingleton (
        void
    );

    bool            NodeLink_setSingleton (
     NODELINK_DATA       *pValue
);
#endif



    //---------------------------------------------------------------
    //              Internal Method Forward Definitions
    //---------------------------------------------------------------

    OBJ_IUNKNOWN *  NodeLink_getSuperVtbl (
        NODELINK_DATA   *this
    );


    ERESULT         NodeLink_Assign (
        NODELINK_DATA   *this,
        NODELINK_DATA   *pOther
    );


    NODELINK_DATA * NodeLink_Copy (
        NODELINK_DATA   *this
    );


    void            NodeLink_Dealloc (
        OBJ_ID          objId
    );


#ifdef  NODELINK_JSON_SUPPORT
    /*!
     Parse the new object from an established parser.
     @param pParser an established jsonIn Parser Object
     @return    a new object if successful, otherwise, OBJ_NIL
     @warning   Returned object must be released.
     */
    NODELINK_DATA * NodeLink_ParseJsonObject (
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
    ERESULT         NodeLink_ParseJsonFields (
        JSONIN_DATA     *pParser,
        NODELINK_DATA   *pObject
    );
#endif


    void *          NodeLink_QueryInfo (
        OBJ_ID          objId,
        uint32_t        type,
        void            *pData
    );


#ifdef  NODELINK_JSON_SUPPORT
    /*!
     Create a string that describes this object and the objects within it in
     HJSON formt. (See hjson object for details.)
     Example:
     @code
     ASTR_DATA      *pDesc = NodeLink_ToJson(this);
     @endcode
     @param     this    object pointer
     @return    If successful, an AStr object which must be released containing the
                JSON text, otherwise OBJ_NIL.
     @warning   Remember to release the returned AStr object.
     */
    ASTR_DATA *     NodeLink_ToJson (
        NODELINK_DATA   *this
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
    ERESULT         NodeLink_ToJsonFields (
        NODELINK_DATA   *this,
        ASTR_DATA       *pStr
    );
#endif




#ifdef NDEBUG
#else
    bool            NodeLink_Validate (
        NODELINK_DATA   *this
    );
#endif



#ifdef  __cplusplus
}
#endif

#endif  /* NODELINK_INTERNAL_H */

