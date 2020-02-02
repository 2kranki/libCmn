// vi:nu:et:sts=4 ts=4 sw=4
/* 
 * File:   NodeProp_internal.h
 *	Generated 12/18/2019 23:31:17
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




#include        <NodeProp.h>
#include        <JsonIn.h>


#ifndef NODEPROP_INTERNAL_H
#define	NODEPROP_INTERNAL_H



#define     PROPERTY_STR_OWNED 1



#ifdef	__cplusplus
extern "C" {
#endif




    //---------------------------------------------------------------
    //                  Object Data Description
    //---------------------------------------------------------------

#pragma pack(push, 1)
struct NodeProp_data_s	{
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
    struct NodeProp_class_data_s  NodeProp_ClassObj;

    extern
    const
    NODEPROP_VTBL         NodeProp_Vtbl;



    //---------------------------------------------------------------
    //              Class Object Method Forward Definitions
    //---------------------------------------------------------------

#ifdef  NODEPROP_SINGLETON
    NODEPROP_DATA *     NodeProp_getSingleton (
        void
    );

    bool            NodeProp_setSingleton (
     NODEPROP_DATA       *pValue
);
#endif



    //---------------------------------------------------------------
    //              Internal Method Forward Definitions
    //---------------------------------------------------------------

    OBJ_IUNKNOWN *  NodeProp_getSuperVtbl (
        NODEPROP_DATA     *this
    );


    void            NodeProp_Dealloc (
        OBJ_ID          objId
    );


#ifdef  NODEPROP_JSON_SUPPORT
    NODEPROP_DATA *       NodeProp_ParseJsonObject (
        JSONIN_DATA     *pParser
    );
#endif


    void *          NodeProp_QueryInfo (
        OBJ_ID          objId,
        uint32_t        type,
        void            *pData
    );


#ifdef  SRCREF_JSON_SUPPORT
    ASTR_DATA *     NodeProp_ToJson (
        NODEPROP_DATA      *this
    );
#endif




#ifdef NDEBUG
#else
    bool			NodeProp_Validate (
        NODEPROP_DATA       *this
    );
#endif



#ifdef	__cplusplus
}
#endif

#endif	/* NODEPROP_INTERNAL_H */

