// vi:nu:et:sts=4 ts=4 sw=4
/* 
 * File:   Node_internal.h
 *	Generated 01/12/2020 16:09:18
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




#include        <Node.h>
#include        <JsonIn.h>
#include        <listdl.h>
#include        <Name.h>
#include        <NodeArray.h>
#include        <NodeBT.h>
#include        <szData.h>
#include        <szTbl.h>


#ifndef NODE_INTERNAL_H
#define	NODE_INTERNAL_H



#define     PROPERTY_STR_OWNED 1



#ifdef	__cplusplus
extern "C" {
#endif




    //---------------------------------------------------------------
    //                  Object Data Description
    //---------------------------------------------------------------

#pragma pack(push, 1)
struct Node_data_s	{
    /* Warning - OBJ_DATA must be first in this object!
     */
    OBJ_DATA        super;
    OBJ_IUNKNOWN    *pSuperVtbl;    // Needed for Inheritance
#define NODE_DUP_NAME   OBJ_FLAG_USER1  // We allocated Name

    // Common Data
    int32_t         cls;
    int32_t         type;
    uint32_t        unique;
    uint32_t        misc;
    NAME_DATA       *pName;
    OBJ_ID          pData;
    OBJ_ID          pExtra;
    OBJ_ID          pOther;
    NODEBT_DATA     *pProperties;

};
#pragma pack(pop)

    extern
    struct Node_class_data_s  Node_ClassObj;

    extern
    const
    NODE_VTBL         Node_Vtbl;

    extern
    const
    uint32_t        node_cProps;
    extern
    const
    OBJ_PROP        node_pProps[];



    //---------------------------------------------------------------
    //              Class Object Method Forward Definitions
    //---------------------------------------------------------------

#ifdef  NODE_SINGLETON
    NODE_DATA *     Node_getSingleton (
        void
    );

    bool            Node_setSingleton (
     NODE_DATA       *pValue
);
#endif



    //---------------------------------------------------------------
    //              Internal Method Forward Definitions
    //---------------------------------------------------------------

    bool            Node_setName (
        NODE_DATA       *this,
        NAME_DATA       *pValue
    );


    bool            Node_setProperties (
        NODE_DATA       *this,
        NODEBT_DATA     *pValue
    );


    OBJ_IUNKNOWN *  Node_getSuperVtbl (
        NODE_DATA     *this
    );


    void            Node_Dealloc (
        OBJ_ID          objId
    );


#ifdef  NODE_JSON_SUPPORT
    /*!
     Parse the new object from an established parser.
     @param pParser an established jsonIn Parser Object
     @return    a new object if successful, otherwise, OBJ_NIL
     @warning   Returned object must be released.
     */
    NODE_DATA *       Node_ParseJsonObject (
        JSONIN_DATA     *pParser
    );


    /*!
     Parse the object from an established parser.
     @param pParser     an established jsonIn Parser Object
     @param pObject     an Object to be filled in with the
                        parsed fields.
     @return    If successful, ERESULT_SUCCESS. Otherwise, an ERESULT_*
                error code.
     */
    ERESULT         Node_ParseJsonFields(
        JSONIN_DATA     *pParser,
        NODE_DATA       *pObject
    );
#endif


    void *          Node_QueryInfo (
        OBJ_ID          objId,
        uint32_t        type,
        void            *pData
    );


#ifdef  NODE_JSON_SUPPORT
    ASTR_DATA *     Node_ToJson (
        NODE_DATA       *this
    );
#endif




#ifdef NDEBUG
#else
    bool			Node_Validate (
        NODE_DATA       *this
    );
#endif



#ifdef	__cplusplus
}
#endif

#endif	/* NODE_INTERNAL_H */

