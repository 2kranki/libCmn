// vi:nu:et:sts=4 ts=4 sw=4
/* 
 * File:   NodeRtn_internal.h
 *	Generated 11/03/2019 08:11:37
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




#include        <NodeBase_internal.h>
#include        <NodeRtn.h>
#include        <JsonIn.h>


#ifndef NODERTN_INTERNAL_H
#define	NODERTN_INTERNAL_H



#define     PROPERTY_TEST_OWNED 1



#ifdef	__cplusplus
extern "C" {
#endif




    //---------------------------------------------------------------
    //                  Object Data Description
    //---------------------------------------------------------------

#pragma pack(push, 1)
struct NodeRtn_data_s	{
    /* Warning - OBJ_DATA must be first in this object!
     */
    NODEBASE_DATA   super;
    OBJ_IUNKNOWN    *pSuperVtbl;    // Needed for Inheritance

    // Common Data
    NODETEST_DATA   *pTest;

};
#pragma pack(pop)

    extern
    struct NodeRtn_class_data_s  NodeRtn_ClassObj;

    extern
    const
    NODERTN_VTBL         NodeRtn_Vtbl;



    //---------------------------------------------------------------
    //              Class Object Method Forward Definitions
    //---------------------------------------------------------------

#ifdef  NODERTN_SINGLETON
    NODERTN_DATA *     NodeRtn_getSingleton (
        void
    );

    bool            NodeRtn_setSingleton (
     NODERTN_DATA       *pValue
);
#endif



    //---------------------------------------------------------------
    //              Internal Method Forward Definitions
    //---------------------------------------------------------------

    OBJ_IUNKNOWN *  NodeRtn_getSuperVtbl (
        NODERTN_DATA     *this
    );


    void            NodeRtn_Dealloc (
        OBJ_ID          objId
    );


    NODERTN_DATA *       NodeRtn_ParseObject (
        JSONIN_DATA     *pParser
    );


    void *          NodeRtn_QueryInfo (
        OBJ_ID          objId,
        uint32_t        type,
        void            *pData
    );


    ASTR_DATA *     NodeRtn_ToJSON (
        NODERTN_DATA      *this
    );




#ifdef NDEBUG
#else
    bool			NodeRtn_Validate (
        NODERTN_DATA       *this
    );
#endif



#ifdef	__cplusplus
}
#endif

#endif	/* NODERTN_INTERNAL_H */

